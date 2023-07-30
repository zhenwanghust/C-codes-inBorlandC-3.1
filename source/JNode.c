#include<JNode.h>
#include "common.h"
//儿子节点并文件赋值
void CreateFileNodeChild(Node* tree, struct find_t file)
{
	Node* NewNode;
	if ((NewNode = (Node*)malloc(sizeof(Node))) == NULL)
	{
		printf("no enough memory");
		return NULL;
	}
	NewNode->file.size = file.size;
	NewNode->file.time = file.wr_time;
	NewNode->file.date = file.wr_date;
	NewNode->file.attrib = file.attrib;
	strcpy(NewNode->file.name, file.name);
	NewNode->flag = 1;
	NewNode->responseFlag = 0;
	NewNode->copyflag = 0;
	NewNode->treeResponseFlag = 0;
	NewNode->treeflag = 0;
	NewNode->delecopyflag = 0;
	NewNode->freeflag = 0;
	NewNode->child = NULL;
	NewNode->brother = NULL;
	NewNode->parent = tree;
	tree->child = NewNode;
}
//兄弟节点并文件赋值
void CreateFileNodeBro(Node* tree, struct find_t file)
{
	Node* NewNode;
	if ((NewNode = (Node*)malloc(sizeof(Node))) == NULL)
	{
		printf("no enough memory");
		return;
	}
	NewNode->file.size = file.size;
	NewNode->file.time = file.wr_time;
	NewNode->file.date = file.wr_date;
	NewNode->file.attrib = file.attrib;
	NewNode->flag = 0;
	NewNode->responseFlag = 0;
	NewNode->copyflag = 0;
	NewNode->treeResponseFlag = 0;
	NewNode->treeflag = 0;
	NewNode->delecopyflag = 0;
	NewNode->freeflag = 0;
	strcpy(NewNode->file.name, file.name);
	NewNode->child = NULL;
	NewNode->brother = NULL;
	NewNode->delecopyflag = 0;
	NewNode->parent = tree;
	tree->brother = NewNode;
}
Node* CreateNode()
{
	Node* newNode;
	if ((newNode = (Node*)malloc(sizeof(Node))) == NULL)//给指针分配内存使之成为结构变量
	{
		printf("no enough memory");
		return NULL;
	}
	newNode->treeflag = 0;
	newNode->copyflag = 0;
	newNode->responseFlag = 0;
	newNode->freeflag = 0;
	newNode->delecopyflag = 0;
	newNode->treeResponseFlag = 0;
	newNode->delecopyflag = 0;
	newNode->child = NULL;
	newNode->brother = NULL;
	newNode->parent = NULL;
	return newNode;
}

