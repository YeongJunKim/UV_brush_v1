/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32l0xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_LOW_Pin GPIO_PIN_0
#define LED_LOW_GPIO_Port GPIOA
#define LED_MIDDLE_Pin GPIO_PIN_1
#define LED_MIDDLE_GPIO_Port GPIOA
#define LED_UP_Pin GPIO_PIN_2
#define LED_UP_GPIO_Port GPIOA
#define BAT_ADC_Pin GPIO_PIN_3
#define BAT_ADC_GPIO_Port GPIOA
#define LED_UV_Pin GPIO_PIN_4
#define LED_UV_GPIO_Port GPIOA
#define SWITCH_Pin GPIO_PIN_5
#define SWITCH_GPIO_Port GPIOA
#define SWITCH_EXTI_IRQn EXTI4_15_IRQn
#define BOOST_EN_UV_Pin GPIO_PIN_6
#define BOOST_EN_UV_GPIO_Port GPIOA
#define CHARGE_Pin GPIO_PIN_7
#define CHARGE_GPIO_Port GPIOA
#define CHARGE_EXTI_IRQn EXTI4_15_IRQn
#define LED_CHARGE_Pin GPIO_PIN_1
#define LED_CHARGE_GPIO_Port GPIOB
#define LED_NEOPIXEL_Pin GPIO_PIN_9
#define LED_NEOPIXEL_GPIO_Port GPIOA
#define BOOST_EN_NEOPIXEL_Pin GPIO_PIN_10
#define BOOST_EN_NEOPIXEL_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
