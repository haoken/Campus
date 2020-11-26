#include"athlete.h"

//��ʼ���˶�Ա��
void InitAthleteList(SAthleteList& SList) {
	SList.pSAthleteList = (SAthlete*)malloc(ATHLETELIST_INIT_SIZE * sizeof(SAthlete));
	if (!SList.pSAthleteList) {
		printf("�ڴ�����");
		exit(0);
	}
	SList.nListSize = ATHLETELIST_INIT_SIZE;
	SList.nListLength = 0;
}

void ClearAthleteList(SAthleteList& SList) {
	SList.nListLength = 0;
}

void DestroyAthleteList(SAthleteList& SList) {
	free(SList.pSAthleteList);
	SList.nListLength = 0;
	SList.nListSize = 0;
}

void InputAthleteInfo(SAthlete& SAthle) {
	printf("\n\t������");
	GetString(SAthle.szAthleteName, sizeof(SAthle.szAthleteName));

	printf("\n\tѧ�ţ�");
	GetString(SAthle.szAthleteID, sizeof(SAthle.szAthleteID));

	int nChoice_Gender = 0;
	printf("\n\t�Ա�1��Ů��   2������ :");//�Ա�
	nChoice_Gender = GetOption(1, 2);
	switch (nChoice_Gender)
	{
	case 1:
		SAthle.GENDER_athleteGender = GENDER_FEMALE;
		break;
	case 2:
		SAthle.GENDER_athleteGender = GENDER_MALE;
		break;
	} 

	int nChoice_Academy = 0;
	SAcademyList academylist;
	InitAcademyList(academylist);
	ReadAcademyListFile(academylist);
	DisplayAcademyList(academylist);
	printf("\t������λ��");
	nChoice_Academy = GetOption(0, academylist.nListLength - 1);
	SAthle.academy = academylist.pSAcademyList[nChoice_Academy];//������λ


	char szAthleteItemIDorName[20];
	SItemList list;
	int nCount = 0;
	InitItemList(list);
	ReadItemListFile(list);
	printf("\n");
	DisplayItemList(list);
	printf("\n\t�����뱨����Ŀ����(1~%d)��",ATHLETE_MAX_ITEM);
	int nNumber_item = 0;
	nNumber_item = GetOption(1, ATHLETE_MAX_ITEM);
	for (int i = 0; i < nNumber_item; i++) {
		printf("\n\t����������˶�Ա��������Ŀ��Ż������֣�");
		GetString(szAthleteItemIDorName, sizeof(szAthleteItemIDorName));
		int nPos = LocateItem(list, szAthleteItemIDorName);
		if (nPos != -1) {//����Ŀ����
			if (list.pSItemList[nPos].GENDER_itemgender==SAthle.GENDER_athleteGender) {//�Ա�����ſ��Ա���,������ͬʱ���ڶ�Ӧ��Ŀ�ı����˶�Ա��������ϸ����˶�Ա
				SAthle.SAthleteItem[nCount++] = list.pSItemList[nPos];
			}
			else {
				if (list.pSItemList[nPos].GENDER_itemgender == GENDER_MALE)
					printf("\t%s����%s����\n",list.pSItemList[nPos].szItemName, "����");
				else
					printf("\t%s����%s����\n",list.pSItemList[nPos].szItemName, "Ů��");
			}
		}
	}
	SAthle.nSItemNumber = nCount;
	printf("\t�ɹ�����%d����Ŀ\n", nCount);//�Ѿ�����˶�Ա����Ϣ¼��
	for (int i = 0; i < SAthle.nSItemNumber; i++) {
		int nPos_item = LocateItem(list, SAthle.SAthleteItem[i].szItemName);//��Ŀ����Ŀ���е�λ��
		AddAthlete(*list.pSItemList[nPos_item].pAthleteList, SAthle);//�������˶�Ա���뵽����Ŀ�ı���������
	}
	WriteItemListFile(list);//�����º����Ŀ��д���ļ��С�
	DestroyItemList(list);
}

