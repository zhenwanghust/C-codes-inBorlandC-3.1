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


typedef struct file  //�ļ����Լ�����Ϣ�ڵ�,�����������ṹ���б����� 
{
	char name[13];
	long size;
	unsigned time;
	unsigned date;
	char attrib;
}file;
typedef struct Search//�ļ����Լ�����Ϣ�ڵ�,�����������ṹ���б����� 
{
	struct Search* next;
	struct Node* node;
}Search;
typedef struct NewStack//�ļ����Լ�����Ϣ�ڵ�,�����������ṹ���б����� 
{
	struct Node* Data[20];
	int Top;
}NewStack;
typedef struct Stack//�ļ����Լ�����Ϣ�ڵ�,�����������ṹ���б����� 
{
	struct Stack* next;
	struct Node* node;
}Stack;
typedef struct Copy//�ļ���֮�䣩�ܽ��
{
	int flag;//�����ж��ǲ���0���ƻ�1����
	struct Copy* pre;
	struct Copy* next;
	struct Node* node;
}Copy;

typedef struct Node//�ļ���֮�䣩�ܽ��
{
	file file;
	int flag;//�����ж��ǲ�����֦�ĸ��ڵ�(2�Ǵ��� 1����֦�� 0��������ͨ���)rootΪ3 
	int responseFlag;
	int treeflag;//0�ǹر�1�Ǵ�
	int treeResponseFlag;
	int freeflag;
	int copyflag;
	int delecopyflag;
	struct Node* child;//ָ�����ļ� 
	struct Node* brother;//ָ���ֵ��ļ� 
	struct Node* parent;//ָ���ļ��е�ָ�룬���ڷ��ز���
}Node;

typedef struct TreeRoot//�������
{
	
	file file;
	int flag;//�����ж��ǲ�����֦�ĸ��ڵ�(2�Ǵ��� 1����֦�� 0��������ͨ���)
	int responseFlag;
	int fileTreeflag;
	struct Node* child;
	struct Node* brother;
	struct Node* parent;//ָ���ļ��е�ָ�룬���ڷ��ز���
	struct Node* quickSpace;
	struct Node* copySpace;
	struct Node* searchSpace;
}TreeRoot;

typedef struct fileDirNode//������ʵ����¸���ճ���Ĵ���ļ�����·����С��� 
{
	char fileDir[50];
	int saveorigin;  //1Ϊ���ƣ�������ԭ���ڵ㣬0Ϊ���У���Ϊ������ 
}fileDirNode;

typedef struct Back
{
    struct Back *next;
    struct Back *pre;
	struct Node* tempNode;
}Back;



typedef struct Current//����ʹһ������ͬʱ���ض������
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
