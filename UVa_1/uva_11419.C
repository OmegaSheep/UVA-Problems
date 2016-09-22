/* UVa problem: <11419>
 *
 * Topic: (Bipartite Graphs)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *   Find the minimum number of canons and their locations to kill all enemies on a grid.
 *
 * Solution Summary:
 *
 *   This boils down to a network flow problem, the PDF I linked describes a similar problem nicely.
 *
 *	 1. Create a flowgraph. The first node is source. The last is the sink. 
 *	 2. Connect from the source to all rows that contain enemies. dist = 1
 *	 3. Connect all columns that contain enemies to the sink. dist = 1
 *	 4. Connect each row with an enemy to the column that the enemy is in. dist = infinity
 *	 5. Perform the Edmond Karp network flow algorithm on the resulting graph.
 *	 6. Perform a DFS on the result. Rows that were unvisitable and columns that are visitable represent the position of the cannons.
 *	 7. The Edmond Karp algorithm itself returns the total number of canons required.
 *	 8. Process the result.
 *
 * Used Resources:
 *
 *   - Class Code Archive (edmondkarp.cpp, graph.cpp, dijkstra.cpp [dijkstra not used in final product] )
 *	 - http://olympiad.cs.uct.ac.za/presentations/camp2_2008/vertexcover.pdf 
 	   (^^ Describes a similar problem from a high level stand point in not too specific amount of detail.)
 *	 - https://en.wikipedia.org/wiki/Depth-first_search (Pseudocode for depth first search was useful, but not followed directly.)
 *	 - Textbook Point Struct (used for enemy position)
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <limits>
#include <climits>
#include <queue>
#include <functional>
#include <utility>

using namespace std;

struct point { int x, y; 
	point() { x = y = 0; }
	point(int _x, int _y) : x(_x), y(_y) {}
};

//Print debug function.
void vpi(vector<int> v) {
	for (auto it = v.begin(); it!= v.end(); ++it) {
		cout << *it << " ";
	}
	cout << "\n";
}

//Print debug function.
void vpb(vector<bool> v) {
	for (auto it = v.begin(); it!= v.end(); ++it) {
		cout << *it << " ";
	}
	cout << "\n";
}

// From class code archive.
// Flow graph implementation, including reverse-edge pointers.
struct FlowEdge {
	FlowEdge() : dst(0), src(0), cap(0), flow(0) {}
	FlowEdge(int src, int dst, int cap) : src(src), dst(dst), cap(cap), flow(0) {}
	int dst, src, cap;
	int flow;
	FlowEdge *redge;

	bool operator<(const FlowEdge& rhs) const { return cap > rhs.cap; }
};

// From class code archive.
// Typedefs for readability.
typedef vector<list<FlowEdge> > AdjFlowGraph;
typedef vector<list<FlowEdge> >::iterator NodeIterator;
typedef vector<list<FlowEdge> >::const_iterator ConstNodeIterator;
typedef list<FlowEdge>::iterator EdgeIterator;
typedef list<FlowEdge>::const_iterator ConstEdgeIterator;

// From class code archive.
struct FlowGraph {
	FlowGraph(int N) : graph(N, list<FlowEdge>()) {}
	void reserve(int N) { graph.reserve(N); }
	void addEdge(int src, int dst, int cap)
	{
		graph[src].push_back(FlowEdge(src, dst, cap));
		FlowEdge *e1 = &graph[src].back();
		graph[dst].push_back(FlowEdge(dst, src, 0));
		FlowEdge *e2 = &graph[dst].back();
		e1->redge = e2;	// Carefully assign pointers to reverse edges.
		e2->redge = e1;	// This is really bad and likely buggy. Should be fixed.
	}
	AdjFlowGraph graph;
};

// From class code archive.
int EdmondsKarp(FlowGraph& FG, int source, int sink)
{
	for(;;) {
		queue<int> visitQueue;
		vector<bool> visited(FG.graph.size(), false);

		vector<FlowEdge *> pathTo(FG.graph.size(), NULL);
		
		visitQueue.push(source);
		visited[source] = true;
		
		int cur;
		for(;;) {
			if (visitQueue.empty()) {
				int flow = 0;
				for (ConstEdgeIterator it = FG.graph[source].begin();
						it != FG.graph[source].end(); ++it) {
					flow += it->flow;
				}
				return flow;
			}
			cur = visitQueue.front();
			visitQueue.pop();
			if (cur == sink) break;
			for (EdgeIterator it = FG.graph[cur].begin();
					it != FG.graph[cur].end(); ++it) {
				if (visited[it->dst] || it->flow >= it->cap) continue;
				visitQueue.push(it->dst);
				visited[it->dst] = true;
				pathTo[it->dst] = &*it;
			}
		}
		int capacity = numeric_limits<int>::max();
		for (int loc = cur; loc != source; loc = pathTo[loc]->src) {
			capacity = min(pathTo[loc]->cap - pathTo[loc]->flow, capacity);
		}
		for (int loc = cur; loc != source; loc = pathTo[loc]->src) {
			pathTo[loc]->flow += capacity;
			pathTo[loc]->redge->flow -= capacity;
		}
	}
}

/* WIKIPEDIA DFS PSEUDO CODE
1  procedure DFS-iterative(G,v):
2      let S be a stack
3      S.push(v)
4      while S is not empty
5            v = S.pop()
6            if v is not labeled as discovered:
7                label v as discovered
8                for all edges from v to w in G.adjacentEdges(v) do
9                    S.push(w)
*/

