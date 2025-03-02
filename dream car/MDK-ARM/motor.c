#include "motor.h"
#include "tim.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_tim.h"

#define DEAD_ZONE 50        // 死区范围
#define MAX_INTEGRAL 5000   // 积分限幅值
#define MIN_SPEED_THRESH 100 // 最小速度阈值

// PID参数结构体
typedef struct {
	float Kp;           // 比例系数
	float Ki;           // 积分系数
	float Kd;           // 微分系数
	float target;       // 目标值
	float actual;       // 实际值
	float error;        // 当前误差
	float last_error;   // 上次误差
	float prev_error;   // 上上次误差
	float error_sum;    // 误差累积
	float output;       // PID输出
	float output_limit; // 输出限幅
	float dead_zone;    // 死区范围
} PID_TypeDef;

// 电机参数结构体
typedef struct {
	GPIO_TypeDef* IN1_GPIO_Port;
	uint16_t IN1_Pin;
	GPIO_TypeDef* IN2_GPIO_Port;
	uint16_t IN2_Pin;
	TIM_HandleTypeDef* htim;
	uint32_t channel;
	PID_TypeDef pid;    // 每个电机的PID控制器
	float current_rpm;  // 当前转速
	float target_rpm;   // 目标转速
	uint8_t direction;  // 电机方向
} Motor_TypeDef;

// 定义四个电机
static Motor_TypeDef motors[4] = {
	{AIN1_GPIO_Port, AIN1_Pin, AIN2_GPIO_Port, AIN2_Pin, &htim1, TIM_CHANNEL_1, 
	 {2.0f, 0.15f, 0.08f, 0, 0, 0, 0, 0, 0, 0, 9500.0f, DEAD_ZONE}}, // 左前
	{BIN1_GPIO_Port, BIN1_Pin, BIN2_GPIO_Port, BIN2_Pin, &htim1, TIM_CHANNEL_2,
	 {2.0f, 0.15f, 0.08f, 0, 0, 0, 0, 0, 0, 0, 9500.0f, DEAD_ZONE}}, // 右前
	{CIN1_GPIO_Port, CIN1_Pin, CIN2_GPIO_Port, CIN2_Pin, &htim1, TIM_CHANNEL_3,
	 {2.0f, 0.15f, 0.08f, 0, 0, 0, 0, 0, 0, 0, 9500.0f, DEAD_ZONE}}, // 左后
	{DIN1_GPIO_Port, DIN1_Pin, DIN2_GPIO_Port, DIN2_Pin, &htim1, TIM_CHANNEL_4,
	 {2.0f, 0.15f, 0.08f, 0, 0, 0, 0, 0, 0, 0, 9500.0f, DEAD_ZONE}}  // 右后
};

// 运动参数结构体
typedef struct {
	float max_speed;      // 最大速度
	float acceleration;   // 加速度
	float current_speed;  // 当前速度
	float turn_ratio;     // 转向比例
} Motion_Params;

static Motion_Params motion = {
	.max_speed = 9500.0f,
	.acceleration = 1000.0f,
	.current_speed = 0.0f,
	.turn_ratio = 0.8f
};

static inline int myabs(int a) {
	return (a < 0) ? -a : a;
}

// 增量式PID控制计算
static float PID_Calculate(PID_TypeDef* pid) {
	// 计算误差
	pid->error = pid->target - pid->actual;
	
	// 死区控制
	if (myabs(pid->error) < pid->dead_zone) {
		pid->error = 0;
		pid->error_sum = 0;
		return 0;
	}
	
	// 增量式PID计算
	float delta_u = pid->Kp * (pid->error - pid->last_error) +
				   pid->Ki * pid->error +
				   pid->Kd * (pid->error - 2 * pid->last_error + pid->prev_error);
	
	// 更新误差
	pid->prev_error = pid->last_error;
	pid->last_error = pid->error;
	
	// 更新输出
	pid->output += delta_u;
	
	// 输出限幅
	if (pid->output > pid->output_limit) {
		pid->output = pid->output_limit;
	} else if (pid->output < -pid->output_limit) {
		pid->output = -pid->output_limit;
	}
	
	return pid->output;
}

