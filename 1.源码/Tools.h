#include "Tree.h"

Status JudgeCode(char *code) //检测输入的编号是否合法函数
{
	int len = strlen(code);
	if (len >= 1 && len <= 6)
	{
		for (int i = 0; i < len; i++)
			if (!isdigit(code[i]))
				return FALSE;
		return TRUE;
	}
	return FALSE;
}

Status JudgeName(char *name) //检测输入的名称是否合法函数
{
	int len = strlen(name);
	if (len <= MaxNameLength && len > 0)
		return TRUE;
	return FALSE;
}

void GetCode(char *code) //输入编号函数
{
	while (printf("请输入对象编号："), scanf("%s", code), fflush(stdin), !JudgeCode(code))
	{
		printf("对象编号应为[1,6]位的数字,并且不应和已有的编号重复。\n");
		printf("您输入的编号不符合规范，请重新输入！\n");
	}
	if (strlen(code) == 5)
	{
		code[6] = code[5];
		code[5] = code[4];
		code[4] = '0';
	}
}

void GetName(char *name) //输入姓名函数
{
	while (printf("请输入对象名称："), scanf("%s", name), fflush(stdin), !JudgeName(name))
	{
		printf("对象的名称不应超过%d位数。\n", MaxNameLength);
		printf("您输入的名称不符合规范，请重新输入！\n");
	}
}

void Add(Tree t, char *code, char *name) //预添加
{
	Tree temp = CreateTNode();
	strcpy(temp->code, code);
	strcpy(temp->name, name);
	if (!FinTNode(t, temp))
	{
		if (AddTNode(t, temp) == NULL)
			printf("请先输入[%s]%s的上一级！！！\n", code, name);
		else
		{
			Put(code, 1);
			return;
		}
	}
	printf("编号为：%s,姓名为：%s 的对象 预添加失败！\n\n", code, name);
	system("pause");
}

void PreInput(Tree t) //预输入函数
{
	FILE *fp = NULL;
	fp = fopen("input.txt", "r");
	char *name = (char *)malloc(char_init_size * sizeof(char));
	char *code = (char *)malloc(char_init_size * sizeof(char));
	while (~fscanf(fp, "%s %s", code, name))
		Add(t, code, name);
	fclose(fp);
}