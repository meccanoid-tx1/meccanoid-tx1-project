#include <MeccaBrain.h>

//for Uno and like

const int pwmPin1=9;
const int pwmPin2=10;
const int pwmPin3=11;

//for Mega and like
//const int pwmPin1=44;
//const int pwmPin2=45;
//const int pwmPin3=46;

MeccaBrain chain1(pwmPin1); //each chain allows to plug up to 4 smart modules
MeccaBrain chain2(pwmPin2);
MeccaBrain chain3(pwmPin3);
 
void setup() {

  /*
  chain1.setServoPosition(0,255);
  chain1.communicate();
  delay(1000);

  chain1.setServoPosition(0,128);
  chain1.communicate();
  delay(1000);

  chain1.setServoPosition(0,0);
  chain1.communicate();
  delay(1000);
  */
 
}

void loop() {

   
   /*
    //Res axeln
    chain1.setServoPosition(0, 105);
    chain1.communicate();
    delay(500);
    
    //Räta ut armbåge
    chain1.setServoPosition(1, 128);
    chain1.communicate();
    delay(500);
    
    //Vinka
    chain1.setServoPosition(2, 0);
    chain1.communicate();
    delay(500);
    chain1.setServoPosition(2, 128);
    chain1.communicate();
    delay(500);
  */


    lowerShoulder();
    delay(1000);
    raiseShoulder();
    delay(1000);
    elbow();
    delay(1000);
    //This should wave 3 times
    wave();
    delay(500);
    lowerShoulder();
    delay(1000);
  
}

void raiseShoulder() {
    chain1.setServoPosition(0,105);
    chain1.communicate();
    delay(1500);
}

void elbow() {
    chain1.setServoPosition(1, 128);
    chain1.communicate();
    delay(1500);
  }

void wave() {
  chain1.setServoPosition(2,0);
  chain1.communicate();
  delay(400);
  chain1.setServoPosition(2,128);
  chain1.communicate();
  delay(400); 
   
  chain1.setServoPosition(2,0);
  chain1.communicate();
  delay(400);
  chain1.setServoPosition(2,128);
  chain1.communicate();
  delay(400); 
   
  chain1.setServoPosition(2,0);
  chain1.communicate();
  delay(400);
  chain1.setServoPosition(2,128);
  chain1.communicate();
  delay(400); 
  }

void lowerShoulder() {
  chain1.setServoPosition(2,128);
  chain1.communicate();
  delay(600);
  chain1.setServoPosition(1,0);
  chain1.communicate();
  delay(600);
  chain1.setServoPosition(0,255);
  chain1.communicate();
  delay(600);

  
  }
