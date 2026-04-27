/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:
********************************************/
#ifndef _USER_FREE_RT_OS_H_
#define _USER_FREE_RT_OS_H_

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "USER_GLOBAL.h"

extern osMessageQueueId_t myQueueCan1RevHandle;
extern osMessageQueueId_t myQueueCan2RevHandle;
extern osMessageQueueId_t myQueueCan3RevHandle;
extern osMessageQueueId_t myQueueUart7RecHandle;
extern osMessageQueueId_t myQueueUart2Spi3RecHandle;
extern osSemaphoreId_t myCountingSemMoter1Handle;
extern osSemaphoreId_t myCountingSemMoter2Handle;
extern osSemaphoreId_t myCountingSemMoter3Handle;
extern osSemaphoreId_t myCountingSemMoter4Handle;
extern osSemaphoreId_t myCountingSemMoter5Handle;
extern osSemaphoreId_t myCountingSemEngineHandle;
extern osSemaphoreId_t myCountingSemDOHandle;
 
extern osSemaphoreId_t myCountingSemElecAcceleratorHandle;
extern osSemaphoreId_t myCountingSemTubeHandle;
extern osSemaphoreId_t myCountingSemAutoTurnHandle;
/* USER CODE END Includes */


#endif


