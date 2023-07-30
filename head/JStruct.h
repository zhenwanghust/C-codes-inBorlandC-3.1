#ifndef _JSTRUCT_H_
#define _JSTRUCT_H_


//struct find_t 
//{
  //  char     reserved[21];      /* Microsoft reserved - do not change */
    //char     attrib;            /* attribute byte for matched file */
    //unsigned wr_time;           /* time of last write to file */
    //unsigned wr_date;           /* date of last write to file */
    //long     size;              /* size of file */
    //char     name[13];          /* asciiz name of matched file */
//};


typedef struct file  //文件（自己）信息节点,在下面两个结构体中被调用 
{
	char name[13];
	long size;
	unsigned time;
	unsigned date;
	char attrib;
}file;
typedef struct Search//文件（自己）信息节点,在下面两个结构体中被调用 
{
	struct Search* next;
	struct Node* node;
}Search;
typedef struct NewStack//文件（自己）信息节点,在下面两个结构体中被调用 
{
	struct Node* Data[20];
	int Top;
}NewStack;
typedef struct Stack//文件（自己）信息节点,在下面两个结构体中被调用 
{
	struct Stack* next;
	struct Node* node;
}Stack;
typedef struct Copy//文件（之间）总结点
{
	int flag;//用于判断是不是0复制或1剪切
	struct Copy* pre;
	struct Copy* next;
	struct Node* node;
}Copy;

typedef struct Node//文件（之间）总结点
{
	file file;
	int flag;//用于判断是不是树枝的根节点(2是磁盘 1是树枝根 0是其他普通结点)root为3 
	int responseFlag;
	int treeflag;//0是关闭1是打开
	int treeResponseFlag;
	int freeflag;
	int copyflag;
	int delecopyflag;
	struct Node* child;//指向子文件 
	struct Node* brother;//指向兄弟文件 
	struct Node* parent;//指向父文件夹的指针，便于返回操作
}Node;

typedef struct TreeRoot//树根结点
{
	
	file file;
	int flag;//用于判断是不是树枝的根节点(2是磁盘 1是树枝根 0是其他普通结点)
	int responseFlag;
	int fileTreeflag;
	struct Node* child;
	struct Node* brother;
	struct Node* parent;//指向父文件夹的指针，便于返回操作
	struct Node* quickSpace;
	struct Node* copySpace;
	struct Node* searchSpace;
}TreeRoot;

typedef struct fileDirNode//用于真实情况下复制粘贴的存放文件绝对路径的小结点 
{
	char fileDir[50];
	int saveorigin;  //1为复制，即保留原来节点，0为剪切，即为不保留 
}fileDirNode;

typedef struct Back
{
    struct Back *next;
    struct Back *pre;
	struct Node* tempNode;
}Back;



typedef struct Current//用来使一个函数同时返回多个参数
{
    short int Currentpage;
    short int CurrentfilePage;
    Node* CurrentNode;
    int displayModeReturn;
    int sortFlagReturn;
}Current;



typedef struct pageAndMode
{
    int pageRe;
    short int displayModeReturn;
}pageAndMode;


#endif 
