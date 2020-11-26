/////////////////////////////////////////////////////////////////////   
//工程: 校运会管理系统  
//     描述:该文件定义了本项目所用到的所有的结构体和枚举类型，实现两个结构体之间的相互引用。 还有各种顺序表的初始化操作。
//     版本: 校运会系统2.0，
//	   完成日期：2020/4/29   
//     修改:删除itemgroup结构体。在sportitem中添加所有报名该项目的运动员名单和运动员分组名单。sportitem还添加了性别限制。  
/////////////////////////////////////////////////////////////////////  

#pragma once
#ifndef __ALLSTRUCT_H__
#define __ALLSTRUCT_H__ 
#endif

#define ITEMLIST_INIT_SIZE 30//项目表的初始大小
#define ITEMLIST_INCREASEMENT 5//项目表增量

#define ATHLETELIST_INIT_SIZE 100//运动员表的初始大小
#define ATHLETELIST_INCREASEMENT 10//运动员表增量

#define ACADEMYLIST_INIT_SIZE 10//参赛单位表的初始大小
#define ACADEMYLIST_INCREASEMENT 5//参赛单位表增量

#define RECORDLIST_INIT_SIZE 100//记录表的初始大小
#define RECORDLIST_INCREASEMENT 10//记录表增量

#define ATHLETE_MAX_ITEM 3 //运动员最多报名项目
#define MAX_ITEM_TIME 7//一个比赛组多的比赛次数

#define TITLELENGTH 100//程序封面的字

#define EXCEL_MAX_CHARONELINE 100   //表格一行最大字符数量
#define MAX_PLACE_NUMBER 30  //最多不同的比赛场地

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<conio.h>
#include<time.h>

#include"io.h"


typedef enum SPORTTYPE {
	SPORTTYPE_FIELD,//田赛
	SPORTTYPE_TRACK//径赛
}SPORTTYPE;

typedef enum GENDER {
	GENDER_MALE,//男性
	GENDER_FEMALE//女性
}GENDER;

//结构体提前声明，用来实现相互引用
struct SSportItem;
struct SItemList;

struct SAcademy;
struct SAcademyList;

struct SAthlete;
struct SAthleteList;

struct SItemRecord;
struct SRecordList;

typedef struct SSportItem {
	char szItemID[10];//项目编号
	char szItemName[25];//项目名称
	SPORTTYPE SPORTTYPE_itemtype;//项目类别
	GENDER GENDER_itemgender;//能参加项目运动员性别
	char szPlace[20];//场地
	double dItemTime;//耗时
	double dResult;//成绩,田赛需要6轮成绩.第一个元素用来存放成绩的个数
	int GroupNumber;//分组数量，在运动员报名之后实时更新
	SAthleteList *pAthleteList;//指向一个运动员列表，该列表存放着报名该项目的运动员名单
	SAthleteList **ppAthleteGroup;//指针数组，有GroupNumber个元素，每个元素都是指向运动员列表的指针,分组名单。
}SSportItem;

typedef struct SItemList {//动态存储结构顺序表
	SSportItem* pSItemList;//数组
	int nListLength;//顺序表实际长度
	int nListSize;//顺序表分配的内存
}SItemList;

typedef struct SAcademy {
	char szAcademyName[20];//参赛组织名称
	int score;//得分
}SAcademy;

typedef struct SAcademyList {
	SAcademy* pSAcademyList;
	int nListLength;
	int nListSize;
}SAcademyList;

typedef struct SAthlete {
	char szAthleteName[20];//姓名
	char szAthleteID[20];//学号
	GENDER GENDER_athleteGender;//性别
	int nSItemNumber;//报名项目数量
	SSportItem SAthleteItem[ATHLETE_MAX_ITEM];//最多报三个项目
	SAcademy academy;//参赛单位
}SAthlete;

typedef struct SAthleteList {
	SAthlete* pSAthleteList;
	int nListLength;
	int nListSize;
}SAthleteList;

typedef struct SItemRecord {
	char szRecordID[10];//记录编号
	char szRecordName[20];//纪录的项目名称
	double dRecordResult;//纪录成绩
	char szAthleteName[20];//纪录保持者姓名
	GENDER AthleteGender;//纪录保持者性别 
}SItemRecord;

typedef struct SRecordList {
	SItemRecord* pSRecordList;
	int nListLength;  //实际长度 
	int nListSize;
}SRecordList;

//初始化项目表
void InitItemList(SItemList& SList);
//初始化运动员表
void InitAthleteList(SAthleteList& SList);
//初始化径赛单位表
void InitAcademyList(SAcademyList& SList);
//初始化记录表
void InitRecordList(SRecordList& SList);

