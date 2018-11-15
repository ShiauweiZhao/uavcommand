/**
 * @file offb_node.cpp
 * @brief offboard example node, written with mavros version 0.14.2, px4 flight
 * stack and tested in Gazebo SITL
 */

#include <ros/ros.h>
#include <std_msgs/UInt8.h>
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  ros::init(argc, argv, "uav_command_node");
  ros::NodeHandle nh;

  ros::Publisher uav_command_pub =
      nh.advertise<std_msgs::UInt8>("mul/command", 1);

  ros::Rate loop_rate(10);
  ros::spinOnce();

  std_msgs::UInt8 uav_command;
  uav_command.data = 0;

  int count = 0;
  while (ros::ok()) {
    if (count == 0) {
      cin >> uav_command.data;
    }
    if (count <= 5) uav_command_pub.publish(uav_command);

    if (count > 5) {
      uav_command.data = 0;
      uav_command_pub.publish(uav_command);
    }
    count++;
    if (count == 20) count = 0;
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
