#include "main.h"
#include "ZShuxing.h"


void showshuxing(Node* fileNode,int type)
{
	Node*tempNode=fileNode->child;
	if(fileNode->flag == 3&&type==1)//不显示c盘爸爸的属性 
		return;
	if(type==2)//对文件点击属性，找到选中的要显示的文件
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
	else if(type==1)//对空白点击属性
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
	rectangle(200,180,580,420);//画出背景
	puthz(200,8,"单击属性界面右上角以退出",16,16,RED);
	setcolor(DARKGRAY);
	rectangle(550,175,575,210);
	line(555,180,570,205);
	line(570,180,555,205);
    
    
	suffix=ZGetSuffix(tempNode);//得到文件名
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
			ImysteryL(235,200);//暂时未画出压缩文件的大图标
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
			ImysteryL(235,200);//其他文件大图标模式下一律用lmystery函数刻画。
		}
	}
	setcolor(DARKGRAY);//不能删
  
	
    tempDir=GetDir(fileNode);//得到并显示路径
    outtextxy(330,360,tempDir);

    if(strcmp(suffix,"DIR")==0)//如果是文件夹
    {
        Fileini(tempDir,tempNode);
        changeNode=tempNode->child;//进入文件夹
        while(changeNode)
        {
			fileNum++;
			changeNode=changeNode->brother;
        }
       // SFreeFolder(tempNode);
       
        sprintf(fileSum,"%d",fileNum);
        outtextxy(300,330,fileSum);
        puthz(230,295,"文件类型：",16,16,DARKGRAY);//1
		puthz(320,295,"文件夹",16,16,DARKGRAY);
		
    }
    else
    {
		if(fileNode->flag == 2)
		{
			puthz(230,295,"文件类型：磁盘",16,16,DARKGRAY);//1
        }
		else if(fileNode->flag != 2)
		{
			puthz(230,295,"文件类型：",16,16,DARKGRAY);//1
			puthz(360,295,"型文件",16,16,DARKGRAY);
			outtextxy(330,300,suffix);
        }
       
    }
	
	
	
    sprintf(dateAndTime,"%d/%d/%d %02d:%02d",tempNode->file.date/512+1980,\
	(tempNode->file.date%512)/32,tempNode->file.date%32,\
	tempNode->file.time/2048,(tempNode->file.time%2048)/32);
	sprintf(fileSize,"%d kB",(tempNode->file.size/1024)+1);
	/*以下进行内容的显示*/
	
	settextstyle(0,0,2);
	outtextxy(330,220,tempNode->file.name);
	settextstyle(0,0,1);
	
	
	
	if(*fileSize == '-')    //2
	{
		strcpy(fileSize,">32MB");//如果文件大小溢出 
	}
	if(fileNode->flag != 2)
	{
		if(strcmp(suffix,"DIR")!=0)//是否为文件夹
		{
			puthz(230,325,"文件大小：",16,16,DARKGRAY);
			outtextxy(330,330,fileSize);
		}
		else
		{
			puthz(230,325,"内部共有",16,16,DARKGRAY);
			puthz(315,325,"个文件（夹）。",16,16,DARKGRAY);
		}
	}
	puthz(230,355,"文件路径：",16,16,DARKGRAY);//3
    puthz(230,385,"修改时间：",16,16,DARKGRAY);//4
    outtextxy(330,390,dateAndTime);
	free(suffix);suffix=NULL;
	free(tempDir);tempDir=NULL;
 
   
}