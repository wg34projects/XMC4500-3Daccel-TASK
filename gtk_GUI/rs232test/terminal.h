#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <stdlib.h>
#include <inttypes.h>
#include <signal.h>
#include "rs232.h"

#define BAUD 115200
#define XMCBUFFER 64
#define OSBUFFER 4096
#define INPUT 1

int cport_nr;

#endif
