//version : 1.0
//YY-MM-DD: 18/05/20

/**/#define _CRT_SECURE_NO_WARNINGS																	//no warnings
/**/#include <utility>																				//system("pause")
#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
#include <queue>

#define MAXINT 2147483647
#define pii std::pair<int, int>

int arr[26][26];

void input(std::string &A, std::string &B, int &shifts)												//string A, string B, allowed shifts
{
	char from, to;
	int dist;

	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			arr[i][j] = MAXINT;																		//initial value = MAXINT

	std::cin >> A >> B;
	scanf("%d", &shifts);																			//incoming allowed shifts

	for (int i = 0; i<shifts; i++)
	{
		fgetc(stdin); from = fgetc(stdin);															//drop '\n' & scan
		fgetc(stdin); to = fgetc(stdin);															//~
		scanf_s("%d", &dist);
		arr[from - 'a'][to - 'a'] = std::min(arr[from - 'a'][to - 'a'], dist);						//because the same cell arr[i][j] can be entered many times
	}
}

//shortest distance from each vertex to another
void Floyd()
{
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			for (int k = 0; k < 26; k++)
			{
				if (arr[i][k] != MAXINT && arr[k][j] != MAXINT)										//2 allowed shifts
					arr[i][j] = std::min(arr[i][j], arr[i][k] + arr[k][j]);
			}
		}
		arr[i][i] = 0;																				//obvious addition
	}
}

//for each [i] in A & B: shortest mutual distance A[i]->j & B[i]->j
//-1 if no path (for any [i]) available
int func(std::string &A, std::string &B)
{
	int size = A.length(),
		temp = MAXINT,
		result = 0;

	char current_A = '0';
	char current_B = '0';
	bool flag = false;

	if (size == B.length())																			//only if A & B have the same length
	{
		for (int i = 0; i<size && !flag; i++)
		{
			current_A = A.at(i) - 'a';
			current_B = B.at(i) - 'a';
			if (current_A != current_B)
			{
				for (int j = 0; j < 26; j++)														//"j" is 3rd value compared to A & B to make them equal
				{
					if (arr[current_A][j] != MAXINT && arr[current_B][j] != MAXINT)
					{
						temp = std::min(temp, arr[current_A][j] + arr[current_B][j]);				//get the smallest shift distance of A + ~ of B
					}
				}
				if (temp == MAXINT) flag = true;													//no shifts current_A->j or current_B->j available; flag = true: EXIT
				else result += temp;
				temp = MAXINT;
			}
		}
	}

	if (result == 0 || flag == true)
		result = -1;
	return result;
}

int main()
{
	std::string A, B;
	int shifts;

	_scan(A, B, shifts);

	Floyd();

	printf("%d\n", func(A, B));

	/**/system("pause");
	/**/return 0;
}

