
 #include "ZInput.h"
 #include "XMouse.h"

//个人认为这个输入除了在输入时不能移动鼠标之外，是全bc最简易实用的输入。

char *GetString(int x,int y,int length,char *string)
{
    char tempChar='\0',dotFlag=0;     //用于接收输入的字符
    char temp[80];          //辅助字符串
    int n,i=-1,t=0,j;          //n为字符串长度，i为当前输出位置
    setfillstyle(1,WHITE);
    length+=20;
	bar(x+2,y+2,x+length,y+20);
    fflush(stdin);  //刷新键盘缓冲区
    setcolor(RED);
	outtextxy(200,13,"PRESS ENTER TO QUIT!");//退出后要bar！
	setcolor(DARKGRAY);
	strcpy(string,"");
    
    rectangle(505,65,635,86);//画搜索框
	setfillstyle(1,WHITE);
	setcolor(DARKGRAY);
	outtextxy(x+2,y+9,string);//写出字符串初始内容
   
    n=strlen(string);
   
    if(i==-1)
        i=n;

    
    while(1)
    {
        while(!kbhit())//当没有键盘输入时
        {
            if(t>0)//判断是否应该改为奇数偶数
                setcolor(RED);
            else
                setcolor(WHITE);
            line(x+2+8*i,y+9,x+2+8*i,y+18);//实现输入光标划线
            t++;
        }
        //变量t用于计时，实现闪烁光标的效果
		setcolor(DARKGRAY);
		rectangle(505,65,635,86);//画搜索框
	
        tempChar=getch();

        if(tempChar=='\r'||tempChar==0x1B)  //回车键ESC键直接退出
        { 
			setcolor(WHITE);
            line(x+2+8*i,y+9,x+2+8*i,y+18);
            break;
        }
        else if(tempChar=='\b')  //退格键
        {
            if(n&&i)
            {
                strcpy(string+i-1,string+i);//底层让string退后
                n--;
                i--;
            }
        }
        else if(tempChar=='\0')
        {
            tempChar=getch();
            if(tempChar=='K'&&i)  //左方向键
                i--;
            else if(tempChar=='M'&&n>i)    //右方向键
                i++;
        }
        else if(n<13&&
			(tempChar>='0'&&tempChar<='9'
            ||tempChar>='a'&&tempChar<='z'
            ||tempChar>='A'&&tempChar<='Z'
            ||tempChar=='.')
            )//先限制长度后限制字符
        {
            strcpy(temp,string+i);
            string[i++]=tempChar;
            strcpy(string+i,temp);
            n++;
        }
        //合法字符检验

        setfillstyle(1,WHITE);
        bar(x+2,y+2,x+length,y+20);  //先覆盖 
          rectangle(505,65,635,86);//画搜索框
		outtextxy(x+2,y+9,string);//再全部输出
	}
    
    bar(190, 1, 190 + 16 * 23, 29);
    setcolor(DARKGRAY);
   	rectangle(505,65,635,86);
    for(i=0,n=strlen(string);i<n;i++)
		if(string[i]>='a'&&string[i]<='z')
			string[i]+='A'-'a';
    clrmous(MouseX,MouseY);
    return string;
}