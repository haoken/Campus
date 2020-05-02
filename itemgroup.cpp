#include"itemgroup.h"

#define TRACKNUMBER 8//赛道

void DisplayItemGroup(SItemGroup& SGroup) {
	printf("\n项目信息\n");
	printf("\t|%-10s", "项目编号");
	printf("|%-20s","项目名称");
	printf("|项目类别\t\n");
	printf("\t|%-10s", SGroup.szItemID);
	printf("|%-20s", SGroup.szItemName);
	if (SGroup.SPORTTYPE_SportType == SPORTTYPE_TRACK)
		printf("|径赛\t");
	else if (SGroup.SPORTTYPE_SportType == SPORTTYPE_FIELD)
		printf("|田赛\t");
	if (SGroup.nMaleGroupNumber != 0) {
		printf("\n\n\t男子分组情况\n");
		for (int i = 1; i <= SGroup.nMaleGroupNumber; i++) {
			printf("\t第%d组", i);
			DisplayAthleteListInfo(SGroup.SMaleGroups[i - 1]);
			printf("\n\n");
		}
	}
	if (SGroup.nFemaleGroupNumber != 0) {
		printf("\n\n\t女子组分组情况\n");
		for (int i = 1; i <= SGroup.nFemaleGroupNumber; i++) {
			printf("\t第%d组", i);
			DisplayAthleteListInfo(SGroup.SFemaleGroups[i - 1]);
			printf("\n\n");
		}
	}
}

void ConnectItemList(SGroupList& SGroups, SItemList& SItems) {
	SGroups.nListSize = SItems.nListSize;
	SGroups.nListLength = SItems.nListLength;
	SGroups.pSItemGroupList = (SItemGroup*)malloc(SGroups.nListSize * sizeof(SItemGroup));
	if (!SGroups.pSItemGroupList) {
		printf("内存已满");
		exit(0);
	}

	int nLength = SGroups.nListLength;
	SItemGroup Group;
	for (int i = 0; i < nLength; i++) {
		strcpy_s(Group.szItemName,20, SItems.pSItemList[i].szItemName);//项目名称
		strcpy_s(Group.szItemID, 20, SItems.pSItemList[i].szItemID);//项目编号
		Group.SPORTTYPE_SportType = SItems.pSItemList[i].SPORTYPE_itemtype;//项目类别
		Group.nFemaleGroupNumber = 0;
		Group.nMaleGroupNumber = 0;
		if (SGroups.nListSize != 0) {
			SGroups.pSItemGroupList[i] = Group;//前面限制，nListSize!=0
		}
	}
}

