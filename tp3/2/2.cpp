#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

bool min_set(vector<bool> &a, vector<bool> &b){
	int count_a = 0, count_b = 0;
	for(int i = 0; i < a.size(); i++){
		if(a[i])
			count_a++;
		if(b[i])
			count_b++;
	}
	return (count_a <= count_b);
}

bool dominant(vector<vector<bool> > &g, vector<bool> &v){
	// cout << "Probando dominante:\n";
	// for(int i = 0; i < v.size(); i++){
	// 	cout << v[i] << " ";
	// }
	// cout << "\n";

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
	// cout << "DOMINANT" << endl;
	return true;
}
bool independent(vector<vector<bool> > &g, vector<bool> &v){
	
	// cout << "Probando independiente:\n";
	// for(int i = 0; i < v.size(); i++){
	// 	cout << v[i] << " ";
	// }
	// cout << "\n";

	//independence check
	for(int i = 0; i < v.size(); i++){
		if(v[i]){
			for(int j = i + 1; j < v.size(); j++){
				if(v[j] && g[i][j])
					return false;
			}
		}
	}
	
//	cout << "INDEPENDENT" << endl;
	return true;

}

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
			if(min_set(sol1,sol2))
				return sol1;
			else
				return sol2;
	}
}

int main(){
	int vertices, edges, a, b;
	cin >> vertices;

	vector<vector<bool> > g(vertices, vector<bool>(vertices, false));

	while(true){
		cin >> a >> b;
		if(cin.eof()) break;
		assert(a < vertices);
		assert(b < vertices);
		g[a][b] = true;
		g[b][a] = true;
	}
/*
	for(int i = 0; i < vertices; i++){
		cout << "Adyacentes a " << i << ":\n";
		for(int j = 0; j < vertices; j++){
			if(g[i][j])
				cout << j << " ";
		}
		cout << "\n";
	}*/

	vector<bool> initial_guess(vertices, false);
	vector<bool> result = solve(g, vertices, initial_guess, 0);
	for(int i = 0; i < result.size(); i++){
		cout << result[i]<< " ";
	}
	cout << "\n";
}