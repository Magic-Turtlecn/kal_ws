#include "controller.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <tuple>

#include "internal/utils.hpp"


namespace kal_controller {

ControlCommand Controller::getControlCommand(const Pose& vehiclePose,
                                             const Trajectory& trajectory,
                                             const bool returnDebugInfo /* = false*/) const {
    throwIfParametersNotInitialized();

    size_t indexOfClosestPointOnTrajectory =
        utils::findIndexOfClosestPointOnTrajectory(trajectory, vehiclePose.translation());

    // Compute desired speed
    size_t indexForEstimation =
        std::clamp(indexOfClosestPointOnTrajectory, static_cast<size_t>(0), trajectory.size() - 2);
    StampedPose firstStampedPose = trajectory[indexForEstimation];
    StampedPose secondStampedPose = trajectory[indexForEstimation + 1];
    double desiredSpeed = utils::computeDesiredSpeed(firstStampedPose, secondStampedPose);

    // Stop the car if the speed is below the minimum speed threshold
    double speed = desiredSpeed < parameters_.minVelocityThreshold ? 0 : desiredSpeed;

    // Compute adaptive look-ahead distance based on speed and initial curvature estimate
    if (parameters_.lookAheadIndex < 1) {
        throw std::out_of_range("Look ahead index must be 1 or larger.");
    }
    
    // Initial curvature estimation for adaptive look-ahead
    size_t initialCurvatureIndex = std::clamp(
        indexOfClosestPointOnTrajectory + parameters_.lookAheadIndex, static_cast<size_t>(1), trajectory.size() - 2);
    Position initPrevPoint = trajectory[initialCurvatureIndex - 1].pose.translation();
    Position initCurrPoint = trajectory[initialCurvatureIndex].pose.translation();
    Position initNextPoint = trajectory[initialCurvatureIndex + 1].pose.translation();
    double initialCurvature = utils::discreteCurvature(initPrevPoint, initCurrPoint, initNextPoint);
    
    // Adaptive look-ahead index calculation
    double speedFactor = std::max(0.5, std::min(2.0, speed / 2.0));  // Speed factor between 0.5-2.0
    double curvatureFactor = 1.0 / (1.0 + std::abs(initialCurvature) * 20.0);  // Reduce look-ahead in curves
    size_t adaptiveLookAheadIndex = std::max(static_cast<size_t>(1), 
        static_cast<size_t>(parameters_.lookAheadIndex * speedFactor * curvatureFactor));
    
    // Compute improved trajectory curvature using multiple points for smoothing
    size_t indexForCurvatureEstimation = std::clamp(
        indexOfClosestPointOnTrajectory + adaptiveLookAheadIndex, static_cast<size_t>(2), trajectory.size() - 3);
    
    // Use 5-point curvature estimation for better smoothness
    std::vector<double> curvatures;
    for (int offset = -1; offset <= 1; offset++) {
        size_t idx = std::clamp(static_cast<int>(indexForCurvatureEstimation) + offset, 
                               static_cast<int>(1), static_cast<int>(trajectory.size() - 2));
        Position prevPoint = trajectory[idx - 1].pose.translation();
        Position currPoint = trajectory[idx].pose.translation();
        Position nextPoint = trajectory[idx + 1].pose.translation();
        curvatures.push_back(utils::discreteCurvature(prevPoint, currPoint, nextPoint));
    }
    // Weighted average of curvatures (center point gets higher weight)
    double curvature = 0.25 * curvatures[0] + 0.5 * curvatures[1] + 0.25 * curvatures[2];
    
    Position lookAheadPoint = trajectory[indexForCurvatureEstimation].pose.translation();

    // Compute angle between road and vehicle orientation
    Eigen::Vector2d targetDirection = secondStampedPose.pose.translation() - firstStampedPose.pose.translation();
    double anglePath = std::atan2(targetDirection.y(), targetDirection.x());
    double yawVehicle = Eigen::Rotation2Dd(vehiclePose.rotation()).angle();
    double errorAngle = utils::normalizeAnglePlusMinusPi(yawVehicle - anglePath);

    // Compute signed distance between vehicle and trajectory
    double errorSignedDistance = utils::signedDistanceBetweenPointAndLine(
        vehiclePose.translation(),
        std::make_tuple(firstStampedPose.pose.translation(), secondStampedPose.pose.translation()));

    // Speed-adaptive control gains to prevent oscillation at high speeds
    double speedAdaptiveKDistance = parameters_.kDistance / (1.0 + speed * 0.3);
    double speedAdaptiveKAngle = parameters_.kAngle / (1.0 + speed * 0.2);
    
    // Predictive control: consider future trajectory points for better anticipation
    double predictiveError = 0.0;
    if (indexForCurvatureEstimation + 2 < trajectory.size()) {
        // Look 2 more points ahead for predictive control
        size_t futureIndex = std::min(indexForCurvatureEstimation + 2, trajectory.size() - 1);
        Position futurePoint = trajectory[futureIndex].pose.translation();
        Position currentPos = vehiclePose.translation();
        
        // Calculate predicted lateral error
        Eigen::Vector2d futureDirection = futurePoint - lookAheadPoint;
        if (futureDirection.norm() > 0.1) {  // Avoid division by near-zero
            futureDirection.normalize();
            Eigen::Vector2d vehicleToFuture = futurePoint - currentPos;
            predictiveError = futureDirection.x() * vehicleToFuture.y() - futureDirection.y() * vehicleToFuture.x();
            predictiveError *= 0.3;  // Scale down predictive term
        }
    }
    
    // Enhanced control law with adaptive gains and predictive control
    double feedforwardControl = curvature;
    double lateralFeedback = speedAdaptiveKDistance * (errorSignedDistance + predictiveError);
    double angularFeedback = speedAdaptiveKAngle * errorAngle;
    
    // Low-pass filter for smoother control (simple exponential filter)
    static double previousU = 0.0;
    double currentU = feedforwardControl - lateralFeedback - angularFeedback;
    double filteredU = 0.7 * currentU + 0.3 * previousU;  // 70% current, 30% previous
    previousU = filteredU;
    
    double steeringAngle = std::atan(parameters_.wheelBase * filteredU);
    steeringAngle = std::clamp(steeringAngle, -parameters_.steeringAngleMax, parameters_.steeringAngleMax);

    std::optional<ControlCommand::DebugInfo> debugInfo;
    if (returnDebugInfo) {
        debugInfo.emplace();
        debugInfo->closestPointOnTrajectory = trajectory[indexOfClosestPointOnTrajectory].pose.translation();
        debugInfo->lookAheadPoint = lookAheadPoint;
        debugInfo->anglePath = anglePath;
        debugInfo->curvature = curvature;
        debugInfo->errorAngle = errorAngle;
        debugInfo->errorSignedDistance = errorSignedDistance;
        debugInfo->yawVehicle = yawVehicle;
    }

    return {speed, steeringAngle, debugInfo};
}

void Controller::throwIfParametersNotInitialized() const {
    if (!parameterInitialized_) {
        throw std::runtime_error("Controller parameters are not initialized!");
    }
}

} // namespace kal_controller
