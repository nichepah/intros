/* publishes messages to perform final bend to object at ground
 * Alters only joint 2, 3 and 4 only
 * This is to be run after youbot_bend.
   Written by Aneesh PA on 04/05/17 for Kuka Youbot
   Tested on Gazebo first
*/
#include <ros/ros.h>
#include <unistd.h> //for usleep
#include <trajectory_msgs/JointTrajectory.h>

int main(int argc, char **argv) {
 ros::init(argc, argv, "node_pubvel1");
 ros::NodeHandle nh;
 ros::Publisher pub = nh.advertise<trajectory_msgs::JointTrajectory>("/arm_1/arm_controller/command", 1000);

 ROS_INFO_STREAM("pub node created");
int sub_count = pub.getNumSubscribers(); //get number of subscribers
if (sub_count == 0) {
    ROS_INFO_STREAM("sub_count"<<sub_count);
    usleep(1); //microseconds
    }
else{
    ROS_INFO_STREAM("sub_count"<<sub_count);
    }

ros::Rate rate(1);
ROS_INFO_STREAM("enterring ros::ok loop");

while (ros::ok()) {

   trajectory_msgs::JointTrajectory msg;
  // msg.header.seq = iSeq;
   //msg.header.stamp.sec =
   ROS_INFO_STREAM("to resize joint names array");

   msg.joint_names.resize(5);
   msg.joint_names[0] = "arm_joint_1";
   msg.joint_names[1] = "arm_joint_2";
   msg.joint_names[2] = "arm_joint_3";
   msg.joint_names[3] = "arm_joint_4";
   msg.joint_names[4] = "arm_joint_5";

   ROS_INFO_STREAM("after resize joint names array");
   // resize to the number of way points
   int way_points = 1;
   msg.points.resize(way_points);

   // Start waypoint #0; all home positions except joint 5
   int ind=0;
   msg.points[ind].positions.resize(5);
   msg.points[ind].positions[0]=0.5;
   msg.points[ind].positions[1]=0.03;
   msg.points[ind].positions[2]=-3.52;
   msg.points[ind].positions[3]=0.86;
   msg.points[ind].positions[4]= 2.91;

   // fill velocities for waypoint #0 as 0
   msg.points[ind].velocities.resize(5);
   for(size_t j=0; j<5; j++) {
       msg.points[ind].velocities[j]=0;
   }
   // time to start for waypoint 0; initial stamp is 0 in header by default
   msg.points[ind].time_from_start= ros::Duration(1.0);
   // End waypoint #0

   pub.publish(msg);
   //wait until its time
   rate.sleep();
   ROS_INFO_STREAM("Sending val to topic");
   }
}

