#include"program.h"

void InitTimeList(STimeList& timelist) {
	timelist.length = 0;
}

void ClearTimeList(STimeList& timelist) {
	timelist.length = 0;
}

void AddTime(STimeList& timelist,STime time) {
	timelist.times[timelist.length] = time;
	timelist.length++;
}

int IsEmpty(STimeList& timelist) {
	return (!timelist.length);
}

void InputBaseInfo() {
	char szSchoolName[40];//学校名字
	char szSponsor[40];//主办方
	char szOrganizer[40];//承办方
	char szPlace[40];//举办地点
	char szNumber[15];//第几届
	STimeList timelist;
	InitTimeList(timelist);
	STime time;
	char flag;//判断是否结束标志
	int nChoice_confirm= 0;
	int nIntervalTime = 0;
	while (nChoice_confirm != 1&&nChoice_confirm!=3) {
		ClearTimeList(timelist);
		printf("\n\t请输入秩序册的基本信息：\n");
		printf("\n\t学校名字:");
		scanf_s("%s", szSchoolName, 40);
		printf("\n\t主办单位：");
		scanf_s("%s", szSponsor, 40);
		printf("\n\t承办单位:");
		scanf_s("%s", szOrganizer, 40);
		printf("\n\t地点：");
		scanf_s("%s", szPlace, 40);
		printf("\n\t届数：");
		scanf_s("%s", szNumber, 15);
		printf("\n\n\t时间：\n");
		printf("请输入比赛进行的时间段：(输入#结束)\n");
		printf("\n例如：(输入所有连续的时间区间，需要严格按照一下格式输入)\n2020-3-29-9:00~11:00\n2020-3-29-14:00~16:00\n2020-3-30-9:00~11:00\n\n");
		printf("\n\t输入你的时间：\n");
		while (getchar() != '\n')
			continue;
		while ((flag = getchar()) != '#') {
			ungetc(flag, stdin);//放回去
			scanf_s("%d-%d-%d-%d:%d~%d:%d", &time.year, &time.month, &time.day, &time.hour_begin, &time.min_begin, &time.hour_end, &time.min_end);
			AddTime(timelist, time);
			while (getchar() != '\n')
				continue;
		}
		printf("\n\t项目和项目之间的相隔时间：");
		while (!(cin >> nIntervalTime)) {
			cin.clear();
			while (cin.get() != '\n')
				continue;
			cout << "\t输入错误，请重新输入：";
		}


		printf("\n\n");
		system("cls");
		printf("\n\t检查信息是否正确：\n");
		printf("\n\t学校：%s", szSchoolName);
		printf("\n\n\t主办方：%s",szSponsor);
		printf("\n\n\t举办方：%s", szOrganizer);
		printf("\n\n\t举办地点：%s\n", szPlace);
		printf("\n\t第%s届\n", szNumber);
		printf("\n\n\t项目相隔时间：%d\n\n", nIntervalTime);
		DisplayTimeInfo(timelist);
		printf("\n\t1.确定\n");
		printf("\n\t2.重新输入\n");
		printf("\n\t3.取消\n");
		printf("\n\t你的选择：");

		while (!(cin >> nChoice_confirm)) {
			cin.clear();
			while (cin.get() != '\n')
				continue;
			printf("请重新输入：");
		}//while
		if (nChoice_confirm == 1) {
			AllocItemTime(timelist,nIntervalTime,szSchoolName,szSponsor,szOrganizer,szPlace,szNumber);//为项目分配时间
		}//if
		else if (nChoice_confirm == 3) {
			break;
		}

	}//while(confirm);
}

void DisplayTimeInfo(STimeList& timelist) {
	for (int i = 0; i < timelist.length; i++) {
		STime* pTime = &timelist.times[i];
		printf("%d-%d-%d-%d:%02d~%d:%02d\n", pTime->year, pTime->month, pTime->day, pTime->hour_begin, pTime->min_begin, pTime->hour_end, pTime->min_end);
	}
}

