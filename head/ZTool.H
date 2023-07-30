#ifndef _ZTOOL_H_
#define _ZTOOL_H_
#include"common.h"

void downarrow(int x, int y,  int arrowtype);
void leftarrow(int x, int y,  int arrowtype); 

void uparrow(int x, int y,  int arrowtype);
void rightarrow(int x, int y,  int arrowtype);
void drawhomebutton (int x,int y);

void rightordownarrow(int x, int y,  int arrowtype,int downorright);//downorright参数决定画什么方向的箭头
#endif  
