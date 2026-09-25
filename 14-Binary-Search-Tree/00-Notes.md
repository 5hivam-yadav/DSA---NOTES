# 14 — Binary Search Tree — Complete Pattern-Based Notes

---

## 1. Topic Overview

A **BST** is a binary tree with the ordering invariant `left < node < right` — turning search/insert/delete into `O(h)` guided walks, exactly like binary search on arrays.

**What it is**
Binary tree + global ordering: an inorder traversal yields a **sorted sequence**; at every node, everything left is smaller, everything right is larger.

**Why it is important**
- `O(log n)` average operations on dynamic ordered data (when balanced).
- The ordering invariant enables kth order statistics, validation, LCA-by-value, successor/predecessor, iterators.
- Interviews love it: validation, kth smallest, recover BST, BST-from-preorder — all test *understanding of bounds*, not memorization.

**Where it is used**
- Databases/indexes, ordered maps (std::map is a red-black BST), symbol tables.
- Sorted streaming with `lower_bound` semantics.

**How it connects to other topics**
- §13 Trees: all traversal/DFS patterns transfer.
- §04 Binary Search: BST = tree-embedded binary search; bounds logic mirrors `lo/hi`.
- §11 Heap: heap is a *different* tree invariant (parent-child order, not global).

**Interview memory hook:** *Inorder = sorted. Search/insert walks by comparison. Validation = propagate `(min, max)` bounds. Kth = inorder counter.*

---

## 2. Fundamentals

### 2.1 The invariant

```text
        8
       / \
      3   10
     / \    \
    1   6    14
       / \
      4   7

inorder: 1 3 4 6 7 8 10 14   (sorted!)
```

**Rules**
- No duplicates (or a defined policy — state it).
- The invariant is **global**: every node in the left subtree < node < every node in the right subtree — not just direct children.

### 2.2 Why operations are O(h)

```text
search(x):   at node: x < node -> go left;  x > node -> go right;  equal -> found
insert(x):   same walk; attach at the null where the walk ends
delete(x):   3 cases (below)
```

`h = O(log n)` when balanced, `O(n)` when skewed → self-balancing variants (AVL/RBT) keep `h = O(log n)` — mention in interviews.

### 2.3 Deletion — the three cases

```text
Case 1: leaf            -> just remove
Case 2: one child       -> link parent to that child
Case 3: two children    -> replace value with INORDER SUCCESSOR (smallest in right subtree)
                            then delete that successor from the right subtree
```

### 2.4 Terminology

| Term | Meaning |
|---|---|
| **Inorder successor** | Smallest value greater than node (leftmost of right subtree). |
| **Inorder predecessor** | Largest value smaller than node (rightmost of left subtree). |
| **Height h** | Longest root-to-leaf path (edges). `h = O(log n)` iff balanced. |
| **Order statistics** | Kth smallest/largest via inorder counting. |
| **Bounds `(lo, hi)`** | Valid value range a node must lie in — validation/build tool. |

---

## 3. Core Concepts

### 3.1 Search & Insert (guided walk)

**Definition** Walk down comparing `x` with the current node until found or null reached.

**Why O(h)** Each step discards an entire subtree — the tree analogue of binary search halving.

```cpp
TreeNode* searchBST(TreeNode* r, int x) {
    while (r && r->val != x) r = (x < r->val) ? r->left : r->right;
    return r;
}
```

**Insert** = search walk; attach new node where the walk hits null.

**Complexity** `O(h)` time, `O(1)` iterative / `O(h)` recursion. Balanced → `O(log n)`; skewed → `O(n)`.

**Common mistake** Inserting duplicates without a policy (usually ignore or count — state it).

---

### 3.2 Delete (three cases)

**Definition** Leaf → remove; one child → bypass; two children → swap in the **inorder successor** (leftmost of right subtree), then delete it there.

**Why successor** It's the smallest value greater than the node — placing it at the node's position preserves *both* subtree orderings.

**How it works**

```text
delete(x):
  walk to node
  if no left  -> replace with right
  else if no right -> replace with left
  else -> successor = leftmost(node.right);
          node.val = successor.val;
          delete successor from right subtree (recursive call)
```

