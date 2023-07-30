#ifndef _JTREENOD_H_
#define _JTREENOD_H_

#include"common.h"

int JTreeCheckOpen(Node* parent);//返回文件夹内部打开文件夹数量
int JGetTreeFolderNum(Node* Root, int line, Node** getFolder);//line——点击文件夹所在行数 >=1
void JDFlag(Node* child);//递归使当前文件夹内所有文件夹关闭
void clearleftscreen();//用白色覆盖zuo侧显示屏
int JGetFirstTree(Node* RootC, int filepage, Node** temp, int time);
int JDeep(Node* temp, int n);//c盘下第1层
int ZDrawLeft(Node* temp, int bx, int by, int time);
int ZFileUnitLeft(Node* tempNodeSe, int x, int y, int filePage);
void leftshowcurrentpage(int filepage);
void DrawLeftFileUnit(char* suffix, Node* tempNode, int x, int y);
int JChecktreefolder(Node* parent);
int treemouseknowwhere();
void JDtreeResponseFlag(Node* child);//递归使当前文件夹内所有文件夹
void Jfreetree(Node* Root);//递归使当前文件夹内所有文件夹关闭
void JBuildTree(Node* temp);
int JGetTreePage(Node* Root, Node* now, int leftpage);
void JfreetreeCir(Node* RootC);//关闭树
#endif  