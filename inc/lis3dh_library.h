#ifndef _lis3dh_library_h
#define _lis3dh_library_h

#include "3Daccel_app.h"

uint8_t initMEMSsensor();
uint8_t configMEMSsensor();
uint8_t getTemperature();
uint8_t get6Dposition();
AXESRAWDATA getAxesRawData();

#endif
