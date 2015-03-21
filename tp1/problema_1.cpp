#include "problema_1.h"

using namespace std;

int main(){
	int n, P, cost;
	cin >> n >> P;
	vector<City> cities(n);
	
	for(int i = 0; i < n; i++){
		cin >> cities[i].z >> cities[i].s >> cities[i].c;
		cost = ((int)ceil(((double) cities[i].z)/10) - cities[i].s) * cities[i].c;
		cities[i].cost = cost > 0 ? cost : 0;
	}

	for(int i = 0; i < n; i++)
		cout << cities[i].z << "\t" << cities[i].s << "\t" << cities[i].c << "\t" << cities[i].cost << endl;




	// sort(cities, naive_compare);

	// for(int i = 0; i < 10; i++){
	// 	cout << cities[i] << endl;
	// }
}