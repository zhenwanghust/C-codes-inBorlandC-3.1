 #include "common.h"
 #include "ZRight.h"
 #include "main.h"
 
/********************************************************************************
 * ���ܣ���ʾ��ǰ�ļ��������е��ļ���Ԫ
 * �������ļ��еĽṹָ��temoNode����ʾ����ʼ�㣨�����Ͻǣ���x��y������ǰҳ��filePage
 * ����ֵ����
 * *******************************************************************************/
void clearrightscreen()//�ð�ɫ�����Ҳ���ʾ��
{
	setfillstyle(1,WHITE);
	bar(RIGHTSTARTX-5,RIGHTSTARTY+3,639,457);
}

int ZFileUnit(Node*tempNodeSe,int x,int y,int filePage,short int displayMode)
{
    Node* temp;
    int size;
    char* c,*k;
	char* suffix=NULL;//���ڴ����ļ���׺���ڴ��Ժ����
	char* countchar=NULL;
	char* pagemaxchar=NULL;
	short int bigIconXCount = 0;//���ڼ����ͼ��ģʽ�£���ǰ��һ���Ѿ���ʾ���ļ�����
	int i = 0;
	int bx=x,by=y;
	int count=0;
	int pagemax;
	int fileallnum;
	int selected;
	char fileallnumchar[4];
	char selectedchar[4];
	Node* tempNode = tempNodeSe;
	temp=tempNode;
	tempNode = tempNode->child;//tempnodeΪ��ǰ�ļ��еĽṹָ���child,�Ѿ������ļ��У���������
	if(displayMode == 2) 
		bx+=20;//��ͼ��ģʽʱ��ʼ��ͼλ��ƫ��
		by+=7;
	if(displayMode == 1) 
		by+=3;//Сͼ��ģʽʱ��ʼ��ͼλ��ƫ��
	clrmous(MouseX,MouseY);
	clearrightscreen();
	showcurrentpage(filePage);
	pagemax=countpages(tempNode);//�õ��ýڵ�����Ҫ�����ҳ��������Ϊ����ֵ
	if(pagemax==0)
		pagemax=1;//����ʾ�����߼�
	fileallnum=countfiles(tempNodeSe);//������ʾ�����ļ��ܸ���
	setfillstyle(1,WHITE);
	bar(39,461,60,479);
	itoa(fileallnum,fileallnumchar,10);
	outtextxy(46,467,fileallnumchar);//������ʾ�������ļ�
	itoa(pagemax,pagemaxchar,10);
	bar(138,461,152,479);
	outtextxy(140,467,pagemaxchar);//������ʾ���ҳ��
	selected=countselected(tempNodeSe);
	itoa(selected,selectedchar,10);
	setfillstyle(1,WHITE);
	bar(283,461,299,479);
	outtextxy(285,467,selectedchar);
	leftarrow(30, 448, 1);
	rightarrow(120, 448, 1);
	if (temp->flag != 2 && temp->flag != 3)//��ʾ·��
		{
			setfillstyle(1, WHITE);
			bar(121, 66, 454, 84);
			c = GetDir(temp);
			
			size=strlen(c);
			if(size>40)
			{
				for(i=0;i<size-37;i++)
				{
					strcpy(c,c+1);
				}
				strcpy(k,"...");
				strcat(k,c);
				outtextxy(125, 72, k);
			}	
			else
			{
				outtextxy(125, 72, c);
			}
			free(c);
		}
		else if (temp->flag == 2)
		{
			setfillstyle(1, WHITE);
			bar(121, 66, 454, 84);
			outtextxy(125, 72, "C:/");
		}
	if(temp->flag == 3)
	{
		setfillstyle(1, WHITE);
		bar(121, 66, 454, 84);
		outtextxy(129, 72, "Home");
		
	}
	if(displayMode==2)
		for(i = 0;i<(BIGPAGEMAX*(filePage-1));i++)//ָ���Ƶ��ڶ�ҳ��ͷӦ��ʾ���ļ��Ľ�㴦,�ڶ�ҳִ��һ�Σ�����ҳִ������
		{
			tempNode = tempNode->brother;
			if(tempNode == NULL)
			{
				filePage = 0;//����ڶ�ҳ��ͷӦ��ʾ���ļ��Ľ��Ϊ�գ���ôֱ���˳�ѭ����
				break;
			}
		}
	else if (displayMode==1)
	{
		for(i = 0;i<(SHOWMAX*(filePage-1));i++)//ָ���Ƶ��ڶ�ҳ��ͷӦ��ʾ���ļ��Ľ�㴦,�ڶ�ҳִ��һ�Σ�����ҳִ������
		{
			tempNode = tempNode->brother;
			if(tempNode == NULL)
			{
				filePage = 0;//����ڶ�ҳ��ͷӦ��ʾ���ļ��Ľ��Ϊ�գ���ôֱ���˳�ѭ����
				break;
			}
		}
	}
	
	
	for(i = 0;i<SHOWMAX;i++)//iС��ÿҳ��ʾ������ļ�����
	{
		suffix = ZGetSuffix(tempNode);//����getsuffix�����õ���ǰ�ļ������ļ��ĺ�׺���ơ�
		if(tempNode == NULL) //1.�ļ���Ϊ�յ����,ֱ�ӷ��ء�
		{
			puthz(RIGHTSTARTX+150,RIGHTSTARTY+40,"���ļ���Ϊ�ա�",32,32,LIGHTGRAY);
			free(suffix);
			return;
		}
		
		if(tempNode->brother == NULL)//2.������ļ��к�û���ļ�������ͽ�����������Ϊѡ�к�δѡ�����ֻ�ͼ��
		{
			if(tempNode->responseFlag == 0)//��δѡ���ļ�
			{
				
				if(displayMode == 1) //Сͼ��ģʽ�£�����drawfile��������ͼ�꣬���ƣ�
				{
					ZDrawFileUnit((char*)suffix,tempNode,bx,by,displayMode);
					by+=YGAP;//��y��ͼ��������
					
				}
				if(displayMode == 2)//��ͼ��ģʽ�£�����drawfile��������ͼ�꣬���ƣ�
				{
					ZDrawFileUnit((char*)suffix,tempNode,bx,by,displayMode);
					bx+=BIGICONX;
					
					bigIconXCount++;
				}
			}
			
			else if(tempNode->responseFlag == 1)//��ѡ�����ļ�
			{
				if(displayMode == 1)
				{
					setfillstyle(1,CLICKCOLOR);
					bar(bx-2,by-2,bx+CLICKCOLORLENGTH,by+YGAP-3);//�̵�ɫ
					ZDrawFileUnit((char*)suffix,tempNode,bx,by,displayMode);
					by+=YGAP;
					
				}
				if(displayMode == 2)//
				{
					setfillstyle(1,CLICKCOLOR);
					bar(bx-20,by-2,bx+BIGSELECTEDX,by+BIGSELECTEDY-3);//�̵�ɫ
					ZDrawFileUnit((char*)suffix,tempNode,bx,by,displayMode);
					bx+=BIGICONX;
					bigIconXCount++;
				}
				
			}
			filePage = 0;
			free(suffix);//�ͷź�׺���ַ����ڴ�
			break;
		}
		//3.�ļ��������ж���ļ�
		if(tempNode->responseFlag == 0)//��δѡ���ļ�
		{
			
			if(displayMode == 1) 
			{
				ZDrawFileUnit((char*)suffix,tempNode,bx,by,displayMode);
				by+=YGAP;
			}
			if(displayMode == 2)
			{
				ZDrawFileUnit((char*)suffix,tempNode,bx,by,displayMode);
				bx+=BIGICONX;
				bigIconXCount++;
			}
		}
		else if(tempNode->responseFlag == 1)//��ѡ�����ļ�
		{
			
			if(displayMode == 1)
			{
				setfillstyle(1,CLICKCOLOR);//clickcolorΪ11��ɫ
				bar(bx-2,by-2,bx+CLICKCOLORLENGTH,by+YGAP-3);//�̵�ɫ
				ZDrawFileUnit((char*)suffix,tempNode,bx,by,displayMode);
				by+=YGAP;
			}
			if(displayMode == 2)
			{
				setfillstyle(1,CLICKCOLOR);
				bar(bx-15,by-2,bx+BIGSELECTEDX,by+BIGSELECTEDY-3);//�̵�ɫ
				ZDrawFileUnit((char*)suffix,tempNode,bx,by,displayMode);
				bx+=BIGICONX;
				bigIconXCount++;
			}
		}
		//����Ϊ�ļ������ж���ļ�ʱ��ϸ�ڴ���
		if(tempNode->brother != NULL) //�����һ���ļ����ڣ��ƶ�����һ���ļ�
			tempNode = tempNode->brother;
		if(bigIconXCount == BIGLINEMAX && displayMode == 2) //��ͼ��ģʽ�£���������Ѿ�����4���ļ���ת����һ��
		{
			bigIconXCount = 0;
			by+=BIGICONY;//�����������120
			bx = x+20;//�������ָ�
		}
		if(i == FILECONMAX && displayMode == 1)//�������һҳ�ͽ�����ͼ
		{
			filePage = 0;
			free(suffix);
			break;
		}
		else if(i == BIGPAGEMAX-1 && displayMode == 2)
		{
			filePage = 0;
			free(suffix);
			break;
		}
	}
	return pagemax;
	
	
}

