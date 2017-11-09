/*
 * xmc4500_i2c_lib.c
 *
 *  Created on: 25 Jul 2017
 *      Author: rbeneder
 */

#include <xmc4500_i2c_lib.h>

XMC_GPIO_CONFIG_t i2c_sda = {
    .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
    .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
};

XMC_GPIO_CONFIG_t i2c_scl = {
    .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
    .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
};


XMC_I2C_CH_CONFIG_t i2c_cfg = {
    .baudrate = 100000U,
};

/*!
 *  @brief This function configures the I2C interface to communicate via pins
 *         P0_5 & P0_11
 *  @param none
 *  @return on success this function returns 0
 */
uint8_t _init_i2c1_ch0 (void)
{
    XMC_I2C_CH_Init (XMC_I2C1_CH0, &i2c_cfg);
    XMC_I2C_CH_SetInputSource (XMC_I2C1_CH0, XMC_I2C_CH_INPUT_SDA, USIC1_C0_DX0_P0_5);
    XMC_I2C_CH_SetInputSource (XMC_I2C1_CH0, XMC_I2C_CH_INPUT_SCL, USIC1_C0_DX1_SCLKOUT);
    XMC_I2C_CH_Start (XMC_I2C1_CH0);

    XMC_GPIO_Init (P0_11, &i2c_scl);
    XMC_GPIO_Init (P0_5, &i2c_sda);


    return 0;
}

/*!
 *  @brief This function writes/reads data to a specific I2C channel
 *  @param id       ... I2C device ID
 *         reg_addr ... I2C register address of the device
 *         i2c_data ... I2C data value
 *         rd_wr    ... I2C Read/Write direction
 *  @return read-value on a I2C read request or return write-value on I2C write
 *          request
 */
uint8_t _i2c_xfer (uint8_t id, uint8_t reg_addr, uint8_t i2c_data, _Bool rd_wr)
{
    XMC_USIC_CH_t *channel;
    char _tmp_i2c_recv_ = 0;
    uint8_t id_tmp = 0;

    channel = XMC_I2C1_CH0;
/*	printf("\n");*/

    id_tmp = LIS3DH_RD_ADR;

    XMC_I2C_CH_MasterStart (channel, id_tmp, XMC_I2C_CH_CMD_WRITE);
    while ( (XMC_I2C_CH_GetStatusFlag (channel) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U) {
        /* wait for ACK */
/*		printf("ACK1\r");*/
    }
    XMC_I2C_CH_ClearStatusFlag (channel, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

    XMC_I2C_CH_MasterTransmit (channel, reg_addr);
    while ( (XMC_I2C_CH_GetStatusFlag (channel) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U) {
        /* wait for ACK */
/*		printf("ACK2\r");*/
    }
    XMC_I2C_CH_ClearStatusFlag (channel, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

    if (rd_wr) {
        /* Read from REG */
        XMC_I2C_CH_MasterRepeatedStart (channel, id_tmp, XMC_I2C_CH_CMD_READ);
        while ( (XMC_I2C_CH_GetStatusFlag (channel) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U) {
            /* wait for ACK */
/*			printf("ACK3\r");*/
        }
        XMC_I2C_CH_ClearStatusFlag (channel, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

        XMC_I2C_CH_MasterReceiveNack (channel);

        while ( (XMC_USIC_CH_GetReceiveBufferStatus (channel) !=
                 (uint32_t) XMC_USIC_CH_RBUF_STATUS_DATA_VALID1) && ( (uint32_t) XMC_USIC_CH_GetReceiveBufferStatus (channel)
                         != (uint32_t) XMC_USIC_CH_RBUF_STATUS_DATA_VALID0));

        _tmp_i2c_recv_ = XMC_I2C_CH_GetReceivedData (channel);

        XMC_I2C_CH_MasterStop (channel);

        return _tmp_i2c_recv_;
    } else {
        /* Write to REG */
        XMC_I2C_CH_MasterTransmit (channel, i2c_data);
        while ( (XMC_I2C_CH_GetStatusFlag (channel) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U) {
            /* wait for ACK */
/*			printf("ACK4\rS");*/
        }
        XMC_I2C_CH_ClearStatusFlag (channel, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

        XMC_I2C_CH_MasterStop (channel);

        return i2c_data;
    }
}
