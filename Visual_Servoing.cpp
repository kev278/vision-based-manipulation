#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/QR>
#include "std_msgs/Float64.h"
#include <sensor_msgs/JointState.h>


static const std::string OPENCV_WINDOW = "Image window";

using namespace cv;
using namespace std;
using namespace Eigen;

//Centers of the circles
int counter {0};
cv::Point center1;
cv::Point center2;
cv::Point center3;
cv::Point center4;

cv::Point center1r;
cv::Point center2r;
cv::Point center3r;
cv::Point center4r;

double x {0}, y {0};
double q1_vel {0}, q2_vel {0};



class ImageConverter
{	
  ros::NodeHandle nh_;
  ros::NodeHandle nh1;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;
  //ros::NodeHandle n1;
  ros::Publisher chatter_pub1, chatter_pub2;	
    int itr = 1;	


public:



 
  ImageConverter()
    : it_(nh_)
  {
  
  	
    // Subscribe to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/vbmbot/camera1/image_raw", 1,
      &ImageConverter::imageCb, this);
    
    image_pub_ = it_.advertise("/image_converter/output_video", 1);
    chatter_pub1 = nh1.advertise<std_msgs::Float64>("Joint_Vel1", 1000);
    chatter_pub2 = nh1.advertise<std_msgs::Float64>("Joint_Vel2", 1000);
    
	
    

