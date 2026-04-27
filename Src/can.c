/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
#include "cmsis_os.h"
#include "USER_FREE_RT_OS.h"
//can 输入时钟为系统时钟2分频
//CAN波特率为 can输入时钟  / CAN_Prescaler / (CAN_BS1+CAN_BS2+1) 

/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;
CAN_HandleTypeDef hcan3;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 25;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_4TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_3TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}
/* CAN2 init function */
void MX_CAN2_Init(void)
{

  /* USER CODE BEGIN CAN2_Init 0 */

  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 25;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_4TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_3TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = DISABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */

  /* USER CODE END CAN2_Init 2 */

}
/* CAN3 init function */
void MX_CAN3_Init(void)
{

  /* USER CODE BEGIN CAN3_Init 0 */

  /* USER CODE END CAN3_Init 0 */

  /* USER CODE BEGIN CAN3_Init 1 */

  /* USER CODE END CAN3_Init 1 */
  hcan3.Instance = CAN3;
  hcan3.Init.Prescaler = 25;
  hcan3.Init.Mode = CAN_MODE_NORMAL;
  hcan3.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan3.Init.TimeSeg1 = CAN_BS1_4TQ;
  hcan3.Init.TimeSeg2 = CAN_BS2_3TQ;
  hcan3.Init.TimeTriggeredMode = DISABLE;
  hcan3.Init.AutoBusOff = DISABLE;
  hcan3.Init.AutoWakeUp = DISABLE;
  hcan3.Init.AutoRetransmission = DISABLE;
  hcan3.Init.ReceiveFifoLocked = DISABLE;
  hcan3.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN3_Init 2 */

  /* USER CODE END CAN3_Init 2 */

}

static uint32_t HAL_RCC_CAN1_CLK_ENABLED=0;

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspInit 0 */

  /* USER CODE END CAN2_MspInit 0 */
    /* CAN2 clock enable */
    __HAL_RCC_CAN2_CLK_ENABLE();
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN2 GPIO Configuration
    PB5     ------> CAN2_RX
    PB6     ------> CAN2_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN2 interrupt Init */
    HAL_NVIC_SetPriority(CAN2_RX1_IRQn, 7, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX1_IRQn);
  /* USER CODE BEGIN CAN2_MspInit 1 */
