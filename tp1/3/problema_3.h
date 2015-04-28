#include <iostream>
#include <vector>
#include <cassert>
//#include <pair>

using namespace std;

void add_horse(vector<vector<char> > &board, int x, int y, char type);

void set_square(vector<vector<char> > &board, int x, int y);

void print_board(vector<vector<char> > &board);

// vector<vector<char> > solve(vector<vector<char> > board);

vector<vector<char> > solve(vector<vector<char> > board, int i, int j);

int count_new_horses(vector<vector<char> > &board);

// pair<int, int> find_blank(vector<vector<char> > &board);

bool is_solution(vector<vector<char> > &board);