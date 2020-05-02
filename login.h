////////////////////////////////////////////
//文件说明
//工程：MyCampusSportSystem
//作者：李嘉浩
//描述：该文件提供为程序设置密码的工作，并提供较为好看的封面。
//主要函数：
//			
//完成日期：2020/3/18 /12：26
/////////////////////////////////////////////

#pragma once
#ifndef __login_H__
#define __login_H__
#endif

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

#include"xxtea.h"

using namespace std;

void welcome_interface(char szSystemName[]);

void welcome_interface_with_password(char szSystemName[]);

//利用xxtea.h中的函数将密码加密，然后写入文件
void WritePasswordtoFile(char password[]);

//将密码从文件中读出，然后解密，将解密后的字符串返回。
char* ReadPasswordfromFile();

//当删除密码时，需要修改符号位
void DeletePassword();

//用来获取密码，当键入时，屏幕显示‘*’。
void GetPasssword(char password[],int size_password);