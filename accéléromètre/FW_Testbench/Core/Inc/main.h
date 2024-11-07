/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
<<<<<<< HEAD
#define PWM_Motor_1_Pin GPIO_PIN_0
#define PWM_Motor_1_GPIO_Port GPIOA
#define DIR_Motor_1_Pin GPIO_PIN_1
#define DIR_Motor_1_GPIO_Port GPIOA
=======
#define DIR_MOTOR_6_Pin GPIO_PIN_3
#define DIR_MOTOR_6_GPIO_Port GPIOC
#define PWM_MOTOR_6_Pin GPIO_PIN_0
#define PWM_MOTOR_6_GPIO_Port GPIOA
#define DIR_MOTOR_1_Pin GPIO_PIN_1
#define DIR_MOTOR_1_GPIO_Port GPIOA
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
<<<<<<< HEAD
=======
#define ENCODER_CHANNEL_A_Pin GPIO_PIN_6
#define ENCODER_CHANNEL_A_GPIO_Port GPIOA
#define ENCODER_CHANNEL_B_Pin GPIO_PIN_7
#define ENCODER_CHANNEL_B_GPIO_Port GPIOA
#define PWM_MOTOR_2_Pin GPIO_PIN_10
#define PWM_MOTOR_2_GPIO_Port GPIOB
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
<<<<<<< HEAD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
=======
#define PWM_MOTOR_1_Pin GPIO_PIN_15
#define PWM_MOTOR_1_GPIO_Port GPIOA
#define DIR_MOTOR_2_Pin GPIO_PIN_2
#define DIR_MOTOR_2_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define DIR_MOTOR_5_Pin GPIO_PIN_4
#define DIR_MOTOR_5_GPIO_Port GPIOB
#define DIR_MOTOR_4_Pin GPIO_PIN_5
#define DIR_MOTOR_4_GPIO_Port GPIOB
#define DIR_MOTOR_3_Pin GPIO_PIN_6
#define DIR_MOTOR_3_GPIO_Port GPIOB
#define PWM_MOTOR_5_Pin GPIO_PIN_7
#define PWM_MOTOR_5_GPIO_Port GPIOB
#define PWM_MOTOR_4_Pin GPIO_PIN_8
#define PWM_MOTOR_4_GPIO_Port GPIOB
#define PWM_MOTOR_3_Pin GPIO_PIN_9
#define PWM_MOTOR_3_GPIO_Port GPIOB
>>>>>>> 9b9e9519ef4823c5775a255998e3b3a3749f4d0f

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
