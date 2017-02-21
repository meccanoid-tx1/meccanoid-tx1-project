;; Auto-generated. Do not edit!


(when (boundp 'meccanoid_tx1::meccanoid_map_pos)
  (if (not (find-package "MECCANOID_TX1"))
    (make-package "MECCANOID_TX1"))
  (shadow 'meccanoid_map_pos (find-package "MECCANOID_TX1")))
(unless (find-package "MECCANOID_TX1::MECCANOID_MAP_POS")
  (make-package "MECCANOID_TX1::MECCANOID_MAP_POS"))

(in-package "ROS")
;;//! \htmlinclude meccanoid_map_pos.msg.html


(defclass meccanoid_tx1::meccanoid_map_pos
  :super ros::object
  :slots (_data ))

(defmethod meccanoid_tx1::meccanoid_map_pos
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

(setf (get meccanoid_tx1::meccanoid_map_pos :md5sum-) "992ce8a1687cec8c8bd883ec73ca41d1")
(setf (get meccanoid_tx1::meccanoid_map_pos :datatype-) "meccanoid_tx1/meccanoid_map_pos")
(setf (get meccanoid_tx1::meccanoid_map_pos :definition-)
      "# -------------------------------#
# Meccanoid map position message #
# -------------------------------#

# TODO: implement message fields

string data
")



(provide :meccanoid_tx1/meccanoid_map_pos "992ce8a1687cec8c8bd883ec73ca41d1")


