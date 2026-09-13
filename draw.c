#include"draw.h"
#include"tools.h"
#include"game_runner.h"
#include"archive.h"
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<stdbool.h>
#include<time.h>
extern int checkerboard0[10][9],checkerboard[12][11],checkerboard2[14][13],rounds,roundC,sx,sy,fx,fy,flag,flag2,BLACKscore,REDscore,interfaces,dt;
extern int BlackTakeBace,RedTakeBace;
extern color_t pinkColor;
extern color_t chessColor;
extern color_t grayColor;
extern time_t start,end;
extern mouse_msg msg;
extern bool clickButton;
void draw_map()//绘制游戏地图 
{ 
	draw_allchess(checkerboard,0);//绘制背景及所有棋子
	draw_sidebar();//绘制侧边栏 
} 


void draw_allchess(int checkerboard[12][11],int k)//绘制背景及所有棋子  
{
	cleardevice();
	PIMAGE imgCHECKERBOARD = newimage();getimage(imgCHECKERBOARD,"./image//checkerboard.png");
	putimage(0, 0, imgCHECKERBOARD);
	delimage(imgCHECKERBOARD);
	int i,j;
	for(i=1;i<6;i++)//遍历棋盘，根据checkerboard[][]信息摆放棋子
	{
		for(j=1;j<5;j++)
		{
			if(checkerboard[i][j]!=-10)
			{
				if(k==1&&sx==j&&sy==i)
					continue;
				draw_3D(66+94*j-94,72+93*i-94,45+checkerboard0[i-1][j-1]*1.2,3+checkerboard0[i-1][j-1]*0.2); //3D效果 
				draw_chess(checkerboard[i][j],66+94*j-94 ,72+93*i-94,i,j,75);
			}
		}
		for(j=9;j>4;j--)
		{
			if(checkerboard[i][j]!=-10)
			{
				if(k==1&&sx==j&&sy==i)
					continue;
				draw_3D(66+94*j-94,72+93*i-94,45+checkerboard0[i-1][j-1]*1.2,3+checkerboard0[i-1][j-1]*0.2);
				draw_chess(checkerboard[i][j],66+94*j-94 ,72+93*i-94,i,j,75);
			}
		}
	}
	for(i=10;i>5;i--)
	{
		for(j=1;j<5;j++)
		{
			if(checkerboard[i][j]!=-10)
			{
				if(k==1&&sx==j&&sy==i)
					continue;
				draw_3D(66+94*j-94,72+93*i-94,45+checkerboard0[i-1][j-1]*1.2,3+checkerboard0[i-1][j-1]*0.2);
				draw_chess(checkerboard[i][j],66+94*j-94 ,72+93*i-94,i,j,75);
			}
		}
		for(j=9;j>4;j--)
		{
			if(checkerboard[i][j]!=-10)
			{
				if(k==1&&sx==j&&sy==i)
					continue;
				draw_3D(66+94*j-94,72+93*i-94,45+checkerboard0[i-1][j-1]*1.2,3+checkerboard0[i-1][j-1]*0.2);
				draw_chess(checkerboard[i][j],66+94*j-94 ,72+93*i-94,i,j,75);
			}
		}
	}
	visual_feedback();//视觉反馈(框选第一次点击的棋子)
}