///////////////////////////////////
//创建一个项目，输入相关信息
void CreateItem(SSportItem& SItem);
//显示项目信息
void DisplayItem(SSportItem& SItem, int withTitle);
//显示项目列表
void DisplayItemList(const SItemList& SList);
//清空项目列表
void ClearItemList(SItemList& SList);
//销毁项目列表
void DestroyItemList(SItemList& SList);
//定位项目再项目列表中的位置
int LocateItem(SItemList& SList, char szItemIDorName[]);
//添加项目到项目列表中
int AddItem(SItemList& SList, SSportItem SItem);
//删除项目列表中的项目。
int DeleteItem(SItemList& SList, char szItemIDorName[]);
//修改项目列表中某个项目
int ModifiItem(SItemList& SList, char szItemIDorName[]);
//将项目列表写入文件中
int WriteItemListFile(SItemList& SList);
//从文件中读取项目列表
int ReadItemListFile(SItemList& SList);
//对某个项目的报名表进行分组
int Grouping(SItemList& SList);
//将项目列表中所有的分组按照成绩进行排序。
void Ordering(SItemList& SList);
//分页显示某个项目所有的分组情况
int DisplayGroupingPagination(SSportItem& SItem);
//分页显示某个项目的分组请开给你，函数中有三个选项，1.上一页 2.下一页，3.返回。其中第三个可能是其他。而且这个分组最上面的标题也可能是其他，所以把这部分作为参数传入函数中
int DisplayGroupingPagination(SSportItem& SItem, const char* szTitle,const char* szThirdChoice);
//显示第n组（从1开始）
void DisplayNGroup(SSportItem& SItem, int n);
//分页显示项目
void DisplayItemListPagination(const SItemList& SList, int page, int NumberPerPage);
//////////////////////////////////

//输入运动员信息
void InputAthleteInfo(SAthlete& SAthle);
//清空运动员列表
void ClearAthleteList(SAthleteList& SList);
//销毁运动员列表
void DestroyAthleteList(SAthleteList& SList);
//显示运动员信息
void DisplayAthleteInfo(const SAthlete& SAthle, int withTitle);
//显示运动员列表信息
void DisplayAthleteListInfo(const SAthleteList& SList);
//分页显示运动员列表，只显示第page页，然后每页NumberPerPage个
void DisplayAthleteListInfo(const SAthleteList& SList, int page, int NumberPerPage);
//分页显示运动员列表，每页NumberPerPage个。提供换页功能
void DisplayAthleteListPagination(const SAthleteList& SList, int nNumberPerPage);
//找到某个运动员在运动员列表中的位置
int LocateAthlete(SAthleteList& SList, char szAthleteIDorName[]);
//添加运动员到运动员列表中
int AddAthlete(SAthleteList& SList, SAthlete SAthle);
//删除运动员列表中的某个运动员，且不同步到报名表中。
int DeleteAthlete(SAthleteList& SList, char szAthleteIDorName[]);
//删除运动员列表中某个运动员,且同步到项目报名表中
int DeleteAthleteSync(SAthleteList& SList, char szAthleteIDorName[]);
//删除运动员列表中某个位置的运动员,且同步到项目报名表中
int DeleteAthleteSync(SAthleteList& SList, int nPos_athlete);
//找到某个项目在某个运动员中的位置
int LocateAthleteItem(SAthlete& SAthle, char szItemIDorName[]);
//删除某个运动员报名项目中的某个项目
int DeleteAthleteItem(SAthlete& SAthle, char szItemIDorName[]);
//为某个运动员添加某个项目
int AddAthleteItem(SAthlete& SAthle, SSportItem SItem);
//修改某个运动员的信息
int ModifiAthlete(SAthleteList& SList, char szAthleteIDorName[]);
//将运动员列表写入文件
int WriteAthleteListFile(SAthleteList& SList);
//从文件中读取运动员列表的信息
int ReadAthleteListFile(SAthleteList& SList);
//同步数据
void AthleteSync(SAthlete& athlete);
//将某个运动员中SAthle.SAthleteItem[n]替换成SItem.然后实现报名表中的同步数据
int ReplaceAthleteItem(SAthlete& SAthle, SSportItem SItem, int n);

///////////////////////////////////
//创建新的参赛单位
void CreateAcademy(SAcademy& academy);
//清空参赛单位列表
void ClearAcademyList(SAcademyList& SList);
//销毁参赛单位列表
void DestroyAcademyList(SAcademyList& SList);
//得到某个参赛单位在参赛单位列表中的位置
int LocateAcademy(SAcademyList& SList, char szAcademyName[]);
//添加参赛单位到参赛单位列表中
int  AddAcademy(SAcademyList& SList, SAcademy academy);
//从参赛单位列表中删除某个参赛单位
int DeleteAcademy(SAcademyList& SList, char* szAcademyName);
//在参赛单位列表中修改某个参赛单位
int ModifyAcademy(SAcademyList& SList, char* szAcademyName);
//显示参赛单位列表中的参赛单位
void DisplayAcademyList(SAcademyList& SList);
//将参赛单位列表的信息写入到文件中
int WriteAcademyListFile(SAcademyList& SList);
//从文件中读取现有参赛单位的信息。
int ReadAcademyListFile(SAcademyList& SList);
////////////////////////////////////

//将密码加密的写入文件中
void WritePasswordtoFile(char password[]);
//将密码解密读出文件
char* ReadPasswordfromFile();

////////批量增加
//打印从excel中读出来的运动员信息
void PrintAthleteInfo(SAthlete SAthle);
//从excel中作为字符串读出某一行，然后把这一行字符串分开成若干份复制到SAthle结构体中
void DivideLine(SAthlete& SAthle, char szLine[EXCEL_MAX_CHARONELINE]);
//从excel中读取
void ReadExcel();
////////


///业务逻辑
//项目管理
void ItemManagement();
//运动员管理
void AthleteManagement();
//参赛单位管理
void AcademyManagement();
//成绩管理
void GradeManagament();
//系统设置管理
void SystemManagement(bool&pwdFlag, char* szTitle);
//秩序册管理
void ProgramManagement();

//系统初始化
void SystemInit(bool& pwd, char* szTitle, int n);