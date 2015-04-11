#include "1.h"

#define BMX 1
#define MOTOX 2
#define BUGGY 3
#define SPACE ' '

using namespace std;

int main(){
	int n, km, kb, i;
	cin >> n >> km >> kb;
	vector<Phase> race(n);

	for(int i = 0; i < n; i++)
		cin >> race[i].BMX_cost >> race[i].motox_cost >> race[i].buggy_cost;

	pair<int,stack<char> > res = solve(race, km, kb, 0);

	cout << res.first << endl;

	while(!res.second.empty()){
		cout << (int)res.second.top() << endl;
		res.second.pop();
	}
}

pair<int,stack<char> > solve(vector<Phase> &race, int km, int kb, int i){

	pair<int,stack<char> > res, BMX_option, motox_option, buggy_option;
	if(i == race.size()){
		res.first = 0;
		return res;
	}

	BMX_option = solve(race, km, kb, i + 1);
	BMX_option.first += race[i].BMX_cost;
	int min_time = BMX_option.first;
	char best_choice = BMX;

	if(km > 0){
		motox_option = solve(race, km - 1, kb, i + 1);
		motox_option.first += race[i].motox_cost;
		if(motox_option.first < min_time){
			min_time = motox_option.first;
			best_choice = MOTOX;
		}

	}if(kb > 0){
		buggy_option = solve(race, km, kb - 1, i + 1);
		buggy_option.first += race[i].buggy_cost;
		if(buggy_option.first < min_time){
			min_time = buggy_option.first;
			best_choice = BUGGY;
		}
	}

	if(best_choice == BMX){
		BMX_option.second.push(BMX);
		return BMX_option;
	}else if(best_choice == MOTOX){
		motox_option.second.push(MOTOX);
		return motox_option;
	}else{
		buggy_option.second.push(BUGGY);
		return buggy_option;
	}

	// cout << "choices" << endl;
	// for(int j = 0; j < choices.size(); j++)
	// 	cout << (int)choices[i] << endl;

	// cout << "km, kb, i, best_choice" << SPACE << km << SPACE << kb << SPACE << i << SPACE << (int)best_choice << endl;
}