void ConnectAthleteList(SGroupList& SGroups, SAthleteList& SAthletes) {
	SAthleteList SItemAthleteList;//某个项目所有名单
	SAthleteList SFemaleAthleteList;//报名某个项目的女子名单
	SAthleteList SMaleAthleteList;//报名某个项目的男子名单

	for (int i = 0; i < SGroups.nListLength; i++) {
		InitAthleteList(SItemAthleteList);
		InitAthleteList(SFemaleAthleteList);
		InitAthleteList(SMaleAthleteList);

		CreateItemAthleteList(SAthletes, SItemAthleteList, SGroups.pSItemGroupList[i].szItemID);
		CreateFemaleAthleteList(SItemAthleteList, SFemaleAthleteList);
		CreateMaleAthleteList(SItemAthleteList, SMaleAthleteList);

		InitAthleteList(SGroups.pSItemGroupList[i].SFemaleAthleteList);
		InitAthleteList(SGroups.pSItemGroupList[i].SMaleAthleteList);
		for (int j = 0; j < SFemaleAthleteList.nListLength; j++) {
			AddAthlete(SGroups.pSItemGroupList[i].SFemaleAthleteList, SFemaleAthleteList.pSAthleteList[j]);
		}
		for (int j = 0; j < SMaleAthleteList.nListLength; j++) {
			AddAthlete(SGroups.pSItemGroupList[i].SMaleAthleteList, SMaleAthleteList.pSAthleteList[j]);
		}
		if (SGroups.pSItemGroupList[i].SPORTTYPE_SportType == SPORTTYPE_TRACK) {//如果这个项目是径赛,根据人数分组
			SGroups.pSItemGroupList[i].nFemaleGroupNumber = ceil(double(SFemaleAthleteList.nListLength) / TRACKNUMBER);//确定分组数量
			SGroups.pSItemGroupList[i].nMaleGroupNumber = ceil(double(SMaleAthleteList.nListLength) / TRACKNUMBER);
			GroupingAthlete(SFemaleAthleteList, SMaleAthleteList, SGroups.pSItemGroupList[i]);//径赛分组
		}
		else if (SGroups.pSItemGroupList[i].SPORTTYPE_SportType == SPORTTYPE_FIELD) {//如果这个项目是田赛，直接就一组
			if (SGroups.pSItemGroupList[i].SFemaleAthleteList.nListLength == 0)
				SGroups.pSItemGroupList[i].nFemaleGroupNumber = 0;
			else
				SGroups.pSItemGroupList[i].nFemaleGroupNumber = 1;

			if (SGroups.pSItemGroupList[i].SMaleAthleteList.nListLength == 0)
				SGroups.pSItemGroupList[i].nMaleGroupNumber = 0;
			else
				SGroups.pSItemGroupList[i].nMaleGroupNumber = 1;

			InitAthleteList(SGroups.pSItemGroupList[i].SFemaleGroups[0]);
			InitAthleteList(SGroups.pSItemGroupList[i].SMaleGroups[0]);
			for (int j = 0; j < SFemaleAthleteList.nListLength; j++) {//将所有的女性运动员放到一个组中
				AddAthlete(SGroups.pSItemGroupList[i].SFemaleGroups[0], SFemaleAthleteList.pSAthleteList[j]);
			}
			for (int j = 0; j < SMaleAthleteList.nListLength; j++) {//将所有的男性运动员放到一个组中
				AddAthlete(SGroups.pSItemGroupList[i].SMaleGroups[0], SMaleAthleteList.pSAthleteList[j]);
			}

		}
		else {//这种情况是没有定义类别，这时候就出错了
			printf("%s 项目出错",SGroups.pSItemGroupList[i].szItemName);
			exit(0);
		}

		DestroyAthleteList(SFemaleAthleteList);
		DestroyAthleteList(SMaleAthleteList);
		DestroyAthleteList(SItemAthleteList);
	}
}

 void GroupingAthlete(SAthleteList& SFemaleAthleteList,SAthleteList& SMaleAthleteList,SItemGroup& ItemGroup) {
	
	int GroupNumber_Female = ItemGroup.nFemaleGroupNumber;
	int GroupNumber_Male = ItemGroup.nMaleGroupNumber;

	if (GroupNumber_Female == 0 && GroupNumber_Male == 0)//如果该项目无人报名，则直接返回跳出函数
		return;

	int nOffset = -1;
	int nAcademy[ACADEMYNUMBER] = {0};//第一个元素表示现有运动员个数

	SAthleteList STempList;
	InitAthleteList(STempList);

	for (int i = 0; i < GroupNumber_Female; i++) {//先初始化几个分组的运动员名单
		InitAthleteList(ItemGroup.SFemaleGroups[i]);
	}
	for (int i = 0; i < GroupNumber_Male; i++) {
		InitAthleteList(ItemGroup.SMaleGroups[i]);
	}

	if (GroupNumber_Female != 0) {
		////处理女子分组
		for (int i = 0; i < SFemaleAthleteList.nListLength; i++) {//计数
			int nIndex = (int)SFemaleAthleteList.pSAthleteList[i].academy;
			nAcademy[nIndex + nOffset]++;
			AddAthlete(STempList, SFemaleAthleteList.pSAthleteList[i]);//STempList是SFemaleAthleteList的副本
		}

		int nDiv = SFemaleAthleteList.nListLength / GroupNumber_Female;
		int nMod = SFemaleAthleteList.nListLength % GroupNumber_Female;
		int i = 0;//女子组的第i组
		int nIndex = 0;

		while (STempList.nListLength > 0 && i < GroupNumber_Female) {
			while (nAcademy[nIndex] == 0) {//选择某个书院的人，轮着选
				if (nIndex == ACADEMYNUMBER - 1)
					nIndex = 0;
				else
					nIndex++;
			}
			nAcademy[nIndex]--;
			int nAcademyIndex = nIndex - nOffset;//要将序号为nAcademyIndex的书院的运动员进行分组

			if (nIndex == ACADEMYNUMBER - 1)
				nIndex = 0;
			else
				nIndex++;

			int nPos = LocateAthleteAcademy(STempList, nAcademyIndex);//上面的循环确保了不会出现找不到的状况
			AddAthlete(ItemGroup.SFemaleGroups[i], STempList.pSAthleteList[nPos]);
			DeleteAthlete(STempList, STempList.pSAthleteList[nPos].szAthleteID);//把这个运动员删除掉
			if (i < nMod && ItemGroup.SFemaleGroups[i].nListLength == nDiv + 1) {
				i++;
			}
			else if (i < GroupNumber_Female && i >= nMod && ItemGroup.SFemaleGroups[i].nListLength == nDiv) {
				i++;
			}//else
		}//while()
	}//if(GroupNumber_Female!=0)
	
	if (GroupNumber_Male != 0) {
		////处理男子分组
		for (int i = 0; i < ACADEMYNUMBER; i++) {//确保数组全部元素为0
			nAcademy[i] = 0;
		}
		for (int i = 0; i < SMaleAthleteList.nListLength; i++) {
			int nIndex = (int)SMaleAthleteList.pSAthleteList[i].academy;
			nAcademy[nIndex + nOffset]++;
			AddAthlete(STempList, SMaleAthleteList.pSAthleteList[i]);
		}
		int nDiv = SMaleAthleteList.nListLength / GroupNumber_Male;
		int nMod = SMaleAthleteList.nListLength % GroupNumber_Male;
		int i = 0;
		int nIndex = 0;
		while (STempList.nListLength > 0 && i < GroupNumber_Male) {
			while (nAcademy[nIndex] == 0) {
				if (nIndex == ACADEMYNUMBER)
					nIndex = 0;
				else
					nIndex++;
			}
			nAcademy[nIndex]--;
			int nAcaDemyIndex = nIndex - nOffset;

			if (nIndex == ACADEMYNUMBER - 1)
				nIndex = 0;
			else
				nIndex++;

			int nPos = LocateAthleteAcademy(STempList, nAcaDemyIndex);
			AddAthlete(ItemGroup.SMaleGroups[i], STempList.pSAthleteList[nPos]);
			DeleteAthlete(STempList, STempList.pSAthleteList[nPos].szAthleteID);
			if (i < nMod && ItemGroup.SMaleGroups[i].nListLength == nDiv + 1) {
				i++;
			}
			else if (i < GroupNumber_Male && i >= nMod && ItemGroup.SMaleGroups[i].nListLength == nDiv) {
				i++;
			}//else if
		}//while
	}//if(GroupNumber_Male!=0)
	DestroyAthleteList(STempList);
}

