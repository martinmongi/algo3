/**
 * Ejercicio 1 - Zombieland.
 */
#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include <stdint.h>
#include <cmath>

#define MEDIR  0 // para medir tiempo, poner en 1

using namespace std;


struct Ciudad {
    int zombies;
    int soldados;
    int costo;

    int costo_total;
    int refurezo;
};

struct Estado {
      int presupuesto;
      vector<Ciudad> ciudades;

      int ciudades_a_recuperar;
};

/**
 * Función de comparacion para pares. (lo usa sort)
 * @param pair x
 * @param pair y
 * @return bool x < y
 */
bool comp(pair<int,int> x, pair<int,int> y) {
                return x.first < y.first;
}

/**
 * Guardar el estado de la ciudad que vienen de stdin.
 * @param referencia al pais donde voy a guardar el estado
 * @param int n cantidad de ciudades en la entrada
 * @return int 0 si esta todo bien, -1 si hay alguna linea mal formada.
 */
int cargar_ciudades (Estado & pais, int n) {

        int z,s,c;
        Ciudad ciudad;

        for (int j = 0; j < n; j++){
                cin >> z >> s >> c;
                /* Chequeo simple de naturales */
                if(z < 0 || s < 0  || c < 0){
                        cout << "error: z=" << z << " s=" << s << " c=" << c << "\n";
                        return -1;
                }

                ciudad.zombies = z;
                ciudad.soldados = s;
                ciudad.costo = c;

                pais.ciudades.push_back(ciudad);
        }
        return 0;
}


/**
 * Obtener una solucion a partir del  estado del pais.
 * @param Estado del país 
 * @param vector<pair<int,int> > solucion del problema
 * @return int solucion al problema (cantidad de ciudades recuperables)
 */
int recuperar_pais(Estado & pais, vector<pair<int,int> > & solucion) {

        /* Preparar la solucion */
        for (int j = 0; j < pais.ciudades.size() ; j++){
            int zombies = pais.ciudades[j].zombies;
            int soldados = pais.ciudades[j].soldados;

            int refurezo = zombies/10 + (zombies % 10 > 0 )*1 - soldados;
            if(refurezo < 0){
                refurezo = 0; // hay mas soldados que zombies
            }

            pais.ciudades[j].refurezo = refurezo;

            int costo_total = pais.ciudades[j].costo*refurezo;
            pair<int,int> r = make_pair(costo_total,j); 

            /* Agrego <costo_total,ciudad>*/
            solucion.push_back(r);
        }

        /* Ordenamos los costos*/
        sort(solucion.begin(), solucion.end(),comp);
        
        int P = pais.presupuesto;

        for( int i = 0; i < solucion.size(); i++) {
            if( P - solucion[i].first >= 0){
                P = P - solucion[i].first;
                pais.ciudades_a_recuperar++;
            } else{
                pais.ciudades[solucion[i].second].refurezo = 0;
            }

                       
        }

        return pais.ciudades_a_recuperar;

}

int main() {

        int n, P;
        Estado pais;


        vector<pair<int,int> > solucion;

        /* Cosas para medir tiempo (ticks de clock) */
        unsigned int tiempo0, tiempo1, tiempod0, tiempod1;
        uint64_t aux, tiempo;


        while(cin >> n >> P) {
                /* inicializamos el estado de la ciudad */
                solucion.clear();

                pais.ciudades_a_recuperar = 0;
                pais.presupuesto = P;
                pais.ciudades.clear();

                if(cargar_ciudades(pais, n) == -1){
                        cout << " Intervalo mal formado" << endl;
                        return -1;
                }

                /* medir tiempo inicial */
                __asm__ ("cpuid\n\t"
                         "rdtsc" : "=a"(tiempo0),  "=d"(tiempod0));

                /* Obtener la solucion. Devolver la cantidad de ciudades.*/
                int C = recuperar_pais(pais, solucion);


                /* medir tiempo final*/
                __asm__ ("cpuid\n\t"
                         "rdtsc" : "=a"(tiempo1),  "=d"(tiempod1));

                /* Calcular el tiempo: final - inicial */
                if(tiempod1 == tiempod0){
                        tiempo = (uint64_t)(tiempo1 - tiempo0);

                }else{
                        aux = ((uint64_t)(tiempod0) << 32 ) | (uint64_t)(tiempo0);
                        tiempo = ((uint64_t)(tiempod1) << 32 ) | (uint64_t)(tiempo1);
                        tiempo -= aux;
 
                }


                if(MEDIR){
                        /* Medimos tiempo, la salida es: n tiempo */
                        cout << n << " " << tiempo << endl;

                }else{
                        /* No medimos, la salida es lo que pide el tp*/
                        cout << C ;
                        for(int i = 0; i < n ; i++){
                            cout << " " << pais.ciudades[i].refurezo;
                        }
                        cout <<  endl;

                }
 
        }
 
        return 0;
}
