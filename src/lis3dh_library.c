/**
 * @file		lis3dh_library.c
 * @version		v1.0
 * @date		Jan 2018
 * @author		Egermann, Resch
 *
 * @brief		lis3dh library
 *
 */

#include "lis3dh_library.h"

/**
 * @brief	init MEMS sensor
 * @param	none
 * @return	amount of errors if some occurred
 *
 */
uint8_t initMEMSsensor()
{
    uint8_t error = 0;
    uint8_t response = 0;

    //set ODR (turn ON device)
    if(LIS3DH_SetODR(LIS3DH_ODR_100Hz) == 1)
    {
        printf("LIS3DH_SetODR done...\n");
    }
    else
    {
        error++;
        errorcount++;
    }

    //set PowerMode
    if(LIS3DH_SetMode(LIS3DH_NORMAL) == 1)
    {

        printf("LIS3DH_SetMode done...\n");
    }
    else
    {
        error++;
        errorcount++;
    }

    //set Fullscale
    if(LIS3DH_SetFullScale(LIS3DH_FULLSCALE_4) == 1)
    {

        printf("LIS3DH_SetFullScale done...\n");
    }
    else
    {
        error++;
        errorcount++;
    }

    //set axis Enable
    response = LIS3DH_SetAxis(LIS3DH_X_ENABLE | LIS3DH_Y_ENABLE | LIS3DH_Z_ENABLE);
    if(response == 1)
    {
        printf("LIS3DH_SetAxis done...\n");
    }
    else
    {
        error++;
        errorcount++;
    }

    return error;
}

/**
 * @brief	config MEMS sensor
 * @param	none
 * @return	amount of errors if some occurred
 *
 */
uint8_t configMEMSsensor()
{
    uint8_t error = 0;
    uint8_t response = 0;

    //set Interrupt Threshold
    if(LIS3DH_SetInt1Threshold(20) == 1)
    {
        printf("LIS3DH_SetInt1Thershold done...\n");
    }
    else
    {
        error++;
        errorcount++;
    }

    //set Interrupt configuration (all enabled)
    response = LIS3DH_SetIntConfiguration(LIS3DH_INT1_ZHIE_ENABLE | LIS3DH_INT1_ZLIE_ENABLE |
                                          LIS3DH_INT1_YHIE_ENABLE | LIS3DH_INT1_YLIE_ENABLE |
                                          LIS3DH_INT1_XHIE_ENABLE | LIS3DH_INT1_XLIE_ENABLE );
    if(response == 1)
    {
        printf("LIS3DH_SetIntConfiguration done...\n");
    }
    else
    {
        error++;
        errorcount++;
    }

    //set Interrupt Mode
    if(LIS3DH_SetIntMode(LIS3DH_INT_MODE_6D_POSITION) == 1)
    {
        printf("LIS3DH_SetIntMode done...\n");
    }
    else
    {
        error++;
        errorcount++;
    }

    return error;
}

/**
 * @brief	get 6D position
 * @param	none
 * @return	6D direction as integer 0 - 6
 *
 */
uint8_t get6Dposition()
{
    uint8_t response = 0;

    // request 6D position and set global variable

    response = LIS3DH_Get6DPosition(&position);

    if((response == 1) && (old_position != position))
    {
        switch (position)
        {
        case LIS3DH_UP_SX:
        {
            direction = 0;
            break;
        }
        case LIS3DH_UP_DX:
        {
            direction = 1;
            break;
        }
        case LIS3DH_DW_SX:
        {
            direction = 2;
            break;
        }
        case LIS3DH_DW_DX:
        {
            direction = 3;
            break;
        }
        case LIS3DH_TOP:
        {
            direction = 4;
            break;
        }
        case LIS3DH_BOTTOM:
        {
            direction = 5;
            break;
        }
        default:
        {
            direction = 6;
            errorcount++;
            break;
        }
        }
    }
    else if(response != 1)
    {
        errorcount++;
    }
    old_position = position;

    return direction;
}

/**
 * @brief	get axes acceleration raw data
 * @param	none
 * @return	acceleration data in structure
 *
 */
AXESRAWDATA getAxesRawData()
{
    uint8_t response = 0;
    AxesRaw_t data;
    AXESRAWDATA dataOut;
    dataOut.axisX = 0;
    dataOut.axisY = 0;
    dataOut.axisZ = 0;

    // request sensor data and add to struct

    response = LIS3DH_GetAccAxesRaw(&data);
    if(response != 1)
    {
        errorcount++;
    }

    dataOut.axisX = data.AXIS_X;
    dataOut.axisY = data.AXIS_Y;
    dataOut.axisZ = data.AXIS_Z;

    return dataOut;
}

/** EOF **/
