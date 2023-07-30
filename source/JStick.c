#include"common.h"
#include"JStick.h"
#include"main.h"
void JStick(Copy* head, Node* parent)//总粘贴循环
{
	char* dir;
	Copy* temp = head->next;
	Node* tempnode = parent->child;
	/*
	while (tempnode)//把当前所有文件改为未选中
	{
		tempnode->responseFlag = 0;
		tempnode = tempnode->brother;
	}
	*/
	JSort(parent, 2);
	while (temp!=NULL)
	{
		JStickFile(temp, parent);
		temp = temp->next;
	}
	if (head->next->flag==1)
	{
		/*tempnode =
		JDeleCopy()
		*/
		FreeCopy(&head);
	}

	JFreeFile(parent);
	dir = GetDir(parent);
	Fileini(dir, parent);
	free(dir);
}
void JStickFile(Copy* temp, Node* parent)//单个文件粘贴
{
	Node* pre;
	char* dir;
	int flag;
	flag=JPaste(temp, parent);
	if(flag)
	{
		if (temp->flag)
		{
			JDelete(temp->node);
			pre = JDeleteLink(temp->node);
		}
	}
	JSort(parent, 2);

}
int JPaste(Copy* temp, Node* parent)//粘贴粘贴链表也要做排序
{
	int num;
	Node* addnode=parent->child;
	Node* newnode;
	char*p= GetDir(parent);//文件夹路径
	char* c = GetDir(temp->node);//源文件路径
	if (temp == NULL)
	{
		free(p);
		free(c);
		return 0;
	}
	while (addnode->brother!=NULL&&addnode!=NULL)
	{
		addnode = addnode->brother;
	}
	newnode = CreateNode();
	newnode->file = temp->node->file;
	if (addnode == NULL)
	{
		newnode->flag = 1;
		parent->child = newnode;
		newnode->parent = parent;
		newnode->brother = NULL;
	}
	else
	{
		newnode->flag = 0;
		addnode->brother = newnode;
		newnode->parent = addnode;
		newnode->brother = NULL;
	}
	//newnode->responseFlag = 1;
	if (JCheckchild(newnode, temp->node))
	{
		free(p);
		free(c);
		free(newnode);
		if (addnode == NULL)
		{
			parent->child = NULL;
		}
		else
		{
			addnode->brother = NULL;
		}
		bar(190, 1, 190 + 16 * 22, 29);//190+（汉字个数+1）*16
		puthz(200, 8, "目标文件夹是源文件夹的子文件夹，无法操作！", 16, 16, RED);//输入汉字
		setcolor(DARKGRAY);
		delay(2000);
		setfillstyle(1, WHITE);
		bar(190, 1, 190 + 16 * 22, 29);//190+（汉字个数+1）*16
		return 0;
	}
	
	/*puthz(200, 8, "目标文件夹是源文件夹的子文件夹，无法操作！", 16, 16, RED);//输入汉字
	setcolor(DARKGRAY);
	delay(2000);
	setfillstyle(1, WHITE);
	bar(190, 1, 190 + 16 * 22, 29);//190+（汉字个数+1）*16
	*/
	num = JCheckName(newnode, parent);
	if (num!=0)
	{
		JChangeName(num, newnode);
	}
	if ((newnode->file.attrib & _A_SUBDIR) == 0)
		JWinStick(c, p, newnode->file.name);
	else if ((newnode->file.attrib & _A_SUBDIR) != 0)
	{
		JFolderStack(newnode, temp->node);
		//JFreeFile(newfolder);
		//JFreeFile(oldfolder);
	}
	free(p);
	free(c);
	//free(newnode);
	return 1;
}
int JCheckName(Node* copynode, Node* parent)
{
	char* test;
	int sizecopy, sizetemp;
	int num1=0,num2=0;
	int time = 0, n = 1;
	char* copySuffix, * tempSuffix;
	char copypure[9], filepure[9];
	Node* temp = parent->child;
	sizecopy=JGetPureName(copynode, copypure,9);
	copySuffix=ZGetSuffix(copynode);
	while (temp->brother != NULL)
	{
		sizetemp=JGetPureName(temp, filepure,sizecopy);
		/*if (sizetemp<sizecopy)
		{
			test = copynode;
			while (*test!='\0')
			{
				test++;
			}
			test--;
			*test = '\0';
		}
		*/
		if (strcmp(copypure, filepure)==0)
		{
			tempSuffix = ZGetSuffix(temp);
			if (strcmp(copySuffix, tempSuffix)==0)
			{
				time++;
				if (n==1)
				{

					num1 = JGetSameNumber(temp->file.name);
					/*itoa(num1, test, 10);
					outtextxy(1, 250, test);
					delay(1000);
					setfillstyle(1, WHITE);
					bar(1, 240, 50, 290);
					*/
				}
				else if (n==-1)
				{
					num2 = JGetSameNumber(temp->file.name);
					/*itoa(num2, test, 10);
					outtextxy(1, 440, test);
					delay(1000);
					setfillstyle(1, WHITE);
					bar(1, 420, 50, 459);
					*/
				}
				if ((num1-num2>=2)&&n==1)
				{
					free(copySuffix);
					free(tempSuffix);
					return (num2 + 1);
				}
				if ((num2-num1>=2)&&n==-1)
				{
					free(copySuffix);
					free(tempSuffix);
					return (num1 + 1);
				}
				n *= -1;
			}
			free(tempSuffix);
		}
		temp = temp->brother;
	}
	free(copySuffix);
	if (time==0)
	{
		return 0;
	}
	if (num1>num2)
	{
		return (num1+1);
	}
	else
	{
		return (num2 + 1);
	}
}
void JWinStick(char*old,char*parent,char*name)
{
	FILE* fileRead, * fileWrite;
	char *olddir, newdir[60],ch;
	olddir = old;
	strcpy(newdir, parent);
	strcat(newdir, "\\");
	strcat(newdir, name);//得到新的文件的绝对路径
	
	if ((fileRead = fopen(olddir, "rb+")) == NULL)
		printf("file %s open error", olddir);//打开要被复制的文件
	if ((fileWrite = fopen(newdir, "wb+")) == NULL)
		printf("file %s open error", newdir);//创建复制后的文件
	ch = fgetc(fileRead);
	while (!feof(fileRead))
	{
		fputc(ch, fileWrite);
		ch = fgetc(fileRead);
	}
	fclose(fileRead);
	fclose(fileWrite);
}
void JWinStickFolder(char* oldDir, char* newDir)
{
	static n = 0;
	char* test;
	FILE* fileRead, * fileWrite;
	char ch;
	if ((fileRead = fopen(oldDir, "rb+")) == NULL)
		printf("file %s open error", oldDir);//打开要被复制的文件
	if ((fileWrite = fopen(newDir, "wb+")) == NULL)
		printf("file %s open error", newDir);//创建复制后的文件
	ch = fgetc(fileRead);
	while (!feof(fileRead))
	{
		fputc(ch, fileWrite);
		ch = fgetc(fileRead);
	}
	fclose(fileRead);
	fclose(fileWrite);

}
int JGetPureName(Node* temp, char* c,int copy)
{
	char name[13];
	char* n;
	int time=0;
	int size;
	strcpy(name, temp->file.name);
	n = name;
	while (*n != '.' && *n != '~'&& *n != '\0'&&time<copy)//只要没碰上特殊字符
	{
		time++;
		n++;//指针往后指
	}
	*n = '\0';//把特殊字符改成终止符号,得到未加处理的纯净名
	size= strlen(name);
	if (size == 7)
	{
		n--;//如果文件名等于7，那就将前6位作为纯净文件名
		size = 6;
	}
	if (size == 8) //如果文件名等于8，那就将前6位作为纯净文件名
	{
		n--;
		n--;
		size = 6;
	}
	*n = '\0';
	strcpy(c, name);
	return size;
}
int JGetSameNumber(char* filename)//获取文件数字名字
{
	char* test;
	int number;
	char* temp;
	char pureName[13];
	strcpy(pureName, filename);
	temp = pureName;
	/*outtextxy(1, 300, "w");
	delay(1000);
	setfillstyle(1, WHITE);
	bar(1, 300, 50, 459);
	*/
	while (*temp != '\0'&& *temp != '.')
	{
		temp++;
	}
	*temp = '\0';
	temp = pureName;
	while (*temp != '\0')
	{
		if (*temp=='~')
		{
			//while (*temp != '\0')
			{
				
			}
			//temp--;
			temp++;
			//if (*temp == '\0')
			//{
				//return 0;
			//}
			//number = *temp - 48;
			number = atoi(temp);
			return number;
		}
		temp++;
	}

	return 0;
}
void JChangeName(int num, Node* newnode)
{
	char pureName[13];
	char numchar[4];
	char* name;
	char* suffix;
	int size, i;
	int nii;
	nii=JGetPureName(newnode, pureName,13);
	size = strlen(newnode);
	name = pureName;
	if (num==0)
	{
		return;
	}
		if (num>=10)
		{
			for (i = 0; i < 5; i++)
			{
				name++;
			}
			*name = '\0';
			itoa(num, numchar, 10);
			strcat(pureName, "~");
			strcat(pureName, numchar);
			suffix = ZGetSuffix(newnode);//得到后缀名
			if (strcmp(suffix, "DIR") != 0)
			{
				strcat(pureName, ".");
				strcat(pureName, suffix);//加上后缀名，完成更改
			}
			free(suffix);
		}
		else
		{
				for (i = 0; i < 6; i++)
				{
					name++;
				}
				*name = '\0';
				itoa(num, numchar, 10);
				strcat(pureName, "~");
				strcat(pureName, numchar);
				suffix = ZGetSuffix(newnode);//得到后缀名
				if (strcmp(suffix, "DIR") != 0)
				{
					strcat(pureName, ".");
					strcat(pureName, suffix);//加上后缀名，完成更改
				}
				free(suffix);
		}
		strcpy(newnode->file.name, pureName);//更改结点中的文件名
}
void JFolderStack(Node* now, Node* before)
{
	int i;
	char* test;
	char* newFolderDir;
	Node* newfolder = now;
	Node* oldfolder = before;
	Stack* S = CreatStack();
	Stack* T = CreatStack();
	JFolderStick(newfolder, oldfolder);
	newFolderDir = GetDir(newfolder);
	Fileini(newFolderDir, newfolder);
	free(newFolderDir);
	newfolder = now->child;
	oldfolder = before->child;
	
	while (oldfolder || S->next != NULL)
	{
		while (oldfolder)
		{	
			if ((oldfolder->file.attrib & _A_SUBDIR) != 0 && oldfolder != NULL)//复制下一层
			{
				JFolderStick(newfolder, oldfolder);
				newFolderDir = GetDir(newfolder);
				Fileini(newFolderDir, newfolder);
				free(newFolderDir);
			}
			PushStack(oldfolder, S);
			PushStack(newfolder, T);
			oldfolder = oldfolder->child;
			newfolder = newfolder->child;
		}
		if (S->next != NULL)
		{
			oldfolder = PopStack(S);
			newfolder = PopStack(T);
			JFreeFile(oldfolder);
			JFreeFile(newfolder);
			oldfolder = oldfolder->brother;
			newfolder = newfolder->brother;
			i++;
			/*puthz(200, 8, "无法操作！", 16, 16, RED);//输入汉字
			setcolor(DARKGRAY);
			delay(2000);
			setfillstyle(1, WHITE);
			bar(190, 1, 190 + 16 * 22, 29);//190+（汉字个数+1）*16
			*/
			setfillstyle(1, WHITE);
			bar(249, 1, 280, 29);
			itoa(i, test, 10);
			outtextxy(250, 10, test);
			delay(10);
			
			
		}
	}
}
void JFolderStickCir(Node* now, Node* before,Node* parent)//粘贴大递归新建节点，被复制的节点
{
	Node* newfolder = now;
	Node* oldfolder = before;
	char* newFolderDir ;//新文件夹的目录
	//char* oldFolderDir = GetDir(oldfolder);
	//int file = JCheckFolder(before);
	/*if (strcmp(oldfolder->file.name, parent->file.name) == 0)
	{
		puthz(200, 8, "子文件夹", 16, 16, RED);//输入汉字
		setcolor(DARKGRAY);
		delay(800);
		setfillstyle(1, WHITE);
		bar(190, 1, 190 + 5 * 16, 29);//190+（汉字个数+1）*16
		return;
	}
	*/
	
	if ((oldfolder->file.attrib & _A_SUBDIR) != 0&& oldfolder!=NULL)//复制下一层
	{
		newFolderDir = GetDir(newfolder);
		JFolderStick(newfolder, oldfolder);
		Fileini(newFolderDir, newfolder);
		free(newFolderDir);
	}

	if (before->child!=NULL)
	{
		JFolderStickCir1(now->child, before->child,parent);
	}
	/*if (strcmp(oldfolder->file.name, parent->file.name) == 0)
		;//return;
	if (now->brother!= NULL)
	{
		JFolderStickCir(now->brother, before->brother, parent);
	}
	*/
	//JFreeFile(newfolder);
	//JFreeFile(oldfolder);
	return;
}

