#ifndef _servo_driver_h
#define _servo_driver_h

#include "3Daccel_app.h"
#include "GPIO.h"

void initServoPWM();
uint8_t pwmXMC(double dutycycle);

#endif
