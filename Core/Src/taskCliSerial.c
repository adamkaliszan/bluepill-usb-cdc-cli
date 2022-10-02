#include <stdio.h>
#include <taskCliSerial.h>

#include "streamSerial.h"
#include "vty.h"


/*
void StartCliTaskSerial(void const * argument)
{
	UART_HandleTypeDef *huartX = (UART_HandleTypeDef*) argument;
	FILE *cliSerialStream;
	struct CmdState cliSerialState;

	cliSerialStream = openSerialStream(huartX);
	fprintf(cliSerialStream, "Restart\r\n");
	fflush(cliSerialStream);

	cmdStateConfigure(&cliSerialState, cliSerialStream, cliSerialStream, cmdListNormal, NR_NORMAL);

	cmdlineInputFunc('\r', &cliSerialState);
	cliMainLoop(&cliSerialState);
	fflush(cliSerialStream);

	for(;;)
	{
		int x = fgetc(cliSerialStream);
		if (x == -1)
			continue;

		cmdlineInputFunc(x, &cliSerialState);
		cliMainLoop(&cliSerialState);
		fflush(cliSerialStream);
	}
}
*/

