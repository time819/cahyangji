/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:
********************************************/
#ifndef _USER_FLASH_H_
#define _USER_FLASH_H_

#include "USER_DATA_TYPE.h"
#include "stdio.h"	
#include "LSCanUpgrade.h"

#define FLASH_STOR_INFOR_ADDR 0x8018000
#define BOOT_VER_INFOR_ADDR   0x800fc00
#define SN_PN_INFOR_ADDR      0x8010000
#define FLASH_STOR_INFOR_ADDR 0x8018000

extern sn_pn_t user_sn_pn ;
extern basic_infor_t user_basic_infor ;
extern  char * user_ver;
extern  char * user_ver_can;


extern void writeFlashTest(void);
extern void user_write_Flash_buffer(uint32 addr ,uint8 *buffer,uint16 buffer_size);
extern void user_write_Flash_buffer_1(uint32 addr,uint8 *buffer, uint16 buffer_size,uint8 page);
extern void user_read_flash_buff(uint32 addr ,uint8 *buffer,uint16 buffer_size);
extern void User_Flash_Stor_Infor_Init(void);
extern void User_Flash_Stor_Infor_write(void);
extern void User_sensor_Pra_Init(void);

extern void user_basic_infor_init(void);

#endif


