#include "3Daccel_out_library.h"

void protocolComplete(int16_t position6D, int16_t positionX, int16_t positionY, int16_t positionZ, uint8_t temperature)
{
	char string6D[8][6] = {"#USX,", "#UDX,", "#DSX,", "#DDX,", "#TOP,", "#BOT,", "#XXX,", "#FAL,"};
	char send[RX_BUFFER_SIZE];

	memset (&send, 0, sizeof (send));

	if (statisticSend == 1)
	{
		if (sprintf(send, "#STA,%10lu,%3d$\n", packagesSent, errorcount) < 0)
		{
			errorcount++;
		}
		else
		{
#if DEBUGO
			printf("send %s", send);
#endif
			_uart_printf("%s", send);
			packagesSent++;
		}
		statisticSend = 0;
		return;
	}
	else if (buttonSend == 1)
	{
		if (sprintf(send, "#BUT,1$\n") < 0)
		{
			errorcount++;
		}
		else
		{
#if DEBUGO
			printf("send %s", send);
#endif
			_uart_printf("%s", send);
			packagesSent++;
		}
		buttonSend = 0;
		return;
	}
	else if (buttonSend == 2)
	{
		if (sprintf(send, "#BUT,2$\n") < 0)
		{
			errorcount++;
		}
		else
		{
#if DEBUGO
			printf("send %s", send);
#endif
			_uart_printf("%s", send);
			packagesSent++;
		}
		buttonSend = 0;
		return;
	}
	else
	{	
		if (sprintf(send, "%s%7d%s%7d%s%7d%s%02d$\n", string6D[position6D], positionX, ",", positionY, ",", positionZ, ",", temperature* 2 + 6) < 0)
		{
			errorcount++;
		}
		else
		{
#if DEBUGO
			printf("send %s", send);
#endif
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

void pwmAngleCalc(int16_t positionX, int16_t positionY, int16_t positionZ)
{
	double roll, pitch;
	double pi = 3.141592654;
	double divider = 8190.0;
	double gX, gY, gZ;

	gX = positionX/divider;
	gY = positionY/divider;
	gZ = positionZ/divider;

	roll = atan(gY/(sqrt((gX*gX)+(gZ*gZ)))) * 180 / pi;
	pitch = atan(gX/(sqrt((gY*gY)+(gZ*gZ)))) * 180 / pi;

	signal1 = (90.00+roll) * 0.045 + 3.00;
	signal2 = (90.00+pitch) * 0.045 + 3.05;

	signal1 = (int)(signal1 * 10000 + 0.5) / 10000.0;
	signal2 = (int)(signal2 * 10000 + 0.5) / 10000.0;
}

void SysTick_Handler (void)
{
    static uint32_t ticks = 0, howMuchTicks = 5;
	static uint8_t buttonIDpressed;

	readButtonDebounce();

	if (circularGet(&buttonIDpressed))
    {
		switch (buttonIDpressed)
		{
			case BUTTON1INT:
			{
				printf("button 1\n");
				buttonSend = 1;
				break;
			}
			case BUTTON2INT:
			{
				printf("button 2\n");
				buttonSend = 2;
	            break;
			}
			default:
			{
				buttonSend = 0;
				break;
			}
		}
	}

	ticks++;
	if(ticks == howMuchTicks)
	{
		// get temperature
		temperature = getTemperature(&temperature);
		// get 6D Position
		direction = get6Dposition();
		// get raw data
		readAxes = getAxesRawData();
		// calculate angle for servo output
		pwmAngleCalc(readAxes.axisX, readAxes.axisY, readAxes.axisZ);
/*		getFREEfall();*/
		ticks = 0;
	}

	if (servoEnable == 1)
	{
		// set servo
		pwm(signal1, 0);
		pwm(signal2, 1);
	}
	else
	{
		pwm(7.00, 0);
		pwm(7.00, 1);
	}
}

/**
 * @brief read buttons debounce from Mr. Horauer
 */
void readButtonDebounce()
{
    if ((XMC_GPIO_GetInput(BUTTON1) == 0) && (button1pressed == 0))
    {
        button1pressed = 1;
    }
    if ((XMC_GPIO_GetInput(BUTTON1) == 0) && (button1pressed == 1))
    {
        button1pressed = 2;
    }
    if ((XMC_GPIO_GetInput(BUTTON1) == 1) && (button1pressed == 2))
    {
        if (circularAdd(BUTTON1INT) == 1)
        {
            button1pressed = 0;
        }
    }

    if ((XMC_GPIO_GetInput(BUTTON2) == 0) && (button2pressed == 0))
    {
        button2pressed = 1;
    }
    if ((XMC_GPIO_GetInput(BUTTON2) == 0) && (button2pressed == 1))
    {
        button2pressed = 2;
    }
    if ((XMC_GPIO_GetInput(BUTTON2) == 1) && (button2pressed == 2))
    {
        if (circularAdd(BUTTON2INT) == 1)
        {
            button2pressed = 0;
        }
    }
}

/**
 * @brief start values for circular buffer
 */
void circularInit()
{
    inix = 0;
    outix = 0;
    full = 0;
    empty = 1;
}

/**
 * @brief initialize input GPIOs
 */
void inputInit()
{
    XMC_GPIO_CONFIG_t config_in;
    config_in.mode = XMC_GPIO_MODE_INPUT_INVERTED_PULL_UP;
    XMC_GPIO_Init(BUTTON1, &config_in);
    XMC_GPIO_Init(BUTTON2, &config_in);

    // initialize global variables
    button1pressed = 0;
    button2pressed = 0;
    button1state = 0;
    button2state = 0;
}

/**
 * @brief  add element to circular buffer
 * @param  8 bit value for buffer
 * @return 1 if OK, 0 if KO
 */
uint8_t circularAdd (uint8_t item)
{
    if (full)
    {
        return 0;
    }
    inix = (inix + 1) % CBSIZE;
    cb[inix] = item;
    if (inix == outix)
    {
        full = 1;
    }
    empty = 0;
    return 1;
}

/**
 * @brief read element from circular buffer
 * @param pointer to the 8-bit value
 * @return 1 if OK, 0 if KO
 */
uint8_t circularGet (uint8_t *pItem)
{
    if (empty)
    {
        return 0;
    }
    outix = (outix + 1) % CBSIZE;
    *pItem = cb[outix];
    if (outix == inix)
    {
        empty = 1;
    }
    full = 0;
    return 1;
}