**Common mistakes** Forgetting to relink the successor's old parent; using predecessor inconsistently; losing the subtree pointer during replacement.

---

### 3.3 Min / Max / Floor / Ceil

**Definition** Min = leftmost node; max = rightmost node. **Ceil(x)** = smallest value ≥ x; **floor(x)** = largest value ≤ x.

**Intuition** Track a "best candidate" while walking: for ceil, when `node.val ≥ x`, record candidate and go left (smaller); else go right.

**Complexity** `O(h)`.

---

### 3.4 Kth smallest / largest (order statistics)

**Definition** Kth smallest = kth node in **inorder** (sorted) sequence; kth largest = kth in reverse inorder.

**How it works** Inorder traversal with a counter; when counter hits k, record/short-circuit.

**Complexity** `O(h + k)` best (early stop), `O(n)` worst; augmenting each node with subtree sizes gives `O(h)` per query (order-statistic tree — advanced).

---

### 3.5 Validation (bounds propagation)

**Definition** BST valid iff every node lies within `(min, max)` inherited from its ancestors.

**Key insight** Direct-parent comparison is NOT enough (grandparent constraints matter) — pass bounds down:

```cpp
bool valid(TreeNode* r, long long lo, long long hi) {
    return !r || (r->val > lo && r->val < hi
               && valid(r->left, lo, r->val)
               && valid(r->right, r->val, hi));
}
// call: valid(root, LLONG_MIN, LLONG_MAX)
```

**Alternative** Inorder must be strictly increasing — compare with `prev` during traversal.

**Common mistake** Using `int` bounds (`INT_MIN/INT_MAX` break when node value equals them) → `long long`.

---

### 3.6 LCA in BST (value compare)

**Definition** First node where `p` and `q` diverge — found by value comparison without child checks.

**Algorithm** While true: if both values < node → go left; both > node → go right; else current node is LCA.

**Complexity** `O(h)` — better than general-tree LCA `O(n)`.

---

### 3.7 Successor / Predecessor (iterator state)

**Definition** **Successor of x** (may not be in tree): smallest value > x → leftmost node of the subtree *right of x*; if no right child → nearest ancestor where you came from a left child. **Predecessor**: mirror.

**BST Iterator** Maintain a stack of the leftmost path (the "unfinished" traversals): `next()` pops, then pushes the entire left spine of the popped node's right child → amortized `O(1)` per call, `O(h)` space.

**Complexity** `O(h)` per query; iterator amortized `O(1)`.

---

## 4. PATTERN LIBRARY

### P1 — Guided Walk (search / insert / min / max / floor / ceil)

#### What is the pattern?
A single downward walk where each comparison discards a subtree.

#### When should I recognize it?
- "Search in BST", "insert into BST", "find min/max", "floor/ceil of x", "check membership".

#### Core intuition
The BST invariant answers "left or right?" at every node — the tree version of `lo/hi` binary search.

#### Generic algorithm
```text
search:   while r && r->val != x: r = (x < r->val) ? left : right
insert:   walk like search; remember parent; attach new node at null
ceil(x):  when r->val >= x: candidate = r->val; go left; else go right
min:      go left until null;  max: go right until null
```

#### C++ template
```cpp
TreeNode* searchBST(TreeNode* r, int x) {
    while (r && r->val != x) r = (x < r->val) ? r->left : r->right;
    return r;
}
int ceilBST(TreeNode* r, int x) {
    int c = -1;
    while (r) { if (r->val >= x) { c = r->val; r = r->left; } else r = r->right; }
    return c;
}
```

#### Time / Space
`O(h)` / `O(1)` iterative.

#### Edge cases
Empty tree; all left/right (skewed); x smaller/larger than everything (ceil/floor = -1 / max).

#### Common mistakes
Using `>=` vs `>` (equality semantics); inserting duplicates without a stated policy.

#### Variations
Iterative vs recursive; parent-pointer variants.

#### Practice mapping
- `01-Search-in-BST.cpp`, `02-Find-Min-Max.cpp`, `03-Insert-into-BST.cpp`, `16-Ceil-and-Floor.cpp`

---

