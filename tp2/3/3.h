#include <iostream>
#include <vector>

struct Node{
	int neighbor;
	int weight;
};

struct Edge{
	int v1, v2, weight;
};

bool compare_edges(Edge a, Edge b){
	return a.weight < b.weight;
}