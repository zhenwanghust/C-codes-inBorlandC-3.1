
 #include "ZMenu.h"
 #include "XMouse.h"
 #include "number.h"
 #include "ZIcons.h"
 #include "ZIconl.h"
 #include "ZTool.h"
 #include "JFileOpe.h"
#include "Zright.h"
#include "JFileini.h"
#include "JSort.h"
#include "main.h"


int menu(Node* RootC)
{
	Search* searchtemp;
	Back* tempback=NULL,* headback=NULL;
	char* searchchar=NULL;
	Node* temp=RootC;
	Copy* head;
	Node* change=NULL;
	Node* tool=NULL;
	Node* Jtree=NULL;
	Search* parent;
	int Jtreeflag=0;
	int dakaiflag=0,fuzhiflag=0,paixuflag=0,zhantieflag=0,jianqieflag=0,chongmingmingflag=0;
	int xinjianflag=0,shuxingflag=0,shanchuflag=0,quedingshanchuflag=0;
	int drawtimes=0;//limit rightclick draw
	int quit=0;
	int searchflag=0;
	int area;//click right draw direction
	int rightnewx,rightnewy;//右键新建起始点
	int rightmodex,rightmodey;//右键起始点
	char* youjianwherechar=NULL;
	int tempx,tempy;// click right where
	int youjianwhere;//11,12,13,21,22,23
	int rightwhere=0;//where you click on rightclick-menu
	int rightpaixuarea=0;//where you click on rightclick-menu-paixu
	int k,filepage=1,showmode=1;	
    int i ,j ,x,y;	//辅助
	int sortflag = 2;
    int ifoneselected=0;
    int mousewhere=0;//记录鼠标的位置
    int Rmousewhere=0;//右键鼠标的位置
    int rightarea=0;
	int leftpage = 1;
    int pagemax=1,useless;//与显示的页数相关
    char filepagechar[3];
    char fangwenchar[40];
    char* dir;
	char* test;
    char* sousuochar=NULL,*xinjianchar=NULL,*chongmingmingchar=NULL;
    int ifselected=0;//记录是否有选中的文件
    int modeicon=0;
	int size = 0;
    short int alreadyfz=0,alreadyzt=0,alreadyjq=0,alreadysc=0,alreadyqx=0;
    short int alreadyquxiao=0  ,alreadyfx=0,alreadycmm=0,alreadyxjwjj=0,alreadyxjwbwj=0;
	cleardevice();
	setbkcolor(WHITE);
	clrmous(MouseX,MouseY);
	mouseinit();
	setfillstyle(1,WHITE);
	line(0,90,640,90);//上下分界线
	line(0,60,640,60);
	line(0,30,640,30);//上屏幕工具栏分界线
	line(150,90,150,460);//左右界面分界线
	line(615,15,625,25);
	line(615,25,625,15);
	rectangle(120,65,475,85);
	line(455,65,455,85);//画中间横向工具栏
	drawhomebutton (575,6);//画返回c盘键
	leftarrow(15,75,1);
	rightarrow(55,75,1);
	uparrow(90,72,1);//画出左上角后退前进与返回c磁盘页
	leftarrow(98,452,1);
	rightarrow(148,452,1);
	outtextxy(120,450,"1");//画出左下角左侧屏幕翻页与显示页数功能,
	rectangle(505,65,635,86);//画搜索框
	line(0,460,639,460);//画底部菜单
	rightarrow(490,470,1);
	leftarrow(440,470,1);
	outtextxy(462,468,"1");//画出右下角右侧屏幕翻页与显示页数功能
	//puthz(510,68,"在此位置下搜索",16,16,LIGHTGRAY);
	
	circle(497,73,4);//画刷新图标
	line(487,85,494,77);
	circle(465,75,7);
	bar(463,67,470,70);
	line(470,70,467,74);
	line(470,70,474,70);
	line(150,90,150,110);
	line(300,90,300,110);
	line(470,90,470,110);
	line(550,90,550,110);//排序功能的分界线
	puthz(155,95,"名称",16,16,LIGHTGRAY);
	puthz(305,95,"修改日期",16,16,LIGHTGRAY);
	puthz(475,95,"类型",16,16,LIGHTGRAY);
	puthz(555,95,"大小",16,16,LIGHTGRAY);
	puthz(5,38,"复制",16,16,LIGHTGRAY);
	puthz(84,38,"粘贴",16,16,LIGHTGRAY);
	puthz(165,38,"剪切",16,16,LIGHTGRAY);
	puthz(245,38,"删除",16,16,LIGHTGRAY);
	puthz(322,38,"重命名",16,16,LIGHTGRAY);
	puthz(408,38,"全选",16,16,LIGHTGRAY);
	puthz(485,38,"取消",16,16,LIGHTGRAY);
	puthz(565,38,"反选",16,16,LIGHTGRAY);
	puthz(5,8,"新建文件夹",16,16,LIGHTGRAY);
	puthz(112,8,"新建文件",16,16,LIGHTGRAY);
	setfillstyle(1,11);
	bar(605,464,625,479);//默认先进入详细信息模式
	detailmodeicon(610,465);
	bigmodeicon(570,465);	
	puthz(10,462,"共有",16,16,LIGHTGRAY);
	puthz(62,462,"个项目",16,16,LIGHTGRAY);
	puthz(120,462,"共",16,16,LIGHTGRAY);
	puthz(152,462,"页",16,16,LIGHTGRAY);
	puthz(235,462,"共选中",16,16,LIGHTGRAY);
	puthz(301,462,"个项目",16,16,LIGHTGRAY);
	useless=ZFileUnit(RootC,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);//显示模式先默认为1
	tempback=NewBack();
	headback = NewBack();
	tempback->tempNode=RootC;
	headback->next = tempback;
	tempback->pre = headback;
	head = CreateCopy();
	parent=JCreateSearch();
	leftpage=ZFileUnitLeft(RootC, 1, 92, leftpage);

	
	
	while(1)//all
	{
		while(1)//first
		{	newmouse(&MouseX,&MouseY,&press);
		/************************
		1.to exit
		************************/
			if(mouse_press(590,10,630,45)==1)
			{return 0;	}
		/************************
		2.change showmode
		************************/
			if(mouse_press(605,460,639,479)==1&&searchflag==0)//go small
			{
				delay(30);
				clrmous(MouseX,MouseY);
				showmode=1;//切换为详细信息模式
				pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);
				setfillstyle(1,11);
				bar(605,464,625,479);
				detailmodeicon(610,465);
				setfillstyle(1,WHITE);
				bar(565,464,585,479);
				bigmodeicon(570,465);
			}
			else if(mouse_press(565,460,605,479)==1&&searchflag==0)
			{
				delay(30);showmode=2;//go big
				pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);
				setfillstyle(1,11);
				bar(565,464,585,479);
				bigmodeicon(570,465);
				setfillstyle(1,WHITE);
				bar(605,464,625,479);
				detailmodeicon(610,465);
			}
			/************************
		3.refresh
		************************/
			if (mouse_press(455,65,475,85)==1&&searchflag==0)//3.刷新功能
			{
				delay(30);
				clrmous(MouseX,MouseY);
				pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);//需要当前节点，当前显示模式。
				newmouse(&MouseX,&MouseY,&press);delay(400);
			}
			/************************
				4.back to menu
				************************/
			if (mouse_press(555,10,585,25)==1&&( bioskey(2)&2)!=0)//4.返回c盘功能
			{
				JFreeBack(headback);
				FreeCopy(&head);
				JFreeSearch(parent);
				free(headback);
				free(head);
				free(parent);
				JCFree(RootC->child);
				RootC->child->responseFlag = 0;
				RootC->child->copyflag = 0;
				RootC->child->treeResponseFlag = 0;
				RootC->child->treeflag = 0;
				RootC->child->delecopyflag = 0;
				RootC->child->freeflag = 0;
				Fileini("C:", RootC->child);
				searchflag=0;
				return 2;
			}	
			/************************
			5.up|^upupupupup
			************************/
			if (mouse_press(80,60,100,90) == 1&&(temp->flag!=3|| searchflag == 1))//5.后退功能(后退到上一级)
			{
				if(searchflag==1)
				{
					pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);//重新画图，得到背景色。
					JDFlag(temp->child);
					leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
					searchflag=0;
					JFreeBack(headback);
					delay(100);
				}
				else if (temp->flag!=3)
				{
					clrmous(MouseX, MouseY);
					JDFlag(temp);
					temp = BackFile(1, temp, filepage, showmode);
					temp->treeResponseFlag = 1;
					delay(60);
					newmouse(&MouseX, &MouseY, &press);
					delay(200);
					leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
					JFreeBack(tempback);
					tempback = headback;
					Jfreetree(RootC);
					filepage = 1;
					delay(100);
				}
			}
			/************************
			6.go front front
				************************/
			if (mouse_press(37,60,62,90) == 1&& tempback->next!=NULL&&searchflag==0)//5.1前进功能
			{
				clrmous(MouseX,MouseY);
				delay(100);
				JFront(&temp,&tempback,&pagemax,showmode);
				filepage = 1;
				temp->treeResponseFlag = 1;
				JBuildTree(temp);
				leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
				newmouse(&MouseX,&MouseY,&press);
				delay(200);
			}
			/************************
			7.go back back
				************************/
			if (mouse_press(1,60,36,90)==1&& tempback->pre->tempNode != NULL&& tempback->pre!=NULL)//后退功能，可以考虑可点击前进加一个if条件(后退到上一个画面)
			{
				if(searchflag==1)
				{
					pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);//重新画图，得到背景色。
					leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
					JDFlag(temp->child);
					searchflag=0;
					delay(100);
				}
				else
				{
					clrmous(MouseX, MouseY);
					delay(60);
					filepage = 1;
					temp->treeResponseFlag = 1;
					temp->treeflag = 0;
					leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
					JBack(&temp, &tempback, &pagemax, showmode);
					newmouse(&MouseX, &MouseY, &press);
					delay(200);
				}
			}
			/************************
			8.page++,right page++
				************************/
			if(mouse_press(478,460,492,479)==1&&searchflag==0)//右侧向后翻页功能
			{
				clrmous(MouseX,MouseY);
				delay(90);	
				filepage++;
				if(filepage>=pagemax)
				{
					filepage=pagemax;
				}
				pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);
				newmouse(&MouseX,&MouseY,&press);	
				delay(200);
			}
			/************************
			9.page--,right page--
				************************/
			if(mouse_press(435,460,455,479)==1&&searchflag==0)//右侧向前翻页功能
			{
				delay(90);
				clrmous(MouseX,MouseY);
				filepage--;
				if(filepage<=0)//防止页数超出范围
					{filepage=1;}
				pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);
				newmouse(&MouseX,&MouseY,&press);
				delay(200);
			}
			/************************
			10.search search search
				************************/
			if(mouse_press(505,65,635,86)==1&& searchflag==0)//搜索框功能
			{
				clrmous(MouseX,MouseY);
				sousuochar=GetString(505,65,120,sousuochar);
				useless=JSearch(sousuochar,temp,RootC->child,parent);
				if(useless)
					{searchflag=1;}
				useless = 0;
				sousuochar=NULL;
				JFreeBack(tempback);
				tempback = headback;
				delay(100);
			}
			/************************
			11 press crtl    duoxuan
				************************/
			 while(bioskey(2)&4)//如果按了CRTL,多选
			{
				newmouse(&MouseX,&MouseY,&press);
				mousewhere = 0;
				if (showmode == 1)
				{
					mousewhere = smallknowwhere();
				}
				else if (showmode == 2)
				{
					mousewhere = bigknowwhere();
				}
				if (mousewhere != 0)
				{
					if(getfilenumer(temp->child)>=mousewhere+(filepage-1)*12)
					{
						delay(30);
						clrmous(MouseX,MouseY);
						change=temp->child;
						for(i=0;i<mousewhere+(filepage-1)*12-1;i++)
						{
							change=change->brother;
						}
						change->responseFlag=1;
						//如果mousewhere变量得到了非零的值，那么改变背景色参数responseflag
						pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);//重新画图，得到背景色。
					}
				}
			}
			/************************
			12.RIGHT!!!!   press TO OPEN右键单击
				************************/
			if(dakaiflag==1&&searchflag==0)//右键的打开文件
			{
				tool = temp->child;
				while(tool != NULL)
				{
					if(tool->responseFlag==1)
					{
						break;
					}
					tool = tool->brother;
				}
				if (ifonlyoneselected(temp) == 1)//如果只有一个文件被选中
				{
					if ((tool->file.attrib & _A_SUBDIR) != 0 || tool->flag == 2)
						temp = tool;
					if (searchflag == 1)
					{
					/*
						JOpenSearch(parent, &temp, mousewhere + (filepage - 1) * 12, 1);
						tempback = JPushBack(tempback, temp);
						if (temp->file.attrib & 0x10 || temp->flag == 2)
						{
							JBuildTree(temp);
							Jfreetree(RootC);
						}
						temp->treeResponseFlag = 1;
						//leftpage = JGetTreePage(RootC, temp, leftpage);
						leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
						searchflag = 0;
						filepage = 1;
						*/
						;
					}
					else
					{
						if (change && (change->file.attrib & 0x10) || change->flag == 2)
						{
							temp->treeResponseFlag = 1;
							if (temp->file.attrib & 0x10 || temp->flag == 2)
							{
								JBuildTree(temp);
							}
							//Jfreetree(RootC);
							change = NULL;
							if (temp->child == NULL && (temp->file.attrib & 0x10 || temp->flag == 2))
							{
								dir = GetDir(temp);
								Fileini(dir, temp);
								free(dir);
							}
							//leftpage = JGetTreePage(RootC, temp, leftpage);
							leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
							pagemax = ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, filepage, showmode);
							tempback = JPushBack(tempback, temp);
							filepage = 1;//进入新的一级文件夹之后归零
						}
					}
				}
				dakaiflag=0;
				tool=NULL;
				delay(300);
			}
			/************************
			13.left page-----------
				************************/
			if (mouse_press(25, 445, 55, 460) == 1&&searchflag==0)//left page--
			{
				leftarrow(30, 448, 1);
				rightarrow(120, 448, 1);
				leftpage--;
				if (leftpage <= 0)
				{
					leftpage = 1;
				}
				else
				{
					leftpage=ZFileUnitLeft(RootC, 1, 92, leftpage);
				}
				delay(200);
				
			}
			/************************
			14 left page ++++++++++LEFT
				************************/
			if (mouse_press(95, 445, 125, 460) == 1&&searchflag==0)//left page ++
			{
				leftarrow(30, 448, 1);
				rightarrow(120, 448, 1);
				leftpage++;
				leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
				delay(200);
			}
				/************************
			15. left page  OPEN!!!
				************************/
			if (mouse_press(1,92,149,459)==1&&searchflag==0)//文件树
			{
				leftarrow(30, 448, 1);
				rightarrow(120, 448, 1);
				Jtreeflag = treemouseknowwhere();
				if (Jtreeflag)
				{
					useless=JGetTreeFolderNum(RootC, Jtreeflag+12* (leftpage-1), &Jtree);
					if (Jtree)
					{
						if (JChecktreefolder(Jtree))
						{
							if (Jtree->treeflag == 1)
							{
								if (Jtree->child != NULL)
								{
									JDFlag(Jtree->child);
								}
								Jtree->treeflag = 0;
							}
							else
							{
								JBuildTree(Jtree);
							}
						}

						if (Jtree->child == NULL&&Jtree->flag!=2&&Jtree->flag!=3)
						{
							dir = GetDir(Jtree);
							Fileini(dir, Jtree);
							free(dir);
						}
						temp = Jtree;//没建树，没有后退
						temp->treeResponseFlag = 1;
						Jtree = NULL;
						if(temp->flag!=2&&temp->flag!=3)
						{
							;//Jfreetree(RootC);
						}
						leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
						pagemax = ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, filepage, showmode);
						JFreeBack(tempback);
						tempback = headback;
						Jtreeflag = 0;
					}
				}
				
			}
				/************************
			16. DBPRESS!
			 
			 SINGLEPRESS!
				************************/
			if (mouse_press(RIGHTSTARTX, RIGHTSTARTY, 639, 459) == 1&&searchflag==0)//鼠标单双击反馈
			{
				delay(50);
				if (mouse_press(RIGHTSTARTX, RIGHTSTARTY, 639, 459) == 2)
				{
					delay(50);
					if (mouse_press(RIGHTSTARTX, RIGHTSTARTY, 639, 459) == 1)//if doubleclick
					{
						clrmous(MouseX,MouseY);
						mousewhere = 0;
						if (showmode == 1)
						{
							mousewhere = smallknowwhere();
						}
						else if (showmode == 2)
						{
							mousewhere = bigknowwhere();
						}
						if (mousewhere != 0)
						{
								if (getfilenumer(temp->child) >= mousewhere + (filepage - 1) * 12)
								{
									delay(30);
									clrmous(MouseX, MouseY);
									change = temp->child;
									while (change != NULL)
									{
										change->responseFlag = 0;
										change = change->brother;
									}
									change = temp->child;
									for (i = 0; i < mousewhere + (filepage - 1) * 12 - 1; i++)
									{
										if (change == NULL)
											{break;}
										change = change->brother;
									}
									if (change)
									{
										change->responseFlag = 1;
										pagemax = ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, filepage, showmode);
									}
									if (change&& (change->file.attrib & 0x10)||change->flag==2)
									{	
										temp = change;
										temp->treeResponseFlag = 1;
										if (temp->file.attrib & 0x10 || temp->flag == 2)
										{
											JBuildTree(temp);
										}
										//Jfreetree(RootC);
										change = NULL;
										if (temp->child==NULL&&(temp->file.attrib & 0x10)&& temp->flag != 2&& temp->flag != 3)
										{
											dir = GetDir(temp);
											Fileini(dir, temp);
											free(dir);
										}
										leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
										pagemax = ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, filepage, showmode);
										tempback = JPushBack(tempback, temp);
										filepage = 1;//进入新的一级文件夹之后归零
									}
									
								}
						}
						delay(200);
					}
					else if(mouse_press(RIGHTSTARTX, RIGHTSTARTY, 639, 459) == 2)//if、singleclick
					{
						mousewhere = 0;
						if (showmode == 1)
						{
							mousewhere = djsmallknowwhere();
						}
						else if (showmode == 2)
						{
							mousewhere = djbigknowwhere();
						}
						if (mousewhere != 0)
						{
								
									if (getfilenumer(temp->child) >= mousewhere + (filepage - 1) * 12)
									{
										delay(30);
										clrmous(MouseX, MouseY);
										change = temp->child;
										while (change != NULL)
										{
											change->responseFlag = 0;
											change = change->brother;
										}
										change = temp->child;
										for (i = 0; i < mousewhere + (filepage - 1) * 12 - 1; i++)
										{
											change = change->brother;
										}
										change->responseFlag = 1;
										if ((change && (change->file.attrib & 0x10) || change->flag == 2))//if click folder do left
										{
											change->treeResponseFlag = 1;
											leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
										}
										//如果mousewhere变量得到了非零的值，那么改变背景色参数responseflag
										pagemax = ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, filepage, showmode);//重新画图，得到背景色。
									}
								
						}
						delay(200);
					}
				
				
				}
			}
				/************************
			17 SORT BY name______2,3
				************************/
			if ((mouse_press(150,90,300,110) == 1||paixuflag==1)&&searchflag!=1)//名称排序功能
			{
				delay(100);
				clrmous(MouseX,MouseY);
				if (sortflag==2)
				{
					sortflag = 3;
				}
				else if (sortflag == 3)
				{
					sortflag = 2;
				}
				else
				{
					sortflag = 2;
				}
				paixuflag=0;
				JSort(temp,sortflag);
				pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);
				leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
				newmouse(&MouseX,&MouseY,&press);
				delay(300);

			}/************************
			18 SORT BY TIME______4,5
				************************/
			if (mouse_press(301,90,470,110) == 1&&searchflag==0)//修改日期排序功能
			{
				delay(100);
				clrmous(MouseX,MouseY);
				if (sortflag == 4)
				{
					sortflag = 5;
				}
				else if (sortflag == 5)
				{
					sortflag = 4;
				}
				else
				{
					sortflag = 4;
				}
				JSort(temp,sortflag);
				pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);
				leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
				newmouse(&MouseX,&MouseY,&press);
				delay(300);
			}
			/************************
			19 SORT BY TYPE______8,9
				************************/
			if (mouse_press(471,90,550,110) == 1&&searchflag!=1)//文件类型排序功能
			{
				delay(100);
				clrmous(MouseX,MouseY);
				if (sortflag == 8)
				{
					sortflag = 9;
				}
				else if (sortflag == 9)
				{
					sortflag = 8;
				}
				else
				{
					sortflag = 8;
				}
				JSort(temp,sortflag);
				pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);
				leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
				newmouse(&MouseX,&MouseY,&press);
				delay(300);
			}
			/************************
			20 SORT BY SIZE______6,7
				************************/
			if (mouse_press(551,90,639,110) == 1&&searchflag!=1)//大小排序功能
			{
				if (sortflag == 6)
				{
					sortflag = 7;
				}
				else if (sortflag == 7)
				{
					sortflag = 6;
				}
				else
				{
					sortflag = 6;
				}
				delay(100);
				clrmous(MouseX,MouseY);
				JSort(temp,sortflag);
				pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);
				leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
				newmouse(&MouseX,&MouseY,&press);
				delay(300);
			}/************************
			21rename  RENAME
				************************/
			if((mouse_press(320,30,380,60)==1||chongmingmingflag==1)&&temp!=RootC\
			&& ifonlyoneselected(temp)==1 &&searchflag == 0)//重命名
			{
				clrmous(MouseX,MouseY);
				rectangle(430,5,540,28);
				chongmingmingchar=GetString(430,5,80,chongmingmingchar);
				JReName(temp, chongmingmingchar);
				JSort(temp, sortflag);
				pagemax = ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, filepage, showmode);
				leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
				chongmingmingflag=0;
				chongmingmingchar=NULL;
			}
			/************************
			22 new FOLDER
				************************/
			if((mouse_press(1,0,90,29)==1||xinjianflag==1)&&temp!=RootC && searchflag == 0)//NEW FOLDER
			{
				clrmous(MouseX,MouseY);
				rectangle(430,5,540,28);
				xinjianchar=GetString(430,5,80,xinjianchar);
				if (JCreatFile(temp, "DIR", xinjianchar) == 0){;}
				JSort(temp, sortflag);
				pagemax = ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, filepage, showmode);
				leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
				xinjianflag=0;
				xinjianchar=NULL;
			}
			/************************
			23 new FILE
				************************/
			if(mouse_press(115,0,190,29)==1&&temp!=RootC && searchflag == 0)//NEW FILE
			{
				clrmous(MouseX,MouseY);
				rectangle(430,5,540,28);
				xinjianchar=GetString(430,5,80,xinjianchar);
				if (JCreatFile(temp, "TXT", xinjianchar) == 0){;}
				JSort(temp, sortflag);
				pagemax = ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, filepage, showmode);
				leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
				xinjianchar=NULL;
			}/************************
			24  delete SHANCHU
				************************/			
			if((mouse_press(245,30,320,60)==1||shanchuflag==1)&&ifselected==1&&  temp != RootC && searchflag == 0)//删除
			{
				clrmous(MouseX, MouseY);
				quedingshanchuflag=areyousure();
				if(quedingshanchuflag==1)
				{
					puthz(200, 8, "删除中，请稍候！", 16, 16, RED);//输入汉字
					JDeletemain(temp,&head);
					JSort(temp, sortflag);
					setcolor(DARKGRAY);
					pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);
					setfillstyle(1, WHITE);
					bar(190, 1, 190 + 16 * 16, 29);//190+（汉字个数+1）*16
					
				}
				shanchuflag=0;
				quedingshanchuflag=0;
				pagemax = ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, filepage, showmode);
				leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
			}
			/************************
			25 FUZHI  copyCOPY
				************************/
			if ((mouse_press(0, 30, 40, 60) == 1||fuzhiflag==1) && ifselected == 1 &&  temp != RootC && searchflag == 0)//复制
			{
				clrmous(MouseX, MouseY);
				JCopy(&head, temp, 0);
				JSort(temp, sortflag);
				pagemax = ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, filepage, showmode);
				leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
				delay(30);
				fuzhiflag=0;
			}
			/************************
			26 stickSTICK zhantie
				************************/
			if( (mouse_press(80, 30, 120, 60) == 1 ||zhantieflag==1)&&  temp != RootC && head->next != NULL && searchflag == 0)//粘贴
			{
				delay(100);
				clrmous(MouseX, MouseY);
				puthz(200,8,"已粘贴",16,16,DARKGRAY);
				puthz(283, 8, "个文件", 16, 16, DARKGRAY);
				JStick(head, temp);//总粘贴循环
				JSort(temp, sortflag);
				pagemax = ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, filepage, showmode);
				leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
				setfillstyle(1, WHITE);
				bar(190, 1, 190 + 16 * 20, 29);//190+（汉字个数+1）*16
				delay(100);
				zhantieflag=0;
			}
			/************************
			27 JIANQIE  CUTCUT
				************************/
			if ((mouse_press(160, 30, 200, 60) == 1||jianqieflag==1)\
			&& ifselected == 1 && temp != RootC && searchflag == 0)//剪切
			{
				clrmous(MouseX, MouseY);
				JCopy(&head, temp, 1);
				JSort(temp, sortflag);
				pagemax = ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, filepage, showmode);
				leftpage = ZFileUnitLeft(RootC, 1, 92, leftpage);
				delay(30);
				jianqieflag=0;
			}/************************
			28select ALL    QUANXUAN
				************************/
			if(mouse_press(400,30,440,60)==1 && searchflag == 0)//全选
			{
				clrmous(MouseX,MouseY);
				tool=temp;
				temp = temp->child;
				while(temp != NULL)
				{
					temp -> responseFlag=1;
					temp = temp->brother;
				}
				temp=tool;
				tool=NULL;
				pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);
				delay(30);

			}
			/************************
			29 QUXIAO  NO SELECT
				************************/
			if(mouse_press(480,30,520,60)==1 && searchflag == 0)//取消
			{		
				clrmous(MouseX,MouseY);
				tool=temp;
				temp = temp->child;
				while(temp != NULL)
				{
					temp -> responseFlag=0;
					temp = temp->brother;
				}
				temp=tool;
				tool=NULL;
				pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);
				delay(30);

			}
			/************************
			30 ANTI SELECT fanxuan
				************************/
			if(mouse_press(560,30,600,60)==1 && searchflag == 0)//反选
			{
				clrmous(MouseX,MouseY);
				tool=temp;
				temp = temp->child;
				while(temp != NULL)
				{
					if(temp -> responseFlag==0)
					{
						temp -> responseFlag++;
					}
					else if(temp -> responseFlag==1)
					{
						temp -> responseFlag--;
					}
					temp = temp->brother;
				}	
				temp=tool;
				tool=NULL;	
				pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);
				delay(100);
			}
			/************************
			31 GIVE COLOR!!
				************************/
			if(mouse_press(1,0,90,29)==2&&alreadyxjwjj==0 && temp != RootC && searchflag == 0)//新建文件夹
			{//FOLDER 31
				clrmous(MouseX,MouseY);
				setfillstyle(1,11);
				bar(1,0,90,29);
				puthz(5,8,"新建文件夹",16,16,LIGHTGRAY);
				alreadyxjwjj=1;
			}
			if(mouse_press(115,0,190,29)==2&&alreadyxjwbwj==0 && temp != RootC && searchflag == 0)//新建文本文件
			{//FILE 31
				clrmous(MouseX,MouseY);
				setfillstyle(1,11);
				bar(110,0,190,29);
				puthz(112,8,"新建文件",16,16,LIGHTGRAY);
				alreadyxjwbwj=1;
			}
			if(mouse_press(245,30,320,60)==2&&ifselected==1&&alreadysc==0&&temp!=RootC && searchflag == 0)//删除
			{//DELETE 31
				clrmous(MouseX,MouseY);
				setfillstyle(1,11);
				bar(243,32,285,58);
				puthz(245,38,"删除",16,16,LIGHTGRAY);	
				alreadysc=1;
			}
		
			if(mouse_press(400,30,440,60)==2&&alreadyqx==0 && searchflag == 0)//全选
			{//SELECT ALL 31
				clrmous(MouseX,MouseY);
				setfillstyle(1,11);
				bar(403,32,445,58);
				puthz(405,38,"全选",16,16,LIGHTGRAY);
				alreadyqx=1;
			}
			if(mouse_press(480,30,520,60)==2&&alreadyquxiao==0 && searchflag == 0)//取消
			{//NO SELECT31
				clrmous(MouseX,MouseY);
				setfillstyle(1,11);
				bar(483,32,525,58);
				puthz(485,38,"取消",16,16,LIGHTGRAY);
				alreadyquxiao=1;
			}
			if(mouse_press(560,30,600,60)==2&&alreadyfx==0 && searchflag == 0)//反选
			{// ANTI SELECT 31
				clrmous(MouseX,MouseY);
				setfillstyle(1,11);
				bar(563,32,605,58);
				puthz(565,38,"反选",16,16,LIGHTGRAY);
				alreadyfx=1;
			}
			if(mouse_press(0,30,40,60)==2&&ifselected==1&&alreadyfz==0&&temp!=RootC && searchflag == 0)//复制
			{// COPY 31
				clrmous(MouseX,MouseY);
				setfillstyle(1,11);
				bar(3,32,45,58);
				puthz(5,38,"复制",16,16,LIGHTGRAY);
				alreadyfz=1;
			}
			if(mouse_press(80,30,120,60)==2&&alreadyzt==0&&temp!=RootC && head->next != NULL && searchflag == 0)//粘贴
			{// STICK 31
				clrmous(MouseX,MouseY);
				setfillstyle(1,11);
				bar(83,32,125,58);
				puthz(85,38,"粘贴",16,16,LIGHTGRAY);
				alreadyzt=1;
			}
			if(mouse_press(160,30,200,60)==2&&ifselected==1&&alreadyjq==0&&temp!=RootC && searchflag == 0)//剪切
			{//CUT 31
				clrmous(MouseX,MouseY);
				setfillstyle(1,11);
				bar(163,32,205,58);
				puthz(165,38,"剪切",16,16,LIGHTGRAY);
				alreadyjq=1;
			}
			if(mouse_press(320,30,380,60)==2&&ifonlyoneselected(temp)==1 &&alreadycmm==0&&temp!=RootC && searchflag == 0)//重命名
			{// RENAME 31
				clrmous(MouseX,MouseY);
				setfillstyle(1,11);
				bar(321,32,385,58);
				puthz(322,38,"重命名",16,16,LIGHTGRAY);
				alreadycmm=1;
			}
			/************************
			32 NO COLOR!
				************************/
			ifselected=ifanyselected(temp);
			if(mouse_press(1,0,90,29)==0&&alreadyxjwjj==1)//新建文件夹&&temp!=RootC
			{//FOLDER 32
				clrmous(MouseX,MouseY);
				setfillstyle(1,WHITE);
				bar(1,0,90,29);
				puthz(5,8,"新建文件夹",16,16,LIGHTGRAY);
				alreadyxjwjj=0;
			}
			if(mouse_press(115,0,190,29)==0&&alreadyxjwbwj==1)//新建文本文件
			{//FILE 32
				clrmous(MouseX,MouseY);
				setfillstyle(1,WHITE);
				bar(110,0,190,29);
				puthz(112,8,"新建文件",16,16,LIGHTGRAY);
				alreadyxjwbwj=0;
			}
			if(mouse_press(245,30,320,60)==0&&alreadysc==1)//删除
			{// DELETE 32
				clrmous(MouseX,MouseY);
				setfillstyle(1,WHITE);
				bar(243,32,285,58);
				puthz(245,38,"删除",16,16,LIGHTGRAY);	
				alreadysc=0;
			}
		
			if(mouse_press(400,30,440,60)==0&&alreadyqx==1)//全选
			{//SELECT ALL 32
				clrmous(MouseX,MouseY);
				setfillstyle(1,WHITE);
				bar(403,32,445,58);
				puthz(405,38,"全选",16,16,LIGHTGRAY);
				alreadyqx=0;
			}
			if(mouse_press(480,30,520,60)==0&&alreadyquxiao==1)//取消
			{	// NO SELECT 32
				clrmous(MouseX,MouseY);
				setfillstyle(1,WHITE);
				bar(483,32,525,58);
				puthz(485,38,"取消",16,16,LIGHTGRAY);
				alreadyquxiao=0;
			}
			if(mouse_press(560,30,600,60)==0&&alreadyfx==1)//反选
			{// ANTI SELECT 32
				clrmous(MouseX,MouseY);
				setfillstyle(1,WHITE);
				bar(563,32,605,58);
				puthz(565,38,"反选",16,16,LIGHTGRAY);
				alreadyfx=0;
			}
			if(mouse_press(0,30,40,60)==0&&alreadyfz==1)//复制
			{//COPY 32
				clrmous(MouseX,MouseY);
				setfillstyle(1,WHITE);
				bar(3,32,45,58);
				puthz(5,38,"复制",16,16,LIGHTGRAY);
				alreadyfz=0;
			}
			if(mouse_press(80,30,120,60)==0&&alreadyzt==1&&head->next!=NULL)//粘贴
			{// STICK 32
				clrmous(MouseX,MouseY);
				setfillstyle(1,WHITE);
				bar(83,32,125,58);
				puthz(85,38,"粘贴",16,16,LIGHTGRAY);
				alreadyzt=0;
			}
			if(mouse_press(160,30,200,60)==0&&alreadyjq==1)//剪切
			{// CUT 32
				clrmous(MouseX,MouseY);
				setfillstyle(1,WHITE);
				bar(163,32,205,58);
				puthz(165,38,"剪切",16,16,LIGHTGRAY);
				alreadyjq=0;
			}
			if(mouse_press(320,30,380,60)==0&&alreadycmm==1)//重命名
			{//RENAME 32
				clrmous(MouseX,MouseY);
				setfillstyle(1,WHITE);
				bar(321,32,385,58);
				puthz(322,38,"重命名",16,16,LIGHTGRAY);
				alreadycmm=0;
			}
			/************************
		RIGHTCLICK
		RIGHTCLICK
				************************/
				/************************
			33 RIGHT FILE SMALL
				************************/
				if(mouse_press(RIGHTSTARTX,RIGHTSTARTY,560,458)==3&&showmode==1)//对文件点击右键，小图标
				{
					Rmousewhere=Rsmallknowwhere();//加上判断是否无文件！！！！
					youjianwhere=11;//判断右键在哪点击,1
					tempx=MouseX;
					tempy=MouseY;
					if (Rmousewhere != 0)
					{
						if(getfilenumer(temp->child)>=Rmousewhere+(filepage-1)*12)
						{
								delay(30);
								change=temp->child;
								while(change!=NULL)
								{
									change->responseFlag=0;
									change=change->brother;
								}
								change=temp->child;
								for(i=0;i<Rmousewhere+(filepage-1)*12-1;i++)
								{
									change=change->brother;
								}
								change->responseFlag=1;
								
						}
						else
						{
							youjianwhere=13;
						}
					}	
								
					pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);//重新画图，得到背景色。
					delay(30);
					Rmousewhere = 0;
					break;
					
				}
				/************************
			34 RIGHT BLANK SMALL
				************************/
				if(mouse_press(561,RIGHTSTARTY,639,459)==3&&showmode==1)//17.对点击空白区域右键，xiao图标
				{
					clrmous(MouseX,MouseY);
					youjianwhere=12;//判断右键在哪点击
					tempx=MouseX;
					tempy=MouseY;
					delay(30);
					break;
				}
				/************************
			35 RIGHT BIG
				************************/
					if(mouse_press(RIGHTSTARTX,RIGHTSTARTY,639,458)==3&&showmode==2)//16.点击右键,大图标
				{
					clrmous(MouseX,MouseY);
					Rmousewhere=Rbigknowwhere();
					if(Rmousewhere>0&&Rmousewhere<13)
					{
						youjianwhere=21;
						tempx=MouseX;
						tempy=MouseY;
						
						if(getfilenumer(temp->child)>=Rmousewhere+(filepage-1)*12)
						{
								delay(30);
								change=temp->child;
								while(change!=NULL)
								{
									change->responseFlag=0;
									change=change->brother;
								}
								change=temp->child;
								for(i=0;i<Rmousewhere+(filepage-1)*12-1;i++)
								{
									change=change->brother;
								}
								change->responseFlag=1;
								pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);//重新画图，得到背景色。
						}
						else
						{
							youjianwhere=23;//点击本来是文件的空白，大图标
						}
					
						break;
					}
					else if (Rmousewhere==999)
					{
						youjianwhere=22;
						tempx=MouseX;
						tempy=MouseY;
						break;
					}
				}
			/************************
	             END OF FIRST WHILE 
				************************/
		}
		//youjianwhere变量的含义：11,12为小图标模式下文件，空白；21,22为大图标模式下文件，13为小模式点击本该是文件的空白
		//rmousewhere的含义：在点击文件时获取12个分区的文件编号并+12*（filepage-1），大图标点击本来就是空白的空白为999
		area=getarea(tempx,tempy);//know where I rightclicked
		if(showmode==1&&youjianwhere!=13)//放在循环外保证画图只画一次
		{//除了点击本应是文件的空白
			if(youjianwhere==11)//small,file
			{
				if(area==1)
				{
					bigrightpressfilefirst(tempx,tempy);
				}
				if(area==2)
				{
					bigrightpressfilesecond(tempx,tempy);
				}
				if(area==3)
				{
					bigrightpressfilethird(tempx,tempy);
				}
				if(area==4)
				{
					bigrightpressfilefourth(tempx,tempy);
				}
			}
			else if(youjianwhere==12)//small,blank
			{
				if(area==4)
				{
					smallrightpressblankdrawup(tempx,tempy,showmode);
				}
				else if (area==1)
				{
					smallrightpressblankdrawdown(tempx,tempy,showmode);
				}
			}
		}
		else if(showmode==2||youjianwhere==13)
		{
			if(youjianwhere==21)
			{
				if(area==1)
				{
					bigrightpressfilefirst(tempx,tempy);
				}
				if(area==2)
				{
					bigrightpressfilesecond(tempx,tempy);
				}
				if(area==3)
				{
					bigrightpressfilethird(tempx,tempy);
				}
				if(area==4)
				{
					bigrightpressfilefourth(tempx,tempy);
				}
			}
			else if(youjianwhere==22||youjianwhere==13||youjianwhere==23)
			{
				if(area==1)
				{
					bigrightpressblankfirst(tempx,tempy,showmode);
				}
				if(area==2)
				{
					bigrightpressblanksecond(tempx,tempy,showmode);
				}
				if(area==3)
				{
					bigrightpressblankthird(tempx,tempy,showmode);
				}
				if(area==4)
				{
					bigrightpressblankfourth(tempx,tempy,showmode);
				}
			}
		}				
		while(1)//second while1
		{
			newmouse(&MouseX,&MouseY,&press);
			quit=quitornot(tempx,tempy,area);//第一种退出情况：左键单击非右键菜单处
			rightarea=getrightarea(area,tempx,tempy);//判断右键是否点击一级菜单
			if(rightarea!=0)//如果点击一级菜单  IF CLICKED
			{
				quit=1;//第二种退出情况：即将执行某一个右键功能
				if(youjianwhere==11||youjianwhere==21)//IF FILE如果是文件
				{
					if(rightarea==1)
					{
						dakaiflag=1;
						}
					if(rightarea==2)
					{
						fuzhiflag=1;
						}
					if(rightarea==3)
					{
						jianqieflag=1;
						}
					if(rightarea==4)
					{
						shanchuflag=1;
						}
					if(rightarea==5)
					{
						chongmingmingflag=1;
						}
					if(rightarea==6)
					{
						shuxingflag=2;
						}
				}
				else//如果是空白       IF BLANK
				{
					if(rightarea==1)
					{
						showmode++;
						if(showmode==3)
						{
							showmode=1;
						}
						if(showmode==1)//
						{
							setfillstyle(1,11);
							bar(605,464,625,479);
							detailmodeicon(610,465);
							setfillstyle(1,WHITE);
							bar(565,464,585,479);
							bigmodeicon(570,465);
						}
						else if(showmode==2)
						{
							setfillstyle(1,11);
							bar(565,464,585,479);
							bigmodeicon(570,465);
							setfillstyle(1,WHITE);
							bar(605,464,625,479);
							detailmodeicon(610,465);
						}
					}
					if(rightarea==2)
					{
						paixuflag=1;
					}
					if(rightarea==4)
					{
						zhantieflag=1;
					}
					if(rightarea==5)
					{
						xinjianflag=1;
					}
					if(rightarea==6)
					{
						shuxingflag=1;
					}
				}
			}	
				rightarea=0;//防止下次一进来就进入一级菜单判断
				if(quit==1)//判断是否应该返回第一个while
				{
					if(paixuflag==0)//如果排序就不重新画图。影响观感
					{
						pagemax=ZFileUnit(temp,RIGHTSTARTX,RIGHTSTARTY,filepage,showmode);//画出正常文件背景，覆盖右键，也是刷新功能
					}
					quit=0;
					delay(250);
					break;
				}
		}//2while
		if (shuxingflag == 1 || shuxingflag == 2)
		{
			showshuxing(temp, shuxingflag);
			shuxingflag = 0;
			pagemax = ZFileUnit(temp, RIGHTSTARTX, RIGHTSTARTY, filepage, showmode);//画出正常文件背景，覆盖属性，
			delay(250);
		}							
	}//zong de while
}//end of function
		
	/************************
		得知鼠标点击的位置处于哪个分区	
************************/
int getarea(int tempx,int tempy)
{			
			int area;
			if(tempy>=300)//判断象限
				{
					if(tempx>=400)
					{
						area=4;
					}
					else
					{
						area=3;
					}
				}
				else//判断象限
				{
					if(tempx>=400)
					{
						area=1;
					}
					else
					{
						area=2;
					}
				}
			return area;
}

