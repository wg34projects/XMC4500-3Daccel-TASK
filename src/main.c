#include <debug_lib.h>
#include <xmc4500_uart_lib.h>
#include "lis3dh_driver.h"
#include "xmc4500_i2c_lib.h"

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 500

#define RX_BUFFER_SIZE 64

uint8_t response;

void SysTick_Handler (void)
{
    static uint32_t ticks = 0;
    static int32_t cnt = 0;

    ticks++;
    if (ticks == TICKS_WAIT)
    {
        ticks = 0;
        cnt++;
    }
}

int main (void)
{
    AxesRaw_t data;

    initRetargetSwo();

    _init_i2c1_ch0();

    printf("init done...\n");

    _init_uart0_ch0();
    //SysTick_Config (SystemCoreClock / TICKS_PER_SECOND);

    //Inizialize MEMS Sensor
    //set ODR (turn ON device)
    response = LIS3DH_SetODR(LIS3DH_ODR_100Hz);
    if(response==1)
    {
        printf("LIS3DH_SetODR done...\n");
    }

    //set PowerMode
    response = LIS3DH_SetMode(LIS3DH_NORMAL);
    if(response==1)
    {

        printf("LIS3DH_SetMode done...\n");
    }

    //set Fullscale
    response = LIS3DH_SetFullScale(LIS3DH_FULLSCALE_2);
    if(response==1)
    {

        printf("LIS3DH_SetFullScale done...\n");
    }

    //set axis Enable
    response = LIS3DH_SetAxis(LIS3DH_X_ENABLE | LIS3DH_Y_ENABLE | LIS3DH_Z_ENABLE);
    if(response==1)
    {
        printf("LIS3DH_SetAxis done...\n");
    }

    while (1)
    {
        response = LIS3DH_GetAccAxesRaw(&data);
		if(response == 1)
		{
        	printf("X=%6d Y=%6d Z=%6d\n", data.AXIS_X, data.AXIS_Y, data.AXIS_Z);
			_uart_printf ("%d\r\n%d\r\n%d\r\n", data.AXIS_X, data.AXIS_Y, data.AXIS_Z);
		}
    }
}