//		 __HAL_CAN_ENABLE_IT(&CAN1_Handler,CAN_IT_FMP0); 
  /* USER CODE END CAN2_MspInit 1 */
  }
  else if(canHandle->Instance==CAN3)
  {
  /* USER CODE BEGIN CAN3_MspInit 0 */

  /* USER CODE END CAN3_MspInit 0 */
    /* CAN3 clock enable */
    __HAL_RCC_CAN3_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN3 GPIO Configuration
    PA8     ------> CAN3_RX
    PA15     ------> CAN3_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF11_CAN3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN3 interrupt Init */
    HAL_NVIC_SetPriority(CAN3_RX0_IRQn, 8, 0);
    HAL_NVIC_EnableIRQ(CAN3_RX0_IRQn);
  /* USER CODE BEGIN CAN3_MspInit 1 */

  /* USER CODE END CAN3_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspDeInit 0 */

  /* USER CODE END CAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN2_CLK_DISABLE();
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN2 GPIO Configuration
    PB5     ------> CAN2_RX
    PB6     ------> CAN2_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5|GPIO_PIN_6);

    /* CAN2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN2_RX1_IRQn);
  /* USER CODE BEGIN CAN2_MspDeInit 1 */

  /* USER CODE END CAN2_MspDeInit 1 */
  }
  else if(canHandle->Instance==CAN3)
  {
  /* USER CODE BEGIN CAN3_MspDeInit 0 */

  /* USER CODE END CAN3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN3_CLK_DISABLE();

    /**CAN3 GPIO Configuration
    PA8     ------> CAN3_RX
    PA15     ------> CAN3_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8|GPIO_PIN_15);

    /* CAN3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN3_RX0_IRQn);
  /* USER CODE BEGIN CAN3_MspDeInit 1 */

  /* USER CODE END CAN3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/*************************************************				CAN 配置					****************************************************************************/ 

/**
* @brief   按位比较数组内每个数，对应位都相等时为1，其余情况为0。由低到高按位返回
* @param   numbers      数组地址
* @param   size         数组元素个数
* @param   bitPosition  数据位数
* @retval  按位返回比较结果
*/
uint8_t checkSameBits(uint32_t *numbers, uint8_t size, uint8_t bitPosition) 
{
    int firstBit = (numbers[0] >> bitPosition) & 1;
    for (int i = 1; i < size; i++) //所有数据依次比较
    {
        if (((numbers[i] >> bitPosition) & 1)!= firstBit) //有数据不同，返回0
        {
            return 0;
        }
    }
    return 1;  //所有数据都相同
}

/**
* @brief   计算需要筛选的数据和位
* @param   numbers      数组地址
* @retval  按位返回比较结果
*/
uint8_t can_temp = 0;
uint8_t can_size = 0;
uint32_t can_msk_data = 0xFFFFFFFF;  //需要筛选的数据
uint32_t can_msk_bit = 0;   //需要筛选的位
uint32_t can1_ext_id[] = {0x0C900101,0x0C900201,0x0C900301,0x0C900401}; 
uint32_t can2_ext_id[] = {0x0CFF5326,0x0C900601,0x0CF0E426};  //掩码模式过滤id
uint32_t can3_ext_id[] = {0x04853001};
            
//掩码模式筛选的数值和过滤的位计算                
uint32_t msk_data(uint32_t *can_data) 
{
    can_msk_data = 0xFFFFFFFF; //每次计算前先清除
    can_msk_bit = 0;
    for(uint8_t i = 0; i < can_size; i++)  //所有元素进行与运算，得到筛选数值
    {
       can_msk_data = can_msk_data & can_data[i];
    }
  
    for (uint8_t bit = 0; bit < 32; bit++)  //计算过滤的位（所有元素位相等的数作为筛选条件）
    {  
        can_temp = checkSameBits(can_data, can_size, bit);
        can_msk_bit = can_temp<<bit | can_msk_bit;
    }
    return 0;
}

/**
 *@brief	CAN1过滤设置,给雷达使用
*/
void CAN1_Filter_Init(void)
{
	CAN_FilterTypeDef CAN_FilterInitStructure;

  can_size = sizeof(can1_ext_id)/sizeof(can1_ext_id[0]);
  msk_data(can1_ext_id);
	CAN_FilterInitStructure.FilterBank = 0;
	CAN_FilterInitStructure.FilterMode = CAN_FILTERMODE_IDMASK;   //掩码模式
	CAN_FilterInitStructure.FilterFIFOAssignment = CAN_RX_FIFO0;  //CANx_RX0_IRQn 关联FIFO0
	CAN_FilterInitStructure.FilterActivation = CAN_FILTER_ENABLE;
	CAN_FilterInitStructure.FilterScale = CAN_FILTERSCALE_32BIT;
  CAN_FilterInitStructure.FilterIdHigh         =   (can_msk_data >> 13) & 0xFFFF;                     //CAN id高16位
  CAN_FilterInitStructure.FilterIdLow          =   (can_msk_data << 3) | CAN_ID_EXT | CAN_RTR_DATA;   //CAN id低13位+帧格式+帧类型+预留位
  CAN_FilterInitStructure.FilterMaskIdHigh     =   (can_msk_bit>> 13) & 0xFFFF;                       //掩码 id高16位
  CAN_FilterInitStructure.FilterMaskIdLow      =   (can_msk_bit << 3) | CAN_ID_EXT | CAN_RTR_DATA;    //掩码 id低13位+帧格式+帧类型+预留位
  CAN_FilterInitStructure.SlaveStartFilterBank = 14;  //主CAN过滤器分配,0-14给主CAN使用，后面给CAN2，
	if (HAL_CAN_ConfigFilter(&hcan1, &CAN_FilterInitStructure) != HAL_OK)
		Error_Handler();  
  
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
		Error_Handler();
  
	if (HAL_CAN_Start(&hcan1) != HAL_OK)
		Error_Handler();
}


/**
 *@brief	CAN2过滤设置，上位机数据
*/
void CAN2_Filter_Init(void)
{
  can_size = sizeof(can2_ext_id)/sizeof(can2_ext_id[0]);
  msk_data(can2_ext_id);
	CAN_FilterTypeDef CAN_FilterInitStructure;
	CAN_FilterInitStructure.FilterBank = 14;
	CAN_FilterInitStructure.FilterMode = CAN_FILTERMODE_IDMASK;
	CAN_FilterInitStructure.FilterFIFOAssignment = CAN_RX_FIFO1;
	CAN_FilterInitStructure.FilterActivation = CAN_FILTER_ENABLE;
	CAN_FilterInitStructure.FilterScale = CAN_FILTERSCALE_32BIT;
  CAN_FilterInitStructure.FilterIdHigh         =   (can_msk_data >> 13) & 0xFFFF;                     //CAN id高16位
  CAN_FilterInitStructure.FilterIdLow          =   (can_msk_data << 3) | CAN_ID_EXT | CAN_RTR_DATA;   //CAN id低13位+帧格式+帧类型+预留位
  CAN_FilterInitStructure.FilterMaskIdHigh     =   (can_msk_bit>> 13) & 0xFFFF;                       //掩码 id高16位
  CAN_FilterInitStructure.FilterMaskIdLow      =   (can_msk_bit << 3) | CAN_ID_EXT | CAN_RTR_DATA;    //掩码 id低13位+帧格式+帧类型+预留位
  
	if (HAL_CAN_ConfigFilter(&hcan2, &CAN_FilterInitStructure) != HAL_OK)
		Error_Handler();
	if (HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK)
		Error_Handler();
	if (HAL_CAN_Start(&hcan2) != HAL_OK)
		Error_Handler();
}


/**
 *@brief	CAN3过滤设置，车上电机驱动器、电池等使用
*/
void CAN3_Filter_Init(void)
{
  can_size = sizeof(can3_ext_id)/sizeof(can3_ext_id[0]);
  msk_data(can3_ext_id);
	CAN_FilterTypeDef CAN_FilterInitStructure;
	CAN_FilterInitStructure.FilterBank = 3;
	CAN_FilterInitStructure.FilterMode = CAN_FILTERMODE_IDMASK;
	CAN_FilterInitStructure.FilterFIFOAssignment = CAN_RX_FIFO0;
  CAN_FilterInitStructure.FilterIdHigh         =   (can_msk_data >> 13) & 0xFFFF;                     //CAN id高16位
  CAN_FilterInitStructure.FilterIdLow          =   (can_msk_data << 3) | CAN_ID_EXT | CAN_RTR_DATA;   //CAN id低13位+帧格式+帧类型+预留位
  CAN_FilterInitStructure.FilterMaskIdHigh     =   (can_msk_bit>> 13) & 0xFFFF;                       //掩码 id高16位
  CAN_FilterInitStructure.FilterMaskIdLow      =   (can_msk_bit << 3) | CAN_ID_EXT | CAN_RTR_DATA;    //掩码 id低13位+帧格式+帧类型+预留位
		
	CAN_FilterInitStructure.FilterActivation = CAN_FILTER_ENABLE;
	CAN_FilterInitStructure.FilterScale = CAN_FILTERSCALE_32BIT;

		
	if (HAL_CAN_ConfigFilter(&hcan3, &CAN_FilterInitStructure) != HAL_OK)
		Error_Handler();
	if (HAL_CAN_ActivateNotification(&hcan3, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
		Error_Handler();
	if (HAL_CAN_Start(&hcan3) != HAL_OK)
		Error_Handler();
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)  //接收回调函数
{
	if(hcan ==&hcan1)
	{	
		uint8_t  Datatemp[8]={0};
		uint8 can1_rx_buff[12]={0};
		CAN_RxHeaderTypeDef     RxMeg;
		HAL_StatusTypeDef	HAL_RetVal;
		
    HAL_RetVal=HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxMeg,  Datatemp);//接收帧头和数据
    if ( HAL_OK==HAL_RetVal)
		{                              			
      //在这里接收数据
			
			
			if(RxMeg.IDE==0x04 )
			{
				can1_rx_buff[0] =RxMeg.ExtId>>24 ;
				can1_rx_buff[1] =RxMeg.ExtId>>16&0x00ff ;
				can1_rx_buff[2] =RxMeg.ExtId>>8&0x0000ff ;
				can1_rx_buff[3] =RxMeg.ExtId&0x000000ff ;		
			}
			else if(RxMeg.IDE==0x00 )
			{
				can1_rx_buff[0] =RxMeg.StdId>>24 ;
				can1_rx_buff[1] =RxMeg.StdId>>16&0x00ff ;
				can1_rx_buff[2] =RxMeg.StdId>>8&0x0000ff ;
				can1_rx_buff[3] =RxMeg.StdId&0x000000ff ;		
			}

			can1_rx_buff[4] = Datatemp[0] ;
			can1_rx_buff[5] = Datatemp[1] ;
			can1_rx_buff[6] = Datatemp[2] ;
			can1_rx_buff[7] = Datatemp[3] ;
			can1_rx_buff[8] = Datatemp[4] ;
			can1_rx_buff[9] = Datatemp[5] ;
			can1_rx_buff[10] = Datatemp[6] ;
			can1_rx_buff[11] = Datatemp[7] ;
			
			osMessageQueuePut(myQueueCan1RevHandle , can1_rx_buff, 0, NULL);//用于中断时，延时要为0
		}
  }
	
	if(hcan ==&hcan2)
	{	
		uint8_t  Datatemp[8]={0};
		uint8 can2_rx_buff[12]={0};
		CAN_RxHeaderTypeDef     RxMeg;
		HAL_StatusTypeDef	HAL_RetVal;
		
    HAL_RetVal=HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxMeg,  Datatemp);//接收帧头和数据
    if ( HAL_OK==HAL_RetVal)
		{                              			
      //在这里接收数据
			
			
			if(RxMeg.IDE==0x04 )
			{
				can2_rx_buff[0] =RxMeg.ExtId>>24 ;
				can2_rx_buff[1] =RxMeg.ExtId>>16&0x00ff ;
				can2_rx_buff[2] =RxMeg.ExtId>>8&0x0000ff ;
				can2_rx_buff[3] =RxMeg.ExtId&0x000000ff ;		
			}
			else if(RxMeg.IDE==0x00 )
			{
				can2_rx_buff[0] =RxMeg.StdId>>24 ;
				can2_rx_buff[1] =RxMeg.StdId>>16&0x00ff ;
				can2_rx_buff[2] =RxMeg.StdId>>8&0x0000ff ;
				can2_rx_buff[3] =RxMeg.StdId&0x000000ff ;		
			}

			
			
			can2_rx_buff[4] = Datatemp[0] ;
			can2_rx_buff[5] = Datatemp[1] ;
			can2_rx_buff[6] = Datatemp[2] ;
			can2_rx_buff[7] = Datatemp[3] ;
			can2_rx_buff[8] = Datatemp[4] ;
			can2_rx_buff[9] = Datatemp[5] ;
			can2_rx_buff[10] = Datatemp[6] ;
			can2_rx_buff[11] = Datatemp[7] ;
			
			osMessageQueuePut(myQueueCan2RevHandle , can2_rx_buff, 0, NULL);//用于中断时，延时要为0
		}
  }
	
}


void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)  //接收回调函数
{
	if(hcan ==&hcan2)
	{	
		uint8_t  Datatemp[8]={0};
		uint8 can2_rx_buff[12]={0};
		CAN_RxHeaderTypeDef     RxMeg;
		HAL_StatusTypeDef	HAL_RetVal;
		
    HAL_RetVal=HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &RxMeg,  Datatemp);//接收帧头和数据
    if ( HAL_OK==HAL_RetVal)
		{                              			
      //在这里接收数据
			
			
			if(RxMeg.IDE==0x04 )
			{
				can2_rx_buff[0] =RxMeg.ExtId>>24 ;
				can2_rx_buff[1] =RxMeg.ExtId>>16&0x00ff ;
				can2_rx_buff[2] =RxMeg.ExtId>>8&0x0000ff ;
				can2_rx_buff[3] =RxMeg.ExtId&0x000000ff ;		
			}
			else if(RxMeg.IDE==0x00 )
			{
				can2_rx_buff[0] =RxMeg.StdId>>24 ;
				can2_rx_buff[1] =RxMeg.StdId>>16&0x00ff ;
				can2_rx_buff[2] =RxMeg.StdId>>8&0x0000ff ;
				can2_rx_buff[3] =RxMeg.StdId&0x000000ff ;		
			}

			can2_rx_buff[4] = Datatemp[0] ;
			can2_rx_buff[5] = Datatemp[1] ;
			can2_rx_buff[6] = Datatemp[2] ;
			can2_rx_buff[7] = Datatemp[3] ;
			can2_rx_buff[8] = Datatemp[4] ;
			can2_rx_buff[9] = Datatemp[5] ;
			can2_rx_buff[10] = Datatemp[6] ;
			can2_rx_buff[11] = Datatemp[7] ;
			
			osMessageQueuePut(myQueueCan2RevHandle , can2_rx_buff, 0, NULL);//用于中断时，延时要为0
		}
  }
}
//can发送数据，只需要id和数据
void user_can_EXTID_send(CAN_HandleTypeDef *hcan,uint32 extid,uint8 *TxData, uint32_t *pTxMailbox)
{
	CAN_TxHeaderTypeDef TxHeader;
 
// CAN_TX_MAILBOX0
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_EXT;            
	TxHeader.StdId = 0;
	TxHeader.ExtId = extid;
	TxHeader.TransmitGlobalTime = DISABLE;
	TxHeader.DLC = 8;

  while(HAL_CAN_GetTxMailboxesFreeLevel(hcan) == 0);		//等待邮箱有空闲		
	HAL_CAN_AddTxMessage(hcan, &TxHeader, TxData, pTxMailbox);

}


void CAN2_SendData(uint32_t Device_ID,uint8_t *TX_msg,uint8_t TX_len)
{
    static CAN_TxHeaderTypeDef  CAN_TX_HDR ;
    
    CAN_TX_HDR.ExtId= Device_ID;
	CAN_TX_HDR.DLC=TX_len;
	CAN_TX_HDR.IDE=CAN_ID_EXT;
	CAN_TX_HDR.RTR=CAN_RTR_DATA;
	CAN_TX_HDR.TransmitGlobalTime = DISABLE;  //关闭时间标签
    while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan2)==0);
	//发送消息过程
	HAL_CAN_AddTxMessage(&hcan2, &CAN_TX_HDR, TX_msg,  (uint32_t*)CAN_TX_MAILBOX0);
}


/* USER CODE END 1 */
