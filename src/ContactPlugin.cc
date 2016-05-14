#include "ContactPlugin.hh"

int argc;
char **argv;

using namespace gazebo;
GZ_REGISTER_SENSOR_PLUGIN(ContactPlugin)

/////////////////////////////////////////////////
ContactPlugin::ContactPlugin() : SensorPlugin()
{

    max_update_rate = 2.0;
    updateRate = common::Time(0, common::Time::SecToNano((1.0/max_update_rate)));
    prevUpdateTime = common::Time::GetWallTime();
    
    word_sep = ' ';
}

/////////////////////////////////////////////////
ContactPlugin::~ContactPlugin()
{
}

/////////////////////////////////////////////////
void ContactPlugin::Load(sensors::SensorPtr _sensor, sdf::ElementPtr /*_sdf*/)
{
  // Get the parent sensor.
  this->parentSensor =
    boost::dynamic_pointer_cast<sensors::ContactSensor>(_sensor);

  // Make sure the parent sensor is valid.
  if (!this->parentSensor)
  {
    gzerr << "ContactPlugin requires a ContactSensor.\n";
    return;
  }

  // Connect to the sensor update event.
  this->updateConnection = this->parentSensor->ConnectUpdated(
      boost::bind(&ContactPlugin::OnUpdate, this));

  // Make sure the parent sensor is active.
  this->parentSensor->SetActive(true);


  ros::init(argc, argv, "contact_sensor");
  ros::NodeHandle n;
  contactSensor_pub = n.advertise<std_msgs::String>("contact", 1000);


}

/////////////////////////////////////////////////
void ContactPlugin::OnUpdate()
{
  if (common::Time::GetWallTime() - prevUpdateTime < updateRate)
    return;
  // Get all the contacts.
  msgs::Contacts contacts;

  
    char g0,g1,g2,g3,g4,g5,g6,g7,g8,g9,g10,g11,g12,g13;
    g0 = g1 = g2 = g3 = g4 = g5 = g6 = g7 = g8 = g9 = g10 = g11 = g12 = g13 = '0';

  contacts = this->parentSensor->GetContacts();
  int no_of_collisions = contacts.contact_size();
  if ((common::Time::GetWallTime() - prevUpdateTime < updateRate) && no_of_collisions <= 0)
    return;
  for (unsigned int i = 0; i < no_of_collisions; ++i)
  {
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
    //ROS_INFO("%s , %s",parts[0].c_str(), parts[2].c_str());
    objects.push_back(parts[0]);
    sensors.push_back(parts[2]);
    parts.clear();
  
    str_1 = contacts.contact(i).collision2();
    std::stringstream ss_2(str_1);
 
    while (getline(ss_1,token, ':'))
    {
        parts.push_back(token);
        //ROS_INFO("%s",token.c_str());
    }
    objects.push_back(parts[0]);
    sensors.push_back(parts[2]);

    

    for (int i = 0; i<2; i++)
    {
      if(objects[i] == "robot0" && g0 < 3)
      {
        if(sensors[i] == "base") g0 = '1';
        if(sensors[i] == "top_sensor") g0 = '2';
      }
      if(objects[i] == "robot1" && g1 < 3)
      {
        if(sensors[i] == "base") g1 = '1';
        if(sensors[i] == "top_sensor") g1 = '2';
      }
      if(objects[i] == "robot2" && g2 < 3)
      {
        if(sensors[i] == "base") g2 = '1';
        if(sensors[i] == "top_sensor") g2 = '2';
      }
      if(objects[i] == "robot3" && g3 < 3)
      {
        if(sensors[i] == "base") g3 = '1';
        if(sensors[i] == "top_sensor") g3 = '2';
      }
   
      if(objects[i] == "robot4" && g4 < 3)
      {
        if(sensors[i] == "base") g4 = '1';
        if(sensors[i] == "top_sensor") g4 = '2';
      }
   
      if(objects[i] == "robot5" && g5 < 3)
      {
        if(sensors[i] == "base") g5 = '1';
        if(sensors[i] == "top_sensor") g5 = '2';
      }
      if(objects[i] == "robot6" && g6 < 3)
      {
        if(sensors[i] == "base") g6 = '1';
        if(sensors[i] == "top_sensor") g6 = '2';
      }
      if(objects[i] == "robot7" && g7 < 3)
      {
        if(sensors[i] == "base") g7 = '1';
        if(sensors[i] == "top_sensor") g7 = '2';
      }
      if(objects[i] == "robot8" && g8 < 3)
      {
        if(sensors[i] == "base") g8 = '1';
        if(sensors[i] == "top_sensor") g8 = '2';
      }
      if(objects[i] == "robot9" && g9 < 3)
      {
        if(sensors[i] == "base") g9 = '1';
        if(sensors[i] == "top_sensor") g9 = '2';
      }
      if(objects[i] == "robot10" && g10 < 3)
      {
        if(sensors[i] == "base") g10 = '1';
        if(sensors[i] == "top_sensor") g10 = '2';
      }
      if(objects[i] == "robot11" && g11 < 3)
      {
        if(sensors[i] == "base") g11 = '1';
        if(sensors[i] == "top_sensor") g11 = '2';
      }
      if(objects[i] == "robot12" && g12 < 3)
      {
        if(sensors[i] == "base") g12 = '1';
        if(sensors[i] == "top_sensor") g12 = '2';
      }
      if(objects[i] == "robot13" && g13< 3)
      {
        if(sensors[i] == "base") g13 = '1';
        if(sensors[i] == "top_sensor") g13 = '2';
      }
      

    }
  }
 
  
   
    std_msgs::String msg;
    std::stringstream ss;
    ss << g0 << word_sep << g1 << word_sep << g2 << word_sep << g3 << word_sep << g4 << word_sep << g5 << word_sep << g6 << word_sep << g7 << word_sep << g8 << word_sep << g9 << word_sep << g10 << word_sep << g11 << word_sep << g12 << word_sep << g13;
    msg.data = ss.str();
 
    //ROS_INFO("%s",msg.data.str());

    prevUpdateTime = common::Time::GetWallTime();
    contactSensor_pub.publish(msg);
    ros::spinOnce();
}
