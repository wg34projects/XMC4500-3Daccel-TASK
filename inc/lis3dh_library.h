/**
 * @file		lis3dh_library.h
 * @version		v1.0
 * @date		Jan 2018
 * @author		Egermann, Resch
 *
 * @brief		lis3dh library header
 */

#ifndef _lis3dh_library_h
#define _lis3dh_library_h

#include "lis3dh_driver.h"
#include <stdint.h>
#include <stdio.h>

// typedef and struct definition

typedef struct axesRawdata AXESRAWDATA;

struct axesRawdata
{
    int16_t axisX;
    int16_t axisY;
    int16_t axisZ;
};

// global variables

uint8_t errorcount;
uint8_t position, old_position;
uint8_t direction;

// function prototypes

uint8_t initMEMSsensor();
uint8_t configMEMSsensor();
uint8_t get6Dposition();
AXESRAWDATA getAxesRawData();

#endif

/** EOF **/
