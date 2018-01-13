/**
 * @file		servo_library.h
 * @version		v1.0
 * @date		Jan 2018
 * @author		Egermann, Resch
 *
 * @brief		servo library header
 */

#ifndef _servo_library_h
#define _servo_library_h

#include "servo_driver.h"

// function prototypes

void initServoPWM();
uint8_t pwm(double dutycycle, uint8_t out);

#endif

/** EOF **/
