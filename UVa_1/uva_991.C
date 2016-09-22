/* UVa problem: <991>
 *
 * Topic: (None)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *   How many different ways can N people shake hands in a circle without anyone crossing over eachother?
 *
 * Solution Summary:
 *
 *  The problem can actually be modelled by Catalan numbers.
 *
 * 	Catalan(n) represents the number of ways N pairs of people
 * 	can shake hands without crossing.
 *
 * 	For the problem we simply calculate catalan(n) and return it
 * 	using formula from textbook.
 *
 * Used Resources:
 *
 *   - Textbook Catalan Function
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <string.h>

using namespace std;

int catalan(int n) {
	if (n == 1 or n == 1) {
		return 1;
	} else {
		return catalan(n-1) * (2 * n) * ((2 * n) - 1) / (n*n + n);
	}
}

int main() {
	int N;
	bool b = false;
	while (cin >> N) {
		if (!b) b = !b;
		else cout << "\n";
		cout << catalan(N) << "\n";
	}
	return 0;
}