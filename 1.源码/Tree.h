#include "SqStack.h"
#define tree_init_size 100
#define char_init_size 30
#define path_init_size 1000

Tree now;
Tree extension;

Status KMP(char *text, char *pattern) //字符串匹配
{
    int n = strlen(text);
    int m = strlen(pattern);
    if (n < m)
        return FALSE;
    for (int i = 0; i < n - m + 1; i++)
    {
        int turn = 0;
        for (int j = 0; j < m; j++)
        {
            if (text[i + j] == pattern[j])
                turn++;
            else
                break;
        }
        if (turn == m)
            return TRUE;
    }
    return FALSE;
}

Tree CreateTNode() //创建一个树的节点
{
    Tree t = (TNode *)malloc(tree_init_size * sizeof(TNode));
    t->name = (char *)malloc(char_init_size * sizeof(char));
    t->code = (char *)malloc(char_init_size * sizeof(char));
    t->child = NULL;
    t->next = NULL;
    return t;
}

Tree SearchTNode(Tree t, char *code) //查找节点
{
    if (!t)
        return NULL;
    Tree chi = t->child;
    while (chi)
    {
        if (!strcmp(chi->code, code))
            return chi;
        Tree ans = SearchTNode(chi, code);
        if (ans == NULL)
            chi = chi->next;
        else
            return ans;
    }
    return NULL;
}

Tree AddTNode(Tree t, Tree ele) //添加树的节点
{
    int len = strlen(ele->code);
    if (len != 1)
    {
        char *fcode = (char *)malloc(char_init_size * sizeof(char));
        strcpy(fcode, ele->code);
        if (len == 6)
            fcode[4] = '\0';
        else
            fcode[len - 1] = '\0';
        t = SearchTNode(t, fcode);
    }
    if (t)
    {
        if (!t->child)
        {
            t->child = ele;
            return t->child;
        }
        else if (ele->next == NULL)
        {
            Tree x = t->child;
            while (x->next)
                x = x->next;
            x->next = ele;
            return x->next;
        }
        else
        {
            Tree x = t->child;
            if (!strcmp(x->code, ele->next->code))
            {
                t->child = ele;
                return ele;
            }
            else
            {
                while (strcmp(x->next->code, ele->next->code))
                    x = x->next;
                x->next = ele;
                return ele;
            }
        }
    }
    return NULL;
}

Tree DelTNode(Tree t, Tree ele) //删除树的节点
{
    int len = strlen(ele->code);
    if (len != 1)
    {
        char *fcode = (char *)malloc(char_init_size * sizeof(char));
        strcpy(fcode, ele->code);
        if (len == 6)
            fcode[4] = '\0';
        else
            fcode[len - 1] = '\0';
        t = SearchTNode(t, fcode);
    }
    if (t)
    {
        if (!t->child)
            return FALSE;
        else
        {
            Tree x = t->child;
            if (!strcmp(x->code, ele->code))
            {
                Tree temp = t->child;
                t->child = x->next;
                return temp;
            }
            while (x->next)
            {
                if (!strcmp(x->next->code, ele->code))
                {
                    Tree temp = x->next;
                    x->next = x->next->next;
                    return temp;
                }
                x = x->next;
            }
        }
    }
    return NULL;
}

Tree FinTNode(Tree t, Tree ele) //找到树的节点
{
    int len = strlen(ele->code);
    if (len != 1)
    {
        char *fcode = (char *)malloc(char_init_size * sizeof(char));
        strcpy(fcode, ele->code);
        if (len == 6)
            fcode[4] = '\0';
        else
            fcode[len - 1] = '\0';
        t = SearchTNode(t, fcode);
    }
    if (t)
    {
        if (!t->child)
            return NULL;
        else
        {
            Tree x = t->child;
            while (x)
            {
                if (!strcmp(x->code, ele->code))
                    return x;
                x = x->next;
            }
        }
    }
    return NULL;
}

Tree ExactSearch(Tree t, char *text, char *path) //精确查找
{
    if (!t)
        return NULL;
    Tree chi = t->child;
    while (chi)
    {
        char *temp = (char *)malloc(path_init_size * sizeof(char));
        strcpy(temp, path);
        if (strlen(temp))
            strcat(temp, "->");
        strcat(temp, chi->name);
        if (!strcmp(chi->code, text) || !strcmp(chi->name, text))
        {
            printf("%d. 对象路径为：%s 对象编号为%s\n", ++SearchNum, temp, chi->code);
            return chi;
        }
        ExactSearch(chi, text, temp);
        chi = chi->next;
    }
    return NULL;
}

Tree FuzzySearch(Tree t, char *text, char *path) //模糊查找
{
    if (!t)
        return NULL;
    Tree chi = t->child;
    while (chi)
    {
        char *temp = (char *)malloc(path_init_size * sizeof(char));
        strcpy(temp, path);
        if (strlen(temp))
            strcat(temp, "->");
        strcat(temp, chi->name);
        if (KMP(chi->name, text) || KMP(chi->code, text))
            printf("%d. 对象路径为：%s 对象编号为%s\n", ++SearchNum, temp, chi->code);
        FuzzySearch(chi, text, temp);
        chi = chi->next;
    }
    return NULL;
}

