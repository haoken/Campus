#include"io.h"

void WipeSpace(char* str){
	char* p = str;
	int i = 0;
	while (*p) {
		if (*p != ' ')
			str[i++] = *p;
		p++;
	}
	str[i] = '\0';
}

void GetString(char* str, int n) {
	while(true){
		std::cin.get(str, n);//1.读取n-1个字符后停止  2.读取到回车后停止，回车留在输入队列中  3.直接回车，会导致接下来的cin.get()会得到EOF
		char ch;
		if ((ch = std::cin.get()) == EOF) {//情况三,直接输入回车，cin.get会读到一个EOF，str长度为0
			std::cin.clear();//读到EOF cin会取消读取
		}
		else if (ch != '\n') {//情况1
			while ( std::cin.get() != '\n');
			printf("输入过长，重新输入：");
			continue;
		}
		WipeSpace(str);
		if ( strlen(str) == 0) {//全部是空格的情况 和直接回车的情况
			while (std::cin.get() != '\n');
			printf("输入错误，重新输入：");
		}
		else
			break;
	}
}

int GetOption(int floor,int upper){
	int option;
	while (!(std::cin >> option) || (option <floor || option >upper)) {
		std::cin.clear();
		while (std::cin.get() != '\n')
			continue;
		printf("\t输入错误，重新输入：");
	}
	char ch;
	while ((ch = getchar()) != '\n');//将剩余的输入缓存读取。
	return option;
}

double GetDouble() {
	double res;
	while (!(std::cin >> res)) {
		std::cin.clear();
		while (std::cin.get() != '\n');
		printf("\t输入错误，重新输入：");
	}
	char ch;
	while ((ch = getchar()) != '\n');
	return res;
}

double GetDouble(double floor, double upper) {
	double res;
	while (!(std::cin >> res)||(res<floor||res>upper) ){
		std::cin.clear();
		while (std::cin.get() != '\n');
		printf("\t输入错误，重新输入：");
	}
	char ch;
	while ((ch = getchar()) != '\n');
	return res;
}

int Index_BF(char* txt, char* pattern) {
	if (strlen(pattern) == 0)
		return 0;
	if (strlen(txt) == 0)
		return -1;
	int i = 0;
	int j = 0;
	while (txt[i] != '\0' && pattern[j] != '\0') {
		if (txt[i] == pattern[j])
			i++, j++;
		else {
			i = i - j + 1;
			j = 0;
		}
		if (j == strlen(pattern)) {
			return i - j;
		}
	}
	return -1;
}

int Index_BF(char* txt,const char* pattern) {
	if (strlen(pattern) == 0)
		return 0;
	if (strlen(txt) == 0)
		return -1;
	int i = 0;
	int j = 0;
	while (txt[i] != '\0' && pattern[j] != '\0') {
		if (txt[i] == pattern[j])
			i++, j++;
		else {
			i = i - j + 1;
			j = 0;
		}
		if (j == strlen(pattern)) {
			return i - j;
		}
	}
	return -1;
}