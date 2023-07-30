#include"JTreeNod.h"
#include"main.h"
#include"common.h"
int JChecktreefolder(Node* parent)
{
	char* dir;
	int n = 0;
	int flag=0;
	Node* temp;
	if (parent->child == NULL)
	{
		dir = GetDir(parent);
		Fileini(dir, parent);
		free(dir);
		flag = 1;
	}
	temp = parent->child;
	while (temp)
	{
		if (temp->file.attrib & _A_SUBDIR)
		{
			n++;
			if (flag)
			{
				JFreeFile(parent);
			}
			return n;
		}
		temp = temp->brother;
	}
	if (flag)
	{
		JFreeFile(parent);
	}
	return 0;
}

int JTreeCheckOpen(Node* parent)//返回文件夹内部打开文件夹数量
{
    Node* node = NULL;
    int openfile = 0;  //文件夹数目
    char suffix[4] = { 0 };  //文件扩展名
    node = parent->child;  //进入文件夹内层
    while (node != NULL)
    {
        if (((node->file.attrib & _A_SUBDIR) != 0) && (node->treeflag == 1))
          {
          openfile++;
           }
        node = node->brother;  //指针指向文件夹内部第一层并列文件
    }
	return openfile;
}
int JGetTreePage(Node* RootC, Node* now,int leftpage)
{
	Node* Root = RootC->child;//c盘
	int size = 0;
	char* dir;
	char* dirtemp;
	char* test;
	Stack* S = CreatStack();
	dir = GetDir(now);
	
	while (Root || S->next != NULL)
	{
		while (Root)
		{
			dirtemp = GetDir(Root);
			if (Root->treeflag == 1)
			{
				size++;
				if (strcmp(dirtemp, dir)==0)
				{
					FreeStack(S);
					free(dirtemp);
					free(dir);
					setfillstyle(1, WHITE);
					bar(249, 1, 280, 29);
					itoa(((size - 1) / SHOWMAX + 1), test, 10);
					outtextxy(250, 10, test);
					delay(1000);
					return ((size-1)/ SHOWMAX+1);
				}
				PushStack(Root, S);
				Root = Root->child;
			}
			else if ((Root->file.attrib & 0x10) || Root->flag == 2)
			{
				size++;
				if (strcmp(dirtemp, dir) == 0)
				{
					FreeStack(S);
					free(dirtemp);
					free(dir);
					setfillstyle(1, WHITE);
					bar(249, 1, 280, 29);
					itoa(((size - 1) / SHOWMAX + 1), test, 10);
					outtextxy(250, 10, test);
					delay(1000);
					return ((size - 1) / SHOWMAX + 1);
				}
				Root = Root->brother;

			}
			else
			{
				Root = Root->brother;
			}
			free(dirtemp);
		}
if (S->next != NULL)
{
	Root = PopStack(S);
	Root = Root->brother;
}
	}
	FreeStack(S);
	free(dir);
	return leftpage;
}
int JGetTreeFolderNum(Node* Root, int line, Node** getFolder)//line——点击文件夹所在行数 >=1
{
	int folderOpennum = 0;  //已打开文件夹数目
	Node* tempNode = NULL;
	Node* changeNode = Root;
	changeNode = changeNode->child;
	while (changeNode)
	{
		if ((changeNode->treeflag == 1 && ((changeNode->file.attrib & 0x10)) || changeNode->flag == 2))
		{
			folderOpennum++;
			if (folderOpennum == line)
			{
				(*getFolder) = changeNode;
				break;
			}
			tempNode = changeNode;
			if (JChecktreefolder(changeNode))
			{
				folderOpennum += JGetTreeFolderNum(tempNode, line - folderOpennum, getFolder);
				if (folderOpennum == line && *getFolder && ((*getFolder)->file.attrib & 0x10))//如果*getFolder不为空且是文件夹
				{
					break;
				}
			}
		}
		else if (((changeNode->file.attrib & 0x10)) || changeNode->flag == 2)
			folderOpennum++;
		if (folderOpennum == line && (*getFolder) == NULL)
		{
			(*getFolder) = changeNode;
			break;
		}
		changeNode = changeNode->brother;

	}
	if (folderOpennum < line)
	{
		(*getFolder) = NULL;
	}
	tempNode = NULL;
	changeNode = NULL;
	return folderOpennum;
}
void JDFlag(Node* child)//递归使当前文件夹内所有文件夹关闭
{
	if (child->child)
	{
		JDFlag(child->child);
	}
	if (child->brother)
	{
		JDFlag(child->brother);
	}
	if ((child->file.attrib & 0x10) && child->treeflag == 1)
	{
		child->treeflag = 0;
	}
}
void JBuildTree(Node* temp)
{
	temp->treeflag = 1;
	while (temp->flag != 3)
	{
		while (temp->flag == 0)
		{
			temp = temp->parent;
		}
		temp = temp->parent;
		temp->treeflag = 1;
	}

}
void Jfreetree(Node* RootC)//关闭树
{
	if (RootC->child)
	{
		JfreetreeCir(RootC->child);
	}
	
}
void JfreetreeCir(Node* Root)
{
	if (Root->child)
	{
		JfreetreeCir(Root->child);
	}
	if (Root->treeflag == 0 && Root->child != NULL && Root->copyflag == 0)
	{
		JFreeFile(Root);
	}
	if (Root->brother)
	{
		JfreetreeCir(Root->brother);
	}
}
void JDtreeResponseFlag(Node* child)//递归使当前文件夹内所有文件夹
{
	if (child->child)
	{
		JDFlag(child->child);
	}
	if (child->brother)
	{
		JDFlag(child->brother);
	}
	if ((child->file.attrib & 0x10))
	{
		child->treeResponseFlag = 0;
	}
}

