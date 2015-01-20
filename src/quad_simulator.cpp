#include "ros/ros.h"
#include "std_msgs/Empty.h"
#include "geometry_msgs/Twist.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include "ardrone_autonomy/Navdata.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

ardrone_autonomy::Navdata msg_in;
geometry_msgs::Twist input;
image_transport::Publisher image_pub;

using namespace cv;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  // sensor_msgs::CvBridge bridge;
  // namedWindow( "view", cv::WINDOW_AUTOSIZE );
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        if(msg_in.tags_count > 0){
            long int tagy = ((((long int)msg_in.tags_yc[0]) * 640)/1000 );
            long int tagx = ((((long int)msg_in.tags_xc[0]) * 480)/1000 );
            ROS_INFO(" [%u] [%u] ", tagx, tagx);
            cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
            circle(cv_ptr->image, Point(tagx,tagy),25, Scalar(129,221,150), -1 , 8,0);
            
            // sensor_msgs::ImagePtr new_img = cv_bridge::CvImage(std_msgs::Header(), "bgr8", cv_ptr->image).toImageMsg();
            // image_pub.publish(new_img); 
        }       
        else{
            cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
            // sensor_msgs::ImagePtr new_img = cv_bridge::CvImage(std_msgs::Header(), "bgr8", cv_ptr->image).toImageMsg();
            // image_pub.publish(new_img);  
        }
   }
   catch (cv_bridge::Exception& e)
   {
     ROS_ERROR("cv_bridge exception: %s", e.what());
     return;
   }
     cv::imshow("view", cv_ptr->image);
}

void vision_dataCB(const geometry_msgs::Twist::ConstPtr& msg)
{
    // input = *msg;

    ROS_INFO("[%f], [%f], [%f], [%f], [%f], [%f]",msg->linear.x,msg->linear.y,msg->linear.z,msg->angular.x,msg->angular.y,msg->angular.z);
}
void tagCB(const ardrone_autonomy::Navdata& msg)
{
    msg_in = msg;
    if(msg.tags_count > 0)
    {
        // ROS_INFO("[%u], [%u]",msg.tags_xc[0],msg.tags_yc[0]);
        long int tagy = -1 * ((((long int)msg.tags_xc[0]) * 640)/1000 - 320);
        long int tagx = -1 * ((((long int)msg.tags_yc[0]) * 480)/1000 - 240);
        double tagy_f = ((double) tagy/320.0) * 0.5;
        double tagx_f = ((double) tagx/240.0) * 0.5;
        ROS_INFO("[%lf], [%lf]",tagx_f,tagy_f);
        input.linear.x = tagx_f;
        input.linear.y = tagy_f;
    }
    else
        ROS_INFO("No tags");
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "flight");
    ros::NodeHandle node;
    ros::Rate loop_rate(30);

    ros::Publisher take_off;
    ros::Publisher twist;
    ros::Publisher land;
    ros::Publisher emergency;

    ros::Subscriber vision_data;
    ros::Subscriber navdata;

    std_msgs::Empty msg;

    geometry_msgs::Twist hover;
    geometry_msgs::Twist move;

    input.linear.x = 0.0;
    input.linear.y = 0.0;
    input.linear.z = 10.0;
    input.angular.x = 0.0;
    input.angular.y = 0.0;
    input.angular.z = 0.0;

    hover.linear.x = 0.0;
    hover.linear.y = 0.0;
    hover.linear.z = 0.0;
    hover.angular.x = 0.0;
    hover.angular.y = 0.0;
    hover.angular.z = 0.0;

    // cv::namedWindow("view");
    // cv::startWindowThread();
    ROS_INFO("Drone Flight | Test 1.0");

    twist = node.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    take_off = node.advertise<std_msgs::Empty>("/ardrone/takeoff", 1);
    land = node.advertise<std_msgs::Empty>("/ardrone/land", 1);
    // vision_data = node.subscribe("/ardrone/vision_data",10, vision_dataCB);
    // navdata = node.subscribe("/tagdata", 10, tagCB);
    // image_transport::ImageTransport it_sub(node);
    // image_transport::Subscriber image_sub = it_sub.subscribe("/camera/image", 10, imageCallback);
    // image_transport::ImageTransport it_pub(node);
    // image_pub = it_pub.advertise("/new_image", 10);

    int cnt = 0;
    ROS_INFO("Flight Starting");
    // double time_count = (double)ros::Time::now().toSec();
    while( ros::ok()) {
        if(cnt < 5){
            cnt+=1;
            take_off.publish(msg);
            twist.publish(hover);
            ros::spinOnce();
        }

        else if(cnt < 15){
            cnt+=1;
            // take_off.publish(msg);
            twist.publish(input);
            ros::spinOnce();
        }
        else{
            twist.publish(hover);
            ros::spinOnce();
        }
        loop_rate.sleep();
    }
    // cv::destroyWindow("view");

}
    //ROS_INFO(time_count);
/*
    while (ros::ok())
    {
        if((double)ros::Time::now().toSec() < time_count + 4)
        {
            ROS_INFO("Taking Off");
        }

        while (((double)ros::Time::now().toSec() < time_count + 3.0) && ros::ok())
        {
            take_off.publish(msg);
            twist.publish(hover);
            ros::spinOnce();
            ROS_INFO("Taking OFF");
            loop_rate.sleep();
        }

        ROS_INFO("Hovering and Moving");
        twist.publish(hover);

        ros::spinOnce();
        loop_rate.sleep();

        while (((double)ros::Time::now().toSec() < time_count + 20.0) && ros::ok())
        {
            twist.publish(hover);
            // land.publish(msg);
            ros::spinOnce();
            ROS_INFO("Moving");
            loop_rate.sleep();
        }
        
        // ROS_INFO("Landing");
        while (((double)ros::Time::now().toSec() > time_count + 20.0) && ros::ok())
        {
            twist.publish(hover);
            land.publish(msg);
            ros::spinOnce();
            loop_rate.sleep();
        }
        
        if (((double)ros::Time::now().toSec() > time_count + 20.0)  && ros::ok())
        {
            ROS_INFO("Closing Flight");
            exit(0);
            ros::spinOnce();
            loop_rate.sleep();
        }
    }
}
*/