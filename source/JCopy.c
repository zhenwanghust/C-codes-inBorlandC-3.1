#include"common.h"
#include"JCopy.h"
void JCopy(Copy**head,Node* parent,int flag)
{
	Node* temp = parent;
	temp = parent->child;
	FreeCopy(head);
	while (temp!=NULL)
	{
		if (temp->responseFlag == 1)
		{
			PushCopy(*head,temp,flag);
			JCopyFlag(parent);
		}
		temp = temp->brother;
	}
}
void JDeleCopy(Node* parent)
{
	parent->copyflag = 0;
	while (parent->flag != 3)
	{
		while (parent->flag == 0)
		{
			parent = parent->parent;
		}
		parent = parent->parent;
		parent->copyflag = 0;
	}
}
void JCopyFlag(Node*parent)
{
	parent->copyflag = 1;
	while (parent->flag != 3)
	{
		while (parent->flag == 0)
		{
			parent = parent->parent;
		}
		parent = parent->parent;
		parent->copyflag = 1;
	}
}
void PushCopy(Copy* head, Node* now, int flag)
{
	char* c;
	Copy* new = CreateCopy();
	Copy* temp = head;
	while (temp->next)
	{
		temp = temp->next;
	}
	new->node = now;
	new->flag = flag;
	temp->next = new;
}
void FreeCopy(Copy** head)
{
	Copy* temp = *head;
	Node* parent;
	int i, j, size = 0;
	if ((*head)->next)
	{
		parent = ((*head)->next) -> node;
		JDeleCopy(parent);
	}
	if (temp->next = NULL)
	{
		size++;
		temp = temp->next;
	}
	temp = *head;
	for (i = 0; i < size; i++)
	{
		temp = *head;
		for (j=0;j<size-i;j++)
		{
			temp = temp->next;
		}
		temp->node->copyflag = 0;
		free(temp);
	}
	(*head)->next = NULL;
}
Copy* CreateCopy()
{
	Copy* temp;
	if ((temp=(Copy*)malloc(sizeof(Copy)))==NULL)
	{
		//outtextxy();
	}
	temp->flag = 0;
	temp->next = NULL;
	temp->pre = NULL;
}