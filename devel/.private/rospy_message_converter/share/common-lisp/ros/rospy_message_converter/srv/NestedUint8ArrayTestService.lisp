; Auto-generated. Do not edit!


(cl:in-package rospy_message_converter-srv)


;//! \htmlinclude NestedUint8ArrayTestService-request.msg.html

(cl:defclass <NestedUint8ArrayTestService-request> (roslisp-msg-protocol:ros-message)
  ((input
    :reader input
    :initarg :input
    :type rospy_message_converter-msg:NestedUint8ArrayTestMessage
    :initform (cl:make-instance 'rospy_message_converter-msg:NestedUint8ArrayTestMessage)))
)

(cl:defclass NestedUint8ArrayTestService-request (<NestedUint8ArrayTestService-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <NestedUint8ArrayTestService-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'NestedUint8ArrayTestService-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rospy_message_converter-srv:<NestedUint8ArrayTestService-request> is deprecated: use rospy_message_converter-srv:NestedUint8ArrayTestService-request instead.")))

(cl:ensure-generic-function 'input-val :lambda-list '(m))
(cl:defmethod input-val ((m <NestedUint8ArrayTestService-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rospy_message_converter-srv:input-val is deprecated.  Use rospy_message_converter-srv:input instead.")
  (input m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <NestedUint8ArrayTestService-request>) ostream)
  "Serializes a message object of type '<NestedUint8ArrayTestService-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'input) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <NestedUint8ArrayTestService-request>) istream)
  "Deserializes a message object of type '<NestedUint8ArrayTestService-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'input) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<NestedUint8ArrayTestService-request>)))
  "Returns string type for a service object of type '<NestedUint8ArrayTestService-request>"
  "rospy_message_converter/NestedUint8ArrayTestServiceRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'NestedUint8ArrayTestService-request)))
  "Returns string type for a service object of type 'NestedUint8ArrayTestService-request"
  "rospy_message_converter/NestedUint8ArrayTestServiceRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<NestedUint8ArrayTestService-request>)))
  "Returns md5sum for a message object of type '<NestedUint8ArrayTestService-request>"
  "5eb791b1c2426cb63f1fa2ab8df04df3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'NestedUint8ArrayTestService-request)))
  "Returns md5sum for a message object of type 'NestedUint8ArrayTestService-request"
  "5eb791b1c2426cb63f1fa2ab8df04df3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<NestedUint8ArrayTestService-request>)))
  "Returns full string definition for message of type '<NestedUint8ArrayTestService-request>"
  (cl:format cl:nil "# service with nested types for testing purposes~%NestedUint8ArrayTestMessage input~%~%~%================================================================================~%MSG: rospy_message_converter/NestedUint8ArrayTestMessage~%# array of arrays for testing purposes~%Uint8ArrayTestMessage[] arrays~%~%================================================================================~%MSG: rospy_message_converter/Uint8ArrayTestMessage~%# Size-agnostic uint8 array for testing purposes~%uint8[] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'NestedUint8ArrayTestService-request)))
  "Returns full string definition for message of type 'NestedUint8ArrayTestService-request"
  (cl:format cl:nil "# service with nested types for testing purposes~%NestedUint8ArrayTestMessage input~%~%~%================================================================================~%MSG: rospy_message_converter/NestedUint8ArrayTestMessage~%# array of arrays for testing purposes~%Uint8ArrayTestMessage[] arrays~%~%================================================================================~%MSG: rospy_message_converter/Uint8ArrayTestMessage~%# Size-agnostic uint8 array for testing purposes~%uint8[] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <NestedUint8ArrayTestService-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'input))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <NestedUint8ArrayTestService-request>))
  "Converts a ROS message object to a list"
  (cl:list 'NestedUint8ArrayTestService-request
    (cl:cons ':input (input msg))
))
;//! \htmlinclude NestedUint8ArrayTestService-response.msg.html

(cl:defclass <NestedUint8ArrayTestService-response> (roslisp-msg-protocol:ros-message)
  ((output
    :reader output
    :initarg :output
    :type rospy_message_converter-msg:NestedUint8ArrayTestMessage
    :initform (cl:make-instance 'rospy_message_converter-msg:NestedUint8ArrayTestMessage)))
)

(cl:defclass NestedUint8ArrayTestService-response (<NestedUint8ArrayTestService-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <NestedUint8ArrayTestService-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'NestedUint8ArrayTestService-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rospy_message_converter-srv:<NestedUint8ArrayTestService-response> is deprecated: use rospy_message_converter-srv:NestedUint8ArrayTestService-response instead.")))

(cl:ensure-generic-function 'output-val :lambda-list '(m))
(cl:defmethod output-val ((m <NestedUint8ArrayTestService-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rospy_message_converter-srv:output-val is deprecated.  Use rospy_message_converter-srv:output instead.")
  (output m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <NestedUint8ArrayTestService-response>) ostream)
  "Serializes a message object of type '<NestedUint8ArrayTestService-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'output) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <NestedUint8ArrayTestService-response>) istream)
  "Deserializes a message object of type '<NestedUint8ArrayTestService-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'output) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<NestedUint8ArrayTestService-response>)))
  "Returns string type for a service object of type '<NestedUint8ArrayTestService-response>"
  "rospy_message_converter/NestedUint8ArrayTestServiceResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'NestedUint8ArrayTestService-response)))
  "Returns string type for a service object of type 'NestedUint8ArrayTestService-response"
  "rospy_message_converter/NestedUint8ArrayTestServiceResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<NestedUint8ArrayTestService-response>)))
  "Returns md5sum for a message object of type '<NestedUint8ArrayTestService-response>"
  "5eb791b1c2426cb63f1fa2ab8df04df3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'NestedUint8ArrayTestService-response)))
  "Returns md5sum for a message object of type 'NestedUint8ArrayTestService-response"
  "5eb791b1c2426cb63f1fa2ab8df04df3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<NestedUint8ArrayTestService-response>)))
  "Returns full string definition for message of type '<NestedUint8ArrayTestService-response>"
  (cl:format cl:nil "~%NestedUint8ArrayTestMessage output~%~%~%================================================================================~%MSG: rospy_message_converter/NestedUint8ArrayTestMessage~%# array of arrays for testing purposes~%Uint8ArrayTestMessage[] arrays~%~%================================================================================~%MSG: rospy_message_converter/Uint8ArrayTestMessage~%# Size-agnostic uint8 array for testing purposes~%uint8[] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'NestedUint8ArrayTestService-response)))
  "Returns full string definition for message of type 'NestedUint8ArrayTestService-response"
  (cl:format cl:nil "~%NestedUint8ArrayTestMessage output~%~%~%================================================================================~%MSG: rospy_message_converter/NestedUint8ArrayTestMessage~%# array of arrays for testing purposes~%Uint8ArrayTestMessage[] arrays~%~%================================================================================~%MSG: rospy_message_converter/Uint8ArrayTestMessage~%# Size-agnostic uint8 array for testing purposes~%uint8[] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <NestedUint8ArrayTestService-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'output))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <NestedUint8ArrayTestService-response>))
  "Converts a ROS message object to a list"
  (cl:list 'NestedUint8ArrayTestService-response
    (cl:cons ':output (output msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'NestedUint8ArrayTestService)))
  'NestedUint8ArrayTestService-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'NestedUint8ArrayTestService)))
  'NestedUint8ArrayTestService-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'NestedUint8ArrayTestService)))
  "Returns string type for a service object of type '<NestedUint8ArrayTestService>"
  "rospy_message_converter/NestedUint8ArrayTestService")