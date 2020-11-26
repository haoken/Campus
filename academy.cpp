#include"academy.h"

//��ʼ��������λ��
void InitAcademyList(SAcademyList& SList) {
	SList.pSAcademyList = (SAcademy*)malloc(ACADEMYLIST_INIT_SIZE * sizeof(SAcademy));
	if (!SList.pSAcademyList) {
		printf("�ڴ�����");
		exit(0);
	}
	SList.nListSize = ACADEMYLIST_INIT_SIZE;
	SList.nListLength = 0;
}

void ClearAcademyList(SAcademyList& SList) {
	SList.nListLength = 0;
}

void CreateAcademy(SAcademy& academy) {
	printf("\n\t���������λ���ƣ�");
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
	if (LocateAcademy(SList, academy.szAcademyName) != -1) {//������λ�Ѵ���
		printf("\n�ò�����λ�Ѵ���\n");
		return -1;
	}
	if (SList.nListLength == SList.nListSize) {
		SAcademy* newbase = (SAcademy*)realloc(SList.pSAcademyList,(SList.nListLength+ACADEMYLIST_INCREASEMENT)*sizeof(SAcademy));
		if (!newbase) {
			printf("�ڴ�����");
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
		printf("\n�ò�����λ������\n");
		return -1;
	}
	for (int i = nPos; i < SList.nListLength - 1; i++) {
		SList.pSAcademyList[i] = SList.pSAcademyList[i + 1];
	}
	SList.nListLength--;

	//���˶�Ա���е����иò�����λ���˶�Աɾ��
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
		printf("�ò�����λ������");
		return -1;
	}
	SAcademy* pAcademy = &SList.pSAcademyList[nPos];


	printf("�µĲ�����λ����");
	GetString(SList.pSAcademyList[nPos].szAcademyName, sizeof(SList.pSAcademyList[nPos].szAcademyName));
	printf("�޸ĳɹ���");

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
	printf("\t|��� |������λ\n");
	for (int i = 0; i < SList.nListLength; i++) {
		printf("\t_____________________________\n");
		printf("\t|%d    |%s\n", i, SList.pSAcademyList[i].szAcademyName);
	}
}

int WriteAcademyListFile(SAcademyList& SList) {
	FILE* pFAcademyFile;
	errno_t err = fopen_s(&pFAcademyFile, "academyinfo.txt", "w");
	if (err != 0) {
		printf("academyinfo.txt�ļ���ʧ��");
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
		printf("academyinfo.txt�ļ���ʧ��");
		exit(0);
	}
	SAcademy academy;
	if (pFAcademyFile) {
		while (!feof(pFAcademyFile)) {
			if (ferror(pFAcademyFile)) {
				clearerr(pFAcademyFile);
				printf("�ļ���ȡ����");
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
	printf("\t**1.���Ӳ�����λ  |2.ɾ��������λ  |3.�޸Ĳ�����λ  |4.��ѯ��Ա      |5.�������˵�       **");
	printf("\n\t*******************************************************************************************\n");
	printf("\t���ѡ���ǣ�");
}

//ҵ���߼�
void AcademyManagement(){//������λ����
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
		case 1: {//���Ӳ�����λ
			SAcademy academy;
			CreateAcademy(academy);
			if (LocateAcademy(academylist, academy.szAcademyName) != -1) {
				printf("\n\t�ò�����λ�Ѵ���\n");
				break;
			}
			AddAcademy(academylist, academy);
			WriteAcademyListFile(academylist);
			printf("\n\t��ӳɹ�\n");
			break;
		}//case 1
		case 2: {//ɾ��������λ
			char szAcademyName[20];
			printf("\t����������Ҫɾ���Ĳ�����λ�����ƣ�");
			GetString(szAcademyName, sizeof(szAcademyName));
			if (LocateAcademy(academylist, szAcademyName) == -1) {
				printf("\t�ò�����λ������");
				break;
			}
			printf("\n\tע�⣬ɾ��������λ���ᵼ�¸ò�����λ�����˶�Ա�˳����б���\n");
			printf("\t1. ȷ��  2.ȡ��\n");
			printf("\t���ѡ��:");
			int nChoice_tmp = GetOption(1, 2);
			if (nChoice_tmp == 1) {
				DeleteAcademy(academylist, szAcademyName);
				WriteAcademyListFile(academylist);
				printf("\n\tɾ���ɹ�\n");
				break;
			}
			else
				break;
		}//case 2 
		case 3: {//�޸Ĳ�����λ����
			printf("\n\t��������Ҫ�޸ĵĲ�����λ����");
			char szAcademyName[20];
			GetString(szAcademyName, sizeof(szAcademyName));
			int nPos_academy = LocateAcademy(academylist, szAcademyName);
			if (nPos_academy == -1) {
				printf("\n\t�ò�����λ������\n");
				break;
			}
			else {
				printf("\n\t�����µĲ�����λ����");
				char szNewName[20];
				GetString(szNewName, sizeof(szNewName));
				int nPos_newName = LocateAcademy(academylist, szNewName);
				if (nPos_newName != -1) {
					printf("\n\t�Ѵ���һ����Ϊ%s�Ĳ�����λ\n", szNewName);
					break;
				}
				else {
					strcpy_s(academylist.pSAcademyList[nPos_academy].szAcademyName, sizeof(academylist.pSAcademyList[nPos_academy].szAcademyName), szNewName);
					printf("\n\t�޸ĳɹ�\n");
					WriteAcademyListFile(academylist);
					break;
				}//else
			}//else
		}//case 3
		case 4: {//��ѯ����
			printf("\n\t��������Ҫ��ѯ�Ĳ�����λ��");
			char szAcademyName[20];
			GetString(szAcademyName, sizeof(szAcademyName));
			int nPos_academy = LocateAcademy(academylist, szAcademyName);
			if (nPos_academy == -1) {
				printf("\n\t�ò�����λ������\n");
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