### P2 — Inorder = Sorted (kth, validation, recover, two-sum, iterator)

#### What is the pattern?
Leverage "inorder traversal of a BST is sorted" — one inorder pass answers order-statistic and sortedness questions.

#### When should I recognize it?
- "Kth smallest/largest", "validate BST", "recover swapped nodes", "two sum in BST", "merge two BSTs", "BST iterator".

#### Core intuition
Sortedness is *defined* by inorder — if inorder isn't strictly increasing, the tree isn't a BST; the kth visit is the kth smallest.

#### Generic algorithm
1. Inorder with early stop at k (kth).
2. Track `prev` — first decrease = one of the swapped pair; fix with the other found similarly (recover).
3. Two pointers from both ends of the sorted sequence (iterator pair for two-sum).

#### C++ template
```cpp
void kth(TreeNode* r, int& k, int& ans) {
    if (!r || k <= 0) return;
    kth(r->left, k, ans);
    if (--k == 0) { ans = r->val; return; }
    kth(r->right, k, ans);
}
```

#### Time / Space
`O(h + k)` (early stop), `O(n)` full pass; `O(h)` space.

#### Edge cases
k out of range; single node; duplicates (recovery assumes unique values).

#### Common mistakes
Not stopping recursion after finding k (minor); forgetting that *both* swapped nodes must be recorded in the right order (first = larger than successor, second = smaller than predecessor).

#### Variations
Validation via bounds (§3.5) or via inorder `prev`; iterator = stack of left spines.

#### Practice mapping
- `05-Kth-Smallest.cpp`, `06-Kth-Largest.cpp`, `07-Validate-BST.cpp`, `13-Recover-BST.cpp`, `12-Two-Sum-in-BST.cpp`, `11-BST-Iterator.cpp`, `15-Merge-Two-BSTs.cpp`

---

### P3 — Bounds Recursion (validate / build from preorder / largest BST)

#### What is the pattern?
Pass a valid value range `(lo, hi)` (or an index range) down the recursion; the current node must fit, and it *tightens* the bounds for children.

#### When should I recognize it?
- "Validate BST", "construct BST from preorder", "count BSTs from values", "largest BST subtree".

#### Core intuition
The BST rule is a **constraint inheritance**: left subtree inherits `(lo, node.val)`, right inherits `(node.val, hi)` — violating any inherited bound breaks global order.

#### Generic algorithm
```text
validate:  node fits in (lo, hi)? recurse left (lo, node) and right (node, hi)
build:     bounds also restrict WHICH preorder values belong to this subtree
           (values < lo or > hi stop the subtree)
```

#### C++ template
```cpp
bool valid(TreeNode* r, long long lo, long long hi) {
    return !r || (r->val > lo && r->val < hi
               && valid(r->left, lo, r->val)
               && valid(r->right, r->val, hi));
}
```

#### Time / Space
`O(n)` / `O(h)`.

#### Edge cases
Values equal to `INT_MIN/MAX` → `long long` bounds; empty tree (valid); skewed structures.

#### Common mistakes
Checking only parent-child (misses ancestor constraints); `int` bounds; wrong strictness on duplicates.

#### Variations
Largest BST subtree returns `(isBST, min, max, size)` per node — a multi-value return type.

#### Practice mapping
- `07-Validate-BST.cpp`, `09-Build-BST-from-Preorder.cpp`, `14-Largest-BST-Subtree.cpp`

---

### P4 — Delete (three-case surgery)

#### What is the pattern?
Locate node; apply leaf / one-child / two-child (successor swap) surgery.

#### When should I recognize it?
- "Delete a node in BST" — any removal preserving the invariant.

#### Core intuition
Only the two-children case is interesting: replace the value with the inorder successor (min of right subtree), then delete *that* node — a problem that now has ≤1 child.

#### Generic algorithm
```text
if !left: return right
if !right: return left
succ = min(node.right)
node.val = succ.val
node.right = deleteNode(node.right, succ.val)
```