void DestroyItemGroupList(SGroupList& SList) {
	free(SList.pSItemGroupList);
	SList.nListLength = 0;
	SList.nListSize = 0;
}

void InputResult(char szItemIDorName[]) {
	SItemList itemlist;
	InitItemList(itemlist);
	ReadItemListFile(itemlist);
	SAthleteList athletelist;
	InitAthleteList(athletelist);
	ReadAthleteListFile(athletelist);
	SGroupList grouplist;
	ConnectItemList(grouplist, itemlist);
	ConnectAthleteList(grouplist, athletelist);
	SItemGroup *itemgroup;
	int nPosofItem = LocateItem(itemlist, szItemIDorName);
	if (nPosofItem == -1) {
		printf("无此项目\n");
		return;
	}
	else {//有此项目
		itemgroup = &grouplist.pSItemGroupList[nPosofItem];
		SAthleteList* pGroupathletelist;
		DisplayItemGroup(*itemgroup);
		printf("\n你需要输入成绩的组是：\n");
		printf("1.男子组\t2.女子组：");
		int nChoice_gender = 1;
		do {
			scanf_s("%d", &nChoice_gender);
			if (nChoice_gender < 1 || nChoice_gender>2)
				printf("选项错误，请重新输入：");
		} while (nChoice_gender < 1 || nChoice_gender>2);

		if (itemgroup->nFemaleGroupNumber == 0 && nChoice_gender == 2) {//该项目女子组没人！退出不让输成绩
			printf("该项目无人报名\n");
			return;
		}
		if (itemgroup->nMaleGroupNumber == 0 && nChoice_gender == 1) {//该项目男子组没人！退出不让输入成绩
			printf("该项目无人报名\n");
			return;
		}

		int nGroup_number = 1;
		if (itemgroup->SPORTTYPE_SportType == SPORTTYPE_TRACK && nChoice_gender==1) {//男子径赛组
			do {
				printf("你需要的输入的组数：");
				scanf_s("%d", &nGroup_number);
				if (nGroup_number<1 || nGroup_number>itemgroup->nMaleGroupNumber)
					printf("选项错误，请重新输入：");
			} while (nGroup_number<1 || nGroup_number>itemgroup->nMaleGroupNumber);			
		}
		else if (itemgroup->SPORTTYPE_SportType == SPORTTYPE_TRACK && nChoice_gender == 2) {//女子径赛组
			do {
				printf("你需要的输入的组数：");
				scanf_s("%d", &nGroup_number);
				if (nGroup_number<1 || nGroup_number>itemgroup->nFemaleGroupNumber)
					printf("选项错误，请重新输入：");
			} while (nGroup_number<1 || nGroup_number>itemgroup->nFemaleGroupNumber);
		}

		system("cls");
		if (nChoice_gender == 1)
			pGroupathletelist = &itemgroup->SMaleGroups[nGroup_number - 1];
		else
			pGroupathletelist = &itemgroup->SFemaleGroups[nGroup_number - 1];
		DisplayAthleteListInfo(*pGroupathletelist);

		printf("\n\n\n请按一下顺序输入改组运动员在 \"%s\" 中的成绩：\n", itemgroup->szItemName);
		printf("|%-15s","学号");
		printf("|%-20s","姓名");
		if (itemgroup->SPORTTYPE_SportType == SPORTTYPE_FIELD)
			printf("|%-10s", "成绩(/m)");
		else
			printf("|%-10s", "成绩(/s)");

		for (int i = 0; i < pGroupathletelist->nListLength; i++) {//直接写入运动员表中
			printf("\n\n|%-15s", pGroupathletelist->pSAthleteList[i].szAthleteID);
			printf("|%-20s|", pGroupathletelist->pSAthleteList[i].szAthleteName);
			int nPosAthlete = LocateAthlete(athletelist, pGroupathletelist->pSAthleteList[i].szAthleteID);//该名运动员在运动员表中的位置
			int nPosAthleteItem = LocateAthleteItem(athletelist.pSAthleteList[nPosAthlete], itemgroup->szItemID);//该项目在该运动员报名的项目中的位置
			double dResult;
			while (!(cin >> dResult)) {
				cin.clear();
				while (cin.get() != '\n')
					continue;
				printf("%38s", "请重新输入:");
			}
			athletelist.pSAthleteList[nPosAthlete].SAthleteItem[nPosAthleteItem].dResult = dResult;//成绩输入到athletelist列表中
			pGroupathletelist->pSAthleteList[i].SAthleteItem[nPosAthleteItem].dResult = dResult;//成绩输入到分组名单中
		}


		while (true) {//将刚刚输入的所有的成绩显示出来，让用户确定是否需要修改，或者保存文件
			system("cls");
			printf("\t|%-15s", "学号");
			printf("|%-10s", "姓名");
			printf("|%-20s", "项目名");
			printf("|%-10s\n", "成绩");
			for (int i = 0; i < pGroupathletelist->nListLength; i++) {
				printf("\t|%-15s", pGroupathletelist->pSAthleteList[i].szAthleteID);
				printf("|%-10s", pGroupathletelist->pSAthleteList[i].szAthleteName);
				printf("|%-20s", itemgroup->szItemName);
				int nPosAthlete = LocateAthlete(athletelist, pGroupathletelist->pSAthleteList[i].szAthleteID);//该名运动员在运动员表中的位置
				int nPosAthleteItem = LocateAthleteItem(athletelist.pSAthleteList[nPosAthlete], itemgroup->szItemID);//该项目在该运动员报名的项目中的位置
				printf("|%.2lf", pGroupathletelist->pSAthleteList[i].SAthleteItem[nPosAthleteItem].dResult);//输出成绩
				printf("\n\n");
			}
			printf("\n\n1.保存\n");
			printf("2.修改\n");
			printf("你的选择：");
			int nChoice = 0;
			while (!(cin >> nChoice)) {
				cin.clear();
				while (cin.get() != '\n')
					continue;
				printf("请重新输入");
			}
			if (nChoice == 1) {
				WriteAthleteListFile(athletelist);//将运动员表写入文件中。
				printf("\n保存成功！\n");
				break;
			}
			else {
				printf("请输入需要修改成绩的ID:");
				char szAthleteID[20];
				scanf_s("%s", szAthleteID, 20);
				int i = LocateAthlete(*pGroupathletelist, szAthleteID);
				int nPosAthleteItem = LocateAthleteItem(pGroupathletelist->pSAthleteList[i], itemgroup->szItemID);
				printf("\n\n\t|%-15s", "学号");
				printf("|%-10s", "姓名");
				printf("|%-20s", "项目名");
				printf("|%-10s\n", "成绩");
				printf("\t|%-15s", pGroupathletelist->pSAthleteList[i].szAthleteID);
				printf("|%-10s", pGroupathletelist->pSAthleteList[i].szAthleteName);
				printf("|%-20s", itemgroup->szItemName);
				printf("|%.2lf", pGroupathletelist->pSAthleteList[i].SAthleteItem[nPosAthleteItem].dResult);//输出成绩
				printf("\n%57s", "请输入修改后的成绩:");
				double dResult = 0;
				while (!(cin >> dResult)) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					printf("%57s", "请重新输入:");
				}
				pGroupathletelist->pSAthleteList[i].SAthleteItem[nPosAthleteItem].dResult = dResult;
				int nPosAthlete = LocateAthlete(athletelist, szAthleteID);
				athletelist.pSAthleteList[nPosAthlete].SAthleteItem[nPosAthleteItem].dResult = dResult;//将athletelist中的的成绩修改。
			}
		}//while(true)

	}//else(nPosition!=1);
	DestroyItemList(itemlist);
	DestroyAthleteList(athletelist);
	DestroyItemGroupList(grouplist);
}

