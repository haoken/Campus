#include"login.h"

void welcome_interface(char szSystemName[]) {
	while (true) {
		time_t now_time;
		now_time = time(NULL);//就是个大整数
		struct tm block;
		localtime_s(&block,& now_time);
		int year = block.tm_year + 1900;
		int mon = block.tm_mon+1;
		int day = block.tm_mday;
		int weekday = block.tm_wday;
		printf("\n\t%d年%d月%d日   ", year, mon, day);
		switch (weekday)
		{
		case 0:
			printf("星期天");
			break;
		case 1:
			printf("星期一");
			break;
		case 2:
			printf("星期二");
			break;
		case 3:
			printf("星期三");
			break;
		case 4:
			printf("星期四");
			break;
		case 5:
			printf("星期五");
			break;
		case 6:
			printf("星期六");
			break;
		}
		
		char szTempName[101] = {};
		strncpy_s(szTempName, 101, szSystemName, 100);
		printf("\n\n\n\n");
		printf("\n\n\n\n\n");
		printf("\t\t\t\t\t\t  %s 校 运 会 管 理 系 统 1.0\n", szTempName);
		printf("\n\n\n\n");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t\t\t 请按 E 键进入");
		char ch =_getch();
		if (ch == 'e' || ch == 'E')
			break;
		system("cls");
	}
}

void welcome_interface_with_password(char szSystemName[]) {
	while (true) {
		time_t now_time;
		now_time = time(NULL);//就是个大整数
		struct tm block;
		localtime_s(&block, &now_time);
		int year = block.tm_year + 1900;
		int mon = block.tm_mon + 1;
		int day = block.tm_mday;
		int weekday = block.tm_wday;
		printf("\n\t%d年%d月%d日   ", year, mon, day);
		switch (weekday)
		{
		case 0:
			printf("星期天");
			break;
		case 1:
			printf("星期一");
			break;
		case 2:
			printf("星期二");
			break;
		case 3:
			printf("星期三");
			break;
		case 4:
			printf("星期四");
			break;
		case 5:
			printf("星期五");
			break;
		case 6:
			printf("星期六");
			break;
		}

		char szTempName[101] = {};
		strncpy_s(szTempName, 101, szSystemName, 100);
		printf("\n\n\n\n");
		printf("\n\n\n\n\n");
		printf("\t\t\t\t\t\t  %s 校 运 会 管 理 系 统 1.0\n", szTempName);
		printf("\n\n\n\n");
		printf("\n\n");
		printf("\t\t\t\t\t\t    password:");
		char password[100] = {};//全部初始化为空字符！
		char ch;
		int index = 0;
		while(index<sizeof(password)-1&&(ch=_getch())!='\r'){
			if (ch != char(8)) {//不等于退格键
				password[index++] = ch;
				printf("*");
			}
			else {//输入退格键
				if (index != 0) {//如果退到第零个字符就不能再退了
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
			printf("\n\n\t\t\t\t\t\t\t    密码错误!");
			printf("\n\t\t\t\t\t\t\t    请输入任意键后重新输入");
			getchar();
		}
		system("cls");
	}
}

void WritePasswordtoFile(char password[]) {
	const char* key = "wozhenshuai";//用来加密的key
	size_t len;
	unsigned char* encrypt_data = (unsigned char*)xxtea_encrypt(password, strlen(password), key, &len);//数据加密，encrypt_data是加密后的数据
	FILE* pPassword;
	errno_t err = fopen_s(&pPassword, "password", "w");
	if (err != 0) {
		printf("password文件无法打开");
		return;
	}
	bool ok = true;
	if (pPassword) {
		fwrite(&ok, sizeof(ok), 1, pPassword);
		fputc('\n', pPassword);
		fwrite(&len, sizeof(len), 1, pPassword);//将长度也存入文件
		fputc('\n', pPassword);
		fwrite(encrypt_data, len, 1, pPassword);
		fclose(pPassword);
	}
}

char* ReadPasswordfromFile() {//password文件由三部分组成，一个是符号位，决定是否有密码的存在，然后是数据保密之后的长度，然后是保密之后的数据
	const char* key = "wozhenshuai";//用来解密的key
	size_t len;
	FILE* pPassword;
	errno_t err = fopen_s(&pPassword, "password", "r");
	if (err != 0) {
		printf("password文件无法打开");
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
		printf("password文件无法打开");
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
		if (ch != char(8)) {//不等于退格键
			password[index++] = ch;
			printf("*");
		}
		else {//输入退格键
			if (index != 0) {//如果退到第零个字符就不能再退了
				printf("\b \b");
				index--;
			}
		}
	}//while
	password[index] = '\0';
}