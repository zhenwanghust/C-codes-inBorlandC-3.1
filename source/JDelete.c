#include"main.h"
#include "common.h"

void JDeletemain(Node* parent,Copy**head)//主删除
{
	char* dir;
	Node* temp = parent->child;
	if (parent->copyflag)
	{
		puthz(200, 8, "待粘贴文件被删除！", 16, 16, RED);//输入汉字
		setcolor(DARKGRAY);
		delay(2000);
		setfillstyle(1, WHITE);
		bar(190, 1, 190 + 16 * 10, 29);//190+（汉字个数+1）*16
		FreeCopy(head);
	}
	if (temp->flag==2|| temp->flag == 3  )
	{
		return;
	}
	
	while (temp!=NULL)
	{
		if (temp->responseFlag==1)
		{
			JDelete(temp);
			temp=JDeleteLink(temp);
			continue;
		}
		temp = temp->brother;
	}
	/*
	dir = GetDir(parent);
	Fileini(dir, parent);
	free(dir);
	*/
}
/*void* JDelete(Node* parent)
{
	Node* temp = parent;
	Node* pre;
	char* c;
	char* dir,*test;
	int i=0;
	Stack* S = CreatStack();
	c = GetDir(parent);
	if (parent->copyflag)
	{
		outtextxy(1, 430, "error");
	}
	if ((temp->file.attrib & _A_SUBDIR) == 0)
	{
		if (remove(c) == -1);
		free(c);
		free(S);
		return;
		//printf("error!\n");
	}
	if ((temp->file.attrib & _A_SUBDIR) != 0)
	{
		if (temp->child == NULL)
		{
			Fileini(c, temp);
		}
		temp = temp->child;
		while (temp || S->next != NULL)
		{
			while (temp)
			{
				if ((temp->file.attrib & 0x10) != 0)
				{
					if (temp->child == NULL)
					{
						dir = GetDir(temp);
						Fileini(dir, temp);
						free(dir);
					}
				}
				PushStack(temp, S);
				temp = temp->child;
			}
			if (S->next != NULL)
			{
				temp = PopStack(S);
				if ((temp->file.attrib & _A_SUBDIR) == 0)
				{
					dir = GetDir(temp);
					if (remove(dir) == -1);//printf("error!\n");
					free(dir);
				}
				if ((temp->file.attrib & _A_SUBDIR) != 0)
				{
					JFreeFile(temp);
					dir = GetDir(temp);
					if (rmdir(dir) != 0); //printf("error!\n");
					free(dir);
				}
				temp = temp->brother;
				i++;
				itoa(i, test, 10);
				outtextxy(1, 440, test);
				delay(3);
				setfillstyle(1, WHITE);
				bar(1, 420, 50, 459);
				
			}
		}
	}
	FreeStack(S);
	if (rmdir(c) != 0); //printf("error!\n");
	free(c);
}
*/
void* JDelete(Node* parent)//删除一个文件
{
	Node* temp = parent;
	Node* pre;
	char* c;
	c = GetDir(parent);
	//if(temp->child)
	//JDFlag(temp->child);
	if ((temp->file.attrib & _A_SUBDIR )== 0)
	{
		if (remove(c) == -1);
			//printf("error!\n");
	}
	if ((temp->file.attrib & _A_SUBDIR)!=0)
	{
		if (temp->child == NULL)
		{
			Fileini(c, temp);
		}
			JDeleteChildFile(temp->child);
			JDeleteChildFolder(temp->child);
			if (rmdir(c) != 0); //printf("error!\n");
			JFreeFile(temp);
	}
	free(c);
}

void JDeleteChildFile(Node* child)//删除这个文件的里面
{
	char* c;
	Node* temp = child;
	if (temp!=NULL)
	{
		if (temp->file.attrib & _A_SUBDIR)
		{
			if (temp->child == NULL)
			{
				c = GetDir(temp);
				Fileini(c, temp);
				free(c);
			}
		}
		if (temp->child != NULL)
		{
			JDeleteChildFile(temp->child);
		}
		JFreeFile(temp);
		if ((temp->file.attrib & _A_SUBDIR) == 0)
		{
			c = GetDir(temp);
			if (remove(c) == -1);//printf("error!\n");
			free(c);
		}
		if (temp->brother != NULL)
		{
			JDeleteChildFile(temp->brother);
		}
		
	
	}
}
void JDeleteChildFolder(Node* child)
{
	char* c;
	Node* temp = child;
	if (temp != NULL)
	{
		if (temp->file.attrib & _A_SUBDIR)
		{
			if (temp->child == NULL)
			{
				c = GetDir(temp);
				Fileini(c, temp);
				free(c);
			}
		}
		if (temp->child != NULL)
		{
			JDeleteChildFolder(temp->child);
		}
		JFreeFile(temp);

		if ((temp->file.attrib & _A_SUBDIR) != 0)
		{
			c = GetDir(temp);
			if (rmdir(c) != 0); //printf("error!\n");
			free(c);
		}
		if (temp->brother != NULL)
		{
			JDeleteChildFolder(temp->brother);
		}
	
	}
}
Node* JDeleteLink(Node* temp)
{
	Node* pre=NULL;
	Node* next=NULL;
	if (temp->flag==0&&temp->brother!=NULL)
	{
		pre = temp->parent;
		next=temp->brother;
		pre->brother = next;
		next->parent = pre;
		free(temp);
		temp = NULL;
		return next;
	}
	if (temp->flag == 1 && temp->brother != NULL)
	{
		pre = temp->parent;
		next = temp->brother;
		pre->child = next;
		next->parent = pre;
		next->flag = 1;
		free(temp);
		temp = NULL;
		return next;
	}
	if (temp->flag == 0 && temp->brother == NULL)
	{
		pre = temp->parent;
		pre->brother = NULL;
		free(temp);
		temp = NULL;
		return next;
	}
	if (temp->flag == 1 && temp->brother == NULL)
	{
		pre = temp->parent;
		pre->child = NULL;
		free(temp);
		temp = NULL;
		return next;
	}
	return next;
}