#include "sort.h"
#include <iostream>
#include <cmath>

#define SET 1
#define RESET 0

struct Frequency{
	int i, f, cost, id;
};

vector<Frequency> solve(vector<Frequency> &v);
vector<Frequency> merge_frequencies(vector<Frequency> &a, vector<Frequency> &b);
