#include"sportitem.h"

void CreateItem(SSportItem& SItem) {
	//����
	printf("\n\t��������Ŀ����:");
	GetString(SItem.szItemName, 20);

	//�Ա�
	char male[] = "��";
	char female[] = "Ů";
	if (Index_BF(SItem.szItemName, male) != -1)
		SItem.GENDER_itemgender = GENDER_MALE;
	else if (Index_BF(SItem.szItemName, female) != -1)
		SItem.GENDER_itemgender = GENDER_FEMALE;
	else {
		printf("\n\t1.������  2.Ů����\n");
		printf("\t���ѡ��");
		int option;
		option = GetOption(1, 2);
		if (option == 1) {
			SItem.GENDER_itemgender = GENDER_MALE;
			char tmp[25]="����";
			strncat_s(tmp, SItem.szItemName, sizeof(SItem.szItemName));
			strcpy_s(SItem.szItemName, tmp);
		}
		else {
			SItem.GENDER_itemgender = GENDER_FEMALE;
			char tmp[25] = "Ů��";
			strncat_s(tmp, SItem.szItemName, sizeof(tmp));
			strcpy_s(SItem.szItemName, tmp);
		}
	}

	//���
	printf("\n\t��������Ŀ���:");
	GetString(SItem.szItemID, sizeof(SItem.szItemID));

	//���
	int nItemType = 0;
	printf("\n\t0:������1:����\n\t��Ŀ���:");
	nItemType = GetOption(0, 1);
	if (nItemType == 0)
		SItem.SPORTTYPE_itemtype = SPORTTYPE_FIELD;
	else
		SItem.SPORTTYPE_itemtype = SPORTTYPE_TRACK;
	
	printf("\n\t���볡�أ�");
	GetString(SItem.szPlace, sizeof(SItem.szPlace));

	//��ʱ
	printf("\n\tÿ������ʱ��(min):");
	SItem.dItemTime = GetDouble(0,1000);

	//�˶�Ա���ʼ��
	SAthleteList *athletelist = (SAthleteList*)malloc(sizeof(SAthleteList));
	InitAthleteList(*athletelist);
	SItem.pAthleteList = athletelist;

	//�˶�Ա��������˶�Ա����֮��Ż����ɡ�
	SItem.ppAthleteGroup = NULL;
	SItem.GroupNumber = 0;

	//�ɼ����ڱ�����ɺ������
	SItem.dResult = 0;
}

//��ʼ����Ŀ��
void InitItemList(SItemList& SList) {
	SList.pSItemList = (SSportItem*)malloc(ITEMLIST_INIT_SIZE * sizeof(SSportItem));
	if (!SList.pSItemList) {
		printf("�ڴ�����");
		exit(0);
	}
	SList.nListSize = ITEMLIST_INIT_SIZE;
	SList.nListLength = 0;
}

void ClearItemList(SItemList& SList) {
	SList.nListLength = 0;
}

void DisplayItem(SSportItem& SItem,int withTitle) {
	if (withTitle == true) {
		printf("\t|���      |����                      |���\t|����  |��ʱ(min)|����|");
		printf("\n\t________________________________________________________________________\n");
	}
	printf("\t|%-10s", SItem.szItemID);
	printf("|%-26s", SItem.szItemName);

	if (SItem.SPORTTYPE_itemtype == SPORTTYPE_TRACK)
		printf("|����\t");
	else if (SItem.SPORTTYPE_itemtype == SPORTTYPE_FIELD)
		printf("|����\t");

	printf("|%-6s", SItem.szPlace);

	printf("|%-9.2lf", SItem.dItemTime);

	printf("|%-2d  |", SItem.pAthleteList->nListLength);
}

void DisplayItemList(const SItemList& SList) {
	printf("\t|���      |����                      |���\t|����  |��ʱ(min)|����|");
	for (int i = 0; i < SList.nListLength; i++) {
		printf("\n\t________________________________________________________________________\n");
		DisplayItem(SList.pSItemList[i],false);
	}
}

