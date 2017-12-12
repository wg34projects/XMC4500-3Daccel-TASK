#ifndef _3Daccel_out_library_h
#define _3Daccel_out_library_h

#include "3Daccel_app.h"
#include "lis3dh_library.h"

void protocolComplete(int16_t position6D, int16_t positionX, int16_t positionY, int16_t positionZ, uint8_t temperature);
void outputInit(void);
void ledSetting(uint8_t ledID, uint8_t ledState);
void pwm(double dutycycle);
void getDouble(char *input, double *numDouble);
void SysTick_Handler (void);
double pwmAngleCalc(int16_t positionX, int16_t positionY, int16_t positionZ);



#endif
