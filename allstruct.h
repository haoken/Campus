/////////////////////////////////////////////////////////////////////   
//����: У�˻����ϵͳ  
//     ����:���ļ������˱���Ŀ���õ������еĽṹ���ö�����ͣ�ʵ�������ṹ��֮����໥���á� ���и���˳���ĳ�ʼ��������
//     �汾: У�˻�ϵͳ2.0��
//	   ������ڣ�2020/4/29   
//     �޸�:ɾ��itemgroup�ṹ�塣��sportitem��������б�������Ŀ���˶�Ա�������˶�Ա����������sportitem��������Ա����ơ�  
/////////////////////////////////////////////////////////////////////  

#pragma once
#ifndef __ALLSTRUCT_H__
#define __ALLSTRUCT_H__ 
#endif

#define ITEMLIST_INIT_SIZE 30//��Ŀ��ĳ�ʼ��С
#define ITEMLIST_INCREASEMENT 5//��Ŀ������

#define ATHLETELIST_INIT_SIZE 100//�˶�Ա��ĳ�ʼ��С
#define ATHLETELIST_INCREASEMENT 10//�˶�Ա������

#define ACADEMYLIST_INIT_SIZE 10//������λ��ĳ�ʼ��С
#define ACADEMYLIST_INCREASEMENT 5//������λ������

#define RECORDLIST_INIT_SIZE 100//��¼��ĳ�ʼ��С
#define RECORDLIST_INCREASEMENT 10//��¼������

#define ATHLETE_MAX_ITEM 3 //�˶�Ա��౨����Ŀ
#define MAX_ITEM_TIME 7//һ���������ı�������

#define TITLELENGTH 100//����������

#define EXCEL_MAX_CHARONELINE 100   //���һ������ַ�����
#define MAX_PLACE_NUMBER 30  //��಻ͬ�ı�������

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
	SPORTTYPE_FIELD,//����
	SPORTTYPE_TRACK//����
}SPORTTYPE;

typedef enum GENDER {
	GENDER_MALE,//����
	GENDER_FEMALE//Ů��
}GENDER;

//�ṹ����ǰ����������ʵ���໥����
struct SSportItem;
struct SItemList;

struct SAcademy;
struct SAcademyList;

struct SAthlete;
struct SAthleteList;

struct SItemRecord;
struct SRecordList;

typedef struct SSportItem {
	char szItemID[10];//��Ŀ���
	char szItemName[25];//��Ŀ����
	SPORTTYPE SPORTTYPE_itemtype;//��Ŀ���
	GENDER GENDER_itemgender;//�ܲμ���Ŀ�˶�Ա�Ա�
	char szPlace[20];//����
	double dItemTime;//��ʱ
	double dResult;//�ɼ�,������Ҫ6�ֳɼ�.��һ��Ԫ��������ųɼ��ĸ���
	int GroupNumber;//�������������˶�Ա����֮��ʵʱ����
	SAthleteList *pAthleteList;//ָ��һ���˶�Ա�б����б����ű�������Ŀ���˶�Ա����
	SAthleteList **ppAthleteGroup;//ָ�����飬��GroupNumber��Ԫ�أ�ÿ��Ԫ�ض���ָ���˶�Ա�б��ָ��,����������
}SSportItem;

typedef struct SItemList {//��̬�洢�ṹ˳���
	SSportItem* pSItemList;//����
	int nListLength;//˳���ʵ�ʳ���
	int nListSize;//˳��������ڴ�
}SItemList;

typedef struct SAcademy {
	char szAcademyName[20];//������֯����
	int score;//�÷�
}SAcademy;

typedef struct SAcademyList {
	SAcademy* pSAcademyList;
	int nListLength;
	int nListSize;
}SAcademyList;

typedef struct SAthlete {
	char szAthleteName[20];//����
	char szAthleteID[20];//ѧ��
	GENDER GENDER_athleteGender;//�Ա�
	int nSItemNumber;//������Ŀ����
	SSportItem SAthleteItem[ATHLETE_MAX_ITEM];//��౨������Ŀ
	SAcademy academy;//������λ
}SAthlete;

