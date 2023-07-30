#include"common.h"
#include"JFileOpe.h"
#include"Zright.h"

Node* OpenFile(int Filepage, Node* parentNode, int filenumber, int showmode)//˫�����ļ�
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
void JCFree(Node* RootC)//c��
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
	//if(outputDir == NULL) printf("no enough memory");//����������Ҫ���⣡
	*test = '\\';
	*(test + 1) = '\0';
	strcpy(fileDir, test);
	strcat(fileDir, changeNode->file.name);//�ȵõ���ǰ�ļ���
	while (*fileDir != 'C' && *(fileDir + 1) != ':')//������Ǵ����ļ�
	{
		while (changeNode->flag != 1)//ָ����֦ͷ�ڵ�
		{
			changeNode = changeNode->parent;
		}
		changeNode = changeNode->parent;//ָ����һ�ļ���
		if (changeNode->flag != 2)//������Ǵ���
		{
			strcpy(tempDir, test);
			strcat(tempDir, changeNode->file.name);//�õ�Ŀǰ�ļ���
		}
		else if (changeNode->flag == 2)//����Ǵ��̣������ټ�\\��
		{
			strcpy(tempDir, changeNode->file.name);//�õ�Ŀǰ�ļ���
		}
		strcat(tempDir, fileDir);//���������ļ����õ�һ��·��
		strcpy(fileDir, tempDir);//��fileDir��Ϊ��һ��·��
	}
	strcpy(outputDir, fileDir);

	return outputDir;
}
Node* BackFile(int Filepage, Node* parentNode, int filenumber, int showmode)
{
	Node* temp = parentNode;
	if (temp->flag == 3)//�Ǵ���ʱ
	{
		return temp;
	}
	else if (temp->flag != 2)
	{
		while (temp->flag == 0)
			temp = temp->parent;//ָ������
		temp = temp->parent;//ָ����һ���ļ���
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