void Statistics(Tree t) //统计各个对象的人数
{
    Tree now0 = t->child;
    //学校
    while (now0)
    {
        int AcaNum = 0;
        Tree now1 = now0->child;
        //学院
        while (now1)
        {
            int SpeNum = 0;
            Tree now2 = now1->child;
            //专业
            while (now2)
            {
                int ClaNum = 0;
                Tree now3 = now2->child;
                //班级
                while (now3)
                {
                    int StuNum = 0;
                    Tree now4 = now3->child;
                    //学生
                    while (now4)
                    {
                        StuNum++;
                        now4 = now4->next;
                    }
                    SPut(now3->code, StuNum);
                    ClaNum++;
                    now3 = now3->next;
                }
                SPut(now2->code, ClaNum);
                SpeNum ++;
                now2 = now2->next;
            }
            SPut(now1->code, SpeNum);
            AcaNum ++;
            now1 = now1->next;
        }
        SPut(now0->code, AcaNum);
        now0 = now0->next;
    }
}

void PrintAll(Tree t) //显示全部数据信息
{
    puts("[编号]名称(个数)\n\n");
    Tree now0 = t->child;
    //学校
    while (now0)
    {
        if (now0->next)
            printf("├─ ");
        else
            printf("└─ ");
        printf("[%s]%s(共%d个)\n", now0->code, now0->name, SGetValue(now0->code));
        Tree now1 = now0->child;
        //学院
        while (now1)
        {
            if (now0->next)
                printf("│  ");
            else
                printf("   ");
            if (now1->next)
                printf("├─ ");
            else
                printf("└─ ");
            printf("[%s]%s(共%d个)\n", now1->code, now1->name, SGetValue(now1->code));
            Tree now2 = now1->child;
            //专业
            while (now2)
            {
                if (now0->next)
                    printf("│  ");
                else
                    printf("   ");
                if (now1->next)
                    printf("│  ");
                else
                    printf("   ");
                if (now2->next)
                    printf("├─ ");
                else
                    printf("└─ ");
                printf("[%s]%s(共%d个)\n", now2->code, now2->name, SGetValue(now2->code));
                Tree now3 = now2->child;
                //班级
                while (now3)
                {
                    if (now0->next)
                        printf("│  ");
                    else
                        printf("   ");
                    if (now1->next)
                        printf("│  ");
                    else
                        printf("   ");
                    if (now2->next)
                        printf("│  ");
                    else
                        printf("   ");
                    if (now3->next)
                        printf("├─ ");
                    else
                        printf("└─ ");
                    printf("[%s]%s(共%d个)\n", now3->code, now3->name, SGetValue(now3->code));
                    Tree now4 = now3->child;
                    //学生
                    while (now4)
                    {
                        if (now0->next)
                            printf("│  ");
                        else
                            printf("   ");
                        if (now1->next)
                            printf("│  ");
                        else
                            printf("   ");
                        if (now2->next)
                            printf("│  ");
                        else
                            printf("   ");
                        if (now3->next)
                            printf("│  ");
                        else
                            printf("   ");
                        if (now4->next)
                            printf("├─ ");
                        else
                            printf("└─ ");
                        printf("[%s]%s\n", now4->code, now4->name);
                        now4 = now4->next;
                    }
                    now3 = now3->next;
                }
                now2 = now2->next;
            }
            now1 = now1->next;
        }
        now0 = now0->next;
    }
}

void Display(Tree t) //显示部分数据信息
{
    if(now==t)
    {
        puts("★");
    }
    Tree now0 = t->child;
    //学校
    while (now0)
    {
        if (now0->next)
            printf("├─ ");
        else
            printf("└─ ");
        if (!strcmp(now->code, now0->code))
            printf("★ ");
        printf("[%s]%s\n", now0->code, now0->name);
        Tree now1 = now0->child;
        //学院
        while (now1)
        {
            if (now0->next)
                printf("│  ");
            else
                printf("   ");
            if (now1->next)
                printf("├─ ");
            else
                printf("└─ ");
            if (!strcmp(now->code, now1->code))
                printf("★ ");
            printf("[%s]%s\n", now1->code, now1->name);
            Tree now2 = now1->child;
            //专业
            while (now2)
            {
                if (now0->next)
                    printf("│  ");
                else
                    printf("   ");
                if (now1->next)
                    printf("│  ");
                else
                    printf("   ");
                if (now2->next)
                    printf("├─ ");
                else
                    printf("└─ ");
                if (!strcmp(now->code, now2->code))
                    printf("★ ");
                printf("[%s]%s\n", now2->code, now2->name);
                Tree now3 = now2->child;
                //班级
                while (now3)
                {
                    if (now0->next)
                        printf("│  ");
                    else
                        printf("   ");
                    if (now1->next)
                        printf("│  ");
                    else
                        printf("   ");
                    if (now2->next)
                        printf("│  ");
                    else
                        printf("   ");
                    if (now3->next)
                        printf("├─ ");
                    else
                        printf("└─ ");
                    if (!strcmp(now->code, now3->code))
                        printf("★ ");
                    printf("[%s]%s\n", now3->code, now3->name);
                    now3 = now3->next;
                }
                now2 = now2->next;
            }
            now1 = now1->next;
        }
        now0 = now0->next;
    }
}