/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "FreeRTOS.h"
#include "task.h"
//#include "main.h"
#include "cmsis_os.h"
#include "USER_DATA_TYPE.h"
#include "tim.h"
#include "USER_PRO.h"
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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, DO8_Pin|DO7_Pin|DO6_Pin|DO1_Pin
                          |PD01_Pin|DO2_Pin|PDO2_Pin|PDO4_Pin
                          |PDO3_Pin|DO4_Pin|M1_INB_Pin|M1_INA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, DO5_Pin|DA1_SW_Pin|CAN3_RESIS_Pin|AD3_3_0V_SEL_Pin
                          |LOW_CTR3_Pin|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, CAN_SW_1_3_Pin|CAN1_RESIS_Pin|DA2_SW_Pin|M5_SEL_Pin
                          |POER_CTR_Pin|CS_SEL0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RS485_DIR_Pin|M4_INA_Pin|CS_SEL1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, M5_INB_Pin|M5_INA_Pin|LSDO2_Pin|LSDO1_Pin
                          |M5_PWM_Pin|M3_INB_Pin|WPOW_Pin|E43_M1_Pin
                          |E43_M0_Pin|REL_SUP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, M3_INA_Pin|M2_INB_Pin|M2_INA_Pin|DO9_Pin
                          |DO10_Pin|LSDO4_Pin|LSDO3_Pin|M1_SEL_Pin
                          |M4_SEL_Pin|REL_STAR_Pin|REL_ACC_Pin|REL_COM_Pin
                          |CAN2_RSIS_Pin|M4_INB_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LOW_CTR2_Pin|LOW_CTR1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PEPin PEPin PEPin PEPin
                           PEPin PEPin PEPin PEPin
                           PEPin PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = DO8_Pin|DO7_Pin|DO6_Pin|DO1_Pin
                          |PD01_Pin|DO2_Pin|PDO2_Pin|PDO4_Pin
                          |PDO3_Pin|DO4_Pin|M1_INB_Pin|M1_INA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin PCPin PCPin
                           PCPin */
  GPIO_InitStruct.Pin = DO5_Pin|DA1_SW_Pin|CAN3_RESIS_Pin|AD3_3_0V_SEL_Pin
                          |LOW_CTR3_Pin|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PFPin PFPin PFPin PFPin
                           PFPin PFPin */
  GPIO_InitStruct.Pin = CAN_SW_1_3_Pin|CAN1_RESIS_Pin|DA2_SW_Pin|M5_SEL_Pin
                          |POER_CTR_Pin|CS_SEL0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADC3_IN10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ADC3_IN10_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = POWER_MONITOR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(POWER_MONITOR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = RS485_DIR_Pin|M4_INA_Pin|CS_SEL1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin PDPin
                           PDPin PDPin PDPin PDPin
                           PDPin PDPin */
  GPIO_InitStruct.Pin = M5_INB_Pin|M5_INA_Pin|LSDO2_Pin|LSDO1_Pin
                          |M5_PWM_Pin|M3_INB_Pin|WPOW_Pin|E43_M1_Pin
                          |E43_M0_Pin|REL_SUP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PGPin PGPin PGPin PGPin
                           PGPin PGPin PGPin PGPin
                           PGPin PGPin PGPin PGPin
                           PGPin PGPin */
  GPIO_InitStruct.Pin = M3_INA_Pin|M2_INB_Pin|M2_INA_Pin|DO9_Pin
                          |DO10_Pin|LSDO4_Pin|LSDO3_Pin|M1_SEL_Pin
                          |M4_SEL_Pin|REL_STAR_Pin|REL_ACC_Pin|REL_COM_Pin
                          |CAN2_RSIS_Pin|M4_INB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = LOW_CTR2_Pin|LOW_CTR1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

/* USER CODE BEGIN 2 */

/*************************************************
* Funcname      :
* Pra       :
* Describtion   :车启动停止控制初始化
************************************************/
void user_stop_start_pin_init(void)
{
//	 HAL_GPIO_WritePin(GPIOD,REL_SUP_Pin, GPIO_PIN_RESET);//钥匙门上电时用到
	HAL_GPIO_WritePin(GPIOG,REL_COM_Pin|REL_STAR_Pin|REL_ACC_Pin, GPIO_PIN_RESET);
}


/*************************************************
* Funcname      :
* Pra       		:
* Describtion   : 车启动 
************************************************/
void user_engine_start(void)
{
		HAL_GPIO_WritePin(GPIOD,REL_SUP_Pin, GPIO_PIN_RESET);//整车的公共端的电流 从这个常闭端经过，DRV1
		HAL_GPIO_WritePin(GPIOG, REL_COM_Pin, GPIO_PIN_SET);//公共端12电接入驱动器 
		HAL_GPIO_WritePin(GPIOG,REL_ACC_Pin, GPIO_PIN_SET);//整车上电
		osDelay(500);//延时500ms
	
		HAL_GPIO_WritePin(GPIOG,REL_STAR_Pin, GPIO_PIN_SET);
	
//	   HAL_GPIO_WritePin(GPIOD,LSDO1_Pin, GPIO_PIN_SET);//相当于踩刹车
		 HAL_GPIO_WritePin(GPIOC, DO5_Pin, GPIO_PIN_SET);//相当于踩刹车
//		HAL_GPIO_WritePin(GPIOE,PD01_Pin, GPIO_PIN_SET);//右侧开
	  	osDelay(2500);//延时2500ms
//		HAL_GPIO_WritePin(GPIOE,PD01_Pin, GPIO_PIN_RESET);//右侧开
		HAL_GPIO_WritePin(GPIOC, DO5_Pin, GPIO_PIN_RESET);//相当于不踩刹车
//	    HAL_GPIO_WritePin(GPIOD,LSDO1_Pin, GPIO_PIN_RESET);//相当于不踩刹车
	
//		osDelay(1000);//延时2500ms
		HAL_GPIO_WritePin(GPIOG,REL_STAR_Pin, GPIO_PIN_RESET);

	
}


/*************************************************
* Funcname      :
* Pra       		:
* Describtion   : 车停止
************************************************/
void user_engine_stop(void)
{
		HAL_GPIO_WritePin(GPIOG, REL_COM_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG,REL_ACC_Pin, GPIO_PIN_RESET);//整车断电
		HAL_GPIO_WritePin(GPIOD,REL_SUP_Pin, GPIO_PIN_SET);//钥匙门上电时用到

//	 HAL_GPIO_WritePin(GPIOD,REL_SUP_Pin, GPIO_PIN_RESET);//钥匙门上电时用到
	
//		HAL_GPIO_WritePin(GPIOE,PD01_Pin, GPIO_PIN_RESET);	//用作熄火串联ACC的那个外挂继电器
		osDelay(3000);//延时2500ms
	HAL_GPIO_WritePin(GPIOD,REL_SUP_Pin, GPIO_PIN_RESET);//钥匙门上电时用到
	HAL_GPIO_WritePin(GPIOG, REL_COM_Pin, GPIO_PIN_SET);//断电后再上电让仪表盘点亮
	HAL_GPIO_WritePin(GPIOG,REL_ACC_Pin, GPIO_PIN_SET);// 断电后再上电让仪表盘点亮
//	 //用作熄火串联ACC的那个外挂继电器
//		HAL_GPIO_WritePin(GPIOE,PD01_Pin, GPIO_PIN_SET);	
}



/*************************************************
* Funcname      :
* Pra       		:
* Describtion   : 电机向前
************************************************/
void user_moter_forward(uint8 moter_num,uint16 cycle)
{
	if(moter_num==0x01)//电机1
	{
	//需要记录电机状态,用于电流等判断
		 HAL_GPIO_WritePin(GPIOE,  M1_INA_Pin, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOE, M1_INB_Pin, GPIO_PIN_RESET);
		 
		 HAL_GPIO_WritePin(GPIOG, M1_SEL_Pin, GPIO_PIN_SET);
		
		HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);//电机1
		 __HAL_TIM_SetCompare(&htim9, TIM_CHANNEL_2, cycle);  
	}
	else if(moter_num==0x02)//电机2
	{
	//需要记录电机状态,用于电流等判断
//		 HAL_GPIO_WritePin(GPIOG,  M2_INA_Pin, GPIO_PIN_SET);
//		 HAL_GPIO_WritePin(GPIOG, M2_INB_Pin, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(GPIOF, M2_SEL_Pin, GPIO_PIN_SET);
//		
//		HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);//电机2
//	 __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, cycle); 
		
		 HAL_GPIO_WritePin(GPIOB,  M4_INA_Pin, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOG, M4_INB_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(GPIOG, M4_SEL_Pin, GPIO_PIN_SET);
		
		HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);//电机4
		__HAL_TIM_SetCompare(&htim9, TIM_CHANNEL_1, cycle); 
		
	}
	else if(moter_num==0x03)//电机3
	{
	//需要记录电机状态,用于电流等判断
		 HAL_GPIO_WritePin(GPIOG,  M3_INA_Pin, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOD, M3_INB_Pin, GPIO_PIN_RESET);
		
//		HAL_GPIO_WritePin(GPIOF,M3_SEL_Pin, GPIO_PIN_SET);
		
		HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);//电机3
		 __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, cycle); 
	}
	else if(moter_num==0x04)//电机4
	{
	//需要记录电机状态,用于电流等判断
//		 HAL_GPIO_WritePin(GPIOB,  M4_INA_Pin, GPIO_PIN_SET);
//		 HAL_GPIO_WritePin(GPIOG, M4_INB_Pin, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(GPIOG, M4_SEL_Pin, GPIO_PIN_SET);
//		
//		HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);//电机4
//		__HAL_TIM_SetCompare(&htim9, TIM_CHANNEL_1, cycle); 
		
		 HAL_GPIO_WritePin(GPIOG,  M2_INA_Pin, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOG, M2_INB_Pin, GPIO_PIN_RESET);
		
//		HAL_GPIO_WritePin(GPIOF, M2_SEL_Pin, GPIO_PIN_SET);
		
		HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);//电机2
	 __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, cycle);
	}
	else if(moter_num==0x05)//电机5
	{
	//需要记录电机状态,用于电流等判断
		 HAL_GPIO_WritePin(GPIOD,  M5_INA_Pin, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOD, M5_INB_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(GPIOF, M5_SEL_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, M5_PWM_Pin, GPIO_PIN_SET);
//		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);//电机5
//		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, cycle); 
	}	
	
}


