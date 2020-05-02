////////////////////////////////////////////
//文件说明
//工程：MyCampusSportSystem
//作者：李嘉浩
//描述：该文件提供和运动员表增删，运动员信息的增删改查，运动员信息的文件读写更新相关的操作
//主要函数：
//			void InitAthleteList(SAthleteList& SList)//初始化运动员表
//			void DestroyAthleteList(SAthleteList& SList)//销毁运动员表
//			int AddAthlete(SAthleteList& SList, SAthlete SAthle)//运动员表的元素增加操作
//			int DeleteAthlete(SAthleteList& SList, char szAthleteIDorName[])//运动员表的元素删除操作
//			int ModifiAthlete(SAthleteList& SList, char szAthleteIDorName[])//运动员表中元素信息的修改操作
//			int WriteAthleteListFile(SAthleteList& SList)//运动员信息写入athleteinfo.txt
//			int ReadAthleteListFile(SAthleteList& SList)//在athleteinfo.txt中读取运动员信息
//			void AthleteFIlEUpdate_ItemModify(SSportItem& SItem)//当项目信息修改时，althleteinfo.txt的信息更新操作
//			void AthleteFILEUpdate_ItemDelete(char szItemIDorName[])//当项目信息删除时，althleteinfo.txt的信息更新操作。
//完成日期：2020/3/18 /12：26
/////////////////////////////////////////////

#pragma once

#ifndef __athlete_H__
#define __athlete_H__
#endif

#include<stdio.h>
#include<iostream>

#include "sportitem.h"

using namespace std;

#define MAXATHLETESIZE 200 //运动员顺序表初始分配长度
#define INCREASEATHLETESIZE 10 //运动员顺序表满后增加的长度
#define ACADEMYNUMBER 9 //书院个数(参赛单位数量)

//运动员所属书院。
typedef enum Academy {
	知行书院=1,
	思源书院,
	弘毅书院,
	敬一书院,
	至诚书院,
	修远书院,
	明德书院,
	德馨书院,
	研究生院
}Academy;

//性别
typedef enum Gender {
	GENDER_FEMALE,//女性
	GENDER_MALE//男性
}Gender;

//运动员结构，其内容为运动员的基本信息
typedef struct SAthlete {
	char szAthleteName[20];
	char szAthleteID[20];
	Gender AthleteGender;
	int nSItemNumber;
	SSportItem SAthleteItem[3];//最多报三个项目
	Academy academy;
}SAthlete;

//运动员列表，其元素为SAthlete类型的数据
typedef struct SAthleteList {
	SAthlete* pSAthleteList;
	int nListLength;
	int nListSize;
}SAthleteList;

//================
//功能：初始化运动员列表
//参数：SList
//	SList:运动员列表（SAthleteList类型）
//思路：将为动态顺序表分配内存，将nListLength赋值为0;
//修改日期：2020/3/17/11：54
//================
void InitAthleteList(SAthleteList& SList);

//================
//功能：销毁运动员列表
//参数：SList
//	SList:运动员列表
//思路：释放动态分配的内存，并把长度和大小设置为0
//修改日期：2020/3/17/11：56
//================
void DestroyAthleteList(SAthleteList& SList);

//================
//功能：在dos输入运动员SAthle的信息
//参数：SAthle
//	SAthle:运动员的结构（SAthlete类型）
//思路：在dos输入，用于测试其他函数是否正常
//修改日期：2020/3/17/11：58
//================
void InputAthleteInfo(SAthlete& SAthle);

//================
//功能：在dos上显示运动员SAthle所选项目SAthle.SAthleteItem[3]的信息。
//参数：SAthle
//	SAthle:运动员的结构（SAthlete类型）
//思路：用于测试后续函数是否正常
//修改日期：2020/3/17/12：01
//================
void DisplayAthleteItem(const SAthlete& SAthle);

//================
//功能：在dos上显示运动员SAthle的所有信息
//参数：SAthle
//	SAthle:运动员结构（SAthlete类型）
//思路：用于测试后续函数是否功能正常
//修改：2020/3/17/12：03
//================
void DisplayAthleteInfo(const SAthlete& SAthle);

