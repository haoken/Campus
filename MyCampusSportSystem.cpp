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

bool flag_setting_password = true;//�������������ֵΪ1������Ϊ0

char szTitle[100] = {};//ʹ�õ�λ����


void menu_item() {

	/*printf("\n\t1.������Ŀ\n");
	printf("\n\t2.ɾ����Ŀ\n");
	printf("\n\t3.�޸���Ŀ\n");
	printf("\n\t4.�鿴��Ŀ�ı�����Ա\n");
	printf("\n\t5.�鿴��Ŀ�ķ�������\n");
	printf("\n\t6.���沢�������˵�\n");
	printf("\n\t���ѡ��");*/

	printf("\t**************************************************************************************************************************************\n");
	printf("\t**1.������Ŀ\t\t2.ɾ����Ŀ\t\t3.�޸���Ŀ\t\t4.��Ŀ������Ա\t\t5.��Ŀ��������\t\t6.�������˵�**");
	printf("\n\t**************************************************************************************************************************************\n");
	printf("\t���ѡ���ǣ�");
}

void menu_athlete() {
	//printf("\n\t1.�����˶�Ա\n");
	//printf("\n\t2.ɾ���˶�Ա\n");
	//printf("\n\t3.�޸��˶�Ա\n");
	//printf("\n\t4.��ѯ\n");
	//printf("\n\t5.���沢�������˵�\n");
	//printf("\n\t���ѡ��");
	printf("\n\t**********************************************************************************************************\n");
	printf("\t**1.�����˶�Ա\t\t2.ɾ���˶�Ա\t\t3.�޸��˶�Ա\t\t4.��ѯ\t\t5.�������˵�\t**");
	printf("\n\t**********************************************************************************************************\n");
	printf("\t���ѡ���ǣ�");
}

void menu_inputResult() {
	printf("\n\t1.����ɼ�\n");
	printf("\n\t2.�鿴����\n");
	printf("\n\t���ѡ��");
}

void menu_System() {
	printf("\n\t1.���ݱ���\n");
	printf("\n\t2.���ݻָ�\n");
	printf("\n\t3.��������\n");
	printf("\n\t4.�޸�����\n");
	printf("\n\t5.�޸ķ���\n");
	printf("\n\t6.�������˵�\n");
	printf("\n\t���ѡ��");
}

void menu_System_with_password() {
	printf("\n\t1.���ݱ���\n");
	printf("\n\t2.���ݻָ�\n");
	printf("\n\t3.ɾ������\n");
	printf("\n\t4.�޸�����\n");	
	printf("\n\t5.�޸ķ���\n");
	printf("\n\t6.�������˵�\n");
	printf("\n\t���ѡ��");
}

void main_menu() {
	printf("\n\t1.��Ŀ����\n");
	printf("\n\t2.�˶�Ա����\n");
	printf("\n\t3.���������\n");
	printf("\n\t4.�ɼ�����\n");
	printf("\n\t5.ϵͳ����\n");
	printf("\n\t6.ע��\n");
	printf("\n\t���ѡ��");
	
}

void SetConsole() {//���ÿ���̨����
	const TCHAR* title = TEXT("У�˻����ϵͳ");
	SetConsoleTitle(title);
}

