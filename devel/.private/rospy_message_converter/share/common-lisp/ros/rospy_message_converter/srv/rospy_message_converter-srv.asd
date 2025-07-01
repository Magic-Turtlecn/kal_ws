
(cl:in-package :asdf)

(defsystem "rospy_message_converter-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :rospy_message_converter-msg
)
  :components ((:file "_package")
    (:file "NestedUint8ArrayTestService" :depends-on ("_package_NestedUint8ArrayTestService"))
    (:file "_package_NestedUint8ArrayTestService" :depends-on ("_package"))
  ))