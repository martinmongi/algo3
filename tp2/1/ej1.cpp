#include "1.h"
#include <limits.h>
#include <algorithm>

#define BMX 1
#define MOTOX 2
#define BUGGY 3
#define SPACE ' '
#define VECT_DE_MATRIZ vector<vector<vector<minimoCase> > >

using namespace std;

/****************************estructuras y cosas a tener en cuenta*********************************************************
 Hay 2 estructuras principales donde se guardan los datos:
 * vector<Phase> race(n)   que guarda los costos para cada etapa (vector indexado por etapa, desde 0 hasta n-1)
 * VECT_DE_MATRIZ dakkar
		que se puede interpretar como un vector de matrices (cubo de componentes X,Y,Z), donde cada componente es:
			*la primera componente (X) corresponde a la etapa (de 0 hasta n-1)
			*la segunda (Y) corresponde a la cantidad de veces exactamente que se uso el buggi hasta la etapa X
			*la tercera (Z) identifica la cantidad de veces que se uso la moto hasta la etapa X
			*Cada elemento del cubo guarda el minimo costo de usar hasta la etapa X, Y buggis y Z motos exactamente;
				el vehiculo que conviene usar en la etapa X dado Y, Z; ademas de guardar el (Y,Z) de la etapa anterior
*De aqui en mas el cubo "dakkar" se indexara de la siguiente manera dakkar[X][Y][Z] = mCase (estructura minimoCase)
* donde:
		*mCase.vehiculo representa el vehiculo que conviene usar para la etapa X habiendo usado hasta dicha etapa Y buggys y Z motos
		*mCase.costo_min representa el costo mínimo de usar Y buggys y Z motos hasta la etapa X (sin tomar en cuenta las etapas siguientes)
		*mCase.fil_ant y m.col_ant es una referencia al resultado de la etapa X-1 
**********************************************************************************************************************/

int main(){
	int n, km, kb;
	cin >> n >> km >> kb;
	vector<Phase> race(n);
				
	for(int i = 0; i < n; i++)
		cin >> race[i].BMX_cost >> race[i].motox_cost >> race[i].buggy_cost;
		
	VECT_DE_MATRIZ dakkar(n);
	
	for(int i=0; i<n; i++){
		dakkar[i].resize(kb+1);
		for (int b=0; b<kb+1; b++){
			dakkar[i][b].resize(km+1);
			for(int m=0; m<km+1; m++){
				dakkar[i][b][m].fil_ant = 0;
				dakkar[i][b][m].col_ant = 0;
				dakkar[i][b][m].costo_min = INT_MAX;
				dakkar[i][b][m].vehiculo = 5;
			}
		}
	}
	
	int etapa_actual = 0;	//componente X que representa a la etapa va desde 0 a n-1
	//comienzo llenando la matriz para la etapa X=cero y los Y, Z correspondientes
	//dakkar[X][Y][Z]
	if (n > 0){//si hay por lo menos una etapa:
		//el minimo costo de usar Y=0 buggis y Z=0 motos hasta la primera etapa (etapa X=0) es usar la BMX, entonces:
		dakkar[etapa_actual][0][0].costo_min = race[etapa_actual].BMX_cost;
		dakkar[etapa_actual][0][0].vehiculo = BMX;
		dakkar[etapa_actual][0][0].fil_ant = 0;
		dakkar[etapa_actual][0][0].col_ant = 0;
		
		//el minimo costo de usar Y=1 buggi y Z=0 motos hasta la primera etapa (X=0)
		dakkar[etapa_actual][1][0].costo_min = race[etapa_actual].buggy_cost;
		dakkar[etapa_actual][1][0].vehiculo = BUGGY;
		dakkar[etapa_actual][1][0].fil_ant = 0;
		dakkar[etapa_actual][1][0].col_ant = 0;
		
		//el minimo costo de usar Y=0 buggis y Z=1 motos hasta la primera etapa (X=0)
		dakkar[etapa_actual][0][1].costo_min = race[etapa_actual].motox_cost;
		dakkar[etapa_actual][0][1].vehiculo = MOTOX;
		dakkar[etapa_actual][0][1].fil_ant = 0;
		dakkar[etapa_actual][0][1].col_ant = 0;
	}
	etapa_actual ++;
	
	while(etapa_actual < n){
		llenarCostosMinimos(dakkar, etapa_actual, kb, km, race);
		etapa_actual ++;
	}
	//imprimirDakkar(dakkar);
	
	devolverResultado(dakkar, n-1, kb, km);
}

