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

    // Initial curvature calculation for adaptive speed adjustment
    size_t speedCurvatureIndex = std::clamp(
        indexOfClosestPointOnTrajectory + 1, static_cast<size_t>(1), trajectory.size() - 2);
    Position speedPrevPoint = trajectory[speedCurvatureIndex - 1].pose.translation();
    Position speedCurrPoint = trajectory[speedCurvatureIndex].pose.translation();
    Position speedNextPoint = trajectory[speedCurvatureIndex + 1].pose.translation();
    double speedCurvature = utils::discreteCurvature(speedPrevPoint, speedCurrPoint, speedNextPoint);
    
    // Adaptive speed reduction in curves for smoother cornering
    double curvatureSpeedFactor = 1.0;
    if (std::abs(speedCurvature) > 0.05) {  // Apply speed reduction for curves
        // Reduce speed proportionally to curvature magnitude
        // Higher curvature = more speed reduction
        double curvatureMagnitude = std::abs(speedCurvature);
        curvatureSpeedFactor = 1.0 / (1.0 + curvatureMagnitude * 3.0);  // Adjustable factor
        curvatureSpeedFactor = std::max(curvatureSpeedFactor, 0.3);  // Minimum 30% of original speed
    }
    
    // Apply smooth speed adjustment
    double adjustedSpeed = desiredSpeed * curvatureSpeedFactor;
    
    // Stop the car if the speed is below the minimum speed threshold
    double speed = adjustedSpeed < parameters_.minVelocityThreshold ? 0 : adjustedSpeed;

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
    
    // Use improved 5-point curvature estimation with Gaussian-like weights for smoother results
    std::vector<double> curvatures;
    std::vector<double> weights = {0.15, 0.7, 0.15};  // More weight to center, Gaussian-like distribution
    for (int offset = -1; offset <= 1; offset++) {
        size_t idx = std::clamp(static_cast<int>(indexForCurvatureEstimation) + offset, 
                               static_cast<int>(1), static_cast<int>(trajectory.size() - 2));
        Position prevPoint = trajectory[idx - 1].pose.translation();
        Position currPoint = trajectory[idx].pose.translation();
        Position nextPoint = trajectory[idx + 1].pose.translation();
        curvatures.push_back(utils::discreteCurvature(prevPoint, currPoint, nextPoint));
    }
    // Weighted average of curvatures with improved weights
    double curvature = weights[0] * curvatures[0] + weights[1] * curvatures[1] + weights[2] * curvatures[2];
    
    // Apply curvature smoothing to prevent sudden changes
    static double previousCurvature = 0.0;
    double curvatureSmoothingFactor = 0.6;  // Smooth curvature changes
    curvature = curvatureSmoothingFactor * curvature + (1.0 - curvatureSmoothingFactor) * previousCurvature;
    previousCurvature = curvature;
    
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

    // Enhanced speed-adaptive control gains with dynamic error-based adjustment
    double errorMagnitude = std::sqrt(errorSignedDistance * errorSignedDistance + errorAngle * errorAngle);
    double errorAdaptiveGain = 1.0 + std::min(2.0, errorMagnitude * 0.5);  // Increase gains for larger errors
    double speedAdaptiveKDistance = parameters_.kDistance * errorAdaptiveGain / (1.0 + speed * 0.3);
    double speedAdaptiveKAngle = parameters_.kAngle * errorAdaptiveGain / (1.0 + speed * 0.2);
    
    // Enhanced predictive control with speed-dependent horizon
    double predictiveError = 0.0;
    if (indexForCurvatureEstimation + 2 < trajectory.size()) {
        // Dynamic prediction horizon based on speed
        size_t predictionHorizon = std::max(2, static_cast<int>(2 + speed * 0.5));  // Longer horizon at higher speeds
        size_t futureIndex = std::min(indexForCurvatureEstimation + predictionHorizon, trajectory.size() - 1);
        Position futurePoint = trajectory[futureIndex].pose.translation();
        Position currentPos = vehiclePose.translation();
        
        // Calculate predicted lateral error with improved direction estimation
        Eigen::Vector2d futureDirection = futurePoint - lookAheadPoint;
        if (futureDirection.norm() > 0.1) {  // Avoid division by near-zero
            futureDirection.normalize();
            Eigen::Vector2d vehicleToFuture = futurePoint - currentPos;
            predictiveError = futureDirection.x() * vehicleToFuture.y() - futureDirection.y() * vehicleToFuture.x();
            
            // Speed-dependent predictive scaling
            double predictiveScale = 0.2 + speed * 0.05;  // Higher prediction influence at higher speeds
            predictiveScale = std::min(predictiveScale, 0.4);  // Cap at 0.4
            predictiveError *= predictiveScale;
        }
    }
    
    // Enhanced control law with deadband for small errors to reduce jitter
    double feedforwardControl = curvature;
    
    // Apply deadband to lateral error to prevent jitter from small errors
    double adjustedLateralError = errorSignedDistance + predictiveError;
    if (std::abs(adjustedLateralError) < 0.02) {  // 2cm deadband
        adjustedLateralError *= 0.3;  // Reduce response for very small errors
    }
    
    // Apply deadband to angular error
    double adjustedAngularError = errorAngle;
    if (std::abs(adjustedAngularError) < 0.02) {  // ~1.1 degree deadband
        adjustedAngularError *= 0.3;  // Reduce response for very small errors
    }
    
    double lateralFeedback = speedAdaptiveKDistance * adjustedLateralError;
    double angularFeedback = speedAdaptiveKAngle * adjustedAngularError;
    
    // Adaptive low-pass filter with speed-dependent coefficients
    static double previousU = 0.0;
    double currentU = feedforwardControl - lateralFeedback - angularFeedback;
    
    // More aggressive filtering at high speeds, less at low speeds
    double filterCoeff = 0.5 + speed * 0.1;  // 0.5 to 0.7 range
    filterCoeff = std::min(filterCoeff, 0.8);  // Cap at 0.8
    double filteredU = filterCoeff * currentU + (1.0 - filterCoeff) * previousU;
    previousU = filteredU;
    
    double steeringAngle = std::atan(parameters_.wheelBase * filteredU);
    
    // Add rate limiting to prevent sudden steering changes
    static double previousSteeringAngle = 0.0;
    double maxSteeringRate = 0.5;  // Maximum change per control cycle (radians)
    double steeringChange = steeringAngle - previousSteeringAngle;
    if (std::abs(steeringChange) > maxSteeringRate) {
        steeringAngle = previousSteeringAngle + std::copysign(maxSteeringRate, steeringChange);
    }
    
    steeringAngle = std::clamp(steeringAngle, -parameters_.steeringAngleMax, parameters_.steeringAngleMax);
    previousSteeringAngle = steeringAngle;

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
