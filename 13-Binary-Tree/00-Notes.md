# Binary Tree — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — DFS Return-Info-Up (height / diameter / balanced / same-tree)

**What is the pattern?**

Children return computed values; parent combines them; optionally update a global.

**When should I recognize it?**

- "Height/depth", "diameter", "is balanced", "same tree / mirror", "max path sum", "count nodes", "children sum property".

**Core intuition**

Post-order: what the parent needs (child's height/flag) is only known after children are processed — recursion does the waiting.

**Generic algorithm**

1. Base: `!r` → return 0 / flag.
2. Recurse both children.
3. Combine (`max`, `sum`, update global `d`).
4. Return height/flag to parent.

**Time / Space**

`O(n)` / `O(h)` recursion (skewed → `O(n)`).

**Edge cases**

Empty tree (height 0 / diameter 0); single node; negative values (max path sum needs `max(0, child)` clamping).

**Common mistakes**

Edges-vs-nodes height convention; forgetting the global update; clamping negative child contributions.

**Variations**

Balanced with `-1` early-exit sentinel; max path sum = diameter generalized to weights.

### P2 — BFS Level Order (views, width, zigzag, level aggregates)

**What is the pattern?**

Queue of nodes per level; process level-by-level → knowledge of depth enables views/width/zigzag.

**When should I recognize it?**

- "Level order / zigzag order", "left-right-top-bottom-vertical view", "maximum width", "level averages", "nodes at distance K", "burn time".

**Core intuition**

BFS discovers nodes in non-decreasing depth → after each level boundary you know *exactly* which nodes share a depth.

**Generic algorithm**

1. Push root; while queue not empty: `sz = queue.size()` → process exactly `sz` nodes = one level.
2. For views: record first/last of each level.
3. For width: attach an index (`2i`, `2i+1`-style or incrementing) — width = `lastIdx − firstIdx + 1` (use `long long`).

**Time / Space**

`O(n)` / `O(w)` where `w` = max width (`O(n)` worst).

**Edge cases**

Empty tree; single node; skewed tree (width 1); index overflow in width-by-index (use `long long` or `unsigned long long`).

**Common mistakes**

Updating `sz` inside the inner loop (breaks level boundary); DFS for top view (wrong order — top view needs breadth-first discovery).

**Variations**

Zigzag (reverse odd levels or two-stack); vertical (map by hd); nodes-at-distance-K (BFS with parent links).

### P3 — LCA (post-order meet-in-the-middle)

**What is the pattern?**

Recurse; the first node with *both* children returning non-null (or target-found-and-other-subtree) is the LCA.

**When should I recognize it?**

- "Lowest common ancestor", "path between two nodes", "distance between nodes", "is ancestor".

**Core intuition**

LCA is where the searches for `p` and `q` **diverge** — post-order detects divergence from below.

**Generic algorithm**

1. Base: null → null; node == p or q → node.
2. Get L/R results.
3. If both non-null → current is LCA; else bubble up the non-null one.

**Time / Space**

`O(n)` / `O(h)`.

**Edge cases**

One node is the ancestor of the other (LCA = that node); p/q not in tree (spec: guaranteed present, else validate); null root.

**Common mistakes**

Returning non-null child *and* also the parent chain incorrectly; assuming both must be found below (ancestor case!).

**Variations**

LCA in BST → value walk `O(h)` (§14); with parent pointers → depth-align + walk; binary lifting → `O(log n)` queries after `O(n log n)` preprocessing (advanced).

### P4 — Boundary Traversal (left border + leaves + right border)

**What is the pattern?**

Collect: left boundary (top-down, excluding leaves), leaves (left→right, post/inorder), right boundary (bottom-up, excluding leaves).

**When should I recognize it?**

- "Boundary traversal of binary tree" (anti-clockwise outline).

**Core intuition**

The outline = three disjoint sequences stitched: left edge down, leaves across, right edge up — with careful exclusion rules to avoid duplicates.

**Generic algorithm**

1. Left boundary: go left while possible; skip leaf nodes (record non-leaf).
2. Leaves: inorder/preorder collecting nodes with no children.
3. Right boundary: go right; record on unwind (bottom-up) skipping leaves.
4. Concatenate: left + leaves + right.

**Time / Space**

`O(n)` / `O(h)`.

**Edge cases**

Single node (itself only); root is a leaf; left-only tree (left boundary == leaf path — dedup!); empty.

**Common mistakes**

Double-counting leaves in boundary lists; including root twice; right boundary order (must be reversed to bottom-up).

**Variations**

Right view boundary (clockwise) — reverse the assembly order.

### P5 — Path Carry / Collect (root-to-leaf paths, K distance, serialize)

**What is the pattern?**

Carry state (sum, path string, distance) down the recursion; collect/act at targets; **undo on return**.

**When should I recognize it?**

- "Root-to-leaf paths with sums", "all root-to-leaf numbers", "path from root to a node", "serialize/deserialize", "nodes at distance K from target".

**Core intuition**

State flows down with the recursion; backtracking's undo keeps the shared path correct for siblings (§07 rule applies to trees).

**Generic algorithm**

```text
dfs(node, path, target):
    path.push(node)
    if node is target / leaf condition: record path / sum
    dfs(children...)
    path.pop()                      // undo
```

**Time / Space**

`O(n + total path length)` / `O(h)` working, `O(n·h)` output worst.

**Edge cases**

Root is target/leaf; skewed tree (one path); no path exists.

**Common mistakes**

Forgetting `pop_back` (corrupts sibling paths); passing `path` **by value** (quadratic copying); serialization: null markers (`#`) required to reconstruct.

**Variations**

Serialize with preorder + `#` + `null` markers; deserialize consumes an iterator over tokens; nodes-at-distance-K needs parent links + BFS upward/downward.

### P6 — Construction from Traversals (inorder + one other)

**What is the pattern?**

`inorder` locates the root's position; `preorder`/`postorder` gives root first/last; recurse on left/right index ranges (or map index for `O(1)` lookups).

**When should I recognize it?**

- "Construct binary tree from inorder+preorder", "from inorder+postorder", "from preorder+level-order", "unique trees count (Catalan)".

**Core intuition**

Preorder tells you *which* value is the root next; inorder splits the remaining into left/right subtrees — the split point defines the recursion.

**Generic algorithm (preorder + inorder)**

1. Root = `pre[pi++]`.
2. Find `root` in `inorder` at index `m` (map value→index for speed).
3. Build left from `in[lo..m-1]`, right from `in[m+1..hi]` (counts from inorder determine preorder consumption order).

**Time / Space**

`O(n)` with map (else `O(n²)` linear search) / `O(n)`.

**Edge cases**

Empty range; single node; duplicate values (assumed unique — otherwise ambiguous).

**Common mistakes**

Wrong subtree ranges (off-by-one on `m-1`/`m+1`); forgetting to increment `pi` exactly once per node; inorder+level-order needs value→index map per level (advanced).

**Variations**

Morris traversal (threaded, `O(1)` space) for inorder/preorder without stack; postorder-from-in+pre (two pointers meeting).

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
