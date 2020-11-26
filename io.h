/////////////////////////////////////////////////////////////////////   
//����: У�˻����ϵͳ  
//     ����:���ļ��ṩ�˴����������������c++cin��һЩ��������ݴ��һЩ������ ����һЩ���ߣ�����ģʽƥ�� 
//	   ����������void WipeSpace(char* str)�� ȥ���ַ����еĿո�
//               void GetString(char* str, int n);�����ַ������������������룬ȫ�ǿո�����������
//				 int GetOption(int floor, int upper);�ú������û���[floor,upper]��ѡȡһ��ѡ��
//				 double GetDouble();��ȡһ��������
//				 double GetDouble(double floor, double upper);���һ��[floor,upper]�еĸ�����
//				 int Index_BF(char* txt, char* pattern);����ƥ���㷨
//				 int Index_BF(char* txt, const char* pattern);����ƥ���㷨
//     �汾: У�˻�ϵͳ2.0��
//	   ������ڣ�2020/4/29   
/////////////////////////////////////////////////////////////////////  

#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

//========
//���ܣ�ȥ���ַ����еĹ���
//����:str
//	str: ��'\0'�������ַ���
//Ӧ�ã����û����������Ǵ��пո񣬽��ո�ȥ����
//========
void WipeSpace(char* str);

//========
//���ܣ������ַ������������������룬ȫ�ǿո�����������
//����:str��n
//	str: �������ַ������ַ�����
//	n:�ַ��������󳤶�
//========
void GetString(char* str, int n);

//========
//���ܣ��ú������û���[floor,upper]��ѡȡһ��ѡ�
//�ݴ�����������������������볬����Χ���������������롣
//����:floor,upper
//	floor:����ѡ�����С��һ��
//	upper:����ѡ��������һ����
//���أ����û�ѡ���ѡ��ء�
//ע��:ѡ��Ӧ����Ҫ������������
//========
int GetOption(int floor, int upper);

//========
//���ܣ����һ��double���͵�����
//�ݴ�����Ǹ�������������������
//���أ��������������
//========
double GetDouble();

//========
//���ܣ����һ��double���͵�����
//�ݴ�����Ǹ�������������������
//������floor,upper
//	floor:������������
//	upper:������������
//���أ��������������
//========
double GetDouble(double floor, double upper);

//========
//���ܣ�����ģʽ�����ı����е�λ�ã���������ڷ���-1
//������txt,pattern
//	txt:�ı���
//	pattern:ģʽ��
//���أ�ģʽ�����ı����е�λ�ã���������ڷ���-1
//ע�⣺����ƥ���㷨
//========
int Index_BF(char* txt, char* pattern);

int Index_BF(char* txt, const char* pattern);