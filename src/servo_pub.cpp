//servo demo
//written on 14/03/17
//by Aneesh PA, RDCIS
//for arduino controlled manipulator with 3 servos
//use rosserrial_python to connect arduino to ros
// 

#include <ros/ros.h>
#include <std_msgs/UInt16.h>

int main(int argc, char **argv) {
 ros::init(argc, argv, "node_pub_servo_angle");
 ros::NodeHandle nh;

 ros::Publisher pub1 = nh.advertise<std_msgs::UInt16>("/servo1", 1000);
 ros::Publisher pub2 = nh.advertise<std_msgs::UInt16>("/servo2", 1000);
 ros::Publisher pub3 = nh.advertise<std_msgs::UInt16>("/servo3", 1000);

 ROS_INFO_STREAM("pub nodes for servos created");
 int sub_count = pub1.getNumSubscribers(); //get number of subscribers
 if (sub_count == 0) {
    ROS_INFO_STREAM("sub_count"<<sub_count);
    usleep(1); //microseconds
    }
else{
    ROS_INFO_STREAM("sub_count"<<sub_count);
    }

ros::Rate rate(0.5);

while(ros::ok()) {
   std_msgs::UInt16 msg;
   msg.data=10;
   pub2.publish(msg);
   
  /* for(int i=0; i<180; i=i+10)
    {
     msg.data = i;
     //pub1.publish(msg);
     pub2.publish(msg);
     //pub3.publish(msg);
     //wait until its time
     rate.sleep();
     ROS_INFO_STREAM("Sending val to topic");
   }

   for(int i=180; i>0; i=i-10)
    {
     msg.data = i;
     //pub1.publish(msg);
     //pub2.publish(msg);
     pub2.publish(msg);
     //wait until its time
     rate.sleep();
     ROS_INFO_STREAM("Sending val to topic");
   }
*/
   }
} 


