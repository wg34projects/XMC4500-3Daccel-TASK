#include "3Daccel_app.h"
#include "3Daccel_out_library.h"

void SysTick_Handler (void)
{
    static uint32_t ticks = 0;

    ticks++;
    if (ticks == TICKS_WAIT)
    {
        ticks = 0;
//		printf("\nerrorcountRAW = %d errorcount6D = %d | errorcountSETUP = %d | errorcountInternal = %d\n", errorcountRAW, errorcount6D, errorcountSetup, errorcountInternal);
    }
}

int main (void)
{
	uint8_t position = 0, old_position = 0, direction = 6;
	AxesRaw_t data;
	
	errorcountRAW = 0, errorcount6D = 0, errorcountInternal = 0, errorcountSetup = 0;

    initRetargetSwo();

    _init_uart0_ch0();
    _init_i2c1_ch0();

    printf("I2C+UART init done...\n");

    SysTick_Config (SystemCoreClock / TICKS_PER_SECOND);

    //Inizialize MEMS Sensor
    //set ODR (turn ON device)
    response = LIS3DH_SetODR(LIS3DH_ODR_25Hz);
    if(response == 1)
    {
        printf("LIS3DH_SetODR done...\n");
    }
	else
	{
		errorcountSetup++;
	}

    //set PowerMode
    response = LIS3DH_SetMode(LIS3DH_NORMAL);
    if(response == 1)
    {

        printf("LIS3DH_SetMode done...\n");
    }
	else
	{
		errorcountSetup++;
	}

    //set Fullscale
    response = LIS3DH_SetFullScale(LIS3DH_FULLSCALE_2);
    if(response == 1)
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
	response = LIS3DH_SetInt1Threshold(20);
	if(response == 1)
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
	response = LIS3DH_SetIntMode(LIS3DH_INT_MODE_6D_POSITION);
	if(response == 1)
	{
		printf("LIS3DH_SetIntMode done...\n");
    }
	else
	{
		errorcountSetup++;
	}

	while(1)
	{
		//get 6D Position
  		response = LIS3DH_Get6DPosition(&position);
  		if((response == 1) && (old_position != position))
		{
		    switch (position)
			{
				case LIS3DH_UP_SX:
				{
//					printf("\nposition = UP_SX  \n");
					direction = 0;
					break;
				}
				case LIS3DH_UP_DX:
				{
//					printf("\nposition = UP_DX  \n");
					direction = 1;
					break;
				}
				case LIS3DH_DW_SX:
				{
//					printf("\nposition = DW_SX  \n");
					direction = 2;
					break;
				}
				case LIS3DH_DW_DX:
				{
//					printf("\nposition = DW_DX  \n");
					direction = 3;
					break; 
				}
				case LIS3DH_TOP:    
				{
//					printf("\nposition = TOP    \n");
					direction = 4;
					break; 
				}
				case LIS3DH_BOTTOM: 
				{
//					printf("\nposition = BOTTOM \n");   
					direction = 5;
					break; 
				}
				default:
				{
//					printf("\nposition = unknown\n");
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
#if PROTOCOL
			protocolComplete(direction, data.AXIS_X, data.AXIS_Y, data.AXIS_Z);
#else
			_uart_printf ("%d\r\n%d\r\n%d\r\n", data.AXIS_X, data.AXIS_Y, data.AXIS_Z);
#endif
		}
		else
		{
			errorcountRAW++;
		}
	}
}
