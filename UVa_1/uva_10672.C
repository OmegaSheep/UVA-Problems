/* UVa problem: <10672>
 *
 * Topic: (Graphs)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *  Find the minimum number of moves to get 1 marble at each position on a tree.
 *
 * Solution Summary:
 *
 *	It's an almost greedy approach, we simply move Marbles as efficiently as possible.
 *	1. Start with all of the leaves of the tree. Move all but 1 marble from the leaves to the parent.
 *	2. After moving from a leaf. Remove that leaf.
 *	3. Increment our total by the number of marbles we moved each operation.
 *	4. If a parent has no children left, it becomes a leaf.
 *	5. Finally, when we run out of leaves return the total.
 *
 * Used Resources:
 *
 *   - Textbook
 *	 - http://www.algorithmist.com/index.php/UVa_10672 (Explains problem in a high level sense)
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
#include <unordered_map>
#include <queue>

using namespace std;

int main() {
	int N;
	while (1) {
		cin >> N;
		if (!N) break;
		int totalMoves = 0;

		int vertex;
		int marbles;
		int childrenNum;
		int child;

		vector<int> parents(N,-1);	// Who is a nodes parent. -1 if root.
		vector<int> childCount(N);	// How many children does a node have?
		vector<int> marbleCount(N);	// How many marbles does a node have?

		for (int i=0;i<N;++i) {

			cin >> vertex;
			cin >> marbles;
			cin >> childrenNum;

			childCount[vertex-1] = childrenNum;
			marbleCount[vertex-1] = marbles;

			//Indicate parents for future reference.
			for (int j=0; j<childrenNum;++j) {
				cin >> child;
				parents[child-1] = vertex;
			}
		}

		//Create queue and all the leaves to it.
		queue<int> leaves;
		for (int k = 0; k < N; ++k) {
			if (childCount[k] == 0) {
				leaves.push(k+1);
			}
		}

		//Keep going until we run out of leaves.
		while (!leaves.empty()) {
			int leaf = leaves.front();
			leaves.pop();
			int parent = parents[leaf-1];

			//No parents left? Break.
			if (parent==-1) break;

			//Parent has one less child.
			childCount[parent-1] -= 1;

			//If the parent is a leaf now, add it to the queue.
			if (childCount[parent-1] == 0) {
				leaves.push(parent);
			}

			// Add all but one marble to the parent.
			marbleCount[parent-1] += marbleCount[leaf-1] - 1;

			//Total moves increases by the number of marbles we moved.
			//This may occasionally be negative but will always balance out when finished.
			totalMoves += abs(marbleCount[leaf-1] - 1);
		}
		cout << totalMoves << "\n";
	}
	return 0;
}
