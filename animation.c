#include"game_runner.h"
#include"draw.h"
#include"tools.h"
#include"linked_list.h"
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
extern int checkerboard[12][11],rounds,sx,sy,fx,fy,flag,BLACKscore,REDscore;
extern color_t pinkColor;
extern color_t chessColor;
extern struct ListNode *head,*current;
void Animation(int k)//动画 
{
	int i=0,j=0,dx=94*(fx-sx),dy=93*(fy-sy);
	int d=dx*dx+dy*dy;
	int x=30+94*sx-94,y=39+93*sy-94;
	int tC=checkerboard[sy][sx],tC2=checkerboard[fy][fx];
	for (i=0,j=0; is_run(); delay_fps(60),i++)
	{
		switch(k)//选择动画 
		{
			case 0://黑方胜利动画 
				draw_allchess(checkerboard,0);
				if(flag==200)
				{
					BLACKscore+=200;
					extendingList(&current);//延长链表
					saveList(head);//保存链表
					putList(head);
					flag=-200;
				}
				draw_information();
				if(flag==-200)
				{
					if(i<120)
					{
						setcolor(GREEN);
						setfont(2*i,0,"华文行楷");
						//xyprintf(220-i/2,400-i/2,"绝杀");
						xyprintf(i*4+2,670-i,"绝杀");
					}
					else
					{
						setcolor(GREEN);
						setfont(2*(240-i),0,"华文行楷");
						//xyprintf(110+i/2,290+i/2,"绝杀");
						xyprintf(i*4+2,670-i,"绝杀");
					}
				}
				if(i<120)
				{
					setcolor(BLACK);
					setfont(i,0,"华文行楷");
					xyprintf(i*4,4*i,"恭喜黑方胜出");
				}
				else
				{
					setcolor(BLACK);
					i+=3; 
					if(i>220)i=221;
					setfont(240-i,0,"华文行楷");
					xyprintf(i*4,4*(240-i),"恭喜黑方胜出");
				}
				setfont(20,0,"华文行楷");
				xyprintf(880,0,"右键返回菜单");
				setfont(30,0,"华文行楷");
				xyprintf(880,20,"    黑方");
				xyprintf(880,50,"    胜出");if(i>220)return ;
				break; 
			case 1://红方胜出动画 
				draw_allchess(checkerboard,0);
				if(flag==200)
				{
					REDscore+=200;
					extendingList(&current);//延长链表
					saveList(head);//保存链表
					putList(head);
					flag=-200;
				}
				draw_information();
				if(flag==-200)
				{
					if(i<120)
					{
						setcolor(GREEN);
						setfont(2*i,0,"华文行楷");
						xyprintf(i*4+2,620+i,"绝杀");
					}
					else
					{
						setcolor(GREEN);
						setfont(2*(240-i),0,"华文行楷");
						xyprintf(i*4+2,620+i,"绝杀");
					}
				}
				if(i<120)
				{
					setcolor(RED);
					setfont(i,0,"华文行楷");
					xyprintf(i*4,4*i,"恭喜红方胜出");
				}
				else
				{
					setcolor(RED);
					i+=3; 
					if(i>220)i=221;
					setfont(240-i,0,"华文行楷");
					xyprintf(i*4,4*(240-i),"恭喜红方胜出");
				}
				setfont(20,0,"华文行楷");
				xyprintf(880,0,"右键返回菜单");
				setfont(30,0,"华文行楷");
				xyprintf(880,20,"    红方");
				xyprintf(880,50,"    胜出");if(i>220)return ;
				break; 
			case 2://将军提示动画
				draw_map();
				i++;
				setcolor(GREEN);
				if(i<110)
				{
					setfont(2*i,0,"华文行楷");
					xyprintf(320-i/2,400-i/2,"将军");
				}
				else
				{
					setfont(2*(220-i),0,"华文行楷");
					xyprintf(210+i/2,290+i/2,"将军");
				}
				if(i<80||i>155)i+=3;if(i>220)return ;
				break; 
			case 3://明将提示动画
				draw_map();
				i++;
				setcolor(YELLOW);
				if(i<110)
				{
					setfont(2*i,0,"华文行楷");
					xyprintf(320-i/2,400-i/2,"明将");
				}
				else
				{
					setfont(2*(220-i),0,"华文行楷");
					xyprintf(210+i/2,290+i/2,"明将");
				}
				if(i<80||i>155)i+=3;if(i>220)return ;
				break; 
			case 4://吃提示动画
				checkerboard[sy][sx]=-10;
				checkerboard[fy][fx]=tC;
				draw_map();
				i+=5;
				setcolor(YELLOW);
				if(i<110)
				{
					setfont(2*i,0,"华文行楷");
					xyprintf(72+93*fx-94-i/2,72+93*fy-94-i/2,"吃");
				}
				else
				{
					setfont(2*(220-i),0,"华文行楷");
					xyprintf(72+93*fx-94-110+i/2,72+93*fy-94-110+i/2,"吃");
				}
				checkerboard[sy][sx]=tC;
				checkerboard[fy][fx]=tC2;
				if(i<80||i>155)i+=3;if(i>220)return ;
				break; 
			case 5:
				return ;
				break; 
			case 6://非法移动提示动画
				draw_map();
				i+=1;
				if(i<110)
				{
					if(rounds%2==1)
					{
						setcolor(RED);setfont(i*1.3,0,"华文行楷");
						xyprintf(220-i/2,400-i/2,"红棋回合");
					}
					else
					{
						setcolor(BLACK);setfont(i*1.3,0,"华文行楷");
						xyprintf(220-i/2,400-i/2,"黑棋回合");
					}
				}
				else
				{	
					if(rounds%2==1)
					{
						setcolor(RED);setfont((220-i)*1.3,0,"华文行楷");
						xyprintf(110+i/2,290+i/2,"红棋回合");
					}
					else
					{
						setcolor(BLACK);setfont((220-i)*1.3,0,"华文行楷");
						xyprintf(110+i/2,290+i/2,"黑棋回合");
					}
				}
				if(i<80||i>155)i+=3;if(i>220)return ;
				break; 
			case 7://棋子移动动画
				draw_allchess(checkerboard,1);
				draw_sidebar();
				i--;
				if(d<70000) 
				{
					j+=dx/40;
					i+=dy/40;
				}
				if((i*i+j*j)>d*(2/3))
				{
					j+=dx/40;
					i+=dy/40;
				}
				if((i*i+j*j)>d/3)
				{
					j+=dx/100;
					i+=dy/100;
				}
				j+=dx/50;
				i+=dy/50;
				if((i*i+j*j)>d)
					return ;
				draw_3D(66+94*sx-94+j,72+93*sy-94+i,70-((i*i+j*j)*10/d),7.0-((i*i+j*j)*3/d)); //3D效果 
				draw_chess(checkerboard[sy][sx],66+94*sx-94+j ,72+93*sy-94+i,sy,sx,100.0-((i*i+j*j)*10/d));
				break; 
			default :break; 
		}
	}
}


void openingAnimation()//进入棋盘开场动画 
{
	int i,j;
	for(i=1000; is_run(); delay_fps(60),i--)
	{
		cleardevice();
		for(j=0;j<i;j++)
		{
			line(0,j,1000,j);
		}
		if(i==0)return ;
	}
	return; 
}









