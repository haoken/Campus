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
	һ = 1,
	��,
	��,
	��,
	��,
	��,
	��,
	��
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
//���ܣ�Ϊÿ����Ŀ����ʱ�䣬�����ʱ��Ҫ�����ܵĽ���.������ɺ󣬽����б�Ҫ����Ϣд��docx�ĵ��С�
//������timelist,nIntervalTime
//	timelist:ʱ��Σ����û����룬��ʱ�������Ҫ��ģ�ÿ��ʱ���Ӧ��һ��������ʱ�䡣
//	nIntervalTime:���ʱ�䣬Ҳ�����û����룬��������Ŀ֮��ļ��ʱ��
//���أ������Ŀ���õ�ʱ����û������ʱ���Ҫ�����򷵻�-1
//            ���ÿ����Ŀ�����Է���ʱ��Σ��򷵻�0
//�޸�ʱ�䣺2020/3/28/20��33
//=================
int AllocItemTime(STimeList& timelist,int nIntervalTime, char szSchoolName[], char szSponsor[], char szOrganize[], char szPlace[], char szNumber[]);

//==================
//���ܣ�����Сʱhour:����min ����Ҫ�ӵķ�����add_min���ó�һ��������Ԫ�ص����顣��������������add_min֮���ʱ��
//������hour,min,add_min
//	hour:ԭ����Сʱ��
//	min:ԭ���ķ�����
//	add_min:��Ҫ��ӵķ�����
//���أ�int*(һ������)
//	int*[0]:������ʱ��֮���Сʱ��
//	int*[1]:�������¼�֮��ķ�����
//�޸��¼���2020/4/1/13��39
//==================
int* finishTime(int hour, int min, int add_min);

//==================
//���ܣ���������ʱ�䣨Сʱ�ͷ��ӹ��ɣ��Ƚ�����ʱ��Ĵ�С
//������hour,min   other_hour,other_min
//	hour,min:��һ��ʱ���Сʱ�ͷ���
//	other_hour,other_min:�ڶ���ʱ���Сʱ��ʱ��
//���أ�����ڶ���ʱ��󣬷���1
//          �����һ��ʱ��򣬷���-1
//          �������ʱ����ͬ������0
//�޸�ʱ�䣺2020/3/28/19��56
//==================
int compareTime(int hour, int min, int other_hout, int other_min);

//==================
//���ܣ���ӡĳ��������λ�˶�Ա��doc�ļ�
//������pProgram,athletelist,academy,count;
//	pProgram:һ��ָ����˵�doc�ĵ����ļ�ָ��
//	athletelsit:���������˶�Ա���˶�Ա��
//	academy:Ҫ��ӡ����Ժ
//	count:�˶�Ա��Ŵ�count+1��ʼ����
//˼·��ѭ���Ƚ�
//�޸�ʱ�䣺2020/4/1/11:09
//==================
void fprintAcademyAthlete(FILE* pProgram,SAthleteList& athletelist, Academy academy, int& count);