void AcademyGroup(SAthleteList& athletelist, int nAcademy) {

	if (nAcademy < 1 || nAcademy>9) {
		printf("\n无此参赛单位\n");
		return;
	}

	SAthleteList allAthleteList;
	InitAthleteList(allAthleteList);
	ReadAthleteListFile(allAthleteList);
	for (int i = 0; i < allAthleteList.nListLength; i++) {
		if (allAthleteList.pSAthleteList[i].academy == nAcademy) {
			AddAthlete(athletelist, allAthleteList.pSAthleteList[i]);
		}
	}
	DestroyAthleteList(allAthleteList);
}

int FinishInputResult(SItemGroup& group) {
	int is_finish;
	bool female_finish = true;
	bool male_finish = true;

	for (int i = 0; i < group.SFemaleAthleteList.nListLength; i++) {
		int Pos_item = LocateAthleteItem(group.SFemaleAthleteList.pSAthleteList[i],group.szItemID);
		double dResult = group.SFemaleAthleteList.pSAthleteList[i].SAthleteItem[Pos_item].dResult;
		if (dResult < 0 || dResult>1000)
			female_finish = false;
	}

	for (int i = 0; i < group.SMaleAthleteList.nListLength; i++) {
		int Pos_item = LocateAthleteItem(group.SMaleAthleteList.pSAthleteList[i], group.szItemID);
		double dResult = group.SMaleAthleteList.pSAthleteList[i].SAthleteItem[Pos_item].dResult;
		if (dResult < 0 || dResult>1000)
			male_finish = false;
	}

	if (female_finish && male_finish)
		is_finish = 1;
	else if (female_finish == true && male_finish == false)
		is_finish = -1;
	else if (female_finish == false && male_finish == true)
		is_finish = 0;
	else
		is_finish = -2;

	return is_finish;
}

