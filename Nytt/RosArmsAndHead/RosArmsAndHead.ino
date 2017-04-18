/*
  RosArmsAndHead
  Meccanoid Robot Bachelor Thesis 2017
  SSYX02-17-08
  Chalmers University of Technology - Gothenburg - Sweden
  All rights reserved.
  
  Arduino code used for communicating with
  servos (arms and bottom engines) on a meccanoid robot.
*/
#include "Arduino.h"
#include "MeccaBrain.h"
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/Int8MultiArray.h>

#include <MD23.h>
#include<Wire.h>

MD23 md23;

ros::NodeHandle nh;

const int pwnPin1 = 9; //left arm
const int pwnPin2 = 10; //right arm
MeccaBrain chain1(pwnPin1);
MeccaBrain chain2(pwnPin2);

//Used to control which part of the wave-routine should be executed.
//0 = Hold, 1 = Start, 2 = Elbow, 3 = Wave, 4 = Lower
int state = 0;

//Callback function - when subscriber recieves an "Empty" message, execute the following
void servo_cb( const std_msgs::Empty& cmd_msg){
    state = 1;
    stopEngines();
}

std_msgs::Empty empty_msg;

/*
  Publishers and subscribers
    waveDonePub - to indicate when the waving routine is done
    armSub - to trigger the wave when a face is detected
    startEngines - to control the bottom motors
*/

ros::Publisher waveDonePub("/wave_done", &empty_msg);
ros::Subscriber<std_msgs::Empty> armSub("servo", servo_cb);
ros::Publisher startEngines("/MotorControl", &empty_msg);
ros::Subscriber<std_msgs::Empty> motorSub("MotorControl", md23_cb);

//-----------------------------------------------------------------------------



//------------------------------------------------------
// Right arm


//Sets servo to LIM , allowing it to return its position. Then calls getServoPosition.
int setToLIMAndGetPos (int servoNum) {
  chain2.setServotoLIM(servoNum);
  int pos = chain2.getServoPosition(servoNum);
  chain2.communicate();
  delay(100);
  return pos;
}

/*
  Raises the shoulder of the robot by changing the first servos position
*/
void raiseShoulderTwo() {

    int pos = 255;
    //setToLIMAndGetPos(0)
    
    for (pos = 255; pos >= 128; pos -= 10) {
      chain2.setServoPosition(0,pos);
      chain2.communicate();
      //delay(10);
    }

    /*
      Set LED-color to red and change the state
    */
    chain2.setServoColor(0, 0xF1);
    chain2.communicate();
    delay(200);
    state = 2;
}
/*
  Raises the elbow by changing the position of the second servo
*/
void elbowTwo() {

    int pos = 0;
    
    //chain = c;
    for (pos = setToLIMAndGetPos(1); pos <= 150; pos += 20) {
      chain2.setServoPosition(1, pos);
      chain2.communicate();
      delay(10);
    }

    //Någon oklar färg
    chain2.setServoColor(1, 0xF3);
    chain2.communicate();
    delay(500);
    
    
    state = 3;
}

/*
  Makes the robot wave by changing the position of the third servo
  back and forth
*/
void waveTwo() {

  int pos = 255;
  int i = 0;
  for (i = 0; i <= 1; i++) {  //Number of waves
    for (pos = 128; pos <= 255; pos += 20) {
      chain2.setServoPosition(2, pos);
      chain2.communicate();
      delay(10);
    }
    
    for (pos = 255; pos >= 128; pos -= 20) {
      chain2.setServoPosition(2, pos);
      chain2.communicate();
      delay(10); 
    }
  }

  /*
    Changes the servocolor to purle
    and switch state
  */
  chain2.setServoColor(2, 0xF5);
  chain2.communicate();
  delay(200);
  
  state = 4;
}

