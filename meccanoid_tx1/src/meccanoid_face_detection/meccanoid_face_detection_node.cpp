#include <ros/ros.h>

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include <std_msgs/Bool.h>
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
    MeccanoidFaceDetector(ros::Publisher pub, bool showIm){
        faceLocationPublisher = pub;
        showImages = showIm;
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
    std::vector<cv::Rect> faceLocations;
    cv::CascadeClassifier faceLocationClassifier;
    cv::Mat image;
    bool isNavigating;
    bool showImages;

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

    /*
    / Publishes face locations as meccanoid_face_location messages
    */
    void publishFaceLocations(){
        for (size_t i = 0; i < faceLocations.size(); i++){
            meccanoid_face_location face_location_msg;
            face_location_msg.x = faceLocations[i].x;
            face_location_msg.y = faceLocations[i].y;
            face_location_msg.w = faceLocations[i].width;
            face_location_msg.h = faceLocations[i].height;
            faceLocationPublisher.publish(face_location_msg);
        }
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

    // set up face detector
    MeccanoidFaceDetector faceDetector(faceLocationPublisher,showImages);

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