void DisplayAthleteInfo(const SAthlete& SAthle,int withTitle) {
	if (withTitle == true) {
		printf("\t|%-12s", "ѧ��");
		printf("|%-8s", "����");
		printf("%-5s", "|�Ա�");
		printf("%-12s","|��Ժ");
		printf("%-21s", "|��Ŀһ");
		printf("%-6s", "|�ɼ�");
		printf("%-21s", "|��Ŀ��");
		printf("%-6s", "|�ɼ�");
		printf("%-21s", "|��Ŀ��");
		printf("%-6s", "|�ɼ�");
		printf("\n");
		printf("\t____________________________________________________________________________________________________________________\n\t");

	}
	printf("|%-12s", SAthle.szAthleteID);
	printf("|%-8s", SAthle.szAthleteName);
	if (SAthle.GENDER_athleteGender == GENDER_FEMALE)
		printf("%-5s", "|Ů");
	else
		printf("%-5s", "|��");

	printf("|%-11s", SAthle.academy.szAcademyName);

	for (int i = 0; i < SAthle.nSItemNumber; i++) {
		printf("|%-20s", SAthle.SAthleteItem[i].szItemName);
		if (SAthle.SAthleteItem[i].dResult>0)//�����ĳɼ�Ӧ�ò��ᳬ�������Χ��
			printf("|%-5.2lf", SAthle.SAthleteItem[i].dResult);
		else {
			printf("|%-5s", "��");
		}
	}
	for (int i = SAthle.nSItemNumber; i < ATHLETE_MAX_ITEM; i++) {
		printf("%-21s", "|δ�");
		printf("|%-5s", "��");
	}

	printf("\n");

}

void DisplayAthleteListInfo(const SAthleteList& SList) {
	printf("\n\n");
	printf("\t%-5s", "|���");
	printf("|%-12s", "ѧ��");
	printf("|%-8s", "����");
	printf("%-5s", "|�Ա�");
	printf("%-12s", "|��Ժ");
	printf("%-21s", "|��Ŀһ");
	printf("%-6s", "|�ɼ�");
	printf("%-21s", "|��Ŀ��");
	printf("%-6s", "|�ɼ�");
	printf("%-21s", "|��Ŀ��");
	printf("%-6s", "|�ɼ�");
	printf("\n");
	for (int i = 0; i < SList.nListLength; i++) {
		printf("\t______________________________________________________________________________________________________________________________\n");
		printf("\t|%-4d", i + 1);
		DisplayAthleteInfo(SList.pSAthleteList[i],false);
	}
}

//��ҳ��ʾ����ʾ��pageҳ
void DisplayAthleteListInfo(const SAthleteList& SList, int page,int NumberPerPage) {
	int maxPage = 0;
	if (SList.nListLength % NumberPerPage != 0)
		maxPage = SList.nListLength / NumberPerPage + 1;
	else
		maxPage = SList.nListLength / NumberPerPage;
	if (page > maxPage)
		page = maxPage;
	if (page < 1)
		page = 1;
	printf("\n\n");
	printf("\t%-5s", "|���");
	printf("|%-12s", "ѧ��");
	printf("|%-8s", "����");
	printf("%-5s", "|�Ա�");
	printf("%-12s", "|��Ժ");
	printf("%-21s", "|��Ŀһ");
	printf("%-6s", "|�ɼ�");
	printf("%-21s", "|��Ŀ��");
	printf("%-6s", "|�ɼ�");
	printf("%-21s", "|��Ŀ��");
	printf("%-6s", "|�ɼ�");
	printf("\n");
	for (int i = (page - 1) * NumberPerPage; i < page * NumberPerPage; i++) {
		if (i>=SList.nListLength)//�����Ϊ��,���ߵ������ֵ
			break;
		printf("\t______________________________________________________________________________________________________________________________\n");
		printf("\t|%-4d", i + 1);
		DisplayAthleteInfo(SList.pSAthleteList[i], false);
	}
	printf("\n\t\t\t\t\t\t\t        \t��%d/%dҳ\t\t\n", page, maxPage);
}

//��ҳ��ʾ
void DisplayAthleteListPagination(const SAthleteList& SList,int nNumberPerPage) {
	int nPage = 1;
	int nMaxPage = 0;
	int nChoice = 0;
	if (SList.nListLength % nNumberPerPage == 0)
		nMaxPage = SList.nListLength / nNumberPerPage;
	else
		nMaxPage = SList.nListLength / nNumberPerPage + 1;

	while (true) {//��ҳ��ʾ�����˶�Ա��
		system("cls");
		DisplayAthleteListInfo(SList, nPage, nNumberPerPage);
		printf("\n\t**********************************************************\n");
		printf("\t**1.��һҳ\t2.��һҳ\t3.ת��\t\t4.����\t**\n");
		printf("\t**********************************************************\n");
		printf("\t���ѡ��");
		nChoice = GetOption(1, 4);
		if (nChoice == 1 && nPage > 1)
			nPage--;
		else if (nChoice == 2 && nPage < nMaxPage)
			nPage++;
		else if (nChoice == 3) {
			printf("\n\tת����");
			nPage = GetOption(1, nMaxPage);
		}
		else if (nChoice == 4)
			break;
	}
}

