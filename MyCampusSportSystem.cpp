#include"sportitem.h"
#include"athlete.h"
#include"itemgroup.h"
#include"program.h"
#include"login.h"

#include<conio.h>
#include<Windows.h>
#include<iostream>
#include<ctime>
#include<fstream>
#include<sstream>

using namespace std;

bool flag_setting_password = true;//若设置了密码该值为1。否则为0

char szTitle[100] = {};//使用单位名称


void menu_item() {

	/*printf("\n\t1.增加项目\n");
	printf("\n\t2.删除项目\n");
	printf("\n\t3.修改项目\n");
	printf("\n\t4.查看项目的报名人员\n");
	printf("\n\t5.查看项目的分组名单\n");
	printf("\n\t6.保存并返回主菜单\n");
	printf("\n\t你的选择：");*/

	printf("\t**************************************************************************************************************************************\n");
	printf("\t**1.增加项目\t\t2.删除项目\t\t3.修改项目\t\t4.项目报名人员\t\t5.项目分组名单\t\t6.返回主菜单**");
	printf("\n\t**************************************************************************************************************************************\n");
	printf("\t你的选择是：");
}

void menu_athlete() {
	//printf("\n\t1.增加运动员\n");
	//printf("\n\t2.删除运动员\n");
	//printf("\n\t3.修改运动员\n");
	//printf("\n\t4.查询\n");
	//printf("\n\t5.保存并返回主菜单\n");
	//printf("\n\t你的选择：");
	printf("\n\t**********************************************************************************************************\n");
	printf("\t**1.增加运动员\t\t2.删除运动员\t\t3.修改运动员\t\t4.查询\t\t5.返回主菜单\t**");
	printf("\n\t**********************************************************************************************************\n");
	printf("\t你的选择是：");
}

void menu_inputResult() {
	printf("\n\t1.输入成绩\n");
	printf("\n\t2.查看排名\n");
	printf("\n\t你的选择：");
}

void menu_System() {
	printf("\n\t1.数据备份\n");
	printf("\n\t2.数据恢复\n");
	printf("\n\t3.设置密码\n");
	printf("\n\t4.修改密码\n");
	printf("\n\t5.修改封面\n");
	printf("\n\t6.返回主菜单\n");
	printf("\n\t你的选择：");
}

void menu_System_with_password() {
	printf("\n\t1.数据备份\n");
	printf("\n\t2.数据恢复\n");
	printf("\n\t3.删除密码\n");
	printf("\n\t4.修改密码\n");	
	printf("\n\t5.修改封面\n");
	printf("\n\t6.返回主菜单\n");
	printf("\n\t你的选择：");
}

void main_menu() {
	printf("\n\t1.项目管理\n");
	printf("\n\t2.运动员管理\n");
	printf("\n\t3.生成秩序册\n");
	printf("\n\t4.成绩管理\n");
	printf("\n\t5.系统设置\n");
	printf("\n\t6.注销\n");
	printf("\n\t你的选择：");
	
}

void SetConsole() {//设置控制台属性
	const TCHAR* title = TEXT("校运会管理系统");
	SetConsoleTitle(title);
}

void Init() {//设置一些必须的参数
	SetConsole();
	FILE* pPassword;
	errno_t err = fopen_s(&pPassword, "password", "r");
	if (err != 0) {
		printf("password文件无法打开");
		return;
	}
	if (pPassword) {
		fread(&flag_setting_password, sizeof(flag_setting_password), 1, pPassword);
		fclose(pPassword);
	}
	if (flag_setting_password) {
		welcome_interface_with_password(szTitle);
	}
	else {
		welcome_interface(szTitle);
	}

}