/*************************************************
* Funcname      :
* Pra       		:
* Describtion   : 电机向后
************************************************/
void user_moter_backward(uint8 moter_num,uint16 cycle)
{
	if(moter_num==0x01)//电机1
	{
	//需要记录电机状态,用于电流等判断
		 HAL_GPIO_WritePin(GPIOE,  M1_INB_Pin, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOE, M1_INA_Pin, GPIO_PIN_RESET);
	
		 HAL_GPIO_WritePin(GPIOG, M1_SEL_Pin, GPIO_PIN_SET);
		
			HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);//电机1
		 __HAL_TIM_SetCompare(&htim9, TIM_CHANNEL_2, cycle);  
	
	}
	else if(moter_num==0x02)//电机2
	{
	//需要记录电机状态,用于电流等判断
//		 HAL_GPIO_WritePin(GPIOG,  M2_INB_Pin, GPIO_PIN_SET);
//		 HAL_GPIO_WritePin(GPIOG, M2_INA_Pin, GPIO_PIN_RESET);
//	
//		HAL_GPIO_WritePin(GPIOF,M2_SEL_Pin, GPIO_PIN_SET);
//		
//			HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);//电机2
//	  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, cycle); 
		
		 HAL_GPIO_WritePin(GPIOG,  M4_INB_Pin, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOB, M4_INA_Pin, GPIO_PIN_RESET);

			HAL_GPIO_WritePin(GPIOG, M4_SEL_Pin, GPIO_PIN_SET);
		
		HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);//电机4
		__HAL_TIM_SetCompare(&htim9, TIM_CHANNEL_1, cycle); 
	
	}
	else if(moter_num==0x03)//电机3
	{
	//需要记录电机状态,用于电流等判断
		 HAL_GPIO_WritePin(GPIOD,  M3_INB_Pin, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOG, M3_INA_Pin, GPIO_PIN_RESET);
	
//		HAL_GPIO_WritePin(GPIOF,M3_SEL_Pin, GPIO_PIN_SET);
		
		HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);//电机3
		 __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, cycle);	
	
	}
	else if(moter_num==0x04)//电机4
	{
	//需要记录电机状态,用于电流等判断
//		 HAL_GPIO_WritePin(GPIOG,  M4_INB_Pin, GPIO_PIN_SET);
//		 HAL_GPIO_WritePin(GPIOB, M4_INA_Pin, GPIO_PIN_RESET);

//				 HAL_GPIO_WritePin(GPIOG, M4_SEL_Pin, GPIO_PIN_SET);
//		
//		HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);//电机4
//		__HAL_TIM_SetCompare(&htim9, TIM_CHANNEL_1, cycle); 	

		 HAL_GPIO_WritePin(GPIOG,  M2_INB_Pin, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOG, M2_INA_Pin, GPIO_PIN_RESET);
	
//		HAL_GPIO_WritePin(GPIOF,M2_SEL_Pin, GPIO_PIN_SET);
		
			HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);//电机2
	  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, cycle); 		
	
	}
	else if(moter_num==0x05)//电机5
	{
	//需要记录电机状态,用于电流等判断
		 HAL_GPIO_WritePin(GPIOD,  M5_INB_Pin, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOD, M5_INA_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(GPIOF, M5_SEL_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, M5_PWM_Pin, GPIO_PIN_SET);
//		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);//电机5
//		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, cycle); 
	}	
		
}

