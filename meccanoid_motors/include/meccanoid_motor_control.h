#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 64

struct MeccanoidMotorControl{
    int active;
    int numMotors;
    //TODO: add necessary stuff
};

struct MeccanoidMotorControl* createMeccanoidMotorControl();
void destroyMeccanoidMotorControl(struct MeccanoidMotorControl* motorController);
void activateMeccanoidMotorControl(struct MeccanoidMotorControl* motorController);
void deactivateMeccanoidMotorControl(struct MeccanoidMotorControl* motorController);

typedef unsigned int jetsonGPIO;
typedef unsigned int pinDirection;
typedef unsigned int pinValue;

enum pinDirections {
	inputPin  = 0,
	outputPin = 1
};

enum pinValues {
    low = 0,
    high = 1,
    off = 0,  // synonym for things like lights
    on = 1
};

enum jetsonGPIONumber {
    gpio57  =  57,    // J3A1 - Pin 50
	gpio160 = 160,	  // J3A2 - Pin 40	
	gpio161 = 161,    // J3A2 - Pin 43
	gpio162 = 162,    // J3A2 - Pin 46
	gpio163 = 163,    // J3A2 - Pin 49
	gpio164 = 164,    // J3A2 - Pin 52
	gpio165 = 165,    // J3A2 - Pin 55
	gpio166 = 166     // J3A2 - Pin 58
};

enum jetsonTX1GPIONumber {
       gpio36 = 36,      // J21 - Pin 32 - Unused - AO_DMIC_IN_CLK
       gpio37 = 37,      // J21 - Pin 16 - Unused - AO_DMIC_IN_DAT
       gpio38 = 38,      // J21 - Pin 13 - Bidir  - GPIO20/AUD_INT
       gpio63 = 63,      // J21 - Pin 33 - Bidir  - GPIO11_AP_WAKE_BT
       gpio184 = 184,    // J21 - Pin 18 - Input  - GPIO16_MDM_WAKE_AP
       gpio186 = 186,    // J21 - Pin 31 - Input  - GPIO9_MOTION_INT
       gpio187 = 187,    // J21 - Pin 37 - Output - GPIO8_ALS_PROX_INT
       gpio219 = 219,    // J21 - Pin 29 - Output - GPIO19_AUD_RST
};

int gpioExport ( jetsonGPIO gpio ) ;
int gpioUnexport ( jetsonGPIO gpio ) ;
int gpioSetDirection ( jetsonGPIO, pinDirection out_flag ) ;
int gpioSetValue ( jetsonGPIO gpio, pinValue value ) ;
int gpioGetValue ( jetsonGPIO gpio, unsigned int *value ) ;
int gpioSetEdge ( jetsonGPIO gpio, char *edge ) ;
int gpioOpen ( jetsonGPIO gpio ) ;
int gpioClose ( int fileDescriptor ) ;
int gpioActiveLow ( jetsonGPIO gpio, unsigned int value ) ;

#ifdef __cplusplus
}
#endif