#include"itemgroup.h"

#define TRACKNUMBER 8//����

void DisplayItemGroup(SItemGroup& SGroup) {
	printf("\n��Ŀ��Ϣ\n");
	printf("\t|%-10s", "��Ŀ���");
	printf("|%-20s","��Ŀ����");
	printf("|��Ŀ���\t\n");
	printf("\t|%-10s", SGroup.szItemID);
	printf("|%-20s", SGroup.szItemName);
	if (SGroup.SPORTTYPE_SportType == SPORTTYPE_TRACK)
		printf("|����\t");
	else if (SGroup.SPORTTYPE_SportType == SPORTTYPE_FIELD)
		printf("|����\t");
	if (SGroup.nMaleGroupNumber != 0) {
		printf("\n\n\t���ӷ������\n");
		for (int i = 1; i <= SGroup.nMaleGroupNumber; i++) {
			printf("\t��%d��", i);
			DisplayAthleteListInfo(SGroup.SMaleGroups[i - 1]);
			printf("\n\n");
		}
	}
	if (SGroup.nFemaleGroupNumber != 0) {
		printf("\n\n\tŮ����������\n");
		for (int i = 1; i <= SGroup.nFemaleGroupNumber; i++) {
			printf("\t��%d��", i);
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
		printf("�ڴ�����");
		exit(0);
	}

	int nLength = SGroups.nListLength;
	SItemGroup Group;
	for (int i = 0; i < nLength; i++) {
		strcpy_s(Group.szItemName,20, SItems.pSItemList[i].szItemName);//��Ŀ����
		strcpy_s(Group.szItemID, 20, SItems.pSItemList[i].szItemID);//��Ŀ���
		Group.SPORTTYPE_SportType = SItems.pSItemList[i].SPORTYPE_itemtype;//��Ŀ���
		Group.nFemaleGroupNumber = 0;
		Group.nMaleGroupNumber = 0;
		if (SGroups.nListSize != 0) {
			SGroups.pSItemGroupList[i] = Group;//ǰ�����ƣ�nListSize!=0
		}
	}
}

void ConnectAthleteList(SGroupList& SGroups, SAthleteList& SAthletes) {
	SAthleteList SItemAthleteList;//ĳ����Ŀ��������
	SAthleteList SFemaleAthleteList;//����ĳ����Ŀ��Ů������
	SAthleteList SMaleAthleteList;//����ĳ����Ŀ����������

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
		if (SGroups.pSItemGroupList[i].SPORTTYPE_SportType == SPORTTYPE_TRACK) {//��������Ŀ�Ǿ���,������������
			SGroups.pSItemGroupList[i].nFemaleGroupNumber = ceil(double(SFemaleAthleteList.nListLength) / TRACKNUMBER);//ȷ����������
			SGroups.pSItemGroupList[i].nMaleGroupNumber = ceil(double(SMaleAthleteList.nListLength) / TRACKNUMBER);
			GroupingAthlete(SFemaleAthleteList, SMaleAthleteList, SGroups.pSItemGroupList[i]);//��������
		}
		else if (SGroups.pSItemGroupList[i].SPORTTYPE_SportType == SPORTTYPE_FIELD) {//��������Ŀ��������ֱ�Ӿ�һ��
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
			for (int j = 0; j < SFemaleAthleteList.nListLength; j++) {//�����е�Ů���˶�Ա�ŵ�һ������
				AddAthlete(SGroups.pSItemGroupList[i].SFemaleGroups[0], SFemaleAthleteList.pSAthleteList[j]);
			}
			for (int j = 0; j < SMaleAthleteList.nListLength; j++) {//�����е������˶�Ա�ŵ�һ������
				AddAthlete(SGroups.pSItemGroupList[i].SMaleGroups[0], SMaleAthleteList.pSAthleteList[j]);
			}

		}
		else {//���������û�ж��������ʱ��ͳ�����
			printf("%s ��Ŀ����",SGroups.pSItemGroupList[i].szItemName);
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

	if (GroupNumber_Female == 0 && GroupNumber_Male == 0)//�������Ŀ���˱�������ֱ�ӷ�����������
		return;

	int nOffset = -1;
	int nAcademy[ACADEMYNUMBER] = {0};//��һ��Ԫ�ر�ʾ�����˶�Ա����

	SAthleteList STempList;
	InitAthleteList(STempList);

	for (int i = 0; i < GroupNumber_Female; i++) {//�ȳ�ʼ������������˶�Ա����
		InitAthleteList(ItemGroup.SFemaleGroups[i]);
	}
	for (int i = 0; i < GroupNumber_Male; i++) {
		InitAthleteList(ItemGroup.SMaleGroups[i]);
	}

	if (GroupNumber_Female != 0) {
		////����Ů�ӷ���
		for (int i = 0; i < SFemaleAthleteList.nListLength; i++) {//����
			int nIndex = (int)SFemaleAthleteList.pSAthleteList[i].academy;
			nAcademy[nIndex + nOffset]++;
			AddAthlete(STempList, SFemaleAthleteList.pSAthleteList[i]);//STempList��SFemaleAthleteList�ĸ���
		}

		int nDiv = SFemaleAthleteList.nListLength / GroupNumber_Female;
		int nMod = SFemaleAthleteList.nListLength % GroupNumber_Female;
		int i = 0;//Ů����ĵ�i��
		int nIndex = 0;

		while (STempList.nListLength > 0 && i < GroupNumber_Female) {
			while (nAcademy[nIndex] == 0) {//ѡ��ĳ����Ժ���ˣ�����ѡ
				if (nIndex == ACADEMYNUMBER - 1)
					nIndex = 0;
				else
					nIndex++;
			}
			nAcademy[nIndex]--;
			int nAcademyIndex = nIndex - nOffset;//Ҫ�����ΪnAcademyIndex����Ժ���˶�Ա���з���

			if (nIndex == ACADEMYNUMBER - 1)
				nIndex = 0;
			else
				nIndex++;

			int nPos = LocateAthleteAcademy(STempList, nAcademyIndex);//�����ѭ��ȷ���˲�������Ҳ�����״��
			AddAthlete(ItemGroup.SFemaleGroups[i], STempList.pSAthleteList[nPos]);
			DeleteAthlete(STempList, STempList.pSAthleteList[nPos].szAthleteID);//������˶�Աɾ����
			if (i < nMod && ItemGroup.SFemaleGroups[i].nListLength == nDiv + 1) {
				i++;
			}
			else if (i < GroupNumber_Female && i >= nMod && ItemGroup.SFemaleGroups[i].nListLength == nDiv) {
				i++;
			}//else
		}//while()
	}//if(GroupNumber_Female!=0)
	
	if (GroupNumber_Male != 0) {
		////�������ӷ���
		for (int i = 0; i < ACADEMYNUMBER; i++) {//ȷ������ȫ��Ԫ��Ϊ0
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
		printf("�޴���Ŀ\n");
		return;
	}
	else {//�д���Ŀ
		itemgroup = &grouplist.pSItemGroupList[nPosofItem];
		SAthleteList* pGroupathletelist;
		DisplayItemGroup(*itemgroup);
		printf("\n����Ҫ����ɼ������ǣ�\n");
		printf("1.������\t2.Ů���飺");
		int nChoice_gender = 1;
		do {
			scanf_s("%d", &nChoice_gender);
			if (nChoice_gender < 1 || nChoice_gender>2)
				printf("ѡ��������������룺");
		} while (nChoice_gender < 1 || nChoice_gender>2);

		if (itemgroup->nFemaleGroupNumber == 0 && nChoice_gender == 2) {//����ĿŮ����û�ˣ��˳�������ɼ�
			printf("����Ŀ���˱���\n");
			return;
		}
		if (itemgroup->nMaleGroupNumber == 0 && nChoice_gender == 1) {//����Ŀ������û�ˣ��˳���������ɼ�
			printf("����Ŀ���˱���\n");
			return;
		}

		int nGroup_number = 1;
		if (itemgroup->SPORTTYPE_SportType == SPORTTYPE_TRACK && nChoice_gender==1) {//���Ӿ�����
			do {
				printf("����Ҫ�������������");
				scanf_s("%d", &nGroup_number);
				if (nGroup_number<1 || nGroup_number>itemgroup->nMaleGroupNumber)
					printf("ѡ��������������룺");
			} while (nGroup_number<1 || nGroup_number>itemgroup->nMaleGroupNumber);			
		}
		else if (itemgroup->SPORTTYPE_SportType == SPORTTYPE_TRACK && nChoice_gender == 2) {//Ů�Ӿ�����
			do {
				printf("����Ҫ�������������");
				scanf_s("%d", &nGroup_number);
				if (nGroup_number<1 || nGroup_number>itemgroup->nFemaleGroupNumber)
					printf("ѡ��������������룺");
			} while (nGroup_number<1 || nGroup_number>itemgroup->nFemaleGroupNumber);
		}

		system("cls");
		if (nChoice_gender == 1)
			pGroupathletelist = &itemgroup->SMaleGroups[nGroup_number - 1];
		else
			pGroupathletelist = &itemgroup->SFemaleGroups[nGroup_number - 1];
		DisplayAthleteListInfo(*pGroupathletelist);

		printf("\n\n\n�밴һ��˳����������˶�Ա�� \"%s\" �еĳɼ���\n", itemgroup->szItemName);
		printf("|%-15s","ѧ��");
		printf("|%-20s","����");
		if (itemgroup->SPORTTYPE_SportType == SPORTTYPE_FIELD)
			printf("|%-10s", "�ɼ�(/m)");
		else
			printf("|%-10s", "�ɼ�(/s)");

		for (int i = 0; i < pGroupathletelist->nListLength; i++) {//ֱ��д���˶�Ա����
			printf("\n\n|%-15s", pGroupathletelist->pSAthleteList[i].szAthleteID);
			printf("|%-20s|", pGroupathletelist->pSAthleteList[i].szAthleteName);
			int nPosAthlete = LocateAthlete(athletelist, pGroupathletelist->pSAthleteList[i].szAthleteID);//�����˶�Ա���˶�Ա���е�λ��
			int nPosAthleteItem = LocateAthleteItem(athletelist.pSAthleteList[nPosAthlete], itemgroup->szItemID);//����Ŀ�ڸ��˶�Ա��������Ŀ�е�λ��
			double dResult;
			while (!(cin >> dResult)) {
				cin.clear();
				while (cin.get() != '\n')
					continue;
				printf("%38s", "����������:");
			}
			athletelist.pSAthleteList[nPosAthlete].SAthleteItem[nPosAthleteItem].dResult = dResult;//�ɼ����뵽athletelist�б���
			pGroupathletelist->pSAthleteList[i].SAthleteItem[nPosAthleteItem].dResult = dResult;//�ɼ����뵽����������
		}


		while (true) {//���ո���������еĳɼ���ʾ���������û�ȷ���Ƿ���Ҫ�޸ģ����߱����ļ�
			system("cls");
			printf("\t|%-15s", "ѧ��");
			printf("|%-10s", "����");
			printf("|%-20s", "��Ŀ��");
			printf("|%-10s\n", "�ɼ�");
			for (int i = 0; i < pGroupathletelist->nListLength; i++) {
				printf("\t|%-15s", pGroupathletelist->pSAthleteList[i].szAthleteID);
				printf("|%-10s", pGroupathletelist->pSAthleteList[i].szAthleteName);
				printf("|%-20s", itemgroup->szItemName);
				int nPosAthlete = LocateAthlete(athletelist, pGroupathletelist->pSAthleteList[i].szAthleteID);//�����˶�Ա���˶�Ա���е�λ��
				int nPosAthleteItem = LocateAthleteItem(athletelist.pSAthleteList[nPosAthlete], itemgroup->szItemID);//����Ŀ�ڸ��˶�Ա��������Ŀ�е�λ��
				printf("|%.2lf", pGroupathletelist->pSAthleteList[i].SAthleteItem[nPosAthleteItem].dResult);//����ɼ�
				printf("\n\n");
			}
			printf("\n\n1.����\n");
			printf("2.�޸�\n");
			printf("���ѡ��");
			int nChoice = 0;
			while (!(cin >> nChoice)) {
				cin.clear();
				while (cin.get() != '\n')
					continue;
				printf("����������");
			}
			if (nChoice == 1) {
				WriteAthleteListFile(athletelist);//���˶�Ա��д���ļ��С�
				printf("\n����ɹ���\n");
				break;
			}
			else {
				printf("��������Ҫ�޸ĳɼ���ID:");
				char szAthleteID[20];
				scanf_s("%s", szAthleteID, 20);
				int i = LocateAthlete(*pGroupathletelist, szAthleteID);
				int nPosAthleteItem = LocateAthleteItem(pGroupathletelist->pSAthleteList[i], itemgroup->szItemID);
				printf("\n\n\t|%-15s", "ѧ��");
				printf("|%-10s", "����");
				printf("|%-20s", "��Ŀ��");
				printf("|%-10s\n", "�ɼ�");
				printf("\t|%-15s", pGroupathletelist->pSAthleteList[i].szAthleteID);
				printf("|%-10s", pGroupathletelist->pSAthleteList[i].szAthleteName);
				printf("|%-20s", itemgroup->szItemName);
				printf("|%.2lf", pGroupathletelist->pSAthleteList[i].SAthleteItem[nPosAthleteItem].dResult);//����ɼ�
				printf("\n%57s", "�������޸ĺ�ĳɼ�:");
				double dResult = 0;
				while (!(cin >> dResult)) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					printf("%57s", "����������:");
				}
				pGroupathletelist->pSAthleteList[i].SAthleteItem[nPosAthleteItem].dResult = dResult;
				int nPosAthlete = LocateAthlete(athletelist, szAthleteID);
				athletelist.pSAthleteList[nPosAthlete].SAthleteItem[nPosAthleteItem].dResult = dResult;//��athletelist�еĵĳɼ��޸ġ�
			}
		}//while(true)

	}//else(nPosition!=1);
	DestroyItemList(itemlist);
	DestroyAthleteList(athletelist);
	DestroyItemGroupList(grouplist);
}

void AcademyGroup(SAthleteList& athletelist, int nAcademy) {

	if (nAcademy < 1 || nAcademy>9) {
		printf("\n�޴˲�����λ\n");
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
	if (finish_input == 1) {//�����˶�Ա�ɼ��������
		//���Ů���������
		SAthleteList femaleList;
		InitAthleteList(femaleList);
		while (group.SFemaleAthleteList.nListLength > 0) {//���ɼ��Ӹߵ�������
			double dResult = 0;
			int nPos_athlete = 0;
  			for (int i = 0; i < group.SFemaleAthleteList.nListLength; i++) {//�ҵ��ɼ������Ǹ��˶�Աλ��
				int nPos_item = LocateAthleteItem(group.SFemaleAthleteList.pSAthleteList[i], group.szItemID);
				if (group.SFemaleAthleteList.pSAthleteList[i].SAthleteItem[nPos_item].dResult >= dResult) {
					nPos_athlete = i;
					dResult = group.SFemaleAthleteList.pSAthleteList[i].SAthleteItem[nPos_item].dResult;
				}
			}//for
			AddAthlete(femaleList, group.SFemaleAthleteList.pSAthleteList[nPos_athlete]);
			DeleteAthlete(group.SFemaleAthleteList, nPos_athlete);
		}//while
		if (group.SPORTTYPE_SportType == SPORTTYPE_FIELD) {//�����ɼ��Ӹߵ�������
			for (int i = 0; i < femaleList.nListLength; i++)
				AddAthlete(group.SFemaleAthleteList, femaleList.pSAthleteList[i]);
		}
		else {//�����ӵ͵�������
			for (int i = femaleList.nListLength - 1; i >= 0; i--)
				AddAthlete(group.SFemaleAthleteList, femaleList.pSAthleteList[i]);
		}
		DestroyAthleteList(femaleList);

		//��������������
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
		if (group.SPORTTYPE_SportType == SPORTTYPE_FIELD) {//�����ɼ��Ӹߵ�������
			for (int i = 0; i < maleList.nListLength; i++)
				AddAthlete(group.SMaleAthleteList, maleList.pSAthleteList[i]);
		}
		else {//�����ӵ͵�������
			for (int i = maleList.nListLength - 1; i >= 0; i--)
				AddAthlete(group.SMaleAthleteList, maleList.pSAthleteList[i]);
		}
		DestroyAthleteList(maleList);
		return 1;
	}//if(finish_input==1)
	else {
		if (finish_input == -1)
			printf("\n %s Ů���� �ɼ�δ������ɣ�\n", group.szItemName);
		else if (finish_input == 0)
			printf("\n %s ������ �ɼ�δ������ɣ�\n", group.szItemName);
		else if(finish_input==-2)
			printf("\n %s �������Ů���� �ɼ�δ������ɣ�\n", group.szItemName);
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
		printf("|����\t");
	else if (SItem.SPORTYPE_itemtype == SPORTTYPE_FIELD)
		printf("|����\t");

	printf("|%.2lf\t", SItem.dItemTime);
	printf("|%8d|\t", count);
	printf("\n");
}

void DisplayItemListWithNumber(SItemList& SList) {
	printf("\n\t__________________________________________________________\n");
	printf("\t|���      |����                |���\t|��ʱ\t|��������|\n");
	for (int i = 0; i < SList.nListLength; i++) {
		printf("\t__________________________________________________________\n");
		DisplayItemWithNumber(SList.pSItemList[i]);
	}
}