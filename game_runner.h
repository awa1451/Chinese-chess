#pragma once
void menu(); //菜单界面 
void run_game();//运行游戏 
void initialization();//初始化棋盘 
int addScore(int c);//加分 
void judge(int sx ,int sy ,int checkerboard[12][11]);//合法性判断  
void chess_move();//象棋移动判断 
int face_to_face();//明将判断 
int check(int checkerboard[12][11]);//将军判断 
int winning_judge();//胜负判断 
int sure_killed();//绝杀判断  
void renew();//重置checkerboard2[][]数组 


