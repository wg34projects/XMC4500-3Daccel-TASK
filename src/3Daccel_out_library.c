#include "3Daccel_out_library.h"
#include "3Daccel_app.h"

uint8_t protocolComplete(int16_t position6D, int16_t positionX, int16_t positionY, int16_t positionZ)
{
	char string6D[8][6] = {"#USX,", "#UDX,", "#DSX,", "#DDX,", "#TOP,", "#BOT,", "#XXX,", "#FAL,"};
	char send[RX_BUFFER_SIZE];
	memset (&send, 0, sizeof (send));

	if (sprintf(send, "%s%d%s%d%s%d$\n", string6D[position6D], positionX, ",", positionY, ",", positionZ) < 0)
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
