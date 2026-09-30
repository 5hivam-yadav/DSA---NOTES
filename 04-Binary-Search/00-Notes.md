# Binary Search — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — Classic Index Binary Search

**What is the pattern?**

Search a sorted array by repeatedly comparing the midpoint and discarding the impossible half.

**When should I recognize it?**

- "Given a **sorted** array, find `x` / insertion position / floor / ceil."
- Any `O(log n)` hint, or `n` up to `10^6–10^12` with a cheap check.

**Core intuition**

Sortedness makes the predicate "`a[i] >= x`" monotonic — one comparison eliminates half the candidates.

**General approach / Generic algorithm**

1. `lo = 0, hi = n - 1`.
2. While `lo <= hi`: `mid = lo + (hi - lo) / 2`.
3. `a[mid] == x` → return; `a[mid] < x` → `lo = mid + 1`; else `hi = mid - 1`.
4. Return `-1` / `lo` (insertion point).

**Time / Space**

`O(log n)` — halving; `O(1)` — only indices stored.

**Edge cases**

Empty array (`hi = -1` → loop skipped), single element, `x` smaller/larger than all.

**Common mistakes**

`(lo+hi)/2` overflow; `lo = mid` infinite loop; returning `hi` instead of `lo` as insertion point.

**Variations**

Search insert position; floor/ceil; square root (predicate `mid*mid <= x`).

### P2 — Boundary Search (Lower/Upper Bound, First/Last Occurrence)

**What is the pattern?**

Binary search for the **first position where a predicate flips** from false to true (or vice versa) instead of an exact value.

**When should I recognize it?**

- "First / last occurrence", "count of `x`", "smallest index with …", duplicates present.

**Core intuition**

Keep a candidate answer whenever `mid` satisfies the condition, and always move toward the condition's boundary — you converge on the flip point.

**General approach**

1. `lo = 0, hi = n` (note `hi = n`, one past end).
2. If `P(mid)` (e.g. `a[mid] >= x`) holds → record `mid`, `hi = mid`; else `lo = mid + 1`.
3. The recorded/`lo` value is the first true position.

**Time / Space**

`O(log n)` / `O(1)`.

**Edge cases**

All elements `< x` → returns `n`; all `>= x` → returns `0`; empty → `0`.

**Common mistakes**

Using `hi = n - 1` for boundary searches (misses "one past end" answers); mixing up `>` vs `>=` (lower vs upper bound).

**Variations**

Count = `ub - lb`; last occurrence = `ub - 1`; "last false" = `lb - 1`.

### P3 — Rotated Sorted Array Search

**What is the pattern?**

Binary search on an array that was sorted, then rotated — exactly one half of `[lo..hi]` is always sorted.

**When should I recognize it?**

- Keywords: "rotated sorted array", "search in rotated", "find minimum in rotated", "rotation count", "single element in sorted (pair-broken) array".

**Core intuition**

`a[lo] <= a[mid]` ⟹ left half sorted. Test whether `x` lies inside the sorted half; if not, the answer must be in the other half.

**General approach**

1. Compute which half is sorted.
2. Check if `x` is in that half's value range → go there; else go the other way.
3. For minimum/rotation count: compare `a[mid]` with `a[hi]` to decide which side holds the pivot.

**Time / Space**

`O(log n)` distinct values; `O(n)` worst case with duplicates (`lo++` fallback). `O(1)` space.

**Edge cases**

No rotation (already sorted); fully rotated; all duplicates; `lo == mid` or `mid == hi`.

**Common mistakes**

Wrong sorted-half test (`<` vs `<=`); forgetting `a[lo] <= a[mid]` must use `<=` so a single-element left half counts as sorted.

**Variations**

Find minimum (`10`); rotation count (`11`); search with duplicates (`09`); single non-paired element (`12`).

### P4 — Binary Search on Answer (Feasibility / Min-Max)

**What is the pattern?**

Binary search over **possible answer values** using a monotonic feasibility predicate instead of over array indices.

**When should I recognize it?**

