#include"athlete.h"

void InitAthleteList(SAthleteList& SList){
	SList.pSAthleteList = (SAthlete*)malloc(MAXATHLETESIZE*sizeof(SAthlete));
	if (!SList.pSAthleteList) {
		printf("内存已满");
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
	printf("\n\t姓名：");
	scanf_s("%s", SAthle.szAthleteName, 20);

	printf("\n\t学号：");
	scanf_s("%s", SAthle.szAthleteID, 20);

	int nChoice_Gender = 0;
	do {
		printf("\n\n\t性别：1、女性   2、男性:");
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
			printf("输入错误！\n");
			break;
		}
	} while (nChoice_Gender != 1 && nChoice_Gender != 2);

	int nChoice_Academy = 0;
	printf("\n\n\t1.知行书院\n\t2.思源书院\n\t3.弘毅书院\n\t4.敬一书院\n\t5.至诚书院\n\t6.修远书院\n\t7.明德书院\n\t8.德馨书院\n\t9.研究生院\n");
	do {
		printf("\n\t所属书院：");
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
	printf("\n\t请输入报名项目数量：");
	int nNumber_item = 0;
	while (!(cin >> nNumber_item)) {
		cin.clear();
		while (cin.get() != '\n')
			continue;
		printf("\n\t输入错误 请重新输入：");
	}
	if (nNumber_item < 0 ){
		nNumber_item = 0;
	}
	else if (nNumber_item > 3) {
		nNumber_item = 3;
	}
	SAthle.nSItemNumber = nNumber_item;
	for (int i = 0; i < SAthle.nSItemNumber; i++) {
		printf("\n\t请输入该名运动员报名的项目编号或者名字：");
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
	printf("\t|编号      |名称                |类别\t|成绩\t|\n");
	for (int i = 0; i < SAthle.nSItemNumber; i++) {
		printf("\t|%-10s", SAthle.SAthleteItem[i].szItemID);
		printf("|%-20s", SAthle.SAthleteItem[i].szItemName);

		if (SAthle.SAthleteItem[i].SPORTYPE_itemtype == SPORTTYPE_TRACK)
			printf("|径赛\t");
		else if (SAthle.SAthleteItem[i].SPORTYPE_itemtype == SPORTTYPE_FIELD)
			printf("|田赛\t");
		if (SAthle.SAthleteItem[i].dResult < 0 || SAthle.SAthleteItem[i].dResult>1000) {
			printf("|%2s\t|", "无");
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
		printf("%-7s","|女");
	else
		printf("%-7s","|男");

	switch (SAthle.academy)
	{
	case 知行书院:
		printf("|知行书院\t");
		break;
	case 思源书院:
		printf("|思源书院\t");
		break;
	case 弘毅书院:
		printf("|弘毅书院\t");
		break;
	case 敬一书院:
		printf("|敬一书院\t");
		break;
	case 至诚书院:
		printf("|至诚书院\t");
		break;
	case 修远书院:
		printf("|修远书院\t");
		break;
	case 明德书院:
		printf("|明德书院\t");
		break;
	case 德馨书院:
		printf("|德馨书院\t");
		break;
	case 研究生院:
		printf("|研究生院\t");
		break;
	default:
		break;
	}

	for (int i = 0; i < SAthle.nSItemNumber; i++) {
		printf("|%-20s", SAthle.SAthleteItem[i].szItemName);
		if(SAthle.SAthleteItem[i].dResult>0&& SAthle.SAthleteItem[i].dResult<=1000)//比赛的成绩应该不会超过这个范围。
			printf("|%-6.2lf", SAthle.SAthleteItem[i].dResult);
		else {
			printf("|%-5s", "无");
		}
	}
	for (int i = SAthle.nSItemNumber; i < 3; i++) {
		printf("%-21s","|未填报");
		printf("|%-5s", "无");
	}

	printf("\n");

}

void DisplayAthleteListInfo(const SAthleteList& SList) {
	printf("\n\n");
	printf("\t%-6s", "|序号");
	printf("|%-15s","学号");
	printf("|%-10s", "姓名");
	printf("%-7s","|性别");
	printf("|书院\t\t");
	printf("%-21s", "|项目一");
	printf("%-7s", "|成绩");
	printf("%-21s", "|项目二");
	printf("%-6s", "|成绩");
	printf("%-21s", "|项目三");
	printf("%-6s", "|成绩");
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
	printf("\t%-6s", "|序号");
	printf("|%-15s", "学号");
	printf("|%-10s", "姓名");
	printf("%-7s", "|性别");
	printf("|书院\t\t");
	printf("%-21s", "|项目一");
	printf("%-7s", "|成绩");
	printf("%-21s", "|项目二");
	printf("%-6s", "|成绩");
	printf("%-21s", "|项目三");
	printf("%-6s", "|成绩");
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

//返回运动员表中第一个所属书院编号为nAcademyIndex的运动员位置
int LocateAthleteAcademy(SAthleteList& SList, int nAcademyIndex) {
	if (nAcademyIndex<1 || nAcademyIndex>ACADEMYNUMBER) {//没有这个书院
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
	if (LocateAthlete(SList, SAthle.szAthleteID) != -1 || LocateAthlete(SList, SAthle.szAthleteName) != -1) {//已存在的运动员不能添加
		printf("运动员已存在");
		return -1;
	}

	if (SList.nListLength == SList.nListSize) {
		SAthlete* pNewBase = (SAthlete*)realloc(SList.pSAthleteList, (MAXATHLETESIZE + INCREASEATHLETESIZE) * sizeof(SAthlete));
		if (!pNewBase) {
			printf("内存已满");
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
		printf("\n该运动员不存在\n");
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
		printf("\n并无此运动员\n");
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
		for (int i = nPosition; i < SAthle.nSItemNumber-1; i++) {//将后面的移到前面去
			SAthle.SAthleteItem[i] = SAthle.SAthleteItem[i + 1];
		}
		SAthle.nSItemNumber--;
		return 0;
	}
	else 
		return -1;
}

int ModifiAthlete(SAthleteList& SList, char szAthleteIDorName[]){
	int nPos = LocateAthlete(SList, szAthleteIDorName);//nPos时
	if (nPos == -1) {
		printf("\n\t该运动员不存在\n");
		return -1;
	}
	printf("\n\t你需要修改的内容\n");
	printf("\n\t1.姓名\n");
	printf("\n\t2.学号\n");
	printf("\n\t3.性别\n");
	printf("\n\t4.所属学院\n");
	printf("\n\t5.所报项目\n");
	int nChoice = 0;
	scanf_s("%d", &nChoice);
	if (nChoice >= 1 && nChoice <= 5) {
		switch (nChoice)
		{
		case 1: {
			char szTemp[20];
			printf("\n\t新的名称:");
			scanf_s("%s", szTemp, 20);
			if (LocateAthlete(SList, szTemp) == -1) {
				strcpy_s(SList.pSAthleteList[nPos].szAthleteName,20, szTemp);
			}
			else
				printf("该名称已存在");
			break;
		}
		case 2: {
			char szTemp[20];
			printf("\n\t新的学号:");
			scanf_s("%s", szTemp, 20);
			if (LocateAthlete(SList, szTemp) == -1) {
				strcpy_s(SList.pSAthleteList[nPos].szAthleteID,20, szTemp);
			}
			else
				printf("该学号已存在");
			break;
		}
		case 3: {
			int nChoice_Gender = 0;
			printf("\n\t性别：\n1.女性  \n2.男性\n");
			printf("\n\t你的选择：");
			scanf_s("%d", &nChoice_Gender);
			if (nChoice_Gender == 1)
				SList.pSAthleteList[nPos].AthleteGender = GENDER_FEMALE;
			else if(nChoice_Gender ==2)
				SList.pSAthleteList[nPos].AthleteGender = GENDER_MALE;
			break;
		}
		case 4: {
			int nChoice_Academy = 0;
			printf("\n\n\t1.知行书院\n\t2.思源书院\n\t3.弘毅书院\n\t4.敬一书院\n\t5.至诚书院\n\t6.修远书院\n\t7.明德书院\n\t8.德馨书院\n\t9.研究生院\n");
			do {
				printf("\n\t所属书院：");
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
			printf("\n\t1.删除项目\n");
			printf("\n\t2.添加项目\n");
			int nChoice_Item = 0;
			scanf_s("%d", &nChoice_Item);
			switch (nChoice_Item)
			{
			case 1: {
				printf("\n\n\t请输入你需要删除的项目编号或者名称：");
				char szIDorName[20];
				scanf_s("%s", szIDorName, 20);
				if (DeleteAthleteItem(SList.pSAthleteList[nPos], szIDorName) == -1) {
					printf("不存在这个项目\n");
				}
				if (SList.pSAthleteList[nPos].nSItemNumber == 0) {//如果该名运动员没有报名项目了，就将该运动员从运动员表中删除。
					DeleteAthlete(SList, nPos);
				}
				break;
			}
			case 2: {
				if (SList.pSAthleteList[nPos].nSItemNumber == 3) {
					printf("该名运动员报名项目数已达上限");
				}
				else {
					printf("\n\n\t所有项目如下:\n");
					SItemList list;
					InitItemList(list);
					ReadItemListFile(list);
					DisplayItemList(list);
					printf("\n\n\t改名运动员已报名的项目\n");
					DisplayAthleteItem(SList.pSAthleteList[nPos]);
					printf("\n\t请输入你需要添加的项目或者名称：");
					char szIDorName[20];
					scanf_s("%s", szIDorName, 20);
					if (LocateAthleteItem(SList.pSAthleteList[nPos], szIDorName) == -1) {//该项目未曾填报
						int nPosition = LocateItem(list, szIDorName);
						SList.pSAthleteList[nPos].SAthleteItem[SList.pSAthleteList[nPos].nSItemNumber] = list.pSItemList[nPosition];
						SList.pSAthleteList[nPos].nSItemNumber++;
					}
					else {
						printf("该项目已经填报，不需再次填报");
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
		printf("文件打开失败");
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
		printf("文件打开失败");
		exit(0);
	}

	SAthlete SAthle;
	if (pFAthleteFile) {
		fread(&SAthle, sizeof(SAthlete), 1, pFAthleteFile);
		fgetc(pFAthleteFile);
		while (!feof(pFAthleteFile)) {
			if (ferror(pFAthleteFile)) {
				clearerr(pFAthleteFile);
				printf("文件读取出错");
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
		if (LocateAthleteItem(*pAthlete, szItemIDorName) != -1) {//该名运动员选了这个项目
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
		int nPos = LocateAthleteItem(*pAthlete, item.szItemID);//找到该项目的位置
		if (nPos == -1) {//编号找不到，可能时修改了编号，这时需要用姓名作为查找的根据
			nPos = LocateAthleteItem(*pAthlete, item.szItemName);
		}
		if (nPos == -1)
			continue;
		else {
			item.dResult = pAthlete->SAthleteItem[nPos].dResult;//将成绩保持原来的值
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
		if (pAthlete->nSItemNumber == 0)//如果该运动员没有报名任何项目则将该名运动员删除。
			DeleteAthlete(athleteList, i);
	}
	WriteAthleteListFile(athleteList);
	DestroyAthleteList(athleteList);
}