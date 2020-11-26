#include"grade.h"

void GradeMenu() {
	printf("\n\t**************************************************\n");
	printf("\t**1.输入成绩\t|2.查看排名\t|3.返回主菜单\t**");
	printf("\n\t**************************************************\n");
	printf("\t你的选择是：");
}

void GradeManagament() {
	//录入成绩相关操作
	while (true) {
		system("cls");
		printf("\n");
		GradeMenu();
		int nChoice_inputResult = 0;
		nChoice_inputResult = GetOption(1, 3);
		switch (nChoice_inputResult)
		{
		case 1: {//输入成绩
			system("cls");
			SAthleteList athletelist;
			InitAthleteList(athletelist);
			ReadAthleteListFile(athletelist);
			SItemList itemlist;
			InitItemList(itemlist);
			ReadItemListFile(itemlist);
			DisplayItemList(itemlist);
			Grouping(itemlist);
			printf("\n\t请输入你需要录入成绩的项目ID或者名称：");
			char szIDorName[25];
			GetString(szIDorName, sizeof(szIDorName));
			int nPos = LocateItem(itemlist, szIDorName);
			if (nPos == -1) {
				printf("不存在该项目");
				break;
			}
			else {
				SSportItem* item = &itemlist.pSItemList[nPos];
				if (item->GroupNumber == 0) {
					printf("\t该项目无人报名！\n");
					system("pause");
					break;
				}
				system("cls");
				int nGroup = DisplayGroupingPagination(*item,"请选择你要输入成绩的组数","选择这一组") - 1;
				system("cls");
				SAthleteList* SGroupN = item->ppAthleteGroup[nGroup];//第nGroup组运动员
				printf("\n\t请按以下顺序输入改组运动员在 \"%s\"第%d组 中的成绩：\n", item->szItemName, item->GroupNumber);
				printf("\t|%-15s", "学号");
				printf("|%-20s", "姓名");
				if (item->SPORTTYPE_itemtype == SPORTTYPE_FIELD)
					printf("|%-10s", "成绩(/m)");
				else
					printf("|%-10s", "成绩(/s)");
				//输入成绩

				for (int i = 0; i < SGroupN->nListLength; i++) {
					printf("\n\n\t|%-15s", SGroupN->pSAthleteList[i].szAthleteID);
					printf("|%-20s|", SGroupN->pSAthleteList[i].szAthleteName);
					double dResult;
					dResult = GetDouble();
					int nPos_AthleteItem = LocateAthleteItem(SGroupN->pSAthleteList[i], item->szItemID);//该项目在该名运动员报名项目中的位置
					SSportItem* athleteItem = &SGroupN->pSAthleteList[i].SAthleteItem[nPos_AthleteItem];//获得该分组中的项目
					int nPos_ItemAthlete = LocateAthlete(*item->pAthleteList, SGroupN->pSAthleteList[i].szAthleteID);//在项目报名表中该名运动员的位置
					SSportItem* itemAthleteitem = &item->pAthleteList->pSAthleteList[nPos_ItemAthlete].SAthleteItem[nPos_AthleteItem];
					itemAthleteitem->dResult = dResult;
					int nPos_Athlete = LocateAthlete(athletelist, SGroupN->pSAthleteList[i].szAthleteID);
					SSportItem* athleteItem_All = &athletelist.pSAthleteList[nPos_Athlete].SAthleteItem[nPos_AthleteItem];//将成绩也同步到运动员表中
					athleteItem->dResult = dResult;
					athleteItem_All->dResult = dResult;
				}

				system("cls");


				while (true) {//将刚刚输入的所有的成绩显示出来，让用户确定是否需要修改，或者保存文件

					//根据这个项目的成绩排序。
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
					printf("\n\t \"%s\"第%d组 中的成绩：\n", item->szItemName, item->GroupNumber);
					printf("\t|%-15s", "学号");
					printf("|%-10s", "姓名");
					printf("|%-20s", "项目名");
					printf("|%-10s\n", "成绩");
					for (int i = 0; i < SGroupN->nListLength; i++) {
						printf("\t|%-15s", SGroupN->pSAthleteList[i].szAthleteID);
						printf("|%-10s", SGroupN->pSAthleteList[i].szAthleteName);
						printf("|%-20s", item->szItemName);
						int nPos_AthleteItem = LocateAthleteItem(SGroupN->pSAthleteList[i], item->szItemID);
						printf("|%.2lf", SGroupN->pSAthleteList[i].SAthleteItem[nPos_AthleteItem].dResult);//输出成绩
						printf("\n\n");
					}
					printf("\n\n\t1.保存\n");
					printf("\t2.修改\n");
					printf("\t3.取消\n");
					printf("\t你的选择：");
					int nChoice = 0;
					nChoice = GetOption(1, 3);
					if (nChoice == 1) {
						WriteAthleteListFile(athletelist);//将运动员表写入文件中。
						WriteItemListFile(itemlist);
						printf("\n保存成功！\n");
						break;
					}
					else if(nChoice==2){
						printf("\n\t请输入需要修改成绩的ID或者名字:");
						char szAthleteIDorName[25];
						GetString(szAthleteIDorName, sizeof(szAthleteIDorName));
						int nPosAthlete = LocateAthlete(*SGroupN, szAthleteIDorName);//在分组表中的位置
						if (nPosAthlete == -1) {
							printf("\n\t该运动员不存在\n");
							continue;
						}
						SAthlete* athlete = &SGroupN->pSAthleteList[nPosAthlete];
						int nPosAthleteAll = LocateAthlete(athletelist, szAthleteIDorName);//在运动员总表中的位置
						if (nPosAthleteAll == -1) {
							printf("\n\t该运动员不存在\n");
							continue;
						}
						SAthlete* athleteAll = &athletelist.pSAthleteList[nPosAthleteAll];
						int nPosAthleteItem = LocateAthleteItem(*athlete, item->szItemID);
						printf("\n\n\t|%-15s", "学号");
						printf("|%-10s", "姓名");
						printf("|%-20s", "项目名");
						printf("|%-10s\n", "成绩");
						printf("\t|%-15s", SGroupN->pSAthleteList[nPosAthlete].szAthleteID);
						printf("|%-10s", SGroupN->pSAthleteList[nPosAthlete].szAthleteName);
						printf("|%-20s", item->szItemName);
						printf("|%.2lf", SGroupN->pSAthleteList[nPosAthlete].SAthleteItem[nPosAthleteItem].dResult);
						printf("\n%57s", "请输入修改后的成绩:");
						double dResult = 0;
						dResult = GetDouble();
						athlete->SAthleteItem[nPosAthleteItem].dResult = dResult;
						athleteAll->SAthleteItem[nPosAthleteItem].dResult = dResult;
					}
					else {//取消
						for (int i = 0; i < SGroupN->nListLength; i++) {//该分组中所有的成绩复原
							SAthlete* athlete = &SGroupN->pSAthleteList[i];//分组中的运动员
							int nPos_Item = LocateAthleteItem(*athlete, item->szItemID);//在运动员报名项目中的位置
							int nPos_Athlete = LocateAthlete(*item->pAthleteList, athlete->szAthleteID);///运动员在项目报名表中的位置
							int nPos_AllAthlete = LocateAthlete(athletelist, athlete->szAthleteID);//运动员在运动员总表中的位置
							athletelist.pSAthleteList[nPos_AllAthlete].SAthleteItem[nPos_Item].dResult = 0;//运动员总表复原
							item->pAthleteList->pSAthleteList[nPos_Athlete].SAthleteItem[nPos_Item].dResult = 0;//项目报名表复原
							SGroupN->pSAthleteList[i].SAthleteItem[nPos_Item].dResult = 0;//项目分组表复原
						}
						break;
					}
				}//while(true)
			}
			DestroyAthleteList(athletelist);
			DestroyItemList(itemlist);
			break;
		}//case 1
		case 2: {//查看排名
			system("cls");
			SItemList itemlist;
			InitItemList(itemlist);
			ReadItemListFile(itemlist);
			Grouping(itemlist);
			Ordering(itemlist);
			DisplayItemList(itemlist);
			printf("\n\t你需要查询的项目：");
			char szItemIDorName[25];
			GetString(szItemIDorName, sizeof(szItemIDorName));
			int nPos = LocateItem(itemlist, szItemIDorName);
			if (nPos == -1) {
				printf("没有该项目");
			}
			else {
				SSportItem* item = &itemlist.pSItemList[nPos];
				DisplayGroupingPagination(*item,"","返回");
			}
		}//case 2
		}
		if (nChoice_inputResult == 3) {
			break;
		}
	}
}