/* UVa problem: <10026>
 *
 * Topic: (Sorting)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 *	- Determine the ordering for jobs such that the shoemaker pays the minimum price.
 *
 * Solution Summary:
 *	
 *	- Perform bubble sort but compare the cost that each value will inflict if it does not go first based on the duration of each job.
 *	- Return the sorted order of jobs.
 *	
 * Used Resources:
 *
 *   - Textbook
 *	 - Referenced: https://en.wikipedia.org/wiki/Bubble_sort
 * 
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

void shoeSort(vector <int> &jobz, vector<int> &f, vector<int> &t) {
	
	int n = jobz.size();
	int tmp;

	for (int i=0;i<n-1;++i) {
		for(int j=0;j<n-1;++j) {
			if (f[j+1]*t[j] > f[j]*t[j+1]) {
				tmp = jobz[j];
				jobz[j] = jobz[j+1];
				jobz[j+1] = tmp;

				tmp = f[j];
				f[j] = f[j+1];
				f[j+1] = tmp;

				tmp = t[j];
				t[j] = t[j+1];
				t[j+1] = tmp;
			}
		}
	}
}

int main() {
	int cases;
	int N;
	int t;
	int fine;
	cin >> cases;
	vector<int> Fine;
	vector<int> Time;
	vector<int> Jobs;
	for (int i = 0; i < cases; ++i) {
		cin >> N;
		for (int j = 0; j < N; ++j) {
			cin >> t >> fine;
			Fine.push_back(fine);
			Time.push_back(t);
			Jobs.push_back(j+1);
		}
		shoeSort(Jobs,Fine,Time);
		if (i)
			cout << "\n";
		for (int k = 0; k < Jobs.size(); ++k) {
			if (k)
				cout << " ";
			cout << Jobs[k];
		}
		cout << "\n";
		Jobs.clear();
		Time.clear();
		Fine.clear();
	}
}