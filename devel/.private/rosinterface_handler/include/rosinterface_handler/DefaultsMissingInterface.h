// *********************************************************
//
// File autogenerated for the rosinterface_handler package
// by the rosinterface_handler package.
// Please do not edit.
//
// ********************************************************/

#pragma once

#include <stdlib.h>
#include <string>
#include <limits>
#include <memory>
#include <ros/param.h>
#include <ros/node_handle.h>
#include <rosinterface_handler/console_bridge_compatibility.hpp>
#include <rosinterface_handler/utilities.hpp>
#ifdef MESSAGE_FILTERS_FOUND
#include <message_filters/subscriber.h>

#else

#endif
#ifndef DIAGNOSTIC_UPDATER_FOUND

#endif
#ifdef DYNAMIC_RECONFIGURE_FOUND
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses"
#include <rosinterface_handler/DefaultsMissingConfig.h>
#pragma GCC diagnostic pop
#else
struct DefaultsMissingConfig{};
#endif

namespace rosinterface_handler {

/// \brief Parameter struct generated by rosinterface_handler
struct DefaultsMissingInterface {

  using Config = DefaultsMissingConfig;
#ifdef MESSAGE_FILTERS_FOUND
  template<typename T>
  using Subscriber = message_filters::Subscriber<T>;
  template<typename T>
  using SubscriberPtr = std::shared_ptr<Subscriber<T>>;
#endif
#ifdef IF_HANDLER_DIAGNOSTICS_INCLUDED
  template<typename T, typename BaseT = message_filters::Subscriber<T>>
  using DiagSubscriber = rosinterface_handler::DiagnosedSubscriber<T, BaseT>;
  template<typename T, typename BaseT = message_filters::Subscriber<T>>
  using DiagSubscriberPtr = std::shared_ptr<DiagSubscriber<T, BaseT>>;
  template<typename T>
  using DiagPublisher = rosinterface_handler::DiagnosedPublisher<T>;
#endif

  DefaultsMissingInterface(const ros::NodeHandle& private_node_handle)
  : globalNamespace_{"/"},
    publicNamespace_{rosinterface_handler::getParentNamespace(private_node_handle) + "/"},
    privateNamespace_{private_node_handle.getNamespace() + "/"},
    nodeName_{rosinterface_handler::getNodeName(private_node_handle)},
    privateNodeHandle_{private_node_handle} {}

  /// \brief Get values from parameter server
  ///
  /// Will fail if a value can not be found and no default value is given.
  void fromParamServer(){
    bool success = true;
    success &= rosinterface_handler::getParam(privateNamespace_ + "int_param", int_param);




    if(!success){
      missingParamsWarning();
      rosinterface_handler::exit("RosinterfaceHandler: GetParam could net retrieve parameter.");
    }
    ROS_DEBUG_STREAM(*this);
  }

  /// \brief Set parameters on ROS parameter server.
  void toParamServer(){
    rosinterface_handler::setParam(privateNamespace_ + "int_param",int_param);
  }

  /// \brief Update configurable parameters.
  ///
  /// \param config  dynamic reconfigure struct
  /// \level ?
  void fromConfig(const Config& config, const uint32_t level = 0){
#ifdef DYNAMIC_RECONFIGURE_FOUND


#else
  ROS_FATAL_STREAM("dynamic_reconfigure was not found during compilation. So fromConfig() is not available. Please recompile with dynamic_reconfigure.");
  rosinterface_handler::exit("dynamic_reconfigure was not found during compilation. So fromConfig() is not available. Please recompile with dynamic_reconfigure.");
#endif
  }

  /// \brief Stream operator for printing parameter struct
  friend std::ostream& operator<<(std::ostream& os, const DefaultsMissingInterface& p)
  {
    os << "[" << p.nodeNameWithNamespace() << "]\nNode " << p.nodeNameWithNamespace() << " has the following parameters:\n"
      << "	" << p.privateNamespace_ << "int_param:" << p.int_param << "\n"
;
    return os;
  }

  /// \brief get the node handle that the interface struct uses internally
  ros::NodeHandle getPrivateNodeHandle() {
      return privateNodeHandle_;
  }

  /// \brief returns the name of the node (works in nodelets, too)
  const std::string& nodeName() const {
      return nodeName_;
  }

  /// \brief returns the name of the node with its namespace (works in nodelets, too)
  const std::string& nodeNameWithNamespace() const {
      return privateNodeHandle_.getNamespace();
  }

  /// \brief logs to the debug output. Works also within nodelets.
  // NOLINTNEXTLINE(readability-function-size)
  template <typename Msg, typename... Msgs>
  inline void logDebug(const Msg& msg, const Msgs&... Msgs_) const {
      ROS_DEBUG_STREAM_NAMED(nodeNameWithNamespace(), rosinterface_handler::asString(msg, Msgs_...));
  }

  /// \brief logs to the debug output. Works also within nodelets. Output is throttled.
  // NOLINTNEXTLINE(readability-function-size)
  template <typename Msg, typename... Msgs>
  inline void logInfo(const Msg& msg, const Msgs&... Msgs_) const {
      ROS_INFO_STREAM_THROTTLE_NAMED(5, nodeNameWithNamespace(), rosinterface_handler::asString(msg, Msgs_...));
  }

  /// \brief logs to the debug output. Works also within nodelets. Output is throttled.
  // NOLINTNEXTLINE(readability-function-size)
  template <typename Msg, typename... Msgs>
  inline void logWarn(const Msg& msg, const Msgs&... Msgs_) const {
      ROS_WARN_STREAM_THROTTLE_NAMED(5, nodeNameWithNamespace(), rosinterface_handler::asString(msg, Msgs_...));
  }

  /// \brief logs to the error output. Works also within nodelets. Output is throttled.
  // NOLINTNEXTLINE(readability-function-size)
  template <typename Msg, typename... Msgs>
  inline void logError(const Msg& msg, const Msgs&... Msgs_) const {
      ROS_ERROR_STREAM_THROTTLE_NAMED(5, nodeNameWithNamespace(), rosinterface_handler::asString(msg, Msgs_...));
  }

  /// \brief logs to the error output. Works also within nodelets. Not throttled! Dont call this in loops!
  // NOLINTNEXTLINE(readability-function-size)
  template <typename Msg, typename... Msgs>
  inline void logErrorDirect(const Msg& msg, const Msgs&... Msgs_) const {
      ROS_ERROR_STREAM_NAMED(nodeNameWithNamespace(), rosinterface_handler::asString(msg, Msgs_...));
  }

  /// \brief logs subscribed and advertised topics to the command line. Works also within nodelets.
  // NOLINTNEXTLINE(readability-function-size)
  void showNodeInfo() const {
      std::string message = "Node '" + nodeName() + "' from package 'rosinterface_handler', type 'DefaultsMissing'"
                                                    " in namespace '" + publicNamespace_ + "'.\nSubscribed to: [";

      message += "]\nAdvertising: [";

      message += ']';
      logInfo(message);
  }

private:
  const std::string globalNamespace_;
  const std::string publicNamespace_;
  const std::string privateNamespace_;
  const std::string nodeName_;
  ros::NodeHandle privateNodeHandle_;

public:
  int int_param; /*!< Handler should keep node from starting, when no default is given here or at launch. */



private:
  /// \brief Issue a warning about missing default parameters.
  void missingParamsWarning(){
    ROS_WARN_STREAM("[" << nodeName_ << "]\nThe following parameters do not have default values and need to be specified:\n"
      << "	" << privateNamespace_ << "int_param" << " (int) \n"
    );
  }
};
} // namespace rosinterface_handler
