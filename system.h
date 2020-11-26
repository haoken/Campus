#pragma once
#include"allstruct.h"
void SystemManagement(bool&pwdFlag, char* szTitle);

//将密码加密的写入文件中
void WritePasswordtoFile(char password[]);
//将密码从文件中解密读出
char* ReadPasswordfromFile();

void SystemInit(bool& pwd, char* szTitle, int n);