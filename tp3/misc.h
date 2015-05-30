#include <iostream>
#include <vector>
#include <set>
#include <cassert>

#define SPACE " "
#define NEWLINE "\n"

using namespace std;

//O(n)
int v_count(vector<bool> &a){
	int count = 0;
	for(int i = 0; i < a.size(); i++){
		if(a[i])
			count++;
	}
	return count;
}

//O(n)
template <typename T>
void print_vector(vector<T> &v){
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	cout << "\n";
}

void print_result(vector<bool> &v){
	cout << v_count(v) << SPACE;
	for(int i = 0; i < v.size(); i++){
		if(v[i])
		cout << i+1 << " ";
	}
	cout << NEWLINE;
}

vector<vector<bool> > graph_input(){
	int a, b, vertices, edges;
	cin >> vertices >> edges;
	vector<vector<bool> > g(vertices, vector<bool>(vertices, false));

	while(edges--){
		cin >> a >> b;
		a--; b--;
		assert(a < vertices);
		assert(b < vertices);
		g[a][b] = true;
		g[b][a] = true;
	}
	return g;
}



//O(v^2)
bool dominant(vector<vector<bool> > &g, vector<bool> &v){
	
	vector<bool> seen(v.size(), false);
	for(int i = 0; i < v.size(); i++){
		if(v[i]){
			seen[i] = true;
			for(int j = 0; j < v.size(); j++){
				if(g[i][j])
					seen[j] = true;
			}
		}
	}

	for(int i = 0; i < v.size(); i++){
		if(!seen[i])
			return false;
	}

	return true;
}

//O(v^2)
bool independent(vector<vector<bool> > &g, vector<bool> &v){
	
	for(int i = 0; i < v.size(); i++){
		if(v[i]){
			for(int j = i + 1; j < v.size(); j++){
				if(v[j] && g[i][j])
					return false;
			}
		}
	}
	
	return true;
}

void arg_error(std::string program_name){
	std::cout << "Especifique el algoritmo que desea usar:" << std::endl;
	std::cout << "\t" << program_name << " EXACT" << std::endl;
	std::cout << "\t" << program_name << " GREEDY" << std::endl;
	std::cout << "\t" << program_name << " LOCAL_SEARCH" << std::endl;
	std::cout << "\t" << program_name << " GRASP" << std::endl;
}