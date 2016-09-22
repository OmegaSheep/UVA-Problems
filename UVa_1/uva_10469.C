/* UVa problem: <10469>
 *
 * Topic: (None)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *   Perform unsigned version of addition of two numbers.
 *
 * Solution Summary:
 *
 *  The problem can be solved by simply performing 
 *	a bitwise XOR operation on the two numbers to produce the
 * 	unsigned addition in 32 bits.
 *
 * Used Resources:
 *
 *   - Textbook (Suggested XOR)
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

#include <iostream>

using namespace std;
int main() {
	int a, b;
	while(cin >> a) {
		cin >> b;
		int x = a ^ b;
		cout << x << "\n";
	}
}