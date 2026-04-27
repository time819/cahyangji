#ifndef __LSCANUPGRADE_H
#define __LSCANUPGRADE_H

#include "SimpleQueue.h"
#include "stm32f7xx_hal_can.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "USER_DATA_TYPE.h"
//#include "can_config.h"


#define CANTxUPG_ID					0x18EF2690
#define CANRxUPG_ID					0x18EF9026
#define CANCfg_ID   		 		0x18FFF326


typedef enum {
  UPG_Useless			= 0,
  UPG_Ver			    = 1,//版本号
	UPG_Timer				= 2,//倒计时
	UPG_Menu				= 3//升级菜单
}BootUPGStateTypedef;

typedef struct
{
	void (*CANSendPtr)(uint32_t Device_ID,uint8_t *TX_msg,uint8_t TX_len); //CAN发送
	void (*SystemResetFctn)();//系统复位函数
	void (*YmodeDelay_MS)(uint16 num); //延时函数ms,参数类型修改为uint16
}CANUPGParmInitTypedef;

extern ElemType EnableCanBoot;
extern CANUPGParmInitTypedef CANUPGParmInit;


int ReceiveCanData(ElemType *Datatemp,ElemType DLC);
uint8_t CANUPG_Send_Msg(uint8_t* msg,int len);
char *OutUPGStr(BootUPGStateTypedef BootUPGState,char Instr[]);
int CANDataToYmodem(ElemType *c);
void RecvCANData(CAN_RxHeaderTypeDef RxHeader,uint8_t RxData[]);
void StartCountDownFctn(void);
void SendMenuInfoFctn(void);
void  YmodeCANUPGInit(void);
#endif
