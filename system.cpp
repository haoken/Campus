#include"system.h"
#include"xxtea.h"

#define TITLELENGTH 100

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

void welcome_interface(char szSystemName[]) {
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
		printf("\t\t\t\t\t\t  %s 校 运 会 管 理 系 统 2.0\n", szTempName);
		printf("\n\n\n\n");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t\t\t 请按 E 键进入");
		char ch = _getch();
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
		printf("\t\t\t\t\t\t  %s 校 运 会 管 理 系 统 2.0\n", szTempName);
		printf("\n\n\n\n");
		printf("\n\n");
		printf("\t\t\t\t\t\t    password:");
		char password[100] = {};//全部初始化为空字符！
		char ch;
		int index = 0;
		while (index < sizeof(password) - 1 && (ch = _getch()) != '\r') {
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

		char* password_decode = ReadPasswordfromFile();
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

void SystemInit(bool&pwd,char*szTitle,int n) {
	pwd = false;
	FILE* pPassword;
	bool flag_setting_password;
	char szTitle_tmp[TITLELENGTH] = { 0 };
	errno_t err = fopen_s(&pPassword, "password", "r");
	if (err != 0) {
		printf("password文件无法打开");
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
		printf("Title文件无法打开");
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
	
	const char* key = "wozhenshuai";//用来加密的key
	size_t len;
	unsigned char* encrypt_data = (unsigned char*)xxtea_encrypt(password, strlen(password), key, &len);//数据加密，encrypt_data是加密后的数据
	FILE* pPassword;
	errno_t err = fopen_s(&pPassword, "password", "w");
	if (err != 0) {
		printf("password文件无法打开");
		return;
	}

	if (strlen(password) == 0) {//长度为0
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

void GetPasssword(char password[], int size_password) {
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

void backups(const char* szFileName,const char* szSpareFileName) {//备份
	std::fstream infile(szFileName, std::ios::in);
	std::fstream outfile(szSpareFileName, std::ios::out);
	if (!infile.is_open())
	{
		std::cout << szFileName<<"文件打开失败..." << std::endl;
		return;
	}
	if (!outfile.is_open())
	{
		std::cout <<szSpareFileName <<"打开失败..." << std::endl;
		return;
	}
	outfile << infile.rdbuf();  //将infile流中的数据传入outfile流中
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
			printf("\n\n\t备份成功\n");
			break;
		}//case 1
		case 2: {
			backups("athleteinfo_spare.txt", "athleteinfo.txt");
			backups("iteminfo_spare.txt", "iteminfo.txt");
			backups("academyinfo_spare.txt", "academyinfo.txt");
			backups("password_spare", "password");
			backups("Title_spare", "Title");
			printf("\n\n\t恢复成功\n");
			break;
		}//case 2
		case 3: {
			if (pwdFlag) {//有密码
				printf("\n\n\t请输入密码:");
				char* password_temp = ReadPasswordfromFile();//正确的密码
				char password[100] = {};//全部初始化为空字符！
				GetPasssword(password, sizeof(password));
				if (strcmp(password, password_temp) == 0) {//密码正确
					pwdFlag = false;//删除密码
					printf("\n\n\t删除密码成功\n");
					DeletePassword();
				}
				else {
					printf("\n\n\t密码错误！无法删除密码\n");
				}
			}//if
			else {
				printf("\n\n\t请输入密码:");
				char password[100] = {};//第一次输入密码
				GetPasssword(password, sizeof(password));
				printf("\n\n\t请再次输入:");
				char password_temp[100] = {};//第二次输入密码
				GetPasssword(password_temp, sizeof(password_temp));

				if (strcmp(password, password_temp) == 0) {
					pwdFlag = true;
					printf("\n\n\t密码设置成功！\n");
					WritePasswordtoFile(password);
				}
				else
					printf("\n\n\t两次密码不一致！\n");
			}
			break;
		}//case 3
		case 4: {
			printf("\n\t请输入密码:");
			char password[100] = {};
			GetPasssword(password, sizeof(password));
			char* password_temp = ReadPasswordfromFile();//正确的密码
			char password_new[100] = {};//新的密码
			char password_new_temp[100] = {};//第二次输入新的密码
			if (strcmp(password, password_temp) == 0) {//密码正确
				printf("\n\n\t请输入新的密码：");
				GetPasssword(password_new, sizeof(password_new));
				printf("\n\n\t请再次输入新的密码：");
				GetPasssword(password_new_temp, sizeof(password_new_temp));
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
			char coverName[TITLELENGTH] = {};
			GetString(coverName, sizeof(coverName));
			//写入文件
			FILE* pTitle;
			errno_t err = fopen_s(&pTitle, "Title", "w");
			if (err != 0) {
				printf("Title文件无法打开");
				exit(0);
			}
			fwrite(coverName, sizeof(coverName), 1, pTitle);
			fclose(pTitle);
			printf("\n\t修改成功\n");
			break;
		}//case 5
		}//switch
		if (nChoice == 6)
			break;
		system("pause");
	}
}

