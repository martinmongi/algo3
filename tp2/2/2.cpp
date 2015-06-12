#include "grid.h"

using namespace std;

int main(){
	Grid city;

	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

	city.Solve();

	chrono::steady_clock::time_point t2 = chrono::steady_clock::now();

	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

	cerr << city.n << ", " << city.m << ", " << city.s << ", " << time_span.count();
	cerr << endl;	

	// city.PrintGrid();
	// city.PrintCorners();
	city.PrintTrajectory();
	return 0;
}