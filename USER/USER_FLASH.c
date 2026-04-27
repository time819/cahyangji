/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:
********************************************/

#include "USER_FLASH.h"
#include "stm32f7xx_hal.h"//注意头文件的包含顺序，千万千万
#include "stm32f7xx_hal_flash.h"//注意头文件的包含顺序，千万千万

#include "stm32f7xx_hal_flash_ex.h"
#include "tim.h"
#include "usart.h"
#include "USER_PRO.h"

	uint32 writeFlashData = 0x11223366;
	uint32 addr = 0x080C0000;//地址要和sector相对应
	
	char * user_ver_std  ="APPINFO,V1.01.21.31";//统一版本号
  char * user_ver    =  "shangmaio_tb012024061202\r\n";//自定义版本号
	sn_pn_t user_sn_pn ;
	basic_infor_t user_basic_infor;
	
	//FLASH写入数据测试
	void writeFlashTest(void)
	{
			FLASH_EraseInitTypeDef EraseInitStruct;
			uint32_t PageError = 0;
//			__disable_irq(); //关闭所有中断

		//1、解锁FLASH
			HAL_FLASH_Unlock();

			//2、擦除FLASH
			//初始化FLASH_EraseInitTypeDef


			/* Fill EraseInit structure*/
			EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
			EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
			EraseInitStruct.Sector        = FLASH_SECTOR_7;
			EraseInitStruct.NbSectors     = 1;

			if(HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK)
			{
					;
			}
				
				
	  //	f.PageAddress = addr;
		//	f.NbPages = 1;
			//设置PageError
		//	uint32_t PageError = 0;
		//	//调用擦除函数
		//	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

			//3、对FLASH烧写
			HAL_FLASH_Program(TYPEPROGRAM_BYTE , addr, writeFlashData);

			//4、锁住FLASH
			HAL_FLASH_Lock();
		
//			__enable_irq();//打开所有中断
	}

	
/*************************************************
* Funcname      :
* Pra       		:
* Describtion   :  在最后一页写数据
************************************************/
	void user_read_flash_buff(uint32 addr ,uint8 *buffer,uint16 buffer_size)
	{
		uint16 buffer_size_temp = buffer_size ;
		uint32 addr_temp = addr;
		while( buffer_size_temp>0)
		{
			*buffer = *((uint8*)(addr_temp));	
			buffer_size_temp--;
			buffer++;
			addr_temp++;
		}

	}