typedef struct SAthleteList {
	SAthlete* pSAthleteList;
	int nListLength;
	int nListSize;
}SAthleteList;

typedef struct SItemRecord {
	char szRecordID[10];//��¼���
	char szRecordName[20];//��¼����Ŀ����
	double dRecordResult;//��¼�ɼ�
	char szAthleteName[20];//��¼����������
	GENDER AthleteGender;//��¼�������Ա� 
}SItemRecord;

typedef struct SRecordList {
	SItemRecord* pSRecordList;
	int nListLength;  //ʵ�ʳ��� 
	int nListSize;
}SRecordList;

//��ʼ����Ŀ��
void InitItemList(SItemList& SList);
//��ʼ���˶�Ա��
void InitAthleteList(SAthleteList& SList);
//��ʼ��������λ��
void InitAcademyList(SAcademyList& SList);
//��ʼ����¼��
void InitRecordList(SRecordList& SList);

///////////////////////////////////
//����һ����Ŀ�����������Ϣ
void CreateItem(SSportItem& SItem);
//��ʾ��Ŀ��Ϣ
void DisplayItem(SSportItem& SItem, int withTitle);
//��ʾ��Ŀ�б�
void DisplayItemList(const SItemList& SList);
//�����Ŀ�б�
void ClearItemList(SItemList& SList);
//������Ŀ�б�
void DestroyItemList(SItemList& SList);
//��λ��Ŀ����Ŀ�б��е�λ��
int LocateItem(SItemList& SList, char szItemIDorName[]);
//�����Ŀ����Ŀ�б���
int AddItem(SItemList& SList, SSportItem SItem);
//ɾ����Ŀ�б��е���Ŀ��
int DeleteItem(SItemList& SList, char szItemIDorName[]);
//�޸���Ŀ�б���ĳ����Ŀ
int ModifiItem(SItemList& SList, char szItemIDorName[]);
//����Ŀ�б�д���ļ���
int WriteItemListFile(SItemList& SList);
//���ļ��ж�ȡ��Ŀ�б�
int ReadItemListFile(SItemList& SList);
//��ĳ����Ŀ�ı�������з���
int Grouping(SItemList& SList);
//����Ŀ�б������еķ��鰴�ճɼ���������
void Ordering(SItemList& SList);
//��ҳ��ʾĳ����Ŀ���еķ������
int DisplayGroupingPagination(SSportItem& SItem);
//��ҳ��ʾĳ����Ŀ�ķ����뿪���㣬������������ѡ�1.��һҳ 2.��һҳ��3.���ء����е����������������������������������ı���Ҳ���������������԰��ⲿ����Ϊ�������뺯����
int DisplayGroupingPagination(SSportItem& SItem, const char* szTitle,const char* szThirdChoice);
//��ʾ��n�飨��1��ʼ��
void DisplayNGroup(SSportItem& SItem, int n);
//��ҳ��ʾ��Ŀ
void DisplayItemListPagination(const SItemList& SList, int page, int NumberPerPage);
//////////////////////////////////

