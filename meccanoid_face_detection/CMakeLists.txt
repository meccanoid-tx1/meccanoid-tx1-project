cmake_minimum_required(VERSION 2.8.3)
project(meccanoid_face_detection)

### find catkin required system packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
#  message_generation
)

### find other required packages
find_package(OpenCV REQUIRED)


#-----------------------------------------------------#
#    Declare ROS messages, services and actions       #
#-----------------------------------------------------#


### MESSAGES
#add_message_files(
#   FILES
#   meccanoid_face_location.msg
   #bounding_box_msg.msg
#)

### SERVICES
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

### ACTIONS
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

### MESSAGE AND SERVICE DEPENDENCIES
#generate_messages(
#   DEPENDENCIES
#   sensor_msgs
#   std_msgs
#)


#-------------------------------------------------------#
#            catkin specific configuration              #
#-------------------------------------------------------#


### PACKAGE
catkin_package(
  LIBRARIES meccanoid_face_detection
  CATKIN_DEPENDS 
  cv_bridge 
  image_transport 
  roscpp 
  sensor_msgs 
  std_msgs
  meccanoid_face_localization
)


#--------------------------------------------------------#
#                        Build                           #
#--------------------------------------------------------#

### INCLUDES
include($ENV{ROS_ROOT}/core/rosbuild/FindPkgConfig.cmake)
# include_directories( include )
include_directories( ${catkin_INCLUDE_DIRS} )

### LIBRARIES
# add_library(
#  bounding_box src/bounding_box/bounding_box.cpp
# )

### LIBRARY DEPENDENCIES
# add_dependencies( 
#   bounding_box
#   ${${PROJECT_NAME}_EXPORTED_TARGETS} 
#   ${catkin_EXPORTED_TARGETS}
# )

### EXECUTABLES
add_executable(meccanoid_face_detection_node 
  src/meccanoid_face_detection_node.cpp
)

### EXECUTABLE DEPENDENCIES
add_dependencies(meccanoid_face_detection_node 
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

### TARGET LINKS
target_link_libraries(meccanoid_face_detection_node
   ${catkin_LIBRARIES}
   ${OpenCV_LIBRARIES}
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
install(TARGETS meccanoid_face_detection_node
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

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
