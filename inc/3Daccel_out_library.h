/**
 * @file		3Daccel_out_library.h
 * @version		v1.0
 * @date		Jan 2018
 * @author		Egermann, Resch
 *
 * @brief		3Daccel out library header
 */

#ifndef _3Daccel_out_library_h
#define _3Daccel_out_library_h

#include "3Daccel_out_driver.h"
#include "lis3dh_library.h"
#include "servo_library.h"
#include "debug_lib.h"
#include "xmc4500_uart_lib.h"
#include <math.h>

#define CBSIZE 10					// size of ringbuffer
#define RXBUFFERSIZE 64				// size of UART receive buffer
#define GDIVIDER 8190.0				// divider to convert raw sensor values, presetting 4G
#define PI 3.141592654

// see README.md for description of the values as defined below
				
#define SERUPLO0 3.00				// upper servo -90° PWM dutycycle
#define SERVOUPCENTER 7.50			// upper servo 0° PWM dutycycle
#define SERVOUOLINEAR 0.050			// upper servo linear factor
#define SERVOLO0 3.00				// lower servo -90° PWM dutycycle
#define SERVOLOCENTER 7.50			// lower servo 0° PWM dutycycle
#define SERVOLOLINEAR 0.050			// lower servo linear factor
#define PITCHCORRECTPOS 0.05294		// pitch angle correction value

#define SENSORTICKS 10				// every 10 ticks - with presetting systemtick every 10ms sensor request
#define PWMAVERAGE 5				// averaging value
#define ANGAVERAGE 3.5				// threshold value
#define RNDFACTOR 100.0				// round to 0.01
#define SYSTEMTICKDIVIDER 1000		// systick every ms
#define DEBUG 1						// debug messages

// function prototypes

void initGlobals();
void protocolComplete(uint16_t position6D, int16_t positionX, int16_t positionY, int16_t positionZ);
void outputInit(void);
void ledSetting(uint8_t ledState);
void getDouble(char *input, double *numDouble);
void SysTick_Handler (void);
void pwmAngleCalc(int16_t positionX, int16_t positionY, int16_t positionZ);
uint8_t circularAdd (uint8_t item);
uint8_t circularGet (uint8_t *pItem);
void readButtonDebounce();
void inputInit();

// globals

AXESRAWDATA readAxes;
uint8_t full, empty;
uint8_t inix, outix;
uint8_t cb[CBSIZE];
uint8_t statisticSend, servoEnable;
uint8_t buttonSend;
uint8_t connection;
uint8_t averageChoice;
uint32_t startup;
uint32_t packagesSent;
double signal1, signal2;

#endif

/** EOF **/
