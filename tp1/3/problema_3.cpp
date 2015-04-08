#include "problema_3.h"

using namespace std;

#define EMPTY 0
#define OLD_THREATENED -1
#define OLD_HORSE -2
#define NEW_HORSE -3
#define INCR_THREAT 1
#define TAB '\t'

int main(){
	int n, k, i, x, y;

	cin >> n >> k;

	vector<vector<char> > board(n, vector<char>(n, 0)); //Tablero en cero todo

	for(i = 0; i < k; i++){
		cin >> x >> y;
		x--;
		y--;
		//print_board(board);
		add_horse(board,x,y,OLD_HORSE);
	}

	//Tablero con los caballos por default puestos
	cout << "Tablero inicial:" << endl;
	print_board(board);
	vector<vector<char> > solution = solve(board);

	cout << "Solucion encontrada:" << endl;
	print_board(solution);

	cout << "Caballos usados: " << count_new_horses(solution) << endl;
}

void add_horse(vector<vector<char> > &board, int x, int y, char type){
	//cout << "Agrego caballo en " << x << TAB << y << endl;
	//int n = board.size();
	//if(x >= 0 && x < n && y >= 0 && y < n){
		board[x][y] = type;
		set_square(board, x + 2, y + 1);
		set_square(board, x + 1, y + 2);
		set_square(board, x + 2, y - 1);
		set_square(board, x + 1, y - 2);
		set_square(board, x - 2, y + 1);
		set_square(board, x - 1, y + 2);
		set_square(board, x - 2, y - 1);
		set_square(board, x - 1, y - 2);
	//}
}

void set_square(vector<vector<char> > &board, int x, int y){
	int n = board.size();
	if(x >= 0 && x < n && y >= 0 && y < n)
		if(board[x][y] >= 0)
			board[x][y]++;
}

void print_board(vector<vector<char> > &board){
	int n = board.size();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << (int)board[i][j] << TAB;
		}
		cout << endl;
	}
}

int count_new_horses(vector<vector<char> > &board){
	int n = board.size(), count = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(board[i][j] == NEW_HORSE)
				count++;
		}
	}
	return count;
}

pair<int, int> find_blank(vector<vector<char> > &board){
	pair<int, int> ans;
	int n = board.size();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(board[i][j] == 0){
				ans.first = i;
				ans.second = j;
				return ans;
			}
		}
	}
	ans.first = n;
	ans.second = n;
	return ans;
}

vector<vector<char> > solve(vector<vector<char> > board){
	int n = board.size();
	int min_horses, horses;

	pair<int, int> first_blank = find_blank(board);

	//Si llego al final del tablero sin encontrar 0 significa que esta todo cubierto, entonces, devuelvo el que me pasan
	if(first_blank.first == n)
		return board;

	//en i, j esta el primer casillero no expuesto

	int x = first_blank.first, y = first_blank.second;
	vector<vector<char> > sug_board, solution;

	//case 1
	sug_board = board;
	add_horse(sug_board, x, y, NEW_HORSE);
	sug_board = solve(sug_board);
	horses = count_new_horses(sug_board);
	min_horses = horses;
	solution = sug_board;
	
	//case 2
	sug_board = board;
	if(x-1 >= 0 && y-2 >= 0){
		add_horse(sug_board, x-1, y-2, NEW_HORSE);
		sug_board = solve(sug_board);
		horses = count_new_horses(sug_board);
		if(horses < min_horses){
			min_horses = horses;
			solution = sug_board;
		}
	}
	//case 3
	sug_board = board;
	if(x-2 >= 0 && y-1 >= 0){
		add_horse(sug_board, x-2, y-1, NEW_HORSE);
		sug_board = solve(sug_board);
		horses = count_new_horses(sug_board);
		if(horses < min_horses){
			min_horses = horses;
			solution = sug_board;
		}
	}
	//case 4
	sug_board = board;
	if(x+1 < n && y-2 >= 0){
		add_horse(sug_board, x+1, y-2, NEW_HORSE);
		sug_board = solve(sug_board);
		horses = count_new_horses(sug_board);
		if(horses < min_horses){
			min_horses = horses;
			solution = sug_board;
		}
	}
	//case 5
	sug_board = board;
	if(x+2 < n && y-1 >= 0){
		add_horse(sug_board, x+2, y-1, NEW_HORSE);
		sug_board = solve(sug_board);
		horses = count_new_horses(sug_board);
		if(horses < min_horses){
			min_horses = horses;
			solution = sug_board;
		}
	}
	//case 6
	sug_board = board;
	if(x+1 < n && y+2 < n){
		add_horse(sug_board, x+1, y+2, NEW_HORSE);
		sug_board = solve(sug_board);
		horses = count_new_horses(sug_board);
		if(horses < min_horses){
			min_horses = horses;
			solution = sug_board;
		}
	}
	//case 7
	sug_board = board;
	if(x+2 < n && y+1 < n){
		add_horse(sug_board, x+2, y+1, NEW_HORSE);
		sug_board = solve(sug_board);
		horses = count_new_horses(sug_board);
		if(horses < min_horses){
			min_horses = horses;
			solution = sug_board;
		}
	}
	//case 8
	sug_board = board;
	if(x-1 >= 0 && y+2 < n){
		add_horse(sug_board, x-1, y+2, NEW_HORSE);
		sug_board = solve(sug_board);
		horses = count_new_horses(sug_board);
		if(horses < min_horses){
			min_horses = horses;
			solution = sug_board;
		}
	}
	//case 9
	sug_board = board;
	if(x-2 >= 0 && y+1 < n){
		add_horse(sug_board, x-2, y+1, NEW_HORSE);
		sug_board = solve(sug_board);
		horses = count_new_horses(sug_board);
		if(horses < min_horses){
			min_horses = horses;
			solution = sug_board;
		}
	}
	return solution;
}