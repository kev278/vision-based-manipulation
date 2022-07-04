#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>

static int iter = 0;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
  	if (iter == 0)
  	{
		cv::imwrite("/home/keval/catkin_ws/src/image_converter/data/ref_image.png", cv_bridge::toCvShare(msg, "bgr8")->image);
    	//cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
    	//cv::waitKey(30);
    	iter++;
    	std::cout << "in " << std::endl;
    }
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{
  int i;
   i = 5;
    int sum = i+i;
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;
  cv::namedWindow("view");
  cv::namedWindow("view1");

  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("vbmbot/camera1/image_raw", 1, imageCallback);
 
  
   
 
  
  
  ros::spin();
  cv::destroyWindow("view");
  cv::destroyWindow("view1");
 
 
  
}

 
 
//image_sub_ = it_.subscribe("/vbmbot/camera1/image_raw", 1,
//      &ImageConverter::imageCb, this);
      
      
 
