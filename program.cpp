#include"program.h"

void InitTimeList(STimeList& timelist) {
	timelist.length = 0;
}

void ClearTimeList(STimeList& timelist) {
	timelist.length = 0;
}

void AddTime(STimeList& timelist, STime time) {
	timelist.times[timelist.length] = time;
	timelist.length++;
}

int IsEmpty(STimeList& timelist) {
	return (!timelist.length);
}

void DisplayTimeInfo(STimeList& timelist) {
	for (int i = 0; i < timelist.length; i++) {
		STime* pTime = &timelist.times[i];
		printf("%d-%d-%d-%d:%02d~%d:%02d\n", pTime->year, pTime->month, pTime->day, pTime->hour_begin, pTime->min_begin, pTime->hour_end, pTime->min_end);
	}
}

void DisplayTimeItemInfo(STimeList& timelist) {
	FILE* pProgram=NULL;
	errno_t err = fopen_s(&pProgram,"program.txt","a");
	SItemList itemlist;
	InitItemList(itemlist);
	ReadItemListFile(itemlist);
	Grouping(itemlist);//分组
	int nPos_tmp = LocateItem(itemlist, timelist.times[0].szItemName);
	if (itemlist.pSItemList[nPos_tmp].SPORTTYPE_itemtype == SPORTTYPE_TRACK) {
		printf("\n\n===================径赛==================\n");
		fprintf(pProgram, "\n\n===================径赛==================\n");
	}
	else {
		printf("\n\n===================田赛==================\n");
		fprintf(pProgram, "\n\n===================田赛==================\n");
	}
	for (int i = 0; i < timelist.length; i++) {
		STime* time = &timelist.times[i];//获得这个时间段
		int nPos_item = LocateItem(itemlist, time->szItemName);
		SSportItem* item = &itemlist.pSItemList[nPos_item];//获得这个项目
		printf("\n\n\t%s %s   组数：%d  人数：%d  场地：%s",item->szItemID,item->szItemName,item->GroupNumber,item->pAthleteList->nListLength,item->szPlace);
		fprintf(pProgram, "\n\n\t%s %s   组数：%d  人数：%d  场地：%s", item->szItemID, item->szItemName, item->GroupNumber, item->pAthleteList->nListLength, item->szPlace);
		printf("\n\t时间段：%d-%d-%d-%02d:%02d~%02d:%02d\n", time->year, time->month, time->day, time->hour_begin, time->min_begin, time->hour_end, time->min_end);
		fprintf(pProgram, "\n\t时间段：%d-%d-%d-%02d:%02d~%02d:%02d\n", time->year, time->month, time->day, time->hour_begin, time->min_begin, time->hour_end, time->min_end);
		printf("\t***************************************************************************\n");
		fprintf(pProgram,"\t***************************************************************************\n");
		for (int j = 0; j < item->GroupNumber; j++) {
			printf("\t**  第%d组\n",j+1);
			fprintf(pProgram, "\t**  第%d组\n", j + 1);
			SAthleteList* SGroupJ = item->ppAthleteGroup[j];//第j组
			for (int k = 0; k < SGroupJ->nListLength; k++) {//把所有的人员输出
				if (k == 0) {
					printf("\t**");
					fprintf(pProgram, "\t**");
				}
				if ((k % 8) == 0 && k != 0) {
					printf("**\n\t**");
					fprintf(pProgram, "**\n\t**");
				}
				SAthlete* athleteK = &SGroupJ->pSAthleteList[k];
				printf("%-2d %-8s\t", k + 1,athleteK->szAthleteName);
				fprintf(pProgram, "%-2d %-8s\t", k + 1, athleteK->szAthleteName);
			}
			printf("\n\t**-------------------------------------------------------------------------\n");
			fprintf(pProgram, "\n\t**-------------------------------------------------------------------------\n");
		}//for
		printf("\t***************************************************************************\n");
		fprintf(pProgram, "\t***************************************************************************\n");
	}
	DestroyItemList(itemlist);
	fclose(pProgram);
}

