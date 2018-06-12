/**/#define _CRT_SECURE_NO_WARNINGS																	//no warnings
/**/#include <utility>																				//system("pause")
#include <stdio.h>
#include <vector>																					//vector
#include <algorithm>																				//min, max, fill
#include <cstring>																					//memset

#define SMALL_INT (0-1667457892)																	//cannot real INT_MIN because of memset
int storage[500][500];																				//max result between every 2 cells
int sums[500][500];																					//sum of elements inbetween every 2 cells

void input(int &N, std::vector<int> &vec)
{
	int dummy;
	scanf("%d", &N);

	for (int i = 0; i<N; i++)
	{
		scanf("%d", &dummy);
		vec.push_back(dummy);
	}

	memset(storage, -100, sizeof(storage));															//-100 via binary memset = SMALL_INT = -1667457892
	memset(sums, -100, sizeof(sums));																//~

	for (int i = 1; i <= N-2; i++)																	//obvious values:
	{
		storage[i][i] = sums[i][i] = vec[i];														//the same cell

		sums[i][i + 1] = vec[i] + vec[i + 1];														//neighbouring cells, left-to-right
		storage[i][i+1] = std::max(vec[i], sums[i][i + 1]);											//~

		sums[i][i - 1] = vec[i] + vec[i - 1];														//neighbouring cells, right-to-left
		storage[i][i-1] = std::max(vec[i], sums[i][i - 1]);											//~
	}
	storage[0][0] = sums[0][0] = vec[0];															//the same cell
	storage[N - 1][N - 1] = sums[N - 1][N - 1] = vec[N - 1];										//~
}

//calculates sum of el-s between vec[left] & vec[right]
int sum_elements(const std::vector<int> &vec, const int &left, const int &right)
{
	if (sums[left][right] != SMALL_INT) return sums[left][right];									//already calculated; boolean flag-marker structure preferred
	//else:
	int result = 0;
	for (int i = left; i <= right; i++)
	{
		result += vec[i];
	}
	sums[left][right] = result;																		//save the result
	return result;
}

//for each step generates all possible next steps; calculates max result of all
int func(const std::vector<int> &vec, int left, int right, int direction, int max_step)	//direction = {1,2} = {left,right}
{
	int size = vec.size();
	int next_jump = 0;
	int result = 0;
	
	//left-to-right
	if (direction == 2)
	{
		if (storage[left][right] != SMALL_INT) return storage[left][right];							//already calculated; boolean flag-marker structure preferred
		//else:
		result = vec[left];																			//initial value of result
		for (int step = 1; step <= max_step; step++)												//calculate value of all possible steps
		{
			next_jump = func(vec, /*storage, sums, */left+1, left+step, 1, step-1);					//calculate value of all possible steps (after current fixed step)
			result = std::max(result, sum_elements(vec,left, left + step - 1) + next_jump);			//result = the maximum
			storage[left][left + step] = std::max(storage[left][left + step], result);				//save the result
		}
		return storage[left][right];																//return the result
	}

	//right-to-left (mirror image)
	else if (direction == 1)
	{
		if (storage[right][left] != SMALL_INT) return storage[right][left];							//already calculated; boolean flag-marker structure preferred
		//else:
		result = vec[right];																		//initial value of result
		for (int step = 1; step <= max_step; step++)												//calculate value of all possible steps
		{
			next_jump = func(vec,right-step, right-1, 2, step-1);									//calculate value of all possible steps (after current fixed step)
			result = std::max(result, sum_elements(vec, right - step + 1,right) + next_jump);		//result = the maximum
			storage[right][right - step] = std::max(storage[right][right - step], result);			//save the result
		}
		return storage[right][left];																//return the result
	}
}

int main()
{
	int N = 0,																						//size
		result = 0;																					//result
	std::vector<int> vec;
	
	input(N, vec);

	int size = vec.size();
	result = func(vec, 0, size-1, 2, size-1);														//promised correct input (>0 elements)

	printf("%d\n", result);

	system("pause");
}

