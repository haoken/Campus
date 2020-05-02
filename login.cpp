#include"login.h"

void welcome_interface(char szSystemName[]) {
	while (true) {
		time_t now_time;
		now_time = time(NULL);//���Ǹ�������
		struct tm block;
		localtime_s(&block,& now_time);
		int year = block.tm_year + 1900;
		int mon = block.tm_mon+1;
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
		printf("\t\t\t\t\t\t  %s У �� �� �� �� ϵ ͳ 1.0\n", szTempName);
		printf("\n\n\n\n");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t\t\t �밴 E ������");
		char ch =_getch();
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
		printf("\t\t\t\t\t\t  %s У �� �� �� �� ϵ ͳ 1.0\n", szTempName);
		printf("\n\n\n\n");
		printf("\n\n");
		printf("\t\t\t\t\t\t    password:");
		char password[100] = {};//ȫ����ʼ��Ϊ���ַ���
		char ch;
		int index = 0;
		while(index<sizeof(password)-1&&(ch=_getch())!='\r'){
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
		
		char *password_decode =ReadPasswordfromFile();
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

void GetPasssword(char password[],int size_password) {
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