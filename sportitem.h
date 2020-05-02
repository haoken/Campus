////////////////////////////////////////////
//�ļ�˵��
//���̣�MyCampusSportSystem
//���ߣ���κ�
//��������Ŀ�����ɾ�ò鹦��
//��Ҫ������
//			void InitItemList(SItemList& SList);//��ʼ����Ŀ��
//			int LocateItem(SItemList& SList, char szItemIDorName[]);//��ѯĳ����Ŀ����Ŀ���е�λ��
//			int AddItem(SItemList& SList, SSportItem SItem);//��ĳ����Ŀ��ӵ���Ŀ���ĩβ
//			int DeleteItem(SItemList& SList, char szItemIDorName[]);//ɾ����Ŀ���ĳ����Ŀ
//			int ModifiItem(SItemList& SList, char szItemIDorName[]);//�޸���Ŀ����ĳ����Ŀ����Ϣ
//			int WriteItemListFile(SItemList& SList);//����Ŀ��д��iteminfo.txt�ļ���
//			int ReadItemListFile(SItemList& SList);//��iteminfo.txt�ļ��ж�ȡ��Ŀ��Ϣ���������Ŀ����
//������ڣ�2020/3/18 /12��26
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
	SPORTTYPE_FIELD,//����
	SPORTTYPE_TRACK//����
};

typedef struct SSportItem {
	char szItemID[10];//��Ŀ���
	char szItemName[20];//��Ŀ����
	enum SPORTTYPE SPORTYPE_itemtype;//��Ŀ���
	double dItemTime;//ÿ������ʱ�����Է���Ϊ��λ
	double dResult;//��Ŀ�ɼ�
}SSportItem;

typedef struct SItemList {//��̬�洢�ṹ˳���
	SSportItem* pSItemList;//����
	int nListLength;//˳���ʵ�ʳ���
	int nListSize;//˳��������ڴ�
}SItemList;

//=============
//���ܣ� ���û�����SSportItem�ṹ��Ա��ֵ
//������ SItem: SSportItem�ṹ���ͱ�������
//˼·�� ʹ��scanf_s������ṹ��Ա��ֵ
//���÷�����SSportItem item;
//                   CreateItem(item);
//�޸����ڣ�2020/3/13/17:55
//=============
void CreateItem(SSportItem& SItem);

//=============
//���ܣ���ʾSSportItem�ṹ����
//������SItem: SSportItem�ṹ���ͱ�������
//˼·��ʹ��printf��ӡ����
//���÷�����SSportItem item;
//                    DisplayItem(item);
//���ڣ�2020/3/13/17��58 
//=============
void DisplayItem(const SSportItem& SItem);

//=============
//���ܣ���ʾ��Ŀ������
//������SList
//	SList:��Ŀ��SItemList
//���ڣ�2020/3/13/23:49
//=============
void DisplayItemList(const SItemList& SList);

//=============
//���ܣ���ʼ����Ŀ��
//������SList: SItemList���ͱ�������
//˼·������mallocΪ˳�������ڴ�ռ�
//���÷�����SItemList List;
//                    InitItemList(List);
//�޸�����:2020/3/13/18:07
//=============
void InitItemList(SItemList& SList);

//=============
//���ܣ�������Ŀ��
//������SList
//	SList:��Ҫ���ٵ���Ŀ��
//˼·����̬�洢�ṹ˳�������ٲ���
//�޸�ʱ�䣺2020/3/26/23��21
//=============
void DestroyItemList(SItemList& SList);

//=============
//���ܣ������Ŀ��Ż�������ΪszItemIDorName����Ŀ������Ŀ��SList�У��򷵻ظ���Ŀ��λ�ã����򷵻�-1.
//������SList,szItemIDorName[]
//	SList:��Ŀ�������
//	szItemIDorName[]:��Ҫ���ҵ���Ŀ�ı�Ż�������
//���أ���Ŀ���ڣ�������Ŀλ�ã�
//            ��Ŀ�����ڣ�����-1.
//˼·��ͨ��ѭ���Ƚϵķ���������Ŀ��������Ŀ��λ��
//���ڣ�2020/3/13/21��52
//=============
int LocateItem(SItemList& SList, char szItemIDorName[]);

//=============
//���ܣ�����Ŀ��ĩβ������Ŀ������ɹ�����0��ʧ�ܷ���-1
//������List,SItem
//	List:��Ŀ��SItemList������
//	SItem:��Ҫ�������Ŀ
//���أ�����ɹ�����0
//            ���˶������߱���ظ��򷵻�-1
//���÷���������Ŀ�����Ҫ�������Ŀ�ֱ��뺯������
//���ڣ�2020/3/13/21��29
//=============
int AddItem(SItemList& SList, SSportItem SItem);

//=============
//���ܣ�ɾ����Ŀ��SList�б�Ż�����ΪszItemIDorName����Ŀ��ɾ���ɹ�����0�����򷵻�-1
//������SList,szItemIDorName
//	SList:��Ŀ˳���(SItemList)
//	szItemIDorName:һ���ַ��������Դ�����Ŀ���ƻ�����Ŀ���
//���أ�ɾ���ɹ�����0���Ҳ�����Ŀ����-1
//˼·��ѭ���Ƚϣ��ҵ���Ŀλ�á�
//            ��szItemIDorName��������������ǰ�������ƺͱ�Ų��ܴ󣬲��������ƺͱ����ͬ�����
//���ڣ�2020/3/13/22��41
//=============
int DeleteItem(SItemList& SList, char szItemIDorName[]);

//=============
//���ܣ�����Ŀ��SList�в�����Ŀ��������Ŀ���ΪszItemIDorName ����Ŀ���������޸�
//������SList��szItemIDorName
//	SList:��Ŀ��(SItemList)
//	szItemIDorName: ��Ҫ�޸ĵ���Ŀ��������Ŀ���
//���أ��޸ĳɹ�����0���Ҳ�����Ŀ����-1
//˼·������LocateItem�ҵ���Ŀλ�ã���ѡ����Ҫ�޸ĵ����ݽ����޸ġ�
//���ڣ�2020/3/14/10:16
//=============
int ModifiItem(SItemList& SList, char szItemIDorName[]);

//=============
//���ܣ�����Ŀ����ÿ��SSportItem�ṹд��iteminfo.txt��
//            ���д��ļ���ģʽΪ"w",����ÿд��һ���ṹ����һ�����з�'\n'��
//������SList
//	SList:��Ŀ��(SItemList)
//���أ�д��ɹ�����0
//˼·��ѭ��д��
//Σ�գ���������Ὣiteminfo.txt�ļ����ǵ�
//                    ������ȷ���÷����Ƚ��ļ��е���Ŀ��������Ŀ���С�
//                    ����Ŀ����в������ڰ������Ŀ��д�뵽�ļ��С�
//���ڣ�2020/3/14/11:33
//=============
int WriteItemListFile(SItemList& SList);

//=============
//���ܣ���iteninfo.txt�ļ��ж�ȡ�����е���Ŀ��Ϣ����ŵ���Ŀ��SList��
//������SList
//	SList����Ŀ��(SItemList)
//���أ���ȡ������-1  ��ȡ�ɹ�����0
//˼·��ע���д���ļ��ĸ�ʽ���Ӧ����д��ʱ������һ�����з�����ȡʱ��Ҫ��������з���ȡ��
//���ڣ�2020/3/14/12��41
//=============
int ReadItemListFile(SItemList& SList);

