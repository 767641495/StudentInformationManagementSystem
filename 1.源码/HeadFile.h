#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#define Status int
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW 0
#define OK 1

char opt = ' '; //选项
int MaxNameLength = 20;//字符串长度上限
int HashMap[10][10][10][10][10][10];
int StatNum[10][10][10][10][10][10];
int key[6];
int SearchNum = 0;