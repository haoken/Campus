#pragma once
#include"allstruct.h"

//================
//���ܣ���ʼ���˶�Ա�б�
//������SList
//	SList:�˶�Ա�б�SAthleteList���ͣ�
//˼·����Ϊ��̬˳�������ڴ�
//�޸����ڣ�2020/5/2
//================
void InitAthleteList(SAthleteList& SList);

//================
//���ܣ����˶�Ա�б�SListĩβ������˶�ԱSAthle.
//������SList,SAthle
//	SList:�˶�Ա�б�(SAthleteList)
//	SAthle:�˶�Ա(SAthlete)
//���أ���ӳɹ�����0
//            ���˶�Ա�Ѵ����б��з���-1
//˼·���ҵ�ĩβ��λ�ã����ṹ��SAthle��ֵ����λ�á�
//�޸����ڣ�2020/3/17/12��32
//================
int AddAthlete(SAthleteList& SList, SAthlete SAthle);

//==========
//���ܣ�����˶�Ա��SList
//ʵ�֣���SList.nLength��ֵΪ0
//==========
void ClearAthleteList(SAthleteList& SList);

//==========
//���ܣ������˶�Ա�б�
//ʵ�֣�������Ŀռ��ͷ�
//==========
void DestroyAthleteList(SAthleteList& SList);

//==========
//���ܣ����û�Ϊ�˶�ԱSAthle���������Ϣ��������Ϣ��ͬʱ��������˶�Ա���뵽��������Ŀ��������
//ע�⣺��������ʱ��SAthle��û�м��뵽�ܵ��˶�Ա�б��С�
//            InputAthleteInfo(SAthle);//����������һ��Ҫһ��ţ����ܹ�ʵ���˶�Ա�ļ�����Ŀ�ļ�������ͬ����
//            AddAthlete(allathlete,SAthle);//allathlete�ǰ��������˶�Ա���˶�Ա�б�
//            WriteAthleteListFile(allathlete);//д���ļ���
//==========
void InputAthleteInfo(SAthlete& SAthle);

//==========
//���ܣ��ñ�����ʽ��dos�����ĳ���˶�Ա����Ϣ
//������SAthle��withTitle
//	SAthle:�˶�Ա�Ľṹ��SAthlete���ͣ�
//	withTitle:Ϊ��ʱ,������б��ͷ��д�����������У�
//			  Ϊ��ʱ��������ͷ
//==========
void DisplayAthleteInfo(const SAthlete& SAthle, int withTitle);

//================
//���ܣ���dos����ʾ�˶�Ա�б�SList�������˶�Ա����Ϣ
//������SList
//	SList:�˶�Ա�б�SAthleteList���ͣ�
//˼·�����ڲ��Ժ��������Ƿ�������
//================
void DisplayAthleteListInfo(const SAthleteList& SList);

//================
//���ܣ���ҳ��ʾ�˶�Ա�б��е����ݣ��ú���ֻ��ʾpageҳ�����ݣ�ÿҳ�����NumberPerPage��Ԫ��
//������SList��page,NumberPerPage
//	SList:�˶�Ա�б�SAthleteList���ͣ�
//	page:ҳ��
//	NumberPerPage:ÿҳ����������
//================
void DisplayAthleteListInfo(const SAthleteList& SList, int page, int NumberPerPage);

//================
//���ܣ���ҳ��ʾ�˶�Ա�б��еĶ����ݣ��ú�����������1��2ʵ����һҳ��һҳ�Ĺ��ܡ�
//      �ú����Ῠסֱ���û�����3.���زŻ������������
//������SList��nNumberPerPage
//	SList:�˶�Ա�б�
//	nNumberPerPage:ÿ����������
//================
void DisplayAthleteListPagination(const SAthleteList& SList, int nNumberPerPage);

//================
//���ܣ�ͨ���˶�Ա��ID���������������˶�Ա���˶�Ա�б�SList�е�λ��
//������SList��szAthleteIDorName[]
//	SList:�˶�Ա�б�SAthleteList���ͣ�
//	szAthleteIDorName[]:�ַ������������˶�Ա��ID��������
//���أ��ҵ����������ֻ�IDΪszAthleteIDorName���˶�Ա���б�SList�е��±꣬�±��0��ʼ
//            �Ҳ���������-1
//================
int LocateAthlete(SAthleteList& SList, char szAthleteIDorName[]);

//================
//���ܣ����˶�Ա�б�SList��ɾ�� ���ֻ�ѧ��ΪszAthleteIDorName[]���˶�Ա
//������SList,szAthleteIDorName[]
//	SList:�˶�Ա�б�
//	szAthleteIDorName[]:�ַ���������Ҫɾ�����˶�Ա���������߱��
//���أ�ɾ���ɹ�����0
//            �б��в����ڸ��˶�Ա����-1��
//================
int DeleteAthlete(SAthleteList& SList, char szAthleteIDorName[]);

//================
//���ܣ�ͨ�������˶�Ա�ܱ���ɾ��ĳ���˶�Ա�����ҽ���Ŀ�������еĹ�������˶�Ա����ϢҲɾ��
//������SList,szAthleteIDorName[]
//	SList:�˶�Ա�ܱ�Ҫд���ļ����˶�Ա��
//	szAthleteIDorName[]������˶�Ա�����ֻ���ѧ��
//================
int DeleteAthleteSync(SAthleteList& SList, char szAthleteIDorName[]);

