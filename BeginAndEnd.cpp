#include "myHead.h"

int iStart = -1;
char cButton = ' ';
struct Point stPoint;

void GotoXY(int x,int y)
{
    static COORD c;    //表示一个字符在控制台屏幕上的坐标
    c.X = 2 * x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Choose(void)
{
    iStart  =-1;
    while(iStart != 0 && iStart != 1)
    {
        cButton = getch();
        //如果是 UP 或 DOWN 就进行光标移动
        if(cButton == 72 || cButton == 80)
        {
            if(stPoint.y == 13)
            {
                stPoint.y = 16;
                GotoXY(10, 13);
                printf("   ");   //将之前的-->覆盖掉
                GotoXY(10, 16);
                printf("-->");
                GotoXY(12, 16);
            }
            else if(stPoint.y == 16)
            {
                stPoint.y = 13;
                GotoXY(10, 16);
                printf("   ");   //将之前的-->覆盖掉
                GotoXY(10, 13);
                printf("-->");
                GotoXY(12, 13);
            }
        }
        //按 ENTER 键根据相应的选择开始游戏或退出游戏
        //按 ESC 键退出游戏
        if((cButton == ENTER && stPoint.y == 16) || cButton == ESC)
        {
            iStart = 0;
            break;
        }
        if(cButton == ENTER && stPoint.y == 13)
        {
            iStart = 1;
            break;
        }
    }
}

void WelcomeScreen(void)
{
    system("color 0F");
    GotoXY(14, 1);
    printf("Welcome to play Tetris");
    GotoXY(17, 7);
    printf("MAIN MENU");
    GotoXY(15, 13);
    printf("***START GAME***");
    GotoXY(15, 16);
    printf("***QUIT  GAME***");
    GotoXY(10, 13);
    printf("-->");
    stPoint.x = 15;
    stPoint.y = 13;
    GotoXY(12, 13);
    Choose();
}

void EndScreen(void)
{
    system("cls");
    system("color 0f");
    GotoXY(16, 3);
    printf("GAME OVER!!!");
    GotoXY(15, 10);
    printf("YOUR SCORE IS: %d\n", iScore * 100);
    GotoXY(15, 12);
    printf("YOUR LEVEL IS: %d\n\n\n", iLevel);
}
