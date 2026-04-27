/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:
********************************************/
#ifndef _TYPE_DEF_H
#define _TYPE_DEF_H


typedef unsigned char  uint8;    //无符号8位整形变量    
typedef unsigned char  u8;    //无符号8位整形变量 
typedef signed   char  int8;     //有符号8位整形变量               
typedef unsigned short uint16;   //无符号16位整形变量                
typedef unsigned short u16;   //无符号16位整形变量 
typedef signed   short int16;    //有符号16位整形变量   

typedef unsigned int   uint32;   //无符号32位整形变量               
typedef unsigned int    u32;
typedef signed   int   int32;    //有符号32位整形变量               
typedef float          fp32;     //单精度浮点数(32位)               
typedef double         fp64;     //双精度浮点数(64位)             
typedef  void (*pFunction)(void);//定义一个函数指针

#define NULL 0


#ifndef _STRUCT_ME_
#define  _STRUCT_ME_
#pragma pack(1)
	struct me
	{
		uint8 DataPage          : 1;
		uint8 Res               : 1;
		uint8 Priority          : 3;
		uint8 PDUFormat_Top     : 3;
		uint8 PDUFormat;
		uint8 PDUSpecific;
		uint8 SourceAddress;
		//uint8 DataLength        : 4;
		//uint8 RTR               : 4;//这几位总是为0
		//uint8 Data[8];
	};
#endif	


#ifndef _J1939_MESSAGE_UNION_
#define  _J1939_MESSAGE_UNION_
typedef union J1939_MESSAGE_UNION
{
	struct me Mxe;
  uint8  Array[12];
}j1939_msg_t;
#endif


#ifndef _USER_PRO_T_
#define _USER_PRO_T_
typedef struct {
uint16 pgn;
uint8 (*pfun)(j1939_msg_t * RxMessage);
}user_pro_func_t;
#endif

#ifndef _MOTER_PRA_STRUCT_
#define _MOTER_PRA_STRUCT_
#define AN_VAL_MAX_NUM 6//每个角度传感器，需要存储的最大数据
#define AN_MOT_MAX_NUM 10//包括5个电机的5个角度传感器，其他4个角度传感器
typedef struct {

	u16 AN_Val[AN_MOT_MAX_NUM][AN_VAL_MAX_NUM];
	u16	AN_Val_Min[AN_MOT_MAX_NUM];
	u16	AN_Val_Max[AN_MOT_MAX_NUM];
//	int16 AN_Val_OffSet[AN_MOT_MAX_NUM][AN_VAL_MAX_NUM];
//	int16 OffSet_Ratio[AN_MOT_MAX_NUM][AN_VAL_MAX_NUM][2];//边沿比例
	u8  model_type[8];//主机类型 行走控制方式 升降控制方式  作业控制,[7]用来配置有无粮筒,0带粮筒，1不带粮筒
	
	u8 flash_empty_flag;//有无初始数据
	uint16 remot_id;
	uint8 remot_chn;
	u8 flash_type_flag;//车的类型
	u16 DA_Val[3];//用于行走DA输出，包括后退 中位 前进,对于收割机 后退不管了，中位当做最小油门

	u16  moter_spd_level[5][3];//5个电机的速度等级，0-3字节分为3等，从粗到精，用于精确控制,4字节设置电机余量,0表示忽略
  u16 moter_sensor[ AN_MOT_MAX_NUM][3];//5个电机，2个手柄传感器的字节0灵敏度、字节1中位裕量;值为0表示忽略
  
  int speed_base;   //基本速度
//  int speed_f[14];  //相差档位对应的速度偏差，相对基本速度；  用于追赶
//  int speed_b[14];  //相差档位对应的速度偏差，相对基本速度； 用于等待
//  uint16 ang_m[27]; //原车秧台角度传感器
//	uint16 ang_s[27]; //秧板角度传感器
  int speed_f[60];  //相差档位对应的速度偏差，相对基本速度；  用于追赶
  int speed_b[60];  //相差档位对应的速度偏差，相对基本速度； 用于等待
  uint16 ang_m[60]; //原车秧台角度传感器
	uint16 ang_s[60]; //秧板角度传感器
	uint16 ang_min_max[4];//秧台、样板角度传感器的最小最大值
	int spd_min_max[4];//追或者等速度的最小最大值
  int speed_init;
	uint16	AN_reset_data;   //秧板复位到推苗位置AD值
	uint16  yangban_xuanzhe; //样板列数选择电机标定
}moter_pra_struct_t;
#endif

#ifndef _MID_THD_T_
#define _MID_THD_T_  //中位边缘的绝对值
typedef struct{	
	int val_a; 
	int val_b;	
 
}mid_thd_t;

#endif



