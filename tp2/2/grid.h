#include <vector>
#include <iostream>
#include <cassert>
#include <queue>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define TAB '\t'
#define NEWLINE '\n'
#define SPACE ' '

struct Corner{
	int y, x, soldiers_left;
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
	std::vector<std::queue<Corner> > hashed_queues;
	std::vector<Corner> queue;
	int CostOfMoving(int y, int x, int direction);
};

Grid::Grid(){
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

	//Initialize queues
	std::queue<Corner> q;
	for(int i = 0; i <= s; i++){
		hashed_queues.push_back(q);
	}

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
	std::vector<int> c(m, 0);
	for(int i = 0; i < n; i++){
		corners.push_back(c);
	}

	corners[iv][ih] = s;

	for(int i = 0; i < n - 1; i++){

		for(int j = 0; j < m - 1; j++){
			// std::cout << "FILA   " << i << "   COLUMNA   " << j << NEWLINE;
			std::cin >> h_streets[i][j];
			// std::cout << "h  " <<  i << SPACE << j << SPACE << buff << NEWLINE;
		}
		for(int j = 0; j < m; j++){
			std::cin >> v_streets[i][j];
			// std::cout << "v  " <<  i << SPACE << j << SPACE << buff << NEWLINE;
		}	
	}

	for(int j = 0; j < m - 1; j++){
		std::cin >> h_streets[n-1][j];
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
	c.soldiers_left = s;
	hashed_queues[c.soldiers_left].push(c);
	//Insert(c);
	int i = 0, x, y, soldiers_left, soldiers_i = s;

	while((soldiers_i > 0) /*|| ((bv == hashed_queues[cost_i].front().x) && (bh == hashed_queues[cost_i].front().y))*/) {
		x = hashed_queues[soldiers_i].front().x;
		y = hashed_queues[soldiers_i].front().y;
		soldiers_left = hashed_queues[soldiers_i].front().soldiers_left;
		std::cout << x << SPACE << y << SPACE << soldiers_left << SPACE << soldiers_i << NEWLINE;

		//move north
		c.x = x;
		c.y = y - 1;
		
		if((c.y >= 0) && (c.x >= 0) && (c.y < corners.size()) && (c.x < corners[0].size())){
			if(soldiers_left >= CostOfMoving(y, x, NORTH))
				c.soldiers_left = soldiers_left;
			else if(soldiers_left*2 <= CostOfMoving(y, x, NORTH))
				c.soldiers_left = 0;
			else
				c.soldiers_left = c.soldiers_left - (CostOfMoving(y, x, NORTH) - c.soldiers_left);
			std::cout << c.x << SPACE << c.y << SPACE << c.soldiers_left << NEWLINE;
			if(c.soldiers_left > corners[c.y][c.x]){
				corners[c.y][c.x] = c.soldiers_left;
				hashed_queues[c.soldiers_left].push(c);
				std::cout << "entro en la cola" << NEWLINE;
			}
		}

		//move south
		c.x = x;
		c.y = y + 1;
		if((c.y >= 0) && (c.x >= 0) && (c.y < corners.size()) && (c.x < corners[0].size())){
			if(soldiers_left >= CostOfMoving(y, x, SOUTH))
				c.soldiers_left = soldiers_left;
			else if(soldiers_left*2 <= CostOfMoving(y, x, SOUTH))
				c.soldiers_left = 0;
			else
				c.soldiers_left = c.soldiers_left - (CostOfMoving(y, x, SOUTH) - c.soldiers_left);
			std::cout << c.x << SPACE << c.y << SPACE << c.soldiers_left << NEWLINE;
			if(c.soldiers_left > corners[c.y][c.x]){
				corners[c.y][c.x] = c.soldiers_left;
				hashed_queues[c.soldiers_left].push(c);
				std::cout << "entro en la cola" << NEWLINE;
			}
		}
		
		//move east
		c.x = x + 1;
		c.y = y;
		if((c.y >= 0) && (c.x >= 0) && (c.y < corners.size()) && (c.x < corners[0].size())){
			if(soldiers_left >= CostOfMoving(y, x, EAST))
				c.soldiers_left = soldiers_left;
			else if(soldiers_left*2 <= CostOfMoving(y, x, EAST))
				c.soldiers_left = 0;
			else
				c.soldiers_left = c.soldiers_left - (CostOfMoving(y, x, EAST) - c.soldiers_left);
			std::cout << c.x << SPACE << c.y << SPACE << c.soldiers_left << NEWLINE;
			if(c.soldiers_left > corners[c.y][c.x]){
				corners[c.y][c.x] = c.soldiers_left;
				hashed_queues[c.soldiers_left].push(c);
				std::cout << "entro en la cola" << NEWLINE;
			}
		}
		
		//move west
		c.x = x - 1;
		c.y = y;
		if((c.y >= 0) && (c.x >= 0) && (c.y < corners.size()) && (c.x < corners[0].size())){
			if(soldiers_left >= CostOfMoving(y, x, WEST))
				c.soldiers_left = soldiers_left;
			else if(soldiers_left*2 <= CostOfMoving(y, x, WEST))
				c.soldiers_left = 0;
			else
				c.soldiers_left = c.soldiers_left - (CostOfMoving(y, x, WEST) - c.soldiers_left);
			std::cout << c.x << SPACE << c.y << SPACE << c.soldiers_left << NEWLINE;
			if(c.soldiers_left > corners[c.y][c.x]){
				corners[c.y][c.x] = c.soldiers_left;
				hashed_queues[c.soldiers_left].push(c);
				std::cout << "entro en la cola" << NEWLINE;
			}
		}
		
		hashed_queues[soldiers_i].pop();
		while(soldiers_i > 0 && hashed_queues[soldiers_i].empty()){
			soldiers_i--;
			std::cout << soldiers_i << NEWLINE;
		}
	}
	return corners[bv][bh];
}
