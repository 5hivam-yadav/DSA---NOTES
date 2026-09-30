# Graph — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — BFS (unweighted shortest path / layers / multi-source)

**What is the pattern?**

Queue-based layer-by-layer exploration; distance = layer number.

**When should I recognize it?**

- "Shortest path in an **unweighted** graph/grid", "minimum steps / moves", "level order of states", "rotten oranges / nearest 0 / multi-source spread", "word ladder".

**Core intuition**

All edges cost 1 → exploring in FIFO order guarantees the first reach is the shortest; states expand like ripples.

**Generic algorithm**

1. `queue`, `dist[] = -1/INF`, mark source visited, `dist = 0`.
2. Pop `u`; for each unvisited neighbor: `dist[v] = dist[u] + 1`, mark, push.
3. Multi-source: push *all* sources first with distance 0.

**Time / Space**

`O(V + E)` / `O(V)`.

**Edge cases**

Source == target (0); disconnected (−1); multiple components (loop over all); self-loops.

**Common mistakes**

Mark visited on **enqueue**; forgetting distance array initialization; grid boundary checks.

**Variations**

Multi-source (all sources initially); 0-1 BFS (deque, weights 0/1); BFS on implicit grids/word graphs.

### P2 — DFS (components / cycles / flood fill / paths)

**What is the pattern?**

Recursive (or stack) depth-first traversal marking visited.

**When should I recognize it?**

- "Count provinces / islands", "flood fill", "find paths", "cycle detection", "surrounded regions", "number of enclaves", "islands variants".

**Core intuition**

DFS claims an entire connected region in one descent; what remains unvisited belongs to other components.

**Generic algorithm**

```text
for each node:  if !visited: dfs(node)     // components
dfs(u):  mark; for v in adj[u]: if !visited and valid: dfs(v)
```

For cycles add `parent` (undirected) or `inStack` (directed).

**Time / Space**

`O(V + E)` / `O(V)` recursion (grid `O(mn)`).

**Edge cases**

Empty graph; isolated nodes; deep recursion (stack overflow → iterative); grid borders.

**Common mistakes**

Not marking before recursion (infinite loops on cycles); wrong direction array; visiting invalid cells.

**Variations**

Iterative DFS (explicit stack); DFS with early exit (target found); DFS coloring for bipartite.

### P3 — Topological Sort (Kahn / DFS-postorder)

**What is the pattern?**

Order DAG nodes so all dependencies precede dependents; indegree-BFS (Kahn) or reverse post-order (DFS).

**When should I recognize it?**

- "Course schedule / prerequisites possible?", "alien dictionary ordering", "build order / task scheduling with dependencies", "sort words by derived order", "sequence reconstruction".

**Core intuition**

A valid order exists iff you can repeatedly remove a node with **no unresolved prerequisites** (indegree 0). Stuck with nodes remaining → cycle → impossible.

**Generic algorithm (Kahn)**

1. Compute indegrees; push all 0-indegree nodes.
2. Pop → order; decrement neighbors → push new 0s.
3. `order.size() == V` ⇒ valid; else cycle.

**Time / Space**

`O(V + E)` / `O(V)`.

**Edge cases**

Disconnected DAGs (multiple 0-indegree starts); single node; cycle detection (output size); multiple valid orders (any is fine).

**Common mistakes**

Only seeding *some* zero-indegree nodes; not detecting cycle (compare size to V); building edges in the wrong direction (prerequisite → course).

**Variations**

DFS-postorder reversed; lexicographically smallest order (use a min-heap / `set` in Kahn); DP over topo order for DAG paths (§16).

### P4 — Dijkstra (non-negative weighted shortest path)

**What is the pattern?**

Min-heap of `(distance, node)`; pop smallest, relax neighbors; stale-entry skip.

**When should I recognize it?**

- "Shortest path with **non-negative** weights", "minimum time / cost with positive costs", "network delay time", "path with minimum effort (threshold via heap or binary search)", "cheapest flights with constraints (variant)".

**Core intuition**

The globally closest unsettled node can't be improved later (weights ≥ 0) — commit its distance, expand.

**Generic algorithm**

1. `dist[src] = 0`; heap push `(0, src)`.
2. Pop `(d, u)`; if `d > dist[u]` → stale, skip.
3. For each edge `u→v` with weight `w`: if `d + w < dist[v]` → update and push.
4. Repeat until heap empty.

**Time / Space**

`O(E log V)` / `O(V + E)`.

**Edge cases**

Unreachable nodes (stay INF); `INF + w` overflow (skip when `d == INF`); source = target; ties (any order).

**Common mistakes**

Negative edges (illegal — use Bellman-Ford); forgetting the staleness check; wrong `INF` (too small → saturation, too large → overflow on add).

**Variations**

Dijkstra with `set` (`O(E log V)`, allows erase); K-stops variants (track stops in state); path reconstruction (parent array).

### P5 — Bellman-Ford / Floyd-Warshall (negative & all-pairs)

**What is the pattern?**

**Bellman-Ford**: relax all edges `V−1` times (single source, negatives, negative-cycle detection). **Floyd**: `V×V×V` DP over intermediates (all pairs).

**When should I recognize it?**

- "Shortest path with **negative** weights", "detect negative cycle", "can debts be settled (difference constraints)", "all-pairs shortest / cheapest flights with at most k stops (rephrased)", "matrix with negative edges".

**Core intuition**

Bellman-Ford: after `k` rounds every path of ≤ `k` edges is optimal; simple paths have ≤ `V−1` edges. Floyd: `d[i][j]` using intermediates `0..k` = DP over subsets of vertices.

