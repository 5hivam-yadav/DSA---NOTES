# 15 — Graph — Complete Pattern-Based Notes

---

## 1. Topic Overview

A **graph** is a set of vertices connected by edges (directed/undirected, weighted/unweighted) — the general model for networks, dependencies, grids, and states.

**What it is**
`G = (V, E)`; stored as adjacency lists (`V` lists of neighbors) or adjacency matrix (`V×V`). Everything else in this chapter — BFS, DFS, topological sort, shortest paths, MST, DSU — is an *algorithm over this representation*.

**Why it is important**
- Real systems: social networks, maps, routers, task schedulers, compilers, file systems.
- The grid problems you've seen (islands, rotten oranges, matrices) are graphs in disguise.
- Highest-yield interview topic: one decision table separates most candidates.

**Where it is used**
- Connectivity & components (provinces, islands, accounts merge).
- Cycle detection & ordering (prerequisites, alien dictionary).
- Shortest paths (routes, minimum time, discount paths).
- Minimum spanning trees (network design, clustering).
- Advanced: bridges, articulation points, strongly connected components.

**How it connects to other topics**
- §09 Queue/Stack: BFS/DFS containers. §11 Heap: Dijkstra. §12 Greedy: Kruskal/Prim.
- §07 Recursion: DFS is recursion on structure. §04 Binary Search: threshold search on graphs.
- §16 DP: DAG dynamic programming. §08 Bit: masks for tiny graphs.

**Interview memory hook:** *unweighted shortest → BFS · dependencies → topo sort · non-negative weights → Dijkstra · negative → Bellman-Ford · all-pairs → Floyd · min cost connect → MST · dynamic connectivity → DSU.*

---

## 2. Fundamentals

### 2.1 Representations

```text
Adjacency list (default):
  vector<vector<int>> adj(n);          unweighted
  vector<vector<pair<int,int>>> adj;    weighted: {to, w}

  0 -- 1 -- 2        adj[0]={1}, adj[1]={0,2}, adj[2]={1}

Adjacency matrix:  bool a[n][n]   -> O(1) edge check, O(n^2) memory
                   use when n <= ~1000 and dense

Edge list:  vector<tuple<w,u,v>>      -> Kruskal / Bellman-Ford input
```

**Which to choose**: adjacency list for sparse (`E ≈ V`) — memory `O(V + E)`; matrix for dense (`E ≈ V²`) or repeated edge queries.

### 2.2 Directed vs undirected, weighted

- **Undirected**: store both `(u,v)` and `(v,u)`; degree = list length.
- **Directed**: one direction only; **indegree/outdegree** matter for topological sort.
- **Weighted**: pair/struct per edge; weights ≥ 0 → Dijkstra; negative → Bellman-Ford/Floyd.

### 2.3 Grids are graphs

```text
matrix cell (r, c)  ->  node id r * cols + c
neighbors: (r±1, c), (r, c±1)   [or 8-directional]

visited[r][c]  ==  graph visited[]
```

All island/flood-fill/shortest-path-in-grid problems are graph algorithms with implicit adjacency.

### 2.4 Terminology

| Term | Meaning |
|---|---|
| **Path / cycle** | Vertex sequence where consecutive nodes are adjacent; path returning to start. |
| **Component** | Maximal connected subgraph (undirected). |
| **Degree** | Number of incident edges (indegree/outdegree for directed). |
| **DAG** | Directed acyclic graph — enables topological order. |
| **Bipartite** | 2-colorable ⇔ no odd cycle. |
| **Topological order** | Linear order respecting all directed edges (DAG only). |
| **Tree** | Connected graph with `V−1` edges, no cycles. |
| **Cut / bridge** | Edge whose removal disconnects the graph. |
| **SCC** | Maximally strongly connected component (directed). |
| **INF** | Sentinel distance for unreachable (`1e9`/`1e18` by weight size). |

### 2.5 Complexity budget

```text
V <= 10        ->  O(2^V) state enumeration
V <= 100       ->  O(V^3) Floyd
V <= 10^3      ->  O(V^2) BFS matrix / Dijkstra naive
V <= 10^5, E <= 10^5..10^6  ->  O(V+E) BFS/DFS, Dijkstra O(E log V)
```

---

## 3. Core Concepts

### 3.1 BFS (Breadth-First Search)

**Definition**  \nExplore layer by layer using a queue; first time you reach a node = shortest path in **unweighted** graphs.

**Why it works**  \nQueue processes nodes in non-decreasing distance from source — when `v` is first enqueued via `u`, no shorter route can exist (all earlier queue entries are closer or equal).

**How it works**
1. Mark source visited, push; `dist[source] = 0`.
2. Pop `u`; for each neighbor not visited: `dist[v] = dist[u]+1`, push.
3. Repeat until queue empty.

**Common mistakes**  \nMark visited *on enqueue* (not dequeue) or you enqueue the same node twice; forgetting all components (loop over all vertices).

**Complexity**  \n`O(V + E)` time, `O(V)` space.

---

### 3.2 DFS (Depth-First Search)

**Definition**  \nGo as deep as possible via recursion/stack; backtrack at dead ends.

**Why it matters**  \nNatural for components, cycle detection, topological order, bridges/articulation (with `tin`/`low`), and maze-style exploration.

**How it works**

```cpp
void dfs(int u, vector<vector<int>>& adj, vector<bool>& vis) {
    vis[u] = true;
    for (int v : adj[u]) if (!vis[v]) dfs(v, adj, vis);
}
```

