#include"athlete.h"

//初始化运动员表
void InitAthleteList(SAthleteList& SList) {
	SList.pSAthleteList = (SAthlete*)malloc(ATHLETELIST_INIT_SIZE * sizeof(SAthlete));
	if (!SList.pSAthleteList) {
		printf("内存已满");
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
	printf("\n\t姓名：");
	GetString(SAthle.szAthleteName, sizeof(SAthle.szAthleteName));

	printf("\n\t学号：");
	GetString(SAthle.szAthleteID, sizeof(SAthle.szAthleteID));

	int nChoice_Gender = 0;
	printf("\n\t性别：1、女性   2、男性 :");//性别
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
	printf("\t所属单位：");
	nChoice_Academy = GetOption(0, academylist.nListLength - 1);
	SAthle.academy = academylist.pSAcademyList[nChoice_Academy];//参赛单位


	char szAthleteItemIDorName[20];
	SItemList list;
	int nCount = 0;
	InitItemList(list);
	ReadItemListFile(list);
	printf("\n");
	DisplayItemList(list);
	printf("\n\t请输入报名项目数量(1~%d)：",ATHLETE_MAX_ITEM);
	int nNumber_item = 0;
	nNumber_item = GetOption(1, ATHLETE_MAX_ITEM);
	for (int i = 0; i < nNumber_item; i++) {
		printf("\n\t请输入该名运动员报名的项目编号或者名字：");
		GetString(szAthleteItemIDorName, sizeof(szAthleteItemIDorName));
		int nPos = LocateItem(list, szAthleteItemIDorName);
		if (nPos != -1) {//该项目存在
			if (list.pSItemList[nPos].GENDER_itemgender==SAthle.GENDER_athleteGender) {//性别相符才可以报名,报名的同时，在对应项目的报名运动员表中添加上该名运动员
				SAthle.SAthleteItem[nCount++] = list.pSItemList[nPos];
			}
			else {
				if (list.pSItemList[nPos].GENDER_itemgender == GENDER_MALE)
					printf("\t%s限制%s报名\n",list.pSItemList[nPos].szItemName, "男性");
				else
					printf("\t%s限制%s报名\n",list.pSItemList[nPos].szItemName, "女性");
			}
		}
	}
	SAthle.nSItemNumber = nCount;
	printf("\t成功报名%d个项目\n", nCount);//已经完成运动员的信息录入
	for (int i = 0; i < SAthle.nSItemNumber; i++) {
		int nPos_item = LocateItem(list, SAthle.SAthleteItem[i].szItemName);//项目在项目表中的位置
		AddAthlete(*list.pSItemList[nPos_item].pAthleteList, SAthle);//将该名运动员加入到该项目的报名名单中
	}
	WriteItemListFile(list);//将更新后的项目表写入文件中。
	DestroyItemList(list);
}

void DisplayAthleteInfo(const SAthlete& SAthle,int withTitle) {
	if (withTitle == true) {
		printf("\t|%-12s", "学号");
		printf("|%-8s", "姓名");
		printf("%-5s", "|性别");
		printf("%-12s","|书院");
		printf("%-21s", "|项目一");
		printf("%-6s", "|成绩");
		printf("%-21s", "|项目二");
		printf("%-6s", "|成绩");
		printf("%-21s", "|项目三");
		printf("%-6s", "|成绩");
		printf("\n");
		printf("\t____________________________________________________________________________________________________________________\n\t");

	}
	printf("|%-12s", SAthle.szAthleteID);
	printf("|%-8s", SAthle.szAthleteName);
	if (SAthle.GENDER_athleteGender == GENDER_FEMALE)
		printf("%-5s", "|女");
	else
		printf("%-5s", "|男");

	printf("|%-11s", SAthle.academy.szAcademyName);

	for (int i = 0; i < SAthle.nSItemNumber; i++) {
		printf("|%-20s", SAthle.SAthleteItem[i].szItemName);
		if (SAthle.SAthleteItem[i].dResult>0)//比赛的成绩应该不会超过这个范围。
			printf("|%-5.2lf", SAthle.SAthleteItem[i].dResult);
		else {
			printf("|%-5s", "无");
		}
	}
	for (int i = SAthle.nSItemNumber; i < ATHLETE_MAX_ITEM; i++) {
		printf("%-21s", "|未填报");
		printf("|%-5s", "无");
	}

	printf("\n");

}

void DisplayAthleteListInfo(const SAthleteList& SList) {
	printf("\n\n");
	printf("\t%-5s", "|序号");
	printf("|%-12s", "学号");
	printf("|%-8s", "姓名");
	printf("%-5s", "|性别");
	printf("%-12s", "|书院");
	printf("%-21s", "|项目一");
	printf("%-6s", "|成绩");
	printf("%-21s", "|项目二");
	printf("%-6s", "|成绩");
	printf("%-21s", "|项目三");
	printf("%-6s", "|成绩");
	printf("\n");
	for (int i = 0; i < SList.nListLength; i++) {
		printf("\t______________________________________________________________________________________________________________________________\n");
		printf("\t|%-4d", i + 1);
		DisplayAthleteInfo(SList.pSAthleteList[i],false);
	}
}

//分页显示，显示第page页
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
	printf("\t%-5s", "|序号");
	printf("|%-12s", "学号");
	printf("|%-8s", "姓名");
	printf("%-5s", "|性别");
	printf("%-12s", "|书院");
	printf("%-21s", "|项目一");
	printf("%-6s", "|成绩");
	printf("%-21s", "|项目二");
	printf("%-6s", "|成绩");
	printf("%-21s", "|项目三");
	printf("%-6s", "|成绩");
	printf("\n");
	for (int i = (page - 1) * NumberPerPage; i < page * NumberPerPage; i++) {
		if (i>=SList.nListLength)//如果表为空,或者到达最大值
			break;
		printf("\t______________________________________________________________________________________________________________________________\n");
		printf("\t|%-4d", i + 1);
		DisplayAthleteInfo(SList.pSAthleteList[i], false);
	}
	printf("\n\t\t\t\t\t\t\t        \t第%d/%d页\t\t\n", page, maxPage);
}

