/** Subscribes to "/arm_1/arm_controller/command" published by rqt gui and publishes relevant
 *  information to "/mybot/arm_1/arm_controller/position_command"
 *  In effect the messages published in "trajectory_msgs/JointTrajectory" are converted to
 *  to "brics_actuator/JointPositions"
 *  This way both the simulated robot in gazebo and the actual bot can be controlled via rqt plugin
 *  Written by Aneesh PA on 05/06/2017; mypa4me@gmail.com
 ***/

#include <ros/ros.h>
#include <iomanip>
#include <trajectory_msgs/JointTrajectory.h>
#include <brics_actuator/JointPositions.h>

#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/io.hpp>

// This piece of code works, however its dirty; a better method is the
// one using the class
/*
void poseMsgRcvd(const turtlesim::Pose &msg) {
ROS_INFO_STREAM("position"<<msg.x<<","<<msg.y <<"; direction"<<msg.theta);
}
*/
/*

void trajMsgRcvd(const trajectory_msgs::JointTrajectory &msg){
    ROS_INFO_STREAM("timestamp"<<msg.header.stamp<<"; joints "<<msg.joint_names[0] << "; position "<<msg.points[0].positions[0]<<";"<<msg.points[0].positions[1]); //;

}

int main(int argc, char **argv) {
//initialize ROS
ros::init(argc, argv, "subscribe_to_jointTrajectoryMsgs");
ros::NodeHandle nh;
ros::Subscriber sub = nh.subscribe("/arm_1/arm_controller/command", 1000, &trajMsgRcvd);
ros::Publisher pub =
ros::spin();
}
*/


class SubPubBridge
{
private:
    ros::NodeHandle n;
    ros::Subscriber subTrajMsg, subGripperMsg;
    ros::Publisher pubBricsPos, pubGripperBricsPos;

public:
    SubPubBridge(){
        //for the arm control
        subTrajMsg=n.subscribe("/arm_1/arm_controller/command", 1, &SubPubBridge::trajMsgRcvdCallBack, this);
        pubBricsPos =n.advertise<brics_actuator::JointPositions > ("/mybot/arm_1/arm_controller/position_command", 1);

        //for gripper control
        subGripperMsg=n.subscribe("/arm_1/gripper_controller/command", 1, &SubPubBridge::gripperMsgRcvdCallBack, this);
        pubGripperBricsPos =n.advertise<brics_actuator::JointPositions > ("/mybot/arm_1/gripper_controller/position_command", 1);

    }

    //for arm control
    void trajMsgRcvdCallBack(const trajectory_msgs::JointTrajectory &msg){
        const int numberOfArmJoints = 5;
        brics_actuator::JointPositions command;
        std::vector <brics_actuator::JointValue> armJointPositions;
        armJointPositions.resize(numberOfArmJoints); //number of arm joints


       /* for (int i=0; i < numberOfArmJoints; i++) {
            armJointPositions[i].joint_uri = msg.joint_names[i];
            armJointPositions[i].value = msg.points[0].positions[i];
            armJointPositions[i].unit = boost::units::to_string(boost::units::si::radians);
            //ROS_INFO_STREAM("Recevied msg timestamp"<<msg.header.stamp<<"; joints "<<msg.joint_names[i] << "; position" <<msg.points[0].positions[i]<<";";
        } */

        armJointPositions[0].joint_uri = "arm_joint_1";
        armJointPositions[1].joint_uri = "arm_joint_2";
        armJointPositions[2].joint_uri = "arm_joint_3";
        armJointPositions[3].joint_uri = "arm_joint_4";
        armJointPositions[4].joint_uri = "arm_joint_5";

        armJointPositions[0].value = msg.points[0].positions[0];
        armJointPositions[1].value = msg.points[0].positions[1];
        armJointPositions[2].value = msg.points[0].positions[2];
        armJointPositions[3].value = msg.points[0].positions[3];
        armJointPositions[4].value = msg.points[0].positions[4];

        armJointPositions[0].unit = boost::units::to_string(boost::units::si::radians);
        armJointPositions[1].unit = boost::units::to_string(boost::units::si::radians);
        armJointPositions[2].unit = boost::units::to_string(boost::units::si::radians);
        armJointPositions[3].unit = boost::units::to_string(boost::units::si::radians);
        armJointPositions[4].unit = boost::units::to_string(boost::units::si::radians);


        command.positions = armJointPositions;
        pubBricsPos.publish(command);
    }

    //for gripper control
    void gripperMsgRcvdCallBack(const trajectory_msgs::JointTrajectory &msg){
        const int numberOfGripperJoints = 2;
        brics_actuator::JointPositions command;
        std::vector <brics_actuator::JointValue> gripperJointPositions;
        gripperJointPositions.resize(numberOfGripperJoints); //number of gripper joints


       /* for (int i=0; i < numberOfArmJoints; i++) {
            armJointPositions[i].joint_uri = msg.joint_names[i];
            armJointPositions[i].value = msg.points[0].positions[i];
            armJointPositions[i].unit = boost::units::to_string(boost::units::si::radians);
            //ROS_INFO_STREAM("Recevied msg timestamp"<<msg.header.stamp<<"; joints "<<msg.joint_names[i] << "; position" <<msg.points[0].positions[i]<<";";
        } */

        gripperJointPositions[0].joint_uri = "gripper_finger_joint_l";
        gripperJointPositions[1].joint_uri = "gripper_finger_joint_r";

        gripperJointPositions[0].value = msg.points[0].positions[0];
        gripperJointPositions[1].value = msg.points[0].positions[1];

        gripperJointPositions[0].unit = "m"; //boost::units::to_string(boost::units::si::meter_base_unit);
        gripperJointPositions[1].unit = "m"; //boost::units::to_string(boost::units::si::meter_base_unit);

        command.positions = gripperJointPositions;
        pubGripperBricsPos.publish(command);
    }

};

int main(int argc, char **argv) {
//initialize ROS
ros::init(argc, argv, "SubPubBridge");
SubPubBridge myBridgeObject;
ros::spin();
return (0);
}

