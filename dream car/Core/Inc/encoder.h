#ifndef _ENCODER_H_
#define _ENCODER_H_
#include "gpio.h"
#include "tim.h"
#include "stm32f1xx_hal.h"

#define CNT  						__HAL_TIM_GetCounter(encoder->encoder_tim);
#define AUT  						__HAL_TIM_GetAutoreload(encoder->encoder_tim);
#define Acircle 				(34*11*4)
typedef struct{
	TIM_HandleTypeDef *     encoder_tim;
	uint32_t         				encoder_Channel;
	
	
	TIM_HandleTypeDef *     gap_tim;

	uint8_t 								state;
	uint32_t 								pulse;
	uint32_t 								tol_pulse;
	uint32_t 								last_tol_pulse;
	int8_t									Overflow;
	uint8_t 								rpm;
	int32_t 								location;
	
	int8_t 									(*pfinit)(void*);
	int8_t 									(*pfCalculation_en)(void*);
	int8_t 									(*pfCalculation_gap)(void*);
}encoder_t;

void encoder_init(encoder_t *encoder);
int8_t encoder_enc_cal(encoder_t *encoder);
int8_t encoder_gap_cal(encoder_t *encoder);

#endif

