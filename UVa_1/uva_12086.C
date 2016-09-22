/* UVa problem: <12086>
 *
 * Topic: (Data Structures)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *   Perform several operations on a list of values representing electrical resistance and return the results of these operations.
 *
 * Solution Summary:
 *
 *	This is a Fenwick tree problem. The Fenwick tree allows us to perform Range Sum Query's and singular update
 *	operations in a very short amount of time. 
 *
 *	I used the Fenwick tree code from the textbook. For each test case we construct the tree using the adjust operation.
 *	Then for the M operations I simply perform the range sum query.
 *
 *	For the S operations, you update the tree using adjust (adjust merely adds a value, you have to account for this.)
 *	Additionally, you have to update the original meter array or the wrong value can be produced.
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
#include <string.h>
#include <vector>
#include <sstream>

using namespace std;

typedef vector<int> vi;

//Text book bit operation required by the tree.
int LSOne(int i) {
	return (i & (-i));
}

class FenwickTree {
	private: vi ft;
	public: FenwickTree(int n) { ft.assign(n + 1, 0); }

		int rsq(int b) {
			int sum = 0; for (; b; b -= LSOne(b)) sum += ft[b];
			return sum;
		}

		int rsq(int a, int b) {
			return rsq(b) - (a == 1 ? 0 : rsq(a - 1));
		}

		void adjust(int k, int v) {
			for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v;
		}

		void printv() {
			for (auto it = ft.begin(); it != ft.end(); ++it) {
				cout << *it << " ";
			}
			cout << "\n";
		}

};

int main() {

	int N;
	vi meters;
	int meter;

	int counter = 1;
	while (cin >> N) {
		if (N == 0) break;				//Udebug requires this case, not sure if the problem does though.
		if (counter != 1) cout << "\n";	//Formatting garbage.

		cout << "Case " << counter << ":\n";
		FenwickTree ft(N);
		meters.push_back(-1);	//Since index 0 is ignored we push an arbitrary value
		for (int i = 0; i < N; ++i) {
			scanf("%d\n",&meter);
			meters.push_back(meter);
		}		

		//Index i is increased by the value of the meter at i.
		for (int i = 1; i <= N; ++i) {
			ft.adjust(i, meters[i]);
		}

		int x, y;
		string s;

		while (cin >> s) {
			if (s == "END") {
				break;
			}
			scanf("%d\n",&x);
			scanf("%d\n",&y);
			if (s == "S") {
				ft.adjust(x, -(meters[x] - y));	// Set X to Y? - Subtract(current value of x - value of y) from x in our tree.
				meters[x] = y;					// Have to update the value in our array since the tree wont account for that.
			} else {							//Should be an "M" operation case.
				printf("%d\n",ft.rsq(x,y));
			}
		}

		counter++;
		meters.clear();
	}

	return 0;
}