#### C++ template
```cpp
TreeNode* deleteNode(TreeNode* r, int key) {
    if (!r) return nullptr;
    if (key < r->val)      r->left = deleteNode(r->left, key);
    else if (key > r->val) r->right = deleteNode(r->right, key);
    else {
        if (!r->left)  return r->right;
        if (!r->right) return r->left;
        TreeNode* succ = r->right;
        while (succ->left) succ = succ->left;
        r->val = succ->val;
        r->right = deleteNode(r->right, succ->val);
    }
    return r;
}
```

#### Time / Space
`O(h)` / `O(h)` recursion.

#### Edge cases
Key absent (no change); root deleted; successor is the direct right child (no left — handled by `while`); duplicates policy.

#### Common mistakes
Copying successor value but forgetting to remove the successor node (duplicate created); using predecessor inconsistently.

#### Variations
Predecessor swap (leftmost of left subtree) equally valid; iterative deletion with parent pointers.

#### Practice mapping
- `04-Delete-Node-in-BST.cpp`

---

### P5 — Successor / Predecessor & Iterator (inorder positions)

#### What is the pattern?
Find the next/previous value in sorted order using subtree structure + ancestor routing; iterator packages this as a reusable API.

#### When should I recognize it?
- "Inorder successor of a node", "inorder predecessor", "BST iterator (next/hasNext)", "k-th next element".

#### Core intuition
- Has right child → successor = leftmost of right subtree.
- Else → go up until you arrive from a *left* link (the ancestor you were smaller than).
- Iterator pre-computes "left spines" so `next()` is amortized `O(1)`.

#### Generic algorithm (iterator)
```text
pushLeft(node):  while node: stack.push(node), node = node.left
next():          n = stack.pop(); pushLeft(n.right); return n.val
hasNext():       !stack.empty()
```

#### C++ template
```cpp
struct BSTIter {
    stack<TreeNode*> st;
    BSTIter(TreeNode* r) { pushLeft(r); }
    void pushLeft(TreeNode* n) { while (n) { st.push(n); n = n->left; } }
    int next() { TreeNode* n = st.top(); st.pop(); pushLeft(n.right); return n->val; }
    bool hasNext() { return !st.empty(); }
};
```

#### Time / Space
`O(1)` amortized per `next` (each node pushed/popped once overall), `O(h)` space.

#### Edge cases
End of iteration (`hasNext` false before `pop`); successor of max element (none); successor node given (not search value).

#### Common mistakes
Forgetting `pushLeft(n.right)` after pop (skips the right subtree); confusing "successor of value" vs "successor of node".

#### Variations
Morris threaded traversal computes successor links in `O(1)` space — advanced.

#### Practice mapping
- `10-Inorder-Successor-Predecessor.cpp`, `11-BST-Iterator.cpp`

---

### P6 — Merge / Combine Two BSTs

#### What is the pattern?
Extract sorted sequences (inorder) and merge (§06 P4), or insert one tree's nodes into the other.

#### When should I recognize it?
- "Merge two BSTs into a balanced BST", "two-sum using both BSTs", "kth smallest across two BSTs".

#### Core intuition
Both trees yield sorted inorder streams → merging is the classic linear merge; if you need a *balanced output tree*, build from the merged sorted array (`O(n)` mid-split build).

#### Generic algorithm
1. Inorder both (or use two iterators — P5).
2. Two-pointer merge → sorted array (or direct output).
3. Optional: build balanced BST from sorted array via mid-recursion.

#### C++ template
```cpp
TreeNode* buildBalanced(vector<int>& v, int lo, int hi) {
    if (lo > hi) return nullptr;
    int mid = lo + (hi - lo) / 2;
    TreeNode* r = new TreeNode(v[mid]);
    r->left = buildBalanced(v, lo, mid - 1);
    r->right = buildBalanced(v, mid + 1, hi);
    return r;
}
```

#### Time / Space
`O(n + m)` merge (+ `O(n + m)` build); space `O(n + m)` — or in-place merging advanced (`O(1)` extra).

#### Edge cases
One tree empty; duplicates across trees (spec: unique combined?); skewed inputs.

#### Common mistakes
Naively inserting all nodes of B into A (`O(m·h)` — may be fine, but state complexity); output not balanced (violates "balanced BST" requirement).

#### Variations
Balanced-from-sorted build is also the standard "convert sorted array/list to BST" problem.

