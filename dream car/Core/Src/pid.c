//#include "pid.h"
//#include "motor.h"
///**************************************************************************
// 函数功能：单位时间读取编码器计数
// 入口参数：定时器
// 返回  值：速度值
// **************************************************************************/
//int Read_Velocity(uint8_t TIMX) {
//	int Encoder_TIM;
//	switch (TIMX) {
//	case 2:
//		Encoder_TIM = -(short) TIM2->CNT;
//		TIM2->CNT = 0;
//		break;
//	case 3:
//		Encoder_TIM = (short) TIM3->CNT;
//		TIM3->CNT = 0;
//		break;
//	case 4:
//		Encoder_TIM = (short) TIM4->CNT;
//		TIM4->CNT = 0;
//		break;
//	default:
//		Encoder_TIM = 0;
//	}
//	return Encoder_TIM;
//}

////计算速度  cm/s
//float CalActualSpeed(int pulse) {
//	return (float) (0.3092424 * pulse);
//}
///**************************************************************************
// 函数功能：限制PWM赋值
// 入口参数：无
// 返回  值：无
// **************************************************************************/
////void Xianfu_Pwm(void) 
////	{
////	int  Amplitude = 7200;    //===PWM满幅是7200 限制在7100
////	if (motor_left1() < -Amplitude)
////	(motor_left1() =_-Amplitude);
////	if (motor_left1()> Amplitude)
////		motor_left1= Amplitude;
////	if (motor_right1() < -Amplitude)
////		motor_right1 = -Amplitude;
////	if (motor_right1() > Amplitude)
////		motor_right1 = Amplitude;
////}
////有问题
///**************************************************************************
// 函数功能：增量PI控制器
// 入口参数：编码器测量值，目标速度
// 返回  值：电机PWM
// 根据增量式离散PID公式
// pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
// e(k)代表本次偏差
// e(k-1)代表上一次的偏差  以此类推
// pwm代表增量输出
// 在我们的速度控制闭环系统里面，只使用PI控制
// pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
// **************************************************************************/
//int Incremental_PI_A(float Encoder, float Target) {
//	static float Bias_A, Pwm_A, Last_bias_A;
//	Bias_A = Target - Encoder;                                  //计算偏差
//	Pwm_A += Velocity_KP_A * (Bias_A - Last_bias_A) + Velocity_KI_A * Bias_A; //增量式PI控制器
//	Last_bias_A = Bias_A;	                                   //保存上一次偏差
//	return Pwm_A;                                           //增量输出
//}

//int Incremental_PI_B(float Encoder, float Target) {
//	static float Bias, Pwm, Last_bias;
//	Bias = Target - Encoder;                                  //计算偏差
//	Pwm += Velocity_KP_B * (Bias - Last_bias) + Velocity_KI_B * Bias; //增量式PI控制器
//	Last_bias = Bias;	                                   //保存上一次偏差
//	return Pwm;                                           //增量输出
//}


