#include "servo_library.h"

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

void initServoPWM()
{
	initServoPWMXMC();
}
