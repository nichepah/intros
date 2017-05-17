
#include <ros/ros.h>

int main(int argc, char **argv) {

//initialize the ros system
ros::init(argc, argv, "hello_ros");

//ros node
ros::NodeHandle nh;


ROS_INFO_STREAM("Hello, ROS from Qt..wow..!");
}
