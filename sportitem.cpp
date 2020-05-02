#include"sportitem.h"

void CreateItem(SSportItem& SItem) {
	
	printf("\n\t��������Ŀ����:");
	scanf_s("%s", SItem.szItemName, 20);

	printf("\n\t��������Ŀ���:");
	scanf_s("%s", SItem.szItemID,10);

	int nItemType=0;
	printf("\n\t0:������1:����\n��Ŀ���:");
	scanf_s("%d", &nItemType);
	SItem.SPORTYPE_itemtype = (SPORTTYPE)nItemType;

	printf("\n\tÿ������ʱ��(min):");
	scanf_s("%lf", &SItem.dItemTime);
}

void DisplayItem(const SSportItem& SItem) {
	printf("\t|%-10s", SItem.szItemID);
	printf("|%-20s", SItem.szItemName);

	if (SItem.SPORTYPE_itemtype == SPORTTYPE_TRACK)
		printf("|����\t");
	else if (SItem.SPORTYPE_itemtype == SPORTTYPE_FIELD)
		printf("|����\t");

	printf("|%.2lf\t|", SItem.dItemTime);
	printf("\n");
}

void DisplayItemList(const SItemList& SList) {
	printf("\t|���      |����                |���\t|��ʱ\t|\n");
	for (int i = 0; i < SList.nListLength; i++) {
		printf("\t__________________________________________________________\n");
		DisplayItem(SList.pSItemList[i]);
	}
}

void InitItemList(SItemList& SList) {
	SList.pSItemList = (SSportItem*)malloc(MAXITEMSIZE*sizeof(SSportItem));
	if (!SList.pSItemList) {
		printf("�ڴ�����");
		exit(0);
	}
	SList.nListSize = MAXITEMSIZE;
	SList.nListLength = 0;
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

int AddItem(SItemList& SList,SSportItem SItem) {
	SSportItem* pSNewBase;

	if ((LocateItem(SList, SItem.szItemID) != -1)||(LocateItem(SList,SItem.szItemName)!=-1)) {
		printf("��Ŀ�Ѵ���\n");
		return -1;
	}

	if (SList.nListLength == SList.nListSize) {
		pSNewBase = (SSportItem*)realloc(SList.pSItemList,(SList.nListSize+INCREASEITEMSIZE)*sizeof(SSportItem));
		if (!pSNewBase) {
			printf("�ڴ�����");
			exit(0);
		}
		SList.nListSize += INCREASEITEMSIZE;
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
	for (int i = nPosition; i < SList.nListLength-1; i++) {
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

	int nChoice = 0;
	printf("\n\n\t����Ҫ�޸ĵ����ݣ�\n");
	printf("\n\t1.��Ŀ���\n");
	printf("\n\t2.��Ŀ����\n");
	printf("\n\t3.��Ŀ���\n");
	printf("\n\t4.ÿ������ʱ��\n");
	printf("\n\t���ѡ��");
	scanf_s("%d", &nChoice);
	switch (nChoice)
	{
	case 1: {
		char szTemp[10];
		printf("\n\n\t�µı��:");
		scanf_s("%s", szTemp, 10);
		if (LocateItem(SList, szTemp) == -1) {
			strcpy_s(SList.pSItemList[nPosition].szItemID,10, szTemp);
		}
		else
			printf("�ñ���Ѵ���\n");
		break;
	}
	case 2: {
		char szTemp[20];
		printf("\n\n\t�µ�����:");
		scanf_s("%s", szTemp, 20);
		if (LocateItem(SList, szTemp) == -1) {
			strcpy_s(SList.pSItemList[nPosition].szItemName,20, szTemp);
		}
		else
			printf("�������Ѵ���");
		break;
	}
	case 3: {
		int nChoiceType = 0;
		printf("\n\n\t�µ���Ŀ���: \n1.����\n2.����");
		printf("\n\t���ѡ��");
		scanf_s("%d",&nChoiceType);
		if (nChoiceType == 1)
			SList.pSItemList[nPosition].SPORTYPE_itemtype = SPORTTYPE_FIELD;
		else if (nChoiceType == 2)
			SList.pSItemList[nPosition].SPORTYPE_itemtype = SPORTTYPE_TRACK;
		else
			printf("\n�����������\n");
		break;
	}
	case 4:
		printf("\n\n\t�µ�ʱ��(\min):");
		scanf_s("%lf", &SList.pSItemList[nPosition].dItemTime);
		break;
	default:
		printf("\n\t��������ȷ�����\n");
		break;
	}
	return 0;
}

int WriteItemListFile(SItemList& SList) {
	FILE* pFItemFile;
	errno_t err = fopen_s(&pFItemFile, "iteminfo.txt", "w");
	if (err != 0) {
		printf("�ļ���ʧ��");
		exit(0);
	}
	if (pFItemFile) {
		for (int i = 0; i < SList.nListLength; i++) {
			fwrite(&SList.pSItemList[i], sizeof(SSportItem), 1, pFItemFile);
			fputc('\n', pFItemFile);
		}//for
		fclose(pFItemFile);
	}//if
	return 0;
}

int ReadItemListFile(SItemList& SList) {
	FILE* pFItemFile;
	errno_t err = fopen_s(&pFItemFile, "iteminfo.txt", "r");
	if (err != 0) {
		printf("�ļ���ʧ��");
		exit(0);
	}

	SSportItem SItem;
	if (pFItemFile) {
		fread(&SItem, sizeof(SSportItem), 1, pFItemFile);
		fgetc(pFItemFile);
		while (!feof(pFItemFile)) {//feof()��ȡ��EOFʱ����true�����򷵻�false
			if (ferror(pFItemFile)) {//ferror()��ȡ����ʱ����true,���򷵻�false 
				clearerr(pFItemFile);
				printf("�ļ���ȡ����");
				exit(0);
			}
			AddItem(SList, SItem);
			fread(&SItem, sizeof(SSportItem), 1, pFItemFile);
			fgetc(pFItemFile);
		}//while
		fclose(pFItemFile);
	}//if
	return 0;
}
