/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:
********************************************/
#include "USER_MISC.h"
#include "USER_DATA_TYPE.h"
#include "stm32f7xx_hal.h"
#include "USER_PRO.h"
#include "USER_FREE_RT_OS.h"
//#include "USER_CRC.h"																				
//#include "USER_REMOTE.h"

/*********************************软复位***************/
/*******************************************************************************
* Function Name  :  
* Description    : 软件复位
* Input          :
* Output         :  
* Return         : 
*******************************************************************************/
void User_Soft_Reset(void)
{
//		__set_FAULTMASK(1); // 屏蔽中断
//		NVIC_SystemReset();// 复位重启
	
	
//	  __set_PRIMASK(0);/*  使能全局中断 */
    __set_PRIMASK(1);/* 禁止全局中断*/
		HAL_NVIC_SystemReset();
//	__disable_irq();   // 关闭总中断
//  __enable_irq();    // 开启总中断?
}

	
/***************************************************************************************************************************
* Function Name  :  
* Description    : 看门狗的初始化
* Input          :  
* Output         :  
* Return         :  
****************************************************************************************************************************/
//void IWDG_Configuration(void)
//{

//	 IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);		//是能看门狗的设置
//	 
//	 	IWDG_SetPrescaler(IWDG_Prescaler_256);		//看门狗预分频，40K/256=156HZ(6.4ms)
//			
//	 IWDG_SetReload(234); 			//喂狗时间234*156=1.5s 
//	 

//	 IWDG_ReloadCounter();			//喂狗

//		IWDG_Enable();						//使能。
//}


/***************************************************************************************************************************
* Function Name  :  
* Description    : JTAG禁能，swd使能
* Input          :  
* Output         :  
* Return         :  
****************************************************************************************************************************/
//void user_JTAG_SWD_set(void)
//{
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO ,ENABLE);
//		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
//}


/***************************************************************************************************************************
* Function Name  :  
* Description    : CRC16校验下，得个串号
* Input          :  
* Output         :  
* Return         :  
****************************************************************************************************************************/
//void user_STM32F10X_ID_get(void)
//{
//		uint8 ID_temp[12]={0};
//		uint8 i;
//		uint8* p;
//		p = ((uint8*)(0x1ffff7e8));
//		for(i=0;i<12;i++)
//		{
//			ID_temp[i] =*p;
//			p++;
//		
//		}
//		
//		user_dec_infor.device_ID=CRC_ALL(ID_temp,12);

//}

void User_get_Reset_State(void)
{
//////	uint8 reset_state=0x00;
//////	 if(__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST)) //引脚复位,即按一下复位按钮 bit26（第27位)
//////	 {
//////				reset_state = reset_state|(0x01<<(0));
////////			user_send_str(&huart7, "引脚复位\r\n"); 
//////	 }

//////	 if(__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST)) //POR/PDR复位,上电或者掉电复位
//////	 	{
//////			  reset_state = reset_state|(0x01<<(1));
////////			user_send_str(&huart7, "上电或者掉电复位\r\n"); 
//////		}

//////	 if(__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST)) //软件复位，也伴随着引脚复位
//////	 	{
//////			reset_state = reset_state|(0x01<<(2));
////////			user_send_str(&huart7, "软件复位\r\n"); 
//////		}

//////	 if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST))//独立看门狗复位,伴随着引脚复位
//////	 	{
//////			reset_state = reset_state|(0x01<<(3));
////////			user_send_str(&huart7, "看门狗复位\r\n"); 
//////		}

//////	 if(__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST))//窗口看门狗复位
//////	 	{
//////			reset_state = reset_state|(0x01<<(4));
////////			user_send_str(&huart7, "窗口看门狗复位\r\n"); 
//////		}


//////	 if(__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST))//低电量复位
//////	 {
//////		 reset_state = reset_state|(0x01<<(5));
////////			user_send_str(&huart7, "电量低复位\r\n"); 
//////	 }
//////	 
//////	 __HAL_RCC_CLEAR_RESET_FLAGS();//清除所有复位标识,用于复位类型的判断
//////	{
////////		user_send_str(&huart7, "复位已经清除\r\n");
//////	}
//////		
//////	{
//////		uint8 i=0;
//////		for(i=9;i>0;i--)
//////		{
//////			user_moter_pra.reset_record[i] = user_moter_pra.reset_record[i-1];
//////		}
//////		user_moter_pra.reset_record[0] = reset_state;
//////		
//////		osMessageQueuePut(myQueueUart7RecHandle, "ok", 0, NULL);//用于中断时，延时要为0
////////		portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);//如果需要的话进行一次任务切换
//////	}
}
