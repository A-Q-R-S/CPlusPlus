/**/#define _CRT_SECURE_NO_WARNINGS																	//no warnings
/**/#include <utility>																				//system("pause")
#include <stdio.h>																					//input & output
#include <iostream>																					//~
#include <vector>
#include <tuple>
#include <algorithm>																				//sort
#include <chrono>                                                                                   //time

#define tiii std::tuple<int,int,int>
#define first std::get<0>
#define second std::get<1>
#define third std::get<2>
#define MAX_SIZE 1001

int family[MAX_SIZE];																				//each vertex has family (family parent = root/alpha vertex)
int rank[MAX_SIZE] = { 0 };																			//each family member has rank (root/alpha member = highest rank)
//std::chrono::high_resolution_clock::time_point time_begin;

void input(int &N, int &M,int &K, std::vector<tiii> &data)											//N = vertices, M = edjes, K = bottleneck
{
	int from, to, weight;
	scanf("%d%d", &N, &M);
	//time_begin = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < M; i++)
	{
		scanf("%d%d%d", &from, &to, &weight);
		data.push_back(tiii(from, to, weight));
		family[from] = from;																		//each vertex is part of its own family (alone)
		family[to] = to;																			//~
	}
	scanf("%d", &K);
}

//returns the family (= root/alpha vertex) of the tree
int find_family(int vertex)
{
	if (family[vertex] == vertex)
		return vertex;
	return family[vertex] = find_family(family[vertex]);
}

//make X child of Y
//keep the tree height low
void union_trees(int A, int B)
{
	if (rank[A] == rank[B])
	{
		family[A] = B;
		rank[B]++;
	}

	else if (rank[A] < rank[B])
	{
		family[A] = B;
	}

	else family[B] = A;
}

//tuple comparator: sort(up) to get the biggest edges first
bool Compare(tiii A, tiii B)
{
	return third(A) > third(B);
}

void Kruskal(const int &N, const int &M, const int &K, std::vector<tiii> &data)
{
	std::sort(data.begin(), data.end(), Compare);													//sort(up) to get the biggest edges first

	int i = 0, count = 0, sum = 0, family_from, family_to;

	while(count<N-1)																				//when count = N-1: DONE
	{
		family_from = find_family(first(data[i]));
		family_to = find_family(second(data[i]));

		if (family_from != family_to)																//edge allowed only if the vertices have different families
		{
			count++;
			union_trees(family_from, family_to);													//unite the families into one
			if (third(data[i]) < K)
				sum++;																				//sum of the edges that create bottleneck (third(data[i]) < K)
		}
		i++;
	}

	printf("%d\n", sum);
}

int main()
{
	int N, M, K;
	std::vector<tiii> data;
	input(N, M, K, data);

    //auto time_begin = std::chrono::high_resolution_clock::now();

	Kruskal(N, M, K, data);

	/*std::chrono::duration<double> time_span = std::chrono::duration_cast< std::chrono::duration<double> >
		(std::chrono::high_resolution_clock::now() - time_begin);
	std::cout << time_span.count() << " seconds passed\n";*/

	/**/system("pause");
}
