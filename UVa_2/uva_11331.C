/* UVa problem: <11331>
 *
 * Topic: (Bipartite Graphs)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 *   Determine if b+c nodes with 'a' edges (provided) can be 2-colored with exactly b and c nodes of each color.
 *
 * Solution Summary:
 *
 *   1. Determine if graph is bipartite at all.
 *   2. Construct a list of tuples of each graph component and the size of its partitions.
 *   3. Use dynamic programming to determine if a m sum can be made from the tuples to produce b or c.
 *   4. If nothing has failed so far, return true. Else return false.
 *
 * Used Resources:
 *
 *   - Textbook (particularly illuminating for the bipartite check, and the dynamic element)
 *   - https://en.wikipedia.org/wiki/m_sum_problem
 *   - https://en.wikipedia.org/wiki/Knapsack_problem
 * 
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

//INPUT:  Takes in, a source node, list of node colorings, a queue and an adjacency list. 
//OUTPUT: Returns if the graph is bipartite or not.
bool bipartiteCheck(int source, int vex, vector<int> &colo, queue<int> &qq, vector<vector<int>> &adjlis) {
	qq.push(source);
	colo[source] = 0;
	bool isBipartite = true;
	while(!qq.empty() & isBipartite) {
		
		int u = qq.front(); qq.pop();
		for (int j = 0; j < vex; j++) {
			if (adjlis[u][j] && colo[j] == -1) {
				int col = 1 - colo[u];
				colo[j] = col;
				qq.push(j);
			}
			else if (adjlis[u][j] && colo[j] == colo[u]) {
				isBipartite = false;
			}
		}	
	}	
	return isBipartite;
}

int main() {
	int cases; 	 		// Number of cases.
	int b;				// # of bulls
	int c;				// # of cows
	int a;				// # of edges

	int temp1; 	 		// Temporary vars for filling adjacency list.
	int temp2; 

	int red = 0; 		// 'red' and 'blue' are used for counting partition size of each graph component.
	int blue = 0;
	bool pass = true;	// Does the solution still work for this graph?

	cin >> cases;
	while(cin >> b >> c >> a) {
		vector<int> colors(b+c, -1); 							 // Contains the color of each node.
		queue<int> q;											 // Queue for bipartite algorithm.
		vector< vector<int> > adjlist (b+c, vector<int>(b+c,0)); // 1 = adjacent, 0 = not, -1 = untouched.
		vector<tuple<int, int>> knapsack; 						 // Contains partition sizing for each graph component.

		// Fill the adjecency list.
		for (int i = 0; i < a; ++i) {
			cin >> temp1 >> temp2;
			adjlist[temp1-1][temp2-1] = 1;
			adjlist[temp2-1][temp1-1] = 1;
		}
		
		// If graph disconnected, we reattempt coloring at a new source node.
		for (int i = 0; i < colors.size(); ++i) {
			if (colors[i] == -1) {
				if (pass) {

					// Colors new component and determines if still bipartite.
					pass = bipartiteCheck(i,b+c,colors,q,adjlist);

					// Fill knapsack with partition size of new component.
					for (int x = 0; x < colors.size(); ++x) {
						if (colors[x] == 1) {
							colors[x] = 2; // Section has been Knapsacked.
							red++;
						}
						else if (colors[x] == 0) {
							colors[x] = 2; // Section has been Knapsacked.
							blue++;
						}
					}
					// Add component to knapsack and reset counters.
					knapsack.push_back(make_tuple(red,blue));
					red = 0;
					blue = 0;

				}

				// If we are no longer passing it is time to stop.
				else {
					continue;
				}
			}
		}

		
		// Still passing? Need to verify backpack fits.
		if (pass) {

			// Order all tuples by (big,small).
			for (int i = 0; i < knapsack.size(); ++i) {
				int p = get<0>(knapsack[i]);
				int r = get<1>(knapsack[i]);
				if ( p < r) {
					knapsack[i] = make_tuple(r,p);
				}
			}

			int w = max(b,c);										// Try to solve for the larger b||c value, the smaller value will follow.
			int n = knapsack.size();						// Number of items in the knapsack essentially.
			vector< vector<bool> > m(w+1,				// Grid of bools for determining if we can solve problem at a given size.
				vector<bool>(n+1));

			// 0 items can fit into anything.
			for (int i = 0; i <= n; ++ i) {
				m[0][i] = true;
			}

			// Begin dynamic programming bottom up.
			for (int i = 1; i <= w; ++i) {
				for (int j = 1; j <= n; ++j) {
					m[i][j] = m[i][j-1];

					// Attempts to use the larger element of the tuple.
					if (i >= get<0>(knapsack[j-1])) {
						if (!m[i][j])
							m[i][j] = m[i - get<0>(knapsack[j-1]) ][j-1];
					} 
					// Attempts to use the smaller element of the tuple.
					else if (i >= get<1>(knapsack[j-1])) {
						if (!m[i][j])
							m[i][j] = m[i - get<1>(knapsack[j-1]) ][j-1];
					}
				}
			}
			pass = m[w][n]; // Can we fit all the tuples into exactly this weight?
		}

		// Print the final answer.
		if (pass)
			cout << "yes\n";
		else
			cout << "no\n";

		//Reset for next run.
		pass = true;
		adjlist.clear();
		colors.clear();
		knapsack.clear();
	}
	return 0;
}
