#include"common.h"
#include"JStick.h"
#include"main.h"
void JStick(Copy* head, Node* parent)//��ճ��ѭ��
{
	char* dir;
	Copy* temp = head->next;
	Node* tempnode = parent->child;
	/*
	while (tempnode)//�ѵ�ǰ�����ļ���Ϊδѡ��
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
void JStickFile(Copy* temp, Node* parent)//�����ļ�ճ��
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
int JPaste(Copy* temp, Node* parent)//ճ��ճ������ҲҪ������
{
	int num;
	Node* addnode=parent->child;
	Node* newnode;
	char*p= GetDir(parent);//�ļ���·��
	char* c = GetDir(temp->node);//Դ�ļ�·��
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
		bar(190, 1, 190 + 16 * 22, 29);//190+�����ָ���+1��*16
		puthz(200, 8, "Ŀ���ļ�����Դ�ļ��е����ļ��У��޷�������", 16, 16, RED);//���뺺��
		setcolor(DARKGRAY);
		delay(2000);
		setfillstyle(1, WHITE);
		bar(190, 1, 190 + 16 * 22, 29);//190+�����ָ���+1��*16
		return 0;
	}
	
	/*puthz(200, 8, "Ŀ���ļ�����Դ�ļ��е����ļ��У��޷�������", 16, 16, RED);//���뺺��
	setcolor(DARKGRAY);
	delay(2000);
	setfillstyle(1, WHITE);
	bar(190, 1, 190 + 16 * 22, 29);//190+�����ָ���+1��*16
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
	strcat(newdir, name);//�õ��µ��ļ��ľ���·��
	
	if ((fileRead = fopen(olddir, "rb+")) == NULL)
		printf("file %s open error", olddir);//��Ҫ�����Ƶ��ļ�
	if ((fileWrite = fopen(newdir, "wb+")) == NULL)
		printf("file %s open error", newdir);//�������ƺ���ļ�
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
		printf("file %s open error", oldDir);//��Ҫ�����Ƶ��ļ�
	if ((fileWrite = fopen(newDir, "wb+")) == NULL)
		printf("file %s open error", newDir);//�������ƺ���ļ�
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
	while (*n != '.' && *n != '~'&& *n != '\0'&&time<copy)//ֻҪû���������ַ�
	{
		time++;
		n++;//ָ������ָ
	}
	*n = '\0';//�������ַ��ĳ���ֹ����,�õ�δ�Ӵ���Ĵ�����
	size= strlen(name);
	if (size == 7)
	{
		n--;//����ļ�������7���Ǿͽ�ǰ6λ��Ϊ�����ļ���
		size = 6;
	}
	if (size == 8) //����ļ�������8���Ǿͽ�ǰ6λ��Ϊ�����ļ���
	{
		n--;
		n--;
		size = 6;
	}
	*n = '\0';
	strcpy(c, name);
	return size;
}
int JGetSameNumber(char* filename)//��ȡ�ļ���������
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
			suffix = ZGetSuffix(newnode);//�õ���׺��
			if (strcmp(suffix, "DIR") != 0)
			{
				strcat(pureName, ".");
				strcat(pureName, suffix);//���Ϻ�׺������ɸ���
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
				suffix = ZGetSuffix(newnode);//�õ���׺��
				if (strcmp(suffix, "DIR") != 0)
				{
					strcat(pureName, ".");
					strcat(pureName, suffix);//���Ϻ�׺������ɸ���
				}
				free(suffix);
		}
		strcpy(newnode->file.name, pureName);//���Ľ���е��ļ���
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
			if ((oldfolder->file.attrib & _A_SUBDIR) != 0 && oldfolder != NULL)//������һ��
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
			/*puthz(200, 8, "�޷�������", 16, 16, RED);//���뺺��
			setcolor(DARKGRAY);
			delay(2000);
			setfillstyle(1, WHITE);
			bar(190, 1, 190 + 16 * 22, 29);//190+�����ָ���+1��*16
			*/
			setfillstyle(1, WHITE);
			bar(249, 1, 280, 29);
			itoa(i, test, 10);
			outtextxy(250, 10, test);
			delay(10);
			
			
		}
	}
}
void JFolderStickCir(Node* now, Node* before,Node* parent)//ճ����ݹ��½��ڵ㣬�����ƵĽڵ�
{
	Node* newfolder = now;
	Node* oldfolder = before;
	char* newFolderDir ;//���ļ��е�Ŀ¼
	//char* oldFolderDir = GetDir(oldfolder);
	//int file = JCheckFolder(before);
	/*if (strcmp(oldfolder->file.name, parent->file.name) == 0)
	{
		puthz(200, 8, "���ļ���", 16, 16, RED);//���뺺��
		setcolor(DARKGRAY);
		delay(800);
		setfillstyle(1, WHITE);
		bar(190, 1, 190 + 5 * 16, 29);//190+�����ָ���+1��*16
		return;
	}
	*/
	
	if ((oldfolder->file.attrib & _A_SUBDIR) != 0&& oldfolder!=NULL)//������һ��
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

void JFolderStickCir1(Node* now, Node* before, Node* parent)//����ճ����ݹ��½��ڵ㣬�����ƵĽڵ�
{
	Node* newfolder = now;
	Node* oldfolder = before;
	char* newFolderDir;//���ļ��е�Ŀ¼
	//char* oldFolderDir = GetDir(oldfolder);
	//int file = JCheckFolder(before);
	/*if (strcmp(oldfolder->file.name, parent->file.name) == 0)
	{
		puthz(200, 8, "���ļ���", 16, 16, RED);//���뺺��
		setcolor(DARKGRAY);
		delay(800);
		setfillstyle(1, WHITE);
		bar(190, 1, 190 + 5 * 16, 29);//190+�����ָ���+1��*16
		return;
	}
	*/
	if ((before->file.attrib & _A_SUBDIR) != 0 && before != NULL)//������һ��
	{
		newFolderDir = GetDir(newfolder);
		/*puthz(200, 8, "���", 16, 16, RED);//���뺺��
		setcolor(DARKGRAY);
		delay(800);
		setfillstyle(1, WHITE);
		bar(190, 1, 190 + 3 * 16, 29);//190+�����ָ���+1��*16
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
void JFolderStick(Node* New, Node* Old)//ճ�����ļ��кͱ����Ƶ��ļ��У��ҳ�
{
	Node* newFolder = NULL;
	Node* oldFolder = NULL;//��������ָ��ֱ�ָ�������ļ����µĵ�һ���ļ�
	char* newFolderDir = NULL;
	char* oldFolderDir = NULL;

	newFolderDir = GetDir(New);
	oldFolderDir = GetDir(Old);
	mkdir(newFolderDir);//win�½����µ��ļ���
	if (Old->child==NULL)
	{
		Fileini(oldFolderDir, Old);//�ȴ򿪾ɵ��ļ���
	}
	newFolder = New->child;
	oldFolder = Old->child;
	free(newFolderDir);
	free(oldFolderDir);
	while (oldFolder != NULL)//�ȸ���һ��
	{
		if ((oldFolder->file.attrib & _A_SUBDIR) != 0)//������ļ���
		{
			oldFolderDir = GetDir(oldFolder);//�õ�����·��
			newFolderDir = GetDir(New);//�õ��µ��ļ��еľ���·��
			strcat(newFolderDir, "\\");
			strcat(newFolderDir, oldFolder->file.name);
			mkdir(newFolderDir);//�����µ��ļ���
			free(newFolderDir);
			free(oldFolderDir);
		}
		else if ((oldFolder->file.attrib & _A_SUBDIR) == 0)//��������ļ���
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
			if ((old->file.attrib & _A_SUBDIR) != 0 && old != NULL)//������һ��
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

	if ((old->file.attrib & _A_SUBDIR) != 0)//���ļ��оʹ�
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