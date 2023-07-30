#ifndef _JStick_H_
#define _JStick_H_
#include"common.h"
void JStick(Copy* head, Node* parent);//总粘贴循环
void JStickFile(Copy* temp, Node* parent);//单个文件粘贴
int JPaste(Copy* temp, Node* parent);//粘贴
int JCheckName(Node* copynode, Node* parent);
int JGetPureName(Node* temp, char* c, int copy);
int JGetSameNumber(char* filename);//获取文件数字名字
void JChangeName(int num, Node* newnode);
void JFolderStickCir(Node* now, Node* before,Node* parent);//粘贴大递归
void JFolderStickCir1(Node* now, Node* before, Node* parent);//粘贴大递归
void JFolderStick(Node* New, Node* Old);//粘贴新文件夹和被复制的文件夹
int JCheckFolder(Node* parent);
void JWinStick(char* old, char* parent, char* name);
void JWinStickFolder(char* oldDir, char* newDir);
int JCheckchildCir(Node* new, Node* old,int flag);
int JCheckchild(Node* new, Node* old);
void JFolderStack(Node* now, Node* before);
#endif
