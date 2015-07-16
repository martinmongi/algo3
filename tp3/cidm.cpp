#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <chrono>
#include <ctime>
#include <ratio>
#include <algorithm>
#include "misc.h"

#define TAB '\t'
using namespace std;
int ub;

vector<bool> exact_solve(vector<vector<bool> > &g, vector<bool> v, int i){
	int vertices = g.size();
	if(i == vertices){
		if(dominant(g,v) && independent(g,v)){
			ub = min(ub, v_count(v));
			return v;
		}
		else
			return vector<bool>();
	}


	// pruning better_solution_already_found
	if(ub < v_count(v))
		return vector<bool>();

	// pruning solution_already_dependent
	if(!independent(g,v))
		return vector<bool>();

	vector<bool> sol1 = exact_solve(g, v, i + 1);
	v[i] = true; 
	vector<bool> sol2 = exact_solve(g, v, i + 1);
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

	while(v_count(taken) < g.size()){

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

vector<bool> greedy_randomized(vector<vector<bool> > &g, double p){

	int potential_vertices, best_vertex, rcl_size;
	vector<pair<int, int> > vertex_value;
	pair<int, int> buffer_pair;
	vector<bool> taken(g.size(), false);
	vector<bool> vertices(g.size(), false);

	while(v_count(taken) < g.size()){

		//choose vertex that takes the most not taken vertices
		vertex_value = vector<pair<int, int> >();

		for(int i = 0; i < g.size(); i++){
			potential_vertices = 0;
			if(!taken[i]){
				potential_vertices++;
				for(int j = 0; j < g.size(); j++){
					if(g[i][j] && !taken[j])
						potential_vertices++;
				}
				buffer_pair.first = i;
				buffer_pair.second = potential_vertices;
				vertex_value.push_back(buffer_pair);
			}
		}

		sort(vertex_value.begin(), vertex_value.end(), compare_vertices);


		rcl_size = vertex_value.size()*(1-p);

		if(rcl_size == 0) rcl_size++;

		int vertex_i = rand() % rcl_size;

		best_vertex = vertex_value[vertex_i].first;

		vertices[best_vertex] = true;
		taken[best_vertex] = true;
		for(int j = 0; j < g.size(); j++){
			if(g[best_vertex][j])
				taken[j] = true;
		}

	}

	return vertices;
}

vector<bool> grasp_solve(vector<vector<bool> > &g, double p, int iterations){

	vector<bool> best_solution(g.size(), true);
	int i = iterations;

	while(i--){
		// cout << i << endl;
		vector<bool> res = greedy_randomized(g, p);

		vector<bool> res_local = local_search_2(g, res);

		if(v_count(res_local) < v_count(best_solution)){
			best_solution = res_local;
			//print_result(best_solution);
			i = iterations;
		}
	}

	return best_solution;
}

int main(int argc, char* argv[]){

	

	if(argc < 2){
		arg_error(argv[0]);
		return 0;
	}

	vector<bool> result;
	
	vector<vector<bool> > g = graph_input();

	string chosen_algorithm = string(argv[1]);

	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

	if(chosen_algorithm == "EXACT"){

		ub = g.size() + 1;

		vector<bool> initial_guess(g.size(), false);

		result = exact_solve(g, initial_guess, 0);		

	} else if(chosen_algorithm == "GREEDY"){

		result = greedy_solve(g);

	} else if(chosen_algorithm == "LOCAL_SEARCH_NAIVE_1"){

		result = naive_solve(g);

		vector<bool> aux;
		int i = 0;
		
		do{
			//cerr << i << endl;
			i++;
			aux = result;
			result = local_search_1(g, result);
		}while(aux != result);

	} else if(chosen_algorithm == "LOCAL_SEARCH_GREEDY_1"){

		result = greedy_solve(g);

		vector<bool> aux;
		int i = 0;
		double ts = 0;
		
		do{
			//chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
			i++;
			aux = result;
			result = local_search_1(g, result);
			//chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
			//chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
			//ts = time_span.count();

		}while(aux != result);

		//cerr << g.size() <<  "; " << i <<  "; " << ts << endl;

	} else if(chosen_algorithm == "LOCAL_SEARCH_NAIVE_2"){

		result = naive_solve(g);

		vector<bool> aux;
		int i = 0;
		
		do{
			i++;
			aux = result;
			result = local_search_2(g, result);
		}while(aux != result);

	} else if(chosen_algorithm == "LOCAL_SEARCH_GREEDY_2"){

		result = greedy_solve(g);

		vector<bool> aux;
		int i = 0;
		
		do{

			i++;
			aux = result;
			result = local_search_2(g, result);
		}while(aux != result);

	} else if(chosen_algorithm == "NAIVE"){

		result = naive_solve(g);

	} else if(chosen_algorithm == "GRASP"){

		double p;
		int iterations;

		if(argc <= 2)
			p = 0.5;
		else
			p = atof(argv[2]);

		if(argc <= 3)
			iterations = 100;
		else
			iterations = atoi(argv[3]);

		srand(time(NULL));

		result = grasp_solve(g, p, iterations);

	}else{

		arg_error(argv[0]);
	
	}

	chrono::steady_clock::time_point t2 = chrono::steady_clock::now();

	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

	int edges = 0, vertices;

	vertices = g.size();

	for(int i = 0; i < vertices; i++){
		for(int j = i + 1; j < vertices; j++){
			if(g[i][j])
				edges++;
		}
	}
	cerr << vertices << TAB << edges << TAB << time_span.count() << TAB << v_count(result) << std::endl;		

	print_result(result);

	return 0;

}
