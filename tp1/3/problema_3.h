#include <iostream>
#include <vector>

using namespace std;

void add_horse(vector<vector<char> > &board, int x, int y, char type);

void set_square(vector<vector<char> > &board, int x, int y);

void print_board(vector<vector<char> > &board);

vector<vector<char> > solve(vector<vector<char> > board);

int count_new_horses(vector<vector<char> > &board);