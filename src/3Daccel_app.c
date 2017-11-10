#include "3Daccel_app.h"

void SysTick_Handler (void)
{
    static uint32_t ticks = 0;
    static int32_t cnt = 0;

    ticks++;
    if (ticks == TICKS_WAIT)
    {
        ticks = 0;
		printf("\nerrorcount = %d | totalcount = %ld\n", errorcount, cnt);
    }
	cnt++;
}

int main (void)
{
    AxesRaw_t data;
	errorcount = 0;

    initRetargetSwo();

    _init_i2c1_ch0();

    printf("init done...\n");

    _init_uart0_ch0();
    SysTick_Config (SystemCoreClock / TICKS_PER_SECOND);

    //Inizialize MEMS Sensor
    //set ODR (turn ON device)
    response = LIS3DH_SetODR(LIS3DH_ODR_100Hz);
    if(response==1)
    {
        printf("LIS3DH_SetODR done...\n");
    }
	else
	{
		errorcount++;
	}

    //set PowerMode
    response = LIS3DH_SetMode(LIS3DH_NORMAL);
    if(response==1)
    {

        printf("LIS3DH_SetMode done...\n");
    }
	else
	{
		errorcount++;
	}

    //set Fullscale
    response = LIS3DH_SetFullScale(LIS3DH_FULLSCALE_2);
    if(response==1)
    {

        printf("LIS3DH_SetFullScale done...\n");
    }
	else
	{
		errorcount++;
	}

    //set axis Enable
    response = LIS3DH_SetAxis(LIS3DH_X_ENABLE | LIS3DH_Y_ENABLE | LIS3DH_Z_ENABLE);
    if(response==1)
    {
        printf("LIS3DH_SetAxis done...\n");
    }
	else
	{
		errorcount++;
	}

    while (1)
    {
        response = LIS3DH_GetAccAxesRaw(&data);
		if(response == 1)
		{
        	printf("X=%6d Y=%6d Z=%6d\r", data.AXIS_X, data.AXIS_Y, data.AXIS_Z);
			_uart_printf ("%d\r\n%d\r\n%d\r\n", data.AXIS_X, data.AXIS_Y, data.AXIS_Z);
		}
	else
	{
		errorcount++;
	}
    }
}