void draw_chess(int kind,int x,int y,int i,int j,int size)//绘制单个棋子 
{
	int d=(size-75)*1.2;
	setcolor(BLACK);
	setfillcolor(pinkColor);
	if(size!=75)
	{
		fillellipse(x,y,size-30,size-30);
		setfillcolor(chessColor);
		fillellipse(x,y,size-39,size-39);
		setfont(size*1.3,0,"华文行楷");
	}
	else
	{
		d+=checkerboard0[i-1][j-1]*1.2;
		fillellipse(x,y,size-30+checkerboard0[i-1][j-1],size-30+checkerboard0[i-1][j-1]);
		setfillcolor(chessColor);
		fillellipse(x,y,size-35+checkerboard0[i-1][j-1],size-35+checkerboard0[i-1][j-1]);
		setfont(75+checkerboard0[i-1][j-1]*2.5,0,"华文行楷");
	}
	switch(kind)
	{//对于黑棋  0车  1马  5炮  2象  3士  4将  6卒  对于红棋 10俥 11傌 15炮 12相 13仕 14帅 16兵
		case 0:
			xyprintf(x-33-d,y-33-d ,"车");break;
		case 1:
			xyprintf(x-33-d,y-33-d ,"马");break;
		case 2:
			xyprintf(x-33-d,y-33-d ,"象");break;
		case 3:
			xyprintf(x-33-d,y-33-d ,"士");break;
		case 4:
			xyprintf(x-33-d,y-33-d ,"将");break;
		case 5:
			xyprintf(x-36-d,y-36-d ,"炮");break;
		case 6:
			xyprintf(x-33-d,y-33-d ,"卒");break;
		case 10:
			setcolor(RED);xyprintf(x-33-d,y-33-d*0.8 ,"车");break;
		case 11:
			setcolor(RED);xyprintf(x-36-d,y-36-d*0.8 ,"马");break;
		case 12:
			setcolor(RED);xyprintf(x-36-d,y-36-d*0.8 ,"相");break;
		case 13:
			setcolor(RED);xyprintf(x-36-d,y-36-d*0.8 ,"仕");break;
		case 14:
			setcolor(RED);xyprintf(x-36-d,y-30-d*0.8 ,"帅");break;
		case 15:
			setcolor(RED);xyprintf(x-36-d,y-36-d*0.8 ,"炮");break;
		case 16:
			setcolor(RED);xyprintf(x-36-d,y-36-d*0.8 ,"兵");break;
		default:break;
	}
}


void draw_sidebar()//绘制侧边栏 
{
	draw_back_button();//绘制返回菜单按钮  
	draw_pause_button();//绘制暂停游戏按钮 
	draw_draw_button();//绘制和棋按钮 
	draw_information();//绘制对局状态信息
	draw_backMove_button();//绘制悔棋按钮 
}


void draw_information()//绘制对局状态信息
{
	if(rounds%2==1)//红方回合 
	{
		setcolor(RED);
		rectangle(883,490,999,880);
		
		setcolor(WHITE);
		setfont(28,0,"隶书");
		xyprintf(884,489,"红方回合");
		xyprintf(884,519,"剩余时间");
		setcolor(RED);
		setfont(27,0,"隶书");
		xyprintf(885,490,"红方回合");
		xyprintf(885,520,"剩余时间");
		
		if(45+start-end>15)
		{
			setfont(50,0,"Kristen ITC");
			setcolor(WHITE);
			xyprintf(900,550,"%d",45+start-end);
		}
		else
		{
			setfont(80,0,"Kristen ITC");
			setcolor(RED);
			xyprintf(900,530,"%d",45+start-end);
		}
		
		setcolor(BLACK);
		setfont(30,0,"隶书");
		xyprintf(885,100,"黑方");
		rectangle(883,100,999,490);
	}
	else//黑方回合 
	{
		setcolor(BLACK);
		rectangle(883,100,999,490);
	
		setcolor(WHITE);
		setfont(28,0,"隶书");
		xyprintf(884,99,"黑方回合");
		xyprintf(884,129,"剩余时间");
		setcolor(BLACK);
		setfont(27,0,"隶书");
		xyprintf(885,100,"黑方回合");
		xyprintf(885,130,"剩余时间");
		if(45+start-end>15)
		{
			setfont(50,0,"Kristen ITC");
			setcolor(WHITE);
			xyprintf(900,160,"%d",45+start-end);
		}
		else
		{
			setfont(80,0,"Kristen ITC");
			setcolor(RED);
			xyprintf(900,140,"%d",45+start-end);
		}
		setcolor(RED);
		setfont(30,0,"隶书");
		xyprintf(885,490,"红方");
		rectangle(883,490,999,880);
	} 
	setfont(20,0,"隶书");setcolor(WHITE);
	xyprintf(885,600,"分数 %d",REDscore);//显示分数 
	xyprintf(885,210,"分数 %d",BLACKscore);
	xyprintf(885,900,"回合 %d",(rounds+1)/2 );
}


void draw_back_button()//绘制返回菜单 
{
	setfont(30,0,"华文行楷");
	setcolor(BLACK);
	roundedRectangle(882,1,998,30);
	setcolor(WHITE);
	xyprintf(882,0,"返回菜单");
	if(msg.x>880&&msg.x<1000&&msg.y>0&&msg.y<25)
	{
		setcolor(GREEN);
		roundedRectangle(882,1,998,30);
		setcolor(RED);
		xyprintf(882,0,"返回菜单 ");
		if( msg.is_left() )
		{
			interfaces=1;//界面1（主菜单） 
			dt=end-start;
		}
	}
} 


