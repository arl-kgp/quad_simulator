#include "ros/ros.h"
#include <math.h>
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"
#include "nav_msgs/Odometry.h"
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h> 

//Parameters
float v_max = 0.6;
float a_max = 0.8;
float a_max_p = 0.06;
double wait_period = 20;

//Common
bool bool_turn = false;
double angle_diff = 45;
bool calculate_turn = false; 
bool first_run = true; 

//Individual Ground Robots
float vx_0 = v_max;
float az_0 = a_max_p;
char prev_0 = '0';

float vx_1 = v_max;
float az_1 = a_max_p;
char prev_1 = '0';

float vx_2 = v_max;
float az_2 = a_max_p;
char prev_2 = '0';

float vx_3 = v_max;
float az_3 = a_max_p;
char prev_3 = '0';


float vx_4 = v_max;
float az_4 = 0.0;
double time_begin_4 = 0;
double z_target_4 = 0;
char prev_4 = '0';
bool start_turn_4 = false;
bool quad_top_turn_4 = false;
bool is_turning_4 = false;

float vx_5 = v_max;
float az_5 = 0.0;
double time_begin_5 = 0;
double z_target_5 = 0.683;
char prev_5 = '0';
bool start_turn_5 = false;
bool quad_top_turn_5 = false;
bool is_turning_5 = false;

float vx_6 = v_max;
float az_6 = 0.0;
double time_begin_6 = 0;
double z_target_6 = 1.234;
char prev_6 = '0';
bool start_turn_6 = false;
bool quad_top_turn_6 = false;
bool is_turning_6 = false;

float vx_7 = v_max;
float az_7 = 0.0;
double time_begin_7 = 0;
double z_target_7 = 1.907;
char prev_7 = '0';
bool start_turn_7 = false;
bool quad_top_turn_7 = false;
bool is_turning_7 = false;

float vx_8 = v_max;
float az_8 = 0.0;
double time_begin_8 = 0;
double z_target_8 = 2.458;
char prev_8 = '0';
bool start_turn_8 = false;
bool quad_top_turn_8 = false;
bool is_turning_8 = false;

float vx_9 = v_max;
float az_9 = 0.0;
double time_begin_9 = 0;
double z_target_9 = 0;
char prev_9 = '0';
bool start_turn_9 = false;
bool quad_top_turn_9 = false;
bool is_turning_9 = false;

float vx_10 = v_max;
float az_10 = 0.0;
double time_begin_10 = 0;
double z_target_10 = -2.458;
char prev_10 = '0';
bool start_turn_10 = false;
bool quad_top_turn_10 = false;
bool is_turning_10 = false;

float vx_11 = v_max;
float az_11 = 0.0;
double time_begin_11 = 0;
double z_target_11 = -1.907;
char prev_11 = '0';
bool start_turn_11 = false;
bool quad_top_turn_11 = false;
bool is_turning_11 = false;

float vx_12 = v_max;
float az_12 = 0.0;
double time_begin_12 = 0;
double z_target_12 = -1.234;
char prev_12 = '0';
bool start_turn_12 = false;
bool quad_top_turn_12 = false;
bool is_turning_12 = false;

float vx_13 = v_max;
float az_13 = 0.0;
double time_begin_13 = 0;
double z_target_13 = -0.683;
char prev_13 = '0';
bool start_turn_13 = false;
bool quad_top_turn_13 = false;
bool is_turning_13 = false;

class Controller
{
  ros::NodeHandle n;
  ros::Publisher vel_pub_0;
  ros::Publisher vel_pub_1;
  ros::Publisher vel_pub_2;
  ros::Publisher vel_pub_3;
  ros::Publisher vel_pub_4;
  ros::Subscriber odom_sub_4;
  ros::Publisher vel_pub_5;
  ros::Subscriber odom_sub_5;
  ros::Publisher vel_pub_6;
  ros::Subscriber odom_sub_6;
  ros::Publisher vel_pub_7;
  ros::Subscriber odom_sub_7;
  ros::Publisher vel_pub_8;
  ros::Subscriber odom_sub_8;
  ros::Publisher vel_pub_9;
  ros::Subscriber odom_sub_9;
  ros::Publisher vel_pub_10;
  ros::Subscriber odom_sub_10;
  ros::Publisher vel_pub_11;
  ros::Subscriber odom_sub_11;
  ros::Publisher vel_pub_12;
  ros::Subscriber odom_sub_12;
  ros::Publisher vel_pub_13;
  ros::Subscriber odom_sub_13;

