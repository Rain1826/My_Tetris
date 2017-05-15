#include "myHead.h"

GLfloat afCurLoc[4][2] = {0};
int iScore = 0;
int iTimeS = 1000;

bool CheckConflict(int iLefRig)
{
    int i;
    for(i = 0; i < 4; ++ i)
    {
        double x = (afCurLoc[i][0] + 1) * 10;
        double y = (afCurLoc[i][1] + 1) * 10 + 0.5;
        x = x > 0 ? (x + 0.5) : (x - 0.5);
        if(iLefRig == 1)
        {
            if((int)x > 13 || (int)x < 1)
                break;
        }
        //判断是否发生冲突
        if(aiBlock[(int)y][(int)x] == 1)
        {
            break;
        }
    }
    if(i < 4)   return true;
    return false;
}

void Delete(int *empty)
{
    int i, j, pos;
    while(true)
    {
        i = 1;
        while(i < SIZE && empty[i] == 0)    ++ i;
        if(i >= SIZE)   break;
        j = i + 1;
        while(j < SIZE && empty[j] == -1)   ++ j;
        if(j >= SIZE)   break;
        else if(empty[j] != -1)
        {
            for(pos = 1; pos < SIZE - 6; ++ pos)
            {
                aiBlock[i][pos] = aiBlock[j][pos];
            }
            empty[i] = empty[j];    //将第i行与第j行的状态交换
            empty[j] = -1;
        }
    }
    for(i = 1; i < SIZE; ++ i)
    {
        if(empty[i] != 0)
        {
            for(j = 1; j < SIZE - 6; ++ j)
            {
                aiBlock[i][j] = 0;
            }
        }
    }
}

int CheckDelete(void)
{
    int i, j, count;
    bool is_need = false;
    int empty[SIZE];
    for(int i = 1; i < SIZE; ++ i)
    {
        empty[i] = -1;
    }
    for(i = 0; i < 4; ++ i)
    {
        //将坐标 (x,y) 转换成界面中对应的小格数
        double x = (afCurLoc[i][0] + 1) * 10 + 0.5;
        double y = (afCurLoc[i][1] + 1) * 10 + 0.5;
        aiBlock[(int)y][(int)x] = 1;
    }
    for(i = 1; i < SIZE; ++ i)
    {
        count = 0;
        for(j = 1; j < SIZE - 6; ++ j)
        {
            if(aiBlock[i][j] == 1)
                ++ count;
        }
        if(count == SIZE - 7)
        {
            empty[i] = 1;   //满行则置1
            ++ iScore;      //更新分数
            iTimeS -= 50;   //速度变快
            is_need = true; //需要消除则置为true
        }
        else if(count > 0 && count < 13)
        {
            empty[i] = 0;   //部分空。置为0
        }
    }
    if(is_need)
        Delete(empty);
}
