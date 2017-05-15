#include "myHead.h"

void InitBlock(void);   //图形界面初始化
void InitString(void);  //显示帮助信息
void CreateBlocks(void);
void WelcomeScreen(void);
void EndScreen(void);
void Down(int id);
void Key(unsigned char k, int x, int y);

int main(int argc,char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(400, 0);
    glutInitWindowSize(750, 720);
    WelcomeScreen();
    if(iStart)
    {
        InitBlock();
        glutCreateWindow("My_Tetris");
        InitString();
        glutDisplayFunc(&CreateBlocks);
        glutTimerFunc(iTimeS, Down, 1);
        glutKeyboardFunc(Key);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glutMainLoop();
    }
    else{
        EndScreen();
    }
}
