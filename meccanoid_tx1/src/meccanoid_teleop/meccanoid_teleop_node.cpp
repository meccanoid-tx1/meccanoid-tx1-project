#include <ros/ros.h>

#include <iostream>
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int8MultiArray.h"


class MeccanoidTeleop {

	public:
	MeccanoidTeleop(ros::Publisher pub){
		keyPublisher = pub;
	};

    bool teleoperate(){
        bool operate = true;

        switch(getkey()){
            case 119: // w
                forward();
                break;
            case 97: // a
                left();
                break;
            case 100: // d
                right();
                break;
            case 115: // s
                backward();
                break;
            case 113: // q
                stop();
                break;
            case 27: // ctrl+c
                operate = false;
                break;
            default:
                ROS_INFO("\nldir: %d, rdir: %d,\n lbreak: %d, rbreak: %d,\n lspeed: %d, rspeed: %d",
                         _l_dir, _r_dir, _l_break, _r_break, _l_speed, _r_speed);
        }
        return operate;
    }
	
	private:
	ros::Publisher keyPublisher;
    int8_t _l_dir;
    int8_t _r_dir;
    int8_t _l_break;
    int8_t _r_break;
    int8_t _l_speed;
    int8_t _r_speed;

    int getkey(){
        int character;
        struct termios orig_term_attr;
        struct termios new_term_attr;

        /* set the terminal to raw mode */
        tcgetattr(fileno(stdin), &orig_term_attr);
        memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
        new_term_attr.c_lflag &= ~(ECHO | ICANON);
        new_term_attr.c_cc[VTIME] = 0;
        new_term_attr.c_cc[VMIN] = 0;
        tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

        /* read a character from the stdin stream without blocking */
        /*   returns EOF (-1) if no character is available */
        character = fgetc(stdin);

        /* restore the original terminal attributes */
        tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

        return character;
    }

    std_msgs::Int8MultiArray message(int8_t l_dir, int8_t r_dir,
                                        int8_t l_break, int8_t r_break, 
                                        int8_t l_speed, int8_t r_speed){
        std_msgs::Int8MultiArray msg;
        msg.data.clear();
        msg.data.push_back(l_dir);
        _l_dir = l_dir;
        msg.data.push_back(r_dir);
        _r_dir = r_dir;
        msg.data.push_back(l_break);
        _l_break = l_break;
        msg.data.push_back(r_break);
        _r_break = r_break;
        msg.data.push_back(l_speed);
        _l_speed = l_speed;
        msg.data.push_back(r_speed);
        _r_speed = r_speed;
        return msg;
    }

    void forward(){
        ROS_INFO("<< forward >>");
        keyPublisher.publish(message(1,1,0,0,255,255));
    }

    void backward(){
        ROS_INFO("<< backward >>");
        keyPublisher.publish(message(0,0,0,0,255,255));
    }

    void left(){
        ROS_INFO("<< left >>");
        keyPublisher.publish(message(0,1,0,0,255,255));
    }

    void right(){
        ROS_INFO("<< right >>");
        keyPublisher.publish(message(1,0,0,0,255,255));
    }

    void stop(){
        ROS_INFO("<< stop >>");
        keyPublisher.publish(message(1,1,1,1,0,0));
    }
	
};



/*
/ Meccanoid teleop main
*/
int main(int argc, char **argv){
    // init ros
    ros::init(argc, argv, "meccanoid_teleop");
    ros::NodeHandle nodeHandle;
    ros::Publisher keyPublisher = nodeHandle.advertise<std_msgs::Int8MultiArray>("motor_control_signal", 10);
    ros::Rate loop_rate(10);

    MeccanoidTeleop *teleop = new MeccanoidTeleop(keyPublisher);

    while(ros::ok()){
        if(!teleop->teleoperate()){
            return 0;
        }
        ros::spinOnce();
        loop_rate.sleep();
    }
}
