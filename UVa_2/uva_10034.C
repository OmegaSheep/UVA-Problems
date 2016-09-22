/* UVa problem: <10034>
 *
 * Topic: (Graphs)
 *
 * Level: 2 points
 * 
 * Brief problem description: 
 *
 * 	Determine the minimum amount of ink for drawing lines that connect all freckles on the dads back. (gross)
 *	 
 * Solution Summary:
 *
 *	This is a minimum spanning tree problem. You make a graph with an edge between every freckle.
 *	The weight of each edge is simply the euclidean distance of the freckles in question. Once you have this graph,
 *	you construct an MST using Kruskal's. Finally you output the length of all the edges in the MST to get the amount
 *	of ink required.
 *	
 * Used Resources:
 *
 *	 - Code Archive Kruskal's, Graph and DisjointSet code. I had to modify it to support doubles, but otherwise
 *	   it's just copy and pasta from the code archive. Very useful stuff.
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */


#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <map>
#include <climits>
#include <vector>
#include <sstream>
#include <algorithm>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <utility>
#define MAXN   1000
#define MAXM   1000000
#define EPS    1e-8

using namespace std;

class DisjointSets {
	public:
		DisjointSets(double N) : parent(vector<double>(N)), rank(vector<double>(N)) {}
		void MakeSet(double i) { parent[i] = i; rank[i] = 0; }
		void Union(double i, double j)
		{
			double iRoot = Find(i);
			double jRoot = Find(j);
			if (iRoot == jRoot) return;
			if (rank[iRoot] < rank[jRoot]) parent[iRoot] = jRoot;
			else if (rank[iRoot] > rank[jRoot]) parent[jRoot] = iRoot;
			else {
				parent[jRoot] = iRoot;
				rank[iRoot] += 1;
			}
		}
		double Find(double i)
		{
			if (parent[i] != i) parent[i] = Find(parent[i]);
			return parent[i];
		}
	private:
		vector<double> parent;
		vector<double> rank;
};

// Some basic data structures for graph storage.
struct Edge {
	Edge(double a, double b) : a(a), b(b) {}
	Edge() {}
	double a, b;
};

typedef pair<Edge, double> WeightedEdge;
typedef set<double>::iterator NodeIterator;
typedef set<double>::const_iterator ConstNodeIterator;
typedef vector<WeightedEdge>::iterator EdgeIterator;
typedef vector<WeightedEdge>::const_iterator ConstEdgeIterator;

// Graph implemented as edge list and node set.
struct Graph {
	vector<WeightedEdge> edges;	// Weighted directed edges in the graph.
	set<double> nodes;	// Keep a set of nodes around so we know how many nodes are in the graph.
	void AddEdge(double a, double b, double w)
	{
		nodes.insert(a); nodes.insert(b);
		edges.push_back(make_pair(Edge(a,b), w));
	}
	void AddBiEdge(double a, double b, double w) { AddEdge(a,b,w); AddEdge(b,a,w); }
	int NumEdges() const { return edges.size(); }
	int NumNodes() const { return nodes.size(); }
};

// Comparison function for sorting edges by edge weight.
bool EdgeWeightComp(const WeightedEdge& L, const WeightedEdge& R)
{
	return L.second < R.second;
}

// Kruskal's MST algorithm using Disjoint Sets data structure.
vector<WeightedEdge> KruskalMST(const Graph& G)
{
	DisjointSets DS(G.nodes.size());
	vector<WeightedEdge> MST;
	MST.reserve(G.NumNodes() - 1);
	for (ConstNodeIterator it = G.nodes.begin(); it != G.nodes.end(); ++it)
		DS.MakeSet(*it);
	vector<WeightedEdge> edges = G.edges;
	sort(edges.begin(), edges.end(), EdgeWeightComp);
	for (int i = 0; i < edges.size(); ++i) {
		if (DS.Find(edges[i].first.a) != DS.Find(edges[i].first.b)) {
			MST.push_back(edges[i]);
			DS.Union(edges[i].first.a, edges[i].first.b);
		}
	}
	return MST;
}

double dist(double x1, double y1, double x2, double y2) {
	return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

int main() {
	vector<pair<double,double>> pairs;
	int T;
	cin >> T;

	for (int i =0; i < T; ++i) {
		if (i != 0) cout << "\n";

		Graph G;
		int freckles;
		cin >> freckles;

		double x,y;
		for (int j=0; j < freckles; ++j) {
			cin >> x;
			cin >> y;
			pairs.push_back(make_pair(x,y));
		}

		for (int z=0;z<pairs.size();++z) {
			for (int zz=0;zz<pairs.size();++zz) {
				G.AddBiEdge(z,zz,dist( pairs[z].first, pairs[z].second, pairs[zz].first, pairs[zz].second ));
			}
		}

		double total = 0;
		vector<WeightedEdge> thing = KruskalMST(G);

		for (int h=0;h<thing.size();++h) {
			total+= thing[h].second;
		}
		printf("%.2f\n",total);
		pairs.clear();
		thing.clear();

	}
	return 0;
}
