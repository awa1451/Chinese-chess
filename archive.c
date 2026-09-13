#include"game_runner.h"
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<stdbool.h>
#include<math.h>
extern int checkerboard[12][11],checkerboard2[14][13],rounds,roundC,sx,sy,fx,fy,flag,BLACKscore,REDscore,interfaces,dt,allTime;
extern int BlackTakeBace,RedTakeBace;
extern color_t pinkColor;
extern color_t chessColor;
extern color_t grayColor;
extern time_t start,end;
extern mouse_msg msg;
extern bool clickButton;
int checkArchive()//检查是否存在存档 
{
	FILE* pfRead = fopen("./data//gameData.txt","r");
	if(pfRead==NULL)
	{
		perror("menu:");
		FILE* pfWrite = fopen("./data//gameData.txt","w");//重新创建gameData.txt文件（该文件可能被意外删除） 
		fclose(pfWrite);
		return -1;
	}
	char buffer[40]={0};
	rewind(pfRead);
	fgets(buffer,40,pfRead);
	fclose(pfRead);
	if( buffer[0]!='0')
	{
		return 1; 
	}
	return 0; 
}

void readArchive()//读取存档 
{
	FILE* pfRead = fopen("./data//gameData.txt","r");
	if(pfRead==NULL)
	{
		perror("menu:");
		FILE* pfWrite = fopen("./data//gameData.txt","w");//重新创建gameData.txt文件（该文件可能被意外删除） 
		fclose(pfWrite);
		return ;
	}
	char buffer[40]={0};
	rewind(pfRead);
	fgets(buffer,40,pfRead);
	sscanf(buffer,"%d %d %d %d %d %d %d %d %d %d %d %d",&flag,&rounds,&sx,&sy,&fx,&fy,&dt,&RedTakeBace,&BlackTakeBace,&REDscore,&BLACKscore,&allTime);
	int i=1;
	while(fgets(buffer,40,pfRead)!=0)
	{
		sscanf(buffer,"%d %d %d %d %d %d %d %d %d",&checkerboard[i][1],&checkerboard[i][2],&checkerboard[i][3],&checkerboard[i][4],&checkerboard[i][5],&checkerboard[i][6],&checkerboard[i][7],&checkerboard[i][8],&checkerboard[i][9]);
		i++;
	}
	fclose(pfRead);
}

void saveGame()//保存游戏 
{
	int dt=end-start;
	FILE* pfWrite = fopen("./data//gameData.txt","w");
	if(pfWrite==NULL)
	{
		perror("saveGame:");
		return;
	}
	fprintf(pfWrite,"%d %d %d %d %d %d %d %d %d %d %d %d\n",flag,rounds,sx,sy,fx,fy,dt,RedTakeBace,BlackTakeBace,REDscore,BLACKscore,allTime);
	int i=0,j=0;
	for(i=1;i<11;i++)
	{
		for(j=1;j<10;j++)
		{
			fprintf(pfWrite,"%d ",checkerboard[i][j]);
		}
		fprintf(pfWrite,"\n");
	}
	fclose(pfWrite);
}

