/**
 * @file		3Daccel_app.c
 * @version		v1.0
 * @date		Nov 2017
 * @author		Egermann, Resch
 *
 * @mainpage	I2C sensor task 3D accelerometer BEL3
 * @brief		BEL3 task I2C sensor with GUI <br>
 *				Libraries for Debug, UART and I2C used as
 *				provided on CIS without changes, thanks!<br>
 */

#include "3Daccel_app.h"

/**
 * @brief	main routine 
 *		  
 */
int main (void)
{
	char rxBuff[RXBUFFERSIZE];

	// init receive buffer	
	memset (&rxBuff, 0, sizeof (rxBuff));

	// init values for globals
	initGlobals();

	// init DEBUG, UART, I2C, PWM
    initRetargetSwo();
    _init_uart0_ch0();
    _init_i2c1_ch0();
	initServoPWM();

	// center both servo
	pwm(SERVOUPCENTER, 0);
	pwm(SERVOLOCENTER, 1);

	// init LED output
	outputInit();
	ledSetting(0);

	// init BUTTONS
	inputInit();

#if DEBUG
    printf("DEBUG+I2C+UART+PWM+LED+BUTTON init done...\n");
#endif

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
		}
	}

	// set up SysTick
    SysTick_Config (SystemCoreClock / SYSTEMTICKDIVIDER);

	// main loop
	while(1)
	{
		// clear buffer and receie incoming data
		memset (&rxBuff, 0, sizeof (rxBuff));
		_uart_get_string (rxBuff);

#if DEBUG
		printf("received %s\n", rxBuff);
#endif

        if (strncmp(rxBuff, "#REQ,", strlen(rxBuff)) == 0)
        {
			protocolComplete(direction, readAxes.axisX, readAxes.axisY, readAxes.axisZ, temperature);
		}
		else if (strncmp(rxBuff, "#END,", strlen(rxBuff)) == 0)
		{
			ledSetting(0);
		}
		else if (strncmp(rxBuff, "#CON,", strlen(rxBuff)) == 0)
		{
			ledSetting(1);
		}
		else if (strncmp(rxBuff, "#SER,f", strlen(rxBuff)) == 0)
		{
			servoEnable = 0;
		}
		else if (strncmp(rxBuff, "#SER,n", strlen(rxBuff)) == 0)
		{
			servoEnable = 1;
		}
		else if (strncmp(rxBuff, "#STA,", strlen(rxBuff)) == 0)
		{
			statisticSend = 1;
		}
		else
		{
			continue;
		}
	}
}

/** EOF **/
