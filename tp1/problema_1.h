#include "sort.h"
#include <iostream>
#include <cmath>

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