/* UVa problem: <100>
 *
 * Topic: (Arithmetic)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 *   Find the largest cycle length for the 3n+1 problem in a given range of numbers.
 *
 * Solution Summary:
 *
 *   Measure the cycle length of 3n+1 problem and change the max whenever the cycle is larger than existing max.
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
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int cycleLength(int i) {
	int count = 1;
	
	while (i != 1) {
		if (i %2 == 0) {
			i = i/2;
		}
		else {
			i = i*3 + 1;
		}
		count += 1;
	}
	return count;
}

int main() {
	string tmp;
	while(getline(cin, tmp)) {
		vector<int> nums;
		stringstream ss(tmp);
		int ti;
		while(ss >> ti) {
			nums.push_back(ti);
		}
		int x = nums[0];
		int y = nums[1];
		sort(nums.begin(),nums.end());
		int max = 0;
		for (int i = nums[0]; i <= nums[1]; ++i) {
			if (cycleLength(i) > max) {
				max = cycleLength(i);
			}
		}
		cout << x << " " << y << " " << max << "\n";
	}
	return 0;
}
