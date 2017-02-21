/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include "MeccaBrain.h"


const int pwmPin = 9;

MeccaBrain chain1(pwmPin);

//Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  //myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  delay(2000);
 
}

void loop() {


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
      //delay(1);
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

  //chain1.setServoColor(0, 0xFF);
  //chain1.communicate();

  
  /*for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  */
  
}

