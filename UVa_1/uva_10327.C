/* UVa problem: <10327>
 *
 * Topic: (Sorting)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *   Find the minimum number of "flips" required to sort an input list.
 *
 * Solution Summary:
 *
 *   Perform a traditional bubble sort, but increment a counter everytime you flip. Return the counter value.
 *
 * Used Resources:
 *
 *   - Textbook
 *	 - Referenced: https://en.wikipedia.org/wiki/Bubble_sort
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int flipcount(vector<int> x) {
	
	int total = 0;
	int n = x.size();
	int tmp;

	for (int i=0;i<n-1;++i) {
		for(int j=0;j<n-1;++j) {
			if (x[j] > x[j+ 1]) {
				tmp = x[j];
				x[j] = x[j+1];
				x[j+1] = tmp;
				total++;
			}
		}
	}
	return total;
}

int main() { 
	
	int size;
	vector<int> nums;
	string line;
	string message = "Minimum exchange operations : ";
	int ans;	
	int numm;
	while (scanf("%d\n", &size) == 1) {
		for (int i = 0; i < size; ++i) {
			scanf("%d\n", &numm);
			nums.push_back(numm); 
		}
		//hello picnic this line does literally nothing!
		ans = flipcount(nums);
		cout << message << ans << "\n"; 
		nums.clear();	

	}		 		
	return 0;
}	


