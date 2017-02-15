/*
 * meccanoid_armservo_control
 * Bachelor Thesis Spring 2017
 * 
 * 
 * Enable arm connected with arduino to wave once triggered 
 * by a facial recognition, using kinect/ZED-camera. 
 * Code for waving arm is implemented in ArmTest.ino

*/

#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/Int8MultiArray.h>

#include <math.h>
#include "MeccaBrain.h"

int servoPin = 3;
MeccaBrain mb = MeccaBrain(servoPin);
ros::NodeHandle  nh;
byte positions[2] = {0x77, 0x97}; // 0x00 = full clockwise, 0xEF = full counter clockwise 
byte currentPositions[2] = {0x77, 0x97};
byte ledColor[] = {0x07,0x00,0x00,0x00}; // r,g,b,fade
int splits = 20;



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
