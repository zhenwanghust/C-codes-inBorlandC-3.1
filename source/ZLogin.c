//���ã�������¼���棬ʶ���û���������ȷ���¼���˳��������ߣ�����
 #include "common.h"
 #include "ZLogin.h"
int login()
{
	
	
    int i ,j ,m,n,k=0,l=0,b;	int gdriver ,gmode;
    char str1[100],str2[100],str3[100],str4[100];
    int c;
    char s[100];
    int flag=1;//flag=0ʱ˵��������ȷ
    
    FILE* fp1;FILE* fp2;//fp1Ϊ�˻���fp2Ϊ����
    fp1=fopen("../txt/username","rt");
    fp2=fopen("../txt/password","rt");
    
	gdriver=DETECT;
	initgraph(&gdriver,&gmode,"../../borlandc/bgi");
    fgets(str1,6,fp1);
    fgets(str2,9,fp2);//str1Ϊϵͳ�˻���str2Ϊϵͳ����,str3Ϊ�����˻���str4Ϊ��������
	
	setbkcolor(LIGHTBLUE);
	clrmous(MouseX,MouseY);
	mouseinit();
	delay(10);	
	puthz(90,150,"��ӭ����������Դ����ϵͳ",32,32,WHITE);
	puthz(70,300,"�������������룺",16,16,WHITE);
	puthz(70,260,"�����������˻���",16,16,WHITE);
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
	puthz(100,370,"�˳�",16,16,RED);
	puthz(315,370,"��¼",16,16,RED);	
	puthz(528,370,"�ο͵�¼",16,16,RED);	
	setcolor(WHITE);
	while(1)
{	
	newmouse(&MouseX,&MouseY,&press);
	if(mouse_press(195,230,500,275)==1)
	{
		here4:
	
		newmouse(&MouseX,&MouseY,&press);		
		 while(1)                         //�˺ŵ�����
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
		while(1)                             //�������룬���˺�ͬ
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
			switch(mouse_press(70,360,170,400))//����˳���
			{
				case 1:
					return 0;
				case 2:
					break;					
				default:
					break;
			}
			switch(mouse_press(290,360,390,400))//�����¼��
			{
				case 1:
				if(flag==0)
						
						return 2;
					else
						puthz(195,340,"�˻�����������������ԣ�",16,16,RED);
						delay(300);
						setfillstyle(1,LIGHTBLUE);
						bar(190,340,630,358);
					break;
					
				case 2:
					break;
				default:
					break;
			}
			switch(mouse_press(510,360,610,400))//�ο͵�¼��ʵ��
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

