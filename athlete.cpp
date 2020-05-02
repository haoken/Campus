#include"athlete.h"

void InitAthleteList(SAthleteList& SList){
	SList.pSAthleteList = (SAthlete*)malloc(MAXATHLETESIZE*sizeof(SAthlete));
	if (!SList.pSAthleteList) {
		printf("�ڴ�����");
		exit(0);
	}
	SList.nListLength = 0;
	SList.nListSize = MAXATHLETESIZE;
}

void DestroyAthleteList(SAthleteList& SList) {
	free(SList.pSAthleteList);
	SList.nListLength = 0;
	SList.nListSize = 0;
}

void InputAthleteInfo(SAthlete& SAthle){
	printf("\n\t������");
	scanf_s("%s", SAthle.szAthleteName, 20);

	printf("\n\tѧ�ţ�");
	scanf_s("%s", SAthle.szAthleteID, 20);

	int nChoice_Gender = 0;
	do {
		printf("\n\n\t�Ա�1��Ů��   2������:");
		scanf_s("%d", &nChoice_Gender);
		switch (nChoice_Gender)
		{
		case 1:
			SAthle.AthleteGender = GENDER_FEMALE;
			break;
		case 2:
			SAthle.AthleteGender = GENDER_MALE;
			break;
		default:
			printf("�������\n");
			break;
		}
	} while (nChoice_Gender != 1 && nChoice_Gender != 2);

	int nChoice_Academy = 0;
	printf("\n\n\t1.֪����Ժ\n\t2.˼Դ��Ժ\n\t3.������Ժ\n\t4.��һ��Ժ\n\t5.������Ժ\n\t6.��Զ��Ժ\n\t7.������Ժ\n\t8.��ܰ��Ժ\n\t9.�о���Ժ\n");
	do {
		printf("\n\t������Ժ��");
		scanf_s("%d", &nChoice_Academy);
		if (nChoice_Academy >= 1 && nChoice_Academy <= 9) {
			SAthle.academy = (Academy)nChoice_Academy;
		}
	} while (nChoice_Academy < 1 || nChoice_Academy > 9);


	char szAthleteItemIDorName[20];
	SItemList list;
	int nCount = 0;
	InitItemList(list);
	ReadItemListFile(list);
	printf("\n\n\n");
	DisplayItemList(list);
	printf("\n\t�����뱨����Ŀ������");
	int nNumber_item = 0;
	while (!(cin >> nNumber_item)) {
		cin.clear();
		while (cin.get() != '\n')
			continue;
		printf("\n\t������� ���������룺");
	}
	if (nNumber_item < 0 ){
		nNumber_item = 0;
	}
	else if (nNumber_item > 3) {
		nNumber_item = 3;
	}
	SAthle.nSItemNumber = nNumber_item;
	for (int i = 0; i < SAthle.nSItemNumber; i++) {
		printf("\n\t����������˶�Ա��������Ŀ��Ż������֣�");
		scanf_s("%s", szAthleteItemIDorName, 20);
		int nPos = LocateItem(list, szAthleteItemIDorName);
		if (nPos != -1) {
			SAthle.SAthleteItem[nCount] = list.pSItemList[nPos];
			SAthle.SAthleteItem[nCount++].dResult = 0;
		}
	}
	DestroyItemList(list);
}

void DisplayAthleteItem(const SAthlete& SAthle){
	printf("\t|���      |����                |���\t|�ɼ�\t|\n");
	for (int i = 0; i < SAthle.nSItemNumber; i++) {
		printf("\t|%-10s", SAthle.SAthleteItem[i].szItemID);
		printf("|%-20s", SAthle.SAthleteItem[i].szItemName);

		if (SAthle.SAthleteItem[i].SPORTYPE_itemtype == SPORTTYPE_TRACK)
			printf("|����\t");
		else if (SAthle.SAthleteItem[i].SPORTYPE_itemtype == SPORTTYPE_FIELD)
			printf("|����\t");
		if (SAthle.SAthleteItem[i].dResult < 0 || SAthle.SAthleteItem[i].dResult>1000) {
			printf("|%2s\t|", "��");
		}
		else {
			printf("|%.2lf\t|", SAthle.SAthleteItem[i].dResult);
		}
		printf("\n");
	}
}

