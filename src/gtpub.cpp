#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "tum_ardrone/filter_state.h"

ros::Publisher chatter_pub;

void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  tum_ardrone::filter_state outputmsg;
  outputmsg.header = msg->header;
  outputmsg.x = -msg->pose.pose.position.y;
  outputmsg.y = msg->pose.pose.position.x;
  outputmsg.z = msg->pose.pose.position.z;
  outputmsg.dx = -msg->twist.twist.linear.y;
  outputmsg.dy = msg->twist.twist.linear.x;
  outputmsg.dz = msg->twist.twist.linear.z;
  outputmsg.roll = 0.0;
  outputmsg.pitch = 0.0;
  outputmsg.yaw = 0.0;
  outputmsg.dyaw = 0.0;
  outputmsg.scale = 1.0;
  outputmsg.ptamState = outputmsg.PTAM_GOOD;
  outputmsg.scaleAccuracy = 1.0;
  outputmsg.droneState = 3;
  outputmsg.batteryPercent = 100;
  chatter_pub.publish(outputmsg);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "gtpub");
  ros::NodeHandle n;
  chatter_pub = n.advertise<tum_ardrone::filter_state>("/ardrone/predictedPose", 1);
  ros::Subscriber sub = n.subscribe("/ground_truth/state", 1, chatterCallback);
  ros::spin();

  return 0;
}