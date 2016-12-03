#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/Int8MultiArray.h>
#include <math.h>

ros::NodeHandle  nh;
byte dirA, dirB, breakA, breakB, speedA = 0, speedB = 0;

const int MOTOR_A_DIRECTION_PIN = 12;
const int MOTOR_B_DIRECTION_PIN = 13;

const int MOTOR_A_BREAK_PIN = 9;
const int MOTOR_B_BREAK_PIN = 8;

const int MOTOR_A_SPEED_PIN = 3;
const int MOTOR_B_SPEED_PIN = 11;

// position callback to set motor speed
void motorControlCallback(const std_msgs::Int8MultiArray& motor_control_msg){
  dirA = motor_control_msg.data[0];
  dirB = motor_control_msg.data[1];
  breakA = motor_control_msg.data[2];
  breakB = motor_control_msg.data[3];
  speedA = motor_control_msg.data[4];
  speedB = motor_control_msg.data[5];
  
  updateMotorControl();
}

void updateMotorControl(){
  digitalWrite(MOTOR_A_DIRECTION_PIN,dirA);
  digitalWrite(MOTOR_B_DIRECTION_PIN,dirB);
  
  digitalWrite(MOTOR_A_BREAK_PIN,breakA);
  digitalWrite(MOTOR_B_BREAK_PIN,breakB);
  
  analogWrite(MOTOR_A_SPEED_PIN,speedA);
  analogWrite(MOTOR_B_SPEED_PIN,speedB);
}

ros::Subscriber<std_msgs::Int8MultiArray> sub("/motor_control_signal", motorControlCallback );

void setup(){
  pinMode(MOTOR_A_DIRECTION_PIN,OUTPUT); // init motor channel A
  pinMode(MOTOR_A_BREAK_PIN,OUTPUT); // init break channel A

  pinMode(MOTOR_B_DIRECTION_PIN,OUTPUT); // init motor channel B
  pinMode(MOTOR_B_BREAK_PIN,OUTPUT); // init break channel B
  
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(300);
}
