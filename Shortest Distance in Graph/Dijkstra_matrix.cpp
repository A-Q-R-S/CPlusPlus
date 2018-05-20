/**/#define _CRT_SECURE_NO_WARNINGS																	//no warnings
/**/#include <utility>																				//system("pause")																		//system("pause")
/**/#include "stdafx.h"
#include <stdio.h>
#include <cstring>																					//memset
#include <cmath>																					//abs
#include <vector>
#include <queue>
#include <tuple>

#define MAX_SIZE 1501
#define pii std::pair<int,int>
#define tiii std::tuple<int,int,int>

int data[MAX_SIZE][MAX_SIZE];
int dist[MAX_SIZE][MAX_SIZE];
bool marked[MAX_SIZE][MAX_SIZE];

void input(int &N, int &M, pii &start, pii &end)
{
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			scanf_s("%d", &data[i][j]);
		}
	}
	scanf("%d%d%d%d", &(start).first, &(start).second, &(end).first, &(end).second);
}

struct Container
{
	int x, y, weight;
	Container(int _x = 0, int _y = 0, int _weight = 0) : x(_x), y(_y), weight(_weight) {}

	const Container operator=(const Container &other)
	{
		if (this == &other)
			return *this;

		x = other.x;
		y = other.y;
		weight = other.weight;
	}
};

struct CompareDist
{
	bool operator() (const Container A, const Container B) const
	{
		return A.weight > B.weight;
	}
};


//Shortest distance from "start" to "end". There is path available, no need to check.
int Dijkstra_PQ(pii &start, pii &end, int &N, int &M, std::priority_queue<Container, std::vector<Container>, CompareDist> &PQ)
{
	Container current;
	pii	data_iter;

	memset(dist, 0, sizeof(dist));
	memset(marked, false, sizeof(marked));

	PQ.push(Container(start.first,start.second,data[start.first][start.second]));
	while (!PQ.empty())
	{
		current = PQ.top(); PQ.pop();																//get the shortest distance cell
		if (marked[current.x][current.y] == false)													//check if marked
		{
			marked[current.x][current.y] = true;													//mark as used
			dist[current.x][current.y] = current.weight;											//set distance to "current"

			for (int i = current.x - 1; i <= current.x + 1; i++)									//iterate & check dimensions
			{
				if (i >= 1 && i <= N)																//~
				{
					for (int j = current.y - 1; j <= current.y + 1; j++)							//~
					{
						if (j >= 1 && j <= M)														//~
						{
							if (std::abs(current.x - i) != std::abs(current.y - j))					//only up,down,left,right allowed
							{
								if (marked[i][j] == false)											//check if marked
								{
									PQ.push(Container(i, j, data[i][j] + current.weight));			//push
								}
							}
						}
					}
				}
			}
		}
	}
	return dist[end.first][end.second];
}

int main()
{
	int N,																							//dimensions
		M,																							//dimensions
		result;
	pii start,
		end;
	std::priority_queue<Container, std::vector<Container>, CompareDist> PQ;


	input(N, M, start, end);

	result = Dijkstra_PQ(start, end, N, M, PQ);
	printf("%d\n", result);

	/**/system("pause");
    /**/return 0;
}

