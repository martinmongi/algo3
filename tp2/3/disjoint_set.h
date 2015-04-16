#include <vector>
#include <set>
#include <iostream>

#define SPACE ' '

class DisjointSets{
public:
	DisjointSets(int x);
	int FindSet(int x);
	void MergeSets(int x, int y);
	std::set<int> SetIds();

private:

	std::vector<int> uf;
};

DisjointSets::DisjointSets(int x){
	for(int i = 0; i < x; i++)
		uf.push_back(i);
	// std::cout << "Creado el vector" << std::endl;
	// for(int i = 0; i < x; i++)
		// std::cout << i << SPACE << uf[i] << std::endl;
}

int DisjointSets::FindSet(int x){
	if(uf[x] == x)
		return x;
	return FindSet(uf[x]);
}

void DisjointSets::MergeSets(int x, int y){
	// std::cout << "Merging " << x << SPACE << y << std::endl;
	uf[FindSet(std::max(x,y))] = FindSet(std::min(x,y));
}

std::set<int> DisjointSets::SetIds(){
	std::set<int> res;
	for(unsigned int i = 0; i < uf.size(); i++)
		res.insert(uf[i]);
	return res;
}