  ros::Subscriber contact_sub;
  
public:
  Controller()
  {
    vel_pub_0 = n.advertise<geometry_msgs::Twist>("/robot0/cmd_vel", 1);
    vel_pub_1 = n.advertise<geometry_msgs::Twist>("/robot1/cmd_vel", 1);
    vel_pub_2 = n.advertise<geometry_msgs::Twist>("/robot2/cmd_vel", 1);
    vel_pub_3 = n.advertise<geometry_msgs::Twist>("/robot3/cmd_vel", 1);
    vel_pub_4 = n.advertise<geometry_msgs::Twist>("/robot4/cmd_vel", 1);
    odom_sub_4 = n.subscribe("/robot4/odom", 10, &Controller::odomCb,this);
    vel_pub_5 = n.advertise<geometry_msgs::Twist>("/robot5/cmd_vel", 1);
    odom_sub_5 = n.subscribe("/robot5/odom", 10, &Controller::odomCb,this);
    vel_pub_6 = n.advertise<geometry_msgs::Twist>("/robot6/cmd_vel", 1);
    odom_sub_6 = n.subscribe("/robot6/odom", 10, &Controller::odomCb,this);
    vel_pub_7 = n.advertise<geometry_msgs::Twist>("/robot7/cmd_vel", 1);
    odom_sub_7 = n.subscribe("/robot7/odom", 10, &Controller::odomCb,this);
    vel_pub_8 = n.advertise<geometry_msgs::Twist>("/robot8/cmd_vel", 1);
    odom_sub_8 = n.subscribe("/robot8/odom", 10, &Controller::odomCb,this);
    vel_pub_9 = n.advertise<geometry_msgs::Twist>("/robot9/cmd_vel", 1);
    odom_sub_9 = n.subscribe("/robot9/odom", 10, &Controller::odomCb,this);
    vel_pub_10 = n.advertise<geometry_msgs::Twist>("/robot10/cmd_vel", 1);
    odom_sub_10 = n.subscribe("/robot10/odom", 10, &Controller::odomCb,this);
    vel_pub_11 = n.advertise<geometry_msgs::Twist>("/robot11/cmd_vel", 1);
    odom_sub_11 = n.subscribe("/robot11/odom", 10, &Controller::odomCb,this);
    vel_pub_12 = n.advertise<geometry_msgs::Twist>("/robot12/cmd_vel", 1);
    odom_sub_12 = n.subscribe("/robot12/odom", 10, &Controller::odomCb,this);
    vel_pub_13 = n.advertise<geometry_msgs::Twist>("/robot13/cmd_vel", 1);
    odom_sub_13 = n.subscribe("/robot13/odom", 10, &Controller::odomCb,this);

    contact_sub = n.subscribe("/contact", 1000, &Controller::contactCb,this);    
  }

  ~Controller()
  {
    
  }

  struct Quaternionm
  {
      double w, x, y, z;
  };

  void move_patrolbots(std::string identification)
  {
    geometry_msgs::Twist command;
    if(identification == "all")
    {     
      command.linear.x = v_max;
      command.angular.z = a_max_p;
      command.linear.y = command.linear.z = command.angular.x = command.angular.y = 0;     
      vel_pub_0.publish(command);
      vel_pub_1.publish(command);
      vel_pub_2.publish(command);
      command.linear.x = -v_max;
      vel_pub_3.publish(command);
    }
    else if(identification == "robot0")
    {     
      command.linear.x = vx_0;
      command.angular.z = az_0;
      command.linear.y = command.linear.z = command.angular.x = command.angular.y = 0;     
      vel_pub_0.publish(command);     
    }
    else if(identification == "robot1")
    {     
      command.linear.x = vx_1;
      command.angular.z = az_1;
      command.linear.y = command.linear.z = command.angular.x = command.angular.y = 0;     
      vel_pub_1.publish(command);     
    }
    else if(identification == "robot2")
    {     
      command.linear.x = vx_2;
      command.angular.z = az_2;
      command.linear.y = command.linear.z = command.angular.x = command.angular.y = 0;     
      vel_pub_2.publish(command);     
    }
    else if(identification == "robot3")
    {     
      command.linear.x = -vx_3;
      command.angular.z = az_3;
      command.linear.y = command.linear.z = command.angular.x = command.angular.y = 0;     
      vel_pub_3.publish(command);     
    }
  
  }

