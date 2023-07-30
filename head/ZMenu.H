#ifndef _ZMENU_H_
#define _ZMENU_H_
#include "common.h"
#include "Xmouse.h"
int menu(Node* NodeC); 

int smallknowwhere();
int bigknowwhere();
int Rsmallknowwhere();
int Rbigknowwhere();
int djsmallknowwhere();
int djbigknowwhere();
int getarea(int tempx,int tempy); 
int ifanyselected(Node* tempNode);
int ifonlyoneselected(Node* tempNode); 
int quitornot(int tempx,int tempy,int area); 

#endif  
