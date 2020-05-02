//#pragma once

#ifndef __itemrecord_H__
#define __itemrecord_H__
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXRECORDSIZE 30
#define INCREASERECORDSIZE 5

//性别 
typedef enum Gender {
	GENDER_FEMALE,//女性
	GENDER_MALE//男性
}Gender;

typedef struct SItemRecord {
	char szRecordID[10];//记录编号
	char szRecordName[20];//纪录的项目名称
    double dRecordResult;//纪录成绩
    char szAthleteName[20];//纪录保持者姓名
    Gender AthleteGender;//纪录保持者性别 

}SItemRecord;

//纪录链表，其元素为类型SItemRecord的数据
typedef struct SRecordList {
	SItemRecord* pSRecordList;
	int nListLength;  //实际长度 
	int nListSize;
}SRecordList;


//=============
//功能：初始化纪录表
//参数：SList: SRecordList类型变量引用
//思路：利用malloc为顺序表分配内存空间
//调用方法：SRecordList recordlist;
//          InitRecordList(recordlist);
//=============
void InitRecordList(SRecordList& SList);

//=============
//功能： 让用户输入SItemRecord结构成员的值
//参数： SRecord: SItemRecord结构类型变量引用
//思路： 使用scanf来输入结构成员的值
//调用方法：SItemRecord record;
//          CreateRecord(record);
//=============
void CreateRecord(SItemRecord& SRecord);

//=============
//功能：如果项目名称为szRecordName的项目纪录存在纪录表SList中，则返回该项目的位置，否则返回-1.
//参数：SList,szRecordName[]
//	SList:纪录表的引用 
//	szRecordName[]:需要查找的项目的名称
//返回：项目存在，返回项目位置，
//            项目不存在，返回-1.
//思路：通过循环比较的方法遍历项目表，查找项目的位置
//=============
int LocateRecord(SRecordList& SList, char szRecordName[]);

//=============
//功能：在纪录表末尾插入未拥有的项目记录，插入成功返回0，失败返回-1
//参数：List,SRecord
//返回：插入成功返回0，若项目名重复则返回-1
//=============
int AddRecord(SRecordList& SList, SItemRecord SRecord);

//=============
//功能：删除项目表SList中w第i个位置的纪录 
//参数：SList,szItemIDorName
//	SList:纪录顺序表
//	RecordLocation：纪录在表中的位置，i=LocateRecord（）； 
//返回：删除成功返回0，找不到项目返回-1
//思路：循环比较，找到项目位置。
//=============
int DeleteRecord(SRecordList& SList, char szRecordName[]);

//=============
//功能：在项目表SList中查找第i个项目，并进行修改。i=LocateRecord（）； 
//参数：SList，szItemIDorName
//	SList:项目表(SRecordList)
//	RecordLocation：纪录在表中的位置，i=LocateRecord（）； 
//返回：修改成功返回0，找不到项目返回-1
//思路：利用LocateItem找到项目位置，再选择需要修改的内容进行修改。
//=============
int ModifiRecord(SRecordList& SList, char szRecordName[]);


//=============
//功能：显示SSportItem结构内容
//参数：SItem: SSportItem结构类型变量引用
//思路：使用printf打印内容
//调用方法：SSportItem item;
//                    DisplayItem(item);
//日期：2020/3/13/17：58 
//=============
void PrintRecord(SItemRecord &SRecord);

//=============
//功能：显示项目表内容
//参数：SList
//	SList:项目表SItemList
//日期：2020/3/13/23:49
//=============
void PrintRecordList(const SRecordList& SList);

//=============
//功能：将项目表中每个SItemRecord结构写入recordinfo.txt中
//其中打开文件的模式为"w",并且每写入一个结构输入一个换行符'\n'。
//参数：SList
//	SList:项目表(SRecordList)
//返回：写入成功返回0
//=============
int WriteRecordListFile(SRecordList& SList);

//=============
//功能：从recordinfo.txt文件中读取出所有的项目信息，存放到项目表SRecordList中
//参数：SList
//	SList：项目表(SRecordList)
//返回：读取出错返回-1  读取成功返回0
//思路：注意和写入文件的格式相对应，在写入时输入了一个换行符，读取时需要把这个换行符读取。
//=============
int ReadRecordListFile(SRecordList& SList);