#### Practice mapping
- `15-Merge-Two-BSTs.cpp`, `12-Two-Sum-in-BST.cpp`

---

## 5. PATTERN RECOGNITION

| If the problem says... | Think about... |
|---|---|
| "search / insert in BST" | guided walk (P1) |
| "find min / max / floor / ceil" | walk to extreme + candidate (P1) |
| "kth smallest / largest" | inorder with counter (P2) |
| "validate BST" | bounds propagation or inorder-prev (P3/P2) |
| "recover two swapped nodes" | inorder anomalies (P2) |
| "two sum in BST" | two sorted iterators (P2) |
| "merge two BSTs" | inorder + merge / balanced build (P6) |
| "delete node in BST" | three-case surgery (P4) |
| "successor / predecessor / iterator" | leftmost + ancestor routing (P5) |
| "build BST from preorder" | bounds recursion (P3) |
| "largest BST subtree" | subtree summary (min,max,size,isBST) (P3) |
| "inorder is sorted?" | that IS the BST invariant (P2) |

**Decision rules**
1. Ordering question (kth, sorted, next) → **inorder**.
2. Validity/construction → **`(lo, hi)` bounds recursion**.
3. Structural change → **delete surgery / rebuild balanced**.
4. Complexity question → always answer in terms of **h**, then note balanced ⇒ `log n`.

---

## 6. BRUTE → BETTER → OPTIMAL THINKING

### Search in BST
- **Brute** — linear scan (BFS all nodes): `O(n)` — wastes the invariant.
- **Better** — recursive guided walk: `O(h)`.
- **Optimal** — iterative guided walk: `O(h)` time, `O(1)` space. Note: `O(h)` is the *hard lower bound* for this structure; balancing (AVL/RBT) is how you force `h = O(log n)`.

### Validate BST
- **Brute** — for each node, verify all left-subtree values < node < all right values: `O(n²)`.
- **Better** — one inorder pass, check strictly increasing: `O(n)`.
- **Optimal** — bounds propagation with `long long`: `O(n)`, `O(h)` — equivalent complexity, but *works for early exit* and is the template that extends to "build from preorder".

### Kth smallest
- **Brute** — inorder collect all, index: `O(n)` time + `O(n)` space.
- **Better** — inorder with early stop: `O(h + k)` time, `O(h)` space.
- **Optimal** — augment nodes with subtree sizes: `O(h)` per query, `O(1)` after — (order-statistic tree; only if asked).

### Two sum in BST
- **Brute** — inorder to array + two pointers: `O(n)` time, `O(n)` space.
- **Better** — two stacks (iterators) from both ends: `O(n)` time, `O(h)` space.
- **Optimal** — same iterator pair: the `O(h)` space is essentially required without augmentation — this *is* optimal for the comparison model.

### Delete in BST
- **Brute** — rebuild the whole tree without the key (`O(n)` collect + `O(n)` build): correct but destructive/heavy.
- **Better** — three-case surgery: `O(h)`.
- **Optimal** — same `O(h)`; successor *or* predecessor both valid. State why the successor preserves order.

### Build balanced BST from sorted array
- **Brute** — insert sequentially: `O(n log n)` and possibly unbalanced output... actually sorted insert → skewed `O(n²)`.
- **Better** — insert with mid-first order: `O(n)`.
- **Optimal** — mid-recursion: `O(n)` time, `O(log n)` stack — the standard answer.

### Key transferable idea
> Every BST question asks one of two things: *"use the sorted order"* (inorder) or *"use the bounds"* (lo/hi recursion). Identify which — the rest is mechanics.

---

## 7. C++ / STL TOOLKIT

| Tool | Syntax | Use |
|---|---|---|
| Guided walk | `while (r && r->val != x) r = ...` | search/insert/ceil |
| Inorder + stack | classic iterative inorder | sorted sequence |
| Iterator stack | `stack<TreeNode*>` + `pushLeft` | next/hasNext |
| Bounds | `long long lo, hi` params | validation/build |
| Value→index map | `unordered_map<int,int>` | fast inorder position |
| Collect + sort | inorder into vector | merge / two pointers |

