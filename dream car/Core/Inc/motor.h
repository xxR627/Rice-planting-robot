
#ifndef MOTOR_H_
#define MOTOR_H_
#include "main.h"

extern	int myabs(int a);
void Set_Pwmb(int motor_right1);
void Set_Pwma(int motor_left1);
void Set_Pwmd(int motor_left2);
void Set_Pwmc(int motor_right2);
int myabs(int a);
int motor_right1();
int motor_right2();
int motor_left1();
int motor_left2();
void go_forward();
void go_left();
void go_back();
void go_l();
void go_right();
void go_r();
void stop();
void go_forward1();
void go_left1();
void go_back1();
void go_l1();
void go_right1();
void go_r1();
void Motor_X_FAN();
void Motor_X_ZHENG();

#endif /* MOTOR_H_ */
