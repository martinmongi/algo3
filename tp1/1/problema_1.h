
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

struct City{
	int z, s, c, cost, id;
	bool saveable;
};

bool compare_cities_cost(City a, City b){
	return a.cost <= b.cost;
}

bool compare_cities_id(City a, City b){
	return a.id <= b.id;
}