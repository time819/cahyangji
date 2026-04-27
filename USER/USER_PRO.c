/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:
********************************************/
#include "USER_PRO.h"
#include "dma.h"
#include "cmsis_os.h"
#include "USER_FREE_RT_OS.h"
#include "USER_FLASH.h"
#include "tim.h"
#include "gpio.h"
#include "stdio.h"	
#include "string.h"
#include "USER_SET.h"
#include "USER_RADAR.h"
#include "USER_CAN_PAD.h"
#include "usart.h"
#include "can.h"
#include "USER_MISC.h"
#include "USER_MOTER.h"
moter_pra_struct_t user_moter_pra;
moter_pra_struct_t  user_flash_moter_pra ;
user_state_t user_state;
user_dec_state_t user_dec_state;


//中位阈值边缘绝对值，两个电机，三个手柄，0行走电机；1秧台电机；2行走手柄；3秧台手柄；4转向手柄
mid_thd_t  user_mid_thd[AN_MOT_MAX_NUM]={

{0,0},

};


j1939_msg_t j1939_msg_rev_can1;
j1939_msg_t j1939_msg_rev_can2;

uint8 suidong_rec = 0;//串口调试用，当前样板的随动状态
int speed_show = 0;

uint8 yangban_dir = 0;
uint8 yangtai_dir = 0;

uint8 yangban_wz = 0;
uint8 yangtai_wz = 0;


user_moter_t user_moter5;
user_moter_t user_moter1;
user_moter_t user_moter2;
user_moter_t user_moter3;
user_moter_t user_moter4;

volatile uint32 YangTai_rec = 0;  //齿轮转动计数
uint8 YangTai_speed = 10; //秧台齿轮转速，hh默认是10，大概17或者18，此变量用于设置秧板的基本速度，以及秧台是否停止

uint8  speed_text1 = 0;
uint8  rad_text= 0;
uint8  moter_id = 3;
  