**Generic algorithm (Bellman-Ford)**

```text
dist[src] = 0
repeat V-1 times: for each edge (u,v,w): relax
one more pass: any relaxation => negative cycle
```

**Time / Space**

Bellman `O(V·E)` / `O(V)`; Floyd `O(V³)` / `O(V²)`.

**Edge cases**

Unreachable (`INF` guard before adding); negative self-loops; `V = 1`; Floyd init (`d[i][i] = 0`, edges overwrite mins).

**Common mistakes**

Running Bellman only `V-2` times; forgetting INF guards; Floyd with `k` not outermost; using Dijkstra with negatives.

**Variations**

Floyd for transitive closure (Warshall); "at most k edges" → relax exactly `k+1` rounds (a Bellman-Ford variant).

### P6 — DSU / MST (connectivity & minimum cost)

**What is the pattern?**

**DSU**: incremental connectivity queries/unions. **Kruskal**: sort edges, add if it connects two components. **Prim**: grow min-cost tree from a vertex with a heap.

**When should I recognize it?**

- "Connect all nodes at minimum cost", "minimum spanning tree", "accounts merge / provinces via given edges", "redundant connection", "is it possible to connect with budget", "number of connected components after adding edges".

**Core intuition**

DSU answers "already connected?" in ~`O(1)`; Kruskal adds the cheapest edge that *doesn't* close a cycle; Prim always crosses the cut with the cheapest edge (cut property ⇒ optimal).

**Generic algorithm (Kruskal)**

1. Sort edges by weight.
2. For each: `union(u,v)` — if it merged (returned true) → count++, add weight.
3. Stop at `V−1` edges; if fewer possible → disconnected.

**Time / Space**

DSU ~`O(α(n))`/op; Kruskal `O(E log E)`; Prim `O(E log V)`; Prim dense `O(V²)`.

**Edge cases**

Self-loops (always cycle); duplicate edges; disconnected graph (MST undefined / component count); single node (`0` edges).

**Common mistakes**

Not calling `find` before comparing; forgetting union return value as cycle test; counting edges after `V−1` (stop early).

**Variations**

DSU with component sizes (accounts merge labels); DSU offline reverse (delete-edge → add-edge problems, advanced); Prim with lazy deletion.

### P7 — Cycle Detection & Bipartite Coloring

**What is the pattern?**

DFS/BFS with an extra piece of state — `parent` (undirected cycle), `inStack` (directed cycle), or `color` (bipartite) — that turns "did I revisit a node?" into a meaningful signal.

**When should I recognize it?**

- "Does the graph contain a cycle?", "course schedule possible?", "can jobs be scheduled?", "is the graph bipartite / 2-colorable?", "detect redundant connection", "eventual safe states".

**Core intuition**

- Undirected: revisiting a visited node *that isn't the node you came from* means you looped around.
- Directed: reaching a node still being processed (on the recursion stack) means a back edge → cycle.
- Bipartite: color alternates along edges; an edge between same-colored nodes closes an **odd cycle**.

**Generic algorithm**

```text
undirected cycle:  dfs(u, parent): for v != parent: if visited(v) -> cycle; else dfs(v, u)
directed cycle:    dfs(u): inStack[u]=true; for v: if inStack[v] -> cycle;
                              if !visited(v) && dfs(v): cycle;  inStack[u]=false
bipartite:         bfs: color[v] = 1 - color[u]; same color -> false
Kahn cycle:        topo order size < V -> cycle
```

**Time / Space**

`O(V + E)` / `O(V)`.

**Edge cases**

Self-loops (always cycle / never bipartite); disconnected graphs (loop over all starts); single node/edge.

**Common mistakes**

Undirected without parent → false cycle from the edge you arrived on; directed with plain visited → wrong; bipartite checked on one component only.

**Variations**

DSU-based cycle check (edge unites same component → cycle); Kahn for directed cycle; 2-coloring as greedy assignment.

### P8 — Implicit Graphs (grid / words / states)

**What is the pattern?**

Nodes are *not given* — they're positions, strings, or states; neighbors are generated on the fly (direction tables, one-letter mutations).

**When should I recognize it?**

- "Islands / rotten oranges / floods" (grid cells), "word ladder" (string states), "sliding puzzle / minimum moves" (board states), "swim in rising water / path min effort" (grid with weights).

**Core intuition**

Anything with "states + legal moves" is a graph: cells connect to 4/8 neighbors; words connect by one substitution; puzzle moves connect boards. BFS/DFS/Dijkstra run unchanged once you can *enumerate neighbors*.

**Generic algorithm**

1. Define state → node (index or hash).
2. Define `neighbors(state)` generator (direction arrays / letter loops / move sets).
3. Run the right traversal (BFS unweighted, Dijkstra weighted, A*/binary search variants).

**Time / Space**

`O(states + transitions)` — grid `O(mn)`, word ladder `O(N·L·26)` neighbor gen (or wildcard buckets), sliding puzzle states ≤ `9!`.

**Edge cases**

Visited states must be marked **when enqueued**; hash collisions if using `unordered_set` of boards; start == goal; unreachable goal (−1).

**Common mistakes**

Generating neighbors out of bounds; not deduplicating states (exponential blowup); forgetting to encode state completely (missing one cell → wrong).

**Variations**

Multi-source grid BFS (§3.6); grid Dijkstra (weights from cell values); binary search + BFS on threshold (§04 × BFS).

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
