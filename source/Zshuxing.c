#include "main.h"
#include "ZShuxing.h"


void showshuxing(Node* fileNode,int type)
{
	Node*tempNode=fileNode->child;
	if(fileNode->flag == 3&&type==1)//����ʾc�ְֵ̰����� 
		return;
	if(type==2)//���ļ�������ԣ��ҵ�ѡ�е�Ҫ��ʾ���ļ�
	{
		while(tempNode)
		{
			if(tempNode->responseFlag==1)
			{
				break;
			}
			tempNode=tempNode->brother;
		}
	}
	else if(type==1)//�Կհ׵������
	{
		tempNode = fileNode;
	}
	clrmous(MouseX,MouseY);
	drawshuxing(tempNode);
	delay(100);
	while(1)
	{
		newmouse(&MouseX,&MouseY,&press);
		if(mouse_press(550,180,580,210)==1)
		{
			break;
		}
	}
	setfillstyle(1,WHITE);
	bar(200,1,500,29);
	
}

void drawshuxing(Node*fileNode)
{
    char*tempDir;
    char*suffix;
    char folderSum[10]={0},fileSum[10]={0};
	char dateAndTime[40];
	char fileSize[30];
    int folderNum=0,fileNum=0;
    Node*tempNode=fileNode;
    Node*changeNode=NULL;
    
	setfillstyle(1,WHITE);
	bar(200,180,580,420);
	setcolor(DARKGRAY);
	rectangle(200,180,580,420);//��������
	puthz(200,8,"�������Խ������Ͻ����˳�",16,16,RED);
	setcolor(DARKGRAY);
	rectangle(550,175,575,210);
	line(555,180,570,205);
	line(570,180,555,205);
    
    
	suffix=ZGetSuffix(tempNode);//�õ��ļ���
	if(fileNode->flag == 2)
	{
		IdiskL(235,185);
	}
	else{
		if(strcmp(suffix,"C") == 0)
		{
			IcL(235,200);
		}
		else if(strcmp(suffix,"H") == 0)
		{
			IhL(235,200);
		}
		else if(strcmp(suffix,"DIR") == 0)
		{
			IfolderL(235,200);
		}
		else if(strcmp(suffix,"TXT") == 0)
		{
			ItxtL(235,200);
		}
		else if(strcmp(suffix,"ZIP") == 0 || strcmp(suffix,"RAR") == 0)
		{
			ImysteryL(235,200);//��ʱδ����ѹ���ļ��Ĵ�ͼ��
		}
		else if(strcmp(suffix,"DOC") == 0)
		{
			IdocL(235,200);
		}
		else if(strcmp(suffix,"BMP") == 0 || strcmp(suffix,"JPG") == 0 || strcmp(suffix,"PNG") == 0)
		{
			IpicL(235,200);
		}
		else if(strcmp(suffix,"MP4") == 0 || strcmp(suffix,"MP3") == 0)
		{
			ImysteryL(235,200);
		}
		else
		{
			ImysteryL(235,200);//�����ļ���ͼ��ģʽ��һ����lmystery�����̻���
		}
	}
	setcolor(DARKGRAY);//����ɾ
  
	
    tempDir=GetDir(fileNode);//�õ�����ʾ·��
    outtextxy(330,360,tempDir);

    if(strcmp(suffix,"DIR")==0)//������ļ���
    {
        Fileini(tempDir,tempNode);
        changeNode=tempNode->child;//�����ļ���
        while(changeNode)
        {
			fileNum++;
			changeNode=changeNode->brother;
        }
       // SFreeFolder(tempNode);
       
        sprintf(fileSum,"%d",fileNum);
        outtextxy(300,330,fileSum);
        puthz(230,295,"�ļ����ͣ�",16,16,DARKGRAY);//1
		puthz(320,295,"�ļ���",16,16,DARKGRAY);
		
    }
    else
    {
		if(fileNode->flag == 2)
		{
			puthz(230,295,"�ļ����ͣ�����",16,16,DARKGRAY);//1
        }
		else if(fileNode->flag != 2)
		{
			puthz(230,295,"�ļ����ͣ�",16,16,DARKGRAY);//1
			puthz(360,295,"���ļ�",16,16,DARKGRAY);
			outtextxy(330,300,suffix);
        }
       
    }
	
	
	
    sprintf(dateAndTime,"%d/%d/%d %02d:%02d",tempNode->file.date/512+1980,\
	(tempNode->file.date%512)/32,tempNode->file.date%32,\
	tempNode->file.time/2048,(tempNode->file.time%2048)/32);
	sprintf(fileSize,"%d kB",(tempNode->file.size/1024)+1);
	/*���½������ݵ���ʾ*/
	
	settextstyle(0,0,2);
	outtextxy(330,220,tempNode->file.name);
	settextstyle(0,0,1);
	
	
	
	if(*fileSize == '-')    //2
	{
		strcpy(fileSize,">32MB");//����ļ���С��� 
	}
	if(fileNode->flag != 2)
	{
		if(strcmp(suffix,"DIR")!=0)//�Ƿ�Ϊ�ļ���
		{
			puthz(230,325,"�ļ���С��",16,16,DARKGRAY);
			outtextxy(330,330,fileSize);
		}
		else
		{
			puthz(230,325,"�ڲ�����",16,16,DARKGRAY);
			puthz(315,325,"���ļ����У���",16,16,DARKGRAY);
		}
	}
	puthz(230,355,"�ļ�·����",16,16,DARKGRAY);//3
    puthz(230,385,"�޸�ʱ�䣺",16,16,DARKGRAY);//4
    outtextxy(330,390,dateAndTime);
	free(suffix);suffix=NULL;
	free(tempDir);tempDir=NULL;
 
   
}