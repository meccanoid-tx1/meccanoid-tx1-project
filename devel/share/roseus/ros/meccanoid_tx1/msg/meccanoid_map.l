;; Auto-generated. Do not edit!


(when (boundp 'meccanoid_tx1::meccanoid_map)
  (if (not (find-package "MECCANOID_TX1"))
    (make-package "MECCANOID_TX1"))
  (shadow 'meccanoid_map (find-package "MECCANOID_TX1")))
(unless (find-package "MECCANOID_TX1::MECCANOID_MAP")
  (make-package "MECCANOID_TX1::MECCANOID_MAP"))

(in-package "ROS")
;;//! \htmlinclude meccanoid_map.msg.html


(defclass meccanoid_tx1::meccanoid_map
  :super ros::object
  :slots (_data ))

(defmethod meccanoid_tx1::meccanoid_map
  (:init
   (&key
    ((:data __data) "")
    )
   (send-super :init)
   (setq _data (string __data))
   self)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; string _data
    4 (length _data)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _data
       (write-long (length _data) s) (princ _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _data
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _data (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get meccanoid_tx1::meccanoid_map :md5sum-) "992ce8a1687cec8c8bd883ec73ca41d1")
(setf (get meccanoid_tx1::meccanoid_map :datatype-) "meccanoid_tx1/meccanoid_map")
(setf (get meccanoid_tx1::meccanoid_map :definition-)
      "# ----------------------#
# Meccanoid map message #
# ----------------------#

# TODO: implement message fields

string data
")



(provide :meccanoid_tx1/meccanoid_map "992ce8a1687cec8c8bd883ec73ca41d1")