/*************************************************
* Funcname      :
* Pra       		:
* Describtion   : 电机停止
************************************************/
void user_moter_stop(uint8 moter_num)
{
		if(moter_num==0x01)//电机1
	{
	//需要记录电机状态,用于电流等判断
		 HAL_GPIO_WritePin(GPIOE,  M1_INA_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(GPIOE, M1_INB_Pin, GPIO_PIN_RESET);
// 		 HAL_GPIO_WritePin(GPIOE,  M1_INA_Pin, GPIO_PIN_SET);
//		 HAL_GPIO_WritePin(GPIOE, M1_INB_Pin, GPIO_PIN_SET);

		if((user_state.manul_auto == 0x01)&&(user_moter1.manul_change_elec ==0x00))//人工 手动状态,不是手改电，电机不自锁
	 {
		 	if(user_moter1.lock_s==0x01)//串口指令电机1动作
			{
				__HAL_TIM_SetCompare(&htim9, TIM_CHANNEL_2, 500);
				
			}
			else
			{
					__HAL_TIM_SetCompare(&htim9, TIM_CHANNEL_2, 0);
			}
			
			
	 }
//	 else if(user_state.manul_auto == 0x02)//无人状态自锁
	 else
	 {
			__HAL_TIM_SetCompare(&htim9, TIM_CHANNEL_2, 500); 	
	 
	 }
		
//		HAL_TIM_PWM_Stop(&htim9,TIM_CHANNEL_2);

	}
	else if(moter_num==0x02)//电机2
	{
	//需要记录电机状态,用于电流等判断
//		 HAL_GPIO_WritePin(GPIOG,  M2_INA_Pin, GPIO_PIN_RESET);
//		 HAL_GPIO_WritePin(GPIOG, M2_INB_Pin, GPIO_PIN_RESET);
////		HAL_GPIO_WritePin(GPIOF,M2_SEL_Pin, GPIO_PIN_RESET);
//		 HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1);	
		
		 HAL_GPIO_WritePin(GPIOB,  M4_INA_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(GPIOG, M4_INB_Pin, GPIO_PIN_RESET);
//	   HAL_GPIO_WritePin(GPIOG, M4_SEL_Pin, GPIO_PIN_RESET);
		
	 if((user_state.manul_auto == 0x01)&&(user_moter2.manul_change_elec ==0x00))//人工 手动状态，电机不自锁
	 {
		 	if(user_moter2.lock_s==0x01)//串口指令电机1动作
			{
				__HAL_TIM_SetCompare(&htim9, TIM_CHANNEL_1, 500);
				
			}
			else
			{
					__HAL_TIM_SetCompare(&htim9, TIM_CHANNEL_1, 0);
			}
//			__HAL_TIM_SetCompare(&htim9, TIM_CHANNEL_1, 0);
	 }
//	 else if(user_state.manul_auto == 0x02)//无人状态自锁
	 else
	 {
			__HAL_TIM_SetCompare(&htim9, TIM_CHANNEL_1, 500); 	
	 
	 }
//		 HAL_TIM_PWM_Stop(&htim9,TIM_CHANNEL_1);
	}
	else if(moter_num==0x03)//电机3
	{
	//需要记录电机状态,用于电流等判断
		 HAL_GPIO_WritePin(GPIOG,  M3_INA_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(GPIOD, M3_INB_Pin, GPIO_PIN_RESET);

//			HAL_GPIO_WritePin(GPIOF,M3_SEL_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, 500);
//		 HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_2);
	}
	else if(moter_num==0x04)//电机4
	{
	//需要记录电机状态,用于电流等判断
//		 HAL_GPIO_WritePin(GPIOB,  M4_INA_Pin, GPIO_PIN_RESET);
//		 HAL_GPIO_WritePin(GPIOG, M4_INB_Pin, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOG, M4_SEL_Pin, GPIO_PIN_RESET);
//		HAL_TIM_PWM_Stop(&htim9,TIM_CHANNEL_1);
		
		 HAL_GPIO_WritePin(GPIOG,  M2_INA_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(GPIOG, M2_INB_Pin, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOF,M2_SEL_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 500);
//		 HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1);
	}
	else if(moter_num==0x05)//电机5
	{
	//需要记录电机状态,用于电流等判断
		 HAL_GPIO_WritePin(GPIOD,  M5_INA_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(GPIOD, M5_INB_Pin, GPIO_PIN_RESET);
	
		HAL_GPIO_WritePin(GPIOF, M5_SEL_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, M5_PWM_Pin, GPIO_PIN_RESET);
//		 HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
	}	
}



//DA 继电器切换，0关掉，1打开
void user_DA_SW(uint8 DA_type,uint8 ctr)
{
	if(DA_type==0x01)//第二对DA切换开关
	{
		if(ctr==0x00)
		{
			HAL_GPIO_WritePin(GPIOC, DA1_SW_Pin, GPIO_PIN_RESET);
		}
		else if(ctr==0x01)
		{
			HAL_GPIO_WritePin(GPIOC, DA1_SW_Pin, GPIO_PIN_SET);		
		}
	}
	else 	if(DA_type==0x02)//第二对DA切换开关
	{
		if(ctr==0x00)
		{
			HAL_GPIO_WritePin(GPIOF, DA2_SW_Pin, GPIO_PIN_RESET);		
		}
		else if(ctr==0x01)
		{
			HAL_GPIO_WritePin(GPIOF, DA2_SW_Pin, GPIO_PIN_SET);			
		}
	}
}

						
						
//DA 的值,两路DA
void user_DA_value(uint8 DA_type,uint16 val1,uint16 val2)	
{
	if(DA_type==0x01)//第一对DA切换开关
	{
		__HAL_TIM_SetCompare(&htim10, TIM_CHANNEL_1, val1);
		__HAL_TIM_SetCompare(&htim10, TIM_CHANNEL_2, val2);	
	}
	else if(DA_type==0x02)//第二对DA切换开关
	{
		__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, val1);
		__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_2, val2);	
		
	}
}	
/*************************************************
* Funcname      :
* Pra       		:
* Describtion   : 0,驱动电路不上电，1驱动电路上电
************************************************/
void user_moter_power_ctr(uint8 ctr)
{
	if(ctr==0x00)
	{
		HAL_GPIO_WritePin(GPIOF, POER_CTR_Pin , GPIO_PIN_SET);
	}
  else 	if(ctr==0x01)
	{
		HAL_GPIO_WritePin(GPIOF, POER_CTR_Pin , GPIO_PIN_RESET);
	}
}

/*************************************************
* Funcname      :
* Pra       		:
* Describtion   : 0, 不上电，1 上电
************************************************/
//void user_pend_switch(uint8 ctr)
//{
//	if(ctr==0x00) 
//	{
//		  HAL_GPIO_WritePin(GPIOE, PDO2_Pin,GPIO_PIN_RESET);
//	}
//  else 	if(ctr==0x01)
//	{
//		  HAL_GPIO_WritePin(GPIOE, PDO2_Pin,GPIO_PIN_SET);

//	}
//}

/*************************************************
* Funcname      :
* Pra       		:
* Describtion   : N型mos管
************************************************/
void user_pend_switch_init(void)
{
  HAL_GPIO_WritePin(GPIOG,LSDO4_Pin|LSDO3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,LSDO2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,LSDO1_Pin, GPIO_PIN_RESET);
}


//1对应A；2对应B
void user_moter_current_detect(uint8 AB_num)
{
//	sel0=1,sel1=0,A,前进;sel0=0,sel1=0,B，后退;
	if(AB_num==0x01)
	{
			HAL_GPIO_WritePin(GPIOF, CS_SEL0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, CS_SEL1_Pin, GPIO_PIN_RESET);	
	}
	else 	if(AB_num==0x02)
	{
			HAL_GPIO_WritePin(GPIOF, CS_SEL0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, CS_SEL1_Pin, GPIO_PIN_RESET);	
	}
}


/*************************************************
* Funcname      :P2-4，ADC3-10，exit0中断,两个绞龙；P2-15，ADC3-11，exit1中断，发动机转速；
* Pra       		:
* Describtion   : 
************************************************/
 void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 {
   if(GPIO_Pin==ADC3_IN10_Pin)//秧台转速
	 {
	    YangTai_rec++;
	 }
 }
/* USER CODE END 2 */
