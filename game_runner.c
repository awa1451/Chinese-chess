#include"game_runner.h"//游戏代码 
#include"tools.h"//工具代码 
#include"animation.h"//动画代码 
#include"archive.h"//存档代码 
#include"draw.h"//绘图代码 
#include"linked_list.h"//链表代码 
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>
bool clickButton=false;//用于鼠标松发点击 
int checkerboard0[10][9]={0};//checkerboard0储存棋子大小信息，用于播放动画 
int checkerboard[10+2][9+2]={0};//checkerboard储存棋子类型及位置信息  -10代表没有  黑棋:0车  1马  5炮  2象  3士  4将  6卒  红棋:10俥 11傌 15炮 12相 13仕 14帅 16兵
int checkerboard2[14][13]={0};//checkerboard2储存棋子可落子位置信息  1代表对应的点可落子  10/0代表不能 
int sx=-1,fx=-1,sy=-1,fy=-1; //sx,fx记录第一次点击（start起点）棋子的坐标 sy,fy记录第二次点击（final终点）
int flag=0;//flag=0代表此次是第一次点击"开始游戏"
int flag2=0;//用于播放选定棋子放大动画 
int interfaces=1;//用于界面选择：0棋盘 1主菜单 2游戏说明 3游戏帮助 
int rounds=-1;//rounds回合储存回合次数 及 rounds%2==1时红方动棋 rounds%2==0时黑方动棋
int roundC=-1;//用于防止连续悔棋 
int General=1;//黑棋将军存在则General==1;不存在则 General==0;黑棋超时 General==2; 
int Marshal=1;//红棋元帅 
int REDscore=0,BLACKscore=0;//记分 
time_t start=0,end=0;//计时 
int allTime;//储存总耗时
int dt=0;//DELTA德尔塔time，时间差值，用于暂停游戏等情况时记录已耗时间从而在继续游戏时推算剩余时间 
long long int timeInfomation;//记录对局开始时间
int year,mon,day,hour,minu;
struct tm *timeinfo;
time_t rawtime;
int BlackTakeBace=1;//悔棋次数 
int RedTakeBace=1;

struct ListNode 
{	
	int rounds;
	int REDscore;
	int BLACKscore;
	int allTime;
	int year;
	int mon;
	int day;
	int hour;
	int min;
    struct ListNode *next;
};
struct ListNode *head,*current;
char s[10]; 

