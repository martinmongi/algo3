#include "problema_1.h"

#define SPACE " "

using namespace std;

int main(){
    
	int n, P, cost, C = 0;
        /* 
         * Entrada primera línea: 
         * n: cantidad de ciudades
         * P: presupuesto
         */
	cin >> n >> P;
	vector<City> cities(n);
	
        /* 
         * Entrada n líneas siguientes: Para cada ciudad se recibe
         * z: cantidad de zombies
         * s: cantidad de soldados asignados
         * c: costo por cada soldado extra
         */
	for(int i = 0; i < n; i++){
		cities[i].id = i;
		cin >> cities[i].z >> cities[i].s >> cities[i].c;
                // Cálculo y almacenamiento del costo total para salvar la ciudad
		cost = ((int)ceil(((double) cities[i].z)/10) - cities[i].s) * cities[i].c;
		cities[i].cost = cost > 0 ? cost : 0;
	}

        /*
         * Resolución
         */        
        // Se ordenan las ciudades por el costo total calculado de menor a mayor costo
	sort(cities.begin(), cities.end(), compare_cities_cost);

        // Por cada ciudad se decide si alcanza el presupuesto para salvarla o no
        // Si alcanza, se marca la ciudad como salvable, se descuenta del
        // presupuesto el costo de salvarla y se la cuenta como salvada
        // Si no alcanza el presupuesto se la marca como no salvable
	for(int i = 0; i < n; i++){
		if(cities[i].cost <= P){
			cities[i].saveable = true;
			P -= cities[i].cost;
			C++;
		}else{
			cities[i].saveable = false;
		}
	}
        
        /*
         * Salida:
         * C: cantidad de ciudades salvadas
         * sold: soldados enviados a cada ciudad
         */
        
	cout << C << SPACE;

        // Se ordenan las ciudades por id
	sort(cities.begin(), cities.end(), compare_cities_id);

        // Para cada ciudad, si es salvable se calcula cuantos soldados se enviaron,
        // si no se devuelve 0
	for(int i = 0; i < n; i++){
		if(cities[i].saveable){
			int sold = ((int)ceil(((double) cities[i].z)/10) - cities[i].s);
			cout << (sold > 0 ? sold : 0);
		}else{
			cout << "0";
		}
		if(i != n - 1){
			cout << SPACE;
		}else{
			cout << "\n";
		}
	}
}