```cpp
// iterative inorder (sorted output)
stack<TreeNode*> st; TreeNode* cur = root;
while (cur || !st.empty()) {
    while (cur) { st.push(cur); cur = cur->left; }
    cur = st.top(); st.pop();
    /* visit cur->val */
    cur = cur->right;
}

// bounds validation
bool ok(TreeNode* r, long long lo, long long hi) {
    return !r || (r->val > lo && r->val < hi
               && ok(r->left, lo, r->val) && ok(r->right, r->val, hi));
}
```

**Common mistakes**
- `int` bounds (use `long long`).
- Forgetting `cur = cur->right` after pop.
- Mixing successor-of-node vs successor-of-value.

---

## 8. COMPLEXITY GUIDE

| Operation | Time | Space |
|---|---:|---:|
| Search / insert / ceil / floor | `O(h)` | `O(1)` iter / `O(h)` rec |
| Delete | `O(h)` | `O(h)` |
| Min / max | `O(h)` | `O(1)` |
| Kth smallest | `O(h + k)` | `O(h)` |
| Validate (bounds) | `O(n)` | `O(h)` |
| LCA in BST | `O(h)` | `O(1)` |
| Iterator (all n) | `O(n)` total (amortized `O(1)`/next) | `O(h)` |
| Build balanced from sorted | `O(n)` | `O(log n)` |
| Merge two BSTs | `O(n + m)` | `O(n + m)` |
| Sorted-insert n items (skewed worst) | `O(n²)` | `O(1)` |

**How to estimate** — everything is `O(h)`; substitute `h = log n` (balanced) or `n` (skewed). State both in interviews; mention self-balancing trees as the fix.

---

## 9. EDGE CASES

- **Empty tree** — search returns null; min/max undefined per spec; kth invalid; validate → true.
- **Single node** — kth 1 = it; successor none; delete → empty.
- **All values equal to INT_MIN / INT_MAX** — `long long` bounds required.
- **Duplicates** — validation strictness (`<` vs `<=`) and delete policy must be stated.
- **Key not present (delete)** — no change.
- **Successor of max** — none (null / sentinel per spec).
- **k out of range** — return −1 / throw per spec.
- **Skewed tree from sorted input** — `O(n)` height; recursion may overflow for `n ~ 10^5`.
- **Iterator exhausted** — check `hasNext()` before `next()`.
- **Recover BST with only one anomaly visible** — must track *first* and *second* violation (second may appear adjacent or far depending on swap positions).

---

## 10. COMMON MISTAKES

| # | Mistake | What goes wrong | Why | How to avoid |
|---|---|---|---|---|
| 1 | Parent-only comparison for validation | false positives | ancestor constraints missed | propagate `(lo, hi)` bounds |
| 2 | `int` bounds in validation | wrong at INT_MIN/MAX | sentinel collision | `long long lo, hi` |
| 3 | Deleting 2-child node without removing successor | duplicate value | value copied but node kept | `node.right = delete(node.right, succ)` |
| 4 | Forgetting `pushLeft(right)` in iterator | skips subtrees | incomplete inorder | push left spine after every pop |
| 5 | Using `>` vs `>=` inconsistently (ceil/floor) | off-by-one answers | equality semantics | define ceil ≥, floor ≤; write test |
| 6 | Duplicates policy unstated | ambiguous insert/search | strict BST assumed | document: ignore or count |
| 7 | Assuming `O(log n)` always | wrong complexity claim | BSTs can be `O(n)` | answer in `O(h)`; note balance |
| 8 | Sorted insert into BST → skew | worst-case chain | no balancing | mention AVL/RBT; or build balanced |
| 9 | Inorder `prev` not updated in validate | no detection | stale prev | update `prev = node` each visit |
| 10 | Recover: expecting both anomalies adjacent | missed second swap | swaps can be far | keep `first` and `second` markers |

**Conceptual mistakes**
- Confusing **search value x** with **given node** for successor (different walk).
- Forgetting inorder is *strictly* increasing (equality = duplicate policy question).

---

## 11. IMPORTANT FORMULAS / RULES

