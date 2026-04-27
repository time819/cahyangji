/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:
********************************************/
#include "USER_BOOT_MISC.h"
#include "USER_MISC.h"
#include "USER_MISC.h"
#include "stm32f7xx_hal.h"
#include "stm32f767xx.h"
#include "tim.h"
#include "usart.h"
#include "stm32f7xx_hal_flash.h"
#include "stm32f7xx_hal_flash_ex.h"
#include "SimpleQueue.h"
#include "LSCanUpgrade.h"
pFunction Jump_To_Application;
uint32_t JumpAddress;//入口地址
uint8 can_uart = 0;//串口0，can口1


/******************************************************************************
  * @函数名称   IsIapBoot
  * @函数说明   启动内 50ms 检测串口是否收到命令，进而进入IAP模式
  * @输入参数
  * @输出参数
  * @返回参数   返回 0 时说明检测到指定 字符
  * @函数备注   添加时间 2014-01-17
******************************************************************************/
uint8_t IsIapBoot(void)	 //uint8_t
{
	uint8_t key = 0;
	delay_ms(30);
	SerialKeyPressed( (uint8_t*)&key);

	if( (char)key == '\b')//如果收到制定字符
	{
//		if(can_uart==0)
//		{
//		  EnableCanBoot = false;//串口升级使能
//		}
//		else if(can_uart==1)
//		{
//		  EnableCanBoot = true;//can口升级使能
//		}
		
    QueueClear(); //CAN 队列清除
		return 1;		
	}
	else 
	{
	  return 0;	
	}
		
}


/******************************************************************************
  * @函数名称   
  * @函数说明   清除 初始化中断
  * @输入参数
  * @输出参数
  * @返回参数   
  * @函数备注   
******************************************************************************/
void NVIC_DeInit(void)
{
  u32 index = 0;
  
  NVIC->ICER[0] = 0xFFFFFFFF;
  NVIC->ICER[1] = 0x000007FF;
  NVIC->ICPR[0] = 0xFFFFFFFF;
  NVIC->ICPR[1] = 0x000007FF;
  
  for(index = 0; index < 0x0B; index++)
  {
     NVIC->IP[index] = 0x00000000 ;
  } 
}

/*******************************************************************************
  * @函数名称	Int2Str
  * @函数说明   整形数据转到字符串
  * @输入参数   intnum:数据
  * @输出参数   str：转换为的字符串
  * @返回参数   无
*******************************************************************************/
void Int2Str(uint8_t* str, int32_t intnum)
{
    uint32_t i, Div = 1000000000, j = 0, Status = 0;

    for (i = 0; i < 10; i++)
    {
        str[j++] = (intnum / Div) + 48;

        intnum = intnum % Div;
        Div /= 10;
        if ((str[j-1] == '0') & (Status == 0))
        {
            j = 0;
        }
        else
        {
            Status++;
        }
    }
}

/*******************************************************************************
  * @函数名称	Int2Str
  * @函数说明   字符串转到数据
  * @输入参数   inputstr:需转换的字符串
  * @输出参数   intnum：转好的数据
  * @返回参数   转换结果
                1：正确
                0：错误
*******************************************************************************/
uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum)
{
    uint32_t i = 0, res = 0;
    uint32_t val = 0;

    if (inputstr[0] == '0' && (inputstr[1] == 'x' || inputstr[1] == 'X'))
    {
        if (inputstr[2] == '\0')
        {
            return 0;
        }
        for (i = 2; i < 11; i++)
        {
            if (inputstr[i] == '\0')
            {
                *intnum = val;
                //返回1
                res = 1;
                break;
            }
            if (ISVALIDHEX(inputstr[i]))
            {
                val = (val << 4) + CONVERTHEX(inputstr[i]);
            }
            else
            {
                //无效输入返回0
                res = 0;
                break;
            }
        }

        if (i >= 11)
        {
            res = 0;
        }
    }
    else//最多10为2输入
    {
        for (i = 0; i < 11; i++)
        {
            if (inputstr[i] == '\0')
            {
                *intnum = val;
                //返回1
                res = 1;
                break;
            }
            else if ((inputstr[i] == 'k' || inputstr[i] == 'K') && (i > 0))
            {
                val = val << 10;
                *intnum = val;
                res = 1;
                break;
            }
            else if ((inputstr[i] == 'm' || inputstr[i] == 'M') && (i > 0))
            {
                val = val << 20;
                *intnum = val;
                res = 1;
                break;
            }
            else if (ISVALIDDEC(inputstr[i]))
            {
                val = val * 10 + CONVERTDEC(inputstr[i]);
            }
            else
            {
                //无效输入返回0
                res = 0;
                break;
            }
        }
        //超过10位无效，返回0
        if (i >= 11)
        {
            res = 0;
        }
    }

    return res;
}

