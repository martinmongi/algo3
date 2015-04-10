//GENERA ENTRADAS PARA EL PROBLEMA 2 Y LAS GUARDA EN EL ARCHIVO entrada.txt

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

int main(){
	srand (time(NULL));
	int cantInstancias;
	int cantFrec_max;
	int cantFrec_min;
	int max_cost;
	int max_t;
	int ti;
	int tf;
	int cost;
	int n;
	int aux;
	
	ofstream myfile;
	cout << "ingresar la cantidad de instancias que desea generar" << endl;
	cin >> cantInstancias;
	cout << "ingresar la cantidad máxima de frecuncias para las instancias" << endl;
	cin >> cantFrec_max;
	cout << "ingresar la cantidad mínima de frecuencias para las instancias" << endl;
	cin >> cantFrec_min;
	cout << "ingresar el costo máximo para las frecuencias" << endl;
	cin >> max_cost;
	cout << "ingresar el instante máximo de tiempo" << endl;
	cin >> max_t;
	
	
  myfile.open ("entradas");

	for(int i=0; i<cantInstancias; i++){  
		//escojemos la cantidad de intervalos
		aux = cantFrec_max - cantFrec_min;
		n = cantFrec_min + (rand() % (aux));
		
		myfile << n << endl;
		
		for (int h = 0; h < n; h++){
			ti = rand() % (max_t);
			if (ti==0) ti++;
			tf = ti + (rand() % (max_t - ti));
			if (ti==tf) tf++;
			cost = rand() % (max_cost) + 1;
			myfile << cost << " " << ti << " " << tf << endl;
		}
	}
	myfile << 0 << endl;
	
  myfile.close();
  return 0;
}

