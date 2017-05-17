cmake_minimum_required(VERSION 2.8.3)
project(intros)

find_package(catkin REQUIRED)

## System dependencies are found with CMake's conventions
find_package(catkin REQUIRED COMPONENTS roscpp trajectory_msgs turtlesim std_msgs )

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include ${catkin_INCLUDE_DIRS})

## Call this before add_executable, else the executable might not be 
## visible to rosrun
catkin_package()

## Declare a C++ executable
add_executable(hello src/hello.cpp)
add_executable(pubvel src/agitr_pubvel.cpp)
add_executable(agitr_sub src/agitr_sub.cpp)
add_executable(vel_rev src/rev_vel.cpp)
add_executable(servo_pub src/servo_pub.cpp)
add_executable(youbot_bend_to_pick src/youbot_bend_to_pick.cpp)
add_executable(youbot_bend src/youbot_bend.cpp)
add_executable(youbot_gripper_open src/youbot_gripper_open.cpp)
add_executable(youbot_gripper_close src/youbot_gripper_close.cpp)
add_executable(youbot_home src/youbot_home.cpp)
add_executable(youbot_base_rotate_bend src/youbot_base_rotate_bend.cpp)
add_executable(youbot_gazebo_pick_n_place src/youbot_gazebo_pick_n_place.cpp)


## Specify libraries to link a library or executable target against

target_link_libraries(pubvel
   ${catkin_LIBRARIES}
 )
target_link_libraries(hello
   ${catkin_LIBRARIES}
 )
target_link_libraries(agitr_sub
   ${catkin_LIBRARIES}
)
target_link_libraries(vel_rev
   ${catkin_LIBRARIES}
)
target_link_libraries(servo_pub
   ${catkin_LIBRARIES}
)
target_link_libraries(youbot_bend_to_pick
   ${catkin_LIBRARIES}
)
target_link_libraries(youbot_bend
   ${catkin_LIBRARIES}
)
target_link_libraries(youbot_gripper_open
   ${catkin_LIBRARIES}
)
target_link_libraries(youbot_gripper_close
   ${catkin_LIBRARIES}
)
target_link_libraries(youbot_home
   ${catkin_LIBRARIES}
)
target_link_libraries(youbot_base_rotate_bend
    ${catkin_LIBRARIES}
)
target_link_libraries(youbot_gazebo_pick_n_place
    ${catkin_LIBRARIES}
)
