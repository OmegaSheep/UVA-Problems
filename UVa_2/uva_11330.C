/* UVa problem: <11330>
 *
 * Topic: (Combinatorics)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 * What is the minimum number of moves required to sort the shoes by pair, if our only operation is swap shoes.
 *
 * Solution Summary:
 *
 *	The core of the solution is maintaining a two-way unordered mapping from ShoeType -> Position and
 *	Position -> ShoeType. We do this seperately for left and right shoes to avoid confusions.
 *	
 *	As for the actual solution, we greedily swap shoes from left to right in a way that at least 1 pair is made
 *	every swap. By the time we reach the end of the shoes we will have sorted the entire thing in the most minimal way
 *	possible.
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
#include <algorithm>
#include <sstream>
#include <string>
#include <unordered_map>
#include <stdio.h>
#include <climits>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include <set>
#include <utility>

using namespace std;


int main() {
	unordered_map<int,int> left2pos;
	unordered_map<int,int> right2pos;
	unordered_map<int,int> pos2left;
	unordered_map<int,int> pos2right;

	vector<int> shoes;
	int shoe1, shoe2;
	int N;
	cin >> N; //Num of test cases.

	for (int i=0;i<N;++i) {
		int swaps = 0;

		int shoeNum;
		cin >> shoeNum;
		int ii = 0;

		// Loop for shoe getting.
		while (ii < shoeNum*2) {

			if (ii % 2 == 0) {
				cin >> shoe1;
				left2pos[shoe1] = ii;
				pos2left[ii] = shoe1;
			}
			else if (ii % 2 == 1) {
				cin >> shoe2;	
				right2pos[shoe2] = ii;
				pos2right[ii] = shoe2;
				shoes.push_back(shoe1);
				shoes.push_back(shoe2);
			}
			ii++;
		}

		// Loop for shoe sorting.
		for (int i = 0; i < shoes.size(); ++i) {

			//Even shoe, dont swap if already a pair.
			if (i % 2 == 0 and shoes[i] != shoes[i+1]) {
				int swp;
				swp = left2pos[shoes[i+1]];

				int tmp = shoes[i];

				shoes[i] = shoes[swp];
				pos2left[i] = shoes[swp];
				left2pos[shoes[swp]] = i;

				shoes[swp] = tmp;
				pos2left[swp] = tmp;
				left2pos[tmp] = swp;

				swaps++;
			}

			//Odd shoe, dont swap if already a pair.
			if (i % 2 == 1 and shoes[i] != shoes[i-1]) {
				int swp;
				swp = right2pos[shoes[i-1]];

				int tmp = shoes[i];

				shoes[i] = shoes[swp];
				pos2right[i] = shoes[swp];
				right2pos[shoes[swp]] = i;

				shoes[swp] = tmp;
				pos2right[swp] = tmp;
				right2pos[tmp] = swp;

				swaps++;
			}
		}

		cout << swaps << "\n";
		shoes.clear();
	}
	return 0;
}