////////////////////////////////////////////
//�ļ�˵��
//���̣�MyCampusSportSystem
//���ߣ���κ�
//���������ļ��ṩ���鹦�ܣ��ɰ���Ŀ���飬�ɰ�������λ���顣���ṩ��ز������ڷ���Ļ�����ʵ���˶�Ա��Ϣ�Ĳ�ѯ���ܡ�
//��Ҫ������
//			void ConnectItemList(SGroupList& SGroups,SItemList& SItems)//���ݴ������Ŀ��������֮��Ӧ����Ŀ�����
//			void ConnectAthleteList(SGroupList& SGroups, SAthleteList& SAthletes)//���ݴ�����˶�Ա�б��������顣
//			void InputResult(char szItemIDorName[])//����ĳ����Ŀ�˶�Ա�ɼ�
//������ڣ�2020/3/18 /12��26
/////////////////////////////////////////////

#pragma once

#ifndef __itemgroup_H__
#define __itemgroup_H__
#endif

#include<math.h>
#include<iostream>
#include"sportitem.h"
#include"athlete.h"

using namespace std;

#define MAXGROUPNUMBER 6 //ÿ����Ŀ��������Ŀ

//��Ŀ���飬ÿ����ĿSSportItem���Ǹ�һ������SItemGroup
typedef struct SItemGroup {
	char szItemName[20];
	char szItemID[20];
	SPORTTYPE SPORTTYPE_SportType;
	int nFemaleGroupNumber;//Ů�ӷ�������
	SAthleteList SFemaleAthleteList;//����Ů������,�������гɼ�������
	SAthleteList SFemaleGroups[MAXGROUPNUMBER];//ÿ��Ů�ӷ��������
	int nMaleGroupNumber;//�������������
	SAthleteList SMaleAthleteList;//������������,�������гɼ�������
	SAthleteList SMaleGroups[MAXGROUPNUMBER];//ÿ�����ӷ��������
}SItemGroup;

//��Ŀ�����
typedef struct SGroupList {
	SItemGroup* pSItemGroupList;
	int nListLength;
	int nListSize;
}SGroupList;

//==============
//���ܣ�������ʽĳ����Ŀ��������
//������SGroup
//	SGroup:��Ŀ���飨SItemGroup��
//˼·����dos����ʾ�����ڲ��Ժ���������ȷ��
//�޸�ʱ�䣺2020/3/17/13��27
//==============
void DisplayItemGroup(SItemGroup& SGroup);

//==============
//���ܣ���ʼ����Ŀ�����б�����Ŀ�������
//������SGroups,SItems
//	SGroups:��Ŀ���������Ŀ��һһ��Ӧ
//	SItems:��Ŀ��
//˼·��ĳ����Ŀ��������Ŀ������е�λ�ã��͸���Ŀ����Ŀ���λ����ͬ���Ӷ���һһ��Ӧ��Ч��
//ע�⣺�ú�����������Ŀ�����ĳ�ʼ�������������ڶ���Ŀ�������в���ǰӦ�ȵ��øú�����
//�޸�ʱ�䣺2020/3/17
//==============
void ConnectItemList(SGroupList& SGroups,SItemList& SItems);

//==============
//���ܣ������˶�Ա��SAthletes����ø�����Ŀ�ķ�����Ϣ
//������SGroups,SAthletes
//	SGroups:��Ŀ�����������Ϣ�洢��SGroups�ṹ�С�
//	SAthletes:�˶�Ա�ܱ�
//ʵ�ֲ��裺
//	1.���˶�Ա�ܱ��г�ȡ��������ĳһ����Ŀ���˶�Ա���ú���CreateItemAthleteList��
//	2.�ٴ�������з���������˶�Ա���Ů���˶�Ա���ú���CreateFemaleAthleteList,CreateMaleAthleteList��
//	3.�����Ҫ��ÿһ���е��˶�Ա�������Բ�ͬ�Ĳ�����λ
//	4.���շ����Ҫ����飨��GroupingAthlete������
//ע�⣺�ڵ��øú���֮ǰ��Ӧ�ȵ���ConnectItemList��������Ŀ�������г�ʼ����������Ŀ�������ӡ�
//�޸�ʱ�䣺2020/3/17/13��44
//==============
void ConnectAthleteList(SGroupList& SGroups, SAthleteList& SAthletes);

