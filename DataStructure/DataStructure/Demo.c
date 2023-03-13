#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define SQLMAXSIZE 100
typedef int Status;
typedef char ElemType;

/*************************************************顺序表的操作函数*****************************************************/
typedef struct _SqLIist {
	ElemType* Base;
	int Length;
}SqList;

//顺序表的初始化
Status InitList(SqList L)
{
	L.Base = (ElemType*)malloc(sizeof(ElemType) * SQLMAXSIZE);		//为数组分配一段内存
	if (!L.Base) exit(OVERFLOW);
	L.Length = 0;

	return OK;
}

//销毁线性表
void DestroyList(SqList L)
{
	if (L.Base) free(L.Base);
}

//清空线性表
void ClearList(SqList L)
{
	L.Length = 0;
}

//求线性表的长度
int ListLength(SqList L)
{
	return L.Length;
}

//判断线性表是否为空，为空返回1，非空返回0
int ListIsEmpty(SqList L)
{
	if (L.Length == 0) return 1;
	else return 0;
}

//获取线性表第i的位置的元素
Status GetElem(SqList L, int i, ElemType e)
{
	if ((i < 1) || (i > L.Length)) return ERROR;

	e = L.Base[i - 1];
	return OK;
}

//查找线性表是否存在元素e
int LocalElme(SqList L, ElemType e)
{
	int i;
	for (i = 0; i < L.Length; i++)
	{
		if (e == L.Base[i]) return i + 1;
	}
	return 0;
}

//线性表第i个位置中插入元素e
Status ListInsertElem(SqList L, ElemType e, int i)
{

	if (i < 1 || i > L.Length + 1) return ERROR;
	if (i == SQLMAXSIZE) return ERROR;
	for (int j = L.Length - 1; j >= i - 1; j--)
	{
		L.Base[j + 1] = L.Base[j];
	}
	L.Base[i - 1] = e;
	L.Length++;
	return OK;
}

//线性表删除第i个位置中的元素e
Status ListDeletElem(SqList L, int i)
{
	if (i < 1 || i > L.Length) return ERROR;
	for (int j = i; j < L.Length; j++)
	{
		L.Base[j - 1] = L.Base[j];
	}
	L.Length--;
	return OK;
}

/*********************************链表的操作函数,以下链表都是带头结点的单链表*********************************************/
typedef struct Stu {
	char name[10];	//姓名
	int ID;			//学号
	float score;	//成绩
}Elemtype;

typedef struct Lnode{
	Elemtype Data;			//数据域
	struct Lnode *Next;		//指针域
}LNode, *LinkList;			//LinkList 为指向结构体 LNode 的指针类型

/****链表初始化*****/
Status InitLinkList(LinkList L)
{
	L = (LinkList)malloc(sizeof(LNode));		//为链表开辟空间
	L->Next = NULL;								//指针域为空
	return OK;
}

/****判断链表是否为空**但头指针和头结点存在***/
Status LinkListEmpty(LinkList L)
{
	if (L->Next == NULL) return OK;
	else return ERROR;
}

//销毁链表，头指针和头结点不存在
Status DestroyLinkList(LinkList L)
{
	LNode* p;			//定义结点指针
	while (L != NULL)
	{
		p = L;			//将头指针赋值给p
		L = L->Next;	//将下一个结点的指针域赋值给L,便于销毁下一个结点
		free(p);
	}
	return OK;
}

//清空链表，头指针和头结点存在
Status ClearLinkList(LinkList L)
{
	LNode *p, *q;
	p = L->Next;
	while(p != NULL)
	{	
		q = p->Next;
		free(p);
		p = q;
	}
	return OK;
}

//求链表的表长，不包括头结点
int LengthLinkList(LinkList L)
{
	int i = 0;
	LNode* p;
	p = L->Next;			//首元结点指针,不是头结点哦
	while (p != NULL)
	{
		p = p->Next;
		i++;
	}
	return i;
}

//查找链表中第i个元素的内容
Status GetElemLinkList(LinkList L, int i, Elemtype e)
{
	LNode* p;
	p = L->Next;			//首元结点指针
	int j = 1;	
	while (i > j && p != NULL)						//1 < i < length
	{
		p = p->Next;
		j++;
	}
	if ((i < j) || (p == NULL)) return ERROR;	    //i < 1 或者 L为空链表
	e = p->Data;
	return OK;
}

/*有问题
//获取链表中元素为e的位置,返回指针
LNode* GetLocatinkList(LinkList L, Elemtype e)
{
	LNode* p;
	p = L->Next;			//首元结点指针
	while (p && p->Data != e)
	{
		p = p->Next;
	}
	return p;	
}


//获取链表中元素为e的位置,返回位置
int GetLocatinkList(LinkList L, Elemtype e)
{
	LNode* p;
	p = L->Next;			//首元结点指针
	int i;
	while (p && p->Data != e)
	{
		p = p->Next;
		i++;
	}
	if(p) return i;
	else return 0;
}*/

