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
#include "stm32g0xx_hal.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_gpio.h"

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
#define OUT_4_Pin GPIO_PIN_11
#define OUT_4_GPIO_Port GPIOC
#define OUT_3_Pin GPIO_PIN_12
#define OUT_3_GPIO_Port GPIOC
#define OUT_2_Pin GPIO_PIN_13
#define OUT_2_GPIO_Port GPIOC
#define OUT_1_Pin GPIO_PIN_14
#define OUT_1_GPIO_Port GPIOC
#define OUT_0_Pin GPIO_PIN_15
#define OUT_0_GPIO_Port GPIOC
#define STATUS_Pin GPIO_PIN_0
#define STATUS_GPIO_Port GPIOC
#define IN_0_Pin GPIO_PIN_1
#define IN_0_GPIO_Port GPIOC
#define IN_1_Pin GPIO_PIN_2
#define IN_1_GPIO_Port GPIOC
#define IN_2_Pin GPIO_PIN_3
#define IN_2_GPIO_Port GPIOC
#define IN_3_Pin GPIO_PIN_1
#define IN_3_GPIO_Port GPIOA
#define SPI1_CS1_Pin GPIO_PIN_1
#define SPI1_CS1_GPIO_Port GPIOB
#define SPI1_CS2_Pin GPIO_PIN_2
#define SPI1_CS2_GPIO_Port GPIOB
#define IN_4_Pin GPIO_PIN_12
#define IN_4_GPIO_Port GPIOB
#define IN_5_Pin GPIO_PIN_13
#define IN_5_GPIO_Port GPIOB
#define IN_6_Pin GPIO_PIN_14
#define IN_6_GPIO_Port GPIOB
#define IN_7_Pin GPIO_PIN_15
#define IN_7_GPIO_Port GPIOB
#define IN_8_Pin GPIO_PIN_8
#define IN_8_GPIO_Port GPIOA
#define IN_9_Pin GPIO_PIN_9
#define IN_9_GPIO_Port GPIOA
#define IN_10_Pin GPIO_PIN_6
#define IN_10_GPIO_Port GPIOC
#define IN_11_Pin GPIO_PIN_7
#define IN_11_GPIO_Port GPIOC
#define IN_12_Pin GPIO_PIN_8
#define IN_12_GPIO_Port GPIOD
#define IN_13_Pin GPIO_PIN_9
#define IN_13_GPIO_Port GPIOD
#define IN_14_Pin GPIO_PIN_10
#define IN_14_GPIO_Port GPIOA
#define IN_15_Pin GPIO_PIN_11
#define IN_15_GPIO_Port GPIOA
#define OUT_23_Pin GPIO_PIN_12
#define OUT_23_GPIO_Port GPIOA
#define OUT_22_Pin GPIO_PIN_15
#define OUT_22_GPIO_Port GPIOA
#define OUT_21_Pin GPIO_PIN_8
#define OUT_21_GPIO_Port GPIOC
#define OUT_20_Pin GPIO_PIN_9
#define OUT_20_GPIO_Port GPIOC
#define OUT_19_Pin GPIO_PIN_0
#define OUT_19_GPIO_Port GPIOD
#define OUT_18_Pin GPIO_PIN_1
#define OUT_18_GPIO_Port GPIOD
#define OUT_17_Pin GPIO_PIN_2
#define OUT_17_GPIO_Port GPIOD
#define OUT_16_Pin GPIO_PIN_3
#define OUT_16_GPIO_Port GPIOD
#define OUT_15_Pin GPIO_PIN_4
#define OUT_15_GPIO_Port GPIOD
#define OUT_14_Pin GPIO_PIN_5
#define OUT_14_GPIO_Port GPIOD
#define OUT_13_Pin GPIO_PIN_6
#define OUT_13_GPIO_Port GPIOD
#define OUT_12_Pin GPIO_PIN_3
#define OUT_12_GPIO_Port GPIOB
#define OUT_11_Pin GPIO_PIN_4
#define OUT_11_GPIO_Port GPIOB
#define OUT_10_Pin GPIO_PIN_5
#define OUT_10_GPIO_Port GPIOB
#define OUT_9_Pin GPIO_PIN_6
#define OUT_9_GPIO_Port GPIOB
#define OUT_8_Pin GPIO_PIN_7
#define OUT_8_GPIO_Port GPIOB
#define OUT_7_Pin GPIO_PIN_8
#define OUT_7_GPIO_Port GPIOB
#define OUT_6_Pin GPIO_PIN_9
#define OUT_6_GPIO_Port GPIOB
#define OUT_5_Pin GPIO_PIN_10
#define OUT_5_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
