/* UVa problem: <11955>
 *
 * Topic: (Arithmetic)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *   Find the binomial expansion given two items and a power.
 *
 * Solution Summary:
 *
 *   Use DP to construct Pascal's Triangles. This will have all the coefficients.
 *	 Start parsing out the powers Going from a^p,b^0 -----> a^0,b^p. Use coefficients as necessary.
 *	 I have special cases for coefficient 1 and coefficient 0 to fit the formatting requirements.
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
#include <string.h>
#include <cmath>
using namespace std;

long triangles[51][51];

int main() {
	//Base case setup. See page 205 of textbook.
	memset(triangles,-1,sizeof(triangles));
	triangles[0][0] = 1;
	triangles[1][0] = 1;
	triangles[1][1] = 1;

	for (int i = 0; i <= 50; ++i) {
		for (int j = 0; j <= 50; j++) {
			triangles[i][0] = 1;
			triangles[i][i] = 1;
		}
	}
	for (int i = 2; i <= 50; ++i) {
		for (int j = 1; j < i; j++) {
			triangles[i][j] = triangles[i-1][j-1] + triangles[i-1][j]; 
		}
	}

	int N;
	cin >> N;
	string line;
	string a;
	string b;
	int p;
	getline(cin, line);	//Gets rid of first line. Weird C++ quirk.
	int count = 1;
	while (getline(cin, line)) {
		//Get each variable.
		line.erase(0,1);
		while (line[0] != '+') {
			a+= line[0];
			line.erase(0,1);
		}
		line.erase(0,1);
		while (line[0] != ')') {
			b+= line[0];
			line.erase(0,1);
		}
		//Get the power of the equation.
		line.erase(0,2);
		p = atoi(line.c_str());

		//We now have our things.
		cout << "Case " << count << ": ";
		int s = 0;

		//This print loop is kind of ugly but it uses the powers in pascals tree and parses it all out as required.
		for (int i = 0; i <= p; ++i) {
			if (i != 0)
				cout << "+";
			if (triangles[p][i] != 1) {
				printf("%ld*",triangles[p][i]);
			}

			if (p-i == 0) {

			} else if (p-i == 1) {
				printf("%s",a.c_str());
			} else {
				printf("%s^%d",a.c_str(),p-i);
			}

			if (p-i != 0 and s+i != 0)
				cout << "*";

			if (s+i == 0) {

			} else if (s+i == 1) {
				printf("%s",b.c_str());
			} else {
				printf("%s^%d",b.c_str(),s+i);
			}			
		}
		cout << "\n";

		//Reset strings.
		a = "";
		b = "";
		count++;
	}
	return 0;
}