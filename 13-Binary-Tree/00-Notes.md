# 13 — Binary Tree — Complete Pattern-Based Notes

---

## 1. Topic Overview

A **binary tree** is a hierarchical structure where each node has up to two children — the basis for BSTs, heaps, tries-in-tree-form, and tree-shaped recursion.

**What it is**
Nodes with `val`, `left`, `right`; no cycles; exactly one root; paths from root to any node are unique.

**Why it is important**
- Tree traversal (DFS/BFS) is the template for graph traversal (§15).
- Most tree problems reduce to a handful of recursive patterns: *return info up*, *carry info down*, *LCA*, *views via levels*.
- Interviews: diameter, LCA, views, serialization, path sums — near-guaranteed questions.

**Where it is used**
- File systems, DOM, compilers (ASTs), databases (B-trees), routing (tries), heaps.
- Interview staples listed in §4's pattern library.

**How it connects to other topics**
- §06 Linked List: a tree node is a list node with two pointers.
- §07 Recursion: tree DFS *is* recursion on structure.
- §09 Stack/Queue: iterative traversals (explicit stack), level order (queue).
- §14 BST: add the ordering property → everything gets `O(h)`.

**Interview memory hook:** *DFS returns height/flags up; BFS answers views/width; LCA is post-order; diameter = max(lh+rh) at each node.*

---

## 2. Fundamentals

### 2.1 Structure & terminology

```text
        1              level 0
       / \
      2   3           level 1
     / \   \
    4   5   6         level 2 (leaves: 4, 5, 6)

height(node)  = edges to deepest leaf below   (leaf height 0; null height -1)
depth(node)   = edges from root               (root depth 0)
size          = number of nodes
skewed        = degenerates to a linked list (worst case height n)
balanced       = height O(log n) (AVL: |lh - rh| <= 1)
```

### 2.2 Node definition

```cpp
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```

### 2.3 The four traversals

```text
Preorder:   visit  root -> left -> right     (structure-copying, prefixes)
Inorder:    visit  left -> root -> right     (BST sorted order!)
Postorder:  visit  left -> right -> root     (process children first: free, height)
Levelorder: BFS by depth                    (views, widths)
```

```text
        1
       / \
      2    3
     / \    \
    4   5    6

preorder:  1 2 4 5 3 6
inorder:   4 2 5 1 3 6
postorder: 4 5 2 6 3 1
level:     1 | 2 3 | 4 5 6
```

### 2.4 Recursion shapes

```text
Type A: children return VALUES, parent combines   -> height, diameter, balanced, same-tree
Type B: parent PASSES VALUES down                 -> root-to-leaf path sums, target path
Type C: global/mutable accumulator                -> count, collect results
```

---

## 3. Core Concepts

### 3.1 Traversals (recursive + iterative)

**Definition**  \nPreorder/inorder/postorder by recursion; iterative versions use an explicit stack; level order uses a queue.

**Why needed**  \nTraversal is the skeleton of nearly every tree algorithm — visiting each node exactly once → `O(n)`.

**How it works (iterative inorder)**

```cpp
vector<int> inorder(TreeNode* r) {
    vector<int> out; stack<TreeNode*> st;
    while (r || !st.empty()) {
        while (r) { st.push(r); r = r->left; }
        r = st.top(); st.pop();
        out.push_back(r->val);
        r = r->right;
    }
    return out;
}
```

**Complexity**  \n`O(n)` time, `O(h)` space (recursion/stack), `O(n)` worst skewed.

**Common mistakes** Null root; forgetting `r = r->right` after pop; mixing up order in Morris traversals.

---

### 3.2 Height / depth (return-info-up pattern)

**Definition**  \n`height = 1 + max(height(left), height(right))`, null = 0 (nodes) or −1 (edges).

**Intuition** The parent can only know subtree heights *after* children return — classic post-order accumulation.

**How it works**

```cpp
int height(TreeNode* r) { return r ? 1 + max(height(r->left), height(r->right)) : 0; }
```

**Common mistakes** Off-by-one between "edges" vs "nodes" convention — state which you use; null handling.

---

### 3.3 Diameter (global update inside recursion)

**Definition** Longest path (edges) between any two nodes — not necessarily through root.

**Core insight** At each node, the best path *through* it = `lh + rh`; track the global max while returning heights.