int LocateAthlete(SAthleteList& SList, char szAthleteIDorName[]) {
	int nPosition = -1;
	for (int i = 0; i < SList.nListLength; i++) {
		if (strcmp(SList.pSAthleteList[i].szAthleteName, szAthleteIDorName) == 0 || strcmp(SList.pSAthleteList[i].szAthleteID, szAthleteIDorName) == 0) {
			nPosition = i;
		}
	}
	return nPosition;
}

int AddAthlete(SAthleteList& SList, SAthlete SAthle) {
	if (LocateAthlete(SList, SAthle.szAthleteID) != -1 || LocateAthlete(SList, SAthle.szAthleteName) != -1) {//�Ѵ��ڵ��˶�Ա�������
		printf("�˶�Ա�Ѵ���");
		return -1;
	}

	if (SList.nListLength == SList.nListSize) {
		SAthlete* pNewBase = (SAthlete*)realloc(SList.pSAthleteList, (SList.nListSize + ATHLETELIST_INCREASEMENT) * sizeof(SAthlete));
		if (!pNewBase) {
			printf("�ڴ�����");
			exit(0);
		}
		SList.nListSize += ATHLETELIST_INCREASEMENT;
		SList.pSAthleteList = pNewBase;
	}

	SList.pSAthleteList[SList.nListLength] = SAthle;
	SList.nListLength++;
	return 0;
}

//ɾ���˶�Ա���е��˶�Ա���Ҳ���ͬ����������
int DeleteAthlete(SAthleteList& SList, char szAthleteIDorName[]) {
	int nPos = LocateAthlete(SList, szAthleteIDorName);
	if (nPos == -1) {
		printf("\n���˶�Ա������\n");
		return 0;
	}
	for (int i = nPos; i < SList.nListLength - 1; i++) {
		SList.pSAthleteList[i] = SList.pSAthleteList[i + 1];
	}
	SList.nListLength--;

	return 0;
}

int DeleteAthleteSync(SAthleteList& SList, char szAthleteIDorName[]) {
	int nPos = LocateAthlete(SList, szAthleteIDorName);
	if (nPos == -1) {//�˶�Ա�����ھͲ���ɾ����
		printf("\n\t���˶�Ա������\n");
		return 0;
	}
	SItemList itemlist;
	InitItemList(itemlist);
	ReadItemListFile(itemlist);

	//ͬ���������б��������б�ĸ��˶�Աɾ����(��ͬ����ɾ��)
	SAthlete* athlete = &SList.pSAthleteList[nPos];
	for (int i = 0; i < athlete->nSItemNumber; i++) {
		SSportItem* item = &athlete->SAthleteItem[i];//ȡ����һ��
		int nPos_item = LocateItem(itemlist, item->szItemID);//����Ŀ���е�λ��
		SAthleteList* appForm = itemlist.pSItemList[nPos_item].pAthleteList;
		DeleteAthlete(*appForm, athlete->szAthleteID);
	}
	WriteItemListFile(itemlist);

	for (int i = nPos; i < SList.nListLength - 1; i++) {
		SList.pSAthleteList[i] = SList.pSAthleteList[i + 1];
	}
	SList.nListLength--;

	

	DestroyItemList(itemlist);

	return 0;
}

int DeleteAthleteSync(SAthleteList& SList, int nPos_athlete) {
	if (nPos_athlete<0 || nPos_athlete>SList.nListLength - 1) {
		printf("\n���޴��˶�Ա\n");
		return -1;
	}

	SItemList itemlist;
	InitItemList(itemlist);
	ReadItemListFile(itemlist);

	//ͬ���������б��������б�ĸ��˶�Աɾ����
	SAthlete* athlete = &SList.pSAthleteList[nPos_athlete];
	for (int i = 0; i < athlete->nSItemNumber; i++) {
		SSportItem* item = &athlete->SAthleteItem[i];
		int nPos_item = LocateItem(itemlist, item->szItemID);//����Ŀ���е�λ��
		SAthleteList* appForm = itemlist.pSItemList[nPos_item].pAthleteList;
		DeleteAthlete(*appForm, athlete->szAthleteID);
	}
	WriteItemListFile(itemlist);

	for (int i = nPos_athlete; i < SList.nListLength - 1; i++) {
		SList.pSAthleteList[i] = SList.pSAthleteList[i + 1];
	}
	SList.nListLength--;

	DestroyItemList(itemlist);

	return 0;
}

