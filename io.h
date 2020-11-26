/////////////////////////////////////////////////////////////////////   
//工程: 校运会管理系统  
//     描述:该文件提供了处理输入输出，利用c++cin的一些特性提高容错的一些函数。 还有一些工具，例如模式匹配 
//	   函数描述：void WipeSpace(char* str)： 去除字符串中的空格。
//               void GetString(char* str, int n);输入字符串，超长则重新输入，全是空格则重新输入
//				 int GetOption(int floor, int upper);该函数让用户从[floor,upper]中选取一个选项
//				 double GetDouble();获取一个浮点数
//				 double GetDouble(double floor, double upper);获得一个[floor,upper]中的浮点数
//				 int Index_BF(char* txt, char* pattern);暴力匹配算法
//				 int Index_BF(char* txt, const char* pattern);暴力匹配算法
//     版本: 校运会系统2.0，
//	   完成日期：2020/4/29   
/////////////////////////////////////////////////////////////////////  

#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

//========
//功能：去除字符串中的功能
//参数:str
//	str: 以'\0'结束的字符串
//应用：当用户输入名称是带有空格，将空格去除。
//========
void WipeSpace(char* str);

//========
//功能：输入字符串，超长则重新输入，全是空格则重新输入
//参数:str，n
//	str: 用来放字符串的字符数组
//	n:字符数组的最大长度
//========
void GetString(char* str, int n);

//========
//功能：该函数让用户从[floor,upper]中选取一个选项。
//容错：输入非整数则重新数。输入超出范围的整数则重新输入。
//参数:floor,upper
//	floor:所有选项的最小的一个
//	upper:所有选项中最大的一个。
//返回：将用户选择的选项返回。
//注意:选项应该是要连续的整数。
//========
int GetOption(int floor, int upper);

//========
//功能：获得一个double类型的数据
//容错：输入非浮点型数据则重新输入
//返回：返回这个浮点数
//========
double GetDouble();

//========
//功能：获得一个double类型的数据
//容错：输入非浮点型数据则重新输入
//参数：floor,upper
//	floor:浮点数的下限
//	upper:浮点数的上限
//返回：返回这个浮点数
//========
double GetDouble(double floor, double upper);

//========
//功能：返回模式串在文本串中的位置，如果不存在返回-1
//参数：txt,pattern
//	txt:文本串
//	pattern:模式串
//返回：模式串在文本串中的位置，如果不存在返回-1
//注意：暴力匹配算法
//========
int Index_BF(char* txt, char* pattern);

int Index_BF(char* txt, const char* pattern);