# Linked List — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — Dummy Node Splice (Insert / Delete / Merge)

**What is the pattern?**

Place a temporary `dummy` node before the head so every node — including the first — has a `prev`.

**When should I recognize it?**

- "Delete a node / remove nth from end / remove all occurrences", "merge two lists", "insert into sorted list", any operation that may change `head`.

**Core intuition**

Most linked-list bugs are "who is `prev` when we delete the head?" A dummy makes the answer uniform: `prev` always exists.

**General approach**

1. `dummy.next = head; prev = &dummy`.
2. Advance `prev` to the position *before* the action point.
3. Relink (`prev->next = ...`).
4. Return `dummy.next`.

**Time / Space**

`O(n)` time (one/two passes), `O(1)` space.

**Edge cases**

Empty list; delete the head; delete the tail; `n == length`.

**Common mistakes**

Returning `dummy` instead of `dummy.next`; off-by-one in the fast-lead distance.

**Variations**

Merge two sorted (attach smaller); remove all occurrences (keep deleting while match).

### P2 — Fast / Slow Pointers (Middle, Cycle, Entry)

**What is the pattern?**

Two walkers, speed 1 vs 2, from the same start.

**When should I recognize it?**

- "Middle of the list", "does the list have a cycle", "start of the cycle", "palindrome list", "reorder list".

**Core intuition**

Speed ratio 2:1 means fast advances exactly one extra node per slow step → in a cycle the gap shrinks by 1 each step → meet. In a chain, fast at end ⇒ slow at middle.

**General approach**

1. `while (f && f->next)`: `s = s->next; f = f->next->next`.
2. Meeting ⇒ cycle; no meeting ⇒ no cycle; when `f` ends ⇒ `s` is middle.
3. Cycle entry: reset `s = head`, step both by 1 until equal.

**Time / Space**

`O(n)` / `O(1)`.

**Edge cases**

Empty / single-node list; cycle at head; even vs odd length (middle convention).

**Common mistakes**

Missing `f->next` null check; resetting the wrong pointer for entry detection.

**Variations**

Cycle length (count from meeting); palindrome check (find middle, reverse second half, compare).

### P3 — In-Place Reverse (prev / curr / next)

**What is the pattern?**

Three pointers walk the list flipping `next` links one at a time.

**When should I recognize it?**

- "Reverse the linked list", "reverse in groups of k", "reverse part of a list", "reorder list".

**Core intuition**

Before flipping `curr->next`, the rest of the list must be saved in a third pointer — `prev` alone loses it.

**General approach**

1. `prev = nullptr, curr = head`.
2. `next = curr->next; curr->next = prev; prev = curr; curr = next`.
3. Final answer is `prev`.

**Time / Space**

`O(n)` / `O(1)` iterative; recursion is `O(n)` stack.

**Edge cases**

Empty list; single node; already-reversed input.

**Common mistakes**

Losing `nxt` before relinking; returning `h` (now the tail) instead of `prev`.

**Variations**

K-group (reverse each chunk, stitch tails); recursive reversal; doubly linked (swap both pointers).

### P4 — Merge-Based Patterns (two-way, K-way, sort-by-merge)

**What is the pattern?**

Repeatedly attach the smallest head of sorted streams — linear merge of two, heap/divide of K.

**When should I recognize it?**

- "Merge two sorted lists", "merge K sorted lists", "sort a linked list", "sort 0/1/2 in one pass", "add two numbers as digit chains".

**Core intuition**

Sorted streams can be interleaved in total-linear time because the next smallest element is always at one of the heads.

**General approach**

1. Dummy head.
2. `while (a && b): attach smaller, advance it`.
3. Attach remainder.
4. For K lists: min-heap of heads (`O(N log K)`) or pairwise divide-and-conquer.

**Time / Space**

Two-way `O(n + m)` / `O(1)`; K-way heap `O(N log K)` / `O(K)`; pairwise merge `O(N log K)` / `O(log K)` recursion.

**Edge cases**

One list empty; equal elements (stability: prefer `<=`); K = 0.

**Common mistakes**

Losing the remainder list; unstable comparisons breaking equal-value order; pushing all nodes of a list into the heap instead of heads.

**Variations**

Three-way partition of 0/1/2 (Dutch flag on list); merge into sorted via repeated merge.

### P5 — Arithmetic on Digit Chains

**What is the pattern?**

Walk two lists in lockstep while carrying `carry`, appending `sum % 10` nodes.

**When should I recognize it?**

- "Add two numbers", "add 1 to a number represented as list", "multiply as list", "reverse digits".

**Core intuition**

The list *is* positional notation; align least-significant digits (or most-significant, depending on statement), simulate column addition.

**General approach**

1. Determine digit order (LeetCode "Add Two Numbers" = least-significant first).
2. Loop while either list has nodes or `carry != 0`.
3. Create node per digit; never drop the final carry.

**Time / Space**

`O(max(n, m))` / `O(1)` extra (excluding output).

**Edge cases**

Different lengths; leading zeros in result; final carry creating a new head; both lists empty.

**Common mistakes**

Dropping final carry; assuming equal lengths; forgetting digit order (MSD-first needs stack/reverse).

**Variations**

Add 1 (carry propagation to head — use stack or reverse first); sum of two numbers as list vs integer.

### P6 — Partition / Reorder Patterns

**What is the pattern?**

Rebuild the list by *collecting nodes into buckets* (by value or position) and relinking — one pass out, one pass stitch.

**When should I recognize it?**

- "Odd-even positions", "segregate odd/even (DLL)", "reorder list", "flatten a multi-level list", "rotate by k", "pairs with given sum in DLL".

**Core intuition**

Values/positions are known in one traversal → build several chains simultaneously → concatenate. Rotation = cut the list at `n - k%n` and reattach the tail to the head.

**General approach**

1. Traverse, appending current node to its bucket chain (advance bucket tail).
2. Stitch buckets head-to-tail.
3. Fix tails (`tail->next = nullptr`).

**Time / Space**

`O(n)` / `O(1)`.

**Edge cases**

Single node; empty list; forgetting to terminate the last chain (creates a cycle!); DLL `prev` pointers not repaired.

**Common mistakes**

Leaving `tail->next` pointing into the old structure; not fixing `prev` in doubly linked lists; rotation with `k > n` or `k = 0`.

**Variations**

Flatten sorted multilevel list (merge down + right); clone with random pointer (hash map or interleaving); pairs with given sum in sorted DLL (two pointers).

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
