/* UVa problem: <10608>
 *
 * Topic: (Data Structures)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *    Given a list of people and who they are friends with, determine the largest group of friends.
 *
 * Solution Summary:
 *
 *		I created a Union-Find Disjoint Set using textbook code.
 *	 	After I create it, I check every person to see who their most prominent friend is.
 *		The "prominent friend" who shows up the most is the person with the most friends.
 *		I use a map to determine how often he/she shows up (ie. how many friends do they have)
 *		After I print the result I move on to the next case.
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
#include <map>

using namespace std;

// From textbook.
class UnionFind {
private: vector<int> p; vector<int> rank;
public:
	UnionFind(int N) { rank.assign(N, 0);
		p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; }
	int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
	bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
	void unionSet(int i, int j) {
		if (!isSameSet(i, j)) {
			int x = findSet(i), y = findSet(j);
			if (rank[x] > rank[y]) p[y] = x;
			else {				   p[x] = y;
								   if (rank[x] == rank[y]) rank[y]++; }
		} 
	} 
	void printt(int i) {
		cout << p[i] << "\n";
	}
};

int main() {

	int t;
	cin >> t; // test case numnbers

	int i = 0;
	while (i < t) {
		int N, M;
		cin >> N;
		cin >> M;
		UnionFind* c = new UnionFind(N);
		int a, b;
		for (int j=0; j < M; j++) {
			cin >> a;
			cin >> b;
			c->unionSet(a-1, b-1); // the union set indexes from 0, unlike the problem.
		}

		// We create a map to determine what the most common value is.
		// I'm certain there's a better way to do this but whatever.
		map<int, int> k;
		for (int i=0;i<N;++i) {
			int temp = c->findSet(i);
			k[temp] += 1;
		}
		int max = -1;
		for (int i=0; i < N; i++) {
			if (k[i] > max) {
				max = k[i];
			}
		} 

		// Handle the zero case.
		if (M != 0)		
			cout << max << "\n";
		else
			cout << "0\n";

		// clear vars, iterate
		delete c;
		k.clear();
		i++;
	}
	return 0;
}