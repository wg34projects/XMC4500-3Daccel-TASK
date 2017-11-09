/*
 * xmc4500_spi_lib.h
 *
 *  Created on: 21 Jul 2017
 *      Author: rbeneder
 */

#ifndef INC_XMC4500_SPI_LIB_H_
#define INC_XMC4500_SPI_LIB_H_

#include "xmc_spi.h"
#include "xmc_gpio.h"
#include "errno.h"

#define SPI_MISO 	P5_1
#define SPI_MOSI 	P5_0
#define SPI_SCLK 	P5_2
#define SPI_SSEL 	P1_14

#define SPI_OK 		0x00

uint8_t _init_spi2_ch0(void);
uint8_t _spi_transmit(XMC_USIC_CH_t *const channel, uint8_t spi_data);
uint8_t _spi_receive(XMC_USIC_CH_t *const channel);

#endif /* INC_XMC4500_SPI_LIB_H_ */
