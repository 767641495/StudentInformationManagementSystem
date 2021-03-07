#include "HashMap.h"
#define SElemType SNode
#define stack_init_size 200
#define stack_increment 10

//结构体保存学校/学院/专业/班级/学生信息
typedef struct TNode
{
    struct TNode *child, *next;
    char *code; //类型：学校x；学院x；专业x；班级x；学生xx
    char *name;
} TNode, *Tree;

typedef struct SNode
{
	Tree t;
	int operation;//存储的是逆向操作。1,2,3分别对应增，删，改
} SNode;

typedef struct SqStack
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

Status GetTop(SqStack *s,SElemType *e)		//获取栈顶元素
{
	if((*s).top==(*s).base) return ERROR;
	*e=*((*s).top-1);
	return OK;
}

Status InitStack(SqStack *s)				//构造一个空栈
{
	(*s).base =(SElemType *)malloc(stack_init_size * sizeof(SElemType));
	if(!(*s).base) return OVERFLOW;
	(*s).top=(*s).base;
	(*s).stacksize=stack_init_size;
	return OK;
}

Status Pop(SqStack *s,SElemType *e)			//出栈
{
	if((*s).top==(*s).base)
		return ERROR;
	*e=*--(*s).top;
	return OK;
}

Status Push(SqStack (*s),SElemType e)		//入栈
{
	if((*s).top-(*s).base>=(*s).stacksize)
	{
		(*s).base=(SElemType *)realloc((*s).base,((*s).stacksize+stack_increment) *sizeof(SElemType));
		if(!(*s).base) exit(OVERFLOW);
		(*s).top=(*s).base+(*s).stacksize;
		(*s).stacksize+=stack_increment;
	}
	*(*s).top++=e;
	return OK;
}

Status StackEmpty(SqStack s)				//栈是否为空
{
	if(s.top==s.base) return OK;
	return OVERFLOW;
}

void StackClear(SqStack *s)					//清空栈里所有元素
{
	SElemType temp;
	while(!StackEmpty((*s))) Pop(s,&temp);
}