void draw_pause_button()//绘制暂停游戏按钮 
{
	setfont(30,0,"华文行楷");
	setcolor(BLACK);
	roundedRectangle(882,33,998,62);
	setcolor(WHITE);
	xyprintf(882,33,"暂停游戏 ");
	if(msg.x>880&&msg.x<1000&&msg.y>31&&msg.y<61)
	{
		setcolor(RED);
		xyprintf(882,33,"暂停游戏 ");
		setcolor(GREEN);
		roundedRectangle(882,33,998,62);
		if( msg.is_left() )
		{
			if( msg.is_down() )
				clickButton = true;
			else 
			{
				if (clickButton)
				{
					setfillcolor(grayColor);
					bar(882,0,1000,100);
					rectangle(883,1,999,99);
					setfont(40,0,"华文行楷");
					xyprintf(882,0,"  游戏   ");
					xyprintf(882,40,"  暂停   ");
					setfont(20,0,"华文行楷");
					xyprintf(882,80,"点击右键继续游戏");
					shadow(0,0,880,1000,2);
					draw_information();
					dt=end-start;
					for ( ; is_run(); delay_fps(60))
					{
					//先用 mousemsg() 函数判断消息队列里有没有鼠标消息。如果没有，直接跳过。 
						while (mousemsg())
						{
							msg = getmouse();
							if( msg.is_right() )
							{
								time(&end);
								start=end-dt;
								return ;
							}
						}
					}
				}
			}
		}
	}
}


void draw_draw_button()//绘制和棋按钮 
{
	setfont(30,0,"华文行楷");
	setcolor(BLACK);
	roundedRectangle(882,65,998,94);
	setcolor(WHITE);
	xyprintf(882,66,"和棋         ");
	if(msg.x>880&&msg.x<1000&&msg.y>62&&msg.y<92)
	{
		setcolor(RED);
		xyprintf(882,66,"和棋         ");
		setcolor(GREEN);
		roundedRectangle(882,65,998,94);
		if( msg.is_left() )
		{
			if( msg.is_down() )
				clickButton = true;
			else 
			{	//左键抬起，执行事件
				if (clickButton)
				{
					clickButton = false;
					dt=end-start; 
					shadow(0,0,880,1000,2);
					draw_information();
					setfillcolor(grayColor);
					setfont(30,0,"隶书");
					for ( ; is_run(); delay_fps(60) )
					{
						bar(882,0,1000,100);
						setcolor(BLACK);
						rectangle(882,0,1000,100);
						xyprintf(882,0,"确认和棋");
						xyprintf(882,33,"  确认        ");
						xyprintf(882,66,"  取消         ");
						while (mousemsg())
						{
							msg = getmouse();
						}
						if(msg.x>882&&msg.x<1000&&msg.y>33&&msg.y<63)
						{
							setcolor(RED);
							xyprintf(882,33,"  确认        ");
							if(msg.is_left())
							{
								if( msg.is_down() )
								clickButton = true;
								else 
								{	//左键抬起，执行事件
									if (clickButton)
									{
										clickButton = false;
										flag=0;
										BLACKscore=0;
										REDscore=0;
										interfaces=1;
										saveGame();
										return ;
									}
								}
							}
						}
						if(msg.x>882&&msg.x<1000&&msg.y>66&&msg.y<96)
						{
							setcolor(RED);
							xyprintf(882,66,"  取消        ");
							if(msg.is_left())
							{
								if( msg.is_down() )
									clickButton = true;
								else 
								{	//左键抬起，执行事件
									if (clickButton)
									{
										clickButton = false;
										time(&end);
										start=end-dt;
										return ;			
									}
								}	
							}
						}
					}
				}
			}
		}
	}
}


