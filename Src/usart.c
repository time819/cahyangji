/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "USER_GLOBAL.h"
#include "cmsis_os.h"
#include "USER_FREE_RT_OS.h"
#include "USER_WIRE_LESS.h"

uint8 uart7RxBufftemp =0;
uint8 uart2RxBufftemp =0;
uint8 uart5RxBufftemp =0;
uint8 buffer_uart2_temp_test[20];
/* USER CODE END 0 */

UART_HandleTypeDef huart5;
UART_HandleTypeDef huart7;
UART_HandleTypeDef huart2;

/* UART5 init function */
void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 9600;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  huart5.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart5.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}
/* UART7 init function */
void MX_UART7_Init(void)
{

  /* USER CODE BEGIN UART7_Init 0 */

  /* USER CODE END UART7_Init 0 */

  /* USER CODE BEGIN UART7_Init 1 */

  /* USER CODE END UART7_Init 1 */
  huart7.Instance = UART7;
  huart7.Init.BaudRate = 115200;
  huart7.Init.WordLength = UART_WORDLENGTH_8B;
  huart7.Init.StopBits = UART_STOPBITS_1;
  huart7.Init.Parity = UART_PARITY_NONE;
  huart7.Init.Mode = UART_MODE_TX_RX;
  huart7.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart7.Init.OverSampling = UART_OVERSAMPLING_16;
  huart7.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart7.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart7) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART7_Init 2 */

  /* USER CODE END UART7_Init 2 */

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(uartHandle->Instance==UART5)
  {
  /* USER CODE BEGIN UART5_MspInit 0 */

  /* USER CODE END UART5_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_UART5;
    PeriphClkInitStruct.Uart5ClockSelection = RCC_UART5CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* UART5 clock enable */
    __HAL_RCC_UART5_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**UART5 GPIO Configuration
    PB12     ------> UART5_RX
    PB13     ------> UART5_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* UART5 interrupt Init */
    HAL_NVIC_SetPriority(UART5_IRQn, 11, 0);
    HAL_NVIC_EnableIRQ(UART5_IRQn);
  /* USER CODE BEGIN UART5_MspInit 1 */

  /* USER CODE END UART5_MspInit 1 */
  }
  else if(uartHandle->Instance==UART7)
  {
  /* USER CODE BEGIN UART7_MspInit 0 */

  /* USER CODE END UART7_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_UART7;
    PeriphClkInitStruct.Uart7ClockSelection = RCC_UART7CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* UART7 clock enable */
    __HAL_RCC_UART7_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**UART7 GPIO Configuration
    PE7     ------> UART7_RX
    PE8     ------> UART7_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART7;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /* UART7 interrupt Init */
    HAL_NVIC_SetPriority(UART7_IRQn, 15, 0);
    HAL_NVIC_EnableIRQ(UART7_IRQn);
  /* USER CODE BEGIN UART7_MspInit 1 */

  /* USER CODE END UART7_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART2;
    PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PD5     ------> USART2_TX
    PD6     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 10, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==UART5)
  {
  /* USER CODE BEGIN UART5_MspDeInit 0 */

  /* USER CODE END UART5_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_UART5_CLK_DISABLE();

    /**UART5 GPIO Configuration
    PB12     ------> UART5_RX
    PB13     ------> UART5_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13);

    /* UART5 interrupt Deinit */
    HAL_NVIC_DisableIRQ(UART5_IRQn);
  /* USER CODE BEGIN UART5_MspDeInit 1 */

  /* USER CODE END UART5_MspDeInit 1 */
  }
  else if(uartHandle->Instance==UART7)
  {
  /* USER CODE BEGIN UART7_MspDeInit 0 */

  /* USER CODE END UART7_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_UART7_CLK_DISABLE();

    /**UART7 GPIO Configuration
    PE7     ------> UART7_RX
    PE8     ------> UART7_TX
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_7|GPIO_PIN_8);

    /* UART7 interrupt Deinit */
    HAL_NVIC_DisableIRQ(UART7_IRQn);
  /* USER CODE BEGIN UART7_MspDeInit 1 */

  /* USER CODE END UART7_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PD5     ------> USART2_TX
    PD6     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_5|GPIO_PIN_6);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void user_uart_init(void)
{
	HAL_UART_Receive_IT(&huart2,&uart2RxBufftemp,1);	//使能串口2
	HAL_UART_Receive_IT(&huart7,&uart7RxBufftemp,1);	//使能串口7
	HAL_UART_Receive_IT(&huart5,&uart7RxBufftemp,1);	//使能串口7
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
   
	if(huart->Instance==UART7)
  {
		static unsigned char  buffer_uart7_temp[30]="123";
		static uint8 len = 0;
		BaseType_t pxHigherPriorityTaskWoken;
//		if(uart7RxBufftemp==0x13)
		{
				if(len>=30)//防越界
				{
					len =0;
				}
				
				buffer_uart7_temp[len] = uart7RxBufftemp;		
				len++;
				
				if(len>=2)
				{
						if(buffer_uart7_temp[len-1]=='\n')
						{
							if(buffer_uart7_temp[len-2]=='\r')
							{	
									len =0;	
									osMessageQueuePut(myQueueUart7RecHandle, buffer_uart7_temp, 0, NULL);//用于中断时，延时要为0
									portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);//如果需要的话进行一次任务切换
									memset(buffer_uart7_temp,0,sizeof(buffer_uart7_temp));
							}					
						}
			  }

		}
  
	  HAL_UART_Receive_IT(&huart7,&uart7RxBufftemp,1);	//再次使能串口3,指定收到数据存到uart7RxBufftemp，并启动串口
	}
	
	else if(huart->Instance==USART2)//接收无线数据
	{
	 //uint8_t TXData[WL_E43_ALEN] = {0x5a,0x0f,1,2,3,0xa5,0xf0,0x00};
		static unsigned char  buffer_uart2_temp[16]={0};
		static uint8 uart2_len = 0;	
		static  uint8 start_flag =0;
		BaseType_t pxHigherPriorityTaskWoken2;
		if(uart2_len>=15)//防越界
		{
			uart2_len =0;
		}
			
			buffer_uart2_temp_test[uart2_len] = uart2RxBufftemp;	
			buffer_uart2_temp[uart2_len] = uart2RxBufftemp;		
			
			
			if(user_wl_struct.E34_mode == Config_MODE)//配置模式,一帧6个字节
			{
				if((buffer_uart2_temp[uart2_len]==0xc0 )&&(start_flag==0))//未收到字头
				{
						uart2_len = 0;
						buffer_uart2_temp[0] = 0xc0;
					  start_flag = 1;//收到字头
				}
				
				if((uart2_len==5 )&&(start_flag==1))//已经收到6个字节
				{
					if(buffer_uart2_temp[uart2_len]==0x40 )//check 字尾
					{
						user_wl_struct.uart_buff_rx_empt_flag = 1;//收到了，做标记
						memcpy(user_wl_struct.uart_buff_rx,buffer_uart2_temp,6);
//						memset(buffer_uart2_temp,0,sizeof(buffer_uart2_temp));
						uart2_len = 0;
						start_flag = 0;
						osMessageQueuePut(myQueueUart2Spi3RecHandle, buffer_uart2_temp, 0, NULL);//用于中断时，延时要为0
						portYIELD_FROM_ISR(pxHigherPriorityTaskWoken2);//如果需要的话进行一次任务切换	
					}
					else//清零
					{
						memset(buffer_uart2_temp,0,sizeof(buffer_uart2_temp));
						uart2_len  = 0;
						start_flag = 0;
					}
				}

			}
			else if(user_wl_struct.E34_mode == HopFreq_MODE)//正常通讯，一帧12字节,
			{
				if(   (buffer_uart2_temp[uart2_len-2]==0xfd )&&    \
							((buffer_uart2_temp[uart2_len-1]==0xd6 )||(buffer_uart2_temp[uart2_len-1]==0xd8 ))&&  \
							(buffer_uart2_temp[uart2_len]==0x98 )&&				\
							(start_flag==0)&&															\
							(uart2_len>=2)
					)//未收到字头
				{

						buffer_uart2_temp[0] = 0xfd;
						buffer_uart2_temp[1] = buffer_uart2_temp[uart2_len-1];
						buffer_uart2_temp[2] = 0x98;
						uart2_len = 2;
						start_flag=1;//收到字头
				}
				
				if((uart2_len==11 )&&(start_flag==1))//收到一帧的长度
				{
					  user_wl_struct.uart_buff_rx_empt_flag = 1;//收到了，做标记
						memcpy(user_wl_struct.uart_buff_rx,buffer_uart2_temp,12);
						osMessageQueuePut(myQueueUart2Spi3RecHandle, buffer_uart2_temp, 0, NULL);//用于中断时，延时要为0
						portYIELD_FROM_ISR(pxHigherPriorityTaskWoken2);//如果需要的话进行一次任务切换	
//						memset(buffer_uart2_temp,0,sizeof(buffer_uart2_temp));
						uart2_len = 0;
						start_flag = 0;
				}
			}
			uart2_len++;
			HAL_UART_Receive_IT(&huart2,&uart2RxBufftemp,1);	//再次使能串口3,指定收到数据存到uart7RxBufftemp，并启动串口
	}
	else if(huart->Instance==UART5)//接收485数据
	{

	}
	
}


//字符串发送函数
void user_send_str(UART_HandleTypeDef *huart, char *ptr)
{
//		char * ptr="hello world";
		HAL_UART_Transmit(huart,(uint8*)ptr,strlen(ptr),10);
}


//字节发送函数
int user_send_bytes(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
	 HAL_UART_Transmit(huart,pData,Size,100);//超时时间指的是size个数据，不能超过100ms
 	while(__HAL_UART_GET_FLAG(huart,UART_FLAG_TC)!=SET);
	HAL_UART_Receive_IT(&huart2,&uart2RxBufftemp,1);
	return 0;
}

int user_485_send_bytes(uint8_t *pData, uint16_t Size)
{
	HAL_GPIO_WritePin(GPIOB,  RS485_DIR_Pin , GPIO_PIN_SET);

	HAL_UART_Transmit(&huart5,pData,Size,100);//超时时间指的是size个数据，不能超过100ms
 	while(__HAL_UART_GET_FLAG(&huart5,UART_FLAG_TC)!=SET);
	HAL_UART_Receive_IT(&huart5,&uart2RxBufftemp,1);
	HAL_GPIO_WritePin(GPIOB,  RS485_DIR_Pin , GPIO_PIN_RESET);
	return 0;
}

/* USER CODE END 1 */
