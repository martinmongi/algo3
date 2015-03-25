#include <stdlib.h>
#include <vector>

using namespace std;

template<typename T>
bool naive_compare(T a, T b){
	return (a<b);
}

template <typename T>
void merge_aux(vector<T> &v, vector<T> &aux, int left, int right, bool (*compare)(T,T)){

	if(left + 1 == right)
		return;
	int middle = (left + right)/2;
	merge_aux(v, aux, left, middle, compare);
	merge_aux(v, aux, middle, right, compare);

	int length = right - left;
	int l_offset = left;
	int r_offset = middle;

	for(int i = left; i < right; i++){
		if(l_offset < middle && (compare(v[l_offset],v[r_offset]) || r_offset >= right)){
			aux[i] = v[l_offset];
			l_offset++;
		}else{
			aux[i] = v[r_offset];
			r_offset++;
		}
	}

	for(int i = left; i < right; i++)
		v[i] = aux[i];

}

template <typename T>
void sort(vector<T> &v, bool (*compare)(T, T)){
	vector<T> aux(v.size());
	merge_aux(v, aux, 0, v.size(), compare);
}