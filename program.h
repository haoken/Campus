#pragma once
#include"allstruct.h"
#define TIMENUMBER 100

typedef struct time {
	char szItemName[25];//存放该时间段中比赛的项目名称
	int year;
	int month;
	int day;
	int hour_begin;
	int hour_end;
	int min_begin;
	int min_end;
}STime;

typedef struct STimeList {
	STime times[TIMENUMBER];
	int length;
}STimeList;

void InitTimeList(STimeList& timelist);

void ClearTimeList(STimeList& timelist);

void AddTime(STimeList& timelist, STime time);

int IsEmpty(STimeList& timelist);

void DisplayTimeInfo(STimeList& timelist);

//显示某个比赛时间安排及其项目请开给你
void DisplayTimeItemInfo(STimeList& timelist);

//=================
//功能：为每个项目分配时间，分配的时间要尽可能的紧凑.分配完成后，将所有必要的信息写入docx文档中。
//参数：timelist,nIntervalTime
//	timelist:时间段，由用户输入，该时间段是有要求的，每个时间段应是一段连续的时间。
//	nIntervalTime:间隔时间，也是由用户输入，是两个项目之间的间隔时间
//返回：如果项目所用的时间比用户输入的时间段要长，则返回-1
//            如果每个项目都可以分配时间段，则返回0
//修改时间：2020/3/28/20：33
//=================
int AllocItemTime(STimeList& timelist, double dIntervalTime_Group,double dIntervalTime_Item);

//==================
//功能：传入小时hour:分钟min 和需要加的分钟数add_min。得出一个有两个元素的数组。该数组存放增加了add_min之后的时间
//参数：hour,min,add_min
//	hour:原本的小时数
//	min:原本的分钟数
//	add_min:需要添加的分钟数
//返回：int*(一个数组)
//	int*[0]:存放添加时间之后的小时数
//	int*[1]:存放添加事件之后的分钟数
//修改事件：2020/4/1/13：39
//==================
int* finishTime(int hour, int min, int add_min);

//==================
//功能：输入两个时间（小时和分钟构成）比较两个时间的大小
//参数：hour,min   other_hour,other_min
//	hour,min:第一个时间的小时和分钟
//	other_hour,other_min:第二个时间的小时和时间
//返回：如果第二个时间大，返回1
//          如果第一个时间打，返回-1
//          如果两个时间相同，返回0
//修改时间：2020/3/28/19：56
//==================
int compareTime(int hour, int min, int other_hout, int other_min);


void ProgramManagement();