void DisplayAthleteInfo(const SAthlete& SAthle) {
	
	printf("|%-15s", SAthle.szAthleteID);
	printf("|%-10s", SAthle.szAthleteName);
	if (SAthle.AthleteGender == GENDER_FEMALE)
		printf("%-7s","|Ů");
	else
		printf("%-7s","|��");

	switch (SAthle.academy)
	{
	case ֪����Ժ:
		printf("|֪����Ժ\t");
		break;
	case ˼Դ��Ժ:
		printf("|˼Դ��Ժ\t");
		break;
	case ������Ժ:
		printf("|������Ժ\t");
		break;
	case ��һ��Ժ:
		printf("|��һ��Ժ\t");
		break;
	case ������Ժ:
		printf("|������Ժ\t");
		break;
	case ��Զ��Ժ:
		printf("|��Զ��Ժ\t");
		break;
	case ������Ժ:
		printf("|������Ժ\t");
		break;
	case ��ܰ��Ժ:
		printf("|��ܰ��Ժ\t");
		break;
	case �о���Ժ:
		printf("|�о���Ժ\t");
		break;
	default:
		break;
	}

	for (int i = 0; i < SAthle.nSItemNumber; i++) {
		printf("|%-20s", SAthle.SAthleteItem[i].szItemName);
		if(SAthle.SAthleteItem[i].dResult>0&& SAthle.SAthleteItem[i].dResult<=1000)//�����ĳɼ�Ӧ�ò��ᳬ�������Χ��
			printf("|%-6.2lf", SAthle.SAthleteItem[i].dResult);
		else {
			printf("|%-5s", "��");
		}
	}
	for (int i = SAthle.nSItemNumber; i < 3; i++) {
		printf("%-21s","|δ�");
		printf("|%-5s", "��");
	}

	printf("\n");

}

void DisplayAthleteListInfo(const SAthleteList& SList) {
	printf("\n\n");
	printf("\t%-6s", "|���");
	printf("|%-15s","ѧ��");
	printf("|%-10s", "����");
	printf("%-7s","|�Ա�");
	printf("|��Ժ\t\t");
	printf("%-21s", "|��Ŀһ");
	printf("%-7s", "|�ɼ�");
	printf("%-21s", "|��Ŀ��");
	printf("%-6s", "|�ɼ�");
	printf("%-21s", "|��Ŀ��");
	printf("%-6s", "|�ɼ�");
	printf("\n");
	for (int i = 0; i < SList.nListLength; i++) {
		printf("\t________________________________________________________________________________________________________________________________________\n");
		printf("\t|%-5d", i+1);
		DisplayAthleteInfo(SList.pSAthleteList[i]);
	}
}

int DisplayAthleteListdepartInfo(const SAthleteList& SList,int group) {
	int length = SList.nListLength;
	int begin_index = (group - 1) * 10;
	if (begin_index>length-1) {
		return -1;
	}
	int end_index = begin_index + 9;
	if (end_index > length - 1) {
		end_index = length - 1;
	}
	printf("\n");
	printf("\t%-6s", "|���");
	printf("|%-15s", "ѧ��");
	printf("|%-10s", "����");
	printf("%-7s", "|�Ա�");
	printf("|��Ժ\t\t");
	printf("%-21s", "|��Ŀһ");
	printf("%-7s", "|�ɼ�");
	printf("%-21s", "|��Ŀ��");
	printf("%-6s", "|�ɼ�");
	printf("%-21s", "|��Ŀ��");
	printf("%-6s", "|�ɼ�");
	printf("\n");
	for (int i = begin_index; i <= end_index; i++) {
		printf("\t________________________________________________________________________________________________________________________________________\n");
		printf("\t|%-5d", i + 1);
		DisplayAthleteInfo(SList.pSAthleteList[i]);
	}
	return 0;
}

