#ifndef __SIMPLEQUEUE_H
#define __SIMPLEQUEUE_H

#include "main.h"

#define MaxSize 1024	//定义队列中元素的最大个数

typedef unsigned char ElemType;

typedef struct{
    ElemType data[MaxSize];		//存放队列元素
    int front;		//队头指针
    int rear;		//队尾指针
}SeqQueue;

enum{
	false =0,
	true  =1
};


void InitQueue(void );
ElemType QueueEmpty(void);
int QueueNum(void);
void QueueClear(void);
ElemType EnQueue(ElemType *x);
ElemType DeQueue(ElemType *x);

#endif
