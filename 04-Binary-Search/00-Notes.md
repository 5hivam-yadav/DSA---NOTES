# 04 — Binary Search — Complete Pattern-Based Notes

---

## 1. Topic Overview

Binary search is the art of **halving a search space at every step**. Given a space of `N` candidates and a way to decide "go left or go right", it finds the answer in `O(log N)` steps instead of `O(N)`.

**What it is**
A divide-and-conquer strategy: repeatedly discard the half of the search space that cannot contain the answer, using a single comparison (a *predicate*) at the midpoint.

**Why it is important**
- `log N` is astonishing: `N = 10^6` needs only ~20 comparisons, `N = 10^12` needs ~40.
- It is one of the few patterns that turns "search over answers" into an exact algorithm — *binary search on answer*.
- Interviewers love it because it tests off-by-one discipline, overflow awareness, and the ability to design a **feasibility function**.

**Where it is used**
- Sorted arrays: search, lower/upper bound, first/last occurrence.
- Rotated/sorted-like arrays: peak element, minimum in rotated array.
- Answer optimization: "minimize the maximum capacity/distance/days" problems.
- Matrix search, square root, nth root, allocation/scheduling problems.

**How it connects to other topics**
- §02 Sorting produces the sorted order binary search consumes.
- §10 Sliding Window uses binary search to fix window sizes in some variants.
- §16 DP + binary search appears in LIS (`O(n log n)`) and patience sorting.
- §15 Graph uses binary search on answer for minimum-threshold path problems.

**Interview memory hook:** *Sorted? → search. Rotated? → sorted-half test. "Minimize the maximum / maximize the minimum"? → binary search on answer with a feasibility check.*

---

## 2. Fundamentals

### 2.1 What you need before starting

- A sequence where a **monotonic predicate** holds: everything on the left of some cut is "bad/false", everything on the right is "good/true" (or vice versa).

```text
false false false | true true true
        lo  ...   mid        hi
        discard the false half when we need a true
```

- **Monotonic predicate**: a condition `P(x)` such that if `P(x)` is true then `P(x')` is true for all `x' > x` (or the reverse). Without monotonicity, binary search is invalid.

### 2.2 Logarithm intuition

| Search space | Steps |
|---:|---:|
| 10 | 4 |
| 1,000 | 10 |
| 1,000,000 | 20 |
| 10^12 | 40 |

Each step removes half → `ceil(log2(N+1))` steps.

### 2.3 Terminology

| Term | Meaning |
|---|---|
| **Search space** | The current range `[lo, hi]` of candidates. |
| **Predicate `P(x)`** | A boolean "is `x` feasible/acceptable?" function. |
| **Feasibility check** | The work done per mid to evaluate `P(mid)`. |
| **Lower bound** | First position where `a[i] >= x` (first not-less). |
| **Upper bound** | First position where `a[i] > x` (first greater). |
| **Answer space** | Binary searching over *values of the answer*, not indices. |
| **Boundary search** | Finding an extreme boundary (first true / last false). |
| **Sorted-half test** | In rotated arrays, one half of `[lo..hi]` is always sorted. |

### 2.4 Two families of binary search

```text
Binary search
├── Index search:    the array is sorted; search for a value's position
│                    (classic, lower/upper bound, first/last, floor/ceil)
└── Answer search:   the array is NOT sorted; you search over possible
                     ANSWERS (capacities, distances, days, speeds) with a
                     feasibility predicate P(x)
```

**Remember**: the second family is where interviews separate candidates. The key question is always *"if I can achieve answer `x`, can I also achieve `x+1`?"* — if yes, monotonicity holds and binary search applies.

---

## 3. Core Concepts

### 3.1 The Basic Loop (index search)

**Definition**  \nSearch a sorted array by comparing the middle element and discarding half.

**Intuition**  \nIf `a[mid] < x`, every element left of `mid` is also `< x` (sortedness) — they can never be the answer.

**How it works**

```text
a = [1, 3, 5, 7, 9], x = 7
lo=0 hi=4 mid=2: a[2]=5 < 7  -> lo=3
lo=3 hi=4 mid=3: a[3]=7 == 7 -> found
```

**Important observations**
- Use `mid = lo + (hi - lo) / 2` — never `(lo + hi) / 2` (overflows for large `lo+hi`).
- The loop invariant: *if the answer exists, it lies in `[lo, hi]`*.
- `while (lo <= hi)` with `lo = mid + 1` / `hi = mid - 1` always terminates and never revisits `mid`.

**Common mistake**  \nSetting `lo = mid` instead of `mid + 1` after `a[mid] < x` → infinite loop when `hi - lo == 1`.

---

### 3.2 Lower Bound and Upper Bound

**Definition**  \n**Lower bound** = first index `i` with `a[i] >= x`. **Upper bound** = first index `i` with `a[i] > x`.

**Why they are needed**  \nThey answer first/last occurrence, insertion position, floor/ceil, count of elements — all without writing custom loops.

**How it works**  \nMove `lo = mid + 1` when `mid` fails the condition; remember `mid` as a candidate when it succeeds:

