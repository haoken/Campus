////////////////////////////////////////////
//�ļ�˵��
//���̣�MyCampusSportSystem
//���ߣ���κ�
//���������ļ��ṩΪ������������Ĺ��������ṩ��Ϊ�ÿ��ķ��档
//��Ҫ������
//			
//������ڣ�2020/3/18 /12��26
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

//����xxtea.h�еĺ�����������ܣ�Ȼ��д���ļ�
void WritePasswordtoFile(char password[]);

//��������ļ��ж�����Ȼ����ܣ������ܺ���ַ������ء�
char* ReadPasswordfromFile();

//��ɾ������ʱ����Ҫ�޸ķ���λ
void DeletePassword();

//������ȡ���룬������ʱ����Ļ��ʾ��*����
void GetPasssword(char password[],int size_password);