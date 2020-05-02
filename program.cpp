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
	char szSchoolName[40];//ѧУ����
	char szSponsor[40];//���췽
	char szOrganizer[40];//�а췽
	char szPlace[40];//�ٰ�ص�
	char szNumber[15];//�ڼ���
	STimeList timelist;
	InitTimeList(timelist);
	STime time;
	char flag;//�ж��Ƿ������־
	int nChoice_confirm= 0;
	int nIntervalTime = 0;
	while (nChoice_confirm != 1&&nChoice_confirm!=3) {
		ClearTimeList(timelist);
		printf("\n\t�����������Ļ�����Ϣ��\n");
		printf("\n\tѧУ����:");
		scanf_s("%s", szSchoolName, 40);
		printf("\n\t���쵥λ��");
		scanf_s("%s", szSponsor, 40);
		printf("\n\t�а쵥λ:");
		scanf_s("%s", szOrganizer, 40);
		printf("\n\t�ص㣺");
		scanf_s("%s", szPlace, 40);
		printf("\n\t������");
		scanf_s("%s", szNumber, 15);
		printf("\n\n\tʱ�䣺\n");
		printf("������������е�ʱ��Σ�(����#����)\n");
		printf("\n���磺(��������������ʱ�����䣬��Ҫ�ϸ���һ�¸�ʽ����)\n2020-3-29-9:00~11:00\n2020-3-29-14:00~16:00\n2020-3-30-9:00~11:00\n\n");
		printf("\n\t�������ʱ�䣺\n");
		while (getchar() != '\n')
			continue;
		while ((flag = getchar()) != '#') {
			ungetc(flag, stdin);//�Ż�ȥ
			scanf_s("%d-%d-%d-%d:%d~%d:%d", &time.year, &time.month, &time.day, &time.hour_begin, &time.min_begin, &time.hour_end, &time.min_end);
			AddTime(timelist, time);
			while (getchar() != '\n')
				continue;
		}
		printf("\n\t��Ŀ����Ŀ֮������ʱ�䣺");
		while (!(cin >> nIntervalTime)) {
			cin.clear();
			while (cin.get() != '\n')
				continue;
			cout << "\t����������������룺";
		}


		printf("\n\n");
		system("cls");
		printf("\n\t�����Ϣ�Ƿ���ȷ��\n");
		printf("\n\tѧУ��%s", szSchoolName);
		printf("\n\n\t���췽��%s",szSponsor);
		printf("\n\n\t�ٰ췽��%s", szOrganizer);
		printf("\n\n\t�ٰ�ص㣺%s\n", szPlace);
		printf("\n\t��%s��\n", szNumber);
		printf("\n\n\t��Ŀ���ʱ�䣺%d\n\n", nIntervalTime);
		DisplayTimeInfo(timelist);
		printf("\n\t1.ȷ��\n");
		printf("\n\t2.��������\n");
		printf("\n\t3.ȡ��\n");
		printf("\n\t���ѡ��");

		while (!(cin >> nChoice_confirm)) {
			cin.clear();
			while (cin.get() != '\n')
				continue;
			printf("���������룺");
		}//while
		if (nChoice_confirm == 1) {
			AllocItemTime(timelist,nIntervalTime,szSchoolName,szSponsor,szOrganizer,szPlace,szNumber);//Ϊ��Ŀ����ʱ��
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
		printf("\nʱ��οգ�������ʱ���\n");
		return -1;
	}
	SItemList itemlist;//��Ŀ��
	InitItemList(itemlist);
	ReadItemListFile(itemlist);
	if (itemlist.nListLength == 0)//����Ŀ����Ϊ0ʱ���˳�����
		return -1;
	SAthleteList athletelist;//�˶�Ա��������ʼ����Ŀ�����
	InitAthleteList(athletelist);
	ReadAthleteListFile(athletelist);
	SGroupList itemgrouplist;//��Ŀ�������ȡ����
	ConnectItemList(itemgrouplist, itemlist);
	ConnectAthleteList(itemgrouplist,athletelist);
	STimeList itemTimeList;//�����Ŀ�ı���ʱ�䣬ÿ����Ŀռ������λ�ã���һ��λ�����������ʱ�䣬�ڶ���λ����Ů�����ʱ�䡣
	InitTimeList(itemTimeList);

	STime time;
	int* itembeginTime_female;//Ů����Ŀ��ʼʱ��
	int* itemfinishTime_female;//Ů����Ŀ����ʱ��
	int* itemfinishTime_male;//������Ŀ����ʱ��
	int* itembeginTime_male;//������Ŀ��ʼʱ��
	int add_min_male;
	int add_min_female;
	int nPeriodsTime = 0;
	time = timelist.times[nPeriodsTime];//�ӵ�һ��ʱ��ο�ʼ
	double dItemTime = itemlist.pSItemList[0].dItemTime;
	if (itemlist.pSItemList[0].SPORTYPE_itemtype == SPORTTYPE_TRACK) {//����
			//��Ŀʱ��=����*��Ŀ��ʱ
		int nMaleGroupNumber = itemgrouplist.pSItemGroupList[0].nMaleGroupNumber;
		int nFemaleGroupNumber = itemgrouplist.pSItemGroupList[0].nFemaleGroupNumber;
		add_min_male = ceil(nMaleGroupNumber * dItemTime);
		add_min_female = ceil(nFemaleGroupNumber * dItemTime);
	}
	else {//����
			//��Ŀʱ��=����*��Ŀ��ʱ
		int maleAthleteNumber = itemgrouplist.pSItemGroupList[0].SMaleAthleteList.nListLength;
		int femaleAthleteNumber = itemgrouplist.pSItemGroupList[0].SFemaleAthleteList.nListLength;
		add_min_male = ceil(maleAthleteNumber * dItemTime);
		add_min_female = ceil(femaleAthleteNumber* dItemTime);
	}

	itemfinishTime_male = finishTime(time.hour_begin, time.min_begin, add_min_male);
	time.hour_end = itemfinishTime_male[0];
	time.min_end = itemfinishTime_male[1];
	AddTime(itemTimeList, time);//�������

	itembeginTime_female = finishTime(itemfinishTime_male[0], itemfinishTime_male[1], nIntervalTime);//���ϼ��ʱ��
	itemfinishTime_female = finishTime(itembeginTime_female[0], itembeginTime_female[1], add_min_female);//������Ŀʱ��
	time.hour_begin = itembeginTime_female[0];
	time.min_begin = itembeginTime_female[1];
	time.hour_end = itemfinishTime_female[0];
	time.min_end = itemfinishTime_female[1];
	AddTime(itemTimeList, time);
	free(itembeginTime_female);
	free(itemfinishTime_female);
	free(itemfinishTime_male);

	for (int i = 1; i < itemlist.nListLength; i++) {
		if (itemlist.pSItemList[i].SPORTYPE_itemtype == SPORTTYPE_TRACK) {//����
			//��Ŀʱ��=����*��Ŀ��ʱ
			int nMaleGroupNumber = itemgrouplist.pSItemGroupList[i].nMaleGroupNumber;
			int nFemaleGroupNumber = itemgrouplist.pSItemGroupList[i].nFemaleGroupNumber;
			add_min_male = ceil(nMaleGroupNumber * dItemTime);
			add_min_female = ceil(nFemaleGroupNumber * dItemTime);
		}
		else {//����
				//��Ŀʱ��=����*��Ŀ��ʱ
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
			//������ʱ���,�����һ��ʱ��ο�ʼ
			nPeriodsTime++;
			if (nPeriodsTime >= timelist.length) {
				printf("ʱ�䲻��������������ʱ���");
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
			//������ʱ���,�����һ��ʱ��ο�ʼ
			nPeriodsTime++;
			if (nPeriodsTime >= timelist.length) {
				printf("ʱ�䲻��������������ʱ���");
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



	//���ʱ��itemTimeList��������е���Ŀ��ʼ��ʱ��
	//��ӡ���е���Ŀ����ʱ��

	printf("\n\nһ������Ŀ������Ϣ\n");
	printf("|���");
	printf("%-25s", "|��Ŀʱ��");
	printf("%-22s\n", "|��Ŀ����");
	int count_item = 1;
	for (int i = 0; i < 2*itemlist.nListLength; i++) {
		STime* pTime = &itemTimeList.times[i];
		printf("__________________________________________________\n");
		printf("|%4d", count_item++);
		printf("|%d-%02d-%02d-%02d:%02d~%02d:%02d  ", pTime->year, pTime->month, pTime->day, pTime->hour_begin, pTime->min_begin, pTime->hour_end, pTime->min_end);//��ʱ����Ϣ��ӡ����
		if (i % 2 == 0) //������
			printf("|������%-15s\n", itemlist.pSItemList[i/2].szItemName);
		else 
			printf("|Ů����%-15s\n", itemlist.pSItemList[i / 2].szItemName);
	}

	////////д��doc�ļ�
	printf("\n\n�Ƿ���������᣿");
	printf("\n1.ȷ��");
	printf("\n2.ȡ��");
	int nChoice_CreateProgram = 0;
	while (!(cin >> nChoice_CreateProgram)) {
		cin.clear();
		while (cin.get() != '\n')
			continue;
		printf("���������룺");
	}
	switch (nChoice_CreateProgram)
	{
	case 1: {
		FILE* pProgram;
		char fileName[100] = "��";
		strncat_s(fileName,100, szNumber, strlen(szNumber));
		strncat_s(fileName,100, "��", sizeof("��"));
		strncat_s(fileName,100, szSchoolName, strlen(szSchoolName));
		strncat_s(fileName,100, "У�˻������.doc", sizeof("У�˻������.doc"));
		char headName[100];
		strncpy_s(headName,100, fileName,strlen(fileName)-4);//��������
		errno_t err = fopen_s(&pProgram, fileName, "w");
		if (err != 0) {
			printf("%s�ļ���ʧ��", fileName);
			exit(0);
		}
		fwrite(headName, strlen(headName)+1, 1, pProgram);//д�����
		fputc('\n', pProgram);
		fputc('\n', pProgram);

		fprintf(pProgram, "���췽��");
		fwrite(szSponsor, strlen(szSponsor) + 1, 1, pProgram);
		fputc('\n', pProgram);	
		fputc('\n', pProgram);

		fprintf(pProgram, "�ٰ췽��");
		fwrite(szOrganize, strlen(szOrganize) + 1, 1, pProgram);
		fputc('\n', pProgram);
		fputc('\n', pProgram);

		fprintf(pProgram, "�ص㣺");
		fwrite(szPlace, strlen(szPlace) + 1, 1, pProgram);
		fputc('\n', pProgram);
		fputc('\n', pProgram);
		fputc('\n', pProgram);

		fprintf(pProgram, "���������");
		fputc('\n', pProgram);
		int count_academy = 0;
		for (int i = 1; i <= 9; i++) {
			fprintAcademyAthlete(pProgram, athletelist, (Academy)i, count_academy);
		}

		fputc('\n', pProgram);
		fputc('\n', pProgram);
		fprintf(pProgram, "��������");
		fputc('\n', pProgram);
		fputc('\n', pProgram);
		fprintf(pProgram,"|���");
		fprintf(pProgram,"%-25s", "|��Ŀʱ��");
		fprintf(pProgram,"%-22s\n", "|��Ŀ����");
		int count_itemtime = 1;
		for (int i = 0; i < 2 * itemlist.nListLength; i++){
			STime* pTime = &itemTimeList.times[i];
			fprintf(pProgram,"__________________________________________________\n");
			fprintf(pProgram,"|%4d", count_itemtime++);
			fprintf(pProgram,"|%d-%02d-%02d-%02d:%02d~%02d:%02d  ", pTime->year, pTime->month, pTime->day, pTime->hour_begin, pTime->min_begin, pTime->hour_end, pTime->min_end);//��ʱ����Ϣ��ӡ����
			if (i % 2 == 0) //������
				fprintf(pProgram,"|������%-15s\n", itemlist.pSItemList[i / 2].szItemName);
			else
				fprintf(pProgram,"|Ů����%-15s\n", itemlist.pSItemList[i / 2].szItemName);
		}

		fputc('\n', pProgram);
		fputc('\n', pProgram);
		fprintf(pProgram, "��Ŀ����");	
		fputc('\n', pProgram);
		for (int i = 0; i < itemgrouplist.nListLength; i++) {
			SItemGroup* itemgroup = itemgrouplist.pSItemGroupList + i;
			if (itemgroup->nMaleGroupNumber != 0) {
				fprintf(pProgram, "\n\n%s ������\n", itemgroup->szItemName);
				for (int j = 0; j < itemgroup->nMaleGroupNumber; j++) {//��nMaleGroupNumber����
					fprintf(pProgram, " \n ��%d��\n", j + 1);
					if (itemgroup->SPORTTYPE_SportType == SPORTTYPE_TRACK) {
						for (int k = 0; k < itemgroup->SMaleGroups[j].nListLength; k++) {//ÿ����nListLength����
							ChineseNumber number = ChineseNumber(k + 1);
							switch (number)
							{
							case һ:
								fprintf(pProgram, "һ\t\t");
								break;
							case ��:
								fprintf(pProgram, "��\t\t");
								break;
							case ��:
								fprintf(pProgram, "��\t\t");
								break;
							case ��:
								fprintf(pProgram, "��\t\t");
								break;
							case ��:
								fprintf(pProgram, "��\t\t");
								break;
							case ��:
								fprintf(pProgram, "��\t\t");
								break;
							case ��:
								fprintf(pProgram, "��\t\t");
								break;
							case ��:
								fprintf(pProgram, "��\t\t");
								break;
							default:
								break;
							}
						}
						fputc('\n', pProgram);
					}//if(sporttype)
					for (int k = 0; k < itemgroup->SMaleGroups[j].nListLength; k++) {//ÿ����nListLength����
						fprintf(pProgram, "%s\t", itemgroup->SMaleGroups[j].pSAthleteList[k].szAthleteName);
					}
					fputc('\n', pProgram);
				}//for(j)
			}//if(gorup!=0)

			if (itemgroup->nFemaleGroupNumber != 0) {
				fprintf(pProgram, "\n\n%s Ů����\n", itemgroup->szItemName);
				for (int j = 0; j < itemgroup->nFemaleGroupNumber; j++) {
					fprintf(pProgram, "\n  ��%d��\n", j + 1);
					if (itemgroup->SPORTTYPE_SportType == SPORTTYPE_TRACK) {
						for (int k = 0; k < itemgroup->SMaleGroups[j].nListLength; k++) {//ÿ����nListLength����
							ChineseNumber number = ChineseNumber(k + 1);
							switch (number)
							{
							case һ:
								fprintf(pProgram, "һ\t\t");
								break;
							case ��:
								fprintf(pProgram, "��\t\t");
								break;
							case ��:
								fprintf(pProgram, "��\t\t");
								break;
							case ��:
								fprintf(pProgram, "��\t\t");
								break;
							case ��:
								fprintf(pProgram, "��\t\t");
								break;
							case ��:
								fprintf(pProgram, "��\t\t");
								break;
							case ��:
								fprintf(pProgram, "��\t\t");
								break;
							case ��:
								fprintf(pProgram, "��\t\t");
								break;
							default:
								break;
							}
						}
						fputc('\n', pProgram);
					}//if(sporttype)
					for (int k = 0; k < itemgroup->SMaleGroups[j].nListLength; k++) {//ÿ����nListLength����
						fprintf(pProgram, "%s\t", itemgroup->SMaleGroups[j].pSAthleteList[k].szAthleteName);
					}
					fputc('\n', pProgram);
				}//for(j)
			}//if(gourp!=0)
		}


		fclose(pProgram);
		printf("\n��������ɳɹ���\n");

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

void fprintAcademyAthlete(FILE* pProgram ,SAthleteList& athletelist, Academy academy, int& count) {
	switch (academy)
	{
	case ֪����Ժ:
		fprintf(pProgram, "֪����Ժ");
		fputc('\n', pProgram);
		break;
	case ˼Դ��Ժ:
		fprintf(pProgram, "˼Դ��Ժ");
		fputc('\n', pProgram);
		break;
	case ������Ժ:
		fprintf(pProgram, "������Ժ");
		fputc('\n', pProgram);
		break;
	case ��һ��Ժ:
		fprintf(pProgram, "��һ��Ժ");
		fputc('\n', pProgram);
		break;
	case ������Ժ:
		fprintf(pProgram, "������Ժ");
		fputc('\n', pProgram);
		break;
	case ��Զ��Ժ:
		fprintf(pProgram, "��Զ��Ժ");
		fputc('\n', pProgram);
		break;
	case ������Ժ:
		fprintf(pProgram, "������Ժ");
		fputc('\n', pProgram);
		break;
	case ��ܰ��Ժ:
		fprintf(pProgram, "��ܰ��Ժ");
		fputc('\n', pProgram);
		break;
	case �о���Ժ:
		fprintf(pProgram, "�о���Ժ");
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
			_itoa_s(count, szCount, 10);//ת�����ַ�������10���ƣ�
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
