#include "problema_2.h"
#include <iostream>

using namespace std;

#define SPACE " "

int main(){
	int n, i;
	cin >> n;
	vector<Frequency> frequencies(n);

	for(i = 0; i < n; i++){ //O(n)
		cin >> frequencies[i].cost >> frequencies[i].i >> frequencies[i].f;
		frequencies[i].id = i + 1;
	}

	vector<Frequency> out = solve(frequencies); //T(n)
	vector<Frequency> clean_out;
	int total_cost = 0;
	int final = -1;

	for(i = 0; i < out.size(); i++){
		if (out[i].i >= final){
			final = out[i].f;
			total_cost += (out[i].f - out[i].i) * out[i].cost;
			clean_out.push_back(out[i]);
		}		
	}

	cout << total_cost << endl;
	for(i = 0; i < clean_out.size(); i++){
		cout << clean_out[i].i << SPACE << clean_out[i].f << SPACE << clean_out[i].id << endl;
	}
	cout << "-1" << endl;
	return 0; 
}

vector<Frequency> solve(vector<Frequency> &v){
	vector <Frequency> a, b;
	int n = v.size(), i;
	for(i = 0; i < n/2; i++){//O(n)
		a.push_back(v[i]);
	}
	for(i = n/2 ; i < n; i++){//O(n)
		b.push_back(v[i]);
	}

	return merge_frequencies(a,b);//T(n)
}