    cv::namedWindow(OPENCV_WINDOW);
    
  }

  ~ImageConverter()
  {
    cv::destroyWindow(OPENCV_WINDOW);
  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {
    //cout << __func__ << endl;
    waitKey(5);
    
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

      

    
    //cv::waitKey(3);
 	
 	
 	// HSV Conversion
	cv::Mat HSVImage;
	cv::Mat ThreshImageYellow, ThreshImageGreen, ThreshImageRed, ThreshImageBlue ;
	//Transform the colors into HSV
	cvtColor(cv_ptr->image,HSVImage,CV_BGR2HSV);
	//for colors
	inRange(HSVImage,cv::Scalar(20,100,100),cv::Scalar(30,255,255),ThreshImageYellow);
	inRange(HSVImage,cv::Scalar(36,25,25),cv::Scalar(86,255,255),ThreshImageGreen);
	inRange(HSVImage,cv::Scalar(0,50,50),cv::Scalar(10,255,255),ThreshImageRed);
	inRange(HSVImage,cv::Scalar(94,80,2),cv::Scalar(126,255,255),ThreshImageBlue);
	
	cv::waitKey(5);	
	

	//To find the center
    cv::Moments mu1 = moments(ThreshImageYellow, true);
    cv::Moments mu2 = moments(ThreshImageGreen, true);
    cv::Moments mu3 = moments(ThreshImageRed, true);
    cv::Moments mu4 = moments(ThreshImageBlue, true);
    
        

    center1.x = mu1.m10 / mu1.m00;
    center1.y = mu1.m01 / mu1.m00;    


    cv::Mat3b res1, res2, res3, res4;
    
    
    cvtColor(ThreshImageYellow, res1, CV_GRAY2BGR);
    cvtColor(ThreshImageGreen, res2, CV_GRAY2BGR);
    cvtColor(ThreshImageRed, res3, CV_GRAY2BGR);
    cvtColor(ThreshImageBlue, res4, CV_GRAY2BGR);
	
	medianBlur(res1, res1, 5);
	medianBlur(res2, res2, 5);
	medianBlur(res3, res3, 5);
	medianBlur(res4, res4, 5);
   
    circle(res1, center1, 2, cv::Scalar(0,0,255));
    
    //waitKey(5);
    //imshow("Result1", res1);
    //cv::waitKey(5);

    center2.x = mu2.m10 / mu2.m00;
    center2.y = mu2.m01 / mu2.m00;    
    circle(res2, center2, 2, cv::Scalar(0,0,255));
    //imshow("Result2", res2);
    //cv::waitKey(5);
    
    center3.x = mu3.m10 / mu3.m00;
    center3.y = mu3.m01 / mu3.m00;    
    circle(res3, center3, 2, cv::Scalar(0,0,255));
    //imshow("Result3", res3);
    //cv::waitKey(5);
    
    
    center4.x = mu4.m10 / mu4.m00;
    center4.y = mu4.m01 / mu4.m00;    
    circle(res4, center4, 2, cv::Scalar(0,0,255));
    //imshow("Result4", res4);
    //cv::waitKey(5);
    //cout << center3 << endl;
	ref_circle_center();
    

	
    // Output modified video stream
    image_pub_.publish(cv_ptr->toImageMsg());
    waitKey(10);
    
  }
  
  
  	MatrixXd Image_Jacobian(int x, int y)
  	{
  		
		MatrixXd J (2,6);
    	J << -1, 0, x, x * y, -(1 + x * x), y,
	         0, -1, y, (1 + y * y), -x * y, -x;

    	
    	return J;
  	}
  
  

  
  
	void ref_circle_center()
	{
	  	cv::Mat ref = imread("/home/keval/catkin_ws/src/image_converter/data/ref_image.png");;
	  
	 
	  // HSV Conversion
		cv::Mat HSVImage;
		cv::Mat ThreshImageYellow, ThreshImageGreen, ThreshImageRed, ThreshImageBlue ;
		//Transform the colors into HSV
		cvtColor(ref,HSVImage,CV_BGR2HSV);
		//for colors
		inRange(HSVImage,cv::Scalar(20,100,100),cv::Scalar(30,255,255),ThreshImageYellow);
		inRange(HSVImage,cv::Scalar(36,25,25),cv::Scalar(86,255,255),ThreshImageGreen);
		inRange(HSVImage,cv::Scalar(0,50,50),cv::Scalar(10,255,255),ThreshImageRed);
		inRange(HSVImage,cv::Scalar(94,80,2),cv::Scalar(126,255,255),ThreshImageBlue);
		
		//cv::waitKey(0);	
		

		//To find the center
		cv::Moments mu1 = moments(ThreshImageYellow, true);
		cv::Moments mu2 = moments(ThreshImageGreen, true);
		cv::Moments mu3 = moments(ThreshImageRed, true);
		cv::Moments mu4 = moments(ThreshImageBlue, true);
		
		    
		//cv::Point center1, center2, center3, center4;
	  
		cv::Point center1r;
		cv::Point center2r;
		cv::Point center3r;
		cv::Point center4r;

    


		cv::Mat3b res1, res2, res3, res4;
		
		
		cvtColor(ThreshImageYellow, res1, CV_GRAY2BGR);
		cvtColor(ThreshImageGreen, res2, CV_GRAY2BGR);
		cvtColor(ThreshImageRed, res3, CV_GRAY2BGR);
		cvtColor(ThreshImageBlue, res4, CV_GRAY2BGR);
		
		medianBlur(res1, res1, 5);
		medianBlur(res2, res2, 5);
		medianBlur(res3, res3, 5);
		medianBlur(res4, res4, 5);
	   
		center1r.x = mu1.m10 / mu1.m00;
		center1r.y = mu1.m01 / mu1.m00;	   
		circle(res1, center1r, 2, cv::Scalar(0,0,255));
		//imshow("Result1", res1);
		//cout << center1r << endl;
		//cout << center1 << endl;
		cv::waitKey(5);

		center2r.x = mu2.m10 / mu2.m00;
		center2r.y = mu2.m01 / mu2.m00;    
		circle(res2, center2r, 2, cv::Scalar(0,0,255));
		//imshow("Result2", res2);
		cv::waitKey(5);
		
		center3r.x = mu3.m10 / mu3.m00;
		center3r.y = mu3.m01 / mu3.m00;    
		circle(res3, center3r, 2, cv::Scalar(0,0,255));
		//imshow("Result3", res3);
		cv::waitKey(5);
		
		center4r.x = mu4.m10 / mu4.m00;
		center4r.y = mu4.m01 / mu4.m00;    
		circle(res4, center4r, 2, cv::Scalar(0,0,255));
		//imshow("Result4", res4);
		cv::waitKey(5);
		//cout << center1r.x << " " << center1r.y << " " << center2r.x << " " << center2r.y << " " << center3r.x << " " << center3r.y << " " << center4r.x << " " << center4r.y << endl;

		
		//cout << "RT " << center1 << endl;
		//cout << "Ref " << center1r << endl;
		//cout << "Error " << error_center_1 << endl;
		
		
		// Start Visual Servoing
	
		cv::Point error_center_1, error_center_2, error_center_3, error_center_4;
		error_center_1 = center1r - center1;
		error_center_2 = center2r - center2;
		error_center_3 = center3r - center3;
		error_center_4 = center4r - center4;
		
		//cout << "RT " << center1 << endl;
		//cout << "Ref " << center1r << endl;
		//cout << "Error " << error_center_1 << endl;
		
		
		long long int e_c_1_x, e_c_1_y, e_c_2_x, e_c_2_y, e_c_3_x, e_c_3_y, e_c_4_x, e_c_4_y;
		
		
		// Error values
		e_c_1_x = error_center_1.x;
		e_c_1_y = error_center_1.y;
		
		e_c_2_x = error_center_2.x;
		e_c_2_y = error_center_2.y;
		
		e_c_3_x = error_center_3.x;
		e_c_3_y = error_center_3.y;
		
		e_c_4_x = error_center_4.x;
		e_c_4_y = error_center_4.y;
		
		// Error Matrix
		
		MatrixXd e (8, 1);
		
		e << e_c_1_x, e_c_1_y,
		     e_c_2_x, e_c_2_y,
		     e_c_3_x, e_c_3_y,
		     e_c_4_x, e_c_4_y;
		     
     	//cout << e << endl;
     	//cout << " " << endl;
		

		
		
		// Image Jacobian
		
		MatrixXd J1 (2, 6);
		MatrixXd J2 (2, 6);
		MatrixXd J3 (2, 6);
		MatrixXd J4 (2, 6);
		MatrixXd J (8, 6);
		

		
		// MatrixXd J_inv (6, 8);
		
		
		J1 = Image_Jacobian(center1.x, center1.y);
		J2 = Image_Jacobian(center2.x, center2.y);
		J3 = Image_Jacobian(center3.x, center3.y);
		J4 = Image_Jacobian(center4.x, center4.y);
		
		J << J1, J2, J3, J4;
		
		
		// Inverse Image Jacobian
		Eigen::MatrixXd J_Image_Inv = J.completeOrthogonalDecomposition().pseudoInverse();  // (6x8)
		
		//cout << J << endl;
		//cout << " " << endl;
		//cout << J_Image_Inv << endl;
		//cout << " " << endl;
		
		// Calculate V_C (6x1)
		
		MatrixXd V_C (6, 1);
		MatrixXd V_C_P (2, 1);
		MatrixXd V_C_Prime (2, 1);
		
		float lambda {0};
		
		lambda = -0.001;
		
		V_C = -lambda * J_Image_Inv * e;
		
		V_C_P = V_C.block<2,1>(0,0);
		
		
		
		//cout << V_C << endl;
		
		// Robot Jacobian
		
		
		//ros::NodeHandle n;
		//ros::Subscriber sub = n.subscribe("/vbmbot/joint1_position_controller/command", 1000, chatterCallback);
		
		double d1 {0.5}, d2 {0.5};
		
		MatrixXd Robot_Jacobian (2, 2);
		MatrixXd Inverse_Robot_Jacobian (2, 2);
		//MatrixXd q1 (1, 1);
		//MatrixXd q2 (1, 1);
		
		Robot_Jacobian << -d1 * sin (x) - d2 * sin (x + y), -d2 * sin(x + y),
		 d1 * cos (x) + d2 * cos (x + y),  d2 * cos (x + y);
		 
		Inverse_Robot_Jacobian = Robot_Jacobian.inverse();
		
		V_C_Prime = Inverse_Robot_Jacobian * V_C_P;
		
		q1_vel = V_C_Prime(0, 0);
		q2_vel = V_C_Prime(1, 0);

		//cout << q1_vel << endl;
		//cout << q2_vel << endl;
		
		std_msgs::Float64 a;
		std_msgs::Float64 b;
		a.data = q1_vel;
		b.data = q2_vel;
		chatter_pub1.publish(a);
		chatter_pub2.publish(b);
		waitKey(1);
		
		
		vector<cv::Point> C1;
		vector<cv::Point> C2;
		vector<cv::Point> C3;
		vector<cv::Point> C4;
		
		C1.push_back(center1);
		C2.push_back(center2);
		C3.push_back(center3);
		C4.push_back(center4);
		
		//cout << center1.x << " " << center1.y << " " << center2.x << " " << center2.y << " " << center3.x << " " << center3.y << " " << center4.x << " " << center4.y << endl; 
		
		//counter++;
		
		/*
		
		for (auto i:C1 )
		{
			cout << i.x << endl;
		}
		
		for (auto i:C1 )
		{
			cout << i.y << endl;
		}
		
		for (auto i:C2 )
		{
			cout << i.x << endl;
		}
		
		for (auto i:C2 )
		{
			cout << i.y << endl;
		}
		
		for (auto i:C3 )
		{
			cout << i.x << endl;
		}
		
		for (auto i:C3 )
		{
			cout << i.y << endl;
		}
		
		for (auto i:C4 )
		{
			cout << i.x << endl;
		}
		
		for (auto i:C4 )
		{
			cout << i.y << endl;
		}
			
		*/	
	
	}

};

void chatterCallback1(const sensor_msgs::JointState& msg1)
{
  
  x = msg1.position[0];
}



void chatterCallback2(const sensor_msgs::JointState& msg2)
	{
	  
	  y = msg2.position[1];
	}


int main(int argc, char** argv)
{

  //ref_circle_center();
  
  
  ros::init(argc, argv, "image_converter");
  ros::NodeHandle n1, n2;
  ros::Subscriber sub1 = n1.subscribe("/vbmbot/joint_states", 1000, chatterCallback1);
  ros::Subscriber sub2 = n2.subscribe("/vbmbot/joint_states", 1000, chatterCallback2);
  
  ImageConverter ic;
 
  ros::spin();

  return 0;
}
