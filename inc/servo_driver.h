/**
 * @file		servo_driver.h
 * @version		v1.0
 * @date		Nov 2017
 * @author		Egermann, Resch
 *
 * @brief		servo driver header
 */

#ifndef _servo_driver_h
#define _servo_driver_h

#include "3Daccel_app.h"

void initServoPWMXMC();
uint8_t pwmXMC(double dutycycle, uint8_t out);

#endif

/** EOF **/