//��ʾ��iҳ
void DisplayItemListPagination(const SItemList& SList, int page,int NumberPerPage) {
	int maxPage = 0;
	if (SList.nListLength % NumberPerPage != 0)
		maxPage = SList.nListLength / NumberPerPage + 1;
	else
		maxPage = SList.nListLength / NumberPerPage;
	if (page > maxPage)
		page = maxPage;
	if (page < 1)
		page = 1;
	printf("\n");
	printf("\t|���   |���      |����                      |���\t|����  |��ʱ(min)|����|");
	printf("\n");
	for (int i = (page - 1) * NumberPerPage; i < page * NumberPerPage; i++) {
		if (i >= SList.nListLength)//�����Ϊ��,���ߵ������ֵ
			break;
		printf("\t____________________________________________________________________________________\n");
		printf("\t|%-4d", i + 1);
		DisplayItem(SList.pSItemList[i], false);
		printf("\n");
	}
	printf("\n\t\t\t\t\t        \t��%d/%dҳ\t\t\n", page, maxPage);
}

void DestroyItemList(SItemList& SList) {
	free(SList.pSItemList);
	SList.nListLength = 0;
	SList.nListSize = 0;
}

int LocateItem(SItemList& SList, char szItemIDorName[]) {
	int nPosition = -1;
	for (int i = 0; i < SList.nListLength; i++) {
		if ((strcmp(szItemIDorName, SList.pSItemList[i].szItemID) == 0) || (strcmp(szItemIDorName, SList.pSItemList[i].szItemName) == 0)) {
			nPosition = i;
			break;
		}//if
	}//for
	return nPosition;
}

int AddItem(SItemList& SList, SSportItem SItem) {
	SSportItem* pSNewBase;

	if ((LocateItem(SList, SItem.szItemID) != -1) || (LocateItem(SList, SItem.szItemName) != -1)) {
		printf("��Ŀ�Ѵ���\n");
		return -1;
	}

	if (SList.nListLength == SList.nListSize) {
		pSNewBase = (SSportItem*)realloc(SList.pSItemList, (SList.nListSize +ITEMLIST_INCREASEMENT) * sizeof(SSportItem));
		if (!pSNewBase) {
			printf("�ڴ�����");
			exit(0);
		}
		SList.nListSize += ITEMLIST_INCREASEMENT;
		SList.pSItemList = pSNewBase;
	}
	SList.pSItemList[SList.nListLength] = SItem;
	SList.nListLength++;
	return 0;
}

int DeleteItem(SItemList& SList, char szItemIDorName[]) {
	int nPosition = LocateItem(SList, szItemIDorName);
	if (nPosition == -1) {
		printf("��Ŀ������\n");
		return -1;//��Ŀ���в����������Ŀ��
	}

	//ͬ�����˶�Ա��
	SSportItem* item = &SList.pSItemList[nPosition];
	SAthleteList* athleteList = SList.pSItemList[nPosition].pAthleteList;
	SAthleteList allAthlete;
	InitAthleteList(allAthlete);
	ReadAthleteListFile(allAthlete);
	for (int i = 0; i < athleteList->nListLength; i++) {//���ÿһ��ѧ����Ȼ��ȡ�������Ŀ
		char* szAthleteID = athleteList->pSAthleteList[i].szAthleteID;//ѧ����
		int nPos_Athlete = LocateAthlete(allAthlete, szAthleteID);//�ҵ�ѧ����λ��
		SAthlete* athlete = &allAthlete.pSAthleteList[nPos_Athlete];
		DeleteAthleteItem(*athlete, item->szItemID);
	}
	WriteAthleteListFile(allAthlete);//ͬ��֮��д���ļ�

	for (int i = nPosition; i < SList.nListLength - 1; i++) {
		SList.pSItemList[i] = SList.pSItemList[i + 1];
	}
	SList.nListLength--;

	return 0;
}

int DeleteItem(SItemList& SList, int pos) {
	int nPosition = pos;
	if (nPosition == -1) {
		printf("��Ŀ������\n");
		return -1;//��Ŀ���в����������Ŀ��
	}

	//ͬ�����˶�Ա��
	SSportItem* item = &SList.pSItemList[nPosition];
	SAthleteList* athleteList = SList.pSItemList[nPosition].pAthleteList;
	SAthleteList allAthlete;
	InitAthleteList(allAthlete);
	ReadAthleteListFile(allAthlete);
	for (int i = 0; i < athleteList->nListLength; i++) {//���ÿһ��ѧ����Ȼ��ȡ�������Ŀ
		char* szAthleteID = athleteList->pSAthleteList[i].szAthleteID;//ѧ����
		int nPos_Athlete = LocateAthlete(allAthlete, szAthleteID);//�ҵ�ѧ����λ��
		SAthlete* athlete = &allAthlete.pSAthleteList[nPos_Athlete];
		DeleteAthleteItem(*athlete, item->szItemID);
	}
	WriteAthleteListFile(allAthlete);//ͬ��֮��д���ļ�

	for (int i = nPosition; i < SList.nListLength - 1; i++) {
		SList.pSItemList[i] = SList.pSItemList[i + 1];
	}
	SList.nListLength--;

	return 0;
}

