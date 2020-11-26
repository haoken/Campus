#include"sportitem.h"

void CreateItem(SSportItem& SItem) {
	//名称
	printf("\n\t请输入项目名称:");
	GetString(SItem.szItemName, 20);

	//性别
	char male[] = "男";
	char female[] = "女";
	if (Index_BF(SItem.szItemName, male) != -1)
		SItem.GENDER_itemgender = GENDER_MALE;
	else if (Index_BF(SItem.szItemName, female) != -1)
		SItem.GENDER_itemgender = GENDER_FEMALE;
	else {
		printf("\n\t1.男子组  2.女子组\n");
		printf("\t你的选择：");
		int option;
		option = GetOption(1, 2);
		if (option == 1) {
			SItem.GENDER_itemgender = GENDER_MALE;
			char tmp[25]="男子";
			strncat_s(tmp, SItem.szItemName, sizeof(SItem.szItemName));
			strcpy_s(SItem.szItemName, tmp);
		}
		else {
			SItem.GENDER_itemgender = GENDER_FEMALE;
			char tmp[25] = "女子";
			strncat_s(tmp, SItem.szItemName, sizeof(tmp));
			strcpy_s(SItem.szItemName, tmp);
		}
	}

	//编号
	printf("\n\t请输入项目编号:");
	GetString(SItem.szItemID, sizeof(SItem.szItemID));

	//类别
	int nItemType = 0;
	printf("\n\t0:田赛；1:径赛\n\t项目类别:");
	nItemType = GetOption(0, 1);
	if (nItemType == 0)
		SItem.SPORTTYPE_itemtype = SPORTTYPE_FIELD;
	else
		SItem.SPORTTYPE_itemtype = SPORTTYPE_TRACK;
	
	printf("\n\t输入场地：");
	GetString(SItem.szPlace, sizeof(SItem.szPlace));

	//耗时
	printf("\n\t每场比赛时间(min):");
	SItem.dItemTime = GetDouble(0,1000);

	//运动员表初始化
	SAthleteList *athletelist = (SAthleteList*)malloc(sizeof(SAthleteList));
	InitAthleteList(*athletelist);
	SItem.pAthleteList = athletelist;

	//运动员分组表在运动员报名之后才会生成。
	SItem.ppAthleteGroup = NULL;
	SItem.GroupNumber = 0;

	//成绩是在比赛完成后输入的
	SItem.dResult = 0;
}

//初始化项目表
void InitItemList(SItemList& SList) {
	SList.pSItemList = (SSportItem*)malloc(ITEMLIST_INIT_SIZE * sizeof(SSportItem));
	if (!SList.pSItemList) {
		printf("内存已满");
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
		printf("\t|编号      |名称                      |类别\t|场地  |耗时(min)|人数|");
		printf("\n\t________________________________________________________________________\n");
	}
	printf("\t|%-10s", SItem.szItemID);
	printf("|%-26s", SItem.szItemName);

	if (SItem.SPORTTYPE_itemtype == SPORTTYPE_TRACK)
		printf("|径赛\t");
	else if (SItem.SPORTTYPE_itemtype == SPORTTYPE_FIELD)
		printf("|田赛\t");

	printf("|%-6s", SItem.szPlace);

	printf("|%-9.2lf", SItem.dItemTime);

	printf("|%-2d  |", SItem.pAthleteList->nListLength);
}

void DisplayItemList(const SItemList& SList) {
	printf("\t|编号      |名称                      |类别\t|场地  |耗时(min)|人数|");
	for (int i = 0; i < SList.nListLength; i++) {
		printf("\n\t________________________________________________________________________\n");
		DisplayItem(SList.pSItemList[i],false);
	}
}

