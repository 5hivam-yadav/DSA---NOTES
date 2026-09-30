# Binary Search Tree — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — Guided Walk (search / insert / min / max / floor / ceil)

**What is the pattern?**

A single downward walk where each comparison discards a subtree.

**When should I recognize it?**

- "Search in BST", "insert into BST", "find min/max", "floor/ceil of x", "check membership".

**Core intuition**

The BST invariant answers "left or right?" at every node — the tree version of `lo/hi` binary search.

**Generic algorithm**

```text
search:   while r && r->val != x: r = (x < r->val) ? left : right
insert:   walk like search; remember parent; attach new node at null
ceil(x):  when r->val >= x: candidate = r->val; go left; else go right
min:      go left until null;  max: go right until null
```

**Time / Space**

`O(h)` / `O(1)` iterative.

**Edge cases**

Empty tree; all left/right (skewed); x smaller/larger than everything (ceil/floor = -1 / max).

**Common mistakes**

Using `>=` vs `>` (equality semantics); inserting duplicates without a stated policy.

**Variations**

Iterative vs recursive; parent-pointer variants.

### P2 — Inorder = Sorted (kth, validation, recover, two-sum, iterator)

**What is the pattern?**

Leverage "inorder traversal of a BST is sorted" — one inorder pass answers order-statistic and sortedness questions.

**When should I recognize it?**

- "Kth smallest/largest", "validate BST", "recover swapped nodes", "two sum in BST", "merge two BSTs", "BST iterator".

**Core intuition**

Sortedness is *defined* by inorder — if inorder isn't strictly increasing, the tree isn't a BST; the kth visit is the kth smallest.

**Generic algorithm**

1. Inorder with early stop at k (kth).
2. Track `prev` — first decrease = one of the swapped pair; fix with the other found similarly (recover).
3. Two pointers from both ends of the sorted sequence (iterator pair for two-sum).

**Time / Space**

`O(h + k)` (early stop), `O(n)` full pass; `O(h)` space.

**Edge cases**

k out of range; single node; duplicates (recovery assumes unique values).

**Common mistakes**

Not stopping recursion after finding k (minor); forgetting that *both* swapped nodes must be recorded in the right order (first = larger than successor, second = smaller than predecessor).

**Variations**

Validation via bounds (§3.5) or via inorder `prev`; iterator = stack of left spines.

### P3 — Bounds Recursion (validate / build from preorder / largest BST)

**What is the pattern?**

Pass a valid value range `(lo, hi)` (or an index range) down the recursion; the current node must fit, and it *tightens* the bounds for children.

**When should I recognize it?**

- "Validate BST", "construct BST from preorder", "count BSTs from values", "largest BST subtree".

**Core intuition**

The BST rule is a **constraint inheritance**: left subtree inherits `(lo, node.val)`, right inherits `(node.val, hi)` — violating any inherited bound breaks global order.

**Generic algorithm**

```text
validate:  node fits in (lo, hi)? recurse left (lo, node) and right (node, hi)
build:     bounds also restrict WHICH preorder values belong to this subtree
           (values < lo or > hi stop the subtree)
```

**Time / Space**

`O(n)` / `O(h)`.

**Edge cases**

Values equal to `INT_MIN/MAX` → `long long` bounds; empty tree (valid); skewed structures.

**Common mistakes**

Checking only parent-child (misses ancestor constraints); `int` bounds; wrong strictness on duplicates.

**Variations**

Largest BST subtree returns `(isBST, min, max, size)` per node — a multi-value return type.

### P4 — Delete (three-case surgery)

**What is the pattern?**

Locate node; apply leaf / one-child / two-child (successor swap) surgery.

**When should I recognize it?**

- "Delete a node in BST" — any removal preserving the invariant.

**Core intuition**

Only the two-children case is interesting: replace the value with the inorder successor (min of right subtree), then delete *that* node — a problem that now has ≤1 child.

**Generic algorithm**

```text
if !left: return right
if !right: return left
succ = min(node.right)
node.val = succ.val
node.right = deleteNode(node.right, succ.val)
```

**Time / Space**

`O(h)` / `O(h)` recursion.

**Edge cases**

Key absent (no change); root deleted; successor is the direct right child (no left — handled by `while`); duplicates policy.

**Common mistakes**

Copying successor value but forgetting to remove the successor node (duplicate created); using predecessor inconsistently.

**Variations**

Predecessor swap (leftmost of left subtree) equally valid; iterative deletion with parent pointers.

### P5 — Successor / Predecessor & Iterator (inorder positions)

**What is the pattern?**

Find the next/previous value in sorted order using subtree structure + ancestor routing; iterator packages this as a reusable API.

**When should I recognize it?**

- "Inorder successor of a node", "inorder predecessor", "BST iterator (next/hasNext)", "k-th next element".

**Core intuition**

- Has right child → successor = leftmost of right subtree.
- Else → go up until you arrive from a *left* link (the ancestor you were smaller than).
- Iterator pre-computes "left spines" so `next()` is amortized `O(1)`.

**Generic algorithm (iterator)**

```text
pushLeft(node):  while node: stack.push(node), node = node.left
next():          n = stack.pop(); pushLeft(n.right); return n.val
hasNext():       !stack.empty()
```

**Time / Space**

`O(1)` amortized per `next` (each node pushed/popped once overall), `O(h)` space.

**Edge cases**

End of iteration (`hasNext` false before `pop`); successor of max element (none); successor node given (not search value).

**Common mistakes**

Forgetting `pushLeft(n.right)` after pop (skips the right subtree); confusing "successor of value" vs "successor of node".

**Variations**

Morris threaded traversal computes successor links in `O(1)` space — advanced.

### P6 — Merge / Combine Two BSTs

**What is the pattern?**

Extract sorted sequences (inorder) and merge (§06 P4), or insert one tree's nodes into the other.

**When should I recognize it?**

- "Merge two BSTs into a balanced BST", "two-sum using both BSTs", "kth smallest across two BSTs".

**Core intuition**

Both trees yield sorted inorder streams → merging is the classic linear merge; if you need a *balanced output tree*, build from the merged sorted array (`O(n)` mid-split build).

**Generic algorithm**

1. Inorder both (or use two iterators — P5).
2. Two-pointer merge → sorted array (or direct output).
3. Optional: build balanced BST from sorted array via mid-recursion.

**Time / Space**

`O(n + m)` merge (+ `O(n + m)` build); space `O(n + m)` — or in-place merging advanced (`O(1)` extra).

**Edge cases**

One tree empty; duplicates across trees (spec: unique combined?); skewed inputs.

**Common mistakes**

Naively inserting all nodes of B into A (`O(m·h)` — may be fine, but state complexity); output not balanced (violates "balanced BST" requirement).

**Variations**

Balanced-from-sorted build is also the standard "convert sorted array/list to BST" problem.

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
