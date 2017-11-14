#ifndef _3Daccel_out_library_h
#define _3Daccel_out_library_h

#include "3Daccel_app.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t protocolComplete(int16_t position6D, int16_t positionX, int16_t positionY, int16_t positionZ, int8_t temperature);

#endif
