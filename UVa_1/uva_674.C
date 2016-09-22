/* UVa problem: <674>
 *
 * Topic: (Dynamic Programming)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *	Determine the # of different ways of producing the given value with 5 coin types.
 *
 * Solution Summary:
 *
 *   Use dynamic programming to solve for smaller values and eventually produce the full solution.
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
#define MAX_VAL 7500
using namespace std;

int mem[6][MAX_VAL];

int ways(int type, int value, vector<int> cV) {
	if (mem[type][value] == -1) {
		if (value == 0) {
			mem[type][value] = 1;
			return 1;
		}
		//For negatives.
		if (value < 0) {
			return 0;
		}
		if (type == 5) {
			mem[type][value] = 0;
			return 0;
		}
		return mem[type][value] = ways(type + 1, value, cV) + ways(type, value - cV[type], cV);	
	}
	else {
		return mem[type][value];
	}
}

int main() {
	int total; //Input
	vector<int> coinValue(5);
	coinValue[0] = 1;
	coinValue[1] = 5;
	coinValue[2] = 10;
	coinValue[3] = 25;
	coinValue[4] = 50;
	memset(mem,-1,sizeof(mem)); //Only have to do this once. Future inputs can re-use past values.
	while( cin >> total ) {
		cout << ways(0, total, coinValue) << "\n";
	}
	return 0;	
}