  void GetEulerAngles(Quaternionm q, double& yaw, double& pitch, double& roll)
  {
      const double w2 = q.w*q.w;
      const double x2 = q.x*q.x;
      const double y2 = q.y*q.y;
      const double z2 = q.z*q.z;
      const double unitLength = w2 + x2 + y2 + z2;    // Normalised == 1, otherwise correction divisor.
      const double abcd = q.w*q.x + q.y*q.z;
      const double eps = 1e-7;    // TODO: pick from your math lib instead of hardcoding.
      const double pi = 3.14159265358979323846;   // TODO: pick from your math lib instead of hardcoding.
      if (abcd > (0.5-eps)*unitLength)
      {
          yaw = 2 * atan2(q.y, q.w);
          pitch = pi;
          roll = 0;
      }
      else if (abcd < (-0.5+eps)*unitLength)
      {
          yaw = -2 * ::atan2(q.y, q.w);
          pitch = -pi;
          roll = 0;
      }
      else
      {
          const double adbc = q.w*q.z - q.x*q.y;
          const double acbd = q.w*q.y - q.x*q.z;
          yaw = ::atan2(2*adbc, 1 - 2*(z2+x2));
          pitch = ::asin(2*abcd/unitLength);
          roll = ::atan2(2*acbd, 1 - 2*(y2+x2));
      }
  }

  /**
    Outputs angle error.

    IARC documentation specifies that an error of
    upto 20 degrees is added to the groundbot path
    every 5 seconds. We instead of adding error every
    5 seconds are adding 4 such errors every 20 seconds.
  */
  int add_multiple_error(int times)
  {
    int error = 0;
    for (int i = 0; i<times; i++)
    {
      error += rand() % 20 - 9;
    }
    return error;
  }

  
  //Main function to publish velocities
  void publish_velocity(std::string identification)
  {
    if(identification == "robot4/odom")
    {
      geometry_msgs::Twist command;
      command.linear.x = vx_4;
      command.angular.z = az_4;
      command.linear.y = command.linear.z = command.angular.x = command.angular.y = 0;     
      vel_pub_4.publish(command);
    }
    else if(identification == "robot5/odom")
    {
      geometry_msgs::Twist command;
      command.linear.x = vx_5;
      command.angular.z = az_5;
      command.linear.y = command.linear.z = command.angular.x = command.angular.y = 0;     
      vel_pub_5.publish(command);
    } 
    else if(identification == "robot6/odom")
    {
      geometry_msgs::Twist command;
      command.linear.x = vx_6;
      command.angular.z = az_6;
      command.linear.y = command.linear.z = command.angular.x = command.angular.y = 0;     
      vel_pub_6.publish(command);
    }
    else if(identification == "robot7/odom")
    {
      geometry_msgs::Twist command;
      command.linear.x = vx_7;
      command.angular.z = az_7;
      command.linear.y = command.linear.z = command.angular.x = command.angular.y = 0;     
      vel_pub_7.publish(command);
    }
    else if(identification == "robot8/odom")
    {
      geometry_msgs::Twist command;
      command.linear.x = vx_8;
      command.angular.z = az_8;
      command.linear.y = command.linear.z = command.angular.x = command.angular.y = 0;     
      vel_pub_8.publish(command);
    }
    else if(identification == "robot9/odom")
    {
      geometry_msgs::Twist command;
      command.linear.x = -vx_9;
      command.angular.z = az_9;
      command.linear.y = command.linear.z = command.angular.x = command.angular.y = 0;     
      vel_pub_9.publish(command);
    }
    else if(identification == "robot10/odom")
    {
      geometry_msgs::Twist command;
      command.linear.x = vx_10;
      command.angular.z = az_10;
      command.linear.y = command.linear.z = command.angular.x = command.angular.y = 0;     
      vel_pub_10.publish(command);
    }
    else if(identification == "robot11/odom")
    {
      geometry_msgs::Twist command;
      command.linear.x = vx_11;
      command.angular.z = az_11;
      command.linear.y = command.linear.z = command.angular.x = command.angular.y = 0;     
      vel_pub_11.publish(command);
    }
    else if(identification == "robot12/odom")
    {
      geometry_msgs::Twist command;
      command.linear.x = vx_12;
      command.angular.z = az_12;
      command.linear.y = command.linear.z = command.angular.x = command.angular.y = 0;     
      vel_pub_12.publish(command);
    }
    else if(identification == "robot13/odom")
    {
      geometry_msgs::Twist command;
      command.linear.x = vx_13;
      command.angular.z = az_13;
      command.linear.y = command.linear.z = command.angular.x = command.angular.y = 0;     
      vel_pub_13.publish(command);
    }     
    
  }

