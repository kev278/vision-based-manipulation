#ifndef MY_GLOBALS_H
#define MY_GLOBALS_H

// This is a declaration of your variable, which tells the linker this value
// is found elsewhere.  Anyone who wishes to use it must include global.h,
// either directly or indirectly.
extern int myglobalint {30};


#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>








/*


 	// HSV Conversion
	cv::Mat HSVImage;
	cv::Mat ThreshImageYellow, ThreshImageGreen, ThreshImageRed, ThreshImageBlue ;
	//Transform the colors into HSV
	cvtColor(cv_ptr->image,HSVImage,CV_BGR2HSV);
	//for colors
	inRange(HSVImage,cv::Scalar(20,100,100),cv::Scalar(temp,255,255),ThreshImageYellow);
	inRange(HSVImage,cv::Scalar(36,25,25),cv::Scalar(86,255,255),ThreshImageGreen);
	inRange(HSVImage,cv::Scalar(0,50,50),cv::Scalar(10,255,255),ThreshImageRed);
	inRange(HSVImage,cv::Scalar(94,80,2),cv::Scalar(126,255,255),ThreshImageBlue);
	
	cv::waitKey(0);	
	

	//To find the center
    cv::Moments mu1 = moments(ThreshImageYellow, true);
    cv::Moments mu2 = moments(ThreshImageGreen, true);
    cv::Moments mu3 = moments(ThreshImageRed, true);
    cv::Moments mu4 = moments(ThreshImageBlue, true);
    
        
    //cv::Point center1, center2, center3, center4;
 /*   
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
	
	medianBlur(res1, res1, 5);
	medianBlur(res2, res2, 5);
	medianBlur(res3, res3, 5);
	medianBlur(res4, res4, 5);
   
    circle(res1, center1, 2, cv::Scalar(0,0,255));
    
    waitKey(5);
    imshow("Result1", res1);
    cv::waitKey(5);

    center2.x = mu2.m10 / mu2.m00;
    center2.y = mu2.m01 / mu2.m00;    
    circle(res2, center2, 2, cv::Scalar(0,0,255));
    imshow("Result2", res2);
    cv::waitKey(5);
    
    center3.x = mu3.m10 / mu3.m00;
    center3.y = mu3.m01 / mu3.m00;    
    circle(res3, center3, 2, cv::Scalar(0,0,255));
    imshow("Result3", res3);
    cv::waitKey(5);
    
    center4.x = mu4.m10 / mu4.m00;
    center4.y = mu4.m01 / mu4.m00;    
    circle(res4, center4, 2, cv::Scalar(0,0,255));
    imshow("Result4", res4);
    cv::waitKey(5);


*/


#endif

