 #include "common.h"
 #include "ZRight.h"
 #include "main.h"
 
/********************************************************************************
 * 功能：显示当前文件夹下所有的文件单元
 * 参数：文件夹的结构指针temoNode；显示的起始点（最左上角）（x，y）；当前页数filePage
 * 返回值：无
 * *******************************************************************************/
void clearrightscreen()//用白色覆盖右侧显示屏
{
	setfillstyle(1,WHITE);
	bar(RIGHTSTARTX-5,RIGHTSTARTY+3,639,457);
}

int ZFileUnit(Node*tempNodeSe,int x,int y,int filePage,short int displayMode)
{
    Node* temp;
    int size;
    char* c,*k;
	char* suffix=NULL;//用于储存文件后缀，内存稍后分配
	char* countchar=NULL;
	char* pagemaxchar=NULL;
	short int bigIconXCount = 0;//用于计算大图标模式下，当前的一行已经显示的文件数量
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
	tempNode = tempNode->child;//tempnode为当前文件夹的结构指针的child,已经进入文件夹！！！！！
	if(displayMode == 2) 
		bx+=20;//大图标模式时起始画图位置偏移
		by+=7;
	if(displayMode == 1) 
		by+=3;//小图标模式时起始画图位置偏移
	clrmous(MouseX,MouseY);
	clearrightscreen();
	showcurrentpage(filePage);
	pagemax=countpages(tempNode);//得到该节点下需要的最大页数，并作为返回值
	if(pagemax==0)
		pagemax=1;//让显示符合逻辑
	fileallnum=countfiles(tempNodeSe);//用来显示出来文件总个数
	setfillstyle(1,WHITE);
	bar(39,461,60,479);
	itoa(fileallnum,fileallnumchar,10);
	outtextxy(46,467,fileallnumchar);//用来显示共多少文件
	itoa(pagemax,pagemaxchar,10);
	bar(138,461,152,479);
	outtextxy(140,467,pagemaxchar);//用来显示最大页数
	selected=countselected(tempNodeSe);
	itoa(selected,selectedchar,10);
	setfillstyle(1,WHITE);
	bar(283,461,299,479);
	outtextxy(285,467,selectedchar);
	leftarrow(30, 448, 1);
	rightarrow(120, 448, 1);
	if (temp->flag != 2 && temp->flag != 3)//显示路径
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
		for(i = 0;i<(BIGPAGEMAX*(filePage-1));i++)//指针移到第二页开头应显示的文件的结点处,第二页执行一次，第三页执行两次
		{
			tempNode = tempNode->brother;
			if(tempNode == NULL)
			{
				filePage = 0;//如果第二页开头应显示的文件的结点为空，那么直接退出循环。
				break;
			}
		}
	else if (displayMode==1)
	{
		for(i = 0;i<(SHOWMAX*(filePage-1));i++)//指针移到第二页开头应显示的文件的结点处,第二页执行一次，第三页执行两次
		{
			tempNode = tempNode->brother;
			if(tempNode == NULL)
			{
				filePage = 0;//如果第二页开头应显示的文件的结点为空，那么直接退出循环。
				break;
			}
		}
	}
	
	
	for(i = 0;i<SHOWMAX;i++)//i小于每页显示的最大文件数量
	{
		suffix = ZGetSuffix(tempNode);//调用getsuffix函数得到当前文件夹下文件的后缀名称。
		if(tempNode == NULL) //1.文件夹为空的情况,直接返回。
		{
			puthz(RIGHTSTARTX+150,RIGHTSTARTY+40,"此文件夹为空。",32,32,LIGHTGRAY);
			free(suffix);
			return;
		}
		
		if(tempNode->brother == NULL)//2.如果该文件夹后没有文件，画完就结束函数，分为选中和未选中两种画图。
		{
			if(tempNode->responseFlag == 0)//当未选中文件
			{
				
				if(displayMode == 1) //小图标模式下，调用drawfile函数画出图标，名称，
				{
					ZDrawFileUnit((char*)suffix,tempNode,bx,by,displayMode);
					by+=YGAP;//将y画图坐标下移
					
				}
				if(displayMode == 2)//大图标模式下，调用drawfile函数画出图标，名称，
				{
					ZDrawFileUnit((char*)suffix,tempNode,bx,by,displayMode);
					bx+=BIGICONX;
					
					bigIconXCount++;
				}
			}
			
			else if(tempNode->responseFlag == 1)//当选中了文件
			{
				if(displayMode == 1)
				{
					setfillstyle(1,CLICKCOLOR);
					bar(bx-2,by-2,bx+CLICKCOLORLENGTH,by+YGAP-3);//铺底色
					ZDrawFileUnit((char*)suffix,tempNode,bx,by,displayMode);
					by+=YGAP;
					
				}
				if(displayMode == 2)//
				{
					setfillstyle(1,CLICKCOLOR);
					bar(bx-20,by-2,bx+BIGSELECTEDX,by+BIGSELECTEDY-3);//铺底色
					ZDrawFileUnit((char*)suffix,tempNode,bx,by,displayMode);
					bx+=BIGICONX;
					bigIconXCount++;
				}
				
			}
			filePage = 0;
			free(suffix);//释放后缀名字符串内存
			break;
		}
		//3.文件夹里面有多个文件
		if(tempNode->responseFlag == 0)//当未选中文件
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
		else if(tempNode->responseFlag == 1)//当选中了文件
		{
			
			if(displayMode == 1)
			{
				setfillstyle(1,CLICKCOLOR);//clickcolor为11青色
				bar(bx-2,by-2,bx+CLICKCOLORLENGTH,by+YGAP-3);//铺底色
				ZDrawFileUnit((char*)suffix,tempNode,bx,by,displayMode);
				by+=YGAP;
			}
			if(displayMode == 2)
			{
				setfillstyle(1,CLICKCOLOR);
				bar(bx-15,by-2,bx+BIGSELECTEDX,by+BIGSELECTEDY-3);//铺底色
				ZDrawFileUnit((char*)suffix,tempNode,bx,by,displayMode);
				bx+=BIGICONX;
				bigIconXCount++;
			}
		}
		//以下为文件夹里有多个文件时的细节处理。
		if(tempNode->brother != NULL) //如果下一个文件存在，移动到下一个文件
			tempNode = tempNode->brother;
		if(bigIconXCount == BIGLINEMAX && displayMode == 2) //大图标模式下，如果该行已经画出4个文件，转到下一行
		{
			bigIconXCount = 0;
			by+=BIGICONY;//纵向距离向下120
			bx = x+20;//横向距离恢复
		}
		if(i == FILECONMAX && displayMode == 1)//如果画满一页就结束画图
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
 * 功能：得到文件最大页数
 * 参数：当前文件夹的结构指针tempNode
 * 返回值：文件个数
 * ************************************/
int countpages(Node*tempNode)//得到文件最大页数
{
	int times = 0;
	//tempNode = tempNode->child;//进入文件夹
	while(tempNode != NULL)
	{
		times += 1;
		tempNode = tempNode->brother;
	}
	if(times % FILECONMAX == 0)
	{
		return times / FILECONMAX;//当前文件数能被每页最多文件数整除
	}
	return (times / FILECONMAX)+1;//当前文件数不能被每页最多文件数整除
}
/***********************************
 * 功能：得到当前文件夹下文件的个数
 * 参数：当前文件夹的结构指针tempNode
 * 返回值：文件个数
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
 * 功能：得到当前文件的后缀名
 * 参数：当前文件夹的结构指针tempNode
 * 返回值：文件后缀名
 * *********************************/
char* ZGetSuffix(Node* tempNode)
{
	char* suffix = (char*)malloc(5);

	char* fileName = (char*)malloc(20);
	strcpy(fileName,tempNode->file.name);
	if(tempNode->file.attrib & _A_SUBDIR )//如果是文件夹
	{
		strcpy(suffix,"DIR");//如果是文件夹，后缀名直接命名为DIR
		free(fileName);		//释放字符串的内存  
	}
	else if(strstr(tempNode->file.name,".")==NULL)//如果不是文件夹又不带后缀名
    {
        strcpy(suffix,"N.A");//如果不是文件夹又不带后缀名，后缀名直接命名为UNKNOWN
		free(fileName);    //释放字符串的内存    
    }
	else
	{
		while(*fileName != '.'&&*fileName !='\0')//如果不是文件夹且有后缀名,也是大多数的情况
		{
			strcpy(fileName,fileName+1);
		}
		strcpy(suffix,fileName+1);	
		free(fileName);//释放字符串的内存  
	}
	return suffix;//并返回字符串,设计为单一返回值，有利于函数的调试与运行。
}

/*************************************************************************************
 * 功能：显示单个文件单元
 * 参数：文件的后缀名suffix；当前文件的结构指针tempNode；显示的起始点（最左上角）（x，y）
 * 返回值：无
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
	tempNode->file.time/2048,(tempNode->file.time%2048)/32);//把文件的最后修改时间写入字符串
	//
	sprintf(fileSize,"%d kB",(tempNode->file.size/1024)+1);//把文件的大小写入字符串  
	//byte/1024=kb
	
	if(*fileSize == '-')//如果文件大小溢出，显示为>32MB
	{
		strcpy(fileSize,">32MB");
	}
	
	
	setcolor(DARKGRAY);
	
	if(tempNode->flag == 2)//如果是盘符根结点
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
		else if(displayMode == 2)//大图标模式
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
	//如果不是盘根符节点，分为大图标模式和详细信息模式两种方式显示。
	if(displayMode == 1)//详细信息模式
	{
		setcolor(DARKGRAY);
		if(strcmp(suffix,"DIR")==0)
		{
			setcolor(DARKGRAY);
			outtextxy(x+NAMEX,y+NAMEY,tempNode->file.name);
			outtextxy(x+DATEX,y+DATEY+1,dateAndTime);
			puthz(x+TYPEORSIZEX,y+TYPEORSIZEY+6,"文件夹",16,16,DARKGRAY);
			//outtextxy(x+SIZENEW,y+TYPEORSIZEY+11,"N.A");
		}
		else
		{
			setcolor(DARKGRAY);
			outtextxy(x+NAMEX,y+NAMEY,tempNode->file.name);
			outtextxy(x+DATEX,y+DATEY+1,dateAndTime);
			outtextxy(x+TYPEORSIZEX,y+TYPEORSIZEY+11,suffix);
			puthz(x+TYPEORSIZEX+25,y+TYPEORSIZEY+6,"文件",16,16,DARKGRAY);
			outtextxy(x+SIZENEW,y+TYPEORSIZEY+11,fileSize);
		}
		//画出图标
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
			smystery(x,y);//暂时还没画出mp4的图标
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
			spic(x,y);//图片三种后缀暂时都用pic
		}
		else if(strcmp(suffix,"ZIP") == 0)
		{
			smystery(x,y);//暂时还没画出zip的图标
		}
		else if(strcmp(suffix,"DAT") == 0)
		{
			smystery(x,y);//暂时还没画出dat的图标
		}
		else if(strcmp(suffix,"TXT") == 0)
		{
			stxt(x,y);
		}
		else if(strcmp(suffix,"PDF") == 0)
		{
			smystery(x,y);//暂时还没画出pdf的图标
		}
		else if(strcmp(suffix,"XLS") == 0)
		{
			smystery(x,y);//暂时还没画出xls的图标
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
			smystery(x,y);//其他未知文件一律用smystery函数来刻画
		}
		y-=7;
	}
	else if(displayMode == 2)//大图标模式
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
			ImysteryL(x,y+7);//暂时未画出压缩文件的大图标
		}
		else if(strcmp(suffix,"DOC") == 0)
		{
			IdocL(x,y+7);
		}
		else if(strcmp(suffix,"BMP") == 0 || strcmp(suffix,"JPG") == 0 || strcmp(suffix,"PNG") == 0)
		{
			IpicL(x,y+7);//三种图片文件的大图标暂时都用pic表示
		}
		else if(strcmp(suffix,"MP4") == 0 || strcmp(suffix,"MP3") == 0)
		{
			ImysteryL(x,y+7);//暂时未画出音频视频文件的大图标
		}
		else
		{
			ImysteryL(x,y+7);//其他文件大图标模式下一律用lmystery函数刻画。
		}
	}
}
int areyousure()
{
	setfillstyle(1,WHITE);
	bar(300,240,500,380);
	setcolor(DARKGRAY);
	rectangle(300,240,500,380);
	puthz(302, 250, "确认要进行删除？", 16, 16, DARKGRAY);
	puthz(335,358, "取消", 16, 16, DARKGRAY);
	puthz(435,358, "确认", 16, 16, DARKGRAY);
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