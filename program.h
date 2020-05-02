#pragma once

#ifndef __program_H__
#define __program_H__
#endif

#include<ctime>
#include<cmath>
#include<stdio.h>
#include<iostream>
#include<Python.h>

#include"sportitem.h"
#include"athlete.h"
#include"itemgroup.h"
using namespace std;

#define TIMENUMBER 100

typedef enum ChineseNumber {
	一 = 1,
	二,
	三,
	四,
	五,
	六,
	七,
	八
}ChineseNumber;

typedef struct time {
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

void AddTime(STimeList& timelist,STime time);

int IsEmpty(STimeList& timelist);

void InputBaseInfo();

void DisplayTimeInfo(STimeList& timelist);

//=================
//功能：为每个项目分配时间，分配的时间要尽可能的紧凑.分配完成后，将所有必要的信息写入docx文档中。
//参数：timelist,nIntervalTime
//	timelist:时间段，由用户输入，该时间段是有要求的，每个时间段应是一段连续的时间。
//	nIntervalTime:间隔时间，也是由用户输入，是两个项目之间的间隔时间
//返回：如果项目所用的时间比用户输入的时间段要长，则返回-1
//            如果每个项目都可以分配时间段，则返回0
//修改时间：2020/3/28/20：33
//=================
int AllocItemTime(STimeList& timelist,int nIntervalTime, char szSchoolName[], char szSponsor[], char szOrganize[], char szPlace[], char szNumber[]);

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

//==================
//功能：打印某个参赛单位运动员到doc文件
//参数：pProgram,athletelist,academy,count;
//	pProgram:一个指向打开了的doc文档的文件指针
//	athletelsit:包含所有运动员的运动员表
//	academy:要打印的书院
//	count:运动员序号从count+1开始数起
//思路：循环比较
//修改时间：2020/4/1/11:09
//==================
void fprintAcademyAthlete(FILE* pProgram,SAthleteList& athletelist, Academy academy, int& count);