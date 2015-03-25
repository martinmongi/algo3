#include "problema_1.h"

using namespace std;

int main(){
	int n, P, cost, C = 0;
	cin >> n >> P;
	vector<City> cities(n);
	
	for(int i = 0; i < n; i++){
		cities[i].id = i;
		cin >> cities[i].z >> cities[i].s >> cities[i].c;
		cost = ((int)ceil(((double) cities[i].z)/10) - cities[i].s) * cities[i].c;
		cities[i].cost = cost > 0 ? cost : 0;
	}

	sort(cities, compare_cities_cost);


	for(int i = 0; i < n; i++){
		if(cities[i].cost <= P){
			cities[i].saveable = true;
			P -= cities[i].cost;
			C++;
		}else{
			cities[i].saveable = false;
		}
		//cout << cities[i].id << "\t" << cities[i].z << "\t" << cities[i].s << "\t" << cities[i].c << "\t" << cities[i].cost << "\t" << cities[i].saveable << endl;
	}
	cout << C << " ";

	for(int i = 0; i < n; i++){
		if(cities[i].saveable){
			cout << cities[i].cost / cities[i].c;
		}else{
			cout << "0";
		}
		if(i != n - 1){
			cout << " ";
		}else{
			cout << "\n";
		}
	}
}