```text
lower_bound: fail when a[mid] <  x   -> candidate when a[mid] >= x
upper_bound: fail when a[mid] <= x   -> candidate when a[mid] >  x
```

**Important observations**
- `count(x) = upper_bound - lower_bound`.
- `last occurrence of x = upper_bound(x) - 1`.
- `floor(x) = a[lb(x)-1]` if `lb(x) > 0`; `ceil(x) = a[lb(x)]` if `lb(x) < n`.

**Complexity**  \n`O(log n)` time, `O(1)` space.

---

### 3.3 Rotated Sorted Arrays (sorted-half test)

**Definition**  \nA sorted array rotated at some pivot: `[4,5,6,7,0,1,2]`. One half of any range `[lo..hi]` is always genuinely sorted.

**Core intuition**  \nCheck `a[lo] <= a[mid]`:
- If true → **left half is sorted**. Does `x` fall in `[a[lo], a[mid])`? If yes, search left; else search right.
- If false → **right half is sorted**. Does `x` fall in `(a[mid], a[hi]]`? If yes, search right; else search left.

**Why it is needed**  \nPlain binary search fails because the array is not globally sorted; the sorted-half test restores a decision rule.

**Common mistakes**
- With **duplicates**, `a[lo] == a[mid]` can't decide the sorted half — shrink `lo++` and accept `O(n)` worst case.
- Forgetting the minimum is the pivot — finding it uses the same halving logic on `a[mid] > a[hi]`.

**Complexity**  \n`O(log n)` distinct; `O(n)` worst case with duplicates.

---

### 3.4 Binary Search on Answer (feasibility search)

**Definition**  \nThe answer is not an index; it is a numeric quantity. Binary search over `[lo, hi] = [min possible, max possible]`, testing feasibility with a greedy/predicate function.

**Pattern of the question**  \n*"Minimize the maximum …"*, *"maximize the minimum …"*, or *"can we finish within X?"*

**How it works**

```text
lo = min possible answer,  hi = max possible answer
while lo < hi:
    mid = lo + (hi - lo) / 2
    if predicate(mid):   hi = mid        # mid works -> try smaller (min-max)
    else:                lo = mid + 1    # mid fails -> need bigger
return lo
```

**Example shape (Koko-style)**  \n`predicate(speed) = "can Koko eat all piles within h hours?"` → simulate `sum(ceil(pile/speed)) <= h`. Monotonic: if speed `s` works, any speed `> s` also works.

**Important observations**
- Half the work is designing the predicate; the binary search shell is boilerplate.
- The bounds **must** cover the true answer: `lo` = worst-but-possibly-valid, `hi` = trivially valid.

**Common mistakes**
- Wrong bounds (excluding the answer) → returns infeasible value.
- `while (lo < hi)` with `hi = mid` for min-max (correct) vs `hi = mid - 1` (skips the answer).

---

### 3.5 Search in 2D Matrices

| Shape | Strategy | Time |
|---|---|---|
| Rows + cols sorted, independent | Treat as sorted list: `mid → (mid/n, mid%n)` | `O(log(mn))` |
| Rows+cols sorted, staircase | Start top-right; discard a row or a column | `O(m+n)` |
| Each row sorted (row-wise) | Binary search row index by `row[0]`, then within row | `O(log m + log n)` |
| Row-wise sorted merged arrays | Binary search over value range with count | `O(log(max)·m)` |

---

## 4. PATTERN LIBRARY

### P1 — Classic Index Binary Search

#### What is the pattern?
Search a sorted array by repeatedly comparing the midpoint and discarding the impossible half.

#### When should I recognize it?
- "Given a **sorted** array, find `x` / insertion position / floor / ceil."
- Any `O(log n)` hint, or `n` up to `10^6–10^12` with a cheap check.

#### Core intuition
Sortedness makes the predicate "`a[i] >= x`" monotonic — one comparison eliminates half the candidates.

#### General approach / Generic algorithm
1. `lo = 0, hi = n - 1`.
2. While `lo <= hi`: `mid = lo + (hi - lo) / 2`.
3. `a[mid] == x` → return; `a[mid] < x` → `lo = mid + 1`; else `hi = mid - 1`.
4. Return `-1` / `lo` (insertion point).

#### C++ template
```cpp
int bs(const vector<int>& a, int x) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == x) return mid;
        if (a[mid] < x) lo = mid + 1; else hi = mid - 1;
    }
    return -1;
}
```

#### Time / Space
`O(log n)` — halving; `O(1)` — only indices stored.

#### Edge cases
Empty array (`hi = -1` → loop skipped), single element, `x` smaller/larger than all.

#### Common mistakes
`(lo+hi)/2` overflow; `lo = mid` infinite loop; returning `hi` instead of `lo` as insertion point.

#### Variations
Search insert position; floor/ceil; square root (predicate `mid*mid <= x`).