int* finishTime(int hour, int min, int add_min) {
	int* result = (int*)malloc(2 * sizeof(int));
	if (!result) {
		printf("内存分配失败");
		exit(0);
	}
	min = min + add_min;
	while (min > 60) {
		hour++;
		min -= 60;
	}
	result[0] = hour;
	result[1] = min;
	return result;
}

int compareTime(int hour, int min, int other_hour, int other_min) {
	int time_first = hour * 60 + min;
	int time_last = other_hour * 60 + other_min;
	if (time_last > time_first)
		return 1;
	else if (time_last == time_first)
		return 0;
	else
		return -1;
}

int LocateName(char** szNames,int n, char* szName) {
	int nPos = -1;
	for (int i = 0; i < n; i++) {
		if (strcmp(szNames[i], szName) == 0) {
			nPos = i;
			break;
		}
	}
	return nPos;
}

void CreateProgram() {
	SItemList itemlist;
	InitItemList(itemlist);
	ReadItemListFile(itemlist);
	Grouping(itemlist);
	SItemList trackItemList;
	InitItemList(trackItemList);
	SItemList fieldItemList;
	InitItemList(fieldItemList);
	double dTime = 0;
	double intervalTime_Group = 3;//组和组之间的时间间隔
	double intervalTime_item = 10;//项目和项目之间的时间间隔
	for (int i = 0; i < itemlist.nListLength; i++) {//按田径赛分类
		SSportItem* item = &itemlist.pSItemList[i];
		if (item->SPORTTYPE_itemtype == SPORTTYPE_TRACK) {
			dTime += item->dItemTime * item->GroupNumber + intervalTime_Group * (item->GroupNumber - 1) + intervalTime_item;
			AddItem(trackItemList, *item);
		}
		else {
			dTime += item->dItemTime * item->pAthleteList->nListLength + intervalTime_item;
			AddItem(fieldItemList, *item);
		}
	}
	//输入时间信息:
	STimeList timelist;
	while (true) {
		DisplayItemList(itemlist);
		dTime /= 60;//小时
		printf("\n\t预计需要%.2lf小时\n\n", dTime);
		printf("请输入比赛进行的时间段：(输入#结束)\n");
		printf("\n例如：(输入所有连续的时间区间，需要严格按照一下格式输入)\n2020-3-29-9:00~11:00\n2020-3-29-14:00~16:00\n2020-3-30-9:00~11:00\n\n");
		printf("\n\t输入你的时间：\n");

		char flag;
		InitTimeList(timelist);
		STime time;
		while ((flag = getchar()) != '#') {
			ungetc(flag, stdin);//放回去
			scanf_s("%d-%d-%d-%d:%d~%d:%d", &time.year, &time.month, &time.day, &time.hour_begin, &time.min_begin, &time.hour_end, &time.min_end);
			AddTime(timelist, time);
			while (getchar() != '\n')
				continue;
		}
		printf("\n\t项目和项目之间的相隔时间(min)：");
		double dIntervalTime_item = GetDouble();
		printf("\n\n");
		system("cls");
		printf("\n\t检查信息是否正确：\n");
		DisplayTimeInfo(timelist);
		printf("\n\n\t项目相隔时间：%.2lf\n\n", dIntervalTime_item);

		printf("\n\t1.确定\n");
		printf("\n\t2.重新输入\n");
		printf("\n\t3.取消\n");
		printf("\n\t你的选择：");
		int nChoice_confirm = GetOption(1, 3);
		if (nChoice_confirm == 1) {
			system("cls");
			AllocItemTime(timelist, 1, dIntervalTime_item);//为项目分配时间
			break;
		}//if
		else if (nChoice_confirm == 3) {
			break;
		}
	}//while

}

