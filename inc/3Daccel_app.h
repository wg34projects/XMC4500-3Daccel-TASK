/**
 * @file     3Daccel_app.h
 * @version  v0.1
 * @date     Nov 2017
 * @author   Werner Egermeister & Helmut Resch
 *
 * @brief    3Daccel app header
 */

#ifndef _3Daccel_app_
#define _3Daccel_app_

#include "lis3dh_driver.h"
#include "servo_driver.h"
#include "xmc4500_i2c_lib.h"
#include <xmc4500_uart_lib.h>
#include <debug_lib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 100
#define RX_BUFFER_SIZE 64
#define LED1 P1_0
#define LED2 P1_1
#define DEBUG 1

struct axesRawdata
{
	uint16_t axisX;
	uint16_t axisY;
	uint16_t axisZ;
};

typedef struct axesRawdata AXESRAWDATA;

uint8_t response;
uint8_t errorcount;
uint8_t position, old_position, direction;
uint32_t packagesSent;
uint8_t statisticSend, servoEnable;
double signal;
AXESRAWDATA readAxes;
uint8_t direction;
int8_t temperature;

#endif
