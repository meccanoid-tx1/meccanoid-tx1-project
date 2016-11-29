#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <meccanoid_motors/meccanoid_motor_control.h>
#include <meccanoid_map/map.hpp>
#include <meccanoid_map/meccanoid_map.h>
#include <meccanoid_positioning/hedge_pos.h>

/*
/ Path planner class 
*/
class MeccanoidPathPlanner{
  public:
    /*
    / Constructor
    */
    MeccanoidPathPlanner(ros::Publisher pub){
        motorControlPublisher = pub;
        isNavigating.data = false;
        map = new meccanoid_map::Map(-1);
    };

    /*
    / Callback plans path and publishes navigation and motor control messages
    */
    void isNavigatingCallback(const std_msgs::Bool::ConstPtr &msg){
        isNavigating.data = msg->data;
    }

    /*
    / Callback which updates map
    */
    void mapCallback(const meccanoid_map::meccanoid_mapConstPtr &msg){
        map_msg = *msg;
        if(isNavigating.data){
            //TODO: plan path -> send motor commands
            motorControlPublisher.publish(generateMotorControlMsg());
        }
    }

    /*
    / Callback plans path and publishes navigation and motor control messages
    */
    void positionCallback(const meccanoid_positioning::hedge_posConstPtr &msg){
        pos_msg = *msg;
        if(isNavigating.data){
            //TODO: plan path -> send motor commands
            motorControlPublisher.publish(generateMotorControlMsg());
        }
    }


  private:
    ros::Publisher motorControlPublisher;
    std_msgs::Bool isNavigating;
    meccanoid_map::Map* map;
    meccanoid_map::meccanoid_map map_msg;
    meccanoid_positioning::hedge_pos pos_msg;

    /*
    / Generate motor control message
    */
    meccanoid_motors::meccanoid_motor_control generateMotorControlMsg(){
        meccanoid_motors::meccanoid_motor_control motor_control_msg;
        //TODO: generate appropriate motor control msg;
        return motor_control_msg;
    }

};


/*
/ Meccanoid path planner node main 
*/
int main(int argc, char **argv)
{
    // init ros and set showImage param
    ros::init(argc, argv, "meccanoid_path_planning");
    ros::NodeHandle nodeHandle;

    // set up motor control publishers
    ros::Publisher motorControlPublisher = nodeHandle.advertise<meccanoid_motors::meccanoid_motor_control>("motor_control", 10);

    // set up path planner
    MeccanoidPathPlanner pathPlanner(motorControlPublisher);

    // set up is navigating subscriber
    ros::Subscriber isNavigatingSubscriber = nodeHandle.subscribe("/is_navigating", 1, 
                                                  &MeccanoidPathPlanner::isNavigatingCallback, &pathPlanner);
    // set up map subscriber
    ros::Subscriber mapSubscriber = nodeHandle.subscribe("/map", 1, 
                                                  &MeccanoidPathPlanner::mapCallback, &pathPlanner);
    // set up position subscriber
    ros::Subscriber positionSubscriber = nodeHandle.subscribe("/position", 1, 
                                                  &MeccanoidPathPlanner::positionCallback, &pathPlanner);    
    // start ros blocking spin()
    ros::spin();
}