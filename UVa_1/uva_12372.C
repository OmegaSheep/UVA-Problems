/* UVa problem: <12372>
 *
 * Topic: (None)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *   Find if a box fits inside the 20x20x20 suitcase.
 *
 * Solution Summary:
 *
 *   Ensure that all dimensions are less than or equal to 20. If they are, it fits.
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
#include <cmath>
using namespace std;

int main() {
	int N;
	cin >> N;
	int i = 0;
	while (i < N) {
		int a;
		int b;
		int c;
		cin >> a;
		cin >> b;
		cin >> c;

		if (a <= 20 and b <= 20 and c<= 20) {
			cout << "Case " << i+1 << ": good\n";
		} else {
			cout << "Case " << i+1 << ": bad\n";
		}
		i++;
	}
	return 0;
}