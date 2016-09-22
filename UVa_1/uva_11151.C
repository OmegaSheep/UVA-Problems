/* UVa problem: <11151>
 *
 * Topic: (Dynamic Programming)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *	Determine the longest palindrome in a given word.
 *
 * Solution Summary:
 *
 *   Use dynamic programming to solve for smaller string values and eventually determine the result for the whole.
 *
 * Used Resources:
 *
 *   - Textbook (states the algorithm basically flat out)
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <sstream>
#define MAX_VAL 1000

using namespace std;
int mem[MAX_VAL][MAX_VAL];
string line;

int palin(string &s, int l, int r) {
	if (s.length() == 0)
		return 0;	
	if (mem[l][r] != -1) {
		return mem[l][r];
	}
	if (l==r) {
		return mem[l][r] = 1;
	}		
	if (l+1 == r) {
		if (line[l] == line[r]) {
			return mem[l][r] = 2;	
		}
		else {
			return mem[l][r] = 1;
		}
	}
	if (line[l] == line[r]) {
		return mem[l][r] = 2 + palin(line,l+1,r-1);	
	}	
	else {
		return mem[l][r] = max(palin(line,l,r-1), palin(line,l+1,r));
	}	
}

int main() {
	int counter = 0;
	int cases;
	int n;
	char c;
	memset(mem,-1,sizeof(mem));
	cin >> cases;
	mem[0][0] = 0;
	getline(cin, line);
	while (counter < cases) {
		counter++;
		getline(cin, line); //Seems to fix getting stuck on the first new line after the cases number.
		n = line.length();
		if (n) {
			palin(line,0,n);
			cout << mem[0][n] << "\n";
		}
		else {
			cout << "0\n";
		}
		memset(mem,-1,sizeof(mem));
	}
	return 0;
}