/********************************************************************************
 * 功能：显示当前文件夹下所有的文件单元
 * 参数：文件夹的结构指针temoNode；显示的起始点（最左上角）（x，y）；当前页数filePage
 * 返回值：无
 * *******************************************************************************/
void clearleftscreen()//用白色覆盖zuo侧显示屏
{
	setfillstyle(1, WHITE);
	bar(1, 92, 149, 459);
}
int JGetFirstTree(Node* RootC, int filepage,Node** temp,int time)
{
	Node* Root = RootC->child;//c盘
	int size=0;
	char* dir;
	char* test;
	Stack* S = CreatStack();
	while (Root || S->next != NULL)
	{
		while (Root)
		{
			if (Root->treeflag == 1)
			{
				size++;
				if (size > (SHOWMAX * (filepage - 1)))
				{
					*temp =Root;
					FreeStack(S);
					return size;
				}
				PushStack(Root, S);
				Root = Root->child;
			}
			else if ((Root->file.attrib & 0x10) || Root->flag == 2)
			{
					size++;
					if (size > (SHOWMAX * (filepage - 1)))
					{
						*temp = Root;
						FreeStack(S);
						return size;
					}
					Root = Root->brother;
				
			}
			else
			{
				Root = Root->brother;
			}
		}
		if (S->next != NULL)
		{
			Root = PopStack(S);
			Root = Root->brother;
		}
	}
	FreeStack(S);
	return size;
}
/*int JFindFilePage(Node* RootC, Node* temp)
{
	Node* Root = RootC->child;//c盘
	int size = 0;
	char* dir, * tempdir;
	char* test;
	Stack* S = CreatStack();
	tempdir = GetDir(temp);
	while (Root || S->next != NULL)
	{
		while (Root)
		{
			if (Root->treeflag == 1)
			{
				size++;
				if (size > (SHOWMAX * (filepage - 1)))
				{
					*temp = Root;
					FreeStack(S);
					return size;
				}
				PushStack(Root, S);
				Root = Root->child;
			}
			else if ((Root->file.attrib & 0x10) || Root->flag == 2)
			{
				size++;
				if (size > (SHOWMAX * (filepage - 1)))
				{
					*temp = Root;
					FreeStack(S);
					return size;
				}
				Root = Root->brother;

			}
			else
			{
				Root = Root->brother;
			}
		}
		if (S->next != NULL)
		{
			Root = PopStack(S);
			Root = Root->brother;
		}
	}
	FreeStack(S);
	return size;
}
*/
int JDeep(Node* temp,int n)//c盘下第1层
{
	int i=n;
	while (temp->flag!=1&&temp->flag!=2)
	{
		temp = temp->parent;
	}
	if (temp->flag != 2)
	{
		temp = temp->parent;
	}
	i++;
	if (temp->flag!=2)
	{
		i = JDeep(temp, i);
	}
	return i;
}
int ZDrawLeft(Node* Root,int bx,int by,int time)
{
	int size = 0,deep;
	char* dir;
	char* test;
	Node* temp;
	Stack* S = CreatStack();
	while (Root->parent)
	{
		while (Root || S->next != NULL)
		{
			while (Root)
			{
				if (Root->treeflag == 1)
				{
					deep = JDeep(Root, 0) - 1;
					DrawLeftFileUnit("DIR", Root, bx + 10 * deep, by + size * YGAP);
					size++;
					if (size >= SHOWMAX)
					{
						FreeStack(S);
						return size;
					}
					PushStack(Root, S);
					Root = Root->child;
				}
				else if ((Root->file.attrib & 0x10) || Root->flag == 2)
				{
					deep = JDeep(Root, 0) - 1;
					DrawLeftFileUnit("DIR", Root, bx + 10 * deep, by + size * YGAP);
					size++;
					if (size >= SHOWMAX)
					{
						FreeStack(S);
						return size;
					}
					temp = Root;
					Root = Root->brother;
				}
				else
				{
					temp = Root;
					Root = Root->brother;
				}
			}
			if (S->next != NULL)
			{
				Root = PopStack(S);
				Root = Root->brother;
			}
		}
		Root = temp;
		while (Root->parent)
		{
			while (Root->flag == 0)
			{
				Root = Root->parent;
			}
			if (Root->parent)
			{
				Root = Root->parent;
			}
			if (Root->brother!=NULL)
			{
				Root = Root->brother;
				break;
			}
		}
	}
	FreeStack(S);
	return size;
}
int ZFileUnitLeft(Node* tempNodeSe, int x, int y, int filePage)//c的爸爸
{
	Node** temp;
	int useless=0;
	int bx = x, by = y;
	char* test;
	Node* tempNode = tempNodeSe;
	tempNode = tempNode->child;//tempnode为当前文件夹的结构指针的child,已经进入文件夹！！！！！C盘
	*temp = NULL;
	useless=JGetFirstTree(tempNodeSe, filePage, temp, 0);//给出该页第一个
	tempNode = *temp;
	if (tempNode == NULL)
	{
		while (tempNode == NULL && filePage > 0)
		{
			filePage = filePage - 1;
			useless = JGetFirstTree(tempNodeSe, filePage, temp, 0);//给出该页第一个
			tempNode = *temp;

		}
		puthz(200, 8, "无法操作！", 16, 16, RED);//输入汉字
		setcolor(DARKGRAY);
		delay(1000);
		setfillstyle(1, WHITE);
		bar(190, 1, 190 + 16 * 22, 29);//190+（汉字个数+1）*16
		clrmous(MouseX, MouseY);
		clearleftscreen();//清除左侧屏幕
		leftarrow(30, 448, 1);
		rightarrow(120, 448, 1);

		useless = ZDrawLeft(tempNode, bx, by, 0);
		setfillstyle(1, WHITE);
		bar(68, 443, 80, 455);//190+（汉字个数+1）*16
		setcolor(DARKGRAY);
		itoa(filePage, test, 10);
		outtextxy(70, 445, test);
		return filePage;
	}
	clrmous(MouseX, MouseY);
	clearleftscreen();//清除左侧屏幕
	leftarrow(30, 448, 1);
	rightarrow(120, 448, 1);
	
	useless = ZDrawLeft(tempNode, bx, by, 0);
	
	
	setfillstyle(1, WHITE);
	bar(68, 443, 80, 455);//190+（汉字个数+1）*16
	setcolor(DARKGRAY);
	itoa(filePage, test, 10);
	outtextxy(70, 445, test);
	
	return filePage;
}
int treemouseknowwhere()
{
	int i;
	char* test;
	for (i = 0; i < 12; i++)
	{
		if (mouse_press(1, 92 + YGAP * i, 149, 92 + YGAP * i + YGAP-5) == 1)
		{
			delay(60);
			if (mouse_press(1, 92 + YGAP * i, 149, 92 + YGAP * i + YGAP-5) == 2)
			{
				delay(60);
				if (mouse_press(1, 92 + YGAP * i, 149, 92 + YGAP * i + YGAP-5) == 1)
				{
					
					return i + 1;
				}
			}
		}
	}

	return 0;

}






