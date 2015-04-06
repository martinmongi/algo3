//GENERA ENTRADAS PARA EL PROBLEMA 2 Y LAS GUARDA EN EL ARCHIVO entrada.txt

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>

using namespace std;

int main(){
	srand (time(NULL));
	int max_cost;
	int max_t;
	int ti;
	int tf;
	int n;
	int cost;
	ofstream myfile;

	cin >> n;
	cin >> max_t;
	cin >> max_cost;
	
	
  myfile.open ("entradas");

	
    myfile << n << endl;
	  
    for (int h = 0; h < n; h++){
      	ti = rand() % (max_t) + 1;
		tf = ti + (rand() % (max_t - ti)) +1;
		cost = rand() % (max_cost) + 1;
		myfile << cost << " " << ti << " " << tf << endl;
    }

  myfile.close();
  return 0;
}

