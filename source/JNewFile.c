#include"common.h"
#include"JNewFile.h"
#include"main.h"
int JCreatFile(Node* parent, char* suffix, char* name)//文件夹，后缀名，名字
{
	Node* temp,*newnode;
	char* getdir;
	struct find_t find;
	char* su;
	char text[5];//辅助字符串
	int flag,flagfile;
	FILE* fp;
	getdir = GetDir(parent);//父文件地址
	*text = '\\';
	*(text + 1) = '\0';
	strcat(getdir, text);
	if (strlen(name) == 0)
	{
		return 0;
		//strcpy(name, "NewFile");
	}
	
/*	if (JCheckSpace(name) == 0)
	{
		strcpy(name, "NewFile");
	}
	*/
	if (suffix != NULL &&strcmp(suffix,"DIR")!=0)//不是文件夹
	{
		if (strstr(name, ".") == NULL)  //如果在已知格式下没有再次输入扩展名
		{
			JSamename(name,suffix, parent);
			strcat(getdir,name);
			if ((fp = fopen(getdir, "wb+")) == NULL)
			{
				printf(" creat new file fail!");
			}
			else {
				flag = 1;
			}
		}
		else if ((su=strstr(name, ".") )!= NULL)
		{
			su++;
			if (JCheckNewsuffix(su) == 0)
			{
				flag = 0;
				free(getdir);
				return flag;
			}
			else
			{
				JSamename(name, suffix, parent);
				strcat(getdir, name);
			}
			if ((fp = fopen(getdir, "wb+")) == NULL)
			{
				printf(" creat new file fail!");
			}
			else {
				flag = 1;
			}
		}
	}
	else if (suffix != NULL && strcmp(suffix, "DIR") == 0)
	{
		JSamename(name, suffix, parent);
		strcat(getdir, name);
		if (mkdir(getdir) == -1)   //如果在真实win创建文件夹失败
		{
			printf("error open dir");
		}
		else
		{
			flag = 1;
		}
	}
	fclose(fp);
	temp = parent->child;
	newnode = CreateNode();
	if (temp==NULL)
	{
		parent->child = newnode;
		newnode->parent = parent;
		newnode->flag = 1;
	}
	else
	{
		while (temp->brother!=NULL)
		{
			temp = temp->brother;
		}
		temp->brother = newnode;
		newnode->parent = temp;
		newnode->flag = 0;
	}
	flagfile = _dos_findfirst(getdir, 0xFF, &find);
	strcpy(newnode->file.name, find.name);
	newnode->file.size = find.size;
	newnode->file.time = find.wr_time;
	newnode->file.date = find.wr_date;
	newnode->file.attrib = find.attrib;
	free(getdir);
	return flag;
}

