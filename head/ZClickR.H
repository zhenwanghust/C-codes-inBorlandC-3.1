#ifndef _ZClickR_H_
#define _ZClickR_H_
#include"common.h"

void smallrightpressfiledrawup(int x, int y);
void smallrightpressfiledrawdown(int x, int y);
//returnblank* rightonblank(int filepage,int mousewhere,int rightarea,int showmode);//����հ�

//returnfile* rightonfile(int filepage,int mousewhere,int rightarea,int showmode);//����ļ�

//void drawpaixucaidan(int area,int x, int y);

int getrightarea(int area,int tempx,int tempy);
//void smallrightpressblankdrawup(int x, int y,int showmode);
//void smallrightpressblankdrawdown(int x, int y,int showmode);
void bigrightpressblankfirst(int x, int y,int showmode);//��ģʽ��һ���ޣ���հף����»�
void bigrightpressblanksecond(int x, int y,int showmode);//��ģʽ�������ޣ���հף����»�
void bigrightpressblankthird(int x, int y,int showmode);//��ģʽ�������ޣ���հף����ϻ�
void bigrightpressblankfourth(int x, int y,int showmode);//��ģʽ�������ޣ���հף����ϻ�
void bigrightpressfilefirst(int x, int y);//��ģʽ��һ���ޣ����ļ������»�
void bigrightpressfilesecond(int x, int y);//��ģʽ�������ޣ����ļ������»�
void bigrightpressfilethird(int x, int y);//��ģʽ�������ޣ����ļ������ϻ�
void bigrightpressfilefourth(int x, int y);//��ģʽ�������ޣ����ļ������ϻ�

#endif  