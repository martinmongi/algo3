#include "1.h"
#include <limits.h>
#include <algorithm>

#define BMX 1
#define MOTOX 2
#define BUGGY 3
#define SPACE ' '
#define MATRIZ_INT vector<vector<int> >
#define MATRIZ_COL vector<vector<queue <char> > >
#define VECT_DE_MATRIZ vector<vector<vector<solEtapa> > >

using namespace std;

/****************************estructuras****************************
 Hay 2 estructuras principales donde se guardan los datos:
 * vector<Phase> race(n)   que guarda los costos para cada etapa (vector indexado por etapa, desde 0 hasta n-1)
 * VECT_DE_MATRIZ dakkar	que se puede interpretar como un vector de matrices (cubo de componentes X,Y,Z), donde cada componente es:
			*la primera componente (X) corresponde a la etapa (de 0 hasta n-1)
			*la segunda (Y) corresponde a la cantidad de veces exactamente que se uso el buggi hasta la etapa X
			*la tercera (Z) identifica la cantidad de veces que se uso la moto hasta la etapa X
			*Cada elemento del cubo guarda el minimo costo de usar hasta la etapa X, Y buggis y Z motos ademas de guardar el (Y,Z) de la etapa anterior 
***********************************************************************/

int main(){
	int n, km, kb;
	cin >> n >> km >> kb;
	vector<Phase> race(n);
	int etapa_actual = 0;
			
	for(int i = 0; i < n; i++)
		cin >> race[i].BMX_cost >> race[i].motox_cost >> race[i].buggy_cost;
		
	VECT_DE_MATRIZ dakkar(n);
	
	for(int i=0; i<n; i++){
		dakkar[i].resize(kb+1);
		for (int b=0; b<kb+1; b++){
			dakkar[i][b].resize(km+1);
		}
	}
	
	
	//comienzo llenando la matriz para la etapa cero
	if (n > 0){
		//el minimo costo de usar 0 buggis y 0 motos hasta la primera etapa es usar la BMX, entonces:
		dakkar[etapa_actual][0][0].costo_min = race[etapa_actual].BMX_cost;
		dakkar[etapa_actual][0][0].vehiculo = BMX;
		dakkar[etapa_actual][0][0].fila_ant = 0;
		dakkar[etapa_actual][0][0].cola_ant = 0;
		
		//el minimo costo de usar 1 buggi y 0 motos hasta la primera etapa
		dakkar[etapa_actual][1][0].costo_min = race[etapa_actual].buggy_cost;
		dakkar[etapa_actual][1][0].vehiculo = BUGGY;
		dakkar[etapa_actual][1][0].fila_ant = 0;
		dakkar[etapa_actual][1][0].cola_ant = 0;
		
		//el minimo costo de usar 0 buggis y 1 motos hasta la primera etapa
		dakkar[etapa_actual][0][1].costo_min = race[etapa_actual].motox_cost;
		dakkar[etapa_actual][0][1].vehiculo = MOTOX;
		dakkar[etapa_actual][0][1].fila_ant = 0;
		dakkar[etapa_actual][0][1].cola_ant = 0;
	}
	etapa_actual ++;
	
	while(etapa_actual < n){
		llenarCostosMinimos(dakkar, etapa_actual, kb, km, race);
		etapa_actual ++;
	}
	
	devolverResultado(dakkar, n, kb, km);
}

void llenarCostosMinimos (VECT_DE_MATRIZ & dd, int e, int k_b, int k_m, vector<Phase>& v){
	int etapa_ant = e-1;
	int coste_usar_buggy = INT_MAX;
	int coste_usar_moto = INT_MAX;
	int coste_usar_bmx = INT_MAX;
	int coste_min;
	//int aux;
	for(int b = 0; b<= e+1; b++){	//b representa la cantidad exacta de buggis usadas hasta la etapa actual
		for(int m = 0; m<= e+1; m++){	//m representa la cantidad exacta de motos usadas hasta la etapa actual
			//se puede usar b buggis y m motos hasta la etapa actual de tres maneras distintas
			
			if(b-1>=0){
				//uso buggy ahora, necesito saber el costo minimo de haber usado b-1 buggys y m motos hasta la etapa anterior 
				coste_usar_buggy = dd[etapa_ant][b-1][m].costo_min + v[e].buggy_cost;
			}
			
			if(m-1>=0){
				//uso moto ahora, necesito saber el costo minimo de haber usado b buggys y m-1 motos hasta la etapa anterior 
				coste_usar_moto = dd[etapa_ant][b][m-1].costo_min + v[e].motox_cost;
			}
			
			if(b+m < e+1){
				//uso moto ahora, necesito saber el costo minimo de haber usado b buggys y m motos hasta la etapa anterior 
				coste_usar_bmx = dd[etapa_ant][b][m].costo_min + v[e].BMX_cost;
			}
			
			//ahora buscamos el minimo de haber usado un vehiculo en la etapa actual
			coste_min = minimo(coste_usar_bmx, coste_usar_moto, coste_usar_buggy);
			switch (coste_min)
			{
				case BMX:
					dd[e][b][m].costo_min = coste_usar_bmx;
					dd[e][b][m].vehiculo = BMX;
					dd[e][b][m].fila_ant = b;
					dd[e][b][m].cola_ant = m;
					break;
				case MOTOX:
					dd[e][b][m].costo_min = coste_usar_moto;
					dd[e][b][m].vehiculo = MOTOX;
					dd[e][b][m].fila_ant = b;
					dd[e][b][m].cola_ant = m-1;
					break;
				case BUGGY:
					dd[e][b][m].costo_min = coste_usar_buggy;
					dd[e][b][m].vehiculo = BUGGY;
					dd[e][b][m].fila_ant = b-1;
					dd[e][b][m].cola_ant = m;
					break;
			}
			
		}
	}
}

int minimo(int usar_bmx, int usar_moto, int usar_buggy){
	if (usar_bmx <= usar_moto){
		if (usar_bmx <= usar_buggy){
			return BMX;
		}else{
			return BUGGY;
		}
	}else if(usar_moto <= usar_buggy){
		return MOTOX;
	}else{
		return BUGGY;
	}
}

void devolverResultado(VECT_DE_MATRIZ & dd, int cant_etapas, int k_b, int k_m){
	int aux = min(cant_etapas-1 , k_b);
	int aux_2 = min(cant_etapas-1, k_m);
	int y,z;
	int valor_minimo = INT_MAX;
	char vehiculo;
	queue<char> cola;
	for(int b=0; b<=aux; b++){
		for(int m=0; m<=aux_2; m++){
			if(valor_minimo > dd[cant_etapas-1][b][m].costo_min){
				valor_minimo = dd[cant_etapas-1][b][m].costo_min;
				y = b;
				z = m;
			}
		}
	}
	
	cout << valor_minimo << endl;
	for(int i=1; i=cant_etapas; i++){
		cola.push(dd[cant_etapas-i][y][z].vehiculo);
		y = dd[cant_etapas-i][y][z].fila_ant;
		z = dd[cant_etapas-i][y][z].cola_ant;
	}
	
	while (!cola.empty()){
		vehiculo = cola.front();
		cout << vehiculo << endl;
		cola.pop();
	}
}