int LocateAthleteItem(SAthlete& SAthle, char szItemIDorName[]) {
	int nPosition = -1;
	for (int i = 0; i < SAthle.nSItemNumber; i++) {
		if (strcmp(SAthle.SAthleteItem[i].szItemName, szItemIDorName) == 0 || strcmp(SAthle.SAthleteItem[i].szItemID, szItemIDorName) == 0) {
			nPosition = i;
			break;
		}
	}
	return nPosition;
}

int DeleteAthleteItem(SAthlete& SAthle, char szItemIDorName[]) {
	int nPosition = LocateAthleteItem(SAthle, szItemIDorName);//�ҵ������Ŀ���˶�Ա������Ŀ�����е�λ��
	if (nPosition != -1) {
		for (int i = nPosition; i < SAthle.nSItemNumber - 1; i++) {//��������Ƶ�ǰ��ȥ
			SAthle.SAthleteItem[i] = SAthle.SAthleteItem[i + 1];
		}
		SAthle.nSItemNumber--;

		SItemList itemlist;//��Ŀ���е���Ӧ��Ŀ���˶�Ա��Ҫ���Ķ����������˶�Ա�ӱ���ɾ��
		InitItemList(itemlist);
		ReadItemListFile(itemlist);
		int nPos_item = LocateItem(itemlist, szItemIDorName);//����Ŀ�����ҵ�����Ŀ
		DeleteAthleteSync(*itemlist.pSItemList[nPos_item].pAthleteList, SAthle.szAthleteID);//�ڸ���Ŀ��������ɾ�������˶�Ա��
		WriteItemListFile(itemlist);
		DestroyItemList(itemlist);

		return 0;
	}
	else//���˶�Աû�б��������Ŀ
		return -1;
}

int AddAthleteItem(SAthlete& SAthle, SSportItem SItem){
	SItemList itemlist;
	InitItemList(itemlist);
	ReadItemListFile(itemlist);
	int nPos_item = LocateItem(itemlist, SItem.szItemID);//�ҵ�����Ŀ����Ŀ����Ϊλ�ã�
	if (nPos_item == -1) {//����Ŀ��Ҫ����Ŀ���вſ���д��
		printf("%s����Ŀ������",SItem.szItemName);
		DestroyItemList(itemlist);
		return -1;
	} 
	if (SAthle.nSItemNumber >= ATHLETE_MAX_ITEM||LocateAthleteItem(SAthle,SItem.szItemID)!=-1) {//�����Ŀ�Ѵ����ޣ������Ѿ���������Ŀ�Ͳ�������
		return -1;
	}
	SAthle.SAthleteItem[SAthle.nSItemNumber] = SItem;
	SAthle.nSItemNumber++;
	
	AddAthlete(*itemlist.pSItemList[nPos_item].pAthleteList, SAthle);//�������˶�Ա���뵽��Ŀ��������
	WriteItemListFile(itemlist);//�����º����Ŀ��д���ļ���
	DestroyItemList(itemlist);
	return 0;
}

int ReplaceAthleteItem(SAthlete& SAthle, SSportItem SItem, int n) {//��SItem����SAthle.SAthleteItem[n]
	SItemList itemlist;//��Ŀ���е���Ӧ��Ŀ���˶�Ա��Ҫ���Ķ����������˶�Ա�ӱ���ɾ��
	InitItemList(itemlist);
	ReadItemListFile(itemlist);
	int nPos_item = LocateItem(itemlist,SAthle.SAthleteItem[n].szItemName);//����Ŀ�����ҵ�����Ŀ
	DeleteAthleteSync(*itemlist.pSItemList[nPos_item].pAthleteList, SAthle.szAthleteID);//�ڸ���Ŀ��������ɾ�������˶�Ա��
	SAthle.SAthleteItem[n] = SItem;
	nPos_item = LocateItem(itemlist, SItem.szItemID);//�ҵ�����Ŀ����Ŀ����Ϊλ�ã�
	if (nPos_item == -1) {//����Ŀ��Ҫ����Ŀ���вſ���д��
		printf("����Ŀ������");
		DestroyItemList(itemlist);
		return -1;
	}
	AddAthlete(*itemlist.pSItemList[nPos_item].pAthleteList, SAthle);//�������˶�Ա���뵽��Ŀ��������
	WriteItemListFile(itemlist);//�����º����Ŀ��д���ļ���
	DestroyItemList(itemlist);
	return 0;
}

