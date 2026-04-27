/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dma.c
  * @brief   This file provides code for the configuration
  *          of all the requested memory to memory DMA transfers.
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
#include "dma.h"

/* USER CODE BEGIN 0 */
#include "adc.h"
#include "USER_GLOBAL.h"
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure DMA                                                              */
/*----------------------------------------------------------------------------*/

/* USER CODE BEGIN 1 */
//uint32 ADC1_buff[ADC1_BUFF_SIZE]={0};
//uint32 ADC3_buff[ADC3_BUFF_SIZE]={0};
uint32 ADC1_buff[10]={0};
uint32 ADC3_buff[15]={0};
volatile int clutch_ctr[3]={0};//0卸粮离合；1脱谷离合；2割取离合
volatile int AD_CH_value[12]={0};//按照次序存放8个角度传感器的实时数据,，5个电机，1个割台高度，一个电子手柄，3个备用
volatile u32 AD_SEN_value[5]={0};
//volatile int AD_EXT_value[4]={0};
/* USER CODE END 1 */

/**
  * Enable DMA controller clock
  */
void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
  /* DMA2_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

}

/* USER CODE BEGIN 2 */
void user_ad_dma_init(void)
{
//	  HAL_ADC_Start_DMA(&hadc1,ADC1_buff, ADC1_BUFF_SIZE);//DMA模式
//	  HAL_ADC_Start_DMA(&hadc3,ADC3_buff, ADC3_BUFF_SIZE);
		  HAL_ADC_Start_DMA(&hadc1,ADC1_buff,10);//DMA模式
	  HAL_ADC_Start_DMA(&hadc3,ADC3_buff,15);

	//	  HAL_ADC_Stop_DMA(&hadc1);
}


//将AD值放入指定缓存，方便使用
void user_AD_val_get(void)
{
		AD_CH_value[0] = ADC3_buff[6];//电机1
		AD_CH_value[1] =  ADC3_buff[4]; //电机2
	
		AD_CH_value[2] = ADC1_buff[3];//电机3
		AD_CH_value[3] = ADC1_buff[6];//电机4
		AD_CH_value[4] = ADC1_buff[7];//电机5
		AD_CH_value[5] = ADC3_buff[13];// 悬挂
	  AD_CH_value[6] = ADC3_buff[12];// 行走手改电角度传感器

	AD_CH_value[7] = ADC3_buff[5];//秧台电子手柄角度传感器
	
//		AD_CH_value[8]=  ADC3_buff[2];//  旋耕机仿型,也用于粮仓满
	
			AD_CH_value[8] = ADC3_buff[0];//久保田收割机的转向
			
//	AD_CH_value[9] = ADC3_buff[10];//AD3_12;P2-16 艾和旋耕机肥筒 左右角度传感器
//	AD_CH_value[10]=  ADC3_buff[0];//AD3_0;P2-17 艾和旋耕机肥筒 上下角度传感器
	  AD_CH_value[11] = ADC3_buff[2];//久保田收割机的粮仓满，旋耕机仿型
	
	
		AD_SEN_value[0]  = ADC3_buff[14];// 
		AD_SEN_value[1]  = ADC1_buff[1];// 
	
	//离合输入开关
	clutch_ctr[0] = ADC3_buff[7];//卸粮离合p1-5
	clutch_ctr[1] = ADC3_buff[8];//脱谷离合p2-4
	clutch_ctr[2] = ADC3_buff[9];//割取离合p2-15
}
int32  user_cal_valu(uint8 AD_Num,uint8 CH_Num)
{
//	 if( AD_Num==1)
//	 {
//			 
//			 static uint8 AD1_ch_total_num =10;
//		  static uint8 AD3_ch_total_num =14;
//			int32 arr[12]={0};
//			int32 value_result = 0;
//			uint8 i, j,k;
//			
//			for(i=0;i<12;i++)//读出数据
//			{
//				 if( AD_Num==1)
//				 {
//						arr[i]= ADC1_buff[i*AD1_ch_total_num+CH_Num];	
//				 }			
//				 else if( AD_Num==3)
//				 {
//					arr[i]= ADC3_buff[i*AD3_ch_total_num+CH_Num];	
//				 }
//			}
//			
//			
//			for(j=0;j<12;j++)//排序,从小到大排
//			{
//				for(k=j+1;k<12;k++)
//				{
//					if(arr[j]>arr[k])
//					{
//						int32 temp_B;
//						
//						temp_B = arr[j];
//						arr[j] =arr[k];
//						arr[k] =temp_B;
//					}
//				}	
//			}
//			
//			for(i=2;i<10;i++)
//			{
//				value_result= value_result+arr[i];
//			}
//		
//			value_result=value_result>>8;
//			return (value_result);
//			
//	 }
	return 0;
}
/* USER CODE END 2 */

