/**
 * @file		3Daccel_app.c
 * @version		v1.0
 * @date		Jan 2018
 * @author		Egermann, Resch
 *
 * @brief		3Daccel app
 *
 */

#include "3Daccel_app.h"

/**
 * @brief	main routine
 *
 */
int main (void)
{
    char rxBuff[RXBUFFERSIZE];

    // init receive buffer and ring buffer
    memset (&rxBuff, 0, sizeof (rxBuff));
    memset (&cb[inix], 0, sizeof (cb[inix]));

    // init values for globals
    initGlobals();

    // init DEBUG, UART, I2C, PWM
    initRetargetSwo();
    _init_uart0_ch0();

    while (1)
    {
        if (_init_i2c1_ch0() == 0)
        {
#if DEBUG
            printf("I2C init done...\n");
#endif
            break;
        }
        else
        {
#if DEBUG
            printf("Error I2C init, retry...\n");
#endif
        }
    }

    initServoPWM();

    // center both servo
    if (pwm(SERVOUPCENTER, 0) != 0)
    {
#if DEBUG
        printf("error centering servo...\n");
#endif
    }
    if (pwm(SERVOLOCENTER, 1) != 0)
    {
#if DEBUG
        printf("error centering servo...\n");
#endif
    }

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
        // clear buffer and receive incoming data
        memset (&rxBuff, 0, sizeof (rxBuff));
        if (_uart_get_string (rxBuff) != 0)
        {
#if DEBUG
            printf("error receiving from UART...\n");
#endif
            continue;
        }

#if DEBUG
        printf("received %s\n", rxBuff);
#endif

        // check received command and react accodingly
        if (strncmp(rxBuff, "#CON,", strlen(rxBuff)) == 0)
        {
            // connection established
            memset (&cb[inix], 0, sizeof (cb[inix]));
            ledSetting(1);
            startup = 0;
            connection = 1;
        }
        else if (strncmp(rxBuff, "#END,", strlen(rxBuff)) == 0)
        {
            // connection END
            ledSetting(0);
            startup = 0;
            connection = 0;
            memset (&cb[inix], 0, sizeof (cb[inix]));
        }
        else if (strncmp(rxBuff, "#SER,f", strlen(rxBuff)) == 0)
        {
            // Servos off
            servoEnable = 0;
        }
        else if (strncmp(rxBuff, "#SER,n", strlen(rxBuff)) == 0)
        {
            // Servos on
            servoEnable = 1;
            startup = 0;
        }
        else if (strncmp(rxBuff, "#STA,", strlen(rxBuff)) == 0)
        {
            // send statistic package
            statisticSend = 1;
        }
        else if (strncmp(rxBuff, "#AVG,a", strlen(rxBuff)) == 0)
        {
            // average angle
            averageChoice = 1;
        }
        else if (strncmp(rxBuff, "#AVG,p", strlen(rxBuff)) == 0)
        {
            // average PWM
            averageChoice = 0;
        }
        else if (strncmp(rxBuff, "#REQ,", strlen(rxBuff)) == 0)
        {
            // send data to PC GUI
            protocolComplete(direction, readAxes.axisX, readAxes.axisY, readAxes.axisZ);
        }
        else
        {
            continue;
        }
    }

    return 0;
}

/** EOF **/
