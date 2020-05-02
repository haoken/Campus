////////////////////////////////////////////
//�ļ�˵��
//���̣�MyCampusSportSystem
//���ߣ���κ�
//���������ļ��ṩ���˶�Ա����ɾ���˶�Ա��Ϣ����ɾ�Ĳ飬�˶�Ա��Ϣ���ļ���д������صĲ���
//��Ҫ������
//			void InitAthleteList(SAthleteList& SList)//��ʼ���˶�Ա��
//			void DestroyAthleteList(SAthleteList& SList)//�����˶�Ա��
//			int AddAthlete(SAthleteList& SList, SAthlete SAthle)//�˶�Ա���Ԫ�����Ӳ���
//			int DeleteAthlete(SAthleteList& SList, char szAthleteIDorName[])//�˶�Ա���Ԫ��ɾ������
//			int ModifiAthlete(SAthleteList& SList, char szAthleteIDorName[])//�˶�Ա����Ԫ����Ϣ���޸Ĳ���
//			int WriteAthleteListFile(SAthleteList& SList)//�˶�Ա��Ϣд��athleteinfo.txt
//			int ReadAthleteListFile(SAthleteList& SList)//��athleteinfo.txt�ж�ȡ�˶�Ա��Ϣ
//			void AthleteFIlEUpdate_ItemModify(SSportItem& SItem)//����Ŀ��Ϣ�޸�ʱ��althleteinfo.txt����Ϣ���²���
//			void AthleteFILEUpdate_ItemDelete(char szItemIDorName[])//����Ŀ��Ϣɾ��ʱ��althleteinfo.txt����Ϣ���²�����
//������ڣ�2020/3/18 /12��26
/////////////////////////////////////////////

#pragma once

#ifndef __athlete_H__
#define __athlete_H__
#endif

#include<stdio.h>
#include<iostream>

#include "sportitem.h"

using namespace std;

#define MAXATHLETESIZE 200 //�˶�Ա˳����ʼ���䳤��
#define INCREASEATHLETESIZE 10 //�˶�Ա˳����������ӵĳ���
#define ACADEMYNUMBER 9 //��Ժ����(������λ����)

//�˶�Ա������Ժ��
typedef enum Academy {
	֪����Ժ=1,
	˼Դ��Ժ,
	������Ժ,
	��һ��Ժ,
	������Ժ,
	��Զ��Ժ,
	������Ժ,
	��ܰ��Ժ,
	�о���Ժ
}Academy;

//�Ա�
typedef enum Gender {
	GENDER_FEMALE,//Ů��
	GENDER_MALE//����
}Gender;

//�˶�Ա�ṹ��������Ϊ�˶�Ա�Ļ�����Ϣ
typedef struct SAthlete {
	char szAthleteName[20];
	char szAthleteID[20];
	Gender AthleteGender;
	int nSItemNumber;
	SSportItem SAthleteItem[3];//��౨������Ŀ
	Academy academy;
}SAthlete;

//�˶�Ա�б���Ԫ��ΪSAthlete���͵�����
typedef struct SAthleteList {
	SAthlete* pSAthleteList;
	int nListLength;
	int nListSize;
}SAthleteList;

//================
//���ܣ���ʼ���˶�Ա�б�
//������SList
//	SList:�˶�Ա�б�SAthleteList���ͣ�
//˼·����Ϊ��̬˳�������ڴ棬��nListLength��ֵΪ0;
//�޸����ڣ�2020/3/17/11��54
//================
void InitAthleteList(SAthleteList& SList);

//================
//���ܣ������˶�Ա�б�
//������SList
//	SList:�˶�Ա�б�
//˼·���ͷŶ�̬������ڴ棬���ѳ��Ⱥʹ�С����Ϊ0
//�޸����ڣ�2020/3/17/11��56
//================
void DestroyAthleteList(SAthleteList& SList);