```cpp
int dfsH(TreeNode* r, int& d) {
    if (!r) return 0;
    int l = dfsH(r->left, d), rr = dfsH(r->right, d);
    d = max(d, l + rr);               // path through r
    return 1 + max(l, rr);            // height for parent
}
```

**Common mistake** Updating diameter only at the root (misses deepest path elsewhere); returning height but forgetting the global.

---

### 3.4 Balanced check (early-exit sentinel)

**Definition** For every node, `|lh − rh| ≤ 1`.

**Intuition** Return height *or* an error flag (−1). If any child returns −1 → propagate immediately — avoids re-checking.

**Complexity** `O(n)` vs naive `O(n log n)` (recomputing heights).

---

### 3.5 Path problems (carry-down vs return-up)

- **Root-to-leaf sums / paths**: carry `sum` and `path` down (Type B); collect at leaves; pop on return (undo — same as §07 backtracking).
- **Max path any-to-any**: return-up (like diameter).
- **Path between two nodes**: LCA + distance = `depth(a) + depth(b) − 2·depth(lca)`.

**Common mistake** Storing the path by value vs reference: `path.push_back` on a copied vector loses sibling paths; push/pop with one shared vector.

---

### 3.6 LCA (post-order definition)

**Definition** Deepest node that is an ancestor of both `p` and `q`.

**Algorithm** Recurse; if a side returns non-null, bubble up; if **both** sides non-null → current node is LCA.

**Variants**: LCA in BST → compare values (walk down, first node between p and q); LCA with parent pointers → level-align then walk up.

**Complexity** `O(n)` general tree, `O(h)` BST.

---

### 3.7 Views / vertical traversal (level + horizontal distance)

**Definition** Top/bottom/left/right/vertical views organize nodes by **level** and **horizontal distance (hd)**.

**How it works**
- Left/right view: BFS; record first/last node per level.
- Top view: BFS with `map<hd, value>` — first node at each hd wins (level order guarantees top-most).
- Bottom view: same map — last node wins.
- Vertical order: BFS/recursion grouping by hd, sorted by hd.

**Common mistake** Using DFS for top view (deepest-first wrongness); forgetting `long long`/offset for hd keys.

---

## 4. PATTERN LIBRARY

### P1 — DFS Return-Info-Up (height / diameter / balanced / same-tree)

#### What is the pattern?
Children return computed values; parent combines them; optionally update a global.

#### When should I recognize it?
- "Height/depth", "diameter", "is balanced", "same tree / mirror", "max path sum", "count nodes", "children sum property".

