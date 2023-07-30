#include"common.h"
#include"JFileOpe.h"
#include"Zright.h"

Node* OpenFile(int Filepage, Node* parentNode, int filenumber, int showmode)//双击打开文件
{
	
	int i;
	char* c;
	Node* back;
	Node* temp = parentNode->child;
	int size = getfilenumer(temp);
	
	temp = parentNode->child;
	
	if (size < filenumber)
	{
		return parentNode;
	}
	else
	{
		for (i = 0; i < filenumber -1; i++)
		{
			temp = temp->brother;
		}
		if (temp->file.attrib == _A_SUBDIR || temp->flag == 2)
		{
			if (*(temp->file.name) != 'C' && *(temp->file.name) != ':' && temp->flag != 3&&temp->child==NULL)
			{
				c = GetDir(temp);
				Fileini(c, temp);
				free(c);
			}
			ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, Filepage, showmode);
			back = temp;
			return back;
		}
		else
		{
			return parentNode;
		}

	}
}
void JCFree(Node* RootC)//c盘
{
	Node* temp = RootC->child;
	if (temp)
	{
		JCFreeCir(temp);
		RootC->child = NULL;
	}
}
void JCFreeCir(Node* RootC)
{
	Node* temp = RootC;
	if (temp != NULL)
	{
		if (temp->child)
		{
			JCFreeCir(temp->child);
		}
		if (temp->brother)
		{
			JCFreeCir(temp->brother);
		}
		free(temp);
	}
	temp = NULL;
}
void JFreeFile(Node* parent)
{
	Node* temp = parent->child;
	if (temp  && parent->flag != 3&&parent->flag != 2)
	{
		JFreeFileChild(temp);
		parent->child = NULL;
	}
}
void JFreeFileChild(Node* parent)
{
	Node* temp = parent;
	if (parent != NULL)
	{
		JFreeFileChild(temp->brother);
		JFreeFileChild(temp->child);
		free(temp);
	}
	temp = NULL;
}
int getfilenumer(Node* temp)
{
	int size = 0;
	while(temp!=NULL)
	{
		size++;
		temp = temp->brother;
	}
	
	return size;
}
char* GetDir(Node* tempNode)
{
	char fileDir[100];
	char tempDir[100];
	char* outputDir = (char*)malloc(100);
	Node* changeNode = tempNode;
	char test[5];
	if (tempNode->flag == 2)
	{
		strcpy(outputDir, "C:");
		return outputDir;
	}
	//if(outputDir == NULL) printf("no enough memory");//留下隐患，要留意！
	*test = '\\';
	*(test + 1) = '\0';
	strcpy(fileDir, test);
	strcat(fileDir, changeNode->file.name);//先得到当前文件名
	while (*fileDir != 'C' && *(fileDir + 1) != ':')//如果不是磁盘文件
	{
		while (changeNode->flag != 1)//指到树枝头节点
		{
			changeNode = changeNode->parent;
		}
		changeNode = changeNode->parent;//指到上一文件夹
		if (changeNode->flag != 2)//如果不是磁盘
		{
			strcpy(tempDir, test);
			strcat(tempDir, changeNode->file.name);//得到目前文件名
		}
		else if (changeNode->flag == 2)//如果是磁盘（不用再加\\）
		{
			strcpy(tempDir, changeNode->file.name);//得到目前文件名
		}
		strcat(tempDir, fileDir);//链接两个文件名得到一段路径
		strcpy(fileDir, tempDir);//将fileDir改为这一段路径
	}
	strcpy(outputDir, fileDir);

	return outputDir;
}
Node* BackFile(int Filepage, Node* parentNode, int filenumber, int showmode)
{
	Node* temp = parentNode;
	if (temp->flag == 3)//是磁盘时
	{
		return temp;
	}
	else if (temp->flag != 2)
	{
		while (temp->flag == 0)
			temp = temp->parent;//指到树根
		temp = temp->parent;//指到上一级文件夹
		ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, Filepage, showmode);
		return temp;
	}
	else if ((temp->flag == 2))
	{
		temp = temp->parent;
		ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, Filepage, showmode);
		return temp;
	}
}

