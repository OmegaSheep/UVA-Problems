/* UVa problem: <729>
 *
 * Topic: (Combinatorics)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 *    Print all binary permutations of a given length with a given hamming distance in lexographical order.
 *
 * Solution Summary:
 *
 * I generate the lexicographically smallest permutation of string that meets the requirements.
 * Then I use C++ built in next_permutation to iterate through all the permutations of the given
 * hamming code since they will all have the same number of 1's and 0's. I print them out as I go.
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

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <bitset>
#include <string>

using namespace std;

int main() {
	int N;
	cin >> N;

	int iter = 0;
	int LEN = 0;
	int DIF = 0;
	while (iter < N) {
		cin >> LEN;
		cin >> DIF;
		// Base is the initial value. eg. 5, 3 ==> 00111
		vector<int> base;

		//Add the 0's.
		for (int i = 0; i < LEN-DIF; i++) {
			base.push_back(0);
		}

		//Add the 1's.
		for (int i = 0; i < DIF; i++) {
			base.push_back(1);
		}

		//Basic do-while loop to try every permutation.
		do {
			for (int i = 0; i < base.size(); ++i)
				cout << base[i];
			cout << "\n";
		} while (next_permutation(base.begin(),base.end() ) );
		iter++;

		//This prevents an extra new line on the last case which causes submission to fail.
		if (iter != N)
			cout << "\n";
	}
}