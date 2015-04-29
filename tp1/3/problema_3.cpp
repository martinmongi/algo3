#include "problema_3.h"

using namespace std;

#define EMPTY 0
#define OLD_THREATENED -1
#define OLD_HORSE -2
#define NEW_HORSE -3
#define TAB '\t'
#define SPACE ' '

int upper_bound;
vector<pair<int, int> > offsets = {{0,0},{2,1},{1,2},{1,-2},{2,-1},{-1,2},{-2,1},{-1,-2},{-2,-1}};

int main(){
	
	int n, k, i, j, x, y;

	cin >> n >> k;

	upper_bound = n*n + 1;
	vector<vector<char> > board(n, vector<char>(n, EMPTY)); //Tablero en cero todo

	for(i = 0; i < k; i++){
		cin >> x >> y;
		x--;
		y--;
		//print_board(board);
		add_horse(board,x,y,OLD_HORSE);
	}

	//Tablero con los caballos por default puestos
	// cout << "Tablero inicial:" << endl;
	// print_board(board);
	vector<vector<char> > solution = solve(board, 0, 0);

	cout << count_new_horses(solution) << endl;
	for(i = 0; i < (int)solution.size(); i++){
		for(j = 0; j < (int)solution.size(); j++){
			if(solution[i][j] == NEW_HORSE)
				cout << i + 1 << SPACE << j + 1 << endl;
		}
	}
	cout << "Solucion encontrada:" << endl;
	print_board(solution);

	//cout << "Caballos usados: " << count_new_horses(solution) << endl;
	return 0;
}

void add_horse(vector<vector<char> > &board, int x, int y, char type){
	assert(x >= 0);
	assert(y >= 0);
	assert(x < (int)board.size());
	assert(y < (int)board.size());
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

bool is_solution(vector<vector<char> > &board){
	if(board.empty())
		return false;
	for(int i = 0; i < (int)board.size(); i++){
		for(int j = 0; j < (int)board.size(); j++){
			if(board[i][j] == EMPTY){
				return false;
			}
		}
	}
	return true;
}

vector<vector<char> > solve(vector<vector<char> > board, int i, int j){
	int n = board.size(), min_horses = n*n, horses = min_horses;
	vector<vector<char> > sol;

	bool second_prune = true;;
	for(int k = 0; k < i - 2; k++){
		for(int l = 0; l < n; l++){
			second_prune = second_prune && (bool)board[k][l];
		}
	}
	if(i >= 2){
		for(int l = 0; l < j - 1; l++){
			second_prune = second_prune && (bool)board[i - 2][l];
		}
	}
	if(!second_prune){
		return sol;
	}

	int original_horses = count_new_horses(board);

	if(i == n){
		if(is_solution(board)){
			if(original_horses < upper_bound){
				upper_bound = original_horses;
				//cout << upper_bound << endl;
			}
			return board;
		}
		else
			return sol;
	}

	// cout << "FUNCTION CALL:\t" << i << TAB << j << endl;
	// print_board(board);

	int jp = (j == (int)board.size() - 1)? 0: j + 1;
	int ip = (j == (int)board.size() - 1)? i + 1: i;

	vector<vector<char> > sol_without = solve(board, ip, jp);
	if(is_solution(sol_without)){
		horses = count_new_horses(sol_without);
		if(horses < min_horses){
			min_horses = horses;
			sol = sol_without;
		}	
	}

	//I check whether with the addition of the horse, wouldnt I be generating a suboptimal solution
	bool first_prune = (original_horses + 1> upper_bound);

	if(!first_prune){
		vector<vector<char> > board_with_horse = board;
		add_horse(board_with_horse, i, j, NEW_HORSE);
		vector<vector<char> > sol_with = solve(board_with_horse, ip, jp);
		if(is_solution(sol_with)){
			horses = count_new_horses(sol_with);
			if(horses < min_horses){
				min_horses = horses;
				sol = sol_with;
			}	
		}
	}
	return sol;
	
}
