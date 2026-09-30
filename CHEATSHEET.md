# DSA Quick Revision Cheat Sheet

A last-pass refresher: identify the signal, recall the invariant or transition, then check the listed trap. Open the linked topic note when you need the full pattern explanation. Standalone reusable implementations for algorithms not already isolated in the topic folders are grouped under `algorithms/`. For common C++ library calls, see [CPP_STL_FUNCTIONS.md](CPP_STL_FUNCTIONS.md).

## Universal solve checklist

1. **Read constraints first.** Estimate whether the target is `O(n)`, `O(n log n)`, `O(n²)`, or smaller.
2. **Name the pattern and its precondition.** Sortedness, monotonicity, non-negative weights, DAG structure, or bounded alphabet must actually hold.
3. **State the invariant/state.** What does the window, pointer, stack, `dp[i]`, queue, or trie node represent?
4. **Trace boundaries.** Empty/singleton input, duplicates, all equal, answer at either extreme, overflow, disconnected input.
5. **State complexity precisely.** Include output memory, recursion stack, and auxiliary structures.

## 1. Basics & mathematical foundations

See [Basics revision notes](01-Basics/00-Notes.md).

- **Loop/index problems:** write the first and last valid index; half-open `[l,r)` means `i < r` and length `r-l`.
- **Digits:** last digit `n % 10`, remove it with `n /= 10`; reverse with `rev = rev*10 + digit` and check overflow before multiplication.
- **GCD:** repeat `(a,b) = (b,a%b)`; LCM is `(a/gcd)*b` to reduce overflow risk.
- **Divisors/primes:** test divisor pairs only through `sqrt(n)`; sieve marks from `p*p`.
- **Frequency table:** direct indexing for small bounded keys; hash/map for sparse or large values.
- **Recursion:** define the smaller task, a stopping case, and what returns upward. Stack cost follows maximum depth.

## 2. Sorting

See [Sorting revision notes](02-Sorting/00-Notes.md).

- Need order before pairing/ranging/interval work? Sort, then scan or use two pointers: `O(n log n)` overall.
- Need only kth/top-`k`? Use `nth_element`, partial sort, or a heap instead of fully sorting.
- Comparator: primary key then tie-break; use strict `<` and maintain a strict weak ordering.
- 0/1/2 values: Dutch National Flag regions `[0,lo)`, `[lo,mid)`, `(hi,n)`; after swapping with `hi`, inspect `mid` again.
- Inversions: during merge, if right value is smaller, add remaining left count `mid-i+1`.
- Stability preserves equal-key input order; it is independent of whether the sort is in-place.

## 3. Arrays & matrices

See [Arrays revision notes](03-Arrays/00-Notes.md).

- One-pass aggregate: maintain only the state needed so far; initialize from data when all-negative input matters.
- Subarray sum `K`: prefix frequency map; at prefix `p`, add `freq[p-K]`; seed `freq[0]=1`. Works with negative values.
- Range sum `[l,r]`: `pref[r+1]-pref[l]`.
- Maximum subarray: `cur=max(x,cur+x)`, `best=max(best,cur)` (Kadane).
- Sorted pair sum: if sum too small move left pointer up; too large move right pointer down.
- Majority `> n/2`: Boyer–Moore candidate, then verify if not guaranteed.
- Rotate 90° clockwise: transpose, then reverse each row. Spiral: shrink four boundaries, guard after each side.
- Intervals: sort by start; merge while `next.start <= current.end` if touching counts as overlap.
- In-place partition: define exact regions and which pointer owns unprocessed data.

## 4. Binary search

See [Binary Search revision notes](04-Binary-Search/00-Notes.md).

- Search sorted data or a monotone predicate. Use `mid = lo + (hi-lo)/2`; prove the range shrinks.
- Lower bound = first `a[i] >= x`; upper bound = first `a[i] > x`; count equals `upper-lower`.
- Rotated array: identify the sorted half, then check whether target lies in its range. Duplicates can degrade to `O(n)`.
- Search on answer: define `feasible(x)` and confirm it changes only once. Minimize the maximum → first feasible; maximize the minimum → last feasible.
- Peak: compare `a[mid]` with `a[mid+1]` while `lo < hi`; retain a side guaranteed to contain a peak.
- Matrix sorted row-major: virtual index `k` maps to `(k/cols,k%cols)`; staircase search needs row and column sortedness.

## 5. Strings

See [Strings revision notes](05-Strings/00-Notes.md).

- Anagram: character counts; isomorphic: enforce mapping in both directions.
- Palindrome check: two pointers; longest palindrome: expand around every odd/even center (`O(n²)`).
- Parenthesis validity/nesting: stack for matching types, depth counter if only one bracket type.
- KMP: on mismatch set `j = lps[j-1]`; do not reset to zero. Build LPS in `O(m)`, search in `O(n+m)`.
- Z algorithm: `z[i]` is longest prefix match beginning at `i`; reuse the current `[l,r]` box.
- Rotation check: equal lengths and `b` occurs in `a+a`.
- Parsing/conversion: trim spaces, sign, digits, overflow clamp; avoid unsigned reverse-loop underflow.

