;; Auto-generated. Do not edit!


(when (boundp 'rospy_message_converter::NestedUint8ArrayTestService)
  (if (not (find-package "ROSPY_MESSAGE_CONVERTER"))
    (make-package "ROSPY_MESSAGE_CONVERTER"))
  (shadow 'NestedUint8ArrayTestService (find-package "ROSPY_MESSAGE_CONVERTER")))
(unless (find-package "ROSPY_MESSAGE_CONVERTER::NESTEDUINT8ARRAYTESTSERVICE")
  (make-package "ROSPY_MESSAGE_CONVERTER::NESTEDUINT8ARRAYTESTSERVICE"))
(unless (find-package "ROSPY_MESSAGE_CONVERTER::NESTEDUINT8ARRAYTESTSERVICEREQUEST")
  (make-package "ROSPY_MESSAGE_CONVERTER::NESTEDUINT8ARRAYTESTSERVICEREQUEST"))
(unless (find-package "ROSPY_MESSAGE_CONVERTER::NESTEDUINT8ARRAYTESTSERVICERESPONSE")
  (make-package "ROSPY_MESSAGE_CONVERTER::NESTEDUINT8ARRAYTESTSERVICERESPONSE"))

(in-package "ROS")





(defclass rospy_message_converter::NestedUint8ArrayTestServiceRequest
  :super ros::object
  :slots (_input ))

(defmethod rospy_message_converter::NestedUint8ArrayTestServiceRequest
  (:init
   (&key
    ((:input __input) (instance rospy_message_converter::NestedUint8ArrayTestMessage :init))
    )
   (send-super :init)
   (setq _input __input)
   self)
  (:input
   (&rest __input)
   (if (keywordp (car __input))
       (send* _input __input)
     (progn
       (if __input (setq _input (car __input)))
       _input)))
  (:serialization-length
   ()
   (+
    ;; rospy_message_converter/NestedUint8ArrayTestMessage _input
    (send _input :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; rospy_message_converter/NestedUint8ArrayTestMessage _input
       (send _input :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; rospy_message_converter/NestedUint8ArrayTestMessage _input
     (send _input :deserialize buf ptr-) (incf ptr- (send _input :serialization-length))
   ;;
   self)
  )

(defclass rospy_message_converter::NestedUint8ArrayTestServiceResponse
  :super ros::object
  :slots (_output ))

(defmethod rospy_message_converter::NestedUint8ArrayTestServiceResponse
  (:init
   (&key
    ((:output __output) (instance rospy_message_converter::NestedUint8ArrayTestMessage :init))
    )
   (send-super :init)
   (setq _output __output)
   self)
  (:output
   (&rest __output)
   (if (keywordp (car __output))
       (send* _output __output)
     (progn
       (if __output (setq _output (car __output)))
       _output)))
  (:serialization-length
   ()
   (+
    ;; rospy_message_converter/NestedUint8ArrayTestMessage _output
    (send _output :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; rospy_message_converter/NestedUint8ArrayTestMessage _output
       (send _output :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; rospy_message_converter/NestedUint8ArrayTestMessage _output
     (send _output :deserialize buf ptr-) (incf ptr- (send _output :serialization-length))
   ;;
   self)
  )

(defclass rospy_message_converter::NestedUint8ArrayTestService
  :super ros::object
  :slots ())

(setf (get rospy_message_converter::NestedUint8ArrayTestService :md5sum-) "5eb791b1c2426cb63f1fa2ab8df04df3")
(setf (get rospy_message_converter::NestedUint8ArrayTestService :datatype-) "rospy_message_converter/NestedUint8ArrayTestService")
(setf (get rospy_message_converter::NestedUint8ArrayTestService :request) rospy_message_converter::NestedUint8ArrayTestServiceRequest)
(setf (get rospy_message_converter::NestedUint8ArrayTestService :response) rospy_message_converter::NestedUint8ArrayTestServiceResponse)

(defmethod rospy_message_converter::NestedUint8ArrayTestServiceRequest
  (:response () (instance rospy_message_converter::NestedUint8ArrayTestServiceResponse :init)))

(setf (get rospy_message_converter::NestedUint8ArrayTestServiceRequest :md5sum-) "5eb791b1c2426cb63f1fa2ab8df04df3")
(setf (get rospy_message_converter::NestedUint8ArrayTestServiceRequest :datatype-) "rospy_message_converter/NestedUint8ArrayTestServiceRequest")
(setf (get rospy_message_converter::NestedUint8ArrayTestServiceRequest :definition-)
      "# service with nested types for testing purposes
NestedUint8ArrayTestMessage input


================================================================================
MSG: rospy_message_converter/NestedUint8ArrayTestMessage
# array of arrays for testing purposes
Uint8ArrayTestMessage[] arrays

================================================================================
MSG: rospy_message_converter/Uint8ArrayTestMessage
# Size-agnostic uint8 array for testing purposes
uint8[] data
---

NestedUint8ArrayTestMessage output


================================================================================
MSG: rospy_message_converter/NestedUint8ArrayTestMessage
# array of arrays for testing purposes
Uint8ArrayTestMessage[] arrays

================================================================================
MSG: rospy_message_converter/Uint8ArrayTestMessage
# Size-agnostic uint8 array for testing purposes
uint8[] data
")

(setf (get rospy_message_converter::NestedUint8ArrayTestServiceResponse :md5sum-) "5eb791b1c2426cb63f1fa2ab8df04df3")
(setf (get rospy_message_converter::NestedUint8ArrayTestServiceResponse :datatype-) "rospy_message_converter/NestedUint8ArrayTestServiceResponse")
(setf (get rospy_message_converter::NestedUint8ArrayTestServiceResponse :definition-)
      "# service with nested types for testing purposes
NestedUint8ArrayTestMessage input


================================================================================
MSG: rospy_message_converter/NestedUint8ArrayTestMessage
# array of arrays for testing purposes
Uint8ArrayTestMessage[] arrays

================================================================================
MSG: rospy_message_converter/Uint8ArrayTestMessage
# Size-agnostic uint8 array for testing purposes
uint8[] data
---

NestedUint8ArrayTestMessage output


================================================================================
MSG: rospy_message_converter/NestedUint8ArrayTestMessage
# array of arrays for testing purposes
Uint8ArrayTestMessage[] arrays

================================================================================
MSG: rospy_message_converter/Uint8ArrayTestMessage
# Size-agnostic uint8 array for testing purposes
uint8[] data
")



(provide :rospy_message_converter/NestedUint8ArrayTestService "5eb791b1c2426cb63f1fa2ab8df04df3")