- Phrases: **"minimize the maximum …"**, **"maximize the minimum …"**, "smallest capacity such that …", "can we finish within X days/hours?"
- Classic shapes: ship capacity, book allocation, painters, aggressive cows, koko bananas, bouquets, gas stations, split array.

**Core intuition**

If a candidate answer `x` works, every larger (for min-max) or smaller (for max-min) candidate also works — feasibility is monotone → binary search applies.

**General approach**

1. Define `lo` = smallest possible answer, `hi` = answer that trivially works (e.g. sum, max element).
2. `mid = lo + (hi - lo) / 2`.
3. `predicate(mid)` = greedy simulation "can we do it with `mid`?"
4. True → `hi = mid` (min-max) or `lo = mid` (max-min); false → opposite.
5. Return `lo` when `lo == hi`.

**Time / Space**

`O(log(range) · cost(feasible))` — e.g. Koko: `O(log(maxPile) · n)`. Space `O(1)` + predicate's workspace.

**Edge cases**

`range = 0` (single candidate); predicate never true with given bounds (bounds wrong); overflow when `hi = 10^9` and predicate sums `hi · n` → use `long long`.

**Common mistakes**

Bounds not covering the answer; `while (lo < hi)` + `hi = mid - 1` skipping the answer; non-monotone predicate (binary search invalid — rethink).

**Variations**

Binary search the threshold of a path property (min max-edge / min max-effort on a grid); real-valued binary search (fixed iterations, `hi = 1e9`).

### P5 — Peak / Structured Binary Search (unsorted but ordered)

**What is the pattern?**

The array is not sorted, but a **structural guarantee** (neighbor relation) lets halving still work.

**When should I recognize it?**

- "Peak element" (greater than neighbors), "single element in sorted-with-pairs", "first bad version", any "locality" guarantee.

**Core intuition**

If `a[mid] < a[mid+1]`, a peak exists to the right (strictly increasing must eventually come down); else a peak exists to the left/equal. We only need *a direction that guarantees a peak*, not global order.

**General approach**

1. Keep `[lo, hi]` where a peak is guaranteed.
2. Use the neighbor comparison to discard half.
3. For pairs-sorted arrays: compare `mid` with `mid^1` (paired indices) to find the lone element.

**Time / Space**

`O(log n)` / `O(1)` — halving still holds because one half always contains a peak.

**Edge cases**

`n == 1`; strictly increasing (last is peak); strictly decreasing (first is peak); flat regions.

**Common mistakes**

Accessing `a[mid+1]` when `mid == hi` (guaranteed by `lo < hi` — keep it); assuming uniqueness when multiple peaks exist (any peak accepted).

**Variations**

Find peak in 2D matrix (row+col peak, `O(m+n)` staircase); first bad version (predicate on monotone array).

### P6 — 2D Matrix Search

**What is the pattern?**

Flatten a sorted matrix into virtual indices, or walk a staircase discarding row/column.

**When should I recognize it?**

- "Sorted matrix, search `x`", "row-wise sorted matrix", "row with max 1s", "median of row-wise sorted".

**Core intuition**

Two independent sorted dimensions → either encode `k → (k/n, k%n)` as a virtual sorted array, or use top-right comparison (knowing both left and down directions).

**General approach**

- **Fully sorted rows+cols**: `mid` → `m[mid/n][mid%n]`; compare; discard half of `mn` cells.
- **Staircase**: start top-right; `> x` → move left (eliminate column); `< x` → move down (eliminate row).
- **Row-wise only**: binary search the first row ≥ x to find the row, then binary search within it.

**Time / Space**

Staircase `O(m+n)`; virtual flatten `O(log(mn))`; row-wise `O(m + n)` worst, `O(log m + log n)` typical.

**Edge cases**

Empty matrix; single row/column; all equal elements; target outside matrix range.

**Common mistakes**

Treating `vector<vector<int>>` as contiguous (rows separately allocated); wrong row-major index math; forgetting `m[0]` access on empty input.

**Variations**

Row-wise sorted median (binary search value + count-leq per row); peak in 2D (`32`).

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