//==============
//���ܣ��ֱ��������˶�Ա��Ů�����˶�Ա���շ���Ҫ��ֵ����ɸ����С�
//����:SFemaleAthleteList,SMaleAthleteList,ItemGroup
//	SFemaleAthleteList:����Ŀ��Ů�����˶�Ա��
//	SMaleAthleteList:����Ŀ���������˶�Ա��
//	ItemGroup: ����Ŀ�ķ��������SItemGroup��
//˼·�������ڼ��������㷨���Ƚ��˶�Ա���ղ�����λ��Ͱ��Ȼ��ÿ����˶�Ա��˳���ÿ��Ͱ�г�ȡһ�˼����Լ����С�
//�޸����ڣ�2020/3/17/13��53
//==============
void GroupingAthlete(SAthleteList& SFemaleAthleteList, SAthleteList& SMaleAthleteList, SItemGroup& ItemGroup);

void DestroyItemGroupList(SGroupList& SList);

//===============
//���ܣ���ĳ����Ŀ�������ĳɼ�ȫ��¼�롣
//������szItemIDorName[]
//	szItemIDorName[]:��Ҫ����ɼ�����Ŀ
//˼·��������Ŀ�������˶�Ա��Ϣ����󣬰�˳������ɼ�
//�޸����ڣ�2020/3/26/20��07
//===============
void InputResult(char szItemIDorName[]);

//===============
//���ܣ������в�����λʱnAcademy���˶�Ա��ŵ�athletelist�˶�Ա�б���
//������athletelist,nAcademy
//	athletelist:�˶�Ա�б���Ҫ�ȳ�ʼ��,�ٴ���������
//	nAcademy:������λ�����
//	֪����Ժ = 1, ˼Դ��Ժ = 2, ������Ժ = 3,
//	��һ��Ժ = 4, ������Ժ = 5, ��Զ��Ժ = 6,
//	������Ժ = 7, ��ܰ��Ժ = 8, �о���Ժ = 9
//˼·��ѭ���Ƚ�
//�޸����ڣ�2020/3/26/20��16
//===============
void AcademyGroup(SAthleteList& athletelist, int nAcademy);

//===============
//���ܣ�����Ƿ�������Ŀ�������˶�Ա�Ѿ�����ɼ�
//������group
//	group:ĳһ����Ŀ����Ŀ����
//���أ��Ѿ�������ɷ���1
//            ������δ������뷵��0(Ů�������)
//            Ů����δ������뷵��-1(���������)
//            �������Ů���鶼û����ɷ���-2
//˼·���������
//�޸�ʱ�䣺2020/3/26/21��38
//===============
int FinishInputResult(SItemGroup& group);

//===============
//���ܣ����Ѿ�����ɼ������Ŀ���鴫�뺯����Ȼ��������Ŀ�����е��������Ů����
//���˶�Ա���ݸ���Ŀ�ɼ��Ӹߵ�������
//������group
//	group:��Ŀ����ṹ�塣��ע�⣺��ʱ�Ľṹ����Ҫȫ������ɼ���
//���أ���������ɹ�����1������ʧ�ܷ���0
//˼·��ѡ������
//�޸�ʱ�䣺2020/3/26/21��24
//===============
int RankItemGroupAthleteList(SItemGroup& group);

//==============
//���ܣ���ʾ��Ŀ����Ϣ���Ա���sportitem.h�е�DisplayItem����������ʾ�˸���Ŀ�ı�������
//������SItem
//	SItem:��Ŀ�ṹ��
//�޸�ʱ�䣺2020/4/1/14��56
//==============
void DisplayItemWithNumber(SSportItem& SItem);

//==============
//���ܣ���ʾ��Ŀ�����Ϣ���Ա�sportitem.h�е�DisplayItemList������ʾ��Ŀ���������Ĺ���
//������SList
//	SList:��Ŀ��
//�޸�ʱ�䣺2020/4/1/14��57
//==============
void DisplayItemListWithNumber(SItemList& SList);