void showcurrentpage(int filepage)
{
	char* filepagechar;
	setfillstyle(1,WHITE);
	bar(456,461,468,479);
	itoa(filepage,filepagechar,10);
	setcolor(DARKGRAY);
	outtextxy(462,468,filepagechar);
	
}
/***********************************
 * ���ܣ��õ��ļ����ҳ��
 * ��������ǰ�ļ��еĽṹָ��tempNode
 * ����ֵ���ļ�����
 * ************************************/
int countpages(Node*tempNode)//�õ��ļ����ҳ��
{
	int times = 0;
	//tempNode = tempNode->child;//�����ļ���
	while(tempNode != NULL)
	{
		times += 1;
		tempNode = tempNode->brother;
	}
	if(times % FILECONMAX == 0)
	{
		return times / FILECONMAX;//��ǰ�ļ����ܱ�ÿҳ����ļ�������
	}
	return (times / FILECONMAX)+1;//��ǰ�ļ������ܱ�ÿҳ����ļ�������
}
/***********************************
 * ���ܣ��õ���ǰ�ļ������ļ��ĸ���
 * ��������ǰ�ļ��еĽṹָ��tempNode
 * ����ֵ���ļ�����
 * ************************************/
int countfiles(Node* tempNode)
{
	int times = 0;
	tempNode = tempNode->child;
	while(tempNode != NULL)
	{
		times += 1;
		tempNode = tempNode->brother;
	}
	return times;

}
int countselected(Node* tempNode)
{
	int selected = 0;
	tempNode = tempNode->child;
	while(tempNode != NULL)
	{
		if(tempNode->responseFlag==1)
		{
			selected++;
		}
		tempNode = tempNode->brother;
	}
	return selected;

}
/***********************************
 * ���ܣ��õ���ǰ�ļ��ĺ�׺��
 * ��������ǰ�ļ��еĽṹָ��tempNode
 * ����ֵ���ļ���׺��
 * *********************************/
