# 10 — Sliding Window and Two Pointer — Complete Pattern-Based Notes

---

## 1. Topic Overview

**Sliding window** maintains a contiguous range `[l, r]` that satisfies a constraint while expanding `r` and shrinking `l` — turning naive `O(n²)`/`O(n³)` subarray enumeration into `O(n)`.

**What it is**
- **Fixed window**: size `k` — slide by adding one element, removing one.
- **Variable window**: grow `r` until invalid, then shrink `l` until valid again.
- **Two pointers**: paired indices `i < j` on a *sorted* array (or same-direction window) guided by a comparison.

**Why it is important**
- Longest/shortest subarray-with-property is the single most common interview shape.
- The "at-most-K → exactly-K" subtraction trick appears everywhere.
- Two pointers replace `O(n²)` pair search with `O(n)` after sorting.

**Where it is used**
- Longest substring without repeats; maximum consecutive ones with flips; fruits in baskets.
- Count subarrays with sum K / exactly K distinct; minimum window substring.
- 2-sum/3-sum/4-sum on sorted arrays; container with most water.

**How it connects to other topics**
- §03 Arrays: prefix sums feed window sums.
- §05 Strings: all substring problems are windows over characters.
- §04 Binary Search: some window problems binary-search the window length.
- §16 DP: subarray DP shares the "ending here" state idea.

**Interview memory hook:** *Fixed `k` → add/remove slide. Variable → expand+shrink with `while`. Exactly K → atMost(K) − atMost(K−1). Sorted pair-sum → two pointers.*

---

## 2. Fundamentals

### 2.1 Window mechanics

```text
a = [1, 3, -1, -3, 5, 3, 6, 7],  k = 3

r=2: window [0..2] sum = 3
r=3: add a[3], remove a[0] -> window [1..3] sum = -1
each step: +a[r] - a[l-1]      (fixed size)
```

```text
variable window (longest with <= K distinct):

 r expands ---->
[l ......... r]   when distinct > K: l++ until valid again
```

### 2.2 Invariants (what must always be true)

- **Fixed**: `r - l + 1 == k` after each step; answer updated at every step.
- **Variable**: when the `while` exits, `[l..r]` is the *smallest valid window ending at r*; `r` only moves forward → total work `O(n)`.

### 2.3 The at-most / exactly trick

```text
exactly(K) = atMost(K) - atMost(K-1)

atMost counts every valid window ending at r:  res += r - l + 1
```

This converts "exactly" constraints (exactly K distinct, sum == K, exactly K odds) into two easy at-most passes.

### 2.4 Terminology

| Term | Meaning |
|---|---|
| **Expand / shrink** | Move `r` right (add) / move `l` right (remove). |
| **Freq map** | Count of elements in the current window. |
| **`distinct` counter** | Number of keys with positive count (avoid `map.size()` if using array). |
| **At-most-K** | Count windows whose property value ≤ K. |
| **Two pointers (sorted)** | `l` from left, `r` from right, move by comparison with target. |

---

## 3. Core Concepts

### 3.1 Fixed-size window

**Definition**  \nExactly `k` elements in view; each step adds `a[r]` and removes `a[l]`.

**When**: max/sum of every contiguous subarray of length `k`.

**How it works**

```cpp
long long sum = 0;
for (int i = 0; i < n; i++) {
    sum += a[i];
    if (i >= k) sum -= a[i - k];
    if (i >= k - 1) ans = max(ans, sum);
}
```

**Complexity**  \n`O(n)` time, `O(1)` space (prefix-sum alternative: `O(n)` with `O(n)` precompute).

---

### 3.2 Variable-size window (longest / shortest valid)

**Definition**  \nGrow `r` until the window becomes invalid (or valid), then adjust `l`.

**General algorithms**
- **Longest valid**: for each `r`, shrink while invalid → record `r - l + 1` when valid.
- **Shortest valid**: for each `r`, shrink while *still valid* → record min before it breaks.

**Invariant**: after the inner `while`, `[l..r]` is the canonical (smallest valid / just-valid) window ending at `r`. Since `l` and `r` never move left, total operations ≤ `2n` → `O(n)`.

