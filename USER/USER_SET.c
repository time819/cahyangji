/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:
********************************************/
#include "USER_SET.h"
#include "USER_DATA_TYPE.h"
#include "USER_GLOBAL.h"
#include "USER_PRO.h"
#include "usart.h"
#include "USER_FLASH.h"
#include "USER_MISC.h"
#include "cmsis_os.h"
#include "dma.h"
#include "gpio.h"
#include "tim.h"
#include "USER_FREE_RT_OS.h"
#include "can.h"
#include "stdlib.h"
#include "USER_WIRE_LESS.h"
#include "USER_BOOT_MISC.h"
#include "USER_MOTER.h"
/************************************************************************************************
* Function Name  :  
* Description    :  
* Input          :  
* Output         :  
* Return         :  
**************************************************************************************************/
void User_Pra_Set(char *buff)
{
	
	if(strstr(buff,"ok")!=NULL)
	{
				uint8 i=0,j=0;
		
				for(i=0;i<AN_MOT_MAX_NUM;i++)
				{
					uint16 min_temp =0xffff;//在没有设置好值，按了遥控器要不会动作的
					uint16 max_temp =0x0000;//在没有设置好值，按了遥控器要不会动作的
					for(j=0;j<AN_VAL_MAX_NUM;j++)
					{	
							if(user_moter_pra.AN_Val[i][j]!=0)//等于0就没有用到
							{ 
									
//								if(user_moter_pra.AN_Val_Min[i]> user_moter_pra.AN_Val[i][j])//获得最小值
									if(min_temp> user_moter_pra.AN_Val[i][j])//获得最小值
									{
//										user_moter_pra.AN_Val_Min[i]= user_moter_pra.AN_Val[i][j];
											min_temp = user_moter_pra.AN_Val[i][j];
									}
									
//									if(user_moter_pra.AN_Val_Max[i]<user_moter_pra.AN_Val[i][j])//获得最大值
									if(max_temp<user_moter_pra.AN_Val[i][j])//获得最大值
									{
//										user_moter_pra.AN_Val_Max[i]= user_moter_pra.AN_Val[i][j];
									
										max_temp = user_moter_pra.AN_Val[i][j];
									}
							}
							
					}
					user_moter_pra.AN_Val_Max[i] = max_temp;
					user_moter_pra.AN_Val_Min[i] = min_temp;
				}
			
 
			User_Flash_Stor_Infor_write( );//写入flash		
			user_send_str(&huart7, "已经保存数据\r\n");
	}
	
	else if(strstr(buff,"set")!=NULL)
	{
		show_infor( );
	}

	else if(strstr(buff,"angm")!=NULL)//插秧机秧台27个位置
	{
		 int  num=0;
     uint16 val=0;
 
		char ptr[36];
		sscanf(buff,"%[^,],%d",(char*)(&ptr),&num );	
		
		if((num>27)&&
			 (num!=90)&&
       (num!=91)   
		 )
		{
			user_send_str(&huart7,"输入超出范围"); 
		  return;
		}
		
		val = AD_CH_value[6];
		if(num==90)
		{
		  user_moter_pra.ang_min_max[0]=val;
		}
		else if(num==91)
		{
		  user_moter_pra.ang_min_max[1]=val;
		}
		else  
		{
		  user_moter_pra.ang_m[num-1]=val;
		}
		
		sprintf(ptr,"%s,%d,%d\r\n","秧台设置参数:",num,val);
		user_send_str(&huart7, ptr);		
	
	}
	else if(strstr(buff,"angs")!=NULL)//插秧机秧板27个位置
	{
		 int  num=0;
     uint16 val=0;
 
		char ptr[36];
		sscanf(buff,"%[^,],%d",(char*)(&ptr),&num );	
		
		if((num>27)&&
			 (num!=90)&&
       (num!=91)   
		 )
		{
			user_send_str(&huart7,"输入超出范围"); 
		  return;
		}
	
		val = AD_CH_value[0];	
		if(num==90)
		{
		  user_moter_pra.ang_min_max[2]=val;
		}
		else if(num==91)
		{
		  user_moter_pra.ang_min_max[3]=val;
		}
		else  
		{
		  user_moter_pra.ang_s[num-1]=val;
		}
		
		sprintf(ptr,"%s,%d,%d\r\n","秧板设置参数:",num,val);
		user_send_str(&huart7, ptr);		
	}

	else if(strstr(buff,"spd")!=NULL)// 速度设置,基本速度，0-13个速度,
	{
	 	 int  num=0;
     int val=0;
		 int val2=0;
		 char ptr[36];
		 sscanf(buff,"%[^,],%d,%d,%d",(char*)(&ptr),&num,&val,&val2);	
		if(num==89)
		{
      user_moter_pra.speed_init = val;
		}		
		else if(num==90)//追赶速度，输入转数绝对值,是偏移值
		{
		  user_moter_pra.spd_min_max[0]=val;
		  user_moter_pra.spd_min_max[1]= val2 ;			
		}
		else if(num==91)//等待速度，输入转数绝对值，是偏移值
		{
		  user_moter_pra.spd_min_max[2]=val;		
		  user_moter_pra.spd_min_max[3]=val2;
		}
	  sprintf(ptr,"%s%d,%d\r\n","秧板速度参数:",val,val2);
		user_send_str(&huart7, ptr);		
	}
  else if(strstr(buff,"mode")!=NULL)// 模式设置,
	{
	   int val=0;
		 char ptr[36];
		sscanf(buff,"%[^,],%d",(char*)(&ptr),&val);	  
	 	user_state.fit_mode = val;
	  sprintf(ptr,"%s,%d\r\n","模式:",val);
		user_send_str(&huart7, ptr);	
	}
  
  else if(strstr(buff,"box_up")!=NULL)// 
	{
    user_state.YangXiang_high = 1;
    osSemaphoreRelease( myCountingSemMoter2Handle);
    osSemaphoreRelease( myCountingSemMoter3Handle);
    osSemaphoreRelease( myCountingSemMoter4Handle);
    osSemaphoreRelease( myCountingSemMoter5Handle);
    user_send_str(&huart7, "秧箱抬升测试\r\n");	
	}  
  else if(strstr(buff,"box_down")!=NULL)// 
	{
    user_state.YangXiang_high = 2; 
    osSemaphoreRelease( myCountingSemMoter2Handle);
    osSemaphoreRelease( myCountingSemMoter3Handle);
    osSemaphoreRelease( myCountingSemMoter4Handle);
    osSemaphoreRelease( myCountingSemMoter5Handle);
    user_send_str(&huart7, "秧箱下降测试\r\n");	
	}  
	
  else if(strstr(buff,"speed_text1")!=NULL)// 
	{
     speed_text1 = 1;
		 user_send_str(&huart7, "秧板速度测试\r\n");	
	}
  else if(strstr(buff,"speed_text0")!=NULL)// 
	{
     speed_text1 = 0;
		 user_send_str(&huart7, "秧板测试结束\r\n");	
	}
  else if(strstr(buff,"rad_text1")!=NULL)// 
	{
     rad_text = 1;
		 user_send_str(&huart7, "转速测试\r\n");	
	}
  else if(strstr(buff,"rad_text0")!=NULL)// 
	{
     rad_text = 0;
		 user_send_str(&huart7, "转速测试结束\r\n");	
	}  
  
  else if(strstr(buff,"speed_text2")!=NULL)// 
	{
     speed_text1 = 2;
		 user_send_str(&huart7, "秧板速度测试\r\n");	
	}  

  else if(strstr(buff,"def1")!=NULL)// 
	{
     char ptr[36];
     user_moter_pra.AN_reset_data = AD_CH_value[0];
	   sprintf(ptr,"%s,%d\r\n","复位值:", user_moter_pra.AN_reset_data);
		 user_send_str(&huart7, ptr);	
	}
  else if(strstr(buff,"yangban2")!=NULL)// 
	{
     char ptr[36];
     user_moter_pra.yangban_xuanzhe = AD_CH_value[5];
	   sprintf(ptr,"%s,%d\r\n","换行电机复位值:", user_moter_pra.yangban_xuanzhe);
		 user_send_str(&huart7, ptr);	
	}
	else if(strstr(buff,"yangban0")!=NULL) //换行电机复位
	{
		 user_send_str(&huart7, "换行电机复位\r\n");	
		 user_state.huanhang_sta = 0;
	   osSemaphoreRelease(myCountingSemElecAcceleratorHandle);
	}
	else if(strstr(buff,"yangban100")!=NULL)
	{
	   user_send_str(&huart7, "换行电机伸长\r\n");	
		 user_moter_forward(0x01,380);
		 osDelay(120);
		 user_moter_stop(0x01);
	}
	else if(strstr(buff,"yangban99")!=NULL)
	{
	   user_send_str(&huart7, "换行电机缩短\r\n");	
		 user_moter_backward(0x01,380);
		 osDelay(120);
		 user_moter_stop(0x01);
	}	 	  
  
  else if(strstr(buff,"start1")!=NULL)// 
	{
     user_state.manul_auto = 2;
		 user_send_str(&huart7, "测试开始\r\n");	
	}	
  else if(strstr(buff,"start0")!=NULL)// 
	{
     user_state.manul_auto = 1;
		 user_send_str(&huart7, "测试开始\r\n");	
	}	
	else if(strstr(buff,"boot")!=NULL)//软件复位
	{
		user_send_str(&huart7, "请5秒内长按退格键，知道升级信息提示\r\n"); 
		User_Soft_Reset( );
	}
	else if(strstr(buff,"study")!=NULL)//遥控器学习，和flash无关系了
	{
		int id, ch;
		char ptr[20];
		sscanf(buff,"%[^,],%d,%d,",(char*)(&ptr),&id,&ch );
		user_wl_struct.id = id;
		user_wl_struct.ch =  ch;
		if(user_wl_struct.study_cmd_from == 0x01)//指令来自can)
		{
			user_wl_struct.study_cmd_from =0x00;
			//已经设置过了就不在设置了
		}
		else//来自串口
		{
			user_wl_struct.mode =  CFG_MODE;//进入了配置模式
		}
		
//		user_wl_struct.study_on_off =0x01;//意思是开始配置了，不写这个配对中，会退出
		sprintf(ptr,"%s%d\r\n","新设的ID:",id);
		user_send_str(&huart7, ptr);
		sprintf(ptr,"%s%d\r\n","新设的CH:",ch);
		user_send_str(&huart7, ptr);
		osMessageQueuePut(myQueueUart2Spi3RecHandle, "", 0, NULL);//空数据，该队列仅用于触发任务,这是干嘛用的？
	}
	else if(strstr(buff,"CTLRINFO")!=NULL)// 
	{ 
		user_send_str(&huart7, "\r\n");
		user_send_str(&huart7, user_basic_infor.boot_ver); 
		
		user_send_str(&huart7, "\r\n");
		user_send_str(&huart7, user_basic_infor.pn); 
		
		user_send_str(&huart7, "\r\n");
		user_send_str(&huart7, user_basic_infor.sn); 
		
		user_send_str(&huart7, "\r\n");
		user_send_str(&huart7, user_basic_infor.app_ver); 
	}
	else if(strstr(buff,"PNINFO")!=NULL)// 
	{ 
		uint32 val_temp[8]={0};
		sscanf(buff,"%s\r\n",user_basic_infor.pn );
		
		sscanf(user_basic_infor.pn,"PNINFO,%1x%02x%02x%02x%02x%02x%02x%02x", 
		& val_temp[7],&val_temp[6],&val_temp[5],
		& val_temp[4],&val_temp[3],&val_temp[2],
		& val_temp[1],& val_temp[0]); 
		
		val_temp[7] =val_temp[7]|0xf0;
		{
			uint8 i=0;
		  for(i=0;i<8;i++)
			{
			 user_basic_infor.pn_can[i] = val_temp[i];
			}
		}
		
		strcpy(user_sn_pn.pn,user_basic_infor.pn);
		
  	user_write_Flash_buffer_1(SN_PN_INFOR_ADDR,(uint8 *)(&user_sn_pn), sizeof(user_sn_pn),FLASH_SECTOR_2);
		user_send_str(&huart7, "已保存PN码\r\n"); 
	}
	else if(strstr(buff,"SNINFO")!=NULL)// 
	{ 
		uint32 val_temp[5]={0};
		sscanf(buff,"%s\r\n", user_basic_infor.sn);
		
		sscanf(user_basic_infor.sn,"SNINFO,%02x%02x%02x%02x%02x",
		&val_temp[4],&val_temp[3],&val_temp[2],
		&val_temp[1],&val_temp[0]);  			  
	 strcpy(user_sn_pn.sn,user_basic_infor.sn);
		{
			uint8 i=0;
		  for(i=0;i<5;i++)
			{
			 user_basic_infor.sn_can[i] = val_temp[i];
			}
		}
    user_write_Flash_buffer_1(SN_PN_INFOR_ADDR,(uint8 *)(&user_sn_pn), sizeof(user_sn_pn),FLASH_SECTOR_2);
		user_send_str(&huart7, "已保存SN码\r\n"); 
	}
	
	else if(strstr(buff,"clear1")!=NULL)//设备复位
	{
		user_send_str(&huart7, "设备1置初始值\r\n"); 
		{
			uint8 i=0;
			for(i=0;i<AN_VAL_MAX_NUM ;i++)
			{
				user_moter_pra.AN_Val[0][i] =0;
			}
		}
	}
	else if(strstr(buff,"clear2")!=NULL)//设备复位
	{
		
		user_send_str(&huart7, "设备2回复初始值\r\n"); 
		{
			uint8 i=0;
			for(i=0;i<AN_VAL_MAX_NUM ;i++)
			{
				user_moter_pra.AN_Val[1][i] =0;
			}
		}
	}
		else if(strstr(buff,"clear3")!=NULL)//设备复位
	{
		user_send_str(&huart7, "设备3回复初始值\r\n"); 
		{
			uint8 i=0;
			for(i=0;i<AN_VAL_MAX_NUM ;i++)
			{
				user_moter_pra.AN_Val[2][i] =0;
			}
		}
	}
	else if(strstr(buff,"clear4")!=NULL)//设备复位
	{
		
		user_send_str(&huart7, "设备4回复初始值\r\n"); 
		{
			uint8 i=0;
			for(i=0;i<AN_VAL_MAX_NUM ;i++)
			{
				user_moter_pra.AN_Val[3][i] =0;
			}
		}
	}
	else if(strstr(buff,"clear5")!=NULL)//软件复位
	{
		user_send_str(&huart7, "设备5回复初始值\r\n"); 
		{
			uint8 i=0;
			for(i=0;i<AN_VAL_MAX_NUM ;i++)
			{
				user_moter_pra.AN_Val[4][i] =0;
			}
		}
	}
	else if(strstr(buff,"clear6")!=NULL)//软件复位
	{
		
		user_send_str(&huart7, "设备6回复初始值\r\n"); 
		{
			uint8 i=0;
			for(i=0;i<AN_VAL_MAX_NUM ;i++)
			{
				user_moter_pra.AN_Val[5][i] =0;
			}
		}
	}
	else if(strstr(buff,"clear7")!=NULL)//软件复位
	{
		
		user_send_str(&huart7, "设备7回复初始值\r\n"); 
		{
			uint8 i=0;
			for(i=0;i<AN_VAL_MAX_NUM ;i++)
			{
				user_moter_pra.AN_Val[6][i] =0;
			}
		}
	}
	else if(strstr(buff,"clear8")!=NULL)//软件复位
	{
		
		user_send_str(&huart7, "设备8回复初始值\r\n"); 
		{
			uint8 i=0;
			for(i=0;i<AN_VAL_MAX_NUM ;i++)
			{
				user_moter_pra.AN_Val[7][i] =0;
			}
		}
	}
	else//获得电机编号和数据
	{
		int moter_ID,moter_len_ID;
		sscanf(buff,"%d,%d",&moter_ID,&moter_len_ID);
		
		if((moter_ID>=1)&&(moter_ID<=AN_MOT_MAX_NUM)&&(moter_len_ID>=1)&&(moter_len_ID<=10))
		{
			char Ptr[32]={0};
			user_moter_pra.AN_Val[moter_ID-1][moter_len_ID-1] =  AD_CH_value[moter_ID-1];//获取当前AD值
			sprintf(Ptr,"%s%d%s%d%s%d\r\n","电机",moter_ID,"第",moter_len_ID,"段采集到的数据是:",user_moter_pra.AN_Val[moter_ID-1][moter_len_ID-1]);
			user_send_str(&huart7, Ptr);
		}
		else if(moter_len_ID==99)//daotui
		{
		  user_moter_current_detect(2);//监测缩短时电流
			if(moter_ID==1)
			{
				{
					uint8  tet2[8] = {0xf0,0xe0,0xb0,0x7e,0xff,0xff,0xff,0xff}; //7db0,16转每分钟
					user_can_EXTID_send(&hcan2,0x0cff9826, tet2, (uint32_t*)CAN_TX_MAILBOX0);		
				}	
			 	osDelay(150);
			  {
					char Ptr[30]={0};
					user_send_str(&huart7, " ->电机1实时数据：");
					sprintf(Ptr,"%d\r\n",AD_CH_value[0] );
					user_send_str(&huart7, Ptr);
				}
				
				{
						uint8  tet2[8] = {0xf0,0xe0,0x80,0x7d,0xff,0xff,0xff,0xff}; 
						user_can_EXTID_send(&hcan2,0x0cff9826, tet2, (uint32_t*)CAN_TX_MAILBOX0);
						osDelay(5);
						user_can_EXTID_send(&hcan2,0x0cff9826, tet2, (uint32_t*)CAN_TX_MAILBOX0);						
				}					
			}
			else if(moter_ID==2)
			{
				user_moter2.lock_s =1;//电机2需要自锁几秒				
				user_moter_backward(0x02,500);
				osDelay(75);
				{
					char Ptr[30]={0};
					user_send_str(&huart7, " ->电机2实时数据：");
					sprintf(Ptr,"%d\r\n",AD_CH_value[1] );
					user_send_str(&huart7, Ptr);
				}
				user_moter_stop(0x02);
			}
			else if(moter_ID==3)
			{
				user_moter_backward(0x03,500);
				osDelay(75);
			  {
					char Ptr[30]={0};
					user_send_str(&huart7, " ->电机3实时数据：");
					sprintf(Ptr,"%d\r\n",AD_CH_value[2] );
					user_send_str(&huart7, Ptr);
				}				
				user_moter_stop(0x03);
			}
			else if(moter_ID==4)
			{
				user_moter_backward(0x04,500);
				osDelay(75);
			  {
					char Ptr[30]={0};
					user_send_str(&huart7, " ->电机4实时数据：");
					sprintf(Ptr,"%d\r\n",AD_CH_value[3] );
					user_send_str(&huart7, Ptr);
				}				
				user_moter_stop(0x04);
			}
			else if(moter_ID==5)
			{
				user_moter_backward(0x05,500);
				osDelay(75);
			  {
					char Ptr[30]={0};
					user_send_str(&huart7, " ->电机5实时数据：");
					sprintf(Ptr,"%d\r\n",AD_CH_value[4] );
					user_send_str(&huart7, Ptr);
				}				
				user_moter_stop(0x05);
			}
			user_send_str(&huart7, "缩回");
		}
		else if(moter_len_ID==100)//qianjin
		{
			user_moter_current_detect(1);//监测伸长时电流	 
			if(moter_ID==1)
			{
				{
						uint8  tet2[8] = {0xf0,0xe0,0x00,0x7d,0xff,0xff,0xff,0xff}; //7db0,16转每分钟
						user_can_EXTID_send(&hcan2,0x0cff9826, tet2, (uint32_t*)CAN_TX_MAILBOX0);		
				}	
			 	osDelay(150);
			  {
					char Ptr[30]={0};
					user_send_str(&huart7, " ->电机1实时数据：");
					sprintf(Ptr,"%d\r\n",AD_CH_value[0] );
					user_send_str(&huart7, Ptr);
				}
				{
						uint8  tet2[8] = {0xf0,0xe0,0x80,0x7d,0xff,0xff,0xff,0xff}; 
						user_can_EXTID_send(&hcan2,0x0cff9826, tet2, (uint32_t*)CAN_TX_MAILBOX0);
						osDelay(5);
						user_can_EXTID_send(&hcan2,0x0cff9826, tet2, (uint32_t*)CAN_TX_MAILBOX0);		
				}					
			}
			else if(moter_ID==2)
			{
				user_moter2.lock_s =1;//电机1需要自锁几秒				
				user_moter_forward(0x02,500);
				osDelay(75);
			  {
					char Ptr[30]={0};
					user_send_str(&huart7, " ->电机2实时数据：");
					sprintf(Ptr,"%d\r\n",AD_CH_value[1] );
					user_send_str(&huart7, Ptr);
				}				
				user_moter_stop(0x02);
			}
			else if(moter_ID==3)
			{
				user_moter_forward(0x03,500);
				osDelay(75);
			  {
					char Ptr[30]={0};
					user_send_str(&huart7, " ->电机3实时数据：");
					sprintf(Ptr,"%d\r\n",AD_CH_value[2] );
					user_send_str(&huart7, Ptr);
				}				
				user_moter_stop(0x03);
			}
			else if(moter_ID==4)
			{
				user_moter_forward(0x04,500);
				osDelay(75);
			  {
					char Ptr[30]={0};
					user_send_str(&huart7, " ->电机4实时数据：");
					sprintf(Ptr,"%d\r\n",AD_CH_value[3] );
					user_send_str(&huart7, Ptr);
				}				
				user_moter_stop(0x04);
			}			
			else if(moter_ID==5)
			{
				user_moter_forward(0x05,500);
				osDelay(75);
			  {
					char Ptr[30]={0};
					user_send_str(&huart7, " ->电机5实时数据：");
					sprintf(Ptr,"%d\r\n",AD_CH_value[4] );
					user_send_str(&huart7, Ptr);
				}				
				user_moter_stop(0x05);
			}			
			user_send_str(&huart7, "伸长");
		}
		else 
		{
			user_send_str(&huart7, " 输入出错，电机编号不能超过6小于1，长度编号不能超过10小于1\r\n");	
		}
	}
}

