#ifndef _JNEWFILE_H_
#define _JNEWFILE_H_
#include"common.h"
int JCreatFile(Node* parent, char* suffix, char* name);
void JSamename(char* name, char* suffix, Node* parent);
int JGetPureNew(char* temp);
int JNewSameName(char* copypure, char* copySuffix, Node* parent);
void JChangeNewname(int num, char* copySuffix, char* name);
int JCheckNewsuffix(char* suffix);
int JCheckSpace(char* name);
#endif
