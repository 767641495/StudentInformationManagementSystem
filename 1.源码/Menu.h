#include "Tools.h"

void Menu(Tree root, SqStack *s) //用户界面
{
	system("cls");
	printf("  ******************************************************\n\n");
	printf("  *                学生信息管理系统                    *\n \n");
	printf("  **********************HZHNB***************************\n\n");
	printf("*********************系统功能菜单*************************       \n");
	printf("     ----------------------   ----------------------   \n");
	printf("     *********************************************     \n");
	printf("     * 1.说明            * *  2.增加           *\n");
	printf("     *********************************************\n");
	printf("     * 3.删除            * *  4.修改           *\n");
	printf("     *********************************************\n");
	printf("     * 5.查询            * *  6.撤销           *\n");
	printf("     *********************************************\n");
	printf("     * 7.统计            * *  8.退出           *\n");
	printf("     *********************************************\n");
	printf("     ----------------------   ----------------------                           \n\n\n");
	Statistics(root);
	Display(root);
	puts("");
	if (extension != NULL && extension->code[0] >= '0' && extension->code[0] <= '9')
	{
		printf("******************************************************\n");
		printf("|-[ %s ]-|-  %s  -|\n\n", extension->code, extension->name);
		printf("|-[ 学号 ]-|-  姓名  -|\n");
		Tree now4 = extension->child;
		//学生
		while (now4)
		{
			printf("|-[%s]-|-%-8s-|\n", now4->code, now4->name);
			now4 = now4->next;
		}
	}
	puts("");
	puts("★ 为目前光标停留处。");
	puts("若光标停留处为班级，则会在按回车后，展开该班级内的人。\n");
	printf("请输入编号,wsad方向键或者回车：");
	opt = getch();
	puts("\n");
	fflush(stdin);
	Tree ele = CreateTNode();
	char *text = (char *)malloc(char_init_size * sizeof(char));
	SNode sn;
	sn.t = CreateTNode();
	switch (opt)
	{
	case '1': //说明
	{
		puts("*********************************************");
		puts("使用说明：");
		puts("代码规范：学校编号占第一位，学院编号占第二位，专业编号占第三位，班级编号占第四位，学生编号占第五和第六位。");
		system("pause");
		break;
	}
	case '2': //增加
	{
		puts("*********************************************");
		puts("增加：");
		Tree child = now->child;
		if (child == NULL)
		{
			strcpy(ele->code, now->code);
			strcat(ele->code, "1");
		}
		else
		{
			while (child->next != NULL)
				child = child->next;
			strcpy(ele->code, child->code);
			if (strlen(ele->code) == 6 && ele->code[5] == '9')
			{
				ele->code[4]++;
				ele->code[5] = '0';
			}
			else
				ele->code[strlen(child->code) - 1] += 1;
		}
		Put(ele->code, 1);
		sn.t = AddTNode(root, ele);
		sn.operation = 2;
		Push(s, sn);
		GetName(ele->name);
		break;
	}
	case '3': //删除
	{
		printf("*********************************************\n");
		puts("删除：");
		if (extension != NULL)
		{
			GetCode(ele->code);
			if (!FinTNode(root, ele))
			{
				puts("该对象不存在！！！\n");
				system("pause");
				break;
			}
		}
		else
		{
			puts("请问您确定要删除这个对象以及其下面的所有分支吗？输入Y继续");
			char c = 'N';
			scanf("%c", &c);
			if (!(c == 'Y' || c == 'y'))
				break;
			strcpy(ele->code, now->code);
		}
		sn.operation = 1;
		sn.t = DelTNode(root, ele);
		Push(s, sn);
		Put(ele->code, 0);
		now = root;
		break;
	}
	case '4': //修改
	{
		puts("*********************************************");
		puts("修改：");
		SNode stemp;
		stemp.t = CreateTNode();
		if (extension != NULL)
		{
			GetCode(ele->code);
			if (!FinTNode(root, ele))
			{
				puts("该对象不存在！！！\n");
				system("pause");
				break;
			}
		}
		else
			strcpy(ele->code, now->code);
		char *path = (char *)malloc(sizeof(char));
		strcpy(path, "");
		ExactSearch(root, ele->code, path);
		printf("\n请在下方输入修改后的名称\n");
		GetName(ele->name);
		stemp.operation = 3;
		sn.t = FinTNode(root, ele);
		strcpy(stemp.t->code, sn.t->code);
		strcpy(stemp.t->name, sn.t->name);
		Push(s, stemp);
		strcpy(sn.t->name, ele->name);
		break;
	}
	case '5': //查询
	{
		printf("*********************************************\n");
		printf("查询：\n");
		while (1)
		{
			SearchNum = 0;
			puts("\n\n请选择您需要的查找方式:");
			puts("1.精确查找");
			puts("2.模糊查找");
			puts("3.返回主菜单\n\n");
			opt = getch();
			fflush(stdin);
			char *path = (char *)malloc(sizeof(char));
			strcpy(path, "");
			switch (opt)
			{
			case '1':
			{
				printf("请输入精确查找的编码或者名称：");
				scanf("%s", text);
				puts("\n");
				ExactSearch(now, text, path);
				if (SearchNum == 0)
					puts("该对象不存在！！！\n");
				SearchNum = 0;
				system("pause");
				break;
			}
			case '2':
			{
				printf("请输入模糊查找的编码或者名称：");
				scanf("%s", text);
				puts("\n");
				FuzzySearch(now, text, path);
				if (SearchNum == 0)
					puts("该对象不存在！！！\n");
				SearchNum = 0;
				system("pause");
				break;
			}
			case '3':
			{
				break;
			}
			default:
				puts("输入非法！\n");
				system("pause");
			}
			if (opt == '3')
				break;
		}
		break;
	}
	case '6': //撤销
	{
		printf("*********************************************\n");
		printf("撤销：\n");
		if (Pop(s, &sn) == ERROR)
		{
			puts("没有可以撤销的操作！！！\n");
			system("pause");
			break;
		}
		switch (sn.operation)
		{
		case 1:
			AddTNode(root, sn.t);
			break;
		case 2:
			DelTNode(root, sn.t);
			break;
		case 3:
			strcpy(FinTNode(root, sn.t)->name, sn.t->name);
			break;
		default:
			puts("Operation异常！\n");
			system("pause");
		}
		break;
	}
	case '7': //统计
	{
		printf("*********************************************\n");
		printf("统计：\n");
		PrintAll(root);
		system("pause");
		break;
	}
	case '8': //退出
	{
		printf("程序即将退出，感谢您的使用！\n");
		printf("作者：洪智豪 19195216 from HDU\n\n");
		system("pause");
		break;
	}
	case 13: //回车
	{
		if (extension != NULL)
			extension = NULL;
		else if (strlen(now->code) == 4)
			extension = now;
		break;
	}
	case 'W':
	case 'w': //上
	{
		if(now==root)
			break;
		extension = NULL;
		int len = strlen(now->code);
		char *tempcode = (char *)malloc(char_init_size * sizeof(char));
		strcpy(tempcode, now->code);
		if (strlen(now->code) == 1)
			now = root;
		else
		{
			char *fcode = (char *)malloc(char_init_size * sizeof(char));
			strcpy(fcode, now->code);
			fcode[len - 1] = '\0';
			now = SearchTNode(root, fcode);
		}
		Tree temp = now->child;
		if (strcmp(temp->code, tempcode))
			while (strcmp(temp->next->code, tempcode))
				temp = temp->next;
		now = temp;
		break;
	}
	case 'A':
	case 'a': //左
	{
		extension = NULL;
		if (strlen(now->code) > 1)
		{
			int len = strlen(now->code);
			char *fcode = (char *)malloc(char_init_size * sizeof(char));
			strcpy(fcode, now->code);
			fcode[len - 1] = '\0';
			now = SearchTNode(root, fcode);
		}
		else
		{
			now = root;
		}
		break;
	}
	case 'D':
	case 'd': //右
	{
		extension = NULL;
		if (now->child != NULL && strlen(now->code) < 4)
			now = now->child;
		break;
	}
	case 'S':
	case 's': //下
	{
		extension = NULL;
		if (now->next != NULL)
			now = now->next;
		break;
	}

	default:
		puts("你的输入不是菜单编号，wsad方向键或者回车！\n");
		system("pause");
		break;
	}
}