## 6. Linked lists

See [Linked List revision notes](06-Linked-List/00-Notes.md).

- Dummy node removes head special cases for insert/delete/merge.
- Reverse: save `next`, point `curr->next` to `prev`, advance; return `prev`.
- Middle/cycle: slow moves one, fast two; cycle entry is found by resetting one pointer to head after collision.
- Remove nth from end: maintain an `n`-node gap; dummy handles deleting the head.
- Merge sorted lists by relinking nodes; merge sort is `O(n log n)` time and list-friendly.
- Before changing links, preserve the next pointer. Check null, one-node, and tail cases.

## 7. Recursion & backtracking

See [Recursion revision notes](07-Recursion/00-Notes.md).

- Subsets/subsequences: choose/not-choose each index; `2^n` leaves.
- Combinations: move index forward to avoid permutations and duplicates.
- Permutations: choose unused element or swap into position; undo the choice on return.
- Combination sum: sort/prune; reuse current index for unlimited use, advance for single use.
- Duplicate-safe enumeration: sort, then skip equal values at the same recursion depth.
- Backtracking template: choose → recurse → undo. Define path/state and stopping condition first.
- Prune only when the branch cannot produce a valid answer; recursion depth contributes stack space.

## 8. Bit manipulation

See [Bit Manipulation revision notes](08-Bit-Manipulation/00-Notes.md).

- Test bit `b`: `(x>>b)&1`; set `x|(1<<b)`; clear `x&~(1<<b)`; toggle `x^(1<<b)`.
- `x & (x-1)` clears lowest set bit; power of two iff `x>0 && (x&(x-1))==0`.
- XOR: `a^a=0`, `a^0=a`, order independent. Pair cancellation solves single-number variants.
- Enumerate masks `0..(1<<n)-1` only for small `n`; beware shift width/overflow.
- Sieve from `p*p`; divisor scan to `sqrt(n)`.
- Use unsigned or wider types for high-bit shifts; signed overflow is undefined.

## 9. Stack & queue

See [Stack and Queue revision notes](09-Stack-and-Queue/00-Notes.md).

- Matching/nesting: stack. Next greater/smaller: monotonic stack; each item is pushed/popped at most once (`O(n)`).
- Subarray contribution problems: count how many ranges assign each element as min/max; choose strict/non-strict boundaries so duplicates count once.
- Histogram: while popping height `h`, width is `i - previousSmaller - 1`.
- Sliding-window max: decreasing deque of indices; expire front, remove dominated values from back.
- Queue via stacks: transfer only when output stack is empty; amortized `O(1)` per operation.
- LRU: hash map + doubly linked list; LFU additionally tracks frequency and recency within each frequency.

## 10. Sliding window & two pointers

See [Sliding Window revision notes](10-Sliding-Window-and-Two-Pointer/00-Notes.md).

- Fixed window: add entering item, remove leaving item; update answer once window has size `k`.
- Variable window works when extending/shrinking has monotone effect (commonly non-negative values). Negative values often require prefix sums instead.
- Longest valid window: expand right, shrink until valid, then update. Shortest covering window: shrink while still valid.
- Exactly `k` distinct/odd/etc. = `atMost(k) - atMost(k-1)` when the at-most count is easier.
- Minimum window: track required counts and how many requirements are currently satisfied.
- Sorted pair/triple sums: move pointers based on comparison; skip duplicate values when unique answers are required.

## 11. Heap / priority queue

See [Heap revision notes](11-Heap/00-Notes.md).

- Need repeated min/max: priority queue; push/pop `O(log n)`, top `O(1)`.
- Top `k`: keep a size-`k` heap of the desired candidates; choose min-heap for largest `k`, max-heap for smallest `k`.
- Streaming median: max-heap lower half + min-heap upper half; sizes differ by at most one.
- Merge `k` sorted lists: heap holds one current item per list; `O(N log k)`.
- Lazy deletion: heap may hold stale entries; validate against current state when popped.
- C++ `priority_queue` is max-heap by default; comparator direction is a frequent source of bugs.

## 12. Greedy

See [Greedy revision notes](12-Greedy/00-Notes.md).

- Greedy needs a proof: exchange argument, stays-ahead argument, or a structural invariant.
- Maximum non-overlapping intervals: sort by end, take earliest finishing compatible interval.
- Merge intervals: sort by start and extend current right endpoint.
- Resource pairing: sort both sides and match the smallest adequate resource.
- Fractional knapsack uses value/weight ratio; 0/1 knapsack generally needs DP.
- Jump reachability: maintain furthest reachable index; detect a stall before advancing.
- Do not infer greedy correctness from a few examples; search for a counterexample before coding.

## 13. Binary trees

See [Binary Tree revision notes](13-Binary-Tree/00-Notes.md).

