#pragma once
#ifndef __sportitem_H__
#define __sportitem_H__
#endif

#include"allstruct.h"

#define ITEMLIST_INIT_SIZE 30 //项目列表初始内存
#define INCREASEMENTSIZE 5 //项目列表增量

//=============
//功能： 让用户输入SSportItem结构成员的值
//参数： SItem: SSportItem结构类型变量引用
//思路： 使用scanf_s来输入结构成员的值
//调用方法：SSportItem item;
//                   CreateItem(item);
//修改日期：2020/4/29
//=============
void CreateItem(SSportItem& SItem);

//=============
//功能：初始化项目表
//参数：SList: SItemList类型变量引用
//思路：利用malloc为顺序表分配内存空间
//调用方法：SItemList List;
//                    InitItemList(List);
//修改日期:2020/4/30
//=============
void InitItemList(SItemList& SList);

//==========
//功能：清空项目表
//参数：SList项目表
//==========
void ClearItemList(SItemList& SList);

//==========
//功能：销毁项目表
//参数：SList项目表
//==========
void DestroyItemList(SItemList& SList);

//=============
//功能：显示SSportItem结构内容
//参数：SItem: SSportItem结构类型变量引用
//思路：使用printf打印内容
//调用方法：SSportItem item;
//                    DisplayItem(item);
//日期：2020/4/30
//=============
void DisplayItem(SSportItem& SItem,int withTitle);

//=============
//功能：如果项目编号或者名称为szItemIDorName的项目存在项目表SList中，则返回该项目的位置，否则返回-1.
//参数：SList,szItemIDorName[]
//	SList:项目表的引用
//	szItemIDorName[]:需要查找的项目的编号或者名称
//返回：项目存在，返回项目位置，
//            项目不存在，返回-1.
//=============
int LocateItem(SItemList& SList, char szItemIDorName[]);

//=============
//功能：在项目表末尾插入项目，插入成功返回0，失败返回-1
//参数：List,SItem
//	List:项目表SItemList的引用
//	SItem:需要插入的项目
//返回：插入成功返回0
//            若运动名或者编号重复则返回-1
//=============
int AddItem(SItemList& SList, SSportItem SItem);

//=============
//功能：删除项目表SList中编号或名称为szItemIDorName的项目，删除成功返回0，否则返回-1。删除的同时，将报名该项目的运动员取消报名该项目。
//参数：SList,szItemIDorName
//	SList:项目顺序表(SItemList)
//	szItemIDorName:一个字符串，可以代表项目名称或者项目编号
//返回：删除成功返回0，找不到项目返回-1
//=============
int DeleteItem(SItemList& SList, char szItemIDorName[]);

//=============
//功能同上
//参数：pos:项目在项目表中的位置
//=============
int DeleteItem(SItemList& SList, int pos);

//=============
//功能：在项目表SList中查找项目名或者项目编号为szItemIDorName 的项目，并进行修改
//参数：SList，szItemIDorName
//	SList:项目表(SItemList)
//	szItemIDorName: 需要修改的项目名或者项目编号
//返回：修改成功返回0，找不到项目返回-1
//=============
int ModifiItem(SItemList& SList, char szItemIDorName[]);

//=============
//功能：把项目列表中所有的项目进行分组，注意该分组名单并不会存入文件中。
//		每次需要用到分组的时候调用这个函数，然后就会在SSportItem结构体中的**ppAthleteGroup中存放着nGroupNumber个运动员列表
//参数：SList:包含所有项目的项目列表
//=============
int Grouping(SItemList& SList);

//=============
//功能：把所有的项目的分组按照成绩进行排序，如果是田赛就由高到低，如果是径赛就是由低到高
//使用：需要在Grouping函数后面使用，先创建分组才可以对这些分组进行排序
//=============
void Ordering(SItemList& SList);

//=============
//功能：分页显示这个项目的所有分组
//参数：SItem
//	SItem:项目
//返回：选择返回时，当前的组数
//注意，这个函数需要在分组完成后才可以使用，即需要在Grouping()后面
//=============
int DisplayGroupingPagination(SSportItem& SItem);
void DisplayNGroup(SSportItem& SItem, int n);
int DisplayGroupingPagination(SSportItem& SItem,const char* szTitle, const char* szThirdChoice);
//分页显示项目
void DisplayItemListPagination(const SItemList& SList, int page, int NumberPerPage);
//=============
//功能：将项目表中每个SSportItem结构写入iteminfo.txt中
//            其中打开文件的模式为"w",并且每写入一个结构输入一个换行符'\n'。
//参数：SList
//	SList:项目表(SItemList)
//返回：写入成功返回0
//思路：循环写入
//危险：这个函数会将iteminfo.txt文件覆盖掉
//                    所以正确的用法是先将文件中的项目读出到项目表中。
//                    对项目表进行操作，在把这个项目表写入到文件中。
//=============
int WriteItemListFile(SItemList& SList);

//=============
//功能：从iteninfo.txt文件中读取出所有的项目信息，存放到项目表SList中
//参数：SList
//	SList：项目表(SItemList)
//返回：读取出错返回-1  读取成功返回0
//=============
int ReadItemListFile(SItemList& SList);




//==============
//功能：项目的增删改查，项目管理
//==============
void ItemManagement();