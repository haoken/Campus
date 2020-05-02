#include"sportitem.h"

void CreateItem(SSportItem& SItem) {
	
	printf("\n\t请输入项目名字:");
	scanf_s("%s", SItem.szItemName, 20);

	printf("\n\t请输入项目编号:");
	scanf_s("%s", SItem.szItemID,10);

	int nItemType=0;
	printf("\n\t0:田赛；1:径赛\n项目类别:");
	scanf_s("%d", &nItemType);
	SItem.SPORTYPE_itemtype = (SPORTTYPE)nItemType;

	printf("\n\t每场比赛时间(min):");
	scanf_s("%lf", &SItem.dItemTime);
}

void DisplayItem(const SSportItem& SItem) {
	printf("\t|%-10s", SItem.szItemID);
	printf("|%-20s", SItem.szItemName);

	if (SItem.SPORTYPE_itemtype == SPORTTYPE_TRACK)
		printf("|径赛\t");
	else if (SItem.SPORTYPE_itemtype == SPORTTYPE_FIELD)
		printf("|田赛\t");

	printf("|%.2lf\t|", SItem.dItemTime);
	printf("\n");
}

void DisplayItemList(const SItemList& SList) {
	printf("\t|编号      |名称                |类别\t|耗时\t|\n");
	for (int i = 0; i < SList.nListLength; i++) {
		printf("\t__________________________________________________________\n");
		DisplayItem(SList.pSItemList[i]);
	}
}

void InitItemList(SItemList& SList) {
	SList.pSItemList = (SSportItem*)malloc(MAXITEMSIZE*sizeof(SSportItem));
	if (!SList.pSItemList) {
		printf("内存已满");
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
		printf("项目已存在\n");
		return -1;
	}

	if (SList.nListLength == SList.nListSize) {
		pSNewBase = (SSportItem*)realloc(SList.pSItemList,(SList.nListSize+INCREASEITEMSIZE)*sizeof(SSportItem));
		if (!pSNewBase) {
			printf("内存已满");
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
			printf("项目不存在\n");
			return -1;//项目表中不存在这个项目。
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
		printf("项目不存在");
		return -1;
	}

	int nChoice = 0;
	printf("\n\n\t你需要修改的内容：\n");
	printf("\n\t1.项目编号\n");
	printf("\n\t2.项目名称\n");
	printf("\n\t3.项目类别\n");
	printf("\n\t4.每组所需时间\n");
	printf("\n\t你的选择：");
	scanf_s("%d", &nChoice);
	switch (nChoice)
	{
	case 1: {
		char szTemp[10];
		printf("\n\n\t新的编号:");
		scanf_s("%s", szTemp, 10);
		if (LocateItem(SList, szTemp) == -1) {
			strcpy_s(SList.pSItemList[nPosition].szItemID,10, szTemp);
		}
		else
			printf("该编号已存在\n");
		break;
	}
	case 2: {
		char szTemp[20];
		printf("\n\n\t新的名称:");
		scanf_s("%s", szTemp, 20);
		if (LocateItem(SList, szTemp) == -1) {
			strcpy_s(SList.pSItemList[nPosition].szItemName,20, szTemp);
		}
		else
			printf("该名称已存在");
		break;
	}
	case 3: {
		int nChoiceType = 0;
		printf("\n\n\t新的项目类别: \n1.田赛\n2.径赛");
		printf("\n\t你的选择：");
		scanf_s("%d",&nChoiceType);
		if (nChoiceType == 1)
			SList.pSItemList[nPosition].SPORTYPE_itemtype = SPORTTYPE_FIELD;
		else if (nChoiceType == 2)
			SList.pSItemList[nPosition].SPORTYPE_itemtype = SPORTTYPE_TRACK;
		else
			printf("\n并无这种类别\n");
		break;
	}
	case 4:
		printf("\n\n\t新的时间(\min):");
		scanf_s("%lf", &SList.pSItemList[nPosition].dItemTime);
		break;
	default:
		printf("\n\t请输入正确的序号\n");
		break;
	}
	return 0;
}

int WriteItemListFile(SItemList& SList) {
	FILE* pFItemFile;
	errno_t err = fopen_s(&pFItemFile, "iteminfo.txt", "w");
	if (err != 0) {
		printf("文件打开失败");
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
		printf("文件打开失败");
		exit(0);
	}

	SSportItem SItem;
	if (pFItemFile) {
		fread(&SItem, sizeof(SSportItem), 1, pFItemFile);
		fgetc(pFItemFile);
		while (!feof(pFItemFile)) {//feof()读取到EOF时返回true，否则返回false
			if (ferror(pFItemFile)) {//ferror()读取出错时返回true,否则返回false 
				clearerr(pFItemFile);
				printf("文件读取出错");
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
