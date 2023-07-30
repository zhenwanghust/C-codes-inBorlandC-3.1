#include"common.h"
#include"JBack.h"
#include"JFileOpe.h"

Back* NewBack(void)//新建后退前进链表
{
	Back* head;
	if ((head = (Back*)malloc(sizeof(Back))) == NULL)
	{
		puthz(155, 200, "错误", 16, 16, LIGHTGRAY);//printf("error");?
		exit(0);
		return NULL;
	}
	head->tempNode = NULL;
	head->pre = NULL;
	head->next = NULL;
	return head;
}
Back* JPushBack(Back* Now, Node* New)//加入后退前进链表
{
	Back* temp = NewBack();
	Node* Root = New;
	while (Root->parent)
	{
		Root = Root->parent;
	}
	DeleteBack(Now);
	if (temp==NULL)
	{
		puthz(155, 200, "错误", 16, 16, LIGHTGRAY);
		exit(0);
		return;
	}
	Now->next = temp;
	temp->next=NULL;
	temp->pre = Now;
	temp->tempNode = New;
	return temp;
}
void DeleteBack(Back* now)
{
	Back* temp = now;
	int i,j,size=0;
	while (temp->next!=NULL)
	{
		size++; 
		temp = temp->next;
	}
	temp = now;
	for (j = 0; j < size; j++)
	{
		temp = now;
		for (i = size-j; i > 0; i--)
		{
			temp = temp->next;
		}
		free(temp);
	}
	now->next = NULL;
}
void JFreeBack(Back* now)
{
	Back* temp;
	int i, j, size = 0;
	while (now->pre!=NULL)
	{
		now = now->pre;
	}
	temp = now;
	while (temp->next != NULL)
	{
		size++;
		temp = temp->next;
	}
	temp = now;
	for (j = 0; j < size; j++)
	{
		temp = now;
		for (i = size - j; i > 0; i--)
		{
			temp = temp->next;
		}
			free(temp);
	}
	now->next = NULL;
}
void JBack(Node** temp, Back** now,int* pagemax,int showmode)//后退
{
	if ((*now)->pre->tempNode==NULL)
	{
		return;
	}
	*now = (*now)->pre;
	*temp = (*now)->tempNode;
	*pagemax=ZFileUnit(*temp, RIGHTSTARTX, RIGHTSTARTY, 1, showmode);
}

void JFront(Node** temp, Back** now, int* pagemax, int showmode)//前进
{

	if ((*now)->next==NULL)
	{
		return;
	}
	*now = (*now)->next;
	*temp = (*now)->tempNode;
	*pagemax = ZFileUnit(*temp, RIGHTSTARTX, RIGHTSTARTY, 1, showmode);
}
