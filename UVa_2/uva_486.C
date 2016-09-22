/* UVa problem: <486>
 *
 * Topic: (String)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 *   Convert the english phrase of a number into an integer.
 *
 * Solution Summary:
 *
 *   Break up number by words and use a series of categories to distinguish addition and multiplication.
 *	 I use maps to control the word->value conversion.
 *
 * Used Resources:
 *
 *   - Textbook
 *	 - http://stackoverflow.com/questions/18318980/taking-input-of-a-string-word-by-word (STREAMING WORDS PROPERLY IN C++)
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */


#include <iostream>
#include <sstream>
#include <algorithm>
#include <sstream>
#include <string>
#include <map>

using namespace std;

int main() {
	string negative = "negative";
	map<string, int> nums;

	//Cat 1
	nums["zero"] = 0;
	nums["one"] = 1;
	nums["two"] = 2;
	nums["three"] = 3;
	nums["four"] = 4;
	nums["five"] = 5;
	nums["six"] = 6;
	nums["seven"] = 7;
	nums["eight"] = 8;
	nums["nine"] = 9;
	nums["ten"] = 10;
	nums["eleven"] = 11;
	nums["twelve"] = 12;
	nums["thirteen"] = 13;
	nums["fourteen"] = 14;
	nums["fifteen"] = 15;
	nums["sixteen"] = 16;
	nums["seventeen"] = 17;
	nums["eighteen"] = 18;
	nums["nineteen"] = 19;
	nums["twenty"] = 20;
	nums["thirty"] = 30;
	nums["forty"] = 40;
	nums["fifty"] = 50;
	nums["sixty"] = 60;
	nums["seventy"] = 70;
	nums["eighty"] = 80;
	nums["ninety"] = 90;

	//Cat 2
	nums["hundred"] = 100;

	//Cat 3
	nums["thousand"] = 1000;

	//Cat 4
	nums["million"] = 1000000;

	string N;
	string line;
	long total_num = 0;
	bool neg = false;
	long temp = 0;
	int cat;		// Current number category.
	int pcat = 9000; //Previous number category. Set higher initially to control behaviour.

	while(getline(cin, line)) {
		istringstream iss(line);

		string N;
		string line;
		long total_num = 0;
		bool neg = false;
		long temp = 0;
		int cat;
		int pcat = 9000;

		while(iss >> N) {
			if (N == negative) {
				neg = true;
				continue;
			}
			if (nums[N] < 100) {
				cat = 1;
			}
			else if (nums[N] < 1000) {
				cat = 2;
			}
			else if (nums[N] < 1000000) {
				cat = 3;
			}
			else {
				cat = 4;
			}
			if (cat == pcat) {
				temp += nums[N];
			} else if (cat <= pcat) {
				temp += nums[N];
			} else if (cat > pcat) {
				temp *= nums[N];
			}

			pcat = cat;
			if (cat == 4) {
				total_num += temp;
				temp = 0;
			}
			if (cat == 3) {
				total_num += temp;
				temp = 0;
			}
		}

		total_num += temp;
		if (neg) {
			total_num *= -1;
		}
		cout << total_num << "\n";
	}
	return 0;
}
