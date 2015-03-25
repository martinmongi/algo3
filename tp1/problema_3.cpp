#include <problema_3.h>

using namespace std;

#define EMPTY 0
#define THREATENED 1
#define OLD_HORSE 2
#define NEW_HORSE 3

int main(){
	int n, k, i, x, y;

	cin >> n >> k;

	vector<vector<unsigned char>(0,n)> board(0,n);

	for(i = 0, i < k; i){
		cin >> x >> y;
		x--;
		y--;
		board[x][y] = 2;
		
	}
}

void add_horse(vector<vector<unsigned char>> &board, int x, int y, unsigned char type){
	board[x][y] = type;
	set_square(board, x + 2, y + 1);
	set_square(board, x + 1, y + 2);
	set_square(board, x + 2, y - 1);
	set_square(board, x + 1, y - 2);
	set_square(board, x - 2, y + 1);
	set_square(board, x - 1, y + 2);
	set_square(board, x - 2, y - 1);
	set_square(board, x - 1, y - 2);
}

void set_square(vector<vector<unsigned char>> &board, int x, int y){
	n = board.size();
	if(x >= 0 && x < n && y >= 0 && y < n)
		board[x][y] = THREATENED;
}