vector<Frequency> merge_frequencies(vector<Frequency> &a, vector<Frequency> &b){//T(n/2)
	vector<Frequency> a1, a2, out, out_a, out_b, b1, b2;
	int i;
	int na = a.size();	//O(1)
	int nb = b.size();	//O(1)

	if(na == 0 && nb == 0){//O(1)
		return out;
	}else if(nb == 0){//O(1)
		for(i = 0; i < na; i++)//O(n/2)
			out.push_back(a[i]);
		return out;
	}else if(na == 0){//O(1)
		for(i = 0; i < nb; i++)//O(n/2)
			out.push_back(b[i]);
		return out;
	}

	for(i = 0; i < na/2; i++){//O(n/2)
		a1.push_back(a[i]);
	}
	for(i = na/2 ; i < na; i++){//O(n/2)
		a2.push_back(a[i]);
	}
	out_a = merge_frequencies(a1, a2);//T(n/4)

	for(i = 0; i < nb/2; i++){//O(n/2)
		b1.push_back(b[i]);
	}
	for(i = nb/2 ; i < nb; i++){//O(n/2)
		b2.push_back(b[i]);
	}
	out_b = merge_frequencies(b1, b2);//T(n/4)


	int offset_a = 0, offset_b = 0;	//O(1)
	
	//***********************************dejo comentado el while anterior****************************//
	
	/*while(offset_a < na && offset_b < nb){
	//cout << "freqs: " << out_a[offset_a].id << SPACE << out_a[offset_a].i << SPACE << out_a[offset_a].f << endl; 
	//cout << "freqs: " << out_b[offset_b].id << SPACE << out_b[offset_b].i << SPACE << out_b[offset_b].f << endl; 
			
		if(out_a[offset_a].cost > out_b[offset_b].cost){
	
			if(out_a[offset_a].i >= out_b[offset_b].i){
	
				if(out_a[offset_a].f > out_b[offset_b].f){ //opcion 1 y 4
					//cout << "branch 1" << endl;
					out.push_back(out_b[offset_b]);
					out_a[offset_a].i = out_b[offset_b].f;
					offset_b++;
				} else {
					//cout << "branch 2" << endl;
					out.push_back(out_b[offset_b]); //opcion 2,3,5 y 6
					offset_a++;
					offset_b++;
				}
			} else if(out_a[offset_a].i < out_b[offset_b].i){ //opcion 7, 8 y 9
					Frequency wait = out_a[offset_a];
					//cout << "branch 3" << endl;
					wait.f = out_b[offset_b].i;
					out.push_back(wait);
					out_a[offset_a].i = out_b[offset_b].i; 
			}
		} else { //lo mismo de arriba pero dado vuelta

			if(out_b[offset_b].i >= out_a[offset_a].i){

				if(out_b[offset_b].f > out_a[offset_a].f){ //opcion 1 y 4
					out.push_back(out_a[offset_a]);
					//cout << "branch 4" << endl;
					out_b[offset_b].i = out_a[offset_a].f;
					offset_a++;
				} else {
					out.push_back(out_a[offset_a]); //opcion 2,3,5 y 6
					offset_a++;
					offset_b++;
					//cout << "branch 5" << endl;
				}
			} else if(out_b[offset_b].i < out_a[offset_a].i){ //opcion 7, 8 y 9
					Frequency wait = out_b[offset_b];
					wait.f = out_a[offset_a].i;
					//cout << "branch 6" << endl;
					out.push_back(wait);
					out_b[offset_b].i = out_a[offset_a].i; 
			}
		}
	}
	*/
//*******************************************************************************************************************************+	
	int tam_a = out_a.size();
	int tam_b = out_b.size();
	bool idem_id_ant;	//para saber si la frecuencia a pushear es igual a la anterior
	Frequency wait;
	
	while(offset_a < tam_a && offset_b < tam_b){//O(2(n/2))
	//cout << "freqs: " << out_a[offset_a].id << SPACE << out_a[offset_a].i << SPACE << out_a[offset_a].f << endl; 
	//cout << "freqs: " << out_b[offset_b].id << SPACE << out_b[offset_b].i << SPACE << out_b[offset_b].f << endl; 
	//de aca en adelante me refiero a cada frecuencia como 'a' y 'b' a los elementos de out_a y out_b respectivamente actualmente iterados
		
		if(out_a[offset_a].cost > out_b[offset_b].cost){//O(1)
		//si la frecuencia del elemento de b es mas barata:
			if(out_a[offset_a].i >= out_b[offset_b].i){//O(1)
			//si inicio de b es menor o igual que inicio de a (a esta altura ya sé que me conviene usar la frecuencia b)
				if(out_a[offset_a].f > out_b[offset_b].f){ //opcion 1 y 4
				//si final de a es mayor que final de b:
					//cout << "branch 1" << endl;
					//como se que necesariamente voy a pushear b tengo que saber si el anteultimo intervalo tambien es la frecuencia b
					if(out.size()!= 0){
						if (out.back().id == out_b[offset_b].id){//el ultimo elemento que voy a pushiar es igual al anterior pushiado
							out.back().f = out_b[offset_b].f;
						}else{
							out.push_back(out_b[offset_b]);
						}
					}else{
					out.push_back(out_b[offset_b]);
					}
					//el final de la frecuencia dependera de comparar el final de b con el inicio de a
					if(out_a[offset_a].i < out_b[offset_b].f){//O(1)
						out_a[offset_a].i = out_b[offset_b].f;	//O(1)
					}
					offset_b++;
				} else {
				//si el final de a es menor igual que el final de b
					//cout << "branch 2" << endl;
					if(out.size()!= 0){
						if (out.back().id == out_b[offset_b].id){//el ultimo elemento que voy a pushiar es igual al anterior pushiado
							idem_id_ant = true;
						}else{
							idem_id_ant = false;
							wait = out_b[offset_b];	//O(1)
						}
					}else{
						idem_id_ant = false;
						wait = out_b[offset_b];	//O(1)
					}
					if(out_a[offset_a].f < out_b[offset_b].f){	//O(1)
						if(idem_id_ant){
							out.back().f = out_a[offset_a].f;	//O(1)
						}else{
							wait.f = out_a[offset_a].f;	//O(1)
							out.push_back(wait);
						}
						out_b[offset_b].i = out_a[offset_a].f;	//O(1)
						offset_a++;	//O(1)
					}else{
						if(idem_id_ant){
							out.back().f = out_b[offset_b].f;
						}else{
							out.push_back(wait);
						}
						offset_a++;
						offset_b++;
					}
				}
			} else { //opcion 7, 8 y 9
					if(out.size()!=0){
						if (out.back().id == out_a[offset_a].id ){
							idem_id_ant = true;
						}else{
							idem_id_ant = false;
							wait = out_a[offset_a];
						}
					}else{
						idem_id_ant = false;
						wait = out_a[offset_a];
					}
					
					//cout << "branch 3" << endl;
					//nuevamente el final de la nueva frecuencia dependera de la comparacion
					if(out_a[offset_a].f > out_b[offset_b].f){
						if(idem_id_ant){
							out.back().f = out_b[offset_b].i;
						}else{
							wait.f = out_b[offset_b].i;
							out.push_back(wait);
						}
						out.push_back(out_b[offset_b]);
						out_a[offset_a].i = out_b[offset_b].f;
						offset_b++;
					}else if(out_a[offset_a].f == out_b[offset_b].f){
						if(idem_id_ant){
							out.back().f = out_b[offset_b].i;
						}else{
							wait.f = out_b[offset_b].i;
							out.push_back(wait);
						}
						out.push_back(out_b[offset_b]);
						offset_a++;
						offset_b++;
					}else if(out_a[offset_a].f < out_b[offset_b].f){
						if(out_a[offset_a].f < out_b[offset_b].i){
							if(idem_id_ant){
								out.back().f = out_a[offset_a].f;
							}else{
								out.push_back(wait);
							}
							offset_a++;
						}else{
							if(idem_id_ant){
								out.back().f = out_b[offset_b].i;
							}else{
								wait.f = out_b[offset_b].i;
								out.push_back(wait);
							}
							wait = out_b[offset_b];
							wait.f = out_a[offset_a].f;
							out.push_back(wait);
							out_b[offset_b].i = out_a[offset_a].f;
							offset_a++;
						}
					}
										  
			}
		} else { //lo mismo de arriba pero dado vuelta
		//si el costo de la frecuencia del elemento a es menor o igual al de b

			if(out_b[offset_b].i >= out_a[offset_a].i){
			//si el inicio de la frecuencia a es menor o igual que el de la b(a esta altura ya se que me conviene usar la frecuencia a)
				if(out_b[offset_b].f > out_a[offset_a].f){ //opcion 1 y 4
					if (out.size()!=0){
						if(out.back().id == out_a[offset_a].id){
							out.back().f = out_a[offset_a].f;
						}else{
							out.push_back(out_a[offset_a]);
						}
					}else{
						out.push_back(out_a[offset_a]);
					}
					//cout << "branch 4" << endl;
					if(out_b[offset_b].i < out_a[offset_a].f){
						out_b[offset_b].i = out_a[offset_a].f;
					}						
					offset_a++;
					
				} else {
					if (out.size()!=0){
						if(out.back().id == out_a[offset_a].id){
							idem_id_ant = true;
						}else{
							idem_id_ant = false;
							wait = out_a[offset_a];
						}
					}else{
						idem_id_ant = false;
						wait = out_a[offset_a];
					}
					
					if(out_b[offset_b].f < out_a[offset_a].f){
						if(idem_id_ant){
							out.back().f = out_b[offset_b].f;
						}else{
							wait.f = out_b[offset_b].f;
							out.push_back(wait);
						}
						out_a[offset_a].i = out_b[offset_b].f;
						offset_b++;
					}else{
						if(idem_id_ant){
							out.back().f = out_a[offset_a].f;
						}else{
							out.push_back(wait);
						}
						offset_a++;
						offset_b++;
					}
				}
			} else { //opcion 7, 8 y 9
					if(out.size()!=0){
						if(out.back().id == out_b[offset_b].id){
							idem_id_ant = true;
						}else{
							idem_id_ant = false;
							wait = out_b[offset_b];
						}
					}else{
						idem_id_ant = false;
						wait = out_b[offset_b];
					}
								
					//cout << "branch 3" << endl;
					//nuevamente el final de la nueva frecuencia dependera de la comparacion
					if(out_b[offset_b].f > out_a[offset_a].f){
						if(idem_id_ant){
							out.back().f = out_a[offset_a].i;
						}else{
							wait.f = out_a[offset_a].i;
							out.push_back(wait);
						}
						out.push_back(out_a[offset_a]);
						out_b[offset_b].i = out_a[offset_a].f;
						offset_a++;
					}else if(out_b[offset_b].f == out_a[offset_a].f){
						if(idem_id_ant){
							out.back().f = out_a[offset_a].i;
						}else{
							wait.f = out_a[offset_a].i;
							out.push_back(wait);
						}
						out.push_back(out_a[offset_a]);
						offset_a++;
						offset_b++;
					}else if(out_b[offset_b].f < out_a[offset_a].f){
						if(out_b[offset_b].f < out_a[offset_a].i){
							if(idem_id_ant){
								out.back().f = out_b[offset_b].f;
							}else{
								out.push_back(wait);
							}
							offset_b++;
						}else{
							if(idem_id_ant){
								out.back().f = out_a[offset_a].i;
							}else{
								wait.f = out_a[offset_a].i;
								out.push_back(wait);
							}
							wait = out_a[offset_a];
							wait.f = out_b[offset_b].f;
							out.push_back(wait);
							out_a[offset_a].i = out_b[offset_b].f;
							offset_b++;
						}
					}
										  
			}
		}
	}

	if (offset_a < tam_a){
		if(out.size()!=0){
			if(out.back().id == out_a[offset_a].id){
				out.back().f = out_a[offset_a].f;
				offset_a ++;
			}
		}
		
		while(offset_a < tam_a){	//O(n/2)
			out.push_back(out_a[offset_a]);
			offset_a++;
		}
		
	}else if (offset_b < tam_b){
		if(out.size()!=0){
			if(out.back().id == out_b[offset_b].id){
				out.back().f = out_b[offset_b].f;
				offset_b ++;
			}
		}
		
		while(offset_b < tam_b){	//O(n/2)
			out.push_back(out_b[offset_b]);
			offset_b++;
		}
	}

	return out;
}
