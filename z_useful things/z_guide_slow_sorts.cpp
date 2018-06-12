#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>

void bubbleSort(int *&arr, int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j+i<n-1; j++)
        {
            if(arr[j] > arr[j+1])
                std::swap(arr[j],arr[j+1]);
        }
    }
}

void selectionSort(int *arr, int n)
{
    int _min;
    for(int i=0; i<n; i++)
    {
        _min = i;
        for(int j=i+1; j<n; j++)
        {
            if(arr[_min] > arr[j])
                _min = j;
        }
        if(_min != i)
            std::swap(arr[i],arr[i-1]);
    }
}

void insertElement(int *arr, int i)
{
    while(i>0 && arr[i] < arr[i-1])
    {
        std::swap(arr[i],arr[i-1]);
        i--;
    }
}
void insertionSort(int *arr, int n)
{
    for(int i=0; i<n; i++)
    {
        insertElement(arr,i);
    }
}
/*
void couningSort(int *arr,int n)
{
	///make sure N<=n
	int help[n];
	for(int i=0; i<n; i++)
        help[arr[i]]++;

	int counter, current;
	for(int i=0; i<n; i++)
    {
        counter = help[i];
		while(counter>0)
		{
			counter--;
			arr[j]=i;
			j++;
		}
    }
}*/


void _scan_array(int *&arr, int *&N)
{
    scanf("%d",&(*N));
    for(int i=0; i<*N; i++)
    {
        scanf("%d",&arr[i]);
    }
}

void _print_array(int *arr, int *&N)
{
    for(int i=0;i<(*N);i++)
        printf("%d ",arr[i]);
    printf("\n");
}

void _scan_vector(std::vector<int> *&vec , int *&N)
{
	int	num = 0;

	scanf("%d", &(*N));
	for (size_t i = 0; i<(*N); i++)
	{
		scanf("%d", &num);
		(*vec).push_back(num);
	}
}

void _print_vector(std::vector<int> *vec)
{
    size_t N = (*vec).size();
	for (size_t i=0; i<N; i++)
	{
		printf("%d ", (*vec)[i]);
	}
	printf("\n");
}

int main()
{
    int                 *N      = new int;
    int                 *arr    = new int[100010];
    std::vector<int>    *vec    = new std::vector<int>;

    _scan_vector(vec,N);
    std::stable_sort(vec->begin(),vec->end());
    _print_vector(vec);

    _scan_array(arr,N);
    bubbleSort(arr,*N);
    _print_array(arr,N);
}
