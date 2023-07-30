#include"JFileini.h"
#include "common.h"
void Fileini(char* dir, Node* tree)
{
	struct find_t find;
	char scanfilename[13];
	char* fileName = NULL;
	char tem[100];
	Node* tempNode;
	int flag = 0, time = 0;
	strcpy(tem, dir);//将当前目录存入tem
	strcat(tem, "\\*.*");//在末尾加上\\*.*满足扫描函数的要求
	if(tree->flag==3)
	{
		return;
	}
	flag = _dos_findfirst(tem, 0xFF, &find);
	while (flag == 0)
	{
		strcpy(scanfilename, find.name);
		fileName = scanfilename;
		while (*fileName != '.' && *fileName != '\0')//得到后缀名，以过滤文件
		{
			strcpy(fileName, fileName + 1);
		}
		strcpy(fileName, fileName + 1);
		if (strcmp(find.name, ".") == 0 || strcmp(find.name, "..") == 0 || \
			strcmp(find.name, "C_DRIVE") == 0||\
			strcmp(find.name, "WINDOWS") == 0 || strcmp(find.name, "PROGRA~1") == 0 || \
			*(find.name)>126|| *(find.name) <32 || \
			find.attrib & 0x04 || find.attrib & 0x02|| \
			strcmp(fileName, "SYS") == 0 || strcmp(fileName, "BAT") == 0 || \
			strcmp(fileName, "INI") == 0 || strcmp(fileName, "BIN") == 0 || \
			strcmp(fileName, "COM") == 0 || strcmp(find.name, "HZK") == 0 || \
			strcmp(find.name, "IWINDOSN") == 0 || strcmp(find.name, "VSCODE~1") == 0 || \
			strcmp(find.name, "HZ16") == 0 || strcmp(find.name, "HZK24K") == 0 || \
			strcmp(find.name, "HZK32S") == 0 || strcmp(find.name, "HZK48K") == 0 /*  ||\s
			strcmp(find_t.name,"BORLANDC")==0  */)//过滤不正常的文件夹和文件
		{
			flag = _dos_findnext(&find);
			continue;
		}
		if ((find.attrib & _A_SUBDIR) == 0 && *fileName == '\0')//不是文件夹并且没有后缀名
		{
			flag = _dos_findnext(&find);
			continue;
		}
		if (time == 0)//将扫描到的文件信息建树
		{
			CreateFileNodeChild(tree, find);
			tempNode = tree->child;
			time++;
		}
		else
		{
			CreateFileNodeBro(tempNode, find);
			tempNode = tempNode->brother;
			time++;
		}
		if (time == 50)
		{
			JSort(tree, 2);
				return;
		}
		flag = _dos_findnext(&find);
	}
	JSort(tree, 2);
}
char* JGetdate(Node* tempNode)
{
	char* dateAndTime = (char*)malloc(20);
	//printf("%s\n",dateAndTime);
	//printf("%d\n",tempNode->fileInfo.wr_date/512+1980);
	sprintf(dateAndTime, "%d/%d/%d %02d:%02d", tempNode->file.date / 512 + 1980, \
		(tempNode->file.date % 512) / 32, tempNode->file.date % 32, \
		tempNode->file.time / 2048, (tempNode->file.time % 2048) / 32);
	//printf("%s\n",dateAndTime);
	//printf("%d\n",tempNode->fileInfo.wr_date/512+1980);
	return dateAndTime;
}
