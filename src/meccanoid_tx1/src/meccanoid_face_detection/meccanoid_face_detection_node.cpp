#include <ros/ros.h>

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include <stdint.h>

#include <std_msgs/Bool.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/Int8MultiArray.h>
#include <meccanoid_tx1/meccanoid_face_location.h>

using meccanoid_tx1::meccanoid_face_location;

/*
/ Face detector class 
*/
class MeccanoidFaceDetector{
  public:
    /*
    / Constructor
    */
    MeccanoidFaceDetector(ros::Publisher pub, ros::Publisher pub2, bool showIm){
        faceLocationPublisher = pub;
	arduinoPositionPublisher = pub2;
	everyOther = true;
	pos.push_back(0x77);
	pos.push_back(0x87);
        showImages = showIm;
	FOV_WIDTH = 640;
	FOV_HEIGHT = 480;
        if (!faceLocationClassifier.load("/home/ubuntu/code/meccanoid_ws/res/haarcascades/haarcascade_frontalface_alt.xml")){
            ROS_INFO("failed to load classifier xml,"
             " make sure the correct path is specified in meccanoid_face_detection.cpp");
        }
    };

    /*
    / Callback which publishes face locations is faces are detected
    */
    void faceDetectorCallback(const sensor_msgs::ImageConstPtr &msg){
        if(!isNavigating){
            try{
                image = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8)->image;
                if (detectFaces()){
                    publishFaceLocations();
                }else{
		    publishNoFaceLocations();
		}
                cv::imshow("image_window", image);
                cv::waitKey(30);
            }catch (cv_bridge::Exception &e){
                ROS_ERROR("could not convert image");
            }
        }
    }

    /*
    / Callback assigning 'is navigating' mode
    */
    void isNavigatingCallback(const std_msgs::Bool::ConstPtr &msg){
        isNavigating = msg->data;
    }

  private:
    ros::Publisher faceLocationPublisher;
    ros::Publisher arduinoPositionPublisher;
    std::vector<cv::Rect> faceLocations;
    cv::CascadeClassifier faceLocationClassifier;
    cv::Mat image;
    std::vector<uint8_t> pos;
    bool isNavigating;
    bool showImages;
    bool everyOther;
    int FOV_WIDTH;
    int FOV_HEIGHT;

    /*
    / Stores face locations in 'faceLocations' as cv::Rect objects.
    */
    bool detectFaces(){
        faceLocationClassifier.detectMultiScale(image, faceLocations, 1.09, 3, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(40, 40));
        if (faceLocations.size() > 0) {
            if(showImages){
                for (size_t i = 0; i < faceLocations.size(); i++){
                    cv::rectangle(image, faceLocations[i], cv::Scalar(0, 0, 255), 2);
                }
            }
            return true;
        }
        return false;
    }


    void resetPos(){
		pos.clear();
    	pos.push_back(0x77);
		pos.push_back(0x87);
    }

    
    std::vector<uint8_t> mapPixelToPosition(std::vector<int> centerPoint){
	int dx,dy;
	//float range_per_pixel = 0.15; //0.36;

	float range_per_x = (0xA0-0x4E)/640.0;
	float range_per_y = (0xA5-0x87)/(480.0/2); // di-vision by 2 to increase range of motion up/down	
	dx = (centerPoint[0] - FOV_WIDTH/2)*range_per_x;
	dy = (centerPoint[1] - FOV_HEIGHT/2)*range_per_y;
	resetPos();

	pos[0] = ((pos[0]-dx) < 0x00 || (pos[0]-dx) > 0xEF) ? 0x77 : pos[0]-dx;
	pos[1] = ((pos[1]-dy) < 0x00 || (pos[1]-dy) > 0xEF) ? 0x77 : pos[1]-dy;

	//pos[0] -= dx*range_per_x;
	//pos[1] -= dy*range_per_y;

	return pos;
    } 

    std::vector<int> getCenterPoint(cv::Rect face){
	int x,y;
	std::vector<int> centerPoint;
	centerPoint.push_back(face.x + (face.width / 2));
	centerPoint.push_back(face.y + (face.height / 2));
	return centerPoint;
    }

    cv::Rect getLargestFace(){
	int idx = 0,w,h,largest = -1;
	for (size_t i = 0; i < faceLocations.size(); i++){
            w = faceLocations[i].width;
            h = faceLocations[i].height;
            
	    if(w*h > largest){
		idx = i;
		largest = w*h;
	    }
	}
	return faceLocations[idx];
    }


    /*
    / Publishes face locations as meccanoid_face_location messages
    */
    void publishFaceLocations(){
	cv::Rect largestFace = getLargestFace();
	std::vector<int> centerPoint = getCenterPoint(largestFace);
	std::vector<uint8_t> positions = mapPixelToPosition(centerPoint);

	std_msgs::Int8MultiArray position_msg;
	position_msg.data.clear();
	position_msg.data.push_back(positions[0]);
	position_msg.data.push_back(positions[1]);

	arduinoPositionPublisher.publish(position_msg);
    }

    void publishNoFaceLocations(){
	resetPos();
	std_msgs::Int8MultiArray position_msg;
	position_msg.data.clear();
	position_msg.data.push_back(pos[0]);
	position_msg.data.push_back(pos[1]);
	arduinoPositionPublisher.publish(position_msg);
    }

};


/*
/ Meccanoid face detection node main 
*/
int main(int argc, char **argv)
{
    // init ros and set showImage param
    bool showImages = true;
    ros::init(argc, argv, "meccanoid_face_detection");
    ros::NodeHandle nodeHandle;

    // set up face location publisher
    ros::Publisher faceLocationPublisher = nodeHandle.advertise<meccanoid_face_location>("face_location", 10);

    ros::Publisher arduinoPositionPublisher = nodeHandle.advertise<std_msgs::Int8MultiArray>("face_location_pos", 10000);

    // set up face detector
    MeccanoidFaceDetector faceDetector(faceLocationPublisher,arduinoPositionPublisher,showImages);

    // set up image subscriber
    image_transport::ImageTransport it(nodeHandle);
    image_transport::Subscriber faceLocationSubscriber = it.subscribe("/rgb/image_raw", 1,
                                        &MeccanoidFaceDetector::faceDetectorCallback, &faceDetector);

    ros::Subscriber isNavigatingSubscriber = nodeHandle.subscribe("/is_navigating", 1, 
                                        &MeccanoidFaceDetector::isNavigatingCallback, &faceDetector);
    // set up image view 
    if(showImages){
        cv::namedWindow("image_window");
        cv::startWindowThread();
    }
    
    // start ros blocking spin()
    ros::spin();
    
    // kill image view
    if(showImages){
        cv::destroyWindow("image_window");
    }
}
