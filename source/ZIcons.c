 #include "common.h"
 #include "ZIcons.h"


/*
    函数功能：磁盘图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/

void detailmodeicon(int x,int y)
{
    clrmous(MouseX,MouseY);
    setcolor(DARKGRAY);
    line(x,y,x+11,y);
    line(x,y+1,x+11,y+1);
    line(x,y+4,x+11,y+4);
    line(x,y+6,x+11,y+6);
    line(x,y+8,x+11,y+8);
    line(x,y+10,x+11,y+10);
    line(x,y+11,x+11,y+11);
    putpixel(x+1,y+3,LIGHTBLUE);
    putpixel(x+1,y+6,LIGHTCYAN);
    putpixel(x+1,y+9,RED);
}

void sdisk(int x,int y)
{
   int i;
   int v[]={0,7,6,10,6,13,0,10,0,7};

   setcolor(LIGHTGRAY);
   for(i=0;i<5;i++)
   {
		v[2*i]=x+v[2*i];
		v[2*i+1]=y+v[2*i+1];
   }
   drawpoly(5,v);
   moveto(x,y+7);
   lineto(x+8,y+3);
   lineto(x+14,y+6);
   lineto(x+14,y+9);
   lineto(x+6,y+13);
   moveto(x+6,y+10);
   lineto(x+14,y+6);
   setfillstyle(INTERLEAVE_FILL,DARKGRAY);
   floodfill(x+3,y+10,LIGHTGRAY);
   putpixel(x+5,y+11,GREEN);
}

/*
    函数功能：通用图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void sgeneral(int x,int y)
{
	setcolor(LIGHTGRAY);
	line(x,y,x+7,y);
	line(x+7,y,x+7,y+3);
	line(x+10,y+3,x+10,y+14);
	line(x+10,y+14,x,y+14);
	line(x,y+14,x,y);	
	line(x+7,y,x+10,y+3);
}

/*
    函数功能：文本文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void stxt(int x,int y)
{
	int i;

	sgeneral(x,y);
	for(i=1;i<3;i++)
	{
		line(x+2,y+2*i,x+5,y+2*i);
	}
	for(i=3;i<7;i++)
	{
		line(x+2,y+2*i,x+8,y+2*i);
	}
}

/*
    函数功能：word图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void sdoc(int x,int y)
{
	sgeneral(x,y);
	setfillstyle(SOLID_FILL,11);
	bar(x-3,y+3,x+6,y+12);
	setcolor(DARKGRAY);
	line(x-2,y+4,x,y+8);
	line(x,y+8,x+2,y+4);
	line(x+2,y+4,x+4,y+8);
	line(x+4,y+8,x+6,y+4);
}

/*
    函数功能：文件夹图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void sfolder(int x,int y)
{
	setfillstyle(1,YELLOW);
	bar(x,y,x+8,y+11);
	setcolor(DARKGRAY);
	rectangle(x,y,x+8,y+11);
	line(x,y,x+3,y+3);
	line(x+3,y+3,x+3,y+15);
	line(x+3,y+15,x,y+12);
	line(x,y+12,x,y);
	floodfill(x+1,y+10,DARKGRAY);	
	floodfill(x+2,y+13,DARKGRAY);	
}

/*
    函数功能：可执行文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void sexe(int x,int y)
{
	setfillstyle(SOLID_FILL,11);
	bar(x+4,y+4,x+9,y+11);
	setcolor(DARKGRAY);
	rectangle(x,y+2,x+15,y+13);
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(x,y+2,x+15,y);
	setcolor(DARKGRAY);
	line(x+11,y+5,x+13,y+5);
	line(x+11,y+7,x+13,y+7);
	line(x+11,y+9,x+13,y+9);
}

/*
    函数功能：c源码文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void sc(int x,int y)
{
	setcolor(LIGHTGRAY);
	rectangle(x,y,x+11,y+12);
	setfillstyle(SOLID_FILL,11);
	bar(x+2,y+8,x+13,y+14);
	setcolor(DARKGRAY);
	arc(x+9,y+11,60,300,2);
}

/*
    函数功能：h源码文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void sh(int x,int y)
{
	setcolor(LIGHTGRAY);
	rectangle(x,y,x+11,y+12);
	setfillstyle(SOLID_FILL,RED);
	bar(x+2,y+8,x+13,y+14);
	setcolor(WHITE);
	line(x+6,y+9,x+6,y+13);
	line(x+8,y+11,x+8,y+13);
	arc(x+7,y+11,0,180,1);
}

/*
    函数功能：目标文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void sobj(int x,int y)
{
	int i=0;
	int v[]={0,0,7,0,7,3,10,3,10,14,0,14,0,0};
	
	setcolor(LIGHTGRAY);
	for(i=0;i<7;i++)
	{
		v[2*i]=x+v[2*i];
		v[2*i+1]=y+v[2*i+1];
	}
	drawpoly(7,v);
	moveto(x+7,y);
	lineto(x+10,y+3);
	setfillstyle(SOLID_FILL,WHITE);
	bar3d(x+3,y+11,x+6,y+7,2,1);
}

/*
    函数功能：未知文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void smystery(int x,int y){sgeneral(x,y);}

/*
    函数功能：图形文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void spic(int x,int y)
{
	setfillstyle(SOLID_FILL,11);
	bar(x,y,x+14,y+7);
    setfillstyle(SOLID_FILL,LIGHTBLUE);
	bar(x,y+8,x+14,y+14);
	setfillstyle(SOLID_FILL,WHITE);
	bar(x+10,y+2,x+12,y+4);
	setcolor(LIGHTBLUE);
	line(x+1,y+8,x+8,y+8);
	line(x+2,y+7,x+7,y+7);
	line(x+3,y+6,x+6,y+6);
	line(x+4,y+5,x+5,y+4);
}