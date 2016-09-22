/* UVa problem: <11254>
 *
 * Topic: (None)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 *  Given a positive integer n, what are the consecutive positive integers with sum being n?
 *   
 * Solution Summary:
 *
 *  Formula for arithmetic series sum is (n/2) * (2a + (n-1) * d)
 *
 * 	Since we jump by one number, d = 1.
 *
 *	We can isolate: a = (2 * sum + n-n^2) / (2 * n)
 *
 *	We can check if a is valid by ensuring (2 * sum + n-n^2) is divisible
 *	by (2 * n).
 *
 * 	Since the maximum possible value for n is roughly sqrt(2 * sum) we simply start from there
 * 	and work our way down, stopping as soon as we find a solution (instead of going
 * 	forward and recording our maximum solution).
 *
 * 	Finally for the answer, a is your first number and a + n - 1 is your last number. 
 *
 * Used Resources:
 *
 *   - https://en.wikipedia.org/wiki/Arithmetic_progression
 *	 - Textbook a little bit. 
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int sum;
	int a;
	while (cin >> sum) {
		if (sum == -1) break;
		int N = 0;
		for (int i = sqrt(2*sum); i > 0; --i) {

			//We want the largest solution, so work backwards.
			if ((2*sum+i-i*i) % (2*i) == 0) {
				a = (2*sum + i - i*i) / (2*i);
				N = i;
				break;
			}
		}
		cout << sum << " = " << a << " + ... + " << a + N - 1 << "\n";
	}
	return 0;
}