#### Practice mapping
- `01-Binary-Search-to-Find-X.cpp`, `04-Search-Insert-Position.cpp`, `05-Floor-and-Ceil.cpp`, `17-Sqrt-X.cpp`, `18-Nth-Root.cpp`

---

### P2 — Boundary Search (Lower/Upper Bound, First/Last Occurrence)

#### What is the pattern?
Binary search for the **first position where a predicate flips** from false to true (or vice versa) instead of an exact value.

#### When should I recognize it?
- "First / last occurrence", "count of `x`", "smallest index with …", duplicates present.

#### Core intuition
Keep a candidate answer whenever `mid` satisfies the condition, and always move toward the condition's boundary — you converge on the flip point.

#### General approach
1. `lo = 0, hi = n` (note `hi = n`, one past end).
2. If `P(mid)` (e.g. `a[mid] >= x`) holds → record `mid`, `hi = mid`; else `lo = mid + 1`.
3. The recorded/`lo` value is the first true position.

#### C++ template
```cpp
int lowerBound(const vector<int>& a, int x) {
    int lo = 0, hi = (int)a.size();          // hi = n
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] >= x) hi = mid; else lo = mid + 1;
    }
    return lo;                                // first index with a[i] >= x
}
```

#### Time / Space
`O(log n)` / `O(1)`.

#### Edge cases
All elements `< x` → returns `n`; all `>= x` → returns `0`; empty → `0`.

#### Common mistakes
Using `hi = n - 1` for boundary searches (misses "one past end" answers); mixing up `>` vs `>=` (lower vs upper bound).

#### Variations
Count = `ub - lb`; last occurrence = `ub - 1`; "last false" = `lb - 1`.

#### Practice mapping
- `02-Implement-Lower-Bound.cpp`, `03-Implement-Upper-Bound.cpp`, `06-First-and-Last-Occurrence.cpp`, `07-Count-Occurrences.cpp`, `23-Kth-Missing-Positive.cpp`

---

### P3 — Rotated Sorted Array Search

#### What is the pattern?
Binary search on an array that was sorted, then rotated — exactly one half of `[lo..hi]` is always sorted.

#### When should I recognize it?
- Keywords: "rotated sorted array", "search in rotated", "find minimum in rotated", "rotation count", "single element in sorted (pair-broken) array".

#### Core intuition
`a[lo] <= a[mid]` ⟹ left half sorted. Test whether `x` lies inside the sorted half; if not, the answer must be in the other half.

#### General approach
1. Compute which half is sorted.
2. Check if `x` is in that half's value range → go there; else go the other way.
3. For minimum/rotation count: compare `a[mid]` with `a[hi]` to decide which side holds the pivot.

#### C++ template
```cpp
int searchRotated(const vector<int>& a, int x) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == x) return mid;
        if (a[lo] <= a[mid]) {                       // left sorted
            if (a[lo] <= x && x < a[mid]) hi = mid - 1; else lo = mid + 1;
        } else {                                      // right sorted
            if (a[mid] < x && x <= a[hi]) lo = mid + 1; else hi = mid - 1;
        }
    }
    return -1;
}
```

#### Time / Space
`O(log n)` distinct values; `O(n)` worst case with duplicates (`lo++` fallback). `O(1)` space.

#### Edge cases
No rotation (already sorted); fully rotated; all duplicates; `lo == mid` or `mid == hi`.

#### Common mistakes
Wrong sorted-half test (`<` vs `<=`); forgetting `a[lo] <= a[mid]` must use `<=` so a single-element left half counts as sorted.

#### Variations
Find minimum (`10`); rotation count (`11`); search with duplicates (`09`); single non-paired element (`12`).

#### Practice mapping
- `08-Search-Rotated-I.cpp`, `09-Search-Rotated-II.cpp`, `10-Find-Minimum-in-Rotated.cpp`, `11-Find-Rotation-Count.cpp`, `12-Single-Element-in-Sorted.cpp`

---

### P4 — Binary Search on Answer (Feasibility / Min-Max)

#### What is the pattern?
Binary search over **possible answer values** using a monotonic feasibility predicate instead of over array indices.

#### When should I recognize it?
- Phrases: **"minimize the maximum …"**, **"maximize the minimum …"**, "smallest capacity such that …", "can we finish within X days/hours?"
- Classic shapes: ship capacity, book allocation, painters, aggressive cows, koko bananas, bouquets, gas stations, split array.

#### Core intuition
If a candidate answer `x` works, every larger (for min-max) or smaller (for max-min) candidate also works — feasibility is monotone → binary search applies.

#### General approach
1. Define `lo` = smallest possible answer, `hi` = answer that trivially works (e.g. sum, max element).
2. `mid = lo + (hi - lo) / 2`.
3. `predicate(mid)` = greedy simulation "can we do it with `mid`?"
4. True → `hi = mid` (min-max) or `lo = mid` (max-min); false → opposite.
5. Return `lo` when `lo == hi`.

