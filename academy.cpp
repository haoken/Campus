#include"academy.h"

//初始化径赛单位表
void InitAcademyList(SAcademyList& SList) {
	SList.pSAcademyList = (SAcademy*)malloc(ACADEMYLIST_INIT_SIZE * sizeof(SAcademy));
	if (!SList.pSAcademyList) {
		printf("内存已满");
		exit(0);
	}
	SList.nListSize = ACADEMYLIST_INIT_SIZE;
	SList.nListLength = 0;
}

void ClearAcademyList(SAcademyList& SList) {
	SList.nListLength = 0;
}

void CreateAcademy(SAcademy& academy) {
	printf("\n\t输入参赛单位名称：");
	GetString(academy.szAcademyName, sizeof(academy.szAcademyName));
	academy.score = 0;
}

void DestroyAcademyList(SAcademyList& SList) {
	free(SList.pSAcademyList);
	SList.nListSize = 0;
	SList.nListLength = 0;
}

int LocateAcademy(SAcademyList& SList, char szAcademyName[]) {
	int nPosition = -1;
	for (int i = 0; i < SList.nListLength; i++) {
		if (strcmp(SList.pSAcademyList[i].szAcademyName, szAcademyName) == 0) {
			nPosition = i;
		}
	}
	return nPosition;
}

int AddAcademy(SAcademyList& SList, SAcademy academy) {
	if (LocateAcademy(SList, academy.szAcademyName) != -1) {//参赛单位已存在
		printf("\n该参赛单位已存在\n");
		return -1;
	}
	if (SList.nListLength == SList.nListSize) {
		SAcademy* newbase = (SAcademy*)realloc(SList.pSAcademyList,(SList.nListLength+ACADEMYLIST_INCREASEMENT)*sizeof(SAcademy));
		if (!newbase) {
			printf("内存已满");
			exit(0);
		}
		SList.nListSize += ACADEMYLIST_INCREASEMENT;
		SList.pSAcademyList = newbase;
	}
	SList.pSAcademyList[SList.nListLength] = academy;
	SList.nListLength++;
	return 0;
}

int DeleteAcademy(SAcademyList& SList, char* szAcademyName) {
	int nPos = LocateAcademy(SList, szAcademyName);
	if (nPos == -1) {
		printf("\n该参赛单位不存在\n");
		return -1;
	}
	for (int i = nPos; i < SList.nListLength - 1; i++) {
		SList.pSAcademyList[i] = SList.pSAcademyList[i + 1];
	}
	SList.nListLength--;

	//将运动员表中的所有该参赛单位的运动员删除
	SAthleteList athletelist;
	InitAthleteList(athletelist);
	ReadAthleteListFile(athletelist);
	for (int i = 0; i < athletelist.nListLength; i++) {
		SAthlete* athlete = &athletelist.pSAthleteList[i];
		if (strcmp(athlete->academy.szAcademyName, szAcademyName) == 0) {
			DeleteAthleteSync(athletelist, i);
			i--;
		} 
	}
	WriteAthleteListFile(athletelist);
	DestroyAthleteList(athletelist);
	return 0;
}

int ModifyAcademy(SAcademyList& SList, char* szAcademyName) {
	int nPos = LocateAcademy(SList, szAcademyName);
	if (nPos == -1) {
		printf("该参赛单位不存在");
		return -1;
	}
	SAcademy* pAcademy = &SList.pSAcademyList[nPos];


	printf("新的参赛单位名：");
	GetString(SList.pSAcademyList[nPos].szAcademyName, sizeof(SList.pSAcademyList[nPos].szAcademyName));
	printf("修改成功！");

	SAthleteList athletelist;
	InitAthleteList(athletelist);
	ReadAthleteListFile(athletelist);
	for (int i = 0; i < athletelist.nListLength; i++) {
		SAthlete* athlete = &athletelist.pSAthleteList[i];
		if (strcmp(szAcademyName, athlete->academy.szAcademyName) == 0) {
			strcpy_s(athlete->academy.szAcademyName, sizeof(athlete->academy.szAcademyName), SList.pSAcademyList[nPos].szAcademyName);
			athlete->academy.score = SList.pSAcademyList[nPos].score;
		}
	}
	WriteAthleteListFile(athletelist);
	DestroyAthleteList(athletelist);


	return 0;
}

void DisplayAcademyList(SAcademyList& SList) {
	printf("\n");
	printf("\t|序号 |参赛单位\n");
	for (int i = 0; i < SList.nListLength; i++) {
		printf("\t_____________________________\n");
		printf("\t|%d    |%s\n", i, SList.pSAcademyList[i].szAcademyName);
	}
}

int WriteAcademyListFile(SAcademyList& SList) {
	FILE* pFAcademyFile;
	errno_t err = fopen_s(&pFAcademyFile, "academyinfo.txt", "w");
	if (err != 0) {
		printf("academyinfo.txt文件打开失败");
		exit(0);
	}
	if (pFAcademyFile) {
		for (int i = 0; i < SList.nListLength; i++) {
			fwrite(&SList.pSAcademyList[i], sizeof(SAcademy), 1, pFAcademyFile);
			fputc('\n',pFAcademyFile);
		}
	}
	fclose(pFAcademyFile);
	return 0;
}
 
