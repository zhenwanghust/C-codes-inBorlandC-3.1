#include "main.h"


int getrightarea(int area,int x,int y)//���ĸ����ޣ��õ��Ҽ��Ƿ�����ֵ
{//know where you clicked in right menu
	int rightarea=0;
	if(area==1)
	{
		if(mouse_press(x-105,y,x,y+20)==1) 
		{
			rightarea=1;
		}
		if(mouse_press(x-105,y+20,x,y+40)==1) 
			rightarea=2;
		if(mouse_press(x-105,y+40,x,y+60)==1) 
			rightarea=3;
		if(mouse_press(x-105,y+60,x,y+80)==1) 
			rightarea=4;
		if(mouse_press(x-105,y+80,x,y+100)==1) 
			rightarea=5;
		if(mouse_press(x-105,y+100,x,y+120)==1) 
			rightarea=6;
	}
		if(area==2)
	{
		if(mouse_press(x,y,x+105,y+20)==1)
			rightarea=1;
		if(mouse_press(x,y+20,x+105,y+40)==1)
			rightarea=2;
		if(mouse_press(x,y+40,x+105,y+60)==1)
			rightarea=3;
		if(mouse_press(x,y+60,x+105,y+80)==1)
			rightarea=4;
		if(mouse_press(x,y+80,x+105,y+100)==1)
			rightarea=5;
		if(mouse_press(x,y+100,x+105,y+120)==1) 
		{
			rightarea=6;
		}
	}
	if(area==3)
	{
		
		if(mouse_press(x,y-120,x+105,y-100)==1)
			rightarea=1;
		if(mouse_press(x,y-100,x+105,y-80)==1)
			rightarea=2;
		if(mouse_press(x,y-80,x+105,y-60)==1)
			rightarea=3;
		if(mouse_press(x,y-60,x+105,y-40)==1) 
			rightarea=4;
		if(mouse_press(x,y-40,x+105,y-20)==1)
			rightarea=5;
		if(mouse_press(x,y-20,x+105,y)==1)
			rightarea=6;
		
	}
	if(area==4)
	{
		if(mouse_press(x-105,y-120,x,y-100)==1)
			rightarea=1;
		if(mouse_press(x-105,y-100,x,y-80)==1)
			rightarea=2;
		if(mouse_press(x-105,y-80,x,y-60)==1)
			rightarea=3;
		if(mouse_press(x-105,y-60,x,y-40)==1)
			rightarea=4;
		if(mouse_press(x-105,y-40,x,y-20)==1)
			rightarea=5;
		if(mouse_press(x-105,y-20,x,y)==1)
			rightarea=6;
	}

	return rightarea;
	
}



