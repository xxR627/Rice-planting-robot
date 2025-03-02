#include "encoder.h"


void encoder_init(encoder_t* encoder)
{
	HAL_TIM_Base_Start_IT(encoder ->gap_tim);
	HAL_TIM_Encoder_Start_IT(encoder->encoder_tim ,encoder->encoder_Channel);
//	__HAL_TIM_SET_COUNTER(encoder->encoder_tim ,10000);
}

int8_t encoder_enc_cal(encoder_t *encoder)
{
	if(encoder == NULL)
		{
			return -1;
		}
	else
		{encoder->state = __HAL_TIM_IS_TIM_COUNTING_DOWN(encoder->encoder_tim);
	
				if(1 == encoder->state)//1表示向下计数1
				{
					encoder->Overflow--;
					encoder->pulse = 20000 - CNT;
					encoder->tol_pulse = encoder->pulse + encoder->Overflow * 10000;
				}else if(0 == encoder->state)//0表示向上计数或者定时器没有运行
				{
					encoder->Overflow++;
					
					encoder->pulse = CNT;
					encoder->tol_pulse = encoder->pulse + encoder->Overflow * 10000;
				}
//				__HAL_TIM_SET_COUNTER(encoder->encoder_tim ,10000);
			return 0;
		}
}
int8_t encoder_gap_cal(encoder_t *encoder)
{
	if(encoder == NULL)
		{
			return -1;
		}
	else
		{
				encoder ->location = (encoder ->tol_pulse - encoder ->last_tol_pulse)/ Acircle;
				encoder ->rpm = encoder ->location * 10;
			return 0;
		}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2) // 假设使用TIM2作为编码器定时器
    {
        // 读取编码器值并更新速度
        for(int i = 0; i < 4; i++)
        {
            float rpm = get_encoder_speed(i); // 获取编码器速度
            update_motor_speed(i, rpm);
        }
    }
}
