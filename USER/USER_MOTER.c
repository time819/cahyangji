/*************************************************
* Filename      :  
* Version       :  
* Describtion   : 
* Creator				:
* Date					:
********************************************/
#include "USER_MOTER.h"
#include "USER_DATA_TYPE.h"
u16   user_mot_sp_level[2][3]={

	{500,300,200},
	{500,400,400}
};

//数据超出范围进行处理
int m_thrd(int* val,int val_c)
{
  if(val_c>32128)  //安装是正向速度，把速度范围限制在0-正向最大。32128 - 64250
	{
	 if(*val>64250)
	 {
	   *val=64250;
	 }
	 else if(*val<32128)
	 {
	   *val=32128;
	 }
	}
  else if(val_c<32128)  //安装是正向速度，把速度范围限制在0-反向最大。32128 - 0
	{
	 if(*val< 0)
	 {
	   *val=0;
	 }
	 else if(*val>32128)
	 {
	   *val=32128;
	 }
	}
  return 0;
}