```text
Invariant:   for every node: all in left subtree < node < all in right subtree
Inorder      -> sorted ascending          (reverse inorder -> descending)
Complexity:  O(h);  balanced h = ceil(log2(n+1)) - 1;  skewed h = n
Delete 2-ch: replace with inorder successor (min of right) OR predecessor (max of left)
ceil(x):     last node with val >= x along the walk (go left on >=)
floor(x):    last node with val <= x along the walk (go right on <=)
kth smallest -> kth in inorder;  kth largest -> (n-k+1)th inorder / reverse
LCA BST:     first node with values on both sides (or equal to one)
Build from sorted: mid = (lo+hi)/2 -> balanced h = O(log n)
Catalan(n):  # structurally unique BSTs = C(2n, n) / (n+1)
```

**Decision rules**
1. Sorted-order question → inorder. 2. Validity/construction → bounds. 3. Surgery → 3-case delete. 4. Always state complexity as `O(h)`.

---

## 12. REUSABLE TEMPLATES

```cpp
// 1. Search (iterative)
TreeNode* searchBST(TreeNode* r, int x) {
    while (r && r->val != x) r = (x < r->val) ? r->left : r->right;
    return r;
}

// 2. Validate with bounds
bool valid(TreeNode* r, long long lo, long long hi) {
    return !r || (r->val > lo && r->val < hi
               && valid(r->left, lo, r->val)
               && valid(r->right, r->val, hi));
}

// 3. Ceil / Floor
int ceilBST(TreeNode* r, int x) {
    int c = -1;
    while (r) { if (r->val >= x) { c = r->val; r = r->left; } else r = r->right; }
    return c;
}
int floorBST(TreeNode* r, int x) {
    int f = -1;
    while (r) { if (r->val <= x) { f = r->val; r = r->right; } else r = r->left; }
    return f;
}

// 4. Kth smallest (inorder, early stop)
void kth(TreeNode* r, int& k, int& ans) {
    if (!r || k <= 0) return;
    kth(r->left, k, ans);
    if (--k == 0) { ans = r->val; return; }
    kth(r->right, k, ans);
}

// 5. Delete
TreeNode* deleteNode(TreeNode* r, int key) {
    if (!r) return nullptr;
    if (key < r->val)      r->left = deleteNode(r->left, key);
    else if (key > r->val) r->right = deleteNode(r->right, key);
    else {
        if (!r->left)  return r->right;
        if (!r->right) return r->left;
        TreeNode* s = r->right;
        while (s->left) s = s->left;
        r->val = s->val;
        r->right = deleteNode(r->right, s->val);
    }
    return r;
}
```

## 13. ADVANCED CONCEPTS

### 13.1 Order-statistic augmentation
Store `size` in each node: kth query = walk left/right by comparing `k` with left subtree size → `O(h)` regardless of k; also enables "index of value x" and rank queries. The basis of policy-based data structures (`ordered_set`).

### 13.2 Self-balancing trees (AVL / Red-Black)
Rotations restore `|lh − rh| ≤ 1` (AVL) or color constraints (RB) after insert/delete → `h = O(log n)` guaranteed. Mention by name in interviews; implementing rotations is rarely required.

### 13.3 Treap / Splay (randomized balancing)
Treap = BST key + heap priority (random) → expected `O(log n)` with simple code; splay moves accessed nodes to root (amortized). Competition tools; recognize the names.

### 13.4 Split / Merge on BST
Treap-style `split(root, key)` and `merge(a, b)` implement insert/delete/range queries in `O(log n)` — advanced (order-statistic tree operations without augmentation).

### 13.5 Interval trees / augmented ranges
Storing `max end in subtree` in a BST enables interval stabbing queries — advanced; know that BSTs can carry *aggregates*, not just values.

### 13.6 Cartesian tree
From a sequence: parent = nearest greater (or smaller) element — built in `O(n)` with a monotonic stack (§09). Connects arrays ↔ trees; used in RMQ.

---

## 14. CONNECTIONS BETWEEN PATTERNS