void smallrightpressblankdrawdown(int x, int y,int showmode)//Сģʽ����հף����»�
{
		int i;
		setcolor(DARKGRAY);
		setfillstyle(1,WHITE);
		bar(x,y,x-105,y+120);
		rectangle(x,y,x-105,y+120);
		for(i=20;i<=100;i+=20)
		{
			line(x,y+i,x-105,y+i);
		}
		x-=75;
		//y-=20;
		if(showmode==1)
		{
			puthz(x-25,y,"�Դ�ͼ��鿴",16,16,DARKGRAY);
		}
		else if(showmode==2)
		{
			puthz(x-25,y,"��Сͼ��鿴",16,16,DARKGRAY);
		}
		puthz(x-25,y+20,"����������",16,16,DARKGRAY);
		puthz(x-25,y+40,"ˢ��",16,16,DARKGRAY);
		puthz(x-25,y+60,"ճ��",16,16,DARKGRAY);
		puthz(x-25,y+80,"�½��ļ���",16,16,DARKGRAY);
		puthz(x-25,y+100,"����",16,16,DARKGRAY);
		
		//y+=20;
		x+=75;
	
}
void smallrightpressblankdrawup(int x, int y,int showmode)//Сģʽ����հף����ϻ�
{
		int i;
		setcolor(DARKGRAY);
		setfillstyle(1,WHITE);
		bar(x,y,x-105,y-120);
		rectangle(x,y,x-105,y-120);
		for(i=20;i<=100;i+=20)
		{
			line(x,y-i,x-105,y-i);
		}
		x-=75;
		y-=20;
		if(showmode==1)
		{
			puthz(x-25,y-100,"�Դ�ͼ��鿴",16,16,DARKGRAY);
		}
		else if(showmode==2)
		{
			puthz(x-25,y-100,"��Сͼ��鿴",16,16,DARKGRAY);
		}
		puthz(x-25,y-80,"����������",16,16,DARKGRAY);
		puthz(x-25,y-60,"ˢ��",16,16,DARKGRAY);
		puthz(x-25,y-40,"ճ��",16,16,DARKGRAY);
		puthz(x-25,y-20,"�½��ļ���",16,16,DARKGRAY);
		puthz(x-25,y,"����",16,16,DARKGRAY);

		y+=20;
		x+=75;
}
void bigrightpressblankfirst(int x, int y,int showmode)//��ģʽ��һ���ޣ���հף����»�
{
		int i;
		setcolor(DARKGRAY);
		setfillstyle(1,WHITE);
		bar(x,y,x-105,y+120);
		rectangle(x,y,x-105,y+120);
		for(i=20;i<=100;i+=20)
		{
			line(x,y+i,x-105,y+i);
		}
		x-=75;		
		if(showmode==1)
		{
			puthz(x-25,y,"�Դ�ͼ��鿴",16,16,DARKGRAY);
		}
		else if(showmode==2)
		{
			puthz(x-25,y,"��Сͼ��鿴",16,16,DARKGRAY);
		}
		puthz(x-25,y+20,"����������",16,16,DARKGRAY);
		puthz(x-25,y+40,"ˢ��",16,16,DARKGRAY);
		puthz(x-25,y+60,"ճ��",16,16,DARKGRAY);
		puthz(x-25,y+80,"�½��ļ���",16,16,DARKGRAY);
		puthz(x-25,y+100,"����",16,16,DARKGRAY);
		x+=75;
}
void bigrightpressblanksecond(int x, int y,int showmode)//��ģʽ�������ޣ���հף����»�X+Y+
{
		int i;
		setcolor(DARKGRAY);
		setfillstyle(1,WHITE);
		bar(x,y,x+105,y+120);
		rectangle(x,y,x+105,y+120);
		for(i=20;i<=100;i+=20)
		{
			line(x,y+i,x+105,y+i);
		}
		x-=23;
		
		if(showmode==1)
		{
			puthz(x+25,y,"�Դ�ͼ��鿴",16,16,DARKGRAY);
		}
		else if(showmode==2)
		{
			puthz(x+25,y,"��Сͼ��鿴",16,16,DARKGRAY);
		}
		puthz(x+25,y+20,"����������",16,16,DARKGRAY);
		puthz(x+25,y+40,"ˢ��",16,16,DARKGRAY);
		puthz(x+25,y+60,"ճ��",16,16,DARKGRAY);
		puthz(x+25,y+80,"�½��ļ���",16,16,DARKGRAY);
		puthz(x+25,y+100,"����",16,16,DARKGRAY);

		
		x+=23;
}
void bigrightpressblankthird(int x, int y,int showmode)//��ģʽ�������ޣ���հף����ϻ�
{
		int i;
		setcolor(DARKGRAY);
		setfillstyle(1,WHITE);
		bar(x,y,x+105,y-120);
		rectangle(x,y,x+105,y-120);
		for(i=20;i<=100;i+=20)
		{
			line(x,y-i,x+105,y-i);
		}
		x-=23;
		y-=20;
		if(showmode==1)
		{
			puthz(x+25,y-100,"�Դ�ͼ��鿴",16,16,DARKGRAY);
		}
		else if(showmode==2)
		{
			puthz(x+25,y-100,"��Сͼ��鿴",16,16,DARKGRAY);
		}
		puthz(x+25,y-80,"����������",16,16,DARKGRAY);
		puthz(x+25,y-60,"ˢ��",16,16,DARKGRAY);
		puthz(x+25,y-40,"ճ��",16,16,DARKGRAY);
		puthz(x+25,y-20,"�½��ļ���",16,16,DARKGRAY);
		puthz(x+25,y,"����",16,16,DARKGRAY);

		y+=20;
		x+=23;
}
	