int AllocItemTime(STimeList& timelist, int nIntervalTime, char szSchoolName[],char szSponsor[],char szOrganize[],char szPlace[],char szNumber[]) {
	if (timelist.length == 0) {
		printf("\n时间段空，请输入时间段\n");
		return -1;
	}
	SItemList itemlist;//项目表
	InitItemList(itemlist);
	ReadItemListFile(itemlist);
	if (itemlist.nListLength == 0)//当项目表长度为0时，退出函数
		return -1;
	SAthleteList athletelist;//运动员表，用来初始化项目分组表
	InitAthleteList(athletelist);
	ReadAthleteListFile(athletelist);
	SGroupList itemgrouplist;//项目分组表，获取组数
	ConnectItemList(itemgrouplist, itemlist);
	ConnectAthleteList(itemgrouplist,athletelist);
	STimeList itemTimeList;//存放项目的比赛时间，每个项目占据两个位置，第一个位置是男子组的时间，第二个位置是女子组的时间。
	InitTimeList(itemTimeList);

	STime time;
	int* itembeginTime_female;//女子项目开始时间
	int* itemfinishTime_female;//女子项目结束时间
	int* itemfinishTime_male;//男性项目结束时间
	int* itembeginTime_male;//男性项目开始时间
	int add_min_male;
	int add_min_female;
	int nPeriodsTime = 0;
	time = timelist.times[nPeriodsTime];//从第一个时间段开始
	double dItemTime = itemlist.pSItemList[0].dItemTime;
	if (itemlist.pSItemList[0].SPORTYPE_itemtype == SPORTTYPE_TRACK) {//径赛
			//项目时间=组数*项目耗时
		int nMaleGroupNumber = itemgrouplist.pSItemGroupList[0].nMaleGroupNumber;
		int nFemaleGroupNumber = itemgrouplist.pSItemGroupList[0].nFemaleGroupNumber;
		add_min_male = ceil(nMaleGroupNumber * dItemTime);
		add_min_female = ceil(nFemaleGroupNumber * dItemTime);
	}
	else {//田赛
			//项目时间=人数*项目耗时
		int maleAthleteNumber = itemgrouplist.pSItemGroupList[0].SMaleAthleteList.nListLength;
		int femaleAthleteNumber = itemgrouplist.pSItemGroupList[0].SFemaleAthleteList.nListLength;
		add_min_male = ceil(maleAthleteNumber * dItemTime);
		add_min_female = ceil(femaleAthleteNumber* dItemTime);
	}

	itemfinishTime_male = finishTime(time.hour_begin, time.min_begin, add_min_male);
	time.hour_end = itemfinishTime_male[0];
	time.min_end = itemfinishTime_male[1];
	AddTime(itemTimeList, time);//加入表中

	itembeginTime_female = finishTime(itemfinishTime_male[0], itemfinishTime_male[1], nIntervalTime);//加上间隔时间
	itemfinishTime_female = finishTime(itembeginTime_female[0], itembeginTime_female[1], add_min_female);//加上项目时间
	time.hour_begin = itembeginTime_female[0];
	time.min_begin = itembeginTime_female[1];
	time.hour_end = itemfinishTime_female[0];
	time.min_end = itemfinishTime_female[1];
	AddTime(itemTimeList, time);
	free(itembeginTime_female);
	free(itemfinishTime_female);
	free(itemfinishTime_male);

	for (int i = 1; i < itemlist.nListLength; i++) {
		if (itemlist.pSItemList[i].SPORTYPE_itemtype == SPORTTYPE_TRACK) {//径赛
			//项目时间=组数*项目耗时
			int nMaleGroupNumber = itemgrouplist.pSItemGroupList[i].nMaleGroupNumber;
			int nFemaleGroupNumber = itemgrouplist.pSItemGroupList[i].nFemaleGroupNumber;
			add_min_male = ceil(nMaleGroupNumber * dItemTime);
			add_min_female = ceil(nFemaleGroupNumber * dItemTime);
		}
		else {//田赛
				//项目时间=人数*项目耗时
			int maleAthleteNumber = itemgrouplist.pSItemGroupList[i].SMaleAthleteList.nListLength;
			int femaleAthleteNumber = itemgrouplist.pSItemGroupList[i].SFemaleAthleteList.nListLength;
			add_min_male = ceil(maleAthleteNumber * dItemTime);
			add_min_female = ceil(femaleAthleteNumber * dItemTime);
		}
		int last_item_finish_time[2] = { itemTimeList.times[itemTimeList.length - 1].hour_end, itemTimeList.times[itemTimeList.length - 1].min_end };
		itembeginTime_male = finishTime(last_item_finish_time[0], last_item_finish_time[1], nIntervalTime);
		itemfinishTime_male = finishTime(itembeginTime_male[0], itembeginTime_male[1], add_min_male);
		if (compareTime(timelist.times[nPeriodsTime].hour_end, timelist.times[nPeriodsTime].min_end, itemfinishTime_male[0], itemfinishTime_male[1]) == 1 ||
			compareTime(timelist.times[nPeriodsTime].hour_end, timelist.times[nPeriodsTime].min_end, itembeginTime_male[0], itembeginTime_male[1]) == 1) {
			//超过该时间段,则从下一个时间段开始
			nPeriodsTime++;
			if (nPeriodsTime >= timelist.length) {
				printf("时间不够，请输入更多的时间段");
				return -1;
			}
			time = timelist.times[nPeriodsTime];
			free(itemfinishTime_male);
			itemfinishTime_male = finishTime(time.hour_begin, time.min_begin, add_min_male);
			time.hour_end = itemfinishTime_male[0];
			time.min_end = itemfinishTime_male[1];
		}//if(compare)
		else {
			time.hour_begin = itembeginTime_male[0];
			time.min_begin = itembeginTime_male[1];
			time.hour_end = itemfinishTime_male[0];
			time.min_end = itemfinishTime_male[1];
		}
		free(itembeginTime_male);
		AddTime(itemTimeList, time);

		itembeginTime_female = finishTime(itemfinishTime_male[0], itemfinishTime_male[1], nIntervalTime);
		itemfinishTime_female = finishTime(itembeginTime_female[0], itembeginTime_female[1], add_min_female);
		if (compareTime(timelist.times[nPeriodsTime].hour_end, timelist.times[nPeriodsTime].min_end, itemfinishTime_female[0], itemfinishTime_female[1]) == 1 ||
			compareTime(timelist.times[nPeriodsTime].hour_end, timelist.times[nPeriodsTime].min_end, itembeginTime_female[0], itembeginTime_female[1]) == 1) {
			//超过该时间段,则从下一个时间段开始
			nPeriodsTime++;
			if (nPeriodsTime >= timelist.length) {
				printf("时间不够，请输入更多的时间段");
				return -1;
			}
			time = timelist.times[nPeriodsTime];
			free(itemfinishTime_female);
			itemfinishTime_female = finishTime(time.hour_begin, time.min_begin, add_min_male);
			time.hour_end = itemfinishTime_female[0];
			time.min_end = itemfinishTime_female[1];
		}//if(compare)
		else {
			time.hour_begin = itembeginTime_female[0];
			time.min_begin = itembeginTime_female[1];
			time.hour_end = itemfinishTime_female[0];
			time.min_end = itemfinishTime_female[1];
		}
		free(itemfinishTime_male);
		free(itemfinishTime_female);
		free(itembeginTime_female);
		AddTime(itemTimeList, time);
	}//for



	//这个时候，itemTimeList存放着所有的项目开始的时间
	//打印所有的项目分配时间

	printf("\n\n一下是项目分组信息\n");
	printf("|序号");
	printf("%-25s", "|项目时间");
	printf("%-22s\n", "|项目名称");
	int count_item = 1;
	for (int i = 0; i < 2*itemlist.nListLength; i++) {
		STime* pTime = &itemTimeList.times[i];
		printf("__________________________________________________\n");
		printf("|%4d", count_item++);
		printf("|%d-%02d-%02d-%02d:%02d~%02d:%02d  ", pTime->year, pTime->month, pTime->day, pTime->hour_begin, pTime->min_begin, pTime->hour_end, pTime->min_end);//把时间信息打印出来
		if (i % 2 == 0) //男生组
			printf("|男子组%-15s\n", itemlist.pSItemList[i/2].szItemName);
		else 
			printf("|女子组%-15s\n", itemlist.pSItemList[i / 2].szItemName);
	}

	////////写入doc文件
	printf("\n\n是否生成秩序册？");
	printf("\n1.确定");
	printf("\n2.取消");
	int nChoice_CreateProgram = 0;
	while (!(cin >> nChoice_CreateProgram)) {
		cin.clear();
		while (cin.get() != '\n')
			continue;
		printf("请重新输入：");
	}
	switch (nChoice_CreateProgram)
	{
	case 1: {
		FILE* pProgram;
		char fileName[100] = "第";
		strncat_s(fileName,100, szNumber, strlen(szNumber));
		strncat_s(fileName,100, "届", sizeof("届"));
		strncat_s(fileName,100, szSchoolName, strlen(szSchoolName));
		strncat_s(fileName,100, "校运会秩序册.doc", sizeof("校运会秩序册.doc"));
		char headName[100];
		strncpy_s(headName,100, fileName,strlen(fileName)-4);//秩序册标题
		errno_t err = fopen_s(&pProgram, fileName, "w");
		if (err != 0) {
			printf("%s文件打开失败", fileName);
			exit(0);
		}
		fwrite(headName, strlen(headName)+1, 1, pProgram);//写入标题
		fputc('\n', pProgram);
		fputc('\n', pProgram);

		fprintf(pProgram, "主办方：");
		fwrite(szSponsor, strlen(szSponsor) + 1, 1, pProgram);
		fputc('\n', pProgram);	
		fputc('\n', pProgram);

		fprintf(pProgram, "举办方：");
		fwrite(szOrganize, strlen(szOrganize) + 1, 1, pProgram);
		fputc('\n', pProgram);
		fputc('\n', pProgram);

		fprintf(pProgram, "地点：");
		fwrite(szPlace, strlen(szPlace) + 1, 1, pProgram);
		fputc('\n', pProgram);
		fputc('\n', pProgram);
		fputc('\n', pProgram);

		fprintf(pProgram, "代表队名单");
		fputc('\n', pProgram);
		int count_academy = 0;
		for (int i = 1; i <= 9; i++) {
			fprintAcademyAthlete(pProgram, athletelist, (Academy)i, count_academy);
		}

		fputc('\n', pProgram);
		fputc('\n', pProgram);
		fprintf(pProgram, "比赛进程");
		fputc('\n', pProgram);
		fputc('\n', pProgram);
		fprintf(pProgram,"|序号");
		fprintf(pProgram,"%-25s", "|项目时间");
		fprintf(pProgram,"%-22s\n", "|项目名称");
		int count_itemtime = 1;
		for (int i = 0; i < 2 * itemlist.nListLength; i++){
			STime* pTime = &itemTimeList.times[i];
			fprintf(pProgram,"__________________________________________________\n");
			fprintf(pProgram,"|%4d", count_itemtime++);
			fprintf(pProgram,"|%d-%02d-%02d-%02d:%02d~%02d:%02d  ", pTime->year, pTime->month, pTime->day, pTime->hour_begin, pTime->min_begin, pTime->hour_end, pTime->min_end);//把时间信息打印出来
			if (i % 2 == 0) //男生组
				fprintf(pProgram,"|男子组%-15s\n", itemlist.pSItemList[i / 2].szItemName);
			else
				fprintf(pProgram,"|女子组%-15s\n", itemlist.pSItemList[i / 2].szItemName);
		}

		fputc('\n', pProgram);
		fputc('\n', pProgram);
		fprintf(pProgram, "项目名单");	
		fputc('\n', pProgram);
		for (int i = 0; i < itemgrouplist.nListLength; i++) {
			SItemGroup* itemgroup = itemgrouplist.pSItemGroupList + i;
			if (itemgroup->nMaleGroupNumber != 0) {
				fprintf(pProgram, "\n\n%s 男子组\n", itemgroup->szItemName);
				for (int j = 0; j < itemgroup->nMaleGroupNumber; j++) {//有nMaleGroupNumber个组
					fprintf(pProgram, " \n 第%d组\n", j + 1);
					if (itemgroup->SPORTTYPE_SportType == SPORTTYPE_TRACK) {
						for (int k = 0; k < itemgroup->SMaleGroups[j].nListLength; k++) {//每组有nListLength个人
							ChineseNumber number = ChineseNumber(k + 1);
							switch (number)
							{
							case 一:
								fprintf(pProgram, "一\t\t");
								break;
							case 二:
								fprintf(pProgram, "二\t\t");
								break;
							case 三:
								fprintf(pProgram, "三\t\t");
								break;
							case 四:
								fprintf(pProgram, "四\t\t");
								break;
							case 五:
								fprintf(pProgram, "五\t\t");
								break;
							case 六:
								fprintf(pProgram, "六\t\t");
								break;
							case 七:
								fprintf(pProgram, "七\t\t");
								break;
							case 八:
								fprintf(pProgram, "八\t\t");
								break;
							default:
								break;
							}
						}
						fputc('\n', pProgram);
					}//if(sporttype)
					for (int k = 0; k < itemgroup->SMaleGroups[j].nListLength; k++) {//每组有nListLength个人
						fprintf(pProgram, "%s\t", itemgroup->SMaleGroups[j].pSAthleteList[k].szAthleteName);
					}
					fputc('\n', pProgram);
				}//for(j)
			}//if(gorup!=0)

			if (itemgroup->nFemaleGroupNumber != 0) {
				fprintf(pProgram, "\n\n%s 女子组\n", itemgroup->szItemName);
				for (int j = 0; j < itemgroup->nFemaleGroupNumber; j++) {
					fprintf(pProgram, "\n  第%d组\n", j + 1);
					if (itemgroup->SPORTTYPE_SportType == SPORTTYPE_TRACK) {
						for (int k = 0; k < itemgroup->SMaleGroups[j].nListLength; k++) {//每组有nListLength个人
							ChineseNumber number = ChineseNumber(k + 1);
							switch (number)
							{
							case 一:
								fprintf(pProgram, "一\t\t");
								break;
							case 二:
								fprintf(pProgram, "二\t\t");
								break;
							case 三:
								fprintf(pProgram, "三\t\t");
								break;
							case 四:
								fprintf(pProgram, "四\t\t");
								break;
							case 五:
								fprintf(pProgram, "五\t\t");
								break;
							case 六:
								fprintf(pProgram, "六\t\t");
								break;
							case 七:
								fprintf(pProgram, "七\t\t");
								break;
							case 八:
								fprintf(pProgram, "八\t\t");
								break;
							default:
								break;
							}
						}
						fputc('\n', pProgram);
					}//if(sporttype)
					for (int k = 0; k < itemgroup->SMaleGroups[j].nListLength; k++) {//每组有nListLength个人
						fprintf(pProgram, "%s\t", itemgroup->SMaleGroups[j].pSAthleteList[k].szAthleteName);
					}
					fputc('\n', pProgram);
				}//for(j)
			}//if(gourp!=0)
		}


		fclose(pProgram);
		printf("\n秩序册生成成功！\n");

		break;
	}
	default:
		break;
	}//switch

	//free(pItemGroupNumber);
	DestroyItemGroupList(itemgrouplist);
	DestroyAthleteList(athletelist);
	DestroyItemList(itemlist);
	return 0;
}

