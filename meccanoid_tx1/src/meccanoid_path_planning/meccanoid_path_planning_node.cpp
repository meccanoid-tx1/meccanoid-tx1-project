#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include "meccanoid_map/map.hpp"
#include <meccanoid_tx1/meccanoid_motor_control.h>
#include <meccanoid_tx1/meccanoid_map.h>
#include <meccanoid_tx1/hedge_pos.h>

#include <stdint.h>

#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/Int8MultiArray.h>

/*
/ Path planner class 
*/
class MeccanoidPathPlanner{
  public:
    /*
    / Constructor
    */
    MeccanoidPathPlanner(ros::Publisher pub, ros::Publisher pub2){
        motorControlPublisher = pub;
	arduinoMotorControlPublisher = pub2;
        isNavigating.data = false;
        map = new meccanoid_tx1::Map(-1);
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
    void mapCallback(const meccanoid_tx1::meccanoid_mapConstPtr &msg){
        map_msg = *msg;
        if(isNavigating.data){
            //TODO: plan path -> send motor commands
            motorControlPublisher.publish(generateMotorControlMsg());
        }
    }

    /*
    / Callback plans path and publishes navigation and motor control messages
    */
    void positionCallback(const meccanoid_tx1::hedge_posConstPtr &msg){
        pos_msg = *msg;
	ROS_INFO("recieved position callback");
	publishMotorControlSignal();
        if(isNavigating.data){
            //TODO: plan path -> send motor commands
            motorControlPublisher.publish(generateMotorControlMsg());
        }
    }


  private:
    ros::Publisher motorControlPublisher;
    ros::Publisher arduinoMotorControlPublisher;
    std_msgs::Bool isNavigating;
    meccanoid_tx1::Map* map;
    meccanoid_tx1::meccanoid_map map_msg;
    meccanoid_tx1::hedge_pos pos_msg;

    /*
    / Generate motor control message
    */
    meccanoid_tx1::meccanoid_motor_control generateMotorControlMsg(){
        meccanoid_tx1::meccanoid_motor_control motor_control_msg;
        //TODO: generate appropriate motor control msg;
        return motor_control_msg;
    }


    /*
    / Generate motor control signal
    */
    void publishMotorControlSignal(){
	// motor control signals
	uint8_t dirA, dirB, breakA, breakB, speedA, speedB;

	// set up motor control signals using map, beacons etc.

	if(pos_msg.y_m < -1.0){

	  if(pos_msg.x_m > 1.0){
		dirA = 1;
		dirB = 1;
		breakA = 0;
		breakB = 1;
		speedA = 255;
		speedB = 0;
	   }else{
		dirA = 1;
		dirB = 1;
		breakA = 1;
		breakB = 0;
		speedA = 0;
		speedB = 255;
	   }
	}else{
		dirA = 1;
		dirB = 1;
		breakA = 1;
		breakB = 1;
		speedA = 0;
		speedB = 0;
	}

	// message structure
	std_msgs::Int8MultiArray motor_control_signal_msg;
	motor_control_signal_msg.data.clear();

	// populate message structure by pushing in order
	motor_control_signal_msg.data.push_back(dirA);
	motor_control_signal_msg.data.push_back(dirB);
	motor_control_signal_msg.data.push_back(breakA);
	motor_control_signal_msg.data.push_back(breakB);
	motor_control_signal_msg.data.push_back(speedA);
	motor_control_signal_msg.data.push_back(speedB);

	//publish motor control message
	arduinoMotorControlPublisher.publish(motor_control_signal_msg);
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
    ros::Publisher motorControlPublisher = nodeHandle.advertise<meccanoid_tx1::meccanoid_motor_control>("motor_control", 10);

	ros::Publisher arduinoMotorControlPublisher = nodeHandle.advertise<std_msgs::Int8MultiArray>("motor_control_signal", 10);

    // set up path planner
    MeccanoidPathPlanner pathPlanner(motorControlPublisher, arduinoMotorControlPublisher);

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