//================
//���ܣ���dos�����˶�ԱSAthle����Ϣ
//������SAthle
//	SAthle:�˶�Ա�Ľṹ��SAthlete���ͣ�
//˼·����dos���룬���ڲ������������Ƿ�����
//�޸����ڣ�2020/3/17/11��58
//================
void InputAthleteInfo(SAthlete& SAthle);

//================
//���ܣ���dos����ʾ�˶�ԱSAthle��ѡ��ĿSAthle.SAthleteItem[3]����Ϣ��
//������SAthle
//	SAthle:�˶�Ա�Ľṹ��SAthlete���ͣ�
//˼·�����ڲ��Ժ��������Ƿ�����
//�޸����ڣ�2020/3/17/12��01
//================
void DisplayAthleteItem(const SAthlete& SAthle);

//================
//���ܣ���dos����ʾ�˶�ԱSAthle��������Ϣ
//������SAthle
//	SAthle:�˶�Ա�ṹ��SAthlete���ͣ�
//˼·�����ڲ��Ժ��������Ƿ�������
//�޸ģ�2020/3/17/12��03
//================
void DisplayAthleteInfo(const SAthlete& SAthle);

//================
//���ܣ���dos����ʾ�˶�Ա�б�SList�������˶�Ա����Ϣ
//������SList
//	SList:�˶�Ա�б�SAthleteList���ͣ�
//˼·�����ڲ��Ժ��������Ƿ�������
//�޸ģ�2020/3/17/12��05
//================
void DisplayAthleteListInfo(const SAthleteList& SList);

//==================
//���ܣ����˶�Ա�б����Ϣ�ֿ���������������ÿ�����10���ˡ���ʾ��group-1��10+0~9���˶�Ա
//������SList��group
//	SList:�˶�Ա�б�
//	group:����
//����:�������������Ѿ�����SList������������򷵻�-1.���򷵻�0
//���÷���:������Ҫ���1~10��10���˶�Ա��������group==1�����û���㹻10�����˶�Ա������ʾʣ�µ��˶�Ա
//�޸�ʱ�䣺2020/4/9/9:32
//==================
int DisplayAthleteListdepartInfo(const SAthleteList& SList,int group);

//================
//���ܣ�ͨ���˶�Ա��ID���������������˶�Ա���˶�Ա�б�SList�е�λ��
//������SList��szAthleteIDorName[]
//	SList:�˶�Ա�б�SAthleteList���ͣ�
//	szAthleteIDorName[]:�ַ������������˶�Ա��ID��������
//���أ��ҵ����������ֻ�IDΪszAthleteIDorName���˶�Ա���б�SList�е��±꣬�±��0��ʼ
//            �Ҳ���������-1
//˼·��ѭ���Ƚϣ������ҵ��ĵ�һ���˶�Ա���±�
//�޸����ڣ�2020/3/17/12:09
//================
int LocateAthlete(SAthleteList& SList, char szAthleteIDorName[]);

//================
//���ܣ������˶�Ա�б�SList�е�һ��������ԺΪnAcademyIndex���˶�Ա��λ��
//������SList��nAcademyIndex
//	SList:�˶�Ա˳���
//	nAcademyIndex:Ҫ���ҵ���Ժ��ţ���ŷ�Χ��Academyö�ٳ����ķ�Χ
//���أ��ҵ��������˶�Ա�б��е�һ����ԺΪnAcademyIndex ���˶�Աλ��
//            �Ҳ���������-1
//˼·��ѭ���Ƚϣ�����������ڸ��˶�Ա����ʱʹ�ã���������ʵ��ÿ�����о���������ͬ������λ�˶�Ա�Ĺ��ܡ�
//�޸����ڣ�2020/3/17/12:13
//================
int LocateAthleteAcademy(SAthleteList& SList, int nAcademyIndex);

