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
    
    // Fixed look-ahead index (speed controlled externally)
    size_t adaptiveLookAheadIndex = parameters_.lookAheadIndex;
    
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
    double curvature = 0.15 * curvatures[0] + 0.7 * curvatures[1] + 0.15 * curvatures[2];
    
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

    // Use fixed control gains (speed controlled externally)
    double speedAdaptiveKDistance = parameters_.kDistance;
    double speedAdaptiveKAngle = parameters_.kAngle;
    
    // Predictive control: consider future trajectory points for better anticipation
    double predictiveError = 0.0;
    // Temporarily disable predictive control for debugging
    /*
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
            double rawPredictiveError = futureDirection.x() * vehicleToFuture.y() - futureDirection.y() * vehicleToFuture.x();
            
            // Reduce predictive control influence for small field with sharp turns
            double curvatureMagnitude = std::abs(curvature);
            // Lower gain overall for small field, higher gain only for very sharp turns
            double predictiveGain = std::min(0.15, curvatureMagnitude * 0.8 + 0.05);
            predictiveError = rawPredictiveError * predictiveGain;
        }
    }
    */
    
    // Enhanced control law with adaptive gains and predictive control
    double feedforwardControl = curvature;
    double lateralFeedback = speedAdaptiveKDistance * (errorSignedDistance + predictiveError);
    double angularFeedback = speedAdaptiveKAngle * errorAngle;
    
    // Debug: print values for troubleshooting
    // std::cout << "errorSignedDistance: " << errorSignedDistance << std::endl;
    // std::cout << "predictiveError: " << predictiveError << std::endl;
    // std::cout << "feedforwardControl: " << feedforwardControl << std::endl;
    // std::cout << "lateralFeedback: " << lateralFeedback << std::endl;
    // std::cout << "angularFeedback: " << angularFeedback << std::endl;
    
    double currentU = feedforwardControl - lateralFeedback - angularFeedback;
    
    // Improved adaptive filtering with proper state management
    // Use static variable approach for filtering
    static double previousU = 0.0;
    static double previousCurvature = 0.0;
    
    // Detect curvature change rate to adjust filter aggressiveness
    double curvatureChangeRate = std::abs(curvature - previousCurvature);
    double adaptiveFilterWeight = std::max(0.4, std::min(0.8, 1.0 - curvatureChangeRate * 2.0));
    
    // Reset filter when transitioning from curve to straight
    bool isTransitionToStraight = (std::abs(previousCurvature) > 0.5 && std::abs(curvature) < 0.2);
    if (isTransitionToStraight) {
        adaptiveFilterWeight = 0.85;
    }
    
    double filteredU = adaptiveFilterWeight * currentU + (1.0 - adaptiveFilterWeight) * previousU;
    
    // Additional overshoot prevention
    if ((currentU > 0.2 && previousU < -0.2) || (currentU < -0.2 && previousU > 0.2)) {
        filteredU = 0.7 * currentU + 0.3 * previousU;
    }
    
    previousU = filteredU;
    previousCurvature = curvature;
    
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