```text
Binary Tree (§13)
      |
      |  + ordering invariant (left < node < right)
      v
    BINARY SEARCH TREE
      |
      +--> guided walk = binary search on structure (§04 analogy: lo/hi -> lo/hi bounds)
      |
      +--> inorder = sorted  -->  kth / validate / recover / two-sum / merge
      |
      +--> bounds recursion -->  validate / build from preorder
      |
      +--> successor/iterator-->  amortized O(1) next (stack = pending inorder)
      |
      +--> balance (AVL/RBT) -->  guaranteed O(log n)
      |
      +--> augment (sizes)   -->  order-statistics / rank

Heap (§11): different invariant — parent-child only, no inorder sortedness.
```

**Mental map** — 1. Sorted-order question → inorder. 2. Validity/construction → bounds. 3. Surgery → 3-case delete. 4. Next/iterate → left-spine stack. 5. Always say `O(h)`.

---

## 15. PROBLEM → PATTERN MAPPING

*(Reference only — solutions and approaches live in the `.cpp` files.)*

### Guided walk (search / insert / min-max / ceil-floor)
- `01-Search-in-BST.cpp`
- `02-Find-Min-Max.cpp`
- `03-Insert-into-BST.cpp`
- `16-Ceil-and-Floor.cpp`

### Inorder = sorted (kth / validate / recover / two-sum / iterator)
- `05-Kth-Smallest.cpp`
- `06-Kth-Largest.cpp`
- `07-Validate-BST.cpp`
- `13-Recover-BST.cpp`
- `12-Two-Sum-in-BST.cpp`
- `11-BST-Iterator.cpp`
- `10-Inorder-Successor-Predecessor.cpp`

### Bounds recursion (validate / build / largest)
- `09-Build-BST-from-Preorder.cpp`
- `14-Largest-BST-Subtree.cpp`
- `07-Validate-BST.cpp`

### Delete surgery
- `04-Delete-Node-in-BST.cpp`

### LCA by value
- `08-LCA-in-BST.cpp`

### Merge / combine
- `15-Merge-Two-BSTs.cpp`

---

## 16. QUICK REVISION SHEET

**Concepts**
- Invariant: all-left < node < all-right (global, not just direct children).
- Everything is `O(h)`; balanced → `O(log n)`, skewed → `O(n)`.
- Inorder = sorted → kth, validate, recover, two-sum, merge.
- Validation = `(lo, hi)` bounds recursion with `long long`.
- Delete: leaf / one-child / two-child (successor swap + recursive delete).

**Recognition clues**
| Signal | Tool |
|---|---|
| search/insert/min/max/ceil/floor | guided walk |
| kth / sorted / next | inorder |
| validate / build from preorder | bounds recursion |
| delete | 3-case surgery |
| successor / iterator | leftmost + ancestor route |
| merge two BSTs | inorder + merge + balanced build |

**Formulas**
```text
ceil: go left when val >= x (record);  floor: go right when val <= x
kth smallest = kth inorder visit
delete 2-child: successor = leftmost(node.right)
build balanced: mid = (lo+hi)/2  =>  h = O(log n)
Catalan(n) = # structurally unique BSTs
```

**Complexity** — walk/delete `O(h)` · validate `O(n)` · iterator amortized `O(1)`/next · merge `O(n+m)`.

**Common mistakes** — parent-only validation · `int` bounds · successor not unlinked · iterator missing `pushLeft(right)` · duplicates policy · claiming `O(log n)` unconditionally.

**Decision rules** — sorted-order → inorder · validity/construction → bounds · surgery → 3 cases · always answer `O(h)`.

---

## 17. INTERVIEW CHECKLIST

- [ ] Can I write search/insert iteratively without thinking?
- [ ] Can I validate with `long long` bounds and explain why parent-only fails?
- [ ] Can I execute all three delete cases correctly?
- [ ] Can I find kth smallest with early-stop inorder?
- [ ] Can I write ceil/floor with correct `>=`/`<=` directions?
- [ ] Can I derive BST LCA via value comparison?
- [ ] Can I build the iterator with left-spine stack and amortized `O(1)`?
- [ ] Can I recover a BST by tracking both inorder anomalies?
- [ ] Can I merge two BSTs into a *balanced* output?
- [ ] Can I state `O(h)` and discuss self-balancing as the follow-up?

<!-- done -->
