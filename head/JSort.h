#ifndef _JSORT_H_
#define _JSORT_H_
#include"common.h"
void JSort(Node* parent,  int flag);
void JChange(Node* t1, Node* t2);
int JSortDate(Node* t1, Node* t2);
int JSortName(Node* tempNode1, Node* tempNode2);
int JSortSize(Node* tempNode1, Node* tempNode2);
int JSortType(Node* tempNode1, Node* tempNode2);
#endif
