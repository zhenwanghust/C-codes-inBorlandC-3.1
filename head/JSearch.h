#ifndef _JSEARCH_H_
#define _JSEARCH_H_

void JSearchCir(char* name, Node* Root, FILE* fb);
int JSearch(char* name, Node* Root, Node* RootC, Search* parent);
Search* JCreateSearch();
void JFreeSearch(Search* parent);
Node* JSearchDir(char* dir, Node* RootC);
Node* JGetNode(char* name, Node* child);
void JGetName(char* dir, char* Name);
int JSearchDraw(Node* RootC, Search* parent);
void JOpenSearch(Search* parent,Node**now, int filenumber, int Filepage);
int JSearchStack(Node* Root, char* name, FILE* fb);
Stack* CreatStack();
void PushStack(Node* item, Stack* S);
Node* PopStack(Stack* S);
void FreeStack(Stack* S);
void showlujing(char* tempDir,int x,int y);
void SearchDrawFileUnit(char* suffix,Node* tempNode,int x,int y,short int displayMode); 
#endif 