int* finishTime(int hour, int min, int add_min) {
	int* result = (int *)malloc(2*sizeof(int));
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

void fprintAcademyAthlete(FILE* pProgram ,SAthleteList& athletelist, Academy academy, int& count) {
	switch (academy)
	{
	case 知行书院:
		fprintf(pProgram, "知行书院");
		fputc('\n', pProgram);
		break;
	case 思源书院:
		fprintf(pProgram, "思源书院");
		fputc('\n', pProgram);
		break;
	case 弘毅书院:
		fprintf(pProgram, "弘毅书院");
		fputc('\n', pProgram);
		break;
	case 敬一书院:
		fprintf(pProgram, "敬一书院");
		fputc('\n', pProgram);
		break;
	case 至诚书院:
		fprintf(pProgram, "至诚书院");
		fputc('\n', pProgram);
		break;
	case 修远书院:
		fprintf(pProgram, "修远书院");
		fputc('\n', pProgram);
		break;
	case 明德书院:
		fprintf(pProgram, "明德书院");
		fputc('\n', pProgram);
		break;
	case 德馨书院:
		fprintf(pProgram, "德馨书院");
		fputc('\n', pProgram);
		break;
	case 研究生院:
		fprintf(pProgram, "研究生院");
		fputc('\n', pProgram);
		break;
	default:
		break;
	}
	int temp_Count = count;
	for (int i = 0; i < athletelist.nListLength; i++) {
		SAthlete* athlete = athletelist.pSAthleteList + i;
		if (athlete->academy == academy) {
			count++;
			char szCount[10] = {};
			_itoa_s(count, szCount, 10);//转化成字符串，（10进制）
			fwrite(szCount, strlen(szCount), 1, pProgram);
			fwrite(athlete->szAthleteName, strlen(athlete->szAthleteName) + 1, 1, pProgram);
			fputc('  ', pProgram);
			if ((count-temp_Count)%5== 0)
				fputc('\n', pProgram);
		}
	}
	fputc('\n', pProgram);
	fputc('\n', pProgram);
}
