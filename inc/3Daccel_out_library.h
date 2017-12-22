#ifndef _3Daccel_out_library_h
#define _3Daccel_out_library_h

#include "3Daccel_app.h"
#include "lis3dh_library.h"
#include "servo_library.h"

void protocolComplete(int16_t position6D, int16_t positionX, int16_t positionY, int16_t positionZ, uint8_t temperature);
void outputInit(void);
void ledSetting(uint8_t ledID, uint8_t ledState);
void getDouble(char *input, double *numDouble);
void SysTick_Handler (void);
void pwmAngleCalc(int16_t positionX, int16_t positionY, int16_t positionZ);
uint8_t circularAdd (uint8_t item);
uint8_t circularGet (uint8_t *pItem);
void readButtonDebounce();
void circularInit();
void inputInit();

#endif
