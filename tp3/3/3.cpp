#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include "../misc.h"

using namespace std;

vector<bool> solve(vector<vector<bool> > &g){
	int potential_vertices, max_pv, best_vertex;
	vector<bool> taken(g.size(), false);
	vector<bool> vertices(g.size(), false);
	int stop = g.size();
	
	while(v_count(taken) < g.size() && stop--){

		//choose vertex that takes the most not taken vertices
		max_pv = 0;
		for(int i = 0; i < g.size(); i++){
			if(!taken[i]){
				potential_vertices = 1;
				for(int j = 0; j < g.size(); j++){
					if(g[i][j] && !taken[j])
						potential_vertices++;
				}
				if(max_pv < potential_vertices){
					max_pv = potential_vertices;
					best_vertex = i;
				}
			}
		}
		vertices[best_vertex] = true;
		taken[best_vertex] = true;
		for(int j = 0; j < g.size(); j++){
			if(g[best_vertex][j])
				taken[j] = true;
		}

	}

	return vertices;
}

int main(){


	vector<vector<bool> > g = graph_input();

	vector<bool> result = solve(g);
	
	print_result(result);

	return 0;
}