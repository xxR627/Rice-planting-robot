/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor.h"
#include "pid.h"
#include "blue.h"
#include "encoder.h"
#include "step_motor.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t resdate[1];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void Motor_X_ZHENG(void)  // Motor turn forward
{
    HAL_GPIO_WritePin(BJ_GPIO_Port, BJ_Pin,GPIO_PIN_RESET); // Set PB1 to LOW
}

void Motor_X_FAN(void)    // Motor reverse
{
    HAL_GPIO_WritePin(BJ_GPIO_Port, BJ_Pin,GPIO_PIN_SET); // Set PB1 to HIGH
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef*huart)
	{
		HAL_UART_Transmit_IT(&huart3,resdate,1);
	if(resdate[0]=='g'){
		 go_forward();}
	if(resdate[0]=='l'){
		 go_left();}
	if(resdate[0]=='0'){
		 go_r();}
	if(resdate[0]=='1'){
		 go_l();}
	if(resdate[0]=='r'){
		 go_right();}
	if(resdate[0]=='b'){
		 go_back();}
	if(resdate[0]=='s'){
		 stop();}
	if(resdate[0]=='9'){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,1800);}
	if(resdate[0]=='a'){
		 go_forward1();}
	if(resdate[0]=='d'){
		 go_left1();}
	if(resdate[0]=='f'){
		 go_r1();}
	if(resdate[0]=='j'){
		 go_l1();}
	if(resdate[0]=='h'){
		 go_right1();}
	if(resdate[0]=='3'){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,400);}
	if(resdate[0]=='Q'){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,800);}
	if(resdate[0]=='W'){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,1400);}
	if(resdate[0]=='4'){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,1500);}
	if(resdate[0]=='5'){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,500);}
	if(resdate[0]=='6'){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,1350);}
	if(resdate[0]=='7'){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,700);}
	if(resdate[0]=='U'){
		 Motor_X_FAN();
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 500);}
	if(resdate[0]=='D'){  
		Motor_X_ZHENG(); 
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 500);}
if(resdate[0]=='N'){
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);}

HAL_UART_Receive_IT(&huart3,resdate,1);
				
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
		
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART3_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	  
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);//启pwm输出
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3); 
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);//启pwm输出
	
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
HAL_Delay(10);
HAL_UART_Receive_IT(&huart3,resdate,1);

////左面做循迹替�?
//go_forward();
//				HAL_Delay(800);
//stop();
//				HAL_Delay(1500);
//			go_right();
//			HAL_Delay(2200);
//			stop();
//HAL_Delay(1500);
//go_r();
//HAL_Delay(500);
//stop();
//				HAL_Delay(1500);
//	go_forward();
//				HAL_Delay(800);
//stop();
////				HAL_Delay(500); 
////右面
//go_forward();
//				HAL_Delay(700);
//stop();
//				HAL_Delay(300);
//go_l();
//	HAL_Delay(700);
//stop();
//				HAL_Delay(1000);
//				go_forward();
//				HAL_Delay(2000);
//				stop();
//HAL_Delay(1500);
////				
////			go_left();
////			HAL_Delay(3000);
////			stop();
////HAL_Delay(1500);


////	go_forward();
//				HAL_Delay(1500);
//stop();
//				HAL_Delay(500); 
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {	


	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
