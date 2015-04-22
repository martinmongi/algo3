#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Phase{
	int BMX_cost;
	int motox_cost;
	int buggy_cost;
};

struct solEtapa{
	int fila_ant;
	int cola_ant;
	char vehiculo;
	int costo_min;
};


void llenarCostosMinimos (vector<vector<vector<solEtapa> > > & dd, int etapa, int k_b, int k_m, vector<Phase>& v);
int minimo(int usar_bmx, int usar_moto, int usar_buggy);
void devolverResultado(vector<vector<vector<solEtapa> > > & dd, int cant_etapas, int K_b, int k_m);