void DisplayAthleteItem(const SAthlete& SAthle) {
	printf("\n\t|���      |����                |���\t|�ɼ�\t|\n");
	for (int i = 0; i < SAthle.nSItemNumber; i++) {
		printf("\t|%-10s", SAthle.SAthleteItem[i].szItemID);
		printf("|%-20s", SAthle.SAthleteItem[i].szItemName);

		if (SAthle.SAthleteItem[i].SPORTTYPE_itemtype == SPORTTYPE_TRACK)
			printf("|����\t");
		else if (SAthle.SAthleteItem[i].SPORTTYPE_itemtype == SPORTTYPE_FIELD)
			printf("|����\t");

		if (SAthle.SAthleteItem[i].dResult<=0) {
			printf("|%2s\t|", "��");
		}
		else {
			printf("|%.2lf\t|", SAthle.SAthleteItem[i].dResult);
		}
		printf("\n");
	}
}

void AthleteSync(SAthlete& athlete) {//�����º���˶�Ա��Ϣͬ������������
	SItemList itemlist;
	InitItemList(itemlist);
	ReadItemListFile(itemlist);
	for (int i = 0; i < athlete.nSItemNumber;i++) {
		int nPos_item = LocateItem(itemlist, athlete.SAthleteItem[i].szItemID);//�˶�Ա������Ŀ����Ŀ���е�λ��
		if (nPos_item == -1) {
			nPos_item = LocateItem(itemlist, athlete.SAthleteItem[i].szItemName);
		}
		int nPos_athlete = LocateAthlete(*itemlist.pSItemList[nPos_item].pAthleteList, athlete.szAthleteID);//�ҵ��˶�Ա����Ŀ�������е�λ��
		if (nPos_athlete == -1) {
			nPos_athlete = LocateAthlete(*itemlist.pSItemList[nPos_item].pAthleteList, athlete.szAthleteName);
		}
		itemlist.pSItemList[nPos_item].pAthleteList->pSAthleteList[nPos_athlete] = athlete;//����Ӧλ�õ��˶�Ա�滻����
	}
	WriteItemListFile(itemlist);//�����º����Ŀ��д���ļ���
	DestroyItemList(itemlist);
}

