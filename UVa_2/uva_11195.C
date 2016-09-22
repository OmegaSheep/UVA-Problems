/* UVa problem: <11195>
 *
 * Topic: (Backtracking)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 *   Print total solution count for N-queens on a given board with blocked tiles.
 *
 * Solution Summary:
 *
 *   Use the bitmasking code directly from textbook. In addition, store an array of bitmasks representing the availability on a column-by-column
 *	 basis. Or the row | left diagonal | right diagonal and column values as necessary to produce a solution mask. Backtrack accordingly.
 *
 * Used Resources:
 *
 *   - Textbook
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <bitset>
#include <cmath>
#include <vector>
using namespace std;

//bitset<32> rw, ld, rd;
int row[8], TC, a, b, linecounter;
int n = 0;
long ans = 0; 
int OK;
char board[15][15];
vector<bitset<15>> columns(15); 

void makeCols() {
	int count = 0;
	for (int i=0; i < n; ++i) {
		for (int j=0; j < n; ++j) {
			if (board[i][j] == '*') {
				columns[j][i] = 1;
			}
		}
	}
}

void backtrack(int rw, int ld, int rd, int col) {
	if (rw == OK) { ans++; return; }
	int pos = OK & (~(rw | ld | rd | (int)columns[col].to_ulong()));
	 
	while (pos) {
		int p = pos & -pos;
		pos -= p;	
		backtrack(rw | p, (ld | p) << 1, (rd | p) >> 1, col+1);
	}
}

int main() {
	int casenum = 1;
	while(cin >> n) {
		if (n==0) {
			break;
		}
		//Get the input
		string line;
		int linecount = 0;
		getline(cin, line);
		while (linecount < n) {
			getline(cin, line);
			//cout << "Line = " << line << "\n";
			for (int i = 0; i < n; ++i) {
				char x = line[i];
				board[linecount][i] = x;
			}
			linecount++;
		}	
		makeCols();
		OK = (1<<n)-1;
		backtrack(0,0,0,0);
		printf("Case %d: %ld\n",casenum,ans);

		fill(columns.begin(), columns.end(), 0);
		ans = 0;
		casenum+=1;
	}

	return 0;
}

