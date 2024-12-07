/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : app_freertos.c
 * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app_fatfs.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
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
/* USER CODE BEGIN Variables */
GPIO_TypeDef *led_column_ports[] = {LED_Column0_GPIO_Port, LED_Column1_GPIO_Port, LED_Column2_GPIO_Port, LED_Column3_GPIO_Port, LED_Column4_GPIO_Port, LED_Column5_GPIO_Port,
		LED_Column6_GPIO_Port, LED_Column7_GPIO_Port, LED_Column8_GPIO_Port, LED_Column9_GPIO_Port, LED_Column10_GPIO_Port, LED_Column11_GPIO_Port,
		LED_Column12_GPIO_Port, LED_Column13_GPIO_Port, LED_Column14_GPIO_Port, LED_Column15_GPIO_Port};

uint16_t led_column_pins[] = {LED_Column0_Pin, LED_Column1_Pin, LED_Column2_Pin, LED_Column3_Pin, LED_Column4_Pin, LED_Column5_Pin,
		LED_Column6_Pin, LED_Column7_Pin, LED_Column8_Pin, LED_Column9_Pin, LED_Column10_Pin, LED_Column11_Pin,
		LED_Column12_Pin, LED_Column13_Pin, LED_Column14_Pin, LED_Column15_Pin};

GPIO_TypeDef *led_row_ports[] = {LED_Row0_GPIO_Port, LED_Row1_GPIO_Port, LED_Row2_GPIO_Port, LED_Row3_GPIO_Port, LED_Row4_GPIO_Port, LED_Row5_GPIO_Port,
		LED_Row6_GPIO_Port, LED_Row7_GPIO_Port, LED_Row8_GPIO_Port, LED_Row9_GPIO_Port, LED_Row10_GPIO_Port, LED_Row11_GPIO_Port,
		LED_Row12_GPIO_Port, LED_Row13_GPIO_Port, LED_Row14_GPIO_Port, LED_Row15_GPIO_Port};

uint16_t led_row_pins[] = {LED_Row0_Pin, LED_Row1_Pin, LED_Row2_Pin, LED_Row3_Pin, LED_Row4_Pin, LED_Row5_Pin,
		LED_Row6_Pin, LED_Row7_Pin, LED_Row8_Pin, LED_Row9_Pin, LED_Row10_Pin, LED_Row11_Pin,
		LED_Row12_Pin, LED_Row13_Pin, LED_Row14_Pin, LED_Row15_Pin};

uint16_t image_leds[55][16];
extern uint8_t current_frame;

/* USER CODE END Variables */
/* Definitions for driveLED */
osThreadId_t driveLEDHandle;
const osThreadAttr_t driveLED_attributes = {
  .name = "driveLED",
  .priority = (osPriority_t) osPriorityHigh,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDriveLED(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of driveLED */
  driveLEDHandle = osThreadNew(StartDriveLED, NULL, &driveLED_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDriveLED */
/**
  * @brief  Function implementing the driveLED thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDriveLED */
void StartDriveLED(void *argument)
{
  /* USER CODE BEGIN StartDriveLED */
  /* Infinite loop */
  for(;;)
  {
	  for (uint8_t i = 0; i < 16; i++) {
		  // set columns
		  for (uint8_t j = 0; j < 16; j++) {
			  if (image_leds[current_frame][i] & (0x1 << (15-j))) {
				  HAL_GPIO_WritePin(led_column_ports[j], led_column_pins[j], GPIO_PIN_SET);
			  } else {
				  HAL_GPIO_WritePin(led_column_ports[j], led_column_pins[j], GPIO_PIN_RESET);
			  }
		  }
		  // turn on row (active low)
		  HAL_GPIO_WritePin(led_row_ports[i], led_row_pins[i], GPIO_PIN_RESET);
		  osDelay(1);

		  // turn off row
		  HAL_GPIO_WritePin(led_row_ports[i], led_row_pins[i], GPIO_PIN_SET);
	  }
  }
  osThreadTerminate(NULL);
  /* USER CODE END StartDriveLED */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