#### C++ template
```cpp
// minimize the maximum — monotone: true for all x >= answer
long long lo = minPossible, hi = maxPossible;
while (lo < hi) {
    long long mid = lo + (hi - lo) / 2;
    if (feasible(mid)) hi = mid;      // mid works, try smaller
    else               lo = mid + 1;  // mid too small/large, move up
}
return lo;
// feasible(x): greedy scan, e.g. count groups needed <= k
```

#### Time / Space
`O(log(range) · cost(feasible))` — e.g. Koko: `O(log(maxPile) · n)`. Space `O(1)` + predicate's workspace.

#### Edge cases
`range = 0` (single candidate); predicate never true with given bounds (bounds wrong); overflow when `hi = 10^9` and predicate sums `hi · n` → use `long long`.

#### Common mistakes
Bounds not covering the answer; `while (lo < hi)` + `hi = mid - 1` skipping the answer; non-monotone predicate (binary search invalid — rethink).

#### Variations
Binary search the threshold of a path property (min max-edge / min max-effort on a grid); real-valued binary search (fixed iterations, `hi = 1e9`).

#### Practice mapping
- `19-Koko-Eating-Bananas.cpp`, `20-Minimum-Days-Bouquets.cpp`, `21-Smallest-Divisor.cpp`, `22-Capacity-to-Ship-Packages.cpp`, `24-Aggressive-Cows.cpp`, `25-Allocate-Books.cpp`, `26-Painters-Partition.cpp`, `27-Minimize-Max-Distance-Gas.cpp`, `30-Split-Array-Largest-Sum.cpp`

---

### P5 — Peak / Structured Binary Search (unsorted but ordered)

#### What is the pattern?
The array is not sorted, but a **structural guarantee** (neighbor relation) lets halving still work.

#### When should I recognize it?
- "Peak element" (greater than neighbors), "single element in sorted-with-pairs", "first bad version", any "locality" guarantee.

#### Core intuition
If `a[mid] < a[mid+1]`, a peak exists to the right (strictly increasing must eventually come down); else a peak exists to the left/equal. We only need *a direction that guarantees a peak*, not global order.

#### General approach
1. Keep `[lo, hi]` where a peak is guaranteed.
2. Use the neighbor comparison to discard half.
3. For pairs-sorted arrays: compare `mid` with `mid^1` (paired indices) to find the lone element.

#### C++ template
```cpp
int findPeak(const vector<int>& a) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] < a[mid + 1]) lo = mid + 1; else hi = mid;
    }
    return lo;
}
```

#### Time / Space
`O(log n)` / `O(1)` — halving still holds because one half always contains a peak.

#### Edge cases
`n == 1`; strictly increasing (last is peak); strictly decreasing (first is peak); flat regions.

#### Common mistakes
Accessing `a[mid+1]` when `mid == hi` (guaranteed by `lo < hi` — keep it); assuming uniqueness when multiple peaks exist (any peak accepted).

#### Variations
Find peak in 2D matrix (row+col peak, `O(m+n)` staircase); first bad version (predicate on monotone array).

#### Practice mapping
- `13-Find-Peak-Element.cpp`, `32-Peak-Element-2D.cpp`

---

### P6 — 2D Matrix Search

#### What is the pattern?
Flatten a sorted matrix into virtual indices, or walk a staircase discarding row/column.

#### When should I recognize it?
- "Sorted matrix, search `x`", "row-wise sorted matrix", "row with max 1s", "median of row-wise sorted".

#### Core intuition
Two independent sorted dimensions → either encode `k → (k/n, k%n)` as a virtual sorted array, or use top-right comparison (knowing both left and down directions).

#### General approach
- **Fully sorted rows+cols**: `mid` → `m[mid/n][mid%n]`; compare; discard half of `mn` cells.
- **Staircase**: start top-right; `> x` → move left (eliminate column); `< x` → move down (eliminate row).
- **Row-wise only**: binary search the first row ≥ x to find the row, then binary search within it.

#### C++ template
```cpp
bool searchMatrix(const vector<vector<int>>& m, int x) {
    int r = m.size(), c = m[0].size(), i = 0, j = c - 1;
    while (i < r && j >= 0) {
        if (m[i][j] == x) return true;
        if (m[i][j] > x) j--; else i++;
    }
    return false;
}
```

#### Time / Space
Staircase `O(m+n)`; virtual flatten `O(log(mn))`; row-wise `O(m + n)` worst, `O(log m + log n)` typical.

#### Edge cases
Empty matrix; single row/column; all equal elements; target outside matrix range.

#### Common mistakes
Treating `vector<vector<int>>` as contiguous (rows separately allocated); wrong row-major index math; forgetting `m[0]` access on empty input.

#### Variations
Row-wise sorted median (binary search value + count-leq per row); peak in 2D (`32`).

#### Practice mapping
- `14-Search-in-2D-I-Flat.cpp`, `15-Search-in-2D-II-Row-Col.cpp`, `16-Row-with-Max-1s.cpp`, `31-Median-in-Rowwise-Sorted.cpp`

---

## 5. PATTERN RECOGNITION