int ModifiAthlete(SAthleteList& SList, char szAthleteIDorName[]) {
	int nPos = LocateAthlete(SList, szAthleteIDorName);//nPosʱ
	if (nPos == -1) {
		printf("\n\t���˶�Ա������\n");
		return -1;
	}

	system("cls");
	DisplayAthleteInfo(SList.pSAthleteList[nPos],true);

	SAthlete* athlete = &SList.pSAthleteList[nPos];//athleteָ����Ҫ�޸ĵ��˶�Ա��
	int nChoice = 0;

	system("cls");
	DisplayAthleteInfo(*athlete, true);

	printf("\n\t*********************************************************************************\n");
	printf("\t**1.����      |2.ѧ��      |3.�Ա�      |4.������Ժ  |5.������Ŀ  |6.ȡ��      **");
	printf("\n\t*********************************************************************************\n");
	printf("\t���ѡ���ǣ�");

	nChoice = GetOption(1, 6);
	switch (nChoice)
	{
	case 1: {
		char szTemp[20];
		printf("\n\t�µ�����:");
		GetString(szTemp, sizeof(szTemp));
		if (LocateAthlete(SList, szTemp) == -1) {
			strcpy_s(athlete->szAthleteName, sizeof(athlete->szAthleteName), szTemp);
		}
		else
			printf("�������Ѵ���");
		break;
	}
	case 2: {
		char szTemp[20];
		printf("\n\t�µ�ѧ��:");
		GetString(szTemp, sizeof(szTemp));
		if (LocateAthlete(SList, szTemp) == -1) {
			strcpy_s(athlete->szAthleteID, sizeof(athlete->szAthleteID), szTemp);
		}
		else
			printf("��ѧ���Ѵ���");
		break;
	}
	case 3: {//���ﻹ��Ҫ����������˱�������Ŀ���һ�飬�����е���Ŀ�������һ���Ա�ı��������û������ʾ�����û�ѡ���Ƿ�ɾ����
		int nChoice_Gender = 0;
		printf("\n\tע��:����������޸��Ա𣬿��ܻᵼ���еı����޷��μӡ�\n");
		printf("\n\t�Ա�\t1.Ů��  \t2.����\n");
		printf("\n\t���ѡ��");
		nChoice_Gender = GetOption(1, 2);
		GENDER gender = GENDER_FEMALE;
		GENDER originalGender = athlete->GENDER_athleteGender;
		if (nChoice_Gender == 1)
			gender = GENDER_FEMALE;
		else if (nChoice_Gender == 2)
			gender = GENDER_MALE;
		athlete->GENDER_athleteGender = gender;
		SItemList itemlist;
		InitItemList(itemlist);
		ReadItemListFile(itemlist);
		for (int i = 0; i < athlete->nSItemNumber; i++) {
			char szTemp[25];
			strcpy_s(szTemp, sizeof(szTemp), athlete->SAthleteItem[i].szItemName);//��ȡ��Ŀ��
			if (originalGender != gender) {//�Ա�ͬ����Ҫ�޸�
				if (originalGender == GENDER_FEMALE) {//�õ��෴�Ա����Ŀ�������������ܲ���100�ף� �õ��ľ���Ů���ܲ���100�ף�
					int index = Index_BF(szTemp, "Ů");
					szTemp[index] = "��"[0];
					szTemp[index + 1] = "��"[1];
				}
				else {
					int index = Index_BF(szTemp, "��");
					szTemp[index] = "Ů"[0];
					szTemp[index + 1] = "Ů"[1];
				}
			}
			else//����Ա�û�иı䣬��ֱ���˳���������
				return 0;

			int nPos_item = LocateItem(itemlist, szTemp);//ת��֮�����Ŀ����Ŀ���е�λ��
			if (nPos_item == -1) {//�����ڸ���Ŀ
				printf("\n%s�����ڣ����%s��ɾ��\n", szTemp, athlete->SAthleteItem[i].szItemName);
				DeleteAthleteItem(*athlete, athlete->SAthleteItem[i].szItemName);//ɾ������Ŀ
			}
			else {//����Ŀ����
				printf("\n�Ƿ�%s ת���Ƴ� %s", athlete->SAthleteItem[i].szItemName, szTemp);
				printf("\t1.��   2.��(ɾ����Ŀ)  :");
				int nYesOrNo = GetOption(1, 2);
				if (nYesOrNo == 1) {
					ReplaceAthleteItem(*athlete, itemlist.pSItemList[nPos_item], i);//���µ���Ŀ������͵���Ŀ
				}
				else {
					DeleteAthleteItem(*athlete, athlete->SAthleteItem[i].szItemName);
					i--;
				}
			}//else ��Ŀ����
		}//for
		break;
	}
	case 4: {
		int nChoice_Academy = -1;
		SAcademyList academyList;
		InitAcademyList(academyList);
		ReadAcademyListFile(academyList);
		DisplayAcademyList(academyList);
		printf("�µ�������λ:");
		nChoice_Academy = GetOption(0, academyList.nListLength - 1);
		athlete->academy = academyList.pSAcademyList[nChoice_Academy];
		break;
	}
	case 5: {
		printf("\n\n");
		DisplayAthleteItem(SList.pSAthleteList[nPos]);
		printf("\n\t1.ɾ����Ŀ\n");
		printf("\n\t2.�����Ŀ\n");
		int nChoice_Item = 0;
		nChoice_Item = GetOption(1, 2);
		switch (nChoice_Item)
		{
		case 1: {
			printf("\n\n\t����������Ҫɾ������Ŀ��Ż������ƣ�");
			char szIDorName[25];
			GetString(szIDorName, sizeof(szIDorName));
			if (DeleteAthleteItem(*athlete, szIDorName) == -1) {
				printf("\n�����˶�Ա��û�б�����Ŀ\n");
			}
			if (athlete->nSItemNumber == 0) {//��������˶�Աû�б�����Ŀ�ˣ��ͽ����˶�Ա���˶�Ա����ɾ����
				DeleteAthleteSync(SList, nPos);
			}
			break;
		}
		case 2: {
			printf("\n\t������Ŀ����:\n");
			SItemList list;
			InitItemList(list);
			ReadItemListFile(list);
			DisplayItemList(list);
			printf("\n\t����������Ҫ��ӵ���Ŀ�������ƣ�");
			char szIDorName[25];
			GetString(szIDorName, sizeof(szIDorName));
			int nPos_temp = LocateItem(list, szIDorName);
			if (nPos_temp == -1) {//��Ŀ�����ڣ����˳�����
				printf("\n\t����Ŀ������\n");
				DestroyItemList(list);
				return -1;
			}
			if (AddAthleteItem(*athlete, list.pSItemList[nPos_temp]) == -1) {//�����Ŀ
				printf("\n\t�����ظ�������Ŀ\n");
			}
			DestroyItemList(list);
			break;
		}//case 2
		}//switch (nChoice_Item)
	}//case 5
	case 6://ȡ��
		break;
	}//switch(nChoice)

	if (nChoice == 1 || nChoice == 2 || nChoice == 4) {//��������
		AthleteSync(*athlete);
	}
	system("cls");
	DisplayAthleteInfo(*athlete, true);
	printf("\n�޸ĳɹ�!\n");
	return 0;
}

