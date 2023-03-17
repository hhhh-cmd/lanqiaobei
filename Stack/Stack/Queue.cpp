#include <stdio.h>
#include <stdlib.h>


#define OK			1
#define ERROR		0
#define MAXSIZE		100
typedef int Status;
typedef int QElemType;

/*******************顺序队列**********************/
typedef struct {
	QElemType* base;		//初始化的动态分配存储空间
	int front; 
	int rear;
}SqQueue;
 
/*初始化循环队列*/
Status InitSqQueue(SqQueue &Q)
{
	Q.base = (QElemType*)malloc(MAXSIZE * sizeof(QElemType));
	if (!Q.base) return ERROR;
	Q.front = Q.rear;
	return OK;
}

/*求循环队列长度*/
int LengthSqQueue(SqQueue Q)
{
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

/*循环队列入队*/
Status EnSqueue(SqQueue& Q, QElemType e)
{
	if ((Q.rear + 1) % MAXSIZE == Q.front) return ERROR;   //队满
	Q.base[Q.rear] = e;				   //插入元素
	Q.rear = (Q.rear + 1) % MAXSIZE;   //尾指针向后移动一位
	return OK;
}

/*循环队列出队*/
Status DeSqueue(SqQueue& Q, QElemType &e)
{
	if (Q.rear == Q.front) return ERROR;   //队空
	e = Q.base[Q.front];				   //插入元素
	Q.front = (Q.front + 1) % MAXSIZE;   //尾指针向后移动一位
	return OK;
}

/*循环队列取头元素*/
QElemType Gethead(SqQueue Q)
{
	if (Q.rear == Q.front) return ERROR;   //队空
	return Q.base[Q.front];
}

/*******************链式队列**********************/
typedef struct Qnode {
	QElemType data;
	struct Qnode* next; 
}Qnode, * QueuePtr;

typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

/*初始化链队*/ 
Status InitLinkQueue(LinkQueue& Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(Qnode));
	if (!Q.front) return ERROR;
	Q.front = Q.rear = NULL;
	return OK;
}

/*销毁链队*/
Status DestroyLinkQueue(LinkQueue& Q)
{
	while (Q.front)
	{
		Q.rear = Q.front->next;
		delete Q.front;
		Q.front = Q.rear;
	}
	return OK;
}

/*链队入队*/
Status EnLinkQueue(LinkQueue& Q, QElemType e)
{
	Qnode* p;
	p = (QueuePtr)malloc(sizeof(Qnode));
	if (!p) return ERROR;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

/*链队出队*/
Status DeLinkQueue(LinkQueue& Q, QElemType& e)
{
	if (Q.front == Q.rear) return ERROR;		//队空
	e = Q.front->next->data;
	Q.front->next = Q.front->next->next;
	if (Q.rear == Q.front->next) Q.rear = Q.front;
	delete Q.front->next;
	return OK;
}