int ModifiItem(SItemList& SList, char szItemIDorName[]) {
	int nPosition = LocateItem(SList, szItemIDorName);
	if (nPosition == -1) {
		printf("��Ŀ������");
		return -1;
	}
	system("cls");
	SSportItem* pSItem = &SList.pSItemList[nPosition];
	DisplayItem(*pSItem, true);
	int nChoice = 0;
	printf("\n\n\t����Ҫ�޸ĵ����ݣ�\n");
	printf("\n\t1.��Ŀ���\n");
	printf("\n\t2.��Ŀ����\n");
	printf("\n\t3.��Ŀ���\n");
	printf("\n\t4.ÿ������ʱ��\n");
	printf("\n\t5.����\n");
	printf("\n\t6.ȡ��\n");
	printf("\n\t���ѡ��");
	nChoice = GetOption(1, 6);
	switch (nChoice)
	{
	case 1: {//���
		char szTemp[10];
		printf("\n\n\t�µı��:");
		GetString(szTemp, 10);
		if (LocateItem(SList, szTemp) == -1) {
			strcpy_s(pSItem->szItemID, sizeof(pSItem->szItemID), szTemp);
		}
		else {
			printf("�ñ���Ѵ���\n");
			return -1;
		}

		break;
	}
	case 2: {//����
		char szTemp[25];
		printf("\n\n\t�µ�����:");
		GetString(szTemp, sizeof(szTemp));
		int flag = true;

		if ((Index_BF(szTemp, "��") != -1 && pSItem->GENDER_itemgender == GENDER_MALE)|| (Index_BF(szTemp, "Ů") != -1 && pSItem->GENDER_itemgender == GENDER_FEMALE)) {//�����д��У��Ա���Ů
			flag = true;
		}
		else if ((Index_BF(szTemp, "��") != -1 && pSItem->GENDER_itemgender == GENDER_FEMALE) || (Index_BF(szTemp, "Ů") != -1 && pSItem->GENDER_itemgender == GENDER_MALE)) {//�����д�Ů���Ա�����
			flag = false;
		}
		else if (Index_BF(szTemp, "��") == -1 || Index_BF(szTemp, "Ů") == -1) {//�����в�����Ů
			if (pSItem->GENDER_itemgender == GENDER_FEMALE) {
				char tmp[25] = "Ů��";
				strncat_s(tmp, szTemp, sizeof(tmp));
				strcpy_s(szTemp, tmp);
			}
			else {
				char tmp[25] = "����";
				strncat_s(tmp, szTemp, sizeof(tmp));
				strcpy_s(szTemp, tmp);
			}
		}
		if (flag == false) {
			printf("���������Ϲ���ע���Ա�");
			getchar();
			return -1;
		}

		if (LocateItem(SList, szTemp) == -1) {
			strcpy_s(pSItem->szItemName, sizeof(pSItem->szItemName), szTemp);
		}
		else
			printf("�������Ѵ���");
		break;
	}
	case 3: {//���
		int nChoiceType = 0;
		printf("\n\n\t�µ���Ŀ���: \n1.����\n2.����");
		printf("\n\t���ѡ��");
		nChoiceType = GetOption(1, 2);
		if (nChoiceType == 1)
			pSItem->SPORTTYPE_itemtype = SPORTTYPE_FIELD;
		else if (nChoiceType == 2)
			pSItem->SPORTTYPE_itemtype = SPORTTYPE_TRACK;
		break;
	}
	case 4://ʱ��
		printf("\n\n\t�µ�ʱ��(\min):");
		pSItem->dItemTime = GetDouble();
		break;
	case 5: {//����
		printf("\n\t�����µĳ��أ�");
		GetString(pSItem->szPlace, sizeof(pSItem->szPlace));
	}
	case 6://ȡ��
		return 0;
	}

	SAthleteList allAthlete;
	InitAthleteList(allAthlete);
	ReadAthleteListFile(allAthlete);
	if (nChoice != 6) {//ͬ�����˶�Ա������ѡ�˸���Ŀ���˸��´���Ŀ
		for (int i = 0; i < pSItem->pAthleteList->nListLength; i++) {//�����������ȡ���˶�Ա���д���
			SAthlete* athlete = &pSItem->pAthleteList->pSAthleteList[i];//��Ҫ�޸ĵ��˶�Ա
			int nPos_athlete = LocateAthlete(allAthlete, athlete->szAthleteID);//���˶�Ա�����˶�Ա���е�λ��
			int nPos_item = LocateAthleteItem(allAthlete.pSAthleteList[nPos_athlete], pSItem->szItemID);//����Ŀ�ڸ��˶�Ա������Ŀ�е�λ��
			allAthlete.pSAthleteList[nPos_athlete].SAthleteItem[nPos_item] = *pSItem;//������Ŀ�滻�ɸ���Ŀ
		}
	}
	WriteAthleteListFile(allAthlete);
	DestroyAthleteList(allAthlete);

	return 0;
}