int main() {
logout:	Init();
	while (true) {
		system("cls");
		main_menu();
		int nChoice_Menu = 0;
		scanf_s("%d", &nChoice_Menu);
		switch (nChoice_Menu)
		{
		case 1: {
			//添加项目
			SSportItem item;
			SItemList list;
			SAthleteList athletelist;

			InitAthleteList(athletelist);
			ReadAthleteListFile(athletelist);

			InitItemList(list);
			ReadItemListFile(list);

			while (true) {
				system("cls");
				//DisplayItemList(list);
				DisplayItemListWithNumber(list);
				printf("\n\n");
				menu_item();
				int nChoice = 0;
				scanf_s("%d", &nChoice);
				switch (nChoice)
				{
				case 1://添加项目
					CreateItem(item);
					AddItem(list, item);
					break;
				case 2: {//删除项目
					char szIDorName[20];
					printf("请输入需要删除的项目的编号或者名称:");
					scanf_s("%s", szIDorName, 20);
					DeleteItem(list, szIDorName);
					AthleteFILEUpdate_ItemDelete(szIDorName);//同步运动员信息文件
					break;
				}
				case 3: {//修改项目
					char szIDorName[20];
					printf("请输入需要修改的项目的编号或者名称:");
					scanf_s("%s", szIDorName, 20);
					ModifiItem(list, szIDorName);
					int nPos = LocateItem(list, szIDorName);
					SSportItem item_temp = list.pSItemList[nPos];
					AthleteFIlEUpdate_ItemModify(item_temp);
					break;
				}
				case 4: {//查询项目名单
					char szIDorName[20];
					SAthleteList SItemList;
					InitAthleteList(SItemList);

					printf("请输入需要查询报名名单的项目编号或者名称:");
					scanf_s("%s", szIDorName, 20);
					int nPos = LocateItem(list, szIDorName);

					CreateItemAthleteList(athletelist, SItemList, szIDorName);
					printf("\n\n报名 %s 项目名单：\n", list.pSItemList[nPos].szItemName);
					DisplayAthleteListInfo(SItemList);
					break;
				}
				case 5: {//查询项目分组
					char szIDorName[20];
					SAthleteList SItemList;
					InitAthleteList(SItemList);

					printf("请输入需要查看分组的项目编号或者名称:");
					scanf_s("%s", szIDorName, 20);
					int nPos = LocateItem(list, szIDorName);//分组表和项目表是一一对应的。
					SGroupList grouplist;
					ConnectItemList(grouplist, list);
					ConnectAthleteList(grouplist, athletelist);
					DisplayItemGroup(grouplist.pSItemGroupList[nPos]);

					DestroyAthleteList(SItemList);
					DestroyItemGroupList(grouplist);
					break;
				}
				default:
					break;
				}//switch(nChoice)
				if (nChoice == 6)
					break;
				getchar();
				printf("\n请按回车键继续");
				getchar();
			}//while(true)
			WriteItemListFile(list);
			DestroyAthleteList(athletelist);
			DestroyItemList(list);
			break;
		}
		case 2: {
			//运动员相关
			SAthlete athlete;
			SAthleteList athletelist;
			InitAthleteList(athletelist);
			ReadAthleteListFile(athletelist);
			int nGroupNumber = 1;
			int nMaxGroupNumber = 0;
			while (true) {
				system("cls");
				/*DisplayAthleteListInfo(athletelist);*/
				if (athletelist.nListLength % 10 != 0)
					nMaxGroupNumber = athletelist.nListLength / 10 + 1;
				else
					nMaxGroupNumber = athletelist.nListLength / 10;
				DisplayAthleteListdepartInfo(athletelist, nGroupNumber);
				printf("\n\t\t\t\t\t\t\t6.上一页\t第%d/%d页\t\t7.下一页",nGroupNumber,nMaxGroupNumber);
				printf("\n");
				menu_athlete();
				int nChoice_Athlete = 0;
				scanf_s("%d", &nChoice_Athlete);
				switch (nChoice_Athlete)
				{
				case 1:
					printf("\n\t请输入运动员信息\n\n");
					InputAthleteInfo(athlete);
					AddAthlete(athletelist, athlete);
					break;
				case 2: {
					char szIDorName[20];
					printf("\n\t请输入要删除的运动员的名字或者学号:");
					scanf_s("%s", szIDorName, 20);
					DeleteAthlete(athletelist, szIDorName);
					break;
				}
				case 3: {
					char szIDorName[20];
					printf("\n\t请输入需要修改的运动员你的名字或者学号:");
					scanf_s("%s", szIDorName, 20);
					ModifiAthlete(athletelist, szIDorName);
					break;
				}
				case 4: {
					printf("\n\n\t你查询的依据：\n");
					printf("\n\t1.根据参赛单位查询\n");
					printf("\n\t2.根据学号查询\n");
					printf("\n\t3.根据姓名查询\n");
					printf("\n\t你的选择是：");
					int nChoice_inquire = 0;
					while (!(cin >> nChoice_inquire)) {
						cin.clear();
						while (cin.get() != '\n')
							continue;
						cout << "\n输入错误，请重新输入：";
					}
					switch (nChoice_inquire)
					{
					case 1: {
						printf("\n\n1.知行书院\n2.思源书院\n3.弘毅书院\n4.敬一书院\n5.至诚书院\n6.修远书院\n7.明德书院\n8.德馨书院\n9.研究生院\n输入需要查询的参赛单位：");
						int nChoice_academy = 0;
						while (nChoice_academy < 1 || nChoice_academy>9) {
							while (!(cin >> nChoice_academy)) {
								cin.clear();
								while (cin.get() != '\n')
									continue;
								cout << "\n输入错误，请重新输入：";
							}
							if (nChoice_academy < 1 || nChoice_academy>9) {
								printf("无此参赛单位;\n");
								printf("请重新输入：");
							}
						}
						SAthleteList academyAthleteList;
						InitAthleteList(academyAthleteList);
						AcademyGroup(academyAthleteList, nChoice_academy);
						system("cls");
						switch (nChoice_academy)
						{
						case 1:
							printf("\t以下是 知行书院 的参赛名单\n");
							break;
						case 2:
							printf("\t以下是 思源书院 的参赛名单\n");
							break;
						case 3:
							printf("\t以下是 弘毅书院 的参赛名单\n");
							break;
						case 4:
							printf("\t以下是 敬一书院 的参赛名单\n");
							break;
						case 5:
							printf("\t以下是 至诚书院 的参赛名单\n");
							break;
						case 6:
							printf("\t以下是 修远书院 的参赛名单\n");
							break;
						case 7:
							printf("\t以下是 明德书院 的参赛名单\n");
							break;
						case 8:
							printf("\t以下是 德馨书院 的参赛名单\n");
							break;
						case 9:
							printf("\t以下是 研究生院 的参赛名单\n");
							break;
						default:
							break;
						}
						DisplayAthleteListInfo(academyAthleteList);
						DestroyAthleteList(academyAthleteList);
						break;
					}
					case 2: {
						printf("\n\n请输入学号：");
						char szAthleteID[20];
						scanf_s("%s",szAthleteID,20);
						int nPos_ID = LocateAthlete(athletelist, szAthleteID);
						if (nPos_ID != -1) {
							printf("\t|%-15s", "学号");
							printf("|%-10s", "姓名");
							printf("%-7s", "|性别");
							printf("|书院\t\t");
							printf("%-21s", "|项目一");
							printf("%-7s", "|成绩");
							printf("%-21s", "|项目二");
							printf("%-6s", "|成绩");
							printf("%-21s", "|项目三");
							printf("%-6s", "|成绩");
							printf("\n");
							printf("\t________________________________________________________________________________________________________________________________________\n\t");
							DisplayAthleteInfo(athletelist.pSAthleteList[nPos_ID]);
						}
						else {
							printf("\n无此人！\n");
						}
						break;
					}
					case 3: {
						printf("\n\n请输入姓名：");
						char szAthleteName[20];
						scanf_s("%s", szAthleteName, 20);
						int nPos_ID = LocateAthlete(athletelist, szAthleteName);
						if (nPos_ID != -1) {
							printf("\t|%-15s", "学号");
							printf("|%-10s", "姓名");
							printf("%-7s", "|性别");
							printf("|书院\t\t");
							printf("%-21s", "|项目一");
							printf("%-7s", "|成绩");
							printf("%-21s", "|项目二");
							printf("%-6s", "|成绩");
							printf("%-21s", "|项目三");
							printf("%-6s", "|成绩");
							printf("\n");
							printf("\t________________________________________________________________________________________________________________________________________\n\t");
							DisplayAthleteInfo(athletelist.pSAthleteList[nPos_ID]);
						}
						else {
							printf("\n无此人！\n");
						}
						break;
					}
					default:
						break;
					}//switch(nChoice_inquire)
					break;
				}
				case 5:
					break;
				case 6:
					if (nGroupNumber != 1) {
						nGroupNumber--;
					}
					break;
				case 7:
					if (nGroupNumber != nMaxGroupNumber) {
						nGroupNumber++;
					}
					break;
				default:
					break;
				}
				if (nChoice_Athlete == 5) {
					break;
				}
				getchar();
				printf("\n输入任意键继续...");
				getchar();
			}//while(true)
			WriteAthleteListFile(athletelist);
			DestroyAthleteList(athletelist);
			break;
		}
		case 3: {
			system("cls");
			InputBaseInfo();
			break;
		}
		case 4: {
			//录入成绩相关操作
			printf("\n");
			menu_inputResult();
			int nChoice_inputResult = 0;
			while (!(cin >> nChoice_inputResult)) {
				cin.clear();
				while (cin.get() != '\n')
					continue;
				printf("\n\t输入错误，请重新输入：");
			}
			switch (nChoice_inputResult)
			{
			case 1: {//输入成绩
				system("cls");
				SItemList itemlist;
				InitItemList(itemlist);
				ReadItemListFile(itemlist);
				DisplayItemList(itemlist);
				printf("\n\n\t请输入你需要录入成绩的项目ID或者名称：");
				char szIDorName[20];
				scanf_s("%s", szIDorName, 20);
				system("cls");
				InputResult(szIDorName);
				DestroyItemList(itemlist);
				break;
			}
			case 2: {//查看排名
				system("cls");
				SItemList itemlist;
				InitItemList(itemlist);
				ReadItemListFile(itemlist);
				DisplayItemList(itemlist);
				printf("\n\n\t请输入你需要查排名的项目ID或者名称：");
				char szIDorName[20];
				scanf_s("%s", szIDorName, 20);
				SAthleteList athleteslist;
				InitAthleteList(athleteslist);
				ReadAthleteListFile(athleteslist);
				SGroupList groupslist;
				ConnectItemList(groupslist,itemlist);
				ConnectAthleteList(groupslist, athleteslist);
				int nPos_item = LocateItem(itemlist, szIDorName);
				if (nPos_item != -1) {
					if (RankItemGroupAthleteList(groupslist.pSItemGroupList[nPos_item]) == 1) {
						printf("\t项目 %s 的排名情况：\n\n", groupslist.pSItemGroupList[nPos_item].szItemName);
						printf("\t男子组：\n");
						DisplayAthleteListInfo(groupslist.pSItemGroupList[nPos_item].SMaleAthleteList);
						printf("\n\t女子组：\n");
						DisplayAthleteListInfo(groupslist.pSItemGroupList[nPos_item].SFemaleAthleteList);
					}
				}
				else {
					printf("并无此项目");
				}
				DestroyAthleteList(athleteslist);
				DestroyItemList(itemlist);
			}
			default:
				break;
			}
			
			break;
		}
		case 5: {
			system("cls");
			int nChoice_System = 0;
			if (flag_setting_password) {//有无密码显示不同的系统菜单
				menu_System_with_password();
			}
			else {
				menu_System();
			}
			while (!(cin >> nChoice_System)) {
				cin.clear();
				while (cin.get() != '\n')
					continue;
				printf("请重新输入:");
			}
			switch (nChoice_System)
			{
			case 1: {
				fstream infile_athlete("athleteinfo.txt", ios::in);
				fstream outfile_athlete("athleteinfo_spare.txt", ios::out);
				if (!infile_athlete.is_open())
				{
					cout << "athleteinfo.txt文件打开失败..." << endl;
					return -1;
				}
				if (!outfile_athlete.is_open())
				{
					cout << "athleteinfo_spare.txt打开失败..." << endl;
					return -1;
				}
				outfile_athlete << infile_athlete.rdbuf();  //将infile流中的数据传入outfile流中
				infile_athlete.close();
				outfile_athlete.close();

				fstream infile_item("iteminfo.txt", ios::in);
				fstream outfile_item("iteminfo_spare.txt", ios::out);
				if (!infile_item.is_open())
				{
					cout << "iteninfo.txt文件打开失败..." << endl;
					return -1;
				}
				if (!outfile_item.is_open())
				{
					cout << "iteminfo_spare.txt打开失败..." << endl;
					return -1;
				}
				outfile_item << infile_item.rdbuf();  //将infile流中的数据传入outfile流中
				infile_item.close();
				outfile_item.close();
				printf("\n\n备份成功\n");
				break;
			}
			case 2: {
				fstream infile_athlete("athleteinfo_spare.txt", ios::in);
				fstream outfile_athlete("athleteinfo.txt", ios::out);
				if (!infile_athlete.is_open())
				{
					cout << "athleteinfo_spare.txt文件打开失败..." << endl;
					return -1;
				}
				if (!outfile_athlete.is_open())
				{
					cout << "athleteinfo.txt打开失败..." << endl;
					return -1;
				}
				outfile_athlete << infile_athlete.rdbuf();  //将infile流中的数据传入outfile流中
				infile_athlete.close();
				outfile_athlete.close();

				fstream infile_item("iteminfo_spare.txt", ios::in);
				fstream outfile_item("iteminfo.txt", ios::out);
				if (!infile_item.is_open())
				{
					cout << "iteninfo_spare.txt文件打开失败..." << endl;
					return -1;
				}
				if (!outfile_item.is_open())
				{
					cout << "iteminfo.txt打开失败..." << endl;
					return -1;
				}
				outfile_item << infile_item.rdbuf();  //将infile流中的数据传入outfile流中
				infile_item.close();
				outfile_item.close();
				printf("\n\n数据恢复成功\n");
				break;
			}
			case 3: {
				if (flag_setting_password) {//要删除密码,对应有密码的菜单
					printf("\n\n\t请输入密码:");
					char* password_temp = ReadPasswordfromFile();//正确的密码
					char password[100] = {};//全部初始化为空字符！
					GetPasssword(password,sizeof(password));
					if (strcmp(password, password_temp) == 0){//密码正确
						flag_setting_password = false;//删除密码
						printf("\n\n\t删除密码成功\n");
						DeletePassword();
					}
					else {
						printf("\n\n\t密码错误！无法删除密码\n");
					}
				}//if
				else {//对应没有密码的菜单，要设置密码
					printf("\n\n\t请输入密码:");
					char password[100] = {};//第一次输入密码
					GetPasssword(password,sizeof(password));
					printf("\n\n\t请再次输入:");
					char password_temp[100] = {};//第二次输入密码
					GetPasssword(password_temp,sizeof(password_temp));
					
					if (strcmp(password, password_temp) == 0) {
						flag_setting_password = true;
						printf("\n\n\t密码设置成功！\n");
						WritePasswordtoFile(password);
					}
					else 
						printf("\n\n\t两次密码不一致！\n");

				}//else(flag_password)
				break;
			}//case 
			case 4: {
				printf("\n\t请输入密码:");
				char password[100] = {};
				GetPasssword(password,sizeof(password));
				char *password_temp = ReadPasswordfromFile();//正确的密码
				char password_new[100] = {};//新的密码
				char password_new_temp[100] = {};//第二次输入新的密码
				if (strcmp(password, password_temp) == 0) {//密码正确
					printf("\n\n\t\t请输入新的密码：");
					GetPasssword(password_new,sizeof(password_new));
					printf("\n\n\t\t请再次输入新的密码：");
					GetPasssword(password_new_temp,sizeof(password_new_temp));
					if (strcmp(password_new, password_new_temp) == 0) {//修改成功
						WritePasswordtoFile(password_new);
						printf("\n\n\t密码修改成功\n");
					}
					else {
						printf("\n\n\t两次密码不相同\n");
					}
				}//if(密码正确)
				else {//密码不正确
					printf("\n\n\t密码不正确！\n");
				}

				break;
			}
			case 5: {
				printf("\n\n\t输入封面显示名称：");
				char coverName[100] = {};
				scanf_s("%s", coverName, 100);
				strncpy_s(szTitle, sizeof(szTitle), coverName, sizeof(coverName));
				printf("\n\t修改成功\n");
				break;
			}
			case 6: {

			}
			default:
				break;
			}
			
			break;
		}
		case 6: {
			system("cls");
			goto logout;//!!!第一次用goto。
			break;
		}
		default:
			break;
		}
		getchar();
		printf("\n请按回车键继续");
		getchar();
	}

	return 0;
}
