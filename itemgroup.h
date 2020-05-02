////////////////////////////////////////////
//文件说明
//工程：MyCampusSportSystem
//作者：李嘉浩
//描述：该文件提供分组功能，可按项目分组，可按参赛单位分组。并提供相关操作。在分组的基础上实现运动员信息的查询功能。
//主要函数：
//			void ConnectItemList(SGroupList& SGroups,SItemList& SItems)//根据传入的项目表，创建与之对应的项目分组表
//			void ConnectAthleteList(SGroupList& SGroups, SAthleteList& SAthletes)//根据传入的运动员列表，创建分组。
//			void InputResult(char szItemIDorName[])//输入某个项目运动员成绩
//完成日期：2020/3/18 /12：26
/////////////////////////////////////////////

#pragma once

#ifndef __itemgroup_H__
#define __itemgroup_H__
#endif

#include<math.h>
#include<iostream>
#include"sportitem.h"
#include"athlete.h"

using namespace std;

#define MAXGROUPNUMBER 6 //每个项目最大分组项目

//项目分组，每个项目SSportItem对那个一个分组SItemGroup
typedef struct SItemGroup {
	char szItemName[20];
	char szItemID[20];
	SPORTTYPE SPORTTYPE_SportType;
	int nFemaleGroupNumber;//女子分组数量
	SAthleteList SFemaleAthleteList;//所有女生名单,用来进行成绩的排名
	SAthleteList SFemaleGroups[MAXGROUPNUMBER];//每个女子分组的名单
	int nMaleGroupNumber;//男子组分组数量
	SAthleteList SMaleAthleteList;//所有男生名单,用来进行成绩的排名
	SAthleteList SMaleGroups[MAXGROUPNUMBER];//每个男子分组的名单
}SItemGroup;

//项目分组表
typedef struct SGroupList {
	SItemGroup* pSItemGroupList;
	int nListLength;
	int nListSize;
}SGroupList;

//==============
//功能：用来项式某个项目分组的情况
//参数：SGroup
//	SGroup:项目分组（SItemGroup）
//思路：在dos上显示，用于测试后续函数正确性
//修改时间：2020/3/17/13：27
//==============
void DisplayItemGroup(SItemGroup& SGroup);

//==============
//功能：初始化项目分组列表并和项目表项关联
//参数：SGroups,SItems
//	SGroups:项目分组表，和项目表一一对应
//	SItems:项目表
//思路：某个项目分组在项目分组表中的位置，和该项目在项目表的位置相同。从而起到一一对应的效果
//注意：该函数包含的项目分组表的初始化操作，所以在对项目分组表进行操作前应先调用该函数。
//修改时间：2020/3/17
//==============
void ConnectItemList(SGroupList& SGroups,SItemList& SItems);

//==============
//功能：根据运动员表SAthletes，获得各个项目的分组信息
//参数：SGroups,SAthletes
//	SGroups:项目分组表，分组信息存储在SGroups结构中。
//	SAthletes:运动员总表
//实现步骤：
//	1.从运动员总表中抽取出报名了某一个项目的运动员表（用函数CreateItemAthleteList）
//	2.再从这个表中分离出男组运动员表和女组运动员表（用函数CreateFemaleAthleteList,CreateMaleAthleteList）
//	3.分组的要求：每一组中的运动员尽量来自不同的参赛单位
//	4.按照分组的要求分组（用GroupingAthlete函数）
//注意：在调用该函数之前，应先调用ConnectItemList函数对项目分组表进行初始化，并和项目表向链接。
//修改时间：2020/3/17/13：44
//==============
void ConnectAthleteList(SGroupList& SGroups, SAthleteList& SAthletes);

//==============
//功能：分别将男子组运动员和女子组运动员按照分组要求分到若干各组中。
//参数:SFemaleAthleteList,SMaleAthleteList,ItemGroup
//	SFemaleAthleteList:该项目的女子组运动员表
//	SMaleAthleteList:该项目的男子组运动员表
//	ItemGroup: 该项目的分组情况（SItemGroup）
//思路：类似于计数排序算法，先将运动员按照参赛单位分桶，然后每组的运动员表按顺序从每个桶中抽取一人加入自己表中。
//修改日期：2020/3/17/13：53
//==============
void GroupingAthlete(SAthleteList& SFemaleAthleteList, SAthleteList& SMaleAthleteList, SItemGroup& ItemGroup);

void DestroyItemGroupList(SGroupList& SList);

//===============
//功能：将某个项目的名单的成绩全部录入。
//参数：szItemIDorName[]
//	szItemIDorName[]:需要输入成绩的项目
//思路：讲该项目报名的运动员信息输入后，按顺序输入成绩
//修改日期：2020/3/26/20：07
//===============
void InputResult(char szItemIDorName[]);

//===============
//功能：将所有参赛单位时nAcademy的运动员存放到athletelist运动员列表中
//参数：athletelist,nAcademy
//	athletelist:运动员列表（需要先初始化,再传进来！）
//	nAcademy:参赛单位的序号
//	知行书院 = 1, 思源书院 = 2, 弘毅书院 = 3,
//	敬一书院 = 4, 至诚书院 = 5, 修远书院 = 6,
//	明德书院 = 7, 德馨书院 = 8, 研究生院 = 9
//思路：循环比较
//修改日期：2020/3/26/20：16
//===============
void AcademyGroup(SAthleteList& athletelist, int nAcademy);

//===============
//功能：检查是否报名该项目的所有运动员已经输入成绩
//参数：group
//	group:某一个项目的项目分组
//返回：已经输入完成返回1
//            男子组未完成输入返回0(女子组完成)
//            女子组未完成输入返回-1(男子组完成)
//            男子组和女子组都没有完成返回-2
//思路：遍历检查
//修改时间：2020/3/26/21：38
//===============
int FinishInputResult(SItemGroup& group);

//===============
//功能：将已经输入成绩后的项目分组传入函数，然后函数将项目分组中的男子组和女子组
//的运动员根据该项目成绩从高到低排序。
//参数：group
//	group:项目分组结构体。（注意：这时的结构体需要全部输入成绩）
//返回：如果排名成功返回1，排名失败返回0
//思路：选择排序法
//修改时间：2020/3/26/21：24
//===============
int RankItemGroupAthleteList(SItemGroup& group);

//==============
//功能：显示项目的信息，对比与sportitem.h中的DisplayItem函数，多显示了该项目的报名人数
//参数：SItem
//	SItem:项目结构体
//修改时间：2020/4/1/14：56
//==============
void DisplayItemWithNumber(SSportItem& SItem);

//==============
//功能：显示项目表的信息，对比sportitem.h中的DisplayItemList多了显示项目报名人数的功能
//参数：SList
//	SList:项目表
//修改时间：2020/4/1/14：57
//==============
void DisplayItemListWithNumber(SItemList& SList);