int WriteItemListFile(SItemList& SList) {
	FILE* pFItemFile;
	errno_t err = fopen_s(&pFItemFile, "iteminfo.txt", "w");
	if (err != 0) {
		printf("iteminfo.txt�ļ���ʧ��");
		exit(0);
	}
	if (pFItemFile) {
		for (int i = 0; i < SList.nListLength; i++) {
			fwrite(&SList.pSItemList[i], sizeof(SSportItem), 1, pFItemFile);//д����Ŀ
			fputc('\n', pFItemFile);//д����
			int length = SList.pSItemList[i].pAthleteList->nListLength;
			fwrite(&length, sizeof(int), 1, pFItemFile);//д�뱨���˶�Ա�б���
			for (int j = 0; j < length; j++) {//д��������Ա������
				fwrite(&SList.pSItemList[i].pAthleteList->pSAthleteList[j], sizeof(SAthlete), 1, pFItemFile);
				fputc('\n', pFItemFile);//д����
			}//forj
		}//fori
		fclose(pFItemFile);
	}//if
	return 0;
}

int ReadItemListFile(SItemList& SList) {
	ClearItemList(SList);
	FILE* pFItemFile;
	errno_t err = fopen_s(&pFItemFile, "iteminfo.txt", "r");
	if (err != 0) {
		printf("iteminfo.txt�ļ���ʧ��");
		exit(0);
	}
	SSportItem SItem;//��Ŀ
	SAthlete athlete;//�˶�Ա
	if (pFItemFile) {
		while (!feof(pFItemFile)) {
			if (ferror(pFItemFile)) {//ferror()��ȡ����ʱ����true,���򷵻�false 
				clearerr(pFItemFile);
				printf("�ļ���ȡ����");
				exit(0);
			}
			SAthleteList* athletelist = (SAthleteList*)malloc(sizeof(SAthleteList));//��Ŀ�ı�������
			InitAthleteList(*athletelist);
			fread(&SItem, sizeof(SSportItem), 1, pFItemFile);//��ȡ��Ŀ
			fgetc(pFItemFile);//������
			if (feof(pFItemFile)) {//���һ�ζ�ȡ�����eof
				break;
			}
			int length;
			fread(&length, sizeof(int), 1, pFItemFile);//��ȡ�����˶�Ա����
			for (int i = 0; i < length; i++) {//��ȡ�˶�Ա��
				fread(&athlete, sizeof(SAthlete), 1, pFItemFile);
				fgetc(pFItemFile);//������
				AddAthlete(*athletelist, athlete);//����˶�Ա���˶�Ա��
			}
			SItem.pAthleteList = athletelist;
			AddItem(SList, SItem);//�����Ŀ����Ŀ��
		}
		fclose(pFItemFile);
	}
	return 0;
}

