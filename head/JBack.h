#ifndef _JBACK_H_
#define _JBACK_H_
#include"common.h"
Back* NewBack(void);
Back* JPushBack(Back* Now, Node* New);//�������ǰ������
void DeleteBack(Back* now);
void JBack(Node** temp, Back** now, int* pagemax, int showmode);//����
void JFront(Node** temp, Back** now, int* pagemax, int showmode);
void JFreeBack(Back* now);
#endif
