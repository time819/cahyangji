/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:
********************************************/
#ifndef _USER_WIRE_LESS_H_
#define _USER_WIRE_LESS_H_
#include "USER_DATA_TYPE.h"
#include "can.h"
//E34模式
#define 	INVALID_MODE 0 
#define 	FixFreq_MODE 1 
#define 	HopFreq_MODE 2 
#define 	Config_MODE 3 
//#define 	Check_MODE  4

//遥控器 正常通讯 查询 配置
#define 	NML_MODE 0 
#define 	CFG_MODE 1 
#define 	QRY_MODE 2 


#ifndef _USER_WL_T_
#define _USER_WL_T_


/**********
struct AA{

};

typedef struct AA{

}AA1;
这种定义方式，可以在结构体中使用结构体本身
***********/

typedef struct user_wl_struct_t1 {
uint8 uart_buff_rx[12];
uint8 uart_buff_rx_empt_flag;
uint8 buff_tx[12];
uint16 id;//要下发的ID
uint16 current_id;//当前正在使用的ID
uint8 ch;//要下发的通道
uint8 current_ch;//当前正在使用的ch
uint8 state;
uint8 mode;//can的模式，查询 配置中，还是正常使用中
volatile uint8 study_on_off;//配对关闭00，配对开启01,没实际用处，先留着；	
volatile uint8 study_cmd_from;//配置指令来自can，01；来自串口00，默认来自串口
uint8 E34_mode;//配置模式，跳频模式等等
void (*Pfun_can_tx)(CAN_HandleTypeDef *hcan,uint32 extid,uint8 *TxData, uint32_t *pTxMailbox);
int (*Pfun_uart_tx)(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
int (*Pfun_E34_WR)( struct user_wl_struct_t1* user_wl_struct,uint8 rd_wr);
int (*Pfun_E34_mode_cfg)( uint8 mode);
void (*Pfun_delay_ms)(uint16 ms);		
void (*Pfun_key_pro)(uint8 *uart_rx);		
//uint8 (*Pfun_init)(struct user_wl_struct_t1 *);
}user_wl_struct_t;
#endif


extern uint8 Zhu_less_data[8];
extern user_wl_struct_t  user_wl_struct;

extern uint8 user_xor_check(uint8 * buff,uint8 len);
extern uint8 user_wl_init(user_wl_struct_t *user_wl_struct_temp);
extern int user_wl_cfg(uint8 mode);
 
extern void user_key_Pro(uint8* rx_data);
extern uint8 user_wl_pra_from_uart(user_wl_struct_t* user_wl_struct_temp,uint8* buff_uart_rx,uint8  len);
extern void user_key_val_Pro(uint8* rx_data);
extern  uint8 user_wl_pro(user_wl_struct_t* user_wl_struct_temp);
extern  uint8 user_wl_pra_from_can(user_wl_struct_t* user_wl_struct_temp,uint8* buff_can_rx);
//extern uint8 user_wl_pra_get(user_wl_struct_t* user_wl_struct_temp);
extern int user_wl_pra_RD(user_wl_struct_t* user_wl_struct_temp);
#endif