/*
  This function is called when the robot has succesfully completed a wave
  It resets the state and publishes a message to waveDonePub, indicating to
  the face recognition node that it's ready to start recieving messages again.
*/
void waveDone() {
  waveDonePub.publish( &empty_msg);
  delay(100);
  state = 0;
  delay(200);
  
}
/*
  Lowers the shoulder
*/
void lowerShoulderTwo() {

  int pos1 = 0; // Servo two
  int pos2 = 0; // Servo 1
  int pos3 = 0; // Servo 0
  
  for (pos1 = setToLIMAndGetPos(2); pos1 >= 128; pos1 -= 20) {
     chain2.setServoPosition(2, pos1);
     chain2.communicate();
     //delay(10);
  }
  
  
  //128
  for (pos3 = setToLIMAndGetPos(0); pos3 >= 0; pos3 -=10) {
  
    chain2.setServoPosition(0, pos3);
    chain2.communicate();
    //delay(10);
  }
    
  //128 change to 255 resp 0 on servo 0 and 1 
  for (pos2 = 128; pos2 <= 255; pos2 += 10) {
     chain2.setServoPosition(1, pos2);
     chain2.communicate();
  }

  chain2.setServoColor(0, 0xF7);
  chain2.setServoColor(1, 0xF7);
  chain2.setServoColor(2, 0xF7);
  chain2.communicate();
  delay(200);
  
  //Arm succesfully lowered - wave routine complete  
  waveDone();

}

//-------------------------LEGS---------------------------------


/*
  Callback function for the lower motors.
  When a message is recieved on MotorControl or Servo,
  change the state to 1, ie. stop going forward and call
  on the wave routine.
*/
void md23_cb( const std_msgs::Empty& cmd_msg){
  
  state = 1;
  /*
  delay(1000);
  nh.spinOnce();
  fstop();
  delay(1000);
  nh.spinOnce();
  delay(1000);
  nh.spinOnce();
  delay(1000);
  nh.spinOnce();
  delay(1000);
  nh.spinOnce();
  delay(1000);
  nh.spinOnce();
  delay(1000);
  nh.spinOnce();
  delay(1000);
  nh.spinOnce();
  delay(1000);
  nh.spinOnce();
  */
}


/*
  Stops the lower motors
*/
void stopEngines() {
  //nh.spinOnce();
  fstop();
  /*delay(1000);
  nh.spinOnce();
  delay(1000);
  nh.spinOnce();
  delay(1000);
  nh.spinOnce();
  delay(1000);
  nh.spinOnce();
  */
  /*
  delay(1000);
  nh.spinOnce();
  delay(1000);
  nh.spinOnce();
  delay(1000);
  nh.spinOnce();
  delay(1000);
  nh.spinOnce();
  */
}


int i = 129;


/*
  Makes the robot go forward.
  When state is set to 0, this function is looped - 
  ie, this is the robots default state.
*/
void forward()
{
  /*
    Might need an acceleration-routine
  */
    
    while (state == 0){
      md23.setMotor1Speed(150); 
      md23.setMotor2Speed(150);
      nh.spinOnce();
    }
        
}

/*
  Makes the robot go backwards (speed < 128 = reverse)
*/
void backward()
{
   for (i; i>78; i--)
  {
    md23.setMotor1Speed(i); // slow forwad, first motor
    md23.setMotor2Speed(i);
    delay(100);
  }
  
}

void fstop()
{
 /*
   Stops both engines.
   Might need a braking-routine.
 */
  md23.setMotor1Speed(128); // stop the first motor
  md23.setMotor2Speed(128); // stop the second motor
  
}



//-----------------------SETUP AND LOOP-----------------------------


void setup(){
  
  nh.initNode(); 
  //state = 0;
  pinMode(13, OUTPUT);
  nh.subscribe(armSub);
  nh.advertise(waveDonePub);
  nh.advertise(startEngines);
  
  Wire.begin();
  nh.subscribe(motorSub);
  delay(500);
   
}

void loop(){
  delay(300);
  nh.spinOnce();
  
  /*
    State 0 : Go forward (default)
    State 1 -> 4 : Wave
  */
  switch (state) {
    case 0:
      forward();
      break;
    case 1:
      stopEngines();
      raiseShoulderTwo();
      delay(100);
      break;
     case 2:
       elbowTwo();
       delay(100);
       break;
     case 3:
       waveTwo();
       break;
     case 4:
       lowerShoulderTwo();
       break;
  }
  nh.spinOnce();  
}


