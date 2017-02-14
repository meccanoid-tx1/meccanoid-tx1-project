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
 
}

void loop() {

 chain1.setServoPosition(0, 255);
 chain1.communicate();
 delay(1000);


 chain1.setServoPosition(1, 255);
 chain1.setServoPosition(1, 0xC2);
 chain1.communicate();
 delay(1000);
 chain1.setServoPosition(1, 0);
 
 
 
 
 
 
/* 
 chain1.setServoPosition(0, 255);
 chain1.communicate();
 delay(1000);

 chain1.setServoPosition(1, 0);
 chain1.communicate();
 delay(1000);
 chain1.setServoPosition(1, 255);
 chain1.communicate();
 delay(1000);

 chain1.setServoPosition(2, 0);
 chain1.communicate();
 delay(1000);
 chain1.setServoPosition(2, 255);
 chain1.communicate();
 delay(1000);

 chain1.setServoPosition(3, 0);
 chain1.communicate();
 delay(1000);
 chain1.setServoPosition(3, 255);
 chain1.communicate();
 delay(1000);
*/
}
