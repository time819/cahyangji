/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:
********************************************/
#ifndef  _USER_MOTER_H
#define  _USER_MOTER_H

#include "USER_DATA_TYPE.h"
#define MOT1_THD  0 
#define MOT1_SENS 30

#define MOT2_THD  0 
#define MOT2_SENS 60

#define SENSOR1_THD  120 //行走手柄
#define SENSOR1_SENS 15


#define SENSOR2_THD  120 //悬挂手柄，收割机用不到
#define SENSOR2_SENS 30

#define SENSOR3_THD  100 //转向手柄
#define SENSOR3_SENS 30  // 这个数据暂时用不到

//#define MOT1_SP1  500
//#define MOT1_SP2  400
//#define MOT1_SP3  400

//#define MOT2_SP1  500
//#define MOT2_SP2  400
//#define MOT2_SP3  400

extern u16   user_mot_sp_level[2][3];

extern int m_thrd(int* val,int val_c);
#endif


