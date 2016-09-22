/* UVa problem: <10055>
 *
 * Topic: (None)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *   Find the difference between two integers in a fairly large range.
 *
 * Solution Summary:
 *
 *   Use long instead of int to prevent overflows from ruining result. 
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
#include <cmath>
using namespace std;
int main() {
	long x;
	long y;
	while(cin >> x) {
		cin >> y;
		cout << abs(y-x) << "\n";
	}
	return 0;
}