void bigrightpressblankfourth(int x, int y,int showmode)//��ģʽ�������ޣ���հף����ϻ�
{
		int i;
		setcolor(DARKGRAY);
		setfillstyle(1,WHITE);
		bar(x,y,x-105,y-120);
		rectangle(x,y,x-105,y-120);
		for(i=20;i<=100;i+=20)
		{
			line(x,y-i,x-105,y-i);
		}
		x-=75;
		y-=20;
		if(showmode==1)
		{
			puthz(x-25,y-100,"�Դ�ͼ��鿴",16,16,DARKGRAY);
		}
		else if(showmode==2)
		{
			puthz(x-25,y-100,"��Сͼ��鿴",16,16,DARKGRAY);
		}
		puthz(x-25,y-80,"����������",16,16,DARKGRAY);
		puthz(x-25,y-60,"ˢ��",16,16,DARKGRAY);
		puthz(x-25,y-40,"ճ��",16,16,DARKGRAY);
		puthz(x-25,y-20,"�½��ļ���",16,16,DARKGRAY);
		puthz(x-25,y,"����",16,16,DARKGRAY);

		y+=20;
		x+=75;
}
void bigrightpressfilefirst(int x, int y)//��ģʽ��һ���ޣ����ļ������»�
{
		int i;
		setcolor(DARKGRAY);
		setfillstyle(1,WHITE);
		bar(x,y,x-105,y+120);
		rectangle(x,y,x-105,y+120);
		
		for(i=20;i<=100;i+=20)
		{
			line(x,y+i,x-105,y+i);
		}
		x-=105;
		puthz(x,y,"��",16,16,DARKGRAY);
		puthz(x,y+20,"����",16,16,DARKGRAY);
		puthz(x,y+40,"����",16,16,DARKGRAY);
		puthz(x,y+60,"ɾ��",16,16,DARKGRAY);
		puthz(x,y+80,"������",16,16,DARKGRAY);
		puthz(x,y+100,"����",16,16,DARKGRAY);
		x+=105;	
}
void bigrightpressfilesecond(int x, int y)//��ģʽ�������ޣ����ļ������»�
{
		int i;
		setcolor(DARKGRAY);
		setfillstyle(1,WHITE);
		bar(x,y,x+105,y+120);
		rectangle(x,y,x+105,y+120);
		
		for(i=20;i<=100;i+=20)
		{
			line(x,y+i,x+105,y+i);
		}
		x+=3;
		puthz(x,y,"��",16,16,DARKGRAY);
		puthz(x,y+20,"����",16,16,DARKGRAY);
		puthz(x,y+40,"����",16,16,DARKGRAY);
		puthz(x,y+60,"ɾ��",16,16,DARKGRAY);
		puthz(x,y+80,"������",16,16,DARKGRAY);
		puthz(x,y+100,"����",16,16,DARKGRAY);
		x-=3;	
}
void bigrightpressfilethird(int x, int y)//��ģʽ�������ޣ����ļ������ϻ�
{
		int i;
		setcolor(DARKGRAY);
		setfillstyle(1,WHITE);
		bar(x,y,x+105,y-120);
		rectangle(x,y,x+105,y-120);
		for(i=20;i<=100;i+=20)
		{
			line(x,y-i,x+105,y-i);
		}
		y-=20;
		x+=3;
		puthz(x,y-100,"��",16,16,DARKGRAY);
		puthz(x,y-80,"����",16,16,DARKGRAY);
		puthz(x,y-60,"����",16,16,DARKGRAY);
		puthz(x,y-40,"ɾ��",16,16,DARKGRAY);
		puthz(x,y-20,"������",16,16,DARKGRAY);
		puthz(x,y,"����",16,16,DARKGRAY);
		y+=20;
		x-=3;	
}
void bigrightpressfilefourth(int x, int y)//��ģʽ�������ޣ����ļ������ϻ�
{
		int i;
		setcolor(DARKGRAY);
		setfillstyle(1,WHITE);
		bar(x,y,x-105,y-120);
		rectangle(x,y,x-105,y-120);
		
		for(i=20;i<=100;i+=20)
		{
			line(x,y-i,x-105,y-i);
		}
		x-=105;
		y-=20;
		puthz(x,y-100,"��",16,16,DARKGRAY);
		puthz(x,y-80,"����",16,16,DARKGRAY);
		puthz(x,y-60,"����",16,16,DARKGRAY);
		puthz(x,y-40,"ɾ��",16,16,DARKGRAY);
		puthz(x,y-20,"������",16,16,DARKGRAY);
		puthz(x,y,"����",16,16,DARKGRAY);
		x+=105;
		y+=20;	
}

