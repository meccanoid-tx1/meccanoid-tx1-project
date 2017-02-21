/*
 * rosserial Servo Control Example
 *
 * This sketch demonstrates the control of hobby R/C servos
 * using ROS and the arduiono
 * 
 * For the full tutorial write up, visit
 * www.ros.org/wiki/rosserial_arduino_demos
 *
 * For more information on the Arduino Servo Library
 * Checkout :
 * http://www.arduino.cc/en/Reference/Servo
 */

#include "Arduino.h"
#include <MeccaBrain.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;

const int pwnPin1 = 9;
const int pwnPin2 = 10;
MeccaBrain chain1(pwnPin1);
MeccaBrain chain2(pwnPin2);

//Callback function - when subscriber recieves an "Empty" message, execute the following
void servo_cb( const std_msgs::Empty& cmd_msg){

  //Sweep the first servo from 0 -> 180 -> 0
  //sweep();

  //Wave-routine for arm one
   raiseShoulder();
   delay(500);
   elbow();
   delay(500);
   //This should wave 3 times
   wave();
   delay(500);
   lowerShoulder();
   delay(500);

   //Wave-routine for arm two
    raiseShoulderTwo();
    delay(500);
    elbowTwo();
    delay(500);
    //This should wave 3 times
    waveTwo();
    delay(500);
    lowerShoulderTwo();
    delay(500);

  //Toggles the LED  
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}

ros::Subscriber<std_msgs::Empty> sub("servo", servo_cb);

//Used for sweep
int pos = 0;

void setup(){
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);   
}

void loop(){
  nh.spinOnce();
  delay(300);
}


//---------------------------------------------------------------------
//Sweeps from 0 -> 180 -> 0 degrees
void sweep() {
  chain1.setServoPosition(1, 255);
  chain1.communicate();
  delay(1500);

  
  chain1.setServoColor(0, 0xF7);
  chain1.setServoColor(2, 0xF7);
  chain1.communicate();
  delay(1000);
  
  for (pos = 0; pos <= 240; pos += 10) {
      chain1.setServoPosition(0, pos);
      chain1.setServoPosition(2, pos);
      chain1.communicate();
  }


  chain1.setServoColor(0, 0xF1);
  chain1.setServoColor(2, 0xF1);
  chain1.communicate();
  delay(1000);
  

  for (pos = 240; pos >= 0; pos -= 10) {
      chain1.setServoPosition(0, pos);
      chain1.setServoPosition(2, pos);
      chain1.communicate();
      //delay(1);
  }

  chain1.setServoColor(0, 0xF4);
  chain1.setServoColor(2, 0xF4);
  chain1.communicate();
  delay(1000);
}
//-----------------------------------------------------------------------------

//Wave-function för arm 1

void raiseShoulder() {

    int pos = 0;
    //setToLIMAndGetPos(0)
    
    for (pos = 0; pos <= 128; pos += 10) {
      chain1.setServoPosition(0,pos);
      chain1.communicate();
      delay(20);
    }

    //RÖD
    chain1.setServoColor(0, 0xF1);
    chain1.communicate();
    delay(500);
}

void elbow() {

    int pos = 0;
    
    //chain = c;
    for (pos = setToLIMAndGetPos(1); pos <= 128; pos += 10) {
      chain1.setServoPosition(1, pos);
      chain1.communicate();
      delay(10);
    }

    //Någon oklar färg
    chain1.setServoColor(1, 0xF3);
    chain1.communicate();
    delay(500);
}

void wave() {

  int pos = 0;
  int i = 0;
  for (i = 0; i <= 2; i++) {
    for (pos = 0; pos <= 128; pos += 10) {
      chain1.setServoPosition(2, pos);
      chain1.communicate();
      delay(15); 
    }

    for (pos = 128; pos <= 0; pos -= 10) {
      chain1.setServoPosition(2, pos);
      chain1.communicate();
      delay(15);
    }
    //delay(200);
  }

  //Lila
  chain1.setServoColor(2, 0xF5);
  chain1.communicate();
  delay(500);

}