int ReadAcademyListFile(SAcademyList& SList) {
	ClearAcademyList(SList);
	FILE* pFAcademyFile;
	errno_t err = fopen_s(&pFAcademyFile, "academyinfo.txt", "r");
	if (err != 0) {
		printf("academyinfo.txt文件打开失败");
		exit(0);
	}
	SAcademy academy;
	if (pFAcademyFile) {
		while (!feof(pFAcademyFile)) {
			if (ferror(pFAcademyFile)) {
				clearerr(pFAcademyFile);
				printf("文件读取出错");
				return -1;
			}
			fread(&academy, sizeof(SAcademy), 1, pFAcademyFile);
			fgetc(pFAcademyFile);
			if(!feof(pFAcademyFile))
				AddAcademy(SList, academy);
		}
	}
	fclose(pFAcademyFile);
	return 0;
}


void menu_academy() {
	printf("\n\t*******************************************************************************************\n");
	printf("\t**1.增加参赛单位  |2.删除参赛单位  |3.修改参赛单位  |4.查询人员      |5.返回主菜单       **");
	printf("\n\t*******************************************************************************************\n");
	printf("\t你的选择是：");
}

//业务逻辑
void AcademyManagement(){//参赛单位管理
	SAcademyList academylist;
	InitAcademyList(academylist);
	ReadAcademyListFile(academylist);
	while (true) {
		system("cls");
		DisplayAcademyList(academylist);
		printf("\n");
		menu_academy();
		int nChoice = GetOption(1, 5);
		switch (nChoice) {
		case 1: {//增加参赛单位
			SAcademy academy;
			CreateAcademy(academy);
			if (LocateAcademy(academylist, academy.szAcademyName) != -1) {
				printf("\n\t该参赛单位已存在\n");
				break;
			}
			AddAcademy(academylist, academy);
			WriteAcademyListFile(academylist);
			printf("\n\t添加成功\n");
			break;
		}//case 1
		case 2: {//删除参赛单位
			char szAcademyName[20];
			printf("\t请输入你需要删除的参赛单位的名称：");
			GetString(szAcademyName, sizeof(szAcademyName));
			if (LocateAcademy(academylist, szAcademyName) == -1) {
				printf("\t该参赛单位不存在");
				break;
			}
			printf("\n\t注意，删除参赛单位，会导致该参赛单位所有运动员退出所有比赛\n");
			printf("\t1. 确定  2.取消\n");
			printf("\t你的选择:");
			int nChoice_tmp = GetOption(1, 2);
			if (nChoice_tmp == 1) {
				DeleteAcademy(academylist, szAcademyName);
				WriteAcademyListFile(academylist);
				printf("\n\t删除成功\n");
				break;
			}
			else
				break;
		}//case 2 
		case 3: {//修改参赛单位名字
			printf("\n\t输入你需要修改的参赛单位名：");
			char szAcademyName[20];
			GetString(szAcademyName, sizeof(szAcademyName));
			int nPos_academy = LocateAcademy(academylist, szAcademyName);
			if (nPos_academy == -1) {
				printf("\n\t该参赛单位不存在\n");
				break;
			}
			else {
				printf("\n\t输入新的参赛单位名：");
				char szNewName[20];
				GetString(szNewName, sizeof(szNewName));
				int nPos_newName = LocateAcademy(academylist, szNewName);
				if (nPos_newName != -1) {
					printf("\n\t已存在一个名为%s的参赛单位\n", szNewName);
					break;
				}
				else {
					strcpy_s(academylist.pSAcademyList[nPos_academy].szAcademyName, sizeof(academylist.pSAcademyList[nPos_academy].szAcademyName), szNewName);
					printf("\n\t修改成功\n");
					WriteAcademyListFile(academylist);
					break;
				}//else
			}//else
		}//case 3
		case 4: {//查询名单
			printf("\n\t输入你需要查询的参赛单位：");
			char szAcademyName[20];
			GetString(szAcademyName, sizeof(szAcademyName));
			int nPos_academy = LocateAcademy(academylist, szAcademyName);
			if (nPos_academy == -1) {
				printf("\n\t该参赛单位不存在\n");
				break;
			}
			else {
				SAthleteList athletelist;
				InitAthleteList(athletelist);
				ReadAthleteListFile(athletelist);
				SAthleteList tmpAthletelist;
				InitAthleteList(tmpAthletelist);
				for (int i = 0; i < athletelist.nListLength; i++) {
					SAthlete* athlete = &athletelist.pSAthleteList[i];
					if (strcmp(athlete->academy.szAcademyName, szAcademyName) == 0) 
						AddAthlete(tmpAthletelist, *athlete);
				}//for
				DisplayAthleteListPagination(tmpAthletelist, 10);
			}//else
			break;
		}//case 4
		}//switch
		if (nChoice == 5) {
			break;
		}
		system("pause");
	}
}