uint8 Zhu_cont_data[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

volatile uint8 user_key_sta=0;//默认熄火状态，以后会读发动机.1,正在点火；2，正常工作，

volatile uint16 user_speed =0x00;
//user_back_pend_ctr_t user_back_pend_ctr;
//user_back_pend_ctr_t user_back_pend;

float user_harvester_ratio;
user_pro_func_t user_can2_pro_func[FUNC_CAN2_MAX_NUM] ={
	
{MANUL_AUTOM_STATE_PGN, user_manul_autom},
{0x9006			,high_user_get},// hh  秧台状态获取
{BK_CFG_PGN			,user_bk_cfg},
{BK_UPDATE_MODE_PGN,user_bk_update_mode},
{HEART_BEAT_PGN, user_heart_beat},

};

user_pro_func_t user_can1_pro_func[FUNC_CAN1_MAX_NUM] ={

{0x9001, rice_lack1},
{0x9002, rice_lack2},
{0x9003, rice_lack3},
{0x9004, rice_lack4},//新增秧框

{0x9090, YangBang_fuwei},  
  
};

/*************************************************
* Funcname      :
* Pra       		:user_bk_cfg
* Describtion   :  
************************************************/

uint8 user_bk_cfg(j1939_msg_t * RxMessage)
{
  uint8 wr_rd_flag = 0;
	wr_rd_flag = RxMessage->Array[5]>>6;
	switch (wr_rd_flag)
	{
	   case 0:    //读取
				if((RxMessage->Array[4]==0x90)&&(RxMessage->Array[5]==0x02))//02读取pn lsb
				{
					 uint8 pn_lsb_tx[8]={0};
					 pn_lsb_tx[0]=0x26;
					 pn_lsb_tx[1]=0xc2;
					 pn_lsb_tx[2]= user_basic_infor.pn_can[0];
					 pn_lsb_tx[3]= user_basic_infor.pn_can[1];	
					 pn_lsb_tx[4]= user_basic_infor.pn_can[2];
					 pn_lsb_tx[5]= user_basic_infor.pn_can[3];		
					 pn_lsb_tx[6]= user_basic_infor.pn_can[4];	
					 pn_lsb_tx[7]= user_basic_infor.pn_can[5];	
           					 
					 user_can_EXTID_send(&hcan2,0x18fff290,pn_lsb_tx, (uint32_t*)CAN_TX_MAILBOX0);
				}
				else if((RxMessage->Array[4]==0x90)&&(RxMessage->Array[5]==0x03))//03读取pn msb
				{
					 uint8 pn_msb_tx[8]={0};
					 pn_msb_tx[0]=0x26;
					 pn_msb_tx[1]=0xc3;
					 pn_msb_tx[2]= user_basic_infor.pn_can[6];
					 pn_msb_tx[3]= user_basic_infor.pn_can[7];	
					 pn_msb_tx[4]= 0xff;	
					 pn_msb_tx[5]= 0xff;		
					 pn_msb_tx[6]= 0xff;		
					 pn_msb_tx[7]= 0xff;	
					 
					 user_can_EXTID_send(&hcan2,0x18fff290,pn_msb_tx, (uint32_t*)CAN_TX_MAILBOX0);
				}
				else  if((RxMessage->Array[4]==0x90)&&(RxMessage->Array[5]==0x04))//04读取SN号
				{
					uint8 sn_tx[8]={0};
					sn_tx[0]=0x26;
					sn_tx[1]=0xc4;
					sn_tx[2]= user_basic_infor.sn_can[0];
					sn_tx[3]= user_basic_infor.sn_can[1];	
					sn_tx[4]= user_basic_infor.sn_can[2];
					sn_tx[5]= user_basic_infor.sn_can[3];		
					sn_tx[6]= user_basic_infor.sn_can[4];		
					sn_tx[7]= 0xff;	
				 
					user_can_EXTID_send(&hcan2,0x18fff290,sn_tx, (uint32_t*)CAN_TX_MAILBOX0);
				}
				else if((RxMessage->Array[4]==0x90)&&(RxMessage->Array[5]==0x07))//07读取固件号
				{
					 uint8 ver_tx[8]={0};
					 ver_tx[0]=0x26;
					 ver_tx[1]=0xc7;
					 ver_tx[2]= user_basic_infor.app_ver_can[0];
					 ver_tx[3]= user_basic_infor.app_ver_can[1];	
					 ver_tx[4]= user_basic_infor.app_ver_can[2];
					 ver_tx[5]= user_basic_infor.app_ver_can[3];		
					 ver_tx[6]= 0xff;		
					 ver_tx[7]= 0xff;
          					 
					 user_can_EXTID_send(&hcan2,0x18fff290,ver_tx, (uint32_t*)CAN_TX_MAILBOX0);
				}	
					else if((RxMessage->Array[4]==0x90)&&(RxMessage->Array[5]==0x09))//09读取boot固件号
				{
					 uint8 ver_tx[8]={0};
					 ver_tx[0]=0x26;
					 ver_tx[1]=0xc9;
					 ver_tx[2]= user_basic_infor.boot_ver_can[0];
					 ver_tx[3]= user_basic_infor.boot_ver_can[1];	
					 ver_tx[4]= user_basic_infor.boot_ver_can[2];
					 ver_tx[5]= user_basic_infor.boot_ver_can[3];		
					 ver_tx[6]= 0xff;	
           ver_tx[7]= 0xff;		
           					 
					 user_can_EXTID_send(&hcan2,0x18fff290,ver_tx, (uint32_t*)CAN_TX_MAILBOX0);
				}			 
					 
		 break;
		 
		 case 1:    //设置指令
			 	if((RxMessage->Array[4]==0x90)&&(RxMessage->Array[5]==0x42))//42设置pn lsb
				{
				  user_basic_infor.pn_can[0]=RxMessage->Array[6];//PN码的最低位
				  user_basic_infor.pn_can[1]=RxMessage->Array[7];
				  user_basic_infor.pn_can[2]=RxMessage->Array[8];	
				  user_basic_infor.pn_can[3]=RxMessage->Array[9];
				  user_basic_infor.pn_can[4]=RxMessage->Array[10];	
				  user_basic_infor.pn_can[5]=RxMessage->Array[11];
				}
				else if((RxMessage->Array[4]==0x90)&&(RxMessage->Array[5]==0x43))//43设置pn msb
				{
				  user_basic_infor.pn_can[6]=RxMessage->Array[6];					
				  user_basic_infor.pn_can[7]=RxMessage->Array[7]|0xf0;//高4为不存数据
					
					{
							sprintf(user_basic_infor.pn,"%s%1x%02x%02x%02x%02x%02x%02x%2x","PNINFO,",
							user_basic_infor.pn_can[7]&0x0f,user_basic_infor.pn_can[6],user_basic_infor.pn_can[5],
						  user_basic_infor.pn_can[4],user_basic_infor.pn_can[3],user_basic_infor.pn_can[2],
						  user_basic_infor.pn_can[1], user_basic_infor.pn_can[0] ); 
              strcpy(user_sn_pn.pn,user_basic_infor.pn);
							user_write_Flash_buffer_1(SN_PN_INFOR_ADDR,(uint8 *)(&user_sn_pn), sizeof(user_sn_pn),FLASH_SECTOR_2);
							user_send_str(&huart7, "写入PN码\r\n"); 						
					}
				}
				else  if((RxMessage->Array[4]==0x90)&&(RxMessage->Array[5]==0x44))//44设置SN号
				{
					user_basic_infor.sn_can[0]=RxMessage->Array[6] ;
					user_basic_infor.sn_can[1]=RxMessage->Array[7] ;
					user_basic_infor.sn_can[2]=RxMessage->Array[8] ;
					user_basic_infor.sn_can[3]=RxMessage->Array[9] ;
					user_basic_infor.sn_can[4]=RxMessage->Array[10];

					{
 
						sprintf(user_basic_infor.sn,"%s%02x%02x%02x%02x%02x","SNINFO,",
						user_basic_infor.sn_can[4],user_basic_infor.sn_can[3],user_basic_infor.sn_can[2],
						user_basic_infor.sn_can[1],user_basic_infor.sn_can[0]);  	
					  
				    strcpy(user_sn_pn.sn,user_basic_infor.sn);
						
            user_write_Flash_buffer_1(SN_PN_INFOR_ADDR,(uint8 *)(&user_sn_pn), sizeof(user_sn_pn),FLASH_SECTOR_2);
		        user_send_str(&huart7, "写入SN码\r\n"); 
					}
				}
				else if((RxMessage->Array[4] ==0x90)&&(RxMessage->Array[5]==0x48)&&(RxMessage->Array[6]==0x05))//软复位指令
				{
					 uint8 cfg_tx[8]={0x26,0xc8,0x05,0xff,0xff,0xff,0xff,0xff};
					 user_can_EXTID_send(&hcan2,0x18fff290,cfg_tx, (uint32_t*)CAN_TX_MAILBOX0	);
           osDelay(100);					 
					 User_Soft_Reset( );
				}

			break;
		 
		 default:    // 
	  break;
	}

	return 0;
}





/*************************************************
* Funcname      :
* Pra       		:user_bk_cfg ，sn号、版本号、PN号
* Describtion   :  
************************************************/
uint8 user_bk_update_mode(j1939_msg_t * RxMessage)
{
//	if((RxMessage->Array[4] ==0x90)&&(RxMessage->Array[7]==0x05))//软复位指令
//	{
//		user_send_str(&huart7, "请5秒内长按退格键，直到升级信息提示\r\n"); 
//		CANUPG_Send_Msg_1(0x18fff390,&RxMessage->Array[5],3);//组包发数据
		 uint8 cfg_tx[8]={0x00, 0xFF, 0xFF, 0xFF, 0x26};
//		 cfg_tx[0]=0x26;
//		 cfg_tx[1]=0xc8;
//		 cfg_tx[2]= user_basic_infor.ver[0];
//		 cfg_tx[3]= user_basic_infor.ver[1];	
//		 cfg_tx[4]= user_basic_infor.ver[2];
		 cfg_tx[5]= RxMessage->Array[9];			
		 cfg_tx[6]= RxMessage->Array[10];	
		 cfg_tx[7]= RxMessage->Array[11];				 
  	 user_can_EXTID_send(&hcan2,0x18e82690,cfg_tx, (uint32_t*)CAN_TX_MAILBOX0	);	
//		
//		 User_Soft_Reset( );
//	}
		return 0;
}

/*************************************************
* Funcname      :
* Pra       		:
* Describtion   : 心跳包
************************************************/
uint8 user_heart_beat(j1939_msg_t * RxMessage)
{
	 uint8 pra_num  ;
//  static uint8 pra_num_rec =0;
	static uint8 pra_num_rec ;
	pra_num = RxMessage->Array[4];
	if((pra_num <= 251)
		&&((pra_num_rec+1)%250== pra_num%250 )
	  )
	{
	 user_state.pad_heart = 0x01;//收到心跳	
	}
//	else//这里不宜置0
//	{
//  	user_state.pad_heart = 0x00;//未收到心跳	，或者其他故障
//	}
 
	pra_num_rec = pra_num;
	
	if(pra_num_rec ==250)
	{
	 pra_num_rec = 249;
	}
//	user_send_str(&huart7, "xintiao");
	user_state.pad_heart = 0x01;//收到心跳	
	return 0;
}



/*************************************************
* Funcname      :
* Pra       		:
* Describtion   :  
************************************************/
uint8 user_manul_autom(j1939_msg_t * RxMessage)
{
	static uint32  manul_auto_record = 0x01;

	if((RxMessage->Array[4]&0x07)==0x01)//手动
	{
	  user_state.manul_auto = 0x01;
    user_state.YangXiang_high = 1;
    osSemaphoreRelease( myCountingSemMoter2Handle);
    osSemaphoreRelease( myCountingSemMoter3Handle);
    osSemaphoreRelease( myCountingSemMoter4Handle);
    osSemaphoreRelease( myCountingSemMoter5Handle);   //秧箱升起来			
	} 
	else if((RxMessage->Array[4]&0x07)==0x02)//电动
	{
		user_state.manul_auto = 0x02;
	}
	manul_auto_record= user_state.manul_auto;	
	return 0;
}



/*************************************************
* Funcname      :
* Pra       		:
* Describtion   :  
************************************************/
void user_state_init(user_state_t *user_state_temp )
{
	user_state_temp->test_opr_mode=0x00;//默认不是测试模式
	user_state_temp->study_mode =0x00;//默认不是遥控器学习模式
	user_state.manul_auto = 0x01;//初始默认是人工操作
	user_state.pad_heart =1;//开始默认已经收到了心跳数据
}

/*************************************************
* Funcname      :
* Pra       		:
* Describtion   :  安全限位
************************************************/
void user_safe_ctr(void)
{
  ;
}
/*************************************************
* Funcname      :
* Pra       		:
* Describtion   :  行走变速杆一段时间内不动作 就熄火
************************************************/
uint8 user_mot1_state( volatile int  *timer_10ms)
{
  int static value[5]={0};
  uint8  num =0;
	int static timer_10ms_record; 
	if(timer_10ms_record != (*timer_10ms))
	{
	if(((*timer_10ms%400)==0)&&(user_moter1.no_change_err==0))//每400毫秒，采样
	{
		value[4]= value[3];
		value[3]= value[2];
		value[2]= value[1];
		value[1]= value[0];
		value[0]= AD_CH_value[0];
	}
		if(value[4]!=0x00)//程序已经运行开了，不是刚开始运行
		{
			int i;
			for(i=0;i<4;i++)
			{
				if(((value[i]-value[4])<10)&&((value[i]-value[4])>-10))//和标准相比较,没有变化，熄火啊
				{
					num++;
				}
			}
			
			if(num==4)//一次都没有动
			{
				user_moter1.no_change_err =1;//标记 准备熄火
				value[0]= 0;
				value[1]= 0;
				value[2]= 0;
				value[3]= 0;
				value[4]= 0;
//						{
//							char * ptr="ka2";
//							HAL_UART_Transmit(&huart7,(uint8*)ptr,strlen(ptr),10);
//							while(__HAL_UART_GET_FLAG(&huart7,UART_FLAG_TC)!=SET)
//							{
//								osDelay(2);
//							}	
//					}
			}
		}

		timer_10ms_record = *timer_10ms;//记录时间
	}
	return user_moter1.no_change_err;//返回1，要退出，出错了
}


/*************************************************
* Funcname      :
* Pra       		:
* Describtion   :  行走变速杆一段时间内不动作 就熄火
************************************************/
void user_mot1_no_change_err(void)
{
	if(user_moter1.no_change_err==1)//
	{
		user_moter1.no_change_err =0;
		user_key_sta = 0;//熄火
		user_moter_power_ctr(0);//电机驱动芯片断电，复位，避免一直烧
  	osSemaphoreRelease( myCountingSemEngineHandle);//释放一个信号量 
		
	}
}
/*************************************************
* Funcname      :
* Pra       		:
* Describtion   :  秧台手柄限位开关液压锁,不控制这个微动开关，就不会
************************************************/
void user_pend_switch(void)
{
				//防止越界
			if(user_dec_state.dec_fix_state[1]==0x00)//1小
			{
				if(AD_CH_value[1]>=(user_moter_pra.AN_Val[1][2]-30))//中位或者抬升
				{
//						HAL_GPIO_WritePin(GPIOG,DO10_Pin, GPIO_PIN_RESET);//液压锁,上升或者中位开关断开	
							HAL_GPIO_WritePin(GPIOE, DO6_Pin, GPIO_PIN_RESET);
				}
				else 	if(AD_CH_value[1]<(user_moter_pra.AN_Val[1][2]-30))//插值或者下降
				{
//						HAL_GPIO_WritePin(GPIOG,DO10_Pin, GPIO_PIN_SET);//液压锁,上升完成 就把液压锁打开	
							HAL_GPIO_WritePin(GPIOE, DO6_Pin, GPIO_PIN_SET);
				}
			}
			else if(user_dec_state.dec_fix_state[1]==0x01)//1大
			{
				if(AD_CH_value[1]<=(user_moter_pra.AN_Val[1][2]-30))//中位或者抬升
				{
//						HAL_GPIO_WritePin(GPIOG,DO10_Pin, GPIO_PIN_RESET);////液压锁,上升或者中位开关断开	
							HAL_GPIO_WritePin(GPIOE, DO6_Pin, GPIO_PIN_RESET);
				}
				else 	if(AD_CH_value[1]>(user_moter_pra.AN_Val[1][2]-30))//插值或者下降
				{
//						HAL_GPIO_WritePin(GPIOG,DO10_Pin, GPIO_PIN_SET);//液压锁,上升完成 就把液压锁打开
							HAL_GPIO_WritePin(GPIOE, DO6_Pin, GPIO_PIN_SET);
				}
			}


}
/*************************************************
* Funcname      :
* Pra       		:
* Describtion   :  电子手柄转换采样
************************************************/
void user_elec_stic(void)
{
	;
}

/************************************************
* Funcname      :
* Pra       		:
* Describtion   :  收割机离合人工状态下控制
************************************************/
void user_harvest_clutch_manul_ctr(void )
{

  return;
}


/*******************************************************************************
* Function Name  :  
* Description    : 用户变量之类的数据初始化
* Input          :
* Output         :  
* Return         : 
**************************************/
void user_data_init(void)
{
		//电机安装方式设置
		user_moter1.reverse_direction =0x00;
		user_moter2.reverse_direction =0x01;//割台离合反着装
		user_moter3.reverse_direction =0x00;
		user_moter4.reverse_direction =0x01;//脱谷离合反着装
	
		user_state_init(&user_state );
	  User_sensor_Pra_Init();
}

/*******************************************************************************
* Function Name  :  
* Description    : 确认参数是不是设置了
* Input          :
* Output         :  
* Return         :  电机/角度传感器安装状态，设置时，位置1最小时为0；
*位置1最大时为1；位置1和位置2相等为2；位置1和位置2都是0，为3
**************************************/
void user_data_check(void)
{
	uint8 i=0;
	uint8 j=0;
	
	for(i=0;i<AN_MOT_MAX_NUM;i++)
	{
			if((user_moter_pra.AN_Val[i][0]==0x00)&&(user_moter_pra.AN_Val[i][1]==0x00))//电机2没有设置参数
			{
				 user_dec_state.dec_fix_state[i] =3;//没有设置
			}
			else if(user_moter_pra.AN_Val[i][0] ==user_moter_pra.AN_Val[i][1] )
			{
				 user_dec_state.dec_fix_state[i] =2;//设置了不为0的值，但是值相同
			}
			else if(user_moter_pra.AN_Val[i][0] < user_moter_pra.AN_Val[i][1] )//1小
			{
				user_dec_state.dec_fix_state[i] =0;
			}
			else if(user_moter_pra.AN_Val[i][0] > user_moter_pra.AN_Val[i][1] )//1大
			{
				user_dec_state.dec_fix_state[i] =1;
			}
	}
			//行走手改电
	   if((user_moter_pra.AN_Val[6][0]==0x00)||(user_moter_pra.AN_Val[6][1]==0x00)||(user_moter_pra.AN_Val[6][2]==0x00))
		 {
				user_moter1.manul_change_elec =0x00;
		 }
		 else
		{ 
			user_moter1.manul_change_elec =0x01;
		}
		
		
					
	   if((user_moter_pra.AN_Val[7][0]==0x00)||(user_moter_pra.AN_Val[7][1]==0x00)||(user_moter_pra.AN_Val[7][2]==0x00))//都是0，没有设置，不是手改电
		 {
				user_moter2.manul_change_elec =0x00;
		 }
		 else//都不是0，秧台手改电
		{ 
			user_moter2.manul_change_elec =0x01;
		}
		
		 if(user_moter_pra.model_type[7]==0xff)//粮筒控制方式,默认有粮筒can控制器
		 {	 
		   user_moter_pra.model_type[7] = 0x00;
		 }
	
	 //灵敏度
	 if((user_moter_pra.moter_sensor[0][0]==0xffff)||(user_moter_pra.moter_sensor[0][0]==0x0000))
	 {
		 user_moter_pra.moter_sensor[0][0] = MOT1_SENS;//行走电机
	 }
	 
	 if((user_moter_pra.moter_sensor[6][0]==0xffff)||(user_moter_pra.moter_sensor[6][0]==0x0000))
	 {
		 user_moter_pra.moter_sensor[6][0] = SENSOR1_SENS;//行走手柄
	 }
	 
	 if((user_moter_pra.moter_sensor[8][0]==0xffff)||(user_moter_pra.moter_sensor[8][0]==0x0000))
	 {
		 user_moter_pra.moter_sensor[8][0] = SENSOR3_SENS;//转向手柄
	 }
			 
	 //中位裕量
   if((user_moter_pra.moter_sensor[0][1]==0x00)||(user_moter_pra.moter_sensor[0][1]==0xffff))
	 {
	   user_moter_pra.moter_sensor[0][1] =0; //行走电机
	 }

   if((user_moter_pra.moter_sensor[6][1]==0xffff)||(user_moter_pra.moter_sensor[6][1]==0x0000))
	 {
		 user_moter_pra.moter_sensor[6][1] = SENSOR1_THD;//行走手柄
	 }
		 
  	if((user_moter_pra.moter_sensor[8][1]==0xffff)||(user_moter_pra.moter_sensor[8][1]==0x0000))
	 {
		 user_moter_pra.moter_sensor[8][1] = SENSOR3_THD;//转向手柄
	 }	 
	 
	 //	计算中位边缘值

		//行走电机
		if(user_dec_state.dec_fix_state[0]==0)//1小	
		{
		  user_mid_thd[0].val_a = user_moter_pra.AN_Val[0][1]-user_moter_pra.moter_sensor[0][1]; 	
		  user_mid_thd[0].val_b = user_moter_pra.AN_Val[0][1]+user_moter_pra.moter_sensor[0][1]; 				
		}
		else if(user_dec_state.dec_fix_state[0]==1)//1大	
		{
		  user_mid_thd[0].val_a = user_moter_pra.AN_Val[0][1]+user_moter_pra.moter_sensor[0][1]; 	
		  user_mid_thd[0].val_b = user_moter_pra.AN_Val[0][1]-user_moter_pra.moter_sensor[0][1]; 				
		}
		
		
		//行走手柄
		if(user_dec_state.dec_fix_state[6]==0)//1小	
		{
		  user_mid_thd[6].val_a = user_moter_pra.AN_Val[6][1]-user_moter_pra.moter_sensor[6][1]; 	
		  user_mid_thd[6].val_b = user_moter_pra.AN_Val[6][1]+user_moter_pra.moter_sensor[6][1]; 				
		}
		else if(user_dec_state.dec_fix_state[6]==1)//1大	
		{
		  user_mid_thd[6].val_a = user_moter_pra.AN_Val[6][1]+user_moter_pra.moter_sensor[6][1]; 	
		  user_mid_thd[6].val_b = user_moter_pra.AN_Val[6][1]-user_moter_pra.moter_sensor[6][1]; 				
		}		

			//转向手柄
		if(user_dec_state.dec_fix_state[8]==0)//1小	
		{
		  user_mid_thd[8].val_a = user_moter_pra.AN_Val[8][1]-user_moter_pra.moter_sensor[8][1]; 	
		  user_mid_thd[8].val_b = user_moter_pra.AN_Val[8][1]+user_moter_pra.moter_sensor[8][1]; 				
		}
		else if(user_dec_state.dec_fix_state[8]==1)//1大	
		{
		  user_mid_thd[8].val_a = user_moter_pra.AN_Val[8][1]+user_moter_pra.moter_sensor[8][1]; 	
		  user_mid_thd[8].val_b = user_moter_pra.AN_Val[8][1]-user_moter_pra.moter_sensor[8][1]; 				
		}	 
		
		
		
			
	for(i=0;i<2;i++)//电机3个速度等级
	{
	   for(j=0;j<3;j++)
     {
		   if((user_moter_pra.moter_spd_level[i][j]==0xffff)||( user_moter_pra.moter_spd_level[i][j]==0))
       {
         user_moter_pra.moter_spd_level[i][j] = user_mot_sp_level[i][j];  //0表示忽略	 
			 }	
       else
			{
  					
			}
		 }		
	}	
		 
}

/*******************************************************************************
* Function Name  :  
* Description    : 错误处理
* Input          :
* Output         :  
* Return         : 
**************************************/

void user_err(uint8*num_err_temp)
{//死在一个地方不动弹了
		static int AD_CH_value_0 ;
		if((*num_err_temp)>=100)//30ms
		{
			(*num_err_temp)=0;
			if(((AD_CH_value_0-(int)AD_CH_value[0])<=5)&&((AD_CH_value_0-(int)AD_CH_value[0])>=-5))//变化量小于5
			{
				 {
							char * ptr="ka1";
							HAL_UART_Transmit(&huart7,(uint8*)ptr,strlen(ptr),10);
							while(__HAL_UART_GET_FLAG(&huart7,UART_FLAG_TC)!=SET)
							{
								osDelay(2);
							}	
					}
				user_moter_stop(0x01); 
				osDelay(50);//停20ms
			}
		}
		
		 if((*num_err_temp)==0)
		 {
			 AD_CH_value_0 = AD_CH_value[0];
		 }
		 (*num_err_temp)++;
}


/*******************************************************************************
* Function Name  :  
* Description    : 错误处理
* Input          :
* Output         :  
* Return         : 
**************************************/

void user_motor2_err(uint16 *num_err_temp)
{//死在一个地方不动弹了
		static int AD_CH_value_1 ;
		if((*num_err_temp)>=50)//30ms
		{
			(*num_err_temp)=0;
			if(((AD_CH_value_1-(int)AD_CH_value[1])<=5)&&((AD_CH_value_1-(int)AD_CH_value[1])>=-5))//变化量小于5
			{
				 {
							char * ptr="ka2";
							HAL_UART_Transmit(&huart7,(uint8*)ptr,strlen(ptr),10);
							while(__HAL_UART_GET_FLAG(&huart7,UART_FLAG_TC)!=SET)
							{
								osDelay(2);
							}	
					}
				user_moter_stop(0x02); 
				osDelay(500);//停20ms
			}
		}
		
		 if((*num_err_temp)==0)
		 {
			 AD_CH_value_1 = AD_CH_value[1];
		 }
		 (*num_err_temp)++;
}


 void  turn_table_init(void)
 {
	//秧台角度传感器,根据最左最右侧的值，计算刻度
	if((user_moter_pra.ang_min_max[0]!=0) &&(user_moter_pra.ang_min_max[1]!=0))
	{
		uint8 i=0;
		float scal =(user_moter_pra.ang_min_max[1]-user_moter_pra.ang_min_max[0])/59.0; 
		for(i=0;i<60;i++)
		{
      user_moter_pra.ang_m[i] =	scal*i+user_moter_pra.ang_min_max[0];	
		}
	}
	
	//秧板角度传感器,根据最左最右侧的值，计算刻度
	if((user_moter_pra.ang_min_max[2]!=0) &&(user_moter_pra.ang_min_max[3]!=0))
	{
		uint8 i=0;
		float scal =(user_moter_pra.ang_min_max[3]-user_moter_pra.ang_min_max[2])/59.0;
		for(i=0;i<60;i++)
		{
      user_moter_pra.ang_s[i] =	scal*i+user_moter_pra.ang_min_max[2];	
		}
	}

	 {
		 int8 i;
		 float scal_f=( user_moter_pra.spd_min_max[1] - user_moter_pra.spd_min_max[0] )*4.0/59.0;//朝前
		 float scal_b= (user_moter_pra.spd_min_max[3] - user_moter_pra.spd_min_max[2] )*4.0/59.0;//朝前
		 for(i=0;i<60;i++)
		 {
				user_moter_pra.speed_f[i] = i * scal_f * 4.0f; 
				user_moter_pra.speed_b[i] = i * scal_b * 4.0f;	 
		 }
   }
 }
 

uint8 high_user_get(j1939_msg_t * RxMessage)
{
   uint8 high_sta;
   uint8 high_data;
   high_sta = RxMessage->Array[5];
   high_data = RxMessage->Array[4];
   
 if(user_state.manul_auto == 0x02) //无人状态才释放
 {   
	 if(high_sta == 2) //秧台准备升，抬箱子
   {
    user_state.YangXiang_high = 1;
    osSemaphoreRelease( myCountingSemMoter2Handle);
    osSemaphoreRelease( myCountingSemMoter3Handle);
    osSemaphoreRelease( myCountingSemMoter4Handle);
    osSemaphoreRelease( myCountingSemMoter5Handle);    
   } 
   else if((high_sta == 3) && (high_data < 0x25)) //箱子放下去 
   {
    user_state.YangXiang_high = 2;
    osSemaphoreRelease( myCountingSemMoter2Handle);
    osSemaphoreRelease( myCountingSemMoter3Handle);
    osSemaphoreRelease( myCountingSemMoter4Handle);
    osSemaphoreRelease( myCountingSemMoter5Handle);      
   }
//   else 
//   {
//     user_state.YangXiang_high = 0;
//   }
 }
 return 0; 
}

uint8 rice_lack1(j1939_msg_t * RxMessage)
{
   user_state.rice1_state = RxMessage->Array[4]; //
	 if(user_state.manul_auto == 0x02) 
	 {
		 if(RxMessage->Array[10] == 1 && user_state.lieshu_jilu != 2)  //单列缺苗且没有标记成双列
			 user_state.lieshu_jilu = 1;  //标记双列后只有等加苗完成执行复位才清零，才可下一轮锁定
		 
		 else if(RxMessage->Array[11] == 1 && user_state.lieshu_jilu != 1)
			 user_state.lieshu_jilu = 2;
	 }
   return 0;
}

uint8 rice_lack2(j1939_msg_t * RxMessage)
{
   user_state.rice2_state = RxMessage->Array[4];
	 if(user_state.manul_auto == 0x02) 
	 {
		 if(RxMessage->Array[10] == 1 && user_state.lieshu_jilu != 2)  //单列缺苗且没有标记成双列
			 user_state.lieshu_jilu = 1;
		 
		 else if(RxMessage->Array[11] == 1 && user_state.lieshu_jilu != 1)
			 user_state.lieshu_jilu = 2;
	 }
   return 0;
}

uint8 rice_lack3(j1939_msg_t * RxMessage)//hh 自控制器发来的的单双列缺苗状态
{
   user_state.rice3_state = RxMessage->Array[4];
	 if(user_state.manul_auto == 0x02) 
	 {	 
		 if(RxMessage->Array[10] == 1 && user_state.lieshu_jilu != 2)  //单列缺苗且没有标记成双列
			 user_state.lieshu_jilu = 1;
		 
		 else if(RxMessage->Array[11] == 1 && user_state.lieshu_jilu != 1)
			 user_state.lieshu_jilu = 2;
	 }
   return 0;
}

uint8 rice_lack4(j1939_msg_t * RxMessage)//hh 自控制器发来的的单双列缺苗状态
{
   user_state.rice4_state = RxMessage->Array[4];
	 if(user_state.manul_auto == 0x02) 
	 {	 
		 if(RxMessage->Array[10] == 1 && user_state.lieshu_jilu != 2)  //单列缺苗且没有标记成双列
			 user_state.lieshu_jilu = 1;
		 
		 else if(RxMessage->Array[11] == 1 && user_state.lieshu_jilu != 1)
			 user_state.lieshu_jilu = 2;
	 }
   return 0;
}



uint8 YangBang_fuwei(j1939_msg_t * RxMessage)
{
   if(RxMessage->Array[5]==1)

   user_state.fit_mode = 0x02; //hh 加苗完成，可以复位了
   return 0;
}
