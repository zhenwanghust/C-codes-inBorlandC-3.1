#ifndef _ZClickR_H_
#define _ZClickR_H_
#include"common.h"

void smallrightpressfiledrawup(int x, int y);
void smallrightpressfiledrawdown(int x, int y);
//returnblank* rightonblank(int filepage,int mousewhere,int rightarea,int showmode);//点击空白

//returnfile* rightonfile(int filepage,int mousewhere,int rightarea,int showmode);//点击文件

//void drawpaixucaidan(int area,int x, int y);

int getrightarea(int area,int tempx,int tempy);
//void smallrightpressblankdrawup(int x, int y,int showmode);
//void smallrightpressblankdrawdown(int x, int y,int showmode);
void bigrightpressblankfirst(int x, int y,int showmode);//大模式，一象限，点空白，左下画
void bigrightpressblanksecond(int x, int y,int showmode);//大模式，二象限，点空白，右下画
void bigrightpressblankthird(int x, int y,int showmode);//大模式，三象限，点空白，右上画
void bigrightpressblankfourth(int x, int y,int showmode);//大模式，四象限，点空白，左上画
void bigrightpressfilefirst(int x, int y);//大模式，一象限，点文件，左下画
void bigrightpressfilesecond(int x, int y);//大模式，二象限，点文件，右下画
void bigrightpressfilethird(int x, int y);//大模式，三象限，点文件，右上画
void bigrightpressfilefourth(int x, int y);//大模式，四象限，点文件，左上画

#endif  
