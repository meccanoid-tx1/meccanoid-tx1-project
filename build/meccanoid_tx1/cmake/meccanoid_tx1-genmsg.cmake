# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "meccanoid_tx1: 3 messages, 0 services")

set(MSG_I_FLAGS "-Imeccanoid_tx1:/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map/;-Imeccanoid_tx1:/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_positioning/;-Isensor_msgs:/opt/ros/kinetic/share/sensor_msgs/cmake/../msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(meccanoid_tx1_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map_pos.msg" NAME_WE)
add_custom_target(_meccanoid_tx1_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "meccanoid_tx1" "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map_pos.msg" ""
)

get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map.msg" NAME_WE)
add_custom_target(_meccanoid_tx1_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "meccanoid_tx1" "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map.msg" ""
)

get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_positioning//hedge_pos.msg" NAME_WE)
add_custom_target(_meccanoid_tx1_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "meccanoid_tx1" "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_positioning//hedge_pos.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(meccanoid_tx1
  "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_positioning//hedge_pos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/meccanoid_tx1
)
_generate_msg_cpp(meccanoid_tx1
  "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/meccanoid_tx1
)
_generate_msg_cpp(meccanoid_tx1
  "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map_pos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/meccanoid_tx1
)

### Generating Services

### Generating Module File
_generate_module_cpp(meccanoid_tx1
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/meccanoid_tx1
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(meccanoid_tx1_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(meccanoid_tx1_generate_messages meccanoid_tx1_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map_pos.msg" NAME_WE)
add_dependencies(meccanoid_tx1_generate_messages_cpp _meccanoid_tx1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map.msg" NAME_WE)
add_dependencies(meccanoid_tx1_generate_messages_cpp _meccanoid_tx1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_positioning//hedge_pos.msg" NAME_WE)
add_dependencies(meccanoid_tx1_generate_messages_cpp _meccanoid_tx1_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(meccanoid_tx1_gencpp)
add_dependencies(meccanoid_tx1_gencpp meccanoid_tx1_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS meccanoid_tx1_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(meccanoid_tx1
  "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_positioning//hedge_pos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/meccanoid_tx1
)
_generate_msg_eus(meccanoid_tx1
  "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/meccanoid_tx1
)
_generate_msg_eus(meccanoid_tx1
  "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map_pos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/meccanoid_tx1
)

### Generating Services

### Generating Module File
_generate_module_eus(meccanoid_tx1
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/meccanoid_tx1
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(meccanoid_tx1_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(meccanoid_tx1_generate_messages meccanoid_tx1_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map_pos.msg" NAME_WE)
add_dependencies(meccanoid_tx1_generate_messages_eus _meccanoid_tx1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map.msg" NAME_WE)
add_dependencies(meccanoid_tx1_generate_messages_eus _meccanoid_tx1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_positioning//hedge_pos.msg" NAME_WE)
add_dependencies(meccanoid_tx1_generate_messages_eus _meccanoid_tx1_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(meccanoid_tx1_geneus)
add_dependencies(meccanoid_tx1_geneus meccanoid_tx1_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS meccanoid_tx1_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(meccanoid_tx1
  "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_positioning//hedge_pos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/meccanoid_tx1
)
_generate_msg_lisp(meccanoid_tx1
  "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/meccanoid_tx1
)
_generate_msg_lisp(meccanoid_tx1
  "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map_pos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/meccanoid_tx1
)

### Generating Services

### Generating Module File
_generate_module_lisp(meccanoid_tx1
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/meccanoid_tx1
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(meccanoid_tx1_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(meccanoid_tx1_generate_messages meccanoid_tx1_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map_pos.msg" NAME_WE)
add_dependencies(meccanoid_tx1_generate_messages_lisp _meccanoid_tx1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map.msg" NAME_WE)
add_dependencies(meccanoid_tx1_generate_messages_lisp _meccanoid_tx1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_positioning//hedge_pos.msg" NAME_WE)
add_dependencies(meccanoid_tx1_generate_messages_lisp _meccanoid_tx1_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(meccanoid_tx1_genlisp)
add_dependencies(meccanoid_tx1_genlisp meccanoid_tx1_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS meccanoid_tx1_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(meccanoid_tx1
  "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_positioning//hedge_pos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/meccanoid_tx1
)
_generate_msg_nodejs(meccanoid_tx1
  "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/meccanoid_tx1
)
_generate_msg_nodejs(meccanoid_tx1
  "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map_pos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/meccanoid_tx1
)

### Generating Services

### Generating Module File
_generate_module_nodejs(meccanoid_tx1
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/meccanoid_tx1
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(meccanoid_tx1_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(meccanoid_tx1_generate_messages meccanoid_tx1_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map_pos.msg" NAME_WE)
add_dependencies(meccanoid_tx1_generate_messages_nodejs _meccanoid_tx1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map.msg" NAME_WE)
add_dependencies(meccanoid_tx1_generate_messages_nodejs _meccanoid_tx1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_positioning//hedge_pos.msg" NAME_WE)
add_dependencies(meccanoid_tx1_generate_messages_nodejs _meccanoid_tx1_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(meccanoid_tx1_gennodejs)
add_dependencies(meccanoid_tx1_gennodejs meccanoid_tx1_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS meccanoid_tx1_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(meccanoid_tx1
  "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_positioning//hedge_pos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/meccanoid_tx1
)
_generate_msg_py(meccanoid_tx1
  "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/meccanoid_tx1
)
_generate_msg_py(meccanoid_tx1
  "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map_pos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/meccanoid_tx1
)

### Generating Services

### Generating Module File
_generate_module_py(meccanoid_tx1
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/meccanoid_tx1
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(meccanoid_tx1_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(meccanoid_tx1_generate_messages meccanoid_tx1_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map_pos.msg" NAME_WE)
add_dependencies(meccanoid_tx1_generate_messages_py _meccanoid_tx1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_map//meccanoid_map.msg" NAME_WE)
add_dependencies(meccanoid_tx1_generate_messages_py _meccanoid_tx1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jesper/Documents/Programming/Kandidat/src/meccanoid_tx1/msg/meccanoid_positioning//hedge_pos.msg" NAME_WE)
add_dependencies(meccanoid_tx1_generate_messages_py _meccanoid_tx1_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(meccanoid_tx1_genpy)
add_dependencies(meccanoid_tx1_genpy meccanoid_tx1_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS meccanoid_tx1_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/meccanoid_tx1)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/meccanoid_tx1
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(meccanoid_tx1_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(meccanoid_tx1_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/meccanoid_tx1)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/meccanoid_tx1
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(meccanoid_tx1_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(meccanoid_tx1_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/meccanoid_tx1)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/meccanoid_tx1
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(meccanoid_tx1_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(meccanoid_tx1_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/meccanoid_tx1)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/meccanoid_tx1
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(meccanoid_tx1_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(meccanoid_tx1_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/meccanoid_tx1)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/meccanoid_tx1\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/meccanoid_tx1
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(meccanoid_tx1_generate_messages_py sensor_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(meccanoid_tx1_generate_messages_py std_msgs_generate_messages_py)
endif()