/*************************************************************************************
 * 功能：显示单个文件单元
 * 参数：文件的后缀名suffix；当前文件的结构指针tempNode；显示的起始点（最左上角）（x，y）
 * 返回值：无
 * ***********************************************************************************/
void DrawLeftFileUnit(char* suffix, Node* tempNode, int x, int y)
{
	if (tempNode == NULL)
		return;
	setcolor(DARKGRAY);
	if (tempNode->flag == 2)//如果是盘符根结点
	{
		if (tempNode->treeResponseFlag == 1)
		{
			setfillstyle(1, 11);
			bar(1, y, 149, y + YGAP - 5);
			setfillstyle(1, WHITE);
			tempNode->treeResponseFlag = 0;
		}
		sdisk(x, y);
		setcolor(DARKGRAY);
		outtextxy(x + 20, y+5, "C:");
		return;
	}
	else
	{
		if (strcmp(suffix, "DIR") == 0)
		{
			if (tempNode->treeResponseFlag == 1)
			{
				setfillstyle(1, 11);
				bar(1, y, 149, y + YGAP - 5);
				setfillstyle(1, WHITE);
				tempNode->treeResponseFlag = 0;
			}
			setcolor(DARKGRAY);
			outtextxy(x + 10, y+3, tempNode->file.name);
			sfolder(x, y+3);
		}

		if (JChecktreefolder(tempNode))
		{
			//需要一个循环遍历tempNode的儿子，有dir就退出并执行。
			if (tempNode->treeflag == 1)
			{
				rightordownarrow(142, y+8, 0, 1);//向下
			}
				
			if (tempNode->treeflag == 0)
			{
				rightarrow(143, y+8, 0);//向右
			}
		}
		return;
	}
}

