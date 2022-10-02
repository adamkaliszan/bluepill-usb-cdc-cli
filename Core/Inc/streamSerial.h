#ifndef INC_STREAM_SERIAL_H_
#define INC_STREAM_SERIAL_H_

#include <stdio.h>

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

#if 0

FILE* openSerialStream(UART_HandleTypeDef *uartHandle);


struct StreamSerialHandler
{
	UART_HandleTypeDef *device;

	osSemaphoreId uartTxSemaphoreHandle;
	osSemaphoreId uartTxSemaphoreIrqHandle;
	osSemaphoreId uartRxSemaphoreHandle;
	osSemaphoreId uartRxSemaphoreIrqHandle;

	volatile uint16_t rxDtaSize;

	uint8_t tmpTxBuffer[64];
};
#endif

#endif /* INC_STREAM_SERIAL_H_ */
