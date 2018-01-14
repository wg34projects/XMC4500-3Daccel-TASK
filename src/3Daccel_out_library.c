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
    startup = 0;
    connection = 0;
    averageChoice = 0;
}

/**
 * @brief	function to init LED output
 * @param	none
 * @return	none
 *
 */
void outputInit(void)
{
    outputInitXMC();
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

    // ticks acction only when connected
    if (connection == 1)
    {
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

        // servo action only when connected
        if (servoEnable == 1)
        {
            if (averageChoice == 0)
            {
                // PWM averaging
                smoothSignal1 += signal1;
                smoothSignal2 += signal2;
                i++;
                if (i == PWMAVERAGE)
                {
                    // set servo
                    smoothSignal1 /= PWMAVERAGE;
                    smoothSignal2 /= PWMAVERAGE;
                    if (pwm(smoothSignal1, 0) != 0)
                    {
                        errorcount++;
                    }
                    if (pwm(smoothSignal2, 1) != 0)
                    {
                        errorcount++;
                    }
                    smoothSignal1 = 0.0;
                    smoothSignal2 = 0.0;
                    i = 0;
                }
            }
            else if (averageChoice == 1)
            {
                // angle thresholding
                if (pwm(signal1, 0) != 0)
                {
                    errorcount++;
                }
                if (pwm(signal2, 1) != 0)
                {
                    errorcount++;
                }
            }
        }
        else
        {
            // reset servo
            if (pwm(SERVOUPCENTER, 0) != 0)
            {
                errorcount++;
            }
            if (pwm(SERVOLOCENTER, 1) != 0)
            {
                errorcount++;
            }
        }
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
void protocolComplete(uint16_t position6D, int16_t positionX, int16_t positionY, int16_t positionZ)
{
    char string6D[8][6] = {"#USX,", "#UDX,", "#DSX,", "#DDX,", "#TOP,", "#BOT,", "#XXX,", "#FAL,"};
    char button[2][8] = {"#BUT,1$", "#BUT,2$"};

    char send[RXBUFFERSIZE];

    memset (&send, 0, sizeof (send));

    if (statisticSend == 1)
    {
        // send statistic package if requested - all together constant 32 chars
        if (snprintf(send, 32, "#STA,%10lu,%3d,%10lu$\n", packagesSent, errorcount, startup) < 0)
        {
            errorcount++;
        }
        else
        {
#if DEBUG
            printf("send %s\n", send);
#endif
            if (_uart_printf("%s", send) != 0)
            {
                errorcount++;
            }
            packagesSent++;
        }
        statisticSend = 0;
        return;
    }
    else if (buttonSend == 1)
    {
        // send button 1 pressed - constant 9 chars
        if (snprintf(send, 9, "%s\n", button[0]) < 0)
        {
            errorcount++;
        }
        else
        {
#if DEBUG
            printf("send %s", send);
#endif
            if(_uart_printf("%s", send) != 0)
            {
                errorcount++;
            }
            packagesSent++;
        }
        buttonSend = 0;
        return;
    }
    else if (buttonSend == 2)
    {
        // send button 2 pressed - constant 9 chars
        if (snprintf(send, 9, "%s\n", button[1]) < 0)
        {
            errorcount++;
        }
        else
        {
#if DEBUG
            printf("send %s", send);
#endif
            if(_uart_printf("%s", send) != 0)
            {
                errorcount++;
            }
            packagesSent++;
        }
        buttonSend = 0;
        return;
    }
    else
    {
        // send acceleration data - all together constant 29 chars
        if (snprintf(send, 29,"%s%6d,%6d,%6d$\n", string6D[position6D], positionX, positionY, positionZ) < 0)
        {
            errorcount++;
        }
        else
        {
#if DEBUG
            printf("send %s", send);
#endif
            if(_uart_printf("%s", send) != 0)
            {
                errorcount++;
            }
            ledSetting(3);
            packagesSent++;
        }
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
    ledSettingXMC(ledState);
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
    double roll, pitch;
    double gX = 0, gY = 0, gZ = 0;
    static double rollStored = 0.0;
    static double pitchStored = 0.0;

    // calculate acceleration values from raw values
    gX = positionX / GDIVIDER;
    gY = positionY / GDIVIDER;
    gZ = positionZ / GDIVIDER;

    // calculate angles for servos
    roll = atan(gY/(sqrt((gX*gX)+(gZ*gZ)))) * 180 / PI;
    pitch = atan(gX/(sqrt((gY*gY)+(gZ*gZ)))) * 180 / PI;

    // angle correction as documented
    if (pitch >= 0.0)
    {
        pitch += pitch * PITCHCORRECTPOS;
    }

    // angle thresholding
    if (startup == 0)
    {
        pitchStored = pitch;
        rollStored = roll;
    }
    else
    {
        if (averageChoice == 1)
        {
            if (fabs(pitch - pitchStored) < ANGAVERAGE)
            {
                pitch = pitchStored;
            }
            else
            {
                pitchStored = pitch;
            }

            if (fabs(roll - rollStored) < ANGAVERAGE)
            {
                roll = rollStored;
            }
            else
            {
                pitchStored = pitch;
            }
        }
    }

    startup++;

    // final signal values

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
    readButtonDebounceXMC();
}

/**
 * @brief	intialize input GPIOs
 * @param	none
 * @return	none
 *
 */
void inputInit()
{
    inputInitXMC();
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
