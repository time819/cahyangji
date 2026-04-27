/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:
********************************************/
#ifndef _USER_BOOT_MISC_H_
#define  _USER_BOOT_MISC_H_
#include "USER_DATA_TYPE.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_ll_usart.h"

//配置烧写参数
	//说明：stm32f767zg,1M flash;512 sram;
	//sector[0]0x8000000 0x8007fff   32k   bootloader
	//sector[1]0x8008000 0x800ffff   32k
	//sector[2]0x8010000 0x8017fff   32k
	//sector[3]0x8018000 0x801ffff   32k
	//sector[4]0x8020000 0x803ffff   128k  app
	//sector[5]0x8040000 0x807ffff   256k
	//sector[6]0x8080000 0x80bffff   256k
	//sector[7]0x80c0000 0x80fffff   256k
#define APP_FLASH_SIZE         0x10000  //app 
#define APP_FLASH_ADDR   		 0x8000000 //app地址
#define FLASH_SECTOR        FLASH_SECTOR_0


#define CMD_STRING_SIZE       128
//计算上传文件大小 
#define FLASH_IMAGE_SIZE                   (uint32_t) (FLASH_SIZE - (ApplicationAddress - 0x08000000))

#define IS_AF(c)  ((c >= 'A') && (c <= 'F'))
#define IS_af(c)  ((c >= 'a') && (c <= 'f'))
#define IS_09(c)  ((c >= '0') && (c <= '9'))
#define ISVALIDHEX(c)  IS_AF(c) || IS_af(c) || IS_09(c)
#define ISVALIDDEC(c)  IS_09(c)
#define CONVERTDEC(c)  (c - '0')

#define CONVERTHEX_alpha(c)  (IS_AF(c) ? (c - 'A'+10) : (c - 'a'+10))
#define CONVERTHEX(c)   (IS_09(c) ? (c - '0') : CONVERTHEX_alpha(c))

#define SerialPutString(x) Serial_PutString((uint8_t*)(x))


extern void NVIC_DeInit(void);

extern pFunction Jump_To_Application;
extern uint32_t JumpAddress;//入口地址
extern uint32_t BlockNbr;
extern uint32_t UserMemoryMask ;
extern volatile uint32_t FlashProtection ;
extern uint32_t FlashDestination;



/* 函数声明 ------------------------------------------------------------------*/
void Int2Str(uint8_t* str,int32_t intnum);
uint32_t Str2Int(uint8_t *inputstr,int32_t *intnum);
uint32_t GetIntegerInput(int32_t * num);
uint32_t SerialKeyPressed(uint8_t *key);
uint8_t GetKey(void);
void SerialPutChar(uint8_t c);
void Serial_PutString(uint8_t *s);
void GetInputString(uint8_t * buffP);
uint32_t FLASH_PagesMask(__IO uint32_t Size);
void FLASH_DisableWriteProtectionPages(void);
void Main_Menu(void);
void SerialDownload(void);
void SerialUpload(void);
void CloseIQHard(void);
uint8_t IsIapBoot(void)	; //uint8_t
void user_flash_sector_erase(void);
void user_boot(void);
HAL_StatusTypeDef user_flash_word_wr(uint32_t Address, uint64_t Data);
HAL_StatusTypeDef user_flash_byte_wr(uint32_t Address, uint8 Data);
#endif


