#include"system.h"
#include"xxtea.h"

#define TITLELENGTH 100

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

void welcome_interface(char szSystemName[]) {
	while (true) {
		time_t now_time;
		now_time = time(NULL);//���Ǹ�������
		struct tm block;
		localtime_s(&block, &now_time);
		int year = block.tm_year + 1900;
		int mon = block.tm_mon + 1;
		int day = block.tm_mday;
		int weekday = block.tm_wday;
		printf("\n\t%d��%d��%d��   ", year, mon, day);
		switch (weekday)
		{
		case 0:
			printf("������");
			break;
		case 1:
			printf("����һ");
			break;
		case 2:
			printf("���ڶ�");
			break;
		case 3:
			printf("������");
			break;
		case 4:
			printf("������");
			break;
		case 5:
			printf("������");
			break;
		case 6:
			printf("������");
			break;
		}

		char szTempName[101] = {};
		strncpy_s(szTempName, 101, szSystemName, 100);
		printf("\n\n\n\n");
		printf("\n\n\n\n\n");
		printf("\t\t\t\t\t\t  %s У �� �� �� �� ϵ ͳ 2.0\n", szTempName);
		printf("\n\n\n\n");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t\t\t �밴 E ������");
		char ch = _getch();
		if (ch == 'e' || ch == 'E')
			break;
		system("cls");
	}
}

void welcome_interface_with_password(char szSystemName[]) {
	while (true) {
		time_t now_time;
		now_time = time(NULL);//���Ǹ�������
		struct tm block;
		localtime_s(&block, &now_time);
		int year = block.tm_year + 1900;
		int mon = block.tm_mon + 1;
		int day = block.tm_mday;
		int weekday = block.tm_wday;
		printf("\n\t%d��%d��%d��   ", year, mon, day);
		switch (weekday)
		{
		case 0:
			printf("������");
			break;
		case 1:
			printf("����һ");
			break;
		case 2:
			printf("���ڶ�");
			break;
		case 3:
			printf("������");
			break;
		case 4:
			printf("������");
			break;
		case 5:
			printf("������");
			break;
		case 6:
			printf("������");
			break;
		}

		char szTempName[101] = {};
		strncpy_s(szTempName, 101, szSystemName, 100);
		printf("\n\n\n\n");
		printf("\n\n\n\n\n");
		printf("\t\t\t\t\t\t  %s У �� �� �� �� ϵ ͳ 2.0\n", szTempName);
		printf("\n\n\n\n");
		printf("\n\n");
		printf("\t\t\t\t\t\t    password:");
		char password[100] = {};//ȫ����ʼ��Ϊ���ַ���
		char ch;
		int index = 0;
		while (index < sizeof(password) - 1 && (ch = _getch()) != '\r') {
			if (ch != char(8)) {//�������˸��
				password[index++] = ch;
				printf("*");
			}
			else {//�����˸��
				if (index != 0) {//����˵�������ַ��Ͳ���������
					printf("\b \b");
					index--;
				}
			}
		}
		password[index] = '\0';

		char* password_decode = ReadPasswordfromFile();
		if (strcmp(password, password_decode) == 0) {
			system("cls");
			break;
		}
		else {
			printf("\n\n\t\t\t\t\t\t\t    �������!");
			printf("\n\t\t\t\t\t\t\t    ���������������������");
			getchar();
		}
		system("cls");
	}
}

void SystemInit(bool&pwd,char*szTitle,int n) {
	pwd = false;
	FILE* pPassword;
	bool flag_setting_password;
	char szTitle_tmp[TITLELENGTH] = { 0 };
	errno_t err = fopen_s(&pPassword, "password", "r");
	if (err != 0) {
		printf("password�ļ��޷���");
		exit(0);
	}
	if (pPassword) {
		fread(&flag_setting_password, sizeof(flag_setting_password), 1, pPassword);
		if (flag_setting_password!=true) {//true
			flag_setting_password = false;
			pwd = false;
		}
		pwd = flag_setting_password;
		fclose(pPassword);
	}

	FILE* pTitle;
	errno_t err1 = fopen_s(&pTitle, "Title", "r");
	if (err1 != 0) {
		printf("Title�ļ��޷���");
		exit(0);
	}
	fread(szTitle_tmp, sizeof(szTitle_tmp), 1, pTitle);
	fclose(pTitle);
	strcpy_s(szTitle, n, szTitle_tmp);
	if (flag_setting_password) {
		welcome_interface_with_password(szTitle_tmp);
	}
	else {
		welcome_interface(szTitle_tmp);
	}
}

void WritePasswordtoFile(char password[]) {
	
	const char* key = "wozhenshuai";//�������ܵ�key
	size_t len;
	unsigned char* encrypt_data = (unsigned char*)xxtea_encrypt(password, strlen(password), key, &len);//���ݼ��ܣ�encrypt_data�Ǽ��ܺ������
	FILE* pPassword;
	errno_t err = fopen_s(&pPassword, "password", "w");
	if (err != 0) {
		printf("password�ļ��޷���");
		return;
	}

	if (strlen(password) == 0) {//����Ϊ0
		bool ok = false;
		fwrite(&ok, sizeof(ok), 1, pPassword);
		fputc('\n', pPassword);
		fclose(pPassword);
		return;
	}

	bool ok = true;
	if (pPassword) {
		fwrite(&ok, sizeof(ok), 1, pPassword);
		fputc('\n', pPassword);
		fwrite(&len, sizeof(len), 1, pPassword);//������Ҳ�����ļ�
		fputc('\n', pPassword);
		fwrite(encrypt_data, len, 1, pPassword);
		fclose(pPassword);
	}
}

