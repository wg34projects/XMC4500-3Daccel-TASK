/**
 * @file		servo_driver.h
 * @version		v1.0
 * @date		Jan 2018
 * @author		Egermann, Resch
 *
 * @brief		servo driver header
 */

#ifndef _servo_driver_h
#define _servo_driver_h

#include <stdint.h>
#include "GPIO.h"

// see README.md for prescaler calculation

#define PRESCALER 8			// prescaler
#define COUNTER 9375		// PWM counter value

// function prototypes

void initServoPWMXMC();
uint8_t pwmXMC(double dutycycle, uint8_t out);

#endif

/** EOF **/