char* ZGetSuffix(Node* tempNode)
{
	char* suffix = (char*)malloc(5);

	char* fileName = (char*)malloc(20);
	strcpy(fileName,tempNode->file.name);
	if(tempNode->file.attrib & _A_SUBDIR )//������ļ���
	{
		strcpy(suffix,"DIR");//������ļ��У���׺��ֱ������ΪDIR
		free(fileName);		//�ͷ��ַ������ڴ�  
	}
	else if(strstr(tempNode->file.name,".")==NULL)//��������ļ����ֲ�����׺��
    {
        strcpy(suffix,"N.A");//��������ļ����ֲ�����׺������׺��ֱ������ΪUNKNOWN
		free(fileName);    //�ͷ��ַ������ڴ�    
    }
	else
	{
		while(*fileName != '.'&&*fileName !='\0')//��������ļ������к�׺��,Ҳ�Ǵ���������
		{
			strcpy(fileName,fileName+1);
		}
		strcpy(suffix,fileName+1);	
		free(fileName);//�ͷ��ַ������ڴ�  
	}
	return suffix;//�������ַ���,���Ϊ��һ����ֵ�������ں����ĵ��������С�
}

/*************************************************************************************
 * ���ܣ���ʾ�����ļ���Ԫ
 * �������ļ��ĺ�׺��suffix����ǰ�ļ��Ľṹָ��tempNode����ʾ����ʼ�㣨�����Ͻǣ���x��y��
 * ����ֵ����
 * ***********************************************************************************/
