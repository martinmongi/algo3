#include "2.h"

int main(){
	int n, m, s, ih, iv, bh, bv, buff;
	cin >> n >> m >> s;
	cin >> ih >> iv >> bh >> bv;

	vector<vector<int> > h_streets(n, vector<int>(m - 1));
	vector<vector<int> > v_streets(m, vector<int>(n - 1));

	for(int i = 0; i < n - 1; i++){
		for(int j = 0; j < m - 1; j++){
			cin >> buff;
			h_streets[i][j] = buff - s;
		}
		for(int j = 0; j < m; j++){
			cin >> buff;
			v_streets[i][j] = buff - s;
		}	
	}

	for(int j = 0; j < m - 1; j++){
		cin >> buff;
		h_streets[n][j] = buff - s;
	}

	
}