//================
//���ܣ�ͨ�������˶�Ա�ܱ���ɾ��ĳ���˶�Ա�����ҽ���Ŀ�������еĹ�������˶�Ա����ϢҲɾ��
//������SList,nPos_athlete
//	SList:�˶�Ա�ܱ�Ҫд���ļ����˶�Ա��
//	nPos_athlete:�����˶�Ա���˶�Ա�ܱ��е�λ��
//ע�⣺��int DeleteAthleteSync(SAthleteList& SList, char szAthleteIDorName[])ʵ�ֵĹ�����һ���ģ�ֻ����������ͬ
//================
int DeleteAthleteSync(SAthleteList& SList, int nPos_athlete);

//================
//���ܣ������˶�ԱSAthle����Ŀ�����߱��ΪszItemIDorName����Ŀ��SAthle.SAthleteItem[]�е�λ�á�
//������SAthle,szItemIDorName[]
//	SAthle:�˶�Ա
//	szItemIDorName[]:�ַ�������Ŀ�����ƻ��߱��
//���أ��ҵ���������Ŀ���˶�Ա��ѡ����Ŀ�е�λ��
//            �Ҳ���������-1
//================
int LocateAthleteItem(SAthlete& SAthle, char szItemIDorName[]);

//================
//���ܣ�SAthle�˶�Ա������������Ŀ�У��������һ������IDΪszItemIDorName����Ŀ���������Ŀɾ����
//������SAthle,szItemIDorName[]
//���أ�ɾ���ɹ�����0
//           �����˶�Աû��ѡ�����Ŀ���򷵻�-1
//================
int DeleteAthleteItem(SAthlete& SAthle, char szItemIDorName[]);

//================
//���ܣ�SAthle�˶�Ա��������SItem.����SAthle����Ϣ��ӵ���Ŀ�ı�������
//������SAthle��SItem
//	SAthle��Ҫ�����Ŀ���˶�Ա
//	SItem��//Ҫ��ӵ���Ŀ
//���أ���������˶�Ա������Ŀ�Ѵ����ޣ������Ѿ����������Ŀ�����������Ŀ�����ڣ�һ�ɷ���-1
//	�����ӳɹ�����0
//================
int AddAthleteItem(SAthlete& SAthle, SSportItem SItem);

//================
//���ܣ��޸��˶�Ա�б�SList�����ֻ��߱��ΪszAthleteIDorName[]���˶�Ա����Ϣ���޸ĺ����Ŀ�������и����˶�Ա����Ϣ����
//������SList��szAthleteIDorName[]
//	SList:�˶�Ա�б�
//	szAthleteIDorName[]:�ַ�����������Ҫ�޸ĵ��˶�Ա������ֻ��߱��
//���أ��޸ĳɹ�����0
//            �б����Ҳ����˶�Ա����-1
//================
int ModifiAthlete(SAthleteList& SList, char szAthleteIDorName[]);

//================
//���ܣ����˶�Ա�б����Ϣд���ļ�athleteinfo.txt��.�����ļ���mode��"w"��
//������SList
//	SList:�˶�Ա�б�
//���أ�д��ɹ�����0
//Σ�գ��ڵ����������֮��athleteinfo.txt�ᱻ���ǣ�����Ӧ��ʹ��ReadAthleteListFile���ļ����ݶ�ȡ�������к������Ҫ�Ĳ������ٰ�SListд�뵽�ļ��С�
//================
int WriteAthleteListFile(SAthleteList& SList);

//================
//���ܣ����ļ�athleteinfo.txt�е��˶�Ա��Ϣ��ȡ��SList�˶�Ա�б��У����ļ���mode��"r"��
//������SList�����ڲ�����
//	SList���˶�Ա�б����������ļ����˶�Ա��Ϣ
//���أ���ȡ�ɹ�����0
//================
int ReadAthleteListFile(SAthleteList& SList);


//==============
//���ܣ����޸��˶�Ա�Ļ�����Ϣʱ������Щ��Ϣͬ������Ŀ�ı������У�
//������athlete
//	athlete:�޸�����Ϣ���˶�Ա
//ע�⣺Ϊ�˱�֤�˶�Ա�����Ŀ���������Ϣͬ������Ҫÿ���޸��˶�Ա��Ϣ��ÿ��ֻ���޸�ID����Name�е�һ������ʱ����øú���������ͬ������Ŀ��������
//==============
void AthleteSync(SAthlete& athlete);

//==============
//���ܣ���ĳ���˶�Ա��SAthle.SAthleteItem[n]�滻��SItem.Ȼ��ʵ�ֱ������е�ͬ������
//������SAthle,SItem,n
//	SAthle:�˶�Ա
//	SItem:�����滻����Ŀ
//	n:���滻��Ŀ���±�
//==============
int ReplaceAthleteItem(SAthlete& SAthle, SSportItem SItem, int n);




//==============
//���ܣ��˶�Ա����ɾ�Ĳ飬�˶�Ա����
//==============
void AthleteManagement();