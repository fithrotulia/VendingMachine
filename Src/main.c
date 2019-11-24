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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define PB500 		HAL_GPIO_ReadPin(PB500_GPIO_Port, PB500_Pin)==GPIO_PIN_RESET
//#define PB1000 		HAL_GPIO_ReadPin(PB1000_GPIO_Port, PB1000_Pin)==GPIO_PIN_RESET
//#define PBPROSES 	HAL_GPIO_ReadPin(PBPROSES_GPIO_Port, PBPROSES_Pin)==GPIO_PIN_RESET
//#define PBCANCEL 	HAL_GPIO_ReadPin(PBCANCEL_GPIO_Port, PBCANCEL_Pin)==GPIO_PIN_RESET

#define LED500 			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET)
#define LED500M 		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET)
#define LED1000			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET)
#define LED1000M 		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET)
#define LEDPROSES		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET)
#define LEDPROSESM 		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET)
#define LEDCANCEL		HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET)
#define LEDCANCELM 		HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

enum state {start, koin500, koin1000, proses, cancel, out, finish} Kondisi;
volatile uint16_t timeout;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void Task_Init(void);
void Task_Run(void);

unsigned char PB500(void);
unsigned char PB1000(void);
unsigned char PBPROSES(void);
unsigned char PBCANCEL(void);
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
  /* USER CODE BEGIN 2 */
	//	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	//	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);



	Task_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
		//		if (HAL_GPIO_ReadPin(PB1000_GPIO_Port, PB1000_Pin)==GPIO_PIN_RESET)
		//		{
		//			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
		//		}
		//		else
		//		{
		//			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
		//		}
		//		if (HAL_GPIO_ReadPin(PB500_GPIO_Port, PB500_Pin)==GPIO_PIN_RESET)
		//		{
		//			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
		//		}
		//		else
		//		{
		//			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
		//		}
		//		if (HAL_GPIO_ReadPin(PBCANCEL_GPIO_Port, PBCANCEL_Pin)==GPIO_PIN_RESET)
		//		{
		//			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
		//		}
		//		else
		//		{
		//			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		//		}
		//		if (HAL_GPIO_ReadPin(PBPROSES_GPIO_Port, PBPROSES_Pin)==GPIO_PIN_RESET)
		//		{
		//			HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
		//		}
		//		else
		//		{
		//			HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
		//		}
		Task_Run();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the CPU, AHB and APB busses clocks 
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
  /** Initializes the CPU, AHB and APB busses clocks 
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

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED0_Pin LED1_Pin LED2_Pin LED3_Pin */
  GPIO_InitStruct.Pin = LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB500_Pin PB1000_Pin PBPROSES_Pin PBCANCEL_Pin */
  GPIO_InitStruct.Pin = PB500_Pin|PB1000_Pin|PBPROSES_Pin|PBCANCEL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void Task_Init(void)
{
	timeout=0;
	Kondisi=start;
}
void Task_Run(void)
{
	switch(Kondisi)
	{
	case start:
	{
		LED500M;
		LED1000M;
		LEDPROSESM;
		LEDCANCELM;
		Kondisi=koin500;
		break;
	}
	case koin500:
	{
		if(PB500())
		{
			LED500;
			LED1000M;
			LEDPROSESM;
			LEDCANCELM;
			Kondisi=koin1000;
		}
		if(PB1000())
		{
			LED1000;
			LED500M;
			LEDPROSESM;
			LEDCANCELM;
			Kondisi=proses;
		}
		break;
	}
	case koin1000:
	{
		if(PB500())
		{
			LED1000;
			LED500M;
			LEDPROSESM;
			LEDCANCELM;
			Kondisi=proses;
		}
		if(PB1000())
		{
			LED1000;
			LED500M;
			LEDPROSESM;
			LEDCANCELM;
			Kondisi=proses;
		}
		if(PBCANCEL())
		{
			Kondisi=cancel;
		}
		break;
	}
	case proses:
	{
		if(PBPROSES())
		{
			LEDPROSES;
			LED500M;
			LED1000M;
			LEDCANCELM;
			HAL_Delay(1000);
			Kondisi=out;
		}
		if(PBCANCEL())
		{
			Kondisi=cancel;
		}
		break;
	}
	case cancel:
	{
		LED500M;
		LED1000M;
		LEDPROSESM;
		LEDCANCEL;
		HAL_Delay(3000);
		Kondisi=finish;
		break;
	}
	case out:
	{
		LED500;
		LED1000;
		LEDPROSES;
		LEDCANCEL;
		HAL_Delay(3000);
		Kondisi=finish;
	}
	case finish:
	{
		Kondisi=start;
	}
	}
}

unsigned char PB500(void)
{
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(PB500_GPIO_Port, PB500_Pin)==GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(PB500_GPIO_Port, PB500_Pin)==GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(PB500_GPIO_Port, PB500_Pin)==GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}
unsigned char PB1000(void)
{
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(PB1000_GPIO_Port, PB1000_Pin)==GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(PB1000_GPIO_Port, PB1000_Pin)==GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(PB1000_GPIO_Port, PB1000_Pin)==GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}
unsigned char PBPROSES(void)
{
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(PBPROSES_GPIO_Port, PBPROSES_Pin)==GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(PBPROSES_GPIO_Port, PBPROSES_Pin)==GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(PBPROSES_GPIO_Port, PBPROSES_Pin)==GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}
unsigned char PBCANCEL(void)
{
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(PBCANCEL_GPIO_Port, PBCANCEL_Pin)==GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(PBCANCEL_GPIO_Port, PBCANCEL_Pin)==GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(PBCANCEL_GPIO_Port, PBCANCEL_Pin)==GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
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
