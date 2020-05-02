#include"record.h"
#include <Windows.h>
#include<iostream>

void InitRecordList(SRecordList& SList){
	SList.pSRecordList = (SItemRecord*)malloc(MAXRECORDSIZE*sizeof(SItemRecord));
	if (!SList.pSRecordList) {
		printf("�ڴ�����");
		exit(0);
	}
	SList.nListSize = MAXRECORDSIZE;
	SList.nListLength = 0;
}

int LocateRecord(SRecordList &SList, char szRecordName[]){//��������ΪSZRecordName����Ŀ�������е�λ�ã����򷵻�i��ֵ�� 
	int nLocation = -1;
	for (int i = 0; i < SList.nListLength; i++) {
		if (strcmp(szRecordName, SList.pSRecordList[i].szRecordName) == 0||strcmp(szRecordName,SList.pSRecordList[i].szRecordID)==0) {
			nLocation = i;
			break;
		}
	}
	return nLocation; 
} 

void CreateRecord(SItemRecord &SRecord){
	printf("\n��������Ŀ��ţ�");
	scanf_s("%s", SRecord.szRecordID, 10);
	printf("\n��������Ŀ���ƣ�");
	scanf_s("%s",SRecord.szRecordName,20);
	printf("\n�������¼������������");
	scanf_s("%s",SRecord.szAthleteName,20);
	int iGender; 
	printf("\n�������¼�������Ա�0 is male or 1 is famale����");
	scanf_s("%d",&iGender);
	if(iGender==0) SRecord.AthleteGender = GENDER_MALE;
	else SRecord.AthleteGender = GENDER_FEMALE;
	printf("\n�������¼�ɼ���");
	scanf_s("%lf",&SRecord.dRecordResult);
}

int AddRecord(SRecordList &SList,SItemRecord SItem){
	
	if (LocateRecord(SList,SItem.szRecordName)!=-1) {
		printf("��¼�Ѵ���\n");
		return -1;
	}
	else {
		SItemRecord* newbase;
		if (SList.nListLength == SList.nListSize) {
			newbase = (SItemRecord*)realloc(SList.pSRecordList,(MAXRECORDSIZE+INCREASERECORDSIZE)*sizeof(SItemRecord));
			SList.nListSize += INCREASERECORDSIZE;
			if (!newbase) {
				printf("�ڴ治��");
				exit(0);
			}
			else {
				SList.pSRecordList = newbase;
			}
		}//if
		SList.pSRecordList[SList.nListLength] = SItem;
		SList.nListLength++;
    } 
	return 0 ;
}

int DeleteRecord(SRecordList& SList, char szRecordName[]){
	int nLocation = LocateRecord(SList, szRecordName);
	if (nLocation == -1) {
			printf("��Ŀ������\n");
			return -1;//��Ŀ���в����������Ŀ��
	}
	for (int i = nLocation; i < SList.nListLength-1; i++) {
		SList.pSRecordList[i] = SList.pSRecordList[i + 1];
	}
	SList.nListLength--;
	return 0;
}

int ModifiRecord(SRecordList& SList, char szRecordName[]){
	int nLocation = LocateRecord(SList, szRecordName);
//	SItemRecord *pRecordLocation = SList.pSRecordList+nLocation-1;
	if (nLocation == -1) {
		printf("��Ŀ������\n");
		return -1;
	}
	else{
		int nChoice = 0;
		printf("\n1.��Ŀ���\n2.��Ŀ����\n3.��¼����������\n4.�Ա�\n5.�ɼ�\n");
		printf("\n����������Ҫ�޸ĵ���Ϣ��");
		scanf_s("%d",&nChoice);
		switch (nChoice)
		{
		case 1:
			printf("�������µ���Ŀ��ţ�");
			scanf_s("%s", SList.pSRecordList[nLocation].szRecordID, 10);
			break;
		case 2: {
			printf("��������Ŀ����");
			scanf_s("%s", SList.pSRecordList[nLocation].szRecordName,20);
			break;
		}
		case 3:
			printf("�������¼������������");
			scanf_s("%s", SList.pSRecordList[nLocation].szAthleteName, 20);
			break;
		case 4: {
			int iGender;
			printf("�������¼�������Ա�0 is male or 1 is famale����");
			scanf_s("%d", &iGender);
			if (iGender == 1) SList.pSRecordList[nLocation].AthleteGender = GENDER_MALE;
			else SList.pSRecordList[nLocation].AthleteGender = GENDER_FEMALE;
			break;
		}
		case 5:
			printf("�������¼�ɼ���");
			scanf_s("%lf", &SList.pSRecordList[nLocation].dRecordResult);
			break;
		default:
			break;
		}		
    }
	return 0;
}