| If the problem says... | Think about... |
|---|---|
| "sorted array" + find/insert/count | Classic index binary search / lower-upper bound |
| "first / last occurrence" | Boundary search (`lo=0, hi=n`) |
| "rotated sorted array" | Sorted-half test binary search |
| "find minimum / rotation count in rotated" | Pivot-halving (`a[mid]` vs `a[hi]`) |
| "minimize the maximum …" / "maximize the minimum …" | **Binary search on answer** + feasibility predicate |
| "can we finish within X?" / "is X possible?" | Feasibility predicate, monotone in X |
| "peak element" (neighbor-guaranteed) | Structured binary search on direction |
| sqrt / nth root / power check | Predicate `mid^k <= x` |
| "row and column sorted matrix" | Flatten `O(log mn)` or staircase `O(m+n)` |
| `n` up to 10^9–10^12 with a cheap check | Answer-space binary search (`~40` iterations) |
| "count elements ≤ x across rows" | Binary search value + per-row count |
| LIS in `O(n log n)` / patience | Binary search inside DP (§16) |

**Decision rules**
1. Is there sortedness (or a monotone predicate)? → search, don't scan.
2. Is the **answer** a number to minimize/maximize? → binary search on answer, design `feasible(x)`.
3. Only one half sorted (rotated)? → sorted-half test.
4. No monotonicity at all? → binary search does **not** apply — use two pointers, DP, or greedy.

---

## 6. BRUTE → BETTER → OPTIMAL THINKING

### Search in a sorted array
- **Brute** — linear scan: `O(n)`. Works, but wastes sortedness.
- **Better** — binary search: `O(log n)`. Key insight: sortedness makes comparisons eliminate half.
- **Optimal** — `O(log n)` is a hard lower bound for comparison-based search (decision tree depth ≥ `log n`). **This is optimal.**

### First / last occurrence & counting
- **Brute** — scan both directions from a hit: worst `O(n)`.
- **Better** — write two boundary binary searches manually: `O(log n)`.
- **Optimal** — STL `lower_bound`/`upper_bound`: `O(log n)`, less code, fewer off-by-one bugs.

### Search in a rotated array
- **Brute** — linear scan: `O(n)`.
- **Better** — find minimum first (`O(log n)`), rotate virtually, plain BS: `O(log n)` but two steps.
- **Optimal** — single loop with sorted-half test: `O(log n)` time, `O(1)` space. Duplicates force `O(n)` worst case (information-theoretically unavoidable).

### Min-max allocation problems (Koko, ships, books)
- **Brute** — try every candidate answer, simulate each: `O(range · n)` (e.g. `10^9 · n` — TLE).
- **Better** — observe feasibility is monotone; sort candidate answers → `O(range log(range) · n)`.
- **Optimal** — binary search directly on the numeric range: `O(log(range) · n)`. The simulation cannot be improved below `O(n)`, so this is optimal for the standard constraints.

### Square root / nth root
- **Brute** — linear/binary search over `1..x`: `O(x)`.
- **Better** — binary search with overflow-safe check: `O(log x)`.
- **Optimal** — same `O(log x)`; use `long long` mid-products or division-based comparison to avoid overflow.

### Key transferable idea
> Every "brute → optimal" path here is the same move: **find the monotone structure, then binary search it.** The entire chapter is one idea applied to three targets: indices, boundaries, answers.

---

## 7. C++ / STL TOOLKIT

| Tool | Syntax | What it does | Complexity |
|---|---|---|---|
| `binary_search` | `binary_search(a.begin(), a.end(), x)` | exists? | `O(log n)` |
| `lower_bound` | `lower_bound(a.begin(), a.end(), x)` | first `>= x` (or first `P` true) | `O(log n)` |
| `upper_bound` | `upper_bound(a.begin(), a.end(), x)` | first `> x` | `O(log n)` |
| Count range | `upper_bound - lower_bound` | occurrences of `x` | `O(log n)` |
| Custom predicate | `lower_bound(a.begin(), a.end(), x, comp)` | first where `comp(elem, x)` false | `O(log n)` |

**Key facts**
- All require a **partitioned range** w.r.t. the predicate — not necessarily sorted values.
- They return **iterators**; subtract `a.begin()` for indices.
- Two-iterator form: `lower_bound(a.begin() + l, a.begin() + r, x)` searches a sub-range.

```cpp
// first index with a[i] >= x
int lb = (int)(lower_bound(a.begin(), a.end(), x) - a.begin());
// last index with a[i] <= x
int last = (int)(upper_bound(a.begin(), a.end(), x) - a.begin()) - 1;
```

**Binary search on answer with a lambda**
```cpp
long long lo = L, hi = R;
auto ok = [&](long long mid) -> bool { /* feasibility */ return ...; };
while (lo < hi) { long long mid = lo + (hi - lo) / 2; ok(mid) ? hi = mid : lo = mid + 1; }
```

**Common mistakes**
- Calling `lower_bound` on an unsorted array → garbage (UB by contract).
- Comparing `*it == x` then using `it` from `upper_bound` (points past).
- `lower_bound` on `vector<pair<...>>` compares `first` only — use a custom comparator for other orderings.

