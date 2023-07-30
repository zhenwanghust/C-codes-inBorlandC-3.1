#include "common.h"
#include "ZTool.h"

void drawhomebutton (int x,int y)
{
	//setcolor(DARKGRAY);
	line(x,y,x-9,y+9);
	line(x,y,x+9,y+9);
	rectangle(x-6,y+9,x+6,y+20);
	line(x-10,y+9,x+10,y+9);
}

void downarrow(int x, int y,  int arrowtype)//四种箭头函数中，x，y为箭头中心点坐标，arrowtype参数决定箭头种类，0为> ,1为->
{
	line(x,y,x-3,y-3);
	line(x,y,x+3,y-3);
	if(arrowtype==1)
	{
		line(x,y,x,y-9);
	}
}

void leftarrow(int x, int y,  int arrowtype)
{
	line(x,y,x+3,y+3);
	line(x,y,x+3,y-3);
	if(arrowtype==1)
	{
		line(x,y,x+9,y);
	}
}
void uparrow(int x, int y,  int arrowtype)
{
	line(x,y,x+3,y+3);
	line(x,y,x-3,y+3);
	if(arrowtype==1)
	{
		line(x,y,x,y+9);
	}
}

void rightarrow(int x, int y,  int arrowtype)
{
	line(x,y,x-3,y+3);
	line(x,y,x-3,y-3);
	if(arrowtype==1)
	{
		line(x,y,x-9,y);
	}
}


void rightordownarrow(int x, int y,  int arrowtype,int downorright)//downorright参数决定画什么方向的箭头
{
	if(downorright==1)//画下箭头
		line(x,y,x-3,y-3);
		line(x,y,x+3,y-3);
		if(arrowtype==1)
		{
			line(x,y,x,y-9);
		}
	if(downorright==2)//画右箭头
		line(x,y,x-3,y+3);
		line(x,y,x-3,y-3);
		if(arrowtype==1)
		{
			line(x,y,x-9,y);
		}
}


