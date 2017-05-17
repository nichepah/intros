//subscribes to /turtle1/Pose and shows the message on screen

#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <iomanip>

void poseMsgRcvd(const turtlesim::Pose &msg) {
ROS_INFO_STREAM("position"<<msg.x<<","<<msg.y <<"; direction"<<msg.theta);
}

int main(int argc, char **argv) {
//initialize ROS 
ros::init(argc, argv, "subscribe_to_pose");
ros::NodeHandle nh;
ros::Subscriber sub = nh.subscribe("turtle1/pose", 1000, &poseMsgRcvd);
ros::spin(); 
}

