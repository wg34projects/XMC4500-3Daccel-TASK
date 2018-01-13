/**
 * @file		3Daccel_out_driver.h
 * @version		v1.0
 * @date		Jan 2018
 * @author		Egermann, Resch
 *
 * @brief		3Daccel out driver header
 */

#ifndef _3Daccel_out_driver_h
#define _3Daccel_out_driver_h

#include <stdint.h>
#include <xmc_gpio.h>

#define LED1 P1_0			// LED GPIO
#define BUTTON1 P1_14		// BUTTON1 GPIO
#define BUTTON1INT 14
#define BUTTON2 P1_15		// BUTTON2 GPIO^
#define BUTTON2INT 15

// function prototypes

void outputInitXMC(void);
void ledSettingXMC(uint8_t ledState);
void readButtonDebounceXMC();
void inputInitXMC();

// globals

uint8_t button1pressed, button2pressed;

#endif

/** EOF **/