int Grouping(SItemList& SList) {
	SAcademyList academylist;
	InitAcademyList(academylist);
	ReadAcademyListFile(academylist);
	for (int i = 0; i < SList.nListLength; i++) {//����ÿ����Ŀ
		if (SList.pSItemList[i].pAthleteList->nListLength == 0) {
			SList.pSItemList[i].GroupNumber = 0;
			SList.pSItemList[i].ppAthleteGroup = NULL;
			continue;
		}
		if (SList.pSItemList[i].SPORTTYPE_itemtype==SPORTTYPE_TRACK) {//��������
			int* nAcademy = (int*)malloc(academylist.nListLength * sizeof(int));
			for (int j = 0; j < academylist.nListLength; j++) {
				nAcademy[j] = 0;
			}
			SSportItem* item = &SList.pSItemList[i];
			int nGroupNumber = 0;
			if (item->pAthleteList->nListLength % 8 == 0)//�����ܵ�
				nGroupNumber = item->pAthleteList->nListLength / 8;
			else
				nGroupNumber = item->pAthleteList->nListLength / 8 + 1;
			item->GroupNumber = nGroupNumber;

			if (item->GroupNumber == 0) {//���û���˶�Ա��������Ŀ����ֱ�Ӵ���һ����Ŀ��ʼ
				free(nAcademy);
				continue;
			}

			item->ppAthleteGroup = (SAthleteList**)malloc(nGroupNumber * sizeof(SAthleteList*));
			for (int j = 0; j < nGroupNumber; j++) {
				item->ppAthleteGroup[j] = (SAthleteList*)malloc(sizeof(SAthleteList));//ppAthleteGroupָ�򼸸�������˶�Ա�б�
				InitAthleteList(*item->ppAthleteGroup[j]);
			}


			SAthleteList szTempAthleteList;//����Ǳ����������Ŀ��һ�����ݱ���Ϊ����ֱ�Ӵ�����Ŀ������������һ�����ñ�
			InitAthleteList(szTempAthleteList);
			for (int j = 0; j < item->pAthleteList->nListLength; j++) {
				SAthlete* athlete = &item->pAthleteList->pSAthleteList[j];
				int index = LocateAcademy(academylist, athlete->academy.szAcademyName);
				if (index == -1) {
					printf("\n\t����ѧ������û�в����ĵ�λ\n");
					return 0;
				}
				nAcademy[index]++;
				AddAthlete(szTempAthleteList, *athlete);
			}


			int nDiv = item->pAthleteList->nListLength / nGroupNumber;
			int nMod = item->pAthleteList->nListLength % nGroupNumber;
			int iGroup = 0;//��i��
			int nIndex = 0;

			while (szTempAthleteList.nListLength > 0 && iGroup < nGroupNumber) {
				while (nAcademy[nIndex] == 0) {//ѡ��ĳ����Ժ���ˣ�����ѡ
					if (nIndex == academylist.nListLength - 1)
						nIndex = 0;
					else
						nIndex++;
				}
				nAcademy[nIndex]--;
				int nAcademyIndex = nIndex;//Ҫ�����ΪnAcademyIndex����Ժ���˶�Ա���з���

				if (nIndex == academylist.nListLength - 1)
					nIndex = 0;
				else
					nIndex++;

				for (int j = 0; j < szTempAthleteList.nListLength; j++) {
					if (strcmp(szTempAthleteList.pSAthleteList[j].academy.szAcademyName, academylist.pSAcademyList[nAcademyIndex].szAcademyName) == 0) {
						AddAthlete(*item->ppAthleteGroup[iGroup], szTempAthleteList.pSAthleteList[j]);//������˶�Ա���뵽��i��������
						DeleteAthlete(szTempAthleteList, szTempAthleteList.pSAthleteList[j].szAthleteID);//������˶�Աɾ��
						break;
					}
				}

				if (iGroup < nMod && item->ppAthleteGroup[iGroup]->nListLength == nDiv + 1) {//���������0~nMod֮�䣬����һ��������ﵽnDiv+1�������������һ��
					iGroup++;
				}
				else if (iGroup <= nGroupNumber - 1 && iGroup >= nMod && item->ppAthleteGroup[iGroup]->nListLength == nDiv) {//����������һ�飬�������ﵽnDiv�ʹ�����һ��
					iGroup++;
				}//else
			}//while()
			free(nAcademy);
		}
		else {//��������
			SSportItem* item = &SList.pSItemList[i];
			item->GroupNumber = 1;
			item->ppAthleteGroup = (SAthleteList**)malloc(sizeof(SAthleteList*));
			item->ppAthleteGroup[0] = (SAthleteList*)malloc(sizeof(SAthleteList));
			InitAthleteList(*item->ppAthleteGroup[0]);
			for (int i = 0; i < item->pAthleteList->nListLength; i++) {//���������е��˶�Ա�ŵ�һ�����С�
				SAthlete* athlete = &item->pAthleteList->pSAthleteList[i];
				AddAthlete(*item->ppAthleteGroup[0], *athlete);
			}
		}
	}//for(i)
	DestroyAcademyList(academylist);
	return 0;
}//GroupItemAthlete()