/*******************************************************************************
  * @函数名称	Int2Str
  * @函数说明   字符串转到数据
  * @输入参数   inputstr:需转换的字符串
  * @输出参数   intnum：转好的数据
  * @返回参数   转换结果
                1：正确
                0：错误
*******************************************************************************/
/**
  * @brief  Get an integer from the HyperTerminal
  * @param  num: The inetger
  * @retval 1: Correct
  *         0: Error
  */
uint32_t GetIntegerInput(int32_t * num)
{
    uint8_t inputstr[16];

    while (1)
    {
        GetInputString(inputstr);
        if (inputstr[0] == '\0') continue;
        if ((inputstr[0] == 'a' || inputstr[0] == 'A') && inputstr[1] == '\0')
        {
            SerialPutString("User Cancelled \r\n");
            return 0;
        }

        if (Str2Int(inputstr, num) == 0)
        {
            SerialPutString("Error, Input again: \r\n");
        }
        else
        {
            return 1;
        }
    }
}

/*******************************************************************************
  * @函数名称	SerialKeyPressed
  * @函数说明   测试超级终端是否有按键按下
  * @输入参数   key:按键
  * @输出参数   无
  * @返回参数   1：正确
                0：错误
*******************************************************************************/
uint32_t SerialKeyPressed(uint8_t *key2)
{
	uint8_t  Judgeret=0;
 
//    if ( LL_USART_IsActiveFlag_RXNE(UART7) != RESET)//，优先监测 串口不为空
	 if(LL_USART_IsActiveFlag_RXNE(UART7) != RESET && EnableCanBoot==false)
    {
       LL_USART_ClearFlag_PE(UART7) ;
			 LL_USART_ClearFlag_FE(UART7) ;
			LL_USART_ClearFlag_NE(UART7) ;
			LL_USART_ClearFlag_ORE(UART7) ;
			LL_USART_ClearFlag_IDLE(UART7) ;
//			LL_USART_ClearFlag_TC(UART7) ;
			LL_USART_ClearFlag_LBD(UART7) ;
			LL_USART_ClearFlag_nCTS(UART7) ;
			LL_USART_ClearFlag_RTO(UART7) ;
			LL_USART_ClearFlag_EOB(UART7) ;
			LL_USART_ClearFlag_CM(UART7) ;
			LL_USART_ClearFlag_WKUP(UART7) ;
			*key2 = LL_USART_ReceiveData8(UART7);
//			EnableCanBoot = false;//串口升级使能
			Judgeret=1;
			can_uart = 0;
    }
//    else if (QueueEmpty()==false)//队列不为空
		
		if(QueueEmpty()==false||Judgeret==1)
    {
       CANDataToYmodem(key2);
			 can_uart = 1;
//			 EnableCanBoot = true;//can口升级使能
			  return 1;
    }
		else
		{
		  return 0;		
		}
//		return 0;
 
}

/*******************************************************************************
  * @函数名称	GetKey
  * @函数说明   通过超级中断回去键码
  * @输入参数   无
  * @输出参数   无
  * @返回参数   按下的键码
*******************************************************************************/
uint8_t GetKey(void)
{
     uint8_t key1 = 0;

    //等待按键按下
    while (1)
    {
			if(SerialKeyPressed(&key1) )
			break;
    }
    
		return key1;

}

