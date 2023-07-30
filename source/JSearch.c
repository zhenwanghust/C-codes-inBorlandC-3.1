#include"common.h"
#include"JSearch.h"
#include"main.h"
int JSearch(char* name, Node* Root, Node* RootC,Search* parent)//RootC盘节点
{
	int flag=0;
	FILE* fp;
	int file = 0;
	if (strlen(name) == 0)
	{
		puthz(200, 8, "没有输入文件名", 16, 16, RED);//输入汉字
		delay(1000);
		setcolor(DARKGRAY);
		setfillstyle(1, WHITE);
		bar(190, 1, 190 + 9 * 16, 29);//190+（汉字个数+1）*16
		return flag;
	}
	if ((fp = fopen("..\\SEARCH.TXT", "wt+")) == NULL)  //覆盖式创建用于存储搜索到的节点的绝对路径的文档
	{
		printf("error open search.txt");
	}
	file=JSearchStack(Root, name, fp);
	fclose(fp);
	if (file == 0)
	{
		puthz(200, 8, "没有搜索到该文件", 16, 16, RED);//输入汉字
		delay(1000);
		setcolor(DARKGRAY);
		setfillstyle(1, WHITE);
		bar(190, 1, 190 + 9 * 16, 29);//190+（汉字个数+1）*16
		return flag;
	}
	flag = JSearchDraw(RootC,parent);
	if (flag==0)
	{
		puthz(200, 8, "没有搜索到该文件", 16, 16, RED);//输入汉字
		delay(5000);
		setcolor(DARKGRAY);
		setfillstyle(1, WHITE);
		bar(190, 1, 190 + 9 * 16, 29);//190+（汉字个数+1）*16
	}

	return flag;
}
void FreeStack(Stack* S)
{
	Stack* temp = S;
	int i, j, size = 0;
	if (temp->next = NULL)
	{
		size++;
		temp = temp->next;
	}
	temp = S;
	for (j = 0; j < size; j++)
	{
		temp = S;
		for (i = size - j; i > 0; i--)
		{
			temp = temp->next;
		}
		free(temp);
	}
	free(S);
}
Stack* CreatStack()
{
	Stack* S;
	S = (Stack*)malloc(sizeof(Stack));
	S->next = NULL;
	S->node = NULL;
	return S;
}
void PushStack(Node* item, Stack* S)
{
	Stack* temp;
	temp = (Stack*)malloc(sizeof(Stack));
	temp->node = item;
	temp->next = S->next;
	S->next = temp;
}
Node* PopStack(Stack* S)
{
	Stack* first;
	Node* temp;
	if (S->next == NULL)
	{
		printf("NULL");
		return NULL;
	}
	else
	{
		first = S->next;
		S->next = first->next;
		temp = first->node;
		free(first);
		return temp;
	}
}
int JSearchStack(Node* RootC,char* name,FILE* fb)
{
	Node* Root = RootC->child;//
	char* dir;
	int i = 0;
	int file = 0;
	char* test;
	Stack* S = CreatStack();
	while (Root || S->next != NULL)
	{
		while (Root)
		{
			if ((Root->file.attrib & 0x10) != 0||Root->flag==2)
			{
				if (Root->child == NULL)
				{
					Root->freeflag = 1;
					dir = GetDir(Root);
					Fileini(dir, Root);
					free(dir);
					dir = NULL;
				}
			}
			PushStack(Root, S);
			Root = Root->child;
		}
		if (S->next != NULL)
		{
			Root = PopStack(S);
			if (strcmp(name, Root->file.name) == 0)
			{
				/*while (temp->next)
				{
					temp = temp->next;
				}
				news = JCreateSearch();
				temp->next = news;
				news->node = Root;
				*/
				file++;
				dir = GetDir(Root);
				fprintf(fb, "%s\n", dir);
				free(dir);
				dir = NULL;
			}
			if ((Root->file.attrib & 0x10) != 0 && Root->freeflag == 1 && Root->copyflag == 0&&Root->flag!=2)
			{
				Root->freeflag = 0;
				JFreeFile(Root);
			}
			Root = Root->brother;
			//i++;
			/*itoa(i, test, 10);
			outtextxy(1, 440, test);
			delay(1000);
			setfillstyle(1, WHITE);
			bar(1, 420, 50, 459);
			*/
		}
	}
	FreeStack(S);
	return file;
}

