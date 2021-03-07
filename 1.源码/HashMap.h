#include "HeadFile.h"

void GetKey(char *code) //获取键
{
    int len = strlen(code);
    for (int i = 0; i < len; i++)
        key[i] = code[i] - '0';
    for (int i = len; i < 6; i++)
        key[i] = 0;
}

int GetValue(char *code) //获取值
{
    GetKey(code);
    return HashMap[key[0]][key[1]][key[2]][key[3]][key[4]][key[5]];
}

void Put(char *code, int value) //建立键值对
{
    HashMap[key[0]][key[1]][key[2]][key[3]][key[4]][key[5]] = value;
}

void SPut(char *code, int value) //统计时用的键值对
{
    GetKey(code);
    StatNum[key[0]][key[1]][key[2]][key[3]][key[4]][key[5]] = value;
}

int SGetValue(char *code) //统计时用的获取值
{
    GetKey(code);
    return StatNum[key[0]][key[1]][key[2]][key[3]][key[4]][key[5]];
}