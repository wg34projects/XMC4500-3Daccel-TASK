/**
 * @file		3Daccel_app.h
 * @version		v1.0
 * @date		Nov 2017
 * @author		Egermann, Resch
 *
 * @brief		3Daccel app header
 */

#ifndef _3Daccel_app_
#define _3Daccel_app_

typedef struct axesRawdata AXESRAWDATA;

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "3Daccel_out_library.h"
#include "lis3dh_library.h"
#include "servo_library.h"
#include "xmc4500_uart_lib.h"
#include "xmc4500_i2c_lib.h"
#include "GPIO.h"
#include "debug_lib.h"

#define SYSTEMTICKDIVIDER 1000
#define SENSORTICKS 10
#define GDIVIDER 8190.0
#define PI 3.141592654

#define PRESCALER 8
#define COUNTER 9375

#define SERUPLO0 3.00
#define SERVOUPCENTER 7.50
#define SERVOUOLINEAR 0.050

#define SERVOLO0 3.00
#define SERVOLOCENTER 7.50
#define SERVOLOLINEAR 0.050

#define RXBUFFERSIZE 64
#define LED1 P1_0
#define DEBUG 0
#define BUTTON1 P1_14
#define BUTTON2 P1_15
#define BUTTON1INT 14
#define BUTTON2INT 15
#define CBSIZE 10

struct axesRawdata
{
	uint16_t axisX;
	uint16_t axisY;
	uint16_t axisZ;
};

AXESRAWDATA readAxes;
uint8_t errorcount;
uint8_t position, old_position;
uint8_t direction;
uint8_t temperature;
uint8_t statisticSend, servoEnable;
uint8_t buttonSend;
uint32_t packagesSent;
double signal1, signal2;
uint8_t full, empty;
uint8_t inix, outix;
uint8_t cb[CBSIZE];
uint8_t button1pressed, button2pressed;

#endif

/** EOF **/