  // Callback function for odom
  void contactCb(const std_msgs::String::ConstPtr& msg)
  {
    if(first_run)
    {
      move_patrolbots("all");
      first_run = false;
    }
    char str[29];
    std::string data;
    strncpy(str, msg->data.c_str(), sizeof(str));
    //ROS_INFO("%s",msg->data.c_str());
    str[sizeof(str) - 1] = 0;
    char * pch;

    //0th
    pch = strtok (str," ");
    data = pch; 
    //ROS_INFO("data: %s",pch);  
    if(data == "1" && prev_0 == '0')
    { 
      prev_0 = '1';
      vx_0 = 0;
      az_0 = 0;
      //ROS_INFO("Stopping bot0");
      move_patrolbots("robot0"); 
    }
    else if(data == "0" && prev_0 == '1')
    {
      prev_0 = '0'; 
      vx_0 = v_max;
      az_0 = a_max_p;
      //ROS_INFO("Moving bot0");
      move_patrolbots("robot0");      
    }

    //1st
    pch = strtok (NULL," ");
    data = pch;    
    if(data == "1" && prev_1 == '0')
    { 
      prev_1 = '1';
      vx_1 = 0;
      az_1 = 0;
      move_patrolbots("robot1"); 
    }
    else if(data == "0" && prev_1 == '1')
    {
      prev_1 = '0'; 
      vx_1 = v_max;
      az_1 = a_max_p;
      move_patrolbots("robot1");      
    }

    //2nd
    pch = strtok (NULL," ");
    data = pch;    
    if(data == "1" && prev_2 == '0')
    { 
      prev_2 = '1';
      vx_2 = 0;
      az_2 = 0;
      move_patrolbots("robot2"); 
    }
    else if(data == "0" && prev_2 == '1')
    {
      prev_2 = '0'; 
      vx_2 = v_max;
      az_2 = a_max_p;
      move_patrolbots("robot2");      
    }

    //3rd
    pch = strtok (NULL," ");
    data = pch;    
    if(data == "1" && prev_3 == '0')
    { 
      prev_3 = '1';
      vx_3 = 0;
      az_3 = 0;
      move_patrolbots("robot3"); 
    }
    else if(data == "0" && prev_3 == '1')
    {
      prev_3 = '0'; 
      vx_3 = v_max;
      az_3 = a_max_p;
      move_patrolbots("robot3");      
    }
    
    //4th
    pch = strtok (NULL, " ");
    data = pch;    
    if(data == "1" && prev_4 != '1')
    {     
      start_turn_4 = true;
      prev_4 = '1'; 
    }
    else if(data == "2" && prev_4 != '2')
    {     
      quad_top_turn_4 = true;
      prev_4 = '2'; 
    }
    else if(data == "0" && prev_4 != '0')prev_4 = '0'; 

    //5th
    pch = strtok (NULL, " ");
    data = pch;    
    if(data == "1" && prev_5 != '1')
    {
      start_turn_5 = true;
      prev_5 = '1';     
    }
    else if(data == "2" && prev_5 != '2')
    {     
      quad_top_turn_5 = true;
      prev_5 = '2'; 
    }
    else if(data == "0" && prev_5 != '0')prev_5 = '0';

    //6th
    pch = strtok (NULL, " ");
    data = pch;    
    if(data == "1" && prev_6 != '1')
    {
      start_turn_6 = true;
      prev_6 = '1';     
    }
    else if(data == "2" && prev_6 != '2')
    {     
      quad_top_turn_6 = true;
      prev_6 = '2'; 
    }
    else if(data == "0" && prev_6 != '0')prev_6 = '0';

    //7th
    pch = strtok (NULL, " ");
    data = pch;    
    if(data == "1" && prev_7 != '1')
    {
      start_turn_7 = true;
      prev_7 = '1';     
    }
    else if(data == "2" && prev_7 != '2')
    {     
      quad_top_turn_7 = true;
      prev_7 = '2'; 
    }
    else if(data == "0" && prev_7 != '0')prev_7 = '0';

    //8th
    pch = strtok (NULL, " ");
    data = pch;    
    if(data == "1" && prev_8 != '1')
    {
      start_turn_8 = true;
      prev_8 = '1';     
    }
    else if(data == "2" && prev_8 != '2')
    {     
      quad_top_turn_8 = true;
      prev_8 = '2'; 
    }
    else if(data == "0" && prev_8 != '0')prev_8 = '0';

    //9th
    pch = strtok (NULL, " ");
    data = pch;    
    if(data == "1" && prev_9 != '1')
    {
      start_turn_9 = true;
      prev_9 = '1';     
    }
    else if(data == "2" && prev_9 != '2')
    {     
      quad_top_turn_9 = true;
      prev_9 = '2'; 
    }
    else if(data == "0" && prev_9 != '0')prev_9 = '0';

    //10th
    pch = strtok (NULL, " ");
    data = pch;    
    if(data == "1" && prev_10 != '1')
    {
      start_turn_10 = true;
      prev_10 = '1';      
    }
    else if(data == "2" && prev_10 != '2')
    {     
      quad_top_turn_10 = true;
      prev_10 = '2'; 
    }
    else if(data == "0" && prev_10 != '0')prev_10 = '0';

    //11th
    pch = strtok (NULL, " ");
    data = pch;    
    if(data == "1" && prev_11 != '1')
    {
      start_turn_11 = true;
      prev_11 = '1';      
    }
    else if(data == "2" && prev_11 != '2')
    {     
      quad_top_turn_11 = true;
      prev_11 = '2'; 
    }
    else if(data == "0" && prev_11 != '0')prev_11 = '0';

    //12th
    pch = strtok (NULL, " ");
    data = pch;    
    if(data == "1" && prev_12 != '1')
    {
      start_turn_12 = true;
      prev_12 = '1';      
    }
    else if(data == "2" && prev_12 != '2')
    {     
      quad_top_turn_12 = true;
      prev_12 = '2'; 
    }
    else if(data == "0" && prev_12 != '0')prev_12 = '0';

    //13th
    pch = strtok (NULL, " ");
    data = pch;    
    if(data == "1" && prev_13 != '1')
    {
      start_turn_13 = true;
      prev_13 = '1';      
    }
    else if(data == "2" && prev_13 != '2')
    {     
      quad_top_turn_13 = true;
      prev_13 = '2'; 
    }
    else if(data == "0" && prev_13 != '0')prev_13 = '0';
  }
  
  

