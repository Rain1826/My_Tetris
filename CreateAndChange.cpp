#include "myHead.h"

GLint iCurrentBlock = 3;
GLint iNextBlock = 1;
GLint aiTurn[7] = {0};
int iLevel = 0;
bool iOver = false;
int iEndGame = 0;

void BlockDisplay(void);
bool CheckConflict(int iLefRig = 0);
void CheckDelete(void);
void EndScreen(void);

int count = 0;

void CreateBlocks(void)
{
    int i, j;
    //若游戏未结束，则生成下一方块
    if(!iEndGame)
    {
        BlockDisplay();
        if(iOver)
        {
            srand(time(NULL));
            iCurrentBlock = iNextBlock;
            iNextBlock = rand() % 7;
            //每创建一个新的方块后要将变形的记录清空
            for(i = 0; i < 7; ++ i)
            {
                aiTurn[i] = 0;
            }
            for(i = 0; i < 4; ++ i)
            {
                for(j = 0; j < 2; ++ j)
                {
                    afCurLoc[i][j] = afShape[iCurrentBlock][i][j];
                }
            }
            iOver = false;
            glutPostRedisplay();
        }
    }
}

void Down(int id)
{
    int i;
    if(!iOver)
    {
        for(i = 0; i < 4; ++ i)
        {
            afCurLoc[i][1] -= 0.1f;
        }
        if(CheckConflict())
        {
            for(i = 0; i < 4; ++ i)
            {
                afCurLoc[i][1] += 0.1f;
            }
            //若方块位置超出屏幕，则游戏结束
            if(afCurLoc[0][1] >= afShape[iCurrentBlock][0][1])
            {
                iEndGame = 1;
                EndScreen();
                exit(1);
            }
            iOver = true;
        }
        if(iTimeS >= 1000)  iLevel = 0;
        else if(iTimeS >= 900)  iLevel = 1;
        else if(iTimeS >= 700)  iLevel = 2;
        else if(iTimeS >= 500)  iLevel = 3;
        else if(iTimeS >= 300)  iLevel = 4;
        else iLevel = 5;
    }
    if(iOver)
        CheckDelete();
    glutPostRedisplay();
    glutTimerFunc(iTimeS, Down, 1);
}