int AllocItemTime(STimeList& timelist, double dIntervalTime_Group,double dIntervalTime_Item) {
	if (timelist.length == 0) {
		printf("\n时间段空，请输入时间段\n");
		return -1;
	}
	SItemList itemlist;//项目表
	InitItemList(itemlist);
	ReadItemListFile(itemlist);
	Grouping(itemlist);

	SItemList trackItemList;//径赛项目表  注意该表中项目的报名表和分组表和itemlist中项目的报名表和分组表应该是共享的。
	SItemList fieldItemList;//田赛项目表
	InitItemList(trackItemList);
	InitItemList(fieldItemList);
	for (int i = 0; i < itemlist.nListLength; i++) {
		if (itemlist.pSItemList[i].SPORTTYPE_itemtype == SPORTTYPE_TRACK)
			AddItem(trackItemList, itemlist.pSItemList[i]);
		else
			AddItem(fieldItemList, itemlist.pSItemList[i]);
	}

	if (itemlist.nListLength == 0)//当项目表长度为0时，退出函数
		return -1;
	SAthleteList athletelist;//运动员表，用来初始化项目分组表
	InitAthleteList(athletelist);
	ReadAthleteListFile(athletelist);


	STimeList trackTimeList;//径赛时间表
	InitTimeList(trackTimeList);
	STimeList fieldTimeList;//田赛时间表
	InitTimeList(fieldTimeList);
	STime time;//存放实际运动会的某个整时间段
	int* itembeginTime;//存放项目的开始时间
	int* itemfinishTime;//存放项目的结束时间
	int add_min = 0;
	int nPeriodsTime = 0;
	time = timelist.times[nPeriodsTime];//从参数中的itemlist中获得第一个时间段，包含年月日 开始小时分钟，结束小时分钟

	for (int i = 0; i < trackItemList.nListLength; i++) {//处理径赛的时间
		STime time_track;
		SSportItem* item = &trackItemList.pSItemList[i];
		add_min = item->dItemTime * item->GroupNumber + dIntervalTime_Group*(item->GroupNumber-1);//结束时间 = 开始时间+组数*每组比赛时间+每组比赛之间的间隔时间*(组数-1)
		if (i == 0) {
			time_track = time;
			itemfinishTime = finishTime(time_track.hour_begin, time_track.min_begin, add_min);//得出结束时间
			time_track.hour_end = itemfinishTime[0];
			time_track.min_end = itemfinishTime[1];
			strcpy_s(time_track.szItemName, sizeof(time_track.szItemName), item->szItemName);//将这个项目的名字放到这个时间段中
			AddTime(trackTimeList, time_track);///添加到径赛比赛时间表中
			free(itemfinishTime);
		}
		else {
			int Last_Pos = trackTimeList.length - 1;
			time_track = trackTimeList.times[Last_Pos];//等于时间列表中最后一个时间段
			itembeginTime = finishTime(time_track.hour_end, time_track.min_end, dIntervalTime_Item);//开始时间等于上个项目结束时间+项目之间间隔的时间
			time_track.hour_begin = itembeginTime[0];
			time_track.min_begin = itembeginTime[1];
			itemfinishTime = finishTime(itembeginTime[0], itembeginTime[1], add_min);//结束时间
			time_track.hour_end = itemfinishTime[0];
			time_track.min_end = itemfinishTime[1];
			strcpy_s(time_track.szItemName, sizeof(time_track.szItemName), item->szItemName);//放名字

			if (compareTime(time.hour_end, time.min_end, time_track.hour_begin, time_track.min_begin) == 1||
				compareTime(time.hour_end,time.min_end,time_track.hour_end,time_track.min_end)==1) {
				//如果该项目的开始时间比这个时间段要晚，则从下一个时间段开始
				//如果该项目的结束时间比这个时间段的结束时间要晚，则也从下个时间段开始
				nPeriodsTime++;
				time = timelist.times[nPeriodsTime];
				time_track = time;
				itemfinishTime = finishTime(time_track.hour_begin, time_track.min_begin, add_min);//得出结束时间
				time_track.hour_end = itemfinishTime[0];
				time_track.min_end = itemfinishTime[1];
				free(itemfinishTime);
			}

			AddTime(trackTimeList, time_track);//添加到径赛比赛时间表中
			free(itembeginTime);
			free(itemfinishTime);
		}
	}
	system("cls");
	DisplayTimeItemInfo(trackTimeList);


	////////////////处理田赛
	add_min = 0;
	nPeriodsTime = 0;
	time = timelist.times[nPeriodsTime];//从参数中的itemlist中获得第一个时间段，包含年月日 开始小时分钟，结束小时分钟

	for (int i = 0; i < fieldItemList.nListLength; i++) {//处理径赛的时间
		STime time_field;
		SSportItem* item = &fieldItemList.pSItemList[i];
		add_min = item->dItemTime * item->pAthleteList->nListLength;
		if (i == 0) {
			time_field = time;
			itemfinishTime = finishTime(time_field.hour_begin, time_field.min_begin, add_min);//得出结束时间
			time_field.hour_end = itemfinishTime[0];
			time_field.min_end = itemfinishTime[1];
			strcpy_s(time_field.szItemName, sizeof(time_field.szItemName), item->szItemName);//将这个项目的名字放到这个时间段中
			AddTime(fieldTimeList, time_field);///添加到径赛比赛时间表中
			free(itemfinishTime);
		}
		else {
			int Last_Pos = fieldTimeList.length - 1;
			time_field = fieldTimeList.times[Last_Pos];//等于时间列表中最后一个时间段
			itembeginTime = finishTime(time_field.hour_end, time_field.min_end, dIntervalTime_Item);//开始时间等于上个项目结束时间+项目之间间隔的时间
			time_field.hour_begin = itembeginTime[0];
			time_field.min_begin = itembeginTime[1];
			itemfinishTime = finishTime(itembeginTime[0], itembeginTime[1], add_min);//结束时间
			time_field.hour_end = itemfinishTime[0];
			time_field.min_end = itemfinishTime[1];
			strcpy_s(time_field.szItemName, sizeof(time_field.szItemName), item->szItemName);//放名字

			if (compareTime(time.hour_end, time.min_end, time_field.hour_begin, time_field.min_begin) == 1 ||
				compareTime(time.hour_end, time.min_end, time_field.hour_end, time_field.min_end) == 1) {
				//如果该项目的开始时间比这个时间段要晚，则从下一个时间段开始
				//如果该项目的结束时间比这个时间段的结束时间要晚，则也从下个时间段开始
				nPeriodsTime++;
				time = timelist.times[nPeriodsTime];
				time_field = time;
				itemfinishTime = finishTime(time_field.hour_begin, time_field.min_begin, add_min);//得出结束时间
				time_field.hour_end = itemfinishTime[0];
				time_field.min_end = itemfinishTime[1];
				free(itemfinishTime);
			}

			AddTime(fieldTimeList, time_field);//添加到径赛比赛时间表中
			free(itembeginTime);
		}
	}
	DisplayTimeItemInfo(fieldTimeList);


	return 0;
}

void menu_Program() {
	printf("\n\t1.生成秩序册\n");
	printf("\n\t2.查看秩序册\n");
	printf("\n\t3.返回主菜单\n");
	printf("\n\t你的选择：");
}
void ProgramManagement() {
	while (true) {
		system("cls");
		menu_Program();
		int nChoice = GetOption(1, 3);
		switch (nChoice)
		{
		case 1: {
			system("cls");
			FILE* pProgram = NULL;
			errno_t err = fopen_s(&pProgram, "program.txt", "w");//清空秩序册
			fclose(pProgram);
			CreateProgram();
			break;
		}//case 1
		case 2: {
			FILE* pProgram = NULL;
			errno_t err = fopen_s(&pProgram, "program.txt", "r");
			system("cls");
			char ch;
			while ((ch = fgetc(pProgram)) != EOF) {
				putchar(ch);
			}
			fclose(pProgram);
		}//case 2
		}//switch
		if (nChoice == 3)
			break;
		system("pause");
	}//while
}
