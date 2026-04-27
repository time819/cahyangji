/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
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
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "USER_DATA_TYPE.h"
/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan1;

extern CAN_HandleTypeDef hcan2;

extern CAN_HandleTypeDef hcan3;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_CAN1_Init(void);
void MX_CAN2_Init(void);
void MX_CAN3_Init(void);

/* USER CODE BEGIN Prototypes */



extern void CAN1_Filter_Init(void);
extern void CAN2_Filter_Init(void);
extern void CAN3_Filter_Init(void);

extern uint32 can_mask_value(void);
extern  void user_can_EXTID_send(CAN_HandleTypeDef *hcan,uint32 extid,uint8 *TxData, uint32_t *pTxMailbox);
extern void CAN2_SendData(uint32_t Device_ID,uint8_t *TX_msg,uint8_t TX_len);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

