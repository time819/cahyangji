/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:
********************************************/
#ifndef _USER_PRO_H
#define _USER_PRO_H
#include "USER_DATA_TYPE.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#define FUNC_CAN2_MAX_NUM 5
#define FUNC_CAN1_MAX_NUM 5

#define SPEED_CTR_CMD_PGN		      0xfd43  //平板下发0x0cfd4326
#define CURVATURE_CTR_CMD_PGN		  0xAD13  //平板下发0x0cAd1326

#define MOTOR_CTR_CMD_PGN		      0xff51	//发动机启动相关指令
#define HARVESTER_CTR_CMD_PGN     0xff61  //收割机控制命令
#define MANUL_AUTOM_STATE_PGN     0xff53  //平板下发是否进入无人状态
#define ARM_CTR_CMD_PGN						0xFE42  //前悬挂

#define PRA_CFG_PGN						0xFF55  //参数配置 0x0CFF5526
#define PRA_RESP_PGN			    0xFF54  //参数查询 0x0CFF5490 


#define RADAR_STDID_PGN	   	0x55aa //雷达
#define PAD_TOUCH_KEY_PGN	  0x0000 // 按键板
#define PPM_CTR_PGN					0x1234
//#define HEART_BEART_CMD_PGN	0xfea0
#define  CAN_PAD_PGN        0xfdd6 //can面板

#define HEART_BEAT_PGN            0xF0E4     //心跳 0x0CF0E426
#define BK_CFG_PGN						    0xFFF3 //备用配置 0x18FFF326
#define BK_UPDATE_PGN						  0xFE90 //升级 0x18FE9026
#define BK_UPDATE_MODE_PGN	      0xEA90//进入升级模式0x18ea9026

#define MACHINERY_TRACTOR 				0x00//拖拉机
#define MACHINERY_TRANSPLANTER 		0x01//插秧机
#define MACHINERY_HARVESTER 			0x02//收割机
#define MACHINERY_CROP_PROTEC 		0x03//打药机

#define WORKING_CTR_1MOT		  0x00
#define WORKING_CTR_2MOT		  0x01
#define WORKING_CTR_SWITCH		0x02
#define WORKING_CTR_AN		    0x03

#define UP_DOWN_CTR_MOT		    0x00
#define UP_DOWN_CTR_SWITCH	  0x01
#define UP_DOWN_CTR_AN	      0x03

//#define ARM_CTR_CMD_PGN			0xfea4
//#define LIGHT_CTR_CMD_PGN		0xfea5

extern  float turn_table[5][21];
extern  float turn_table_AN[21];
extern  int16 turn_PWM[21];
extern   uint16 pwm_strit ;
extern   uint16 pwm_turn ;

extern uint8 Zhu_cont_data[8]; //主控发给子控数据
extern uint8 YangBang_fuwei(j1939_msg_t * RxMessage);
extern uint8 moter_id ;

extern j1939_msg_t j1939_msg_rev_can2;
extern j1939_msg_t j1939_msg_rev_can1;
extern user_pro_func_t user_can2_pro_func[FUNC_CAN2_MAX_NUM];
extern user_pro_func_t user_can1_pro_func[FUNC_CAN1_MAX_NUM];
extern moter_pra_struct_t user_moter_pra;
extern moter_pra_struct_t  user_flash_moter_pra ;
extern user_state_t user_state;
//extern user_back_pend_ctr_t user_back_pend;

extern user_moter_t user_moter1;
extern user_moter_t user_moter2;
extern user_moter_t user_moter3;
extern user_moter_t user_moter4;
extern user_moter_t user_moter5;


extern  float user_harvester_ratio;
extern volatile uint8 user_key_sta;

extern user_dec_state_t user_dec_state;
//extern user_back_pend_ctr_t user_back_pend_ctr;
extern volatile uint16 user_speed;

extern volatile uint32 YangTai_rec; 
extern uint8 YangTai_speed; 
extern uint8  speed_text1;
extern uint8  rad_text;
extern uint8  suidong_rec;

extern uint8 yangban_dir;
extern uint8 yangtai_dir;

extern uint8 yangban_wz;
extern uint8 yangtai_wz;

extern int speed_show;
extern mid_thd_t  user_mid_thd[AN_MOT_MAX_NUM];


extern void user_pend_switch(void);
extern void user_mot1_no_change_err(void);//检测到出错 熄火处理
extern uint8 user_mot1_state( volatile int  *timer_10ms);//监测是否




extern void user_state_init(user_state_t *user_state_temp );
extern uint8 user_manul_autom(j1939_msg_t * RxMessage);


extern  void user_harvest_clutch_manul_ctr(void );


extern uint8 user_heart_beat(j1939_msg_t * RxMessage);
extern uint8 user_bk_cfg(j1939_msg_t * RxMessage);

extern uint8 user_bk_update_mode(j1939_msg_t * RxMessage); 

extern void user_safe_ctr(void);
extern void user_data_init(void);

extern void user_data_check(void);
extern void user_err(uint8*num_err_temp);
extern void user_motor2_err(uint16 *num_err_temp);
extern int user_back_pend_convert(moter_pra_struct_t * moter_pra_temp,uint8 ratio);

extern  void  turn_table_init(void);
extern uint8 high_user_get(j1939_msg_t * RxMessage);
extern uint8 rice_lack1(j1939_msg_t * RxMessage);
extern uint8 rice_lack2(j1939_msg_t * RxMessage);
extern uint8 rice_lack3(j1939_msg_t * RxMessage);
extern uint8 rice_lack4(j1939_msg_t * RxMessage);


extern osThreadId_t myTask21Handle;
#endif


