/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:
********************************************/

#include "USER_WIRE_LESS.h"
#include "USER_PRO.h"
#include "cmsis_os.h"
#include "USER_FREE_RT_OS.h"
#include "tim.h"
#include "usart.h"
#include "can.h"

user_wl_struct_t  user_wl_struct;
/***************************************************************************************************************************
* Function Name  :  
* Description    : 无线模块引脚初始化
* Input          :  
* Output         :  
* Return         :  
****************************************************************************************************************************/
uint8 user_wl_init(user_wl_struct_t *user_wl_struct_temp)
{
	//跳频模式
//	user_wl_cfg(HopFreq_MODE);

	user_wl_struct_temp->Pfun_can_tx = user_can_EXTID_send;
	user_wl_struct_temp->Pfun_uart_tx = user_send_bytes;
//	user_wl_struct_temp->Pfun_E34_WR = user_wl_pra_RD_WR;
	user_wl_struct_temp->Pfun_E34_mode_cfg =  user_wl_cfg;
 	user_wl_struct_temp->Pfun_delay_ms = delay_ms;
	user_wl_struct_temp->Pfun_key_pro = user_key_val_Pro ;
	user_wl_struct_temp->Pfun_E34_mode_cfg(HopFreq_MODE);//配置成跳频模式
	HAL_UART_Receive_IT(&huart2,&uart2RxBufftemp,1);	//使能串口2
	
	user_wl_struct_temp->E34_mode =  HopFreq_MODE;//默认是跳频模式
	
	return 0;
}



int user_wl_cfg(uint8 mode)
{
	//E34初始化
	//Mode0 = 0    Mode1 = 0 定频模式
	//Mode0 = 1    Mode1 = 0 跳频模式
	//Mode0 = 1    Mode1 = 1 配置模式
	switch( mode)
	{
		case FixFreq_MODE:
			
			HAL_GPIO_WritePin(GPIOD, E43_M0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, E43_M1_Pin, GPIO_PIN_RESET);

			break;
		case HopFreq_MODE:
			
			HAL_GPIO_WritePin(GPIOD, E43_M0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, E43_M1_Pin, GPIO_PIN_RESET);

			break;
		case Config_MODE:
			HAL_GPIO_WritePin(GPIOD, E43_M0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, E43_M1_Pin, GPIO_PIN_SET);

			break;
		default:
			break;
	}
	return 0;
}


/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:熄火，0x00400000；停车0x00001000；开始0x00000001；点火0x00000400
********************************************/