int WriteAthleteListFile(SAthleteList& SList) {
	FILE* pFAthleteFile;
	errno_t err = fopen_s(&pFAthleteFile, "athleteinfo.txt", "w");
	if (err != 0) {
		printf("�ļ���ʧ��");
		exit(0);
	}
	if (pFAthleteFile) {
		for (int i = 0; i < SList.nListLength; i++) {
			fwrite(&SList.pSAthleteList[i], sizeof(SAthlete), 1, pFAthleteFile);
			fputc('\n', pFAthleteFile);
		}
		fclose(pFAthleteFile);
	}//if
	return 0;
}

int ReadAthleteListFile(SAthleteList& SList) {
	ClearAthleteList(SList);
	FILE* pFAthleteFile;
	errno_t err = fopen_s(&pFAthleteFile, "athleteinfo.txt", "r");
	if (err != 0) {
		printf("�ļ���ʧ��");
		exit(0);
	}

	SAthlete SAthle;
	if (pFAthleteFile) {
		fread(&SAthle, sizeof(SAthlete), 1, pFAthleteFile);
		fgetc(pFAthleteFile);
		while (!feof(pFAthleteFile)) {
			if (ferror(pFAthleteFile)) {
				clearerr(pFAthleteFile);
				printf("�ļ���ȡ����");
				return -1; 
			}
			AddAthlete(SList, SAthle);
			fread(&SAthle, sizeof(SAthlete), 1, pFAthleteFile);
			fgetc(pFAthleteFile);
		}
		fclose(pFAthleteFile);
	}
	return 0;
}


void menu_athlete() {
	printf("\n\t********************************************************************************************************************************\n");
	printf("\t**1.�����˶�Ա  |2.��������    |3.ɾ���˶�Ա  |4.�޸��˶�Ա  |5.��ѯ    |6.�������˵�  |7.��һҳ    |8.��һҳ    |9.ת��ҳ    **");
	printf("\n\t********************************************************************************************************************************\n");
	printf("\t���ѡ���ǣ�");
}

