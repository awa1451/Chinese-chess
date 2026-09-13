#include<stdio.h>
#include<stdlib.h>
#include<time.h>
extern int rounds,BLACKscore,REDscore,allTime,timeInfomation,year,mon,day,hour,minu; 
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


struct ListNode *creatingList()//创建链表 
{
	struct ListNode *head = (struct ListNode*)malloc(sizeof(struct ListNode));
	head->next=NULL;
    return head;
}


void extendingList(struct ListNode **current)//延长链表
{
	struct ListNode *p = (struct ListNode*)malloc(sizeof(struct ListNode));
	p->BLACKscore=BLACKscore;
	p->REDscore=REDscore;
	p->rounds=rounds;
	p->allTime=allTime;
	p->year=year;
	p->mon=mon;
	p->day=day;
	p->hour=hour;
	p->min=minu;
	p->next=NULL;
	(*current)->next=p;
	(*current)=p;
}


void readList(struct ListNode *head)//从文件中读取链表
{
	struct ListNode *current = head; 
	FILE* pfRead = fopen("./data//listData.txt","r");
	if(pfRead==NULL)
	{
		perror("list:");
		FILE* pfWrite = fopen("./data//listData.txt","w");//重新创建gameData.txt文件（该文件可能被意外删除） 
		fclose(pfWrite);
		return ;
	}
	char buffer[40]={0};
	rewind(pfRead);
	while(fgets(buffer,40,pfRead)!=0)
	{
		sscanf(buffer,"%d %d %d %d %d %d %d %d %d",&year,&mon,&day,&hour,&minu,&BLACKscore,&REDscore,&rounds,&allTime);
		extendingList(&current);
	}
	fclose(pfRead);
}

void saveList(struct ListNode *head)//保存链表至文件 
{
	struct ListNode *current = head->next;
	FILE* pfWrite = fopen("./data//listData.txt","w");
	if(pfWrite==NULL)
	{
		perror("listGame:");
		return;
	}
	rewind(pfWrite);
	while(current!=NULL)
	{
		fprintf(pfWrite,"%d %d %d %d %d %d %d %d %d\n",current->year,current->mon,current->day,current->hour,current->min,current->BLACKscore,current->REDscore,current->rounds,current->allTime);
		current=current->next;
	}
	fclose(pfWrite);
}


void clearList(struct ListNode *head)//清空链表
{
	struct ListNode *current = head->next;
	struct ListNode *tem;
	head->next=NULL;
	while(current!=NULL)
	{
		tem=current;
		current=current->next;
		free(tem);
	}
	printf("链表已清空\n"); 
}


void putList(struct ListNode *head)//输出链表
{
	struct ListNode *current=head->next; 
	int h,m,s;
	system("cls");
	printf("------Historical record------\n");
	while(current!=NULL)
	{
		s=(current->allTime)%60;
		m=((current->allTime)/60)%60;
		h=(current->allTime)/3600;
		if((current->rounds)%2==1)
			printf("TIME:%04d.%02d.%02d %02d:%02d  WINNER:RED    BLACKscore==%-4d REDscore==%-5d movements==%-4d consumedTime==%2dh %2dm %2ds\n",current->year,current->mon,current->day,current->hour,current->min,current->BLACKscore,current->REDscore,current->rounds,h,m,s);
		else
			printf("TIME:%04d.%02d.%02d %02d:%02d  WINNER:BLACK  BLACKscore==%-4d REDscore==%-5d movements==%-4d consumedTime==%2dh %2dm %2ds\n",current->year,current->mon,current->day,current->hour,current->min,current->BLACKscore,current->REDscore,current->rounds,h,m,s);
		current=current->next;
	}
	if(head->next==NULL)printf("...Empty\n");
	printf("-----------------------------\n\n");
}






