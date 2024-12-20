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
 *  FatFs code based on tutorial project by kiwih at https://github.com/kiwih/cubeide-sd-card
 *  Portions copyright (c) 2020 STMicroelectronics International N.V., all rights reserved.
 *  Portions copyright (C) 2014, ChaN, all rights reserved.
 *  Portions copyright (C) 2017, 2020, kiwih, all rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted, provided that the following conditions are met:
 *
 *  1. Redistribution of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. Neither the name of STMicroelectronics nor the names of other
 *     contributors to this software may be used to endorse or promote products
 *     derived from this software without specific written permission.
 *  4. This software, including modifications and/or derivative works of this
 *     software, must execute solely and exclusively on microcontroller or
 *     microprocessor devices manufactured by or for STMicroelectronics.
 *  5. Redistribution and use of this software other than as permitted under
 *     this license is void and will automatically terminate your rights under
 *     this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "app_fatfs.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <stdarg.h> //for va_list var arg functions
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BUFFER_SIZE 64

//#define TEST_LEDS
#define TEST_SD
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t current_frame = 0;
extern uint16_t image_leds[55][16];

extern GPIO_TypeDef *led_column_ports[];
extern uint16_t led_column_pins[];
extern GPIO_TypeDef *led_row_ports[];
extern uint16_t led_row_pins[];

uint8_t OutputBuffer[BUFFER_SIZE];
uint16_t i = 0;
uint8_t ReceiveCharacter = 0;

uint8_t rx_buffer[BUFFER_SIZE];
uint8_t rx_index = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
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
  if (MX_FATFS_Init() != APP_OK) {
    Error_Handler();
  }
  MX_I2C1_Init();
  MX_ADC1_Init();
  MX_SPI2_Init();
  MX_TIM14_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  if (HAL_TIM_Base_Start_IT(&htim3) != HAL_OK) {
	  Error_Handler();
  }

//  SD card testing code
#ifdef TEST_SD
  for (uint8_t i = 0; i < 16; i++) {
	  HAL_GPIO_WritePin(led_row_ports[i], led_row_pins[i], GPIO_PIN_SET);
  }
  for (i = 0; i < 16; i++) {
	  HAL_GPIO_WritePin(led_column_ports[i], led_column_pins[i], GPIO_PIN_SET);
  }
  HAL_GPIO_WritePin(led_row_ports[0], led_row_pins[0], GPIO_PIN_RESET);


  HAL_Delay(1000); // short delay to let the SD card settle

  // some variables for FatFs
  FATFS FatFs; 	// Fatfs handle
  FIL fil; 		// File handle
  FRESULT fres; 	// Result after operations

  // open the file system
  fres = f_mount(&FatFs, "", 1); //1=mount now
  if (fres != FR_OK) {
	  HAL_GPIO_WritePin(led_row_ports[15], led_row_pins[15], GPIO_PIN_RESET);
	  while(1);
  }
  HAL_GPIO_WritePin(led_row_ports[1], led_row_pins[1], GPIO_PIN_RESET);

  // gather statistics from the SD card
  DWORD free_clusters;

  FATFS* getFreeFs;

  fres = f_getfree("", &free_clusters, &getFreeFs);
  if (fres != FR_OK) {
	  while(1);
  }

  HAL_GPIO_WritePin(led_row_ports[2], led_row_pins[2], GPIO_PIN_RESET);

  //Now let's try to open file "test.txt"
  fres = f_open(&fil, "test.txt", FA_READ);
  if (fres != FR_OK) {
	  HAL_GPIO_WritePin(led_row_ports[15], led_row_pins[15], GPIO_PIN_RESET);
	  while(1);
  }

  HAL_GPIO_WritePin(led_row_ports[3], led_row_pins[3], GPIO_PIN_RESET);



  BYTE readBuf[17];
  int x = -1;
  int x3 = 0;
  int image = 0;
  char fullText[128];
  unsigned int decimal_value = 0;
  memset(fullText, 0, sizeof(fullText));
  TCHAR* rres3 = "4";
  if(rres3 != 0) {
	  while (x < 1760) { //this states limit of how big the txt is
		  f_gets((TCHAR*)readBuf, 17, &fil);
		  x += 1;
		  decimal_value = 0;
		  if ((x+1) % 2 == 1) {
			  // Concatenate the read line to the full text buffer
			  for (int i = 0; i < 16; i++) { // the 16 bits when running
				  // Convert '1' or '0' char to its integer value
				  int bit_value = readBuf[i] - '0'; // '1' - '0' = 1, '0' - '0' = 0

				  // Update the decimal value
				  decimal_value = (decimal_value << 1) | bit_value; // Left-shift and add the current bit
			  }
			  image_leds[image][x3] = decimal_value;
			  x3 += 1;
		  }
		  if (x3 > 15) {
			  image += 1;
			  x3 = 0;
		  }
	  }
  } else {
	  HAL_GPIO_WritePin(led_row_ports[15], led_row_pins[15], GPIO_PIN_RESET);
	  while (1);
  }

  HAL_GPIO_WritePin(led_row_ports[4], led_row_pins[4], GPIO_PIN_RESET);

  f_close(&fil);

  HAL_GPIO_WritePin(led_row_ports[5], led_row_pins[5], GPIO_PIN_RESET);

  //We're done, so de-mount the drive
  f_mount(NULL, "", 0);

  HAL_GPIO_WritePin(led_row_ports[6], led_row_pins[6], GPIO_PIN_RESET);



