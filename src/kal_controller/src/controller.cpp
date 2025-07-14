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

    // Compute trajectory curvature with adaptive lookahead
    if (parameters_.lookAheadIndex < 1) {
        throw std::out_of_range("Look ahead index must be 1 or larger.");
    }
    
    // Initial curvature estimation using base lookahead
    size_t baseLookaheadIndex = std::clamp(
        indexOfClosestPointOnTrajectory + parameters_.lookAheadIndex, static_cast<size_t>(1), trajectory.size() - 2);
    Position basePreviousPoint = trajectory[baseLookaheadIndex - 1].pose.translation();
    Position baseLookAheadPoint = trajectory[baseLookaheadIndex].pose.translation();
    Position baseNextPoint = trajectory[baseLookaheadIndex + 1].pose.translation();
    double baseCurvature = utils::discreteCurvature(basePreviousPoint, baseLookAheadPoint, baseNextPoint);
    
    // Adaptive lookahead based on curvature - reduce lookahead for tight curves
    double curvatureMagnitude = std::abs(baseCurvature);
    double adaptiveLookaheadFactor = 1.0;
    
    // For tight curves (curvature > 1.0), reduce lookahead
    if (curvatureMagnitude > 1.0) {
        adaptiveLookaheadFactor = 0.5;
    } else if (curvatureMagnitude > 0.5) {
        adaptiveLookaheadFactor = 0.7;
    }
    
    size_t adaptiveLookaheadIndex = std::max(
        static_cast<size_t>(1), 
        static_cast<size_t>(parameters_.lookAheadIndex * adaptiveLookaheadFactor));
    
    size_t indexForCurvatureEstimation = std::clamp(
        indexOfClosestPointOnTrajectory + adaptiveLookaheadIndex, static_cast<size_t>(1), trajectory.size() - 2);
    Position previousPoint = trajectory[indexForCurvatureEstimation - 1].pose.translation();
    Position lookAheadPoint = trajectory[indexForCurvatureEstimation].pose.translation();
    Position nextPoint = trajectory[indexForCurvatureEstimation + 1].pose.translation();
    double curvature = utils::discreteCurvature(previousPoint, lookAheadPoint, nextPoint);

    // Compute angle between road and vehicle orientation using lookahead point
    Eigen::Vector2d targetDirection = lookAheadPoint - vehiclePose.translation();
    double anglePath = std::atan2(targetDirection.y(), targetDirection.x());
    double yawVehicle = Eigen::Rotation2Dd(vehiclePose.rotation()).angle();
    double errorAngle = utils::normalizeAnglePlusMinusPi(yawVehicle - anglePath);

    // Compute signed distance between vehicle and trajectory
    double errorSignedDistance = utils::signedDistanceBetweenPointAndLine(
        vehiclePose.translation(),
        std::make_tuple(firstStampedPose.pose.translation(), secondStampedPose.pose.translation()));

    // Adaptive control gains based on curvature
    double kAngleAdaptive = parameters_.kAngle;
    double kDistanceAdaptive = parameters_.kDistance;
    
    // Increase angle control for curves, reduce distance control to avoid oscillation
    if (curvatureMagnitude > 0.5) {
        kAngleAdaptive *= 1.5;  // Increase angle control for better curve following
        kDistanceAdaptive *= 0.8;  // Reduce distance control to avoid overshoot
    }
    
    // Compute steering angle using improved controller law
    double u = curvature - kDistanceAdaptive * errorSignedDistance - kAngleAdaptive * errorAngle;
    double steeringAngle = std::atan(parameters_.wheelBase * u);
    steeringAngle = std::clamp(steeringAngle, -parameters_.steeringAngleMax, parameters_.steeringAngleMax);

    std::optional<ControlCommand::DebugInfo> debugInfo;
    if (returnDebugInfo) {
        debugInfo.emplace();
        debugInfo->closestPointOnTrajectory = trajectory[indexOfClosestPointOnTrajectory].pose.translation();
        debugInfo->lookAheadPoint = trajectory[indexForCurvatureEstimation].pose.translation();
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
