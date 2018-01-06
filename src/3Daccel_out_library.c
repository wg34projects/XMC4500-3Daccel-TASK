/**
 * @file		3Daccel_out_library.c
 * @version		v1.0
 * @date		Jan 2018
 * @author		Egermann, Resch
 *
 * @brief		3Daccel out library
 */

#include "3Daccel_out_library.h"

/**
 * @brief	init global variables
 * @param	none
 * @return	none
 *
 */
void initGlobals()
{
    readAxes.axisX = 0;
    readAxes.axisY = 0;
    readAxes.axisZ = 0;
    direction = 6;
    errorcount = 0;
    packagesSent = 0;
    position = 0;
    old_position = 0;
    signal1 = 0.00;
    signal2 = 0.00;
    button1pressed = 0;
    button2pressed = 0;
    statisticSend = 0;
    servoEnable = 0;
    buttonSend = 0;
    inix = 0;
    outix = 0;
    full = 0;
    empty = 1;
}

/**
 * @brief	function to init LED output
 * @param	none
 * @return	none
 *
 */
void outputInit(void)
{
    XMC_GPIO_CONFIG_t config_out;
    config_out.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
    config_out.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
    config_out.output_strength = XMC_GPIO_OUTPUT_STRENGTH_WEAK;
    XMC_GPIO_Init(LED1, &config_out);
}

/**
 * @brief	SysTick
 * @param	none
 * @return	none
 *
 */
void SysTick_Handler (void)
{
    static uint32_t ticks = 0;
    static uint8_t buttonIDpressed;
	static uint8_t i = 0;
	static double smoothSignal1 = 0.0, smoothSignal2 = 0.0;

    // read buttons and fill circular buffer

    readButtonDebounce();

    if (circularGet(&buttonIDpressed))
    {
        switch (buttonIDpressed)
        {
        case BUTTON1INT:
        {
#if DEBUG
            printf("button 1 pressed\n");
#endif
            buttonSend = 1;
            break;
        }
        case BUTTON2INT:
        {
#if DEBUG
            printf("button 2 pressed\n");
#endif
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
    if(ticks == SENSORTICKS)
    {
        // get 6D Position
        direction = get6Dposition();
        // get raw data
        readAxes = getAxesRawData();
        // calculate servo output
        pwmAngleCalc(readAxes.axisX, readAxes.axisY, readAxes.axisZ);

        ticks = 0;
    }

    if (servoEnable == 1)
    {
		smoothSignal1 += signal1;
		smoothSignal2 += signal2;
		i++;
		if (i == PWMAVERAGE)
		{
	        // set servo
			smoothSignal1 /= PWMAVERAGE;
			smoothSignal2 /= PWMAVERAGE;
    	    pwm(smoothSignal1, 0);
    	    pwm(smoothSignal2, 1);
			smoothSignal1 = 0.0;
			smoothSignal2 = 0.0;
			i = 0;
		}
    }
    else
    {
        // reset servo
        pwm(SERVOUPCENTER, 0);
        pwm(SERVOLOCENTER, 1);
    }
}

/**
 * @brief	send data to PC and GUI
 * @param	6D position <br>
 *			raw X acceleration value <br>
 *			raw Y acceleration value <br>
 *			raw Z acceleration value <br>
 *			temperature value <br>
 * @return	none
 *
 */
void protocolComplete(int16_t position6D, int16_t positionX, int16_t positionY, int16_t positionZ)
{
    char string6D[8][6] = {"#USX,", "#UDX,", "#DSX,", "#DDX,", "#TOP,", "#BOT,", "#XXX,", "#FAL,"};
    char send[RXBUFFERSIZE];

    memset (&send, 0, sizeof (send));

    if (statisticSend == 1)
    {
        // send statistic package if requested
        if (sprintf(send, "#STA,%10lu,%3d$\n", packagesSent, errorcount) < 0)
        {
            errorcount++;
        }
        else
        {
#if DEBUG
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
        // send button 1 pressed
        if (sprintf(send, "#BUT,1$\n") < 0)
        {
            errorcount++;
        }
        else
        {
#if DEBUG
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
        // send button 2 pressed
        if (sprintf(send, "#BUT,2$\n") < 0)
        {
            errorcount++;
        }
        else
        {
#if DEBUG
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
        // send acceleration data
        if (sprintf(send, "%s%7d%s%7d%s%7d$\n", string6D[position6D], positionX, ",", positionY, ",", positionZ) < 0)
        {
            errorcount++;
        }
        else
        {
#if DEBUG
            printf("send %s", send);
#endif
            _uart_printf("%s", send);
            ledSetting(3);
            packagesSent++;
        }
    }
}

/**
 * @brief	safe function to make double value from string
 * @param	input string <br>
 *			output double <br>
 * @return	none
 *
 */
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

/**
 * @brief	function to set LED
 * @param	LED state <br>
 *			0 for LED off <br>
 *			1 for LED on <br>
 *			other for LED toggle <br>
 * @return	none
 *
 */
void ledSetting(uint8_t ledState)
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
}

/**
 * @brief	function to calculate all angles and PWM signal in percent
 * @param	raw X acceleration value <br>
 *			raw Y acceleration value <br>
 *			raw Z acceleration value <br>
 * @return	none
 *
 */
void pwmAngleCalc(int16_t positionX, int16_t positionY, int16_t positionZ)
{
    double pi = PI;
    double divider = GDIVIDER;
    double roll, pitch;
    double gX, gY, gZ;

    gX = positionX / divider;
    gY = positionY / divider;
    gZ = positionZ / divider;

    roll = atan(gY/(sqrt((gX*gX)+(gZ*gZ)))) * 180 / pi;
    pitch = atan(gX/(sqrt((gY*gY)+(gZ*gZ)))) * 180 / pi;

	if (pitch >= 0.0)
	{
		pitch += pitch * PITCHCORRECTPOS;
	}

    signal1 = (90.00+roll) * SERVOUOLINEAR + SERUPLO0;
    signal2 = (90.00+pitch) * SERVOLOLINEAR + SERVOLO0;

    signal1 = (int)(signal1 * RNDFACTOR + 0.5) / RNDFACTOR;
    signal2 = (int)(signal2 * RNDFACTOR + 0.5) / RNDFACTOR;
}

/**
 * @brief	read buttons debounce
 * @param	none
 * @return	none
 *
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
 * @brief	intialize input GPIOs
 * @param	none
 * @return	none
 *
 */
void inputInit()
{
    XMC_GPIO_CONFIG_t config_in;
    config_in.mode = XMC_GPIO_MODE_INPUT_INVERTED_PULL_UP;
    XMC_GPIO_Init(BUTTON1, &config_in);
    XMC_GPIO_Init(BUTTON2, &config_in);
}

/**
 * @brief  	add element to circular buffer
 * @param  	8 bit value for buffer
 * @return 	1 if OK, 0 if KO
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
 * @brief 	read element from circular buffer
 * @param 	pointer to the 8-bit value
 * @return 	1 if OK, 0 if KO
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

/** EOF **/
