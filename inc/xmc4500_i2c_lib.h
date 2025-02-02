/*
 * xmc4500_i2c_lib.h
 *
 *  Created on: 25 Jul 2017
 *      Author: rbeneder
 */

#ifndef INC_XMC4500_I2C_LIB_H_
#define INC_XMC4500_I2C_LIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <xmc_i2c.h>
#include <xmc_gpio.h>
#include <xmc_usic.h>

// defines sensor adress

#define LIS3DH_ADR 0x18
#define LIS3DH_RD_ADR (LIS3DH_ADR<<1)

// function prototypes

uint8_t _init_i2c1_ch0(void);
uint8_t _i2c_xfer(uint8_t id, uint8_t reg_addr, uint8_t i2c_data, _Bool rd_wr);

#endif /* INC_XMC4500_I2C_LIB_H_ */
