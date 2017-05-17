/* Publishes messages for a pick and place demo
   Written by Aneesh PA on 04/05/17 for Kuka Youbot
   Tested on Gazebo first
*/
#include <ros/ros.h>
#include <unistd.h> //for usleep
#include <trajectory_msgs/JointTrajectory.h>

int main(int argc, char **argv) {
 ros::init(argc, argv, "node_pick_n_place_publisher");  //node
 ros::NodeHandle nhArm, nhGripper;
 ros::Publisher armPub = nhArm.advertise<trajectory_msgs::JointTrajectory>("/arm_1/arm_controller/command", 1000);
 ros::Publisher gripperPub = nhGripper.advertise<trajectory_msgs::JointTrajectory>("/arm_1/gripper_controller/command", 1000);
 ROS_INFO_STREAM("armPub node created");

 ros::Rate rate(1);
 trajectory_msgs::JointTrajectory msgArm, msgGripper;
 int sleepDelay = 60; //delay in seconds, to let the arm reach the previous target positions.
 int topicCount = 2;

 // Common parameters for msgArm
 msgArm.joint_names.resize(5);
 msgArm.joint_names[0] = "arm_joint_1";
 msgArm.joint_names[1] = "arm_joint_2";
 msgArm.joint_names[2] = "arm_joint_3";
 msgArm.joint_names[3] = "arm_joint_4";
 msgArm.joint_names[4] = "arm_joint_5";
 // Let waypoints be one only
 int way_points = 1;
 msgArm.points.resize(way_points);
 int ind=0;
 msgArm.points[ind].positions.resize(5);
 // Velocities, even if not required fill them
 float velArm = 0.0;
 msgArm.points[ind].velocities.resize(5);
 for(size_t j=0; j<2; j++) {
     msgArm.points[ind].velocities[j]=velArm;
 }
 // time to start for waypoint;
 msgArm.points[ind].time_from_start= ros::Duration(1.0);

 // Common parameters for msgGripper
 msgGripper.joint_names.resize(2);
 msgGripper.joint_names[0] = "gripper_finger_joint_l";
 msgGripper.joint_names[1] = "gripper_finger_joint_r";

 way_points = 1;
 msgGripper.points.resize(way_points);
 ind=0;
 msgGripper.points[ind].positions.resize(2);
 msgGripper.points[ind].velocities.resize(2);
 float velGripper = 0.0;
 for(size_t j=0; j<2; j++) {
     msgGripper.points[ind].velocities[j]= velGripper;
 }
 msgGripper.points[ind].time_from_start= ros::Duration(1.0);

 // Pick pose
 int count = 0;
 while (ros::ok() && count < topicCount)
 {
   msgArm.points[ind].positions[0]=0.05;
   msgArm.points[ind].positions[1]=0.05;
   msgArm.points[ind].positions[2]=-3.37;
   msgArm.points[ind].positions[3]=0.50;
   msgArm.points[ind].positions[4]= 1.21;
   // Open Gripper
   msgGripper.points[ind].positions[0]=0.1;
   msgGripper.points[ind].positions[1]=0.1;

   armPub.publish(msgArm);
   gripperPub.publish(msgGripper);
   count++;
   rate.sleep();
   ROS_INFO("armPub to Pick Pose at (0.05:0.05:-3.37:0.5:1.21); Gripper Opens; Count: %d\n", count);
   }
 sleep(1.0*sleepDelay); //To let the links reach topic targets


 // Go down to pick pose
 count = 0;
 while (ros::ok() && count < topicCount)
 {
   msgArm.points[ind].positions[0]=0.05;
   msgArm.points[ind].positions[1]=0.00;
   msgArm.points[ind].positions[2]=-3.37;
   msgArm.points[ind].positions[3]=0.53;
   msgArm.points[ind].positions[4]= 1.21;
   // Open Gripper
   msgGripper.points[ind].positions[0]=0.1;
   msgGripper.points[ind].positions[1]=0.1;

   armPub.publish(msgArm);
   gripperPub.publish(msgGripper);
   count++;
   rate.sleep();
   ROS_INFO("armPub to Pick down Pose at (0.05:0.00:-3.37:0.53:1.21); Gripper opened; Count: %d\n", count);
   }
 sleep(0.1*sleepDelay); //To let the links reach topic targets


 // Grab the object, move grippers half way
 count = 0;
 while (ros::ok() && count < topicCount)
 {
     msgGripper.points[ind].positions[0]=0.05;
     msgGripper.points[ind].positions[0]=0.05;

     gripperPub.publish(msgGripper);
     count++;
     rate.sleep();
     ROS_INFO("Gripper closes half way to grab; Count: %d\n", count);

 }
 sleep(0.1*sleepDelay);

 // Hold and rotate to destination
 count = 0;
 while (ros::ok() && count < topicCount)
 {
   msgArm.points[ind].positions.resize(5);
   msgArm.points[ind].positions[0]=0.05;
   msgArm.points[ind].positions[1]=0.59;
   msgArm.points[ind].positions[2]=-3.37;
   msgArm.points[ind].positions[3]=0.53;
   msgArm.points[ind].positions[4]= 1.21;

   armPub.publish(msgArm);
   count++;
   rate.sleep();
   ROS_INFO("Arm to hold at (0.05:0.59:-3.37:0.53:1.21); only j2 changed; Count: %d\n", count);;
   }
 sleep(1*sleepDelay);

 //rotate base to drop destination
 count=0;
 while (ros::ok() && count < 2)
 {
   msgArm.points[ind].positions[0]=3.00;
   msgArm.points[ind].positions[1]=0.59;
   msgArm.points[ind].positions[2]=-3.37;
   msgArm.points[ind].positions[3]=0.53;
   msgArm.points[ind].positions[4]= 1.21;

   armPub.publish(msgArm);
   count++;
   rate.sleep();
   ROS_INFO("armPub to Rotate at J1 and bend at (3.00:0.59:-3.37:0.53:1.21); Count: %d\n", count);;
 }
 sleep(1*sleepDelay);

 //bend to drop
 count=0;
 while (ros::ok() && count < 2)
 {
   msgArm.points[ind].positions[0]=3.00;
   msgArm.points[ind].positions[1]=0.49;
   msgArm.points[ind].positions[2]=-3.37;
   msgArm.points[ind].positions[3]=0.53;
   msgArm.points[ind].positions[4]= 1.21;

   armPub.publish(msgArm);
   count++;
   rate.sleep();
   ROS_INFO("bend to drop only j2 changed to 0.49 (3.00:0.49:-3.37:0.53:1.21); Count: %d\n", count);;
 }
 sleep(0.2*sleepDelay);


 //Open grippers and Drop the object
 while (ros::ok() && count<2)
 {
    msgGripper.points[ind].positions[0]=0.01;
    msgGripper.points[ind].positions[0]=0.01;

    gripperPub.publish(msgGripper);
    count++;
    rate.sleep();
    ROS_INFO("Grippers open to drop the object; Count: %d\n", count);
  }
 sleep(0.2*sleepDelay);


 count = 0;
   while (ros::ok() && count < 2)
   {
     msgArm.points[ind].positions.resize(5);
     msgArm.points[ind].positions[0]=0.05;
     msgArm.points[ind].positions[1]=0.16;
     msgArm.points[ind].positions[2]=-0.27;
     msgArm.points[ind].positions[3]=0.19;
     msgArm.points[ind].positions[4]= 0.1;

     armPub.publish(msgArm);
     count++;
     rate.sleep();
     }
   ROS_INFO("armPub to Home at (0.05:0.16:-0.27:0.19:0.1); Count: %d\n", count);;
   sleep(sleepDelay);
}