void JSamename(char* name,char* suffix,Node*parent)
{
	int flag=0;
	int size = 0;
	char pure[13];//
	char* su;
	char* purename = pure;
	strcpy(pure, name);
	if (suffix != NULL && strcmp(suffix, "DIR") == 0)//是文件夹
	{
		flag=JNewSameName(purename, suffix, parent);
		if (flag!=0)
		{
			JChangeNewname(flag, suffix, name);
		}
		else
		{
			if (strlen(name)>8)
			{
				*(name+8) = '\0';
			}
		}
	}
	else if (suffix != NULL && strcmp(suffix, "DIR") != 0)//不是文件夹
	{
		if (strstr(name, ".") == NULL)//没有自定义文件
		{
			flag = JNewSameName(purename, suffix, parent);
			if (flag != 0)
			{
				JChangeNewname(flag, suffix, name);
			}
			else
			{
				if (strlen(name) > 8)
				{
					*(name + 8) = '\0';
				}
				strcat(name, ".");
				strcat(name, suffix);
			}
		}
		else if (su=strstr(name, ".") != NULL)//自定义文件后缀名
		{
			/*while (*purename != '.' && *purename != '\0')//只要没碰上特殊字符
			{
				purename++;//指针往后指
			}
			*purename = '\0';
			* */
			su++;
			if (JCheckNewsuffix(su)==0)
			{
				return ;
			}
			flag = JNewSameName(purename, su, parent);
			if (flag != 0)
			{
				JChangeNewname(flag, su, name);
			}
		}
	}
	
	
}
int JGetPureNew(char*temp)
{
	char name[13];
	char* n;
	int time = 0;
	int size;
	strcpy(name, temp);
	n = name;
	while (*n != '.' && *n != '~' && *n != '\0' && time < 8)//只要没碰上特殊字符
	{
		time++;
		n++;//指针往后指
	}
	*n = '\0';//把特殊字符改成终止符号,得到未加处理的纯净名
	size = strlen(name);
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
	strcpy(temp, name);
	return size;
}
int JNewSameName(char* copypure, char* copySuffix, Node* parent)
{
	int num1 = 0, num2 = 0;
	int time = 0, n = 1;
	int sizecopy, sizetemp;
	char* tempSuffix;
	char filepure[9];
	Node* temp = parent->child;
	sizecopy = JGetPureNew(copypure);
	while (temp)
	{
		sizetemp = JGetPureName(temp, filepure, sizecopy);
		if (strcmp(copypure, filepure) == 0)
		{
			tempSuffix = ZGetSuffix(temp);
			if (strcmp(copySuffix, tempSuffix) == 0)
			{
				time++;
				if (n = 1)
				{
					num1 = JGetSameNumber(temp->file.name);
				}
				else if (n = -1)
				{
					num2 = JGetSameNumber(temp->file.name);
				}
				if ((num1 - num2 >= 2) && n == 1)
				{
					free(tempSuffix);
					return (num2 + 1);
				}
				if ((num2 - num1 >= 2) && n == -1)
				{
					free(tempSuffix);
					return (num1 + 1);
				}
				n = n*(-1);
			}
			free(tempSuffix);
		}
		temp = temp->brother;
	}
	if (time == 0)
	{
		return 0;
	}
	if (num1 > num2)
	{
		return (num1 + 1);
	}
	else
	{
		return (num2 + 1);
	}
}
void JChangeNewname(int num, char* copySuffix, char* name)
{
	int i;
	char numchar[3];
	char newname[13];
	char* pure;
	int size, nii;
	size = strlen(name);
	strcpy(newname, name);
	nii=JGetPureNew(newname);
	pure = newname;
	if (num == 0)
	{
		return;
	}
	if (num >= 10)
	{
		for (i = 0; i < 5; i++)
		{
			pure++;
		}
		*pure = '\0';
		itoa(num, numchar, 10);
		strcat(newname, "~");
		strcat(newname, numchar);
		if (strcmp(copySuffix, "DIR") != 0)
		{
			strcat(newname, ".");
			strcat(newname, copySuffix);//加上后缀名，完成更改
		}
	}
	else
	{
		for (i = 0; i < 6; i++)
		{
			pure++;
		}
		*pure = '\0';
		itoa(num, numchar, 10);
		strcat(newname, "~");
		strcat(newname, numchar);
		if (strcmp(copySuffix, "DIR") != 0)
		{
			strcat(newname, ".");
			strcat(newname, copySuffix);//加上后缀名，完成更改
		}
	}
	strcpy(name, newname);//更改结点中的文件名
}
int JCheckNewsuffix(char* suffix)
{
	int flag = 0;
	{
		if (strcmp(suffix, "DOC") == 0)
		{
			flag = 1;
		}
		if (strcmp(suffix, "PDF") == 0)
		{
			flag = 1;
		}
		if (strcmp(suffix, "XLS") == 0)
		{
			flag = 1;
		}
		if (strcmp(suffix, "TXT") == 0)
		{
			flag = 1;
		}
		if (strcmp(suffix, "DAT") == 0)
		{
			flag = 1;
		}
		if (strcmp(suffix, "JPG") == 0)
		{
			flag = 1;
		}
		if (strcmp(suffix, "MP4") == 0)
		{
			flag = 1;
		}
		if (strcmp(suffix, "MP3") == 0)
		{
			flag = 1;
		}
		if (strcmp(suffix, "C") == 0)
		{
			flag = 1;
		}
		if (strcmp(suffix, "H") == 0)
		{
			flag = 1;
		}
		return flag;
	}
}
int JCheckSpace(char* name)
{
	char pure[13];
	char* purename = pure;
	int size;
	int i = 0;
	strcpy(pure, name);
	while (*purename != '.' && *purename != '\0')//只要没碰上特殊字符
	{
		purename++;//指针往后指
	}
	*purename = '\0';//把特殊字符改成终止符号,得到未加处理的纯净名

	size = strlen(purename);
	for (i = 0; i < size; i++)
	{
		if (*purename == ' ')
		{
			strcpy(purename, purename + 1);
			continue;
		}
		purename++;
	}
	if (strlen(purename)==0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}