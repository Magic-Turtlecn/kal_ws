#pragma once
#include <ros/node_handle.h>
#include <ros/publisher.h>
#include <ros/time.h>
#include <rosgraph_msgs/Clock.h>

#include <utility>

namespace util_testing {

//! Thrown if time controller cannot control time
class TimeControlError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

/**
 * @brief This struct provides a simple way to fake the clock in ros
 */
struct TimeController {
public:
    /**
     * @brief Construcor for a time controller instance. Please instanciate just one of those...
     * @param t_init Start time for the time controller
     * @param spin set this to true if you are not using an async spinner and dont want to call spinOnce()
     * @throws TimeControlError if ros time cannot be controlled (use_sim_time not set)
     */
    explicit TimeController(const ros::Time& tInit = ros::Time(1), bool spin = false) : spin{spin}, timeNow{tInit} {
        ros::NodeHandle nh;

        bool useSimTime = nh.param("/use_sim_time", false);
        if (!useSimTime) {
            throw TimeControlError("use_sim_time is not set. Can not control time!");
        }
        timePublisher = nh.advertise<rosgraph_msgs::Clock>("/clock", 1);
        publish();
    }

    /**
     * @brief advance time a fixed amount of time and publish it
     * @param delta time to advance (must be >0)
     */
    void advance(const ros::Duration& delta = ros::Duration(1)) {
        timeNow += delta;
        publish();
        if (spin) {
            ros::spinOnce();
        }
    }

    /**
     * @brief publish forces TimeController to publish the current time again
     */
    void publish() const {
        rosgraph_msgs::Clock c;
        c.clock = timeNow;
        timePublisher.publish(c);
    }
    bool spin = false;            //!< spin after each time advance?
    ros::Time timeNow;            //!< current time
    ros::Publisher timePublisher; //!< publisher used for publishing to the clock topic
};
} // namespace util_testing
