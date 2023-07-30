#include"common.h"
#include"JReName.h"
#include"main.h"
void JReName(Node* parent, char* reName)
{
	int flagfile;
	struct find_t find;
	char* olddir, * newdir;
	char* name,*su,*suffix;
	int puresize;
	Node* temp = parent->child;
	if (strlen(name) == 0)
	{
		return;
	}
	
	while (temp)
	{
		if (temp->responseFlag)
		{
			break;
		}
		temp = temp->brother;
	}
	if (strcmp(reName,temp->file.name)==0)
	{
		return;
	}
	if (su=strstr(name,".")!=NULL)
	{
		return;
	}
	olddir = GetDir(temp);
	newdir = GetDir(parent);
	strcat(newdir, "\\");
	suffix = ZGetSuffix(temp);
	JSamename(reName, suffix, parent);//文件夹重命名
	name = reName;
	if (su=strstr(name,".")!=NULL)
	{
		if (temp->file.attrib & _A_SUBDIR)
		{
			*su = '\0';
		}
		else
		{
			su++;
			/*if (strcmp(su, suffix) != 0)
			{
				free(suffix);
				free(olddir);
				free(newdir);
				return;
			}
			*/
		}
	}
	//strcpy(temp->file.name, reName);
	strcat(newdir, reName);
	rename(olddir, newdir);

	flagfile = _dos_findfirst(newdir, 0xFF, &find);
	strcpy(temp->file.name, find.name);
	temp->file.size = find.size;
	temp->file.time = find.wr_time;
	temp->file.date = find.wr_date;
	temp->file.attrib = find.attrib;
	free(suffix);
	free(olddir);
	free(newdir);
}