//�����˶�Ա��Ϣ
void InputAthleteInfo(SAthlete& SAthle);
//����˶�Ա�б�
void ClearAthleteList(SAthleteList& SList);
//�����˶�Ա�б�
void DestroyAthleteList(SAthleteList& SList);
//��ʾ�˶�Ա��Ϣ
void DisplayAthleteInfo(const SAthlete& SAthle, int withTitle);
//��ʾ�˶�Ա�б���Ϣ
void DisplayAthleteListInfo(const SAthleteList& SList);
//��ҳ��ʾ�˶�Ա�б�ֻ��ʾ��pageҳ��Ȼ��ÿҳNumberPerPage��
void DisplayAthleteListInfo(const SAthleteList& SList, int page, int NumberPerPage);
//��ҳ��ʾ�˶�Ա�б�ÿҳNumberPerPage�����ṩ��ҳ����
void DisplayAthleteListPagination(const SAthleteList& SList, int nNumberPerPage);
//�ҵ�ĳ���˶�Ա���˶�Ա�б��е�λ��
int LocateAthlete(SAthleteList& SList, char szAthleteIDorName[]);
//����˶�Ա���˶�Ա�б���
int AddAthlete(SAthleteList& SList, SAthlete SAthle);
//ɾ���˶�Ա�б��е�ĳ���˶�Ա���Ҳ�ͬ�����������С�
int DeleteAthlete(SAthleteList& SList, char szAthleteIDorName[]);
//ɾ���˶�Ա�б���ĳ���˶�Ա,��ͬ������Ŀ��������
int DeleteAthleteSync(SAthleteList& SList, char szAthleteIDorName[]);
//ɾ���˶�Ա�б���ĳ��λ�õ��˶�Ա,��ͬ������Ŀ��������
int DeleteAthleteSync(SAthleteList& SList, int nPos_athlete);
//�ҵ�ĳ����Ŀ��ĳ���˶�Ա�е�λ��
int LocateAthleteItem(SAthlete& SAthle, char szItemIDorName[]);
//ɾ��ĳ���˶�Ա������Ŀ�е�ĳ����Ŀ
int DeleteAthleteItem(SAthlete& SAthle, char szItemIDorName[]);
//Ϊĳ���˶�Ա���ĳ����Ŀ
int AddAthleteItem(SAthlete& SAthle, SSportItem SItem);
//�޸�ĳ���˶�Ա����Ϣ
int ModifiAthlete(SAthleteList& SList, char szAthleteIDorName[]);
//���˶�Ա�б�д���ļ�
int WriteAthleteListFile(SAthleteList& SList);
//���ļ��ж�ȡ�˶�Ա�б����Ϣ
int ReadAthleteListFile(SAthleteList& SList);
//ͬ������
void AthleteSync(SAthlete& athlete);
//��ĳ���˶�Ա��SAthle.SAthleteItem[n]�滻��SItem.Ȼ��ʵ�ֱ������е�ͬ������
int ReplaceAthleteItem(SAthlete& SAthle, SSportItem SItem, int n);

///////////////////////////////////
//�����µĲ�����λ
void CreateAcademy(SAcademy& academy);
//��ղ�����λ�б�
void ClearAcademyList(SAcademyList& SList);
//���ٲ�����λ�б�
void DestroyAcademyList(SAcademyList& SList);
//�õ�ĳ��������λ�ڲ�����λ�б��е�λ��
int LocateAcademy(SAcademyList& SList, char szAcademyName[]);
//��Ӳ�����λ��������λ�б���
int  AddAcademy(SAcademyList& SList, SAcademy academy);
//�Ӳ�����λ�б���ɾ��ĳ��������λ
int DeleteAcademy(SAcademyList& SList, char* szAcademyName);
//�ڲ�����λ�б����޸�ĳ��������λ
int ModifyAcademy(SAcademyList& SList, char* szAcademyName);
//��ʾ������λ�б��еĲ�����λ
void DisplayAcademyList(SAcademyList& SList);
//��������λ�б����Ϣд�뵽�ļ���
int WriteAcademyListFile(SAcademyList& SList);
//���ļ��ж�ȡ���в�����λ����Ϣ��
int ReadAcademyListFile(SAcademyList& SList);
////////////////////////////////////

//��������ܵ�д���ļ���
void WritePasswordtoFile(char password[]);
//��������ܶ����ļ�
char* ReadPasswordfromFile();

////////��������
//��ӡ��excel�ж��������˶�Ա��Ϣ
void PrintAthleteInfo(SAthlete SAthle);
//��excel����Ϊ�ַ�������ĳһ�У�Ȼ�����һ���ַ����ֿ������ɷݸ��Ƶ�SAthle�ṹ����
void DivideLine(SAthlete& SAthle, char szLine[EXCEL_MAX_CHARONELINE]);
//��excel�ж�ȡ
void ReadExcel();
////////


///ҵ���߼�
//��Ŀ����
void ItemManagement();
//�˶�Ա����
void AthleteManagement();
//������λ����
void AcademyManagement();
//�ɼ�����
void GradeManagament();
//ϵͳ���ù���
void SystemManagement(bool&pwdFlag, char* szTitle);
//��������
void ProgramManagement();

//ϵͳ��ʼ��
void SystemInit(bool& pwd, char* szTitle, int n);