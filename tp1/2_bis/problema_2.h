#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct Frequency{
	int start, end, cost, id;
};

vector<Frequency> solve(vector<Frequency> &v);
vector<Frequency> merge_frequencies(vector<Frequency> &a, vector<Frequency> &b);
