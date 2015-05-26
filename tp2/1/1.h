#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Phase{		//representa el costo de usar un vehiculo dada una etapa
	int BMX_cost;
	int motox_cost;
	int buggy_cost;
};

struct minimoCase{
	//esta estructuta representa dada una etapa (E) una cantidad de usos de moto (M) y una cantidad de usos de buggy (B):
	
	int fil_ant;	//guarda el enlace (numero de fila) al costo minimo de la etapa anterior
	int col_ant;	//guarda el enlace (numero de columna) al costo minimo de la etapa anterior
	unsigned int vehiculo;	//el vehiculo que conviene usar en la etapa E
	int costo_min;	//el costo minimo de usar exactamente M motos, B buggys hasta la etapa E
};


void llenarCostosMinimos (vector<vector<vector<minimoCase> > > & dd, int etapa, int k_b, int k_m, vector<Phase>& v);
int minimo(int usar_bmx, int usar_moto, int usar_buggy);
int devolverResultado(vector<vector<vector<minimoCase> > > & dd, int cant_etapas, int K_b, int k_m, stack<unsigned int> & pila);
void imprimirDakkar(vector<vector<vector<minimoCase> > > & dd);
