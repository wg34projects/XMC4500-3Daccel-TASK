/**
 * @file		lis3dh_library.5
 * @version		v1.0
 * @date		Nov 2017
 * @author		Egermann, Resch
 *
 * @brief		lis3dh library header
 */

#ifndef _lis3dh_library_h
#define _lis3dh_library_h

#include "3Daccel_app.h"
#include "lis3dh_driver.h"

uint8_t initMEMSsensor();
uint8_t configMEMSsensor();
uint8_t getTemperature();
uint8_t get6Dposition();
void configFREEfall();
void getFREEfall();
AXESRAWDATA getAxesRawData();

#endif

/** EOF **/
