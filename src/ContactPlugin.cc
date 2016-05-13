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
    //std_msgs::String msg1;

    std::stringstream ss2;
    ss2 << "Collision between[" << contacts.contact(i).collision1()
              << "] and [" << contacts.contact(i).collision2() << "]\n";

    //std::display = ss2.str();
    //ROS_INFO("%s",display);

    std::string tmp = contacts.contact(i).collision1();
    char str[32];
    strncpy(str, tmp.c_str(), sizeof(str));
    str[sizeof(str) - 1] = 0;
    char * pch;
    pch = strtok (str,":");
    //printf ("%s\n",pch);
    //ROS_INFO("%s",pch);
    std::string object1 = pch;

    tmp = contacts.contact(i).collision2();
    char str1[32];
    strncpy(str1, tmp.c_str(), sizeof(str));
    str[sizeof(str) - 1] = 0;
    char * pch1;
    pch1 = strtok (str1,":");
    std::string object2 = pch1;

    //ROS_INFO("%s",pch);

    //Collision detection
    if(object1 == "robot0" || object2 == "robot0")
    {
      g0 = '1';
    }
    if(object1 == "robot1" || object2 == "robot1")
    {
      g1 = '1';
    }
    if(object1 == "robot2" || object2 == "robot2")
    {
      g2 = '1';
    }
    if(object1 == "robot3" || object2 == "robot3")
    {
      g3 = '1';
    }

    if(object1 == "robot4" || object2 == "robot4")
    {
      g4 = '1';
    }

    if(object1 == "robot5" || object2 == "robot5")
    {
      g5 = '1';
    }
    if(object1 == "robot6" || object2 == "robot6")
    {
      g6 = '1';
    }
    if(object1 == "robot7" || object2 == "robot7")
    {
      g7 = '1';
    }
    if(object1 == "robot8" || object2 == "robot8")
    {
      g8 = '1';
    }
    if(object1 == "robot9" || object2 == "robot9")
    {
      g9 = '1';
    }
    if(object1 == "robot10" || object2 == "robot10")
    {
      g10 = '1';
    }
    if(object1 == "robot11" || object2 == "robot11")
    {
      g11 = '1';
    }
    if(object1 == "robot12" || object2 == "robot12")
    {
      g12 = '1';
    }
    if(object1 == "robot13" || object2 == "robot13")
    {
      g13 = '1';
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
