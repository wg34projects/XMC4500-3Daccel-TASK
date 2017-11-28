#include "3Daccel_out_library.h"
#include "3Daccel_app.h"

uint8_t protocolComplete(int16_t position6D, int16_t positionX, int16_t positionY, int16_t positionZ, int8_t temperature)
{
	char string6D[8][6] = {"#USX,", "#UDX,", "#DSX,", "#DDX,", "#TOP,", "#BOT,", "#XXX,", "#FAL,"};
	char send[RX_BUFFER_SIZE];
	memset (&send, 0, sizeof (send));

	if (sprintf(send, "%s%7d%s%7d%s%7d%s%02d$\n", string6D[position6D], positionX, ",", positionY, ",", positionZ, ",", temperature* 2 + 6) < 0)
//	if (sprintf(send, "%s%d%s%d%s%d$\n", string6D[position6D], positionX, ",", positionY, ",", positionZ) < 0)
	{
		errorcountInternal++;
		return 1;
	}
	else
	{
		printf("%s", send);
		_uart_printf("%s", send);	
		return 0;
	}	
}

void SysTick_Handler (void)
{
    static uint32_t ticks = 0;

    ticks++;
    if (ticks == TICKS_WAIT)
    {
        ticks = 0;
//		printf("\nerrorcountRAW = %d errorcount6D = %d | errorcountSETUP = %d | errorcountInternal = %d\n", errorcountRAW, errorcount6D, errorcountSetup, errorcountInternal);
    }
}