char* ReadPasswordfromFile() {//password�ļ�����������ɣ�һ���Ƿ���λ�������Ƿ�������Ĵ��ڣ�Ȼ�������ݱ���֮��ĳ��ȣ�Ȼ���Ǳ���֮�������
	const char* key = "wozhenshuai";//�������ܵ�key
	size_t len;
	FILE* pPassword;
	errno_t err = fopen_s(&pPassword, "password", "r");
	if (err != 0) {
		printf("password�ļ��޷���");
		return NULL;
	}
	bool ok;
	if (pPassword) {
		fread(&ok, sizeof(ok), 1, pPassword);
		fgetc(pPassword);
		if (ok == false) {
			char ch[] = "";
			return ch;
		}
		fread(&len, sizeof(len), 1, pPassword);
		fgetc(pPassword);
		char* password = (char*)malloc((int(len) + 1) * sizeof(char));
		fread(password, len, 1, pPassword);
		char* decrypt_data = (char*)xxtea_decrypt(password, len, key, &len);
		fclose(pPassword);
		return decrypt_data;
	}
	return NULL;
}

void DeletePassword() {
	FILE* pPassword;
	errno_t err = fopen_s(&pPassword, "password", "w");
	if (err != 0) {
		printf("password�ļ��޷���");
		return;
	}
	bool ok = false;
	if (pPassword) {
		fwrite(&ok, sizeof(ok), 1, pPassword);
		fputc('\n', pPassword);
		fclose(pPassword);
	}
}

void GetPasssword(char password[], int size_password) {
	char ch;
	int index = 0;
	while (index < size_password - 1 && (ch = _getch()) != '\r') {
		if (ch != char(8)) {//�������˸��
			password[index++] = ch;
			printf("*");
		}
		else {//�����˸��
			if (index != 0) {//����˵�������ַ��Ͳ���������
				printf("\b \b");
				index--;
			}
		}
	}//while
	password[index] = '\0';
}

void backups(const char* szFileName,const char* szSpareFileName) {//����
	std::fstream infile(szFileName, std::ios::in);
	std::fstream outfile(szSpareFileName, std::ios::out);
	if (!infile.is_open())
	{
		std::cout << szFileName<<"�ļ���ʧ��..." << std::endl;
		return;
	}
	if (!outfile.is_open())
	{
		std::cout <<szSpareFileName <<"��ʧ��..." << std::endl;
		return;
	}
	outfile << infile.rdbuf();  //��infile���е����ݴ���outfile����
	infile.close();
	outfile.close();
}

void SystemManagement(bool& pwdFlag,char* szTitle) {
	while (true) {
		system("cls");
		if (pwdFlag)
			menu_System_with_password();
		else
			menu_System();
		int nChoice = GetOption(1, 6);
		switch (nChoice) {
		case 1: {
			backups("athleteinfo.txt", "athleteinfo_spare.txt");
			backups("iteminfo.txt", "iteminfo_spare.txt");
			backups("academyinfo.txt", "academyinfo_spare.txt");
			backups("password", "password_spare");
			backups("Title", "Title_spare");
			printf("\n\n\t���ݳɹ�\n");
			break;
		}//case 1
		case 2: {
			backups("athleteinfo_spare.txt", "athleteinfo.txt");
			backups("iteminfo_spare.txt", "iteminfo.txt");
			backups("academyinfo_spare.txt", "academyinfo.txt");
			backups("password_spare", "password");
			backups("Title_spare", "Title");
			printf("\n\n\t�ָ��ɹ�\n");
			break;
		}//case 2
		case 3: {
			if (pwdFlag) {//������
				printf("\n\n\t����������:");
				char* password_temp = ReadPasswordfromFile();//��ȷ������
				char password[100] = {};//ȫ����ʼ��Ϊ���ַ���
				GetPasssword(password, sizeof(password));
				if (strcmp(password, password_temp) == 0) {//������ȷ
					pwdFlag = false;//ɾ������
					printf("\n\n\tɾ������ɹ�\n");
					DeletePassword();
				}
				else {
					printf("\n\n\t��������޷�ɾ������\n");
				}
			}//if
			else {
				printf("\n\n\t����������:");
				char password[100] = {};//��һ����������
				GetPasssword(password, sizeof(password));
				printf("\n\n\t���ٴ�����:");
				char password_temp[100] = {};//�ڶ�����������
				GetPasssword(password_temp, sizeof(password_temp));

				if (strcmp(password, password_temp) == 0) {
					pwdFlag = true;
					printf("\n\n\t�������óɹ���\n");
					WritePasswordtoFile(password);
				}
				else
					printf("\n\n\t�������벻һ�£�\n");
			}
			break;
		}//case 3
		case 4: {
			printf("\n\t����������:");
			char password[100] = {};
			GetPasssword(password, sizeof(password));
			char* password_temp = ReadPasswordfromFile();//��ȷ������
			char password_new[100] = {};//�µ�����
			char password_new_temp[100] = {};//�ڶ��������µ�����
			if (strcmp(password, password_temp) == 0) {//������ȷ
				printf("\n\n\t�������µ����룺");
				GetPasssword(password_new, sizeof(password_new));
				printf("\n\n\t���ٴ������µ����룺");
				GetPasssword(password_new_temp, sizeof(password_new_temp));
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
			char coverName[TITLELENGTH] = {};
			GetString(coverName, sizeof(coverName));
			//д���ļ�
			FILE* pTitle;
			errno_t err = fopen_s(&pTitle, "Title", "w");
			if (err != 0) {
				printf("Title�ļ��޷���");
				exit(0);
			}
			fwrite(coverName, sizeof(coverName), 1, pTitle);
			fclose(pTitle);
			printf("\n\t�޸ĳɹ�\n");
			break;
		}//case 5
		}//switch
		if (nChoice == 6)
			break;
		system("pause");
	}
}

