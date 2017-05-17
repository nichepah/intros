//publishes randomly generated velocity messages
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h> //for rand
#include <unistd.h> //for usleep

int main(int argc, char **argv) {
 ros::init(argc, argv, "node_pubvel1");
 ros::NodeHandle nh;
 ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
ROS_INFO_STREAM("pub node created");
int sub_count = pub.getNumSubscribers(); //get number of subscribers
if (sub_count == 0) {
    ROS_INFO_STREAM("sub_count"<<sub_count);
    usleep(1); //microseconds
    }
else{
    ROS_INFO_STREAM("sub_count"<<sub_count);
    }

//random seed
srand(time(0));
ros::Rate rate(1);

while(ros::ok()) {
   geometry_msgs::Twist msg;
   msg.linear.x = double(rand())/double(RAND_MAX);
   msg.angular.z = double(rand())/double(RAND_MAX) - 1;
   pub.publish(msg);
   //wait until its time
   rate.sleep();
   ROS_INFO_STREAM("Sending val to topic");
   }
} 


