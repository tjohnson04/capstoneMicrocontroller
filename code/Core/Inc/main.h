/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

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
#define MOTOR_NS_Pin GPIO_PIN_13
#define MOTOR_NS_GPIO_Port GPIOC
#define LED_Column8_Pin GPIO_PIN_4
#define LED_Column8_GPIO_Port GPIOA
#define LED_Column6_Pin GPIO_PIN_5
#define LED_Column6_GPIO_Port GPIOA
#define LED_Column4_Pin GPIO_PIN_6
#define LED_Column4_GPIO_Port GPIOA
#define LED_Column7_Pin GPIO_PIN_7
#define LED_Column7_GPIO_Port GPIOA
#define LED_Column5_Pin GPIO_PIN_0
#define LED_Column5_GPIO_Port GPIOB
#define LED_Column3_Pin GPIO_PIN_1
#define LED_Column3_GPIO_Port GPIOB
#define LED_Column2_Pin GPIO_PIN_2
#define LED_Column2_GPIO_Port GPIOB
#define LED_Column1_Pin GPIO_PIN_10
#define LED_Column1_GPIO_Port GPIOB
#define LED_Row16_Pin GPIO_PIN_11
#define LED_Row16_GPIO_Port GPIOB
#define LED_Row14_Pin GPIO_PIN_12
#define LED_Row14_GPIO_Port GPIOB
#define LED_Row12_Pin GPIO_PIN_14
#define LED_Row12_GPIO_Port GPIOB
#define LED_Row10_Pin GPIO_PIN_15
#define LED_Row10_GPIO_Port GPIOB
#define LED_Row8_Pin GPIO_PIN_8
#define LED_Row8_GPIO_Port GPIOA
#define LED_Row6_Pin GPIO_PIN_9
#define LED_Row6_GPIO_Port GPIOA
#define LED_Row4_Pin GPIO_PIN_6
#define LED_Row4_GPIO_Port GPIOC
#define LED_Row2_Pin GPIO_PIN_7
#define LED_Row2_GPIO_Port GPIOC
#define LED_Row15_Pin GPIO_PIN_8
#define LED_Row15_GPIO_Port GPIOD
#define LED_Row13_Pin GPIO_PIN_9
#define LED_Row13_GPIO_Port GPIOD
#define LED_Row11_Pin GPIO_PIN_10
#define LED_Row11_GPIO_Port GPIOA
#define LED_Row9_Pin GPIO_PIN_11
#define LED_Row9_GPIO_Port GPIOA
#define LED_Row7_Pin GPIO_PIN_15
#define LED_Row7_GPIO_Port GPIOA
#define LED_Row5_Pin GPIO_PIN_8
#define LED_Row5_GPIO_Port GPIOC
#define LED_Row3_Pin GPIO_PIN_9
#define LED_Row3_GPIO_Port GPIOC
#define LED_Row1_Pin GPIO_PIN_0
#define LED_Row1_GPIO_Port GPIOD
#define LED_Column16_Pin GPIO_PIN_1
#define LED_Column16_GPIO_Port GPIOD
#define LED_Column15_Pin GPIO_PIN_2
#define LED_Column15_GPIO_Port GPIOD
#define LED_Column14_Pin GPIO_PIN_3
#define LED_Column14_GPIO_Port GPIOD
#define LED_Column12_Pin GPIO_PIN_4
#define LED_Column12_GPIO_Port GPIOD
#define LED_Column10_Pin GPIO_PIN_5
#define LED_Column10_GPIO_Port GPIOD
#define LED_Column13_Pin GPIO_PIN_6
#define LED_Column13_GPIO_Port GPIOD
#define LED_Column11_Pin GPIO_PIN_4
#define LED_Column11_GPIO_Port GPIOB
#define LED_Column9_Pin GPIO_PIN_5
#define LED_Column9_GPIO_Port GPIOB
#define SPI2_NSS_Pin GPIO_PIN_8
#define SPI2_NSS_GPIO_Port GPIOB
#define SPI2_NSS_EXTI_IRQn EXTI4_15_IRQn

/* USER CODE BEGIN Private defines */
#define SD_SPI_HANDLE hspi2
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