uint8 Zhu_less_data[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
void user_key_val_Pro(uint8* rx_data)
{
	uint8  key_val_temp5 = rx_data[8];
	uint8  key_val_temp6 = rx_data[9];
	uint8  key_val_temp7 = rx_data[10];
		uint32 id=0x0cfd0098;
 	{//直接转发给平板
		uint8 can_tx_buff[8]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
	  
		id= id|(((uint32)rx_data[1])<<8);
		if(id==0x0cfdd698)
		{
		  id = 0x0cfdda98;
		}
		memcpy(can_tx_buff,&rx_data[3],8);
//		user_can_EXTID_send(&hcan2,id,can_tx_buff, (uint32_t*)CAN_TX_MAILBOX0);//无线信息直接转发
	}
	
   Zhu_less_data[7] = 0;
	 if(id==0x0cfddA98)
	 {
			if(((key_val_temp5>>(6))&0x03)==0x01)//按键0 开始
			{
			   Zhu_less_data[7] = 10;  //70C控制的电机上升
			}
			
			if(((key_val_temp5>>(4))&0x03)==0x01)//按键1 加速  秧板下降
			{
			   Zhu_less_data[7] = 1;
			}
			
			if(((key_val_temp5>>(2))&0x03)==0x01)//按键2 抬升  秧框抬升
			{
			   Zhu_less_data[7] = 3;
			}
			
			if(((key_val_temp5>>(0))&0x03)==0x01)//按键3 左转  挡苗杆打开
			{
         Zhu_less_data[7] = 8;
			}
			
			if(((key_val_temp6>>(6))&0x03)==0x01)//按键4 前进 推苗杆前进
			{
			   Zhu_less_data[7] = 5;
			} 
			
			if(((key_val_temp6>>(4))&0x03)==0x01)//按键5 点火  秧箱抬升
			{
        if(user_state.manul_auto == 1)
        {
          user_state.less_yangxiang = 1;
          osSemaphoreRelease( myCountingSemMoter2Handle);
          osSemaphoreRelease( myCountingSemMoter3Handle);
          osSemaphoreRelease( myCountingSemMoter4Handle); 	
          osSemaphoreRelease( myCountingSemMoter5Handle);	  
        }
			}
			
			if(((key_val_temp6>>(2))&0x03)==0x01)//按键6 后退 推苗杆后退
			{
         Zhu_less_data[7] = 6;
			}
			
			if(((key_val_temp6>>(0))&0x03)==0x01)//按键7 减速  样板收回
			{
			   Zhu_less_data[7] = 2;
			}
      
			if(((key_val_temp7>>(6))&0x03)==0x01)//按键8 下降  秧框下降
			{
			   Zhu_less_data[7] = 4;
			}
			
			if(((key_val_temp7>>(4))&0x03)==0x01)//按键9 右转  挡苗杆收回
			{
          Zhu_less_data[7] = 7;
			}
			
			if(((key_val_temp7>>(2))&0x03)==0x01)//按键10 结束
			{
				  Zhu_less_data[7] = 9;
			}
			
			if(((key_val_temp7>>(0))&0x03)==0x01)//按键11 熄火  秧箱下降
			{
        if(user_state.manul_auto == 1)
        {
          user_state.less_yangxiang = 2;
          osSemaphoreRelease( myCountingSemMoter2Handle);
          osSemaphoreRelease( myCountingSemMoter3Handle);
          osSemaphoreRelease( myCountingSemMoter4Handle);
          osSemaphoreRelease( myCountingSemMoter5Handle);	
        }
			}
		}
		else if(id==0x0cfdd898)
		{
			if(((key_val_temp5>>(6))&0x03)==0x01)//按键12 急停
			{
		     user_state.manul_auto = 1;
				 user_state.stop_sta = 1;
			}
			else 
				user_state.stop_sta = 0;
			
			if(((key_val_temp5>>(4))&0x03)==0x01)//按键13 使能
			{
			   Zhu_less_data[7] = 11;  //70C控制的电机下降
			}
		}
    
}
/**************************************************************************/



/*************************************************
* Funcname      :
* Pra       		:

* Describtion   :   获取当前的ID，和ch;  
* 
************************************************/
int user_wl_pra_RD(user_wl_struct_t* user_wl_struct_temp)
{
	uint8 num =10;
	uint8 set_temp[3]={0xc1,0xc1,0xc1};	
	user_wl_struct_temp->Pfun_E34_mode_cfg(Config_MODE);
	user_wl_struct_temp->E34_mode = Config_MODE;
	user_wl_struct_temp->uart_buff_rx_empt_flag =0;
	user_wl_struct_temp->Pfun_delay_ms(300);

	while(num--)
	{
		user_wl_struct_temp->Pfun_uart_tx(&huart2,set_temp,3);	
		user_wl_struct_temp->Pfun_delay_ms(400);
		 osDelay(10);
		if(user_wl_struct_temp->uart_buff_rx_empt_flag==1)
		{
			user_wl_struct_temp->current_id = user_wl_struct_temp->uart_buff_rx[1]&0x0f;
			user_wl_struct_temp->current_id = (user_wl_struct_temp->id <<8)|user_wl_struct_temp->uart_buff_rx[2];
			user_wl_struct_temp->current_ch = user_wl_struct_temp->uart_buff_rx[4];
			user_wl_struct_temp->uart_buff_rx_empt_flag=0;
			user_wl_struct_temp->Pfun_E34_mode_cfg(HopFreq_MODE );
			user_wl_struct_temp->E34_mode = HopFreq_MODE ;
			return 0;
		}
	}
	user_wl_struct_temp->Pfun_E34_mode_cfg(HopFreq_MODE );
	user_wl_struct_temp->E34_mode =HopFreq_MODE;
	return 1;
}



/*************************************************
* Funcname      :
* Pra       		:

* Describtion   :  写入的ID，和ch;  
* 
************************************************/
int user_wl_pra_WR(user_wl_struct_t* user_wl_struct_temp)
{
	uint8 num =10;
	uint8 set_temp[6]={0xc0,0xf0,0x00,0x18,0x00,0x40};	
	
	set_temp[1]= user_wl_struct_temp->id>>8|0xf0;
	set_temp[2]= user_wl_struct_temp->id&0xff;
	set_temp[4]= user_wl_struct_temp->ch;//0-11,共12个通道
	
	user_wl_struct_temp->Pfun_E34_mode_cfg(Config_MODE);
	user_wl_struct_temp->E34_mode = Config_MODE;
	user_wl_struct_temp->uart_buff_rx_empt_flag =0;
	user_wl_struct_temp->Pfun_delay_ms(300);

	while(num--)//最多写10次
	{
		user_wl_struct_temp->Pfun_uart_tx(&huart2,set_temp,6);	
		user_wl_struct_temp->Pfun_delay_ms(400);
		if(user_wl_struct_temp->uart_buff_rx_empt_flag==1)
		{
			user_wl_struct_temp->uart_buff_rx_empt_flag =0;
			if(memcmp(user_wl_struct_temp->uart_buff_rx,set_temp,6)==0)//成功写入
			{
				user_wl_struct_temp->id = user_wl_struct_temp->uart_buff_rx[1]&0x0f;
				user_wl_struct_temp->id = (user_wl_struct_temp->id <<8)|user_wl_struct_temp->uart_buff_rx[2];
				user_wl_struct_temp->ch = user_wl_struct_temp->uart_buff_rx[4];
				user_wl_struct_temp->uart_buff_rx_empt_flag=0;
				
				user_wl_struct_temp->Pfun_E34_mode_cfg(HopFreq_MODE );
				user_wl_struct_temp->E34_mode =HopFreq_MODE;
				
				user_wl_struct_temp->current_id = user_wl_struct_temp->id;
				user_wl_struct_temp->current_ch = user_wl_struct_temp->ch;
				return 0;	
			}
		}
	}
	user_wl_struct_temp->Pfun_E34_mode_cfg(HopFreq_MODE );
	user_wl_struct_temp->E34_mode =HopFreq_MODE;
	user_wl_struct_temp->current_id = user_wl_struct_temp->id;
	user_wl_struct_temp->current_ch = user_wl_struct_temp->ch;
	return 1;
}
/*************************************************
* Funcname      :
* Pra       		:

* Describtion   :   can接口获取数据
* 
************************************************/
uint8 user_wl_pra_from_can(user_wl_struct_t* user_wl_struct_temp,uint8* buff_can_rx)
{
	
	if((( buff_can_rx[1]>>4)&0x03)==0x01 )//设置模式,可以打开配置，也可以关闭配置
	{
			user_wl_struct_temp->study_cmd_from = 0x01;//设置指令来自can
			user_wl_struct_temp->id = buff_can_rx[3];
			user_wl_struct_temp->id = (user_wl_struct_temp->id<<8)|buff_can_rx[2];
		  user_wl_struct_temp->ch =  buff_can_rx[4];
			user_wl_struct_temp->study_on_off = buff_can_rx[5]&0x03;//配对开启或者关闭，01开启；00关闭
			
			if((buff_can_rx[5]&0x03)==0x01)//开启配对模式
			{
				user_wl_struct_temp->mode = CFG_MODE;
				
			}
			else if((buff_can_rx[5]&0x03)==0x00)//关闭配对模式
			{
			
				user_wl_struct_temp->mode = NML_MODE;
			}
	}
	else if((( buff_can_rx[1]>>4)&0x03)==0x00 )//查询模式
	{
		user_wl_struct_temp->mode = QRY_MODE;
	}


	return 0;
}

/*************************************************
* Funcname      :
* Pra       		:
* Describtion   :   串口获取数据
* 
************************************************/
uint8 user_wl_pra_from_uart(user_wl_struct_t* user_wl_struct_temp,uint8* buff_uart_rx,uint8  len)
{
	uint8 i;
	for(i=0;i<len;i++)
	{    
		user_wl_struct_temp->uart_buff_rx[i]=buff_uart_rx[i];
	}
	user_wl_struct_temp->uart_buff_rx_empt_flag = 1;
	return 0;
}

/*************************************************
* Funcname      :
* Pra       		:
* Describtion   :   有按键的 输出按键值，返回值可以是无线收发所处的状态，配对状态或者是按键处理状态，
											可以信号量触发，也可以标志触发，放在无线接收任务中
* 
************************************************/
uint8 user_wl_pro(user_wl_struct_t* user_wl_struct_temp)
{
	if( user_wl_struct_temp->mode==QRY_MODE)//查询模式
	{
	
		for(; ; )
		{
				uint8 set_temp[3]={0xc1,0xc1,0xc1};	
				user_wl_struct_temp->Pfun_E34_mode_cfg(Config_MODE);//进入配置模式 
				user_wl_struct_temp->E34_mode = Config_MODE;
//				user_wl_struct_temp->Pfun_delay_ms(10);
				osDelay(10);//
				user_wl_struct_temp->Pfun_uart_tx(&huart2,set_temp,3);
				user_wl_struct_temp->uart_buff_rx_empt_flag = 0;

				user_wl_struct_temp->Pfun_delay_ms(300);
				if(user_wl_struct_temp->uart_buff_rx_empt_flag==1)//为空则等待
				{
					break;
				}
				
				//正配置的时候 收到了下发不配置了
				if(user_wl_struct.mode==NML_MODE)
				{
					return 0;
				}
				
				osDelay(5);//
		}
		user_wl_struct_temp->current_id = user_wl_struct_temp->uart_buff_rx[1]&0x0f;
		user_wl_struct_temp->current_id =user_wl_struct_temp->current_id <<8|user_wl_struct_temp->uart_buff_rx[2];
		user_wl_struct_temp->current_ch = user_wl_struct_temp->uart_buff_rx[4]&0x0f;
		user_wl_struct_temp->uart_buff_rx_empt_flag = 0;
		
		{
				uint8 wl_can_tx[8]={0x01,0xf0,0xff,0xff,0xff,0xff,0xff,0xff};
				wl_can_tx[2]= user_wl_struct_temp->current_id&0xff;
				wl_can_tx[3]= (user_wl_struct_temp->current_id>>8)&0x0f;
				wl_can_tx[4]= user_wl_struct_temp->current_ch;
				wl_can_tx[5]= user_wl_struct_temp->mode;	
				user_wl_struct_temp->Pfun_can_tx(&hcan2,0x0CFF5490,wl_can_tx, (uint32_t*)CAN_TX_MAILBOX0);
		}
		user_wl_struct_temp->mode = NML_MODE;//查询结束 变为正常通讯模式
	}
	else if( user_wl_struct_temp->mode==CFG_MODE)//配置模式 在该处完成所有配置操作
	{
		uint8 E34_factory_pra[6]={0xC0,0xF0,0,0x18,0,0x40};//默认发15次，地址为0，波特率9600，一共6字节
		uint8 E34_new_pra1[6]={0xC0,0xF0,0x00,0x18,0x00,0x40};

		uint8 E34_new_pra[12]   ={0xfd,0xd6,0x98,0xc0,0xf0,0x00,0x18,0x00,0x40,0x00,0x00,0x00};//默认发15次，地址为0，波特率9600，一共6字节
		uint8 E34_test_pdata[12]={0xfd,0xd6,0x98,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//默认发15次，地址为0，波特率9600，一共6字节
		E34_new_pra[4] = (user_wl_struct_temp-> id>>8)|0xf0;
		E34_new_pra[5] = user_wl_struct_temp-> id &0xff;
		E34_new_pra[7] = user_wl_struct_temp->ch;
		
		E34_new_pra1[1] =E34_new_pra1[1]|(user_wl_struct_temp->id>>8);
		E34_new_pra1[2] =user_wl_struct_temp-> id&0xff;		
		E34_new_pra1[4] =user_wl_struct_temp-> ch;	

		
		for(; ; )//恢复出厂参数
		{	
			user_wl_struct_temp->Pfun_E34_mode_cfg(Config_MODE);//进入配置模式 
			user_wl_struct_temp->E34_mode = Config_MODE;
//			user_wl_struct_temp->Pfun_delay_ms(10);
			osDelay(10);//
			user_wl_struct_temp->Pfun_uart_tx(&huart2,E34_factory_pra,sizeof(E34_factory_pra));
			user_wl_struct_temp->uart_buff_rx_empt_flag =0;
			user_wl_struct_temp->Pfun_delay_ms(300);
 
			if(user_wl_struct_temp->uart_buff_rx_empt_flag==1)//为空则等待
			{
				user_wl_struct_temp->uart_buff_rx_empt_flag =0;
				if(memcmp(E34_factory_pra,user_wl_struct_temp->uart_buff_rx,sizeof(E34_factory_pra))==0)//返回值是对的
				{
					break;
				}
  		}
				//正配置的时候 收到了下发不配置了
					if(user_wl_struct.mode==NML_MODE)
				{
					return 0;
				}
			
			osDelay(5);//
			
		}
		
		
		for(; ; )//出厂参数下，发送新参数并接收回传
		{
			user_wl_struct_temp->Pfun_E34_mode_cfg(HopFreq_MODE);//进入跳频模式 
			user_wl_struct_temp->E34_mode = HopFreq_MODE;
//			user_wl_struct_temp->Pfun_delay_ms(10);	
				osDelay(10);//
			E34_new_pra[11] = user_xor_check(E34_new_pra,sizeof(E34_new_pra)-1);
			user_wl_struct_temp->Pfun_uart_tx(&huart2,E34_new_pra,sizeof(E34_new_pra));
			user_wl_struct_temp->uart_buff_rx_empt_flag = 0;
			user_wl_struct_temp->Pfun_delay_ms(300);

			if(user_wl_struct_temp->uart_buff_rx_empt_flag==1)//为空则等待
			{
				user_wl_struct_temp->uart_buff_rx_empt_flag =0;
				if(memcmp(E34_new_pra,user_wl_struct_temp->uart_buff_rx,sizeof(E34_new_pra))==0)//返回值是对的
				{
					break;
				}
  		}
			
							//正配置的时候 收到了下发不配置了
				if(user_wl_struct.mode==NML_MODE)
				{
					return 0;
				}
			osDelay(5);//
		}
		
		for(; ; )//此循环死掉了，出厂参数下，发送字头加全0并接收回传,目的告诉遥控器，已经收到遥控器的回传，下一步升级参数
		{
//			user_wl_struct_temp->Pfun_E34_mode_cfg(HopFreq_MODE);//进入跳频模式 
			E34_test_pdata[11] = user_xor_check( E34_test_pdata,sizeof(E34_test_pdata)-1);
			user_wl_struct_temp->Pfun_uart_tx(&huart2,E34_test_pdata,sizeof(E34_test_pdata));
			user_wl_struct_temp->uart_buff_rx_empt_flag =0;
//			user_wl_struct_temp->Pfun_delay_ms(300);
			osDelay(300);//
			if(user_wl_struct_temp->uart_buff_rx_empt_flag==1)//为空则等待
			{
				user_wl_struct_temp->uart_buff_rx_empt_flag =0;
				if(memcmp(E34_test_pdata,user_wl_struct_temp->uart_buff_rx,sizeof(E34_test_pdata))==0)//返回值是对的
				{
					break;
				}
  		}
			
							//正配置的时候 收到了下发不配置了
				if(user_wl_struct.mode==NML_MODE)
				{
					return 0;
				}
			osDelay(5);//
		}
		
		for(; ; )//生效新参数，接收遥控器字头加全0，并回传
		{
			user_wl_struct_temp->Pfun_E34_mode_cfg(Config_MODE);//进入跳频模式 
			user_wl_struct_temp->E34_mode = Config_MODE;
//			user_wl_struct_temp->Pfun_delay_ms(10);			 
			osDelay(10);//
			user_wl_struct_temp->Pfun_uart_tx(&huart2,E34_new_pra1,sizeof(E34_new_pra1));
			user_wl_struct_temp->uart_buff_rx_empt_flag =0;
//			user_wl_struct_temp->Pfun_delay_ms(300);
			osDelay(300);//
			if(user_wl_struct_temp->uart_buff_rx_empt_flag==1)//为空则等待
			{
				user_wl_struct_temp->uart_buff_rx_empt_flag =0;
				if(memcmp(E34_new_pra1,user_wl_struct_temp->uart_buff_rx,sizeof(E34_new_pra1))==0)//返回值是对的
				{

						break;
				}
  		}
			
				//正配置的时候 收到了下发不配置了
				if(user_wl_struct.mode==NML_MODE)
				{
					return 0;
				}
			
			osDelay(5);//
		}
			
		user_wl_struct_temp->current_id = user_wl_struct_temp->id;
		user_wl_struct_temp->current_ch = user_wl_struct_temp->ch;
		user_wl_struct_temp->mode = NML_MODE;
		user_wl_struct_temp->Pfun_E34_mode_cfg(HopFreq_MODE);//进入跳频模式 
		user_wl_struct_temp->E34_mode = HopFreq_MODE;
		
		user_moter_pra.remot_chn = user_wl_struct_temp->current_ch;
		user_moter_pra.remot_id = user_wl_struct_temp->current_id;
		
		osMessageQueuePut(myQueueUart7RecHandle, "ok\r\n", 0, NULL);//在串口中保存数据
		portYIELD( );//如果需要的话进行一次任务切换
//			user_wl_struct_temp->Pfun_delay_ms(10);
		osDelay(10);//
	}
	else if( user_wl_struct_temp->mode==NML_MODE)//正常通讯模式
	{	
		if( user_wl_struct_temp->E34_mode==HopFreq_MODE )//还必须处在跳频模式下
		{
				if(user_wl_struct_temp->uart_buff_rx_empt_flag==1)//为空则等待	
				{
					user_wl_struct_temp->uart_buff_rx_empt_flag=0;
//					osDelay(100);
					user_wl_struct_temp->Pfun_uart_tx(&huart2,user_wl_struct_temp->uart_buff_rx,12);//收到啥回传就行
					HAL_UART_Receive_IT(&huart2,&uart2RxBufftemp,1);
					
					if(  (user_wl_struct_temp->uart_buff_rx[8]!=0x00) ||		//有按键值，不是心跳包，就处理
							 (user_wl_struct_temp->uart_buff_rx[9]!=0x00) ||
							 (user_wl_struct_temp->uart_buff_rx[10]!=0x00) 
					  )//
					{
						user_wl_struct_temp->Pfun_key_pro(user_wl_struct_temp->uart_buff_rx);
					}
 					
					memset(user_wl_struct_temp->uart_buff_rx,0,12);
				}		
		}
		else
		{
		
		
		}

	}
	return 0;
}

/*************************************************
* Funcname      :
* Pra       		:  
										异或校验 
************************************************/
uint8 user_xor_check(uint8 * buff,uint8 len)
{
	uint8 i; 
	uint8 val=0;
	for(i=0;i<len;i++)
	{
		val = val^buff[i];
	}

  return val ;
}
