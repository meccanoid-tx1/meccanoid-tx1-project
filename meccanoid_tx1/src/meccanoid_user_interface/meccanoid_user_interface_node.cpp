#include <ros/ros.h>
#include <std_msgs/Bool.h>

/*
/ Meccanoid user interface node main 
*/
int main(int argc, char **argv){
    // init ros
    ros::init(argc, argv, "meccanoid_face_localization");
    ros::NodeHandle nodeHandle;
    ros::Publisher isNavigatingPublisher = nodeHandle.advertise<std_msgs::Bool>("is_navigating", 10);
    ros::Rate loop_rate(10);

    // set up message
    std_msgs::Bool is_nav_msg;
    is_nav_msg.data = false;

    // publish message
    while(ros::ok()){
        isNavigatingPublisher.publish(is_nav_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
}