int LocateAthlete(SAthleteList& SList, char szAthleteIDorName[]){
	int nPosition = -1;
	for (int i = 0; i < SList.nListLength; i++) {
		if (strcmp(SList.pSAthleteList[i].szAthleteName, szAthleteIDorName) == 0 || strcmp(SList.pSAthleteList[i].szAthleteID, szAthleteIDorName) == 0) {
			nPosition = i;
		}
	}
	return nPosition;
}

//�����˶�Ա���е�һ��������Ժ���ΪnAcademyIndex���˶�Աλ��
int LocateAthleteAcademy(SAthleteList& SList, int nAcademyIndex) {
	if (nAcademyIndex<1 || nAcademyIndex>ACADEMYNUMBER) {//û�������Ժ
		return -1;
	}
	int nPosition = -1;
	for (int i = 0; i < SList.nListLength; i++) {
		if (SList.pSAthleteList[i].academy == (Academy)nAcademyIndex) {
			nPosition = i;
			break;
		}
	}
	return nPosition;
}

int LocateAthleteItem(SAthlete& SAthle, char szItemIDorName[]) {
	int nPosition = -1;
	for (int i = 0; i < SAthle.nSItemNumber; i++) {
		if (strcmp(SAthle.SAthleteItem[i].szItemName, szItemIDorName) == 0 || strcmp(SAthle.SAthleteItem[i].szItemID, szItemIDorName) == 0) {
			nPosition = i;
		}
	}
	return nPosition;
}

int AddAthlete(SAthleteList& SList, SAthlete SAthle){
	if (LocateAthlete(SList, SAthle.szAthleteID) != -1 || LocateAthlete(SList, SAthle.szAthleteName) != -1) {//�Ѵ��ڵ��˶�Ա�������
		printf("�˶�Ա�Ѵ���");
		return -1;
	}

	if (SList.nListLength == SList.nListSize) {
		SAthlete* pNewBase = (SAthlete*)realloc(SList.pSAthleteList, (MAXATHLETESIZE + INCREASEATHLETESIZE) * sizeof(SAthlete));
		if (!pNewBase) {
			printf("�ڴ�����");
			exit(0);
		}
		SList.nListSize += INCREASEATHLETESIZE;
		SList.pSAthleteList = pNewBase;
	}

	SList.pSAthleteList[SList.nListLength] = SAthle;
	SList.nListLength++;
	return 0;
}

int DeleteAthlete(SAthleteList& SList, char szAthleteIDorName[]){
	int nPos = LocateAthlete(SList, szAthleteIDorName);
	if (nPos == -1) {
		printf("\n���˶�Ա������\n");
		return -1;
	}
	for (int i = nPos; i < SList.nListLength - 1; i++) {
		SList.pSAthleteList[i] = SList.pSAthleteList[i + 1];
	}
	SList.nListLength--;

	return 0;
}

int DeleteAthlete(SAthleteList& SList, int nPos_athlete) {
	if (nPos_athlete<0 || nPos_athlete>SList.nListLength - 1) {
		printf("\n���޴��˶�Ա\n");
		return -1;
	}
	for (int i = nPos_athlete; i < SList.nListLength - 1; i++) {
		SList.pSAthleteList[i] = SList.pSAthleteList[i + 1];
	}
	SList.nListLength--;
	return 0;
}

int DeleteAthleteItem(SAthlete& SAthle, char szItemIDorName[]) {
	int nPosition = LocateAthleteItem(SAthle, szItemIDorName);
	if (nPosition != -1) {
		for (int i = nPosition; i < SAthle.nSItemNumber-1; i++) {//��������Ƶ�ǰ��ȥ
			SAthle.SAthleteItem[i] = SAthle.SAthleteItem[i + 1];
		}
		SAthle.nSItemNumber--;
		return 0;
	}
	else 
		return -1;
}

