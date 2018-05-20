/**/#define _CRT_SECURE_NO_WARNINGS																	//no warnings
/**/#include <utility>																				//system("pause")																			//system("pause")
/**/#include "stdafx.h"
#include <stdio.h>
#include <cstring>																					//memset
#include <vector>
#include <queue>

#define pii std::pair<int,int>
#define MAX_SIZE 10001

std::vector<pii> data[MAX_SIZE];																	//data[i] = vector< (linear numbers + weight), ~, ..., ~ >
bool marked[MAX_SIZE];
int dist[MAX_SIZE];


void input(int &N, int &M, int &K)																	//total, 0-weight edjes, 1-weight edjes
{
	int id1, id2;
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 0; i < M; i++)
	{
		scanf("%d%d", &id1, &id2);
		data[id1].push_back(pii(id2, 0));
		data[id2].push_back(pii(id1, 0));
	}
	for (int i = 0; i < K; i++)
	{
		scanf("%d%d", &id1, &id2);
		data[id1].push_back(pii(id2, 1));
		data[id2].push_back(pii(id1, 1));
	}
}

//Comparator for priority_queue<pii>
class CompareDist
{
public:
	bool operator() (pii A, pii B)
	{
		return A.second > B.second;
	}
};

//Shortest distance from "start" to "end". If there is no path, return -1.
int Dijkstra_PQ(int start, int end, std::priority_queue<pii, std::vector<pii>, CompareDist> &PQ)
{
	pii current,																					//current.first = vertex_to; current.second = weight;
		data_iter;																					//iterator

	memset(marked, false, sizeof(marked));
	memset(dist, -1, sizeof(dist));

	PQ.push(pii(start, 0));
	while (!PQ.empty())
	{
		current = PQ.top(); PQ.pop();																//shortest distance cell
		if (marked[current.first] == false)															//if not marked
		{
			marked[current.first] = true;															//mark it as used
			dist[current.first] = current.second;													//distance to [x] = weight

			int _size = data[current.first].size();
			for (int i = 0; i<_size; i++)															//iterate all connected cells to data[current.first]
			{
				data_iter = data[current.first][i];
				if (marked[data_iter.first] == false)												//if not marked
				{
					PQ.push(pii(data_iter.first, data_iter.second + current.second));				//push
				}
			}
		}
	}
	return std::max(-1, dist[end]);																	//If there is no path, return -1.
}

int main()
{
	int N,																							//total vertices
		M,																							//0-weight
		K,																							//1-weight
		result;
	std::priority_queue<pii, std::vector<pii>, CompareDist> PQ;

	input(N, M, K);
	result = Dijkstra_PQ(N - 1, 0, PQ);
	printf("%d\n", result);

	/**/system("pause");
    /**/return 0;
}

