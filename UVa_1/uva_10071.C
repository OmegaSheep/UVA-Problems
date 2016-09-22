/* UVa problem: <10071>
 *
 * Topic: (None)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *   A particle has initial velocity and acceleration. If its velocity after certain time is v then what will its 
 *	 displacement be in twice of that time?
 *
 * Solution Summary:
 *
 *   Given velocity and time, the displacement in twice that time is simple 2 times displacement which is 2 * v * t.
 *
 * Used Resources:
 *
 *   - Literally none. Just the textbook I guess?
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <bitset>
#include <tuple>
#include <cmath>
#include <utility>
#include <string>
#include <sstream>

using namespace std;

int main() {
	int v;
	int t;
	while (cin >> v) {
		cin >> t;
		cout << 2 * v * t << "\n";
	}
}