#pragma once
#include"allstruct.h"

//=============
//功能：初始化参赛单位表SList
//参数：SList
//	SList:参赛单位顺序表(SAcademyList)
//修改日期：2020/5/2
//=============
void InitAcademyList(SAcademyList& SList);

//=============
//功能：创建新的参赛单位academy
//参数：academy
//	academy:参赛单位的结构体
//修改日期：2020/5/2
//=============
void CreateAcademy(SAcademy& academy);

//=============
//功能：销毁参赛单位SList
//参数：SList
//	SList：参赛单位顺序表
//修改日期：2020/5/2
//=============
void DestroyAcademyList(SAcademyList& SList);

//=============
//功能：清空参赛单位表SList
//参数：SList
//	SList:参赛单位顺序表
//修改日期：2020/5/2
//=============
void ClearAcademyList(SAcademyList& SList);

//=============
//功能：查找名为szAcademyName[]的参赛单位在参赛单位表SList中的位置
//参数：SList，szAcademyName[]
//	SList:参赛单位表
//	szAcademyName[]:要查找的参赛单位的名字
//返回：如果找到返回相应的位置，如果没有找到返回-1
//修改日期：2020/5/2
//=============
int LocateAcademy(SAcademyList& SList, char szAcademyName[]);

//=============
//功能：添加参赛单位academy到参赛单位列表SList
//参数：SList，academy
//	SList：参赛单位列表
//	academy：参赛单位结构体
//返回：插入成功则返回0
//修改日期：2020/5/2
//=============
int AddAcademy(SAcademyList& SList, SAcademy academy);

//=============
//功能：删除参赛单位列表SList中，名为szAcademyName[]的参赛单位
//参数：SList，szAcademyName
//	SList:参赛单位列表
//	szAcademyName:参赛单位名
//返回：删除成功则返回0
//修改日期：2020/5/2
//=============
int DeleteAcademy(SAcademyList& SList, char* szAcademyName);

//=============
//功能：修改参赛单位列表SList中名为szAcademyName[]的参赛单位
//参数：SList，szAcademyName
//	SList:参赛单位列表
//	szAcademyName:参赛单位名
//返回：修改成功则返回0
//修改日期：2020/5/2
//=============
int ModifyAcademy(SAcademyList& SList, char* szAcademyName);

//=============
//功能：显示参赛单位列表SList
//参数：SList
//	SList:参赛单位列表
//修改日期：2020/5/2
//=============
void DisplayAcademyList(SAcademyList& SList);

//=============
//功能：将参赛单位SList写入文件academyinfo.txt中
//参数：SList
//	SList：参赛单位列表
//修改日期：2020/5/2
//=============
int WriteAcademyListFile(SAcademyList& SList);

//=============
//功能：从文件academyinfo.txt中读取参赛单位表到SList
//参数：SList
//	（出口）SList：参赛单位列表
//修改日期：2020/5/2
//=============
int ReadAcademyListFile(SAcademyList& SList);

//=============
//功能：参赛单位的增删改查，利用上面的函数实现
//日期：2020/5/2
//=============
void AcademyManagement();