void PrintRecord(SItemRecord& SRecord){
	printf("\t|%-15s", SRecord.szRecordID);
	printf("|%-20s", SRecord.szRecordName);
	printf("|%-20s", SRecord.szAthleteName);
	if (SRecord.AthleteGender == GENDER_FEMALE)
		printf("|Ů\t");
	else
		printf("|��\t");
	printf("|%.2lf\t\n", SRecord.dRecordResult);
} 

int WriteRecordListFile(SRecordList& SList) {
	FILE* pFRecordFile;
	errno_t err = fopen_s(&pFRecordFile,"recordinfo.txt","w");
	if (err != 0) {
		printf("�ļ���ȡ����");
		exit(0);
	}
	if (pFRecordFile) {
		for (int i = 0; i < SList.nListLength; i++) {
			fwrite(&SList.pSRecordList[i], sizeof(SItemRecord), 1, pFRecordFile);
			fputc('\n', pFRecordFile);
		}
		fclose(pFRecordFile);
	}
	return 0;
}
	
int ReadRecordListFile(SRecordList& SList){
	FILE* pFRecordFile;
	errno_t err = fopen_s(&pFRecordFile, "recordinfo.txt", "r");
	if (err != 0) {
		printf("�ļ���ȡ����");
		exit(0);
	}
	SItemRecord SRecord;
	if (pFRecordFile) {
		fread(&SRecord, sizeof(SItemRecord), 1, pFRecordFile);
		fgetc(pFRecordFile);
		while (!feof(pFRecordFile)) {//feof()��ȡ��EOFʱ����true�����򷵻�false
			if (ferror(pFRecordFile)) {//ferror()��ȡ����ʱ����true,���򷵻�false 
				clearerr(pFRecordFile);
				printf("�ļ���ȡ����");
				exit(0);
			}
			AddRecord(SList, SRecord);
			fread(&SRecord, sizeof(SItemRecord), 1, pFRecordFile);
			fgetc(pFRecordFile);
		}//while
		fclose(pFRecordFile);
	}//if
	return 0;
}

void PrintRecordList(SRecordList& SList) {
	printf("\t|%-15s","��¼���");
	printf("|%-20s", "��¼����");
	printf("|%-20s", "�˶�Ա����");
	printf("|�Ա�\t");
	printf("|�ɼ�\t\n");
	for (int i = 0; i < SList.nListLength; i++) {
		printf("\t________________________________________________________________________________________\n");
		PrintRecord(SList.pSRecordList[i]);
	}
	printf("\n\n\n");
}

void menu_record() {
	printf("\n1.��Ӽ�¼");
	printf("\n2.ɾ����¼");
	printf("\n3.�޸ļ�¼");
	printf("\n4.���沢�˳�\n");
	printf("���ѡ��");
}
//
//int main(void){
//	SItemRecord record;
//	SRecordList recordlist;
//	InitRecordList(recordlist);
//	ReadRecordListFile(recordlist);
//	while (true) {
//		system("cls");
//		PrintRecordList(recordlist);
//		menu_record();
//		int nChoice = 0;
//		scanf_s("%d", &nChoice);
//		switch (nChoice)
//		{
//		case 1:
//			CreateRecord(record);
//			AddRecord(recordlist, record);
//			break;
//		case 2: {
//			char szIdorname[20];
//			printf("\n��������Ҫɾ���ļ�¼��Ż�������:");
//			scanf_s("%s", szIdorname, 20);
//			DeleteRecord(recordlist, szIdorname);
//			break;
//		}
//		case  3: {
//			char szIdorname[20];
//			printf("\n��������Ҫɾ���ļ�¼��Ż�������:");
//			scanf_s("%s", szIdorname, 20);
//			ModifiRecord(recordlist, szIdorname);
//			break;
//		}
//		default:
//			break;
//		}
//		if (nChoice == 4)
//			break;
//		getchar();
//		getchar();
//	}
//	WriteRecordListFile(recordlist);
//}
