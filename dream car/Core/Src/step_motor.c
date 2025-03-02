#include "step_motor.h"
#include "motor.h"
#include "tim.h"

void PWMT(int motor1) {
	if (motor_left1 < 0) {
		HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_SET);
	}
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, myabs(motor1));

}
void run1()
{
	PWMT(6000);
}
  