# Sliding Window and Two Pointer — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — Fixed-Size Window

**What is the pattern?**

Maintain a window of exactly `k` elements, sliding it one step at a time with `+add / −remove`.

**When should I recognize it?**

- "Every subarray of size k", "max sum of k consecutive", "average of each window", "max consecutive ones with k flips" (fixed inner condition).

**Core intuition**

Consecutive windows share `k−1` elements — reuse the previous sum instead of recomputing.

**Generic algorithm**

1. For `i` in `0..n-1`: `sum += a[i]`.
2. If `i >= k`: `sum -= a[i-k]`.
3. If `i >= k-1`: update answer.

**Time / Space**

`O(n)` / `O(1)`.

**Edge cases**

`k > n` (no full window); `k == n`; `k == 1`; negative numbers (best starts at `-inf`, not `0`).

**Common mistakes**

Updating before the first full window; `int` sum overflow → `long long`.

**Variations**

Deque-based fixed window max (§09 pattern 4); prefix-sum equivalent `pref[i+k] - pref[i]`.

### P2 — Variable Window (longest / shortest with constraint)

**What is the pattern?**

Expand `r` one step at a time; when invalid (or after recording), shrink `l` with `while`.

**When should I recognize it?**

- "Longest substring/subarray with …", "shortest subarray with sum ≥ K", "longest without repeating", "fruits into baskets", "k distinct characters".

**Core intuition**

Each `r` has a canonical minimal `l` — since both pointers advance monotonically, total work is `2n`.

**Generic algorithm**

```text
for r in 0..n-1:
    add a[r]
    while invalid:        remove a[l], l++
    update answer         (longest: after while;  shortest: inside while before break)
```

**Time / Space**

`O(n)` time (each index enters/leaves once) / `O(σ)` for freq state.

**Edge cases**

No valid window (answer 0); whole array valid; single element; `l` over-shooting past `r`.

**Common mistakes**

`if` instead of `while`; forgetting `while` exit ordering for shortest-window problems; updating answer at wrong point.

**Variations**

last-seen jump (`l = max(l, last[c]+1)`) for no-repeat; maxFreq metric for replacement problems.

### P3 — At-Most → Exactly Subtraction

**What is the pattern?**

Compute `count(≤K) − count(≤K−1)` to answer "exactly K" counting questions.

**When should I recognize it?**

- "Count subarrays with **exactly** K distinct", "exactly K odd numbers", "binary subarrays with sum exactly K" (non-negative), "nice subarrays".

**Core intuition**

"Exactly K" lacks a clean local invalid-condition; "at most K" is monotone (add → maybe shrink when > K) and counts every valid ending window: `res += r - l + 1`.

**Generic algorithm**

1. Write `atMost(k)` with shrink condition `violating > k`.
2. Return `atMost(K) - atMost(K-1)`; guard `K < 1 → 0`.

**Time / Space**

Two passes of `O(n)` → `O(n)` / `O(σ)`.

**Edge cases**

`K = 0`; `K < 0` (return 0); negative array elements (breaks sum-based at-most).

**Common mistakes**

Not handling `k < 0`; map zero-entries not erased (distinct count wrong); using it for sums with negatives.

**Variations**

Prefix-sum + map for sum==K with arbitrary values (§03 pattern).

### P4 — Sorted Two Pointers / Three Sum family

**What is the pattern?**

Sort, then fix one/two elements and move pointers inward based on sum vs target — skipping duplicates.

**When should I recognize it?**

- "Pair/triplet/quadruplet with sum = target", "container with most water", "three sum closest", "two sum II (sorted input)".

**Core intuition**

Sorted order makes the search monotone in each pointer: too small → advance left; too big → retreat right. Each move discards a row of the pair matrix.

**Generic algorithm (3-sum)**

1. Sort.
2. Fix `i`; run two pointers `l = i+1, r = n-1`.
3. `sum < T → l++`; `sum > T → r--`; `sum == T → record, skip dups on both sides, l++, r--`.
4. Skip `a[i] == a[i-1]` at the outer level too.

**Time / Space**

2-sum `O(n)/O(1)` after sort (`O(n log n)` with sort); 3-sum `O(n²)`; 4-sum `O(n³)`; space `O(1)` excluding output.

**Edge cases**

No solution; all zeros; duplicates giving identical triplets; target extremes (overflow → `long long` sums).

**Common mistakes**

Not sorting → can't move pointers logically; missing duplicate skips → repeated outputs; `int` overflow on sums near `2·10^9`.

**Variations**

Two pointers opposite ends (container water); same-direction (remove duplicates / partition); pair sum on *unsorted* → hash map.

### P5 — Minimum Window / Constrained Coverage (have/need)

**What is the pattern?**

Expand `r`; track "how many required items are satisfied"; shrink while still satisfying, recording minimal lengths.

**When should I recognize it?**

- "Minimum window substring containing all characters of T", "smallest subarray covering all required elements", "longest substring containing three distinct letters with limits".

**Core intuition**

Maintain `need` (counts required) and `have` (how many requirements met). When `have == need`, the window is valid → shrink to find the tightest; the answer is the smallest valid window ever seen.

**Generic algorithm**

1. Count pattern → `need`.
2. Expand `r`; on adding a matching char, `have++` if it reaches required count.
3. While `have == need`: record `r-l+1`, shrink `l`, update `have` when a requirement drops.
4. Answer = min recorded window (empty if none).

**Time / Space**

`O(|s| + |t|)` / `O(σ)`.

**Edge cases**

Pattern longer than text (empty answer); duplicate chars in pattern; pattern chars absent from text.

**Common mistakes**

Shrinking when `have == need` must record *before* decrementing; using `>` vs `>=` when decrementing `have` (only when count drops *below* need).

**Variations**

Window subsequence (§10 `09` file) — two-pointer with a backwards inner scan; fixed-template "shortest subarray sum ≥ K" with prefix sums.

### P6 — Last-Seen Jump (replace while-shrink)

**What is the pattern?**

Instead of shrinking step-by-step, jump `l = max(l, lastIndex[c] + 1)` when a repeat is seen.

**When should I recognize it?**

- "Longest substring without repeating characters", "longest repeating character replacement" (variant with maxFreq), any "no duplicates in window".

**Core intuition**

All characters between the previous occurrence of `s[r]` and `r` are invalidated at once — the last-seen map gives the jump distance directly.

**Generic algorithm**

```text
last[256] = -1
for r:  l = max(l, last[s[r]] + 1);  last[s[r]] = r;  best = max(best, r - l + 1)
```

**Time / Space**

`O(n)` / `O(σ)`.

**Edge cases**

Empty string; all distinct (`l` never moves); ASCII vs extended chars (cast to unsigned).

**Common mistakes**

Not initializing `last` to `−1`; using `last[c]` without checking if it's left of `l` (handled by `max`).

**Variations**

maxFreq variant (never shrink `maxFreq`); jump-based merge of at-most logic.

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
