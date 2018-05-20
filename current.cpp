/**/#define _CRT_SECURE_NO_WARNINGS																	//no warnings
/**/#include <utility>																				//system("pause")
#include <stdio.h>																					//input & output
#include <iostream>																					//~
#include <vector>
#include <tuple>
#include <algorithm>																				//sort
#include <memory>																					//memset, shared_ptr

#define tiii std::tuple<int,int,int>
#define first std::get<0>
#define second std::get<1>
#define third std::get<2>
#define MAX_SIZE 1001

std::shared_ptr<int> family[MAX_SIZE];																//index array: each vertex has family (root/alpha vertex)

void input(int &N, int &M, int &K, std::vector<tiii> &data, std::vector<tiii> &chosen)				//N = vertices, M = edges, K = bottleneck
{
	int from, to, weight;
	scanf("%d%d%d", &N, &M, &K);

	for (int i = 0; i < M; i++)
	{
		scanf("%d%d%d", &from, &to, &weight);
		data.push_back(tiii(from, to, weight));
		//data.push_back(tiii(to, from, weight));

		family[from] = std::make_shared<int>(from);													//allocate memory for shared pointer...
		family[to] = std::make_shared<int>(to);														//... each vertex is part of its own family (alone)
	}

	for (int i = 0; i < K; i++)
	{
		scanf("%d%d", &from, &to);
		chosen.push_back(tiii(from, to, -1));
	}
}

void output(const int &K, const std::vector<tiii> &chosen)
{
	for (int i = 0; i < K; i++)
	{
		printf("%d\n", third(chosen[i]));
	}
}

//returns the family (root/alpha vertex) of the tree
int find_family(const int vertex)
{
	return *(family[vertex].get());
}

//all members of family[A] go to family[B]; empty family[A] is deleted
void union_trees(const int A, const int B)
{
	family[A] = family[B];																			//free memory of family[A] & point to family[B]
}

//tuple comparator: sort(down) to get the biggest edges first
bool Compare(const tiii A, const tiii B)
{
	return third(A) > third(B);
}

//scan "chosen"; if first(chosen[i]) and second(chosen[i]) are from A & B (or B & A): change third(chosen[i]) to value (= families connecting edge)
//needs optimisation: not to scan all of "chosen" every time (maybe some pointers could be used)
void min_weight(const int A, const int B, std::vector<tiii> &chosen, const int value)
{
	int from = *family[A].get(),
		to = *family[B].get();
	int size = chosen.size();
	for (int i = 0; i < size; i++)
	{
		int chosen_from = *family[first(chosen[i])].get();
		int chosen_to = *family[second(chosen[i])].get();
		if ((third(chosen[i]) == -1) &&
			((chosen_from == from && chosen_to == to) ||
			(chosen_from == to  && chosen_to == from)))
		{
				third(chosen[i]) = value;															//value is the smallest edge in the new family union
		}
	}
}

//Maximum Spanning Tree
void Kruskal(const int &N, const int &M, const int &K, std::vector<tiii> &data, std::vector<tiii> &chosen)
{
	std::sort(data.begin(), data.end(), Compare);													//sort(down) to get the biggest edges first

	int i = 0, count = 0, family_from, family_to;

	while (count<N - 1)																				//when count = N-1: DONE
	{
		family_from = find_family(first(data[i]));
		family_to = find_family(second(data[i]));

		if (family_from != family_to)																//edge allowed only if the vertices have different families
		{
			count++;
			min_weight(family_from, family_to, chosen, third(data[i]));								//scan "chosen" and change third(chosen[i])
			union_trees(family_from, family_to);													//unite the families into one
		}
		i++;
	}
}

int main()
{
	int N, M, K;
	std::vector<tiii> data;
	std::vector<tiii> chosen;

	input(N, M, K, data, chosen);

	Kruskal(N, M, K, data, chosen);

	output(K, chosen);

	/**/system("pause");
}