#elif TEST_LEDS
  	// nmos = columns | pmos = rows
  	for (uint8_t j = 0; j < 16; j++) {
  		HAL_GPIO_WritePin(led_column_ports[j], led_column_pins[j], GPIO_PIN_SET);
  	}

  	for (uint8_t i = 0; i < 16; i++) {
  		HAL_GPIO_WritePin(led_row_ports[i], led_row_pins[i], GPIO_PIN_SET);
  	}
  	i = 0;
  	while (1) {
  		HAL_GPIO_WritePin(led_row_ports[i], led_row_pins[i], GPIO_PIN_RESET);
  		HAL_Delay(25);
  		HAL_GPIO_WritePin(led_row_ports[i], led_row_pins[i], GPIO_PIN_SET);
  		i++;
  		if (i > 15) i = 0;
  	}
#else
//  	for (uint8_t i = 0; i < 55; i++) {
//  		image_leds[i][0] = 0xFFFF;
//  		image_leds[i][1] = 0xFFFF;
//  		image_leds[i][2] = 0xFFFF;
//  		image_leds[i][3] = 0xFFFF;
//  		image_leds[i][4] = 0x0000;
//  		image_leds[i][5] = 0x0000;
//  		image_leds[i][6] = 0x0000;
//  		image_leds[i][7] = 0x0000;
//  		image_leds[i][8] = 0x0000;
//  		image_leds[i][9] = 0x0000;
//  		image_leds[i][10] = 0x0000;
//  		image_leds[i][11] = 0x0000;
//  		image_leds[i][12] = 0xFFFF;
//  		image_leds[i][13] = 0xFFFF;
//  		image_leds[i][14] = 0xFFFF;
//  		image_leds[i][15] = 0xFFFF;
//  	}
  	for (uint8_t i = 0; i < 55; i++) {
  	  image_leds[i][0] = 0x0000;
	  image_leds[i][1] = 0x0000;
	  image_leds[i][2] = 0x0000;
	  image_leds[i][3] = 0x0000;
	  image_leds[i][4] = 0x0000;
	  image_leds[i][5] = 0x0000;
	  image_leds[i][6] = 0x0000;
	  image_leds[i][7] = 0x0000;
	  image_leds[i][8] = 0x0000;
	  image_leds[i][9] = 0x0000;
	  image_leds[i][10] = 0x0000;
	  image_leds[i][11] = 0x0000;
	  image_leds[i][12] = 0x0000;
	  image_leds[i][13] = 0x0000;
	  image_leds[i][14] = 0x0000;
	  image_leds[i][15] = 0x0000;

	  image_leds[i][i % 16] = 0xFFFF;
  }
