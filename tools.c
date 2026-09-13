#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<stdbool.h>
#include<math.h>
int min(int a,int b)
{
	if(a>b)
		return b;
	else
		return a;
}
void Tip_line(int sx,int sy,int fx,int fy)
{
	line(86+94*sx ,72+93*sy ,66+94*fx ,72+93*fy);
	line(46+94*sx ,72+93*sy ,66+94*fx ,72+93*fy);
	line(66+94*sx ,92+93*sy ,66+94*fx ,72+93*fy);
	line(66+94*sx ,52+93*sy ,66+94*fx ,72+93*fy);
} 
void roundedRectangle(int sx,int sy,int fx,int fy)//绘制圆角矩形 
{
	int r=(fy-sy)/2;
	arc(sx+r,fy-r,180,270,r);
	arc(sx+r,sy+r,90,180,r);
	arc(fx-r,fy-r,270,360,r);
	arc(fx-r,sy+r,0,90,r);
	line(sx+r, sy, fx-r, sy);
	line(fx, sy+r, fx, fy-r);
	line(sx+r ,fy, fx-r, fy);
	line(sx, sy+r, sx, fy-r);
}

void shadow(int sx,int sy,int fx,int fy,int k)//绘制阴影 
{
	int i=0,j=0;
	for(i=sy;i<fy;i+=k)
		for(j=sx;j<fx;j+=k)
			putpixel(j,i,BLACK);
}

void draw_3D(int x,int y,int r,int l)//3D效果 
{
	setcolor(EGEARGB(0, 133, 86, 32));
	setfillcolor(EGEARGB(0, 133, 86, 32));
	int x0=0,y0=0,i=0;
	/*for(i=0;i<360;i++)
	{
		x0=x+(r*sin(i));
		y0=y-(r*cos(i));
		line(x0,y0,x0-(x0-440)*0.01*l,y0-(y0-500)*0.01*l);
	}*/
	for(i=l-1;i>-1;i--)
	{
		setfillcolor(BLACK);
		fillellipse(x-(x-440)*0.01*i,y-(y-500)*0.01*i,r*(1-0.01*i),r*(1-0.01*i));
		setfillcolor(EGEARGB(0, 133, 86, 32));
		fillellipse(x-(x-440)*0.01*i,y-(y-500)*0.01*i,r*(1-0.01*i)-1,r*(1-0.01*i)-1);
	}
}