//显示第i页
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
	printf("\t|序号   |编号      |名称                      |类别\t|场地  |耗时(min)|人数|");
	printf("\n");
	for (int i = (page - 1) * NumberPerPage; i < page * NumberPerPage; i++) {
		if (i >= SList.nListLength)//如果表为空,或者到达最大值
			break;
		printf("\t____________________________________________________________________________________\n");
		printf("\t|%-4d", i + 1);
		DisplayItem(SList.pSItemList[i], false);
		printf("\n");
	}
	printf("\n\t\t\t\t\t        \t第%d/%d页\t\t\n", page, maxPage);
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
		printf("项目已存在\n");
		return -1;
	}

	if (SList.nListLength == SList.nListSize) {
		pSNewBase = (SSportItem*)realloc(SList.pSItemList, (SList.nListSize +ITEMLIST_INCREASEMENT) * sizeof(SSportItem));
		if (!pSNewBase) {
			printf("内存已满");
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
		printf("项目不存在\n");
		return -1;//项目表中不存在这个项目。
	}

	//同步到运动员表
	SSportItem* item = &SList.pSItemList[nPosition];
	SAthleteList* athleteList = SList.pSItemList[nPosition].pAthleteList;
	SAthleteList allAthlete;
	InitAthleteList(allAthlete);
	ReadAthleteListFile(allAthlete);
	for (int i = 0; i < athleteList->nListLength; i++) {//或得每一个学生，然后取消这个项目
		char* szAthleteID = athleteList->pSAthleteList[i].szAthleteID;//学生名
		int nPos_Athlete = LocateAthlete(allAthlete, szAthleteID);//找到学生的位置
		SAthlete* athlete = &allAthlete.pSAthleteList[nPos_Athlete];
		DeleteAthleteItem(*athlete, item->szItemID);
	}
	WriteAthleteListFile(allAthlete);//同步之后，写入文件

	for (int i = nPosition; i < SList.nListLength - 1; i++) {
		SList.pSItemList[i] = SList.pSItemList[i + 1];
	}
	SList.nListLength--;

	return 0;
}

