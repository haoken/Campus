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
	Grouping(itemlist);//����
	int nPos_tmp = LocateItem(itemlist, timelist.times[0].szItemName);
	if (itemlist.pSItemList[nPos_tmp].SPORTTYPE_itemtype == SPORTTYPE_TRACK) {
		printf("\n\n===================����==================\n");
		fprintf(pProgram, "\n\n===================����==================\n");
	}
	else {
		printf("\n\n===================����==================\n");
		fprintf(pProgram, "\n\n===================����==================\n");
	}
	for (int i = 0; i < timelist.length; i++) {
		STime* time = &timelist.times[i];//������ʱ���
		int nPos_item = LocateItem(itemlist, time->szItemName);
		SSportItem* item = &itemlist.pSItemList[nPos_item];//��������Ŀ
		printf("\n\n\t%s %s   ������%d  ������%d  ���أ�%s",item->szItemID,item->szItemName,item->GroupNumber,item->pAthleteList->nListLength,item->szPlace);
		fprintf(pProgram, "\n\n\t%s %s   ������%d  ������%d  ���أ�%s", item->szItemID, item->szItemName, item->GroupNumber, item->pAthleteList->nListLength, item->szPlace);
		printf("\n\tʱ��Σ�%d-%d-%d-%02d:%02d~%02d:%02d\n", time->year, time->month, time->day, time->hour_begin, time->min_begin, time->hour_end, time->min_end);
		fprintf(pProgram, "\n\tʱ��Σ�%d-%d-%d-%02d:%02d~%02d:%02d\n", time->year, time->month, time->day, time->hour_begin, time->min_begin, time->hour_end, time->min_end);
		printf("\t***************************************************************************\n");
		fprintf(pProgram,"\t***************************************************************************\n");
		for (int j = 0; j < item->GroupNumber; j++) {
			printf("\t**  ��%d��\n",j+1);
			fprintf(pProgram, "\t**  ��%d��\n", j + 1);
			SAthleteList* SGroupJ = item->ppAthleteGroup[j];//��j��
			for (int k = 0; k < SGroupJ->nListLength; k++) {//�����е���Ա���
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
		printf("�ڴ����ʧ��");
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
	double intervalTime_Group = 3;//�����֮���ʱ����
	double intervalTime_item = 10;//��Ŀ����Ŀ֮���ʱ����
	for (int i = 0; i < itemlist.nListLength; i++) {//���ﾶ������
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
	//����ʱ����Ϣ:
	STimeList timelist;
	while (true) {
		DisplayItemList(itemlist);
		dTime /= 60;//Сʱ
		printf("\n\tԤ����Ҫ%.2lfСʱ\n\n", dTime);
		printf("������������е�ʱ��Σ�(����#����)\n");
		printf("\n���磺(��������������ʱ�����䣬��Ҫ�ϸ���һ�¸�ʽ����)\n2020-3-29-9:00~11:00\n2020-3-29-14:00~16:00\n2020-3-30-9:00~11:00\n\n");
		printf("\n\t�������ʱ�䣺\n");

		char flag;
		InitTimeList(timelist);
		STime time;
		while ((flag = getchar()) != '#') {
			ungetc(flag, stdin);//�Ż�ȥ
			scanf_s("%d-%d-%d-%d:%d~%d:%d", &time.year, &time.month, &time.day, &time.hour_begin, &time.min_begin, &time.hour_end, &time.min_end);
			AddTime(timelist, time);
			while (getchar() != '\n')
				continue;
		}
		printf("\n\t��Ŀ����Ŀ֮������ʱ��(min)��");
		double dIntervalTime_item = GetDouble();
		printf("\n\n");
		system("cls");
		printf("\n\t�����Ϣ�Ƿ���ȷ��\n");
		DisplayTimeInfo(timelist);
		printf("\n\n\t��Ŀ���ʱ�䣺%.2lf\n\n", dIntervalTime_item);

		printf("\n\t1.ȷ��\n");
		printf("\n\t2.��������\n");
		printf("\n\t3.ȡ��\n");
		printf("\n\t���ѡ��");
		int nChoice_confirm = GetOption(1, 3);
		if (nChoice_confirm == 1) {
			system("cls");
			AllocItemTime(timelist, 1, dIntervalTime_item);//Ϊ��Ŀ����ʱ��
			break;
		}//if
		else if (nChoice_confirm == 3) {
			break;
		}
	}//while

}

int AllocItemTime(STimeList& timelist, double dIntervalTime_Group,double dIntervalTime_Item) {
	if (timelist.length == 0) {
		printf("\nʱ��οգ�������ʱ���\n");
		return -1;
	}
	SItemList itemlist;//��Ŀ��
	InitItemList(itemlist);
	ReadItemListFile(itemlist);
	Grouping(itemlist);

	SItemList trackItemList;//������Ŀ��  ע��ñ�����Ŀ�ı�����ͷ�����itemlist����Ŀ�ı�����ͷ����Ӧ���ǹ���ġ�
	SItemList fieldItemList;//������Ŀ��
	InitItemList(trackItemList);
	InitItemList(fieldItemList);
	for (int i = 0; i < itemlist.nListLength; i++) {
		if (itemlist.pSItemList[i].SPORTTYPE_itemtype == SPORTTYPE_TRACK)
			AddItem(trackItemList, itemlist.pSItemList[i]);
		else
			AddItem(fieldItemList, itemlist.pSItemList[i]);
	}

	if (itemlist.nListLength == 0)//����Ŀ����Ϊ0ʱ���˳�����
		return -1;
	SAthleteList athletelist;//�˶�Ա��������ʼ����Ŀ�����
	InitAthleteList(athletelist);
	ReadAthleteListFile(athletelist);


	STimeList trackTimeList;//����ʱ���
	InitTimeList(trackTimeList);
	STimeList fieldTimeList;//����ʱ���
	InitTimeList(fieldTimeList);
	STime time;//���ʵ���˶����ĳ����ʱ���
	int* itembeginTime;//�����Ŀ�Ŀ�ʼʱ��
	int* itemfinishTime;//�����Ŀ�Ľ���ʱ��
	int add_min = 0;
	int nPeriodsTime = 0;
	time = timelist.times[nPeriodsTime];//�Ӳ����е�itemlist�л�õ�һ��ʱ��Σ����������� ��ʼСʱ���ӣ�����Сʱ����

	for (int i = 0; i < trackItemList.nListLength; i++) {//��������ʱ��
		STime time_track;
		SSportItem* item = &trackItemList.pSItemList[i];
		add_min = item->dItemTime * item->GroupNumber + dIntervalTime_Group*(item->GroupNumber-1);//����ʱ�� = ��ʼʱ��+����*ÿ�����ʱ��+ÿ�����֮��ļ��ʱ��*(����-1)
		if (i == 0) {
			time_track = time;
			itemfinishTime = finishTime(time_track.hour_begin, time_track.min_begin, add_min);//�ó�����ʱ��
			time_track.hour_end = itemfinishTime[0];
			time_track.min_end = itemfinishTime[1];
			strcpy_s(time_track.szItemName, sizeof(time_track.szItemName), item->szItemName);//�������Ŀ�����ַŵ����ʱ�����
			AddTime(trackTimeList, time_track);///��ӵ���������ʱ�����
			free(itemfinishTime);
		}
		else {
			int Last_Pos = trackTimeList.length - 1;
			time_track = trackTimeList.times[Last_Pos];//����ʱ���б������һ��ʱ���
			itembeginTime = finishTime(time_track.hour_end, time_track.min_end, dIntervalTime_Item);//��ʼʱ������ϸ���Ŀ����ʱ��+��Ŀ֮������ʱ��
			time_track.hour_begin = itembeginTime[0];
			time_track.min_begin = itembeginTime[1];
			itemfinishTime = finishTime(itembeginTime[0], itembeginTime[1], add_min);//����ʱ��
			time_track.hour_end = itemfinishTime[0];
			time_track.min_end = itemfinishTime[1];
			strcpy_s(time_track.szItemName, sizeof(time_track.szItemName), item->szItemName);//������

			if (compareTime(time.hour_end, time.min_end, time_track.hour_begin, time_track.min_begin) == 1||
				compareTime(time.hour_end,time.min_end,time_track.hour_end,time_track.min_end)==1) {
				//�������Ŀ�Ŀ�ʼʱ������ʱ���Ҫ�������һ��ʱ��ο�ʼ
				//�������Ŀ�Ľ���ʱ������ʱ��εĽ���ʱ��Ҫ����Ҳ���¸�ʱ��ο�ʼ
				nPeriodsTime++;
				time = timelist.times[nPeriodsTime];
				time_track = time;
				itemfinishTime = finishTime(time_track.hour_begin, time_track.min_begin, add_min);//�ó�����ʱ��
				time_track.hour_end = itemfinishTime[0];
				time_track.min_end = itemfinishTime[1];
				free(itemfinishTime);
			}

			AddTime(trackTimeList, time_track);//��ӵ���������ʱ�����
			free(itembeginTime);
			free(itemfinishTime);
		}
	}
	system("cls");
	DisplayTimeItemInfo(trackTimeList);


	////////////////��������
	add_min = 0;
	nPeriodsTime = 0;
	time = timelist.times[nPeriodsTime];//�Ӳ����е�itemlist�л�õ�һ��ʱ��Σ����������� ��ʼСʱ���ӣ�����Сʱ����

	for (int i = 0; i < fieldItemList.nListLength; i++) {//��������ʱ��
		STime time_field;
		SSportItem* item = &fieldItemList.pSItemList[i];
		add_min = item->dItemTime * item->pAthleteList->nListLength;
		if (i == 0) {
			time_field = time;
			itemfinishTime = finishTime(time_field.hour_begin, time_field.min_begin, add_min);//�ó�����ʱ��
			time_field.hour_end = itemfinishTime[0];
			time_field.min_end = itemfinishTime[1];
			strcpy_s(time_field.szItemName, sizeof(time_field.szItemName), item->szItemName);//�������Ŀ�����ַŵ����ʱ�����
			AddTime(fieldTimeList, time_field);///��ӵ���������ʱ�����
			free(itemfinishTime);
		}
		else {
			int Last_Pos = fieldTimeList.length - 1;
			time_field = fieldTimeList.times[Last_Pos];//����ʱ���б������һ��ʱ���
			itembeginTime = finishTime(time_field.hour_end, time_field.min_end, dIntervalTime_Item);//��ʼʱ������ϸ���Ŀ����ʱ��+��Ŀ֮������ʱ��
			time_field.hour_begin = itembeginTime[0];
			time_field.min_begin = itembeginTime[1];
			itemfinishTime = finishTime(itembeginTime[0], itembeginTime[1], add_min);//����ʱ��
			time_field.hour_end = itemfinishTime[0];
			time_field.min_end = itemfinishTime[1];
			strcpy_s(time_field.szItemName, sizeof(time_field.szItemName), item->szItemName);//������

			if (compareTime(time.hour_end, time.min_end, time_field.hour_begin, time_field.min_begin) == 1 ||
				compareTime(time.hour_end, time.min_end, time_field.hour_end, time_field.min_end) == 1) {
				//�������Ŀ�Ŀ�ʼʱ������ʱ���Ҫ�������һ��ʱ��ο�ʼ
				//�������Ŀ�Ľ���ʱ������ʱ��εĽ���ʱ��Ҫ����Ҳ���¸�ʱ��ο�ʼ
				nPeriodsTime++;
				time = timelist.times[nPeriodsTime];
				time_field = time;
				itemfinishTime = finishTime(time_field.hour_begin, time_field.min_begin, add_min);//�ó�����ʱ��
				time_field.hour_end = itemfinishTime[0];
				time_field.min_end = itemfinishTime[1];
				free(itemfinishTime);
			}

			AddTime(fieldTimeList, time_field);//��ӵ���������ʱ�����
			free(itembeginTime);
		}
	}
	DisplayTimeItemInfo(fieldTimeList);


	return 0;
}

void menu_Program() {
	printf("\n\t1.���������\n");
	printf("\n\t2.�鿴�����\n");
	printf("\n\t3.�������˵�\n");
	printf("\n\t���ѡ��");
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
			errno_t err = fopen_s(&pProgram, "program.txt", "w");//��������
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
