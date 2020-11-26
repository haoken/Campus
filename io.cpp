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
		std::cin.get(str, n);//1.��ȡn-1���ַ���ֹͣ  2.��ȡ���س���ֹͣ���س��������������  3.ֱ�ӻس����ᵼ�½�������cin.get()��õ�EOF
		char ch;
		if ((ch = std::cin.get()) == EOF) {//�����,ֱ������س���cin.get�����һ��EOF��str����Ϊ0
			std::cin.clear();//����EOF cin��ȡ����ȡ
		}
		else if (ch != '\n') {//���1
			while ( std::cin.get() != '\n');
			printf("����������������룺");
			continue;
		}
		WipeSpace(str);
		if ( strlen(str) == 0) {//ȫ���ǿո����� ��ֱ�ӻس������
			while (std::cin.get() != '\n');
			printf("��������������룺");
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
		printf("\t��������������룺");
	}
	char ch;
	while ((ch = getchar()) != '\n');//��ʣ������뻺���ȡ��
	return option;
}

double GetDouble() {
	double res;
	while (!(std::cin >> res)) {
		std::cin.clear();
		while (std::cin.get() != '\n');
		printf("\t��������������룺");
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
		printf("\t��������������룺");
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