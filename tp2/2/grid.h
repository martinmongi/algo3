#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

class Grid{
public:
	Grid();
private:
	int n, m, s, ih, iv, bh, bv;
	vector<vector<int> > h_streets;
	vector<vector<int> > v_streets;
};

Grid::Grid(){
	int buff;
	cin >> n >> m >> s;
	cin >> ih >> iv >> bh >> bv;
	ih--; iv--; bh--; bv--;

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

int Grid::CostOfMoving(int y, int x, int direction){
	switch(direction)
		case NORTH:
			if(y > 0)
				return v_streets[y - 1][x];
			else
				return -1;
		case EAST:
			if(x < m - 1)
				return h_streets[y][x];
			else
				return -1;
		case SOUTH:
			if(y < n - 1)
				return v_streets[y][x];
			else
				return -1;
		case WEST:
			if(x > 0)
				return h_streets[y - 1][x];
			else
				return -1;
}