#pragma once
#include"allstruct.h"

//================
//功能：初始化运动员列表
//参数：SList
//	SList:运动员列表（SAthleteList类型）
//思路：将为动态顺序表分配内存
//修改日期：2020/5/2
//================
void InitAthleteList(SAthleteList& SList);

//================
//功能：在运动员列表SList末尾处添加运动员SAthle.
//参数：SList,SAthle
//	SList:运动员列表(SAthleteList)
//	SAthle:运动员(SAthlete)
//返回：添加成功返回0
//            若运动员已存在列表中返回-1
//思路：找到末尾的位置，将结构体SAthle赋值到该位置。
//修改日期：2020/3/17/12：32
//================
int AddAthlete(SAthleteList& SList, SAthlete SAthle);

//==========
//功能：清空运动员表SList
//实现：将SList.nLength赋值为0
//==========
void ClearAthleteList(SAthleteList& SList);

//==========
//功能：销毁运动员列表
//实现：将分配的空间释放
//==========
void DestroyAthleteList(SAthleteList& SList);

//==========
//功能：让用户为运动员SAthle输入基本信息，输入信息的同时，将这个运动员加入到报名的项目报名表中
//注意：函数结束时，SAthle还没有加入到总的运动员列表中。
//            InputAthleteInfo(SAthle);//这三个函数一定要一起放，才能够实现运动员文件和项目文件的数据同步！
//            AddAthlete(allathlete,SAthle);//allathlete是包含所有运动员的运动员列表
//            WriteAthleteListFile(allathlete);//写入文件中
//==========
void InputAthleteInfo(SAthlete& SAthle);

//==========
//功能：用表格的形式在dos中输出某个运动员的信息
//参数：SAthle，withTitle
//	SAthle:运动员的结构（SAthlete类型）
//	withTitle:为真时,将表格有表格头（写属性名的那行）
//			  为假时，不带表头
//==========
void DisplayAthleteInfo(const SAthlete& SAthle, int withTitle);

//================
//功能：在dos上显示运动员列表SList中所有运动员的信息
//参数：SList
//	SList:运动员列表（SAthleteList类型）
//思路：用于测试后续函数是否功能正常
//================
void DisplayAthleteListInfo(const SAthleteList& SList);

//================
//功能：分页显示运动员列表中的内容，该函数只显示page页的内容，每页最多有NumberPerPage个元素
//参数：SList，page,NumberPerPage
//	SList:运动员列表（SAthleteList类型）
//	page:页数
//	NumberPerPage:每页中最多的行数
//================
void DisplayAthleteListInfo(const SAthleteList& SList, int page, int NumberPerPage);

//================
//功能：分页显示运动员列表中的额内容，该函数可以输入1，2实现上一页下一页的功能。
//      该函数会卡住直到用户输入3.返回才会继续进行下面
//参数：SList，nNumberPerPage
//	SList:运动员列表
//	nNumberPerPage:每组最多的行数
//================
void DisplayAthleteListPagination(const SAthleteList& SList, int nNumberPerPage);

//================
//功能：通过运动员的ID或者姓名，返回运动员在运动员列表SList中的位置
//参数：SList，szAthleteIDorName[]
//	SList:运动员列表（SAthleteList类型）
//	szAthleteIDorName[]:字符串，可以是运动员的ID或者姓名
//返回：找到：返回名字或ID为szAthleteIDorName的运动员在列表SList中的下标，下标从0开始
//            找不到：返回-1
//================
int LocateAthlete(SAthleteList& SList, char szAthleteIDorName[]);

//================
//功能：在运动员列表SList中删除 名字或学号为szAthleteIDorName[]的运动员
//参数：SList,szAthleteIDorName[]
//	SList:运动员列表
//	szAthleteIDorName[]:字符串，代表要删除的运动员的姓名或者编号
//返回：删除成功返回0
//            列表中不存在该运动员返回-1；
//================
int DeleteAthlete(SAthleteList& SList, char szAthleteIDorName[]);

