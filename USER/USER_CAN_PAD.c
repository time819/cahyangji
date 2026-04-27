/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:
********************************************/

#include "USER_CAN_PAD.h"
#include "USER_PRO.h"
#include "USER_WIRE_LESS.h"
/*************************************************
* Funcname      :
* Pra           : can面板控制
* Describtion   : 最多只有一个按键有效
BYTE[0]:0 开始；
BYTE[0]:1 停车；
BYTE[0]:2 左转；
BYTE[0]:3 右转；
BYTE[1]:0 农具升；
BYTE[1]:1 农具降；
BYTE[1]:2 加速；
BYTE[1]:3 减速；
************************************************/
uint8 user_pad_touch_key_ctr(j1939_msg_t * RxMessage)
{
	uint32 key_value =0x0000;//默认全零
	uint16 can_pad_val=0x0000;
	//解析can信息
	uint32 rx_id = 0x00;
	rx_id = rx_id |((uint32)RxMessage->Array[0]<<24);
	rx_id = rx_id |((uint32)RxMessage->Array[1]<<16);
	rx_id = rx_id |((uint32)RxMessage->Array[2]<<8);
	rx_id = rx_id |((uint32)RxMessage->Array[3]<<0);
	can_pad_val = (((uint32)RxMessage->Array[5])<<8)|RxMessage->Array[4];
  if(rx_id ==0x00000007)
	{
		if((can_pad_val&0x01)==0x01)
		{
			key_value=key_value|(0x00000001<<0) ;//开始
		}
		else if((can_pad_val&0x02)==0x02)
		{
			key_value=key_value|(0x00000001<<12);//停车
		}
		else if((can_pad_val&0x04)==0x04)
		{
			key_value=key_value|(0x00000001<<6);//左转
		}	
		else if((can_pad_val&0x08)==0x08)
		{
			key_value=key_value|(0x00000001<<18);//右转
		}	
		else 	if(((can_pad_val>>8)&0x01)==0x01)
		{
			key_value=key_value|(0x00000001<<4);//农具升
		}
		else if(((can_pad_val>>8)&0x02)==0x02)
		{
			key_value=key_value|(0x00000001<<16);//农具降
		}
		else if(((can_pad_val>>8)&0x04)==0x04)
		{
				key_value=key_value|(0x00000001<<1);//加速
		}	
		else if(((can_pad_val>>8)&0x08)==0x08)
		{
				key_value=key_value|(0x00000001<<14);//减速
		}
		
		if(key_value!=0x00)
		{
//      user_key_val_Pro(&key_value);			
		}

	}
	return 0;
}