/*************************************************
* Funcname      :
* Pra       		:
* Describtion   :  在最后一页写数据
************************************************/
void user_write_Flash_buffer(uint32 addr,uint8 *buffer, uint16 buffer_size)
{
		FLASH_EraseInitTypeDef EraseInitStruct;
		uint32_t PageError = 0;
		uint32 addr_temp = addr;
		uint16 buffer_size_temp = buffer_size;
			__disable_irq(); //关闭所有中断

	//1、解锁FLASH
		HAL_FLASH_Unlock();

		//2、擦除FLASH
		//初始化FLASH_EraseInitTypeDef

	
	//这个参数VoltageRange_3代表你以什么为单位进行擦除。
//VoltageRange_1代表以字节（8bit）为单位进行擦除、
//VoltageRange_1代表以半字（16bit）为单位进行擦除、
//VoltageRange_3代表以字（32bit）为单位进行擦除、
//VoltageRange_4代表以双字（64bit）为单位进行擦除。

		/* Fill EraseInit structure*/
		EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
		EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
		EraseInitStruct.Sector        = FLASH_SECTOR_3;
		EraseInitStruct.NbSectors     = 1;

		{
			uint8 i=0;
			for(i=0;i<5;i++)
			{
				delay_ms(50);	
				if(HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) == HAL_OK)
				{	
					break;
				}
				delay_ms(200);	
			}
		}
			
		//3、对FLASH烧写
		while( buffer_size_temp>0)
		{
				HAL_FLASH_Program(TYPEPROGRAM_BYTE , addr_temp ,*buffer);
				addr_temp++;
				buffer++;
				buffer_size_temp--;
//				delay_ms(10);
		}
		//4、锁住FLASH
		HAL_FLASH_Lock();
		delay_ms(10);
	
		__enable_irq();//打开所有中断
}
/*************************************************
* Funcname      :
* Pra       		:
* Describtion   :  在最后一页写数据
************************************************/
void user_write_Flash_buffer_1(uint32 addr,uint8 *buffer, uint16 buffer_size,uint8 page)
{
		FLASH_EraseInitTypeDef EraseInitStruct;
		uint32_t PageError = 0;
		uint32 addr_temp = addr;
		uint16 buffer_size_temp = buffer_size;
			__disable_irq(); //关闭所有中断

	//1、解锁FLASH
		HAL_FLASH_Unlock();
 
		/* Fill EraseInit structure*/
		EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
		EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
		EraseInitStruct.Sector        =  page;
		EraseInitStruct.NbSectors     = 1;

		{
			uint8 i=0;
			for(i=0;i<5;i++)
			{
				delay_ms(50);	
				if(HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) == HAL_OK)
				{
					
					break;
				}
				delay_ms(200);	
			}
		}
			
		//3、对FLASH烧写
		while( buffer_size_temp>0)
		{
				HAL_FLASH_Program(TYPEPROGRAM_BYTE , addr_temp ,*buffer);
				addr_temp++;
				buffer++;
				buffer_size_temp--;
//				delay_ms(10);
		}
		//4、锁住FLASH
		HAL_FLASH_Lock();
		delay_ms(10);
	
		__enable_irq();//打开所有中断
}
	/*************************************************
	* Funcname      :  
	* Version       :  
	* Describtion   : 初始化基本本配置信息，这些信息是要求保存在flash中的，从flash中读取数据到User_Flash_Stor_Infor
	* Creator				:
	* Date					:
	********************************************/
	void user_basic_infor_init(void)
	{
		  char ptr[16]={0};
			delay_ms(200);
			user_read_flash_buff( BOOT_VER_INFOR_ADDR	,(uint8*)(&user_basic_infor.boot_ver),sizeof(user_basic_infor.boot_ver));//读数据到flash变量区
      {
				uint32 val_temp[4]={0};
//			  sscanf(user_basic_infor.boot_ver,"%15[^0-9]%d.%d.%d.%d",(char*)(&ptr),
          sscanf(user_basic_infor.boot_ver,"BOOTINFO,V%d.%d.%d.%d",				
				&val_temp[0],
				&val_temp[1],
				&val_temp[2],
				&val_temp[3]			
				);
				
				{
					uint8 i=0;
					for(i=0;i<4;i++)
					{
					  user_basic_infor.boot_ver_can[i] = val_temp[i];
					}
				}
				
				memset(ptr,0,sizeof(ptr));
			}
//				delay_ms(200);	
			user_read_flash_buff( SN_PN_INFOR_ADDR,(uint8*)(&user_basic_infor.sn),sizeof(user_basic_infor.sn));//读数据到flash变量区
      {
				 uint32 val_temp[5]={0};
//			  sscanf(user_basic_infor.sn,"%15[^0-9]%02x%02x%02x%02x%02x",(char*)(&ptr),	
				 sscanf(user_basic_infor.sn,"%15[^0,],%02x%02x%02x%02x%02x",(char*)(&ptr),	
				&val_temp[4],
				&val_temp[3],
				&val_temp[2],
				&val_temp[1],
        &val_temp[0]			
				);
				{
					uint8 i=0;
					for(i=0;i<5;i++)
					{
					  user_basic_infor.sn_can[i] = val_temp[i];
					}
				}
				
				memset(ptr,0,sizeof(ptr));
			}	
//      delay_ms(200);			
			
			user_read_flash_buff( SN_PN_INFOR_ADDR+30,(uint8*)(&user_basic_infor.pn),sizeof(user_basic_infor.pn));//读数据到flash变量区
      {
				 uint32 val_temp[8]={0};
//			  sscanf(user_basic_infor.pn,"%15[^0-9]%01x%02x%02x%02x%02x%02x%02x%02x",(char*)(&ptr),		
				 sscanf(user_basic_infor.pn,"%15[^,],%1x%02x%02x%02x%02x%02x%02x%02x",(char*)(&ptr),	
				&val_temp[7],
				&val_temp[6],
				&val_temp[5],
				&val_temp[4],
        &val_temp[3],	
				&val_temp[2],
				&val_temp[1],
        &val_temp[0]						
				);
 
				val_temp[7] = val_temp[7]|0xf0;
				
				{
					uint8 i=0;
					for(i=0;i<8;i++)
					{
					  user_basic_infor.pn_can[i] = val_temp[i];
					}
				}
				memset(ptr,0,sizeof(ptr));
			}	
	 
      {
				uint32 val_temp[4]={0};
			  user_basic_infor.app_ver = user_ver_std;			
//			  sscanf(user_basic_infor.app_ver,"%15[^0-9]%d.%d.%d.%d",(char*)(&ptr),
          sscanf(user_basic_infor.app_ver,"APPINFO,V%d.%d.%d.%d",					
        &val_temp[0],
        &val_temp[1],
        &val_temp[2],
        &val_temp[3]);	
				
				{
					uint8 i=0;
					for(i=0;i<4;i++)
					{
					  user_basic_infor.app_ver_can[i] = val_temp[i];
					}
				}
 				memset(ptr,0,sizeof(ptr));   			
			}
 
	}
	/*************************************************
	* Funcname      :  
	* Version       :  
	* Describtion   : 初始化基本本配置信息，这些信息是要求保存在flash中的，从flash中读取数据到User_Flash_Stor_Infor
	* Creator				:
	* Date					:
	********************************************/
	void User_Flash_Stor_Infor_Init(void)
	{
			user_read_flash_buff( FLASH_STOR_INFOR_ADDR	,(uint8*)(&user_flash_moter_pra),sizeof(user_flash_moter_pra));//读数据到flash变量区

			if(user_flash_moter_pra.flash_empty_flag == 0x5a)//flash已经存储有内容
			{
				
				user_moter_pra = user_flash_moter_pra ;	
			}
			else //如果flash还没有存储控制板基本信息，那么将默认信息写入flash
			{
				user_moter_pra.flash_empty_flag  = 0x5a;//flash存储了内容，做标记
				user_flash_moter_pra = user_moter_pra ;			
				user_write_Flash_buffer(FLASH_STOR_INFOR_ADDR	,(uint8*)(&user_flash_moter_pra ),sizeof(user_flash_moter_pra ));//写flash
			}

	}

		void User_Flash_Stor_Infor_write(void)
		{
			user_flash_moter_pra = user_moter_pra ;		
			user_write_Flash_buffer(FLASH_STOR_INFOR_ADDR	,(uint8*)(&user_flash_moter_pra ),sizeof(user_flash_moter_pra ));//写flash
		}
		
		/************************************************************************************************
* Function Name  :  
* Description    :  
* Input          :  
* Output         :  
* Return         :  
**************************************************************************************************/
void User_sensor_Pra_Init(void)
{
	//user_moter_pra.flash_empty_flag =0x00;
//	user_moter_pra.AN_Val[0][0]=0x01;
		uint8 i,j;
		for(i=0;i<10;i++)
		{
			for(j=0;j<6;j++)
			{
			
				user_moter_pra.AN_Val[i][j]=0;
			}
		
		}
//		user_moter_pra.AN_Val[1][0]=;//三点悬挂
//		user_moter_pra.AN_Val[1][1]=;
//		user_moter_pra.AN_Val[1][2]=;
//		
//	user_moter_pra.AN_Val[2][2]=0x03;
//	user_moter_pra.AN_Val[3][3]=0x04;
//	user_moter_pra.AN_Val[4][4]=0x05;
	

}
/*********************************软复位***************/
/*******************************************************************************
* Function Name  :  
* Description    : 软件复位
* Input          :
* Output         :  
* Return         : 
*******************************************************************************/
