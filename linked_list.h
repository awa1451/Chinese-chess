#pragma once
struct ListNode *creatingList();//创建链表 
void extendingList(struct ListNode **current);//延长链表
void saveList(struct ListNode *head);//保存链表至文件 
void readList(struct ListNode *head);//从文件中读取链表
void clearList(struct ListNode *head);//清空链表
void putList(struct ListNode *head);//输出链表