void lowerShoulder() {

  int pos1 = 0;
  int pos2 = 0;
  int pos3 = 0;
  
  for (pos1 = setToLIMAndGetPos(2); pos1 <= 128; pos1 += 10) {
     chain1.setServoPosition(2, pos1);
     chain1.communicate();
     delay(20);
  }
  //128
  //setToLIMAndGetPos(1)
  for (pos2 = setToLIMAndGetPos(1); pos2 >= 0; pos2 -= 10) {
     chain1.setServoPosition(1, pos2);
     chain1.communicate();
     delay(20);
  }

  //128
  for (pos3 = setToLIMAndGetPos(0); pos3 <= 255; pos3 +=10) {
  
    chain1.setServoPosition(0, pos3);
    chain1.communicate();
    delay(20);
  }

  chain1.setServoColor(0, 0xF7);
  chain1.setServoColor(1, 0xF7);
  chain1.setServoColor(2, 0xF7);
  chain1.communicate();
  delay(500);
  //c = c;
  /* Gammal kod
  chain1.setServoPosition(2,128);
  chain1.communicate();
  delay(600);
  chain1.setServoPosition(1,24);
  chain1.communicate();
  delay(600);
  chain1.setServoPosition(0,232);
  chain1.communicate();
  delay(600);
  */
}

//Sets servo to LIM , allowing it to return its position. Then calls getServoPosition.
int setToLIMAndGetPos (int servoNum) {
  chain1.setServotoLIM(servoNum);
  int pos = chain1.getServoPosition(servoNum);
  chain1.communicate();
  delay(500);
  return pos;
}

//------------------------------------------------------
//Andra armen

void raiseShoulderTwo() {

    int pos = 0;
    //setToLIMAndGetPos(0)
    
    for (pos = 0; pos <= 128; pos += 10) {
      chain2.setServoPosition(0,pos);
      chain2.communicate();
      delay(20);
    }

    //RÖD
    chain2.setServoColor(0, 0xF1);
    chain2.communicate();
    delay(500);
}

void elbowTwo() {

    int pos = 0;
    
    //chain = c;
    for (pos = setToLIMAndGetPos(1); pos <= 128; pos += 10) {
      chain2.setServoPosition(1, pos);
      chain2.communicate();
      delay(10);
    }

    //Någon oklar färg
    chain2.setServoColor(1, 0xF3);
    chain2.communicate();
    delay(500);
}

void waveTwo() {

  int pos = 0;
  int i = 0;
  for (i = 0; i <= 2; i++) {
    for (pos = 0; pos <= 128; pos += 10) {
      chain2.setServoPosition(2, pos);
      chain2.communicate();
      delay(15); 
    }

    for (pos = 128; pos <= 0; pos -= 10) {
      chain2.setServoPosition(2, pos);
      chain2.communicate();
      delay(15);
    }
    //delay(200);
  }

  //Lila
  chain2.setServoColor(2, 0xF5);
  chain2.communicate();
  delay(500);

}


void lowerShoulderTwo() {

  int pos1 = 0;
  int pos2 = 0;
  int pos3 = 0;
  
  for (pos1 = setToLIMAndGetPos(2); pos1 <= 128; pos1 += 10) {
     chain2.setServoPosition(2, pos1);
     chain2.communicate();
     delay(20);
  }
  //128
  //setToLIMAndGetPos(1)
  for (pos2 = setToLIMAndGetPos(1); pos2 >= 0; pos2 -= 10) {
     chain2.setServoPosition(1, pos2);
     chain2.communicate();
     delay(20);
  }

  //128
  for (pos3 = setToLIMAndGetPos(0); pos3 <= 255; pos3 +=10) {
  
    chain2.setServoPosition(0, pos3);
    chain2.communicate();
    delay(20);
  }

  chain2.setServoColor(0, 0xF7);
  chain2.setServoColor(1, 0xF7);
  chain2.setServoColor(2, 0xF7);
  chain2.communicate();
  delay(500);
  //c = c;
  /* Gammal kod
  chain1.setServoPosition(2,128);
  chain1.communicate();
  delay(600);
  chain1.setServoPosition(1,24);
  chain1.communicate();
  delay(600);
  chain1.setServoPosition(0,232);
  chain1.communicate();
  delay(600);
  */
}


