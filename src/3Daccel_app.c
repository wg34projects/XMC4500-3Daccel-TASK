#include "3Daccel_app.h"
#include "3Daccel_out_library.h"
#include "lis3dh_library.h"

int main (void)
{

	char rx_buff[RX_BUFFER_SIZE] = {0};

	direction = 6;
	temperature = 0;
	errorcount = 0;
	packagesSent = 0;
	position = 0;
	old_position = 0;
	readAxes.axisX = 0;
	readAxes.axisY = 0;
	readAxes.axisZ = 0;
	statisticSend = 0;
	signal = 7.00;
	servoEnable = 0;

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

	// set up SysTick
    SysTick_Config (SystemCoreClock / 1000);

	// main loop
	while(1)
	{
		// clear buffer and receie incoming data
		memset (&rx_buff, 0, sizeof (rx_buff));
		_uart_get_string (rx_buff);
#if DEBUG
		printf("received %s\n", rx_buff);
#endif

/*		// get temperature*/
/*		temperature = getTemperature(&temperature);*/
/*		// get 6D Position*/
/*		direction = get6Dposition();*/
/*		// get raw data*/
/*		readAxes = getAxesRawData();*/
/*		// calculate angle for servo output*/
/*		signal = pwmAngleCalc(readAxes.axisX, readAxes.axisY, readAxes.axisZ);*/

        if (strncmp(rx_buff, "#REQ,", strlen(rx_buff)) == 0)
        {
			// send data over UART
			protocolComplete(direction, readAxes.axisX, readAxes.axisY, readAxes.axisZ, temperature);
		}
		else if (strncmp(rx_buff, "#END,", strlen(rx_buff)) == 0)
		{
			ledSetting(0, 0);
		}
		else if (strncmp(rx_buff, "#CON,", strlen(rx_buff)) == 0)
		{
			ledSetting(0, 1);
		}
		else if (strncmp(rx_buff, "#SER,", strlen(rx_buff)) == 0)
		{
			if (servoEnable == 0)
			{
				servoEnable = 1;
			}
			else
			{
				servoEnable = 0;
			}
		}
		else
		{
			continue;
		}
	}
}
