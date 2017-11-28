#include "3Daccel_app.h"
#include "3Daccel_out_library.h"

int main (void)
{
	uint8_t position = 0, old_position = 0, direction = 6;
	char rx_buff[RX_BUFFER_SIZE] = {0};
	AxesRaw_t data;
	i8_t temp = 0;
	
	errorcountRAW = 0, errorcount6D = 0, errorcountInternal = 0, errorcountSetup = 0;

    initRetargetSwo();

    _init_uart0_ch0();
    _init_i2c1_ch0();

    printf("I2C+UART init done...\n");

    SysTick_Config (SystemCoreClock / TICKS_PER_SECOND);

    //Inizialize MEMS Sensor

    //set ODR (turn ON device)
    if(LIS3DH_SetODR(LIS3DH_ODR_100Hz) == 1)
    {
        printf("LIS3DH_SetODR done...\n");
    }
	else
	{
		errorcountSetup++;
	}

    //set PowerMode
    if(LIS3DH_SetMode(LIS3DH_NORMAL) == 1)
    {

        printf("LIS3DH_SetMode done...\n");
    }
	else
	{
		errorcountSetup++;
	}

    //set Fullscale
    if(LIS3DH_SetFullScale(LIS3DH_FULLSCALE_2) == 1)
    {

        printf("LIS3DH_SetFullScale done...\n");
    }
	else
	{
		errorcountSetup++;
	}

    //set axis Enable
    response = LIS3DH_SetAxis(LIS3DH_X_ENABLE | LIS3DH_Y_ENABLE | LIS3DH_Z_ENABLE);
    if(response == 1)
    {
        printf("LIS3DH_SetAxis done...\n");
    }
	else
	{
		errorcountSetup++;
	}

	//configure Mems Sensor
	//set Interrupt Threshold 
	if(LIS3DH_SetInt1Threshold(20) == 1)
	{
    	printf("LIS3DH_SetInt1Thershold done...\n");
	}
	else
	{
		errorcountSetup++;
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
		errorcountSetup++;
	}

	 //set Interrupt Mode
	if(LIS3DH_SetIntMode(LIS3DH_INT_MODE_6D_POSITION) == 1)
	{
		printf("LIS3DH_SetIntMode done...\n");
    }
	else
	{
		errorcountSetup++;
	}

	// internal temperature sensor -- check accuracy!!!
	if (LIS3DH_SetADCAux(MEMS_ENABLE) == 1)
	{
		printf("LIS3DH_SetADCAux done...");
	}
	else
	{
		errorcountSetup++;
	}

	if (LIS3DH_SetBDU(MEMS_ENABLE) == 1)
	{
		printf("LIS3DH_SetBDU done...\n");
	}
	else
	{
		errorcountSetup++;
	}

	if (LIS3DH_SetTemperature(MEMS_ENABLE) == 1)
	{
		printf("LIS3DH_SetTemperature done...");
	}
	else
	{
		errorcountSetup++;
	}

	while(1)
	{
		memset (&rx_buff, 0, sizeof (rx_buff));
		_uart_get_string (rx_buff);

        if (strncmp(rx_buff, "REQUEST", strlen(rx_buff)) == 0)
        {
			// get temperature
			LIS3DH_GetTempRaw(&temp);

			//get 6D Position
	  		response = LIS3DH_Get6DPosition(&position);
	  		if((response == 1) && (old_position != position))
			{
				switch (position)
				{
					case LIS3DH_UP_SX:
					{
						printf("\nposition = UP_SX  \n");
						direction = 0;
						break;
					}
					case LIS3DH_UP_DX:
					{
						printf("\nposition = UP_DX  \n");
						direction = 1;
						break;
					}
					case LIS3DH_DW_SX:
					{
						printf("\nposition = DW_SX  \n");
						direction = 2;
						break;
					}
					case LIS3DH_DW_DX:
					{
						printf("\nposition = DW_DX  \n");
						direction = 3;
						break; 
					}
					case LIS3DH_TOP:    
					{
						printf("\nposition = TOP    \n");
						direction = 4;
						break; 
					}
					case LIS3DH_BOTTOM: 
					{
						printf("\nposition = BOTTOM \n");   
						direction = 5;
						break; 
					}
					default:
					{
						printf("\nposition = unknown\n");
						direction = 6;
						break;
					}
				}
			}
			else if(response != 1)
			{
				errorcount6D++;
			}
			old_position = position;

			//get raw data
			response = LIS3DH_GetAccAxesRaw(&data);
			if(response == 1)
			{
			   	printf("X=%6d Y=%6d Z=%6d\r", data.AXIS_X, data.AXIS_Y, data.AXIS_Z);
				protocolComplete(direction, data.AXIS_X, data.AXIS_Y, data.AXIS_Z, temp);
			}
			else
			{
				errorcountRAW++;
			}
		}
		else
		{
			continue;
		}
	}
}
