#include <vector>
#include <iostream>
#include <cassert>
#include <queue>
#include <stack>

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
	void PrintTrajectory();
private:
	int n, m, s, ih, iv, bh, bv;
	std::vector<std::vector<int> > h_streets;
	std::vector<std::vector<int> > v_streets;
	std::vector<std::vector<int> > corners;
	std::vector<std::vector<int> > directions;
	std::vector<std::queue<Corner> > hashed_queues;
	std::vector<Corner> queue;
	int CostOfMoving(int y, int x, int direction);
};

Grid::Grid(){
	std::cin >> n >> m >> s;
	std::cin >> ih >> iv >> bh >> bv;
	ih--; iv--; bh--; bv--;

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
	std::vector<int> d(m, -1);
	for(int i = 0; i < n; i++){
		corners.push_back(c);
		directions.push_back(d);
	}

	//Corner where they start with s soldiers
	corners[ih][iv] = s;
	directions[ih][iv] = -1;


	for(int i = 0; i < n - 1; i++){

		for(int j = 0; j < m - 1; j++)
			std::cin >> h_streets[i][j];
		for(int j = 0; j < m; j++)
			std::cin >> v_streets[i][j];
	
	}

	for(int j = 0; j < m - 1; j++)
		std::cin >> h_streets[n-1][j];

}

void Grid::PrintCorners(){

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			std::cout << corners[i][j] << TAB; 
		}
		std::cout << NEWLINE;
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			std::cout << directions[i][j] << TAB; 
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

void Grid::PrintTrajectory(){


	std::stack<Corner> q;
	Corner c;
	c.x = bv;
	c.y = bh;
	q.push(c);

	if(directions[c.y][c.x] < 0){
		std::cout << "0" << NEWLINE;
		return;
	}else{
		std::cout << corners[c.y][c.x] << NEWLINE;
	}
	while(iv != c.x || ih != c.y){
		//std::cout << c.y << SPACE  << c.x << NEWLINE;
		switch(directions[c.y][c.x]){
			case NORTH:
				c.y--;
				q.push(c);
				break;
			case EAST:
				c.x++;
				q.push(c);
				break;
			case SOUTH:
				c.y++;
				q.push(c);
				break;
			case WEST:
				c.x--;
				q.push(c);
				break;
		}
	}

	while(!q.empty()){
		std::cout << q.top().y + 1 << SPACE << q.top().x + 1 << NEWLINE;
		q.pop();
	}
}
int Grid::CostOfMoving(int y, int x, int direction){

	switch(direction){
		case NORTH:
			return v_streets[y - 1][x];
		case EAST:
			return h_streets[y][x];
		case SOUTH:
			return v_streets[y][x];
		case WEST:
			return h_streets[y][x - 1];
	}
}

int Grid::Solve(){
	Corner c;
	c.y = ih;
	c.x = iv;
	c.soldiers_left = s;
	hashed_queues[c.soldiers_left].push(c);
	//Insert(c);
	int i = 0, x, y, soldiers_left, soldiers_i = s;

	while(soldiers_i > 0){
		x = hashed_queues[soldiers_i].front().x;
		y = hashed_queues[soldiers_i].front().y;
		soldiers_left = hashed_queues[soldiers_i].front().soldiers_left;
		// std::cout << "====================================" << NEWLINE;
		// std::cout << y << SPACE << x << SPACE << soldiers_left << SPACE << directions[y][x] << NEWLINE;
		//move north
		c.x = x;
		c.y = y - 1;
		
		if((c.y >= 0) && (c.x >= 0) && (c.y < corners.size()) && (c.x < corners[0].size())){
			if(soldiers_left >= CostOfMoving(y, x, NORTH))
				c.soldiers_left = soldiers_left;
			else if(soldiers_left*2 <= CostOfMoving(y, x, NORTH))
				c.soldiers_left = 0;
			else
				c.soldiers_left = soldiers_left - (CostOfMoving(y, x, NORTH) - soldiers_left);
			if(c.soldiers_left > corners[c.y][c.x]){

				corners[c.y][c.x] = c.soldiers_left;
				directions[c.y][c.x] = SOUTH;
				hashed_queues[c.soldiers_left].push(c);
				// std::cout << c.y << SPACE << c.x << SPACE << c.soldiers_left << SPACE << directions[c.y][c.x] << NEWLINE;
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
				c.soldiers_left = soldiers_left - (CostOfMoving(y, x, SOUTH) - soldiers_left);
			if(c.soldiers_left > corners[c.y][c.x]){
				corners[c.y][c.x] = c.soldiers_left;
				directions[c.y][c.x] = NORTH;
				hashed_queues[c.soldiers_left].push(c);
				// std::cout << c.y << SPACE << c.x << SPACE << c.soldiers_left << SPACE << directions[c.y][c.x] << NEWLINE;
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
				c.soldiers_left = soldiers_left - (CostOfMoving(y, x, EAST) - soldiers_left);
			if(c.soldiers_left > corners[c.y][c.x]){
				corners[c.y][c.x] = c.soldiers_left;
				directions[c.y][c.x] = WEST;
				hashed_queues[c.soldiers_left].push(c);
				// std::cout << c.y << SPACE << c.x << SPACE << c.soldiers_left << SPACE << directions[c.y][c.x] << NEWLINE;
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
				c.soldiers_left = soldiers_left - (CostOfMoving(y, x, WEST) - soldiers_left);
			if(c.soldiers_left > corners[c.y][c.x]){
				corners[c.y][c.x] = c.soldiers_left;
				directions[c.y][c.x] = EAST;
				hashed_queues[c.soldiers_left].push(c);
				// std::cout << c.y << SPACE << c.x << SPACE << c.soldiers_left << SPACE << directions[c.y][c.x] << NEWLINE;
			}
		}
		
		hashed_queues[soldiers_i].pop();
		while(soldiers_i > 0 && hashed_queues[soldiers_i].empty()){
			soldiers_i--;
		}
	}
	return corners[bh][bv];
}
