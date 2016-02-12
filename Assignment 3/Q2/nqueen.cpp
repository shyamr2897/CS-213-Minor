#include <iostream>
#include "queen_defs.h"

using namespace std;

Vars glob_vars;


void countQueens(int col, int ld, int rd) {
	// The three variables represent the dangers for the current row. 
	// col : bit pattern for dangers from vertical attacks
	// ld : bit pattern for dangers from bottom left diagonal attacks
	// rd : bit pattern for dangers from bottom right diagonal attacks
	
	if (solved (col, ld, rd)) {
		glob_vars.count++;
		return;
	}

	int valid_posns;
	valid_posns = getValidPositions(col, ld, rd);

	while (positionsAvailable(valid_posns)) {
		
		int cur_posn = chooseOnePosition(valid_posns);
		
		valid_posns = removeChosenPosition(valid_posns, cur_posn);

		int new_col = calcNewColDanger(col, cur_posn);
		int new_ld = calcNewLdDanger(ld, cur_posn);
		int new_rd = calcNewRdDanger(rd, cur_posn);

		countQueens(new_col, new_ld, new_rd);
	}
}

int main() {
	int N;
	cin >> N;

	glob_vars.setup(N);
	glob_vars.count = 0;

	countQueens(0,0,0);

	cout << glob_vars.count << endl;
}

