/**
 * @file		servo_library.c
 * @version		v1.0
 * @date		Nov 2017
 * @author		Egermann, Resch
 *
 * @brief		servo library
 */

#include "servo_library.h"

/**
 * @brief	set PWM for servos
 * @param	dutycycle in percent <br>
 *			0 for upper servo <br>
 *			1 for lower servo <br>
 * @return	none
 *		  
 */
void pwm(double dutycycle, uint8_t out)
{
	if (out == 0)
	{
		pwmXMC(dutycycle, 0);
	}
	else
	{
		pwmXMC(dutycycle, 1);
	}
}

/**
 * @brief	init PWM for servos
 * @param	none
 * @return	none
 *		  
 */
void initServoPWM()
{
	initServoPWMXMC();
}

/** EOF **/
