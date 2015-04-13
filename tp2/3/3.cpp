#include "3.h"

int main(){

	int m, n, C, weight, a, b;
	Edge buff;

	cin << n << m << C;

	vector<Edge> edges;

	set<int> in_tree, out_tree;

	in_tree,insert(0);
	for(int i = 1; i < n; i++)
		out_tree.insert(i);

	for(int i = 0; i < m; i++){
		cin >> a >> b >> weight;
		a--; b--;
		Edge.v1 = min(a,b);
		Edge.v2 = max(a,b);
		Edge.weight = weight;
		edges.push_back(edge);
	}

	sort(edges.begin(), edges.end(), compare_edges);

	//Tengo todos los vertices, ahora ordeno por menor peso

	//elijo el nodo 0 para arrancar con el spanning tree

	


}