#ifndef _USER_STATE_T_
#define _USER_STATE_T_
typedef struct {
	uint8 test_opr_mode;
	volatile uint8  study_mode;
	volatile uint8  manul_auto;
//	volatile uint8  auto_turn_manul_4sec;//退出无人后4秒标志
//	volatile uint8  barrier;//1,有障碍物，0无障碍物
//	volatile uint8  radar_on_0ff;//1,关，0开，默认雷达是开的
//	volatile uint8 	dirc;//当前车的方向
//	volatile uint16  current_speed;//当前速度
//	volatile uint8 speed_rec;//收到下发的速度标识为1；2.5秒内收不到为0
//	volatile uint16 elc_accelerator;//电子油门
	volatile uint8   manul_aotu_turn;//人工和自动相互转换，00忽略，2人工转无人；1无人转人工

	volatile uint8 pad_heart;
  
	volatile int  ang_m_num;//当前秧台所在位置
  volatile uint8 ang_m_dirc;//当前秧台运行方向   hh  1左2右
  volatile int  ang_s_num;//当前秧板所在位置
  volatile uint8 ang_s_dirc;//当前秧板运行方向
	
  volatile int8 fit_mode;//	0,样板秧台动作不需要协调一致；1需要协调一致 3   hh 2复位；3推苗时不动作
	volatile int  speed_cur;

  volatile uint8  YangXiang_high; //hh 1升起；2落下
  volatile uint8  high_state;
  volatile uint8  rice1_state;    //上苗状态，1：推苗完成 2：正在推苗中 3：样板已经放下 4： 5：不缺苗，等待下次推苗
  volatile uint8  rice2_state;
  volatile uint8  rice3_state;
  volatile uint8  rice4_state;
 
  volatile uint8  less_yangxiang; 
  volatile uint8  huanhang_sta;  //换行执行 0复位，1伸长(单列)，2缩短(双列)
	volatile uint8  lieshu_jilu;   //先缺苗的列数记录
	
	volatile uint8  stop_sta;
}user_state_t;
#endif


#ifndef _USER_MOTER_T_
#define _USER_MOTER_T_
typedef struct {
	volatile int32 target_value;
	volatile uint8 min_thrd_flag;
	volatile uint8 max_thrd_flag;
	uint8 reverse_direction;//0,电机伸长分离，缩回是结合；
	volatile uint8 no_change_err;
	volatile uint8 manul_change_elec;//手改电标志
	volatile uint8 lock_s;//电机是否是自锁
	volatile uint8 cmd_from_can_remote_sensor;//电机指令来自can 1；remote 2；sensor 3
	
}user_moter_t;
#endif


//#ifndef _USER_BACK_SPEND_T_H_
//#define _USER_BACK_SPEND_T_H_
//typedef struct {
//volatile uint8 pto;//pto动作
//volatile uint8 hight;//悬挂高度
//}user_back_pend_ctr_t;
//#endif


#ifndef _USER_HARVESTER_STATE_T_H_
#define _USER_HARVESTER_STATE_T_H_ 
typedef struct {

	volatile uint8 granary_state;//粮仓状态 00，不使用
	volatile uint8 liangtong_motive_state;//粮筒驱动力
	volatile uint8 cluth_thresher_state;	//脱粒
	volatile uint8 cluth_harvest_state;	//收割台00，不使用，就是因为11783反编译器
	volatile uint8 cluth_unloadt_state;	//卸载
	volatile int32 getai_pos_state;	//割台运动到位置标志。
	volatile uint8 elec_engin_start_state;//是否电子启动车，00，不是；01是电子启动
	volatile uint32 pra_all_set_flag_state;//00,所有必须参数未全部设置；bit0=1，收割离合已经设置；

	volatile uint8 dec_fix_state[AN_MOT_MAX_NUM];//电机/角度传感器安装状态，设置时，位置1最小时为0；位置1最大时为1；位置1和位置2相等为2；位置1和位置2都是0，为3
//	volatile uint8 motor2_fix_state;
//	volatile uint8 motor3_fix_state;
//	volatile uint8 motor4_fix_state;
//	volatile uint8 motor5_fix_state;
//	volatile uint8 angle6_fix_state;//角度传感器安装状态，设置时，位置1最小时为0；位置1最大时为1；位置1和位置2相等为2；位置1和位置2都是0，为3
//	volatile uint8 angle7_fix_state;

}user_dec_state_t;
#endif

#ifndef _SN_PN 
#define _SN_PN
typedef struct{
	char sn[30];
	char pn[30];
}sn_pn_t;
#endif

#ifndef _BASIC_INFOR
#define _BASIC_INFOR
typedef struct{
	char pn[30];
	char sn[30];
	char boot_ver[30];
	char *app_ver;
  uint8 pn_can[8];	
	uint8 sn_can[5];
	uint8 boot_ver_can[4];	
	uint8 app_ver_can[4];	
}basic_infor_t;
#endif


#endif