// 电机方向控制
static void Set_Motor_Direction(Motor_TypeDef* motor, int direction) {
	if (direction >= 0) {
		HAL_GPIO_WritePin(motor->IN1_GPIO_Port, motor->IN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(motor->IN2_GPIO_Port, motor->IN2_Pin, GPIO_PIN_RESET);
		motor->direction = 1;
	} else {
		HAL_GPIO_WritePin(motor->IN1_GPIO_Port, motor->IN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(motor->IN2_GPIO_Port, motor->IN2_Pin, GPIO_PIN_SET);
		motor->direction = 0;
	}
}

// 统一的电机控制函数
static void Set_Motor(Motor_TypeDef* motor, float target_speed) {
	// 更新目标速度
	motor->target_rpm = target_speed;
	motor->pid.target = myabs(target_speed);
	
	// 计算PID输出
	float speed = PID_Calculate(&motor->pid);
	
	// 设置方向
	Set_Motor_Direction(motor, target_speed);
	
	// 设置PWM
	if (speed < MIN_SPEED_THRESH) {
		speed = 0;  // 防止低速抖动
	}
	__HAL_TIM_SET_COMPARE(motor->htim, motor->channel, (uint32_t)speed);
}

// 平滑速度控制
static float smooth_speed(float target_speed, float current_speed) {
	float speed_diff = target_speed - current_speed;
	float acc = motion.acceleration;
	
	// 根据速度差值动态调整加速度
	if (myabs(speed_diff) < motion.acceleration * 2) {
		acc = motion.acceleration * 0.5f;
	}
	
	if (myabs(speed_diff) < acc) {
		return target_speed;
	}
	return current_speed + (speed_diff > 0 ? acc : -acc);
}

// 更新电机实际速度
void update_motor_speed(uint8_t motor_id, float rpm) {
	if (motor_id < 4) {
		motors[motor_id].current_rpm = rpm;
		motors[motor_id].pid.actual = myabs(rpm);
	}
}

// 设置所有电机速度
void set_motors(float left_front, float right_front, float left_rear, float right_rear) {
	float speeds[4] = {left_front, right_front, left_rear, right_rear};
	
	// 应用速度限制和平滑处理
	for (int i = 0; i < 4; i++) {
		if (speeds[i] > motion.max_speed) speeds[i] = motion.max_speed;
		if (speeds[i] < -motion.max_speed) speeds[i] = -motion.max_speed;
		speeds[i] = smooth_speed(speeds[i], motors[i].current_rpm);
		Set_Motor(&motors[i], speeds[i]);
	}
}

// 改进的转向控制
void turn(float angle, float speed) {
	float turn_ratio = (angle / 90.0f) * motion.turn_ratio;
	float inner_speed = speed * (1.0f - turn_ratio);
	float outer_speed = speed * (1.0f + turn_ratio);
	
	if (angle > 0) {  // 右转
		set_motors(-inner_speed, outer_speed, -inner_speed, outer_speed);
	} else {  // 左转
		set_motors(outer_speed, -inner_speed, outer_speed, -inner_speed);
	}
}

void go_forward(void) {
	set_motors(5000, 9500, 5000, 9000);
}

void go_forward1(void) {
	set_motors(2500, 4750, 2500, 4500);
}

void go_right(void) {
	set_motors(-7000, 8000, 8000, -7000);
}

void go_left(void) {
	set_motors(7000, -8000, -8000, 7000);
}

void go_back(void) {
	set_motors(-5000, -8000, -6000, -9000);
}

void stop(void) {
	set_motors(0, 0, 0, 0);
	motion.current_speed = 0;
}

void go_right1()
{
	Set_Pwma(-3000);
	Set_Pwmb(3500);
	Set_Pwmc(3500);		
	Set_Pwmd(-3000);
}
void go_r1()
{
	Set_Pwma(9500);
	Set_Pwmb(-9500);
	Set_Pwmc(9500);		
	Set_Pwmd(-9500);
}
void go_r()
{
	Set_Pwma(8000);
	Set_Pwmb(-8000);
	Set_Pwmc(8000);		
	Set_Pwmd(-8000);
}
void go_left1()
{
	Set_Pwma(3000);
	Set_Pwmb(-3500);
	Set_Pwmc(-3500);		
	Set_Pwmd(3000);
} 
void go_l()
{
	Set_Pwma(-8000);
	Set_Pwmb(8000);
	Set_Pwmc(-8000);		
	Set_Pwmd(8000);
} 
void go_l1()
{
	Set_Pwma(-9500);
	Set_Pwmb(9500);
	Set_Pwmc(-9500);		
	Set_Pwmd(9500);
} 
   
// 可以根据实际情况调整以下参数
motors[0].pid.Kp = 2.0f;  // 比例系数
motors[0].pid.Ki = 0.15f; // 积分系数
motors[0].pid.Kd = 0.08f; // 微分系数

// 调整转向灵敏度
motion.turn_ratio = 0.8f; // 范围0~1，越大转向越灵敏
