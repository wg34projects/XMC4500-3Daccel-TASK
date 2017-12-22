#ifndef _servo_library_h
#define _servo_library_h

#include "3Daccel_app.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

void pwm(double dutycycle, uint8_t out);
void initServoPWM();

#endif
