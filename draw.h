#pragma once
void draw_map();//绘制游戏地图 
void draw_allchess(int checkerboard[12][11],int k);//绘制棋盘及所有棋子/除所选棋子外的所有棋子（播放动画时要单独绘制 
void draw_chess(int kind,int x,int y,int i,int j,int size);//绘制单个棋子 
void draw_sidebar();//绘制侧边栏 
void draw_information();//绘制对局状态信息
void draw_back_button();//绘制返回菜单按钮 
void draw_pause_button();//绘制暂停游戏按钮 
void draw_draw_button();//绘制和棋按钮 
void draw_backMove_button();//绘制悔棋按钮 
void visual_feedback();//绘制视觉反馈（放大第一次点击的棋子） 
void point_of_fall();//绘制落点提示(显示可落棋子的位置)	

void draw_continueGame_button(int *p);//绘制询问是否继续游戏按钮 


