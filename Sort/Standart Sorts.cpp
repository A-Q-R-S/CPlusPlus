//version : 1.0 
//YY-MM-DD: 18/05/20

/**/#define _CRT_SECURE_NO_WARNINGS																	//no warnings
/**/#include <utility>																				//system("pause")#include "stdafx.h"
#include <utility>

#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

#include <vector>
#include <queue>


void input_array(int *&arr, int &N)
{
	scanf("%d", &N);
	for (int i = 0; i<N; i++)
	{
		scanf("%d", &arr[i]);
	}
}

void _print_array(int *&arr, int &N)
{
	for (int i = 0; i<N; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void _scan_vector(std::vector<int> &vec)
{
	int	N, num = 0;

	scanf("%d", &N);
	for (int i = 0; i<N; i++)
	{
		scanf("%d", &num);
		vec.push_back(num);
	}
}

void _print_vector(std::vector<int> &vec)
{
	size_t N = vec.size();
	for (size_t i = 0; i<N; i++)
	{
		printf("%d ", vec[i]);
	}
	printf("\n");
}

void _scan_vector_string(std::vector<std::string> &vec)
{
	int _size;
	std::string input;
	scanf("%d", &_size);
	for (int i = 0; i<_size; i++)
	{
		std::cin >> input;
		vec.push_back(input);
	}
}

void _print_vector_string(std::vector<std::string> &vec)
{
	int _size = vec.size();
	for (int i = 0; i<_size; i++)
	{
		printf("%s\n", vec[i].c_str());
	}
	//printf("\n");
}

//O(n^2); stable;
void selectionSort(int *&arr, const int n)
{
	int _min;
	for (int i = 0; i<n; i++)
	{
		_min = i;
		for (int j = i + 1; j<n; j++)
		{
			if (arr[_min] > arr[j])
				_min = j;
		}
		if (_min != i)
			std::swap(arr[i], arr[_min]);
	}
}

//O(n^2); stable;
void bubbleSort(int *&arr, const int n)
{
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
				std::swap(arr[j], arr[j + 1]);
		}
	}
}

//O(n^2); stable;
void insertionSort(int *&arr, const int n)
{
	for (int i = 1; i<n; i++)
	{
		while (i > 0 && arr[i - 1] > arr[i])
		{
			std::swap(arr[i - 1], arr[i]);
			i--;
		}
	}
}

//O(n); For small-range data; +/- numbers
void couningSort(int *&arr, const int n)
{
	int *count_arr;
	int maxElem = 0-2147483648, 
		minElem = 2147483647,
		size_count_arr = 0,
		counter, 
		current = 0;

	for (int i = 0; i < n; i++)
	{
		maxElem = std::max(maxElem, arr[i]);
		minElem = std::min(minElem, arr[i]);
	}
	size_count_arr = maxElem - minElem + 1;

	count_arr = new int[size_count_arr];
	memset(count_arr, 0, sizeof(int)*size_count_arr);

	for(int i=0; i<n; i++)
		(count_arr)[arr[i] - minElem]++;
	
	for(int i=0; i<size_count_arr; i++)
	{
		counter = count_arr[i];
		while(counter>0)
		{
			arr[current] = i + minElem;
			current++;
			counter--;
		}
	}
}

//O(n*logn); stable???
void quickSort(int *data, const int _size)
{
	if (_size <= 1) return;

	int pivot = data[_size / 2];                                                                    //could be: mean, median, avg, etc...
	int a = 0, b = _size - 1;

	while (a < b)
	{
		if (data[a] < pivot)
			a++;
		else if (data[b] > pivot)
			b--;
		else
		{
			std::swap(data[a], data[b]);
			a++;
		}
	}

	quickSort(data, a);																				//a = b
	quickSort(data + a, _size - a);																	//data+a = pivot+1
}

//O(n*logn); counting inversions;
void mergeSort_ARRAY(int *&data, int *&help, int start, int end, long long &inversions)
{
	if (end - start <= 1) return;

	int pivot = start + (end - start) / 2;

	mergeSort_ARRAY(data, help, start, pivot, inversions);
	mergeSort_ARRAY(data, help, pivot, end, inversions);

	int left = start;
	int right = pivot;

	while (left < pivot || right < end)
	{
		if (left < pivot)
		{
			if (right < end)
			{
				if (data[left] <= data[right])
				{
					help[(left - 0) + (right - pivot)] = data[left];								//save left elem
					left++;
				}
				else
				{
					help[(left - 0) + (right - pivot)] = data[right];								//save right elem
					right++;
					inversions += pivot - left;														//right elem: inversion with all elements in (left,pivot)
				}
			}
			else //right = end
			{
				help[(left - 0) + (right - pivot)] = data[left];
				left++;
			}
		}
		else //left = pivot
		{
			help[(left - 0) + (right - pivot)] = data[right];
			right++;
		}
	}
	std::memcpy(&data[start], &help[start], sizeof(int)*(end - start));
}

