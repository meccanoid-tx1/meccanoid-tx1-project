#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include "meccanoid_map/map.hpp"
#include <meccanoid_tx1/meccanoid_map.h>
#include <meccanoid_tx1/hedge_pos.h>

#include <stdint.h>
#include <stdlib.h>
#include <list>
#include <math.h>

#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/Int8MultiArray.h>
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/Bool.h>


bool mode = false;
bool first = true;
int delay = 0;
float heading = 0.00;
float headingThreshold = 0.1;
float distanceThreshold = 0.1;
float currentPosition[20];
float trustedPosition[20];
float targetPosition[20];
float offsetTargetPosition[20];

/*
/ Path planner class 
*/
class MeccanoidPathPlanner{
  
	public:
    MeccanoidPathPlanner(ros::Publisher pub){
		arduinoMotorControlPublisher = pub;
    };


    void modeCallback(const std_msgs::Bool::ConstPtr &msg){
		mode = msg->data;
        ROS_INFO("path planner: Setting mode to: %s",(mode)?"auto":"manual");
    }

	void obstaclePositionCallback(const std_msgs::Int16MultiArray::ConstPtr &msg){
			
		int obstacleLevel = msg->data[2];	
		float targetHeading;	

		ROS_INFO("path planner: Obstacle level: %d and mode: %s", obstacleLevel, (mode)?"true":"false");

		if(mode){
			switch(obstacleLevel){

				case 0: // no obstruction
					forward();
					/*targetHeading = calculateHeading(targetPosition);
					if(abs(heading - targetHeading) < headingThreshold){
						forward();
					}else{
						adjustHeading(targetHeading);
					}	*/

					ROS_INFO("No obstruction: currentHeading %.3f, targetHeading %.3f",heading, targetHeading);
					break;
				
				case 1: // partial obstruction
					offsetTargetPosition[0] = currentPosition[0] + (float) (msg->data[0] / 100.0);
					offsetTargetPosition[1] = currentPosition[1] + (float) (msg->data[1] / 100.0);
					targetHeading = calculateHeading(offsetTargetPosition);
					if(abs(heading - targetHeading) < headingThreshold){
						forward();
					}else{
						adjustHeading(targetHeading);
					}	
					ROS_INFO("partial obstruction: currentHeading %.3f, targetHeading %.3f",heading, targetHeading);
					break;
				
				case 2: // total obstruction
					targetHeading = calculateHeading(targetPosition);
					if(abs(heading - targetHeading) > headingThreshold){
						adjustHeading(targetHeading);
					}
					ROS_INFO("Total obstruction: currentHeading %.3f, targetHeading %.3f",heading, targetHeading);
					break;

				default:
					stop();
			}
		}
		
		ROS_INFO("path planner: obstacle offset, x = %d, y = %d, case = %d",msg->data[0], msg->data[1],msg->data[2]);
	}	

    void positionCallback(const meccanoid_tx1::hedge_posConstPtr &msg){
		delay += 1;		
		currentPosition[0] = msg->x_m;
		currentPosition[1] = msg->y_m;
		if(first){
			forward();
			trustedPosition[0] = currentPosition[0];
			trustedPosition[1] = currentPosition[1];
			first = false;
		}

		/*if(distance() > distanceThreshold){
			ROS_INFO("Heading prior to update: %.1f",heading*180.0/3.1415);
			updateHeading();
			ROS_INFO("Heading post update: %.1f",heading*180.0/3.1415);
		}*/

	    if(heading < headingThreshold && delay > 10){ // Check Heading Treshold Instead of Distance Moved
			ROS_INFO("Heading prior to update: %.1f",heading*180.0/3.1415);
			updateHeading();
			ROS_INFO("Heading post update: %.1f",heading*180.0/3.1415);
		}
		//ROS_INFO("path planner: position: x=%.4f, y=%.4f, distance = %.5f", currentPosition[0], currentPosition[1], distance());
		//ROS_INFO("path planner: trusted position: x=%.4f, y=%.4f", trustedPosition[0], trustedPosition[1]);
    }


