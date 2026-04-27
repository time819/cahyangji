#include "SimpleQueue.h"

static SeqQueue q;

// 初始化队列
void InitQueue(void )
{
    q.front = q.rear = 0;
}

// 判断队列是否为空
ElemType QueueEmpty(void)
{
    if (q.rear == q.front)	//队空条件
        return true;
    else
        return false;
}

// 入队
ElemType EnQueue(ElemType *x)
{
    if ((q.rear+1) % MaxSize == q.front)
        return false;		//队列满则报错

    q.data[q.rear] = *x;		//将x插入队尾
    q.rear = (q.rear + 1) % MaxSize;    //队尾指针后移
    return true;
}

// 出队
ElemType DeQueue(ElemType *x)
{
    if (q.rear == q.front)
        return false;	//队空则报错

    *x = q.data[q.front];

    q.front = (q.front + 1) % MaxSize; //队头指针后移
    return true;
}

// 获取队头元素
ElemType GetHead(ElemType *x)
{
    int i = 0;
    if (q.rear == q.front)
        return false;	//队空则报错

    for( i = 0 ; i < 8; i++)
    {
        *x = q.data[q.front];
    }

    return true;
}

// 队列中元素的个数
int QueueNum(void)
{
    return (q.rear - q.front + MaxSize) % MaxSize;
}

// 清空队列中得所有元素
void QueueClear(void)
{
		while(!QueueEmpty())
		{
				ElemType c;
				DeQueue(&c);
		}
}

