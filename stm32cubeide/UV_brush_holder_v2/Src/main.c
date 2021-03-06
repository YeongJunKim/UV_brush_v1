/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "brush.h"
#include "neopixel.h"


#define BAT_MIN_LIMIT 10
#define BAT_MIN 30
#define BAT_MAX 90

#define BAT_MIN_ADC 3367
#define BAT_MAX_ADC 3895
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
ADC_HandleTypeDef hadc;

IWDG_HandleTypeDef hiwdg;

TIM_HandleTypeDef htim2;
DMA_HandleTypeDef hdma_tim2_ch2;

/* USER CODE BEGIN PV */

uint8_t isSwitch = 0;
uint8_t isCharging = 0;
uint8_t isLowBat = 0;

uint8_t isRunning = 0;

uint8_t isMoodLighting = 0;
uint8_t isUVLighting = 0;

uint8_t step;

uint8_t clickCount = 0;
uint8_t getCount = 0;
uint8_t pastCount = 0;

uint32_t nowTick = 0;
uint32_t pastTick = 0;

uint32_t nowLedTick = 0;
uint32_t pastLedTick = 0;

uint32_t nowADCTick = 0;
uint32_t pastADCTick = 0;

uint32_t nowBatTick = 0;
uint32_t pastBatTick = 0;

uint32_t nowSleepTick = 0;
uint32_t pastSleepTick = 0;

uint32_t nowUvCountTick = 0;
uint32_t pastUvCountTick = 0;

uint16_t adcValue = 0;
float adc_A = 0;
uint16_t adc_B = 0;