  private:
    ros::Publisher arduinoMotorControlPublisher;

	void adjustHeading(float targetHeading){
		if(heading > targetHeading){
			right();
		}else{
			left();
		}
	}

	float calculateHeading(float target[]){
		return calculateHeading(currentPosition, target);
	}

	float calculateHeading(float pos1[], float pos2[]){
		float dx,dy;
		dx = pos2[0] - pos1[0];
		dy = pos2[1] - pos1[1];
		return atan2f(dy,dx);
	}

	float distance(){
		float dx,dy;
		dx = trustedPosition[0] - currentPosition[0];
		dy = trustedPosition[1] - currentPosition[1];
		return sqrt(dx*dx + dy*dy);
	}

	void updateHeading(){
		heading = calculateHeading(trustedPosition,currentPosition);
		trustedPosition[0] = currentPosition[0];
		trustedPosition[1] = currentPosition[1];
	}
    

	std_msgs::Int8MultiArray message(int8_t l_dir, int8_t r_dir,
                                        int8_t l_break, int8_t r_break, 
                                        int8_t l_speed, int8_t r_speed){
        std_msgs::Int8MultiArray msg;
        msg.data.clear();
        msg.data.push_back(l_dir);
        //_l_dir = l_dir;
        msg.data.push_back(r_dir);
        //_r_dir = r_dir;
        msg.data.push_back(l_break);
        //_l_break = l_break;
        msg.data.push_back(r_break);
        //_r_break = r_break;
        msg.data.push_back(l_speed);
        //_l_speed = l_speed;
        msg.data.push_back(r_speed);
        //_r_speed = r_speed;
        return msg;
    }

    void forward(){
        ROS_INFO("<< forward >>");
        arduinoMotorControlPublisher.publish(message(1,1,0,0,255,255));
    }

    void backward(){
        ROS_INFO("<< backward >>");
        arduinoMotorControlPublisher.publish(message(0,0,0,0,255,255));
    }

    void left(){
        ROS_INFO("<< left >>");
        arduinoMotorControlPublisher.publish(message(0,1,0,0,255,255));
    }

	void forward_left(){
        ROS_INFO("<< forward left >>");
        arduinoMotorControlPublisher.publish(message(1,1,0,0,0,255));
    }

    void right(){
        ROS_INFO("<< right >>");
        arduinoMotorControlPublisher.publish(message(1,0,0,0,255,255));
    }

	void forward_right(){
        ROS_INFO("<< forward right >>");
        arduinoMotorControlPublisher.publish(message(1,1,0,0,225,0));
    }

    void stop(){
        ROS_INFO("<< stop >>");
        arduinoMotorControlPublisher.publish(message(1,1,1,1,0,0));
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
	ros::Publisher arduinoMotorControlPublisher = nodeHandle.advertise<std_msgs::Int8MultiArray>("motor_control_signal", 10);

    // set up path planner
    MeccanoidPathPlanner pathPlanner(arduinoMotorControlPublisher);

    // set up mode subscriber
    ros::Subscriber modeSubscriber = nodeHandle.subscribe("/operation_mode", 1, 
                                                  &MeccanoidPathPlanner::modeCallback, &pathPlanner);

	// set up obstacle position subscriber
    ros::Subscriber obstaclePositionSubscriber = nodeHandle.subscribe("/obstacle_avoidance/offsetxy", 1, 
                                         &MeccanoidPathPlanner::obstaclePositionCallback, &pathPlanner);

    // set up position subscriber
    ros::Subscriber positionSubscriber = nodeHandle.subscribe("/position", 1, 
                                         &MeccanoidPathPlanner::positionCallback, &pathPlanner);    
    // start ros blocking spin()
    ros::spin();

}
