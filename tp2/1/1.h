#include <iostream>
#include <vector>

using namespace std;

struct Phase{
	int BMX_cost;
	int motox_cost;
	int buggy_cost;
};

int solve(vector<Phase> &race, int km, int kb, int i, vector<char> &choices);