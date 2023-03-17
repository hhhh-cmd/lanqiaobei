#include <stdio.h>
#include <stdlib.h>


#define OK			1
#define ERROR		0
#define MAXSIZE		100
typedef int Status;
typedef int SElemType;

typedef struct {
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;

/*栈初始化*/
Status InitStack(SqStack& S)
{
	S.base = (SElemType*)malloc(MAXSIZE * sizeof(SElemType));
	if (!S.base) return ERROR;
	S.base = S.top;
	S.stacksize = MAXSIZE;
	return OK;
}

/*判断栈是否为空  OK:空   ERROR：非空*/
Status EmptyStack(SqStack S)
{
	if (S.base == S.top) return OK;
	else return ERROR;
}

/*求栈长度*/
int LengthStack(SqStack S)
{
	return S.top - S.base;
}

/*清空栈*/
Status ClearStack(SqStack S)
{
	if(S.base) S.top = S.base;
	return OK;
}

/*销毁栈*/
Status DestroyStack(SqStack &S) 
{
	if (S.base)
	{
		delete S.base;
		S.stacksize = 0;
		S.top = S.base = NULL;
	}
	return OK;
}

/*入栈*/
Status PushStack(SqStack &S, SElemType e)
{
	if (S.top - S.base == S.stacksize) return ERROR;	//上溢
	*S.top++ = e;
	return OK;
}

/*出栈*/
Status PopStack(SqStack &S, SElemType &e)
{
	if (S.top == S.base) return ERROR;	//下溢
	e = *--S.top;
	return OK;
}

/***************链栈的表示和实现*******************/

typedef struct StackNode{
	SElemType data;
	struct StackNode* next;
}StackNode, *LinkStack;
LinkStack S;

/*链栈的初始化*/
Status InitStack(LinkStack& S)
{
	S = NULL;
	return OK;
}

/*判断链栈是否为空*/
int EmptyStack(LinkStack S)
{
	if (S == NULL) return 1;
	else return 0;
}

/*链栈入栈*/      
Status PushStack(LinkStack &S, SElemType e)
{
	StackNode *p = new StackNode;
	p->data = e;
	p->next = S;
	S = p;
	return OK;	
}

/*链栈出栈*/
Status PopStack(LinkStack& S, SElemType &e)
{
	StackNode* p = new StackNode;
	if (S == NULL) return ERROR;
	e = S->data;
	p = S;
	S = S->next;
	delete p;
	return OK;
}

/*取栈顶元素*/
SElemType GetTopStack(LinkStack S)
{
	if (S != NULL)
		return S->data;
}
     
 






int main(void)
{   
	printf("fsfsfs");
	return 0;
}  