#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include "../misc.h"

using namespace std;

int upper_bound;

vector<bool> solve(vector<vector<bool> > &g, int vertices, vector<bool> v, int i){
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

	vector<bool> sol1 = solve(g, vertices, v, i + 1);
	v[i] = true; 
	vector<bool> sol2 = solve(g, vertices, v, i + 1);
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

int main(){


	vector<vector<bool> > g = graph_input();
	int vertices = g.size();

	upper_bound = vertices + 1;

	vector<bool> initial_guess(vertices, false);
	vector<bool> result = solve(g, vertices, initial_guess, 0);
	
	print_result(result);

	return 0;
}