//分页显示
void DisplayAthleteListPagination(const SAthleteList& SList,int nNumberPerPage) {
	int nPage = 1;
	int nMaxPage = 0;
	int nChoice = 0;
	if (SList.nListLength % nNumberPerPage == 0)
		nMaxPage = SList.nListLength / nNumberPerPage;
	else
		nMaxPage = SList.nListLength / nNumberPerPage + 1;

	while (true) {//分页显示备用运动员表
		system("cls");
		DisplayAthleteListInfo(SList, nPage, nNumberPerPage);
		printf("\n\t**********************************************************\n");
		printf("\t**1.上一页\t2.下一页\t3.转到\t\t4.返回\t**\n");
		printf("\t**********************************************************\n");
		printf("\t你的选择：");
		nChoice = GetOption(1, 4);
		if (nChoice == 1 && nPage > 1)
			nPage--;
		else if (nChoice == 2 && nPage < nMaxPage)
			nPage++;
		else if (nChoice == 3) {
			printf("\n\t转到：");
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
	if (LocateAthlete(SList, SAthle.szAthleteID) != -1 || LocateAthlete(SList, SAthle.szAthleteName) != -1) {//已存在的运动员不能添加
		printf("运动员已存在");
		return -1;
	}

	if (SList.nListLength == SList.nListSize) {
		SAthlete* pNewBase = (SAthlete*)realloc(SList.pSAthleteList, (SList.nListSize + ATHLETELIST_INCREASEMENT) * sizeof(SAthlete));
		if (!pNewBase) {
			printf("内存已满");
			exit(0);
		}
		SList.nListSize += ATHLETELIST_INCREASEMENT;
		SList.pSAthleteList = pNewBase;
	}

	SList.pSAthleteList[SList.nListLength] = SAthle;
	SList.nListLength++;
	return 0;
}

//删除运动员表中的运动员，且不许同步到报名表
int DeleteAthlete(SAthleteList& SList, char szAthleteIDorName[]) {
	int nPos = LocateAthlete(SList, szAthleteIDorName);
	if (nPos == -1) {
		printf("\n该运动员不存在\n");
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
	if (nPos == -1) {//运动员不存在就不用删除了
		printf("\n\t该运动员不存在\n");
		return 0;
	}
	SItemList itemlist;
	InitItemList(itemlist);
	ReadItemListFile(itemlist);

	//同步到报名列表（将报名列表的该运动员删除）(先同步再删除)
	SAthlete* athlete = &SList.pSAthleteList[nPos];
	for (int i = 0; i < athlete->nSItemNumber; i++) {
		SSportItem* item = &athlete->SAthleteItem[i];//取其中一个
		int nPos_item = LocateItem(itemlist, item->szItemID);//在项目表中的位置
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
		printf("\n并无此运动员\n");
		return -1;
	}

	SItemList itemlist;
	InitItemList(itemlist);
	ReadItemListFile(itemlist);

	//同步到报名列表（将报名列表的该运动员删除）
	SAthlete* athlete = &SList.pSAthleteList[nPos_athlete];
	for (int i = 0; i < athlete->nSItemNumber; i++) {
		SSportItem* item = &athlete->SAthleteItem[i];
		int nPos_item = LocateItem(itemlist, item->szItemID);//在项目表中的位置
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
	int nPosition = LocateAthleteItem(SAthle, szItemIDorName);//找到这个项目在运动员报名项目数组中的位置
	if (nPosition != -1) {
		for (int i = nPosition; i < SAthle.nSItemNumber - 1; i++) {//将后面的移到前面去
			SAthle.SAthleteItem[i] = SAthle.SAthleteItem[i + 1];
		}
		SAthle.nSItemNumber--;

		SItemList itemlist;//项目表中的相应项目的运动员表要做改动，将这名运动员从表中删除
		InitItemList(itemlist);
		ReadItemListFile(itemlist);
		int nPos_item = LocateItem(itemlist, szItemIDorName);//在项目表中找到该项目
		DeleteAthleteSync(*itemlist.pSItemList[nPos_item].pAthleteList, SAthle.szAthleteID);//在该项目报名表中删除该名运动员。
		WriteItemListFile(itemlist);
		DestroyItemList(itemlist);

		return 0;
	}
	else//该运动员没有报名这个项目
		return -1;
}

int AddAthleteItem(SAthlete& SAthle, SSportItem SItem){
	SItemList itemlist;
	InitItemList(itemlist);
	ReadItemListFile(itemlist);
	int nPos_item = LocateItem(itemlist, SItem.szItemID);//找到该项目在项目表中为位置，
	if (nPos_item == -1) {//该项目需要在项目表中才可以写入
		printf("%s该项目不存在",SItem.szItemName);
		DestroyItemList(itemlist);
		return -1;
	} 
	if (SAthle.nSItemNumber >= ATHLETE_MAX_ITEM||LocateAthleteItem(SAthle,SItem.szItemID)!=-1) {//如果项目已达上限，或者已经报名该项目就不给报了
		return -1;
	}
	SAthle.SAthleteItem[SAthle.nSItemNumber] = SItem;
	SAthle.nSItemNumber++;
	
	AddAthlete(*itemlist.pSItemList[nPos_item].pAthleteList, SAthle);//将该名运动员加入到项目报名表中
	WriteItemListFile(itemlist);//将跟新后的项目表写入文件中
	DestroyItemList(itemlist);
	return 0;
}

int ReplaceAthleteItem(SAthlete& SAthle, SSportItem SItem, int n) {//用SItem代替SAthle.SAthleteItem[n]
	SItemList itemlist;//项目表中的相应项目的运动员表要做改动，将这名运动员从表中删除
	InitItemList(itemlist);
	ReadItemListFile(itemlist);
	int nPos_item = LocateItem(itemlist,SAthle.SAthleteItem[n].szItemName);//在项目表中找到该项目
	DeleteAthleteSync(*itemlist.pSItemList[nPos_item].pAthleteList, SAthle.szAthleteID);//在该项目报名表中删除该名运动员。
	SAthle.SAthleteItem[n] = SItem;
	nPos_item = LocateItem(itemlist, SItem.szItemID);//找到该项目在项目表中为位置，
	if (nPos_item == -1) {//该项目需要在项目表中才可以写入
		printf("该项目不存在");
		DestroyItemList(itemlist);
		return -1;
	}
	AddAthlete(*itemlist.pSItemList[nPos_item].pAthleteList, SAthle);//将该名运动员加入到项目报名表中
	WriteItemListFile(itemlist);//将跟新后的项目表写入文件中
	DestroyItemList(itemlist);
	return 0;
}

void DisplayAthleteItem(const SAthlete& SAthle) {
	printf("\n\t|编号      |名称                |类别\t|成绩\t|\n");
	for (int i = 0; i < SAthle.nSItemNumber; i++) {
		printf("\t|%-10s", SAthle.SAthleteItem[i].szItemID);
		printf("|%-20s", SAthle.SAthleteItem[i].szItemName);

		if (SAthle.SAthleteItem[i].SPORTTYPE_itemtype == SPORTTYPE_TRACK)
			printf("|径赛\t");
		else if (SAthle.SAthleteItem[i].SPORTTYPE_itemtype == SPORTTYPE_FIELD)
			printf("|田赛\t");

		if (SAthle.SAthleteItem[i].dResult<=0) {
			printf("|%2s\t|", "无");
		}
		else {
			printf("|%.2lf\t|", SAthle.SAthleteItem[i].dResult);
		}
		printf("\n");
	}
}

void AthleteSync(SAthlete& athlete) {//将更新后的运动员信息同步到报名表中
	SItemList itemlist;
	InitItemList(itemlist);
	ReadItemListFile(itemlist);
	for (int i = 0; i < athlete.nSItemNumber;i++) {
		int nPos_item = LocateItem(itemlist, athlete.SAthleteItem[i].szItemID);//运动员报名项目在项目表中得位置
		if (nPos_item == -1) {
			nPos_item = LocateItem(itemlist, athlete.SAthleteItem[i].szItemName);
		}
		int nPos_athlete = LocateAthlete(*itemlist.pSItemList[nPos_item].pAthleteList, athlete.szAthleteID);//找到运动员在项目报名表中得位置
		if (nPos_athlete == -1) {
			nPos_athlete = LocateAthlete(*itemlist.pSItemList[nPos_item].pAthleteList, athlete.szAthleteName);
		}
		itemlist.pSItemList[nPos_item].pAthleteList->pSAthleteList[nPos_athlete] = athlete;//将对应位置的运动员替换掉。
	}
	WriteItemListFile(itemlist);//将更新后的项目表写入文件中
	DestroyItemList(itemlist);
}

int ModifiAthlete(SAthleteList& SList, char szAthleteIDorName[]) {
	int nPos = LocateAthlete(SList, szAthleteIDorName);//nPos时
	if (nPos == -1) {
		printf("\n\t该运动员不存在\n");
		return -1;
	}

	system("cls");
	DisplayAthleteInfo(SList.pSAthleteList[nPos],true);

	SAthlete* athlete = &SList.pSAthleteList[nPos];//athlete指向需要修改的运动员。
	int nChoice = 0;

	system("cls");
	DisplayAthleteInfo(*athlete, true);

	printf("\n\t*********************************************************************************\n");
	printf("\t**1.姓名      |2.学号      |3.性别      |4.所属书院  |5.所报项目  |6.取消      **");
	printf("\n\t*********************************************************************************\n");
	printf("\t你的选择是：");

	nChoice = GetOption(1, 6);
	switch (nChoice)
	{
	case 1: {
		char szTemp[20];
		printf("\n\t新的名称:");
		GetString(szTemp, sizeof(szTemp));
		if (LocateAthlete(SList, szTemp) == -1) {
			strcpy_s(athlete->szAthleteName, sizeof(athlete->szAthleteName), szTemp);
		}
		else
			printf("该名称已存在");
		break;
	}
	case 2: {
		char szTemp[20];
		printf("\n\t新的学号:");
		GetString(szTemp, sizeof(szTemp));
		if (LocateAthlete(SList, szTemp) == -1) {
			strcpy_s(athlete->szAthleteID, sizeof(athlete->szAthleteID), szTemp);
		}
		else
			printf("该学号已存在");
		break;
	}
	case 3: {//这里还需要将所有这个人报名的项目审核一遍，将所有的项目变成两外一个性别的比赛，如果没有则提示，让用户选择是否删除。
		int nChoice_Gender = 0;
		printf("\n\t注意:如果报名后修改性别，可能会导致有的比赛无法参加。\n");
		printf("\n\t性别：\t1.女性  \t2.男性\n");
		printf("\n\t你的选择：");
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
			strcpy_s(szTemp, sizeof(szTemp), athlete->SAthleteItem[i].szItemName);//获取项目名
			if (originalGender != gender) {//性别不同才需要修改
				if (originalGender == GENDER_FEMALE) {//得到相反性别的项目名，例如男子跑步（100米） 得到的就是女子跑步（100米）
					int index = Index_BF(szTemp, "女");
					szTemp[index] = "男"[0];
					szTemp[index + 1] = "男"[1];
				}
				else {
					int index = Index_BF(szTemp, "男");
					szTemp[index] = "女"[0];
					szTemp[index + 1] = "女"[1];
				}
			}
			else//如果性别没有改变，就直接退出函数。。
				return 0;

			int nPos_item = LocateItem(itemlist, szTemp);//转性之后的项目在项目表中的位置
			if (nPos_item == -1) {//不存在该项目
				printf("\n%s不存在，因此%s已删除\n", szTemp, athlete->SAthleteItem[i].szItemName);
				DeleteAthleteItem(*athlete, athlete->SAthleteItem[i].szItemName);//删除该项目
			}
			else {//该项目存在
				printf("\n是否将%s 转报称成 %s", athlete->SAthleteItem[i].szItemName, szTemp);
				printf("\t1.是   2.否(删除项目)  :");
				int nYesOrNo = GetOption(1, 2);
				if (nYesOrNo == 1) {
					ReplaceAthleteItem(*athlete, itemlist.pSItemList[nPos_item], i);//用新的项目代替掉就的项目
				}
				else {
					DeleteAthleteItem(*athlete, athlete->SAthleteItem[i].szItemName);
					i--;
				}
			}//else 项目存在
		}//for
		break;
	}
	case 4: {
		int nChoice_Academy = -1;
		SAcademyList academyList;
		InitAcademyList(academyList);
		ReadAcademyListFile(academyList);
		DisplayAcademyList(academyList);
		printf("新的所属单位:");
		nChoice_Academy = GetOption(0, academyList.nListLength - 1);
		athlete->academy = academyList.pSAcademyList[nChoice_Academy];
		break;
	}
	case 5: {
		printf("\n\n");
		DisplayAthleteItem(SList.pSAthleteList[nPos]);
		printf("\n\t1.删除项目\n");
		printf("\n\t2.添加项目\n");
		int nChoice_Item = 0;
		nChoice_Item = GetOption(1, 2);
		switch (nChoice_Item)
		{
		case 1: {
			printf("\n\n\t请输入你需要删除的项目编号或者名称：");
			char szIDorName[25];
			GetString(szIDorName, sizeof(szIDorName));
			if (DeleteAthleteItem(*athlete, szIDorName) == -1) {
				printf("\n该名运动员并没有报此项目\n");
			}
			if (athlete->nSItemNumber == 0) {//如果该名运动员没有报名项目了，就将该运动员从运动员表中删除。
				DeleteAthleteSync(SList, nPos);
			}
			break;
		}
		case 2: {
			printf("\n\t所有项目如下:\n");
			SItemList list;
			InitItemList(list);
			ReadItemListFile(list);
			DisplayItemList(list);
			printf("\n\t请输入你需要添加的项目或者名称：");
			char szIDorName[25];
			GetString(szIDorName, sizeof(szIDorName));
			int nPos_temp = LocateItem(list, szIDorName);
			if (nPos_temp == -1) {//项目不存在，则退出函数
				printf("\n\t该项目不存在\n");
				DestroyItemList(list);
				return -1;
			}
			if (AddAthleteItem(*athlete, list.pSItemList[nPos_temp]) == -1) {//添加项目
				printf("\n\t无需重复报名项目\n");
			}
			DestroyItemList(list);
			break;
		}//case 2
		}//switch (nChoice_Item)
	}//case 5
	case 6://取消
		break;
	}//switch(nChoice)

	if (nChoice == 1 || nChoice == 2 || nChoice == 4) {//更新数据
		AthleteSync(*athlete);
	}
	system("cls");
	DisplayAthleteInfo(*athlete, true);
	printf("\n修改成功!\n");
	return 0;
}

int WriteAthleteListFile(SAthleteList& SList) {
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

int ReadAthleteListFile(SAthleteList& SList) {
	ClearAthleteList(SList);
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


void menu_athlete() {
	printf("\n\t********************************************************************************************************************************\n");
	printf("\t**1.增加运动员  |2.批量增加    |3.删除运动员  |4.修改运动员  |5.查询    |6.返回主菜单  |7.上一页    |8.下一页    |9.转到页    **");
	printf("\n\t********************************************************************************************************************************\n");
	printf("\t你的选择是：");
}

//业务逻辑
void AthleteManagement() {
	//运动员相关
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
			printf("\n\t请输入运动员信息\n");
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
			printf("\n\t请输入要删除的运动员的名字或者学号:");
			GetString(szIDorName, sizeof(szIDorName));
			DeleteAthleteSync(athletelist, szIDorName);
			WriteAthleteListFile(athletelist);
			break;
		}//case 3
		case 4: {
			char szIDorName[20];
			printf("\n\t请输入需要修改的运动员你的名字或者学号:");
			GetString(szIDorName, sizeof(szIDorName));
			ModifiAthlete(athletelist, szIDorName);
			WriteAthleteListFile(athletelist);
			break;
		}//case 4
		case 5: {
			printf("\n\n\t查询的依据：\n");
			printf("\t**********************************************************************************\n");
			printf("\t**1.参赛单位\t|2.学号\t\t|3.姓名\t\t|4.项目\t\t|5.返回\t\t**");
			printf("\n\t**********************************************************************************\n");
			printf("\t你的选择是：");

			int nChoice_inquire = 0;
			nChoice_inquire = GetOption(1,5);
			switch (nChoice_inquire)
			{
			case 1: {//根据参赛单位查询
				system("cls");
				
				SAcademyList academylist;
				InitAcademyList(academylist);
				ReadAcademyListFile(academylist);
				DisplayAcademyList(academylist);
				printf("\n\t需要查询的参赛单位名单：");
				int nChoice_academy = 0;
				nChoice_academy = GetOption(0, academylist.nListLength - 1);
				SAthleteList tmpAthletelist;//备用表，用来存放在某个参赛单位的运动员
				InitAthleteList(tmpAthletelist);
				for (int i = 0; i < athletelist.nListLength; i++) {
					SAthlete* athlete =&athletelist.pSAthleteList[i];
					if (strcmp(athlete->academy.szAcademyName, academylist.pSAcademyList[nChoice_academy].szAcademyName) == 0) {//如果这名运动员是这个参赛单位的，就显示出来u
						AddAthlete(tmpAthletelist, *athlete);
					}
				}
				DisplayAthleteListPagination(tmpAthletelist, 10);
				DestroyAthleteList(tmpAthletelist);
				DestroyAcademyList(academylist);
				break;
			}//case 1
			case 2: {//根据学号查询
				printf("\n\n\t请输入学号：");
				char szAthleteID[20];
				GetString(szAthleteID, sizeof(szAthleteID));
				int nPos_ID = LocateAthlete(athletelist, szAthleteID);
				if (nPos_ID != -1) {
					DisplayAthleteInfo(athletelist.pSAthleteList[nPos_ID], true);
				}
				else {
					printf("\n无此人！\n");
				}
				break;
			}//case 2
			case 3: {//根据姓名查询
				printf("\n\n\t请输入姓名：");
				char szAthleteName[20];
				GetString(szAthleteName, sizeof(szAthleteName));
				int nPos_ID = LocateAthlete(athletelist, szAthleteName);
				if (nPos_ID != -1) {
					DisplayAthleteInfo(athletelist.pSAthleteList[nPos_ID], true);
				}
				else {
					printf("\n无此人！\n");
				}
				break;
			}//case 3
			case 4: {//根据项目查询
				system("cls");
				SItemList itemlist;//临时项目表
				InitItemList(itemlist);
				ReadItemListFile(itemlist);
				DisplayItemList(itemlist);
				printf("\n\n\t需要查询的项目是：");
				char szItemIDorName[25];
				GetString(szItemIDorName,sizeof(szItemIDorName));
				int nPos_item = LocateItem(itemlist, szItemIDorName);
				if (nPos_item == -1) {//找不到该项目
					printf("\t此项目不存在");
					system("pause");
				}
				else {//找到该项目
					system("cls");
					SAthleteList tmpAthletelist;//备用运动员表，用来存放报名了该项目的运动员
					InitAthleteList(tmpAthletelist);
					SSportItem* item = &itemlist.pSItemList[nPos_item];
					for (int i = 0; i < athletelist.nListLength; i++) {
						if (LocateAthleteItem(athletelist.pSAthleteList[i], item->szItemID) != -1) //该名运动员报了该项目
							AddAthlete(tmpAthletelist, athletelist.pSAthleteList[i]);//将这个运动员加入备用运动员表中
					}//for
					DisplayAthleteListPagination(tmpAthletelist, 8);
					DestroyAthleteList(tmpAthletelist);
				}//else
				DestroyItemList(itemlist);//释放掉临时项目表
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
			printf("\n\t转到:");
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