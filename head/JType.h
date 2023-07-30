#ifndef _JTYPE_H_
#define _JTYPE_H_
typedef struct file//文件信息结点
{
	char name[13];
	long size;
	unsigned time;
	unsigned date;
	char attrib;
}file;
typedef struct Node//文件总结点
{
	struct Node* child;
	struct Node* brother;
	struct Node* parent;//指向父文件夹的指针，便于返回操作
	file file;
	int flag;
}Node;
#endif
