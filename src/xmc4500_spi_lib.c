/*
 * xmc4500_spi_driver.c
 *
 *  Created on: 21 Jul 2017
 *      Author: rbeneder
 */

#include <xmc4500_spi_lib.h>

/**
 * @brief SPI configuration structure
*/
XMC_SPI_CH_CONFIG_t spi_config = {
    .baudrate = 25000,
    .bus_mode = XMC_SPI_CH_BUS_MODE_MASTER,
    .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
    .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
};

/**
 * @brief GPIO configuration structure
*/
XMC_GPIO_CONFIG_t gpio_config;

/*!
 *  @brief This function configures the SPI interface to communicate with the
 *         MCP23S08 & the MCP3004
 *  @param none
 *  @return on success this function returns SPI_OK (0)
 */
uint8_t _init_spi2_ch0 (void)
{
    /*Initialize and Start SPI*/
    XMC_SPI_CH_Init (XMC_SPI2_CH0, &spi_config);

    /*Input source selected*/
    XMC_SPI_CH_SetInputSource (XMC_SPI2_CH0, XMC_SPI_CH_INPUT_DIN0,
                               USIC2_C0_DX0_P5_1);
    XMC_SPI_CH_EnableEvent (XMC_SPI2_CH0, XMC_SPI_CH_EVENT_STANDARD_RECEIVE);
    XMC_SPI_CH_Start (XMC_SPI2_CH0);

    /*GPIO configuration*/
    XMC_GPIO_SetMode (SPI_MOSI, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1);
    XMC_GPIO_SetMode (SPI_MISO, XMC_GPIO_MODE_INPUT_TRISTATE);
    XMC_GPIO_SetMode (SPI_SCLK, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1);

    gpio_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
    gpio_config.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
    gpio_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;

    XMC_GPIO_Init (SPI_SSEL, &gpio_config);
    XMC_GPIO_SetOutputHigh (SPI_SSEL);

    return SPI_OK;
}


/*!
 *  @brief This function writes data to a specific SPI channel
 *  @param channel ... SPI channel
 *		   spi_data .. byte which should be transmitted
 *  @return on success this function returns SPI_OK (0)
 */
uint8_t _spi_transmit (XMC_USIC_CH_t *const channel, uint8_t spi_data)
{
    XMC_ASSERT ("XMC_USIC_CH_Enable: channel not valid",
                XMC_USIC_IsChannelValid (channel));

    XMC_SPI_CH_Transmit (channel, spi_data, XMC_SPI_CH_MODE_STANDARD);
    while ( (XMC_SPI_CH_GetStatusFlag (channel) & XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION) == 0U);
    XMC_SPI_CH_ClearStatusFlag (channel, XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION);

    return SPI_OK;
}

/*!
 *  @brief This function reads data from a specific SPI channel
 *  @param channel ... SPI channel
 *  @return byte which was received and is valid
 */
uint8_t _spi_receive (XMC_USIC_CH_t *const channel)
{
    XMC_ASSERT ("XMC_USIC_CH_Enable: channel not valid",
                XMC_USIC_IsChannelValid (channel));

    /* edited @xmc_spi.c Line 186 */
    return XMC_SPI_CH_GetReceivedData (channel);
}

/*! EOF */
