//#pragma once

#ifndef __itemrecord_H__
#define __itemrecord_H__
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXRECORDSIZE 30
#define INCREASERECORDSIZE 5

//�Ա� 
typedef enum Gender {
	GENDER_FEMALE,//Ů��
	GENDER_MALE//����
}Gender;

typedef struct SItemRecord {
	char szRecordID[10];//��¼���
	char szRecordName[20];//��¼����Ŀ����
    double dRecordResult;//��¼�ɼ�
    char szAthleteName[20];//��¼����������
    Gender AthleteGender;//��¼�������Ա� 

}SItemRecord;

//��¼������Ԫ��Ϊ����SItemRecord������
typedef struct SRecordList {
	SItemRecord* pSRecordList;
	int nListLength;  //ʵ�ʳ��� 
	int nListSize;
}SRecordList;


//=============
//���ܣ���ʼ����¼��
//������SList: SRecordList���ͱ�������
//˼·������mallocΪ˳�������ڴ�ռ�
//���÷�����SRecordList recordlist;
//          InitRecordList(recordlist);
//=============
void InitRecordList(SRecordList& SList);

//=============
//���ܣ� ���û�����SItemRecord�ṹ��Ա��ֵ
//������ SRecord: SItemRecord�ṹ���ͱ�������
//˼·�� ʹ��scanf������ṹ��Ա��ֵ
//���÷�����SItemRecord record;
//          CreateRecord(record);
//=============
void CreateRecord(SItemRecord& SRecord);

//=============
//���ܣ������Ŀ����ΪszRecordName����Ŀ��¼���ڼ�¼��SList�У��򷵻ظ���Ŀ��λ�ã����򷵻�-1.
//������SList,szRecordName[]
//	SList:��¼������� 
//	szRecordName[]:��Ҫ���ҵ���Ŀ������
//���أ���Ŀ���ڣ�������Ŀλ�ã�
//            ��Ŀ�����ڣ�����-1.
//˼·��ͨ��ѭ���Ƚϵķ���������Ŀ��������Ŀ��λ��
//=============
int LocateRecord(SRecordList& SList, char szRecordName[]);

//=============
//���ܣ��ڼ�¼��ĩβ����δӵ�е���Ŀ��¼������ɹ�����0��ʧ�ܷ���-1
//������List,SRecord
//���أ�����ɹ�����0������Ŀ���ظ��򷵻�-1
//=============
int AddRecord(SRecordList& SList, SItemRecord SRecord);

//=============
//���ܣ�ɾ����Ŀ��SList��w��i��λ�õļ�¼ 
//������SList,szItemIDorName
//	SList:��¼˳���
//	RecordLocation����¼�ڱ��е�λ�ã�i=LocateRecord������ 
//���أ�ɾ���ɹ�����0���Ҳ�����Ŀ����-1
//˼·��ѭ���Ƚϣ��ҵ���Ŀλ�á�
//=============
int DeleteRecord(SRecordList& SList, char szRecordName[]);

//=============
//���ܣ�����Ŀ��SList�в��ҵ�i����Ŀ���������޸ġ�i=LocateRecord������ 
//������SList��szItemIDorName
//	SList:��Ŀ��(SRecordList)
//	RecordLocation����¼�ڱ��е�λ�ã�i=LocateRecord������ 
//���أ��޸ĳɹ�����0���Ҳ�����Ŀ����-1
//˼·������LocateItem�ҵ���Ŀλ�ã���ѡ����Ҫ�޸ĵ����ݽ����޸ġ�
//=============
int ModifiRecord(SRecordList& SList, char szRecordName[]);


//=============
//���ܣ���ʾSSportItem�ṹ����
//������SItem: SSportItem�ṹ���ͱ�������
//˼·��ʹ��printf��ӡ����
//���÷�����SSportItem item;
//                    DisplayItem(item);
//���ڣ�2020/3/13/17��58 
//=============
void PrintRecord(SItemRecord &SRecord);

//=============
//���ܣ���ʾ��Ŀ������
//������SList
//	SList:��Ŀ��SItemList
//���ڣ�2020/3/13/23:49
//=============
void PrintRecordList(const SRecordList& SList);

//=============
//���ܣ�����Ŀ����ÿ��SItemRecord�ṹд��recordinfo.txt��
//���д��ļ���ģʽΪ"w",����ÿд��һ���ṹ����һ�����з�'\n'��
//������SList
//	SList:��Ŀ��(SRecordList)
//���أ�д��ɹ�����0
//=============
int WriteRecordListFile(SRecordList& SList);

//=============
//���ܣ���recordinfo.txt�ļ��ж�ȡ�����е���Ŀ��Ϣ����ŵ���Ŀ��SRecordList��
//������SList
//	SList����Ŀ��(SRecordList)
//���أ���ȡ������-1  ��ȡ�ɹ�����0
//˼·��ע���д���ļ��ĸ�ʽ���Ӧ����д��ʱ������һ�����з�����ȡʱ��Ҫ��������з���ȡ��
//=============
int ReadRecordListFile(SRecordList& SList);


