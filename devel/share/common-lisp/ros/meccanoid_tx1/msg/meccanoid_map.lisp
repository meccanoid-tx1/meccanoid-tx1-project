; Auto-generated. Do not edit!


(cl:in-package meccanoid_tx1-msg)


;//! \htmlinclude meccanoid_map.msg.html

(cl:defclass <meccanoid_map> (roslisp-msg-protocol:ros-message)
  ((data
    :reader data
    :initarg :data
    :type cl:string
    :initform ""))
)

(cl:defclass meccanoid_map (<meccanoid_map>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <meccanoid_map>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'meccanoid_map)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name meccanoid_tx1-msg:<meccanoid_map> is deprecated: use meccanoid_tx1-msg:meccanoid_map instead.")))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <meccanoid_map>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader meccanoid_tx1-msg:data-val is deprecated.  Use meccanoid_tx1-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <meccanoid_map>) ostream)
  "Serializes a message object of type '<meccanoid_map>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <meccanoid_map>) istream)
  "Deserializes a message object of type '<meccanoid_map>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'data) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'data) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<meccanoid_map>)))
  "Returns string type for a message object of type '<meccanoid_map>"
  "meccanoid_tx1/meccanoid_map")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'meccanoid_map)))
  "Returns string type for a message object of type 'meccanoid_map"
  "meccanoid_tx1/meccanoid_map")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<meccanoid_map>)))
  "Returns md5sum for a message object of type '<meccanoid_map>"
  "992ce8a1687cec8c8bd883ec73ca41d1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'meccanoid_map)))
  "Returns md5sum for a message object of type 'meccanoid_map"
  "992ce8a1687cec8c8bd883ec73ca41d1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<meccanoid_map>)))
  "Returns full string definition for message of type '<meccanoid_map>"
  (cl:format cl:nil "# ----------------------#~%# Meccanoid map message #~%# ----------------------#~%~%# TODO: implement message fields~%~%string data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'meccanoid_map)))
  "Returns full string definition for message of type 'meccanoid_map"
  (cl:format cl:nil "# ----------------------#~%# Meccanoid map message #~%# ----------------------#~%~%# TODO: implement message fields~%~%string data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <meccanoid_map>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'data))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <meccanoid_map>))
  "Converts a ROS message object to a list"
  (cl:list 'meccanoid_map
    (cl:cons ':data (data msg))
))
