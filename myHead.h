#include<gl/glut.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

#define LEFT    'a'
#define RIGHT   'd'
#define UP      'w'
#define DOWN    's'
#define START    0      //图形范围定义
#define SIZE     20
#define ESC      27     //键值定义
#define ENTER    13
#define MAX_CHAR 128    //输出文字需要用到

#ifndef MY_POINT
#define MY_POINT

struct Point
{
    int x;
    int y;
};
#endif // MY_POINT

extern GLint aiBlock[SIZE][SIZE];   //记录游戏区域方块状态
extern GLfloat afCurLoc[4][2];      //记录当前正在下落方块的坐标
extern GLfloat afNextLoc[4][2];     //记录下一个下落方块的坐标
extern GLint iCurrentBlock;         //记录当前下落的是第几种图形，顺序如下面所示
extern GLint iNextBlock;            //记录下一个下落的是第几种图形，顺序如下面所示
extern GLint aiTurn[7];             //应该变换的形态
extern GLfloat xd, yd;
extern GLuint uiTextFont;           //定义文字输出函数时需要用到
extern int iLevel;
extern bool iOver;
extern int iEndGame;
extern int iScore;
extern int iTimeS;
extern int iStart;                  //0表示退出游戏，1表示开始游戏
extern char cButton;
extern int count;

const GLfloat afShape[7][4][2] = {
	{{-0.2f, 0.9f},{-0.2f, 0.8f},{-0.2f, 0.7f},{-0.2f, 0.6f}},	//长条
	{{-0.3f, 0.9f},{-0.2f, 0.9f},{-0.3f, 0.8f},{-0.2f, 0.8f}},	//正方形
	{{-0.3f, 0.9f},{-0.4f, 0.8f},{-0.3f, 0.8f},{-0.2f, 0.8f}},	//T字形
	{{-0.3f, 0.9f},{-0.2f, 0.9f},{-0.2f, 0.8f},{-0.1f, 0.8f}},	//Z字形
	{{-0.3f, 0.9f},{-0.2f, 0.9f},{-0.4f, 0.8f},{-0.3f, 0.8f}},	//倒Z字形
	{{-0.3f, 0.9f},{-0.3f, 0.8f},{-0.3f, 0.7f},{-0.2f, 0.7f}},	//L字形
	{{-0.2f, 0.9f},{-0.2f, 0.8f},{-0.3f, 0.7f},{-0.2f, 0.7f}}	//倒L字形
};

const GLfloat afShapeNext[7][4][2] = {
	{{0.7f, 0.7f},{0.7f, 0.6f},{0.7f, 0.5f},{0.7f, 0.4f}},	//预览长条
	{{0.6f, 0.7f},{0.7f, 0.7f},{0.6f, 0.6f},{0.7f, 0.6f}},	//预览正方形
	{{0.7f, 0.7f},{0.6f, 0.6f},{0.7f, 0.6f},{0.7f, 0.6f}},	//预览T字形
	{{0.6f, 0.7f},{0.7f, 0.7f},{0.7f, 0.6f},{0.8f, 0.6f}},	//预览Z字形
	{{0.7f, 0.7f},{0.8f, 0.7f},{0.6f, 0.6f},{0.7f, 0.6f}},	//预览倒Z字形
	{{0.6f, 0.7f},{0.6f, 0.6f},{0.6f, 0.5f},{0.7f, 0.5f}},	//预览L字形
	{{0.7f, 0.7f},{0.7f, 0.6f},{0.6f, 0.5f},{0.7f, 0.5f}}	//预览倒L字形
};

extern void GotoXY(int x,int y);