//================
//功能：通常是在运动员总表中删除某个运动员，并且将项目报名表中的关于这个运动员的信息也删除
//参数：SList,szAthleteIDorName[]
//	SList:运动员总表（要写入文件的运动员表）
//	szAthleteIDorName[]：这个运动员的名字或者学号
//================
int DeleteAthleteSync(SAthleteList& SList, char szAthleteIDorName[]);

//================
//功能：通常是在运动员总表中删除某个运动员，并且将项目报名表中的关于这个运动员的信息也删除
//参数：SList,nPos_athlete
//	SList:运动员总表（要写入文件的运动员表）
//	nPos_athlete:该名运动员在运动员总表中的位置
//注意：和int DeleteAthleteSync(SAthleteList& SList, char szAthleteIDorName[])实现的功能是一样的，只不过参数不同
//================
int DeleteAthleteSync(SAthleteList& SList, int nPos_athlete);

//================
//功能：返回运动员SAthle中项目名或者编号为szItemIDorName的项目在SAthle.SAthleteItem[]中的位置。
//参数：SAthle,szItemIDorName[]
//	SAthle:运动员
//	szItemIDorName[]:字符串，项目的名称或者编号
//返回：找到：返回项目在运动员所选的项目中的位置
//            找不到：返回-1
//================
int LocateAthleteItem(SAthlete& SAthle, char szItemIDorName[]);

//================
//功能：SAthle运动员报名的三个项目中，如果存在一个名或ID为szItemIDorName的项目，则将这个项目删除。
//参数：SAthle,szItemIDorName[]
//返回：删除成功返回0
//           该名运动员没有选这个项目，则返回-1
//================
int DeleteAthleteItem(SAthlete& SAthle, char szItemIDorName[]);

//================
//功能：SAthle运动员新增报名SItem.并将SAthle的信息添加到项目的报名表中
//参数：SAthle，SItem
//	SAthle：要添加项目的运动员
//	SItem：//要添加的项目
//返回：如果该名运动员所报项目已达上限，或者已经报了这个项目，或者这个项目不存在，一律返回-1
//	如果添加成功返回0
//================
int AddAthleteItem(SAthlete& SAthle, SSportItem SItem);

//================
//功能：修改运动员列表SList中名字或者编号为szAthleteIDorName[]的运动员的信息，修改后把项目报名表中该名运动员的信息更新
//参数：SList，szAthleteIDorName[]
//	SList:运动员列表
//	szAthleteIDorName[]:字符串，代表需要修改的运动员你的名字或者编号
//返回：修改成功返回0
//            列表中找不到运动员返回-1
//================
int ModifiAthlete(SAthleteList& SList, char szAthleteIDorName[]);

//================
//功能：将运动员列表的信息写入文件athleteinfo.txt中.（打开文件的mode："w"）
//参数：SList
//	SList:运动员列表
//返回：写入成功返回0
//危险：在调用这个函数之后，athleteinfo.txt会被覆盖，所以应该使用ReadAthleteListFile将文件内容读取到程序中后，完成需要的操作后再把SList写入到文件中。
//================
int WriteAthleteListFile(SAthleteList& SList);

//================
//功能：将文件athleteinfo.txt中的运动员信息读取到SList运动员列表中（打开文件的mode："r"）
//参数：SList（出口参数）
//	SList：运动员列表，用来承载文件中运动员信息
//返回：读取成功返回0
//================
int ReadAthleteListFile(SAthleteList& SList);


//==============
//功能：当修改运动员的基本信息时，将这些信息同步到项目的报名表中，
//参数：athlete
//	athlete:修改了信息的运动员
//注意：为了保证运动员表和项目报名表的信息同步，需要每次修改运动员信息（每次只能修改ID或者Name中的一个）的时候调用该函数，将其同步到项目报名表中
//==============
void AthleteSync(SAthlete& athlete);

//==============
//功能：将某个运动员中SAthle.SAthleteItem[n]替换成SItem.然后实现报名表中的同步数据
//参数：SAthle,SItem,n
//	SAthle:运动员
//	SItem:用来替换的项目
//	n:被替换项目的下标
//==============
int ReplaceAthleteItem(SAthlete& SAthle, SSportItem SItem, int n);




//==============
//功能：运动员的增删改查，运动员管理
//==============
void AthleteManagement();