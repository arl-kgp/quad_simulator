#include "ContactPlugin.hh"

int argc;
char **argv;

using namespace gazebo;
GZ_REGISTER_SENSOR_PLUGIN(ContactPlugin)

/////////////////////////////////////////////////
ContactPlugin::ContactPlugin() : SensorPlugin()
{

    max_update_rate = 2.0;
    updateRate = common::Time(0, common::Time::SecToNano(1));
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
  //if (common::Time::GetWallTime() - prevUpdateTime < updateRate)
  //  return;
  // Get all the contacts.
  msgs::Contacts contacts;

  
    char g0,g1,g2,g3,g4,g5,g6,g7,g8,g9,g10,g11,g12,g13;
    g0 = g1 = g2 = g3 = g4 = g5 = g6 = g7 = g8 = g9 = g10 = g11 = g12 = g13 = '0';

  contacts = this->parentSensor->GetContacts();
  int no_of_collisions = contacts.contact_size();

  if ((common::Time::GetWallTime() - prevUpdateTime < updateRate) && no_of_collisions <= 0)
    return;

  for (unsigned int i = 0; i < no_of_collisions; i++)
  {
    std::vector<std::vector<std::string> > collisions; 
    std::vector<std::string> input_string;
    std::vector<std::string> parts;

    input_string.push_back(contacts.contact(i).collision1());
    input_string.push_back(contacts.contact(i).collision2());
    
    std::string delimiter = "::";

    size_t pos = 0;
    std::string token;

    for (unsigned int j = 0; j<2; j++)
    {
      pos = 0;
      while ((pos = input_string[j].find(delimiter)) != std::string::npos) {
        token = input_string[j].substr(0, pos);
        parts.push_back(token);
        input_string[j].erase(0, pos + delimiter.length());
      }
      parts.push_back(input_string[j]);
      collisions.push_back(parts);
      parts.clear();
    }
    
    
    for (int j = 0;  j<2; j++)
    {
      if(collisions[j][0] == "robot0")
      {
        if(collisions[j][2] == "base_collision") g0 = '1';
        if(collisions[j][2] == "top_collision") g0 = '2';
      }
      else if(collisions[j][0] == "robot1")
      {
        if(collisions[j][2] == "base_collision") g1 = '1';
        if(collisions[j][2] == "top_collision") g1 = '2';
      }
      else if(collisions[j][0] == "robot2")
      {
        if(collisions[j][2] == "base_collision") g2 = '1';
        if(collisions[j][2] == "top_collision") g2 = '2';
      }
      else if(collisions[j][0] == "robot3")
      {
        if(collisions[j][2] == "base_collision") g3 = '1';
        if(collisions[j][2] == "top_collision") g3 = '2';
      }
      else if(collisions[j][0] == "robot4")
      {
        if(collisions[j][2] == "base_collision") g4 = '1';
        if(collisions[j][2] == "top_collision") g4 = '2';
      }
      else if(collisions[j][0] == "robot5")
      {
        if(collisions[j][2] == "base_collision") g5 = '1';
        if(collisions[j][2] == "top_collision") g5 = '2';
      }
      else if(collisions[j][0] == "robot6")
      {
        if(collisions[j][2] == "base_collision") g6 = '1';
        if(collisions[j][2] == "top_collision") g6 = '2';
      } 
      else if(collisions[j][0] == "robot7")
      {
        if(collisions[j][2] == "base_collision") g7 = '1';
        if(collisions[j][2] == "top_collision") g7 = '2';
      }
      else if(collisions[j][0] == "robot8")
      {
        if(collisions[j][2] == "base_collision") g8 = '1';
        if(collisions[j][2] == "top_collision") g8 = '2';
      }
      else if(collisions[j][0] == "robot9")
      {
        if(collisions[j][2] == "base_collision") g9 = '1';
        if(collisions[j][2] == "top_collision") g9 = '2';
      }
      else if(collisions[j][0] == "robot10")
      {
        if(collisions[j][2] == "base_collision") g10 = '1';
        if(collisions[j][2] == "top_collision") g10 = '2';
      }
      else if(collisions[j][0] == "robot11")
      {
        if(collisions[j][2] == "base_collision") g11 = '1';
        if(collisions[j][2] == "top_collision") g11 = '2';
      }
      else if(collisions[j][0] == "robot12")
      {
        if(collisions[j][2] == "base_collision") g12 = '1';
        if(collisions[j][2] == "top_collision") g12 = '2';
      }
      else if(collisions[j][0] == "robot13")
      {
        if(collisions[j][2] == "base_collision") g13 = '1';
        if(collisions[j][2] == "top_collision") g13 = '2';
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