void Init() {//����һЩ����Ĳ���
	SetConsole();
	FILE* pPassword;
	errno_t err = fopen_s(&pPassword, "password", "r");
	if (err != 0) {
		printf("password�ļ��޷���");
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
			//�����Ŀ
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
				case 1://�����Ŀ
					CreateItem(item);
					AddItem(list, item);
					break;
				case 2: {//ɾ����Ŀ
					char szIDorName[20];
					printf("��������Ҫɾ������Ŀ�ı�Ż�������:");
					scanf_s("%s", szIDorName, 20);
					DeleteItem(list, szIDorName);
					AthleteFILEUpdate_ItemDelete(szIDorName);//ͬ���˶�Ա��Ϣ�ļ�
					break;
				}
				case 3: {//�޸���Ŀ
					char szIDorName[20];
					printf("��������Ҫ�޸ĵ���Ŀ�ı�Ż�������:");
					scanf_s("%s", szIDorName, 20);
					ModifiItem(list, szIDorName);
					int nPos = LocateItem(list, szIDorName);
					SSportItem item_temp = list.pSItemList[nPos];
					AthleteFIlEUpdate_ItemModify(item_temp);
					break;
				}
				case 4: {//��ѯ��Ŀ����
					char szIDorName[20];
					SAthleteList SItemList;
					InitAthleteList(SItemList);

					printf("��������Ҫ��ѯ������������Ŀ��Ż�������:");
					scanf_s("%s", szIDorName, 20);
					int nPos = LocateItem(list, szIDorName);

					CreateItemAthleteList(athletelist, SItemList, szIDorName);
					printf("\n\n���� %s ��Ŀ������\n", list.pSItemList[nPos].szItemName);
					DisplayAthleteListInfo(SItemList);
					break;
				}
				case 5: {//��ѯ��Ŀ����
					char szIDorName[20];
					SAthleteList SItemList;
					InitAthleteList(SItemList);

					printf("��������Ҫ�鿴�������Ŀ��Ż�������:");
					scanf_s("%s", szIDorName, 20);
					int nPos = LocateItem(list, szIDorName);//��������Ŀ����һһ��Ӧ�ġ�
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
				printf("\n�밴�س�������");
				getchar();
			}//while(true)
			WriteItemListFile(list);
			DestroyAthleteList(athletelist);
			DestroyItemList(list);
			break;
		}
		case 2: {
			//�˶�Ա���
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
				printf("\n\t\t\t\t\t\t\t6.��һҳ\t��%d/%dҳ\t\t7.��һҳ",nGroupNumber,nMaxGroupNumber);
				printf("\n");
				menu_athlete();
				int nChoice_Athlete = 0;
				scanf_s("%d", &nChoice_Athlete);
				switch (nChoice_Athlete)
				{
				case 1:
					printf("\n\t�������˶�Ա��Ϣ\n\n");
					InputAthleteInfo(athlete);
					AddAthlete(athletelist, athlete);
					break;
				case 2: {
					char szIDorName[20];
					printf("\n\t������Ҫɾ�����˶�Ա�����ֻ���ѧ��:");
					scanf_s("%s", szIDorName, 20);
					DeleteAthlete(athletelist, szIDorName);
					break;
				}
				case 3: {
					char szIDorName[20];
					printf("\n\t��������Ҫ�޸ĵ��˶�Ա������ֻ���ѧ��:");
					scanf_s("%s", szIDorName, 20);
					ModifiAthlete(athletelist, szIDorName);
					break;
				}
				case 4: {
					printf("\n\n\t���ѯ�����ݣ�\n");
					printf("\n\t1.���ݲ�����λ��ѯ\n");
					printf("\n\t2.����ѧ�Ų�ѯ\n");
					printf("\n\t3.����������ѯ\n");
					printf("\n\t���ѡ���ǣ�");
					int nChoice_inquire = 0;
					while (!(cin >> nChoice_inquire)) {
						cin.clear();
						while (cin.get() != '\n')
							continue;
						cout << "\n����������������룺";
					}
					switch (nChoice_inquire)
					{
					case 1: {
						printf("\n\n1.֪����Ժ\n2.˼Դ��Ժ\n3.������Ժ\n4.��һ��Ժ\n5.������Ժ\n6.��Զ��Ժ\n7.������Ժ\n8.��ܰ��Ժ\n9.�о���Ժ\n������Ҫ��ѯ�Ĳ�����λ��");
						int nChoice_academy = 0;
						while (nChoice_academy < 1 || nChoice_academy>9) {
							while (!(cin >> nChoice_academy)) {
								cin.clear();
								while (cin.get() != '\n')
									continue;
								cout << "\n����������������룺";
							}
							if (nChoice_academy < 1 || nChoice_academy>9) {
								printf("�޴˲�����λ;\n");
								printf("���������룺");
							}
						}
						SAthleteList academyAthleteList;
						InitAthleteList(academyAthleteList);
						AcademyGroup(academyAthleteList, nChoice_academy);
						system("cls");
						switch (nChoice_academy)
						{
						case 1:
							printf("\t������ ֪����Ժ �Ĳ�������\n");
							break;
						case 2:
							printf("\t������ ˼Դ��Ժ �Ĳ�������\n");
							break;
						case 3:
							printf("\t������ ������Ժ �Ĳ�������\n");
							break;
						case 4:
							printf("\t������ ��һ��Ժ �Ĳ�������\n");
							break;
						case 5:
							printf("\t������ ������Ժ �Ĳ�������\n");
							break;
						case 6:
							printf("\t������ ��Զ��Ժ �Ĳ�������\n");
							break;
						case 7:
							printf("\t������ ������Ժ �Ĳ�������\n");
							break;
						case 8:
							printf("\t������ ��ܰ��Ժ �Ĳ�������\n");
							break;
						case 9:
							printf("\t������ �о���Ժ �Ĳ�������\n");
							break;
						default:
							break;
						}
						DisplayAthleteListInfo(academyAthleteList);
						DestroyAthleteList(academyAthleteList);
						break;
					}
					case 2: {
						printf("\n\n������ѧ�ţ�");
						char szAthleteID[20];
						scanf_s("%s",szAthleteID,20);
						int nPos_ID = LocateAthlete(athletelist, szAthleteID);
						if (nPos_ID != -1) {
							printf("\t|%-15s", "ѧ��");
							printf("|%-10s", "����");
							printf("%-7s", "|�Ա�");
							printf("|��Ժ\t\t");
							printf("%-21s", "|��Ŀһ");
							printf("%-7s", "|�ɼ�");
							printf("%-21s", "|��Ŀ��");
							printf("%-6s", "|�ɼ�");
							printf("%-21s", "|��Ŀ��");
							printf("%-6s", "|�ɼ�");
							printf("\n");
							printf("\t________________________________________________________________________________________________________________________________________\n\t");
							DisplayAthleteInfo(athletelist.pSAthleteList[nPos_ID]);
						}
						else {
							printf("\n�޴��ˣ�\n");
						}
						break;
					}
					case 3: {
						printf("\n\n������������");
						char szAthleteName[20];
						scanf_s("%s", szAthleteName, 20);
						int nPos_ID = LocateAthlete(athletelist, szAthleteName);
						if (nPos_ID != -1) {
							printf("\t|%-15s", "ѧ��");
							printf("|%-10s", "����");
							printf("%-7s", "|�Ա�");
							printf("|��Ժ\t\t");
							printf("%-21s", "|��Ŀһ");
							printf("%-7s", "|�ɼ�");
							printf("%-21s", "|��Ŀ��");
							printf("%-6s", "|�ɼ�");
							printf("%-21s", "|��Ŀ��");
							printf("%-6s", "|�ɼ�");
							printf("\n");
							printf("\t________________________________________________________________________________________________________________________________________\n\t");
							DisplayAthleteInfo(athletelist.pSAthleteList[nPos_ID]);
						}
						else {
							printf("\n�޴��ˣ�\n");
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
				printf("\n�������������...");
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
			//¼��ɼ���ز���
			printf("\n");
			menu_inputResult();
			int nChoice_inputResult = 0;
			while (!(cin >> nChoice_inputResult)) {
				cin.clear();
				while (cin.get() != '\n')
					continue;
				printf("\n\t����������������룺");
			}
			switch (nChoice_inputResult)
			{
			case 1: {//����ɼ�
				system("cls");
				SItemList itemlist;
				InitItemList(itemlist);
				ReadItemListFile(itemlist);
				DisplayItemList(itemlist);
				printf("\n\n\t����������Ҫ¼��ɼ�����ĿID�������ƣ�");
				char szIDorName[20];
				scanf_s("%s", szIDorName, 20);
				system("cls");
				InputResult(szIDorName);
				DestroyItemList(itemlist);
				break;
			}
			case 2: {//�鿴����
				system("cls");
				SItemList itemlist;
				InitItemList(itemlist);
				ReadItemListFile(itemlist);
				DisplayItemList(itemlist);
				printf("\n\n\t����������Ҫ����������ĿID�������ƣ�");
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
						printf("\t��Ŀ %s �����������\n\n", groupslist.pSItemGroupList[nPos_item].szItemName);
						printf("\t�����飺\n");
						DisplayAthleteListInfo(groupslist.pSItemGroupList[nPos_item].SMaleAthleteList);
						printf("\n\tŮ���飺\n");
						DisplayAthleteListInfo(groupslist.pSItemGroupList[nPos_item].SFemaleAthleteList);
					}
				}
				else {
					printf("���޴���Ŀ");
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
			if (flag_setting_password) {//����������ʾ��ͬ��ϵͳ�˵�
				menu_System_with_password();
			}
			else {
				menu_System();
			}
			while (!(cin >> nChoice_System)) {
				cin.clear();
				while (cin.get() != '\n')
					continue;
				printf("����������:");
			}
			switch (nChoice_System)
			{
			case 1: {
				fstream infile_athlete("athleteinfo.txt", ios::in);
				fstream outfile_athlete("athleteinfo_spare.txt", ios::out);
				if (!infile_athlete.is_open())
				{
					cout << "athleteinfo.txt�ļ���ʧ��..." << endl;
					return -1;
				}
				if (!outfile_athlete.is_open())
				{
					cout << "athleteinfo_spare.txt��ʧ��..." << endl;
					return -1;
				}
				outfile_athlete << infile_athlete.rdbuf();  //��infile���е����ݴ���outfile����
				infile_athlete.close();
				outfile_athlete.close();

				fstream infile_item("iteminfo.txt", ios::in);
				fstream outfile_item("iteminfo_spare.txt", ios::out);
				if (!infile_item.is_open())
				{
					cout << "iteninfo.txt�ļ���ʧ��..." << endl;
					return -1;
				}
				if (!outfile_item.is_open())
				{
					cout << "iteminfo_spare.txt��ʧ��..." << endl;
					return -1;
				}
				outfile_item << infile_item.rdbuf();  //��infile���е����ݴ���outfile����
				infile_item.close();
				outfile_item.close();
				printf("\n\n���ݳɹ�\n");
				break;
			}
			case 2: {
				fstream infile_athlete("athleteinfo_spare.txt", ios::in);
				fstream outfile_athlete("athleteinfo.txt", ios::out);
				if (!infile_athlete.is_open())
				{
					cout << "athleteinfo_spare.txt�ļ���ʧ��..." << endl;
					return -1;
				}
				if (!outfile_athlete.is_open())
				{
					cout << "athleteinfo.txt��ʧ��..." << endl;
					return -1;
				}
				outfile_athlete << infile_athlete.rdbuf();  //��infile���е����ݴ���outfile����
				infile_athlete.close();
				outfile_athlete.close();

				fstream infile_item("iteminfo_spare.txt", ios::in);
				fstream outfile_item("iteminfo.txt", ios::out);
				if (!infile_item.is_open())
				{
					cout << "iteninfo_spare.txt�ļ���ʧ��..." << endl;
					return -1;
				}
				if (!outfile_item.is_open())
				{
					cout << "iteminfo.txt��ʧ��..." << endl;
					return -1;
				}
				outfile_item << infile_item.rdbuf();  //��infile���е����ݴ���outfile����
				infile_item.close();
				outfile_item.close();
				printf("\n\n���ݻָ��ɹ�\n");
				break;
			}
			case 3: {
				if (flag_setting_password) {//Ҫɾ������,��Ӧ������Ĳ˵�
					printf("\n\n\t����������:");
					char* password_temp = ReadPasswordfromFile();//��ȷ������
					char password[100] = {};//ȫ����ʼ��Ϊ���ַ���
					GetPasssword(password,sizeof(password));
					if (strcmp(password, password_temp) == 0){//������ȷ
						flag_setting_password = false;//ɾ������
						printf("\n\n\tɾ������ɹ�\n");
						DeletePassword();
					}
					else {
						printf("\n\n\t��������޷�ɾ������\n");
					}
				}//if
				else {//��Ӧû������Ĳ˵���Ҫ��������
					printf("\n\n\t����������:");
					char password[100] = {};//��һ����������
					GetPasssword(password,sizeof(password));
					printf("\n\n\t���ٴ�����:");
					char password_temp[100] = {};//�ڶ�����������
					GetPasssword(password_temp,sizeof(password_temp));
					
					if (strcmp(password, password_temp) == 0) {
						flag_setting_password = true;
						printf("\n\n\t�������óɹ���\n");
						WritePasswordtoFile(password);
					}
					else 
						printf("\n\n\t�������벻һ�£�\n");

				}//else(flag_password)
				break;
			}//case 
			case 4: {
				printf("\n\t����������:");
				char password[100] = {};
				GetPasssword(password,sizeof(password));
				char *password_temp = ReadPasswordfromFile();//��ȷ������
				char password_new[100] = {};//�µ�����
				char password_new_temp[100] = {};//�ڶ��������µ�����
				if (strcmp(password, password_temp) == 0) {//������ȷ
					printf("\n\n\t\t�������µ����룺");
					GetPasssword(password_new,sizeof(password_new));
					printf("\n\n\t\t���ٴ������µ����룺");
					GetPasssword(password_new_temp,sizeof(password_new_temp));
					if (strcmp(password_new, password_new_temp) == 0) {//�޸ĳɹ�
						WritePasswordtoFile(password_new);
						printf("\n\n\t�����޸ĳɹ�\n");
					}
					else {
						printf("\n\n\t�������벻��ͬ\n");
					}
				}//if(������ȷ)
				else {//���벻��ȷ
					printf("\n\n\t���벻��ȷ��\n");
				}

				break;
			}
			case 5: {
				printf("\n\n\t���������ʾ���ƣ�");
				char coverName[100] = {};
				scanf_s("%s", coverName, 100);
				strncpy_s(szTitle, sizeof(szTitle), coverName, sizeof(coverName));
				printf("\n\t�޸ĳɹ�\n");
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
			goto logout;//!!!��һ����goto��
			break;
		}
		default:
			break;
		}
		getchar();
		printf("\n�밴�س�������");
		getchar();
	}

	return 0;
}
