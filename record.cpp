#include"record.h"
#include <Windows.h>
#include<iostream>

void InitRecordList(SRecordList& SList){
	SList.pSRecordList = (SItemRecord*)malloc(MAXRECORDSIZE*sizeof(SItemRecord));
	if (!SList.pSRecordList) {
		printf("内存已满");
		exit(0);
	}
	SList.nListSize = MAXRECORDSIZE;
	SList.nListLength = 0;
}

int LocateRecord(SRecordList &SList, char szRecordName[]){//查找名字为SZRecordName的项目在链表中的位置，在则返回i的值。 
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
	printf("\n请输入项目编号：");
	scanf_s("%s", SRecord.szRecordID, 10);
	printf("\n请输入项目名称：");
	scanf_s("%s",SRecord.szRecordName,20);
	printf("\n请输入纪录保持者姓名：");
	scanf_s("%s",SRecord.szAthleteName,20);
	int iGender; 
	printf("\n请输入纪录保持者性别（0 is male or 1 is famale）：");
	scanf_s("%d",&iGender);
	if(iGender==0) SRecord.AthleteGender = GENDER_MALE;
	else SRecord.AthleteGender = GENDER_FEMALE;
	printf("\n请输入纪录成绩：");
	scanf_s("%lf",&SRecord.dRecordResult);
}

int AddRecord(SRecordList &SList,SItemRecord SItem){
	
	if (LocateRecord(SList,SItem.szRecordName)!=-1) {
		printf("纪录已存在\n");
		return -1;
	}
	else {
		SItemRecord* newbase;
		if (SList.nListLength == SList.nListSize) {
			newbase = (SItemRecord*)realloc(SList.pSRecordList,(MAXRECORDSIZE+INCREASERECORDSIZE)*sizeof(SItemRecord));
			SList.nListSize += INCREASERECORDSIZE;
			if (!newbase) {
				printf("内存不足");
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
			printf("项目不存在\n");
			return -1;//项目表中不存在这个项目。
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
		printf("项目不存在\n");
		return -1;
	}
	else{
		int nChoice = 0;
		printf("\n1.项目编号\n2.项目名称\n3.记录保持者姓名\n4.性别\n5.成绩\n");
		printf("\n请输入你需要修改的信息：");
		scanf_s("%d",&nChoice);
		switch (nChoice)
		{
		case 1:
			printf("请输入新的项目编号：");
			scanf_s("%s", SList.pSRecordList[nLocation].szRecordID, 10);
			break;
		case 2: {
			printf("请输入项目名称");
			scanf_s("%s", SList.pSRecordList[nLocation].szRecordName,20);
			break;
		}
		case 3:
			printf("请输入纪录保持者姓名：");
			scanf_s("%s", SList.pSRecordList[nLocation].szAthleteName, 20);
			break;
		case 4: {
			int iGender;
			printf("请输入纪录保持者性别（0 is male or 1 is famale）：");
			scanf_s("%d", &iGender);
			if (iGender == 1) SList.pSRecordList[nLocation].AthleteGender = GENDER_MALE;
			else SList.pSRecordList[nLocation].AthleteGender = GENDER_FEMALE;
			break;
		}
		case 5:
			printf("请输入纪录成绩：");
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
		printf("|女\t");
	else
		printf("|男\t");
	printf("|%.2lf\t\n", SRecord.dRecordResult);
} 

int WriteRecordListFile(SRecordList& SList) {
	FILE* pFRecordFile;
	errno_t err = fopen_s(&pFRecordFile,"recordinfo.txt","w");
	if (err != 0) {
		printf("文件读取出错");
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
		printf("文件读取出错");
		exit(0);
	}
	SItemRecord SRecord;
	if (pFRecordFile) {
		fread(&SRecord, sizeof(SItemRecord), 1, pFRecordFile);
		fgetc(pFRecordFile);
		while (!feof(pFRecordFile)) {//feof()读取到EOF时返回true，否则返回false
			if (ferror(pFRecordFile)) {//ferror()读取出错时返回true,否则返回false 
				clearerr(pFRecordFile);
				printf("文件读取出错");
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
	printf("\t|%-15s","记录编号");
	printf("|%-20s", "记录名称");
	printf("|%-20s", "运动员姓名");
	printf("|性别\t");
	printf("|成绩\t\n");
	for (int i = 0; i < SList.nListLength; i++) {
		printf("\t________________________________________________________________________________________\n");
		PrintRecord(SList.pSRecordList[i]);
	}
	printf("\n\n\n");
}

void menu_record() {
	printf("\n1.添加记录");
	printf("\n2.删除记录");
	printf("\n3.修改记录");
	printf("\n4.保存并退出\n");
	printf("你的选择：");
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
//			printf("\n请输入需要删除的记录编号或者名字:");
//			scanf_s("%s", szIdorname, 20);
//			DeleteRecord(recordlist, szIdorname);
//			break;
//		}
//		case  3: {
//			char szIdorname[20];
//			printf("\n请输入需要删除的记录编号或者名字:");
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
