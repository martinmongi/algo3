#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include "../misc.h"
using namespace std;

vector<bool> solve(vector<vector<bool> > &g, int vertices, vector<bool> v, int i){
	if(i == vertices){
		if(dominant(g,v) && independent(g,v)){
			return v;
		}
		else
			return vector<bool>();
	}

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

	vector<bool> initial_guess(vertices, false);
	vector<bool> result = solve(g, vertices, initial_guess, 0);
	
	print_vector(result);

	return 0;
}