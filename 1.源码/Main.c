#include "Menu.h"

//函数声明
/*哈希表*/
void GetKey(char *code);		  //获取键
int GetValue(char *code);		  //获取值
void Put(char *code, int value);  //建立键值对
int SGetValue(char *code);		  //统计时用的获取值
void SPut(char *code, int value); //统计时用的键值对
/*栈*/
Status GetTop(SqStack *s, SElemType *e); //获取栈顶元素
Status InitStack(SqStack *s);			 //构造一个空栈
Status Pop(SqStack *s, SElemType *e);	 //出栈
Status Push(SqStack(*s), SElemType e);	 //入栈
Status StackEmpty(SqStack s);			 //栈是否为空
void StackClear(SqStack *s);			 //清空栈里所有元素
/*树*/
Tree CreateTNode();								  //创建一个树的节点
Tree AddTNode(Tree t, Tree ele);				  //添加树的节点
Tree DelTNode(Tree t, Tree ele);				  //删除树的节点
Tree FinTNode(Tree t, Tree ele);				  //找到树的节点
Tree SearchTNode(Tree t, char *code);			  //查找树的节点
Tree ExactSearch(Tree t, char *code, char *path); //精确查找
Tree FuzzySearch(Tree t, char *name, char *path); //模糊查找
void Add(Tree t, char *code, char *name);		  //预添加
void Statistics(Tree t);						  //统计各个对象的人数
void PrintAll(Tree t);							  //显示全部数据信息
void Display(Tree t);							  //显示部分数据信息
/*工具*/
Status KMP(char *text, char *pattern); //字符串匹配
Status JudgeCode(char *code);		   //检测输入的编号是否合法函数
Status JudgeName(char *name);		   //检测输入的名称是否合法函数
void PreInput(Tree t);				   //预输入函数
void GetCode(char *code);			   //输入编号函数
void GetName(char *name);			   //输入姓名函数
void Menu(Tree t, SqStack *s);		   //用户界面

//主函数
int main()
{
	Tree root = CreateTNode();
	strcpy(root->code, "");
	SqStack s;
	InitStack(&s);
	memset(HashMap, 0, sizeof(HashMap));
	memset(StatNum, 0, sizeof(StatNum));
	memset(key, 0, sizeof(key));
	extension = CreateTNode();
	extension = NULL;
	PreInput(root);
	now = root;
	while (opt != '8')
		Menu(root, &s);
	return 0;
}