#include "3Daccel_out_library.h"

void protocolComplete(int16_t position6D, int16_t positionX, int16_t positionY, int16_t positionZ, uint8_t temperature)
{
	char string6D[8][6] = {"#USX,", "#UDX,", "#DSX,", "#DDX,", "#TOP,", "#BOT,", "#XXX,", "#FAL,"};
	char send[RX_BUFFER_SIZE];

	memset (&send, 0, sizeof (send));
	
/*	if (statisticSend == 10)*/
/*	{*/
/*		if (sprintf(send, "#STA,%10lu,%3d$\n", packagesSent, errorcount) < 0)*/
/*		{*/
/*			errorcount++;*/
/*		}*/
/*		else*/
/*		{*/
/*			_uart_printf("%s", send);*/
/*			ledSetting(1, 3);*/
/*			packagesSent++;*/
/*			statisticSend = 0;*/
/*		}*/
/*	}*/
/*	else*/
	{
		if (sprintf(send, "%s%7d%s%7d%s%7d%s%02d$\n", string6D[position6D], positionX, ",", positionY, ",", positionZ, ",", temperature* 2 + 6) < 0)
		{
			errorcount++;
		}
		else
		{
			_uart_printf("%s", send);
			ledSetting(0, 3);
			packagesSent++;
		}
	}
}

void getDouble(char *input, double *numDouble)
{
    long double number = 0;
    char *pointToEnd = NULL;

    number = strtod(input, &pointToEnd);
    if(*pointToEnd != '\0')
    {
        return;
    }
    else
    {
        *numDouble = (double)number;
    }
}

void outputInit(void)
{
    XMC_GPIO_CONFIG_t config_out;
    config_out.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
    config_out.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
    config_out.output_strength = XMC_GPIO_OUTPUT_STRENGTH_WEAK;
    XMC_GPIO_Init(LED1, &config_out);
/*    XMC_GPIO_Init(LED2, &config_out);*/
}

void ledSetting(uint8_t ledID, uint8_t ledState)
{
	switch (ledID)
	{
		case 0:
		{
			if (ledState == 0)
			{
				XMC_GPIO_SetOutputLow(XMC_GPIO_PORT1, 0);
			}
			else if (ledState == 1)
			{
				XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT1, 0);
			}
			else
			{
				XMC_GPIO_ToggleOutput(LED1);
			}
			break;
		}
		case 1:
		{
			if (ledState == 0)
			{
				XMC_GPIO_SetOutputLow(XMC_GPIO_PORT1, 1);
			}
			else if (ledState == 1)
			{
				XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT1, 1);
			}
			else
			{
				XMC_GPIO_ToggleOutput(LED2);
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

void pwm(double dutycycle)
{
	pwmXMC(dutycycle);
}

double pwmAngleCalc(int16_t positionX, int16_t positionY, int16_t positionZ)
{
	double pitch, pitchOut;
//	double roll;
	double pi = 3.141592654;
	double divider = 8190.0;
	double gX, gY, gZ;

	gX = positionX/divider;
	gY = positionY/divider;
	gZ = positionZ/divider;

	pitch = atan(gX/(sqrt((gY*gY)+(gZ*gZ)))) * 180 / pi;
//	roll = atan(gY/(sqrt((gX*gX)+(gZ*gZ)))) * 180 / pi;

	pitchOut = (90.00+pitch) * 0.05 + 3.00;

	return pitchOut;
}

void SysTick_Handler (void)
{
    static uint32_t ticks = 0, howMuchTicks = 1000;
	double steps = 0.266666, up = 11.00, lo = 3.00;

    ticks++;

    if (ticks == howMuchTicks)
    {
		if (dir == 0)
		{
			signal = signal + steps;
			if (signal >= up)
			{
				signal = up;
				dir = 1;
			}
		}
		else
		{
			signal = signal - steps;
			if (signal <= lo)
			{
				signal = lo;
				dir = 0;
			}
		}
		ticks = 0;
    }
}