int RankItemGroupAthleteList(SItemGroup& group) {
	int finish_input = FinishInputResult(group);
	if (finish_input == 1) {//所有运动员成绩输入完成
		//完成女子组的排名
		SAthleteList femaleList;
		InitAthleteList(femaleList);
		while (group.SFemaleAthleteList.nListLength > 0) {//将成绩从高到低排序
			double dResult = 0;
			int nPos_athlete = 0;
  			for (int i = 0; i < group.SFemaleAthleteList.nListLength; i++) {//找到成绩最大的那个运动员位置
				int nPos_item = LocateAthleteItem(group.SFemaleAthleteList.pSAthleteList[i], group.szItemID);
				if (group.SFemaleAthleteList.pSAthleteList[i].SAthleteItem[nPos_item].dResult >= dResult) {
					nPos_athlete = i;
					dResult = group.SFemaleAthleteList.pSAthleteList[i].SAthleteItem[nPos_item].dResult;
				}
			}//for
			AddAthlete(femaleList, group.SFemaleAthleteList.pSAthleteList[nPos_athlete]);
			DeleteAthlete(group.SFemaleAthleteList, nPos_athlete);
		}//while
		if (group.SPORTTYPE_SportType == SPORTTYPE_FIELD) {//田赛成绩从高到低排序
			for (int i = 0; i < femaleList.nListLength; i++)
				AddAthlete(group.SFemaleAthleteList, femaleList.pSAthleteList[i]);
		}
		else {//径赛从低到高排序
			for (int i = femaleList.nListLength - 1; i >= 0; i--)
				AddAthlete(group.SFemaleAthleteList, femaleList.pSAthleteList[i]);
		}
		DestroyAthleteList(femaleList);

		//完成男子组的排名
		SAthleteList maleList;
		InitAthleteList(maleList);
		while (group.SMaleAthleteList.nListLength > 0) {
			double dResult = 0;
			int nPos_athlete = 0;
			for (int i = 0; i < group.SMaleAthleteList.nListLength; i++) {
				int nPos_item = LocateAthleteItem(group.SMaleAthleteList.pSAthleteList[i], group.szItemID);
				if (group.SMaleAthleteList.pSAthleteList[i].SAthleteItem[nPos_item].dResult >= dResult) {
					nPos_athlete = i;
					dResult = group.SMaleAthleteList.pSAthleteList[i].SAthleteItem[nPos_item].dResult;
				}
			}//for
			AddAthlete(maleList, group.SMaleAthleteList.pSAthleteList[nPos_athlete]);
			DeleteAthlete(group.SMaleAthleteList, nPos_athlete);
		}//while
		if (group.SPORTTYPE_SportType == SPORTTYPE_FIELD) {//田赛成绩从高到低排序
			for (int i = 0; i < maleList.nListLength; i++)
				AddAthlete(group.SMaleAthleteList, maleList.pSAthleteList[i]);
		}
		else {//径赛从低到高排序
			for (int i = maleList.nListLength - 1; i >= 0; i--)
				AddAthlete(group.SMaleAthleteList, maleList.pSAthleteList[i]);
		}
		DestroyAthleteList(maleList);
		return 1;
	}//if(finish_input==1)
	else {
		if (finish_input == -1)
			printf("\n %s 女子组 成绩未输入完成！\n", group.szItemName);
		else if (finish_input == 0)
			printf("\n %s 男子组 成绩未输入完成！\n", group.szItemName);
		else if(finish_input==-2)
			printf("\n %s 男子组和女子组 成绩未输入完成！\n", group.szItemName);
		return 0;
	}
}

