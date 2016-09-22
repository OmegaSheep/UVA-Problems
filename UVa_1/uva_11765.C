/* UVa problem: <10034>
 *
 * Topic: (Graphs)
 *
 * Level: 1 points
 * 
 * Brief problem description: 
 *
 *  Determine the minimum cost of placing components given a set of restrictions and costs regarding placement.
 *   
 * Solution Summary:
 *
 *  This boils down to a network flow problem. You can use a flow graph to represent the arrangement of components.
 *  You connect top-only edges to the source by cost, and sink by infinity.
 *  You connect bot-only edges to the source by infinity and sink by cost.
 *  Edges that can go to both simply connect them to source by top-cost and sink by bot-cost.
 *
 *  Finally connect nodes with an interconnection cost with a two-way edge of that cost.
 *
 *  Once this is completed, run a Max Flow algorithm (in this case Edmond Karp) on the graph and it will produce the minimum cost
 *  of placing the components (which is the Maximum Flow of the graph.) 
 *  
 * Used Resources:
 *
 *   - Zach's Max Flow algorithm (was e-mailed to the class since the code archive is too slow!)
 *   - Noah - Verbally discussed problem (mentioned network flow might hold the solution.)
 *
 * I hereby certify that I have produced the following solution myself 
 * using the resources listed above in accordance with the CMPUT 403 
 * collaboration policy.
 *
 * --- (Aedan)
 */

#include <cstdio>
#include <vector>
#include <list>
#include <climits>
#include <iostream>
#include <algorithm>
#include <queue>

#define INF 100000000000ll
#define MAXN 500

using namespace std;

typedef long long LL;

struct Edge {
  int u, v, i;
  LL c;
  bool r;
  Edge(int uu = 0, int vv = 0, LL cc = 0, int ii = 0, bool rr = false) :
    u(uu), v(vv), c(cc), i(ii), r(rr) {}
};

vector<Edge> g[MAXN];
int pre[MAXN];

void add_edge(int u, int v, LL c) {
  g[u].push_back(Edge(u, v, c, g[v].size(), false));
  g[v].push_back(Edge(v, u, 0, g[u].size()-1, true));
}

LL augment(int s, int t, int n) {
  queue<int> q;
  for (int i = 0; i < n; ++i) pre[i] = -1;
  pre[s] = -2;
  q.push(s);

  while (!q.empty() && pre[t] == -1) {
    int curr = q.front();
    q.pop();
    for (int i = 0; i < g[curr].size(); ++i) {
      Edge succ = g[curr][i];
      if (pre[succ.v] == -1 && succ.c > 0) {
        pre[succ.v] = succ.i;
        q.push(succ.v);
      }
    }
  }

  if (pre[t] == -1) return 0;

  LL val = INF;
  int v = t;
  while (v != s) {
    int u = g[v][pre[v]].v;
    val = min(val, g[u][g[v][pre[v]].i].c);
    v = u;
  }

  v = t;
  while (v != s) {
    int u = g[v][pre[v]].v;
    g[v][pre[v]].c += val;
    g[u][g[v][pre[v]].i].c -= val;
    v = u;
  }

  return val;
}

LL max_flow(int s, int t, int n) {
  LL flow = 0, aug;

  while ((aug = augment(s, t, n))) flow += aug;

  return flow;
}


int main()
{
  vector<int> topCost;
  vector<int> botCost;
  int T;
  scanf("%d\n",&T);

  int N, M; //Vert / Edge
  int top, bot, type;
  for (int t = 0; t < T; ++t) {
    scanf("%d %d\n",&N, &M);

    for (int i = 0; i < N; ++i) {
      scanf("%d",&top);
      topCost.push_back(top);
    }

    for (int i = 0; i < N; ++i) {
      scanf("%d",&bot);
      botCost.push_back(bot);
    }

    //Keep in mind source is 0, sink is N+1, total size is N + 2 nodes.
    int cost;
    for (int i = 0; i < N; ++i) {
      scanf("%d",&type);

      if (type == 0) {
        cost = topCost[i];
        add_edge( 0, i+1, cost );

        cost = botCost[i];
        add_edge( i+1, N+1, cost );

      } else if (type == 1) {
        cost = topCost[i];
        add_edge( 0, i+1, cost );
        add_edge( i+1, N+1, INT_MAX );

      } else {
        cost = botCost[i];
        add_edge( i+1, N+1, cost );
        add_edge( 0, i+1, INT_MAX );

      }
    }
    
    int p, q, r;

    for (int i = 0; i < M; ++i) {
      scanf("%d %d %d\n",&p, &q, &r);
      add_edge( p, q, r );
      add_edge( q, p, r );
    }
    
    int f = max_flow(0, N+1, N+2);
    printf("%d\n",f);

    // Clear as required by Zach's code.
    for (int i = 0; i < N+2; ++i) {
      g[i].clear();
    }
    topCost.clear();
    botCost.clear();
  }
  return 0;
}