- Preorder = root/left/right; inorder = left/root/right; postorder = left/right/root; level order = BFS.
- Need child-derived answer (height, diameter, balanced)? Postorder returns info upward in one pass.
- Need levels/views/width/minimum depth? BFS with level boundaries or queue size.
- Diameter: at each node combine left height + right height; update global best.
- LCA: return current node if null/target; if both sides return non-null, current is LCA.
- Build from traversals: inorder plus preorder or postorder; map value→inorder index for `O(n)`.
- Avoid repeated full subtree scans (`O(n²)`); propagate computed metadata.

## 14. Binary search trees

See [BST revision notes](14-Binary-Search-Tree/00-Notes.md).

- Ordering invariant: left subtree keys `< node`, right subtree keys `> node` (adapt deliberately if duplicates allowed).
- Search/insert/min/max/floor/ceil follow one root-to-leaf path: `O(h)`; balanced `O(log n)`, skewed `O(n)`.
- Inorder traversal is sorted; kth smallest can stop after visiting `k` nodes.
- Validate using exclusive `(low,high)` bounds, not only parent-child comparisons.
- Delete: leaf, one child (splice), two children (successor/predecessor replacement).
- Successor/predecessor: candidate while walking, or next/previous inorder node.

## 15. Graphs

See [Graph revision notes](15-Graph/00-Notes.md).

- BFS: unweighted shortest distance; mark visited on enqueue. Multi-source BFS seeds all starts.
- DFS: components, reachability, flood fill; run from every unvisited node for disconnected graphs.
- Directed cycle/topological order: Kahn indegrees; fewer than `V` outputs means a cycle.
- Undirected cycle: detect visited neighbor other than parent; directed DFS uses recursion-stack state.
- Dijkstra: non-negative edges only; stale heap entry guard `if (d != dist[u]) continue`.
- Negative edges: Bellman–Ford (`V-1` passes; extra relaxation detects negative cycle). All-pairs: Floyd–Warshall.
- 0–1 BFS: weight 0 goes front, weight 1 goes back. MST: Kruskal sorts edges + DSU; Prim grows with min-heap.
- DSU: path compression + union by size/rank; near-constant amortized operations.

## 16. Dynamic programming

See [DP revision notes](16-Dynamic-Programming/00-Notes.md).

- DP needs **overlapping subproblems + optimal substructure**. Define state, transition, base case, order, answer.
- 1D take/skip: `dp[i]=best(skip i, take i + dp[i-gap])`; roll to a few variables if only recent states matter.
- Grid: `dp[r][c]` combines allowed predecessor states; obstacle/base initialization determines reachability.
- 0/1 knapsack/subset sum: item used once → capacity loops downward. Unbounded reuse → upward.
- LCS: match → `1+diag`; mismatch → `max(up,left)`. Substring resets mismatch to zero; subsequence does not.
- Edit distance: min of insert/delete/replace; initialize empty-prefix row/column.
- LIS: `O(n²)` predecessor DP; `O(n log n)` tails for length (tails is not itself the subsequence).
- Stock: state = holding/not holding plus transaction/cooldown constraints; transitions must not use same-day impossible states.
- Interval DP: choose the last split/operation; iterate shorter intervals before longer ones.
- Count ways vs optimize: sum transitions vs min/max; sentinel and modulo handling differ.
- Space optimize only after identifying which previous states are still needed.

## 17. Trie

See [Trie revision notes](17-Trie/00-Notes.md).

- Trie operation follows characters: `O(L)`; terminal/end count means a full word ends here, prefix count means words pass through.
- Use trie for many prefix queries/dictionary matching; hash set is simpler for exact-word lookup only.
- Distinct substrings: insert every suffix and count newly created nodes (`O(n²)` time/space for plain suffix trie).
- Maximum XOR: binary trie from most significant bit; choose opposite bit whenever available.
- Bounded XOR queries: sort values and queries by limit, insert eligible values incrementally, answer offline.
- Trie + grid DFS: follow only existing trie edges, mark/unmark board cells, and stop once a word path is impossible.

## Fast complexity reference

| Cost | Typical algorithms |
|---|---|
| `O(1)` | Array access, heap top, DSU amortized is near-constant |
| `O(log n)` | Binary search, heap push/pop, balanced BST operation |
| `O(n)` / `O(V+E)` | Scan, two pointers, BFS/DFS, monotonic stack |
| `O(n log n)` | Comparison sort, heap processing, merge sort |
| `O(n²)` | Pairwise DP, all subarrays, suffix trie |
| `O(n³)` | Floyd–Warshall, many interval DP transitions |
| `O(2^n)` / `O(n!)` | Subsets / permutations; only for small `n` |

## High-frequency bug checks

- Use `long long` for large sums/products; guard `INF + cost` and multiplication overflow.
- Distinguish contiguous subarray/substring, subsequence, and subset.
- Binary search: lower bound vs upper bound; inclusive vs half-open endpoints.
- Monotonic stack: strictness on both sides must assign duplicates exactly once.
- Graphs: directed vs undirected, disconnected components, negative weights, 0/1 indexing.
- DP: impossible-state sentinel, loop direction, base row/column, and whether empty selection is allowed.
- C++: signed/unsigned comparisons, invalidated references after vector growth, and recursion depth.
