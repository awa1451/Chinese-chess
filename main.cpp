#include"game_runner.h"
#include"tools.h"
#include <stdio.h>
#include <graphics.h>
int main()
{
    initgraph(1000, 1000,INIT_RENDERMANUAL);
    setcaption("中国象棋");//设置窗口标题 
    menu();//运行游戏菜单函数 
    printf("已退出游戏\n");
	return 0;
}