vector<bool> dfs(FlowGraph fg, int source) {
	queue<int> S;
	vector<bool> visited(fg.graph.size(), false);
	S.push(source);

	while (!S.empty()) {
		source = S.front();
		S.pop();
		if (visited[source] != true) {
			visited[source] = true;
			for (ConstEdgeIterator it = fg.graph[source].begin(); it != fg.graph[source].end(); ++it) {
				if (it->flow < it->cap)
					S.push(it->dst);
			}
		}
	}
	return visited;
}

int main() {	
	int R, C, N;
	while (1) {
		cin >> R; cin >> C; cin >> N;

		if (R+C+N == 0) { 
			break;
		}
		FlowGraph FG(R+C+2);

		int r, c;
		vector<point> enemies;
		for (int i=0;i<N;++i) {
			cin >> r;
			cin >> c;
			enemies.push_back(point(r,c));
		}

		/* FLOW GRAPH STRUCTURE */
		//0 = source
		//1 to R = rows
		//R+1 to R+C = cols
		//Very last node = sink
		//Total Size = R + C + (1 source) + (1 sink) = R+C+2


		//Source to rows -> 1
		for (int i=0; i < R; ++i) {
			FG.addEdge(0, i+1, 1);
			//printf("Adding edge from S to row %d\n", i+1);
		}

		//Rows to Cols -> INF
		for (int i=0; i < enemies.size(); ++i) {
			FG.addEdge(enemies[i].x, enemies[i].y + R, INT_MAX);
			//printf("Adding edge from row %d to col %d\n", enemies[i].x, enemies[i].y);
		}

		//Cols -> Sink -> 1
		for (int i=0; i < C; ++i) {
			FG.addEdge(i+1 + R, R+C+1, 1);
			//printf("Adding edge from col %d to T\n", i+1);
		}

		cout << EdmondsKarp(FG, 0, R+C+1) << "";

		// Which nodes could we visit?
		vector<bool> ans = dfs(FG,0);

		// Reverse the row "visited" values.
		for (int i=1; i < R+1; ++i) {
			ans[i] = !ans[i];
		}

		for (int i=1; i < ans.size()-1; ++i) {
			if (ans[i] and i <= R) {
				cout << " r" << i;
			} else if (ans[i]) {
				cout << " c" << i-R;

			}

		}
		cout << "\n";

		ans.clear();
		enemies.clear();
	}
	return 0;
}