//ARGB颜色EGEARGB(A, R, G, B); 
color_t pinkColor = EGEARGB(0, 193, 102, 0); 
color_t sidebarColor = EGEARGB(0, 168, 106, 59); 
color_t chessColor = EGEARGB(0, 205, 146, 90); 
color_t grayColor = EGEARGB(0, 195, 195, 195); 
mouse_msg msg = {0};//鼠标信息结构体 
void menu()//创建主菜单及其分支 
{
	int i1=0,i2=0,i3=0,i4=0;
	PIMAGE imgMENU = newimage();getimage(imgMENU,"./image//menu.png");
	PIMAGE imgCHECKERBOARD = newimage();getimage(imgCHECKERBOARD,"./image//checkerboard.png");
	PIMAGE imgINSTRUCTIONS = newimage();getimage(imgINSTRUCTIONS,"./image//instructions.png");
	PIMAGE imgHELP = newimage();getimage(imgHELP,"./image//help.png");
	
	head=creatingList();
	current=head;
	readList(head);//从文件中读取链表
	while((current->next)!=NULL)//将current移至链表末尾 
		current=current->next;
	putList(head);
	
	int A=checkArchive();//检查是否存在存档 
	if(A==1)
	{//先读取存档,若玩家选择"重开"再重置地图 
		readArchive();
		checkerboard[fy][fx]=checkerboard[sy][sx];
		checkerboard[sy][sx]=-10; 
		sx=-1,fx=-1,sy=-1,fy=-1; 
		rounds++;
	}
	for ( ; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			msg = getmouse();
		}
		switch(interfaces)//选择界面 
		{
			case 0://显示棋盘界面 
			{
				//openingAnimation();//开场动画 
				if(A==1)//检测到存在未完成的对局 
					draw_continueGame_button(&A);//绘制询问是否继续游戏按钮 
				else
					run_game();//运行游戏函数 
				break;
			}
			case 1://显示主菜单
			{
				cleardevice();
				putimage(0, 0, imgMENU);
				
				if(i1<79||i2<79||i3<79||i4<79){i1+=2;i2+=2;i3+=2;i4+=2;}
				setcolor(WHITE);
				setbkmode(1);//设置字体背景透明 
				setfont(i1,0,"华文行楷");xyprintf(350-(i1-80),350-(i1-80),"开始游戏");
				setfont(i2,0,"华文行楷");xyprintf(350-(i2-80),450-(i2-80),"游戏说明");
				setfont(i3,0,"华文行楷");xyprintf(350-(i3-80),550-(i3-80),"游戏帮助");
				setfont(i4,0,"华文行楷");xyprintf(350-(i4-80),650-(i4-80),"退出游戏");
				setfont(30,0,"华文行楷");xyprintf(0,970,"清空链表");
				if(msg.x>0&&msg.x<100&&msg.y>970&&msg.y<1000)
				{
					setcolor(RED);
					setfont(30,0,"华文行楷");
					xyprintf(0,970,"清空链表");
					if( msg.is_left() )
					{
						if( msg.is_down() )
							clickButton = true;
						else 
						{	//左键抬起，执行事件
							if (clickButton)
							{
								clickButton = false;
								clearList(head);
								current=head;
								saveList(head); 
								delay(500);
								putList(head);
							}
						}
					}
				}
				//开始游戏选项按键判定 
				if(msg.x>350&&msg.x<650&&msg.y>350&&msg.y<430)
				{
					setcolor(RED);
					setfont(i1,0,"华文行楷");
					xyprintf(350-(i1-80),350-(i1-80),"开始游戏");
					if(i1>79&&i1<90)i1+=3;
					if( msg.is_left() )
					{
						if( msg.is_down() )
							clickButton = true;
						else 
						{	//左键抬起，执行事件
							if (clickButton)
							{
								time(&end);
								start=end-dt;
								interfaces=0;//界面0(棋盘）
								clickButton = false;
							}
						}
					}
				}else{if(i1>80)i1--;}
				//游戏说明选项按键判定 
				if(msg.x>350&&msg.x<650&&msg.y>450&&msg.y<530)
				{
					setcolor(RED);
					setfont(i2,0,"华文行楷");
					xyprintf(350-(i2-80),450-(i2-80),"游戏说明");
					if(i2>79&&i2<90)i2+=3;
					if( msg.is_left() )
					{
						if( msg.is_down() )
							clickButton = true;
						else 
						{
							if (clickButton)
							{
								interfaces=2;//界面2(游戏说明）
							}
						}
					}
				}else{if(i2>80)i2--;}if(i2>93)i2-=3;
				//游戏帮助选项按键判定 
				if(msg.x>350&&msg.x<650&&msg.y>550&&msg.y<630)
				{
					setcolor(RED);
					setfont(i3,0,"华文行楷");
					xyprintf(350-(i3-80),550-(i3-80),"游戏帮助");
					if(i3>79&&i3<90)i3+=3;
					if( msg.is_left() )
					{
						if( msg.is_down() )
							clickButton = true;
						else 
						{
							if (clickButton)
							{
								interfaces=3;//界面3(游戏帮助） 
							}
						}
					}
				}else{if(i3>80)i3--;}if(i3>93)i3-=3;
				//退出游戏选项按键判定 
				if(msg.x>350&&msg.x<650&&msg.y>650&&msg.y<730)
				{
					setcolor(RED);
					setfont(i4,0,"华文行楷");
					xyprintf(350-(i4-80),650-(i4-80),"退出游戏");
					if(i4>79&&i4<90)i4+=3;
					if( msg.is_left() )
					{
						if( msg.is_down() )
							clickButton = true;
						else 
						{
							if (clickButton)
							{
								putList(head);
								return ;
							}
						}
					}
				}else{if(i4>80)i4--;}if(i4>93)i4-=3;
				break;
			}
			case 2://显示游戏说明界面
			{
				cleardevice();
				putimage(0, 0, imgINSTRUCTIONS);
				break;
			}
		
			case 3://显示游戏帮助界面
			{
				cleardevice();
				putimage(0, 0, imgHELP);
				break;
			}
		}
		//只要不在界面1（主菜单）就显示 
		if(interfaces!=1&&interfaces!=0)//进入游戏（棋盘）时，单独调用draw_back_button()绘制"返回菜单"按钮
		{
			draw_back_button();//绘制返回菜单 
		}
	}
}