void Ordering(SItemList& SList) {
	for (int i = 0; i < SList.nListLength; i++) {
		SSportItem* item = &SList.pSItemList[i];//����Ŀ
		for (int j = 0; j < item->GroupNumber; j++) {
			SAthleteList* athletelist = item->ppAthleteGroup[j];//����Ŀ������һ������
			for (int k = 0; k < athletelist->nListLength; k++) {
				for (int m = 0; m < athletelist->nListLength - k-1; m++) {
					int nPos1 = LocateAthleteItem(athletelist->pSAthleteList[m], item->szItemID);
					int nPos2 = LocateAthleteItem(athletelist->pSAthleteList[m+1], item->szItemID);
					if (item->SPORTTYPE_itemtype == SPORTTYPE_TRACK) {
						if (athletelist->pSAthleteList[m].SAthleteItem[nPos1].dResult > athletelist->pSAthleteList[m + 1].SAthleteItem[nPos2].dResult) {
							SAthlete tmpAthlete;
							tmpAthlete = athletelist->pSAthleteList[m];
							athletelist->pSAthleteList[m] = athletelist->pSAthleteList[m + 1];
							athletelist->pSAthleteList[m + 1] = tmpAthlete;
						}
					}
					else if (item->SPORTTYPE_itemtype == SPORTTYPE_FIELD) {
						if (athletelist->pSAthleteList[m].SAthleteItem[nPos1].dResult < athletelist->pSAthleteList[m + 1].SAthleteItem[nPos2].dResult) {
							SAthlete tmpAthlete;
							tmpAthlete = athletelist->pSAthleteList[m];
							athletelist->pSAthleteList[m] = athletelist->pSAthleteList[m + 1];
							athletelist->pSAthleteList[m + 1] = tmpAthlete;
						}
					}
				}//for(m)
			}//for(k)ð������
		}//for(j)����
	}//for(i)��Ŀ
}

//��ӡ����n��
void DisplayNGroup(SSportItem&SItem,int n) {
	DisplayAthleteListInfo(*SItem.ppAthleteGroup[n - 1]);
}

int DisplayGroupingPagination(SSportItem& SItem,const char*szTitle,const char*szThirdChoice) {
	if (SItem.GroupNumber == 0) {
		printf("\n����Ŀ���˱���\n");
		system("pause");
		return 0;
	}
	int nGroupNumber = SItem.GroupNumber;
	int iGroup = 1;//��һ��
	while (true) {
		system("cls");
		printf("\t%s\n",szTitle);
		printf("\n\t��Ŀ��%s  ��%d��\n",SItem.szItemName,iGroup);
		DisplayAthleteListInfo(*SItem.ppAthleteGroup[iGroup - 1]);
		printf("\n\t\t\t\t\t\t\t        \t��%d/%d��\n\n", iGroup, nGroupNumber);
		printf("\t1.��һ��\t2.��һ��\t3.%s  ��",szThirdChoice);
		int nChoice = GetOption(1, 3);
		if (nChoice == 1 && iGroup > 1)
			iGroup--;
		else if (nChoice == 2 && iGroup < nGroupNumber)
			iGroup++;
		else if(nChoice==3){
			system("cls");
			printf("\t��Ŀ��%s  ��%d��\n", SItem.szItemName, iGroup);
			DisplayAthleteListInfo(*SItem.ppAthleteGroup[iGroup - 1]);
			break;
		}
	}
	return iGroup;
}