#endif
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* Call init function for freertos objects (in cmsis_os2.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	while (1)
	{

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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void ReadSD() {
	HAL_Delay(1000); // short delay to let the SD card settle

	// some variables for FatFs
	FATFS FatFs; 	// Fatfs handle
	FIL fil; 		// File handle
	FRESULT fres; 	// Result after operations

	// open the file system
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK) {
		while(1);
	}

	// gather statistics from the SD card
	DWORD free_clusters;

	FATFS* getFreeFs;

	fres = f_getfree("", &free_clusters, &getFreeFs);
	if (fres != FR_OK) {
		while(1);
	}

	//Now let's try to open file "test.txt"
	fres = f_open(&fil, "full_obj_output.txt", FA_READ);
	if (fres != FR_OK) {
		while(1);
	}

	BYTE readBuf[17];
	int x = -1;
	int x3 = 0;
	int image = 0;
	char fullText[128];
	unsigned int decimal_value = 0;
	memset(fullText, 0, sizeof(fullText));
	TCHAR* rres3 = "4";
	if(rres3 != 0) {
		while (x < 1760) { //this states limit of how big the txt is
			f_gets((TCHAR*)readBuf, 17, &fil);
			x += 1;
			decimal_value = 0;
			if ((x+1) % 2 == 1) {
				// Concatenate the read line to the full text buffer
				for (int i = 0; i < 16; i++) { // the 16 bits when running
					// Convert '1' or '0' char to its integer value
					int bit_value = readBuf[i] - '0'; // '1' - '0' = 1, '0' - '0' = 0

					// Update the decimal value
					decimal_value = (decimal_value << 1) | bit_value; // Left-shift and add the current bit
				}
				image_leds[image][x3] = decimal_value;
				x3 += 1;
			}
			if (x3 > 15) {
				image += 1;
				x3 = 0;
			}
		}

	}

	f_close(&fil);
	f_mount(NULL, "", 0);
}

//
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin) {
	// If chip select pin goes low, SD card was plugged in
	if (GPIO_Pin == SPI2_NSS_Pin) {
		// critical section to stop scheduler from exiting SD mount
		taskENTER_CRITICAL();
		ReadSD();
		taskEXIT_CRITICAL();
	}
}

// Callback for data reception
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C1) {
        // Handle received data
    	FIL fil; 		// File handle
    	BYTE readBuf[17];
    	int x = -1;
    	int x3 = 0;
    	int image = 0;
    	char fullText[128];
    	unsigned int decimal_value = 0;
    	memset(fullText, 0, sizeof(fullText));
    	TCHAR* rres3 = "4";
    	if (rres3 != 0) {
    		while (x < 1760) { //this states limit of how big the txt is
    			f_gets((TCHAR*)readBuf, 17, &fil);
    			x += 1;
    			decimal_value = 0;
    			if ((x+1) % 2 == 1) {
    				// Concatenate the read line to the full text buffer
    				for (int i = 0; i < 16; i++) { // the 16 bits when running
    					// Convert '1' or '0' char to its integer value
    					int bit_value = readBuf[i] - '0'; // '1' - '0' = 1, '0' - '0' = 0

    					// Update the decimal value
    					decimal_value = (decimal_value << 1) | bit_value; // Left-shift and add the current bit
    				}
    				image_leds[image][x3] = decimal_value;
    				x3 += 1;
    			}
    			if (x3 > 15) {
    				image += 1;
    				x3 = 0;
    			}
    		}
    	}
    	// For example, restart reception or process the received data
    	HAL_I2C_Master_Receive_IT(&hi2c1, 0x70, rx_buffer, BUFFER_SIZE);
    }
}

// Error callback
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C1) {
        // Handle I2C error
        Error_Handler();
    }
}

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
  if (htim->Instance == TIM3) {
	current_frame = (current_frame + 1) % 55;
  }
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
