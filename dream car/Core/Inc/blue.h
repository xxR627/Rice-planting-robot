#ifndef _BLUE_H_
#define _BLUE_H_
#include "gpio.h"
#include "tim.h"
#include "usart.h"
#include "stm32f1xx_hal.h"
typedef struct
{
	uint8_t    resdate[1];
	
}Blue_t;
#define blue_tx 			HAL_UART_Transmit_IT(&huart3, resdate, 1)
#define blue_rx 			HAL_UART_Receive_IT(&huart3, resdate, 1)

uint8_t blue_init();
uint8_t blue_run();


#endif
