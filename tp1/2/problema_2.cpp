#include "problema_2.h"
#include <iostream>

using namespace std;

#define SPACE " "

int main(){
	int n, i;
	cin >> n;
	vector<Frequency> frequencies(n);

	for(i = 0; i < n; i++){
		cin >> frequencies[i].cost >> frequencies[i].i >> frequencies[i].f;
		frequencies[i].id = i + 1;
	}

	vector<Frequency> out = solve(frequencies);
	int total_cost = 0;

	for(i = 0; i < out.size(); i++){
		total_cost += (out[i].f - out[i].i) * out[i].cost;		
	}

	cout << total_cost << endl;
	for(i = 0; i < out.size(); i++){
		cout << out[i].i << SPACE << out[i].f << SPACE << out[i].id << endl;
	}
	cout << "-1" << endl;
	return 0; 
}

vector<Frequency> solve(vector<Frequency> &v){
	vector <Frequency> a, b;
	int n = v.size(), i;
	for(i = 0; i < n/2; i++){
		a.push_back(v[i]);
	}
	for(i = n/2 ; i < n; i++){
		b.push_back(v[i]);
	}

	return merge_frequencies(a,b);
}

vector<Frequency> merge_frequencies(vector<Frequency> &a, vector<Frequency> &b){
	vector<Frequency> a1, a2, out, out_a, out_b, b1, b2;
	int i;
	int na = a.size();
	int nb = b.size();

	if(na == 0 && nb == 0){
		return out;
	}else if(nb == 0){
		for(i = 0; i < na; i++)
			out.push_back(a[i]);
		return out;
	}else if(na == 0){
		for(i = 0; i < nb; i++)
			out.push_back(b[i]);
		return out;
	}

	for(i = 0; i < na/2; i++){
		a1.push_back(a[i]);
	}
	for(i = na/2 ; i < na; i++){
		a2.push_back(a[i]);
	}
	out_a = merge_frequencies(a1, a2);

	for(i = 0; i < nb/2; i++){
		b1.push_back(b[i]);
	}
	for(i = nb/2 ; i < nb; i++){
		b2.push_back(b[i]);
	}
	out_b = merge_frequencies(b1, b2);


	int offset_a = 0, offset_b = 0;
	
	while(offset_a < na && offset_b < nb){
		if(out_a[offset_a].cost > out_b[offset_b].cost){

			if(out_a[offset_a].i >= out_b[offset_b].i){

				if(out_a[offset_a].f > out_b[offset_b].f){ //opcion 1 y 4
					out.push_back(out_b[offset_b]);
					out_a[offset_a].i = out_b[offset_b].f;
					offset_b++;
				} else {
					out.push_back(out_b[offset_b]); //opcion 2,3,5 y 6
					offset_a++;
					offset_b++;
				}
			} else if(out_a[offset_a].i < out_b[offset_b].i){ //opcion 7, 8 y 9
					Frequency wait = out_a[offset_a];
					wait.f = out_b[offset_b].i;
					out.push_back(wait);
					out_a[offset_a].i = out_b[offset_b].i; 
			}
		} else { //lo mismo de arriba pero dado vuelta

			if(out_b[offset_b].i >= out_a[offset_a].i){

				if(out_b[offset_b].f > out_a[offset_a].f){ //opcion 1 y 4
					out.push_back(out_a[offset_a]);
					out_b[offset_b].i = out_a[offset_a].f;
					offset_a++;
				} else {
					out.push_back(out_a[offset_a]); //opcion 2,3,5 y 6
					offset_a++;
					offset_b++;
				}
			} else if(out_b[offset_b].i < out_a[offset_a].i){ //opcion 7, 8 y 9
					Frequency wait = out_b[offset_b];
					wait.f = out_a[offset_a].i;
					out.push_back(wait);
					out_b[offset_b].i = out_a[offset_a].i; 
			}
		}
	}

	while(offset_a < na){
		out.push_back(out_a[offset_a]);
		offset_a++;
	}

	while(offset_b < nb){
		out.push_back(out_b[offset_b]);
		offset_b++;
	}

	return out;
}