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

vector<bool> naive_solve(vector<vector<bool> > &g){
	int vertices = g.size();

	vector<bool> v(vertices, false);
	v[0] = true;

	for(int i = 1; i < vertices; i++){
		bool adyacent = false;
		for(int j = 0; j < i && !adyacent; j++){
			if(g[i][j] && v[j])
				adyacent = true;
		}
		if(!adyacent)
			v[i] = true;
	}
	return v;
}

vector<bool> local_search_1(vector<vector<bool> > &g, vector<bool> v){

	int vertices = g.size();

	for(int i = 0; i < vertices; i++){
		if(!v[i]){
			v[i] = true;
			for(int j = 0; j < vertices; j++){
				if(v[j]){
					v[j] = false;
					for(int j2 = j + 1; j2 < vertices; j2++){
						if(v[j2]){
							v[j2] = false;
							if(dominant(g,v) && independent(g,v)){
								return v;
							}
							v[j2] = true;
						}
					}
					v[j] = true;
				}
			}
			v[i] = false;
		}
	}
	return v;
}

vector<bool> local_search_2(vector<vector<bool> > &g, vector<bool> v){

	int vertices = g.size();

	for(int i = 0; i < vertices; i++){
		if(!v[i]){
			v[i] = true;
			for(int i2 = i + 1; i2 < vertices; i2++){
				if(!v[i2]){
					v[i2] = true;
					for(int j = 0; j < vertices; j++){
						if(v[j]){
							v[j] = false;
							for(int j2 = j + 1; j2 < vertices; j2++){
								if(v[j2]){
									v[j2] = false;
									for(int j3 = j2 + 1; j3 < vertices; j3++){
										if(v[j3]){
											v[j3] = false;
											if(dominant(g,v) && independent(g,v)){
												return v;
											}
											v[j3] = true;
										}
									}
									v[j2] = true;
								}
							}
							v[j] = true;
						}
					}
					v[i2] = false;
				}
			}
			v[i] = false;
		}
	}
	return v;
}

int main(int argc, char* argv[]){

	vector<vector<bool> > g = graph_input();

	if(argc < 2){
		arg_error(argv[0]);
		return 0;
	}

	string chosen_algorithm = string(argv[1]);


	if(chosen_algorithm == "EXACT"){

		upper_bound = g.size() + 1;

		vector<bool> initial_guess(g.size(), false);
		vector<bool> result = exact_solve(g, g.size(), initial_guess, 0);
		
		print_result(result);

	} else if(chosen_algorithm == "GREEDY"){

		vector<bool> result = greedy_solve(g);
		
		print_result(result);

	} else if(chosen_algorithm == "LOCAL_SEARCH_NAIVE_1"){

		vector<bool> result = naive_solve(g);

		vector<bool> aux;
		int i = 0;
		
		do{
			i++;
			aux = result;
			result = local_search_1(g, result);
		}while(aux != result);

		print_result(result);

	} else if(chosen_algorithm == "LOCAL_SEARCH_GREEDY_1"){

		vector<bool> result = greedy_solve(g);

		vector<bool> aux;
		int i = 0;
		
		do{
			i++;
			aux = result;
			result = local_search_1(g, result);
		}while(aux != result);

		print_result(result);

	} else if(chosen_algorithm == "LOCAL_SEARCH_NAIVE_2"){

		vector<bool> result = naive_solve(g);

		vector<bool> aux;
		int i = 0;
		
		do{
			i++;
			aux = result;
			result = local_search_2(g, result);
		}while(aux != result);

		print_result(result);

	} else if(chosen_algorithm == "LOCAL_SEARCH_GREEDY_2"){

		vector<bool> result = greedy_solve(g);

		vector<bool> aux;
		int i = 0;
		
		do{
			i++;
			aux = result;
			result = local_search_2(g, result);
		}while(aux != result);

		print_result(result);

	} else if(chosen_algorithm == "NAIVE"){

		vector<bool> result = naive_solve(g);

		print_result(result);

	}else{

		arg_error(argv[0]);
	
	}

	return 0;

}
