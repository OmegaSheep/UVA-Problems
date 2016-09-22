/* UVa problem: <11659>
 *
 * Topic: (Backtracking)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 * Solution Summary:
 *
 *	Since there are a small number n < 20 informants I brute force the problem.
 *	I start by generating every permutation of truth-lie combinations.
 *	For each permutation, I verify whether it is even POSSIBLE that the given statements are all consistent.
 *	I keep track of the largest number of truth tellers for each POSSIBLE permutation.
 *	The largest truth telling permutation that is possible is the correct one.
 *
 * Used Resources:
 *
 *   - Textbook
 *	 - http://stackoverflow.com/questions/109023/how-to-count-the-number-of-set-bits-in-a-32-bit-integer
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
#include <sstream>
#include <bitset>
#include <tuple>

using namespace std;

//Function from stack overflow.
int Bits(int i)
{
     // Java: use >>> instead of >>
     // C or C++: use uint32_t
     i = i - ((i >> 1) & 0x55555555);
     i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
     return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

bitset<800> informers; //800 max size
int main() {
	int ii; // num informants
	int a; // num of answers
	while (1) {
		cin >> ii;
		cin >> a;
		if (ii + a == 0) {
			break;
		}
		bool reliable;
		int count = 0;
		vector<tuple<int,int>> statements;
		while (count < a) {
			int x, y;
			cin >> x;
			cin >> y;
			statements.push_back(make_tuple(x,y));
			count += 1;
		}

		//For every permutation.
		int max = 0;
		for (int i = 0; i < pow(2,ii); ++i) {
			informers = i;
			bool truetrue = true;

			//For each statement.
			for (int j = 0; j < statements.size(); ++j) {
				int xx = get<0>(statements[j]);
				int yy = get<1>(statements[j]);
				reliable = yy > 0 ? true : false;

				if (reliable && informers[xx-1] == 1 && informers[abs(yy)-1] != 1) { 
					truetrue = false;
					break;
				}
				if (!reliable && informers[xx-1] == 1 && informers[abs(yy)-1] != 0) { 
					truetrue = false;
					break;
				}
			}

			if (truetrue) {
				//cout << "Found Solution: " << i << "\n";
				//cout << "Bits: " << Bits(i) << "\n";
				if (Bits(i) > max) {
					max = Bits(i);
				}
			}
		}	
		cout << max << "\n";
		statements.clear();
	}
	return 0;
}