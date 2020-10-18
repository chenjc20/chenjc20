#include <iostream> //replace of <iostream.h>
#include <cstdlib>	//replace of <stdlib.h>
#include <cstdio>	//replace of <stdio.h>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std; //important

int *myArray;
int tolCount = 0;

bool IsValidNextPerm(int n, int c, int p)
{
	for (int i = 0; i < c; i++)
	{
		if (myArray[i] == p)
		{
			return false;
		}
	}
	myArray[c] = p;
	return true;
}

void ConvertIntToBinaryArray(int data, int n, int *p)
{
	while (data != 0)
	{
		p[--n] = data % 2;
		data = data / 2;
	}
	while (n > 0) //补全位数
	{
		p[--n] = 0;
	}
}

int ConvertBinaryArrayToNum(int *p, int n)
{
	int temp = 0;
	for (int i = 0; i < n; i++)
	{
		temp = temp * 2 + p[i];
	}
	return temp;
}

bool BeOnlyOneBitDiff(int sIndex, int eIndex, int len)
{
	//异或操作 0^0=0；   0^1=1；   1^0=1；   1^1=0；
	int temp = myArray[sIndex] ^ myArray[eIndex];
	int offset = log(temp) / log(2);
	if (temp == (int)pow(2, offset))
	{
		return true;
	}
	return false;
}

//利用回溯方法从小到大有序的枚举试探每一个位置
void EnumPermu(int n, int c, int p)
{
	bool isOk = IsValidNextPerm(n, c, p);
	if (isOk) //前面的匹配如果不符合规则，则不再试探下一位，即事先进行剪枝
	{
		if ((int)pow(2, n) == c + 1 && BeOnlyOneBitDiff(0, c, n))
		{
			tolCount++; /*
			int *temp = new int[n];
			printf("-----------------------------\n");
			for(int i = 0; i <= c; i++)
			{
				ConvertIntToBinaryArray(myArray[i], n, temp);
				for(int j=0;j<n;j++)
				{
					printf("%d ", temp[j]);
				}
				printf(",");
			}
			printf("\n-----------------------------");
			delete[] temp;*/
			return;
		}
		for (int i = 0; i < n; i++)
		{
			int refer = (int)pow(2, i);
			int tempData = p ^ refer; //异或操作 0^0=0；   0^1=1；   1^0=1；   1^1=0；
			EnumPermu(n, c + 1, tempData);
		}
	}
}

//根据中位数计算对应的格雷码
void GeneralGrayCodeByMedi(int codeLen, int mediNum, int *pCode)
{
	int mod = (int)pow(2, codeLen);
	mediNum = mediNum % mod;
	int temp = mediNum >> 1;
	temp = mediNum ^ temp;
	ConvertIntToBinaryArray(temp, codeLen, pCode);
}
//根据格雷码计算中介数
int GetMediNumByGrayCode(int* pCode, int codeLen)
{
	int mediNum = ConvertBinaryArrayToNum(pCode, codeLen);
	for (int i = 1; i < codeLen; i++)
	{
		mediNum = mediNum ^ (mediNum >> i);
	}
	return mediNum;
}
//根据格雷码计算中介数
int GetMediNumByGrayCode(string strGrayCode)
{
	int codeLen= strGrayCode.length();
	int *p = new int[codeLen];
	for(int i = 0; i < codeLen; i++)
	{
		p[i] = strGrayCode[i] - '0';
	}
	int mediNum = GetMediNumByGrayCode(p, codeLen);
	delete[] p;
	return mediNum;
}
//生成格雷码
void GeneralGrayCode(int codeLen)
{
	int codeTolCount = (int)pow(2, codeLen);
	int *p = new int[codeLen];
	for (int i = 0; i < codeTolCount; i++)
	{
		GeneralGrayCodeByMedi(codeLen, i, p);
		for (int i = 0; i < codeLen; i++)
		{
			printf("%d", p[i]);
		}
		printf("\n");
	}
	delete[] p;
}
//根据中位数偏移量计算对应的格雷码
int GeneralGrayCodeByMediOffset(string strGrayCode, int mediNumOffSet, int *pCode)
{
	int codeLen= strGrayCode.length();
	int mod = (int)pow(2, codeLen);
	int mediNum = GetMediNumByGrayCode(strGrayCode);
	mediNum += mediNumOffSet;
	mediNum = mediNum % mod;
	GeneralGrayCodeByMedi(codeLen, mediNum, pCode);
	return codeLen;
}
///////////////
int main()
{
	int a;
	printf("1 for listing all Gray Code,\n 2 for getting Gray Code by medi-num,\n 3 for getting Gray Code by medi-num offset,\n 4 for getting medi-num by Gray Code,\n 5 for getting total combination num of Gray Code.\n");
	printf("please input a num above:");
	while (scanf("%d", &a) != EOF)
	{
		int codeLen = 0;
		int *p = new int[codeLen];
		int mediNum = 0;
		string strGrayCode="";
		strGrayCode.resize(100);
		switch (a)
		{
		case 1:
			printf("please input the length of one Gray Code:");
			scanf("%d", &codeLen);
			printf("the standard gray code is like follow:\n");
			GeneralGrayCode(codeLen);
			break;
		case 2:
			printf("please input the length of one Gray Code and medi-num:");
			scanf("%d %d", &codeLen, &mediNum);
			GeneralGrayCodeByMedi(codeLen, mediNum, p);
			for (int i = 0; i < codeLen; i++)
			{
				printf("%d", p[i]);
			}
			printf("\n");
			break;
		case 3:
			printf("please input one Gray Code and medi-num offset:");
			scanf("%s %d", &strGrayCode[0], &mediNum);
			codeLen =GeneralGrayCodeByMediOffset(strGrayCode.c_str(),mediNum,p);
			for (int i = 0; i < codeLen; i++)
			{
				printf("%d", p[i]);
			}
			printf("\n");
			break;
		case 4:
			printf("please input one Gray Code:");
			scanf("%s", &strGrayCode[0]);
			mediNum = GetMediNumByGrayCode(strGrayCode.c_str());
			printf("the medi-num is: %d\n", mediNum);
			break;
		case 5:
			printf("please input the length of one Gray Code:");
			scanf("%d", &codeLen);
			tolCount = 0;
			int capacity = (int)pow(2, codeLen);
			myArray = new int[capacity];
			EnumPermu(codeLen, 0, 0);
			printf("total count:%d\n", tolCount);
			delete[] myArray;
			break;
		}
		printf("\nplease input a num above:");
	}
	system("PAUSE");
	return 0;
}
