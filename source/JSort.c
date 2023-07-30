#include"common.h"
#include"JSort.h"
#include "main.h"
void JSort(Node* parent,int flag)
{
    int (*fun)(Node*, Node*);
    int size = 0;
    int n;
    int nofile = 0;
    int i, j, k;  //Ñ­»·¸¨Öú±äÁ¿
    Node* temp = parent->child;
    Node* change = parent->child;
    n = flag / 2;
    switch (n)
    {
    case 1:
        fun = JSortName;
        flag = flag % 2;
        break;
    case 2:
        fun = JSortDate;
        flag = flag % 2;
        break;
    case 3:
        fun = JSortSize;
        flag = flag % 2;
        break;
    case 4:
        fun = JSortType;
        flag = flag % 2;
        break;
    default:
        break;
    }
    while (temp != NULL)
    {
        size++;
        temp = temp->brother;
    }
    for (i = 0; i < size - 1; i++)  //Ã°ÅÝ·¨ÅÅÐò
    {
        for (j = 0; j < size - 1 - i; j++)
        {
            temp = parent->child;
            for (k = 0; k < j; k++)
            {
                temp = temp->brother;
            }
            if (flag == 0)
            {

                if (fun(temp, temp->brother) > 0)
                {
                    JChange(temp, temp->brother);
                }
            }
            else if (flag == 1)
            {

                if (fun(temp, temp->brother) < 0)
                {
                    JChange(temp, temp->brother);
                }
            }
        }
    }
    temp = parent->child;
    if (flag==0)
    {
        while (temp != NULL)
        {
            if (!(temp->file.attrib & 0x10))
            {
                nofile++;
            }
            temp = temp->brother;
        }
        temp = parent->child;
        for (i = 0; i < nofile; i++)
        {
            temp = parent->child;
            while (temp->file.attrib & 0x10)
            {
                temp = temp->brother;
            }
            change = temp;
            if (!(temp->file.attrib & 0x10))
            {
                while (temp->brother != NULL)
                {
					temp = parent->child;
					while (temp != change)
					{
						temp = temp->brother;
					}
					JChange(temp, temp->brother);

                   // JChange(change, temp->brother);
                }
            }
        }
    }
    if (flag ==1)
    {
        while (temp != NULL)
        {
            if ((temp->file.attrib & 0x10))
            {
                nofile++;
            }
            temp = temp->brother;
        }
        temp = parent->child;
        for (i = 0; i < nofile; i++)
        {
            temp = parent->child;
            while (!(temp->file.attrib & 0x10))
            {
                temp = temp->brother;
            }
            change = temp;
            if (temp->file.attrib & 0x10)
            {
                while (temp->brother != NULL)
                {
                    JChange(change, temp->brother);
                }
            }
        }
    }
    
	
}
void JChange(Node* t1, Node* t2)
{
    if (t1->flag == 1)//ï¿½ï¿½ï¿½tempNode1ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Í·
    {
        t1->flag = 0;
        t2->flag = 1;
        t1->parent->child = t2;
        t2->parent = t1->parent;
        if (t2->brother)//tempNodeï¿½ÖµÜ½Úµã²»Îªï¿½ï¿½
        {
            t2->brother->parent = t1;
            t1->brother = t2->brother;
            t2->brother = t1;
            t1->parent = t2;
        }
        else
        {
            t1->brother = NULL;
            t2->brother = t1;
            t1->parent = t2;
        }
    }
    else
    {
        if (t2->brother)
        {
            t1->parent->brother = t2;
            t2->brother->parent = t1;
            t2->parent = t1->parent;
            t1->parent = t2;
            t1->brother = t2->brother;
            t2->brother = t1;
        }
        else
        {
            t1->brother = NULL;
            t1->parent->brother = t2;
            t2->parent = t1->parent;
            t2->brother = t1;
            t1->parent = t2;
        }
    }
}

int JSortDate(Node* t1, Node* t2)
{
	int time;
	time = (int)t1->file.date - (int)t2->file.date;
	if (time)
	{
		return time;
	}
	else
	{
		time = (int)t1->file.time - (int)t2->file.time;
		return time;
	}
}
int JSortName(Node* tempNode1, Node* tempNode2)
{
	return strcmp(tempNode1->file.name, tempNode2->file.name);
}
int JSortSize(Node* tempNode1, Node* tempNode2)
{
	int size;
	size = tempNode1->file.size/1024 - tempNode2->file.size/1024;
	if (size)
	{
		return size;
	}
	else
	{
		return  strcmp(tempNode1->file.name, tempNode2->file.name);
	}
}
int JSortType(Node* tempNode1, Node* tempNode2)
{
	char *suffix1;
	char *suffix2;
    int a;
	suffix1=ZGetSuffix(tempNode1);
	suffix2=ZGetSuffix(tempNode2);
    a = strcmp(suffix1, suffix2);
    free(suffix1);
    free(suffix2);
	return a;
}