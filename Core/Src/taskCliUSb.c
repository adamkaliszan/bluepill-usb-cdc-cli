#include <stdio.h>
#include <taskCliSerial.h>

#include "streamUsb.h"
#include "vty.h"


static struct StreamUsbHandler handler;

void StartTaskCliUsb(void const * argument)
{
	FILE *cliStreamUsb;
	struct CmdState cliUsbState;

	cliStreamUsb = openStreamUsb(&handler);
	fprintf(cliStreamUsb, "Restart\r\n");
	fflush(cliStreamUsb);

	cmdStateConfigure(&cliUsbState, cliStreamUsb, cliStreamUsb, cmdListNormal, NR_NORMAL);

	cmdlineInputFunc('\r', &cliUsbState);
	cliMainLoop(&cliUsbState);
	fflush(cliStreamUsb);

	for(;;)
	{
		int x = fgetc(cliStreamUsb);
		if (x == -1)
			continue;

		cmdlineInputFunc(x, &cliUsbState);
		cliMainLoop(&cliUsbState);
		fflush(cliStreamUsb);
	}
}


