
 #include "ZInput.h"
 #include "XMouse.h"

//������Ϊ����������������ʱ�����ƶ����֮�⣬��ȫbc�����ʵ�õ����롣

char *GetString(int x,int y,int length,char *string)
{
    char tempChar='\0',dotFlag=0;     //���ڽ���������ַ�
    char temp[80];          //�����ַ���
    int n,i=-1,t=0,j;          //nΪ�ַ������ȣ�iΪ��ǰ���λ��
    setfillstyle(1,WHITE);
    length+=20;
	bar(x+2,y+2,x+length,y+20);
    fflush(stdin);  //ˢ�¼��̻�����
    setcolor(RED);
	outtextxy(200,13,"PRESS ENTER TO QUIT!");//�˳���Ҫbar��
	setcolor(DARKGRAY);
	strcpy(string,"");
    
    rectangle(505,65,635,86);//��������
	setfillstyle(1,WHITE);
	setcolor(DARKGRAY);
	outtextxy(x+2,y+9,string);//д���ַ�����ʼ����
   
    n=strlen(string);
   
    if(i==-1)
        i=n;

    
    while(1)
    {
        while(!kbhit())//��û�м�������ʱ
        {
            if(t>0)//�ж��Ƿ�Ӧ�ø�Ϊ����ż��
                setcolor(RED);
            else
                setcolor(WHITE);
            line(x+2+8*i,y+9,x+2+8*i,y+18);//ʵ�������껮��
            t++;
        }
        //����t���ڼ�ʱ��ʵ����˸����Ч��
		setcolor(DARKGRAY);
		rectangle(505,65,635,86);//��������
	
        tempChar=getch();

        if(tempChar=='\r'||tempChar==0x1B)  //�س���ESC��ֱ���˳�
        { 
			setcolor(WHITE);
            line(x+2+8*i,y+9,x+2+8*i,y+18);
            break;
        }
        else if(tempChar=='\b')  //�˸��
        {
            if(n&&i)
            {
                strcpy(string+i-1,string+i);//�ײ���string�˺�
                n--;
                i--;
            }
        }
        else if(tempChar=='\0')
        {
            tempChar=getch();
            if(tempChar=='K'&&i)  //�����
                i--;
            else if(tempChar=='M'&&n>i)    //�ҷ����
                i++;
        }
        else if(n<13&&
			(tempChar>='0'&&tempChar<='9'
            ||tempChar>='a'&&tempChar<='z'
            ||tempChar>='A'&&tempChar<='Z'
            ||tempChar=='.')
            )//�����Ƴ��Ⱥ������ַ�
        {
            strcpy(temp,string+i);
            string[i++]=tempChar;
            strcpy(string+i,temp);
            n++;
        }
        //�Ϸ��ַ�����

        setfillstyle(1,WHITE);
        bar(x+2,y+2,x+length,y+20);  //�ȸ��� 
          rectangle(505,65,635,86);//��������
		outtextxy(x+2,y+9,string);//��ȫ�����
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