//================
//���ܣ������˶�ԱSAthle����Ŀ�����߱��ΪszItemIDorName����Ŀ��SAthle.SAthleteItem[3]�е�λ�á�
//������SAthle,szItemIDorName[]
//	SAthle:�˶�Ա
//	szItemIDorName[]:�ַ�������Ŀ�����ƻ��߱��
//���أ��ҵ���������Ŀ���˶�Ա��ѡ����Ŀ�е�λ��
//            �Ҳ���������-1
//˼·��ѭ���Ƚϣ�����������ڻ��ĳ����Ŀ�ı�������
//�޸����ڣ�2020/3/17/12:36
//================
int LocateAthleteItem(SAthlete& SAthle, char szItemIDorName[]);

//================
//���ܣ����˶�Ա�б�SListĩβ������˶�ԱSAthle
//������SList,SAthle
//	SList:�˶�Ա�б�(SAthleteList)
//	SAthle:�˶�Ա(SAthlete)
//���أ���ӳɹ�����0
//            ���˶�Ա�Ѵ����б��з���-1
//˼·���ҵ�ĩβ��λ�ã����ṹ��SAthle��ֵ����λ�á�
//�޸����ڣ�2020/3/17/12��32
//================
int AddAthlete(SAthleteList& SList, SAthlete SAthle);

//================
//���ܣ����˶�Ա�б�SList��ɾ�� ���ֻ�ѧ��ΪszAthleteIDorName[]���˶�Ա
//������SList,szAthleteIDorName[]
//	SList:�˶�Ա�б�
//	szAthleteIDorName[]:�ַ���������Ҫɾ�����˶�Ա���������߱��
//���أ�ɾ���ɹ�����0
//            �б��в����ڸ��˶�Ա����-1��
//˼·��ѭ���Ƚ�
//�޸����ڣ�2020/3/17/13��02
//================
int DeleteAthlete(SAthleteList& SList, char szAthleteIDorName[]);

//================
//���ܣ����˶�Ա�б�SList��ɾ���±�δnPos_athlete���˶�Ա,�Ƕ����溯��������
//������SList,nPos_athlete
//	SList:�˶�Ա�б�
//	nPos_athlete:��Ҫɾ�����˶�Ա��λ��
//���أ�ɾ���ɹ�����0. ɾ��ʧ�ܷ���-1
//˼·����̬˳����ɾ������
//�޸����ڣ�2020/3/26/22��46
//================
int DeleteAthlete(SAthleteList& SList, int nPos_athlete);

//================
//���ܣ�SAthle�˶�Ա������������Ŀ�У��������һ������IDΪszItemIDorName����Ŀ���������Ŀɾ����
//������SAthle,szItemIDorName[]
//���أ�ɾ���ɹ�����0
//           �����˶�Աû��ѡ�����Ŀ���򷵻�-1
//˼·��ѭ���Ƚ�+�����ɾ���������������
//�޸����ڣ�2020/3/18/11��23
//================
int DeleteAthleteItem(SAthlete& SAthle,char szItemIDorName[]);

//================
//���ܣ��޸��˶�Ա�б�SList�����ֻ��߱��ΪszAthleteIDorName[]���˶�Ա����Ϣ
//������SList��szAthleteIDorName[]
//	SList:�˶�Ա�б�
//	szAthleteIDorName[]:�ַ�����������Ҫ�޸ĵ��˶�Ա������ֻ��߱��
//���أ��޸ĳɹ�����0
//            �б����Ҳ����˶�Ա����-1
//˼·��ѭ���Ƚ��ҳ����˶�Ա��λ�ã�ͨ��dos�����޸ĸ����˶�Ա����Ϣ
//�޸�ʱ�䣺2020/3/17
//================
int ModifiAthlete(SAthleteList& SList, char szAthleteIDorName[]);