**Common mistakes**
- Using `if` instead of `while` to shrink (fails when one removal isn't enough).
- Updating the answer *before* restoring validity (longest) or *after* breaking it (shortest).

---

### 3.3 Frequency / distinct-count windows

**Definition**  \nMaintain a count array/map of the current window; distinct = number of positive counts.

**When**: longest substring with ≤ K distinct / without repeats / with character limits.

**C++ detail**: for a known alphabet use `int cnt[26]` + a `distinct` counter incremented when `cnt[c]++ == 0`. With `unordered_map`, `f.size()` works but `erase` is needed when a count hits 0 (map keeps zero entries otherwise!).

**Complexity**  \n`O(n)` with array (`O(σ)` space) or `O(n)` average with hashmap.

---

### 3.4 At-most → exactly subtraction

**Definition**  \n`exactly(K) = atMost(K) − atMost(K−1)`.

**Why**  \n"Exactly K" is hard to maintain with a single window (a window may pass through validity in complex ways), but "at most K" is a clean shrink condition.

**How it works**: write `countAtMost(k)` using the standard expand/shrink loop with condition `distinct > k`; call it twice.

**Works for**: exactly K distinct, sum == K (`atMost` on ≤ K minus ≤ K−1 with non-negative... careful: for sum==K with negatives use prefix-map instead), exactly K odds, exactly K zeros (nice subarrays).

**Common mistake**  \nApplying the trick to sum==K with negative numbers — at-most on sums is not monotone; use prefix sums + map (§03).

---

### 3.5 Sorted two pointers (opposite ends)

**Definition**  \nOn a **sorted** array, `l` from the left, `r` from the right; move based on `sum` vs `target`.

**Why it works**  \nIf `a[l] + a[r] < target`, no pair with this `a[l]` can reach the target (array sorted) → `l++` discards a whole row.

**Complexity**  \n2-sum `O(n)`; 3-sum `O(n²)` (fix one, two-pointer the rest, **skip duplicates**); 4-sum `O(n³)`.

**Common mistake**  \nForgetting to sort first, or not skipping duplicate values (wrong unique-answer output).

---

### 3.6 Longest window with a lazily-maintained metric (maxFreq trick)

**Definition**  \nFor "replace up to K chars" style problems, don't track exact validity — track `maxFreq` (most frequent char in window): window is valid if `windowLen − maxFreq ≤ K`.

**Intuition**  \nOnly the dominant character matters; the rest are the ones we'd replace. `maxFreq` never needs to shrink (monotone trick) — this keeps the loop strictly linear.

---

## 4. PATTERN LIBRARY

### P1 — Fixed-Size Window

#### What is the pattern?
Maintain a window of exactly `k` elements, sliding it one step at a time with `+add / −remove`.

#### When should I recognize it?
- "Every subarray of size k", "max sum of k consecutive", "average of each window", "max consecutive ones with k flips" (fixed inner condition).

#### Core intuition
Consecutive windows share `k−1` elements — reuse the previous sum instead of recomputing.

#### Generic algorithm
1. For `i` in `0..n-1`: `sum += a[i]`.
2. If `i >= k`: `sum -= a[i-k]`.
3. If `i >= k-1`: update answer.

#### C++ template
```cpp
long long maxSumK(const vector<int>& a, int k) {
    long long sum = 0, best = LLONG_MIN;
    for (int i = 0; i < (int)a.size(); i++) {
        sum += a[i];
        if (i >= k) sum -= a[i - k];
        if (i >= k - 1) best = max(best, sum);
    }
    return best;
}
```

#### Time / Space
`O(n)` / `O(1)`.

#### Edge cases
`k > n` (no full window); `k == n`; `k == 1`; negative numbers (best starts at `-inf`, not `0`).

#### Common mistakes
Updating before the first full window; `int` sum overflow → `long long`.

#### Variations
Deque-based fixed window max (§09 pattern 4); prefix-sum equivalent `pref[i+k] - pref[i]`.

#### Practice mapping
- `12-Max-Points-from-Cards.cpp`, `05-Binary-Subarrays-With-Sum.cpp` (prefix variant)

---

### P2 — Variable Window (longest / shortest with constraint)

#### What is the pattern?
Expand `r` one step at a time; when invalid (or after recording), shrink `l` with `while`.

#### When should I recognize it?
- "Longest substring/subarray with …", "shortest subarray with sum ≥ K", "longest without repeating", "fruits into baskets", "k distinct characters".

#### Core intuition
Each `r` has a canonical minimal `l` — since both pointers advance monotonically, total work is `2n`.

#### Generic algorithm
```text
for r in 0..n-1:
    add a[r]
    while invalid:        remove a[l], l++
    update answer         (longest: after while;  shortest: inside while before break)
```

#### C++ template
```cpp
int longestWindow(const vector<int>& a, auto&& valid) {
    int l = 0, best = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        // add a[r]
        while (!valid(/*window l..r*/)) { /* remove a[l] */ l++; }
        best = max(best, r - l + 1);
    }
    return best;
}
```

#### Time / Space
`O(n)` time (each index enters/leaves once) / `O(σ)` for freq state.

#### Edge cases
No valid window (answer 0); whole array valid; single element; `l` over-shooting past `r`.

#### Common mistakes
`if` instead of `while`; forgetting `while` exit ordering for shortest-window problems; updating answer at wrong point.

#### Variations
last-seen jump (`l = max(l, last[c]+1)`) for no-repeat; maxFreq metric for replacement problems.

#### Practice mapping
- `01-Longest-Substring-Without-Repeat.cpp`, `03-Fruits-into-Baskets.cpp`, `04-Longest-Repeating-Char-Replacement.cpp`, `10-Longest-Substring-K-Distinct.cpp`, `02-Max-Consecutive-Ones-III.cpp`

---

### P3 — At-Most → Exactly Subtraction

#### What is the pattern?
Compute `count(≤K) − count(≤K−1)` to answer "exactly K" counting questions.

#### When should I recognize it?
- "Count subarrays with **exactly** K distinct", "exactly K odd numbers", "binary subarrays with sum exactly K" (non-negative), "nice subarrays".

#### Core intuition
"Exactly K" lacks a clean local invalid-condition; "at most K" is monotone (add → maybe shrink when > K) and counts every valid ending window: `res += r - l + 1`.

#### Generic algorithm
1. Write `atMost(k)` with shrink condition `violating > k`.
2. Return `atMost(K) - atMost(K-1)`; guard `K < 1 → 0`.

#### C++ template
```cpp
int atMost(vector<int>& a, int k) {
    if (k < 0) return 0;
    unordered_map<int,int> f; int l = 0; long long res = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        if (f[a[r]]++ == 0) { /* distinct++ if tracking counter */ }
        while ((int)f.size() > k) { if (--f[a[l]] == 0) f.erase(a[l]); l++; }
        res += r - l + 1;
    }
    return res;
}
int exactlyK(vector<int>& a, int k) { return atMost(a, k) - atMost(a, k - 1); }
```

#### Time / Space
Two passes of `O(n)` → `O(n)` / `O(σ)`.

#### Edge cases
`K = 0`; `K < 0` (return 0); negative array elements (breaks sum-based at-most).

#### Common mistakes
Not handling `k < 0`; map zero-entries not erased (distinct count wrong); using it for sums with negatives.

#### Variations
Prefix-sum + map for sum==K with arbitrary values (§03 pattern).

#### Practice mapping
- `07-Subarrays-With-K-Distinct.cpp`, `06-Count-Nice-Subarrays.cpp`, `05-Binary-Subarrays-With-Sum.cpp`, `11-Substrings-Containing-ABC.cpp`, `13-Count-Substrings-Beauty.cpp` (§05)

---

### P4 — Sorted Two Pointers / Three Sum family

#### What is the pattern?
Sort, then fix one/two elements and move pointers inward based on sum vs target — skipping duplicates.

#### When should I recognize it?
- "Pair/triplet/quadruplet with sum = target", "container with most water", "three sum closest", "two sum II (sorted input)".

#### Core intuition
Sorted order makes the search monotone in each pointer: too small → advance left; too big → retreat right. Each move discards a row of the pair matrix.

#### Generic algorithm (3-sum)
1. Sort.
2. Fix `i`; run two pointers `l = i+1, r = n-1`.
3. `sum < T → l++`; `sum > T → r--`; `sum == T → record, skip dups on both sides, l++, r--`.
4. Skip `a[i] == a[i-1]` at the outer level too.

#### C++ template
```cpp
vector<vector<int>> threeSum(vector<int>& a) {
    sort(a.begin(), a.end());
    vector<vector<int>> out;
    for (int i = 0; i < (int)a.size(); i++) {
        if (i > 0 && a[i] == a[i-1]) continue;
        int l = i + 1, r = (int)a.size() - 1;
        while (l < r) {
            long long s = 0LL + a[i] + a[l] + a[r];
            if (s == 0) {
                out.push_back({a[i], a[l], a[r]});
                while (l < r && a[l] == a[l+1]) l++;
                while (l < r && a[r] == a[r-1]) r--;
                l++; r--;
            } else if (s < 0) l++; else r--;
        }
    }
    return out;
}
```

#### Time / Space
2-sum `O(n)/O(1)` after sort (`O(n log n)` with sort); 3-sum `O(n²)`; 4-sum `O(n³)`; space `O(1)` excluding output.

#### Edge cases
No solution; all zeros; duplicates giving identical triplets; target extremes (overflow → `long long` sums).

#### Common mistakes
Not sorting → can't move pointers logically; missing duplicate skips → repeated outputs; `int` overflow on sums near `2·10^9`.

#### Variations
Two pointers opposite ends (container water); same-direction (remove duplicates / partition); pair sum on *unsorted* → hash map.

#### Practice mapping
- `31-Three-Sum.cpp`, `32-Four-Sum.cpp`, `14-Two-Sum.cpp`, `03-Arrays/14-Two-Sum.cpp`, `26-Pairs-with-Given-Sum-DLL.cpp` (§06)

---

### P5 — Minimum Window / Constrained Coverage (have/need)

#### What is the pattern?
Expand `r`; track "how many required items are satisfied"; shrink while still satisfying, recording minimal lengths.

#### When should I recognize it?
- "Minimum window substring containing all characters of T", "smallest subarray covering all required elements", "longest substring containing three distinct letters with limits".

#### Core intuition
Maintain `need` (counts required) and `have` (how many requirements met). When `have == need`, the window is valid → shrink to find the tightest; the answer is the smallest valid window ever seen.

#### Generic algorithm
1. Count pattern → `need`.
2. Expand `r`; on adding a matching char, `have++` if it reaches required count.
3. While `have == need`: record `r-l+1`, shrink `l`, update `have` when a requirement drops.
4. Answer = min recorded window (empty if none).

#### C++ template
```cpp
string minWindow(string s, string t) {
    unordered_map<char,int> need; for (char c : t) need[c]++;
    int have = 0, l = 0, bestLen = INT_MAX, bestL = 0;
    unordered_map<char,int> win;
    for (int r = 0; r < (int)s.size(); r++) {
        win[s[r]]++;
        if (need.count(s[r]) && win[s[r]] == need[s[r]]) have++;
        while (have == (int)need.size()) {
            if (r - l + 1 < bestLen) { bestLen = r - l + 1; bestL = l; }
            if (need.count(s[l]) && win[s[l]] == need[s[l]]) have--;
            win[s[l++]]--;
        }
    }
    return bestLen == INT_MAX ? "" : s.substr(bestL, bestLen);
}
```

#### Time / Space
`O(|s| + |t|)` / `O(σ)`.

#### Edge cases
Pattern longer than text (empty answer); duplicate chars in pattern; pattern chars absent from text.

#### Common mistakes
Shrinking when `have == need` must record *before* decrementing; using `>` vs `>=` when decrementing `have` (only when count drops *below* need).

#### Variations
Window subsequence (§10 `09` file) — two-pointer with a backwards inner scan; fixed-template "shortest subarray sum ≥ K" with prefix sums.

#### Practice mapping
- `08-Minimum-Window-Substring.cpp`, `09-Minimum-Window-Subsequence.cpp`, `11-Substrings-Containing-ABC.cpp`

---

### P6 — Last-Seen Jump (replace while-shrink)

#### What is the pattern?
Instead of shrinking step-by-step, jump `l = max(l, lastIndex[c] + 1)` when a repeat is seen.

#### When should I recognize it?
- "Longest substring without repeating characters", "longest repeating character replacement" (variant with maxFreq), any "no duplicates in window".

#### Core intuition
All characters between the previous occurrence of `s[r]` and `r` are invalidated at once — the last-seen map gives the jump distance directly.

#### Generic algorithm
```text
last[256] = -1
for r:  l = max(l, last[s[r]] + 1);  last[s[r]] = r;  best = max(best, r - l + 1)
```

#### C++ template
```cpp
int longestUnique(string s) {
    int last[256]; memset(last, -1, sizeof last);
    int l = 0, best = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        l = max(l, last[(unsigned char)s[r]] + 1);
        last[(unsigned char)s[r]] = r;
        best = max(best, r - l + 1);
    }
    return best;
}
```

#### Time / Space
`O(n)` / `O(σ)`.

#### Edge cases
Empty string; all distinct (`l` never moves); ASCII vs extended chars (cast to unsigned).

#### Common mistakes
Not initializing `last` to `−1`; using `last[c]` without checking if it's left of `l` (handled by `max`).

#### Variations
maxFreq variant (never shrink `maxFreq`); jump-based merge of at-most logic.

#### Practice mapping
- `01-Longest-Substring-Without-Repeat.cpp`, `04-Longest-Repeating-Char-Replacement.cpp`

---

## 5. PATTERN RECOGNITION

| If the problem says... | Think about... |
|---|---|
| "subarray of size k" / "every window" | fixed window |
| "longest subarray/substring with property" | variable window (expand + while-shrink) |
| "shortest subarray with sum ≥ K" | variable window (shrink while valid) |
| "count subarrays with **exactly** K …" | atMost(K) − atMost(K−1) |
| "no repeating characters" | last-seen jump |
| "replace up to K characters" | maxFreq metric |
| "minimum window containing pattern" | have/need coverage (P5) |
| "pair with sum = target" (sorted) | two pointers opposite ends |
| "triplet / quadruplet sum" | sort + fix + two pointers |
| "container with most water" | two pointers by area |
| "binary subarrays with sum K" | prefix sum + at-most (§03) |
| "k flips / at most k zeros allowed" | window with budget counter |

**Decision rules**
1. Contiguous + constraint → **window**; is the target longest or shortest? → sets where you update the answer.
2. Exactly-K counting → **subtraction trick** (unless negatives → prefix map).
3. Sorted + pair-sum → **two pointers**; unsorted → **hash map**.
4. Need window max/min in `O(1)` → monotonic deque (§09).

---

## 6. BRUTE → BETTER → OPTIMAL THINKING

### Longest substring without repeating characters
- **Brute** — all `O(n²)` substrings, set-check each: `O(n²)` (or `O(n³)` building sets).
- **Better** — sliding window with freq map + while-shrink: `O(n)`.
- **Optimal** — last-seen index jump: `O(n)`, no shrinking loop — same bound, fewer operations.

### Count subarrays with exactly K distinct
- **Brute** — enumerate subarrays, count distinct each: `O(n²)`.
- **Better** — window counting for exactly K directly: fragile (can't shrink correctly while counting exactly).
- **Optimal** — `atMost(K) − atMost(K−1)`, each `O(n)`: total `O(n)` with a *correct, simple* invariant. The subtraction trick converts a hard exact-count into an easy monotone count.

### Minimum window substring
- **Brute** — all substrings × count-check: `O(n² · m)`.
- **Better** — expand/shrink with have/need: `O(n + m)` amortized.
- **Optimal** — same `O(n + m)` with array counts instead of maps — the *structure* is already optimal; optimize constants (`int[128]`).

### Max consecutive ones with K flips
- **Brute** — all subarrays, zeros-count check: `O(n²)`.
- **Better** — window with zeros ≤ K: `O(n)`.
- **Optimal** — same window; optionally never shrink zeros count below K (keep max width) — `O(n)` with smaller constant.

### 3-sum
- **Brute** — three nested loops: `O(n³)`.
- **Better** — fix one + hash set for the pair: `O(n²)` time, `O(n)` space.
- **Optimal** — fix one + two pointers on sorted rest: `O(n²)` time, `O(1)` extra space, and naturally handles duplicates. Sorting (`O(n log n)`) is dominated.

### Key transferable idea
> Windows optimize **enumeration** (drop the inner loop); the subtraction trick optimizes **conditioning** (exactly → at-most); sorting optimizes **search** (pairs become directional).

---

## 7. C++ / STL TOOLKIT

| Tool | Syntax | Use |
|---|---|---|
| Fixed window sums | `sum += a[i]; if (i>=k) sum -= a[i-k];` | no prefix array needed |
| Prefix sums | `pref[i+1] = pref[i] + a[i]` | range sums `pref[r+1]-pref[l]` |
| Freq array | `int cnt[26] = {}` | fixed alphabet windows |
| Freq map | `unordered_map<int,int> f` + `erase` at 0 | dynamic alphabet |
| Distinct counter | `if (--f[c] == 0) distinct--;` | avoid `.size()` with arrays |
| Two pointers | `int l = 0, r = n - 1;` | sorted pair sums |
| Sort + skip dup | `sort`; `if (i>0 && a[i]==a[i-1]) continue;` | 3/4-sum outputs |
| `lower_bound` | pair with §04 | k-th smallest window etc. |

```cpp
// variable window skeleton
int l = 0, best = 0;
for (int r = 0; r < n; r++) {
    // add a[r] to state
    while (state invalid) { /* remove a[l] */ l++; }
    best = max(best, r - l + 1);
}

// at-most counting skeleton
long long res = 0;
for (int r = 0; r < n; r++) {
    // add a[r]
    while (state invalid) { /* remove a[l] */ l++; }
    res += r - l + 1;        // all windows ending at r that are valid
}
```

**Common mistakes**
- `int` sums → `long long` for large `n · value`.
- Forgetting to reset `l` between two separate at-most passes (each pass needs `l = 0`).
- Using `map::size()` for distinct when zero-counts are not erased.

---

## 8. COMPLEXITY GUIDE

| Technique | Time | Space |
|---|---:|---:|
| Fixed window sum/max | `O(n)` | `O(1)` |
| Variable window (any valid metric) | `O(n)` | `O(σ)` |
| At-most twice (exactly K) | `O(2n)` | `O(σ)` |
| Last-seen jump | `O(n)` | `O(σ)` |
| Min window (have/need) | `O(n + m)` | `O(σ)` |
| Prefix-sum subarray count | `O(n)` | `O(n)` |
| Sorted 2-sum | `O(n log n)` incl. sort | `O(1)` |
| Sorted 3-sum | `O(n²)` | `O(1)` |
| Sorted 4-sum | `O(n³)` | `O(1)` |
| Brute subarray enumeration | `O(n²)` | `O(1)` |

**How to estimate** — count pointer movements: each of `l`, `r` moves at most `n` times → `2n` total. For k-sum: `n^(k−1)` after sorting (each fixed element reduces one dimension).

---

## 9. EDGE CASES

- **Empty input / `n = 0`** — window loops must not run; answer `0` or empty string.
- **`k = 1` / `k = n` / `k > n`** — fixed windows at boundaries.
- **All elements identical** — windows never invalid; counts can reach `n(n+1)/2`.
- **All negative numbers** — max subarray sum < 0 (initialize best to `-inf` / first element, not `0`).
- **Target unreachable** — return 0 / empty / −1 per spec.
- **Duplicates in sum problems** — unique-triplet requirements need explicit skipping.
- **Overflow** — three `10^9` sums in `int` wrap → `long long`.
- **`l > r` transient** — after shrinking past `r`, skip answer updates until valid.
- **Zero-length pattern / empty `t`** — min-window semantics (usually empty string).
- **Window with negatives & "shortest sum ≥ K"** — not monotone → prefix + deque (advanced), not plain window.

---

## 10. COMMON MISTAKES

| # | Mistake | What goes wrong | Why | How to avoid |
|---|---|---|---|---|
| 1 | `if` instead of `while` when shrinking | invalid window persists | one removal rarely enough | always `while` |
| 2 | Answer updated at wrong moment | off-by-one lengths | longest vs shortest timing | longest: after shrink; shortest: while still valid |
| 3 | Distinct count via map without `erase` | counts never decrease | zero entries remain | `if (--f[c] == 0) f.erase(c);` |
| 4 | Forgetting `k < 0` in atMost | negative results | misuse of trick | `if (k < 0) return 0;` |
| 5 | Applying at-most to sum==K with negatives | non-monotone | sums can decrease | prefix map (§03) for arbitrary sums |
| 6 | `int` sum overflow | wrapped answers | `10^5 × 10^9` | `long long` |
| 7 | Not sorting before two pointers | pointers meaningless | requires order | sort first |
| 8 | Missing duplicate skips in 3-sum | repeated triplets | same values at different indices | skip at outer + both inner pointers |
| 9 | Recording min-window *after* breaking validity | misses tightest window | window already invalid | record before shrink breaks |
| 10 | Using `maxFreq` that shrinks | wrong (still correct actually) but breaks the monotone trick's constant | keep maxFreq monotone (never decrease) | known trick — never shrink it |

**Conceptual mistakes**
- Confusing **longest** (update after shrink to valid) vs **shortest** (update inside shrink before invalid) — memorize the two timings.
- Trying window on non-contiguous asks (subsequence/ subsets — that's §07).

---

## 11. IMPORTANT FORMULAS / RULES

```text
Fixed window sum:    sum_{i} = sum_{i-1} + a[i] - a[i-k]
Prefix range sum:    sum(l..r) = pref[r+1] - pref[l]
At-most count:       res += r - l + 1     (all valid windows ending at r)
Exactly K:           atMost(K) - atMost(K-1)
Distinct in window:  increment when cnt goes 0->1; decrement when 1->0
Longest no-repeat:   l = max(l, last[c] + 1)
maxFreq validity:    windowLen - maxFreq <= K
Min window:          record when have == need.size(), shrink while it holds
2-sum sorted:        s < T -> l++;  s > T -> r--
k-sum complexity:    O(n^(k-1)) after sort
```

**Rules**
1. Both pointers only move forward → `O(n)` amortized.
2. Freq state must be *exact* (arrays) or *erased at zero* (maps).
3. Sort first whenever moving pointers by comparison.

---

## 12. REUSABLE TEMPLATES

```cpp
// 1. Variable window — longest valid
int longestWindow(const vector<int>& a, auto&& add, auto&& remove, auto&& valid) {
    int l = 0, best = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        add(a[r]);
        while (!valid()) remove(a[l++]);
        best = max(best, r - l + 1);
    }
    return best;
}

// 2. At-most counting
long long atMost(vector<int>& a, int k, auto&& add, auto&& remove, auto&& valid) {
    long long res = 0; int l = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        add(a[r]);
        while (!valid()) remove(a[l++]);
        res += r - l + 1;
    }
    return res;
}
// exactlyK = atMost(K) - atMost(K-1)   (guard k < 0 -> 0)

// 3. Longest substring without repeating (last-seen)
int longestUnique(string s) {
    int last[256]; memset(last, -1, sizeof last);
    int l = 0, best = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        l = max(l, last[(unsigned char)s[r]] + 1);
        last[(unsigned char)s[r]] = r;
        best = max(best, r - l + 1);
    }
    return best;
}

// 4. Sorted 3-sum (dedup built in)
// sort; for i: if (i && a[i]==a[i-1]) continue; two pointers l=i+1, r=n-1 with dup skips
```

## 13. ADVANCED CONCEPTS

### 13.1 Minimum window subsequence
Two-pointer variant where the inner pointer scans **backwards** to find the shortest subsequence (not substring) of `s` containing `t` — different shrink direction than substring windows; know both.

### 13.2 Binary search on window size
When window validity is monotone in length ("longest window with ≤ K flips" can be decided for a candidate length L in `O(n)`), binary search the length → `O(n log n)`. Slower than the direct window, but a useful fallback when the direct condition isn't clean.

### 13.3 Sliding window median (advanced)
Two heaps + lazy deletion or two multisets: maintain medians of every window in `O(log n)` per step. Requires deleting outgoing elements — the hard version of two-heap median (§11 P2).

### 13.4 Fixed-size window with deque for both max and min
Maintain two deques (one decreasing, one increasing) to answer "max − min ≤ K?" constraints per window — extends the window state with deque-based metrics.

### 13.5 Amortized arguments in interviews
State clearly: "each index is added once and removed once, so the inner while-loop totals `O(n)`" — this amortized proof is the expected justification for window optimality.

### 13.6 Window + prefix + deque (shortest subarray sum ≥ K, with negatives)
Not windowable (non-monotone). Use prefix sums + monotonic increasing deque of candidate prefixes — advanced combination of §03 + §09. Recognize this as the escape hatch when the window assumption fails.

---

## 14. CONNECTIONS BETWEEN PATTERNS

```text
Prefix sums (§03)
    |
    +--> fixed window  (+a[r] - a[l-k])
    |
Two pointers (§03)
    |
    v
SLIDING WINDOW  ---- variable constraint (expand/shrink)
    |                        |
    |                        +--> at-most -> exactly (subtraction)
    |                        +--> have/need (min window)
    |                        +--> last-seen jump / maxFreq
    v
Sorted two pointers  <--- sort (§02)   ---> 2/3/4-sum
    |
    v
Binary search on answer (§04)   [when window length is the unknown]

Bridge to DP (§16):  "longest valid window" often equals a DP answer; windows are the
O(n) special case when validity is locally checkable.
```

**Mental map** — contiguous? → window. sorted pair? → two pointers. exactly-K count? → subtraction. pattern coverage? → have/need. non-monotone sum with negatives? → prefix + deque (advanced).

---

## 15. PROBLEM → PATTERN MAPPING

*(Reference only — solutions and approaches live in the `.cpp` files.)*

### Variable window (longest / constraint)
- `01-Longest-Substring-Without-Repeat.cpp`
- `03-Fruits-into-Baskets.cpp`
- `04-Longest-Repeating-Char-Replacement.cpp`
- `10-Longest-Substring-K-Distinct.cpp`
- `02-Max-Consecutive-Ones-III.cpp`

### Fixed window / budgets
- `12-Max-Points-from-Cards.cpp`

### At-most → exactly subtraction
- `07-Subarrays-With-K-Distinct.cpp`
- `06-Count-Nice-Subarrays.cpp`
- `11-Substrings-Containing-ABC.cpp`

### Prefix sum + window hybrid
- `05-Binary-Subarrays-With-Sum.cpp`

### Minimum window (have/need)
- `08-Minimum-Window-Substring.cpp`
- `09-Minimum-Window-Subsequence.cpp`

### Two pointers on sorted arrays (see also §03)
- `31-Three-Sum.cpp` (§03), `32-Four-Sum.cpp` (§03), `14-Two-Sum.cpp` (§03)

---

## 16. QUICK REVISION SHEET

**Concepts**
- Window = `[l..r]` contiguous with a maintained invariant; `r` expands, `l` shrinks via `while`.
- Each index enters/leaves once → `O(n)` amortized.
- Exactly-K = atMost(K) − atMost(K−1); sorted pair search = two pointers.

**Recognition clues**
| Signal | Tool |
|---|---|
| longest / shortest contiguous with property | variable window |
| every window of size k | fixed window |
| exactly K (count) | subtraction trick |
| no repeats | last-seen jump |
| replace up to K | maxFreq metric |
| contains all pattern chars | have/need |
| pair/triplet sum (sorted) | two pointers |

**Skeletons**
```cpp
for r: add(a[r]); while (!valid()) remove(a[l++]);  update answer;
// at-most:  res += r - l + 1;   // exactly = diff of two at-most passes
```

**Complexity** — window `O(n)/O(σ)` · min-window `O(n+m)` · 3-sum `O(n²)` · brute `O(n²)`.

**Common mistakes** — `if` not `while` · wrong update timing (longest vs shortest) · map zero-erase · no sort before pointers · overflow · duplicates in outputs.

**Decision rules** — contiguous→window · exactly→subtract · sorted→pointers · unsorted pair→hash (§03) · window max→deque (§09).

---

## 17. INTERVIEW CHECKLIST

- [ ] Can I write the variable-window skeleton (add / while-shrink / update) correctly?
- [ ] Can I distinguish longest vs shortest update timing without thinking?
- [ ] Can I derive `exactly = atMost(K) − atMost(K−1)` and guard `K < 0`?
- [ ] Can I write last-seen-jump for no-repeat substrings?
- [ ] Can I implement min-window substring with have/need semantics?
- [ ] Can I prove the amortized `O(n)` in one sentence?
- [ ] Can I handle empty input, all-identical, all-negative cases?
- [ ] Can I choose `long long` where sums can overflow?
- [ ] Can I write sorted 3-sum with duplicate skipping?
- [ ] Can I recognize when a problem is NOT a window (negatives, non-contiguous)?

<!-- done -->
