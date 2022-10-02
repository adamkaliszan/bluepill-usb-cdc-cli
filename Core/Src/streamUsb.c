/*
 * streamSerial.c
 *
 *  Created on: Apr 11, 2021
 *      Author: Adam Kaliszan: adam.kaliszan@gmail.com
 */


#include <stdio.h>
#include <string.h>

#include "streamUsb.h"


static ssize_t dummy_cookie_write(void *cookie, const char *buf, unsigned int remainingSize);
static ssize_t dummy_cookie_read(void *cookie, char *buf, unsigned int remainingSize);

#ifndef NO_OF_SERIAL_UART_HANDLERS
#define NO_OF_SERIAL_UART_HANDLERS 1
#endif

cookie_io_functions_t dummy_cookie_funcs = {
  .read = dummy_cookie_read,
  .write = dummy_cookie_write,
  .seek = 0,
  .close = 0
};

FILE* openStreamUsb(struct StreamUsbHandler *handler)
{
	FILE *result = NULL;

	osSemaphoreDef_t tmp = {.controlblock = NULL};

	handler->uartTxSemaphoreHandle    = osSemaphoreCreate(&tmp, 1);
	handler->uartTxSemaphoreIrqHandle = osSemaphoreCreate(&tmp, 1);
	handler->uartRxSemaphoreHandle    = osSemaphoreCreate(&tmp, 1);
	handler->uartRxSemaphoreIrqHandle = osSemaphoreCreate(&tmp, 1);
	handler->rxDtaSize                = 0;

	result = fopencookie(handler, "r+", dummy_cookie_funcs);
exit:
	return result;
}


static ssize_t dummy_cookie_read(void *cookie, char *buf, unsigned int size)
{
	struct StreamUsbHandler *usbHandler = (struct StreamUsbHandler *)cookie;

	int result = 0;

    if (osSemaphoreWait(usbHandler->uartRxSemaphoreHandle, 10000) != osOK)
	    goto exit;

  	osSemaphoreWait(usbHandler->uartRxSemaphoreIrqHandle, 0); //TODO use signals

   	//TODO HAL_UARTEx_ReceiveToIdle_IT(usbHandler->device, (uint8_t *)buf, size);

   	while (osSemaphoreWait(usbHandler->uartRxSemaphoreIrqHandle, 1000) != osOK)
   		;

    result+= usbHandler->rxDtaSize;
  	osSemaphoreRelease(usbHandler->uartRxSemaphoreIrqHandle);

    osSemaphoreRelease(usbHandler->uartRxSemaphoreHandle);
exit:
	return result;
}


static ssize_t dummy_cookie_write(void *cookie, const char *buf, unsigned int remainingSize)
{
	struct StreamUsbHandler *serialHandler = (struct StreamSerialHandler *)cookie;
	int result = 0;
	int blockSize;

	if ((result = osSemaphoreWait(serialHandler->uartTxSemaphoreHandle, 1000)) != osOK) goto exit;

	result = 0; //In optimization process this line schould be removed
    do
    {
    	blockSize = sizeof(serialHandler->tmpTxBuffer);
        if (remainingSize < blockSize)
        {
        	blockSize = remainingSize;
        }

    	if (osSemaphoreWait(serialHandler->uartTxSemaphoreIrqHandle, 100) != osOK) goto exit;
    	memcpy(serialHandler->tmpTxBuffer, buf, blockSize);
    	//TODO HAL_UART_Transmit_IT(StreamUsbHandler->device,  StreamUsbHandler->tmpTxBuffer, blockSize);

        buf+= blockSize;
    	remainingSize-= blockSize;
    	result+= blockSize;
    }
    while (remainingSize > 0);
	osSemaphoreRelease(serialHandler->uartTxSemaphoreHandle);

exit:
    return result;
}

/* TODO
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	struct StreamUsbHandler *serialHandler = StreamSerialHandlers;
	for (int i=0; i < noOfSerialHandlers; i++, serialHandler++)
	{
		if (huart != serialHandler->device)
			continue;
		osSemaphoreRelease(serialHandler->uartRxSemaphoreIrqHandle);
		serialHandler -> rxDtaSize = Size;
		break;
	}
}
*/
/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart3)
	{
		osSemaphoreRelease(uartRxSemaphoreIrqHandle);

//		BaseType_t hptw = pdFALSE;
//		xQueueSendFromISR(queueRxUart3Handle, &_rxDta, NULL);
//		HAL_UART_Receive_IT(huart, &_rxDta, 1);
//		if (hptw == pdTRUE)
//			osThreadYield();
	}
}
*/

/* TODO
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	struct StreamUsbHandler *serialHandler = StreamSerialHandlers;
	for (int i=0; i < noOfSerialHandlers; i++, serialHandler++)
	{
		if (huart != serialHandler->device)
			continue;
		osSemaphoreRelease(serialHandler->uartTxSemaphoreIrqHandle);
		break;
	}
}
*/