long long mergeSort_ARRAY(int *&data, const int _size)
{
	int *help = new int[_size];
	long long inversions = 0;
	mergeSort_ARRAY(data, help, 0, _size, inversions);
	return inversions;
}

//O(n*logn); counting inversions;
void mergeSort_VECTOR(std::vector<int> &data, int *&help, int start, int end, long long &inversions)
{
	if (end - start <= 1) return;

	int pivot = start + (end - start) / 2;

	mergeSort_VECTOR(data, help, start, pivot, inversions);
	mergeSort_VECTOR(data, help, pivot, end, inversions);

	int left = start;
	int right = pivot;

	while (left < pivot || right < end)
	{
		if (left < pivot)
		{
			if (right < end)
			{
				if (data[left] <= data[right])
				{
					help[(left - 0) + (right - pivot)] = data[left];								//save left elem
					left++;
				}
				else
				{
					help[(left - 0) + (right - pivot)] = data[right];								//save right elem
					right++;
					inversions += pivot - left;														//right elem: inversion with all elements in (left,pivot)
				}
			}
			else //right = end
			{
				help[(left - 0) + (right - pivot)] = data[left];
				left++;
			}
		}
		else //left = pivot
		{
			help[(left - 0) + (right - pivot)] = data[right];
			right++;
		}
	}
	std::memcpy(&data[start], &help[start], sizeof(int)*(end - start));
}

long long mergeSort_VECTOR(std::vector<int> &data)
{
	int *help = new int[data.size()];
	long long inversions = 0;
	mergeSort_VECTOR(data, help, 0, data.size(), inversions);
	return inversions;
}

bool lexicographically_smaller(std::string first, std::string second)
//true = first is smaller; false = second is smaller
{
	int fstLen, sndLen;
	for (int i = 0; i<50; i++)
	{
		fstLen = first.length();
		sndLen = second.length();

		if (fstLen == 0 && sndLen >= 0) return true;												//including ( ...==0 && ...==0)
		if (fstLen > 0 && sndLen == 0) return false;
		if (first.at(0) - '0' < second.at(0) - '0') return true;
		if (first.at(0) - '0' > second.at(0) - '0') return false;
		else																						//the same char at beginning
		{
			first = first.substr(1, fstLen - 1);													//drop the 0, start from 1 & count n-1 chars
			second = second.substr(1, sndLen - 1);													//-||-
		}
	}
	return true;
}

//O(n*logn); stable;
void lexicographic_sort(std::vector<std::string> &vec)
{
	std::sort(vec.begin(), vec.end(), lexicographically_smaller);
}


int main()
{
	int                 N;
	int                 *arr = new int[100010];
	std::vector<int>    vec;
	std::vector<std::string> vec_str;

	/*_scan_vector(vec);
	std::stable_sort(vec->begin(), vec->end());
	_print_vector(vec);*/

	/*_scan_array(arr, N);
	selectionSort(arr, N);
	_print_array(arr, N);*/

	/*_scan_array(arr, N);
	insertionSort(arr, N);
	_print_array(arr, N);*/

	/*_scan_array(arr, N);
	bubbleSort(arr, N);
	_print_array(arr, N);*/

	/*_scan_array(arr, N);
	couningSort(arr, N);
	_print_array(arr, N);*/

	/*_scan_array(arr, N);
	quickSort(arr, N);
	_print_array(arr, N);*/

	/*_scan_array(arr, N);
	printf("%lld Inversions\n", mergeSort_ARRAY(arr, N));
	_print_array(arr, N);

	_scan_vector(vec);
	printf("%lld Inversions\n", mergeSort_VECTOR(vec));
	_print_vector(vec);*/

	/*_scan_vector_string(vec_str);
	lexicographic_sort(vec_str);
	_print_vector_string(vec_str);*/

	/**/system("pause");
	/**/return 0;
}



