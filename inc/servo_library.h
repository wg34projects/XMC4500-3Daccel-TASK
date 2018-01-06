/**
 * @file		servo_library.h
 * @version		v1.0
 * @date		Nov 2017
 * @author		Egermann, Resch
 *
 * @brief		servo library header
 */

#ifndef _servo_library_h
#define _servo_library_h

#include "3Daccel_app.h"
#include "servo_driver.h"

void pwm(double dutycycle, uint8_t out);
void initServoPWM();

#endif

/** EOF **/
