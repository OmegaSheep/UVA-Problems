/* UVa problem: <10278>
 *
 * Topic: (Graphs)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 *	Determine the best location to build a fire station given existing intersections, weights and fire stations.
 *
 * Solution Summary:
 *
 *	This problem is shitty but what I did was perform Dijkstra's from every existing fire station
 *	to determine min distance from every node to a fire station. Then I attempted to build a fire station
 *	at every node one by one and re-computed the distances. I started from the highest node, and ended at the lowest.
 *	If the "worst travel time" was ever as good or better than the existing worst travel time, then the node becomes
 *	the best choice for building.
 *
 *	Trick cases: Account for no existing fire stations.
 *	Sometimes the best index for building a fire station ALREADY HAD A F***ING FIRE STATION ON IT. 
 *	WHY THE F*** DID THAT MATTER. (SERIOUSLY. This made the difference between pass and fail for me.)
 *
 *
 * Used Resources:
 *
 *   - Code Archive Dijkstra's code and it's corresponding graph structures.
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
#define UNVISITED -1
#define VISITED 1
#define INF 1000000000

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

void printV(vi thing) {
	for (int i = 0; i < thing.size(); ++i) {
		cout << i+1 << ": " << thing[i] << "\n";
	}
	cout << "-----------\n";
}


struct Edge {
  int u, v;
  int w;
  Edge (int uu, int vv, int ww) : u(uu), v(vv), w(ww) {}

  bool operator<(const Edge& rhs) const { return w > rhs.w; }
};

typedef vector<Edge> VE;

vector<VE> graph;
VE pre;

void dijkstra(int s) {
  priority_queue< Edge > pq;

  pre.assign(graph.size(), Edge(-1, -1, -1));

  pq.push(Edge(-2, s, 0));

  while (!pq.empty()) {
    Edge curr = pq.top();
    pq.pop();

    if (pre[curr.v].v != -1) continue;

    pre[curr.v] = curr;

    for (auto e : graph[curr.v])
      pq.push(Edge(e.u, e.v, e.w + curr.w));
  }
}

int get_path(int v, VE& path) {
  if (pre[v].v == -1) return -1; // no path

  path.clear();
  
  int len = pre[v].w;
  while (pre[v].u != -2) {
    path.push_back(Edge(pre[v].u, pre[v].v, pre[v].w - pre[pre[v].u].w));
    v = pre[v].u;
  }

  reverse(path.begin(), path.end());

  return len;
}

int main() {
	int cases;
	int F, I;		// fire stations, intersections
	int u, v, w;	// node 1, node 2, edgelength
	cin >> cases;

	int CASE = 0;
	//cout << "Cases: " << cases << "\n";

	// Until out of cases.
	while (CASE < cases) {
		if (CASE > 0) cout << "\n";
		cin >> F;
		cin >> I;
		//cout << "F/I: " << F << " " << I << "\n";\

		//Get all the fire station locations.
		vector<int> fireLocations;
		int location;

		for (int i = 0; i < F; ++i) {
			cin >> location;
			//printf("Location %d: %d\n",i+1,location);
			fireLocations.push_back(location);
		}

		//Necessary Line
		graph.assign(I, VE());

		//Get all the edges
		string line;
		getline(cin, line);
		getline(cin, line);
		while (!line.empty()) {
			istringstream iss(line);
			iss >> u;
			iss >> v;
			iss >> w;
			//printf("Edge %d/%d of weight %d\n",u,v,w);
			graph[u-1].push_back(Edge(u-1,v-1,w));
			graph[v-1].push_back(Edge(v-1,u-1,w));
			getline(cin, line);
		}

		//If fire locations is NOT empty
		//compile a Dijkstra's of each source fire location
		vi result(I, INF);
		if (!fireLocations.empty()) {
			for (int j = 0; j < fireLocations.size(); ++j) {
				int s = fireLocations[j]-1;
				dijkstra(s);

				//Get the current dijkstra results.
				for (int i = 0; i < I; ++i) {
					VE path;
					int len = get_path(i, path);
					if (len < result[i]) {
						result[i] = len;
					}
				}
			}
		}
		//printV(result);

		int max = INF;
		int maxIndex = INF;

		for (int i = I-1; i>=0; --i) {
			// If not in fire locations.
			vi comp(result);
			//if (find(fireLocations.begin(), fireLocations.end(), i+1) == fireLocations.end()) {
				int s = i;
				dijkstra(s);

				//Get the new fire location results.
				for (int j = 0; j < I; ++j) {
					VE path;
					int len = get_path(j, path);
					if (len < comp[j]) {
						comp[j] = len;
					}
				}

				auto it = max_element(begin(comp), end(comp));

				//printf("New Station/Max Value: %d / %d \n",i+1,*it);
				if (*it <= max) {
					maxIndex = i+1;
					max = *it;
				}

			//}
		}
		cout << maxIndex << "\n";
		result.clear();
		graph.clear();
		CASE++;
	}
	return 0;
}