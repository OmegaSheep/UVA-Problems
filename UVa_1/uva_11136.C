/* UVa problem: <11136>
 *
 * Topic: (Data Structures)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *	Each day walmart adds bills to pile. It pays a fee equal to largest-smallest and then removes those bills. What is the total cost?
 *
 * Solution Summary:
 *
 *	I use a multi-set. It autosorts all the bills and the end of each day I remove the smallest and biggest before adding them to the total.
 *	At the end of the total cycle of days I print the total and then reset for the next test case.
 *
 * Used Resources:
 *
 *   - Textbook
 *	 - http://stackoverflow.com/questions/19468919/c-multisets-removing-the-last-element (remove last element)
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
#include <set>

using namespace std;

int main() {
	int N;
	long total = 0;
	string line;
	multiset<int> nums;
	while(1) {
		cin >> N;
		if (!N) {
			break;
		}

		int i = 0;
		long val;
		long bill;
		while (i < N) {

			//This gets a line of bills for the day.
			cin >> val;
			int j = 0;
			while (j < val) {
				cin >> bill;
				nums.insert(bill);
				j++;
			}

  			//Erase beginning
			auto bb = nums.begin();
			int b = *bb;
			nums.erase(bb);

			//Erase ending
			auto ee = nums.rbegin();
			int e = *ee;
			nums.erase((++ee).base());		

			//cout << "begin/end: " << b << " " << e << "\n";
			total += e-b;
			i++;
		}
		cout << total << "\n";
		nums.clear();
		total = 0;
	}
	return 0;
}