void DisplayItemWithNumber(SSportItem& SItem) {
	int count = 0;

	SAthleteList athletelist;
	InitAthleteList(athletelist);
	ReadAthleteListFile(athletelist);
	for (int i = 0; i < athletelist.nListLength; i++) {
		if (LocateAthleteItem(athletelist.pSAthleteList[i], SItem.szItemID)!=-1) {
			count++;
		}
	}
	DestroyAthleteList(athletelist);

	printf("\t|%-10s", SItem.szItemID);
	printf("|%-20s", SItem.szItemName);

	if (SItem.SPORTYPE_itemtype == SPORTTYPE_TRACK)
		printf("|径赛\t");
	else if (SItem.SPORTYPE_itemtype == SPORTTYPE_FIELD)
		printf("|田赛\t");

	printf("|%.2lf\t", SItem.dItemTime);
	printf("|%8d|\t", count);
	printf("\n");
}

void DisplayItemListWithNumber(SItemList& SList) {
	printf("\n\t__________________________________________________________\n");
	printf("\t|编号      |名称                |类别\t|耗时\t|报名人数|\n");
	for (int i = 0; i < SList.nListLength; i++) {
		printf("\t__________________________________________________________\n");
		DisplayItemWithNumber(SList.pSItemList[i]);
	}
}