int ModifiAthlete(SAthleteList& SList, char szAthleteIDorName[]){
	int nPos = LocateAthlete(SList, szAthleteIDorName);//nPosʱ
	if (nPos == -1) {
		printf("\n\t���˶�Ա������\n");
		return -1;
	}
	printf("\n\t����Ҫ�޸ĵ�����\n");
	printf("\n\t1.����\n");
	printf("\n\t2.ѧ��\n");
	printf("\n\t3.�Ա�\n");
	printf("\n\t4.����ѧԺ\n");
	printf("\n\t5.������Ŀ\n");
	int nChoice = 0;
	scanf_s("%d", &nChoice);
	if (nChoice >= 1 && nChoice <= 5) {
		switch (nChoice)
		{
		case 1: {
			char szTemp[20];
			printf("\n\t�µ�����:");
			scanf_s("%s", szTemp, 20);
			if (LocateAthlete(SList, szTemp) == -1) {
				strcpy_s(SList.pSAthleteList[nPos].szAthleteName,20, szTemp);
			}
			else
				printf("�������Ѵ���");
			break;
		}
		case 2: {
			char szTemp[20];
			printf("\n\t�µ�ѧ��:");
			scanf_s("%s", szTemp, 20);
			if (LocateAthlete(SList, szTemp) == -1) {
				strcpy_s(SList.pSAthleteList[nPos].szAthleteID,20, szTemp);
			}
			else
				printf("��ѧ���Ѵ���");
			break;
		}
		case 3: {
			int nChoice_Gender = 0;
			printf("\n\t�Ա�\n1.Ů��  \n2.����\n");
			printf("\n\t���ѡ��");
			scanf_s("%d", &nChoice_Gender);
			if (nChoice_Gender == 1)
				SList.pSAthleteList[nPos].AthleteGender = GENDER_FEMALE;
			else if(nChoice_Gender ==2)
				SList.pSAthleteList[nPos].AthleteGender = GENDER_MALE;
			break;
		}
		case 4: {
			int nChoice_Academy = 0;
			printf("\n\n\t1.֪����Ժ\n\t2.˼Դ��Ժ\n\t3.������Ժ\n\t4.��һ��Ժ\n\t5.������Ժ\n\t6.��Զ��Ժ\n\t7.������Ժ\n\t8.��ܰ��Ժ\n\t9.�о���Ժ\n");
			do {
				printf("\n\t������Ժ��");
				scanf_s("%d", &nChoice_Academy);
				if (nChoice_Academy >= 1 && nChoice_Academy <= 9) {
					SList.pSAthleteList[nPos].academy = (Academy)nChoice_Academy;
				}
			} while (nChoice_Academy < 1 && nChoice_Academy > 9);
			break;
		}
		case 5: {
			printf("\n\n");
			DisplayAthleteItem(SList.pSAthleteList[nPos]);
			printf("\n\t1.ɾ����Ŀ\n");
			printf("\n\t2.�����Ŀ\n");
			int nChoice_Item = 0;
			scanf_s("%d", &nChoice_Item);
			switch (nChoice_Item)
			{
			case 1: {
				printf("\n\n\t����������Ҫɾ������Ŀ��Ż������ƣ�");
				char szIDorName[20];
				scanf_s("%s", szIDorName, 20);
				if (DeleteAthleteItem(SList.pSAthleteList[nPos], szIDorName) == -1) {
					printf("�����������Ŀ\n");
				}
				if (SList.pSAthleteList[nPos].nSItemNumber == 0) {//��������˶�Աû�б�����Ŀ�ˣ��ͽ����˶�Ա���˶�Ա����ɾ����
					DeleteAthlete(SList, nPos);
				}
				break;
			}
			case 2: {
				if (SList.pSAthleteList[nPos].nSItemNumber == 3) {
					printf("�����˶�Ա������Ŀ���Ѵ�����");
				}
				else {
					printf("\n\n\t������Ŀ����:\n");
					SItemList list;
					InitItemList(list);
					ReadItemListFile(list);
					DisplayItemList(list);
					printf("\n\n\t�����˶�Ա�ѱ�������Ŀ\n");
					DisplayAthleteItem(SList.pSAthleteList[nPos]);
					printf("\n\t����������Ҫ��ӵ���Ŀ�������ƣ�");
					char szIDorName[20];
					scanf_s("%s", szIDorName, 20);
					if (LocateAthleteItem(SList.pSAthleteList[nPos], szIDorName) == -1) {//����Ŀδ���
						int nPosition = LocateItem(list, szIDorName);
						SList.pSAthleteList[nPos].SAthleteItem[SList.pSAthleteList[nPos].nSItemNumber] = list.pSItemList[nPosition];
						SList.pSAthleteList[nPos].nSItemNumber++;
					}
					else {
						printf("����Ŀ�Ѿ���������ٴ��");
					}
					DestroyItemList(list);
				}
				break;
			}
			default:
				break;
			}

		}//case 5: 
		default:
			break;
		}
	}

	return 0;
}

