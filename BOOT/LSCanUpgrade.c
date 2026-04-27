#include "LSCanUpgrade.h"
#include "USER_BOOT_MISC.h"
#include "can.h"
#include "tim.h"

ElemType EnableCanBoot = 0;

/*升级字符串拼接*/
char *OutUPGStr(BootUPGStateTypedef BootUPGState,char Instr[])
{
    static char outstr[120];
    memset(outstr,'\0',sizeof(outstr));
    if(strlen(Instr)>100)
    {
        return NULL; 
    }
    switch (BootUPGState)
    {
        case UPG_Ver:
            sprintf(outstr,"%s,%s","$UPGRADEVER",Instr);
            return outstr;
//        break;
        case UPG_Timer:
            sprintf(outstr,"%s,%s","$UPGRADETIMER",Instr);
            return outstr;
//        break;
        case UPG_Menu:
            sprintf(outstr,"%s,%s","$UPGRADEMENU",Instr);
            return outstr;
//        break;
        default:
             return NULL; 
//        break;
    }
}


// 接收来自CAN总线的数据 
// 成功返回0  失败返回1
int ReceiveCanData(ElemType *Datatemp,ElemType DLC)
{
		int i = 0;
	  if(DLC>8||DLC<2)
		{
			return 1;
		}
		for( i = 1; i <DLC; i++)
		{
			 if(!EnQueue(&Datatemp[i]))
			 {
				 return 1;
			 }
		}
		return 0;
}
uint8 RecvCfgCANData[8];
void RecvCANData(CAN_RxHeaderTypeDef RxHeader,uint8_t RxData[])
{
	switch(RxHeader.ExtId)
	{
		case CANRxUPG_ID:
			ReceiveCanData(RxData,RxHeader.DLC);
			break;
		case CANCfg_ID:
			memcpy(RecvCfgCANData,RxData,RxHeader.DLC);
			if((RecvCfgCANData[1]&0x3F)==0x3F&&RecvCfgCANData[3]==0x05)//软复位指令
			{
				CANUPGParmInit.SystemResetFctn();
			}
			break;
		default:
			break;
	}	
}

// 按字节发送来自CAN总线的数据，每次发送一个字节
// 成功返回0 队空返回2
int CANDataToYmodem(ElemType *c)
{
	if(!QueueEmpty())
	{   
		DeQueue(c);
		if((char)*c=='\b')//CAN进来退格键,CAN升级使能,禁用串口升级
		{
			EnableCanBoot = true;
		}
		return 0;
	}else
	{
			return 2;
	}
}

CANUPGParmInitTypedef CANUPGParmInit;
// 失败返回1 成功返回0
static uint8_t CANUPGSend(uint32_t Device_ID,uint8_t *TX_msg,uint8_t TX_len)
{
	CANUPGParmInit.CANSendPtr(Device_ID,TX_msg,TX_len);
	return 0;
}
/*CAN发送数据，入口参数为要发送的数组指针，数据长度，返回0代表发送数据无异常，返回1代表传输异常*/
uint8_t CANUPG_Send_Msg(uint8_t* msg,int len)
{	
	uint8_t i=0;
//	uint8_t message[8];
	static uint8_t count = 0;
	int number_fram = 0;
	int number_fram_last = 0;
	int message_number = 0;
	if(len>0)
	number_fram = len/7;
	number_fram_last = len%7;
	while(number_fram--)
	{     
		uint8_t data[8];

		data[0] =  count++ ;
		for(i= 0;i<7;i++)
		{
			data[i+1]=msg[i+message_number*7];
		}
    if(CANUPGSend(CANTxUPG_ID,data,8))
		{
				return 1;
		}		
		message_number++;
		CANUPGParmInit.YmodeDelay_MS(1);
	}
	if(number_fram_last>0)
	{
		uint8_t data[8];
		data[0] =  count++ ;
		for(i=0;i<number_fram_last;i++)
		{
			data[i+1]=msg[i+message_number*7];
		}
    if(CANUPGSend(CANTxUPG_ID,data,number_fram_last+1))
		{
				return 1;
		}
		CANUPGParmInit.YmodeDelay_MS(1);
	}
  return 0;
}

/*启动倒计时*/
void StartCountDownFctn()
{
	SerialPutString(OutUPGStr(UPG_Timer,"倒计时:\r\n"));
	SerialPutString(OutUPGStr(UPG_Timer,"...3秒...\r\n"));
	CANUPGParmInit.YmodeDelay_MS(1000);//上电后延时3秒，等待按键
	SerialPutString(OutUPGStr(UPG_Timer,"...2秒...\r\n"));
	CANUPGParmInit.YmodeDelay_MS(1000);
	SerialPutString(OutUPGStr(UPG_Timer,"...1秒...\r\n"));
	CANUPGParmInit.YmodeDelay_MS(1000);
	SerialPutString(OutUPGStr(UPG_Timer,"...0秒...\r\n"));
}

/*发送菜单栏*/
void SendMenuInfoFctn()
{
	SerialPutString(OutUPGStr(UPG_Menu,"\r\n================== Main Menu ============================\r\n"));
	SerialPutString(OutUPGStr(UPG_Menu,"START\r\n"));
	SerialPutString(OutUPGStr(UPG_Menu,"1,Download,Controller New Firmware ------- 1\r\n"));
  SerialPutString(OutUPGStr(UPG_Menu,"2,Upload,Controller Firmware ------------- 2\r\n"));
  SerialPutString(OutUPGStr(UPG_Menu,"3,Execute,Controller New Firmware -------- 3\r\n"));
  SerialPutString(OutUPGStr(UPG_Menu,"==========================================================\r\n"));
	SerialPutString(OutUPGStr(UPG_Menu,"END\r\n"));
	CANUPGParmInit.YmodeDelay_MS(100);
}

//初始化
void  YmodeCANUPGInit(void)
{
    // CAN 初始化
//     user_can_init( );
    // 队列初始化    
    InitQueue();       
    // CAN扩展帧发送函数
    CANUPGParmInit.CANSendPtr=CAN2_SendData;
    //复位函数
    CANUPGParmInit.SystemResetFctn=HAL_NVIC_SystemReset;
    //延时毫秒函数
    CANUPGParmInit.YmodeDelay_MS = delay_ms;
    
}