**Visited-timing variants**
- Undirected cycle: track **parent** (don't go back the way you came).
- Directed cycle: track **recursion stack** (back edge to a node *currently on stack*).

**Complexity**  \n`O(V + E)` time, `O(V)` space (recursion depth up to `V` — watch stack overflow; consider iterative DFS).

---

### 3.3 Connected components

**Definition**  \nPartition vertices into maximal connected sets.

**How it works**  \nLoop all vertices; if unvisited → start BFS/DFS marking everything → one component found. Count starts = component count.

**Complexity**  \n`O(V + E)` — each node/edge touched once total.

**Grid variant** (Number of Provinces / Islands): each unvisited `1`/land cell triggers a flood-fill; count triggers.

---

### 3.4 Cycle detection

| Graph | Method | Why |
|---|---|---|
| Undirected | DFS with parent param; revisit of a non-parent visited node → cycle | back edge to ancestor |
| Undirected (DSU) | adding edge whose endpoints already united → cycle | edge closes a loop |
| Directed | DFS with recursion-stack flag; edge to node *in stack* → cycle | back edge |
| Directed (Kahn) | processed count < V after Kahn → cycle | leftover nodes have indegree > 0 |

**Common mistakes**
- Undirected: forgetting the parent → false positive (the edge you came from).
- Directed: using plain `visited` instead of an `inStack` (recursion-stack) flag → cross-edges and forward-edges get misreported; only an edge to a node *currently on the recursion stack* (a back edge) proves a cycle.

---

### 3.5 Bipartite check (2-coloring)

**Definition**  \nGraph is bipartite iff no odd-length cycle ⇔ can color with 2 colors so no adjacent share a color.

**How it works**  \nBFS/DFS assigning `color[v] = 1 - color[u]`; any conflict (neighbor same color) → not bipartite. Must run over all components.

**Complexity**  \n`O(V + E)`.

---

### 3.6 Multi-source BFS

**Definition**  \nInitialize the queue with **all sources at once** (distance 0); BFS expands uniformly — answers "min distance from *any* source".

**When**: rotten oranges (all rotten start together), shortest distance to nearest 0/1 in matrix, walls & gates.

**Why it works**  \nEquivalent to a virtual super-source connected to all sources with 0-weight edges.

**Common mistake**  \nRunning BFS from each source separately → `O(V·E)` instead of `O(V + E)`.

---

### 3.7 Topological sort (Kahn & DFS)

**Definition**  \nLinear ordering of a **DAG** such that every edge `u → v` puts `u` before `v`. Valid only if the graph is acyclic.

**Kahn's algorithm (BFS on indegrees)**
1. Compute indegree of every node; push all `indegree == 0`.
2. Pop `u`, append to order; decrement neighbors' indegrees; push any that hit 0.
3. If output size < V → **cycle exists**.

**DFS post-order**  \nFinish a node only after all descendants → push to front (reverse post-order). Cycle if you revisit a node in the current stack.

**Why it matters**  \nCourse schedule, build systems, alien dictionary, task ordering, and DP on DAGs (§16) all reduce to it.

**Complexity**  \n`O(V + E)` for both.

**Common mistakes**  \nForgetting to loop over all zero-indegree nodes initially (disconnected graph); not detecting the cycle case.

---

### 3.8 Shortest paths — family overview

| Algorithm | Graph | Negative? | Complexity |
|---|---|---|---|
| **BFS** | unweighted (unit weights) | n/a | `O(V+E)` |
| **0-1 BFS** | weights ∈ {0,1} | no | `O(V+E)` (deque) |
| **Dijkstra (PQ)** | non-negative | no | `O(E log V)` |
| **Bellman-Ford** | any, detects negative cycles | yes | `O(V·E)` |
| **Floyd-Warshall** | all-pairs, any | yes | `O(V³)` |
| **DAG shortest** | DAG only | yes | `O(V+E)` (topo order) |

**Rule**: never run Dijkstra with negative edges (greedy assumption breaks).

---

### 3.9 Dijkstra

**Definition**  \nRepeatedly settle the unvisited node with the smallest tentative distance (min-heap), relaxing its edges.

**Why it works**  \nNon-negative weights → once popped with the smallest distance, that distance is final (a later path would need a negative edge to improve).

**How it works**

```cpp
vector<int> dijk(int n, vector<vector<pair<int,int>>>& g, int s) {
    const int INF = 1e9;
    vector<int> d(n, INF); d[s] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [c, u] = pq.top(); pq.pop();
        if (c != d[u]) continue;                    // stale entry — skip
        for (auto [v, w] : g[u])
            if (d[v] > c + w) { d[v] = c + w; pq.push({d[v], v}); }
    }
    return d;
}
```

**Complexity**  \n`O(E log V)` with binary heap (`E` pushes × `log V`).

**Common mistakes**  \nNo staleness check (works but slower/wrong if reprocessing); `INF + w` overflow (guard `d[u] == INF`); wrong index base.

---

### 3.10 Bellman-Ford

**Definition**  \nRelax **all edges** `V−1` times; a `V`-th round that still improves ⇒ negative cycle.

**Why `V−1`**: the longest possible simple path has `V−1` edges — after that, no further improvement is possible without a cycle.

**How it works**  \n`dist[source]=0; for i in 1..V-1: for each edge (u,v,w): if d[u]+w < d[v]: d[v]=d[u]+w;` then one more pass for detection.

**Complexity**  \n`O(V·E)`.

**When**: negative weights, "can reach with negative total cost", detect negative cycles.

---

### 3.11 Floyd-Warshall

**Definition**  \nAll-pairs shortest paths: for each intermediate `k`, try `d[i][j] = min(d[i][j], d[i][k] + d[k][j])`.

**Why it works**  \nDP over subsets of allowed intermediates (§16 connection): after round `k`, paths may use vertices `0..k`.

**Complexity**  \n`O(V³)` time, `O(V²)` space; run for `V` rounds — `k` outermost so it reads the previous round.

**When**: `V ≤ ~400`, all-pairs needed, negative edges OK (detect via negative diagonal).

---

### 3.12 Minimum Spanning Tree (Prim & Kruskal)

**Definition**  \nConnect all vertices with `V−1` edges, minimum total weight, no cycles.

**Kruskal (greedy + DSU)**
1. Sort edges by weight ascending.
2. Add an edge iff its endpoints are in **different** components (DSU `union` returns false if already united → skip, cycle).
3. Stop at `V−1` edges.

**Prim (grow a tree)**
1. Start from any node; min-heap of edges crossing the cut.
2. Repeatedly add the cheapest edge to an unseen vertex (lazy deletion for stale entries).

| | Kruskal | Prim |
|---|---|---|
| Complexity | `O(E log E)` | `O(E log V)` |
| Best for | sparse, edge list | dense, adjacency matrix `O(V²)` |
| Needs | DSU | heap + visited |

**Common mistakes**  \nForgetting to skip already-united edges (cycle); not handling disconnected graphs (MST impossible — count components).

---

### 3.13 DSU (Disjoint Set Union / Union-Find)

**Definition** Maintains a partition of elements into disjoint sets with near-`O(1)` `find` (path compression) and `union` (union by rank/size).

**Why it matters** Dynamic connectivity: "are these connected *so far*?" in amortized `α(n)` ≈ constant — Kruskal, accounts merge, provinces via edges, redundant connections.

**How it works**
- `find(x)`: follow parents to root, rewire `x` directly to root (path compression).
- `union(a, b)`: roots differ → attach smaller rank under larger.

**Complexity** Amortized `O(α(n))` per op ≈ `O(1)`.

**Common mistakes** Forgetting to `find` before comparing parents; rank not updated → chain (still OK with compression, but update anyway).

---

### 3.14 Bridges & articulation points (Tarjan)

**Definition** **Bridge**: edge whose removal disconnects. **Articulation point**: vertex whose removal disconnects.

**Core idea (`tin` / `low`)** DFS assigns entry times; `low[u]` = smallest `tin` reachable from `u`'s subtree via one back edge. If `low[v] > tin[u]` for tree edge `u→v`, no back edge bypasses it → bridge.

**Complexity** `O(V + E)`.

---

### 3.15 Strongly connected components (Kosaraju / Tarjan)

**Definition** Maximal sets of vertices mutually reachable (directed).

**Kosaraju (two passes)**
1. DFS on `G`, record **finish order**.
2. Transpose `Gᵀ`.
3. DFS on `Gᵀ` in decreasing finish order — each DFS = one SCC.

**Tarjan**: one DFS with `tin`/`low` and an on-stack container — SCCs pop when `low[u] == tin[u]`.

**Complexity** `O(V + E)` both. Applications: 2-SAT, condensation DAG, maze-of-SCCs problems.

---

### 3.16 DAG shortest path

**Definition** In a DAG, process vertices in **topological order**, relaxing outgoing edges once — correct even with negative weights (no cycles to exploit).

**Complexity** `O(V + E)` — faster than Dijkstra for DAGs.

---

### 3.17 Specialized patterns (0-1 BFS, grid BFS, word graph)

- **0-1 BFS**: weights 0/1 → deque; push front for weight 0, back for weight 1 → `O(V + E)`.
- **Grid BFS**: implicit adjacency; multi-source variants (§3.6); boundary checks per direction.
- **Word ladder**: words = nodes; edge = differs by one letter; BFS on implicit graph (precompute neighbors by wildcard buckets for `O(L·26·N)`).
- **Word ladder II** (all shortest paths): BFS layering + DFS backtracking on the DAG of shortest transitions.

---

## 4. PATTERN LIBRARY

### P1 — BFS (unweighted shortest path / layers / multi-source)

#### What is the pattern?
Queue-based layer-by-layer exploration; distance = layer number.

#### When should I recognize it?
- "Shortest path in an **unweighted** graph/grid", "minimum steps / moves", "level order of states", "rotten oranges / nearest 0 / multi-source spread", "word ladder".

#### Core intuition
All edges cost 1 → exploring in FIFO order guarantees the first reach is the shortest; states expand like ripples.

#### Generic algorithm
1. `queue`, `dist[] = -1/INF`, mark source visited, `dist = 0`.
2. Pop `u`; for each unvisited neighbor: `dist[v] = dist[u] + 1`, mark, push.
3. Multi-source: push *all* sources first with distance 0.

#### C++ template
```cpp
int bfsShortest(int n, vector<vector<int>>& adj, int src, int dst) {
    vector<int> dist(n, -1);
    queue<int> q; q.push(src); dist[src] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == dst) return dist[u];
        for (int v : adj[u]) if (dist[v] == -1) {
            dist[v] = dist[u] + 1; q.push(v);
        }
    }
    return -1;
}
```

#### Time / Space
`O(V + E)` / `O(V)`.

#### Edge cases
Source == target (0); disconnected (−1); multiple components (loop over all); self-loops.

#### Common mistakes
Mark visited on **enqueue**; forgetting distance array initialization; grid boundary checks.

#### Variations
Multi-source (all sources initially); 0-1 BFS (deque, weights 0/1); BFS on implicit grids/word graphs.

#### Practice mapping
- `03-BFS-Traversal.cpp`, `06-Rotten-Oranges.cpp`, `13-Word-Ladder-I.cpp`, `14-Word-Ladder-II.cpp`, `36-Shortest-Path-Binary-Maze.cpp`, `26-Shortest-Path-UG-Unit.cpp`

---

### P2 — DFS (components / cycles / flood fill / paths)

#### What is the pattern?
Recursive (or stack) depth-first traversal marking visited.

#### When should I recognize it?
- "Count provinces / islands", "flood fill", "find paths", "cycle detection", "surrounded regions", "number of enclaves", "islands variants".

#### Core intuition
DFS claims an entire connected region in one descent; what remains unvisited belongs to other components.

#### Generic algorithm
```text
for each node:  if !visited: dfs(node)     // components
dfs(u):  mark; for v in adj[u]: if !visited and valid: dfs(v)
```

For cycles add `parent` (undirected) or `inStack` (directed).

#### C++ template
```cpp
void dfs(int u, vector<vector<int>>& g, vector<bool>& vis) {
    vis[u] = true;
    for (int v : g[u]) if (!vis[v]) dfs(v, g, vis);
}
// grid version: 4 directions + bounds + validity check on cell
```

#### Time / Space
`O(V + E)` / `O(V)` recursion (grid `O(mn)`).

#### Edge cases
Empty graph; isolated nodes; deep recursion (stack overflow → iterative); grid borders.

#### Common mistakes
Not marking before recursion (infinite loops on cycles); wrong direction array; visiting invalid cells.

#### Variations
Iterative DFS (explicit stack); DFS with early exit (target found); DFS coloring for bipartite.

#### Practice mapping
- `04-DFS-Traversal.cpp`, `02-Connected-Components.cpp`, `05-Number-of-Provinces.cpp`, `07-Flood-Fill.cpp`, `15-Number-of-Islands.cpp`, `11-Surrounded-Regions.cpp`, `12-Number-of-Enclaves.cpp`, `54-Number-of-Distinct-Islands.cpp`, `08-Cycle-Undirected-DFS.cpp`, `09-Cycle-Undirected-BFS.cpp`

---

### P3 — Topological Sort (Kahn / DFS-postorder)

#### What is the pattern?
Order DAG nodes so all dependencies precede dependents; indegree-BFS (Kahn) or reverse post-order (DFS).

#### When should I recognize it?
- "Course schedule / prerequisites possible?", "alien dictionary ordering", "build order / task scheduling with dependencies", "sort words by derived order", "sequence reconstruction".

#### Core intuition
A valid order exists iff you can repeatedly remove a node with **no unresolved prerequisites** (indegree 0). Stuck with nodes remaining → cycle → impossible.

#### Generic algorithm (Kahn)
1. Compute indegrees; push all 0-indegree nodes.
2. Pop → order; decrement neighbors → push new 0s.
3. `order.size() == V` ⇒ valid; else cycle.

#### C++ template
```cpp
vector<int> topoSort(int n, vector<vector<int>>& adj) {
    vector<int> in(n, 0), order;
    for (int u = 0; u < n; u++) for (int v : adj[u]) in[v]++;
    queue<int> q;
    for (int u = 0; u < n; u++) if (!in[u]) q.push(u);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) if (--in[v] == 0) q.push(v);
    }
    return order;   // size < n  =>  cycle
}
```

#### Time / Space
`O(V + E)` / `O(V)`.

#### Edge cases
Disconnected DAGs (multiple 0-indegree starts); single node; cycle detection (output size); multiple valid orders (any is fine).

#### Common mistakes
Only seeding *some* zero-indegree nodes; not detecting cycle (compare size to V); building edges in the wrong direction (prerequisite → course).

#### Variations
DFS-postorder reversed; lexicographically smallest order (use a min-heap / `set` in Kahn); DP over topo order for DAG paths (§16).

#### Practice mapping
- `19-Topo-Sort-DFS.cpp`, `20-Topo-Sort-BFS-Kahn.cpp`, `21-Course-Schedule-I.cpp`, `22-Course-Schedule-II.cpp`, `25-Alien-Dictionary.cpp`, `23-Eventual-Safe-States-BFS.cpp`, `24-Eventual-Safe-States-DFS.cpp`

---

### P4 — Dijkstra (non-negative weighted shortest path)

#### What is the pattern?
Min-heap of `(distance, node)`; pop smallest, relax neighbors; stale-entry skip.

#### When should I recognize it?
- "Shortest path with **non-negative** weights", "minimum time / cost with positive costs", "network delay time", "path with minimum effort (threshold via heap or binary search)", "cheapest flights with constraints (variant)".

#### Core intuition
The globally closest unsettled node can't be improved later (weights ≥ 0) — commit its distance, expand.

#### Generic algorithm
1. `dist[src] = 0`; heap push `(0, src)`.
2. Pop `(d, u)`; if `d > dist[u]` → stale, skip.
3. For each edge `u→v` with weight `w`: if `d + w < dist[v]` → update and push.
4. Repeat until heap empty.

#### C++ template
```cpp
vector<int> dijkstra(int n, vector<vector<pair<int,int>>>& g, int src) {
    const int INF = 1e9;
    vector<int> dist(n, INF); dist[src] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : g[u])
            if (dist[v] > d + w) { dist[v] = d + w; pq.push({dist[v], v}); }
    }
    return dist;
}
```

#### Time / Space
`O(E log V)` / `O(V + E)`.

#### Edge cases
Unreachable nodes (stay INF); `INF + w` overflow (skip when `d == INF`); source = target; ties (any order).

#### Common mistakes
Negative edges (illegal — use Bellman-Ford); forgetting the staleness check; wrong `INF` (too small → saturation, too large → overflow on add).

#### Variations
Dijkstra with `set` (`O(E log V)`, allows erase); K-stops variants (track stops in state); path reconstruction (parent array).

#### Practice mapping
- `28-Dijkstra-PQ.cpp`, `29-Dijkstra-Set.cpp`, `39-Network-Delay-Time.cpp`, `40-Swim-in-Rising-Water.cpp`, `37-Path-Min-Effort.cpp`, `38-Cheapest-Flights-K-Stops.cpp`

---

### P5 — Bellman-Ford / Floyd-Warshall (negative & all-pairs)

#### What is the pattern?
**Bellman-Ford**: relax all edges `V−1` times (single source, negatives, negative-cycle detection). **Floyd**: `V×V×V` DP over intermediates (all pairs).

#### When should I recognize it?
- "Shortest path with **negative** weights", "detect negative cycle", "can debts be settled (difference constraints)", "all-pairs shortest / cheapest flights with at most k stops (rephrased)", "matrix with negative edges".

#### Core intuition
Bellman-Ford: after `k` rounds every path of ≤ `k` edges is optimal; simple paths have ≤ `V−1` edges. Floyd: `d[i][j]` using intermediates `0..k` = DP over subsets of vertices.

#### Generic algorithm (Bellman-Ford)
```text
dist[src] = 0
repeat V-1 times: for each edge (u,v,w): relax
one more pass: any relaxation => negative cycle
```

#### C++ template (Bellman-Ford)
```cpp
// edges as {u, v, w}
vector<int> bellman(int n, vector<array<int,3>>& edges, int src) {
    const int INF = 1e9;
    vector<int> d(n, INF); d[src] = 0;
    for (int i = 0; i < n - 1; i++)
        for (auto [u, v, w] : edges)
            if (d[u] != INF && d[v] > d[u] + w) d[v] = d[u] + w;
    // detect: if any edge still relaxes -> negative cycle
    return d;
}
```

#### Time / Space
Bellman `O(V·E)` / `O(V)`; Floyd `O(V³)` / `O(V²)`.

#### Edge cases
Unreachable (`INF` guard before adding); negative self-loops; `V = 1`; Floyd init (`d[i][i] = 0`, edges overwrite mins).

#### Common mistakes
Running Bellman only `V-2` times; forgetting INF guards; Floyd with `k` not outermost; using Dijkstra with negatives.

#### Variations
Floyd for transitive closure (Warshall); "at most k edges" → relax exactly `k+1` rounds (a Bellman-Ford variant).

#### Practice mapping
- `30-Bellman-Ford.cpp`, `31-Floyd-Warshall.cpp`, `34-Number-of-Ways-Arrival.cpp`, `33-Min-Multiplications.cpp`

---

### P6 — DSU / MST (connectivity & minimum cost)

#### What is the pattern?
**DSU**: incremental connectivity queries/unions. **Kruskal**: sort edges, add if it connects two components. **Prim**: grow min-cost tree from a vertex with a heap.

#### When should I recognize it?
- "Connect all nodes at minimum cost", "minimum spanning tree", "accounts merge / provinces via given edges", "redundant connection", "is it possible to connect with budget", "number of connected components after adding edges".

#### Core intuition
DSU answers "already connected?" in ~`O(1)`; Kruskal adds the cheapest edge that *doesn't* close a cycle; Prim always crosses the cut with the cheapest edge (cut property ⇒ optimal).

#### Generic algorithm (Kruskal)
1. Sort edges by weight.
2. For each: `union(u,v)` — if it merged (returned true) → count++, add weight.
3. Stop at `V−1` edges; if fewer possible → disconnected.

#### C++ template
```cpp
struct DSU {
    vector<int> p, r;
    DSU(int n) : p(n), r(n, 0) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};
```

#### Time / Space
DSU ~`O(α(n))`/op; Kruskal `O(E log E)`; Prim `O(E log V)`; Prim dense `O(V²)`.

#### Edge cases
Self-loops (always cycle); duplicate edges; disconnected graph (MST undefined / component count); single node (`0` edges).

#### Common mistakes
Not calling `find` before comparing; forgetting union return value as cycle test; counting edges after `V−1` (stop early).

#### Variations
DSU with component sizes (accounts merge labels); DSU offline reverse (delete-edge → add-edge problems, advanced); Prim with lazy deletion.

#### Practice mapping
- `41-Disjoint-Set-Union.cpp`, `42-Kruskal-MST.cpp`, `43-Prims-MST.cpp`, `44-Number-of-Provinces-DSU.cpp`, `45-Connect-All-Points-Min-Cost.cpp`, `46-Accounts-Merge.cpp`, `47-Making-Large-Island.cpp`, `48-Most-Stones-Removed.cpp`

---

### P7 — Cycle Detection & Bipartite Coloring

#### What is the pattern?
DFS/BFS with an extra piece of state — `parent` (undirected cycle), `inStack` (directed cycle), or `color` (bipartite) — that turns "did I revisit a node?" into a meaningful signal.

#### When should I recognize it?
- "Does the graph contain a cycle?", "course schedule possible?", "can jobs be scheduled?", "is the graph bipartite / 2-colorable?", "detect redundant connection", "eventual safe states".

#### Core intuition
- Undirected: revisiting a visited node *that isn't the node you came from* means you looped around.
- Directed: reaching a node still being processed (on the recursion stack) means a back edge → cycle.
- Bipartite: color alternates along edges; an edge between same-colored nodes closes an **odd cycle**.

#### Generic algorithm
```text
undirected cycle:  dfs(u, parent): for v != parent: if visited(v) -> cycle; else dfs(v, u)
directed cycle:    dfs(u): inStack[u]=true; for v: if inStack[v] -> cycle;
                              if !visited(v) && dfs(v): cycle;  inStack[u]=false
bipartite:         bfs: color[v] = 1 - color[u]; same color -> false
Kahn cycle:        topo order size < V -> cycle
```

#### C++ template (bipartite)
```cpp
bool isBipartite(vector<vector<int>>& g) {
    int n = g.size();
    vector<int> col(n, -1);
    for (int s = 0; s < n; s++) if (col[s] == -1) {
        queue<int> q; q.push(s); col[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                if (col[v] == -1) { col[v] = 1 - col[u]; q.push(v); }
                else if (col[v] == col[u]) return false;
            }
        }
    }
    return true;
}
```

#### Time / Space
`O(V + E)` / `O(V)`.

#### Edge cases
Self-loops (always cycle / never bipartite); disconnected graphs (loop over all starts); single node/edge.

#### Common mistakes
Undirected without parent → false cycle from the edge you arrived on; directed with plain visited → wrong; bipartite checked on one component only.

#### Variations
DSU-based cycle check (edge unites same component → cycle); Kahn for directed cycle; 2-coloring as greedy assignment.

#### Practice mapping
- `08-Cycle-Undirected-BFS.cpp`, `09-Cycle-Undirected-DFS.cpp`, `10-Zero-One-Matrix.cpp`, `16-Bipartite-Check-BFS.cpp`, `17-Bipartite-Check-DFS.cpp`, `18-Cycle-Directed-DFS.cpp`, `21-Course-Schedule-I.cpp`, `53-Shortest-Cycle-Practice.cpp`

---

### P8 — Implicit Graphs (grid / words / states)

#### What is the pattern?
Nodes are *not given* — they're positions, strings, or states; neighbors are generated on the fly (direction tables, one-letter mutations).

#### When should I recognize it?
- "Islands / rotten oranges / floods" (grid cells), "word ladder" (string states), "sliding puzzle / minimum moves" (board states), "swim in rising water / path min effort" (grid with weights).

#### Core intuition
Anything with "states + legal moves" is a graph: cells connect to 4/8 neighbors; words connect by one substitution; puzzle moves connect boards. BFS/DFS/Dijkstra run unchanged once you can *enumerate neighbors*.

#### Generic algorithm
1. Define state → node (index or hash).
2. Define `neighbors(state)` generator (direction arrays / letter loops / move sets).
3. Run the right traversal (BFS unweighted, Dijkstra weighted, A*/binary search variants).

#### C++ template (grid directions)
```cpp
const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};
auto inside = [&](int r, int c) { return r >= 0 && r < R && c >= 0 && c < C; };
for (int k = 0; k < 4; k++) {
    int nr = r + dr[k], nc = c + dc[k];
    if (inside(nr, nc) && valid(nr, nc)) { /* visit */ }
}
```

#### Time / Space
`O(states + transitions)` — grid `O(mn)`, word ladder `O(N·L·26)` neighbor gen (or wildcard buckets), sliding puzzle states ≤ `9!`.

#### Edge cases
Visited states must be marked **when enqueued**; hash collisions if using `unordered_set` of boards; start == goal; unreachable goal (−1).

#### Common mistakes
Generating neighbors out of bounds; not deduplicating states (exponential blowup); forgetting to encode state completely (missing one cell → wrong).

#### Variations
Multi-source grid BFS (§3.6); grid Dijkstra (weights from cell values); binary search + BFS on threshold (§04 × BFS).

#### Practice mapping
- `15-Number-of-Islands.cpp`, `54-Number-of-Distinct-Islands.cpp`, `06-Rotten-Oranges.cpp`, `13-Word-Ladder-I.cpp`, `14-Word-Ladder-II.cpp`, `36-Shortest-Path-Binary-Maze.cpp`, `40-Swim-in-Rising-Water.cpp`, `47-Making-Large-Island.cpp`

---

## 5. PATTERN RECOGNITION

| If the problem says... | Think about... |
|---|---|
| Minimum steps in an **unweighted** graph/grid | BFS |
| Dependencies / prerequisites / order | Topological Sort |
| Non-negative weighted edges | Dijkstra |
| Negative edge weights / detect negative cycle | Bellman-Ford |
| All-pairs shortest paths (small V) | Floyd-Warshall |
| Connect all nodes at minimum cost | MST (Kruskal/Prim) |
| Dynamic connectivity / grouping / merge | DSU |
| Count components / islands / provinces | DFS/BFS loop (or DSU) |
| Cycle in undirected / directed | parent / inStack DFS (or Kahn) |
| 2-colorable / alternate | Bipartite BFS coloring |
| Multi-source spread (all rotten at once) | Multi-source BFS |
| Weights ∈ {0, 1} | 0-1 BFS (deque) |
| Grid with walls / shortest path in maze | Grid BFS/DFS |
| Word → word by one change | Word ladder BFS on implicit graph |
| "At most k edges/stops" | Bellman rounds / state-augmented BFS/Dijkstra |
| Bridges / articulation / cut edges | Tarjan tin/low |
| Mutually reachable groups (directed) | SCC (Kosaraju/Tarjan) |
| Minimum cost with discounts / XOR edge | Special Dijkstra state (dist, extra) |
| Count paths / ways in DAG | DP over topo order (§16) |

**Decision rules**
1. Unweighted → BFS. 2. Weighted ≥ 0 → Dijkstra. 3. Negative → Bellman/Floyd. 4. Ordering/feasibility with deps → topo. 5. Min cost connect → MST. 6. Connectivity merging → DSU. 7. Always ask: directed? weighted? negative? acyclic? — those four answers pick the algorithm.

---

## 6. BRUTE → BETTER → OPTIMAL THINKING

### Shortest path (unweighted)
- **Brute** — DFS all paths, take min: exponential.
- **Better** — Dijkstra with all edges weight 1: `O(E log V)`.
- **Optimal** — BFS: `O(V + E)` — the FIFO queue exploits unit weights directly.

### Single-source shortest path (weighted)
- **Brute** — enumerate all paths: exponential.
- **Better** — Bellman-Ford `O(V·E)` — correct but slow for large sparse graphs.
- **Optimal** — Dijkstra `O(E log V)` when weights ≥ 0 (greedy safe); Bellman-Ford *required* for negatives. The choice is dictated by the weight sign, not preference.

### Cycle detection in directed graph
- **Brute** — enumerate paths / sort and check: messy, slow.
- **Better** — DFS with inStack: `O(V + E)`.
- **Optimal** — Kahn's algorithm computes *and* detects in the same `O(V + E)` pass while also producing a topological order — prefer Kahn when an order is also needed.

### Minimum spanning tree
- **Brute** — enumerate all spanning trees: exponential.
- **Better** — Prim `O(E log V)` or Kruskal `O(E log E)` — both optimal (`Ω(E log E)` for comparison-based MST).
- **Optimal** — either; pick by representation: edge list → Kruskal, dense matrix → Prim `O(V²)`.

### Number of islands
- **Brute** — BFS from every cell without memo: `O((mn)²)`.
- **Better** — visited array + flood fill: `O(mn)`.
- **Optimal** — same `O(mn)`; DSU over land cells alternative `O(mn·α)` — useful when edges arrive incrementally.

### Word ladder
- **Brute** — BFS trying all substitutions naively per word: `O(N² · L)` pairwise comparisons.
- **Better** — precompute adjacency by comparing pairs once: `O(N² · L)`.
- **Optimal** — wildcard-bucket indexing (`c**t` groups) or generate `L·26` mutations with a hash set: `O(N · L · 26)` per BFS — linear in the state space.

### Key transferable idea
> Graph optimization = **pick the weakest sufficient guarantee**: unit weights → BFS; non-negative → Dijkstra; negatives → Bellman; all-pairs → Floyd; connectivity only → DSU (skip paths entirely!). Often the biggest win is *not storing paths at all*.

---

## 7. C++ / STL TOOLKIT

| Tool | Syntax | Use |
|---|---|---|
| Adjacency list | `vector<vector<int>> adj(n)` | unweighted |
| Weighted list | `vector<vector<pair<int,int>>> g(n)` | `{to, w}` |
| Queue | `queue<int> q` | BFS |
| Stack / recursion | `stack<int>` / calls | DFS |
| Min-heap | `priority_queue<pair<int,int>, vector<...>, greater<>> pq` | Dijkstra |
| Deque | `deque<int> dq` (push_front/back) | 0-1 BFS |
| Indegree array | `vector<int> in(n)` | Kahn |
| Color array | `vector<int> col(n, -1)` | bipartite |
| Direction tables | `dr[4]/dc[4]` or `dr[8]/dc[8]` | grids |
| `iota` | `iota(p.begin(), p.end(), 0)` | DSU init |

```cpp
// build undirected graph
for (auto& e : edges) { int u = e[0], v = e[1]; adj[u].push_back(v); adj[v].push_back(u); }

// weighted directed
g[u].push_back({v, w});

// grid neighbors
const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};

// INF guard pattern
if (d[u] != INF && d[v] > d[u] + w) d[v] = d[u] + w;
```

**Common mistakes**
- 0-index vs 1-index mismatch (subgraphs/inputs often 1-indexed → subtract 1).
- Iterating `adj[u]` while modifying `adj` (invalidates iterators) — build fully first.
- `priority_queue<pair>` default is **max**-heap — need `greater<>` for min.

---

## 8. COMPLEXITY GUIDE

| Algorithm | Time | Space |
|---|---:|---:|
| Build adjacency list | `O(V + E)` | `O(V + E)` |
| BFS / DFS | `O(V + E)` | `O(V)` |
| Multi-source BFS | `O(V + E)` | `O(V)` |
| Cycle detection (any) | `O(V + E)` | `O(V)` |
| Bipartite | `O(V + E)` | `O(V)` |
| Topological sort (Kahn/DFS) | `O(V + E)` | `O(V)` |
| Dijkstra (binary heap) | `O(E log V)` | `O(V + E)` |
| Dijkstra (dense `O(V²)`) | `O(V²)` | `O(V)` |
| 0-1 BFS | `O(V + E)` | `O(V)` |
| Bellman-Ford | `O(V·E)` | `O(V)` |
| Floyd-Warshall | `O(V³)` | `O(V²)` |
| DAG shortest path | `O(V + E)` | `O(V)` |
| Kruskal | `O(E log E)` | `O(V)` |
| Prim (heap) | `O(E log V)` | `O(V)` |
| DSU (m ops) | `O(m·α(n))` ≈ `O(m)` | `O(V)` |
| Bridges / SCC (Tarjan/Kosaraju) | `O(V + E)` | `O(V)` |
| Grid BFS (m×n) | `O(mn)` | `O(mn)` |

**How to estimate** — every node and edge is processed a constant number of times in traversal algorithms (that's `V + E`); heaps multiply by `log V`; Floyd is a triple loop; Bellman multiplies edges by `V`.

---

## 9. EDGE CASES

- **Empty graph / single node** — BFS/DFS trivial; topo = `[0]`; MST = 0 edges.
- **Disconnected graph** — loop BFS/DFS over ALL vertices; MST impossible if `components > 1`; distances stay `INF`.
- **Self-loops & parallel edges** — cycle (undirected), duplicates in Kruskal (skip via DSU), Dijkstra handles via relaxation.
- **Source == target** — distance 0; don't return early before marking.
- **`INF` arithmetic** — `INF + w` overflow/saturation → guard `d[u] != INF`.
- **Negative edges with Dijkstra** — wrong; detect weight sign first.
- **1-indexed input** — convert to 0-index consistently.
- **Recursion depth** — DFS recursion up to `V = 10^5` → stack overflow; use iterative DFS or BFS.
- **Multiple edges / duplicate edges in Kruskal** — harmless (second unites false) but count correctly.
- **All nodes unreachable except source** — answer `−1`/`INF` handling per spec.
- **Bipartite with odd self-loop** — immediately false.
- **Floyd init** — `d[i][i] = 0`, other pairs `INF`; do NOT overwrite with `min(d, INF+INF)` (overflow — skip `INF` additions).

---

## 10. COMMON MISTAKES

| # | Mistake | What goes wrong | Why | How to avoid |
|---|---|---|---|---|
| 1 | Mark visited on dequeue | node enqueued many times | duplicates flood queue | mark on **enqueue** |
| 2 | Forgetting disconnected components | misses whole subgraphs | single-source loop only | `for (i<n) if (!vis[i])` |
| 3 | Undirected cycle without parent | false positive | the edge you came from | pass parent / use DSU |
| 4 | Directed cycle with plain visited | wrong answer | cross-edges aren't cycles | use `inStack` |
| 5 | Dijkstra with negative edges | incorrect distances | greedy premise broken | Bellman-Ford / Floyd |
| 6 | No staleness skip in heap | slow, possible wrong processing | heap can't update | `if (d != dist[u]) continue;` |
| 7 | `INF + w` overflow | wrong relaxation | sentinel arithmetic | guard `d[u] != INF` |
| 8 | Floyd `k` not outermost | wrong DP order | must read previous round | loops: `k, i, j` |
| 9 | Kahn missing zero-indegree seeds | drops components | only seeded one node | loop all nodes initially |
| 10 | Topo edge direction backwards | wrong order | prerequisite → course | read statement carefully |
| 11 | 1-indexed input in 0-index code | out of bounds / wrong node | mixed indexing | normalize at read time |
| 12 | DFS recursion on V=10^5 | stack overflow | deep chains | iterative DFS / BFS |
| 13 | Grid neighbors out of bounds | crash / WA | missing bounds check | `inside(nr, nc)` always |
| 14 | Floyd `INF + INF` | integer overflow | sentinel + sentinel | skip if `d[i][k] == INF` |
| 15 | Bipartite on one component only | false positive | odd cycle elsewhere | loop all components |

**Conceptual mistakes**
- Using BFS for *weighted* shortest path (layer order ≠ cheapest).
- Storing full paths when only distance is needed (memory blowup).
- Confusing "strongly connected" (directed) with "connected" (undirected).

---

## 11. IMPORTANT FORMULAS / RULES

```text
Edges in tree:        V - 1
Connected graph:      E >= V - 1
Topo order exists:    DAG <=> Kahn output size == V
Dist relaxation:      if d[u] + w < d[v] then d[v] = d[u] + w
Bellman rounds:       V - 1 (longest simple path has V-1 edges)
Floyd:                d[i][j] = min(d[i][j], d[i][k] + d[k][j])  for k outer
0-1 BFS:              weight 0 -> push_front; weight 1 -> push_back
MST edges:            exactly V-1 (connected)
Bipartite:            no odd cycle  <=>  2-colorable
Grid id:              r * cols + c      neighbors (r±1,c),(r,c±1)
Word ladder neighbor:  L * 26 mutations  (or wildcard buckets)
Safe nodes:           nodes that cannot reach a cycle (reverse topo / 0-outdegree peeling)
Number of ways:       multiply/sum over topo predecessors (DAG DP, §16)
```

**Decision rules**
1. Four questions: directed? weighted? negative? acyclic? → algorithm identified.
2. Distance problems: unit → BFS · ≥0 → Dijkstra · negative → Bellman · all-pairs → Floyd.
3. Ordering → topo · connectivity merges → DSU · min cost spanning → Kruskal/Prim.

---

## 12. REUSABLE TEMPLATES

```cpp
// 1. BFS shortest distances
vector<int> bfs(int n, vector<vector<int>>& adj, int src) {
    vector<int> d(n, -1);
    queue<int> q; q.push(src); d[src] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) if (d[v] == -1) { d[v] = d[u] + 1; q.push(v); }
    }
    return d;
}

// 2. Topological sort (Kahn) + cycle detection
vector<int> topo(int n, vector<vector<int>>& adj) {
    vector<int> in(n, 0), order;
    for (int u = 0; u < n; u++) for (int v : adj[u]) in[v]++;
    queue<int> q;
    for (int u = 0; u < n; u++) if (!in[u]) q.push(u);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) if (--in[v] == 0) q.push(v);
    }
    return order;   // size < n => cycle
}

// 3. Dijkstra
vector<int> dijk(int n, vector<vector<pair<int,int>>>& g, int s) {
    const int INF = 1e9;
    vector<int> d(n, INF); d[s] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [c, u] = pq.top(); pq.pop();
        if (c != d[u]) continue;
        for (auto [v, w] : g[u]) if (d[v] > c + w) { d[v] = c + w; pq.push({d[v], v}); }
    }
    return d;
}

// 4. DSU
struct DSU {
    vector<int> p, r;
    DSU(int n) : p(n), r(n, 0) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};
```

## 13. ADVANCED CONCEPTS

### 13.1 Tarjan bridges & articulation points
One DFS maintaining `tin[u]` (entry time) and `low[u]` (smallest entry reachable via one back edge). Tree edge `u→v` is a bridge iff `low[v] > tin[u]`; articulation rules add root/child conditions. `O(V + E)` — the standard "critical connections" solution.

### 13.2 Strongly connected components
**Kosaraju** (two DFS + transpose) or **Tarjan** (one DFS with on-stack SCC popping). Condensing each SCC into a supernode yields a **DAG** — enabling topo order on components, 2-SAT solving, and cycle-inside-component reasoning. `O(V + E)`.

### 13.3 Eulerian path / Hierholzer
A path using every edge exactly once exists iff (undirected) 0 or 2 odd-degree vertices, (directed) in/out degrees match with ≤1 imbalance. Hierholzer's algorithm builds it in `O(E)` with an edge-used marker.

### 13.4 Binary lifting on trees (LCA preprocessing)
`up[v][k]` = 2^k-th ancestor; `O(n log n)` prep, `O(log n)` LCA/k-th ancestor/path queries — the advanced upgrade of the `O(n)` LCA recursion (§13.2 of binary tree chapter).

### 13.5 Dynamic connectivity (offline)
Union-find handles *additions* only; offline **reverse deletion** (process queries backward turning deletes into adds) solves dynamic connectivity offline in `O((V + E + Q)·α)`. Segment-tree-of-time DSU handles fully online (advanced).

### 13.6 Flow & matching (awareness level)
Max-flow min-cut (Dinic `O(V²E)`), bipartite matching via flow or Hungarian — know they exist for "assign workers to jobs" style problems; interviews rarely require implementation.

### 13.7 Hamiltonian / TSP via bitmask DP
`O(2^V · V²)` over `(mask, last)` states — for `V ≤ ~20`. Connects §08 bitmask, §07 enumeration, and §16 DP (see DP advanced).

---

## 14. CONNECTIONS BETWEEN PATTERNS

```text
Representation (adj list)
        |
        +--> BFS -------> shortest path (unweighted) ---> multi-source ---> grid BFS
        |                     |
        |                     +--> level-by-level states ---> word ladder
        |
        +--> DFS -------> components / cycles / flood fill / bipartite
        |                     |
        |                     +--> topological sort (DAG) ---------> DAG DP (§16)
        |
Weighted?
        |
   +----+-------------------+--------------------+
   v                        v                    v
 all >= 0              negative edges         all pairs (small V)
   |                        |                    |
 Dijkstra (heap §11)   Bellman-Ford          Floyd-Warshall (DP)
   |                        |
 0-1 BFS (deque)      detect neg cycle

Connectivity only  --> DSU  -->  Kruskal MST (greedy §12)   <-- Prim (heap)
Cut/low reasoning  -->  bridges / articulation / SCC
Threshold on edges -->  binary search + BFS/DSU (§04 x graph)
```

**Mental map** — ask: directed? weighted? negative? acyclic? → four answers select: BFS/DFS · Dijkstra · Bellman/Floyd · topo. Connectivity merging → DSU. Min-cost spanning → Kruskal/Prim.

---

## 15. PROBLEM → PATTERN MAPPING

*(Reference only — solutions and approaches live in the `.cpp` files.)*

### Representation & traversals
- `01-Graph-Representation.cpp`
- `02-Connected-Components.cpp`
- `03-BFS-Traversal.cpp`
- `04-DFS-Traversal.cpp`

### Grid / flood fill / islands (implicit graphs)
- `05-Number-of-Provinces.cpp`
- `06-Rotten-Oranges.cpp`
- `07-Flood-Fill.cpp`
- `10-Zero-One-Matrix.cpp`
- `11-Surrounded-Regions.cpp`
- `12-Number-of-Enclaves.cpp`
- `15-Number-of-Islands.cpp`
- `54-Number-of-Distinct-Islands.cpp`
- `47-Making-Large-Island.cpp`

### Cycle detection & bipartite
- `08-Cycle-Undirected-BFS.cpp`
- `09-Cycle-Undirected-DFS.cpp`
- `16-Bipartite-Check-BFS.cpp`
- `17-Bipartite-Check-DFS.cpp`
- `18-Cycle-Directed-DFS.cpp`
- `53-Shortest-Cycle-Practice.cpp`

### Topological sort / dependencies
- `19-Topo-Sort-DFS.cpp`
- `20-Topo-Sort-BFS-Kahn.cpp`
- `21-Course-Schedule-I.cpp`
- `22-Course-Schedule-II.cpp`
- `23-Eventual-Safe-States-BFS.cpp`
- `24-Eventual-Safe-States-DFS.cpp`
- `25-Alien-Dictionary.cpp`

### Shortest paths
- `13-Word-Ladder-I.cpp`
- `14-Word-Ladder-II.cpp`
- `26-Shortest-Path-UG-Unit.cpp`
- `27-Shortest-Path-DAG.cpp`
- `28-Dijkstra-PQ.cpp`
- `29-Dijkstra-Set.cpp`
- `30-Bellman-Ford.cpp`
- `31-Floyd-Warshall.cpp`
- `32-Zero-One-BFS.cpp`
- `33-Min-Multiplications.cpp`
- `34-Number-of-Ways-Arrival.cpp`
- `35-Min-Edges-Reverse.cpp`
- `36-Shortest-Path-Binary-Maze.cpp`
- `37-Path-Min-Effort.cpp`
- `38-Cheapest-Flights-K-Stops.cpp`
- `39-Network-Delay-Time.cpp`
- `40-Swim-in-Rising-Water.cpp`

### DSU / MST
- `41-Disjoint-Set-Union.cpp`
- `42-Kruskal-MST.cpp`
- `43-Prims-MST.cpp`
- `44-Number-of-Provinces-DSU.cpp`
- `45-Connect-All-Points-Min-Cost.cpp`
- `46-Accounts-Merge.cpp`
- `48-Most-Stones-Removed.cpp`

### Advanced (bridges / SCC)
- `49-Bridges-Tarjan.cpp`
- `50-Articulation-Points.cpp`
- `51-SCC-Kosaraju.cpp`
- `52-SCC-Tarjan.cpp`

---

## 16. QUICK REVISION SHEET

**Concepts**
- Adjacency list `O(V+E)` is the default; grids = implicit graphs (`r*cols+c`).
- BFS = FIFO layers ⇒ unweighted shortest. DFS = components/cycles/paths.
- Topo sort = DAG ordering; exists iff acyclic; Kahn detects cycles.
- DSU ≈ `O(1)` connectivity; Kruskal = sort edges + DSU; Prim = grow with heap.

**Recognition clues (the four questions)**
| Question | Answer → algorithm |
|---|---|
| Unweighted / steps? | BFS |
| Weighted ≥ 0? | Dijkstra `O(E log V)` |
| Negative weights? | Bellman-Ford `O(VE)` / Floyd `O(V³)` all-pairs |
| Dependencies / ordering? | Topological sort |
| Min cost to connect? | MST (Kruskal/Prim) |
| Merging connectivity? | DSU |
| 2-color / alternate? | Bipartite BFS |

**Algorithms (memorize)**
```text
BFS: mark on enqueue; dist = layers
Kahn: indegree-0 queue; size < V => cycle
Dijkstra: pop (d,u); if d != dist[u] skip; relax
Bellman: relax all edges V-1 times; V-th => neg cycle
Floyd: k outermost; skip INF additions
0-1 BFS: w=0 push_front, w=1 push_back
DSU: find with path compression; unite by rank
```

**Complexity** — BFS/DFS/topo `O(V+E)` · Dijkstra `O(E log V)` · Bellman `O(VE)` · Floyd `O(V³)` · Kruskal `O(E log E)` · DSU `O(α)`.

**Common mistakes** — visited on enqueue · disconnected loop · parent/inStack for cycles · Dijkstra+negatives · INF guards · 0/1 indexing · recursion depth.

**Decision rules** — directed? weighted? negative? acyclic? → algorithm selected. Connectivity only → skip paths, use DSU.

---

## 17. INTERVIEW CHECKLIST

- [ ] Can I choose representation (list vs matrix) and justify it?
- [ ] Can I write BFS/DFS (recursive + iterative) from memory?
- [ ] Can I detect cycles in undirected (parent) and directed (inStack/Kahn)?
- [ ] Can I write Kahn's topo sort and explain the cycle signal?
- [ ] Can I write Dijkstra with the staleness check and INF guard?
- [ ] Can I state *when* Bellman-Ford/Floyd are required (negative / all-pairs)?
- [ ] Can I write DSU with path compression + union by rank?
- [ ] Can I run Kruskal and detect disconnected input?
- [ ] Can I handle multi-source BFS and grid directions correctly?
- [ ] Can I convert a grid/word problem into a graph formulation?
- [ ] Can I answer complexity for every algorithm in the table above?
- [ ] Can I spot 1-index/0-index and recursion-depth traps before coding?

<!-- done -->
