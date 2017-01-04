#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <std_msgs/Int16.h>
#include <vector>

using namespace cv;
using namespace std;

// ROS Variables
std_msgs::Int16 intmsg_x,intmsg_y;

// Position Variables
int offset_x, offset_y;

// OpenCV Image Variables
cv::Mat src, src_gray, src_blur, pros, pros2, pros_grey;
cv::Mat dst, detected_edges, drawing;

// Robot Variables
int const robot_height = 1200;
int const robot_width = 300;
int const obs_depth = 250;
Rect robot_box;
int pixel_robot_width, pixel_robot_height;

// Kinect Variables
int const focal_length = 525;
int depthmin;
int depthx, depthy;

// Canny Variables
int edgeThresh = 4;
int lowThreshold = 0;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;

// Contour Variables
cv::Mat threshold_output;
std::vector<std::vector<cv::Point> > contours;
std::vector<cv::Vec4i> hierarchy;

// Canny Edge Detector
void CannyThreshold(int, void *)
{   
  
    /// Reduce noise with a kernel 3x3
    blur(src, src_blur, cv::Size(4, 4));
    /// Canny detector
    cv::bitwise_not ( src_blur, src_blur );
   // detected_edges = cv::Scalar::all(0);
    src_blur.convertTo(detected_edges, CV_8U);
    cvtColor(detected_edges, detected_edges, CV_BGR2GRAY);
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size);
  // Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size);
    /// Using Canny's output as a mask, we display our result
    dst = cv::Scalar::all(0);
    src.copyTo(dst, detected_edges);
    cvtColor(dst, dst, CV_BGR2GRAY);
}

// Contours
void Contourmake(int, void *)
{
    cv::findContours(dst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    std::vector<std::vector<cv::Point> > contours_poly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());
    
    for (int i = 0; i < contours.size(); i++)
    {
	approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 3, true);
	boundRect[i] = boundingRect(cv::Mat(contours_poly[i]));
    }
    drawing = cv::Mat::zeros(dst.size(), CV_8UC3);
    for (int i = 0; i < contours.size(); i++)
    {
	cv::Scalar color = cv::Scalar(0, 0, 255);
	drawContours(drawing, contours_poly, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
	rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
    }

    pixel_robot_width = robot_width * focal_length / depthmin;
    pixel_robot_height = robot_height * focal_length / depthmin;


// Collison Detection
    if (true)
    {
		bool intersection = false;
		bool break_var = false;

//left Scan
	for (int i = 320-(pixel_robot_width / 2); i >= 0 && !break_var; i--)
	{
	intersection = false;
    Rect robot_box(i, 0, pixel_robot_width, pixel_robot_height);

	for (int j = 0; j < contours.size(); j++)
    {
	Rect r3 = robot_box & boundRect[j];
	if (r3.area() > 0)
	{
	    intersection = true;
	}
    }
	if (!intersection)
    {
	std::cout << "Opening Found" << std::endl;
	cv::Scalar color2 = cv::Scalar(0, 255, 0);
	rectangle(drawing, robot_box.tl(), robot_box.br(), color2, 2, 8, 0);
	offset_x = depthmin*i/focal_length;
	offset_y = depthmin;
	break_var = true;
    }
	}
//Right Scan
for (int i = 320-(pixel_robot_width / 2); i <= (640-pixel_robot_width) && !break_var; i++)
	{
	intersection = false;
    Rect robot_box(i, 0, pixel_robot_width, pixel_robot_height);

	for (int j = 0; j < contours.size(); j++)
    {
	Rect r3 = robot_box & boundRect[j];
	if (r3.area() > 0)
	{
	    intersection = true;
	}
    }
	if (!intersection)
    {
	std::cout << "Opening Found" << std::endl;
	cv::Scalar color2 = cv::Scalar(0, 255, 0);
	rectangle(drawing, robot_box.tl(), robot_box.br(), color2, 2, 8, 0);
	offset_x = -depthmin*i/focal_length;
	offset_y = depthmin;
	break_var = true;
    }
	}
    }

   //  std::cout << "countours size before = " << contours.size() << std::endl;
    
    /*contours.clear();
    hierarchy.clear();
    contours_poly.clear();
    boundRect.clear();*/

    std::cout << "countours size afer = " << contours.size() << std::endl;
}

// callback
void imCallback(const sensor_msgs::ImageConstPtr &msg)
{
    try
    {
	cv::Mat image = cv_bridge::toCvCopy(msg, "16UC1")->image;
	image.convertTo(pros, CV_8U, 0.00390625);
	cv::cvtColor(pros, pros, CV_GRAY2RGB);
	depthmin = 10000;
	uint16_t depth;
	usleep(8000);
        pros2 = pros.clone();
        pros2 = cv::Scalar::all(0);
	for (int y = 1; y < image.rows; y++)
	{
	    for (int x = 1; x < image.cols; x++)
	    {
		depth = image.at<uint16_t>(x, y);
		if (x != 480 && x < 480) //dead Pixels
		{
		    if (depth < (depthmin) && depth > 400)
		    {
			depthmin = depth;
			depthx = x;
			depthy = y;
		    }
		}
	    }
	}
	for (int i = 0; i < image.rows; i++)
	{
	    for (int j = 0; j < image.cols; j++)
	    {
		depth = image.at<uint16_t>(i, j);
		if (depth >= (depthmin - obs_depth) && depth <= (depthmin + obs_depth))
		{
		    pros.at<cv::Vec3b>(i, j)[0] = 255;
                    pros2.at<cv::Vec3b>(i, j)[0] = 255;
		}
	    }
	}
	//image.release();
	src = pros2.clone();
	cv::bitwise_not(src, src);
	cv::imshow("Processed Image", pros);
	cv::waitKey(30);
	std::cout << "depth: " << depthmin << " location: " << depthx << " X " << depthy << std::endl;
	/// Create a matrix of the same type and size as src (for dst)
	dst.create(src.size(), src.type());
	/// Create a Trackbar for user to enter threshold
	//cv::createTrackbar("Min Threshold:", "Edge Map", &lowThreshold, max_lowThreshold, CannyThreshold);
	/// Show the image
	
	// clear vectors...	
	contours.clear();
	hierarchy.clear();

	CannyThreshold(0, 0);
	Contourmake(0, 0);
	cv::imshow("Edge Map", drawing);
	//cv::imshow("Edge Map",dst);
    }

    catch (cv_bridge::Exception &e)
    {
	ROS_ERROR("could not convert image");
    }
}

// main

int main(int argc, char **argv)
{
    ros::init(argc, argv, "obstacle_avoidance");
    ros::NodeHandle nh;
    cv::namedWindow("Processed Image");
    cv::startWindowThread();
    cv::namedWindow("Edge Map");
    cv::startWindowThread();
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("/depth/image_raw", 1, imCallback);
	ros::Publisher positionx = nh.advertise<std_msgs::Int16>("/obstacle_avoidance/offsetx", 1);
	ros::Publisher positiony = nh.advertise<std_msgs::Int16>("/obstacle_avoidance/offsety", 1);
    ros::Rate loop_rate(100);
    while (ros::ok())
     {
    intmsg_x.data = offset_x;
	intmsg_y.data = offset_y;
	positionx.publish(intmsg_x);
	positiony.publish(intmsg_y);

    ros::spinOnce();

    loop_rate.sleep();
   }
 
	
    return 0;
}
