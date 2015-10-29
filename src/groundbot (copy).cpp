#include "ros/ros.h"
#include <math.h>
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"


/**
 * This tutorial demonstrates simple sending of velocity commands to the IRobot Create in Gazebo.
 */

float vx = 0.0;
float vy = 0.4;
float vz = 0;
float ax = 0;
float ay = 0;
float az = 0;


int main(int argc, char **argv)
{

  ros::init(argc, argv, "CreateController");

  ros::NodeHandle n;

  ros::Publisher vel_pub_0 = n.advertise<geometry_msgs::Twist>("/robot4/cmd_vel", 1);
  // ros::Publisher vel_pub_1 = n.advertise<geometry_msgs::Twist>("/robot0/cmd_vel", 1);
  ros::Rate loop_rate(5);

  int count = 0;

  double begin =ros::Time::now().toSec();

  while (ros::ok())
  {
    double present =ros::Time::now().toSec();

    
    



    // Publish Velocity
    geometry_msgs::Twist cmd_vel;
    cmd_vel.linear.x = vx;
    cmd_vel.linear.y = vy;
    cmd_vel.linear.z = vz;
    cmd_vel.angular.x = ax;
    cmd_vel.angular.y = ay;
    cmd_vel.angular.z = az;
    vel_pub_0.publish(cmd_vel);    
    ros::spinOnce();
    loop_rate.sleep();

    ++count;
  }
  return 0;
}
