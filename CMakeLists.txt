cmake_minimum_required(VERSION 2.8.3)
project(transforms)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    tf
)


## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs  # Or other packages containing msgs
# )

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES transforms
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

include_directories(include ${catkin_INCLUDE_DIRS})

## Declare a cpp executable
add_executable(sensor1_tf_node src/ir1_tf_broadcaster.cpp)
add_executable(sensor2_tf_node src/ir2_tf_broadcaster.cpp)
add_executable(sensor3_tf_node src/ir3_tf_broadcaster.cpp)
add_executable(sensor4_tf_node src/ir4_tf_broadcaster.cpp)
add_executable(map_robot_tf_node src/map_robot_tf.cpp)


## Specify libraries to link a library or executable target against
target_link_libraries(sensor1_tf_node ${catkin_LIBRARIES})
target_link_libraries(sensor2_tf_node ${catkin_LIBRARIES})
target_link_libraries(sensor3_tf_node ${catkin_LIBRARIES})
target_link_libraries(sensor4_tf_node ${catkin_LIBRARIES})
target_link_libraries(map_robot_tf_node ${catkin_LIBRARIES})

