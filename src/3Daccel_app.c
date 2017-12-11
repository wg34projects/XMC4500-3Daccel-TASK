#include "3Daccel_app.h"
#include "3Daccel_out_library.h"
#include "lis3dh_library.h"

int main (void)
{
	uint8_t direction = 6;
	int8_t temperature = 0;
	char rx_buff[RX_BUFFER_SIZE] = {0};
	char an_buff[RX_BUFFER_SIZE] = {0};
	AXESRAWDATA readAxes;
	
	errorcount = 0, packagesSent = 0, position = 0, old_position = 0;
	readAxes.axisX = 0, readAxes.axisY = 0, readAxes.axisZ = 0;
	statisticSend = 0;
	signal = 3.00;
	dir = 0;

	// init DEBUG, UART, I2C
    initRetargetSwo();
    _init_uart0_ch0();
    _init_i2c1_ch0();
	initServoPWM();
	

#if DEBUG
    printf("DEBUG+I2C+UART init done...\n");
#endif

	// init LED output
	outputInit();

	// set up SysTick
//    SysTick_Config (SystemCoreClock / 1000);

    // init MEMS
	while (1)
	{
		if (initMEMSsensor() == 0)
		{
#if DEBUG
			printf("MEMS init done...\n");
#endif
			break;
		}
		else
		{
#if DEBUG
			printf("Error MEMS init, retry...\n");
#endif
			ledSetting(0, 1);
		}
	}

	// config MEMS
	while (1)
	{
		if (configMEMSsensor() == 0)
		{
#if DEBUG
			printf("MEMS config done...\n");
#endif
			break;
		}
		else
		{
#if DEBUG
			printf("Error MEMS config, retry...\n");
#endif
			ledSetting(0, 1);
		}
	}

	pwm(signal);
	// main loop
	while(1)
	{
		pwm(signal);

		// clear buffer and receie incoming data
		memset (&rx_buff, 0, sizeof (rx_buff));
		memset (&an_buff, 0, sizeof (rx_buff));
		_uart_get_string (rx_buff);
#if DEBUG
		printf("received %s\n", rx_buff);
#endif

        if (strncmp(rx_buff, "#REQ,", strlen(rx_buff)) == 0)
        {
			// get temperature
			temperature = getTemperature(&temperature);

			// get 6D Position
	  		direction = get6Dposition();

			// get raw data
			readAxes = getAxesRawData();

			signal = pwmAngleCalc(readAxes.axisX, readAxes.axisY, readAxes.axisZ);

			protocolComplete(direction, readAxes.axisX, readAxes.axisY, readAxes.axisZ, temperature);
		}
		else if (strncmp(rx_buff, "#END,", strlen(rx_buff)) == 0)
		{
			ledSetting(0, 0);
/*			ledSetting(1, 0);*/
		}
		else if (strncmp(rx_buff, "#CON,", strlen(rx_buff)) == 0)
		{
			ledSetting(0, 1);
		}
		else if (strncmp(rx_buff, "#ANG,", strlen(rx_buff)) == 0)
		{
			strncpy(an_buff, rx_buff+5, strlen(an_buff));
			getDouble(an_buff, &signal);
			printf("%s %f", an_buff, signal);
		}
		else
		{
			continue;
		}
/*		statisticSend++;*/
	}
}
