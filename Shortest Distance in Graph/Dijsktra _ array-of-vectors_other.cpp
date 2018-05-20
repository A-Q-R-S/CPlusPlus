//version : 1.0
//YY-MM-DD: 18/05/20

/**/#define _CRT_SECURE_NO_WARNINGS																	//no warnings
/**/#include <utility>																				//system("pause")
/**/#include "stdafx.h"
#include <stdio.h>
#include <algorithm>																				//sort
#include <cstring>																					//memset
#include <vector>
#include <queue>

#define pii		std::pair<int,int>
#define MAX_SIZE 10001

std::vector<pii> data[MAX_SIZE];
bool marked[MAX_SIZE];
int	dist[MAX_SIZE];


void input(int &N, int &M, int &H, std::vector<int> &starts)										//vertices, enjes, starting vertices
{
	scanf("%d%d%d", &N, &M, &H);
	int from, to, weight;
	for (int i = 0; i < H; i++)
	{
		scanf("%d", &from);
		starts.push_back(from);
	}
	//std::sort(starts.begin(), starts.end());														//not needed sort

	for (int i = 0; i < M; i++)
	{
		scanf("%d %d %d", &from, &to, &weight);

		data[from].push_back(pii(to, weight));
		data[to].push_back(pii(from, weight));
	}
}

//Comparator for priority_queue<pii>
class CompareDist
{
public:
	bool operator() (const pii A, const pii B) const
	{
		/*return A.second >= B.second;*/
		if (A.second == B.second)
			return A.first > B.first;
		return A.second > B.second;
	}
};

//in array "dist": dist[x] = find shortest distance from "start" to "x"
void Dijkstra_PQ(int start, std::priority_queue<pii, std::vector<pii>, CompareDist> &PQ)
{
	pii current,																					//current.first = vertex_to; current.second = weight;
		data_iter;																					//iterator
	memset(marked, false, sizeof(marked));
	memset(dist, 0, sizeof(dist));

	PQ.push(pii(start, 0));
	while (!PQ.empty())
	{
		current = PQ.top(); PQ.pop();																//shortest distance vertex
		if (marked[current.first] == false)															//if not marked
		{
			marked[current.first] = true;															//mark as used
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
}

//nullify distances from one starting vertex to another
void nullify_starting_vertices(int count_starters, std::vector<int> &starts)
{
	for (int i = 0; i < count_starters; i++)
	{
		dist[starts[i]] = 0;
	}
}

//return sum of all distances in array dist
int sum_dist(int size)
{
	int result = 0;
	for (int i = 1; i <= size; i++)
	{
		result += dist[i];
	}
	return result;
}

int main()
{
	int N, *N_ptr = &N,																				//vertices		-> houses + hospitals
		M, *M_ptr = &M,																				//edges			-> streets
		H, *H_ptr = &H,																				//end vertices	-> hospitals
		result = 2147483647;																		//max int
	std::vector<int> starts;
	std::priority_queue<pii, std::vector<pii>, CompareDist> PQ;

	input(N_ptr, M_ptr, H_ptr, starts);

	for (int i = 0; i < H; i++)
	{
		Dijkstra_PQ(starts[i], PQ);
		nullify_starting_vertices(H, starts);
		result = std::min(result, sum_dist(N));
	}
	printf("%d\n", result);

	/**/system("pause");
	/**/return 0;
}

