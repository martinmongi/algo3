#include "problema_3.h"

using namespace std;

#define EMPTY 0
#define OLD_THREATENED -1
#define OLD_HORSE -2
#define NEW_HORSE -3
#define TAB '\t'

int upper_bound;
vector<pair<int, int> > offsets = {{0,0},{2,1},{1,2},{1,-2},{2,-1},{-1,2},{-2,1},{-1,-2},{-2,-1}};

int main(){
	
	int n, k, i, x, y;

	cin >> n >> k;

	upper_bound = n*n;
	vector<vector<char> > board(n, vector<char>(n, EMPTY)); //Tablero en cero todo

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
			if(board[i][j] == EMPTY){
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
	int min_horses = n*n, horses;

	pair<int, int> first_blank = find_blank(board);

	//Si llego al final del tablero sin encontrar 0 significa que esta todo cubierto, entonces, devuelvo el que me pasan
	horses = count_new_horses(board);

	if(first_blank.first == n){
		if(horses < upper_bound)
			upper_bound = horses;
		return board;
	}

	//en i, j esta el primer casillero no expuesto

	int x = first_blank.first, y = first_blank.second;
	vector<vector<char> > sug_board, solution;
	int horse_x, horse_y;

// COMENTAR ESTE IF PARA SACAR LA PODA

	if(horses + 1 >= upper_bound)
		return solution;

	
	for(unsigned int i = 0; i < offsets.size(); i++){
		horse_x = x + offsets[i].first;
		horse_y = y + offsets[i].second;
		if(horse_x >= 0 && horse_x < n && horse_y >= 0 && horse_y < n){
			sug_board = board;	
			add_horse(sug_board, horse_x, horse_y, NEW_HORSE);
			sug_board = solve(sug_board);
			if(!sug_board.empty()){
				horses = count_new_horses(sug_board);
				if(horses < min_horses){
					min_horses = horses;
					solution = sug_board;
				}
			}
		}
	}

	return solution;
}