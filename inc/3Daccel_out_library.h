#ifndef _3Daccel_out_library_h
#define _3Daccel_out_library_h

#include "3Daccel_app.h"

void protocolComplete(int16_t position6D, int16_t positionX, int16_t positionY, int16_t positionZ, uint8_t temperature);
void outputInit(void);
void ledSetting(uint8_t ledID, uint8_t ledState);
void SysTick_Handler (void);

#endif