void JSearchCir(char* name, Node* Root, FILE* fb)
{
	char* dir;
	/*Search* temp = parent;
	Search* news;
	*/
	if ((Root->file.attrib & 0x10) != 0)
	{
		if (Root->child == NULL)
		{
			Root->freeflag = 1;
			dir = GetDir(Root);
			Fileini(dir, Root);
			free(dir);
		}
	}
	if (Root->child != NULL)
	{
		JSearchCir(name, Root->child, fb);
	}

	if (strcmp(name, Root->file.name) == 0)
	{
		/*while (temp->next)
		{
			temp = temp->next;
		}
		news = JCreateSearch();
		temp->next = news;
		news->node = Root;
		*/
		dir = GetDir(Root);
		fprintf(fb, "%s\n", dir);
		free(dir);
		dir = NULL;
	}
	if ((Root->file.attrib & 0x10) != 0&&Root->freeflag)
	{
		Root->freeflag = 0;
		JFreeFile(Root);
	}
	if (Root->brother != NULL)
	{
		JSearchCir(name, Root->brother, fb);
	}
}
Search* JCreateSearch()
{
	Search* temp;
	if ((temp = (Search*)malloc(sizeof(Search))) == NULL)//给指针分配内存使之成为结构变量
	{
		printf("no enough memory");
		return NULL;
	}
	temp->next = NULL;
	temp->node = NULL;
}
void JFreeSearch(Search* parent)
{
	int size=0;
	int i,j;
	Search* temp=parent;
	while (temp->next)
	{
		size++;
		temp = temp->next;
	}
	for ( i = 0; i < size; i++)
	{
		temp = parent;
		for ( j = 0; j < size-i; j++)
		{
			temp = temp->next;
			free(temp);
		}
	}
}
Node* JSearchDir(char* dir, Node* RootC)
{
	Node* temp=RootC;
	int i = 0, j = 0;
	char Dir[100];
	char tempname[30];
	char tempdir[100];
	strcpy(Dir, dir);
	while (i< strlen(dir))
	{
		while (i <= strlen(dir))
		{
			if (*(Dir + i) == '\\' && *(Dir + i + 1) != '\\')  //检测双斜线
			{
				JGetName(Dir + i + 1, tempname);
				strcpy(Dir + i, "\0");  //得到每级文件绝对路径
				strcpy(tempdir, Dir);
				if (temp->child == NULL)
					Fileini(tempdir, temp);  //扫描文件
				temp = JGetNode(tempname, temp->child);
				if (temp == NULL)
				{
					return NULL;
				}
			}
			strcpy(Dir, dir);
			i++;
		}
	}
	
	return temp;
}
Node* JGetNode(char* name, Node* child)
{
	Node* firstNode = child;
	int flag = 0;
	while (firstNode != NULL)
	{
		if (strcmp(name, firstNode->file.name) == 0)
		{
			flag = 1;
			break;
		}
		else 
		{
			firstNode = firstNode->brother;
		}
	}
	if (flag == 0)
	{
		firstNode = NULL;
	}
	return firstNode;
}
void JGetName(char* dir, char* Name)
{
	int i = 0;
	while (i < strlen(dir))
	{
		if (*(dir + i) == '\\' && *(dir + i + 1) != '\\')
		{
			strcpy(dir + i, "\0");
			strcpy(Name, dir);
			strcat(Name, "\0");
		}
		i++;
	}
	if (i == strlen(dir))//?get最后的路径
	{
		strcpy(Name, dir);
	}
}

