#pragma once
#ifndef __sportitem_H__
#define __sportitem_H__
#endif

#include"allstruct.h"

#define ITEMLIST_INIT_SIZE 30 //��Ŀ�б��ʼ�ڴ�
#define INCREASEMENTSIZE 5 //��Ŀ�б�����

//=============
//���ܣ� ���û�����SSportItem�ṹ��Ա��ֵ
//������ SItem: SSportItem�ṹ���ͱ�������
//˼·�� ʹ��scanf_s������ṹ��Ա��ֵ
//���÷�����SSportItem item;
//                   CreateItem(item);
//�޸����ڣ�2020/4/29
//=============
void CreateItem(SSportItem& SItem);

//=============
//���ܣ���ʼ����Ŀ��
//������SList: SItemList���ͱ�������
//˼·������mallocΪ˳�������ڴ�ռ�
//���÷�����SItemList List;
//                    InitItemList(List);
//�޸�����:2020/4/30
//=============
void InitItemList(SItemList& SList);

//==========
//���ܣ������Ŀ��
//������SList��Ŀ��
//==========
void ClearItemList(SItemList& SList);

//==========
//���ܣ�������Ŀ��
//������SList��Ŀ��
//==========
void DestroyItemList(SItemList& SList);

//=============
//���ܣ���ʾSSportItem�ṹ����
//������SItem: SSportItem�ṹ���ͱ�������
//˼·��ʹ��printf��ӡ����
//���÷�����SSportItem item;
//                    DisplayItem(item);
//���ڣ�2020/4/30
//=============
void DisplayItem(SSportItem& SItem,int withTitle);

//=============
//���ܣ������Ŀ��Ż�������ΪszItemIDorName����Ŀ������Ŀ��SList�У��򷵻ظ���Ŀ��λ�ã����򷵻�-1.
//������SList,szItemIDorName[]
//	SList:��Ŀ�������
//	szItemIDorName[]:��Ҫ���ҵ���Ŀ�ı�Ż�������
//���أ���Ŀ���ڣ�������Ŀλ�ã�
//            ��Ŀ�����ڣ�����-1.
//=============
int LocateItem(SItemList& SList, char szItemIDorName[]);

//=============
//���ܣ�����Ŀ��ĩβ������Ŀ������ɹ�����0��ʧ�ܷ���-1
//������List,SItem
//	List:��Ŀ��SItemList������
//	SItem:��Ҫ�������Ŀ
//���أ�����ɹ�����0
//            ���˶������߱���ظ��򷵻�-1
//=============
int AddItem(SItemList& SList, SSportItem SItem);

//=============
//���ܣ�ɾ����Ŀ��SList�б�Ż�����ΪszItemIDorName����Ŀ��ɾ���ɹ�����0�����򷵻�-1��ɾ����ͬʱ������������Ŀ���˶�Աȡ����������Ŀ��
//������SList,szItemIDorName
//	SList:��Ŀ˳���(SItemList)
//	szItemIDorName:һ���ַ��������Դ�����Ŀ���ƻ�����Ŀ���
//���أ�ɾ���ɹ�����0���Ҳ�����Ŀ����-1
//=============
int DeleteItem(SItemList& SList, char szItemIDorName[]);

//=============
//����ͬ��
//������pos:��Ŀ����Ŀ���е�λ��
//=============
int DeleteItem(SItemList& SList, int pos);

//=============
//���ܣ�����Ŀ��SList�в�����Ŀ��������Ŀ���ΪszItemIDorName ����Ŀ���������޸�
//������SList��szItemIDorName
//	SList:��Ŀ��(SItemList)
//	szItemIDorName: ��Ҫ�޸ĵ���Ŀ��������Ŀ���
//���أ��޸ĳɹ�����0���Ҳ�����Ŀ����-1
//=============
int ModifiItem(SItemList& SList, char szItemIDorName[]);

//=============
//���ܣ�����Ŀ�б������е���Ŀ���з��飬ע��÷�����������������ļ��С�
//		ÿ����Ҫ�õ������ʱ��������������Ȼ��ͻ���SSportItem�ṹ���е�**ppAthleteGroup�д����nGroupNumber���˶�Ա�б�
//������SList:����������Ŀ����Ŀ�б�
//=============
int Grouping(SItemList& SList);

//=============
//���ܣ������е���Ŀ�ķ��鰴�ճɼ���������������������ɸߵ��ͣ�����Ǿ��������ɵ͵���
//ʹ�ã���Ҫ��Grouping��������ʹ�ã��ȴ�������ſ��Զ���Щ�����������
//=============
void Ordering(SItemList& SList);

//=============
//���ܣ���ҳ��ʾ�����Ŀ�����з���
//������SItem
//	SItem:��Ŀ
//���أ�ѡ�񷵻�ʱ����ǰ������
//ע�⣬���������Ҫ�ڷ�����ɺ�ſ���ʹ�ã�����Ҫ��Grouping()����
//=============
int DisplayGroupingPagination(SSportItem& SItem);
void DisplayNGroup(SSportItem& SItem, int n);
int DisplayGroupingPagination(SSportItem& SItem,const char* szTitle, const char* szThirdChoice);
//��ҳ��ʾ��Ŀ
void DisplayItemListPagination(const SItemList& SList, int page, int NumberPerPage);
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
//=============
int WriteItemListFile(SItemList& SList);

//=============
//���ܣ���iteninfo.txt�ļ��ж�ȡ�����е���Ŀ��Ϣ����ŵ���Ŀ��SList��
//������SList
//	SList����Ŀ��(SItemList)
//���أ���ȡ������-1  ��ȡ�ɹ�����0
//=============
int ReadItemListFile(SItemList& SList);




//==============
//���ܣ���Ŀ����ɾ�Ĳ飬��Ŀ����
//==============
void ItemManagement();