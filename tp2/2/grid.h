#include <vector>
#include <iostream>
#include <cassert>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define TAB '\t'
#define NEWLINE '\n'
#define SPACE ' '

struct Corner{
	int y, x, cost;
};

class Grid{
public:
	Grid();
	int Solve();
	void PrintGrid();
	void PrintCorners();
private:
	int n, m, s, ih, iv, bh, bv;
	std::vector<std::vector<int> > h_streets;
	std::vector<std::vector<int> > v_streets;
	std::vector<std::vector<int> > corners;
	std::vector<Corner> queue;
	void Insert(Corner &c);
	int CostOfMoving(int y, int x, int direction);
};

Grid::Grid(){
	int buff;
	std::cin >> n >> m >> s;
	std::cin >> ih >> iv >> bh >> bv;
	ih--; iv--; bh--; bv--;

	// std::cout << "n    " << n << NEWLINE;
	// std::cout << "m    " << m << NEWLINE;
	// std::cout << "s    " << s << NEWLINE;
	// std::cout << "ih    " << ih << NEWLINE;
	// std::cout << "iv    " << iv << NEWLINE;
	// std::cout << "bh    " << bh << NEWLINE;
	// std::cout << "bv    " << bv << NEWLINE;

	//Initialize h_streets
	std::vector<int> a(m-1);
	for(int i = 0; i < n; i++){
		h_streets.push_back(a);
	}

	//Initialize v_streets
	std::vector<int> b(m);
	for(int i = 0; i < n - 1; i++){
		v_streets.push_back(b);
	}

	//Initialize corners
	std::vector<int> c(m, -1);
	for(int i = 0; i < n; i++){
		corners.push_back(c);
	}

	corners[iv][ih] = 0;

	for(int i = 0; i < n - 1; i++){

		for(int j = 0; j < m - 1; j++){
			// std::cout << "FILA   " << i << "   COLUMNA   " << j << NEWLINE;
			std::cin >> buff;
			h_streets[i][j] = (buff - s > 0? buff - s : 0);
			// std::cout << "h  " <<  i << SPACE << j << SPACE << buff << NEWLINE;
		}
		for(int j = 0; j < m; j++){
			std::cin >> buff;
			v_streets[i][j] = (buff - s > 0? buff - s : 0);
			// std::cout << "v  " <<  i << SPACE << j << SPACE << buff << NEWLINE;
		}	
	}

	for(int j = 0; j < m - 1; j++){
		std::cin >> buff;
		h_streets[n-1][j] = (buff - s > 0? buff - s : 0);
		// std::cout << "h  " <<  n << SPACE << j << SPACE << buff << NEWLINE;
	}
	// std::cout << "SALE" << NEWLINE;
}

void Grid::PrintCorners(){
	std::vector<int> c(m, -1);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			std::cout << corners[i][j] << TAB; 
		}
		std::cout << NEWLINE;
	}

}
void Grid::PrintGrid(){
	for(int i = 0; i < h_streets.size() - 1; i++){
		std::cout << TAB;
		for(int j = 0; j < h_streets[0].size(); j++){
			std::cout << h_streets[i][j] << TAB << TAB;
		}
		std::cout << NEWLINE << NEWLINE;
		for(int j = 0; j < v_streets[0].size(); j++){
			std::cout << v_streets[i][j] << TAB << TAB;
		}
		std::cout << NEWLINE << NEWLINE;
	}

	std::cout << TAB;
	for(int j = 0; j < h_streets[n-1].size(); j++){
		std::cout << h_streets[n-1][j] << TAB << TAB;
	}
	std::cout << NEWLINE;
}

int Grid::CostOfMoving(int y, int x, int direction){
	int res;
	
	switch(direction){
		case NORTH:
			// std::cout << "NORTH" << NEWLINE;
			// assert(y > 0);
			res = v_streets[y - 1][x];
			break;
		case EAST:
			// std::cout << "EAST" << NEWLINE;
			// assert(x < m - 1);
			res = h_streets[y][x];
			break;
		case SOUTH:
			// std::cout << "SOUTH" << NEWLINE;
			// assert(y < n - 1);
			res = v_streets[y][x];
			break;
		case WEST:
			// std::cout << "WEST" << NEWLINE;
			// assert(x > 0);
			res = h_streets[y - 1][x];
			break;
	}
	//std::cout << y << TAB << x << TAB << direction << TAB << res << NEWLINE;
	return res;
}

int Grid::Solve(){
	Corner c;
	c.y = iv;
	c.x = ih;
	c.cost = 0;
	Insert(c);
	int i = 0, x, y, cost;

	while(/*i < queue.size() &&*/ ((queue[i].cost < s) || ((bv == queue[i].x) && (y == queue[i].y)))) {
		x = queue[i].x;
		y = queue[i].y;
		cost = queue[i].cost;

		//move north
		c.x = x;
		c.y = y - 1;
		
		if((c.y >= 0) && (c.x >= 0) && (c.y < corners.size()) && (c.x < corners[0].size()) && (corners[c.y][c.x] < 0)){
			c.cost = cost + CostOfMoving(y, x, NORTH);
			corners[c.y][c.x] = c.cost;
			Insert(c);
		}

		//move south
		c.x = x;
		c.y = y + 1;
		if((c.y >= 0) && (c.x >= 0) && (c.y < corners.size()) && (c.x < corners[0].size()) && (corners[c.y][c.x] < 0)){
			c.cost = cost + CostOfMoving(y, x, SOUTH);
			corners[c.y][c.x] = c.cost;
			Insert(c);
		}
		
		//move east
		c.x = x + 1;
		c.y = y;
		if((c.y >= 0) && (c.x >= 0) && (c.y < corners.size()) && (c.x < corners[0].size()) && (corners[c.y][c.x] < 0)){
			c.cost = cost + CostOfMoving(y, x, EAST);
			corners[c.y][c.x] = c.cost;
			Insert(c);
		}
		
		//move west
		c.x = x - 1;
		c.y = y;
		if((c.y >= 0) && (c.x >= 0) && (c.y < corners.size()) && (c.x < corners[0].size()) && (corners[c.y][c.x] < 0)){
			c.cost = cost + CostOfMoving(y, x, WEST);
			corners[c.y][c.x] = c.cost;
			Insert(c);
		}
		
		i++;
	}
	if(queue[i].cost <= s)
		return s - queue[i].cost;
	else
		return -1;
}

void Grid::Insert(Corner &c){
	Corner aux;
	queue.push_back(c);
	int i = queue.size() - 1;
	while(i > 0 && queue[i].cost < queue[i-1].cost){
		//swap
		aux.cost = queue[i-1].cost;
		aux.x = queue[i-1].x;
		aux.y = queue[i-1].y;
		queue[i-1].cost = queue[i].cost;
		queue[i-1].x = queue[i].x;
		queue[i-1].y = queue[i].y;
		queue[i].cost = aux.cost;
		queue[i].x = aux.x;
		queue[i].y = aux.y;
		i--;
	}
}