int JSearchDraw(Node* RootC,Search* parent)//
{
	Search* temp = parent;
	Search* news;
	char* test;
	Node* tempNode;  //搜索到的节点
	FILE* fp;
	char tempDir[100];  //绝对路径
	char* suffix;  //扩展名
	int filenum = 0;
	if ((fp = fopen("..\\SEARCH.TXT", "rt")) == NULL)
	{
		printf("error on open search.txt-SShowSearchFile");
	}
	setfillstyle(1, WHITE);
	bar(RIGHTSTARTX - 5, RIGHTSTARTY + 3, 639, 457);
	while (!feof(fp))
	{
		fscanf(fp, "%s\n", tempDir);  //得到绝对路径
		//printf("tempDir=%s",tempDir);
		if (strlen(tempDir)==0)
		{
			puthz(200, 8, "有", 16, 16, RED);//输入汉字
			delay(5000);
			setcolor(DARKGRAY);
			setfillstyle(1, WHITE);
			bar(190, 1, 190 + 8 * 16, 29);//190+（汉字个数+1）*16
			break;
		}
		tempNode = JSearchDir(tempDir, RootC);  //进入该节点！！！！！！！！！！
		while (temp->next)
		{
			temp = temp->next;
		}
		news = JCreateSearch();
		temp->next = news;
		news->node = tempNode;
		if (tempNode == NULL)
		{
			puthz(200, 8, "没有", 16, 16, RED);//输入汉字
			delay(5000);
			setcolor(DARKGRAY);
			setfillstyle(1, WHITE);
			bar(190, 1, 190 + 8 * 16, 29);//190+（汉字个数+1）*16
			break;
		}
		suffix = ZGetSuffix(tempNode);  //得到文件扩展名
		SearchDrawFileUnit(suffix, tempNode, RIGHTSTARTX, RIGHTSTARTY + 5+filenum * YGAP, 1);  //画出文件图标及信息
		
		
			
		showlujing(tempDir, RIGHTSTARTX, RIGHTSTARTY + 5+filenum * YGAP);
		//Jfreetree(RootC->parent);
		free(suffix);
		//SFreeFOlderInSearch(tempNode);
		filenum++;
		if (filenum>12)
		{
			fclose(fp);
			return filenum;
		}
	}
	fclose(fp);
	Jfreetree(RootC->parent);
	//*(searchMode) = 1;  //搜索模式激活
	return filenum;
}
void showlujing(char* tempDir,int x,int y)
{
	setcolor(DARKGRAY);
	puthz(x+DATEX-10,y+DATEY-8,"路径：",16,16,DARKGRAY);
	outtextxy(x+DATEX+35,y+DATEY,tempDir);
}
void JOpenSearch(Search* parent,Node**now, int filenumber, int Filepage)
{
	int i;
	int size = 0;
	char* c;
	Search* temp=parent;
	while (temp->next!=NULL)
	{
		size++;
		temp = temp->next;
	}
	if (size < filenumber)
	{
		return ;
	}
	else
	{
		temp = parent;
		for (i = 0; i < filenumber ; i++)
		{
			temp = temp->next;
		}
		if (temp->node->file.attrib == _A_SUBDIR || temp->node->flag == 2)
		{
			if (*(temp->node->file.name) != 'C' && *(temp->node->file.name) != ':' && temp->node->flag != 3 && temp->node->child == NULL)
			{
				c = GetDir(temp->node);
				Fileini(c, temp->node);
				free(c);
			}
			*now=temp->node;
			ZFileUnit(temp->node, RIGHTSTARTX, RIGHTSTARTY, Filepage, 1);
			return;
		}
	}
}
void SearchDrawFileUnit(char* suffix,Node* tempNode,int x,int y,short int displayMode)
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
			
		}
		else
		{
			setcolor(DARKGRAY);
			outtextxy(x+NAMEX,y+NAMEY,tempNode->file.name);
			
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