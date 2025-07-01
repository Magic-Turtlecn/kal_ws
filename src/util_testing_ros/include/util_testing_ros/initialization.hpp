#pragma once
#include <chrono>
#include <initializer_list>
#include <thread>
#include <ros/duration.h>
#include <ros/init.h>
#include <ros/publisher.h>

namespace util_testing {
namespace internal {
inline bool waitForCondition(const std::function<bool()>& condition, const ros::Duration& timeout, bool spin) {
    constexpr int NumPolls = 20;
    int waitcount = 0;
    while (waitcount++ < NumPolls && ros::ok()) {
        const bool conditionMet = condition();
        if (spin) {
            ros::spinOnce();
        }
        std::this_thread::sleep_for(std::chrono::nanoseconds(timeout.toNSec() / NumPolls));
        if (conditionMet) {
            return true;
        }
    }
    return false;
}
} // namespace internal

/**
 * @brief waitForInitalization blocks until a node has subscribed to all publishers
 * @param publishers list with all publishers {publisher1, publisher2, ..}
 * @param timeout time to wait for nodes to subscribe
 * @param spin call spinOnce while waiting. Necessary if no AsyncSpinner is active.
 * @return true if nodes managed to subscribe, false after timeout
 */
inline bool waitForInitalization(const std::initializer_list<ros::Publisher>& publishers,
                                 const ros::Duration& timeout = ros::Duration(5),
                                 bool spin = false) {
    return internal::waitForCondition(
        [&publishers]() {
            return std::all_of(publishers.begin(), publishers.end(), [](const ros::Publisher& publisher) {
                return publisher.getNumSubscribers() >= 1;
            });
        },
        timeout,
        spin);
}

/**
 * @brief waitForInitalization blocks until a publisher for each subscriber advertised the topic
 * @param subscribers list with all subscribers {subscriber1, subscriber2, ..}
 * @param timeout time to wait for nodes to advertise
 * @param spin call spinOnce while waiting. Necessary if no AsyncSpinner is active.
 * @return true if nodes managed to advertise, false after timeout
 */
inline bool waitForInitalization(const std::initializer_list<ros::Subscriber>& subscribers,
                                 const ros::Duration& timeout = ros::Duration(5),
                                 bool spin = false) {
    return internal::waitForCondition(
        [&subscribers]() {
            return std::all_of(subscribers.begin(), subscribers.end(), [](const ros::Subscriber& subscriber) {
                return subscriber.getNumPublishers() >= 1;
            });
        },
        timeout,
        spin);
}
} // namespace util_testing
