#ifndef _JTYPE_H_
#define _JTYPE_H_
typedef struct file//�ļ���Ϣ���
{
	char name[13];
	long size;
	unsigned time;
	unsigned date;
	char attrib;
}file;
typedef struct Node//�ļ��ܽ��
{
	struct Node* child;
	struct Node* brother;
	struct Node* parent;//ָ���ļ��е�ָ�룬���ڷ��ز���
	file file;
	int flag;
}Node;
#endif
