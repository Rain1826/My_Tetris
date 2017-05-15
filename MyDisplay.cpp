#include "myHead.h"

GLint aiBlock[SIZE][SIZE] = {0};
GLfloat afNextLoc[4][2] = {0};
GLuint uiTextFont = 0;

void InitBlock(void)
{
    int i, j;
    for(i = 0; i < SIZE - 5; ++ i)
    {
        for(j = 0; j < SIZE; ++j)
        {
            aiBlock[i][j] = 0;
        }
    }
    for(i = 0; i < SIZE - 5; ++ i)
    {
        aiBlock[0][i] = 1;
    }
    for(i = 0; i < SIZE; ++i)
    {
        aiBlock[i][0] = 1;
        aiBlock[i][SIZE - 6] = 1;
    }
    for(i = 0; i < 4; ++ i)
    {
        for(j = 0; j < 2; ++j)
        {
            afCurLoc[i][j] = afShape[iCurrentBlock][i][j];
        }
    }
}

void InitString(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    //申请 MAX_CHAR 个连续的显示列表编号
    uiTextFont = glGenLists(MAX_CHAR);
    //把每个字符的绘制命令都装到对应的显示列表中
    wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, uiTextFont);
}

void PrintString(char * s)
{
    if(s == NULL) return;
    glPushAttrib(GL_LIST_BIT);
    //调用每个字符对应的显示列表，绘制每个字符
    for( ; *s != '\0'; ++ s)
    {
        glCallList(uiTextFont + *s);
    }
    glPopAttrib();
}

void MenuDisplay(void)
{
    int i, j;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(0.6f, 0.1f, 0.0f);    //设置显示位置
    //显示 Level 信息
    PrintString("Level:");
    glRasterPos3f(0.6f, 0.0f, 0.0f);
    switch(iLevel)
    {
    case 0:
        PrintString("0");
        break;
    case 1:
        PrintString("1");
        break;
    case 2:
        PrintString("2");
        break;
    case 3:
        PrintString("3");
        break;
    case 4:
        PrintString("4");
        break;
    default:
        PrintString("5");
    }
    //显示 Help 信息
    glRasterPos3f(0.6f, -0.25f, 0.0f);
    PrintString("Help:");
    glRasterPos3f(0.6f, -0.4f, 0.0f);
    PrintString("W---ROLL");
    glRasterPos3f(0.6f, -0.5f, 0.0f);
    PrintString("S---Downwards");
    glRasterPos3f(0.6f, -0.6f, 0.0f);
    PrintString("A---Turn Left");
    glRasterPos3f(0.6f, -0.7f, 0.0f);
    PrintString("D---Turn Right");
    glRasterPos3f(0.6f, -0.8f, 0.0f);
    PrintString("ESC---EXIT");
    //显示预览方块信息
    glRasterPos3f(0.6f, 0.9f, 0.0f);
    PrintString("NextBlock:");
    //重置预览下一方块的4个坐标
    for(i = 0;i < 4; ++ i)
    {
        for(j = 0;j < 2; ++j)
        {
            afNextLoc[i][j] = afShapeNext[iNextBlock][i][j];
        }
    }
    //将预览方块涂色
    for(int i = 0;i < 4; ++ i)
    {
        glColor3f(1.0f, 1.0f, 0.0f);
        //将每个点扩展为一个小方块
        glRectf(afNextLoc[i][0], afNextLoc[i][1], afNextLoc[i][0] + 0.1f, afNextLoc[i][1] + 0.1f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
            glColor3f(0.0f, 0.0f, 0.0f);
            glVertex2f(afNextLoc[i][0], afNextLoc[i][1]);
            glVertex2f(afNextLoc[i][0] + 0.1f, afNextLoc[i][1]);
            glVertex2f(afNextLoc[i][0] + 0.1f, afNextLoc[i][1] + 0.1f);
            glVertex2f(afNextLoc[i][0], afNextLoc[i][1] + 0.1f);
        glEnd();
        glutPostRedisplay();
    }
}

void BlockDisplay(void)
{
    int i, j;
    glClear(GL_COLOR_BUFFER_BIT);
    MenuDisplay();
    //将游戏区域边框涂为灰色
    for(i = 0;i < SIZE; ++ i)
    {
        for(j = 0; j < SIZE - 5; ++ j)
        {
            if(aiBlock[i][j] == 1)
            {
                glColor3f(0.7f, 0.7f, 0.7f);
                glRectf(j/10.0f - 1.0f, i/10.0f - 1.0f, j/10.0f - 1.0f + 0.1f, i/10.0f - 1.0f + 0.1f);
                glLineWidth(2.0f);
                glBegin(GL_LINE_LOOP);
                    glColor3f(0.0f, 0.0f, 0.0f);
                    glVertex2f(j/10.0f - 1.0f, i/10.0f - 1.0f);
                    glVertex2f(j/10.0f - 1.0f + 0.1f, i/10.0f - 1.0f);
                    glVertex2f(j/10.0f - 1.0f + 0.1f, i/10.0f - 1.0f + 0.1f);
                    glVertex2f(j/10.0f - 1.0f, i/10.0f - 1.0f + 0.1f);
                glEnd();
                glutPostRedisplay();
            }
        }
    }
    for(i = 1;i < SIZE; ++ i)
    {
        for(j = 1; j < SIZE - 6; ++ j)
        {
            if(aiBlock[i][j] == 1)
            {
                glColor3f(1.0f, 1.0f, 1.0f);
                glRectf(j/10.0f - 1.0f, i/10.0f - 1.0f, j/10.0f - 1.0f + 0.1f, i/10.0f - 1.0f + 0.1f);
                glLineWidth(2.0f);
                glBegin(GL_LINE_LOOP);
                    glColor3f(0.0f, 0.0f, 0.0f);
                    glVertex2f(j/10.0f - 1.0f, i/10.0f - 1.0f);
                    glVertex2f(j/10.0f - 1.0f + 0.1f, i/10.0f - 1.0f);
                    glVertex2f(j/10.0f - 1.0f + 0.1f, i/10.0f - 1.0f + 0.1f);
                    glVertex2f(j/10.0f - 1.0f, i/10.0f - 1.0f + 0.1f);
                glEnd();
                glutPostRedisplay();
            }
        }
    }
    if(!iOver)
	{
		for(i = 0;i < 4; ++ i)
		{
			glColor3f(0.0f, 1.0f, 0.0f);
			glRectf(afCurLoc[i][0], afCurLoc[i][1], afCurLoc[i][0] + 0.1f, afCurLoc[i][1] + 0.1f);
			glLineWidth(2.0f);
			glBegin(GL_LINE_LOOP);
                glColor3f(0.0f,0.0f,0.0f);
                glVertex2f(afCurLoc[i][0], afCurLoc[i][1]);
                glVertex2f(afCurLoc[i][0] + 0.1f, afCurLoc[i][1]);
                glVertex2f(afCurLoc[i][0] + 0.1f, afCurLoc[i][1] + 0.1f);
                glVertex2f(afCurLoc[i][0], afCurLoc[i][1] + 0.1f);
			glEnd();
			glutPostRedisplay();
		}
	}
    glutSwapBuffers();
}