/************************
		通过鼠标点击的位置判断是否返回第一个循环
************************/
int quitornot(tempx,tempy,area)//供第二个while循环使用，如果返回值为1就到第一个while循环
{
	
		if(area==1)
		{
			if(mouse_press(tempx,0,639,479)==1||mouse_press(0,0,tempx-105,479)==1||\
			mouse_press(tempx-105,0,tempx,tempy)==1||mouse_press(tempx-105,tempy+120,tempx,479)==1)//右键界面的退出
			{
				return 1;
			}
		}
		else if (area==2)
		{
			if(mouse_press(0,0,tempx,479)==1||mouse_press(tempx+105,0,639,479)==1||mouse_press(tempx,0,tempx+105,tempy)==1||\
			mouse_press(tempx,tempy+120,tempx+105,479)==1)//右键界面的退出
			{
				return 1;
			}
		}
		else if (area==3)
		{
			if(mouse_press(0,0,tempx,479)==1||mouse_press(tempx+105,0,639,479)==1||mouse_press(tempx,0,tempx+105,tempy-120)==1||\
			mouse_press(tempx,tempy,tempx+105,479)==1)//右键界面的退出
			{
				return 1;
			}
		}
		else if (area==4)
		{
			if(mouse_press(tempx,0,639,479)==1||mouse_press(0,0,tempx-105,479)==1||\
			mouse_press(tempx-105,tempy,tempx,479)==1||mouse_press(tempx-105,0,tempx,tempy-120)==1)//右键界面的退出
			{
				return 1;
			}
		}
		else
		{
			return 0;
		}	
	
}
/************************
	小模式，获取鼠标单击位置
************************/
int smallknowwhere()//功能：鼠标单击获取返回值
{
	int k=1;
	for(;k<=12;k++)
	{
		if (mouse_press(RIGHTSTARTX-2,RIGHTSTARTY+6+YGAP*(k-1),639,RIGHTSTARTY+6+YGAP*k)==1)
		{
			return k;
		}
	}
	return 0;
}
/************************
	大模式，获取鼠标单击位置
************************/
int bigknowwhere()//功能：鼠标单击获取返回值
{
		int k=1,m=1,returnnum;
		int gotnumber=0;
		for(;m<=4&&k<=3;m++)
		{
			if (mouse_press(158+(m-1)*117,118+(k-1)*110,253+(m-1)*117,217+(k-1)*110)==1)
			{
				returnnum=(k-1)*4+m;
				setfillstyle(1,11);
				gotnumber=1;
				return returnnum;
			}
			if(m==4)
			{
				m=0;
				k++;
			}
		}		
		return 0;
}
/************************
	小模式，获取鼠标！right右键单击位置
************************/
int Rsmallknowwhere()//功能：鼠标右键单击获取返回值
{
	int k=1;
	for(;k<=12;k++)
	{
		if (mouse_press(RIGHTSTARTX-2,RIGHTSTARTY+6+YGAP*(k-1),639,RIGHTSTARTY+6+YGAP*k)==3)
		{
			return k;
		}
		
	}
	return 0;
}
/************************
	大模式，获取鼠标！right右键单击位置
************************/
int Rbigknowwhere()//功能：鼠标右键单击获取返回值
{
		int k=1,m=1,returnnum;
		int gotnumber=0;
		for(;m<=4&&k<=3;m++)
		{
			if (mouse_press(158+(m-1)*117,118+(k-1)*110,253+(m-1)*117,217+(k-1)*110)==3)
			{
				returnnum=(k-1)*4+m;
				setfillstyle(1,11);
				gotnumber=1;
				return returnnum;
			}
			if(m==4)
			{
				m=0;
				k++;
			}
		}		
	if(gotnumber==0&&mouse_press(RIGHTSTARTX,RIGHTSTARTY,639,459)!=0)
	{
		return 999;
	}
	return 0;
}
int ifanyselected(Node* tempNode)//whether there are things selected
{
	int selected = 0;
	tempNode = tempNode->child;
	while(tempNode != NULL)
	{
		if(tempNode->responseFlag==1)
		{
			selected=1;
		}
		tempNode = tempNode->brother;
	}
	return selected;

}
int ifonlyoneselected(Node* tempNode)//whether only one selected
{
	int selected = 0;
	tempNode = tempNode->child;
	while(tempNode != NULL)
	{
		if(tempNode->responseFlag==1)
		{
			selected++;
		}
		tempNode = tempNode->brother;
	}
	if(selected==1)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}
/************************
	大模式，获取鼠标悬浮！位置
************************/
int djsmallknowwhere()//功能：鼠标悬浮获取返回值FLOAT
{
	int k=1;
	for(;k<=12;k++)
	{
		if (mouse_press(RIGHTSTARTX-2,RIGHTSTARTY+6+YGAP*(k-1),639,RIGHTSTARTY+6+YGAP*k)==2)
		{
			return k;
		}
	}
	return 0;
}
/************************
	大模式，获取鼠标悬浮！位置
************************/
int djbigknowwhere()//功能：鼠标悬浮获取返回值FLOAT
{
		int k=1,m=1,returnnum;
		int gotnumber=0;
		for(;m<=4&&k<=3;m++)
		{
			if (mouse_press(158+(m-1)*117,118+(k-1)*110,253+(m-1)*117,217+(k-1)*110)==2)
			{
				returnnum=(k-1)*4+m;
				setfillstyle(1,11);
				gotnumber=1;
				return returnnum;
			}
			if(m==4)
			{
				m=0;
				k++;
			}
		}		
		return 0;
}