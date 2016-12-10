cmake_minimum_required(VERSION 2.8.3)
project(meccanoid_tx1)

### find catkin required system packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  rospy
  sensor_msgs
  std_msgs
  message_generation
  genmsg
  visualization_msgs
)

### find other required packages
find_package(OpenCV REQUIRED)


#-----------------------------------------------------#
#    Declare ROS messages, services and actions       #
#-----------------------------------------------------#


### MESSAGES
add_message_files(DIRECTORY msg/meccanoid_face_localization/
   	FILES meccanoid_face_location.msg
)

add_message_files( DIRECTORY msg/meccanoid_map/
   	FILES meccanoid_map.msg meccanoid_map_pos.msg
)

add_message_files( DIRECTORY msg/meccanoid_positioning/
   	FILES hedge_pos.msg
)

add_message_files( DIRECTORY msg/meccanoid_motors/
   	FILES meccanoid_motor_control.msg
)

### MESSAGE AND SERVICE DEPENDENCIES
generate_messages(
   DEPENDENCIES
   sensor_msgs
   std_msgs
)


#-------------------------------------------------------#
#            catkin specific configuration              #
#-------------------------------------------------------#


### PACKAGE
catkin_package(
  LIBRARIES meccanoid_user_interface 
	meccanoid_map 
	meccanoid_positioning
	meccanoid_face_localization
	meccanoid_motors
	meccanoid_face_detection
	meccanoid_path_planning
	meccanoid_obstacle_avoidance
	meccanoid_teleop
  CATKIN_DEPENDS 
  cv_bridge 
  image_transport 
  roscpp 
  message_runtime
  sensor_msgs 
  std_msgs
)


#--------------------------------------------------------#
#                        Build                           #
#--------------------------------------------------------#


### INCLUDES
include($ENV{ROS_ROOT}/core/rosbuild/FindPkgConfig.cmake)
include_directories( include )
include_directories( ${catkin_INCLUDE_DIRS} )
include_directories( ${roscpp_INCLUDE_DIRS} )


### LIBRARIES
add_library(
 meccanoid_map_representation src/meccanoid_map/map.cpp include/meccanoid_map/map.hpp
)

add_library(
marvelmind_nav src/meccanoid_positioning/marvelmind_hedge.c
)

add_library(
 meccanoid_servo_control src/meccanoid_face_localization/meccanoid_servo_control.c include/meccanoid_face_localization/meccanoid_servo_control.h
)

add_library(
 meccanoid_motor_control src/meccanoid_motors/meccanoid_motor_control.c include/meccanoid_motors/meccanoid_motor_control.h
)


### EXECUTABLES
add_executable(meccanoid_user_interface_node 
  src/meccanoid_user_interface/meccanoid_user_interface_node.cpp
)

add_executable(meccanoid_map_node 
  src/meccanoid_map/meccanoid_map_node.cpp src/meccanoid_map/map.cpp
)

add_executable(meccanoid_positioning_node
  src/meccanoid_positioning/meccanoid_positioning_node.cpp src/meccanoid_positioning/marvelmind_hedge.c
)

add_executable(meccanoid_face_localization_node
  src/meccanoid_face_localization/meccanoid_face_localization_node.cpp src/meccanoid_face_localization/meccanoid_servo_control.c
)

add_executable(meccanoid_motors_node
  src/meccanoid_motors/meccanoid_motors_node.cpp src/meccanoid_motors/meccanoid_motor_control.c
)

add_executable(meccanoid_face_detection_node
  src/meccanoid_face_detection/meccanoid_face_detection_node.cpp
)

add_executable(meccanoid_path_planning_node
  src/meccanoid_path_planning/meccanoid_path_planning_node.cpp src/meccanoid_map/map.cpp
)

add_executable(meccanoid_obstacle_avoidance_node
  src/meccanoid_obstacle_avoidance/meccanoid_obstacle_avoidance_node.cpp
)

add_executable(meccanoid_position_visualization_node
  src/meccanoid_positioning/subscriber_test.cpp src/meccanoid_positioning/marvelmind_hedge.c
)

add_executable(meccanoid_teleop_node
  src/meccanoid_teleop/meccanoid_teleop_node.cpp
)

### EXECUTABLE DEPENDENCIES
add_dependencies(meccanoid_user_interface_node 
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(meccanoid_map_node 
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(meccanoid_positioning_node 
marvelmind_nav_generate_messages_cpp
)

add_dependencies(meccanoid_face_localization_node
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(meccanoid_motors_node
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(meccanoid_face_detection_node
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(meccanoid_path_planning_node
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(meccanoid_obstacle_avoidance_node
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(meccanoid_position_visualization_node
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

add_dependencies(meccanoid_teleop_node
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

### TARGET LINKS
target_link_libraries(meccanoid_user_interface_node
   ${catkin_LIBRARIES}
)

target_link_libraries(meccanoid_map_node
   ${catkin_LIBRARIES}
)

target_link_libraries(meccanoid_positioning_node
 ${catkin_LIBRARIES}
)

target_link_libraries(meccanoid_face_localization_node
 ${catkin_LIBRARIES}
)

target_link_libraries(meccanoid_motors_node
 ${catkin_LIBRARIES}
)

target_link_libraries(meccanoid_face_detection_node
 ${catkin_LIBRARIES}
 ${OpenCV_LIBRARIES}
)

target_link_libraries(meccanoid_path_planning_node
 ${catkin_LIBRARIES}
)

target_link_libraries(meccanoid_obstacle_avoidance_node
 ${catkin_LIBRARIES}
 ${OpenCV_LIBRARIES}
)

target_link_libraries(meccanoid_position_visualization_node
 ${catkin_LIBRARIES}
)

target_link_libraries(meccanoid_teleop_node
 ${catkin_LIBRARIES}
)


#---------------------------------------------------------#
#                         Install                         #
#---------------------------------------------------------#


## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
#install(TARGETS meccanoid_user_interface_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#)

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
#)

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )


#------------------------------------------------------------#
#                          Testing                           #
#------------------------------------------------------------#


## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_meccanoid_face_detection.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
