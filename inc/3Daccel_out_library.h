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

#define CBSIZE 10
#define RXBUFFERSIZE 64
#define GDIVIDER 8190.0
#define PI 3.141592654
#define SERUPLO0 3.00
#define SERVOUPCENTER 7.50
#define SERVOUOLINEAR 0.050
#define SERVOLO0 3.00
#define SERVOLOCENTER 7.50
#define SERVOLOLINEAR 0.050
#define PITCHCORRECTPOS 0.05294
#define BUTTON1 P1_14
#define BUTTON2 P1_15
#define BUTTON1INT 14
#define BUTTON2INT 15
#define SENSORTICKS 10
#define PWMAVERAGE 5
#define RNDFACTOR 100.0
#define SYSTEMTICKDIVIDER 1000
#define DEBUG 0

void initGlobals();
void protocolComplete(int16_t position6D, int16_t positionX, int16_t positionY, int16_t positionZ);
void outputInit(void);
void ledSetting(uint8_t ledState);
void getDouble(char *input, double *numDouble);
void SysTick_Handler (void);
void pwmAngleCalc(int16_t positionX, int16_t positionY, int16_t positionZ);
uint8_t circularAdd (uint8_t item);
uint8_t circularGet (uint8_t *pItem);
void readButtonDebounce();
void inputInit();

AXESRAWDATA readAxes;
uint8_t full, empty;
uint8_t inix, outix;
uint8_t cb[CBSIZE];
uint8_t statisticSend, servoEnable;
uint8_t buttonSend;
uint32_t packagesSent;
double signal1, signal2;

#endif

/** EOF **/