---

## 8. COMPLEXITY GUIDE

| Operation | Time | Space | Why |
|---|---:|---:|---|
| Index binary search | `O(log n)` | `O(1)` | halving |
| Lower/upper bound | `O(log n)` | `O(1)` | boundary halving |
| Rotated search (distinct) | `O(log n)` | `O(1)` | sorted-half discard |
| Rotated search (duplicates) | `O(n)` worst | `O(1)` | ambiguity → linear shrink |
| Binary search on answer | `O(log R · T)` | `O(T)` | `R` = value range, `T` = predicate cost |
| Sqrt / nth root | `O(log x)` | `O(1)` | value halving |
| 2D staircase | `O(m+n)` | `O(1)` | discard row or column |
| 2D flatten | `O(log(mn))` | `O(1)` | virtual array |
| Row-wise 2D search | `O(log m + log n)` | `O(1)` | two-level BS |
| Median of two sorted | `O(log(min(n,m)))` | `O(1)` | partition binary search |
| Kth of two sorted | `O(log(min(n,m)))` | `O(1)` | partition binary search |

**How to estimate**
1. Count **iterations of the loop** (log of the search space).
2. Multiply by **cost per iteration** (usually the predicate: one scan → `O(n)`).
3. Add preprocessing (sorting, LPS building) if any.

**Rules of thumb**
- `2^40 ≈ 10^12` → 40 iterations suffice for any range up to `10^12`.
- Predicate of `O(n)` + range `10^9` → `~30·n` operations: fine for `n ≤ 10^5`.
- If predicate itself is `O(n log n)` (needs sorting), sort **once** outside if data is shared — otherwise accept `log R · n log n` and check constraints.

---

## 9. EDGE CASES

- **Empty array** — loop must not execute (`hi = -1` for `hi = n-1` form; `hi = 0` for `hi = n` form).
- **Single element** — `lo == hi` immediately; verify branch logic doesn't skip.
- **`x` smaller / larger than everything** — returns `-1` / insertion `0` / `n`.
- **All elements equal** — boundary searches must still terminate; rotated search degrades.
- **Overflow** — `(lo + hi) / 2` with indices near `2·10^9`; `mid·mid` in sqrt; `mid·n` in predicates → `long long`.
- **`lo == hi` infinite loop** — after `hi = mid`, if `hi - lo == 1` then `mid == lo` → no progress; ensure `hi = mid` only when `mid < hi` is guaranteed (`lo < hi` loop invariant).
- **Range size 1 answer** — min-max problems where `lo == hi` on first check.
- **Negative answers / zero** — bounds must include them (e.g. `lo = 0` wrong if answer can be `-1`).
- **2D empty matrix** — `m.empty() || m[0].empty()` guard.
- **Predicate cost overflow** — capacities × items exceeding `2·10^9` inside feasibility check.

---

## 10. COMMON MISTAKES

| # | Mistake | What goes wrong | Why | How to avoid |
|---|---|---|---|---|
| 1 | `(lo + hi) / 2` | Overflow → negative mid | `lo+hi > INT_MAX` | `lo + (hi - lo) / 2` |
| 2 | `lo = mid` after `a[mid] < x` | Infinite loop | No progress when `hi - lo == 1` | `lo = mid + 1` |
| 3 | `hi = n - 1` in boundary search | Misses "one past end" answers | Answer can be `n` | Use `hi = n`, `lo < hi` |
| 4 | `>` vs `>=` confusion | lower vs upper bound swapped | Off-by-one semantics | Write the condition on paper first |
| 5 | Wrong sorted-half test in rotated | Wrong direction | `<` vs `<=` on `a[lo] <= a[mid]` | Single-element half must count as sorted (`<=`) |
| 6 | Bounds exclude the answer | Returns infeasible value | `lo`/`hi` too tight | `lo` = worst plausible, `hi` = trivially works |
| 7 | `hi = mid - 1` in min-max loop | Skips the answer | Shrinks past feasible point | For `while (lo < hi)` min-max: `hi = mid` |
| 8 | Overflow inside predicate | `int` wraps → wrong feasibility | capacity × count > 2e9 | `long long` accumulators |
| 9 | `lower_bound` on unsorted data | Garbage result | Contract requires partitioned range | Sort first or scan |
| 10 | `binary_search` returns bool | Lost the position | API misuse | Use `lower_bound` for positions |
| 11 | Not handling duplicates in rotated | TLE / wrong index | Ambiguous halves | `lo++` fallback or accept `O(n)` |
| 12 | Empty container | `a[0]` crash / `hi` negative | Missing guard | Early return; test `n = 0` first |

**Conceptual mistakes**
- Assuming binary search needs *sorted values* — it only needs a **monotone predicate** (this unlocks answer-space search).
- Trying binary search on a non-monotone predicate (e.g. "sum equals exactly K" is not monotone) → use two pointers / prefix maps instead.

---

## 11. IMPORTANT FORMULAS / RULES

