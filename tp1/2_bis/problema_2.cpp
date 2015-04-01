#include "problema_2.h"
#include <iostream>

using namespace std;

#define SPACE " "

int main(){
	int n, i;
	cin >> n;
	vector<Frequency> frequencies(n);

	for(i = 0; i < n; i++)
        {
		cin >> frequencies[i].cost >> frequencies[i].start >> frequencies[i].end;
		frequencies[i].id = i + 1;
	}

	vector<Frequency> out = solve(frequencies);
	vector<Frequency> clean_out;
	int total_cost = 0;
	int final = -1;

	for(i = 0; i < out.size(); i++)
        {
		if (out[i].start >= final)
                {
			final = out[i].end;
			total_cost += (out[i].end - out[i].start) * out[i].cost;
			clean_out.push_back(out[i]);
		}		
	}

	cout << total_cost << endl;
	for(i = 0; i < clean_out.size(); i++)
        {
		cout << clean_out[i].start << SPACE << clean_out[i].end << SPACE << clean_out[i].id << endl;
	}
	cout << "-1" << endl;
	return 0; 
}

vector<Frequency> solve(vector<Frequency> &v){
	vector <Frequency> subv1, subv2;
	int v_size = v.size();
	
        for(int i = 0; i < v_size/2; i++)
        {
		subv1.push_back(v[i]);
	}
	for(int i = v_size/2 ; i < v_size; i++)
        {
		subv2.push_back(v[i]);
	}

	return merge_frequencies(subv1,subv2);
}

vector<Frequency> merge_frequencies(vector<Frequency> &subv1, vector<Frequency> &subv2){
	vector<Frequency> subv1_1, subv1_2, out, out_subv1, out_subv2, subv2_1, subv2_2;
	int i;
	int subv1_size = subv1.size();
	int subv2_size = subv2.size();
        
        /* Casos base */

        // Si ambos vectores están vacíos, devuelve un vector vacío
	if(subv1_size == 0 && subv2_size == 0)
        {
		return out;
	}
        // Si el subvector1 está vacío, devuelve el subvector2
        else if(subv2_size == 0)
        {
                for(i = 0; i < subv1_size; i++)
                {
                        out.push_back(subv1[i]);
                }
                return out;
	}
        // Si el subvector2 está vacío, devuelve el subvector1
        else if(subv1_size == 0)
        {
                for(i = 0; i < subv2_size; i++)
                {
                        out.push_back(subv2[i]);
                }
                return out;
	}

        
        /* Paso recursivo */
        
	for(i = 0; i < subv1_size/2; i++)
        {
		subv1_1.push_back(subv1[i]);
	}
	
        for(i = subv1_size/2 ; i < subv1_size; i++)
        {
		subv1_2.push_back(subv1[i]);
	}
	
        out_subv1 = merge_frequencies(subv1_1, subv1_2);

	
        for(i = 0; i < subv2_size/2; i++)
        {
		subv2_1.push_back(subv2[i]);
	}
	
        for(i = subv2_size/2 ; i < subv2_size; i++)
        {
		subv2_2.push_back(subv2[i]);
	}
	
        out_subv2 = merge_frequencies(subv2_1, subv2_2);


        /* El merge propiamente dicho */
	int offset_subv1 = 0, offset_subv2 = 0;
              
	while(offset_subv1 < subv1_size && offset_subv2 < subv2_size){
	//cout << "freqs: " << out_a[offset_a].id << SPACE << out_a[offset_a].i << SPACE << out_a[offset_a].f << endl; 
	//cout << "freqs: " << out_b[offset_b].id << SPACE << out_b[offset_b].i << SPACE << out_b[offset_b].f << endl; 
                
		if(out_subv1[offset_subv1].cost > out_subv2[offset_subv2].cost)
                {
			if(out_subv1[offset_subv1].start >= out_subv2[offset_subv2].start)
                        {
				if(out_subv1[offset_subv1].end > out_subv2[offset_subv2].end)
                                {       
                                        // Si el costo de la frecuencia 1 es mayor que el de la 2,
                                        // empieza y termina después, se toma la frecuencia 2 desde
                                        // que empieza hasta que termina para el merge final, y donde
                                        // y se modifica el comienzo de la frecuencia 1 para que
                                        // comience donde terminó la frecuencia 2
                                        out.push_back(out_subv2[offset_subv2]);
                                        out_subv1[offset_subv1].start = out_subv2[offset_subv2].end;
                                        offset_subv2++;
				}
                                else 
                                {
					// Igual que el anterior, pero la frecuencia 2 termina después 
                                        // que la 1, por lo que se toma la frecuencia 2 de principio a fin y se 
                                        // descarta la 1
                                        out.push_back(out_subv2[offset_subv2]);
                                        offset_subv1++;
                                        offset_subv2++;
				}
			} 
                        else if(out_subv1[offset_subv1].start < out_subv2[offset_subv2].start)
                        { 
                                // En caso que la frecuencia 1 (de mayor costo) empiece antes
                                // que la 2, se toma la frecuencia 1 hasta que comienza la 2
                                // y se la agrega al merge final
                            	Frequency wait = out_subv1[offset_subv1];
				wait.end = out_subv2[offset_subv2].start;
				out.push_back(wait);
				out_subv1[offset_subv1].start = out_subv2[offset_subv2].start; 
			}
		} 
                else 
                { 
                        // Se repite lo mismo que en la sentencia anterior, pero siendo el costo
                        // de la frecuencia 2 mayor que el de la frecuencia 1
			if(out_subv2[offset_subv2].start >= out_subv1[offset_subv1].start)
                        {
				if(out_subv2[offset_subv2].end > out_subv1[offset_subv1].end)
                                { 
					out.push_back(out_subv1[offset_subv1]);
					out_subv2[offset_subv2].start = out_subv1[offset_subv1].end;
					offset_subv1++;
				}
                                else 
                                {
					out.push_back(out_subv1[offset_subv1]);
					offset_subv1++;
					offset_subv2++;
				}
			} 
                        else if(out_subv2[offset_subv2].start < out_subv1[offset_subv1].start)
                        { 
				Frequency wait = out_subv2[offset_subv2];
				wait.end = out_subv1[offset_subv1].start;
				out.push_back(wait);
				out_subv2[offset_subv2].start = out_subv1[offset_subv1].start; 
			}
		}
	}

	while(offset_subv1 < subv1_size)
        {
		out.push_back(out_subv1[offset_subv1]);
		offset_subv1++;
	}

	while(offset_subv2 < subv2_size)
        {
		out.push_back(out_subv2[offset_subv2]);
		offset_subv2++;
	}

	return out;
}