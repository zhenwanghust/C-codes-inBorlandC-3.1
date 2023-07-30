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

void downarrow(int x, int y,  int arrowtype)//���ּ�ͷ�����У�x��yΪ��ͷ���ĵ����꣬arrowtype����������ͷ���࣬0Ϊ> ,1Ϊ->
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


void rightordownarrow(int x, int y,  int arrowtype,int downorright)//downorright����������ʲô����ļ�ͷ
{
	if(downorright==1)//���¼�ͷ
		line(x,y,x-3,y-3);
		line(x,y,x+3,y-3);
		if(arrowtype==1)
		{
			line(x,y,x,y-9);
		}
	if(downorright==2)//���Ҽ�ͷ
		line(x,y,x-3,y+3);
		line(x,y,x-3,y-3);
		if(arrowtype==1)
		{
			line(x,y,x-9,y);
		}
}


