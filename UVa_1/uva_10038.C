/* UVa problem: <10038>
 *
 * Topic: (None)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *   Given a list of numbers, do the differences between them represent 1 through n-1?
 *
 * Solution Summary:
 *
 *   Calculate all the difference values. Put them in an array. Sort it. Is the sorted array = to 1, 2, 3 etc...?
 *	 Return if it is jolly or not. 
 *
 * Used Resources:
 *
 *   - N/A
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

void printVector(vector<int> v) {
	for (auto it = v.begin(); it != v.end(); ++it) {
		cout << *it << " ";
	}
	cout << "\n";
}
int main() {
	int size;
	int num;
	vector<int> numbers;
	vector<int> jumpers;
	while (cin >> size) {
		for (int i=0;i<size;++i) {
			cin >> num;
			numbers.push_back(num);
		}
		if (size == 1) {
			printf("Jolly\n");
			numbers.clear();
			jumpers.clear();
			continue;
		} 
		else {
			for (int i =0; i < numbers.size()-1; ++i) {
				jumpers.push_back(abs(numbers[i] - numbers[i+1]));
			}
			sort(jumpers.begin(),jumpers.end());
			bool jolly = true;
			for (int i=0;i<jumpers.size();++i) {
				if (jumpers[i] != i+1) {
					jolly = false;
				}
			}
			if (jolly)
				printf("Jolly\n");
			else
				printf("Not jolly\n");
		}
		numbers.clear();
		jumpers.clear();
	}
	return 0;
}