int WriteAthleteListFile(SAthleteList& SList){
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

int ReadAthleteListFile(SAthleteList& SList){
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

void CreateItemAthleteList(SAthleteList& SList,SAthleteList& SItemAthleteList, char szItemIDorName[]) {
	InitAthleteList(SItemAthleteList);
	for (int i = 0; i < SList.nListLength; i++) {
		SAthlete* pAthlete = &SList.pSAthleteList[i];
		if (LocateAthleteItem(*pAthlete, szItemIDorName) != -1) {//�����˶�Աѡ�������Ŀ
			AddAthlete(SItemAthleteList, *pAthlete);
		}
	}
}

void CreateFemaleAthleteList(SAthleteList& SList, SAthleteList& SFemaleAthleteList) {
	int nLength = SList.nListLength;
	for (int i = 0; i < nLength; i++) {
		if (SList.pSAthleteList[i].AthleteGender == GENDER_FEMALE) {
			AddAthlete(SFemaleAthleteList, SList.pSAthleteList[i]);
		}
	}
}

void CreateMaleAthleteList(SAthleteList& SList, SAthleteList& SMaleAthleteList) {
	int nLength = SList.nListLength;
	for (int i = 0; i < nLength; i++) {
		if (SList.pSAthleteList[i].AthleteGender == GENDER_MALE) {
			AddAthlete(SMaleAthleteList, SList.pSAthleteList[i]);
		}
	}
}

void AthleteFIlEUpdate_ItemModify(SSportItem& SItem) {
	SSportItem item;
	strcpy_s(item.szItemID, SItem.szItemID);
	strcpy_s(item.szItemName, SItem.szItemName);
	item.dItemTime = SItem.dItemTime;
	item.SPORTYPE_itemtype = SItem.SPORTYPE_itemtype;
	
	SAthleteList athleteList;
	SAthlete* pAthlete;
	InitAthleteList(athleteList);
	ReadAthleteListFile(athleteList);
	for (int i = 0; i < athleteList.nListLength; i++) {
		pAthlete = &athleteList.pSAthleteList[i];
		int nPos = LocateAthleteItem(*pAthlete, item.szItemID);//�ҵ�����Ŀ��λ��
		if (nPos == -1) {//����Ҳ���������ʱ�޸��˱�ţ���ʱ��Ҫ��������Ϊ���ҵĸ���
			nPos = LocateAthleteItem(*pAthlete, item.szItemName);
		}
		if (nPos == -1)
			continue;
		else {
			item.dResult = pAthlete->SAthleteItem[nPos].dResult;//���ɼ�����ԭ����ֵ
			pAthlete->SAthleteItem[nPos] = item;
		}
	}
	WriteAthleteListFile(athleteList);
	DestroyAthleteList(athleteList);
}

void AthleteFILEUpdate_ItemDelete(char szItemIDorName[]) {
	SAthleteList athleteList;
	SAthlete* pAthlete;
	InitAthleteList(athleteList);
	ReadAthleteListFile(athleteList);
	for (int i = 0; i < athleteList.nListLength; i++) {
		pAthlete = &athleteList.pSAthleteList[i];
		DeleteAthleteItem(*pAthlete, szItemIDorName);
		if (pAthlete->nSItemNumber == 0)//������˶�Աû�б����κ���Ŀ�򽫸����˶�Աɾ����
			DeleteAthlete(athleteList, i);
	}
	WriteAthleteListFile(athleteList);
	DestroyAthleteList(athleteList);
}