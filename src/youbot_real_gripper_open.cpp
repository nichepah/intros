/* publishes topic for opening gripper
   Written by Aneesh PA on 04/05/17 for Kuka Youbot
   Tested on Gazebo first
*/
#include <ros/ros.h>
#include <unistd.h> //for usleep
#include <trajectory_msgs/JointTrajectory.h>
#include <brics_actuator/JointPositions.h>

int main(int argc, char **argv) {
 ros::init(argc, argv, "node_pubvel1");
 ros::NodeHandle nh;

 ros::Publisher pub = nh.advertise<brics_actuator::JointPositions>("/arm_1/gripper_controller/position_command", 1000);

 ROS_INFO_STREAM("Finger opening pub node created");

ros::Rate rate(1);
ROS_INFO_STREAM("enterring ros::ok loop");

int count = 0;

while (ros::ok() && count < 2) {

   brics_actuator::JointPositions msg;
   //ROS_INFO_STREAM("to resize joint names array");
   msg.positions.resize(2);
   msg.positions[0].joint_uri="gripper_finger_joint_r";
   msg.positions[0].unit="m";
   msg.positions[0].value=0.01;

   msg.positions[1].joint_uri="gripper_finger_joint_l";
   msg.positions[1].unit="m";
   msg.positions[1].value=0.005;

   pub.publish(msg);
//   pub.publish(msg_l);
   ++count;
   //wait until its time
   rate.sleep();
   ROS_INFO_STREAM("Opened Fingers");
   }
}

