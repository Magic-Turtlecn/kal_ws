;; Auto-generated. Do not edit!


(when (boundp 'rospy_message_converter::NestedUint8ArrayTestMessage)
  (if (not (find-package "ROSPY_MESSAGE_CONVERTER"))
    (make-package "ROSPY_MESSAGE_CONVERTER"))
  (shadow 'NestedUint8ArrayTestMessage (find-package "ROSPY_MESSAGE_CONVERTER")))
(unless (find-package "ROSPY_MESSAGE_CONVERTER::NESTEDUINT8ARRAYTESTMESSAGE")
  (make-package "ROSPY_MESSAGE_CONVERTER::NESTEDUINT8ARRAYTESTMESSAGE"))

(in-package "ROS")
;;//! \htmlinclude NestedUint8ArrayTestMessage.msg.html


(defclass rospy_message_converter::NestedUint8ArrayTestMessage
  :super ros::object
  :slots (_arrays ))

(defmethod rospy_message_converter::NestedUint8ArrayTestMessage
  (:init
   (&key
    ((:arrays __arrays) ())
    )
   (send-super :init)
   (setq _arrays __arrays)
   self)
  (:arrays
   (&rest __arrays)
   (if (keywordp (car __arrays))
       (send* _arrays __arrays)
     (progn
       (if __arrays (setq _arrays (car __arrays)))
       _arrays)))
  (:serialization-length
   ()
   (+
    ;; rospy_message_converter/Uint8ArrayTestMessage[] _arrays
    (apply #'+ (send-all _arrays :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; rospy_message_converter/Uint8ArrayTestMessage[] _arrays
     (write-long (length _arrays) s)
     (dolist (elem _arrays)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; rospy_message_converter/Uint8ArrayTestMessage[] _arrays
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _arrays (let (r) (dotimes (i n) (push (instance rospy_message_converter::Uint8ArrayTestMessage :init) r)) r))
     (dolist (elem- _arrays)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get rospy_message_converter::NestedUint8ArrayTestMessage :md5sum-) "031a2ce5216a9e0c7998cc17696cf368")
(setf (get rospy_message_converter::NestedUint8ArrayTestMessage :datatype-) "rospy_message_converter/NestedUint8ArrayTestMessage")
(setf (get rospy_message_converter::NestedUint8ArrayTestMessage :definition-)
      "# array of arrays for testing purposes
Uint8ArrayTestMessage[] arrays

================================================================================
MSG: rospy_message_converter/Uint8ArrayTestMessage
# Size-agnostic uint8 array for testing purposes
uint8[] data

")



(provide :rospy_message_converter/NestedUint8ArrayTestMessage "031a2ce5216a9e0c7998cc17696cf368")


