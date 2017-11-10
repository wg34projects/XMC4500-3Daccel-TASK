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

#include <debug_lib.h>
#include <xmc4500_uart_lib.h>
#include "lis3dh_driver.h"
#include "xmc4500_i2c_lib.h"

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 5000

#define RX_BUFFER_SIZE 64

uint8_t response;
uint8_t errorcount, errorcount6D;

void SysTick_Handler (void);

#endif
