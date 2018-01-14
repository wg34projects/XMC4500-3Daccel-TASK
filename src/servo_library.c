/**
 * @file		servo_library.c
 * @version		v1.0
 * @date		Jan 2018
 * @author		Egermann, Resch
 *
 * @brief		servo library
 */

#include "servo_library.h"

/**
 * @brief	init PWM for servos
 * @param	none
 * @return	none
 *
 */
void initServoPWM()
{
    // init servos

    initServoPWMXMC();
}

/**
 * @brief	set PWM for servos
 * @param	dutycycle in percent <br>
 *			0 for upper servo <br>
 *			1 for lower servo <br>
 * @return	none
 *
 */
uint8_t pwm(double dutycycle, uint8_t out)
{
    // call pwm driver

    if (out == 0)
    {
        if(pwmXMC(dutycycle, 0) == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }

    }
    else
    {
        if(pwmXMC(dutycycle, 1) == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

/** EOF **/
