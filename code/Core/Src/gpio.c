/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, MOTOR_NS_Pin|LED_Row13_Pin|LED_Row15_Pin|LED_Row4_Pin
                          |LED_Row2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_Column8_Pin|LED_Column10_Pin|LED_Column12_Pin|LED_Column9_Pin
                          |LED_Row9_Pin|LED_Row11_Pin|LED_Row10_Pin|LED_Row8_Pin
                          |LED_Row6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_Column11_Pin|LED_Column13_Pin|LED_Column14_Pin|LED_Column15_Pin
                          |LED_Row1_Pin|LED_Row3_Pin|LED_Row5_Pin|LED_Row7_Pin
                          |LED_Column5_Pin|LED_Column7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LED_Row14_Pin|LED_Row12_Pin|LED_Row0_Pin|LED_Column0_Pin
                          |LED_Column1_Pin|LED_Column2_Pin|LED_Column4_Pin|LED_Column6_Pin
                          |LED_Column3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : MOTOR_NS_Pin LED_Row13_Pin LED_Row15_Pin LED_Row4_Pin
                           LED_Row2_Pin */
  GPIO_InitStruct.Pin = MOTOR_NS_Pin|LED_Row13_Pin|LED_Row15_Pin|LED_Row4_Pin
                          |LED_Row2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_Column8_Pin LED_Column10_Pin LED_Column12_Pin LED_Column9_Pin
                           LED_Row9_Pin LED_Row11_Pin LED_Row10_Pin LED_Row8_Pin
                           LED_Row6_Pin */
  GPIO_InitStruct.Pin = LED_Column8_Pin|LED_Column10_Pin|LED_Column12_Pin|LED_Column9_Pin
                          |LED_Row9_Pin|LED_Row11_Pin|LED_Row10_Pin|LED_Row8_Pin
                          |LED_Row6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_Column11_Pin LED_Column13_Pin LED_Column14_Pin LED_Column15_Pin
                           LED_Row1_Pin LED_Row3_Pin LED_Row5_Pin LED_Row7_Pin
                           LED_Column5_Pin LED_Column7_Pin */
  GPIO_InitStruct.Pin = LED_Column11_Pin|LED_Column13_Pin|LED_Column14_Pin|LED_Column15_Pin
                          |LED_Row1_Pin|LED_Row3_Pin|LED_Row5_Pin|LED_Row7_Pin
                          |LED_Column5_Pin|LED_Column7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_Row14_Pin LED_Row12_Pin LED_Row0_Pin LED_Column0_Pin
                           LED_Column1_Pin LED_Column2_Pin LED_Column4_Pin LED_Column6_Pin
                           LED_Column3_Pin */
  GPIO_InitStruct.Pin = LED_Row14_Pin|LED_Row12_Pin|LED_Row0_Pin|LED_Column0_Pin
                          |LED_Column1_Pin|LED_Column2_Pin|LED_Column4_Pin|LED_Column6_Pin
                          |LED_Column3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI2_NSS_Pin */
  GPIO_InitStruct.Pin = SPI2_NSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SPI2_NSS_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
