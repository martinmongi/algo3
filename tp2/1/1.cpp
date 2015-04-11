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
	vector<char> choices(n, BMX);

	for(int i = 0; i < n; i++)
		cin >> race[i].BMX_cost >> race[i].motox_cost >> race[i].buggy_cost;

	int total_time = solve(race, km, kb, 0, choices);

	cout << total_time << endl;

	for(int i = 0; i < n; i++)
		cout << (int)choices[i] << endl;
}

int solve(vector<Phase> &race, int km, int kb, int i, vector<char> &choices){

	if(i == race.size())
		return 0;

	int BMX_option = race[i].BMX_cost + solve(race, km, kb, i + 1, choices);
	int min_time = BMX_option;
	int best_choice = BMX;

	if(km > 0){
		int motox_option = race[i].motox_cost + solve(race, km - 1, kb, i + 1, choices);
		if(motox_option < min_time){
			min_time = motox_option;
			best_choice = MOTOX;
		}
	}
	
	if(kb > 0){
		int buggy_option = race[i].buggy_cost + solve(race, km, kb - 1, i + 1, choices);
		if(buggy_option < min_time){
			min_time = buggy_option;
			best_choice = BUGGY;
		}
	}

	// cout << "choices" << endl;
	// for(int j = 0; j < choices.size(); j++)
	// 	cout << (int)choices[i] << endl;

	// cout << "km, kb, i, best_choice" << SPACE << km << SPACE << kb << SPACE << i << SPACE << (int)best_choice << endl;

	return min_time;
}

