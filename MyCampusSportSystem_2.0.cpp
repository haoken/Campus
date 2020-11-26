#include"allstruct.h"

void main_menu() {
	printf("\n\t1.项目管理\n");
	printf("\n\t2.运动员管理\n");
	printf("\n\t3.参赛单位管理\n");
	printf("\n\t4.成绩管理\n");
	printf("\n\t5.秩序册管理\n");
	printf("\n\t6.系统设置\n");
	printf("\n\t7.注销\n");
	printf("\n\t你的选择:");
}

int main() {
	bool pwd = false;
	char szTitle[TITLELENGTH] = { 0 };
logout:	//注销从这里重新开始
	SystemInit(pwd, szTitle, TITLELENGTH);
	while (true) {
		system("cls");
		main_menu();
		int nChoice = GetOption(1, 7);
		switch (nChoice)
		{
		case 1:
			ItemManagement();
			break;
		case 2:
			AthleteManagement();
			break;
		case 3:
			AcademyManagement();
			break;
		case 4:
			GradeManagament();
			break;
		case 5:
			ProgramManagement();
			break;
		case 6:
			SystemManagement(pwd,szTitle);//系统设置
			break;
		case 7:
			system("cls");
			goto logout;
			break;
		}//switch
	}//while


}//main

