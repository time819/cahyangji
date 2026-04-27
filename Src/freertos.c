 /* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "USER_GLOBAL.h"
#include "stm32f7xx_hal_can.h"
#include "can.h"
#include "usart.h"
#include "tim.h"
#include "USER_FLASH.h"
#include "gpio.h"
#include "USER_PRO.h"
#include "stdio.h"	
#include "string.h"
#include "USER_SET.h"
#include "dma.h"
#include "iwdg.h"
#include "USER_WIRE_LESS.h"
#include "USER_PPM.h"
#include "USER_PRO.h"
#include "USER_MISC.h"
#include "USER_MOTER.h"
#include "stdint.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh7,
};
/* Definitions for myTask03 */
osThreadId_t myTask03Handle;
const osThreadAttr_t myTask03_attributes = {
  .name = "myTask03",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh6,
};
/* Definitions for myTask04 */
osThreadId_t myTask04Handle;
const osThreadAttr_t myTask04_attributes = {
  .name = "myTask04",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh5,
};
/* Definitions for myTask05 */
osThreadId_t myTask05Handle;
const osThreadAttr_t myTask05_attributes = {
  .name = "myTask05",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh4,
};
/* Definitions for myTask06 */
osThreadId_t myTask06Handle;
const osThreadAttr_t myTask06_attributes = {
  .name = "myTask06",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh3,
};
/* Definitions for myTask07 */
osThreadId_t myTask07Handle;
const osThreadAttr_t myTask07_attributes = {
  .name = "myTask07",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh2,
};
/* Definitions for myTask08 */
osThreadId_t myTask08Handle;
const osThreadAttr_t myTask08_attributes = {
  .name = "myTask08",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal7,
};
/* Definitions for myTask09 */
osThreadId_t myTask09Handle;
const osThreadAttr_t myTask09_attributes = {
  .name = "myTask09",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal6,
};
/* Definitions for myTask10 */
osThreadId_t myTask10Handle;
const osThreadAttr_t myTask10_attributes = {
  .name = "myTask10",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal5,
};
/* Definitions for myTask11 */
osThreadId_t myTask11Handle;
const osThreadAttr_t myTask11_attributes = {
  .name = "myTask11",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal4,
};
/* Definitions for myTask12 */
osThreadId_t myTask12Handle;
const osThreadAttr_t myTask12_attributes = {
  .name = "myTask12",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal3,
};
/* Definitions for myTask13 */
osThreadId_t myTask13Handle;
const osThreadAttr_t myTask13_attributes = {
  .name = "myTask13",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal2,
};
/* Definitions for myTask14 */
osThreadId_t myTask14Handle;
const osThreadAttr_t myTask14_attributes = {
  .name = "myTask14",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for myTask15 */
osThreadId_t myTask15Handle;
const osThreadAttr_t myTask15_attributes = {
  .name = "myTask15",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask20 */
osThreadId_t myTask20Handle;
const osThreadAttr_t myTask20_attributes = {
  .name = "myTask20",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for myTask16 */
osThreadId_t myTask16Handle;
const osThreadAttr_t myTask16_attributes = {
  .name = "myTask16",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal7,
};
/* Definitions for myTask17 */
osThreadId_t myTask17Handle;
const osThreadAttr_t myTask17_attributes = {
  .name = "myTask17",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal6,
};
/* Definitions for myTask18 */
osThreadId_t myTask18Handle;
const osThreadAttr_t myTask18_attributes = {
  .name = "myTask18",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal5,
};
/* Definitions for myTask19 */
osThreadId_t myTask19Handle;
const osThreadAttr_t myTask19_attributes = {
  .name = "myTask19",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal4,
};
/* Definitions for myTask21 */
osThreadId_t myTask21Handle;
const osThreadAttr_t myTask21_attributes = {
  .name = "myTask21",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime1,
};
/* Definitions for myQueueCan2Rev */
osMessageQueueId_t myQueueCan2RevHandle;
const osMessageQueueAttr_t myQueueCan2Rev_attributes = {
  .name = "myQueueCan2Rev"
};
/* Definitions for myQueueCan1Rev */
osMessageQueueId_t myQueueCan1RevHandle;
const osMessageQueueAttr_t myQueueCan1Rev_attributes = {
  .name = "myQueueCan1Rev"
};
/* Definitions for myQueueCan3Rev */
osMessageQueueId_t myQueueCan3RevHandle;
const osMessageQueueAttr_t myQueueCan3Rev_attributes = {
  .name = "myQueueCan3Rev"
};
/* Definitions for myQueueUart7Rec */
osMessageQueueId_t myQueueUart7RecHandle;
const osMessageQueueAttr_t myQueueUart7Rec_attributes = {
  .name = "myQueueUart7Rec"
};
/* Definitions for myQueueUart2Spi3Rec */
osMessageQueueId_t myQueueUart2Spi3RecHandle;
const osMessageQueueAttr_t myQueueUart2Spi3Rec_attributes = {
  .name = "myQueueUart2Spi3Rec"
};

/* Definitions for myCountingSemMoter1 */
osSemaphoreId_t myCountingSemMoter1Handle;
const osSemaphoreAttr_t myCountingSemMoter1_attributes = {
  .name = "myCountingSemMoter1"
};
/* Definitions for myCountingSemMoter2 */
osSemaphoreId_t myCountingSemMoter2Handle;
const osSemaphoreAttr_t myCountingSemMoter2_attributes = {
  .name = "myCountingSemMoter2"
};
/* Definitions for myCountingSemMoter3 */
osSemaphoreId_t myCountingSemMoter3Handle;
const osSemaphoreAttr_t myCountingSemMoter3_attributes = {
  .name = "myCountingSemMoter3"
};
/* Definitions for myCountingSemMoter4 */
osSemaphoreId_t myCountingSemMoter4Handle;
const osSemaphoreAttr_t myCountingSemMoter4_attributes = {
  .name = "myCountingSemMoter4"
};
/* Definitions for myCountingSemMoter5 */
osSemaphoreId_t myCountingSemMoter5Handle;
const osSemaphoreAttr_t myCountingSemMoter5_attributes = {
  .name = "myCountingSemMoter5"
};
/* Definitions for myCountingSemEngine */
osSemaphoreId_t myCountingSemEngineHandle;
const osSemaphoreAttr_t myCountingSemEngine_attributes = {
  .name = "myCountingSemEngine"
};

/* Definitions for myCountingSemElecAccelerator */
osSemaphoreId_t myCountingSemElecAcceleratorHandle;
const osSemaphoreAttr_t myCountingSemElecAccelerator_attributes = {
  .name = "myCountingSemElecAccelerator"
};
/* Definitions for myCountingSemTube */
osSemaphoreId_t myCountingSemTubeHandle;
const osSemaphoreAttr_t myCountingSemTube_attributes = {
  .name = "myCountingSemTube"
};
/* Definitions for myCountingSemTurn */
osSemaphoreId_t myCountingSemTurnHandle;
const osSemaphoreAttr_t myCountingSemTurn_attributes = {
  .name = "myCountingSemTurn"
};
/* Definitions for myCountingSemAutoTurn */
osSemaphoreId_t myCountingSemAutoTurnHandle;
const osSemaphoreAttr_t myCountingSemAutoTurn_attributes = {
  .name = "myCountingSemAutoTurn"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);
void StartTask04(void *argument);
void StartTask05(void *argument);
void StartTask06(void *argument);
void StartTask07(void *argument);
void StartTask08(void *argument);
void StartTask09(void *argument);
void StartTask10(void *argument);
void StartTask11(void *argument);
void StartTask12(void *argument);
void StartTask13(void *argument);
void StartTask14(void *argument);
void StartTask15(void *argument);
void StartTask20(void *argument);
void StartTask16(void *argument);
void StartTask17(void *argument);
void StartTask18(void *argument);
void StartTask19(void *argument);
void StartTask21(void *argument);
 
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of myCountingSemMoter1 */
  myCountingSemMoter1Handle = osSemaphoreNew(1, 1, &myCountingSemMoter1_attributes);

  /* creation of myCountingSemMoter2 */
  myCountingSemMoter2Handle = osSemaphoreNew(1, 1, &myCountingSemMoter2_attributes);

  /* creation of myCountingSemMoter3 */
  myCountingSemMoter3Handle = osSemaphoreNew(1, 1, &myCountingSemMoter3_attributes);

  /* creation of myCountingSemMoter4 */
  myCountingSemMoter4Handle = osSemaphoreNew(1, 1, &myCountingSemMoter4_attributes);

  /* creation of myCountingSemMoter5 */
  myCountingSemMoter5Handle = osSemaphoreNew(1, 1, &myCountingSemMoter5_attributes);

  /* creation of myCountingSemEngine */
  myCountingSemEngineHandle = osSemaphoreNew(1, 1, &myCountingSemEngine_attributes);

  /* creation of myCountingSemPend1 */
 

  /* creation of myCountingSemElecAccelerator */
  myCountingSemElecAcceleratorHandle = osSemaphoreNew(1, 1, &myCountingSemElecAccelerator_attributes);

  /* creation of myCountingSemTube */
  myCountingSemTubeHandle = osSemaphoreNew(1, 1, &myCountingSemTube_attributes);

  /* creation of myCountingSemTurn */
  myCountingSemTurnHandle = osSemaphoreNew(1, 1, &myCountingSemTurn_attributes);

  /* creation of myCountingSemAutoTurn */
  myCountingSemAutoTurnHandle = osSemaphoreNew(1, 1, &myCountingSemAutoTurn_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */
	

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of myQueueCan2Rev */
  myQueueCan2RevHandle = osMessageQueueNew (5, 12, &myQueueCan2Rev_attributes);

  /* creation of myQueueCan1Rev */
  myQueueCan1RevHandle = osMessageQueueNew (5, 12, &myQueueCan1Rev_attributes);

  /* creation of myQueueCan3Rev */
  myQueueCan3RevHandle = osMessageQueueNew (5, 12, &myQueueCan3Rev_attributes);

  /* creation of myQueueUart7Rec */
  myQueueUart7RecHandle = osMessageQueueNew (2, 30, &myQueueUart7Rec_attributes);

  /* creation of myQueueUart2Spi3Rec */
  myQueueUart2Spi3RecHandle = osMessageQueueNew (6, 10, &myQueueUart2Spi3Rec_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* creation of myTask03 */
  myTask03Handle = osThreadNew(StartTask03, NULL, &myTask03_attributes);

  /* creation of myTask04 */
  myTask04Handle = osThreadNew(StartTask04, NULL, &myTask04_attributes);

  /* creation of myTask05 */
  myTask05Handle = osThreadNew(StartTask05, NULL, &myTask05_attributes);

  /* creation of myTask06 */
  myTask06Handle = osThreadNew(StartTask06, NULL, &myTask06_attributes);

  /* creation of myTask07 */
  myTask07Handle = osThreadNew(StartTask07, NULL, &myTask07_attributes);

  /* creation of myTask08 */
  myTask08Handle = osThreadNew(StartTask08, NULL, &myTask08_attributes);

  /* creation of myTask09 */
  myTask09Handle = osThreadNew(StartTask09, NULL, &myTask09_attributes);

  /* creation of myTask10 */
  myTask10Handle = osThreadNew(StartTask10, NULL, &myTask10_attributes);

  /* creation of myTask11 */
  myTask11Handle = osThreadNew(StartTask11, NULL, &myTask11_attributes);

  /* creation of myTask12 */
  myTask12Handle = osThreadNew(StartTask12, NULL, &myTask12_attributes);

  /* creation of myTask13 */
  myTask13Handle = osThreadNew(StartTask13, NULL, &myTask13_attributes);

  /* creation of myTask14 */
  myTask14Handle = osThreadNew(StartTask14, NULL, &myTask14_attributes);

  /* creation of myTask15 */
  myTask15Handle = osThreadNew(StartTask15, NULL, &myTask15_attributes);

  /* creation of myTask20 */
  myTask20Handle = osThreadNew(StartTask20, NULL, &myTask20_attributes);

  /* creation of myTask16 */
  myTask16Handle = osThreadNew(StartTask16, NULL, &myTask16_attributes);

  /* creation of myTask17 */
  myTask17Handle = osThreadNew(StartTask17, NULL, &myTask17_attributes);

  /* creation of myTask18 */
  myTask18Handle = osThreadNew(StartTask18, NULL, &myTask18_attributes);

  /* creation of myTask19 */
  myTask19Handle = osThreadNew(StartTask19, NULL, &myTask19_attributes);

  /* creation of myTask21 */
  myTask21Handle = osThreadNew(StartTask21, NULL, &myTask21_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */ //HH 没有使用到
	 HAL_GPIO_WritePin(GPIOG, REL_COM_Pin, GPIO_PIN_SET);//公共端12电接入驱动器 
	 HAL_GPIO_WritePin(GPIOG,REL_ACC_Pin, GPIO_PIN_SET);//整车上电 
	for(;;)
  {
    osDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**task2用于can和上位机通讯
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
//	uint8 msg[12]={0};
  osStatus_t status;
	HAL_GPIO_WritePin(GPIOG, CAN2_RSIS_Pin, GPIO_PIN_SET);//CAN2的终端电阻接上

  for(;;)
  {
		status = osMessageQueueGet(myQueueCan2RevHandle , j1939_msg_rev_can2.Array, NULL,0xffffffff);   // wait for message
		if (status == osOK)
		{
      uint8 i;
			uint16 pgn_temp ;
			pgn_temp=(uint16)j1939_msg_rev_can2.Array[1]<<8|j1939_msg_rev_can2.Array[2];

			for(i=0;i<FUNC_CAN2_MAX_NUM;i++)
			{
				if(user_can2_pro_func[i].pgn==pgn_temp)
				{			
						user_can2_pro_func[i].pfun( &j1939_msg_rev_can2);					
						break ;
				}			
			}
//			user_rec_radio_data_flag =0x01;//表示收到信息
		}	
    osDelay(1);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**task3用于本地无线数据接收
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
			uint8 msg_uart2_Rx[24]={0};

		osStatus_t uart2_status;
	   user_wl_init(&user_wl_struct);//初始化为跳频模式		
			
		if( user_wl_pra_RD(&user_wl_struct)==1)//读id，ch出错
		{
			user_send_str(&huart7,"无线模块参数读取失败");
		}
//		user_send_str(&huart7,"无线模块参数读取成功");
			
  /* Infinite loop */
  for(;;)
  {
		//这个队列仅用于触发
		uart2_status = osMessageQueueGet(myQueueUart2Spi3RecHandle , &msg_uart2_Rx, NULL, 0xffffffff);   // wait for message
		if (uart2_status == osOK)
		{	
				user_wl_pro(&user_wl_struct);//处理无线数据，
				memset(msg_uart2_Rx,0x00,sizeof(msg_uart2_Rx));	
		}
    osDelay(1); 
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**用于实时状态查询
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void *argument)
{
  /* USER CODE BEGIN StartTask04 */
  /* Infinite loop */
	for(;;)
  {
		user_AD_val_get( );//
//		user_safe_ctr( );//安全限位
    HAL_IWDG_Refresh(&hiwdg);//喂狗
		osDelay(5);
  }
  /* USER CODE END StartTask04 */
}

/* USER CODE BEGIN Header_StartTask05 */
/**用于can传感器之类的数据处理和接收
* @brief Function implementing the myTask05 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask05 */
void StartTask05(void *argument)
{
  /* USER CODE BEGIN StartTask05 */
  /* Infinite loop */
  osStatus_t status;
	HAL_GPIO_WritePin(GPIOF, CAN1_RESIS_Pin, GPIO_PIN_SET);//CAN1的终端电阻接上
	for(;;)
  {
		status = osMessageQueueGet(myQueueCan1RevHandle , j1939_msg_rev_can1.Array , NULL, 0xffffffff);   // wait for message
		if (status == osOK)
		{
      uint8 i;
			uint16 pgn_temp ;
			pgn_temp=(uint16)j1939_msg_rev_can1.Array[1]<<8|j1939_msg_rev_can1.Array[2];

			for(i=0;i<FUNC_CAN1_MAX_NUM;i++)
			{
				if(user_can1_pro_func[i].pgn==pgn_temp)
				{			
						user_can1_pro_func[i].pfun( &j1939_msg_rev_can1);					
						break ;
				}			
			}
			; // process data
    }
    osDelay(1);
  }
  /* USER CODE END StartTask05 */
}

/* USER CODE BEGIN Header_StartTask06 */
/**
* @brief Function implementing the myTask06 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask06 */
void StartTask06(void *argument)
{
  /* USER CODE BEGIN StartTask06 */
  /* Infinite loop */
   uint8  speed_text[8] = {0xf0,0xe0,0x80,0x7d,0xff,0xff,0xff,0xff}; //停止 
   int speed_temp2=0;
  for(;;)
  {
    if(speed_text1 == 1)//hh  本任务仅用于测试设置的基准速度，有无明显不合理
    {
      user_moter_pra.speed_base=(user_moter_pra.speed_init * YangTai_speed + 8032)*4; //基准速度，秧台速度，改task仅用于串口测试
			
			if(user_moter_pra.speed_base < 100)
				user_moter_pra.speed_base = 100;
			
      speed_temp2 = user_moter_pra.speed_base;
			speed_text[2] =  speed_temp2 &0xff;
			speed_text[3] =  speed_temp2>>8;							 
			user_can_EXTID_send(&hcan2,0x0cff9826, speed_text, (uint32_t*)CAN_TX_MAILBOX0);	
    }	
    osDelay(50);
  }
  /* USER CODE END StartTask06 */
}

/* USER CODE BEGIN Header_StartTask07 */
/**
* @brief Function implementing the myTask07 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask07 */
void StartTask07(void *argument)
{
  /* USER CODE BEGIN StartTask07 */
  /* Infinite loop */
	char msg_uart7_Rx[24]="0";
  osStatus_t status;
  for(;;)
  {
		status = osMessageQueueGet(myQueueUart7RecHandle, &msg_uart7_Rx, NULL, 0xffffffff);   // wait for message
		if (status == osOK)
		{	
				if(user_state.test_opr_mode==0x01)//测试模式
				{
//					User_Pra_TEST(user_set_buff ) ;
				}
				else//参数设置模式
				{
					User_Pra_Set(msg_uart7_Rx); 
				}
				memset(msg_uart7_Rx,0x00,sizeof(msg_uart7_Rx));		
		}
    osDelay(1);
  }
  /* USER CODE END StartTask07 */
}

/* USER CODE BEGIN Header_StartTask08 */
/**
* @brief Function implementing the myTask08 thread.
* @param argument: Not used
* @retval None
*/
//
/* USER CODE END Header_StartTask08 */
void StartTask08(void *argument)
{
  /* USER CODE BEGIN StartTask08 */
  /* Infinite loop */
//  osStatus_t val;
 uint8  speed[8] = {0xf0,0xe0,0x80,0x7d,0xff,0xff,0xff,0xff}; //停止 
 user_state.speed_cur = user_moter_pra.speed_base;
 user_state.fit_mode = 0x02; //刚上电给复位
  for(;;)
  {  
//		val = osSemaphoreAcquire(myCountingSemMoter1Handle, 0xffffffff); 
//		if (val== osOK)
		//3停止运行；1无人状态下，跟随；
    if(user_state.fit_mode==0x03 || user_state.stop_sta == 1)//停止运行，正处于推苗过程中或者遥控器急停
    {
       suidong_rec = 0;
       int speed_temp = 0x7D80;
			 speed[2] =  speed_temp &0xff;
			 speed[3] =  speed_temp>>8;							 
			 user_can_EXTID_send(&hcan2,0x0cff9826, speed, (uint32_t*)CAN_TX_MAILBOX0);
       Zhu_cont_data[0] = 0x03; //当前为复位状态      
    }
		else if((user_state.fit_mode==0x01) && (user_state.manul_auto == 0x02))//无人时
		{
			int speed_temp=0;
      user_moter_pra.speed_base=(user_moter_pra.speed_init * YangTai_speed+8032)*4;  //基准速度
      if((user_state.rice1_state == 3 || user_state.rice2_state == 3 || user_state.rice3_state == 3) && user_state.YangXiang_high == 1) //子控有秧板放下了，但秧箱抬起来了，停止动作，防止撞了
      {
         int speed_temp = 0x7D80;
			   speed[2] =  speed_temp &0xff;
			   speed[3] =  speed_temp>>8;							 
			   user_can_EXTID_send(&hcan2,0x0cff9826, speed, (uint32_t*)CAN_TX_MAILBOX0);  
         suidong_rec = 1;
      }
      else if((user_state.rice1_state == 3 || user_state.rice2_state == 3 || user_state.rice3_state == 3) && YangTai_speed == 0) //子控有秧板放下了，但秧台速度停了，缓速运行，hh一般是秧台已经抬起来了（除了传感器故障）
      {
         speed_temp = (user_moter_pra.speed_init * 1.8+8032)*4;
			   speed[2] =  speed_temp &0xff;
			   speed[3] =  speed_temp>>8;							 
				 user_can_EXTID_send(&hcan2,0x0cff9826, speed, (uint32_t*)CAN_TX_MAILBOX0);	 
         suidong_rec = 2;        
      }
      else
      {
        //在边缘换向时候
		    if((user_state.ang_m_dirc ==0) || (user_state.ang_s_dirc ==0))  //方向不明，换向时传感器检测不到    hh方向切换的时候，速度保持
				{
          if(user_state.speed_cur == 0x7D80) //此时碰巧停止状态，给缓速
          {
             user_state.speed_cur = (-1000 + 8032)*4;
          }
           speed_temp = user_state.speed_cur;  //换向时候维持当前速度不变
					 speed[2] =  speed_temp &0xff;
					 speed[3] =  speed_temp>>8;							 
					 user_can_EXTID_send(&hcan2,0x0cff9826, speed, (uint32_t*)CAN_TX_MAILBOX0);	
           suidong_rec = 3;          
				}		
        //同向运行
				else if((user_state.ang_m_dirc ==1) && (user_state.ang_s_dirc ==1))  //同时向左
				{
 				   int32 num = user_state.ang_s_num - user_state.ang_m_num; //秧板 - 秧台位置
					 if(num>=0) //秧板在后，追赶
					 { 
							speed_temp = user_moter_pra.speed_base + user_moter_pra.speed_f[num]; //追赶速度+基准速度
							m_thrd( &speed_temp,user_moter_pra.speed_base); 		
              suidong_rec = 4;
						 
							if(num > 20)
							speed_temp = 100;  //大偏差，直接高速追赶						 
					 }
           else if(num<0) //秧板在前，等待
           {
              num = 0-num; 
							speed_temp = user_moter_pra.speed_base - user_moter_pra.speed_b[num]; //追赶速度+基准速度
							m_thrd( &speed_temp,user_moter_pra.speed_base);      
              suidong_rec = 5;    

					    if(num > 20)
						    speed_temp = 32128;  //大偏差，静止等待						 
           }
					 speed[2] =  speed_temp &0xff;
				   speed[3] =  speed_temp>>8;							 
				   user_can_EXTID_send(&hcan2,0x0cff9826, speed, (uint32_t*)CAN_TX_MAILBOX0);	
				}	
				else if((user_state.ang_m_dirc == 2) && (user_state.ang_s_dirc == 2)) //同时向右
				{
 				   int32 num = user_state.ang_s_num - user_state.ang_m_num;  //秧板 - 秧台位置
					 if(num>=0) //秧板在前，等待
				   {
							speed_temp =   user_moter_pra.speed_base - user_moter_pra.speed_b[num];
							m_thrd( &speed_temp,user_moter_pra.speed_base);
              suidong_rec = 5;       
						 
					    if(num > 20)
						    speed_temp = 32128;  //大偏差，静止等待							 
				   }
           else if(num<0) //秧板在后，追赶
           {
              num = 0-num; 
							speed_temp =   user_moter_pra.speed_base + user_moter_pra.speed_f[num];
							m_thrd( &speed_temp,user_moter_pra.speed_base);		   
              suidong_rec = 4;    

					    if(num > 20)
						    speed_temp = 100;  //大偏差，高速追赶							 
           }
					 speed[2] =  speed_temp &0xff;
					 speed[3] =  speed_temp>>8;							 
					 user_can_EXTID_send(&hcan2,0x0cff9826, speed, (uint32_t*)CAN_TX_MAILBOX0);	
				}
        
        //反向运行，hh 以到边缘的距离左依据，秧板近就追
				else if((user_state.ang_m_dirc ==1) && (user_state.ang_s_dirc ==2)) //秧台朝左，秧板向右
				{
           uint8 dis_m = 0; //秧台到边缘距离
           uint8 dis_s = 0; //秧板到边缘距离
           uint8 num = 0;
          
           dis_m = user_state.ang_m_num - 0;   //秧台向左，所以 它 - 0
           dis_s = 59 - user_state.ang_s_num;  //秧板向右，所以 59 - 它
            
           if(dis_s < dis_m)  //秧板的距离比秧台小，追赶
           {
              num = (59 - user_state.ang_m_num) + (59 - user_state.ang_s_num);
							speed_temp =   user_moter_pra.speed_base + user_moter_pra.speed_f[num];
							m_thrd( &speed_temp,user_moter_pra.speed_base);	
              suidong_rec = 4;     

					    if(num > 20)
						    speed_temp = 100;  //大偏差，高速追赶								 
           }
           else   //秧板的距离比秧台大，等待
           {
             num = user_state.ang_m_num + user_state.ang_s_num;
						 speed_temp =   user_moter_pra.speed_base - user_moter_pra.speed_b[num];
						 m_thrd( &speed_temp,user_moter_pra.speed_base);	
             suidong_rec = 5;  
						 
					   if(num > 20)
						   speed_temp = 32128;  //大偏差，静止等待								 
           }				 
					 speed[2] =  speed_temp &0xff;
				   speed[3] =  speed_temp>>8;							 
					 user_can_EXTID_send(&hcan2,0x0cff9826, speed, (uint32_t*)CAN_TX_MAILBOX0);	            
				}		
        
				else if((user_state.ang_m_dirc ==2) && (user_state.ang_s_dirc ==1)) //秧台向右，秧板向左
				{
           uint8 dis_m = 0; //秧台到边缘距离
           uint8 dis_s = 0; //秧板到边缘距离
           uint8 num = 0;
          
           dis_m = 59 - user_state.ang_m_num;   //秧台向右，所以 59 - 它
           dis_s = user_state.ang_s_num - 0;    //秧板向左，所以 它 - 0
            
           if(dis_s < dis_m)  //秧板的距离比秧台小，追赶
           {
              num = user_state.ang_m_num + user_state.ang_s_num;
							speed_temp =   user_moter_pra.speed_base + user_moter_pra.speed_f[num];
							m_thrd( &speed_temp,user_moter_pra.speed_base);	 
              suidong_rec = 4;     

					    if(num > 20)
						    speed_temp = 100;  //大偏差，高速追赶							 
           }
           else   //秧板的距离比秧台大，等待
           {
             num = (59 - user_state.ang_m_num) + (59 - user_state.ang_s_num);
						 speed_temp =   user_moter_pra.speed_base - user_moter_pra.speed_b[num];
						 m_thrd( &speed_temp,user_moter_pra.speed_base);
             suidong_rec = 5; 
						 
					   if(num > 20)
						   speed_temp = 32128;  //大偏差，静止等待								 
           }
					 speed[2] =  speed_temp &0xff;
				   speed[3] =  speed_temp>>8;							 
					 user_can_EXTID_send(&hcan2,0x0cff9826, speed, (uint32_t*)CAN_TX_MAILBOX0);       
				}			
      }        
			user_state.speed_cur	= speed_temp;
      
      Zhu_cont_data[0] = 1; //正在同步
       if(abs(user_state.ang_m_num - user_state.ang_m_num) < 5) //已经同步上，可以放秧了
       {
           if(user_state.YangXiang_high == 1) //当前转弯，秧箱是抬升状态
              Zhu_cont_data[0] = 1; //正在同步中
           else 
            Zhu_cont_data[0] = 2;  //秧板已同步
       }  
     speed_show = speed_temp;
		}
    
		else if(user_state.fit_mode==0x02) //回位，回到加苗的位置  //hh 指的是，把苗推到秧板的上面，
		{
      suidong_rec = 0;
      if((user_moter_pra.AN_reset_data>4095)||(user_moter_pra.AN_reset_data<=100)) //标定有问题，不动作
      {
          ;
      }
      else
      {
				int speed_temp = (-1000 + 8032)*4;
				if((AD_CH_value[0] - user_moter_pra.AN_reset_data < 50) && (user_moter_pra.AN_reset_data - AD_CH_value[0] < 50)) //距离很小
				{
					 speed_temp = 0x7D80; //停下
					 Zhu_cont_data[0] = 0x03; //秧板已复位
				}
				else if((AD_CH_value[0] - user_moter_pra.AN_reset_data < 200) && (user_moter_pra.AN_reset_data - AD_CH_value[0] < 200))
				{
					 speed_temp = (-560 + 8032)*4;
					 Zhu_cont_data[0] = 0x04; //秧板复位中      
				}
				else if((AD_CH_value[0] - user_moter_pra.AN_reset_data < 400) && (user_moter_pra.AN_reset_data - AD_CH_value[0] < 400))
				{
					 speed_temp = (-900 + 8032)*4;
					 Zhu_cont_data[0] = 0x04; //秧板复位中      
				}
				else
				{
					 speed_temp = (-1200 + 8032)*4;
					 Zhu_cont_data[0] = 0x04; //秧板复位中
				}
					 speed[2] =  speed_temp &0xff;
					 speed[3] =  speed_temp>>8;							 
					 user_can_EXTID_send(&hcan2,0x0cff9826, speed, (uint32_t*)CAN_TX_MAILBOX0);	 	 
		  }
    }
    else if(user_state.fit_mode==0x00)//；hh在标定的时候，不给电机发数据
    {
       suidong_rec = 0;
    }      

	  osDelay(30);
  }
  /* USER CODE END StartTask08 */
}

/* USER CODE BEGIN Header_StartTask09 */
/*
* @brief Function implementing the myTask09 thread.
* @param argument: Not used
* @retval None
*/
//
/* USER CODE END Header_StartTask09 */  //hh抬样箱
void StartTask09(void *argument)
{
  /* USER CODE BEGIN StartTask09 */
  /* Infinite loop */
   osStatus_t val;
  user_moter_stop(0x02);
	for(;;)
  {
		val = osSemaphoreAcquire(myCountingSemMoter2Handle, 0xffffffff); 
		if (val== osOK)
		{
			if(user_state.stop_sta == 0)
			{
					uint8 i = 0;
					if((user_state.YangXiang_high == 1)||(user_state.less_yangxiang == 1)) //秧箱升起
					{
						 user_moter_forward(0x02,500); //电机伸长
						 while(AD_CH_value[1] < user_flash_moter_pra.AN_Val[1][1]-20) //长度还没伸到位，继续升
						 {
								i++;
								osDelay(50);
								if(i > 200) //最长10秒钟断电
								break;
						 }
						 user_moter_stop(0x02); //电机停止
					}
					else if((user_state.YangXiang_high == 2)||(user_state.less_yangxiang == 2)) //秧箱落下
					{
						 user_moter_backward(0x02,500); //电机缩短
						 while(AD_CH_value[1] > user_flash_moter_pra.AN_Val[1][0]+20) //还未缩到位
						 {
								i++;
								osDelay(50);
								if(i > 200) //最长10秒钟断电
								break;
						 }
						 user_moter_stop(0x02); //电机停止        
					}			
			}
			else 
			  user_moter_stop(0x02);
		}
    osDelay(100);
  }
  /* USER CODE END StartTask09 */
}

/* USER CODE BEGIN Header_StartTask10 */
/**
* @brief Function implementing the myTask10 thread.
* @param argument: Not used
* @retval None
*/
//卸粮
/* USER CODE END Header_StartTask10 */
void StartTask10(void *argument)//hh抬样箱
{
  /* USER CODE BEGIN StartTask10 */
  /* Infinite loop */
   osStatus_t val;
  user_moter_stop(0x03);
	for(;;)
  {
		val = osSemaphoreAcquire(myCountingSemMoter3Handle, 0xffffffff); 
		if (val== osOK)
		{
			if(user_state.stop_sta == 0)
			{
					uint8 i = 0;
					if((user_state.YangXiang_high == 1)||(user_state.less_yangxiang == 1)) //秧箱升起
					{
						 user_moter_forward(0x03,500); //电机伸长
						 while(AD_CH_value[2] < user_flash_moter_pra.AN_Val[2][1]-20) //长度还没伸到位，继续升
						 {
								i++;
								osDelay(50);
								if(i > 200) //最长10秒钟断电
								break;
						 }
						 user_moter_stop(0x03); //电机停止
					}
					else if((user_state.YangXiang_high == 2)||(user_state.less_yangxiang == 2)) //秧箱落下
					{
						 user_moter_backward(0x03,500); //电机伸长
						 while(AD_CH_value[2] > user_flash_moter_pra.AN_Val[2][0]+20) //还未缩到位
						 {
								i++;
								osDelay(50);
								if(i > 200) //最长10秒钟断电
								break;
						 }
						 user_moter_stop(0x03); //电机停止        
					}		
			}
			else
				 user_moter_stop(0x03);		
		}
    osDelay(100);
  }
  /* USER CODE END StartTask10 */
}

/* USER CODE BEGIN Header_StartTask11 */
/**
* @brief Function implementing the myTask11 thread.
* @param argument: Not used
* @retval None
*/
//脱谷
/* USER CODE END Header_StartTask11 */ //hh抬样箱
void StartTask11(void *argument)
{
  /* USER CODE BEGIN StartTask11 */
  /* Infinite loop */
   osStatus_t val;
  user_moter_stop(0x04);
	for(;;)
  {
		val = osSemaphoreAcquire(myCountingSemMoter4Handle, 0xffffffff); 
		if (val== osOK)
		{
			if(user_state.stop_sta == 0)
			{
        uint8 i = 0;
        if((user_state.YangXiang_high == 1)||(user_state.less_yangxiang == 1))//秧箱升起
        {
           user_moter_forward(0x04,500); //电机伸长
           while(AD_CH_value[3] < user_flash_moter_pra.AN_Val[3][1]-20) //长度还没伸到位，继续升
           {
              i++;
              osDelay(50);
              if(i > 200) //最长10秒钟断电
              break;
           }
           user_moter_stop(0x04); //电机停止
        }
        else if((user_state.YangXiang_high == 2)||(user_state.less_yangxiang == 2)) //秧箱落下
        {
           user_moter_backward(0x04,500); //电机伸长
           while(AD_CH_value[3] > user_flash_moter_pra.AN_Val[3][0]+20) //还未缩到位
           {
              i++;
              osDelay(50);
              if(i > 200) //最长10秒钟断电
              break;
           }
           user_moter_stop(0x04); //电机停止        
        }				
			}
			else
			  user_moter_stop(0x04);
		}
    osDelay(100);
  }
  /* USER CODE END StartTask11 */
}

/* USER CODE BEGIN Header_StartTask12 */
/**
* @brief Function implementing the myTask12 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask12 *///hh抬样箱
void StartTask12(void *argument)
{
  /* USER CODE BEGIN StartTask12 */
  /* Infinite loop */
   osStatus_t val;
  user_moter_stop(0x05);
	for(;;)
  {
		val = osSemaphoreAcquire(myCountingSemMoter5Handle, 0xffffffff); 
		if (val== osOK)
		{
			if(user_state.stop_sta == 0)
			{
        uint8 i = 0;
        if((user_state.YangXiang_high == 1)||(user_state.less_yangxiang == 1)) //秧箱升起
        {
           user_moter_forward(0x05,500); //电机伸长
           while(AD_CH_value[4] < user_flash_moter_pra.AN_Val[4][1]-20) //长度还没伸到位，继续升
           {
              i++;
              osDelay(50);
              if(i > 200) //最长10秒钟断电
              break;
           }
           user_moter_stop(0x05); //电机停止
        }
        else if((user_state.YangXiang_high == 2)||(user_state.less_yangxiang == 2)) //秧箱落下
        {
           user_moter_backward(0x05,500); //电机伸长
           while(AD_CH_value[4] > user_flash_moter_pra.AN_Val[4][0]+20) //还未缩到位
           {
              i++;
              osDelay(50);
              if(i > 200) //最长10秒钟断电
              break;
           }
           user_moter_stop(0x05); //电机停止        
        }			
			}
			else
				user_moter_stop(0x05);
		}
    osDelay(100);
  }
  /* USER CODE END StartTask12 */
}

/* USER CODE BEGIN Header_StartTask13 */
/**
* @brief Function implementing the myb thread.
* @param argument: Not used
* @retval None
*/
//hh 告诉无人控制器，原车的秧台是不是可以抬升
/* USER CODE END Header_StartTask13 */  
void StartTask13(void *argument)
{
  /* USER CODE BEGIN StartTask13 */
  /* Infinite loop */
//   osStatus_t val;
	uint8 can_tx_high[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	for(;;)
  {
//		val = osSemaphoreAcquire(myCountingSemDOHandle, 0xffffffff); 
//		if (val== osOK)
//		{
//      
//    }
      if((AD_CH_value[1] > user_flash_moter_pra.AN_Val[1][1] - 100)&&
         (AD_CH_value[2] > user_flash_moter_pra.AN_Val[2][1] - 100)&&
         (AD_CH_value[3] > user_flash_moter_pra.AN_Val[3][1] - 100)&&
         (AD_CH_value[4] > user_flash_moter_pra.AN_Val[4][1] - 100))   
      {
         can_tx_high[0] = 0x01;  //每个电机都抬到位，可以升 hh告诉无人控制器状态
      }
      else //禁止升
      {
         can_tx_high[0] = 0x02;
      }
      
      if(user_state.rice1_state == 3 || user_state.rice2_state == 3 || user_state.rice3_state == 3) //只要有秧板放下的，秧台禁止升
      {
         can_tx_high[0] = 0x02;
      }
      user_can_EXTID_send(&hcan2,0x0C900502,can_tx_high, (uint32_t*)CAN_TX_MAILBOX0); //告诉无人驾驶控制器，秧台能不能升
			osDelay(100);        
	}
  /* USER CODE END StartTask13 */
}

/* USER CODE BEGIN Header_StartTask14 */
/**
* @brief Function implementing the myTask13 thread.
* @param argument: Not used
* @retval None
*/
//无阻塞 DO 查询方式，割台升降；5,1高位；5,0，低位
/* USER CODE END Header_StartTask14 */
void StartTask14(void *argument)
{
  /* USER CODE BEGIN StartTask14 */
  /* Infinite loop */

//	osStatus_t val;
	for(;;)//hh 子控制器上报单双列状态，主控反馈锁定的单双列给到所有子控制器
  {
//			val = osSemaphoreAcquire( myCountingSemPend1Handle, 0xffffffff); 
//			if (val== osOK)
//			{

//      }
		if(user_state.stop_sta == 1) //急停，断电 hh断子控制器的电
		{
      HAL_GPIO_WritePin(GPIOE, DO4_Pin, GPIO_PIN_RESET);	
			
		}
		else
			HAL_GPIO_WritePin(GPIOE, DO4_Pin, GPIO_PIN_SET);
		
    if(user_state.manul_auto == 2 && user_state.stop_sta == 0) //无人状态
    {
			 Zhu_cont_data[7] = user_state.lieshu_jilu;  //获取主控锁定状态，发给子控
			
       user_can_EXTID_send(&hcan1,0x0C900501, Zhu_cont_data, (uint32_t*)CAN_TX_MAILBOX0);	  //子控接CAN1,告知秧板状态 
    }
    else if(user_state.manul_auto == 1) //手动状态才发 hh 遥控信息
    {
       user_can_EXTID_send(&hcan1,0x0C900601, Zhu_less_data, (uint32_t*)CAN_TX_MAILBOX0);	  //上苗装置遥控执行
			Zhu_less_data[7] = 0;
    }  		
		osDelay(100); //时间不可随意改
  }
  /* USER CODE END StartTask14 */ 
}

/* USER CODE BEGIN Header_StartTask15 */
/**
* @brief Function implementing the myTask15 thread.
* @param argument: Not used
* @retval None
*/
//hh 解析子控制器数据，设置跟随电机、单双列电机状态
/* USER CODE END Header_StartTask15 */
void StartTask15(void *argument)
{
  /* USER CODE BEGIN StartTask15 */
  /* Infinite loop */
//   osStatus_t val;

	uint8 i = 0;
	for(;;)
  {
//		val = osSemaphoreAcquire(myCountingSemEngineHandle, 0xffffffff); 
//		if (val== osOK)
//		{
//      
//		}
		//相同的列在推苗，有新的需要推，就一起推。后续一起加。
    if(user_state.rice1_state == 2 || user_state.rice2_state == 2 || user_state.rice3_state == 2) //只要有一个在推苗中，就保持不动
    {
       i = 1;
       user_state.fit_mode = 3;
    }
    else if(user_state.rice1_state == 1 || user_state.rice2_state == 1 || user_state.rice3_state == 1) //没有正在推苗，只要有一个推苗完成就开始同步
    {
			 i = 1;
       user_state.fit_mode = 1; //秧板同步
			 user_state.huanhang_sta = user_state.lieshu_jilu; //hh 同步时，考虑单双列，和同步电机，同时进行
			 osSemaphoreRelease(myCountingSemElecAcceleratorHandle); //样板换行操作
    }
    else if(user_state.rice1_state != 3 && user_state.rice2_state != 3 && user_state.rice3_state != 3) //没有正在卸苗的
    {
       if(user_state.rice1_state == 4 || user_state.rice2_state == 4 || user_state.rice3_state == 4) //并且有已经卸苗完成的
       {
				 if(i == 1)
				 {
					 i = 0;
					 user_state.lieshu_jilu = 0;   //列数标记清除
				 }
				 
         user_state.fit_mode = 2;      //随动复位
				 user_state.huanhang_sta = 0;  //换列电机复位
				 osSemaphoreRelease(myCountingSemElecAcceleratorHandle); //换行执行复位
       }
    }    
    osDelay(10);
  }
  /* USER CODE END StartTask15 */
}

/* USER CODE BEGIN Header_StartTask20 */
/**
* @brief Function implementing the myTask20 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask20 */
void StartTask20(void *argument)
{
  /* USER CODE BEGIN StartTask20 */
  /* Infinite loop */

  user_state.manul_auto = 0x01;//初始默认是人工操作
	for(;;)
  {		
    osDelay(100);
  }
  /* USER CODE END StartTask20 */
}

/* USER CODE BEGIN Header_StartTask16 */
/**
* @brief Function implementing the myTask16 thread.
* @param argument: Not used
* @retval None
*/
//hh 判断样板、秧台运动方向和位置
/* USER CODE END Header_StartTask16 */
void StartTask16(void *argument)
{
  /* USER CODE BEGIN StartTask16 */
  /* Infinite loop */
	static int  AD_CH_value6_temp;
	static int  AD_CH_value6_record1,AD_CH_value6_record2,AD_CH_value6_record3,AD_CH_value6_record4,AD_CH_value6_record5;
	
	static int  AD_CH_value0_temp;
	static int  AD_CH_value0_record1,AD_CH_value0_record2,AD_CH_value0_record3,AD_CH_value0_record4,AD_CH_value0_record5;
	
	
	static uint8 m_data = 0;  //秧台  1左侧AD值大；2侧AD值大
	static uint8 m_l_r = 0;   //秧台  1向左移动；2向右移动

	static uint8 s_data = 0; //1左大；2右大
	static uint8 s_l_r = 0;   //1左方向；2右方向
 
  
	uint8 ang_s_num =0;  //秧板所在位置
 	uint8 ang_m_num =0;  //秧台所在位置
 
	uint8 a0_thd =5;
	uint8 a6_thd =5;	
	
	if( user_moter_pra.ang_m[0]>user_moter_pra.ang_m[59])//秧台，坐在驾驶位置，左侧大
	{
     m_data = 1;
	}
	else if( user_moter_pra.ang_m[0]<user_moter_pra.ang_m[59])//秧台，坐在驾驶位置，右侧大
	{
	   m_data = 2;  
	}	
	 
	if( user_moter_pra.ang_s[0]>user_moter_pra.ang_s[59])//秧板，坐在驾驶位置，左侧大
	{
     s_data = 1;
	}
	else if( user_moter_pra.ang_s[0]<user_moter_pra.ang_s[59])//秧板，坐在驾驶位置，右侧大
	{
	   s_data = 2;  
	}		
	
	user_state.manul_auto = 0x01;//初始默认是人工操作
	for(;;)
  {
     AD_CH_value6_temp = AD_CH_value[6];//秧台获取数据,判断运动方向
     AD_CH_value0_temp = AD_CH_value[0];//秧板电机获取数据,判断运动方向
		 
		if(AD_CH_value6_temp > (AD_CH_value6_record1 + a6_thd) && (AD_CH_value6_record1>AD_CH_value6_record2) + a6_thd) //AD值逐渐增大
		{
		  if(m_data==1) //左侧大，秧台向左移动
			  m_l_r = 1;
			else if(m_data==2) //右侧大，秧台向右移动
			  m_l_r = 2;
		}
		else if(AD_CH_value6_temp < (AD_CH_value6_record1 - a6_thd) && AD_CH_value6_record1 < (AD_CH_value6_record2 - a6_thd)) //AD值逐渐减小
		{
		  if(m_data==1) //左侧大，秧台向右移动
			  m_l_r = 2;
			else if(m_data==2) //右侧大，秧台向左移动
			  m_l_r = 1;
		}
		else//静止不动作
			 m_l_r = 0;			
		
		if(AD_CH_value6_temp < user_moter_pra.ang_m[0]+60 || AD_CH_value6_temp > user_moter_pra.ang_m[59]-60)  //在边缘位置(目前确认AD值左侧小右侧大)
		  m_l_r = 0;			


//		if( user_state.fit_mode!=0x01)//秧板不动作
//		  s_l_r = 0;
	  if(AD_CH_value0_temp > (AD_CH_value0_record1+  a0_thd) && AD_CH_value0_record1 > (AD_CH_value0_record2+ a0_thd)) //AD值逐渐变大
		{
		  if(s_data==1)//左侧大
			  s_l_r = 1;
			else if(s_data==2)//右侧大
			  s_l_r = 2;
		}
		else if(AD_CH_value0_temp < (AD_CH_value0_record1- a0_thd) && AD_CH_value0_record1 <(AD_CH_value0_record2-a0_thd)) //AD值逐渐减小
		{
		  if(s_data==1)//左侧大
			  s_l_r = 2;
			else if(s_data==2)//右侧大
			  s_l_r = 1;
		}
		else//静止不动作
			 s_l_r = 0;
	
		if(AD_CH_value0_temp < user_moter_pra.ang_s[0]+60 || AD_CH_value0_temp > user_moter_pra.ang_s[59]-60)  //在边缘位置(目前确认AD值左侧小右侧大)
		   s_l_r = 0;
		
		
		//判断秧台当前位置
		{
			uint8 i=0;
			for(i=0;i<60;i++)
			{
				if(AD_CH_value6_temp<user_moter_pra.ang_m[i])	
				{
					 ang_m_num = i;
					 break;						
				}
			} 
		}
 
    //判断秧板当前位置
		{
			uint8 i=0;
			for(i=0;i<60;i++)
			{
				if(AD_CH_value0_temp<user_moter_pra.ang_s[i])	
				{
					ang_s_num = i;
					break;						
				}
			}	  
		}		
		
		AD_CH_value6_record5 =AD_CH_value6_record4;
		AD_CH_value6_record4 =AD_CH_value6_record3;
		AD_CH_value6_record3 =AD_CH_value6_record2;
		AD_CH_value6_record2 =AD_CH_value6_record1;
//		AD_CH_value6_record1 =AD_CH_value[6];				
    AD_CH_value6_record1 = AD_CH_value6_temp;
		
    AD_CH_value0_record5 =AD_CH_value0_record4;
		AD_CH_value0_record4 =AD_CH_value0_record3;
		AD_CH_value0_record3=AD_CH_value0_record2;
		AD_CH_value0_record2=AD_CH_value0_record1;
//		AD_CH_value0_record1 =AD_CH_value[0];			
    AD_CH_value0_record1 = AD_CH_value0_temp;

		
		user_state.ang_m_dirc = m_l_r;	//秧台运行方向
		user_state.ang_s_dirc = s_l_r;  //秧板运行方向
   
	  user_state.ang_m_num = ang_m_num;	//秧台所处位置	
	  user_state.ang_s_num = ang_s_num; //秧板所处位置
 
     //调试模式手动输，正式版屏蔽 
//		user_state.ang_m_dirc = yangtai_dir;	//秧台运行方向
//		user_state.ang_s_dirc = yangban_dir;  //秧板运行方向
//   
//	  user_state.ang_m_num = yangtai_wz;	//秧台所处位置	
//	  user_state.ang_s_num = yangban_wz; //秧板所处位置		

		osDelay(80);//要延时100ms，监测的是5个数据，500毫秒内的动作
  }
  /* USER CODE END StartTask16 */
}

/* USER CODE BEGIN Header_StartTask17 */
/**
* @brief Function implementing the myTask17 thread.
* @param argument: Not used
* @retval None 秧板换列执行
*/
/* USER CODE END Header_StartTask17 */ //hh 换单双行，只有一个换行电机，最短最长分别对应单双行，复位在中间需要检测模拟量
void StartTask17(void *argument)
{
  /* USER CODE BEGIN StartTask17 */
  /* Infinite loop */
   osStatus_t val17;
	user_state.huanhang_sta = 0;
	osSemaphoreRelease(myCountingSemElecAcceleratorHandle);  //上电给复位
	for(;;)
  {
		val17 = osSemaphoreAcquire(myCountingSemElecAcceleratorHandle, 0xffffffff); 
		if (val17== osOK)
		{
			 if(user_state.huanhang_sta == 0)  //复位
			 {
					 if(user_moter_pra.yangban_xuanzhe < 200 || user_moter_pra.yangban_xuanzhe > 4000) //标定错误，不动
					 {
						 user_moter_stop(0x01); 
					 }
					 else if(AD_CH_value[5] > user_moter_pra.yangban_xuanzhe + 40)  //当前值大于复位值，缩短
					 {
							while(AD_CH_value[5] > user_moter_pra.yangban_xuanzhe)
							{
								if(AD_CH_value[5] < (user_moter_pra.yangban_xuanzhe + 180))//大于100以内，低速
									user_moter_backward(0x01,180);
								else if(AD_CH_value[5] < (user_moter1.target_value + 300))//中速
									user_moter_backward(0x01,300);
								else
									user_moter_backward(0x01,500);	

								osDelay(10);	
							}						
					 }
					 else if(AD_CH_value[5] < user_moter_pra.yangban_xuanzhe - 40) //当前值大于复位值，伸长
					 {
							while(AD_CH_value[5] < user_moter_pra.yangban_xuanzhe)
							{
								if(AD_CH_value[5] > (user_moter_pra.yangban_xuanzhe - 180))
									user_moter_forward(0x01,180);
								else if(AD_CH_value[5] > (user_moter_pra.yangban_xuanzhe - 300))
									user_moter_forward(0x01,300);
								else
									user_moter_forward(0x01,500);
								
								osDelay(10);	
							}						
					 }
					 else //已经是复位状态
					 {
//							Zhu_cont_data[1] = 0;
					 }	
		     user_moter_stop(0x01); 					 
			 }
			 else if(user_state.huanhang_sta == 1)  //单列，缩短
			 {
				  user_moter_backward(0x01,500);	
			 }
			 else if(user_state.huanhang_sta == 2) //双列，伸长
			 {
				  user_moter_forward(0x01,500);
			 }
		}
    osDelay(10);
  }
  /* USER CODE END StartTask17 */
}

/* USER CODE BEGIN Header_StartTask18 */
/**
* @brief Function implementing the myTask18 thread.
* @param argument: Not used
* @retval None
*/

/* USER CODE END Header_StartTask18 */
void StartTask18(void *argument)
{
  /* USER CODE BEGIN StartTask18 */
  /* Infinite loop */
  char Ptr[30]={0};
	for(;;)//hh 串口调试用
  {  
//     if(user_state.lieshu_jilu == 1)
//		 {
//		 
//		 }
		 if(user_state.manul_auto == 0x02)
		 {
			 user_send_str(&huart7, " ->随动模式，状态,速度：");
			 sprintf(Ptr,"%d,%d,%d\r\n",user_state.fit_mode,suidong_rec,speed_show);
			 user_send_str(&huart7, Ptr);
			 memset(Ptr,0,30);	
			 
			 user_send_str(&huart7, " ->列数选择：");
			 sprintf(Ptr,"%d\r\n",user_state.lieshu_jilu);
			 user_send_str(&huart7, Ptr);
			 memset(Ptr,0,30);				 
			 
			 user_send_str(&huart7, " ->秧台方向，位置：");
			 sprintf(Ptr,"%d,%d\r\n",user_state.ang_m_dirc,user_state.ang_m_num);
			 user_send_str(&huart7, Ptr);
			 memset(Ptr,0,30);	
			 user_send_str(&huart7, " ->秧板方向，位置：");		 
			 sprintf(Ptr,"%d,%d\r\n",user_state.ang_s_dirc,user_state.ang_s_num);
			 user_send_str(&huart7, Ptr);
			 memset(Ptr,0,30);			
			 user_send_str(&huart7, " ->秧台速度：");
			 sprintf(Ptr,"%d\r\n",YangTai_speed);
			 user_send_str(&huart7, Ptr);
			 memset(Ptr,0,30);				 
		 }	
		 
		 if(speed_text1 == 2)
		 {
			 user_send_str(&huart7, " ->秧台速度：");
			 sprintf(Ptr,"%d\r\n",YangTai_speed);
			 user_send_str(&huart7, Ptr);
			 memset(Ptr,0,30);	 		 
		 }
		 
		 HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);		//灯闪
		 osDelay(500);     
  }
  /* USER CODE END StartTask18 */
}

/* USER CODE BEGIN Header_StartTask19 */
/**
* @brief Function implementing the myTask19 thread.
* @param argument: Not used
* @retval None
*/
//粮筒的控制
/* USER CODE END Header_StartTask19 */
void StartTask19(void *argument)
{
  /* USER CODE BEGIN StartTask19 *///hh 样箱电机保护，不倾斜太多
  /* Infinite loop */
// 	osStatus_t val19;

	for(;;)
  {
     if(user_state.manul_auto == 0x02)
     {
        if( abs(AD_CH_value[1] - AD_CH_value[2]) > 600 ||
            abs(AD_CH_value[1] - AD_CH_value[3]) > 600 ||
            abs(AD_CH_value[1] - AD_CH_value[4]) > 600  )  //秧箱电机位置误差过大，停止
        {
           user_state.fit_mode = 0x03;
					
           user_moter_stop(0x02);
           user_moter_stop(0x03);
           user_moter_stop(0x04);
           user_moter_stop(0x05);
        }
     }
     osDelay(100);
  }
  /* USER CODE END StartTask19 */
}

/* USER CODE BEGIN Header_StartTask21 */
/**
* @brief Function implementing the myTask21 thread.
* @param argument: Not used
* @retval None
*/
//收割机转向
/* USER CODE END Header_StartTask21 */
void StartTask21(void *argument)
{
  /* USER CODE BEGIN StartTask21 */
  /* Infinite loop */
//  osStatus_t val21;
//  char Ptr[30]={0};
	
	uint8 wz1_rec = 0;
	uint8 wz2_rec = 0;
	YangTai_speed = 0;
	for(;;)
  {
//		val21 = osSemaphoreAcquire( myCountingSemAutoTurnHandle, 0xffffffff); 
//		if(val21==osOK)
//		{
		//hh 检测秧台的左右速度,限定了特定区段来检测
      if(user_state.ang_m_dirc == 2 && user_state.ang_m_num>10 && user_state.ang_m_num<15) //秧板方向朝右
			{
			   wz1_rec = user_state.ang_m_num;
				 osDelay(1300); 
				 wz2_rec = user_state.ang_m_num; //1.5秒后数据记录，看差值，越大速度越快
				 if(wz2_rec > 55)
					 wz2_rec = 55;
				 
				 YangTai_speed = wz2_rec - wz1_rec;
			}				
         
      osDelay(10);  
//    }
  }
  /* USER CODE END StartTask21 */
}


/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

