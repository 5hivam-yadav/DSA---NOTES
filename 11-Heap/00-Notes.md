# Heap (Priority Queue) — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — Size-K Heap (Kth / Top-K)

**What is the pattern?**

Keep at most `k` elements in a heap of the *opposite* direction; top = answer.

**When should I recognize it?**

- "Kth largest / kth smallest", "top k frequent", "k closest points", "k largest sum combinations" (with sorted trick), "kth largest in a stream".

**Core intuition**

For kth largest: maintain the `k` biggest seen — evict the smallest of them when a bigger arrives; the heap root is then exactly the kth biggest.

**Generic algorithm**

1. Min-heap (for kth largest).
2. Push each element; if `size > k` → `pop()`.
3. Answer = `top()`.

**Time / Space**

`O(n log k)` / `O(k)`. Stream of `m` elements: `O(m log k)`.

**Edge cases**

`k == n` (heap holds everything); duplicates at the kth boundary; `k < 1` (invalid input).

**Common mistakes**

Wrong heap direction; pushing then popping when `size > k` *before* push (off-by-one); forgetting `k` may exceed `n`.

**Variations**

Kth smallest → max-heap; "stream" variant (`15-Kth-Largest-in-Stream.cpp`) never needs the old elements removed — same code.

### P2 — Two-Heap Median (streaming median)

**What is the pattern?**

Max-heap for the lower half + min-heap for the upper half, sizes balanced within 1.

**When should I recognize it?**

- "Find median from a data stream", "sliding window median" (with lazy deletion — advanced), "split array into balanced halves".

**Core intuition**

Medians live at the boundary of two halves — each heap stores one side sorted; rebalancing keeps the boundary at the center.

**Generic algorithm**

1. Insert into `lo` (max-heap); move `lo.top()` to `hi` if out of order.
2. Rebalance: if `lo.size() > hi.size() + 1` → move top to `hi`; if `hi.size() > lo.size()` → move back.
3. Median: odd → `lo.top()`; even → average of tops.

**Time / Space**

`O(log n)` per insert, `O(1)` median / `O(n)`.

**Edge cases**

First element; even vs odd counts; overflow when averaging (use `double` or `long long`).

**Common mistakes**

Skipping the order-fix step (median split invalid); off-by-one balancing (`lo` should hold the extra).

**Variations**

Sliding window median needs a multiset/two heaps with lazy deletion — mention as advanced.

### P3 — K-Way Merge (merge K sorted structures)

**What is the pattern?**

Min-heap of the current heads of K sorted streams; pop-min, push its successor.

**When should I recognize it?**

- "Merge K sorted lists / arrays", "k smallest pairs", "merge feeds/timelines", "sort k-sorted array".

**Core intuition**

The global minimum of the union is always among the K heads — the heap maintains exactly those candidates.

**Generic algorithm**

1. Push head of each list as `(value, listId, index)`.
2. Repeatedly pop the smallest, append to output, push the next element from the same list.
3. Stop when the heap empties.

**Time / Space**

`O(N log K)` time (N total elements), `O(K)` heap space.

**Edge cases**

Empty lists among the K; K = 0 / 1; all elements in one list; duplicates across lists.

**Common mistakes**

Pushing all elements up front (`O(N log N)` — loses the point); missing list index in tuple (can't find successor).

**Variations**

Pairwise divide-and-conquer merge (same bound, `O(log K)` depth); k-sorted array = merge adjacent windows.

### P4 — Heap + Greedy (scheduling, ropes, handshakes)

**What is the pattern?**

Repeatedly pick the globally best/worst current candidates from a heap, combine or schedule them, push results back.

**When should I recognize it?**

- "Connect ropes with minimum cost", "task scheduler minimum intervals", "hands of straights", "reorganize string", "minimum time to finish tasks".

**Core intuition**

Local choice among the *extreme* available options is globally safe when an exchange argument applies — the heap provides the extremes in `O(log n)`.

**Generic algorithm (ropes)**

```text
push all ropes into min-heap
while size > 1:
    a = pop; b = pop; cost += a + b; push(a + b)
answer = cost
```

**Time / Space**

`O(n log n)` / `O(n)`.

**Edge cases**

0 or 1 rope (cost 0); single huge rope; overflow when sums approach `10^14` → `long long`.

**Common mistakes**

Forgetting to push the combined value; using min-heap when max needed (task scheduling often needs max-frequency first).

**Variations**

Task scheduler (formula `max(n, (f−1)(n+1)+cnt)` — or heap simulation); maximum sum combinations (two sorted arrays + max-heap of candidate pairs with visited set).

### P5 — Count-then-Heap (top-K frequent / rank by frequency)

**What is the pattern?**

Hash map counts frequencies → heap of `(freq, key)` (size k or full) → pop in frequency order.

**When should I recognize it?**

- "Top K frequent elements", "sort by frequency", "k closest / reorderBy frequency", "design Twitter (rank by time)".

**Core intuition**

Counting is `O(n)`; ordering *only the interesting K* with a heap is `O(n + n log k)` — better than full sort when `k ≪ n`.

**Generic algorithm**

1. `unordered_map` count pass.
2. Push `(freq, key)` into heap; keep size `k`.
3. Pop/collect.

**Time / Space**

`O(n + n log k)` / `O(n)`.

**Edge cases**

Ties at the kth frequency (any order usually accepted); `k ==` number of distinct keys.

**Common mistakes**

Pair ordering: `priority_queue<pair>` sorts by `first` **descending** by default — put freq first and use `greater<>` for min-heap; forgetting tiebreakers.

**Variations**

Bucket sort `O(n)` alternative (buckets by frequency); design Twitter = merge user timelines via heap of iterators.

### P6 — Adaptive Heaps & Stale Entries (lazy deletion)

**What is the pattern?**

Push "candidate versions" into the heap; when popped, check if still current (vs hash/map state) — if stale, discard and pop again.

**When should I recognize it?**

- Problems needing "best current value" where values **decrease over time** (Dijkstra relaxations, scheduling deadlines, sliding-window median).

**Core intuition**

Updating a heap element in place costs `O(n)` with `priority_queue` — instead, push the new state and validate on pop; outdated entries are cheap garbage.

**Generic algorithm**

```text
push (newState)
while top is stale (doesn't match authoritative store): pop
use top
```

**Time / Space**

Each real update adds one push → still `O((n + updates) log n)` / `O(n + updates)`.

**Edge cases**

All entries stale (empty check before use); equal distances (any tie order fine).

**Common mistakes**

Forgetting the staleness check (processing outdated best); comparing wrong fields.

**Variations**

Dijkstra (§15), sliding-window median (multiset erase + heap), "maximum sum of at most k non-overlapping intervals" (heap by end time).

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
