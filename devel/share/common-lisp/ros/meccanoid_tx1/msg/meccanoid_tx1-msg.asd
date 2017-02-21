
(cl:in-package :asdf)

(defsystem "meccanoid_tx1-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "hedge_pos" :depends-on ("_package_hedge_pos"))
    (:file "_package_hedge_pos" :depends-on ("_package"))
    (:file "meccanoid_map" :depends-on ("_package_meccanoid_map"))
    (:file "_package_meccanoid_map" :depends-on ("_package"))
    (:file "meccanoid_map_pos" :depends-on ("_package_meccanoid_map_pos"))
    (:file "_package_meccanoid_map_pos" :depends-on ("_package"))
  ))