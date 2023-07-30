
 #include "common.h"
 #include "ZQuit.h"

void Zquit()//退出程序所用
{
	cleardevice();
	setbkcolor(LIGHTBLUE);
	puthz(90,150,"感谢您的使用，再见！",32,32,WHITE);
	delay(500);
	closegraph();
}