//================
//功能：在dos上显示运动员列表SList中所有运动员的信息
//参数：SList
//	SList:运动员列表（SAthleteList类型）
//思路：用于测试后续函数是否功能正常
//修改：2020/3/17/12：05
//================
void DisplayAthleteListInfo(const SAthleteList& SList);

//==================
//功能：将运动员列表的信息分开若干组进行输出，每次输出10个人。显示（group-1）10+0~9的运动员
//参数：SList，group
//	SList:运动员列表
//	group:组数
//返回:如果输入的组数已经大于SList的最大人数，则返回-1.否则返回0
//调用方法:例如我要输出1~10这10个运动员，则输入group==1。如果没有足够10个的运动员，就显示剩下的运动员
//修改时间：2020/4/9/9:32
//==================
int DisplayAthleteListdepartInfo(const SAthleteList& SList,int group);

//================
//功能：通过运动员的ID或者姓名，返回运动员在运动员列表SList中的位置
//参数：SList，szAthleteIDorName[]
//	SList:运动员列表（SAthleteList类型）
//	szAthleteIDorName[]:字符串，可以是运动员的ID或者姓名
//返回：找到：返回名字或ID为szAthleteIDorName的运动员在列表SList中的下标，下标从0开始
//            找不到：返回-1
//思路：循环比较，返回找到的第一个运动员的下标
//修改日期：2020/3/17/12:09
//================
int LocateAthlete(SAthleteList& SList, char szAthleteIDorName[]);

//================
//功能：返回运动员列表SList中第一个所属书院为nAcademyIndex的运动员的位置
//参数：SList，nAcademyIndex
//	SList:运动员顺序表
//	nAcademyIndex:要查找的书院编号，编号范围是Academy枚举常量的范围
//返回：找到：返回运动员列表中第一个书院为nAcademyIndex 的运动员位置
//            找不到：返回-1
//思路：循环比较，这个函函数在给运动员分组时使用，可以用来实现每个组中尽可能少相同参赛单位运动员的功能。
//修改日期：2020/3/17/12:13
//================
int LocateAthleteAcademy(SAthleteList& SList, int nAcademyIndex);

//================
//功能：返回运动员SAthle中项目名或者编号为szItemIDorName的项目在SAthle.SAthleteItem[3]中的位置。
//参数：SAthle,szItemIDorName[]
//	SAthle:运动员
//	szItemIDorName[]:字符串，项目的名称或者编号
//返回：找到：返回项目在运动员所选的项目中的位置
//            找不到：返回-1
//思路：循环比较，这个函数用于获得某个项目的报名名单
//修改日期：2020/3/17/12:36
//================
int LocateAthleteItem(SAthlete& SAthle, char szItemIDorName[]);

//================
//功能：在运动员列表SList末尾处添加运动员SAthle
//参数：SList,SAthle
//	SList:运动员列表(SAthleteList)
//	SAthle:运动员(SAthlete)
//返回：添加成功返回0
//            若运动员已存在列表中返回-1
//思路：找到末尾的位置，将结构体SAthle赋值到该位置。
//修改日期：2020/3/17/12：32
//================
int AddAthlete(SAthleteList& SList, SAthlete SAthle);

//================
//功能：在运动员列表SList中删除 名字或学号为szAthleteIDorName[]的运动员
//参数：SList,szAthleteIDorName[]
//	SList:运动员列表
//	szAthleteIDorName[]:字符串，代表要删除的运动员的姓名或者编号
//返回：删除成功返回0
//            列表中不存在该运动员返回-1；
//思路：循环比较
//修改日期：2020/3/17/13：02
//================
int DeleteAthlete(SAthleteList& SList, char szAthleteIDorName[]);

//================
//功能：将运动员列表SList中删除下标未nPos_athlete的运动员,是对上面函数的重载
//参数：SList,nPos_athlete
//	SList:运动员列表
//	nPos_athlete:需要删除的运动员的位置
//返回：删除成功返回0. 删除失败返回-1
//思路：动态顺序表的删除操作
//修改日期：2020/3/26/22：46
//================
int DeleteAthlete(SAthleteList& SList, int nPos_athlete);

