#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <bits/stdc++.h>

static const std::string OPENCV_WINDOW = "Image window";

using namespace cv;
using namespace std;

class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;

public:
  ImageConverter()
    : it_(nh_)
  {
    // Subscrive to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/vbmbot/camera1/image_raw", 1,
      &ImageConverter::imageCb, this);
    image_pub_ = it_.advertise("/image_converter/output_video", 1);

    cv::namedWindow(OPENCV_WINDOW);
  }

  ~ImageConverter()
  {
    cv::destroyWindow(OPENCV_WINDOW);
  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {
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



    // Update GUI Window
    cv::imshow(OPENCV_WINDOW, cv_ptr->image);
    
    //Save converted image
    //cv::imwrite("Converted.jpg", cv_ptr->image);

    
    
	cv::Mat HSVImage;
	cv::Mat ThreshImageYellow, ThreshImageGreen, ThreshImageRed, ThreshImageBlue ;
	//Transform the colors into HSV
	cvtColor(cv_ptr->image,HSVImage,CV_BGR2HSV);
	//for colors
	inRange(HSVImage,cv::Scalar(20,100,100),cv::Scalar(30,255,255),ThreshImageYellow);
	inRange(HSVImage,cv::Scalar(36,25,25),cv::Scalar(86,255,255),ThreshImageGreen);
	inRange(HSVImage,cv::Scalar(0,50,50),cv::Scalar(10,255,255),ThreshImageRed);
	inRange(HSVImage,cv::Scalar(94,80,2),cv::Scalar(126,255,255),ThreshImageBlue);
/*	
	cv::waitKey(0);
	
	//Canny Edge Detection
	cv::Mat edges;

    cv::Canny(cv_ptr->image, edges, 100, 200, 3, false);

    // Display canny edge detected image
    imshow("Canny edge detection", edges);
    
    
*/
    cv::waitKey(0);
    
   
   /* 
    //Harris Corner
    
    Mat src_gray;
    
    int blockSize = 9;
    int apertureSize = 5;
    double k = 1;
    int thresh = 200;
    const char* corners_window = "Corners detected";
    
    Mat dst = Mat::zeros( cv_ptr->image.size(), CV_32FC1 );
    cvtColor(cv_ptr->image, src_gray, cv::COLOR_BGR2GRAY);
    cornerHarris( src_gray, dst, blockSize, apertureSize, k );
    Mat dst_norm, dst_norm_scaled;
    normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
    convertScaleAbs( dst_norm, dst_norm_scaled );
    for( int i = 0; i < dst_norm.rows ; i++ )
    {
        for( int j = 0; j < dst_norm.cols; j++ )
        {
            if( (int) dst_norm.at<float>(i,j) > thresh )
            {
                circle( dst_norm_scaled, Point(j,i), 5,  Scalar(0), 2, 8, 0 );
            }
        }
    }
    namedWindow( corners_window );
    imshow( corners_window, dst_norm_scaled );
    


    waitKey(0);




//Hough Circle


 
	Mat src, gray;

	cvtColor( cv_ptr->image, gray, CV_BGR2GRAY );

	// Reduce the noise so we avoid false circle detection
	GaussianBlur( gray, gray, Size(9, 9), 2, 2 );
	//namedWindow( "Gray", WINDOW_AUTOSIZE );
	//imshow( "Gray", gray );

	vector<Vec3f> circles;

	// Apply the Hough Transform to find the circles
	HoughCircles( gray, circles, CV_HOUGH_GRADIENT, 2, 25, 70, 52, 0, 0 );

	// Draw the circles detected
	for( size_t i = 0; i < circles.size(); i++ )
	{
	  Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
	  int radius = cvRound(circles[i][2]);     
	  circle( cv_ptr->image, center, 3, Scalar(0,255,0), -1, 8, 0 );// circle center     
	  circle( cv_ptr->image, center, radius, Scalar(0,0,255), 3, 8, 0 );// circle outline
	  cout << "center : " << center << "\nradius : " << radius << endl;
	}

	// Show your results
	namedWindow( "Hough Circle", WINDOW_AUTOSIZE );
	imshow( "Hough Circle", cv_ptr->image );
*/
	waitKey(0);




	//To find the center
    cv::Moments mu1 = moments(ThreshImageYellow, true);
    cv::Moments mu2 = moments(ThreshImageGreen, true);
    cv::Moments mu3 = moments(ThreshImageRed, true);
    cv::Moments mu4 = moments(ThreshImageBlue, true);
    
        
    //cv::Point center1, center2, center3, center4;
    
    cv::Point center1;
    cv::Point center2;
    cv::Point center3;
    cv::Point center4;
    
    center1.x = mu1.m10 / mu1.m00;
    center1.y = mu1.m01 / mu1.m00;    



    cv::Mat3b res1, res2, res3, res4;
    
    cvtColor(ThreshImageYellow, res1, CV_GRAY2BGR);
    cvtColor(ThreshImageGreen, res2, CV_GRAY2BGR);
    cvtColor(ThreshImageRed, res3, CV_GRAY2BGR);
    cvtColor(ThreshImageBlue, res4, CV_GRAY2BGR);

   
    circle(res1, center1, 2, cv::Scalar(0,0,255));
    //imshow("Result1", res1);
    cv::waitKey(5);
/*
    center2.x = mu2.m10 / mu2.m00;
    center2.y = mu2.m01 / mu2.m00;    
    circle(res2, center2, 2, cv::Scalar(0,0,255));
    //imshow("Result2", res2);
    cv::waitKey(5);
    
    center3.x = mu3.m10 / mu3.m00;
    center3.y = mu3.m01 / mu3.m00;   
    circle(res3, center3, 2, cv::Scalar(0,0,255));
    //imshow("Result3", res3);
    cv::waitKey(5);
    
    center4.x = mu4.m10 / mu4.m00;
    center4.y = mu4.m01 / mu4.m00;    
    circle(res4, center4, 2, cv::Scalar(0,0,255));
    //imshow("Result4", res4);
    cv::waitKey(5);

*/
    
    
    std::cout<<center1;
    //std::cout<<center2;
    //std::cout<<center3;
    //std::cout<<center4;
    cv::waitKey(5);



	
    
    
    
  /*  
    
    cv::imwrite("/home/keval/Desktop/Original_Image.jpg", cv_ptr->image);
    
    cv::imwrite("/home/keval/Desktop/Yellow_Image.jpg", ThreshImageYellow);
    cv::imwrite("/home/keval/Desktop/Green_Image.jpg", ThreshImageGreen);
    cv::imwrite("/home/keval/Desktop/Red_Image.jpg", ThreshImageRed);
    cv::imwrite("/home/keval/Desktop/Blue_Image.jpg", ThreshImageBlue);
    
    //cv::waitKey(3);
    
 */ 

    // Output modified video stream
    image_pub_.publish(cv_ptr->toImageMsg());
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  ImageConverter ic;
  ros::spin();
  return 0;
}
