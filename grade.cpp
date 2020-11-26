#include"grade.h"

void GradeMenu() {
	printf("\n\t**************************************************\n");
	printf("\t**1.����ɼ�\t|2.�鿴����\t|3.�������˵�\t**");
	printf("\n\t**************************************************\n");
	printf("\t���ѡ���ǣ�");
}

void GradeManagament() {
	//¼��ɼ���ز���
	while (true) {
		system("cls");
		printf("\n");
		GradeMenu();
		int nChoice_inputResult = 0;
		nChoice_inputResult = GetOption(1, 3);
		switch (nChoice_inputResult)
		{
		case 1: {//����ɼ�
			system("cls");
			SAthleteList athletelist;
			InitAthleteList(athletelist);
			ReadAthleteListFile(athletelist);
			SItemList itemlist;
			InitItemList(itemlist);
			ReadItemListFile(itemlist);
			DisplayItemList(itemlist);
			Grouping(itemlist);
			printf("\n\t����������Ҫ¼��ɼ�����ĿID�������ƣ�");
			char szIDorName[25];
			GetString(szIDorName, sizeof(szIDorName));
			int nPos = LocateItem(itemlist, szIDorName);
			if (nPos == -1) {
				printf("�����ڸ���Ŀ");
				break;
			}
			else {
				SSportItem* item = &itemlist.pSItemList[nPos];
				if (item->GroupNumber == 0) {
					printf("\t����Ŀ���˱�����\n");
					system("pause");
					break;
				}
				system("cls");
				int nGroup = DisplayGroupingPagination(*item,"��ѡ����Ҫ����ɼ�������","ѡ����һ��") - 1;
				system("cls");
				SAthleteList* SGroupN = item->ppAthleteGroup[nGroup];//��nGroup���˶�Ա
				printf("\n\t�밴����˳����������˶�Ա�� \"%s\"��%d�� �еĳɼ���\n", item->szItemName, item->GroupNumber);
				printf("\t|%-15s", "ѧ��");
				printf("|%-20s", "����");
				if (item->SPORTTYPE_itemtype == SPORTTYPE_FIELD)
					printf("|%-10s", "�ɼ�(/m)");
				else
					printf("|%-10s", "�ɼ�(/s)");
				//����ɼ�

				for (int i = 0; i < SGroupN->nListLength; i++) {
					printf("\n\n\t|%-15s", SGroupN->pSAthleteList[i].szAthleteID);
					printf("|%-20s|", SGroupN->pSAthleteList[i].szAthleteName);
					double dResult;
					dResult = GetDouble();
					int nPos_AthleteItem = LocateAthleteItem(SGroupN->pSAthleteList[i], item->szItemID);//����Ŀ�ڸ����˶�Ա������Ŀ�е�λ��
					SSportItem* athleteItem = &SGroupN->pSAthleteList[i].SAthleteItem[nPos_AthleteItem];//��ø÷����е���Ŀ
					int nPos_ItemAthlete = LocateAthlete(*item->pAthleteList, SGroupN->pSAthleteList[i].szAthleteID);//����Ŀ�������и����˶�Ա��λ��
					SSportItem* itemAthleteitem = &item->pAthleteList->pSAthleteList[nPos_ItemAthlete].SAthleteItem[nPos_AthleteItem];
					itemAthleteitem->dResult = dResult;
					int nPos_Athlete = LocateAthlete(athletelist, SGroupN->pSAthleteList[i].szAthleteID);
					SSportItem* athleteItem_All = &athletelist.pSAthleteList[nPos_Athlete].SAthleteItem[nPos_AthleteItem];//���ɼ�Ҳͬ�����˶�Ա����
					athleteItem->dResult = dResult;
					athleteItem_All->dResult = dResult;
				}

				system("cls");


				while (true) {//���ո���������еĳɼ���ʾ���������û�ȷ���Ƿ���Ҫ�޸ģ����߱����ļ�

					//���������Ŀ�ĳɼ�����
					for (int i = 0; i < SGroupN->nListLength; i++) {
						for (int j = 0; j < SGroupN->nListLength - i - 1; j++) {
							int nPos1 = LocateAthleteItem(SGroupN->pSAthleteList[j], item->szItemID);
							int nPos2 = LocateAthleteItem(SGroupN->pSAthleteList[j + 1], item->szItemID);
							if (item->SPORTTYPE_itemtype == SPORTTYPE_TRACK) {
								if (SGroupN->pSAthleteList[j].SAthleteItem[nPos1].dResult > SGroupN->pSAthleteList[j + 1].SAthleteItem[nPos2].dResult) {
									SAthlete tmpAthlete;
									tmpAthlete = SGroupN->pSAthleteList[j];
									SGroupN->pSAthleteList[j] = SGroupN->pSAthleteList[j + 1];
									SGroupN->pSAthleteList[j + 1] = tmpAthlete;
								}
							}
							else if (item->SPORTTYPE_itemtype == SPORTTYPE_FIELD) {
								if (SGroupN->pSAthleteList[j].SAthleteItem[nPos1].dResult < SGroupN->pSAthleteList[j + 1].SAthleteItem[nPos2].dResult) {
									SAthlete tmpAthlete;
									tmpAthlete = SGroupN->pSAthleteList[j];
									SGroupN->pSAthleteList[j] = SGroupN->pSAthleteList[j + 1];
									SGroupN->pSAthleteList[j + 1] = tmpAthlete;
								}
							}
						}
					}
					////////////////////////
					system("cls");
					printf("\n\t \"%s\"��%d�� �еĳɼ���\n", item->szItemName, item->GroupNumber);
					printf("\t|%-15s", "ѧ��");
					printf("|%-10s", "����");
					printf("|%-20s", "��Ŀ��");
					printf("|%-10s\n", "�ɼ�");
					for (int i = 0; i < SGroupN->nListLength; i++) {
						printf("\t|%-15s", SGroupN->pSAthleteList[i].szAthleteID);
						printf("|%-10s", SGroupN->pSAthleteList[i].szAthleteName);
						printf("|%-20s", item->szItemName);
						int nPos_AthleteItem = LocateAthleteItem(SGroupN->pSAthleteList[i], item->szItemID);
						printf("|%.2lf", SGroupN->pSAthleteList[i].SAthleteItem[nPos_AthleteItem].dResult);//����ɼ�
						printf("\n\n");
					}
					printf("\n\n\t1.����\n");
					printf("\t2.�޸�\n");
					printf("\t3.ȡ��\n");
					printf("\t���ѡ��");
					int nChoice = 0;
					nChoice = GetOption(1, 3);
					if (nChoice == 1) {
						WriteAthleteListFile(athletelist);//���˶�Ա��д���ļ��С�
						WriteItemListFile(itemlist);
						printf("\n����ɹ���\n");
						break;
					}
					else if(nChoice==2){
						printf("\n\t��������Ҫ�޸ĳɼ���ID��������:");
						char szAthleteIDorName[25];
						GetString(szAthleteIDorName, sizeof(szAthleteIDorName));
						int nPosAthlete = LocateAthlete(*SGroupN, szAthleteIDorName);//�ڷ�����е�λ��
						if (nPosAthlete == -1) {
							printf("\n\t���˶�Ա������\n");
							continue;
						}
						SAthlete* athlete = &SGroupN->pSAthleteList[nPosAthlete];
						int nPosAthleteAll = LocateAthlete(athletelist, szAthleteIDorName);//���˶�Ա�ܱ��е�λ��
						if (nPosAthleteAll == -1) {
							printf("\n\t���˶�Ա������\n");
							continue;
						}
						SAthlete* athleteAll = &athletelist.pSAthleteList[nPosAthleteAll];
						int nPosAthleteItem = LocateAthleteItem(*athlete, item->szItemID);
						printf("\n\n\t|%-15s", "ѧ��");
						printf("|%-10s", "����");
						printf("|%-20s", "��Ŀ��");
						printf("|%-10s\n", "�ɼ�");
						printf("\t|%-15s", SGroupN->pSAthleteList[nPosAthlete].szAthleteID);
						printf("|%-10s", SGroupN->pSAthleteList[nPosAthlete].szAthleteName);
						printf("|%-20s", item->szItemName);
						printf("|%.2lf", SGroupN->pSAthleteList[nPosAthlete].SAthleteItem[nPosAthleteItem].dResult);
						printf("\n%57s", "�������޸ĺ�ĳɼ�:");
						double dResult = 0;
						dResult = GetDouble();
						athlete->SAthleteItem[nPosAthleteItem].dResult = dResult;
						athleteAll->SAthleteItem[nPosAthleteItem].dResult = dResult;
					}
					else {//ȡ��
						for (int i = 0; i < SGroupN->nListLength; i++) {//�÷��������еĳɼ���ԭ
							SAthlete* athlete = &SGroupN->pSAthleteList[i];//�����е��˶�Ա
							int nPos_Item = LocateAthleteItem(*athlete, item->szItemID);//���˶�Ա������Ŀ�е�λ��
							int nPos_Athlete = LocateAthlete(*item->pAthleteList, athlete->szAthleteID);///�˶�Ա����Ŀ�������е�λ��
							int nPos_AllAthlete = LocateAthlete(athletelist, athlete->szAthleteID);//�˶�Ա���˶�Ա�ܱ��е�λ��
							athletelist.pSAthleteList[nPos_AllAthlete].SAthleteItem[nPos_Item].dResult = 0;//�˶�Ա�ܱ�ԭ
							item->pAthleteList->pSAthleteList[nPos_Athlete].SAthleteItem[nPos_Item].dResult = 0;//��Ŀ������ԭ
							SGroupN->pSAthleteList[i].SAthleteItem[nPos_Item].dResult = 0;//��Ŀ�����ԭ
						}
						break;
					}
				}//while(true)
			}
			DestroyAthleteList(athletelist);
			DestroyItemList(itemlist);
			break;
		}//case 1
		case 2: {//�鿴����
			system("cls");
			SItemList itemlist;
			InitItemList(itemlist);
			ReadItemListFile(itemlist);
			Grouping(itemlist);
			Ordering(itemlist);
			DisplayItemList(itemlist);
			printf("\n\t����Ҫ��ѯ����Ŀ��");
			char szItemIDorName[25];
			GetString(szItemIDorName, sizeof(szItemIDorName));
			int nPos = LocateItem(itemlist, szItemIDorName);
			if (nPos == -1) {
				printf("û�и���Ŀ");
			}
			else {
				SSportItem* item = &itemlist.pSItemList[nPos];
				DisplayGroupingPagination(*item,"","����");
			}
		}//case 2
		}
		if (nChoice_inputResult == 3) {
			break;
		}
	}
}