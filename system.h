#pragma once
#include"allstruct.h"
void SystemManagement(bool&pwdFlag, char* szTitle);

//��������ܵ�д���ļ���
void WritePasswordtoFile(char password[]);
//��������ļ��н��ܶ���
char* ReadPasswordfromFile();

void SystemInit(bool& pwd, char* szTitle, int n);