void draw_backMove_button()//绘制悔棋按钮 
{
	if(RedTakeBace==1)
	{
		if(rounds%2==0&&roundC==rounds)
		{
			setfont(30,0,"华文行楷");
			setcolor(BLACK);
			roundedRectangle(890,640,990,670);
			setcolor(WHITE);
			xyprintf(882,640,"    悔棋       ");
			if(msg.x>880&&msg.x<1000&&msg.y>640&&msg.y<670)
			{
				setcolor(RED);
				xyprintf(882,640,"    悔棋       ");
				setcolor(GREEN);
				roundedRectangle(890,640,990,670);
				if( msg.is_left() )
				{
					if( msg.is_down() )
						clickButton = true;
					else 
					{	//左键抬起，执行事件
						if (clickButton)
						{
							clickButton = false;
							readArchive(); 
							RedTakeBace=0;
							flag=1;sx=-1;fx=-1; 
							saveGame();
						}
					}
				}
			}
		}
	}
	if(BlackTakeBace==1)
	{
		if(rounds%2==1&&rounds!=1&&roundC==rounds)
		{
			setfont(30,0,"华文行楷");
			setcolor(BLACK);
			roundedRectangle(890,250,990,280);
			setcolor(WHITE);
			xyprintf(882,250,"    悔棋       ");
			if(msg.x>880&&msg.x<1000&&msg.y>250&&msg.y<280)
			{
				setcolor(RED);
				xyprintf(882,250,"    悔棋       ");
				setcolor(GREEN);
				roundedRectangle(890,250,990,280);
				if( msg.is_left() )
				{
					if( msg.is_down() )
						clickButton = true;
					else 
					{	//左键抬起，执行事件
						if (clickButton)
						{
							clickButton = false;
							readArchive(); 
							BlackTakeBace=0;
							flag=1;sx=-1;fx=-1; 
							saveGame();
						}
					}
				}
			}
		}
	}
}


void visual_feedback()//视觉反馈（框选第一次点击的棋子） 
{
	int i=0;
	if(checkerboard[sy][sx]/10==rounds%2&&sx!=-1&&fx==-1)
	{
		if(flag2==1)
		{
			draw_sidebar();
			for (i=75; is_run(); delay_fps(60),i+=3)
			{
				draw_3D(66+94*sx-94,72+93*sy-94,45+i-75,5+(i-75)/10);
				draw_chess(checkerboard[sy][sx],66+94*sx-94 ,72+93*sy-94,sy,sx,i);
				if(i>100)
					break;
			}
			flag2=0;
		}
		else
		{
			draw_3D(66+94*sx-94,72+93*sy-94,70,7);
			draw_chess(checkerboard[sy][sx],66+94*sx-94 ,72+93*sy-94,sy,sx,100);
		}
	}
}


void point_of_fall()//落点提示(显示可落棋子的位置)
{
	if(flag==2)
	{
		int i,j; 
		for(i=2;i<12;i++)
		{
			for(j=2;j<11;j++)
			{
				if(checkerboard2[i][j]==1)
				{
					setfillcolor(GREEN);
					fillellipse( 66+94*(j-2),72+93*(i-2),10 ,10);
				}
			}
		}
	}
}


void draw_continueGame_button(int *p)//绘制询问是否继续游戏按钮 
{
	draw_map();//绘制游戏地图 
	draw_information();//绘制对局状态信息 
	shadow(0,0,880,1000,2);
	setfillcolor(grayColor);
	setfont(30,0,"隶书");
	for ( ; is_run(); delay_fps(60) )
	{
		time(&end);
		start=end-dt;
		bar(882,0,1000,100);
		setcolor(BLACK);
		rectangle(883,1,999,99);
		xyprintf(882,0,"是否继续");
		xyprintf(882,33,"  继续        ");
		xyprintf(882,66,"  重开         ");
		while (mousemsg())
		{
			msg = getmouse();
		}
		if(msg.x>882&&msg.x<1000&&msg.y>33&&msg.y<63)
		{
			setcolor(GREEN);
			setcolor(RED);
			xyprintf(882,33,"  继续        ");
			if(msg.is_left())
			{
				if( msg.is_down() )
				clickButton = true;
				else 
				{	//左键抬起，执行事件
					if (clickButton)
					{
						clickButton = false;
						*p=0;
						return ;
					}
				}
			}
		}
		if(msg.x>882&&msg.x<1000&&msg.y>66&&msg.y<96)
		{
			setcolor(GREEN);
			setcolor(RED);
			xyprintf(882,66,"  重开        ");
			if(msg.is_left())
			{
				if( msg.is_down() )
					clickButton = true;
				else 
				{	//左键抬起，执行事件
					if (clickButton)
					{
						clickButton = false;
						*p=0;
						flag=0; 
						saveGame();
						return ;			
					}
				}	
			}
		}
	}
}













