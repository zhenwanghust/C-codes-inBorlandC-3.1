#ifndef _JDELETE_H_
#define _JDELETE_H_
#include"common.h"
void JDeletemain(Node* parent,Copy**head);
void* JDelete(Node* parent);
void JDeleteChildFile(Node* child);
void JDeleteChildFolder(Node* child);
Node* JDeleteLink(Node* temp);

#endif
