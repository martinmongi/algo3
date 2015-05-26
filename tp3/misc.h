#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

template <typename T>
void print_vector(vector<T> &v){
	for(int i = 0; i < v.size(); i++){
		cout << v[i]<< " ";
	}
	cout << "\n";
}

vector<vector<bool> > graph_input(){
	int a, b, vertices;
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
	return g;
}

int v_count(vector<bool> &a){
	int count = 0;
	for(int i = 0; i < a.size(); i++){
		if(a[i])
			count++;
	}
	return count;
}

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