int DisplayGroupingPagination(SSportItem& SItem) {
	if (SItem.GroupNumber == 0) {
		printf("\n����Ŀ���˱���\n");
		system("pause");
		return 0;
	}
	int nGroupNumber = SItem.GroupNumber;
	int iGroup = 1;//��һ��
	while (true) {
		system("cls");
		printf("\n\t��Ŀ��%s  ��%d��\n", SItem.szItemName, iGroup);
		DisplayAthleteListInfo(*SItem.ppAthleteGroup[iGroup - 1]);
		printf("\n\t\t\t\t\t\t\t        \t��%d/%d��\n\n", iGroup, nGroupNumber);
		printf("\t1.��һ��\t2.��һ��\t3.���� ��");
		int nChoice = GetOption(1, 3);
		if (nChoice == 1 && iGroup > 1)
			iGroup--;
		else if (nChoice == 2 && iGroup < nGroupNumber)
			iGroup++;
		else if (nChoice == 3) {
			system("cls");
			printf("\t��Ŀ��%s  ��%d��\n", SItem.szItemName, iGroup);
			DisplayAthleteListInfo(*SItem.ppAthleteGroup[iGroup - 1]);
			break;
		}
	}
	return iGroup;
}

void menu_item() {//��Ŀ�����Ŀ¼
	printf("\t**********************************************************************************************************\n");
	printf("\t**1.������Ŀ\t2.ɾ����Ŀ\t3.�޸���Ŀ\t4.��Ŀ������Ա\t|5.�������˵�|6.��һҳ\t|7.��һҳ\t**");
	printf("\n\t**********************************************************************************************************\n");
	printf("\t���ѡ���ǣ�");
}

void ItemManagement() {//��Ŀ����
	//�����Ŀ
	SSportItem item;
	SItemList itemlist;
	SAthleteList athletelist;

	InitAthleteList(athletelist);
	ReadAthleteListFile(athletelist);

	InitItemList(itemlist);
	ReadItemListFile(itemlist);
	int nPage = 1;
	int nMaxPage = 0;
	int nNumberPerPage = 8;
	while (true) {
		system("cls");
		if (itemlist.nListLength % nNumberPerPage != 0)
			nMaxPage = itemlist.nListLength / nNumberPerPage + 1;
		else
			nMaxPage = itemlist.nListLength / nNumberPerPage;
		DisplayItemListPagination(itemlist, nPage, nNumberPerPage);
		printf("\n\n");
		menu_item();
		int nChoice = 0;
		nChoice = GetOption(1, 7);
		switch (nChoice)
		{
		case 1://�����Ŀ
			CreateItem(item);
			AddItem(itemlist, item);
			break;
		case 2: {//ɾ����Ŀ
			char szIDorName[25];
			printf("\n\t��������Ҫɾ������Ŀ�ı�Ż�������:");
			GetString(szIDorName, sizeof(szIDorName));
			DeleteItem(itemlist, szIDorName);
			break;
		}//case 2
		case 3: {//�޸���Ŀ
			char szIDorName[25];
			printf("\n\t��������Ҫ�޸ĵ���Ŀ�ı�Ż�������:");
			GetString(szIDorName, sizeof(szIDorName));
			ModifiItem(itemlist, szIDorName);
			break;
		}//case 3
		case 4: {//��ѯ��Ŀ����
			char szIDorName[20];
			SAthleteList SItemList;
			InitAthleteList(SItemList);

			printf("\n\t��������Ҫ��ѯ������������Ŀ��Ż�������:");
			scanf_s("%s", szIDorName, 20);
			int nPos = LocateItem(itemlist, szIDorName);
			int nNumberPerPage = 8;
			int nPage = 1;
			while (true) {
				system("cls");
				DisplayItem(itemlist.pSItemList[nPos], true);
				printf("\n\n");
				DisplayAthleteListInfo(*itemlist.pSItemList[nPos].pAthleteList, nPage,nNumberPerPage);
				printf("\n\t****************************************\n");
				printf("\t**1.��һҳ\t2.��һҳ\t3.����**\n");
				printf("\t****************************************\n");
				printf("\t���ѡ��");
				int nChoice = GetOption(1, 3);
				switch (nChoice)
				{
				case 1:
					if (nPage > 1)
						nPage--;
					break;
				case 2:
					if (nPage < itemlist.pSItemList[nPos].pAthleteList->nListLength / nNumberPerPage + 1)
						nPage++;
					break;
				}//switch
				if (nChoice == 3)
					break;
			}
			break;
		}//case 4
		case 6: {
			if (nPage != 1)
				nPage--;
			break;
		}
		case 7: {
			if (nPage != nMaxPage)
				nPage++;
			break;
		}
		}//switch(nChoice)
		if (nChoice == 5)
			break;
		system("pause");
	}//while(true)
	WriteItemListFile(itemlist);
	DestroyAthleteList(athletelist);
	DestroyItemList(itemlist);
}
