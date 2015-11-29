#include "ContactPlugin.hh"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensors/sensors.hh>
#include <string.h>
#include <stdio.h>
 
#include <sstream>
 
char word_sep = ' ';
 
using namespace gazebo;
GZ_REGISTER_SENSOR_PLUGIN(ContactPlugin)
 
/////////////////////////////////////////////////
ContactPlugin::ContactPlugin() : SensorPlugin()
{
}
 
/////////////////////////////////////////////////
ContactPlugin::~ContactPlugin()
{
}
 
ros::Publisher chatter_pub;
int argc;
char **argv;
 
/////////////////////////////////////////////////
void ContactPlugin::Load(sensors::SensorPtr _sensor, sdf::ElementPtr /*_sdf*/)
{
  // Get the parent sensor.
  this->parentSensor =
    boost::dynamic_pointer_cast<sensors::ContactSensor>(_sensor);
 
  // Make sure the parent sensor is valid.
  if (!this->parentSensor)
  {
    gzerr << "ContactPlugin requires a ContactSensor.n";
    return;
  }
 
  // Connect to the sensor update event.
  this->updateConnection = this->parentSensor->ConnectUpdated(
      boost::bind(&ContactPlugin::OnUpdate, this));
 
  // Make sure the parent sensor is active.
  this->parentSensor->SetActive(true);
 
 
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  chatter_pub = n.advertise<std_msgs::String>("contact", 1000);
 
 
}
 
/////////////////////////////////////////////////
void ContactPlugin::OnUpdate()
{
  // Get all the contacts.
  msgs::Contacts contacts;
 
   
    int g0,g1,g2,g3,g4,g5,g6,g7,g8,g9,g10,g11,g12,g13;
    g0 = g1 = g2 = g3 = g4 = g5 = g6 = g7 = g8 = g9 = g10 = g11 = g12 = g13 = '0';
 
  contacts = this->parentSensor->GetContacts();
  for (unsigned int i = 0; i < contacts.contact_size(); ++i)
  {
    //std_msgs::String msg1;
 
    std::stringstream ss2;
    ss2 << "Collision between[" << contacts.contact(i).collision1()
              << "] and [" << contacts.contact(i).collision2() << "]n";
 
    //std::String display = ss2.str();
    //ROS_INFO("%s",ss2.str().c_str());
 
    /*std::string tmp = contacts.contact(i).collision1();
    char str[32];
    strncpy(str, tmp.c_str(), sizeof(str));
    str[sizeof(str) - 1] = 0;
    char * pch;
    pch = strtok (str,":");
    //printf ("%sn",pch);
    //ROS_INFO("%s",pch);
    std::string object1 = pch;
 
    tmp = contacts.contact(i).collision2();
    char str1[32];
    strncpy(str1, tmp.c_str(), sizeof(str));
    str[sizeof(str) - 1] = 0;
    char * pch1;
    pch1 = strtok (str1,":");
    std::string object2 = pch1;*/
    //std::string object1,object2,sensor1,sensor2;

    std::vector<std::string> objects;
    std::vector<std::string> sensors;
 
    std::string str_1 = contacts.contact(i).collision1();
    std::stringstream ss_1(str_1);
    std::vector<std::string> parts;
    std::string token;
 
    while (getline(ss_1,token, ':'))
    {
        parts.push_back(token);
        //ROS_INFO("%s",token.c_str());
    }
    objects[0] = parts[0];
    sensors[0] = parts[2];
    parts.clear();
 
    str_1 = contacts.contact(i).collision2();
    std::stringstream ss_2(str_1);
 
    while (getline(ss_1,token, ':'))
    {
        parts.push_back(token);
        //ROS_INFO("%s",token.c_str());
    }
    objects[1] = parts[0];
    sensors[1] = parts[2];

    for (int i = 0; i<2; i++)
    {
      if(objects[i] == "robot0")
      {
        if(sensors[i] == "base")g0 += 1;
        if(sensors[i] == "top_sensor")g0 += 2;
      }
      if(objects[i] == "robot1")
      {
        if(sensors[i] == "base")g1 += 1;
        if(sensors[i] == "top_sensor")g1 += 2;
      }
      if(objects[i] == "robot2")
      {
        if(sensors[i] == "base")g2 += 1;
        if(sensors[i] == "top_sensor")g2 += 2;
      }
      if(objects[i] == "robot3")
      {
        if(sensors[i] == "base")g3 += 1;
        if(sensors[i] == "top_sensor")g3 += 2;
      }
   
      if(objects[i] == "robot4")
      {
        if(sensors[i] == "base")g4 += 1;
        if(sensors[i] == "top_sensor")g4 += 2;
      }
   
      if(objects[i] == "robot5")
      {
        if(sensors[i] == "base")g5 += 1;
        if(sensors[i] == "top_sensor")g5 += 2;
      }
      if(objects[i] == "robot6")
      {
        if(sensors[i] == "base")g6 += 1;
        if(sensors[i] == "top_sensor")g6 += 2;
      }
      if(objects[i] == "robot7")
      {
        if(sensors[i] == "base")g7 += 1;
        if(sensors[i] == "top_sensor")g7 += 2;
      }
      if(objects[i] == "robot8")
      {
        if(sensors[i] == "base")g8 += 1;
        if(sensors[i] == "top_sensor")g8 += 2;
      }
      if(objects[i] == "robot9")
      {
        if(sensors[i] == "base")g9 += 1;
        if(sensors[i] == "top_sensor")g9 += 2;
      }
      if(objects[i] == "robot10")
      {
        if(sensors[i] == "base")g10 += 1;
        if(sensors[i] == "top_sensor")g10 += 2;
      }
      if(objects[i] == "robot11")
      {
        if(sensors[i] == "base")g11 += 1;
        if(sensors[i] == "top_sensor")g11 += 2;
      }
      if(objects[i] == "robot12")
      {
        if(sensors[i] == "base")g12 += 1;
        if(sensors[i] == "top_sensor")g12 += 2;
      }
      if(objects[i] == "robot13")
      {
        if(sensors[i] == "base")g13 += 1;
        if(sensors[i] == "top_sensor")g13 += 2;
      }
      ROS_INFO("%d",g0);

    }
 
 
 
 
 
 
    /*for (unsigned int j = 0; j < contacts.contact(i).position_size(); ++j)
    {
      std::cout << j << "  Position:"
                << contacts.contact(i).position(j).x() << " "
                << contacts.contact(i).position(j).y() << " "
                << contacts.contact(i).position(j).z() << "n";
      std::cout << "   Normal:"
                << contacts.contact(i).normal(j).x() << " "
                << contacts.contact(i).normal(j).y() << " "
                << contacts.contact(i).normal(j).z() << "n";
      std::cout << "   Depth:" << contacts.contact(i).depth(j) << "n";
    }*/
  }
 
 
   
    std_msgs::String msg;
    std::stringstream ss;
    //char g0_c = g0;
    //ss<<"hi"<<g0_c;
    //ROS_INFO("%d",g0);
    ss << g0  << word_sep << g1  << word_sep << g2  << word_sep << g3  << word_sep << g4  << word_sep << g5  << word_sep << g6  << word_sep << g7  << word_sep << g8  << word_sep << g9  << word_sep << g10  << word_sep << g11  << word_sep << g12  << word_sep << g13 ;
    msg.data = ss.str();
 
    //ROS_INFO("%s",msg.data.str());
 
    
    chatter_pub.publish(msg);
    ros::spinOnce();
}