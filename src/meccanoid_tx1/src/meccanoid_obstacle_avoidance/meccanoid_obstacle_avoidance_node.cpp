#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/Bool.h>


using namespace cv;
using namespace std;

// ROS Variables
std_msgs::Int16MultiArray intmsg_xy;
std_msgs::Bool obsmsg_dect;

// Position Variables
int offset_x, offset_y;

// OpenCV Image Variables
cv::Mat src, src_gray, src_blur, pros, pros2, pros_grey;
cv::Mat dst, detected_edges, drawing;

// Robot Variables
int const robot_height = 1200;
int const robot_width = 300;
int const obs_depth = 200;
Rect robot_box;
int pixel_robot_width, pixel_robot_height;

// Kinect Variables
int const focal_length = 525;
int depthmin;
int depthx, depthy;
int intersection;

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
		intersection = 0;
		bool break_var = false;

//left Scan
	for (int i = 320-(pixel_robot_width / 2); i >= 0 && !break_var; i--)
	{
	intersection = 0;
    Rect robot_box(i, 0, pixel_robot_width, pixel_robot_height);

		for (int j = 0; j < contours.size(); j++)
    {
	Rect r3 = robot_box & boundRect[j];
	if (r3.area() > 0)
	{
	    intersection = 2;
	}
    }
	if (intersection == 0)
    {
	std::cout << "Opening Found" << std::endl;
	cv::Scalar color2 = cv::Scalar(0, 255, 0);
	rectangle(drawing, robot_box.tl(), robot_box.br(), color2, 2, 8, 0);
	offset_x = depthmin*i/focal_length;
	offset_y = depthmin;
    if(contours.size()>0)
    intersection = 1;
    break_var = true;
    }
	}
//Right Scan
for (int i = 320-(pixel_robot_width / 2); i <= (640-pixel_robot_width) && !break_var; i++)
	{
	intersection = 0;
    Rect robot_box(i, 0, pixel_robot_width, pixel_robot_height);

	for (int j = 0; j < contours.size(); j++)
    {
	Rect r3 = robot_box & boundRect[j];
	if (r3.area() > 0)
	{
	    intersection = 2;
	}
    }
	if (intersection == 0)
    {
	std::cout << "Opening Found" << std::endl;
	cv::Scalar color2 = cv::Scalar(0, 255, 0);
	rectangle(drawing, robot_box.tl(), robot_box.br(), color2, 2, 8, 0);
	offset_x = -depthmin*i/focal_length;
	offset_y = depthmin;
    if(contours.size()>0)
    intersection = 1;
	break_var = true;
    }
	}
    }

}

// callback
void imCallback(const sensor_msgs::ImageConstPtr &msg)
{
    try
    {
	cv::Mat image = cv_bridge::toCvCopy(msg, "16UC1")->image;
	image.convertTo(pros, CV_8U, 0.00390625);
	cv::cvtColor(pros, pros, CV_GRAY2RGB);
	depthmin = 1500;
	uint16_t depth;
	usleep(8000);
        pros2 = pros.clone();
        pros2 = cv::Scalar::all(0);
	/*for (int y = 1; y < image.rows; y++)
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
	}*/

	for (int y = 1; y < (image.rows-2); y++)
	{
	    for (int x = 1; x < (image.cols-2); x++)
	    {
		int depth_filt=0;
		   for(int i=0; i<3; i++) //Depth Filter
		   { 
			   for(int j=0; j<3; j++)
			   {
				   depth = image.at<uint16_t>((x+i), (y+j));
				   if (depth > depth_filt)
			       depth_filt = depth;
		     
			   }
		   }
               if (x != 480 && x < 480) //dead Pixels
{
		   if (depth_filt < (depthmin) && depth_filt > 400)
		    {
			depthmin = depth_filt;
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
	ros::Publisher positionxy = nh.advertise<std_msgs::Int16MultiArray>("/obstacle_avoidance/offsetxy", 1);
	//ros::Publisher obs_dect = nh.advertise<std_msgs::Bool>("/obstacle_avoidance/obs_dect", 1);
    ros::Rate loop_rate(100);

	int counter = 0;
    while (ros::ok()){

	if(counter >= 9){
		intmsg_xy.data.clear();
		intmsg_xy.data.push_back(offset_x);
		intmsg_xy.data.push_back(offset_y);
		intmsg_xy.data.push_back(intersection);
		//obsmsg_dect.data = intersection;
		positionxy.publish(intmsg_xy);
		//obs_dect.publish(obsmsg_dect);
	}
	counter = (counter+1)%10;

	
    ros::spinOnce();
    loop_rate.sleep();
     }
 
	
    return 0;
}