//================
//���ܣ����˶�Ա�б����Ϣд���ļ�athleteinfo.txt��.�����ļ���mode��"w"��
//������SList
//	SList:�˶�Ա�б�
//���أ�д��ɹ�����0
//˼·��������б��е��˶�Ա�ṹд���ļ���.
//Σ�գ��ڵ����������֮��athleteinfo.txt�ᱻ���ǣ�����Ӧ��ʹ��ReadAthleteListFile���ļ����ݶ�ȡ��SList�к������Ҫ�Ĳ������ٰ�SListд�뵽�ļ��С�
//�޸�ʱ�䣺2020/3/17/13��09
//================
int WriteAthleteListFile(SAthleteList& SList);

//================
//���ܣ����ļ�athleteinfo.txt�е��˶�Ա��Ϣ��ȡ��SList�˶�Ա�б��У����ļ���mode��"r"��
//������SList�����ڲ�����
//	SList���˶�Ա�б����������ļ����˶�Ա��Ϣ
//���أ���ȡ�ɹ�����0
//˼·������˶�Ա�ṹ��ȡ
//�޸�ʱ�䣺2020/3/17/13��12
//================
int ReadAthleteListFile(SAthleteList& SList);

//================
//���ܣ����˶�Ա�������г�ȡ������ĳ����Ŀ������
//������SList,SItemAthleteList,szItemIDorName[]
//	����ڣ�SList:�˶�Ա�б�
//	�����ڣ�SItemAthleteList:SList������ѡȡ��ĳ����Ŀ������
//	����ڣ�szItemIDroName[]:��Ŀ��ID��������
//˼·��ѭ���Ƚϣ��˺���������ñ���ĳ����Ŀ��������
//�޸�ʱ�䣺2020/3/17/13��18
//================
void CreateItemAthleteList(SAthleteList& SList, SAthleteList& SItemAthleteList, char szItemIDorName[]);

//=================
//���ܣ���һ���˶�Ա����SList�г�ȡŮ���˶�Ա�ŵ�SFemaleAthleteList�˶�Ա�����С�
//������SList,SFemaleAthleteList
//	����ڣ�SList:�˶�Ա����
//	�����ڣ�SFemaleAthleteList:Ů���˶�Ա����
//˼·��ѭ���Ƚϣ��˺���������ΪŮ��������׼������
//�޸�ʱ�䣺2020/3/17/13��22
//=================
void CreateFemaleAthleteList(SAthleteList& SList, SAthleteList& SFemaleAthleteList);

//=================
//���ܣ���һ���˶�Ա����SList�г�ȡ�����˶�Ա�ŵ�SMaleAthleteList�˶�Ա�����С�
//������SList,SMaleAthleteList
//	����ڣ�SList:�˶�Ա����
//	�����ڣ�SMaleAthleteList:Ů���˶�Ա����
//˼·��ѭ���Ƚϣ��˺���������Ϊ����������׼������
//�޸�ʱ�䣺2020/3/17/13��23
//=================
void CreateMaleAthleteList(SAthleteList& SList, SAthleteList& SMaleAthleteList);

//=================
//���ܣ� ��ĳ����Ŀ�����ı��ʱ����Ҫ�����˶�Ա�ļ���ѡ�����Ŀ����Ϣ
//������SItem
//	SItem:�޸��˵���Ŀ
//˼·��ѭ���Ƚ�ÿ���˶�Ա�ı�����Ŀ�����޸ĵ���Ŀ��ͬʱ�����µ���Ŀ���ǵ�ԭ����λ��
//�޸����ڣ�2020/3/18/10��13
//=================
void AthleteFIlEUpdate_ItemModify(SSportItem& SItem);

//=================
//���ܣ� ��ĳ����Ŀ��ɾ������Ҫ�����˶�Ա�ļ��е�����
//������szItemIDorName[]
//	szItemIDorName[]:��ɾ������Ŀ�����ƻ���ID
//˼·��ѭ���Ƚ�ÿ���˶�Ա�ı�����Ŀ��������ڱ�ɾ������Ŀ���򽫸���Ŀ���˶�Ա������Ŀ��ɾ��
//�޸����ڣ�2020/3/18/10��24
//=================
void AthleteFILEUpdate_ItemDelete(char szItemIDorName[]);