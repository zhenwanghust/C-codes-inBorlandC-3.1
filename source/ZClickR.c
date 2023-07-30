#include "main.h"


int getrightarea(int area,int x,int y)//分四个象限，得到右键是否点击的值
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



void smallrightpressblankdrawdown(int x, int y,int showmode)//小模式，点空白，向下画
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
			puthz(x-25,y,"以大图标查看",16,16,DARKGRAY);
		}
		else if(showmode==2)
		{
			puthz(x-25,y,"以小图标查看",16,16,DARKGRAY);
		}
		puthz(x-25,y+20,"按名称排序",16,16,DARKGRAY);
		puthz(x-25,y+40,"刷新",16,16,DARKGRAY);
		puthz(x-25,y+60,"粘贴",16,16,DARKGRAY);
		puthz(x-25,y+80,"新建文件夹",16,16,DARKGRAY);
		puthz(x-25,y+100,"属性",16,16,DARKGRAY);
		
		//y+=20;
		x+=75;
	
}
void smallrightpressblankdrawup(int x, int y,int showmode)//小模式，点空白，向上画
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
			puthz(x-25,y-100,"以大图标查看",16,16,DARKGRAY);
		}
		else if(showmode==2)
		{
			puthz(x-25,y-100,"以小图标查看",16,16,DARKGRAY);
		}
		puthz(x-25,y-80,"按名称排序",16,16,DARKGRAY);
		puthz(x-25,y-60,"刷新",16,16,DARKGRAY);
		puthz(x-25,y-40,"粘贴",16,16,DARKGRAY);
		puthz(x-25,y-20,"新建文件夹",16,16,DARKGRAY);
		puthz(x-25,y,"属性",16,16,DARKGRAY);

		y+=20;
		x+=75;
}
void bigrightpressblankfirst(int x, int y,int showmode)//大模式，一象限，点空白，左下画
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
			puthz(x-25,y,"以大图标查看",16,16,DARKGRAY);
		}
		else if(showmode==2)
		{
			puthz(x-25,y,"以小图标查看",16,16,DARKGRAY);
		}
		puthz(x-25,y+20,"按名称排序",16,16,DARKGRAY);
		puthz(x-25,y+40,"刷新",16,16,DARKGRAY);
		puthz(x-25,y+60,"粘贴",16,16,DARKGRAY);
		puthz(x-25,y+80,"新建文件夹",16,16,DARKGRAY);
		puthz(x-25,y+100,"属性",16,16,DARKGRAY);
		x+=75;
}
void bigrightpressblanksecond(int x, int y,int showmode)//大模式，二象限，点空白，右下画X+Y+
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
			puthz(x+25,y,"以大图标查看",16,16,DARKGRAY);
		}
		else if(showmode==2)
		{
			puthz(x+25,y,"以小图标查看",16,16,DARKGRAY);
		}
		puthz(x+25,y+20,"按名称排序",16,16,DARKGRAY);
		puthz(x+25,y+40,"刷新",16,16,DARKGRAY);
		puthz(x+25,y+60,"粘贴",16,16,DARKGRAY);
		puthz(x+25,y+80,"新建文件夹",16,16,DARKGRAY);
		puthz(x+25,y+100,"属性",16,16,DARKGRAY);

		
		x+=23;
}
void bigrightpressblankthird(int x, int y,int showmode)//大模式，三象限，点空白，右上画
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
			puthz(x+25,y-100,"以大图标查看",16,16,DARKGRAY);
		}
		else if(showmode==2)
		{
			puthz(x+25,y-100,"以小图标查看",16,16,DARKGRAY);
		}
		puthz(x+25,y-80,"按名称排序",16,16,DARKGRAY);
		puthz(x+25,y-60,"刷新",16,16,DARKGRAY);
		puthz(x+25,y-40,"粘贴",16,16,DARKGRAY);
		puthz(x+25,y-20,"新建文件夹",16,16,DARKGRAY);
		puthz(x+25,y,"属性",16,16,DARKGRAY);

		y+=20;
		x+=23;
}
	

void bigrightpressblankfourth(int x, int y,int showmode)//大模式，四象限，点空白，左上画
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
			puthz(x-25,y-100,"以大图标查看",16,16,DARKGRAY);
		}
		else if(showmode==2)
		{
			puthz(x-25,y-100,"以小图标查看",16,16,DARKGRAY);
		}
		puthz(x-25,y-80,"按名称排序",16,16,DARKGRAY);
		puthz(x-25,y-60,"刷新",16,16,DARKGRAY);
		puthz(x-25,y-40,"粘贴",16,16,DARKGRAY);
		puthz(x-25,y-20,"新建文件夹",16,16,DARKGRAY);
		puthz(x-25,y,"属性",16,16,DARKGRAY);

		y+=20;
		x+=75;
}
void bigrightpressfilefirst(int x, int y)//大模式，一象限，点文件，左下画
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
		puthz(x,y,"打开",16,16,DARKGRAY);
		puthz(x,y+20,"复制",16,16,DARKGRAY);
		puthz(x,y+40,"剪切",16,16,DARKGRAY);
		puthz(x,y+60,"删除",16,16,DARKGRAY);
		puthz(x,y+80,"重命名",16,16,DARKGRAY);
		puthz(x,y+100,"属性",16,16,DARKGRAY);
		x+=105;	
}
void bigrightpressfilesecond(int x, int y)//大模式，二象限，点文件，右下画
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
		puthz(x,y,"打开",16,16,DARKGRAY);
		puthz(x,y+20,"复制",16,16,DARKGRAY);
		puthz(x,y+40,"剪切",16,16,DARKGRAY);
		puthz(x,y+60,"删除",16,16,DARKGRAY);
		puthz(x,y+80,"重命名",16,16,DARKGRAY);
		puthz(x,y+100,"属性",16,16,DARKGRAY);
		x-=3;	
}
void bigrightpressfilethird(int x, int y)//大模式，三象限，点文件，右上画
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
		puthz(x,y-100,"打开",16,16,DARKGRAY);
		puthz(x,y-80,"复制",16,16,DARKGRAY);
		puthz(x,y-60,"剪切",16,16,DARKGRAY);
		puthz(x,y-40,"删除",16,16,DARKGRAY);
		puthz(x,y-20,"重命名",16,16,DARKGRAY);
		puthz(x,y,"属性",16,16,DARKGRAY);
		y+=20;
		x-=3;	
}
void bigrightpressfilefourth(int x, int y)//大模式，四象限，点文件，左上画
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
		puthz(x,y-100,"打开",16,16,DARKGRAY);
		puthz(x,y-80,"复制",16,16,DARKGRAY);
		puthz(x,y-60,"剪切",16,16,DARKGRAY);
		puthz(x,y-40,"删除",16,16,DARKGRAY);
		puthz(x,y-20,"重命名",16,16,DARKGRAY);
		puthz(x,y,"属性",16,16,DARKGRAY);
		x+=105;
		y+=20;	
}