/*******************************************************************************
  * @函数名称	SerialPutChar
  * @函数说明   串口发送一个字符
  * @输入参数   C:需发送的字符
  * @输出参数   i无
  * @返回参数   无
*******************************************************************************/
void SerialPutChar(uint8_t c)
{
			while (!LL_USART_IsActiveFlag_TXE(UART7));
			LL_USART_TransmitData8(UART7, c);
}

/*******************************************************************************
  * @函数名称	SerialPutChar
  * @函数说明   串口发送一个字符串
  * @输入参数   *s:需发送的字符串
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
void Serial_PutString(uint8_t *s)
{
//	   if(EnableCanBoot)
		 {
	     CANUPG_Send_Msg(s,strlen((char *)s));//can升级		 
		 }
//		 else
     {
				while (*s != '\0')
				{
					SerialPutChar(*s);
					s++;
				}		 
		 }
}


/*******************************************************************************
  * @函数名称	GetInputString
  * @函数说明   从串口获取一个字符串
  * @输入参数   *s:存字符串的地址
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
void GetInputString (uint8_t * buffP)
{
    uint32_t bytes_read = 0;
    uint8_t c = 0;
    do
    {
        c = GetKey();
        if (c == '\r')
            break;
        if (c == '\b')// Backspace 按键  
        {
            if (bytes_read > 0)
            {
                SerialPutString("\b \b");
                bytes_read --;
            }
            continue;
        }
        if (bytes_read >= CMD_STRING_SIZE )
        {
            SerialPutString("Command string size overflow\r\n");
            bytes_read = 0;
            continue;
        }
        if (c >= 0x20 && c <= 0x7E)
        {
            buffP[bytes_read++] = c;
            SerialPutChar(c);
        }
    }
    while (1);
    SerialPutString(("\n\r"));
    buffP[bytes_read] = '\0';
}

/*******************************************************************************
  * @函数名称	FLASH_PagesMask
  * @函数说明   计算Falsh页
  * @输入参数   Size:文件长度
  * @输出参数   无
  * @返回参数   页的数量
*******************************************************************************/
//uint32_t FLASH_PagesMask(__IO uint32_t Size)
//{
//    uint32_t pagenumber = 0x0;
//    uint32_t size = Size;

//    if ((size % PAGE_SIZE) != 0)
//    {
//        pagenumber = (size / PAGE_SIZE) + 1;
//    }
//    else
//    {
//        pagenumber = size / PAGE_SIZE;
//    }
//    return pagenumber;

//}