uint8_t red_ = 0;
uint8_t green_ = 50;
uint8_t blue_ = 200;
uint8_t white_ = 10;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM2_Init(void);
static void MX_ADC_Init(void);
static void MX_IWDG_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_ADC_Init();
  MX_IWDG_Init();
  /* USER CODE BEGIN 2 */


  /*
   * if IWDG?
   * */
  if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) == SET)
  {

	  set_charging_led(ON);
	  __HAL_RCC_CLEAR_RESET_FLAGS();
  }
  else
  {
	  set_charging_led(OFF);
  }

  HAL_Delay(1000);


  HAL_ADC_Start(&hadc);


  set_charging_led(OFF);
  set_neopixel_led(OFF);
  set_uv_led(OFF);
  set_neopixel_boost(OFF);
  set_uv_boost(OFF);


  neopixel_init(1);
  neopixel_begin();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */




	  HAL_IWDG_Refresh(&hiwdg);
	  isCharging = HAL_GPIO_ReadPin(CHARGE_GPIO_Port, CHARGE_Pin);


	  /*
	   * getAdcValue
	   *
	   * */
	  nowBatTick = HAL_GetTick();
	  if(nowBatTick - pastBatTick > 100)
	  {
		  HAL_ADC_PollForConversion(&hadc, 0xFFFF);
		  adcValue = HAL_ADC_GetValue(&hadc);
//		  adc_A = (float)(adcValue - 3368) * 0.1953;
//		  adc_B = adc_A;
		  pastBatTick = nowBatTick;
	  }
	  if(isCharging)
	  {
		  if(adcValue > BAT_MAX_ADC)
			  set_charging_led(OFF);
		  else
			  set_charging_led(ON);

		  isLowBat = 0;
	  }
	  else
	  {
		  if(adcValue < BAT_MIN_ADC)
		  {
			  for(uint8_t i = 0; i < 6; i ++)
			  {
				  set_charging_led(TOGGLE);
				  HAL_Delay(500);
			  }
			  isLowBat = 1;
		  }
	  }

	  nowLedTick = HAL_GetTick();
	  if(nowLedTick - pastLedTick > 300)
	  {
		  if(isMoodLighting)
		  {
			  set_neopixel_boost(ON);
			  set_neopixel_led(ON);
			  neopixel_pause();
			  neopixel_SetColor(1, red_+=2, green_+=3, blue_+=6, white_++);
			  neopixel_begin();
		  }
		  else if(isUVLighting)
		  {
			  set_neopixel_boost(ON);
			  set_neopixel_led(ON);
			  neopixel_pause();
			  neopixel_SetColor(1, 0, 0, 255, 1);
			  neopixel_begin();
		  }
		  else
		  {
			  set_neopixel_boost(OFF);
			  set_neopixel_led(OFF);
			  neopixel_SetColor(1, 0, 0, 0, 0);
		  }

		  if(isUVLighting)
		  {
			  set_uv_boost(ON);
			  set_uv_led(ON);
		  }
		  else
		  {
			  set_uv_boost(OFF);
			  set_uv_led(OFF);
		  }


		  pastLedTick = nowLedTick;
	  }



	  nowTick = HAL_GetTick();
	  if(isSwitch)
	  {
		  if(nowTick - pastTick > 800)
		  {
			  clickCount++;
			  isSwitch = 0;
			  pastTick = nowTick;
		  }
	  }
	  if(nowTick - pastTick > 1000)
	  {
		  getCount = clickCount;
		  if(getCount != pastCount)
		  {
			  step++;
		  }
		  switch(step)
		  {
		  case 1:
			  if(!isUVLighting)
			  {
				  nowUvCountTick = HAL_GetTick();
				  pastUvCountTick = nowUvCountTick;
			  }
			  else
			  {
				  nowUvCountTick = HAL_GetTick();
			  }
			  isRunning = 1;
			  isMoodLighting = 0;
			  isUVLighting = 1;
			  /*
			   * count timing
			   * */

			  if(nowUvCountTick - pastUvCountTick > 8000)
			  {
				  step = 3;
			  }
			  break;
		  case 2:
			  isRunning = 1;
			  isMoodLighting = 1;
			  isUVLighting = 0;
			  break;
		  case 3:
			  isRunning = 0;
			  isMoodLighting = 0;
			  isUVLighting = 0;
			  step = 0;
			  break;
		  default:
			  isRunning = 0;
			  isMoodLighting = 0;
			  isUVLighting = 0;
			  step = 0;
			  break;
		  }
		  isSwitch = 0;
		  pastCount = getCount;
		  pastTick = nowTick;
	  }


	  nowSleepTick = HAL_GetTick();

	  if(nowSleepTick - pastSleepTick > 5000)
	  {
		  if(isLowBat)
		  {
			  //goToSleep;
			  set_charging_led(OFF);
			  set_neopixel_boost(OFF);
			  set_neopixel_led(OFF);
			  set_uv_boost(OFF);
			  set_uv_led(OFF);
			  HAL_SuspendTick();
			  HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
			  HAL_ResumeTick();
		  }
		  else
		  {
			  if(isRunning)
			  {
				  //don't sleep;
			  }
			  else
			  {
				  if(isCharging)
				  {
					  //don't sleep;
				  }
				  else
				  {
					  //goToSleep;
					  set_charging_led(OFF);
					  set_neopixel_boost(OFF);
					  set_neopixel_led(OFF);
					  set_uv_boost(OFF);
					  set_uv_led(OFF);
					  HAL_SuspendTick();
					  HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
					  HAL_ResumeTick();
				  }
			  }
		  }
		  pastSleepTick = nowSleepTick;
	  }


  }
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

  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
  hadc.Instance = ADC1;
  hadc.Init.OversamplingMode = DISABLE;
  hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerFrequencyMode = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_128;
  hiwdg.Init.Window = 4095;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 39;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_UV_Pin|BOOST_EN_UV_Pin|LED_NEOPIXEL_Pin|BOOST_EN_NEOPIXEL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_CHARGE_GPIO_Port, LED_CHARGE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_UV_Pin BOOST_EN_UV_Pin LED_NEOPIXEL_Pin BOOST_EN_NEOPIXEL_Pin */
  GPIO_InitStruct.Pin = LED_UV_Pin|BOOST_EN_UV_Pin|LED_NEOPIXEL_Pin|BOOST_EN_NEOPIXEL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SWITCH_Pin CHARGE_Pin */
  GPIO_InitStruct.Pin = SWITCH_Pin|CHARGE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_CHARGE_Pin */
  GPIO_InitStruct.Pin = LED_CHARGE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_CHARGE_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == SWITCH_Pin)
	{
		isSwitch = 1;
	}
	else if(GPIO_Pin == CHARGE_Pin)
	{
		isCharging = 1;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
