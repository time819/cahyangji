/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dma.h
  * @brief   This file contains all the function prototypes for
  *          the dma.c file
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
#ifndef __DMA_H__
#define __DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* DMA memory to memory transfer handles -------------------------------------*/

/* USER CODE BEGIN Includes */
#include "USER_GLOBAL.h"

//#define ADC1_BUFF_SIZE 120 //10个数据，每个数据12个样本
//#define ADC3_BUFF_SIZE 168 //14个数据，每个数据12个样本
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

//extern uint32 ADC1_buff[ ADC1_BUFF_SIZE] ;
//extern uint32 ADC3_buff[ ADC3_BUFF_SIZE];
extern uint32 ADC1_buff[ 10] ;
extern uint32 ADC3_buff[ 15];
extern volatile int clutch_ctr[3];
extern  volatile int AD_EXT_value[4];
extern  volatile u32 AD_SEN_value[5];
/* USER CODE END Private defines */

void MX_DMA_Init(void);

/* USER CODE BEGIN Prototypes */

extern volatile  int AD_CH_value[12];//处理后的最终的二进制数

extern void user_ad_dma_init(void);
extern void user_AD_val_get(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __DMA_H__ */