/*******************************************************************************
  * @函数名称	FLASH_DisableWriteProtectionPages
  * @函数说明   接触Flash写保护
  * @输入参数   无
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
//void FLASH_DisableWriteProtectionPages(void)
//{
//    uint32_t useroptionbyte = 0, WRPR = 0;
//    uint16_t var1 = OB_IWDG_SW, var2 = OB_STOP_NoRST, var3 = OB_STDBY_NoRST;
//    FLASH_Status status = FLASH_BUSY;

//    WRPR = FLASH_GetWriteProtectionOptionByte();

//    //测试是否写保护
//    if ((WRPR & UserMemoryMask) != UserMemoryMask)
//    {
//        useroptionbyte = FLASH_GetUserOptionByte();

//        UserMemoryMask |= WRPR;

//        status = FLASH_EraseOptionBytes();

//        if (UserMemoryMask != 0xFFFFFFFF)
//        {
//            status = FLASH_EnableWriteProtection((uint32_t)~UserMemoryMask);
//        }
//        //用处选项字是否有编程
//        if ((useroptionbyte & 0x07) != 0x07)
//        {
//            //重新保存选项字
//            if ((useroptionbyte & 0x01) == 0x0)
//            {
//                var1 = OB_IWDG_HW;
//            }
//            if ((useroptionbyte & 0x02) == 0x0)
//            {
//                var2 = OB_STOP_RST;
//            }
//            if ((useroptionbyte & 0x04) == 0x0)
//            {
//                var3 = OB_STDBY_RST;
//            }

//            FLASH_UserOptionByteConfig(var1, var2, var3);
//        }

//        if (status == FLASH_COMPLETE)
//        {
//            SerialPutString("Write Protection disabled...\r\n");

//            SerialPutString("...and a System Reset will be generated to re-load the new option bytes\r\n");
//            //系统复位重新加载选项字
//            NVIC_SystemReset();
//        }
//        else
//        {
//            SerialPutString("Error: Flash write unprotection failed...\r\n");
//        }
//    }
//    else
//    {
//        SerialPutString("Flash memory not write protected\r\n");
//    }
//}

/*******************************************************************************
  * @函数名称	Main_Menu
  * @函数说明   显示菜单栏在超级终端
  * @输入参数   无
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
void Main_Menu(void)
{
    uint8_t key = 0;


    while (1)
    {
//        SerialPutString("\r\n================== Main Menu ============================\r\n\n");
//        SerialPutString("Download Image To the STM32F767ZG Internal Flash ------- 1\r\n\n");
//        SerialPutString("Upload Image From the STM32F767ZG Internal Flash ------- 2\r\n\n");
//        SerialPutString("Execute The New Program ------------------------------ 3\r\n\n");
//        SerialPutString("==========================================================\r\n\n");
       SendMenuInfoFctn();
  			key = GetKey();
        if (key == 0x31)  // '1'
        {
            //下载程序
            SerialDownload();
        }
        else if (key == 0x32)  // '2'
        {
            //上传程序
//            SerialUpload();
        }
        else if (key == 0x33)  // '3'
        {
            SerialPutString("Execute user Program\r\n");
            User_Soft_Reset();	  
        }
//        else if ((key == 0x34) && (FlashProtection == 1))
//        {
//            //解除写保护
//            FLASH_DisableWriteProtectionPages();
//        }
        else if(0)//2014-01-16 去掉显示其他按键
        {
            if (FlashProtection == 0)
            {
                SerialPutString("Invalid Number ! ==> The number should be either 1, 2 or 3\r");
            }
            else
            {
                SerialPutString("Invalid Number ! ==> The number should be either 1, 2, 3 or 4\r");
            }
        }
    }
}


/******************************************************************************
  * @函数名称   CloseIQHard
  * @函数说明   IAP 关掉中断以及硬件外设
  * @输入参数
  * @输出参数
  * @返回参数   
  * @函数备注   添加时间 2014-01-17
******************************************************************************/

void CloseIQHard(void)
{
//	NVIC_SETFAULTMASK();  //关闭总中断

	//NVIC_SETFAULTMASK();  //关闭总中断 
	//关IO
	  __HAL_RCC_GPIOH_CLK_DISABLE();
  __HAL_RCC_GPIOE_CLK_DISABLE();
  __HAL_RCC_GPIOA_CLK_DISABLE();

	__disable_irq();   // 关闭总中断
	//关中断
}

/******************************************************************************
  * @函数名称    
  * @函数说明    擦除sector
  * @输入参数
  * @输出参数
  * @返回参数   
  * @函数备注   添加时间 2014-01-17
******************************************************************************/
void user_flash_sector_erase(void)
{
			uint32_t PageError = 0;
			FLASH_EraseInitTypeDef EraseInitStruct;

			__disable_irq(); //关闭总中断

	//1、解锁FLASH
		HAL_FLASH_Unlock();

		//2、擦除FLASH

		/* Fill EraseInit structure*/
		EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
		EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_1;
		EraseInitStruct.Sector        = FLASH_SECTOR;
		EraseInitStruct.NbSectors     = 2;

		while(1)
		{
			if(HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) == HAL_OK)
			{
				break;
			}
			
			FLASH_WaitForLastOperation(0xffffffff);
			 delay_ms(100);	
		}

		FLASH_WaitForLastOperation(0xffffffff);
//		user_delay_ms(10);	
		
		//4、锁住FLASH
		HAL_FLASH_Lock();
		
		__enable_irq();//打开总中断

}

