#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Phase{
	int BMX_cost;
	int motox_cost;
	int buggy_cost;
};

pair<int,stack<char> > solve(vector<Phase> &race, int km, int kb, int i);