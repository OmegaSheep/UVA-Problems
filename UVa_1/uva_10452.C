/* UVa problem: <10452>
 *
 * Topic: (Backtracking)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *   Find the path from @ to # on the grid, only crossing through "IEHOVA".
 *
 * Solution Summary:
 *
 *   We backtrack by trying every possible direction. If our current tile is bad, we remove the direction from the list of directions
 *	 otherwise, we keep recursing forward. As soon as we reach the end we are finished.
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

#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <utility>

using namespace std;

const string god = "@IEHOVA#";
vector<string> instructions;

//For printing vectors.
void printv(vector<string> s) {
	for (auto it = s.begin(); it != s.end(); ++it) {
		if (it != s.begin() ) cout << " ";
		cout << *it;
	}
	cout << "\n";
}

// X is the number of steps taken, p is our position, end is our goal and maze is the current maze.
void backtrack(int x, pair<int,int> p, pair<int,int> end, vector< vector < char > > maze) {

	//We made it to the end!
	if ( p.first == end.first and p.second == end.second ) {
		return;
	}

	//If our current character is correct, we need to keep going!
	if (maze[p.first][p.second] == god[x]) {
		pair<int, int> p1, p2, p3;

		//p1 = forth
		//p2 = left
		//p3 = right
		p1 = make_pair(p.first-1,p.second);
		p2 = make_pair(p.first,p.second-1);
		p3 = make_pair(p.first,p.second+1);

		/* if checks ensure no out of bounds case */
		if ( p1.first >= 0) {
			instructions.push_back("forth");
			backtrack(x+1,p1,end,maze);
		}
		if (p2.second >= 0) {
			instructions.push_back("left");
			backtrack(x+1,p2,end,maze);
		}
		if (p3.second < maze[0].size()) {
			instructions.push_back("right");
			backtrack(x+1,p3,end,maze);
		}

	} 
	//If our current character is bad, we need to stop going this way. Remove the bad instruction!
	else {
		if (!instructions.empty())
			instructions.pop_back();
	}

}

int main() {
	int T;
	cin >> T;

	int m, n;

	for (int i=0; i < T; ++i) {

		//Get dimensions
		cin >> m;
		cin >> n;

		//This block creates the maze.
		vector< vector < char> > maze(m, vector<char> (n));
		char x;
		pair<int, int> start, end;
		for (int j = 0; j < m; ++j) {
			for (int k = 0; k < n; ++k) {
				cin >> x;
				if (x == '@') start = make_pair(j,k);
				if (x == '#') end = make_pair(j,k);
				maze[j][k] = x;
			}
		}

		backtrack(0,start,end,maze);
		printv(instructions);

		maze.clear();
		instructions.clear();
	}
}