void ZDrawFileUnit(char* suffix,Node* tempNode,int x,int y,short int displayMode)
{
	char dateAndTime[40];
	char fileSize[30];
	char* diskdate="1980/0/0 00:00";
	float nameLen;
	if(tempNode == NULL) 
		return;
	sprintf(dateAndTime,"%d/%d/%d %02d:%02d",tempNode->file.date/512+1980,\
	(tempNode->file.date%512)/32,tempNode->file.date%32,\
	tempNode->file.time/2048,(tempNode->file.time%2048)/32);//���ļ�������޸�ʱ��д���ַ���
	//
	sprintf(fileSize,"%d kB",(tempNode->file.size/1024)+1);//���ļ��Ĵ�Сд���ַ���  
	//byte/1024=kb
	
	if(*fileSize == '-')//����ļ���С�������ʾΪ>32MB
	{
		strcpy(fileSize,">32MB");
	}
	
	
	setcolor(DARKGRAY);
	
	if(tempNode->flag == 2)//������̷������
	{
		setcolor(DARKGRAY);
		if(displayMode==1)	
		{
			sdisk(x,y+5);
		}
		else if(displayMode == 2) 
			IdiskL(x,y+4);
		if(displayMode == 1)
		{
			setcolor(DARKGRAY);
			outtextxy(x+NAMEX,y+NAMEY-3,tempNode->file.name);
		}
		else if(displayMode == 2)//��ͼ��ģʽ
		{
			nameLen = strlen(tempNode->file.name);
			setcolor(DARKGRAY);
			outtextxy(x+BIGICONNAMEX-nameLen*3+8,y+BIGICONNAMEY,tempNode->file.name);
		}
		if(displayMode == 1)
		{
			setcolor(DARKGRAY);
			outtextxy(x+DATEX,y+DATEY-3,diskdate);
		}
		return;
	}
	//��������̸����ڵ㣬��Ϊ��ͼ��ģʽ����ϸ��Ϣģʽ���ַ�ʽ��ʾ��
	if(displayMode == 1)//��ϸ��Ϣģʽ
	{
		setcolor(DARKGRAY);
		if(strcmp(suffix,"DIR")==0)
		{
			setcolor(DARKGRAY);
			outtextxy(x+NAMEX,y+NAMEY,tempNode->file.name);
			outtextxy(x+DATEX,y+DATEY+1,dateAndTime);
			puthz(x+TYPEORSIZEX,y+TYPEORSIZEY+6,"�ļ���",16,16,DARKGRAY);
			//outtextxy(x+SIZENEW,y+TYPEORSIZEY+11,"N.A");
		}
		else
		{
			setcolor(DARKGRAY);
			outtextxy(x+NAMEX,y+NAMEY,tempNode->file.name);
			outtextxy(x+DATEX,y+DATEY+1,dateAndTime);
			outtextxy(x+TYPEORSIZEX,y+TYPEORSIZEY+11,suffix);
			puthz(x+TYPEORSIZEX+25,y+TYPEORSIZEY+6,"�ļ�",16,16,DARKGRAY);
			outtextxy(x+SIZENEW,y+TYPEORSIZEY+11,fileSize);
		}
		//����ͼ��
		y+=7;
		if(strcmp(suffix,"C") == 0)
		{
			sc(x,y);
		}
		else if(strcmp(suffix,"H") == 0)
		{
			sh(x,y);
		}
		else if(strcmp(suffix,"DIR") == 0)
		{
			sfolder(x,y);
		}
		else if(strcmp(suffix,"MP3") == 0)
		{
			smystery(x,y);
		}
		else if(strcmp(suffix,"MP4") == 0)
		{
			smystery(x,y);//��ʱ��û����mp4��ͼ��
		}
		else if(strcmp(suffix,"BMP") == 0)
		{
			spic(x,y);
		}
		else if(strcmp(suffix,"JPG") == 0)
		{
			spic(x,y);
		}
		else if(strcmp(suffix,"PNG") == 0)
		{
			spic(x,y);//ͼƬ���ֺ�׺��ʱ����pic
		}
		else if(strcmp(suffix,"ZIP") == 0)
		{
			smystery(x,y);//��ʱ��û����zip��ͼ��
		}
		else if(strcmp(suffix,"DAT") == 0)
		{
			smystery(x,y);//��ʱ��û����dat��ͼ��
		}
		else if(strcmp(suffix,"TXT") == 0)
		{
			stxt(x,y);
		}
		else if(strcmp(suffix,"PDF") == 0)
		{
			smystery(x,y);//��ʱ��û����pdf��ͼ��
		}
		else if(strcmp(suffix,"XLS") == 0)
		{
			smystery(x,y);//��ʱ��û����xls��ͼ��
		}
		else if(strcmp(suffix,"DOC") == 0)
		{
			sdoc(x,y);
		}
		else if(strcmp(suffix,"CPP") == 0)
		{
			sc(x,y);
		}
		else
		{
			smystery(x,y);//����δ֪�ļ�һ����smystery�������̻�
		}
		y-=7;
	}
	else if(displayMode == 2)//��ͼ��ģʽ
	{
		nameLen = strlen(tempNode->file.name);
		outtextxy(x+BIGICONNAMEX-nameLen*3+8,y+BIGICONNAMEY,tempNode->file.name);
		if(strcmp(suffix,"C") == 0)
		{
			IcL(x,y+7);
		}
		else if(strcmp(suffix,"H") == 0)
		{
			IhL(x,y+7);
		}
		else if(strcmp(suffix,"DIR") == 0)
		{
			IfolderL(x,y+7);
		}
		else if(strcmp(suffix,"TXT") == 0)
		{
			ItxtL(x,y+7);
		}
		else if(strcmp(suffix,"ZIP") == 0 || strcmp(suffix,"RAR") == 0)
		{
			ImysteryL(x,y+7);//��ʱδ����ѹ���ļ��Ĵ�ͼ��
		}
		else if(strcmp(suffix,"DOC") == 0)
		{
			IdocL(x,y+7);
		}
		else if(strcmp(suffix,"BMP") == 0 || strcmp(suffix,"JPG") == 0 || strcmp(suffix,"PNG") == 0)
		{
			IpicL(x,y+7);//����ͼƬ�ļ��Ĵ�ͼ����ʱ����pic��ʾ
		}
		else if(strcmp(suffix,"MP4") == 0 || strcmp(suffix,"MP3") == 0)
		{
			ImysteryL(x,y+7);//��ʱδ������Ƶ��Ƶ�ļ��Ĵ�ͼ��
		}
		else
		{
			ImysteryL(x,y+7);//�����ļ���ͼ��ģʽ��һ����lmystery�����̻���
		}
	}
}
int areyousure()
{
	setfillstyle(1,WHITE);
	bar(300,240,500,380);
	setcolor(DARKGRAY);
	rectangle(300,240,500,380);
	puthz(302, 250, "ȷ��Ҫ����ɾ����", 16, 16, DARKGRAY);
	puthz(335,358, "ȡ��", 16, 16, DARKGRAY);
	puthz(435,358, "ȷ��", 16, 16, DARKGRAY);
	rectangle(330,355,370,375);
	rectangle(430,355,470,375);
	while(1)
	{
		newmouse(&MouseX,&MouseY,&press);
		if(mouse_press(330,355,370,375)==1)
			return 0;
		else if (mouse_press(430,355,470,375)==1)
			return 1;
	}
}