#include <cstdio>
#include <cstring>
#include <algorithm>
#include <typeinfo>
#include <chrono>

int dataQS[] = {122,9,6,5,1,54,5885,46,52,88,4,36};

void quicksort(int *data, int _size)
{
    if(_size <= 1)
        return;

    int pivot = data[_size/2];                                                                      ///could be: mean, median, avg, etc...
printf("aaaaa\n");
    int a = 0, b = _size-1;

    while(a != b)
    {
        if(data[a] < pivot)
            a++;
        else if(data[b] > pivot)
            b--;
        else
        {
            std::swap(data[a], data[b]);
            a++;
        }
    }

    quicksort(data, a);                 //a=pivot
    quicksort(data + a, _size - a);      //data+a=pivot+1
}

void _scan(int *&data, int *&N)
{
    scanf("%d",&(*N));

    data = new int[*N];

    for(int i=0; i<*N; i++)
    {
        scanf("%d",&data[i]);
    }
}

void _print(int *&data, clock_t timerA, clock_t timerB)
{
    int arr_size = sizeof(dataQS)/sizeof(typeid(dataQS).name());

    printf("\nQuicksort:\n");
    for(int i = 0;i < arr_size;i++)
    {
        printf("%d ", data[i]);
    }
    printf("%llf\n",timerB-timerA);
}

int main()
{
    int     N;
    int     *N_ptr = &N;
    int     *data = NULL;
    clock_t timerA =0, timerB=0;

    _scan(data,N_ptr);
    printf("%d\n",data[0]);

    //int     arr_size = sizeof(dataQS)/sizeof(typeid(dataQS).name());                                ///sizeof(dataQS)/sizeof(int)


    timerA = clock();
    quicksort(data, N);
    timerB = clock();

    _print(data, timerA, timerB);

    return 0;
}