//在第i个元素之前插入元素e
Status InsertLinkList(LinkList L, Elemtype e, int i)
{
	LNode* p;
	LNode* s;

	/*查找第i-1个结点，p指向该结点*/
	p = L;			//头结点指针
	int j = 0;
	while (i - 1 > j && p != NULL)						//1 < i < length
	{
		p = p->Next;
		j++;
	}
	if ((i - 1 < j) || (p == NULL)) return ERROR;	    //i < 1 或者 L为空链表

	/*改变指针域指向*/
	s = (LNode*)malloc(sizeof(LNode));    //为新结点开辟空间
	s->Data = e;
	s->Next = p->Next;
	p->Next = s;
	return OK;
}

//删除第i个结点
Status DeleteLinkList(LinkList L, int i, Elemtype e)
{
	LNode* p;
	LNode* q;

	/*查找第i-1个结点，p指向该结点*/
	p = L;			//头结点指针
	int j = 0;
	while (i - 1 > j && (p->Next) != NULL)						//1 < i < length
	{
		p = p->Next;
		j++;
	}
	if ((i - 1 < j) || ((p->Next) == NULL)) return ERROR;	    //i < 1 或者 L为空链表

	q = (LNode*)malloc(sizeof(LNode));    //为新结点开辟空间
	q = p->Next; 
	p->Next = q->Next;
	e = q->Data;		//保存被删结点q的数据
	free(q);			//释放q结点
	return OK;
}

//创建单链表   头插法
void HCreatlinkList(LinkList L, int n)
{
	L = (LinkList)malloc(sizeof(LNode));	//创建一个带头结点的链表
	L->Next = NULL;
	int i = 1;
	
	for (i = 1; i <= n; i++)
	{
		LNode* p;
		p = (LNode*)malloc(sizeof(LNode));
		/*cin >> p->data;*/					//scanf(&(p->Data));  此句c++语法 ，不懂 ，用c语言有问题
		p->Next = L->Next;
		L->Next = p;
	}
}

//创建单链表   尾插法
void ECreatlinkList(LinkList L, int n)
{
	LNode *r;		//尾指针
	L = (LinkList)malloc(sizeof(LNode));	//创建一个带头结点的链表
	L->Next = NULL;
	r = L;
	int i = 1;

	for (i = 1; i <= n; i++)
	{
		LNode* p;
		p = (LNode*)malloc(sizeof(LNode));
		/*cin >> p->data;*/					//此句c++语法 ，不懂 ，用c语言有问题
		p->Next = NULL;
		r->Next = p;
		r = p;
	}
}

/*************************************************链表的操作函数,循环链表***********************************************/

//将循环链表Tb连接到循环链表Ta后面
LinkList Connect(LinkList Ta, LinkList Tb)
{
	LinkList p;
	p = Ta->Next;
	Ta->Next = Tb->Next->Next;
	Tb->Next = p;
	return Tb;
}

/**************************************链表的操作函数,以下链表都是双向链表***********************************************/
typedef struct DLNode {
	Elemtype Data;
	struct DLNode* prior, * next;
}DLNode, * DLinkList;

//查找中第i个元素的指针
DLinkList GetP_DLinkList(DLinkList L, int i)
{
	DLNode* p;
	p = L->next;			//首元结点指针
	int j = 1;
	while (i > j && p != NULL)						//1 < i < length
	{
		p = p->next;
		j++;
	}
	if ((i < j) || (p == NULL)) return ERROR;	    //i < 1 或者 L为空链表
	return p;
}

//在双向链表的第i个位置插入元素e
Status InsertDLinkList(DLinkList L, int i, Elemtype e)
{
	DLNode* p;
	DLNode* s;
	if (!(p = GetP_DLinkList(L, i))) return ERROR;		//p就是指向i位置的指针, GetP_DLinkList不确定是对的
	
	s = (LNode*)malloc(sizeof(LNode));				//为被插入结点开辟空间
	s->Data = e;
	s->next = p;
	p->prior = s;
	s->prior = p->prior;
	p->prior->next = s;

	return OK;
}

//删除双向链表的第i个位置的指针，保留数据域e
Status DeletDLinkList(DLinkList L, int i, Elemtype e)
{
	DLNode* p;
	if (!(p = GetP_DLinkList(L, i))) return ERROR;		//p就是指向i位置的指针, GetP_DLinkList不确定是对的

	e = p->Data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);

	return OK;
}

//线性表的合并
void unite(SqList La, SqList Lb)
{
	int La_length, Lb_length;
	int i = 1;
	ElemType e;
	La_length = ListLength(La);
	Lb_length = ListLength(Lb);

	for (i = 1; i <= Lb_length; i++)
	{
		GetElem(Lb, i, e);
		if (!LocalElme(Lb, e)) ListInsertElem(La, e, La_length++);
	}
}










int  main()
{
	printf("调试");
	return 0;
}