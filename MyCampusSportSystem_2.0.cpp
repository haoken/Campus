#include"allstruct.h"

void main_menu() {
	printf("\n\t1.��Ŀ����\n");
	printf("\n\t2.�˶�Ա����\n");
	printf("\n\t3.������λ����\n");
	printf("\n\t4.�ɼ�����\n");
	printf("\n\t5.��������\n");
	printf("\n\t6.ϵͳ����\n");
	printf("\n\t7.ע��\n");
	printf("\n\t���ѡ��:");
}

int main() {
	bool pwd = false;
	char szTitle[TITLELENGTH] = { 0 };
logout:	//ע�����������¿�ʼ
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
			SystemManagement(pwd,szTitle);//ϵͳ����
			break;
		case 7:
			system("cls");
			goto logout;
			break;
		}//switch
	}//while


}//main