//================
//功能：SAthle运动员报名的三个项目中，如果存在一个名或ID为szItemIDorName的项目，则将这个项目删除。
//参数：SAthle,szItemIDorName[]
//返回：删除成功返回0
//           改名运动员没有选这个项目，则返回-1
//思路：循环比较+数组的删除操作。这个函数
//修改日期：2020/3/18/11：23
//================
int DeleteAthleteItem(SAthlete& SAthle,char szItemIDorName[]);

//================
//功能：修改运动员列表SList中名字或者编号为szAthleteIDorName[]的运动员的信息
//参数：SList，szAthleteIDorName[]
//	SList:运动员列表
//	szAthleteIDorName[]:字符串，代表需要修改的运动员你的名字或者编号
//返回：修改成功返回0
//            列表中找不到运动员返回-1
//思路：循环比较找出该运动员的位置，通过dos输入修改改名运动员的信息
//修改时间：2020/3/17
//================
int ModifiAthlete(SAthleteList& SList, char szAthleteIDorName[]);

//================
//功能：将运动员列表的信息写入文件athleteinfo.txt中.（打开文件的mode："w"）
//参数：SList
//	SList:运动员列表
//返回：写入成功返回0
//思路：逐个将列表中的运动员结构写入文件中.
//危险：在调用这个函数之后，athleteinfo.txt会被覆盖，所以应该使用ReadAthleteListFile将文件内容读取到SList中后，完成需要的操作后再把SList写入到文件中。
//修改时间：2020/3/17/13：09
//================
int WriteAthleteListFile(SAthleteList& SList);

//================
//功能：将文件athleteinfo.txt中的运动员信息读取到SList运动员列表中（打开文件的mode："r"）
//参数：SList（出口参数）
//	SList：运动员列表，用来承载文件中运动员信息
//返回：读取成功返回0
//思路：逐个运动员结构读取
//修改时间：2020/3/17/13：12
//================
int ReadAthleteListFile(SAthleteList& SList);

//================
//功能：从运动员总名单中抽取出报名某个项目的名单
//参数：SList,SItemAthleteList,szItemIDorName[]
//	（入口）SList:运动员列表
//	（出口）SItemAthleteList:SList名单中选取了某个项目的名单
//	（入口）szItemIDroName[]:项目的ID或者名字
//思路：循环比较，此函数用来获得报名某个项目的名单。
//修改时间：2020/3/17/13：18
//================
void CreateItemAthleteList(SAthleteList& SList, SAthleteList& SItemAthleteList, char szItemIDorName[]);

//=================
//功能：从一个运动员名单SList中抽取女性运动员放到SFemaleAthleteList运动员名单中。
//参数：SList,SFemaleAthleteList
//	（入口）SList:运动员名单
//	（出口）SFemaleAthleteList:女性运动员名单
//思路：循环比较，此函数可以作为女子组分组的准备工作
//修改时间：2020/3/17/13：22
//=================
void CreateFemaleAthleteList(SAthleteList& SList, SAthleteList& SFemaleAthleteList);

//=================
//功能：从一个运动员名单SList中抽取男性运动员放到SMaleAthleteList运动员名单中。
//参数：SList,SMaleAthleteList
//	（入口）SList:运动员名单
//	（出口）SMaleAthleteList:女性运动员名单
//思路：循环比较，此函数可以作为男子组分组的准备工作
//修改时间：2020/3/17/13：23
//=================
void CreateMaleAthleteList(SAthleteList& SList, SAthleteList& SMaleAthleteList);

//=================
//功能： 当某个项目发生改变的时候，需要更新运动员文件中选择给项目的信息
//参数：SItem
//	SItem:修改了的项目
//思路：循环比较每个运动员的报名项目，和修改的项目相同时，将新的项目覆盖到原来的位置
//修改日期：2020/3/18/10：13
//=================
void AthleteFIlEUpdate_ItemModify(SSportItem& SItem);

//=================
//功能： 当某个项目被删除后，需要更新运动员文件中的数据
//参数：szItemIDorName[]
//	szItemIDorName[]:被删除的项目的名称或者ID
//思路：循环比较每个运动员的报名项目，如果存在被删除的项目，则将该项目从运动员报名项目中删除
//修改日期：2020/3/18/10：24
//=================
void AthleteFILEUpdate_ItemDelete(char szItemIDorName[]);