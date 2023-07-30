#ifndef _JCOPY_H_
#define _JCOPY_H_
#include"common.h"

void JDeleCopy(Node*parent);
void JCopyFlag(Node* parent);
void JCopy(Copy** head, Node* parent, int flag);
void PushCopy(Copy* head, Node* now, int flag);
void FreeCopy(Copy** head);
Copy* CreateCopy();



#endif
