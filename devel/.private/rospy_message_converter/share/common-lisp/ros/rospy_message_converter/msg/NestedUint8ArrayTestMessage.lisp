; Auto-generated. Do not edit!


(cl:in-package rospy_message_converter-msg)


;//! \htmlinclude NestedUint8ArrayTestMessage.msg.html

(cl:defclass <NestedUint8ArrayTestMessage> (roslisp-msg-protocol:ros-message)
  ((arrays
    :reader arrays
    :initarg :arrays
    :type (cl:vector rospy_message_converter-msg:Uint8ArrayTestMessage)
   :initform (cl:make-array 0 :element-type 'rospy_message_converter-msg:Uint8ArrayTestMessage :initial-element (cl:make-instance 'rospy_message_converter-msg:Uint8ArrayTestMessage))))
)

(cl:defclass NestedUint8ArrayTestMessage (<NestedUint8ArrayTestMessage>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <NestedUint8ArrayTestMessage>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'NestedUint8ArrayTestMessage)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rospy_message_converter-msg:<NestedUint8ArrayTestMessage> is deprecated: use rospy_message_converter-msg:NestedUint8ArrayTestMessage instead.")))

(cl:ensure-generic-function 'arrays-val :lambda-list '(m))
(cl:defmethod arrays-val ((m <NestedUint8ArrayTestMessage>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rospy_message_converter-msg:arrays-val is deprecated.  Use rospy_message_converter-msg:arrays instead.")
  (arrays m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <NestedUint8ArrayTestMessage>) ostream)
  "Serializes a message object of type '<NestedUint8ArrayTestMessage>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'arrays))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'arrays))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <NestedUint8ArrayTestMessage>) istream)
  "Deserializes a message object of type '<NestedUint8ArrayTestMessage>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'arrays) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'arrays)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'rospy_message_converter-msg:Uint8ArrayTestMessage))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<NestedUint8ArrayTestMessage>)))
  "Returns string type for a message object of type '<NestedUint8ArrayTestMessage>"
  "rospy_message_converter/NestedUint8ArrayTestMessage")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'NestedUint8ArrayTestMessage)))
  "Returns string type for a message object of type 'NestedUint8ArrayTestMessage"
  "rospy_message_converter/NestedUint8ArrayTestMessage")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<NestedUint8ArrayTestMessage>)))
  "Returns md5sum for a message object of type '<NestedUint8ArrayTestMessage>"
  "031a2ce5216a9e0c7998cc17696cf368")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'NestedUint8ArrayTestMessage)))
  "Returns md5sum for a message object of type 'NestedUint8ArrayTestMessage"
  "031a2ce5216a9e0c7998cc17696cf368")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<NestedUint8ArrayTestMessage>)))
  "Returns full string definition for message of type '<NestedUint8ArrayTestMessage>"
  (cl:format cl:nil "# array of arrays for testing purposes~%Uint8ArrayTestMessage[] arrays~%~%================================================================================~%MSG: rospy_message_converter/Uint8ArrayTestMessage~%# Size-agnostic uint8 array for testing purposes~%uint8[] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'NestedUint8ArrayTestMessage)))
  "Returns full string definition for message of type 'NestedUint8ArrayTestMessage"
  (cl:format cl:nil "# array of arrays for testing purposes~%Uint8ArrayTestMessage[] arrays~%~%================================================================================~%MSG: rospy_message_converter/Uint8ArrayTestMessage~%# Size-agnostic uint8 array for testing purposes~%uint8[] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <NestedUint8ArrayTestMessage>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'arrays) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <NestedUint8ArrayTestMessage>))
  "Converts a ROS message object to a list"
  (cl:list 'NestedUint8ArrayTestMessage
    (cl:cons ':arrays (arrays msg))
))