#### Core intuition
Post-order: what the parent needs (child's height/flag) is only known after children are processed — recursion does the waiting.

#### Generic algorithm
1. Base: `!r` → return 0 / flag.
2. Recurse both children.
3. Combine (`max`, `sum`, update global `d`).
4. Return height/flag to parent.

#### C++ template
```cpp
int dfsH(TreeNode* r, int& d) {
    if (!r) return 0;
    int l = dfsH(r->left, d), rr = dfsH(r->right, d);
    d = max(d, l + rr);
    return 1 + max(l, rr);
}
```

#### Time / Space
`O(n)` / `O(h)` recursion (skewed → `O(n)`).

#### Edge cases
Empty tree (height 0 / diameter 0); single node; negative values (max path sum needs `max(0, child)` clamping).

#### Common mistakes
Edges-vs-nodes height convention; forgetting the global update; clamping negative child contributions.

#### Variations
Balanced with `-1` early-exit sentinel; max path sum = diameter generalized to weights.

#### Practice mapping
- `08-Maximum-Depth.cpp`, `10-Diameter-of-Binary-Tree.cpp`, `09-Height-Balanced-Check.cpp`, `11-Maximum-Path-Sum.cpp`, `12-Same-Tree.cpp`, `19-Symmetric-Tree.cpp`, `23-Children-Sum-Property.cpp`

---

### P2 — BFS Level Order (views, width, zigzag, level aggregates)

#### What is the pattern?
Queue of nodes per level; process level-by-level → knowledge of depth enables views/width/zigzag.

#### When should I recognize it?
- "Level order / zigzag order", "left-right-top-bottom-vertical view", "maximum width", "level averages", "nodes at distance K", "burn time".

#### Core intuition
BFS discovers nodes in non-decreasing depth → after each level boundary you know *exactly* which nodes share a depth.

#### Generic algorithm
1. Push root; while queue not empty: `sz = queue.size()` → process exactly `sz` nodes = one level.
2. For views: record first/last of each level.
3. For width: attach an index (`2i`, `2i+1`-style or incrementing) — width = `lastIdx − firstIdx + 1` (use `long long`).

#### C++ template
```cpp
vector<vector<int>> levelOrder(TreeNode* r) {
    vector<vector<int>> out;
    if (!r) return out;
    queue<TreeNode*> q; q.push(r);
    while (!q.empty()) {
        int sz = q.size();
        vector<int> level;
        while (sz--) {
            TreeNode* n = q.front(); q.pop();
            level.push_back(n->val);
            if (n->left)  q.push(n->left);
            if (n->right) q.push(n->right);
        }
        out.push_back(level);
    }
    return out;
}
```

#### Time / Space
`O(n)` / `O(w)` where `w` = max width (`O(n)` worst).

#### Edge cases
Empty tree; single node; skewed tree (width 1); index overflow in width-by-index (use `long long` or `unsigned long long`).

#### Common mistakes
Updating `sz` inside the inner loop (breaks level boundary); DFS for top view (wrong order — top view needs breadth-first discovery).

#### Variations
Zigzag (reverse odd levels or two-stack); vertical (map by hd); nodes-at-distance-K (BFS with parent links).

#### Practice mapping
- `06-Level-Order-Traversal.cpp`, `13-Zigzag-Traversal.cpp`, `14-Boundary-Traversal.cpp`, `15-Vertical-Order.cpp`, `16-Top-View.cpp`, `17-Bottom-View.cpp`, `18-Left-Right-View.cpp`, `22-Maximum-Width.cpp`, `24-Count-Complete-Nodes.cpp`, `25-Nodes-at-Distance-K.cpp`, `26-Burn-Tree-Min-Time.cpp`

---

### P3 — LCA (post-order meet-in-the-middle)

#### What is the pattern?
Recurse; the first node with *both* children returning non-null (or target-found-and-other-subtree) is the LCA.

#### When should I recognize it?
- "Lowest common ancestor", "path between two nodes", "distance between nodes", "is ancestor".

#### Core intuition
LCA is where the searches for `p` and `q` **diverge** — post-order detects divergence from below.

#### Generic algorithm
1. Base: null → null; node == p or q → node.
2. Get L/R results.
3. If both non-null → current is LCA; else bubble up the non-null one.

#### C++ template
```cpp
TreeNode* lca(TreeNode* r, TreeNode* p, TreeNode* q) {
    if (!r || r == p || r == q) return r;
    TreeNode* L = lca(r->left, p, q);
    TreeNode* R = lca(r->right, p, q);
    if (L && R) return r;
    return L ? L : R;
}
```

#### Time / Space
`O(n)` / `O(h)`.

#### Edge cases
One node is the ancestor of the other (LCA = that node); p/q not in tree (spec: guaranteed present, else validate); null root.

#### Common mistakes
Returning non-null child *and* also the parent chain incorrectly; assuming both must be found below (ancestor case!).

#### Variations
LCA in BST → value walk `O(h)` (§14); with parent pointers → depth-align + walk; binary lifting → `O(log n)` queries after `O(n log n)` preprocessing (advanced).

#### Practice mapping
- `21-LCA-Binary-Tree.cpp`, `14-Binary-Search-Tree/08-LCA-in-BST.cpp`, `20-Root-to-Node-Path.cpp`

---

### P4 — Boundary Traversal (left border + leaves + right border)

#### What is the pattern?
Collect: left boundary (top-down, excluding leaves), leaves (left→right, post/inorder), right boundary (bottom-up, excluding leaves).

#### When should I recognize it?
- "Boundary traversal of binary tree" (anti-clockwise outline).

#### Core intuition
The outline = three disjoint sequences stitched: left edge down, leaves across, right edge up — with careful exclusion rules to avoid duplicates.

#### Generic algorithm
1. Left boundary: go left while possible; skip leaf nodes (record non-leaf).
2. Leaves: inorder/preorder collecting nodes with no children.
3. Right boundary: go right; record on unwind (bottom-up) skipping leaves.
4. Concatenate: left + leaves + right.

#### C++ template
```cpp
// structure:
// isLeaf(n) -> push to leaves
// leftBound: push n, go left else right, stop before leaf
// rightBound: push to temp, reverse at end
```

#### Time / Space
`O(n)` / `O(h)`.

#### Edge cases
Single node (itself only); root is a leaf; left-only tree (left boundary == leaf path — dedup!); empty.

#### Common mistakes
Double-counting leaves in boundary lists; including root twice; right boundary order (must be reversed to bottom-up).

#### Variations
Right view boundary (clockwise) — reverse the assembly order.

#### Practice mapping
- `14-Boundary-Traversal.cpp`

---

### P5 — Path Carry / Collect (root-to-leaf paths, K distance, serialize)

#### What is the pattern?
Carry state (sum, path string, distance) down the recursion; collect/act at targets; **undo on return**.

#### When should I recognize it?
- "Root-to-leaf paths with sums", "all root-to-leaf numbers", "path from root to a node", "serialize/deserialize", "nodes at distance K from target".

#### Core intuition
State flows down with the recursion; backtracking's undo keeps the shared path correct for siblings (§07 rule applies to trees).

#### Generic algorithm
```text
dfs(node, path, target):
    path.push(node)
    if node is target / leaf condition: record path / sum
    dfs(children...)
    path.pop()                      // undo
```

#### C++ template
```cpp
void paths(TreeNode* r, vector<int>& cur, vector<vector<int>>& out) {
    if (!r) return;
    cur.push_back(r->val);
    if (!r->left && !r->right) out.push_back(cur);
    else { paths(r->left, cur, out); paths(r->right, cur, out); }
    cur.pop_back();
}
```

#### Time / Space
`O(n + total path length)` / `O(h)` working, `O(n·h)` output worst.

#### Edge cases
Root is target/leaf; skewed tree (one path); no path exists.

#### Common mistakes
Forgetting `pop_back` (corrupts sibling paths); passing `path` **by value** (quadratic copying); serialization: null markers (`#`) required to reconstruct.

#### Variations
Serialize with preorder + `#` + `null` markers; deserialize consumes an iterator over tokens; nodes-at-distance-K needs parent links + BFS upward/downward.

#### Practice mapping
- `20-Root-to-Node-Path.cpp`, `27-Serialize-Deserialize.cpp`, `25-Nodes-at-Distance-K.cpp`

---

### P6 — Construction from Traversals (inorder + one other)

#### What is the pattern?
`inorder` locates the root's position; `preorder`/`postorder` gives root first/last; recurse on left/right index ranges (or map index for `O(1)` lookups).

#### When should I recognize it?
- "Construct binary tree from inorder+preorder", "from inorder+postorder", "from preorder+level-order", "unique trees count (Catalan)".

#### Core intuition
Preorder tells you *which* value is the root next; inorder splits the remaining into left/right subtrees — the split point defines the recursion.

#### Generic algorithm (preorder + inorder)
1. Root = `pre[pi++]`.
2. Find `root` in `inorder` at index `m` (map value→index for speed).
3. Build left from `in[lo..m-1]`, right from `in[m+1..hi]` (counts from inorder determine preorder consumption order).

#### C++ template
```cpp
TreeNode* build(vector<int>& pre, int& pi, int lo, int hi,
                unordered_map<int,int>& pos) {
    if (lo > hi) return nullptr;
    int v = pre[pi++], m = pos[v];
    TreeNode* r = new TreeNode(v);
    r->left  = build(pre, pi, lo, m - 1, pos);
    r->right = build(pre, pi, m + 1, hi, pos);
    return r;
}
```

#### Time / Space
`O(n)` with map (else `O(n²)` linear search) / `O(n)`.

#### Edge cases
Empty range; single node; duplicate values (assumed unique — otherwise ambiguous).

#### Common mistakes
Wrong subtree ranges (off-by-one on `m-1`/`m+1`); forgetting to increment `pi` exactly once per node; inorder+level-order needs value→index map per level (advanced).

#### Variations
Morris traversal (threaded, `O(1)` space) for inorder/preorder without stack; postorder-from-in+pre (two pointers meeting).

#### Practice mapping
- `31-Build-from-Pre-In.cpp`, `32-Build-from-In-Post.cpp`, `34-Postorder-from-In-Pre.cpp`, `35-Tree-from-In-Level.cpp`, `28-Morris-Inorder.cpp`, `29-Morris-Preorder.cpp`

---

## 5. PATTERN RECOGNITION

| If the problem says... | Think about... |
|---|---|
| "height / depth / max depth" | DFS return-info-up (P1) |
| "diameter / longest path" | global update in height DFS (P1) |
| "is balanced" | -1 sentinel height (P1) |
| "level order / zigzag / views / width" | BFS level (P2) |
| "top / bottom / vertical view" | BFS + horizontal distance map (P2) |
| "lowest common ancestor" | post-order meet (P3) |
| "path between two nodes" | LCA + depths |
| "boundary traversal" | left border + leaves + right border (P4) |
| "root-to-leaf sum / paths" | carry-down + undo (P5) |
| "serialize / deserialize" | preorder + null markers (P5) |
| "rebuild tree from traversals" | inorder split + map (P6) |
| "max path sum (any-to-any)" | diameter-style global (P1) |
| "nodes at distance K / burn time" | BFS with parent links (P2/P5) |
| "complete tree count" | perfect-subtree test + recursion |

**Decision rules**
1. Value from children (height/flag)? → **return-info-up**.
2. Level/depth grouping? → **BFS with `sz` boundary**.
3. Ancestor relationship? → **LCA post-order**.
4. Path with state? → **carry down + pop back**.
5. Structure rebuild? → **inorder split + preorder root**.

---

## 6. BRUTE → BETTER → OPTIMAL THINKING

### Height / diameter
- **Brute** — for each node, compute height of both subtrees independently: `O(n²)`.
- **Better** — memoize heights in a map after one traversal: `O(n)`.
- **Optimal** — single DFS returning height while updating diameter: `O(n)` time, `O(h)` space — the classic return-info-up.

### Balanced check
- **Brute** — for each node, compute heights: `O(n²)`.
- **Better** — bottom-up heights, verify |Δ|≤1 with a second pass: `O(n)`.
- **Optimal** — same pass with `-1` sentinel early-exit: `O(n)` worst, early termination in practice.

### Lowest common ancestor
- **Brute** — find root-to-node paths for both, compare: `O(n)` time but `O(n)` path storage and more code.
- **Better** — depth-align + walk up with parent map: `O(n)`.
- **Optimal** — one post-order recursion bubbling targets: `O(n)` time, `O(h)` space, cleanest.

### Views (left/right/top/bottom)
- **Brute** — print per level, pick first/last manually: `O(n²)` if re-scanning.
- **Better** — DFS with depth tracking (works for left/right only).
- **Optimal** — BFS with level boundaries: `O(n)`; for top/bottom use `map<hd>` with BFS order — `O(n log n)` (log for map), accepted.

### Tree from inorder + preorder
- **Brute** — try all possible roots recursively without memo: exponential.
- **Better** — linear search for root in inorder: `O(n²)`.
- **Optimal** — value→index map: `O(n)` time, `O(n)` space.

### Max root-to-leaf path sum
- **Brute** — enumerate all paths (copy arrays): `O(n²)` copying.
- **Better** — carry sum down, collect at leaves: `O(n)`.
- **Optimal** — same `O(n)` with `O(h)` working space via push/pop undo — no path copies.

### Key transferable idea
> Tree optimization almost always means **merging two traversals into one** (heights+diameter, validate+prune) or **adding a lookup table** (value→index). The traversal itself is already `O(n)` — the win comes from not repeating it.

---

## 7. C++ / STL TOOLKIT

| Tool | Syntax | Use |
|---|---|---|
| TreeNode | `struct TreeNode{int val; TreeNode*left,*right;};` | node |
| Null checks | `if (!r) ...` | base case |
| Stack (iterative traversal) | `stack<TreeNode*> st` | preorder/inorder/postorder |
| Queue (level order) | `queue<TreeNode*> q` + `int sz = q.size()` | BFS levels |
| `map<int, …>` | horizontal distance → value | top/bottom view |
| `unordered_map<int,int>` | value → inorder index | tree construction |
| Path buffer | `vector<int> cur` + push/pop | root-to-leaf paths |

```cpp
// level order skeleton with size boundary
queue<TreeNode*> q; q.push(root);
while (!q.empty()) {
    int sz = q.size();
    while (sz--) { TreeNode* n = q.front(); q.pop(); /* level work */ 
                   if (n->left) q.push(n->left);
                   if (n->right) q.push(n->right); }
}

// carry-down path with undo
void dfs(TreeNode* r, vector<int>& cur, int sum, int target) {
    if (!r) return;
    cur.push_back(r->val); sum += r->val;
    if (!r->left && !r->right && sum == target) { /* record */ }
    dfs(r->left, cur, sum, target);
    dfs(r->right, cur, sum, target);
    cur.pop_back();
}
```

**Common mistakes**
- `q.front()`/`st.top()` without empty checks.
- Passing `path` by value (copies) — always by reference + undo.
- Using `int` for horizontal distance/width indices → overflow (use `long long`).

---

## 8. COMPLEXITY GUIDE

| Operation | Time | Space |
|---|---:|---:|
| Any full traversal | `O(n)` | `O(h)` recursion / `O(w)` BFS |
| Height / diameter / balanced | `O(n)` | `O(h)` |
| Level order / views | `O(n)` | `O(w)` (max width) |
| LCA (general tree) | `O(n)` | `O(h)` |
| LCA (BST) | `O(h)` | `O(1)` iterative |
| Boundary / zigzag / vertical | `O(n)` (map → `O(n log n)`) | `O(n)` |
| Build from traversals (map) | `O(n)` | `O(n)` |
| Serialize / deserialize | `O(n)` | `O(n)` |
| Morris traversal | `O(n)` | **`O(1)`** |
| Diameter with heights recompute (brute) | `O(n²)` | `O(h)` |

**How to estimate** — `h = log n` (balanced) to `n` (skewed); `w` (width) ≤ n. Every node visited once ⇒ base `O(n)`; extra `log` only from ordered maps.

---

## 9. EDGE CASES

- **Empty tree (`root == nullptr`)** — every function must handle first; views return empty; height 0 / diameter 0.
- **Single node** — diameter 0; boundary = itself; LCA = itself; both views = it.
- **Left-only / right-only (skewed)** — recursion depth `n` (stack overflow risk at ~10^5); width 1; boundary dedup.
- **All negative values** — max path sum needs proper initialization (`INT_MIN` or first value), clamp child contributions.
- **Nodes at extremes of level** — first/last detection off-by-one when levels have 1 node.
- **Width index overflow** — complete-tree indices double per level → `long long`.
- **Duplicate values** (construction from traversals) — ambiguous; assume unique or handle carefully.
- **p == q in LCA** — returns that node; ensure no infinite loop.
- **Height convention** — edges vs nodes: state it; tests may differ.
- **Root is leaf + boundary** — don't duplicate root in left/right/leaf lists.

---

## 10. COMMON MISTAKES

| # | Mistake | What goes wrong | Why | How to avoid |
|---|---|---|---|---|
| 1 | Missing null base case | segfault | children dereferenced on null | `if (!r) return ...` first |
| 2 | Height edges vs nodes confusion | off-by-one answers | conventions differ | state convention; test single node |
| 3 | Diameter updated only at root | wrong | deepest path elsewhere | global update in every frame |
| 4 | Forgetting `pop_back` on path | sibling paths corrupted | state not undone | push → recurse → pop |
| 5 | Path passed by value | quadratic copies | vector copy per call | pass `vector<int>&` + undo |
| 6 | `q.size()` re-evaluated in loop | levels merged | queue grows during loop | `int sz = q.size()` snapshot |
| 7 | Width index overflow | wrong width | `2^depth` > 2^31 | `long long` indices |
| 8 | Top view via DFS | wrong node chosen | DFS isn't breadth-first | use BFS for top view |
| 9 | LCA assumes both below | wrong for ancestor case | one node may be ancestor | the standard code handles it — don't "optimize" it away |
| 10 | Balanced check recomputing heights | `O(n²)` | no memoization | return height+flag together |
| 11 | Forgetting `#` in serialization | ambiguous rebuild | left/right nulls invisible | null markers required |
| 12 | Traversal order mix-up | wrong construction | pre/in/post root position | memorize: pre=first, post=last, in=split |

**Conceptual mistakes**
- Treating a tree problem as "just print values" when the *shape* (inorder for BST, hd for views) carries the semantics.
- Using DFS where breadth matters (views, shortest-in-unweighted = BFS).

---

## 11. IMPORTANT FORMULAS / RULES

```text
height(null) = 0 (nodes) or -1 (edges)     -- pick one
height(n)    = 1 + max(h(left), h(right))
diameter at n = h(left) + h(right) (edges)  -- global max over all n
balanced     = |h(left) - h(right)| <= 1 for every node
max path sum through n = val + max(0,l) + max(0,r)
LCA:  both sides non-null -> current node
distance(a,b) = depth(a) + depth(b) - 2*depth(lca)
levels in balanced tree = log2(n) + 1; skewed = n
complete tree nodes in [2^h .. 2^(h+1) - 1]
unique BSTs with n keys = Catalan(n) = C(2n,n)/(n+1)
```

**Rules / invariants**
1. One node visited exactly once → `O(n)` is the floor for any global tree query.
2. State that flows *down* must be undone (or passed by value deliberately).
3. State that flows *up* must combine after both children return (post-order).

---

## 12. REUSABLE TEMPLATES

```cpp
// 1. Height + diameter in one pass
int dfsH(TreeNode* r, int& d) {
    if (!r) return 0;
    int l = dfsH(r->left, d), rr = dfsH(r->right, d);
    d = max(d, l + rr);
    return 1 + max(l, rr);
}

// 2. Balanced check with -1 sentinel
int balanced(TreeNode* r) {
    if (!r) return 0;
    int l = balanced(r->left);
    if (l == -1) return -1;
    int rr = balanced(r->right);
    if (rr == -1) return -1;
    if (abs(l - rr) > 1) return -1;
    return 1 + max(l, rr);
}

// 3. LCA
TreeNode* lca(TreeNode* r, TreeNode* p, TreeNode* q) {
    if (!r || r == p || r == q) return r;
    TreeNode* L = lca(r->left, p, q);
    TreeNode* R = lca(r->right, p, q);
    return (L && R) ? r : (L ? L : R);
}

// 4. Level order with size boundary
queue<TreeNode*> q; q.push(root);
while (!q.empty()) {
    int sz = q.size();
    while (sz--) {
        TreeNode* n = q.front(); q.pop();
        if (n->left)  q.push(n->left);
        if (n->right) q.push(n->right);
    }
}
```

## 13. ADVANCED CONCEPTS

### 13.1 Morris traversal (O(1) space)
Temporarily rewire the *inorder predecessor's right pointer* to the current node (threading), traverse, then restore. Inorder/preorder in `O(n)` time with **no stack/recursion** — great "can you do it without extra space?" follow-up.

### 13.2 Binary lifting (LCA in O(log n) after preprocessing)
`up[v][k]` = 2^k-th ancestor of `v`. Preprocess `O(n log n)`; answer LCA queries in `O(log n)`. Needed when many queries arrive — the advanced successor of the `O(n)` per-query recursion (§15 uses similar ideas).

### 13.3 Tree DP
Problems like "max independent set on tree", "house robber III" = DP on subtrees: `dp[node][0/1]` computed in post-order — bridge between §13 and §16.

### 13.4 Threaded / threaded-in-parent structures
Parent pointers + in-threading enable inorder without stack and O(1) successor — conceptual basis of `std::map` implementations (red-black trees with parent links).

### 13.5 Diameter on weighted & general trees
Same return-height pattern with edge weights; for graphs with cycles (tree diameter via two BFS: pick farthest from any node, then farthest from that) — a neat `O(n)` trick.

### 13.6 Serialization formats
Preorder with null markers (compact); level-order with nulls (parallel arrays). Comparison-based equality: run both serializations — `O(n)`.

---

## 14. CONNECTIONS BETWEEN PATTERNS

```text
Linked List (§06)  --node with 1 child-->  BINARY TREE  <--node with 2 children--
                                                  |
                 +--------------------------------+-------------------+
                 v                                v                   v
       DFS recursion (§07)                 BFS + queue (§09)     BST invariant (§14)
                 |                                |                   |
        return-info-up (heights)          level views/width      sorted inorder
        carry-down (paths)                zigzag / vertical      kth / validate
        LCA post-order                    nodes at distance K    bounds build
                 |
                 v
        Tree DP (§16 on subtrees)

Graphs (§15): tree = connected acyclic graph; tree DFS = graph DFS without visited (parent suffices)
```

**Mental map** — heights/flags up = post-order DFS · levels/views = BFS `sz` · ancestors = LCA · paths = carry+undo · rebuild = inorder split · balance = subtree summaries.

---

## 15. PROBLEM → PATTERN MAPPING

*(Reference only — solutions and approaches live in the `.cpp` files.)*

### Fundamentals & traversals
- `01-Introduction-to-Trees.cpp`
- `02-Binary-Tree-Representation.cpp`
- `03-Inorder-Traversal.cpp`
- `04-Preorder-Traversal.cpp`
- `05-Postorder-Traversal.cpp`
- `06-Level-Order-Traversal.cpp`
- `07-Pre-In-Post-in-One.cpp`
- `36-Mirror-Tree.cpp`

### DFS return-info-up (height / diameter / balanced / paths)
- `08-Maximum-Depth.cpp`
- `09-Height-Balanced-Check.cpp`
- `10-Diameter-of-Binary-Tree.cpp`
- `11-Maximum-Path-Sum.cpp`
- `12-Same-Tree.cpp`
- `19-Symmetric-Tree.cpp`
- `23-Children-Sum-Property.cpp`
- `24-Count-Complete-Nodes.cpp`
- `33-Unique-Binary-Trees.cpp`

### BFS level / views / width
- `13-Zigzag-Traversal.cpp`
- `14-Boundary-Traversal.cpp`
- `15-Vertical-Order.cpp`
- `16-Top-View.cpp`
- `17-Bottom-View.cpp`
- `18-Left-Right-View.cpp`
- `22-Maximum-Width.cpp`
- `25-Nodes-at-Distance-K.cpp`
- `26-Burn-Tree-Min-Time.cpp`

### LCA / paths
- `20-Root-to-Node-Path.cpp`
- `21-LCA-Binary-Tree.cpp`

### Advanced traversals / flattening
- `28-Morris-Inorder.cpp`
- `29-Morris-Preorder.cpp`
- `30-Flatten-to-Linked-List.cpp`
- `27-Serialize-Deserialize.cpp`

### Construction from traversals
- `31-Build-from-Pre-In.cpp`
- `32-Build-from-In-Post.cpp`
- `34-Postorder-from-In-Pre.cpp`
- `35-Tree-from-In-Level.cpp`

---

## 16. QUICK REVISION SHEET

**Concepts**
- Traversals: pre (root first), in (sorted for BST), post (children first), level (BFS `sz` boundary).
- Three recursion shapes: **info-up** (heights/flags), **carry-down** (path state + undo), **global update** (diameter).
- LCA = first node where both sides return non-null.

**Recognition clues**
| Signal | Tool |
|---|---|
| height / diameter / balanced | info-up DFS (+ global) |
| levels / views / width | BFS with `sz` |
| top/bottom view | BFS + `map<hd>` |
| ancestor / path between | LCA post-order |
| root-to-leaf with state | carry-down + pop undo |
| rebuild from traversals | inorder split + preorder root |
| O(1) space traversal | Morris |

**Formulas**
```text
height(n) = 1 + max(h(l), h(r));  diameter@n = h(l) + h(r)
balanced: |h(l) - h(r)| <= 1  (use -1 sentinel)
distance(a,b) = depth(a) + depth(b) - 2*depth(lca)
max path@n = val + max(0,l) + max(0,r)
Catalan(n) = # unique BSTs
```

**Complexity** — any traversal `O(n)` · space `O(h)` / `O(w)` BFS · Morris `O(1)` · build `O(n)` with map.

**Common mistakes** — null checks · height convention · missing global diameter update · forgotten `pop_back` · `q.size()` not snapshotted · width `long long` · traversal mix-ups in construction.

**Decision rules** — info-up? → post-order · level? → BFS · ancestor? → LCA · path? → carry+undo · rebuild? → inorder split.

---

## 17. INTERVIEW CHECKLIST

- [ ] Can I write all four traversals (recursive + at least one iterative)?
- [ ] Can I derive height+diameter in one DFS and explain the global update?
- [ ] Can I implement balanced check with the `-1` sentinel?
- [ ] Can I write LCA and handle the ancestor case?
- [ ] Can I do level order with the size boundary for views/width?
- [ ] Can I carry and *undo* path state correctly?
- [ ] Can I rebuild a tree from inorder+preorder with a value→index map?
- [ ] Can I explain Morris traversal's threading idea?
- [ ] Can I handle empty/single/skewed trees in every template?
- [ ] Can I state `O(n)` time and `O(h)`/`O(w)` space confidently?

<!-- done -->
