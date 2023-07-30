#ifndef _JBACK_H_
#define _JBACK_H_
#include"common.h"
Back* NewBack(void);
Back* JPushBack(Back* Now, Node* New);//加入后退前进链表
void DeleteBack(Back* now);
void JBack(Node** temp, Back** now, int* pagemax, int showmode);//后退
void JFront(Node** temp, Back** now, int* pagemax, int showmode);
void JFreeBack(Back* now);
#endif
