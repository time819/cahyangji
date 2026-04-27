/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "stm32f7xx_hal.h"

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
#define DO8_Pin GPIO_PIN_2
#define DO8_GPIO_Port GPIOE
#define DO7_Pin GPIO_PIN_3
#define DO7_GPIO_Port GPIOE
#define DO6_Pin GPIO_PIN_4
#define DO6_GPIO_Port GPIOE
#define DO5_Pin GPIO_PIN_13
#define DO5_GPIO_Port GPIOC
#define DA1_SW_Pin GPIO_PIN_14
#define DA1_SW_GPIO_Port GPIOC
#define CAN3_RESIS_Pin GPIO_PIN_15
#define CAN3_RESIS_GPIO_Port GPIOC
#define CAN_SW_1_3_Pin GPIO_PIN_0
#define CAN_SW_1_3_GPIO_Port GPIOF
#define CAN1_RESIS_Pin GPIO_PIN_1
#define CAN1_RESIS_GPIO_Port GPIOF
#define ADC3_IN10_Pin GPIO_PIN_0
#define ADC3_IN10_GPIO_Port GPIOC
#define ADC3_IN10_EXTI_IRQn EXTI0_IRQn
#define DA2_SW_Pin GPIO_PIN_11
#define DA2_SW_GPIO_Port GPIOF
#define M5_SEL_Pin GPIO_PIN_12
#define M5_SEL_GPIO_Port GPIOF
#define POER_CTR_Pin GPIO_PIN_13
#define POER_CTR_GPIO_Port GPIOF
#define CS_SEL0_Pin GPIO_PIN_14
#define CS_SEL0_GPIO_Port GPIOF
#define POWER_MONITOR_Pin GPIO_PIN_1
#define POWER_MONITOR_GPIO_Port GPIOG
#define DO1_Pin GPIO_PIN_9
#define DO1_GPIO_Port GPIOE
#define PD01_Pin GPIO_PIN_10
#define PD01_GPIO_Port GPIOE
#define DO2_Pin GPIO_PIN_11
#define DO2_GPIO_Port GPIOE
#define PDO2_Pin GPIO_PIN_12
#define PDO2_GPIO_Port GPIOE
#define PDO4_Pin GPIO_PIN_13
#define PDO4_GPIO_Port GPIOE
#define PDO3_Pin GPIO_PIN_14
#define PDO3_GPIO_Port GPIOE
#define DO4_Pin GPIO_PIN_15
#define DO4_GPIO_Port GPIOE
#define DO3_Pin GPIO_PIN_10
#define DO3_GPIO_Port GPIOB
#define RS485_DIR_Pin GPIO_PIN_11
#define RS485_DIR_GPIO_Port GPIOB
#define M5_INB_Pin GPIO_PIN_8
#define M5_INB_GPIO_Port GPIOD
#define M5_INA_Pin GPIO_PIN_9
#define M5_INA_GPIO_Port GPIOD
#define LSDO2_Pin GPIO_PIN_10
#define LSDO2_GPIO_Port GPIOD
#define LSDO1_Pin GPIO_PIN_11
#define LSDO1_GPIO_Port GPIOD
#define M5_PWM_Pin GPIO_PIN_12
#define M5_PWM_GPIO_Port GPIOD
#define M3_INB_Pin GPIO_PIN_15
#define M3_INB_GPIO_Port GPIOD
#define M3_INA_Pin GPIO_PIN_2
#define M3_INA_GPIO_Port GPIOG
#define M2_INB_Pin GPIO_PIN_3
#define M2_INB_GPIO_Port GPIOG
#define M2_INA_Pin GPIO_PIN_4
#define M2_INA_GPIO_Port GPIOG
#define DO9_Pin GPIO_PIN_5
#define DO9_GPIO_Port GPIOG
#define DO10_Pin GPIO_PIN_6
#define DO10_GPIO_Port GPIOG
#define LSDO4_Pin GPIO_PIN_7
#define LSDO4_GPIO_Port GPIOG
#define LSDO3_Pin GPIO_PIN_8
#define LSDO3_GPIO_Port GPIOG
#define AD3_3_0V_SEL_Pin GPIO_PIN_8
#define AD3_3_0V_SEL_GPIO_Port GPIOC
#define LOW_CTR3_Pin GPIO_PIN_9
#define LOW_CTR3_GPIO_Port GPIOC
#define LOW_CTR2_Pin GPIO_PIN_9
#define LOW_CTR2_GPIO_Port GPIOA
#define LOW_CTR1_Pin GPIO_PIN_10
#define LOW_CTR1_GPIO_Port GPIOA
#define WPOW_Pin GPIO_PIN_1
#define WPOW_GPIO_Port GPIOD
#define E43_M1_Pin GPIO_PIN_3
#define E43_M1_GPIO_Port GPIOD
#define E43_M0_Pin GPIO_PIN_4
#define E43_M0_GPIO_Port GPIOD
#define REL_SUP_Pin GPIO_PIN_7
#define REL_SUP_GPIO_Port GPIOD
#define M1_SEL_Pin GPIO_PIN_9
#define M1_SEL_GPIO_Port GPIOG
#define M4_SEL_Pin GPIO_PIN_10
#define M4_SEL_GPIO_Port GPIOG
#define REL_STAR_Pin GPIO_PIN_11
#define REL_STAR_GPIO_Port GPIOG
#define REL_ACC_Pin GPIO_PIN_12
#define REL_ACC_GPIO_Port GPIOG
#define REL_COM_Pin GPIO_PIN_13
#define REL_COM_GPIO_Port GPIOG
#define CAN2_RSIS_Pin GPIO_PIN_14
#define CAN2_RSIS_GPIO_Port GPIOG
#define M4_INB_Pin GPIO_PIN_15
#define M4_INB_GPIO_Port GPIOG
#define M4_INA_Pin GPIO_PIN_3
#define M4_INA_GPIO_Port GPIOB
#define CS_SEL1_Pin GPIO_PIN_7
#define CS_SEL1_GPIO_Port GPIOB
#define M1_INB_Pin GPIO_PIN_0
#define M1_INB_GPIO_Port GPIOE
#define M1_INA_Pin GPIO_PIN_1
#define M1_INA_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