int DeleteItem(SItemList& SList, int pos) {
	int nPosition = pos;
	if (nPosition == -1) {
		printf("项目不存在\n");
		return -1;//项目表中不存在这个项目。
	}

	//同步到运动员表
	SSportItem* item = &SList.pSItemList[nPosition];
	SAthleteList* athleteList = SList.pSItemList[nPosition].pAthleteList;
	SAthleteList allAthlete;
	InitAthleteList(allAthlete);
	ReadAthleteListFile(allAthlete);
	for (int i = 0; i < athleteList->nListLength; i++) {//或得每一个学生，然后取消这个项目
		char* szAthleteID = athleteList->pSAthleteList[i].szAthleteID;//学生名
		int nPos_Athlete = LocateAthlete(allAthlete, szAthleteID);//找到学生的位置
		SAthlete* athlete = &allAthlete.pSAthleteList[nPos_Athlete];
		DeleteAthleteItem(*athlete, item->szItemID);
	}
	WriteAthleteListFile(allAthlete);//同步之后，写入文件

	for (int i = nPosition; i < SList.nListLength - 1; i++) {
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
	system("cls");
	SSportItem* pSItem = &SList.pSItemList[nPosition];
	DisplayItem(*pSItem, true);
	int nChoice = 0;
	printf("\n\n\t你需要修改的内容：\n");
	printf("\n\t1.项目编号\n");
	printf("\n\t2.项目名称\n");
	printf("\n\t3.项目类别\n");
	printf("\n\t4.每组所需时间\n");
	printf("\n\t5.场地\n");
	printf("\n\t6.取消\n");
	printf("\n\t你的选择：");
	nChoice = GetOption(1, 6);
	switch (nChoice)
	{
	case 1: {//编号
		char szTemp[10];
		printf("\n\n\t新的编号:");
		GetString(szTemp, 10);
		if (LocateItem(SList, szTemp) == -1) {
			strcpy_s(pSItem->szItemID, sizeof(pSItem->szItemID), szTemp);
		}
		else {
			printf("该编号已存在\n");
			return -1;
		}

		break;
	}
	case 2: {//名称
		char szTemp[25];
		printf("\n\n\t新的名称:");
		GetString(szTemp, sizeof(szTemp));
		int flag = true;

		if ((Index_BF(szTemp, "男") != -1 && pSItem->GENDER_itemgender == GENDER_MALE)|| (Index_BF(szTemp, "女") != -1 && pSItem->GENDER_itemgender == GENDER_FEMALE)) {//名称中带男，性别是女
			flag = true;
		}
		else if ((Index_BF(szTemp, "男") != -1 && pSItem->GENDER_itemgender == GENDER_FEMALE) || (Index_BF(szTemp, "女") != -1 && pSItem->GENDER_itemgender == GENDER_MALE)) {//名称中带女，性别是男
			flag = false;
		}
		else if (Index_BF(szTemp, "男") == -1 || Index_BF(szTemp, "女") == -1) {//名字中不带男女
			if (pSItem->GENDER_itemgender == GENDER_FEMALE) {
				char tmp[25] = "女子";
				strncat_s(tmp, szTemp, sizeof(tmp));
				strcpy_s(szTemp, tmp);
			}
			else {
				char tmp[25] = "男子";
				strncat_s(tmp, szTemp, sizeof(tmp));
				strcpy_s(szTemp, tmp);
			}
		}
		if (flag == false) {
			printf("改名不符合规则！注意性别。");
			getchar();
			return -1;
		}

		if (LocateItem(SList, szTemp) == -1) {
			strcpy_s(pSItem->szItemName, sizeof(pSItem->szItemName), szTemp);
		}
		else
			printf("该名称已存在");
		break;
	}
	case 3: {//类别
		int nChoiceType = 0;
		printf("\n\n\t新的项目类别: \n1.田赛\n2.径赛");
		printf("\n\t你的选择：");
		nChoiceType = GetOption(1, 2);
		if (nChoiceType == 1)
			pSItem->SPORTTYPE_itemtype = SPORTTYPE_FIELD;
		else if (nChoiceType == 2)
			pSItem->SPORTTYPE_itemtype = SPORTTYPE_TRACK;
		break;
	}
	case 4://时间
		printf("\n\n\t新的时间(\min):");
		pSItem->dItemTime = GetDouble();
		break;
	case 5: {//场地
		printf("\n\t输入新的场地：");
		GetString(pSItem->szPlace, sizeof(pSItem->szPlace));
	}
	case 6://取消
		return 0;
	}

	SAthleteList allAthlete;
	InitAthleteList(allAthlete);
	ReadAthleteListFile(allAthlete);
	if (nChoice != 6) {//同步到运动员表，所有选了该项目的人更新此项目
		for (int i = 0; i < pSItem->pAthleteList->nListLength; i++) {//报名表中逐个取处运动员进行处理
			SAthlete* athlete = &pSItem->pAthleteList->pSAthleteList[i];//需要修改的运动员
			int nPos_athlete = LocateAthlete(allAthlete, athlete->szAthleteID);//该运动员的在运动员表中的位置
			int nPos_item = LocateAthleteItem(allAthlete.pSAthleteList[nPos_athlete], pSItem->szItemID);//该项目在该运动员报名项目中的位置
			allAthlete.pSAthleteList[nPos_athlete].SAthleteItem[nPos_item] = *pSItem;//将该项目替换成该项目
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
		printf("iteminfo.txt文件打开失败");
		exit(0);
	}
	if (pFItemFile) {
		for (int i = 0; i < SList.nListLength; i++) {
			fwrite(&SList.pSItemList[i], sizeof(SSportItem), 1, pFItemFile);//写入项目
			fputc('\n', pFItemFile);//写换行
			int length = SList.pSItemList[i].pAthleteList->nListLength;
			fwrite(&length, sizeof(int), 1, pFItemFile);//写入报名运动员列表长度
			for (int j = 0; j < length; j++) {//写入所有组员的名单
				fwrite(&SList.pSItemList[i].pAthleteList->pSAthleteList[j], sizeof(SAthlete), 1, pFItemFile);
				fputc('\n', pFItemFile);//写换行
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
		printf("iteminfo.txt文件打开失败");
		exit(0);
	}
	SSportItem SItem;//项目
	SAthlete athlete;//运动员
	if (pFItemFile) {
		while (!feof(pFItemFile)) {
			if (ferror(pFItemFile)) {//ferror()读取出错时返回true,否则返回false 
				clearerr(pFItemFile);
				printf("文件读取出错");
				exit(0);
			}
			SAthleteList* athletelist = (SAthleteList*)malloc(sizeof(SAthleteList));//项目的报名名单
			InitAthleteList(*athletelist);
			fread(&SItem, sizeof(SSportItem), 1, pFItemFile);//读取项目
			fgetc(pFItemFile);//读换行
			if (feof(pFItemFile)) {//最后一次读取会读到eof
				break;
			}
			int length;
			fread(&length, sizeof(int), 1, pFItemFile);//读取报名运动员表长度
			for (int i = 0; i < length; i++) {//读取运动员表
				fread(&athlete, sizeof(SAthlete), 1, pFItemFile);
				fgetc(pFItemFile);//读换行
				AddAthlete(*athletelist, athlete);//添加运动员到运动员表
			}
			SItem.pAthleteList = athletelist;
			AddItem(SList, SItem);//添加项目到项目表。
		}
		fclose(pFItemFile);
	}
	return 0;
}

int Grouping(SItemList& SList) {
	SAcademyList academylist;
	InitAcademyList(academylist);
	ReadAcademyListFile(academylist);
	for (int i = 0; i < SList.nListLength; i++) {//处理每个项目
		if (SList.pSItemList[i].pAthleteList->nListLength == 0) {
			SList.pSItemList[i].GroupNumber = 0;
			SList.pSItemList[i].ppAthleteGroup = NULL;
			continue;
		}
		if (SList.pSItemList[i].SPORTTYPE_itemtype==SPORTTYPE_TRACK) {//径赛分组
			int* nAcademy = (int*)malloc(academylist.nListLength * sizeof(int));
			for (int j = 0; j < academylist.nListLength; j++) {
				nAcademy[j] = 0;
			}
			SSportItem* item = &SList.pSItemList[i];
			int nGroupNumber = 0;
			if (item->pAthleteList->nListLength % 8 == 0)//八条跑道
				nGroupNumber = item->pAthleteList->nListLength / 8;
			else
				nGroupNumber = item->pAthleteList->nListLength / 8 + 1;
			item->GroupNumber = nGroupNumber;

			if (item->GroupNumber == 0) {//如果没有运动员报名该项目，就直接从下一个项目开始
				free(nAcademy);
				continue;
			}

			item->ppAthleteGroup = (SAthleteList**)malloc(nGroupNumber * sizeof(SAthleteList*));
			for (int j = 0; j < nGroupNumber; j++) {
				item->ppAthleteGroup[j] = (SAthleteList*)malloc(sizeof(SAthleteList));//ppAthleteGroup指向几个分组的运动员列表
				InitAthleteList(*item->ppAthleteGroup[j]);
			}


			SAthleteList szTempAthleteList;//这个是报名了这个项目的一个备份表。因为不能直接处理项目报名表。所以用一个备用表
			InitAthleteList(szTempAthleteList);
			for (int j = 0; j < item->pAthleteList->nListLength; j++) {
				SAthlete* athlete = &item->pAthleteList->pSAthleteList[j];
				int index = LocateAcademy(academylist, athlete->academy.szAcademyName);
				if (index == -1) {
					printf("\n\t存在学生属于没有参赛的单位\n");
					return 0;
				}
				nAcademy[index]++;
				AddAthlete(szTempAthleteList, *athlete);
			}


			int nDiv = item->pAthleteList->nListLength / nGroupNumber;
			int nMod = item->pAthleteList->nListLength % nGroupNumber;
			int iGroup = 0;//第i组
			int nIndex = 0;

			while (szTempAthleteList.nListLength > 0 && iGroup < nGroupNumber) {
				while (nAcademy[nIndex] == 0) {//选择某个书院的人，轮着选
					if (nIndex == academylist.nListLength - 1)
						nIndex = 0;
					else
						nIndex++;
				}
				nAcademy[nIndex]--;
				int nAcademyIndex = nIndex;//要将序号为nAcademyIndex的书院的运动员进行分组

				if (nIndex == academylist.nListLength - 1)
					nIndex = 0;
				else
					nIndex++;

				for (int j = 0; j < szTempAthleteList.nListLength; j++) {
					if (strcmp(szTempAthleteList.pSAthleteList[j].academy.szAcademyName, academylist.pSAcademyList[nAcademyIndex].szAcademyName) == 0) {
						AddAthlete(*item->ppAthleteGroup[iGroup], szTempAthleteList.pSAthleteList[j]);//把这个运动员加入到第i个分组中
						DeleteAthlete(szTempAthleteList, szTempAthleteList.pSAthleteList[j].szAthleteID);//把这个运动员删除
						break;
					}
				}

				if (iGroup < nMod && item->ppAthleteGroup[iGroup]->nListLength == nDiv + 1) {//如果组数在0~nMod之间，且这一组的人数达到nDiv+1，则继续处理下一组
					iGroup++;
				}
				else if (iGroup <= nGroupNumber - 1 && iGroup >= nMod && item->ppAthleteGroup[iGroup]->nListLength == nDiv) {//如果不是最后一组，且人数达到nDiv就处理下一组
					iGroup++;
				}//else
			}//while()
			free(nAcademy);
		}
		else {//处理田赛
			SSportItem* item = &SList.pSItemList[i];
			item->GroupNumber = 1;
			item->ppAthleteGroup = (SAthleteList**)malloc(sizeof(SAthleteList*));
			item->ppAthleteGroup[0] = (SAthleteList*)malloc(sizeof(SAthleteList));
			InitAthleteList(*item->ppAthleteGroup[0]);
			for (int i = 0; i < item->pAthleteList->nListLength; i++) {//田赛将所有的运动员放到一个组中。
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
		SSportItem* item = &SList.pSItemList[i];//该项目
		for (int j = 0; j < item->GroupNumber; j++) {
			SAthleteList* athletelist = item->ppAthleteGroup[j];//该项目的其中一个分组
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
			}//for(k)冒泡排序
		}//for(j)分组
	}//for(i)项目
}

//打印出第n组
void DisplayNGroup(SSportItem&SItem,int n) {
	DisplayAthleteListInfo(*SItem.ppAthleteGroup[n - 1]);
}

int DisplayGroupingPagination(SSportItem& SItem,const char*szTitle,const char*szThirdChoice) {
	if (SItem.GroupNumber == 0) {
		printf("\n该项目无人报名\n");
		system("pause");
		return 0;
	}
	int nGroupNumber = SItem.GroupNumber;
	int iGroup = 1;//第一组
	while (true) {
		system("cls");
		printf("\t%s\n",szTitle);
		printf("\n\t项目：%s  第%d组\n",SItem.szItemName,iGroup);
		DisplayAthleteListInfo(*SItem.ppAthleteGroup[iGroup - 1]);
		printf("\n\t\t\t\t\t\t\t        \t第%d/%d组\n\n", iGroup, nGroupNumber);
		printf("\t1.上一组\t2.下一组\t3.%s  ：",szThirdChoice);
		int nChoice = GetOption(1, 3);
		if (nChoice == 1 && iGroup > 1)
			iGroup--;
		else if (nChoice == 2 && iGroup < nGroupNumber)
			iGroup++;
		else if(nChoice==3){
			system("cls");
			printf("\t项目：%s  第%d组\n", SItem.szItemName, iGroup);
			DisplayAthleteListInfo(*SItem.ppAthleteGroup[iGroup - 1]);
			break;
		}
	}
	return iGroup;
}

int DisplayGroupingPagination(SSportItem& SItem) {
	if (SItem.GroupNumber == 0) {
		printf("\n该项目无人报名\n");
		system("pause");
		return 0;
	}
	int nGroupNumber = SItem.GroupNumber;
	int iGroup = 1;//第一组
	while (true) {
		system("cls");
		printf("\n\t项目：%s  第%d组\n", SItem.szItemName, iGroup);
		DisplayAthleteListInfo(*SItem.ppAthleteGroup[iGroup - 1]);
		printf("\n\t\t\t\t\t\t\t        \t第%d/%d组\n\n", iGroup, nGroupNumber);
		printf("\t1.上一组\t2.下一组\t3.返回 ：");
		int nChoice = GetOption(1, 3);
		if (nChoice == 1 && iGroup > 1)
			iGroup--;
		else if (nChoice == 2 && iGroup < nGroupNumber)
			iGroup++;
		else if (nChoice == 3) {
			system("cls");
			printf("\t项目：%s  第%d组\n", SItem.szItemName, iGroup);
			DisplayAthleteListInfo(*SItem.ppAthleteGroup[iGroup - 1]);
			break;
		}
	}
	return iGroup;
}

void menu_item() {//项目管理的目录
	printf("\t**********************************************************************************************************\n");
	printf("\t**1.增加项目\t2.删除项目\t3.修改项目\t4.项目报名人员\t|5.返回主菜单|6.上一页\t|7.下一页\t**");
	printf("\n\t**********************************************************************************************************\n");
	printf("\t你的选择是：");
}

void ItemManagement() {//项目管理
	//添加项目
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
		case 1://添加项目
			CreateItem(item);
			AddItem(itemlist, item);
			break;
		case 2: {//删除项目
			char szIDorName[25];
			printf("\n\t请输入需要删除的项目的编号或者名称:");
			GetString(szIDorName, sizeof(szIDorName));
			DeleteItem(itemlist, szIDorName);
			break;
		}//case 2
		case 3: {//修改项目
			char szIDorName[25];
			printf("\n\t请输入需要修改的项目的编号或者名称:");
			GetString(szIDorName, sizeof(szIDorName));
			ModifiItem(itemlist, szIDorName);
			break;
		}//case 3
		case 4: {//查询项目名单
			char szIDorName[20];
			SAthleteList SItemList;
			InitAthleteList(SItemList);

			printf("\n\t请输入需要查询报名名单的项目编号或者名称:");
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
				printf("\t**1.上一页\t2.下一页\t3.返回**\n");
				printf("\t****************************************\n");
				printf("\t你的选择：");
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
