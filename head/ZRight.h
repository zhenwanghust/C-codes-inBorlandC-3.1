
#ifndef __ZRIGHT_H
#define __ZRIGHT_H
#include"common.h"
int ZFileUnit(Node*tempNodeSe,int x,int y,int filePage,short int displayMode);
char* ZGetSuffix(Node* tempNode);
void ZDrawFileUnit(char* suffix,Node* tempNode,int x,int y,short int displayMode);
void clearrightscreen();
int countfiles(Node* tempNode);
int countpages(Node*tempNode);
void showcurrentpage(int filepage); 
int countselected(Node* tempNode);
int areyousure();

#endif