```text
Steps to halve N:        ceil(log2(N + 1))
2^10 ≈ 10^3, 2^20 ≈ 10^6, 2^30 ≈ 10^9, 2^40 ≈ 10^12

count(x)        = upper_bound(x) - lower_bound(x)
last index of x = upper_bound(x) - 1
floor(x)        = a[lb(x) - 1]   if lb(x) > 0
ceil(x)         = a[lb(x)]       if lb(x) < n
insert position = lower_bound index

Min-max loop:    while (lo < hi) { mid; feasible? hi = mid : lo = mid + 1; }
Max-min loop:    while (lo < hi) { mid; feasible? lo = mid + 1 : hi = mid; }

sqrt(x):  hi = x (or x/2 + 1); feasible mid: mid <= x / mid  (overflow-safe)
nth-root: feasible mid: power(mid, k) <= x using long long with early clamp

Rotated minimum:  a[mid] > a[hi] ? lo = mid + 1 : hi = mid
Rotation count:   first index where a[i] < a[0]
```

**Decision rules / invariants**
1. **Loop invariant**: the answer is always inside `[lo, hi]`.
2. Every iteration must **strictly shrink** `[lo, hi]` (progress guarantee).
3. `while (lo <= hi)` pairs with `lo = mid+1 / hi = mid-1`; `while (lo < hi)` pairs with `hi = mid / lo = mid+1` — never mix the two styles.

---

## 12. REUSABLE TEMPLATES

```cpp
// 1. Classic exact search — returns index or -1
int bs(const vector<int>& a, int x) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == x) return mid;
        if (a[mid] < x) lo = mid + 1; else hi = mid - 1;
    }
    return -1;
}

// 2. Lower bound — first index with a[i] >= x  (hi = n form)
int lowerBound(const vector<int>& a, int x) {
    int lo = 0, hi = (int)a.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] >= x) hi = mid; else lo = mid + 1;
    }
    return lo;
}

// 3. Binary search on answer — minimize maximum (feasible monotone ↑)
long long bsAnswer(long long L, long long R, auto&& feasible) {
    while (L < R) {
        long long mid = L + (R - L) / 2;
        if (feasible(mid)) R = mid; else L = mid + 1;
    }
    return L;
}

// 4. Search in rotated array (distinct values)
int searchRotated(const vector<int>& a, int x) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == x) return mid;
        if (a[lo] <= a[mid]) {
            if (a[lo] <= x && x < a[mid]) hi = mid - 1; else lo = mid + 1;
        } else {
            if (a[mid] < x && x <= a[hi]) lo = mid + 1; else hi = mid - 1;
        }
    }
    return -1;
}
```

## 13. ADVANCED CONCEPTS

### 13.1 Ternary / real-valued search
For unimodal functions (maximize a concave function), compare `mid1 = lo + (hi-lo)/3` and `mid2 = hi - (hi-lo)/3`, discard the third that is worse → `O(log(range/ε))` with fixed iterations (e.g. 100 doubles passes).

### 13.2 Binary search on the answer for graphs
Combine with BFS/DSF-check: "minimum maximum edge along any path" → binary search threshold `k`, keep only edges `≤ k`, test connectivity (`O(log maxW · (V+E))`). Same for "swim in rising water" style problems (also solvable with a heap — §15).

### 13.3 Binary search inside DP (LIS `O(n log n)`)
The patience-sorting tails array is maintained with `lower_bound` — merging §04 and §16. Also binary search the *value* in 2D row-sorted matrices for medians/counts.

### 13.4 Partition binary search (median / kth of two sorted arrays)
Binary search the **cut position** in one array (range `0..n`), validate with 4 boundary comparisons `maxLeft ≤ minRight` → `O(log(min(n,m)))`, the gold-standard hard binary search.

### 13.5 Parametric search on discrete structures
When the answer is a count/selection (not a range of values), parametric search applies a monotone predicate over a *discrete ordered* structure — the same template, different domain.

### 13.6 Overflow-safe comparisons
Instead of `mid * mid <= x`, write `mid <= x / mid` (integer division) when `mid > 0`; avoids 64-bit where unnecessary and survives adversarial bounds.

---

## 14. CONNECTIONS BETWEEN PATTERNS

```text
Sorted array
    |
    v
Index binary search  --------->  lower/upper bound (boundaries)
    |                                   |
    v                                   v
Rotated search (sorted-half)     count / floor / ceil / insert
                                       |
                                       v
Monotone predicate "P(x)"  ==>  BINARY SEARCH ON ANSWER  (the general form)
                                       |
                       +---------------+----------------+
                       v                                v
              greedy feasibility check          graph threshold check
              (Koko, ships, books)             (min max-edge path, §15)
                                       |
                                       v
                              binary search + DP (LIS, §16)

Two pointers (§10) <--- same "discard half the space" philosophy ---> binary search
Sorting (§02) produces the sortedness this chapter consumes.
```

**Mental map**
1. Sort first (§02) → then binary search or two pointers.
2. When the *question* is a number to minimize/maximize → binary search on answer.
3. When the predicate runs on a graph → combine with BFS/DSU (§15).
4. When the predicate is a DP value → binary search inside DP (§16).

