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

/* USER CODE END Variables */
/* Definitions for readSD */
osThreadId_t readSDHandle;
const osThreadAttr_t readSD_attributes = {
  .name = "readSD",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for driveLED */
osThreadId_t driveLEDHandle;
const osThreadAttr_t driveLED_attributes = {
  .name = "driveLED",
  .priority = (osPriority_t) osPriorityRealtime,
  .stack_size = 128 * 4
};
/* Definitions for getImageFrame */
osThreadId_t getImageFrameHandle;
const osThreadAttr_t getImageFrame_attributes = {
  .name = "getImageFrame",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for getLEDstatus */
osThreadId_t getLEDstatusHandle;
const osThreadAttr_t getLEDstatus_attributes = {
  .name = "getLEDstatus",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartReadSD(void *argument);
void StartDriveLED(void *argument);
void StartGetImageFrame(void *argument);
void StartGetLEDStatus(void *argument);

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
  /* creation of readSD */
  readSDHandle = osThreadNew(StartReadSD, NULL, &readSD_attributes);

  /* creation of driveLED */
  driveLEDHandle = osThreadNew(StartDriveLED, NULL, &driveLED_attributes);

  /* creation of getImageFrame */
  getImageFrameHandle = osThreadNew(StartGetImageFrame, NULL, &getImageFrame_attributes);

  /* creation of getLEDstatus */
  getLEDstatusHandle = osThreadNew(StartGetLEDStatus, NULL, &getLEDstatus_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartReadSD */
/**
  * @brief  Function implementing the readSD thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartReadSD */
void StartReadSD(void *argument)
{
  /* USER CODE BEGIN StartReadSD */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  osThreadTerminate(NULL);
  /* USER CODE END StartReadSD */
}

/* USER CODE BEGIN Header_StartDriveLED */
/**
* @brief Function implementing the driveLED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDriveLED */
void StartDriveLED(void *argument)
{
  /* USER CODE BEGIN StartDriveLED */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  osThreadTerminate(NULL);
  /* USER CODE END StartDriveLED */
}

/* USER CODE BEGIN Header_StartGetImageFrame */
/**
* @brief Function implementing the getImageFrame thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartGetImageFrame */
void StartGetImageFrame(void *argument)
{
  /* USER CODE BEGIN StartGetImageFrame */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  osThreadTerminate(NULL);
  /* USER CODE END StartGetImageFrame */
}

/* USER CODE BEGIN Header_StartGetLEDStatus */
/**
* @brief Function implementing the getLEDstatus thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartGetLEDStatus */
void StartGetLEDStatus(void *argument)
{
  /* USER CODE BEGIN StartGetLEDStatus */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  osThreadTerminate(NULL);
  /* USER CODE END StartGetLEDStatus */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

