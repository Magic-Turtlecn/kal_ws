#pragma once

#include <chrono>
#include <vector>

#include <Eigen/Geometry>

namespace kal_controller {

using Duration = std::chrono::duration<double, std::ratio<1>>;
using Time = std::chrono::time_point<std::chrono::steady_clock, Duration>;

using Position = Eigen::Vector2d;
using Path = std::vector<Position>;

using Pose = Eigen::Isometry2d;
struct StampedPose {
    Pose pose;
    Time stamp;
};

using Trajectory = std::vector<StampedPose>;

struct ControlCommand {
    struct DebugInfo {
        Position closestPointOnTrajectory;
        Position lookAheadPoint;

        double anglePath;
        double curvature;
        double errorAngle;
        double errorSignedDistance;
        double yawVehicle;
    };

    double speed;
    double steeringAngle;

    ///@brief Optional return values useful for debugging
    std::optional<DebugInfo> debugInfo;
};

struct Parameters {
    ///@brief Weight punishing differences of vehicle yaw and path angle
    double kAngle;

    ///@brief Weight punishing offset of vehicle position and planned trajectory
    double kDistance;

    ///@brief Index of trajectory pose used to compute path curvature and path angle
    uint16_t lookAheadIndex;

    ///@brief Velocity Threshold to stop the car
    double minVelocityThreshold;

    ///@brief Returned steering angle is limited to [-steeringAngleMax, steeringAngleMax]
    double steeringAngleMax;

    ///@brief Distance between front and rear axle of the car
    double wheelBase;
};

} // namespace kal_controller