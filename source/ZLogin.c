//作用：画出登录界面，识别用户名密码正确后登录，退出程序。作者：王真
 #include "common.h"
 #include "ZLogin.h"
int login()
{
	
	
    int i ,j ,m,n,k=0,l=0,b;	int gdriver ,gmode;
    char str1[100],str2[100],str3[100],str4[100];
    int c;
    char s[100];
    int flag=1;//flag=0时说明密码正确
    
    FILE* fp1;FILE* fp2;//fp1为账户，fp2为密码
    fp1=fopen("../txt/username","rt");
    fp2=fopen("../txt/password","rt");
    
	gdriver=DETECT;
	initgraph(&gdriver,&gmode,"../../borlandc/bgi");
    fgets(str1,6,fp1);
    fgets(str2,9,fp2);//str1为系统账户，str2为系统密码,str3为输入账户，str4为输入密码
	
	setbkcolor(LIGHTBLUE);
	clrmous(MouseX,MouseY);
	mouseinit();
	delay(10);	
	puthz(90,150,"欢迎进入计算机资源管理系统",32,32,WHITE);
	puthz(70,300,"请输入您的密码：",16,16,WHITE);
	puthz(70,260,"请输入您的账户：",16,16,WHITE);
	setlinestyle(0,0,3);
	setcolor(WHITE);

	//bar(195,288,500,315);
	//bar(195,248,500,275);
	setlinestyle(0,0,1);
	rectangle(70,360,170,400);
	rectangle(290,360,390,400);
	rectangle(510,360,610,400);		
	setfillstyle(1,LIGHTGRAY);
	floodfill(100,380,WHITE);
	floodfill(350,380,WHITE);	
	floodfill(550,380,WHITE);		
	puthz(100,370,"退出",16,16,RED);
	puthz(315,370,"登录",16,16,RED);	
	puthz(528,370,"游客登录",16,16,RED);	
	setcolor(WHITE);
	while(1)
{	
	newmouse(&MouseX,&MouseY,&press);
	if(mouse_press(195,230,500,275)==1)
	{
		here4:
	
		newmouse(&MouseX,&MouseY,&press);		
		 while(1)                         //账号的输入
		{
			GetString(195,255,300,str3,2);
			break;
		}
	}
	
	
	k=0;
	l=0;
	if(mouse_press(195,278,500,315)==1)
	{
		here3:
		newmouse(&MouseX,&MouseY,&press);		
		while(1)                             //密码输入，与账号同
		{
			setcolor(LIGHTGRAY);
			newmouse(&MouseX,&MouseY,&press);		
			
			 GetString(195,295,300,str4,3);
			 break;
			 newmouse(&MouseX,&MouseY,&press);
		 }
	}
	if(strcmp(str1,str3)==0&&strcmp(str2,str4)==0)
	{
		flag=0;
	}
	
	while(1)
	{	
		if(mouse_press(195,278,500,315)==1)
	{
			goto here3;
	}
	if(mouse_press(195,230,500,275)==1)
	{
		goto here4;
	}
			newmouse(&MouseX,&MouseY,&press);			
			switch(mouse_press(70,360,170,400))//点击退出键
			{
				case 1:
					return 0;
				case 2:
					break;					
				default:
					break;
			}
			switch(mouse_press(290,360,390,400))//点击登录键
			{
				case 1:
				if(flag==0)
						
						return 2;
					else
						puthz(195,340,"账户名或密码错误，请重试！",16,16,RED);
						delay(300);
						setfillstyle(1,LIGHTBLUE);
						bar(190,340,630,358);
					break;
					
				case 2:
					break;
				default:
					break;
			}
			switch(mouse_press(510,360,610,400))//游客登录的实现
			{
				case 1:
					return 2;					
				case 2:
					break;
				default:
					break;
			}
			
	}
}
fclose(fp1);fclose(fp2);
	
}

