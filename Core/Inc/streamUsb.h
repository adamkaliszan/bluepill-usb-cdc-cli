#ifndef INC_STREAM_SERIAL_H_
#define INC_STREAM_SERIAL_H_

#include <stdio.h>

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

struct StreamUsbHandler
{
	osSemaphoreId uartTxSemaphoreHandle;
	osSemaphoreId uartTxSemaphoreIrqHandle;
	osSemaphoreId uartRxSemaphoreHandle;
	osSemaphoreId uartRxSemaphoreIrqHandle;

	volatile uint16_t rxDtaSize;

	uint8_t tmpTxBuffer[64];
};

FILE* openStreamUsb(struct StreamUsbHandler *uartHandle);


#endif /* INC_STREAM_SERIAL_H_ */