//将图形做变换，采用顺时针旋转的规律
void Change(void)
{
    GLfloat temp00 = afCurLoc[0][0];
    GLfloat temp01 = afCurLoc[0][1];
    GLfloat temp10 = afCurLoc[1][0];
    GLfloat temp11 = afCurLoc[1][1];
    GLfloat temp20 = afCurLoc[2][0];
    GLfloat temp21 = afCurLoc[2][1];
    GLfloat temp30 = afCurLoc[3][0];
    GLfloat temp31 = afCurLoc[3][1];
    int tempTurn = aiTurn[iCurrentBlock];
    switch(iCurrentBlock)
    {
    case 0://长条
        switch(aiTurn[0])
        {
        case 0:
            afCurLoc[0][0] = temp10 - 0.1f;
            afCurLoc[0][1] = temp11;
            afCurLoc[2][0] = temp10 + 0.1f;
            afCurLoc[2][1] = temp11;
            afCurLoc[3][0] = temp10 + 0.2f;
            afCurLoc[3][1] = temp11;
            break;
        case 1:
            afCurLoc[0][0] = temp10;
            afCurLoc[0][1] = temp11 + 0.1f;
            afCurLoc[2][0] = temp10;
            afCurLoc[2][1] = temp11 - 0.1f;
            afCurLoc[3][0] = temp10;
            afCurLoc[3][1] = temp11 - 0.2f;
            break;
        }
        aiTurn[0] = (aiTurn[0] + 1) % 2;
        break;
    case 1://正方形
        break;
    case 2://T字形
        switch(aiTurn[2])
        {
        case 0:
            afCurLoc[1][0] = temp20;
            afCurLoc[1][1] = temp21;
            afCurLoc[2][0] = temp30;
            afCurLoc[2][1] = temp31;
            afCurLoc[3][0] = temp20;
            afCurLoc[3][1] = temp21 - 0.1f;
            break;
        case 1:
            afCurLoc[0][0] = temp10 - 0.1f;
            afCurLoc[0][1] = temp11;
            break;
        case 2:
            afCurLoc[0][0] = temp10;
            afCurLoc[0][1] = temp11 + 0.1f;
            afCurLoc[1][0] = temp00;
            afCurLoc[1][1] = temp01;
            afCurLoc[2][0] = temp10;
            afCurLoc[2][1] = temp11;
            break;
        case 3:
            afCurLoc[3][0] = temp20 + 0.1f;
            afCurLoc[3][1] = temp21;
            break;
        }
        aiTurn[2] = (aiTurn[2] + 1) % 4;
        break;
    case 3://Z字形
        switch(aiTurn[3])
        {
        case 0:
            afCurLoc[0][0] = temp10 + 0.1f;
            afCurLoc[0][1] = temp11 + 0.1f;
            afCurLoc[2][0] = temp10 + 0.1f;
            afCurLoc[2][1] = temp11;
            afCurLoc[3][0] = temp20;
            afCurLoc[3][1] = temp21;
            break;
        case 1:
            afCurLoc[0][0] = temp10 - 0.1f;
            afCurLoc[0][1] = temp11;
            afCurLoc[2][0] = temp30;
            afCurLoc[2][1] = temp31;
            afCurLoc[3][0] = temp30 + 0.1f;
            afCurLoc[3][1] = temp31;
            break;
        }
        aiTurn[3] = (aiTurn[3] + 1) % 2;
        break;
    case 4://反Z字形
        switch(aiTurn[4])
        {
        case 0:
            afCurLoc[0][0] = temp00 - 0.1f;
            afCurLoc[0][1] = temp01 + 0.1f;
            afCurLoc[1][0] = temp00 - 0.1f;
            afCurLoc[1][1] = temp01;
            afCurLoc[2][0] = temp00;
            afCurLoc[2][1] = temp01;
            afCurLoc[3][0] = temp00;
            afCurLoc[3][1] = temp01 - 0.1f;
            break;
        case 1:
            afCurLoc[0][0] = temp20;
            afCurLoc[0][1] = temp21;
            afCurLoc[1][0] = temp20 + 0.1f;
            afCurLoc[1][1] = temp21;
            afCurLoc[2][0] = temp10;
            afCurLoc[2][1] = temp11 - 0.1f;
            break;
        }
        aiTurn[4] = (aiTurn[4] + 1) % 2;
        break;
    case 5://L字形
        switch(aiTurn[5])
        {
        case 0:
            afCurLoc[0][0] = temp10;
            afCurLoc[0][1] = temp11;
            afCurLoc[1][0] = temp10 + 0.1f;
            afCurLoc[1][1] = temp11;
            afCurLoc[2][0] = temp10 + 0.2f;
            afCurLoc[2][1] = temp11;
            afCurLoc[3][0] = temp20;
            afCurLoc[3][1] = temp21;
            break;
        case 1:
            afCurLoc[0][0] = temp00;
            afCurLoc[0][1] = temp01 + 0.1f;
            afCurLoc[1][0] = temp10;
            afCurLoc[1][1] = temp11 + 0.1f;
            afCurLoc[2][0] = temp10;
            afCurLoc[2][1] = temp11;
            afCurLoc[3][0] = temp10;
            afCurLoc[3][1] = temp11 - 0.1f;
            break;
        case 2:
            afCurLoc[0][0] = temp20 + 0.1f;
            afCurLoc[0][1] = temp21;
            afCurLoc[1][0] = temp20 - 0.1f;
            afCurLoc[1][1] = temp21 - 0.1f;
            afCurLoc[2][0] = temp20;
            afCurLoc[2][1] = temp21 - 0.1f;
            afCurLoc[3][0] = temp20 + 0.1f;
            afCurLoc[3][1] = temp21 - 0.1f;
            break;
        case 3:
            afCurLoc[0][0] = temp10;
            afCurLoc[0][1] = temp11 + 0.2f;
            afCurLoc[1][0] = temp10;
            afCurLoc[1][1] = temp11 + 0.1f;
            afCurLoc[2][0] = temp10;
            afCurLoc[2][1] = temp11;
            afCurLoc[3][0] = temp20;
            afCurLoc[3][1] = temp21;
            break;
        }
        aiTurn[5] = (aiTurn[5] + 1) % 4;
        break;
    case 6://反L字形
        switch(aiTurn[6])
        {
        case 0:
            afCurLoc[0][0] = temp20 - 0.1f;
            afCurLoc[0][1] = temp21 + 0.1f;
            afCurLoc[1][0] = temp20 - 0.1f;
            afCurLoc[1][1] = temp21;
            break;
        case 1:
            afCurLoc[0][0] = temp00 + 0.1f;
            afCurLoc[0][1] = temp01 + 0.1f;
            afCurLoc[1][0] = temp30;
            afCurLoc[1][1] = temp31 + 0.2f;
            afCurLoc[2][0] = temp00 + 0.1f;
            afCurLoc[2][1] = temp01;
            afCurLoc[3][0] = temp20;
            afCurLoc[3][1] = temp21;
            break;
        case 2:
            afCurLoc[0][0] = temp00 - 0.1f;
            afCurLoc[0][1] = temp01 - 0.1f;
            afCurLoc[1][0] = temp20;
            afCurLoc[1][1] = temp21;
            afCurLoc[2][0] = temp20 + 0.1f;
            afCurLoc[2][1] = temp21;
            afCurLoc[3][0] = temp30 + 0.1f;
            afCurLoc[3][1] = temp31;
            break;
        case 3:
            afCurLoc[0][0] = temp20;
            afCurLoc[0][1] = temp21 + 0.1f;
            afCurLoc[1][0] = temp20;
            afCurLoc[1][1] = temp21;
            afCurLoc[2][0] = temp30 - 0.1f;
            afCurLoc[2][1] = temp31;
            afCurLoc[3][0] = temp30;
            afCurLoc[3][1] = temp31;
            break;
        }
        aiTurn[6] = (aiTurn[6] + 1) % 4;
        break;
    default:
        break;
    }
    //如果旋转非法(即旋转时碰到墙壁)，则要恢复原来的状态
    if(CheckConflict())
    {
        afCurLoc[0][0] = temp00;
        afCurLoc[0][1] = temp01;
        afCurLoc[1][0] = temp10;
        afCurLoc[1][1] = temp11;
        afCurLoc[2][0] = temp20;
        afCurLoc[2][1] = temp21;
        afCurLoc[3][0] = temp30;
        afCurLoc[3][1] = temp31;
        aiTurn[iCurrentBlock] = tempTurn;
    }
}

void Key(unsigned char k, int x, int y)
{
    int i;
    if(!iOver)
    {
        switch(k)
        {
        case UP:
            Change();
            break;
        case DOWN:
            for(i = 0; i < 4; ++ i)
            {
                afCurLoc[i][1] -= 0.1f;
            }
            if(CheckConflict())
            {
                for(i = 0; i < 4; ++ i)
                {
                    afCurLoc[i][1] += 0.1f;
                }
                iOver = true;
            }
            break;
        case RIGHT:
            for(i = 0; i < 4; ++ i)
            {
                afCurLoc[i][0] += 0.1f;
            }
            if(CheckConflict(1))
            {
                for(i = 0; i < 4; ++ i)
                {
                    afCurLoc[i][0] -= 0.1f;
                }
            }
            break;
        case LEFT:
            for(i = 0; i < 4; ++ i)
            {
                afCurLoc[i][0] -= 0.1f;
            }
            if(CheckConflict(1))
            {
                for(i = 0; i < 4; ++ i)
                {
                    afCurLoc[i][0] += 0.1f;
                }
            }
            break;
        case ESC:
            exit(1);
            break;
        default:
            break;
        }
    }
    if(iOver)
    {
        CheckDelete();
    }
    glutPostRedisplay();
}
