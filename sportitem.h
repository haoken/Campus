////////////////////////////////////////////
//文件说明
//工程：MyCampusSportSystem
//作者：李嘉浩
//描述：项目表的增删该查功能
//主要函数：
//			void InitItemList(SItemList& SList);//初始化项目表
//			int LocateItem(SItemList& SList, char szItemIDorName[]);//查询某个项目在项目表中的位置
//			int AddItem(SItemList& SList, SSportItem SItem);//将某个项目添加到项目表的末尾
//			int DeleteItem(SItemList& SList, char szItemIDorName[]);//删除项目表的某个项目
//			int ModifiItem(SItemList& SList, char szItemIDorName[]);//修该项目表中某个项目的信息
//			int WriteItemListFile(SItemList& SList);//将项目表写入iteminfo.txt文件中
//			int ReadItemListFile(SItemList& SList);//从iteminfo.txt文件中读取项目信息，存放在项目表中
//完成日期：2020/3/18 /12：26
/////////////////////////////////////////////

#pragma once

#ifndef __sportitem_H__
#define __sportitem_H__
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXITEMSIZE 30
#define INCREASEITEMSIZE 5

enum SPORTTYPE {
	SPORTTYPE_FIELD,//田赛
	SPORTTYPE_TRACK//径赛
};

typedef struct SSportItem {
	char szItemID[10];//项目编号
	char szItemName[20];//项目名称
	enum SPORTTYPE SPORTYPE_itemtype;//项目类别
	double dItemTime;//每组所需时间吗，以分钟为单位
	double dResult;//项目成绩
}SSportItem;

typedef struct SItemList {//动态存储结构顺序表
	SSportItem* pSItemList;//数组
	int nListLength;//顺序表实际长度
	int nListSize;//顺序表分配的内存
}SItemList;

//=============
//功能： 让用户输入SSportItem结构成员的值
//参数： SItem: SSportItem结构类型变量引用
//思路： 使用scanf_s来输入结构成员的值
//调用方法：SSportItem item;
//                   CreateItem(item);
//修改日期：2020/3/13/17:55
//=============
void CreateItem(SSportItem& SItem);

//=============
//功能：显示SSportItem结构内容
//参数：SItem: SSportItem结构类型变量引用
//思路：使用printf打印内容
//调用方法：SSportItem item;
//                    DisplayItem(item);
//日期：2020/3/13/17：58 
//=============
void DisplayItem(const SSportItem& SItem);

//=============
//功能：显示项目表内容
//参数：SList
//	SList:项目表SItemList
//日期：2020/3/13/23:49
//=============
void DisplayItemList(const SItemList& SList);

//=============
//功能：初始化项目表
//参数：SList: SItemList类型变量引用
//思路：利用malloc为顺序表分配内存空间
//调用方法：SItemList List;
//                    InitItemList(List);
//修改日期:2020/3/13/18:07
//=============
void InitItemList(SItemList& SList);

//=============
//功能：销毁项目表
//参数：SList
//	SList:需要销毁的项目表
//思路：动态存储结构顺序表的销毁操作
//修改时间：2020/3/26/23：21
//=============
void DestroyItemList(SItemList& SList);

//=============
//功能：如果项目编号或者名称为szItemIDorName的项目存在项目表SList中，则返回该项目的位置，否则返回-1.
//参数：SList,szItemIDorName[]
//	SList:项目表的引用
//	szItemIDorName[]:需要查找的项目的编号或者名称
//返回：项目存在，返回项目位置，
//            项目不存在，返回-1.
//思路：通过循环比较的方法遍历项目表，查找项目的位置
//日期：2020/3/13/21：52
//=============
int LocateItem(SItemList& SList, char szItemIDorName[]);

//=============
//功能：在项目表末尾插入项目，插入成功返回0，失败返回-1
//参数：List,SItem
//	List:项目表SItemList的引用
//	SItem:需要插入的项目
//返回：插入成功返回0
//            若运动名或者编号重复则返回-1
//调用方法：将项目表和需要插入的项目分别传入函数即可
//日期：2020/3/13/21：29
//=============
int AddItem(SItemList& SList, SSportItem SItem);

//=============
//功能：删除项目表SList中编号或名称为szItemIDorName的项目，删除成功返回0，否则返回-1
//参数：SList,szItemIDorName
//	SList:项目顺序表(SItemList)
//	szItemIDorName:一个字符串，可以代表项目名称或者项目编号
//返回：删除成功返回0，找不到项目返回-1
//思路：循环比较，找到项目位置。
//            将szItemIDorName代表两个东西的前提是名称和编号差别很大，不存在名称和编号相同的情况
//日期：2020/3/13/22：41
//=============
int DeleteItem(SItemList& SList, char szItemIDorName[]);

//=============
//功能：在项目表SList中查找项目名或者项目编号为szItemIDorName 的项目，并进行修改
//参数：SList，szItemIDorName
//	SList:项目表(SItemList)
//	szItemIDorName: 需要修改的项目名或者项目编号
//返回：修改成功返回0，找不到项目返回-1
//思路：利用LocateItem找到项目位置，再选择需要修改的内容进行修改。
//日期：2020/3/14/10:16
//=============
int ModifiItem(SItemList& SList, char szItemIDorName[]);

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
//日期：2020/3/14/11:33
//=============
int WriteItemListFile(SItemList& SList);

//=============
//功能：从iteninfo.txt文件中读取出所有的项目信息，存放到项目表SList中
//参数：SList
//	SList：项目表(SItemList)
//返回：读取出错返回-1  读取成功返回0
//思路：注意和写入文件的格式相对应，在写入时输入了一个换行符，读取时需要把这个换行符读取。
//日期：2020/3/14/12：41
//=============
int ReadItemListFile(SItemList& SList);

