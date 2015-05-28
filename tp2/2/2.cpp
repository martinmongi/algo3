#include "2.h"
#include "grid.h"

using namespace std;

int main(){
	Grid city;
	city.PrintGrid();
	cout << city.Solve() << endl;
	city.PrintCorners();
	return 0;

	
}