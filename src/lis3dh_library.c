#include "lis3dh_library.h"

uint8_t initMEMSsensor()
{
	uint8_t error = 0;

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

/*void configFREEfall()*/
/*{*/
/*	LIS3DH_WriteReg(0x20, 0x57);*/
/*	LIS3DH_WriteReg(0x21, 0x00);*/
/*	LIS3DH_WriteReg(0x25, 0x40);	*/
/*	LIS3DH_WriteReg(0x23, 0x00);*/
/*	LIS3DH_WriteReg(0x24, 0x02);*/
/*	LIS3DH_WriteReg(0x36, 0x16);*/
/*	LIS3DH_WriteReg(0x37, 0x03);*/
/*	LIS3DH_WriteReg(0x34, 0x95);*/
/*}*/

/*void getFREEfall()*/
/*{*/
/*	u8_t fall = 0;*/
/*	LIS3DH_ReadReg(0x35, &fall);*/

/*	printf("%d\n", fall);*/

/*	if ((fall & (1 << 6)) == 0)*/
/*	{*/
/*		printf("0\n");*/
/*	}*/
/*	else*/
/*	{*/
/*		printf("1\n");*/
/*	}*/

/*}*/

uint8_t configMEMSsensor()
{
	uint8_t error = 0;

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

	// internal temperature sensor
	if (LIS3DH_SetADCAux(MEMS_ENABLE) == 1)
	{
		printf("LIS3DH_SetADCAux done...");
	}
	else
	{
		error++;
		errorcount++;
	}

	if (LIS3DH_SetBDU(MEMS_ENABLE) == 1)
	{
		printf("LIS3DH_SetBDU done...\n");
	}
	else
	{
		error++;
		errorcount++;
	}

	if (LIS3DH_SetTemperature(MEMS_ENABLE) == 1)
	{
		printf("LIS3DH_SetTemperature done...\n");
	}
	else
	{
		error++;
		errorcount++;
	}
	
	return error;
}

uint8_t getTemperature()
{
	int8_t temperature = 0;

	if (LIS3DH_GetTempRaw(&temperature) != 1)
	{
		errorcount++;
	}

	return temperature;
}

uint8_t get6Dposition()
{
	uint8_t response = 0;

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

AXESRAWDATA getAxesRawData()
{
	uint8_t response = 0;
	uint8_t m = 1;
	uint8_t i = 0;
	AxesRaw_t data[m];
	AXESRAWDATA dataOut;
	dataOut.axisX = 0;
	dataOut.axisY = 0;
	dataOut.axisZ = 0;

	for (i = 0; i <= m; i++)
	{
		response = LIS3DH_GetAccAxesRaw(&data[i]);
		if(response != 1)
		{
			errorcount++;
		}
	}

	for (i = 0; i <= m; i++)
	{
		dataOut.axisX += data[i].AXIS_X;
		dataOut.axisY += data[i].AXIS_Y;
		dataOut.axisZ += data[i].AXIS_Z;
	}

	dataOut.axisX /= m;
	dataOut.axisY /= m;
	dataOut.axisZ /= m;

	return dataOut;	
}
