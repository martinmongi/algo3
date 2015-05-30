#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include "misc.h"

using namespace std;
int upper_bound;

vector<bool> exact_solve(vector<vector<bool> > &g, int vertices, vector<bool> v, int i){
	if(i == vertices){
		if(dominant(g,v) && independent(g,v)){
			upper_bound = min(upper_bound, v_count(v));
			return v;
		}
		else
			return vector<bool>();
	}

	//pruning better_solution_already_found
	if(upper_bound < v_count(v))
		return vector<bool>();

	//pruning solution_already_dependent
	if(!independent(g,v))
		return vector<bool>();

	vector<bool> sol1 = exact_solve(g, vertices, v, i + 1);
	v[i] = true; 
	vector<bool> sol2 = exact_solve(g, vertices, v, i + 1);
	if(sol1.empty()){
		if(sol2.empty())
			return vector<bool>();
		else
			return sol2;
	} else {
		if(sol2.empty())
			return sol1;
		else
			if(v_count(sol1) <= v_count(sol2))
				return sol1;
			else
				return sol2;
	}
}

vector<bool> greedy_solve(vector<vector<bool> > &g){
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

int main(int argc, char* argv[]){

	vector<vector<bool> > g = graph_input();
	string chosen_algorithm = string(argv[1]);

	//exact solve
	if(chosen_algorithm == "EXACT"){

		upper_bound = g.size() + 1;

		vector<bool> initial_guess(g.size(), false);
		vector<bool> result = exact_solve(g, g.size(), initial_guess, 0);
		
		print_result(result);

		return 0;
	} else if(chosen_algorithm == "GREEDY"){

		vector<bool> result = greedy_solve(g);
		
		print_result(result);

		return 0;
	}else{
		arg_error(argv[0]);
		return 0;
	}
}