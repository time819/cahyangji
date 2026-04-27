/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "USER_DATA_TYPE.h"
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
extern void user_stop_start_pin_init(void);
extern void user_engine_stop(void);
extern void user_engine_start(void);
extern void user_moter_stop(uint8 moter_num);
extern void user_moter_backward(uint8 moter_num,uint16 cycle);
extern void user_moter_forward(uint8 moter_num,uint16 cycle);
extern void user_moter_current_detect(uint8 AB_num);
extern void user_DA_SW(uint8 DA_type,uint8 ctr);
void user_DA_value(uint8 DA_type,uint16 val1,uint16 val2)	;//电子油门双通道赋值
extern void user_moter_power_ctr(uint8 ctr);
void user_pend_switch_init(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

