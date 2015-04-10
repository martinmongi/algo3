/*
 * Generador de instancias para Ej1 
 *   genera una instancia al azar de n ciudades,
 *    Argumentos:
 *      n -> cantidad de ciudades
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(int argc, char* argv[]){
        if(argc < 2){
                printf("\nUso: %s n\n",argv[0]);
                printf("\ngenera una instancia al azar de n ciudades, \n");
                return 0;
        }
        srand (time(NULL)); /* inicializar semilla */

        int n = atoi(argv[1]);
        int P = rand() % 100*n + 10*n; /* Presupuesto [n , 100*n]*/

        printf("%d %d\n", n, P);

        int i, j;
        for(i = 0; i < n; i++){
            int s = rand() % n;
            int z = rand() % 100*s;
            int c = rand() % (P/n);

            printf("%d %d %d\n",z,s,c);
        }

        return 0;
}
