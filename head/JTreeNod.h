#ifndef _JTREENOD_H_
#define _JTREENOD_H_

#include"common.h"

int JTreeCheckOpen(Node* parent);//�����ļ����ڲ����ļ�������
int JGetTreeFolderNum(Node* Root, int line, Node** getFolder);//line��������ļ����������� >=1
void JDFlag(Node* child);//�ݹ�ʹ��ǰ�ļ����������ļ��йر�
void clearleftscreen();//�ð�ɫ����zuo����ʾ��
int JGetFirstTree(Node* RootC, int filepage, Node** temp, int time);
int JDeep(Node* temp, int n);//c���µ�1��
int ZDrawLeft(Node* temp, int bx, int by, int time);
int ZFileUnitLeft(Node* tempNodeSe, int x, int y, int filePage);
void leftshowcurrentpage(int filepage);
void DrawLeftFileUnit(char* suffix, Node* tempNode, int x, int y);
int JChecktreefolder(Node* parent);
int treemouseknowwhere();
void JDtreeResponseFlag(Node* child);//�ݹ�ʹ��ǰ�ļ����������ļ���
void Jfreetree(Node* Root);//�ݹ�ʹ��ǰ�ļ����������ļ��йر�
void JBuildTree(Node* temp);
int JGetTreePage(Node* Root, Node* now, int leftpage);
void JfreetreeCir(Node* RootC);//�ر���
#endif  