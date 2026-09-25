# 15 — Graph

## Concept
- What: Nodes + edges (directed/undirected, weighted). Why: networks, grids, schedules.
- When: components, cycles, topo, shortest path, MST. Terms: adj list, indegree, component, distance INF.

## Syntax
```cpp
vector<vector<int>> adj(n); adj[u].push_back(v);
vector<vector<pair<int,int>>> w(n);
queue<int> q; priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
```

## Patterns
- BFS for unweighted shortest; DFS for components/cycles/paths.
- Topo Kahn/BFS or DFS-postorder (DAG only). DSU for connectivity/MST.
- Dijkstra non-negative; Bellman-Ford negative+detect; Floyd all-pairs; 0-1 BFS deque.

## Algorithms
- Build list; BFS/DFS; components; rotten oranges multi-BFS; cycle undirected (parent) / directed (recStack);
- bipartite 2-color; topo Kahn+DFS; alien dict graph; Dijkstra; Bellman-Ford V-1 + 1 detect;
- Floyd; MST Prim/Kruskal+DSU; bridges Tarjan low; SCC Kosaraju; shortest DAG topo+relax; word ladder; accounts merge DSU.

## Examples
Dijkstra 1-2(2),1-3(4),2-3(1): dist 0,2,3. Topo [5->2,5->0,4->0,4->1,2->3,3->1] valid.

## Complexity
BFS/DFS O(V+E); Dijkstra O(E log V); Bellman O(VE); Floyd O(V^3); Kruskal O(E log E).

## Common Mistakes
- 0/1-index; disconnected loop; visited timing; negative with Dijkstra; recursion depth; long long dist.

## Templates
```cpp
struct DSU{vector<int>p,r;DSU(int n):p(n),r(n,0){iota(p.begin(),p.end(),0);}int f(int x){return p[x]==x?x:p[x]=f(p[x]);}bool u(int a,int b){a=f(a);b=f(b);if(a==b)return false;if(r[a]<r[b])swap(a,b);p[b]=a;if(r[a]==r[b])r[a]++;return true;}};
vector<int> dijk(int n,vector<vector<pair<int,int>>>&g,int s){const int INF=1e9;vector<int>d(n,INF);d[s]=0;priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;pq.push({0,s});while(!pq.empty()){auto[c,u]=pq.top();pq.pop();if(c!=d[u])continue;for(auto[v,w]:g[u])if(d[v]>c+w){d[v]=c+w;pq.push({d[v],v});}}return d;}
```

## Revision Summary
BFS unweighted; DFS cycles; topo DAG; Dijkstra >=0; Bellman negative; DSU MST.