//ҵ���߼�
void AthleteManagement() {
	//�˶�Ա���
	SAthlete athlete;
	SAthleteList athletelist;
	InitAthleteList(athletelist);
	ReadAthleteListFile(athletelist);
	int nPage = 1;
	int nMaxPage = 0;
	int nNumberPerPage = 8;
	while (true) {
		system("cls");
	
		if (athletelist.nListLength % nNumberPerPage != 0)
			nMaxPage = athletelist.nListLength / nNumberPerPage + 1;
		else
			nMaxPage = athletelist.nListLength / nNumberPerPage;
		DisplayAthleteListInfo(athletelist, nPage, nNumberPerPage);
		menu_athlete();
		int nChoice_Athlete = 0;
		nChoice_Athlete = GetOption(1, 9);
		switch (nChoice_Athlete)
		{
		case 1:
			system("cls");
			printf("\n\t�������˶�Ա��Ϣ\n");
			InputAthleteInfo(athlete);
			AddAthlete(athletelist, athlete);
			WriteAthleteListFile(athletelist);
			break;
		case 2: 
			system("cls");
			ReadExcel();
			ReadAthleteListFile(athletelist);
			break;
		case 3: {
			char szIDorName[20];
			printf("\n\t������Ҫɾ�����˶�Ա�����ֻ���ѧ��:");
			GetString(szIDorName, sizeof(szIDorName));
			DeleteAthleteSync(athletelist, szIDorName);
			WriteAthleteListFile(athletelist);
			break;
		}//case 3
		case 4: {
			char szIDorName[20];
			printf("\n\t��������Ҫ�޸ĵ��˶�Ա������ֻ���ѧ��:");
			GetString(szIDorName, sizeof(szIDorName));
			ModifiAthlete(athletelist, szIDorName);
			WriteAthleteListFile(athletelist);
			break;
		}//case 4
		case 5: {
			printf("\n\n\t��ѯ�����ݣ�\n");
			printf("\t**********************************************************************************\n");
			printf("\t**1.������λ\t|2.ѧ��\t\t|3.����\t\t|4.��Ŀ\t\t|5.����\t\t**");
			printf("\n\t**********************************************************************************\n");
			printf("\t���ѡ���ǣ�");

			int nChoice_inquire = 0;
			nChoice_inquire = GetOption(1,5);
			switch (nChoice_inquire)
			{
			case 1: {//���ݲ�����λ��ѯ
				system("cls");
				
				SAcademyList academylist;
				InitAcademyList(academylist);
				ReadAcademyListFile(academylist);
				DisplayAcademyList(academylist);
				printf("\n\t��Ҫ��ѯ�Ĳ�����λ������");
				int nChoice_academy = 0;
				nChoice_academy = GetOption(0, academylist.nListLength - 1);
				SAthleteList tmpAthletelist;//���ñ����������ĳ��������λ���˶�Ա
				InitAthleteList(tmpAthletelist);
				for (int i = 0; i < athletelist.nListLength; i++) {
					SAthlete* athlete =&athletelist.pSAthleteList[i];
					if (strcmp(athlete->academy.szAcademyName, academylist.pSAcademyList[nChoice_academy].szAcademyName) == 0) {//��������˶�Ա�����������λ�ģ�����ʾ����u
						AddAthlete(tmpAthletelist, *athlete);
					}
				}
				DisplayAthleteListPagination(tmpAthletelist, 10);
				DestroyAthleteList(tmpAthletelist);
				DestroyAcademyList(academylist);
				break;
			}//case 1
			case 2: {//����ѧ�Ų�ѯ
				printf("\n\n\t������ѧ�ţ�");
				char szAthleteID[20];
				GetString(szAthleteID, sizeof(szAthleteID));
				int nPos_ID = LocateAthlete(athletelist, szAthleteID);
				if (nPos_ID != -1) {
					DisplayAthleteInfo(athletelist.pSAthleteList[nPos_ID], true);
				}
				else {
					printf("\n�޴��ˣ�\n");
				}
				break;
			}//case 2
			case 3: {//����������ѯ
				printf("\n\n\t������������");
				char szAthleteName[20];
				GetString(szAthleteName, sizeof(szAthleteName));
				int nPos_ID = LocateAthlete(athletelist, szAthleteName);
				if (nPos_ID != -1) {
					DisplayAthleteInfo(athletelist.pSAthleteList[nPos_ID], true);
				}
				else {
					printf("\n�޴��ˣ�\n");
				}
				break;
			}//case 3
			case 4: {//������Ŀ��ѯ
				system("cls");
				SItemList itemlist;//��ʱ��Ŀ��
				InitItemList(itemlist);
				ReadItemListFile(itemlist);
				DisplayItemList(itemlist);
				printf("\n\n\t��Ҫ��ѯ����Ŀ�ǣ�");
				char szItemIDorName[25];
				GetString(szItemIDorName,sizeof(szItemIDorName));
				int nPos_item = LocateItem(itemlist, szItemIDorName);
				if (nPos_item == -1) {//�Ҳ�������Ŀ
					printf("\t����Ŀ������");
					system("pause");
				}
				else {//�ҵ�����Ŀ
					system("cls");
					SAthleteList tmpAthletelist;//�����˶�Ա��������ű����˸���Ŀ���˶�Ա
					InitAthleteList(tmpAthletelist);
					SSportItem* item = &itemlist.pSItemList[nPos_item];
					for (int i = 0; i < athletelist.nListLength; i++) {
						if (LocateAthleteItem(athletelist.pSAthleteList[i], item->szItemID) != -1) //�����˶�Ա���˸���Ŀ
							AddAthlete(tmpAthletelist, athletelist.pSAthleteList[i]);//������˶�Ա���뱸���˶�Ա����
					}//for
					DisplayAthleteListPagination(tmpAthletelist, 8);
					DestroyAthleteList(tmpAthletelist);
				}//else
				DestroyItemList(itemlist);//�ͷŵ���ʱ��Ŀ��
				break;
			}//case 4
			}//switch(nChoice_inquire)
			break;
		}//case 5
		case 6:
			break;
		case 7:
			if (nPage != 1) 
				nPage--;
			break;
		case 8:
			if (nPage != nMaxPage) 
				nPage++;
			break;
		case 9: {
			printf("\n\tת��:");
			nPage = GetOption(1, nMaxPage);
			break;
		}
		}//switch
		if (nChoice_Athlete == 6) {
			break;
		}
		system("pause");
	}//while(true)
	DestroyAthleteList(athletelist);
}