void run_game()//运行游戏
{
	time(&end);
	initialization();//初始化棋盘 
	draw_map();//绘制棋盘 
	winning_judge();//胜负判定 
	point_of_fall();//落点提示(显示可落棋子的位置) 
	chess_move();//象棋移动 
}


int check(int checkerboard[12][11])//将军判断 
{
	int i,j,c=0;
	int x0,y0,x1,y1;
	for(i=1;i<11;i++)
	{
		if(i>3&&i<8)continue;
		for(j=4;j<7;j++)
		{
			if(checkerboard[i][j]==4)
			{
				x0=j;y0=i;
				break;
			}
			if(checkerboard[i][j]==14)
			{
				x1=j; y1=i;
				break;
			}
		}
	}
	for(i=1;i<11;i++)
	{
		for(j=1;j<10;j++)
		{
			if(checkerboard[i][j]==-10)continue;
			judge(j,i,checkerboard);
			if(checkerboard2[y0+1][x0+1]==1&&(c==0||c==10))//黑棋被将军 
			{
				c++;
			}
			if(checkerboard2[y1+1][x1+1]==1&&(c==0||c==1))//红棋被将军 
			{
				c+=10;
			}
		}
	}
	return c;
}


int sure_killed(int z)//绝杀判断 
{
	int i,j,k,l,m,n,c;
	int arr[12][11];
	int arr2[14][13];
	for(m=0;m<12;m++)
	{
		for(n=0;n<11;n++)
		{
			arr[m][n]=checkerboard[m][n];
		}
	}
	if(z==1)//z==1判断黑棋是否被绝杀 
	{
		for(i=1;i<11;i++)//遍历被将军一方所有棋子可以移动的位置，如果没有任何一种走法解除将军则被绝杀 
		{
			for(j=1;j<10;j++)
			{
				if(arr[i][j]/10==0)
				{
					judge(j,i,arr);	
					for(m=0;m<12;m++)
					{
						for(n=0;n<11;n++)
						{
							arr2[m][n]=checkerboard2[m][n];
						}
					}
					for(k=1;k<11;k++)
					{
						for(l=1;l<10;l++)
						{
							if(checkerboard2[k+1][l+1]==1)
							{
								arr[k][l]=arr[i][j];
								arr[i][j]=-10;
								c=check(arr);
								if(c==1||c==11)
								{
									for(m=0;m<12;m++)
									{
										for(n=0;n<11;n++)
										{
											arr[m][n]=checkerboard[m][n];
										}
									}
									for(m=0;m<12;m++)
									{
										for(n=0;n<11;n++)
										{
										checkerboard2[m][n]=arr2[m][n];
										}
									}
								}
								else
								{
									return 0;
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{
		for(i=1;i<11;i++)
		{
			for(j=1;j<10;j++)
			{
				if(arr[i][j]/10==1)
				{
					judge(j,i,arr);	
					for(m=0;m<12;m++)
					{
						for(n=0;n<11;n++)
						{
							arr2[m][n]=checkerboard2[m][n];
						}
					}
					for(k=1;k<11;k++)
					{
						for(l=1;l<10;l++)
						{
							if(checkerboard2[k+1][l+1]==1)
							{
								arr[k][l]=arr[i][j];
								arr[i][j]=-10;
								c=check(arr);
								if(c==10||c==11)
								{
									for(m=0;m<12;m++)
									{
										for(n=0;n<11;n++)
										{
											arr[m][n]=checkerboard[m][n];
										}
									}
									for(m=0;m<12;m++)
									{
										for(n=0;n<11;n++)
										{
										checkerboard2[m][n]=arr2[m][n];
										}
									}
								}
								else
								{
									return 0;
								}
							}
						}
					}
				}
			}
		}
	}
	return 1;
} 


int face_to_face()//明将判断 
{	
	time(&end);
	int dtt=end-start;
	int st=checkerboard[sy][sx];
	int ft=checkerboard[fy][fx];
	checkerboard[fy][fx]=checkerboard[sy][sx];
	checkerboard[sy][sx]=-10;
	int i=0,j=0; 
	int x0=-10,x1=-10,y0=-10,y1=-10;
	for(i=1;i<11;i++)
	{
		if(i>3&&i<8)continue;
		for(j=4;j<7;j++)
		{
			if(checkerboard[i][j]==14){x1=j;y1=i;}
			if(checkerboard[i][j]==4) {x0=j;y0=i;}
		}
	}
	if(x0==x1)
	{
		for(i=y0+1;i<y1;i++)
		{
			if(checkerboard[i][x0]!=-10)
			{
				i=100;//将帅之间只要有一个棋子就将i设为100
			}
		}
		if(i!=101)//将帅之间只没有棋子--明将了！读档撤回该操作 
		{
			readArchive();
			time(&end);
			start=end-dtt;
			rounds++;
			checkerboard[fy][fx]=checkerboard[sy][sx];
			checkerboard[sy][sx]=-10; 
			sx=-1,fx=-1,sy=-1,fy=-1;
			flag=1;
			Animation(3);
			delay_ms(600);
			return 1;
		}
	}
	checkerboard[sy][sx]=st;
	checkerboard[fy][fx]=ft;
	return 0;
}


void initialization()//初始化棋盘 
{
	if(flag==0)//flag=0代表此次是第一次点击"开始游戏"
	{
		int i,j;
		allTime=0;
		time(&rawtime);
		timeinfo=localtime(&rawtime);
		year=(timeinfo->tm_year+1900);
		mon=(timeinfo->tm_mon + 1);
		day=(timeinfo->tm_mday);
		hour=(timeinfo->tm_hour);
		minu=(timeinfo->tm_min);
		BlackTakeBace=1;RedTakeBace=1;
		BLACKscore=0;REDscore=0;
		flag=1;rounds=1;
		sx=-1;sy=-1;fx=-1;fy=-1;
		renew();//重置checkerboard2数组 
		time(&start);
		for(i=0;i<12;i++)
			for(j=0;j<11;j++)
				checkerboard[i][j]=-10;
		//遍历棋盘每个位置，按规则设置棋子  
		for(i=1;i<11;i++)
		{
			for(j=1;j<10;j++)
			{
				//设置黑棋信息
				if(i==1)
				{
					if(j<6)
					{
						checkerboard[i][j]=j-1;
					}
					else
					{
						checkerboard[i][j]=9-j;
					}
				}
				if( i==3&&(j==2||j==8) )
				{
					checkerboard[i][j]=5;
				}
				if( i==4&&j%2==1 )
				{
					checkerboard[i][j]=6;
				}
				//设置红棋信息
				if(i==10)
				{
					if(j<6)
					{
						checkerboard[i][j]=j+10-1;
					}
					else
					{
						checkerboard[i][j]=19-j;
					}
				}
				if( i==8&&(j==2||j==8) )
				{
					checkerboard[i][j]=5+10;
				}
				if( i==7&&j%2==1 )
				{
					checkerboard[i][j]=6+10;
				}
			}
		}
	}
} 


int addScore(int c)//加分 
{
	if(c>9)c=c%10;
	switch(c)
	{//对于黑棋  0车  1马  5炮  2象  3士  4将  6卒  对于红棋 10俥 11傌 15炮 12相 13仕 14帅 16兵
		case 0:return 20;
		case 1:return 20;
		case 2:return 20;
		case 3:return 20;
		case 4:return 100;
		case 5:return 20;
		case 6:return 5;
		default:return 0;
	}
}


int winning_judge()//胜负判断
{
	General=0;//黑棋将军存在则General==1;不存在则 General==0;黑棋超时 General==2;
	Marshal=0;//红棋元帅 
	int i,j;
	for(i=1;i<11;i++)//检测双方将军是否存在
	{
		if(i>3&&i<8)continue;
		for(j=4;j<7;j++)
		{
			if(checkerboard[i][j]==14)Marshal=1;
			if(checkerboard[i][j]==4)General=1;
		}
	}
	if(rounds%2==1)//检测是否超时 
	{//红棋超时 
		if((45+start-end)<1)
		{
			rounds++;
			Marshal=2; 
		}
	}
	else
	{//黑棋超时 
		if((45+start-end)<1)
		{
			rounds++;
			General=2; 
		}
	}
	if( General==0||General==2 )//黑棋将军被吃或超时，红方胜出 
	{
		allTime+=end-start;
		extendingList(&current);//延长链表
		saveList(head);//保存链表
		putList(head);
		if((45+start-end)<1)rounds--;
		flag=0;
		interfaces=1;
		saveGame();
		draw_allchess(checkerboard,0);
		draw_information();
		setcolor(RED);
		sx=-1;
		Animation(1);
		shadow(0,0,880,1000,4);
		for ( ; is_run(); delay_fps(60))
		{
			while (mousemsg())
			{
				msg = getmouse();
				if( msg.is_right() )
				{
					return 1;
				}
			}
		}
	}
	if( Marshal==0||Marshal==2 )//红棋将军被吃或超时，黑方胜出 
	{ 
		allTime+=end-start;
		extendingList(&current);
		saveList(head);
		putList(head);
		if((45+start-end)<1)rounds--;
		flag=0;
		interfaces=1;
		saveGame();
		draw_allchess(checkerboard,0);
		draw_information();
		setcolor(BLACK);
		sx=-1;
		Animation(0);
		shadow(0,0,880,1000,4);
		for ( ; is_run(); delay_fps(60))
		{
			while (mousemsg())
			{
				msg = getmouse();
				if( msg.is_right() )
				{
						return 1;
				}
			}
		}
	}
	return 0;
}


void chess_move()//象棋移动
{
	int i,j,k,l;
	for(i=1;i<11;i++)
	{
		for(j=1;j<10;j++)
		{
			int x1=66+94*(j-1),y1=71+93*(i-1);//遍历所有象棋棋子位置中心点坐标
			if( ((msg.x-x1)*(msg.x-x1)+(msg.y-y1)*(msg.y-y1))<45*45 )
			{
				if(checkerboard[i][j]/10==1&&rounds%2==1&&checkerboard0[i-1][j-1]<8) 
				{
					checkerboard0[i-1][j-1]+=4;
				}
				if(checkerboard[i][j]/10==0&&rounds%2==0&&checkerboard0[i-1][j-1]<8) 
				{
					checkerboard0[i-1][j-1]+=4;
				}
				if(msg.is_left()==1)//松发鼠标点击 
				{
					if(msg.is_down())
						clickButton = true;//检测点击的按钮
					else 
					{	//左键抬起，执行事件
						if (clickButton)
						{
							clickButton = false;//重置状态 
							if(flag==1)//第一次选择 
							{
								if(checkerboard[i][j]!=-10)
								{
									sx=j;
									sy=i;
									flag=2;
									flag2=1;
									judge(sx,sy,checkerboard);
								}
								else
								{
									break;
								} 
								if(rounds%2==1)
								{ //红方动棋时如果选了黑棋就break; 
									if(checkerboard[sy][sx]-10<0 )
									{ 
										Animation(6);
										sx=-1;sy=-1;fx=-1;fy=-1;flag=1;
										break; 
									}
								}
							else
								{ //黑方动棋时如果选了红棋就break; 
									if(checkerboard[sy][sx]>9 )
									{ 
										Animation(6);
										sx=-1;sy=-1;fx=-1;fy=-1;flag=1;
										break; 
									}
								}
							}
							else//第二次选择 
							{
								fx=j; fy=i; flag=1;//重置
								if(sx==fx&&sy==fy)//重复选择则重置 
								{
									sx=-1;sy=-1;fx=-1;fy=-1;
									break; 
								}
								if( checkerboard[fy][fx]!=-10&&checkerboard[sy][sx]/10==checkerboard[fy][fx]/10 )//不能吃同自己的棋子 
								{
									sx=fx;sy=fy;fx=-1;fy=-1;
									flag=2;
									flag2=1;
									judge(sx,sy,checkerboard);
									break; 
								} 
								if( checkerboard2[fy+1][fx+1]==1 )//checkerboard2[][]==1可以移动 
								{
									if(face_to_face())return ;
									saveGame();
									if(rounds%2==1)//加分 
										REDscore+=addScore(checkerboard[fy][fx]);
									else
										BLACKscore+=addScore(checkerboard[fy][fx]);
									Animation(7);
									if(checkerboard[fy][fx]/10!=checkerboard[sy][sx]/10&&checkerboard[fy][fx]!=-10)Animation(4);
									checkerboard[fy][fx]=checkerboard[sy][sx];
									checkerboard[sy][sx]=-10;
									draw_map();
									if(winning_judge())return ;//胜负判断 
									switch( check( checkerboard ) )//将军判断  
									{
										case 1://黑方被将军 
											if(sure_killed(1))//绝杀判断 
											{
												flag=0; 
												allTime+=end-start;
												interfaces=1;
												saveGame();
												flag=200;//flag==200代表绝杀 
												Animation(1);
												flag=0; 
												shadow(0,0,880,1000,4);
												for ( ; is_run(); delay_fps(60))
												{
													while (mousemsg())
													{
														msg = getmouse();
														if( msg.is_right() )
														{
															return ;
														}
													}
												}
											}
											Animation(2);
											break; 
										case 10://红方被将军 
											if(sure_killed(10))
											{
												flag=0; 
												allTime+=end-start;
												interfaces=1;
												saveGame();
												flag=200;
												Animation(0);
												flag=0;
												shadow(0,0,880,1000,4);
												for ( ; is_run(); delay_fps(60))
												{
													while (mousemsg())
													{
														msg = getmouse();
														if( msg.is_right() )
														{
															return ;
														}
													}
												}
											}
											Animation(2);
											break; 
										case 11://同时被将军 
											Animation(2);
											break; 
										default:break;
									}
									allTime+=end-start;
									time(&start);
									rounds++;
									roundC=rounds;//如果悔棋了则roundC>rounds;
									for(k=0;k<10;k++)
										for(l=0;l<9;l++)
											checkerboard0[k][l]=0;
								}
								sx=-1;sy=-1;fx=-1;fy=-1;
							}
						}
					}
				}
			}
			else
				if(checkerboard0[i-1][j-1]>0)
					checkerboard0[i-1][j-1]-=1;
		}
	}
} 


void judge(int sx ,int sy ,int checkerboard[12][11])//合法性判断 
{
	renew();
	int chess=checkerboard[sy][sx],i,j,k,l,c;
	if(chess>9)
	{
		chess-=10;
	}
	switch(chess)
	{
		case 0://车 
			{
				for(k=1;k<10-sx;k++)//右 
				{
					if(checkerboard[sy][sx+k]==-10)
						checkerboard2[sy+1][sx+1+k]=1;
					else
					{
						if( checkerboard[sy][sx+k]/10!=checkerboard[sy][sx]/10 )
							checkerboard2[sy+1][sx+1+k]=1;
						break;
					}
				}
				for(k=1;k<sx ;k++)//左 
				{
					if(checkerboard[sy][sx-k]==-10)
						checkerboard2[sy+1][sx+1-k]=1;
					else
					{
						if( checkerboard[sy][sx-k]/10!=checkerboard[sy][sx]/10 )
							checkerboard2[sy+1][sx+1-k]=1;
						break;
					} 
				}
				for(k=1;k<sy;k++)//上 
				{
					if(checkerboard[sy-k][sx]==-10)
						checkerboard2[sy+1-k][sx+1]=1;
					else
					{
						if( checkerboard[sy-k][sx]/10!=checkerboard[sy][sx]/10 )
							checkerboard2[sy+1-k][sx+1]=1;
						break;
					} 
				}
				for(k=1;k<11-sy;k++)//下 
				{
					if(checkerboard[sy+k][sx]==-10)
						checkerboard2[sy+1+k][sx+1]=1;
					else
					{
						if( checkerboard[sy+k][sx]/10!=checkerboard[sy][sx]/10 )
							checkerboard2[sy+1+k][sx+1]=1;
						break;
					} 
				}
				break;
			}
		case 1://马 
			{
				if(checkerboard[sy][sx+1]==-10)//右 
				{
					if( checkerboard[sy-1][sx+2]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1-1][sx+1+2]=1;
					if( checkerboard[sy+1][sx+2]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1+1][sx+1+2]=1;
				}
				if(checkerboard[sy][sx-1]==-10)//左 
				{
					if( checkerboard[sy-1][sx-2]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1-1][sx+1-2]=1;
					if( checkerboard[sy+1][sx-2]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1+1][sx+1-2]=1;
				}
				if(checkerboard[sy+1][sx]==-10)//上 
				{
					if( checkerboard[sy+2][sx-1]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1+2][sx+1-1]=1;
					if( checkerboard[sy+2][sx+1]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1+2][sx+1+1]=1;
				}
				if(checkerboard[sy-1][sx]==-10)//下  
				{
					if( checkerboard[sy-2][sx-1]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1-2][sx+1-1]=1;
					if( checkerboard[sy-2][sx+1]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1-2][sx+1+1]=1;
				}
				break;
			}
		case 2://相 
			{
				if(checkerboard[sy+1][sx+1]==-10 )//右下
					if( checkerboard[sy+2][sx+2]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1+2][sx+1+2]=1;
				if(checkerboard[sy-1][sx+1]==-10 )//右上 
					if( checkerboard[sy-2][sx+2]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1-2][sx+1+2]=1;
				if(checkerboard[sy+1][sx-1]==-10 )//左下
					if( checkerboard[sy+2][sx-2]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1+2][sx+1-2]=1;
				if(checkerboard[sy-1][sx-1]==-10 )//左下
					if( checkerboard[sy-2][sx-2]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1-2][sx+1-2]=1;
				checkerboard2[8][2]=0;checkerboard2[8][6]=0;checkerboard2[8][10]=0;
				checkerboard2[5][2]=0;checkerboard2[5][6]=0;checkerboard2[5][10]=0;
				
				break;
			}
		case 3://士
			{
				//黑方 
				if( (sx==4||sx==6)&&(sy==1||sy==3) )
				{
					if( checkerboard[2][5]/10!=checkerboard[sy][sx]/10 )checkerboard2[3][6]=1;
				}
				if(sx==5&&sy==2)
				{
					if( checkerboard[1][4]/10!=checkerboard[sy][sx]/10 )checkerboard2[2][5]=1;
					if( checkerboard[1][6]/10!=checkerboard[sy][sx]/10 )checkerboard2[2][7]=1;
					if( checkerboard[3][4]/10!=checkerboard[sy][sx]/10 )checkerboard2[4][5]=1;
					if( checkerboard[3][6]/10!=checkerboard[sy][sx]/10 )checkerboard2[4][7]=1;
				}
				//红方 
				if( (sx==4||sx==6)&&(sy==10||sy==8))
				{
					if( checkerboard[9][5]/10!=checkerboard[sy][sx]/10 )checkerboard2[10][6]=1;
				}
				if(sx==5&&sy==9)
				{
					if( checkerboard[10][6]/10!=checkerboard[sy][sx]/10 )checkerboard2[11][7]=1;
					if( checkerboard[8][4]/10!=checkerboard[sy][sx]/10 )checkerboard2[9][5]=1;
					if( checkerboard[10][4]/10!=checkerboard[sy][sx]/10 )checkerboard2[11][5]=1;
					if( checkerboard[8][6]/10!=checkerboard[sy][sx]/10 )checkerboard2[9][7]=1;
				}
				break;
			}
		case 4://将、帅
			{
				
				if( checkerboard[sy+1][sx]/10!=checkerboard[sy][sx]/10&&(sy==1||sy==2||sy==8||sy==9) )checkerboard2[sy+1+1][sx+1]=1;
				if( checkerboard[sy-1][sx]/10!=checkerboard[sy][sx]/10&&(sy==3||sy==2||sy==10||sy==9) )checkerboard2[sy+1-1][sx+1]=1;
				if( checkerboard[sy][sx-1]/10!=checkerboard[sy][sx]/10&&sx!=4 )checkerboard2[sy+1][sx+1-1]=1;
				if( checkerboard[sy][sx+1]/10!=checkerboard[sy][sx]/10&&sx!=6 )checkerboard2[sy+1][sx+1+1]=1;
				break;
			}
		case 5://炮 
			{
				for(c=0,k=1;k<10-sx;k++)//右 
				{
					if(c==0)
					{
						if(checkerboard[sy][sx+k]==-10)
							checkerboard2[sy+1][sx+1+k]=1;
						else
							{
								c=1;
								continue;
							}
					}
					if(c==1)
					{
						if(checkerboard[sy][sx+k]!=-10)
						{
							if( checkerboard[sy][sx+k]/10!=checkerboard[sy][sx]/10 )
								checkerboard2[sy+1][sx+1+k]=1;
							k=100;
						}
					}
				}
				for(c=0,k=1;k<sx;k++)//左 
				{
					if(c==0)
					{
						if(checkerboard[sy][sx-k]==-10)
							checkerboard2[sy+1][sx+1-k]=1;
						else
							{
								c=1;
								continue;
							}
					}
					if(c==1)
					{
						if(checkerboard[sy][sx-k]!=-10)
						{
							if( checkerboard[sy][sx-k]/10!=checkerboard[sy][sx]/10 )
								checkerboard2[sy+1][sx+1-k]=1;
							k=100;
						}
					}
				}
				for(c=0,k=1;k<sy;k++)//上 
				{
					if(c==0)
					{
						if(checkerboard[sy-k][sx]==-10)
							checkerboard2[sy+1-k][sx+1]=1;
						else
							{
								c=1;
								continue;
							}
					}
					if(c==1)
					{
						if(checkerboard[sy-k][sx]!=-10)
						{
							if( checkerboard[sy-k][sx]/10!=checkerboard[sy][sx]/10 )
								checkerboard2[sy+1-k][sx+1]=1;
							k=100;
						}
					}
				}
				for(c=0,k=1;k<11-sy;k++)//下 
				{
					if(c==0)
					{
						if(checkerboard[sy+k][sx]==-10)
							checkerboard2[sy+1+k][sx+1]=1;
						else
							{
								c=1;
								continue;
							}
					}
					if(c==1)
					{
						if(checkerboard[sy+k][sx]!=-10)
						{
							if( checkerboard[sy+k][sx]/10!=checkerboard[sy][sx]/10 )
								checkerboard2[sy+1+k][sx+1]=1;
							k=100;
						}
					}
				}
				break;
			}
		case 6:
			{
				if( checkerboard[sy][sx]>9 )
					if(sy>5)//未过河 
					{
						if( checkerboard[sy-1][sx]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1-1][sx+1]=1;
					}
					else
					{
						if( checkerboard[sy-1][sx]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1-1][sx+1]=1;
						if( checkerboard[sy][sx+1]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1][sx+1+1]=1;
						if( checkerboard[sy][sx-1]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1][sx+1-1]=1;
					}
					
				if( checkerboard[sy][sx]<9&&checkerboard[sy][sx]>-1 )
					if(sy<6)//未过河 
					{
						if( checkerboard[sy+1][sx]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1+1][sx+1]=1;
					}
					else
					{
						if( checkerboard[sy+1][sx]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1+1][sx+1]=1;
						if( checkerboard[sy][sx+1]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1][sx+1+1]=1;
						if( checkerboard[sy][sx-1]/10!=checkerboard[sy][sx]/10 )checkerboard2[sy+1][sx+1-1]=1;
					}
				
				break;
			}
		default:break;
	}
}


void renew()//重置checkerboard2数组 
{
	int i,j;
	for(i=0;i<14;i++)
		for(j=0;j<13;j++)
			checkerboard2[i][j]=10;
	for(i=2;i<12;i++)
		for(j=2;j<11;j++)
			checkerboard2[i][j]=0;
} 


