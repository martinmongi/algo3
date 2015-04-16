#include "3.h"

#define SPACE ' '

using namespace std;

int main(){

	int m, n, C, weight, a, b;
	Edge buff;

	cin >> n >> m >> C;

	vector<Edge> edges;
	vector<Edge> res;

	for(int i = 0; i < m; i++){
		cin >> a >> b >> weight;
		if(weight < C){ //Como lo que voy a generar es un arbol, prefiero construir otra refineria antes que usar ese arista
			a--; b--;	
			buff.v1 = min(a,b);
			buff.v2 = max(a,b);
			buff.weight = weight;
			edges.push_back(buff);
		}
	}

	sort(edges.begin(), edges.end(), compare_edges);

	// for(unsigned int i = 0; i < edges.size(); i++){
	// 	cout << edges[i].v1 << SPACE << edges[i].v2 << SPACE << edges[i].weight << endl;
	// }

	//cout << "Ordenar todo bien" << endl;

	//Tengo todos los vertices, ahora ordeno por menor peso

	//elijo el nodo 0 para arrancar con el spanning tree

	DisjointSets sets(n);

	for(unsigned int i = 0; i < edges.size(); i++){
		// cout << "Se rompe en FindSet?" << endl;
		if(sets.FindSet(edges[i].v1) != sets.FindSet(edges[i].v2)) {
			// cout << "Trato de meter el eje" << edges[i].v1 << SPACE << edges[i].v2 << endl;
			sets.MergeSets(edges[i].v1, edges[i].v2);
			res.push_back(edges[i]);
		}
	}

	// cout << "Genero el arbol bien" << endl;

	int r = n - res.size();
	int t = res.size();
	int K = C*r; //Costo de refinerias
	for(unsigned int i = 0; i < res.size(); i++){
		K += res[i].weight;
	}
	cout << K << SPACE << r << SPACE << t << endl;

	set<int> forests = sets.SetIds();

	for(set<int>::iterator it = forests.begin(); it != forests.end(); it++)
		cout << (*it) + 1 << SPACE;
	cout << endl;

	for(unsigned int i = 0; i < edges.size(); i++)
		cout << edges[i].v1 + 1 << SPACE << edges[i].v2 + 1 << endl;

	return 0;
}