  void odomCb(const nav_msgs::Odometry::ConstPtr& msg)
  {
    float *vx;
    double *z_target; 
    float *az;
    double *time_begin;
    bool *start_turn;
    bool *quad_top_turn;
    bool *is_turning;

    Quaternionm myq;
    double yaw = 0;
    double pitch = 0;
    double roll = 0;
    myq.x = msg->pose.pose.orientation.x;
    myq.y = msg->pose.pose.orientation.y;
    myq.z = msg->pose.pose.orientation.z;
    myq.w = msg->pose.pose.orientation.w;  
    GetEulerAngles(myq, yaw, pitch, roll);
      

    if(msg->header.frame_id == "robot4/odom")
    {
      vx = &vx_4;
      z_target = &z_target_4;
      az = &az_4;
      time_begin = &time_begin_4;
      start_turn = &start_turn_4;
      quad_top_turn = &quad_top_turn_4;
      is_turning = &is_turning_4;
    }
    else if(msg->header.frame_id == "robot5/odom")
    {
      vx = &vx_5;
      z_target = &z_target_5;
      az = &az_5;
      time_begin = &time_begin_5;
      start_turn = &start_turn_5;
      quad_top_turn = &quad_top_turn_5;
      is_turning = &is_turning_5;
    }
    else if(msg->header.frame_id == "robot6/odom")
    {
      vx = &vx_6;
      z_target = &z_target_6;
      az = &az_6;
      time_begin = &time_begin_6;
      start_turn = &start_turn_6;
      quad_top_turn = &quad_top_turn_6;
      is_turning = &is_turning_6;
    }
    else if(msg->header.frame_id == "robot7/odom")
    {
      vx = &vx_7;
      z_target = &z_target_7;
      az = &az_7;
      time_begin = &time_begin_7;
      start_turn = &start_turn_7;
      quad_top_turn = &quad_top_turn_7;
      is_turning = &is_turning_7;
    }
    else if(msg->header.frame_id == "robot8/odom")
    {
      vx = &vx_8;
      z_target = &z_target_8;
      az = &az_8;
      time_begin = &time_begin_8;
      start_turn = &start_turn_8;
      quad_top_turn = &quad_top_turn_8;
      is_turning = &is_turning_8;
    }
    else if(msg->header.frame_id == "robot9/odom")
    {
      vx = &vx_9;
      z_target = &z_target_9;
      az = &az_9;
      time_begin = &time_begin_9;
      start_turn = &start_turn_9;
      quad_top_turn = &quad_top_turn_9;
      is_turning = &is_turning_9;
    }
    else if(msg->header.frame_id == "robot10/odom")
    {
      vx = &vx_10;
      z_target = &z_target_10;
      az = &az_10;
      time_begin = &time_begin_10;
      start_turn = &start_turn_10;
      quad_top_turn = &quad_top_turn_10;
      is_turning = &is_turning_10;
    }
    else if(msg->header.frame_id == "robot11/odom")
    {
      vx = &vx_11;
      z_target = &z_target_11;
      az = &az_11;
      time_begin = &time_begin_11;
      start_turn = &start_turn_11;
      quad_top_turn = &quad_top_turn_11;
      is_turning = &is_turning_11;
    }
    else if(msg->header.frame_id == "robot12/odom")
    {
      vx = &vx_12;
      z_target = &z_target_12;
      az = &az_12;
      time_begin = &time_begin_12;
      start_turn = &start_turn_12;
      quad_top_turn = &quad_top_turn_12;
      is_turning = &is_turning_12;
    }
    else if(msg->header.frame_id == "robot13/odom")
    {
      vx = &vx_13;
      z_target = &z_target_13;
      az = &az_13;
      time_begin = &time_begin_13;
      start_turn = &start_turn_13;
      quad_top_turn = &quad_top_turn_13;
      is_turning = &is_turning_13;
    }

    std::string Caller = "";
      
          
    double diff = *z_target - yaw;
    diff = fabs(diff);
    double time_present = ros::Time::now().toSec();
    //ROS_INFO("time_present: %lf, time_begin: %lf, roll: %lf",time_present,time_begin,diff);
    if(diff > 0.13490 && *is_turning == true)
    {
      *time_begin = time_present;
      *vx = 0;
      *az = a_max;    
    }
    else if(diff < 0.13490 && *is_turning == true)
    {
      *is_turning = false;
      *vx = v_max;
      *az = 0;
    }

    if(!*is_turning)
    {
      *vx = v_max;
      *az = 0;
    }

    if((time_present - *time_begin) > wait_period)
    {
      angle_diff = 45 + add_multiple_error(4);    
      calculate_turn = true;
      Caller = "time"; 
    }

    if(*start_turn == true)
    {
      angle_diff = 180 + add_multiple_error(4);
      calculate_turn = true;
      *start_turn = false;
      Caller = "base";
    }

    if(*quad_top_turn == true)
    {
      angle_diff = 45 + add_multiple_error(4);
      calculate_turn = true;
      *quad_top_turn = false;
      Caller = "top";
    }


    if(calculate_turn)
    {
      *is_turning = true;    
      
      double turn_angle = (angle_diff*3.141592)/180;
      *z_target = yaw - turn_angle;
      if(*z_target > 3.14)
      {
        *z_target = 2*3.14 - *z_target;
      }
      else if(*z_target < -3.14)
      {
        *z_target = 2*3.14 + *z_target;
      }
      //ROS_INFO("target: %lf",z_target);
      *time_begin = time_present;           
      calculate_turn = false;
      *vx = -v_max*5;
    }
    publish_velocity(msg->header.frame_id);
  }
  
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "CreateController");
  Controller ic;
  time_begin_4 = time_begin_5 = time_begin_6 = time_begin_7 = time_begin_8 = time_begin_9 = time_begin_10 = time_begin_11 = time_begin_12 = time_begin_13 = ros::Time::now().toSec();
  srand (time(NULL));
  ros::spin();
  return 0;
}