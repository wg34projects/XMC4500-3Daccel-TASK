#include "3Daccel_app.h"

void SysTick_Handler (void)
{
    static uint32_t ticks = 0;
    static int32_t cnt = 0;

    ticks++;
    if (ticks == TICKS_WAIT)
    {
        ticks = 0;
		printf("\nerrorcount6D = %d | errorcount = %d | totalcount = %ld\n", errorcount6D, errorcount, cnt);
    }
	cnt++;
}

int main (void)
{
    AxesRaw_t data;
	errorcount = 0, errorcount6D = 0;
	uint8_t position=0, old_position=0;

    initRetargetSwo();

    _init_i2c1_ch0();

    printf("init done...\n");

    _init_uart0_ch0();
    SysTick_Config (SystemCoreClock / TICKS_PER_SECOND);

    //Inizialize MEMS Sensor
    //set ODR (turn ON device)
    response = LIS3DH_SetODR(LIS3DH_ODR_100Hz);
    if(response == 1)
    {
        printf("LIS3DH_SetODR done...\n");
    }
	else
	{
		errorcount++;
	}

    //set PowerMode
    response = LIS3DH_SetMode(LIS3DH_NORMAL);
    if(response == 1)
    {

        printf("LIS3DH_SetMode done...\n");
    }
	else
	{
		errorcount++;
	}

    //set Fullscale
    response = LIS3DH_SetFullScale(LIS3DH_FULLSCALE_2);
    if(response == 1)
    {

        printf("LIS3DH_SetFullScale done...\n");
    }
	else
	{
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
		errorcount++;
	}

	//configure Mems Sensor
	//set Interrupt Threshold 
	response = LIS3DH_SetInt1Threshold(20);
	if(response == 1)
	{
    	printf("LIS3DH_SetInt1Thershold done...\n");
	}
	//set Interrupt configuration (all enabled)
	response = LIS3DH_SetIntConfiguration(LIS3DH_INT1_ZHIE_ENABLE | LIS3DH_INT1_ZLIE_ENABLE |
			   LIS3DH_INT1_YHIE_ENABLE | LIS3DH_INT1_YLIE_ENABLE |
			   LIS3DH_INT1_XHIE_ENABLE | LIS3DH_INT1_XLIE_ENABLE ); 
	if(response == 1)
	{
		printf("LIS3DH_SetIntConfiguration done...\n");
  	}
	 //set Interrupt Mode
	response = LIS3DH_SetIntMode(LIS3DH_INT_MODE_6D_POSITION);
	if(response == 1)
	{
		printf("LIS3DH_SetIntMode done...\n");
    }

	while(1)
	{
		//get raw data
		response = LIS3DH_GetAccAxesRaw(&data);
		if(response == 1)
		{
        	printf("X=%6d Y=%6d Z=%6d\r", data.AXIS_X, data.AXIS_Y, data.AXIS_Z);
			_uart_printf ("%d\r\n%d\r\n%d\r\n", data.AXIS_X, data.AXIS_Y, data.AXIS_Z);
		}
		//get 6D Position
  		response = LIS3DH_Get6DPosition(&position);
  		if((response == 1) && (old_position != position))
		{
		    switch (position)
			{
				case LIS3DH_UP_SX:
				{
					printf("\nposition = UP_SX  \n");   	
					break;
				}
				case LIS3DH_UP_DX:
				{
					printf("\nposition = UP_DX  \n");
					break;
				}
				case LIS3DH_DW_SX:
				{
					printf("\nposition = DW_SX  \n");
					break;
				}
				case LIS3DH_DW_DX:
				{
					printf("\nposition = DW_DX  \n");
					break; 
				}
				case LIS3DH_TOP:    
				{
					printf("\nposition = TOP    \n");
					break; 
				}
				case LIS3DH_BOTTOM: 
				{
					printf("\nposition = BOTTOM \n");   	
					break; 
				}
				default:
				{
					printf("\nposition = unknown\n");
					break;
				}
    		}
		}
		else if(response != 1)
		{
			errorcount6D++;
		}
		old_position = position;
  }
}