void JFolderStickCir1(Node* now, Node* before, Node* parent)//辅助粘贴大递归新建节点，被复制的节点
{
	Node* newfolder = now;
	Node* oldfolder = before;
	char* newFolderDir;//新文件夹的目录
	//char* oldFolderDir = GetDir(oldfolder);
	//int file = JCheckFolder(before);
	/*if (strcmp(oldfolder->file.name, parent->file.name) == 0)
	{
		puthz(200, 8, "子文件夹", 16, 16, RED);//输入汉字
		setcolor(DARKGRAY);
		delay(800);
		setfillstyle(1, WHITE);
		bar(190, 1, 190 + 5 * 16, 29);//190+（汉字个数+1）*16
		return;
	}
	*/
	if ((before->file.attrib & _A_SUBDIR) != 0 && before != NULL)//复制下一层
	{
		newFolderDir = GetDir(newfolder);
		/*puthz(200, 8, "你好", 16, 16, RED);//输入汉字
		setcolor(DARKGRAY);
		delay(800);
		setfillstyle(1, WHITE);
		bar(190, 1, 190 + 3 * 16, 29);//190+（汉字个数+1）*16
		*/
		JFolderStick(newfolder, oldfolder);
		Fileini(newFolderDir, newfolder);
		free(newFolderDir);
	}

	if (before->child != NULL )
	{
		JFolderStickCir1(now->child, before->child, parent);
	}
	/*if (strcmp(oldfolder->file.name, parent->file.name) == 0)
		;//return;
		*/
	if (before->brother!= NULL)
	{
		JFolderStickCir1(now->brother, before->brother, parent);
	}
	
	//JFreeFile(newfolder);
	//JFreeFile(oldfolder);

}
void JFolderStick(Node* New, Node* Old)//粘贴新文件夹和被复制的文件夹，家长
{
	Node* newFolder = NULL;
	Node* oldFolder = NULL;//先用两个指针分别指向两个文件夹下的第一个文件
	char* newFolderDir = NULL;
	char* oldFolderDir = NULL;

	newFolderDir = GetDir(New);
	oldFolderDir = GetDir(Old);
	mkdir(newFolderDir);//win下建立新的文件夹
	if (Old->child==NULL)
	{
		Fileini(oldFolderDir, Old);//先打开旧的文件夹
	}
	newFolder = New->child;
	oldFolder = Old->child;
	free(newFolderDir);
	free(oldFolderDir);
	while (oldFolder != NULL)//先复制一层
	{
		if ((oldFolder->file.attrib & _A_SUBDIR) != 0)//如果是文件夹
		{
			oldFolderDir = GetDir(oldFolder);//得到绝对路径
			newFolderDir = GetDir(New);//得到新的文件夹的绝对路径
			strcat(newFolderDir, "\\");
			strcat(newFolderDir, oldFolder->file.name);
			mkdir(newFolderDir);//建立新的文件夹
			free(newFolderDir);
			free(oldFolderDir);
		}
		else if ((oldFolder->file.attrib & _A_SUBDIR) == 0)//如果不是文件夹
		{
			oldFolderDir = GetDir(oldFolder);
			newFolderDir = GetDir(New);
			strcat(newFolderDir, "\\");
			strcat(newFolderDir, oldFolder->file.name);
			JWinStickFolder(oldFolderDir, newFolderDir);
			free(newFolderDir);
			free(oldFolderDir);
		}
		oldFolder = oldFolder->brother;
	}
	//SFreeFolder(folderOldNode);
}
int JCheckFolder(Node* parent)
{
		Node* temp = parent->child;
		while (temp)
		{
			if (temp->file.attrib&_A_SUBDIR)
			{
				return 1;
			}
			temp = temp->brother;
		}
		return 0;
}
int JCheckchild(Node* new, Node* old)
{
	char* newdir, * olddir;
	int flag;
	Stack* S = CreatStack();
	newdir = GetDir(new);
	old = old->child;
	while (old || S->next != NULL)
	{
		while (old)
		{
			if ((old->file.attrib & _A_SUBDIR) != 0 && old != NULL)//复制下一层
			{
				if (old->child == NULL)
				{
					olddir = GetDir(old);
					Fileini(olddir, old);
					free(olddir);
				}
			}
			olddir = GetDir(old);
			if (strcmp(newdir, olddir) == 0)
			{
				free(olddir);
				free(newdir);
				free(S);
				return 1;
			}
			free(olddir);
			PushStack(old, S);
			old = old->child;
		}
		if (S->next != NULL)
		{
			old = PopStack(S);
			JFreeFile(old);
			old = old->brother;
		}
	}
	free(S);

	return 0;
}
int JCheckchildCir(Node* new, Node* old,int flag)
{
	char* newdir, * olddir;
	Node* temp = old->child;
	if (flag)
	{
		return 1;
	}

	if ((old->file.attrib & _A_SUBDIR) != 0)//是文件夹就打开
	{
		if (old->child == NULL)
		{
			olddir = GetDir(old);
			Fileini(olddir, old);
			free(olddir);
		}
		olddir = GetDir(old);
		newdir = GetDir(new);
		if (strcmp(new,old)==0)
		{
			free(olddir);
			free(newdir);
			return 1;
		}
		free(olddir);
		free(newdir);
	}
	if (old->child!=NULL)
	{
		flag=JCheckchildCir(new, old->child,flag);
	}
	if (old->brother!=NULL)
	{
		flag = JCheckchildCir(new, old->brother, flag);
	}
}