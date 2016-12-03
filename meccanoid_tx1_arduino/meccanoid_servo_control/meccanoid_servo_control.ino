
#include <ros.h>

#include <std_msgs/String.h>
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

// position callback to set face location
void positionCallback(const std_msgs::Int8MultiArray& position_msg){
  positions[0] = position_msg.data[0];
  positions[1] = position_msg.data[1];
  
  if(positions[0] == 0x77 && positions[1] == 0x97){
     mb.setLEDColor(7,0,0,0);
  }else{
     mb.setLEDColor(0,7,0,0);
  }
 
  mb.setServoPosition(0,position_msg.data[0]);
  mb.setServoPosition(1,position_msg.data[1]);
  mb.communicate();
  /*
  byte diff = abs(positions[0] - currentPositions[0])/20.0;
  int i;
  for(i=0; i<splits; i++){
    mb.setServoPosition(0,currentPositions[0]+(diff*(i+1)));
    mb.communicate();
    delay(20);
  }
  
  currentPositions[0] = position_msg.data[0];
  currentPositions[1] = position_msg.data[1];
  */
 //setInCenterPosition();
}

void setInCenterPosition(){
  mb.setServoPosition(0,0x77);
  mb.setServoPosition(1,0x77);
  mb.communicate();
}

ros::Subscriber<std_msgs::Int8MultiArray> sub("/face_location_pos", positionCallback );


void setup()
{
  nh.initNode();
  setInCenterPosition();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(300);
}
