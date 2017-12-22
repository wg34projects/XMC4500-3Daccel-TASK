#ifndef _servo_driver_h
#define _servo_driver_h

#include "3Daccel_app.h"
#include "GPIO.h"

void initServoPWMXMC();
uint8_t pwmXMC(double dutycycle, uint8_t out);

#endif