/******************************************************************************
  * @函数名称    
  * @函数说明    擦除sector
  * @输入参数
  * @输出参数
  * @返回参数   
  * @函数备注   添加时间 2014-01-17
******************************************************************************/

HAL_StatusTypeDef user_flash_word_wr(uint32_t Address, uint64_t Data)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  uint32  timeout =0x500000;
  status = FLASH_WaitForLastOperation(timeout);
  
  if(status == HAL_OK)
  {
			assert_param(IS_FLASH_ADDRESS(Address));

			FLASH->CR &= CR_PSIZE_MASK;
			FLASH->CR |= FLASH_PSIZE_WORD;
			FLASH->CR |= FLASH_CR_PG;

			*(__IO uint32_t*)Address = Data;
					__DSB();
    status = FLASH_WaitForLastOperation(timeout);
		
    FLASH->CR &= (~FLASH_CR_PG);
  }



  return status;
}


HAL_StatusTypeDef user_flash_byte_wr(uint32_t Address, uint8 Data)
{
//  HAL_StatusTypeDef status = HAL_ERROR;
//  uint32  timeout =0x500000;
//  status = FLASH_WaitForLastOperation(timeout);
//  
//  if(status == HAL_OK)
//  {
//			assert_param(IS_FLASH_ADDRESS(Address));

//			FLASH->CR &= CR_PSIZE_MASK;
//			FLASH->CR |= FLASH_PSIZE_WORD;
//			FLASH->CR |= FLASH_CR_PG;

//			*(__IO uint32_t*)Address = Data;
//					__DSB();
//    status = FLASH_WaitForLastOperation(timeout);
//		
//    FLASH->CR &= (~FLASH_CR_PG);
//  }



//  return status;
  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));
  
  /* If the previous operation is completed, proceed to program the new data */
  FLASH->CR &= CR_PSIZE_MASK;
  FLASH->CR |= FLASH_PSIZE_BYTE;
  FLASH->CR |= FLASH_CR_PG;

  *(__IO uint8_t*)Address = Data;

  /* Data synchronous Barrier (DSB) Just after the write operation
     This will force the CPU to respect the sequence of instruction (no optimization).*/
  __DSB();
	
	return HAL_OK;
}




//app中升级bootloader 使用不到
//void user_boot(void)
//{
// if (((*(__IO uint32_t*)APP_FLASH_ADDR) & 0x2FFE0000 ) == 0x20000000)
// {
//					SerialPutString("booting\r\n\n");
//					 delay_ms(10);
//					//关闭所有外设
//					LL_USART_Disable(UART7);
//					 LL_TIM_DisableCounter(TIM3);
//					LL_TIM_DisableCounter(TIM2);
//					LL_TIM_DisableCounter(TIM1);
//						LL_TIM_DisableCounter(TIM14);
////					__disable_irq();
////	 HAL_NVIC_SystemReset(void);系统复位
//						LL_RCC_DeInit( );//关闭外设
//	 
////					user_delay_ms(10);
//					NVIC_DeInit();
////				__disable_irq();
//					//跳转至用户代码
//					JumpAddress = *(__IO uint32_t*)(APP_FLASH_ADDR + 4);
//					Jump_To_Application = (pFunction)JumpAddress;

//						/* set up MSP and switch to it */ 
//					__set_MSP(*(uint32_t*)APP_FLASH_ADDR);
//					 __set_PSP(*(uint32_t*)APP_FLASH_ADDR);
//					 __set_CONTROL(0); 

////					__disable_irq();
//					/* disable and clean up all interrupts. */ 
//					{ 
//						int i;
//						for(i = 0; i < 8; i++) 
//						{
//								 /* disable interrupts. */ 
//								NVIC->ICER[i]= 0xFFFFFFFF;//清中断标志
//								 /* clean up interrupts flags. */ 
//								NVIC->ICPR[i] = 0xFFFFFFFF; //解挂中断
//						} 
//					} 

//            Jump_To_Application();
//        }
//	else
//	{
//			SerialPutString("no user Program\r\n\n");
//	}
//}


