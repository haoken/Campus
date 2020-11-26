#pragma once
#include"allstruct.h"

//=============
//���ܣ���ʼ��������λ��SList
//������SList
//	SList:������λ˳���(SAcademyList)
//�޸����ڣ�2020/5/2
//=============
void InitAcademyList(SAcademyList& SList);

//=============
//���ܣ������µĲ�����λacademy
//������academy
//	academy:������λ�Ľṹ��
//�޸����ڣ�2020/5/2
//=============
void CreateAcademy(SAcademy& academy);

//=============
//���ܣ����ٲ�����λSList
//������SList
//	SList��������λ˳���
//�޸����ڣ�2020/5/2
//=============
void DestroyAcademyList(SAcademyList& SList);

//=============
//���ܣ���ղ�����λ��SList
//������SList
//	SList:������λ˳���
//�޸����ڣ�2020/5/2
//=============
void ClearAcademyList(SAcademyList& SList);

//=============
//���ܣ�������ΪszAcademyName[]�Ĳ�����λ�ڲ�����λ��SList�е�λ��
//������SList��szAcademyName[]
//	SList:������λ��
//	szAcademyName[]:Ҫ���ҵĲ�����λ������
//���أ�����ҵ�������Ӧ��λ�ã����û���ҵ�����-1
//�޸����ڣ�2020/5/2
//=============
int LocateAcademy(SAcademyList& SList, char szAcademyName[]);

//=============
//���ܣ���Ӳ�����λacademy��������λ�б�SList
//������SList��academy
//	SList��������λ�б�
//	academy��������λ�ṹ��
//���أ�����ɹ��򷵻�0
//�޸����ڣ�2020/5/2
//=============
int AddAcademy(SAcademyList& SList, SAcademy academy);

//=============
//���ܣ�ɾ��������λ�б�SList�У���ΪszAcademyName[]�Ĳ�����λ
//������SList��szAcademyName
//	SList:������λ�б�
//	szAcademyName:������λ��
//���أ�ɾ���ɹ��򷵻�0
//�޸����ڣ�2020/5/2
//=============
int DeleteAcademy(SAcademyList& SList, char* szAcademyName);

//=============
//���ܣ��޸Ĳ�����λ�б�SList����ΪszAcademyName[]�Ĳ�����λ
//������SList��szAcademyName
//	SList:������λ�б�
//	szAcademyName:������λ��
//���أ��޸ĳɹ��򷵻�0
//�޸����ڣ�2020/5/2
//=============
int ModifyAcademy(SAcademyList& SList, char* szAcademyName);

//=============
//���ܣ���ʾ������λ�б�SList
//������SList
//	SList:������λ�б�
//�޸����ڣ�2020/5/2
//=============
void DisplayAcademyList(SAcademyList& SList);

//=============
//���ܣ���������λSListд���ļ�academyinfo.txt��
//������SList
//	SList��������λ�б�
//�޸����ڣ�2020/5/2
//=============
int WriteAcademyListFile(SAcademyList& SList);

//=============
//���ܣ����ļ�academyinfo.txt�ж�ȡ������λ��SList
//������SList
//	�����ڣ�SList��������λ�б�
//�޸����ڣ�2020/5/2
//=============
int ReadAcademyListFile(SAcademyList& SList);

//=============
//���ܣ�������λ����ɾ�Ĳ飬��������ĺ���ʵ��
//���ڣ�2020/5/2
//=============
void AcademyManagement();