//开机显示信息
void show_infor(void)
{
		char Ptr[30]={0};
//		user_send_str(&huart7, "***************** 上苗二代车主控V1.8_0117 *******************\r\n");	
		user_send_str(&huart7, "***************** 上苗二代车主控*******************\r\n");	
		user_send_str(&huart7, "启动固件版本:\r\n");	
		user_send_str(&huart7, user_basic_infor.boot_ver);
    user_send_str(&huart7, "\r\n");	

		user_send_str(&huart7, "APP固件版本:\r\n");	
		user_send_str(&huart7, user_ver);
    user_send_str(&huart7, "\r\n");			
		
		user_send_str(&huart7, "PN、SN号:\r\n");
		user_send_str(&huart7, user_basic_infor.pn); 
		user_send_str(&huart7, "\r\n");		
		user_send_str(&huart7, user_basic_infor.sn); 
		user_send_str(&huart7, "\r\n");	
		memset(Ptr,0,30);

 		 {
			 uint32 i,j,k;
				for(i=0;i<100;i++)
				{
					for(j=0;j<100;j++)
					{
					  for(k=0;k<1000;k++)
						{
						
						}
					}
				}
			}
		
		user_send_str(&huart7, "\r\n");	
		{
			char Ptr[30]={0};
	
			{
        int val = user_moter_pra.speed_init;
				user_send_str(&huart7, " ->同步状态电机数据：");
				sprintf(Ptr,"%d\r\n",val);
				user_send_str(&huart7, Ptr);
				memset(Ptr,0,30);
			}
			
			user_send_str(&huart7, " ->传感器极限数据：");
			sprintf(Ptr,"%d,%d,%d,%d \r\n",user_moter_pra.ang_min_max[0],user_moter_pra.ang_min_max[1],\
			        user_moter_pra.ang_min_max[2],user_moter_pra.ang_min_max[3] );
			user_send_str(&huart7, Ptr);
			memset(Ptr,0,30);			
 
			user_send_str(&huart7, " ->速度极限数据：");
			sprintf(Ptr,"%d,%d,%d,%d \r\n",user_moter_pra.spd_min_max[0],user_moter_pra.spd_min_max[1],\
			user_moter_pra.spd_min_max[2],user_moter_pra.spd_min_max[3] );
			user_send_str(&huart7, Ptr);
			memset(Ptr,0,30);	
 
			user_send_str(&huart7, "\r\n");
		}
    
 		 {
			 uint32 i,j,k;
				for(i=0;i<100;i++)
				{
					for(j=0;j<100;j++)
					{
					  for(k=0;k<1000;k++)
						{
						
						}
					}
				}
			}   
			user_send_str(&huart7, " ->秧箱电机1数据：");
			sprintf(Ptr,"%d,%d\r\n",user_moter_pra.AN_Val[1][0],user_moter_pra.AN_Val[1][1]);
			user_send_str(&huart7, Ptr);
			memset(Ptr,0,30);  
      
			user_send_str(&huart7, " ->秧箱电机2数据：");
			sprintf(Ptr,"%d,%d\r\n",user_moter_pra.AN_Val[2][0],user_moter_pra.AN_Val[2][1]);
			user_send_str(&huart7, Ptr);
			memset(Ptr,0,30);  
      
			user_send_str(&huart7, " ->秧箱电机3数据：");
			sprintf(Ptr,"%d,%d\r\n",user_moter_pra.AN_Val[3][0],user_moter_pra.AN_Val[3][1]);
			user_send_str(&huart7, Ptr);
			memset(Ptr,0,30);  
      
			user_send_str(&huart7, " ->秧箱电机4数据：");
			sprintf(Ptr,"%d,%d\r\n",user_moter_pra.AN_Val[4][0],user_moter_pra.AN_Val[4][1]);
			user_send_str(&huart7, Ptr);
			memset(Ptr,0,30);  

			user_send_str(&huart7, " ->秧板复位值：");
			sprintf(Ptr,"%d\r\n", user_moter_pra.AN_reset_data);
			user_send_str(&huart7, Ptr);
			memset(Ptr,0,30);  
      
			user_send_str(&huart7, " ->秧板实时值：");
			sprintf(Ptr,"%d\r\n", AD_CH_value[0]);
			user_send_str(&huart7, Ptr);
			memset(Ptr,0,30); 
			
			user_send_str(&huart7, " ->秧台实时值：");
			sprintf(Ptr,"%d\r\n", AD_CH_value[6]);
			user_send_str(&huart7, Ptr);
			memset(Ptr,0,30);   			

			user_send_str(&huart7, " ->换行电机复位值：");
			sprintf(Ptr,"%d\r\n", user_moter_pra.yangban_xuanzhe);
			user_send_str(&huart7, Ptr);
			memset(Ptr,0,30);  
      
			user_send_str(&huart7, " ->换行电机实时值：");
			sprintf(Ptr,"%d\r\n", AD_CH_value[5]);
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

/*************************************************
* Funcname      :
* Pra       		:
主机类型
0拖拉机
1插秧机
2收割机
3植保机

行走控制方式
0单电机控制
1双电机控制
2开关信号控制
3模拟信号控制

升降控制方式
0电机控制
1开关信号控制
2驱动信号控制
3模拟信号控制
* Describtion   :  设置车的类型等
************************************************/
uint8 user_pra_mode_type(uint8 *data_buff_temp)
{
	uint8 pra_num_sub;
	uint8 pra_wr_rd_type;
	uint8 buffer_uart7_cfg_temp[24]={"ok"};
	uint8 buffer_can_cfg[8]={0xff, 0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	BaseType_t pxHigherPriorityTaskWoken;
	
	pra_num_sub =  data_buff_temp[1]&0x0f;
	pra_wr_rd_type = (data_buff_temp[1]>>4)&0x03;
	if(pra_wr_rd_type==0x01)//设置
	{
//		char Ptr1[32]={0};
		switch(pra_num_sub)
		{
			case 0://遥控器地址和频道

//				user_moter_pra.remot_id = data_buff_temp[3];
//				user_moter_pra.remot_id =(user_moter_pra.remot_id<<8)|data_buff_temp[2];
//				user_moter_pra.remot_chn = data_buff_temp[4];
				 
			 user_wl_pra_from_can(&user_wl_struct ,data_buff_temp);
							

			sprintf( (char*)buffer_uart7_cfg_temp,"%s,%d,%d\r\n","study",user_wl_struct.id,user_wl_struct.ch);
			user_send_str(&huart7,  (char*)buffer_uart7_cfg_temp);
			
			
				osMessageQueuePut(myQueueUart7RecHandle,  buffer_uart7_cfg_temp, 0, NULL);//用于中断时，延时要为0
//				portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);//如果需要的话进行一次任务切换
				portYIELD( );//如果需要的话进行一次任务切换
				memset(buffer_uart7_cfg_temp,0,sizeof(buffer_uart7_cfg_temp));

			break;
			case 1://各模块类型
				{
					uint8 i=0;
					for(i=0;i<6;i++)
					{
						if(data_buff_temp[i]!=0xff)
						{
							user_moter_pra.model_type[i] = data_buff_temp[i+2];//车的类型
						}
					}
				}
				osMessageQueuePut(myQueueUart7RecHandle, buffer_uart7_cfg_temp, 0, NULL);//用于中断时，延时要为0
				portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);//如果需要的话进行一次任务切换
				memset(buffer_uart7_cfg_temp,0,sizeof(buffer_uart7_cfg_temp));
				break;
			default:
				break;
			
		}
	}
	else if(pra_wr_rd_type==0x00)//查询
	{
		switch(pra_num_sub)
		{
			case 0://遥控器地址和频道
				buffer_can_cfg[0]	=	0x01;
				buffer_can_cfg[1]	=	0xf0;
				buffer_can_cfg[2]	= user_moter_pra.remot_id &0xff;// 
				buffer_can_cfg[3]	=	user_moter_pra.remot_id>>8 ;// 
				buffer_can_cfg[4]	=	user_moter_pra.remot_chn  ;// 
				buffer_can_cfg[5]	=	user_wl_struct.study_on_off;// 
				buffer_can_cfg[6]	=	0xff;
				buffer_can_cfg[7]	=	0xff;
			
			
//				user_wl_pra_from_can(&user_wl_struct ,data_buff_temp);//查询这句话不要 了
				break;
			case 1://各模块类型
			buffer_can_cfg[0]	=	0x01;
			buffer_can_cfg[1]	=	0xf1;	
			buffer_can_cfg[2]	= user_moter_pra.model_type[0] ;//车的类型
			buffer_can_cfg[3]	=	user_moter_pra.model_type[1] ;//行走类型
			buffer_can_cfg[4]	=	user_moter_pra.model_type[2]  ;//升降类型
			buffer_can_cfg[5]	=	user_moter_pra.model_type[3] ;//作业类型	
			buffer_can_cfg[6]	=	0xff;
			buffer_can_cfg[7]	=	0xff;
				//参数查询 0x0CFF5490 
				
				break;
			default:
				break;	
		}
		user_can_EXTID_send(&hcan2,0x0CFF5490 ,buffer_can_cfg, (uint32_t*)CAN_TX_MAILBOX0);//
		memset(buffer_can_cfg,0,sizeof(buffer_can_cfg));
	}
	return 0;
}
