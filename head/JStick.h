#ifndef _JStick_H_
#define _JStick_H_
#include"common.h"
void JStick(Copy* head, Node* parent);//��ճ��ѭ��
void JStickFile(Copy* temp, Node* parent);//�����ļ�ճ��
int JPaste(Copy* temp, Node* parent);//ճ��
int JCheckName(Node* copynode, Node* parent);
int JGetPureName(Node* temp, char* c, int copy);
int JGetSameNumber(char* filename);//��ȡ�ļ���������
void JChangeName(int num, Node* newnode);
void JFolderStickCir(Node* now, Node* before,Node* parent);//ճ����ݹ�
void JFolderStickCir1(Node* now, Node* before, Node* parent);//ճ����ݹ�
void JFolderStick(Node* New, Node* Old);//ճ�����ļ��кͱ����Ƶ��ļ���
int JCheckFolder(Node* parent);
void JWinStick(char* old, char* parent, char* name);
void JWinStickFolder(char* oldDir, char* newDir);
int JCheckchildCir(Node* new, Node* old,int flag);
int JCheckchild(Node* new, Node* old);
void JFolderStack(Node* now, Node* before);
#endif