---

## 15. PROBLEM → PATTERN MAPPING

*(Reference only — solutions and approaches live in the `.cpp` files.)*

### Classic index search
- `01-Binary-Search-to-Find-X.cpp`
- `04-Search-Insert-Position.cpp`
- `05-Floor-and-Ceil.cpp`

### Lower / upper bound & boundaries
- `02-Implement-Lower-Bound.cpp`
- `03-Implement-Upper-Bound.cpp`
- `06-First-and-Last-Occurrence.cpp`
- `07-Count-Occurrences.cpp`
- `23-Kth-Missing-Positive.cpp`

### Rotated arrays
- `08-Search-Rotated-I.cpp`
- `09-Search-Rotated-II.cpp`
- `10-Find-Minimum-in-Rotated.cpp`
- `11-Find-Rotation-Count.cpp`
- `12-Single-Element-in-Sorted.cpp`

### Peak / structured search
- `13-Find-Peak-Element.cpp`
- `32-Peak-Element-2D.cpp`

### 2D matrix search
- `14-Search-in-2D-I-Flat.cpp`
- `15-Search-in-2D-II-Row-Col.cpp`
- `16-Row-with-Max-1s.cpp`
- `31-Median-in-Rowwise-Sorted.cpp`

### Sqrt / root
- `17-Sqrt-X.cpp`
- `18-Nth-Root.cpp`

### Binary search on answer (feasibility)
- `19-Koko-Eating-Bananas.cpp`
- `20-Minimum-Days-Bouquets.cpp`
- `21-Smallest-Divisor.cpp`
- `22-Capacity-to-Ship-Packages.cpp`
- `24-Aggressive-Cows.cpp`
- `25-Allocate-Books.cpp`
- `26-Painters-Partition.cpp`
- `27-Minimize-Max-Distance-Gas.cpp`
- `30-Split-Array-Largest-Sum.cpp`

### Two sorted arrays (partition search)
- `28-Median-of-Two-Sorted.cpp`
- `29-Kth-Element-of-Two-Sorted.cpp`

---

## 16. QUICK REVISION SHEET

**Concepts (30 seconds)**
- Binary search = halving a space governed by a **monotone predicate**; `~log2(N)` steps (`N=10^12 → 40`).
- Two families: **index search** (sorted data) and **answer search** (feasibility on values).
- Boundary search uses `hi = n`, `lo < hi`, and keeps a candidate.

**Recognition clues**
- sorted / first-last / count → bounds; rotated → sorted-half; "min-max / max-min" → answer BS; peak → neighbor direction; 2D sorted → flatten or staircase.

**Algorithms**
```text
mid = lo + (hi - lo) / 2                       (overflow-safe)
lb: first a[i] >= x    (hi = n form)
min-max: while (lo<hi): feasible(mid) ? hi = mid : lo = mid+1
rotated: a[lo] <= a[mid] => left half sorted
```

**Formulas**
```text
count = ub - lb;   last = ub - 1
insert pos = lb;   sqrt: mid <= x/mid
steps = ceil(log2(N+1))
```

**Complexity cheat sheet**
| Task | Time |
|---|---|
| index/boundary | `O(log n)` |
| rotated (distinct) | `O(log n)` (dupes `O(n)`) |
| answer BS | `O(log R · predicate)` |
| 2D staircase / flatten | `O(m+n)` / `O(log mn)` |

**Common mistakes to avoid**
` (lo+hi)/2` overflow · `lo=mid` infinite loop · `hi=n-1` misses end · wrong `>=` · bounds excluding answer · int overflow in predicate · `lower_bound` on unsorted.

**Templates to remember** — classic `bs`, `lowerBound` (`hi=n`), `bsAnswer` (min-max), `searchRotated` (sorted-half).

**Decision rules**
1. Monotone predicate? → binary search it. 2. Answer is a number? → search the answer. 3. Not monotone? → two pointers / DP / greedy instead.

---

## 17. INTERVIEW CHECKLIST

- [ ] Can I explain why binary search works (loop invariant) in one sentence?
- [ ] Can I write the `while (lo <= hi)` and `while (lo < hi)` templates without bugs?
- [ ] Can I derive lower bound vs upper bound from `>=` / `>` conditions?
- [ ] Can I handle rotated arrays with the sorted-half test (and explain duplicates)?
- [ ] Can I spot "binary search on answer" from a min-max phrasing?
- [ ] Can I design a correct `feasible(x)` and justify its monotonicity?
- [ ] Can I choose safe bounds that provably contain the answer?
- [ ] Can I write overflow-safe mid and predicate arithmetic?
- [ ] Can I calculate `O(log R · T)` and confirm it fits constraints?
- [ ] Can I list edge cases (empty, single, all-equal, overflow) before coding?
- [ ] Can I move from brute force (`O(range·n)`) to optimal (`O(log range·n)`) and explain the jump?

<!-- done -->
