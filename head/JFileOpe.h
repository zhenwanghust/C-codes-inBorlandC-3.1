#ifndef _JFILEOPE_H_
#define _JFILEOPE_H_
#include"common.h"

Node* OpenFile(int Filepage, Node* parentNode, int filenumber,int showmode);
int getfilenumer(Node* temp);
char* GetDir(Node* tempNode);
Node* BackFile(int Filepage, Node* parentNode, int filenumber, int showmode);
void JFreeFile(Node* parent);
void JFreeFileChild(Node* parent);
void JCFree(Node* RootC);//c≈Ã
void JCFreeCir(Node* RootC);
#endif

