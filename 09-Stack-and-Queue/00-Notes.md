# Stack and Queue — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — Valid Parentheses / Nesting Stack

**What is the pattern?**

Push openers; on a closer, verify/pop the matching top; answer = stack empty at end.

**When should I recognize it?**

- "Valid parentheses / brackets", "remove outermost parentheses", "max nesting depth", "reverse substrings in brackets".

**Core intuition**

Nesting is LIFO: the *most recent* opener must be closed first.

**Generic algorithm**

1. `for c in s`: open → push (or `depth++`); close → check top matches (or `depth--` with validation).
2. Valid iff stack empty (and never popped empty / never negative depth).

**Time / Space**

`O(n)` / `O(n)`.

**Edge cases**

Empty string (valid); closers first; interleaved types `([)]`; unbalanced leftovers.

**Common mistakes**

Checking `st.top()` before `st.empty()`; using a plain counter when bracket *types* matter.

**Variations**

Depth counter for single-type nesting; min insertions = simulate and count unclosed.

### P2 — Monotonic Stack (NGE / NSE / PGE / PSE)

**What is the pattern?**

One pass with a stack sorted in monotone order; pops are answered by the current element.

**When should I recognize it?**

- "Next greater element", "next smaller", "previous greater/smaller", "span", "temperature warmer day", "sum of subarray minimums/maximums", "trapping rain water", "largest rectangle in histogram".

**Core intuition**

An element waits in the stack until something *strictly better* (per query direction) arrives — that arrival is its answer; otherwise the array end is its answer (−1).

**Generic algorithm (next greater, right side)**

1. Scan L→R with a stack of **indices** in decreasing value order.
2. While `!st.empty() && a[st.top()] <= a[i]`: `ans[st.top()] = a[i]`; pop.
3. Push `i`. Leftover indices → `-1`.

**Time / Space**

Amortized `O(n)` (each index pushed/popped once) / `O(n)`.

**Edge cases**

All equal (strictness decides); increasing/decreasing arrays (one side never pops); single element.

**Common mistakes**

`<=` vs `<` (duplicate semantics); storing values instead of indices; wrong scan direction for "previous".

**Variations**

Circular array (`i % n` with `2n` loop); contribution counting for subarray min/max sums; two-pass (left + right) for boundary-sensitive problems.

### P3 — Contribution Counting (histogram / maximal rectangle)

**What is the pattern?**

For each element, compute the maximal range where it is the min/max/histogram-bar, then add `value × width` contributions.

**When should I recognize it?**

- "Largest rectangle in histogram", "maximal rectangle of 1s", "sum of subarray minimums".

**Core intuition**

Instead of enumerating subareas (`O(n²)`), ask for each bar: *how far does it extend as the limiting height?* → previous-smaller + next-smaller brackets it.

**Generic algorithm**

1. Histogram: `left[i]` = previous smaller index (strict), `right[i]` = next smaller (non-strict) — pick one strictness consistently to avoid double counting.
2. `area = a[i] * (right[i] - left[i] - 1)`.
3. Maximal rectangle: treat each row as histogram base, heights = consecutive 1s above.

**Time / Space**

`O(n)` / `O(n)` per histogram row → `O(m·n)` for maximal rectangle.

**Edge cases**

Empty histogram; all equal heights; strictly increasing (right never pops — sentinel handles it); zero heights.

**Common mistakes**

Forgetting the sentinel (last bars never evaluated); inconsistent strictness (double/zero counting); not resetting heights between rows.

**Variations**

Sum of subarray minimums uses *counts* `(i - left) * (right - i)` instead of max.

### P4 — Min-Stack / Queue-with-Stacks (auxiliary structure pairs)

**What is the pattern?**

Pair the primary structure with an auxiliary one that tracks the "extra" answer (min, reversed order).

**When should I recognize it?**

- "Min stack with O(1) min", "max stack", "queue using two stacks", "stack using queue", "implement queue with limited API".

**Core intuition**

Every push also records the *running best* (min/max) or routes through a second container so the overall discipline (LIFO/FIFO) is preserved.

**Generic algorithm**

- **Min stack**: push `(x, min(x, prevMin))`; top/min read from the pair.
- **Queue via 2 stacks**: `in` for pushes; when `out` empty, flip all of `in` into `out` — each element flipped once → amortized `O(1)`.

**Time / Space**

Push/pop `O(1)` amortized (queue) / `O(1)` strict (pair stack); `O(n)` space.

**Edge cases**

Single element; popping when auxiliary empties (queue flip trigger); overflow in `2x - top` trick (prefer pairs).

**Common mistakes**

Forgetting to flip only when `out` is empty (breaking amortization); `2x - top` overflow for large values.

**Variations**

Constant-space min stack (2x−top encoding — know its overflow caveat); deque-based sliding max (P5).

### P5 — Monotonic Deque (sliding window maximum / minimum)

**What is the pattern?**

A deque stores *candidate indices* in decreasing (max) or increasing (min) value order; stale (out-of-window) indices are popped from the front.

**When should I recognize it?**

- "Sliding window maximum/minimum", "constraint problems needing window max in `O(1)`", "jump game with window-based reachability".

**Core intuition**

While adding `a[i]`, pop back while `a[back] <= a[i]` (they can never be the max while `i` is inside). Front always holds the max of the current window; expire `front <= i-k`.

**Generic algorithm**

```text
for i:
    while !dq.empty && a[dq.back] <= a[i]: pop_back
    push_back(i)
    while dq.front <= i - k: pop_front        (expired)
    if i >= k-1: answer[i] = a[dq.front]
```

**Time / Space**

`O(n)` (each index pushed/popped once) / `O(k)`.

**Edge cases**

`k = 1`; decreasing array (front never stale from back); duplicates (`<=` pops them).

**Common mistakes**

Expiring *before* pushing vs after (both work — but be consistent with index bounds); storing values instead of indices (can't check expiry).

**Variations**

Monotonic **min** deque for window minimums; two deques for min+max simultaneously.

### P6 — LRU / LFU Cache (hash + linked list / counts)

**What is the pattern?**

Hash map for `O(1)` lookup + doubly linked list (or count buckets) for `O(1)` recency/frequency ordering.

**When should I recognize it?**

- "Design an LRU cache", "LFU cache", "evict least recently used".

**Core intuition**

List order = recency order; a hit moves a node to the head (`O(1)` with a DLL); eviction removes the tail. Hash maps node key → pointer.

**Generic algorithm**

- `get(key)`: lookup → move node to head → value.
- `put(key,val)`: insert at head; if over capacity → remove tail (and its hash entry).

**Time / Space**

`O(1)` get/put average / `O(capacity)`.

**Edge cases**

Capacity 0/1; updating an existing key (must move, not duplicate); evicting while inserting.

**Common mistakes**

Hash entry not erased on eviction (dangling iterator); not moving nodes on `get` (violates recency).

**Variations**

LFU: frequency map + bucket per count (min-heap alternative `O(log n)`).

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