void llenarCostosMinimos (VECT_DE_MATRIZ & dd, int e, int k_b, int k_m, vector<Phase>& v){
	int etapa_ant = e-1;
	int coste_usar_buggy = INT_MAX;
	int coste_usar_moto = INT_MAX;
	int coste_usar_bmx = INT_MAX;
	int coste_min;
	int min_1 = min(e+1,k_b);
	int min_2 = min(e+1,k_m);
	
	for(int b = 0; b<= min_1; b++){	//b representa "Y" la cantidad exacta de buggis usadas hasta la etapa actual
		for(int m = 0; (m<= min_2) && (m+b<=e+1); m++){	//m representa "Z" la cantidad exacta de motos usadas hasta la etapa actual
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
					dd[e][b][m].fil_ant = b;
					dd[e][b][m].col_ant = m;
					break;
				case MOTOX:
					dd[e][b][m].costo_min = coste_usar_moto;
					dd[e][b][m].vehiculo = MOTOX;
					dd[e][b][m].fil_ant = b;
					dd[e][b][m].col_ant = m-1;
					break;
				case BUGGY:
					dd[e][b][m].costo_min = coste_usar_buggy;
					dd[e][b][m].vehiculo = BUGGY;
					dd[e][b][m].fil_ant = b-1;
					dd[e][b][m].col_ant = m;
					break;
			}
			
			coste_usar_buggy = INT_MAX;
			coste_usar_moto = INT_MAX;
			coste_usar_bmx = INT_MAX;
			
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

void devolverResultado(VECT_DE_MATRIZ & dd, int ultima_etapa, int k_b, int k_m){
	int aux = min(ultima_etapa+1, k_b);
	int aux_2 = min(ultima_etapa+1, k_m);
	int y,z;
	int valor_minimo = INT_MAX;
	unsigned int vehiculo;
	stack<unsigned int> pila;
	for(int b=0; b<=aux; b++){
		for(int m=0; m<=aux_2; m++){
			if(valor_minimo > dd[ultima_etapa][b][m].costo_min){
				valor_minimo = dd[ultima_etapa][b][m].costo_min;
				y = b;
				z = m;
			}
		}
	}
	
	cout << valor_minimo;
	for(int i=0; i<=ultima_etapa; i++){
		pila.push(dd[ultima_etapa - i][y][z].vehiculo);
		y = dd[ultima_etapa - i][y][z].fil_ant;
		z = dd[ultima_etapa - i][y][z].col_ant;
	}
	
	while (!pila.empty()){
		vehiculo = pila.top();
		cout << " " << vehiculo;
		pila.pop();
	}
	
	cout << endl;
}

void imprimirDakkar(VECT_DE_MATRIZ & dd){
	for(unsigned int x=0; x<dd.size(); x++){
		cout << "-------------ETAPA N=" << x <<"-------------"<< endl;
		cout << "-------------------------------------------------"<< endl; 
		for(unsigned int y=0; y<dd[x].size(); y++){
			cout << "----buggys: "<< y << "------------"<< endl;
			for(unsigned int z=0; z<dd[x][y].size(); z++){
				cout << "["<<x<<"]["<<y<<"]["<<z<<"].y_ant = "<<dd[x][y][z].fil_ant<<" ||";
				cout << "["<<x<<"]["<<y<<"]["<<z<<"].z_ant = "<<dd[x][y][z].col_ant<<" ||";
				cout << "["<<x<<"]["<<y<<"]["<<z<<"].vehic = "<<dd[x][y][z].vehiculo<<" ||";
				cout << "["<<x<<"]["<<y<<"]["<<z<<"].c_min = "<<dd[x][y][z].costo_min <<endl;
			}
			
		}
	}
	cout << "-------------FIN----DAKKAR-------------"<< endl;
	cout << "------------------------------------------------"<< endl;
}
