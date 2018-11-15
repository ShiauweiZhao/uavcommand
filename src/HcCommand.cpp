/**
 * @file offb_node.cpp
 * @brief offboard example node, written with mavros version 0.14.2, px4 flight
 * stack and tested in Gazebo SITL
 */

#include <geometry_msgs/Vector3.h>
#include <ros/ros.h>
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  ros::init(argc, argv, "uav_command_node");
  ros::NodeHandle nh;

  ros::Publisher stop_uav_pub =
      nh.advertise<geometry_msgs::Vector3>("mul/command", 1);

  ros::Rate loop_rate(10);
  ros::spinOnce();

  geometry_msgs::Vector3 stop_command;

  stop_command.x = 0;
  stop_command.y = 0;
  stop_command.z = 0;

  int count = 0;

  while (ros::ok()) {
    if (count == 0) {
      cin >> stop_command.x;
    }
    if (count <= 5) stop_uav_pub.publish(stop_command);

    if (count > 5) {
      stop_command.x = 0;
      stop_uav_pub.publish(stop_command);
    }
    count++;
    if (count == 20) count = 0;
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
