#include "controller.hpp"

#include <ackermann_msgs/AckermannDriveStamped.h>
#include <ros/time.h>
#include <tf2_eigen/tf2_eigen.h>
#include <visualization_msgs/Marker.h>

#include "conversions.hpp"


namespace kal_controller_ros_tool {

/**
 * Initialization
 */
ControllerNode::ControllerNode(const ros::NodeHandle& nhPrivate)
        : interface_{nhPrivate}, reconfigureServer_{nhPrivate} {

    interface_.fromParamServer();
    setControllerParameters();
    /*
     * Set up callbacks for subscribers and reconfigure.
     *
     * New subscribers can be created with "add_subscriber" in "cfg/Controller.if file.
     * Don't forget to register your callbacks here!
     */
    reconfigureServer_.setCallback(boost::bind(&ControllerNode::reconfigureCallback, this, _1, _2));
    interface_.trajectory_subscriber->registerCallback(&ControllerNode::trajectoryCallback, this);
    controlLoopTimer_ =
        nhPrivate.createTimer(ros::Rate(interface_.control_loop_rate), &ControllerNode::controlLoopCallback, this);

    interface_.showNodeInfo();

    /*
     * The preferred way of logging is to call the logging functions of the interface object.
     * These also work for nodelets and are better than using ROS_DEBUG (etc.) macros.
     */
    interface_.logDebug("Node initialized.");
}


void ControllerNode::trajectoryCallback(const nav_msgs::Path::ConstPtr& trajectoryMsg) {
    trajectoryStamp_ = ros::Time::now();
    trajectory_ = conversions::trajectoryMsgToTrajectory(trajectoryMsg);
}

void ControllerNode::controlLoopCallback(const ros::TimerEvent& timerEvent) {
    if (!checkTrajectoryExists()) {
        return;
    }
    if (!checkTrajectoryAge()) {
        return;
    }
    if (!checkTrajectoryLength()) {
        return;
    }

    // Find vehicle pose
    Pose vehiclePose;
    if (!currentVehiclePose(vehiclePose)) {
        return;
    }

    ros::Time stamp = ros::Time::now();
    ControlCommand controlCommand =
        controller_.getControlCommand(vehiclePose, *trajectory_, interface_.publish_debug_info);
    auto controlCommandMsg =
        conversions::controlCommandToAckermannDriveStamped(controlCommand, stamp, interface_.vehicle_frame);
    interface_.control_command_publisher.publish(controlCommandMsg);
    visualization_msgs::Marker debugControlCommandViz =
        conversions::controlCommandToMarkerMsg(controlCommand, stamp, interface_.vehicle_frame);
    interface_.debug_control_command_viz_publisher.publish(debugControlCommandViz);

    if (controlCommand.debugInfo) {
        publishDebugInfo(controlCommand.debugInfo.value(), stamp);
    }
}

void ControllerNode::reconfigureCallback(const Interface::Config& config, uint32_t /*level*/) {
    interface_.fromConfig(config);
    setControllerParameters();
}

bool ControllerNode::currentVehiclePose(Pose& pose) const {
    // Find vehicle position in tf tree
    geometry_msgs::TransformStamped vehiclePoseRos;
    Eigen::Isometry3d vehiclePose3d;
    try {
        vehiclePoseRos = tfBuffer_.lookupTransform(interface_.map_frame, interface_.vehicle_frame, ros::Time(0));
    } catch (const tf2::TransformException& e) {
        interface_.logWarn("Cannot find vehicle pose. Stopping the vehicle.");
        publishStopCommand();
        return false;
    }

    // Transform to Eigen type
    vehiclePose3d = tf2::transformToEigen(vehiclePoseRos);

    // Convert to two dimensions
    pose = conversions::isometry2dFromIsometry3d(vehiclePose3d);

    return true;
}

bool ControllerNode::checkTrajectoryExists() const {
    if (!trajectory_) {
        interface_.logWarn("Trajectory undefined. Stopping the vehicle.");
        publishStopCommand();
        return false;
    }

    return true;
}

bool ControllerNode::checkTrajectoryAge() const {
    double trajectoryAge = (ros::Time::now() - trajectoryStamp_).toSec();
    if (trajectoryAge > interface_.trajectory_age_max) {
        std::stringstream outStream;
        outStream << std::fixed << std::setprecision(2) << "Trajectory is " << trajectoryAge << "s old. Limit is "
                  << interface_.trajectory_age_max << "s. Stopping the vehicle.";
        interface_.logWarn(outStream.str());
        publishStopCommand();
        return false;
    }

    return true;
}

bool ControllerNode::checkTrajectoryLength() const {
    uint16_t trajectoryMinimumLength = interface_.look_ahead_index + 1;
    if (trajectory_->size() < trajectoryMinimumLength) {
        std::stringstream outStream;
        outStream << std::fixed << std::setprecision(0) << "Trajectory only contains " << trajectory_->size()
                  << " poses. Required minimum is " << trajectoryMinimumLength << ". Stopping the vehicle.";
        interface_.logWarn(outStream.str());
        publishStopCommand();
        return false;
    }

    return true;
}

void ControllerNode::publishStopCommand() const {
    ackermann_msgs::AckermannDriveStamped stopCommandMsg;
    stopCommandMsg.header.stamp = ros::Time::now();
    stopCommandMsg.header.frame_id = interface_.vehicle_frame;
    stopCommandMsg.drive.speed = 0;
    stopCommandMsg.drive.steering_angle = 0;
    interface_.control_command_publisher.publish(stopCommandMsg);
}

void ControllerNode::publishDebugInfo(const ControlCommand::DebugInfo& debugInfo, const ros::Time& stamp) const {
    interface_.debug_closest_point_on_trajectory_publisher.publish(
        conversions::eigenVector2dToPointStampedMsg(debugInfo.closestPointOnTrajectory, stamp, interface_.map_frame));
    interface_.debug_look_ahead_point_publisher.publish(
        conversions::eigenVector2dToPointStampedMsg(debugInfo.lookAheadPoint, stamp, interface_.map_frame));
    interface_.debug_angle_path.publish(conversions::doubleToFloat64Msg(debugInfo.anglePath));
    interface_.debug_curvature.publish(conversions::doubleToFloat64Msg(debugInfo.curvature));
    interface_.debug_error_angle.publish(conversions::doubleToFloat64Msg(debugInfo.errorAngle));
    interface_.debug_error_signed_distance.publish(conversions::doubleToFloat64Msg(debugInfo.errorSignedDistance));
    interface_.debug_yaw_vehicle.publish(conversions::doubleToFloat64Msg(debugInfo.yawVehicle));
}

void ControllerNode::setControllerParameters() {
    Parameters parameters{};
    parameters.kAngle = interface_.k_angular;
    parameters.kDistance = interface_.k_distance;
    parameters.lookAheadIndex = interface_.look_ahead_index;
    parameters.steeringAngleMax = interface_.steering_angle_max;
    parameters.wheelBase = interface_.wheel_base;
    parameters.minVelocityThreshold = interface_.min_velocity_threshold;
    controller_.setParameters(parameters);
}

} // namespace kal_controller_ros_tool
