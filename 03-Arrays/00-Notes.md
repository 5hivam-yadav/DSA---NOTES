# 03 — Arrays and Matrices (Traversal, Two Pointers, Prefix, Kadane, Matrix)

---

## 1. Introduction

The array is the simplest structure with the most leverage: contiguous memory gives `O(1)` index access and cache-friendly sequential scans, and nearly every advanced structure (hash tables, heaps, graphs as edge lists) is built on top of array thinking. This chapter's 40 problems form the working vocabulary of technical interviews — subarray sums, rotations, matrix manipulation, majority element, interval merging — and every one reduces to a small set of reusable patterns.

### Purpose

To convert the 40 problems here from "things I've memorized" into ~8 derivable patterns: one-pass scans, two pointers, prefix sums, Kadane's, frequency hashing, sorting + sweep, matrix indexing tricks, and interval logic.

### Why it matters in DSA

- Arrays are the default container in every language, so interviewers assume fluency.
- Subarray logic (Kadane, prefix-sum maps, sliding window) generalizes to §10 Sliding Window, §16 DP, and §08 Bit Manipulation (XOR sums).
- Matrix patterns reappear in graph grids, DP tables (§16), and image processing.

### Real-world intuition

A spreadsheet is a 2D array: row scans compute aggregates (sum columns), prefix sums compute running totals, and "rotate 90°" is exactly how you transpose a report. Sensor feeds, log files, and pixel buffers are all arrays — the patterns here are literally what production code does to them.

---

## 2. Prerequisites

- §01: loops, functions, pass-by-reference, Big-O.
- §02: sorting basics (`std::sort`, two-pointer merge) — needed for §3.6/§3.8.
- 0-indexed and 1-indexed conventions, and the difference between `int` and `size_t` indices.

---

## 3. Core Concepts

### 3.1 Array Fundamentals — Access, Subarray vs Subsequence

**Definition**  
An array stores `n` elements of equal size in contiguous memory; element `i` lives at `base + i * sizeof(T)`, giving constant-time access. A **subarray** is a contiguous slice `[l..r]`; a **subsequence** keeps order but may skip elements; a **subset** may reorder entirely.

**Intuition**  
Contiguity is why arrays beat linked lists in practice: iterating `n` consecutive words streams through CPU cache lines (64 bytes ≈ 16 ints), while pointer-chasing jumps across memory.

**How it works**

```text
a = [2, 7, 11, 15]     base address B

index:    0      1      2      3
address:  B      B+4    B+8    B+12     (int = 4 bytes)

subarray of [7, 11]:      must be a[1..2]        (contiguous)
subsequence [2, 11]:      a[0], a[2]             (order kept, gap ok)
subset {11, 2}:           any two elements       (no order rule)
```

**Important observation**  
`n` elements have `n(n+1)/2` subarrays (start × end choices) but `2^n` subsequences. Any algorithm enumerating all subarrays is inherently `O(n^2)` — the budget that prefix sums and Kadane's exist to beat.

**Common mistake**  
Treating a subsequence problem with subarray logic or vice versa ("longest common subsequence" vs "longest common substring"), or using `size_t` for `i--` below zero — `size_t i = 0; i--` wraps to 2^64−1.

---

### 3.2 One-Pass Scans and Sortedness Checks

**Definition**  
A single left-to-right sweep maintaining O(1) state: running max/min, previous element, or counters — answering order questions without extra storage.

**Intuition**  
You don't need two passes if the fact you're looking for can be remembered the moment you see it: "second largest" only requires remembering the top two; "sorted" only requires comparing each element with its predecessor.

**How it works**

```cpp
// Second largest in one pass — strict > chains both updates
long long secondLargest(const vector<int> &a) {
    long long first = LLONG_MIN, second = LLONG_MIN;
    for (int x : a) {
        if (x > first)      { second = first; first = x; }
        else if (x > second && x != first) second = x;
    }
    return second;
}
// Sorted check: any descent breaks it
bool isSorted(const vector<int> &a) {
    for (int i = 1; i < (int)a.size(); i++)
        if (a[i - 1] > a[i]) return false;
    return true;
}
```

**Important observation**  
The update *order* matters: setting `first` before reading it (as written) cascades old `first` into `second`. Reversing the two assignments loses the old maximum.

**Common mistake**  
Forgetting the `x != first` guard — with all-equal input (`[5,5,5]`) `second` would falsely become 5; whether that's wrong depends on the problem's distinctness promise, so check it.

---

### 3.3 Two Pointers — In-Place Edits on Sorted Input

**Definition**  
Two indices move through the array under complementary rules (one from left, one from right, or a fast/slow pair), turning nested-loop searches into a single linear sweep.

**Intuition**  
On sorted data, moving pointers is *directional information*: if `a[l] + a[r] < target`, no pair containing `a[l]` can work (everything else is even bigger) — so `l` can safely advance. The sorted order tells you which pointer to move.

**How it works — remove duplicates from sorted array (write head)**

```text
a = [1, 1, 2, 3, 3]
slow=0 (write pos)
fast=1.. :  a[1]=1 == a[0] skip
            a[2]=2 != a[1] -> a[++slow]=2  => [1, 2, _, 3, 3]
            a[3]=3 != a[2] -> a[++slow]=3  => [1, 2, 3, _, 3]
result length = slow + 1 = 3 -> [1, 2, 3]
```

```cpp
int removeDuplicates(vector<int> &a) {         // sorted input
    if (a.empty()) return 0;
    int slow = 0;
    for (int fast = 1; fast < (int)a.size(); fast++)
        if (a[fast] != a[slow]) a[++slow] = a[fast];
    return slow + 1;
}
// Move zeros: same shape, swap instead of overwrite (keeps order)
void moveZeroes(vector<int> &a) {
    int slow = 0;
    for (int fast = 0; fast < (int)a.size(); fast++)
        if (a[fast] != 0) swap(a[slow++], a[fast]);
}
```

**Important observation**  
The `slow` pointer defines the invariant *"a[0..slow] holds the answer so far"*; `fast` only reads. This write-head pattern is the backbone of in-place filtering (zeros, duplicates, partitioning — cf. §02 Lomuto).

**Common mistake**  
Starting `fast` at 0 with `slow` at 0 and comparing `a[fast] != a[slow]` (compares an element to itself, always false), or using assignment instead of `swap` when order of removed elements must be preserved.

---

### 3.4 Rotation by Reversal (O(1) Extra Space)

**Definition**  
Left-rotating by `k` can be done with three reverses: reverse whole array, reverse first `k`, reverse the rest — or equivalently reverse `[0..k-1]`, reverse `[k..n-1]`, then reverse all.

**Intuition**  
Reversal reorders without cross-buffer copying; the two partial reverses undo the scramble outside the boundary so only the `k` block moves.

**How it works**

```text
a = [1, 2, 3, 4, 5], k = 2

reverse whole:      [5, 4, 3, 2, 1]
reverse [0..k-1]:   [4, 5 | 3, 2, 1]
reverse [k..n-1]:   [4, 5 | 1, 2, 3]
result:             [4, 5, 1, 2, 3]   (left rotation by 2)
```

```cpp
void rotateLeft(vector<int> &a, int k) {
    int n = a.size();
    if (!n) return;
    k %= n;                          // k may exceed n or be negative
    reverse(a.begin(), a.end());
    reverse(a.begin(), a.begin() + k);
    reverse(a.begin() + k, a.end());
}
```

**Important observation**  
Always `k %= n` first: rotating by `n` changes nothing, and `k > n` otherwise reads out of bounds. For negative `k` (right rotation), normalize: `k = ((k % n) + n) % n`.

**Common mistake**  
Skipping `k %= n` (crashes or no-ops incorrectly), or doing a naive "shift each element k times" — `O(n·k)` time vs `O(n)` for the reverse trick.

---

### 3.5 Prefix Sums and Subarray-Sum Maps

**Definition**  
`pref[i] = a[0] + … + a[i-1]` (with `pref[0] = 0`). Then any subarray sum is `pref[r+1] - pref[l]` in `O(1)`. A **hash map of prefix positions** answers "count subarrays with sum K" in `O(n)`.

**Intuition**  
Instead of recomputing every window from scratch, remember running totals: the moment you've seen total `S`, every earlier total `S - K` marks a subarray ending here with sum `K`.

**How it works**

```text
a = [1, 2, 3], K = 3
pref: [0, 1, 3, 6]
sum(l..r) = pref[r+1] - pref[l]

Count subarrays sum = 3 with a map:
i=0: S=1        need 1-3=-2 -> 0 seen
i=1: S=3        need  3-3=0 -> 1 seen (pref 0)   count += 1   [1..1]? no: a[0..1]
i=2: S=6        need  6-3=3 -> 1 seen            count += 1   [2..2]
total = 2 subarrays: [1,2] and [3]
```

```cpp
int subarraySumK(const vector<int> &a, int k) {
    unordered_map<long long, int> seen;      // prefix value -> freq
    seen[0] = 1;                             // empty prefix
    long long s = 0; int cnt = 0;
    for (int x : a) {
        s += x;
        if (seen.count(s - k)) cnt += seen[s - k];
        seen[s]++;
    }
    return cnt;
}
```

**Important observation**  
The same idea solves XOR (`pref[r] ^ pref[l-1] == K` → map `pref ^ K`), longest subarray with sum K (store first index of each prefix), and difference-K count. Cumulative logic also gives `max subarray = maxPref - minPref-so-far`.

**Common mistake**  
Forgetting `seen[0] = 1` (misses subarrays starting at index 0), or using `int` for the running sum when values reach ±10^9·n — promote to `long long`.

---

### 3.6 Kadane's Algorithm — Maximum Subarray

**Definition**  
Track `cur = max(a[i], cur + a[i])`: either extend the best subarray ending at `i-1` or start fresh at `i`. `best = max(best, cur)`.

**Intuition**  
A negative running prefix is dead weight — any subarray continuing through it is worse than one starting after it. So `cur` resets the instant adding history hurts.

**How it works**

```text
a = [-2, 1, -3, 4, -1, 2, 1, -5, 4]

i:  -2   1   -3   4   -1    2    1   -5    4
cur: -2   1   -2   4    3    5    6    1    5
best:-2   1    1   4    4    5    6    6    6
                                    ^
                         answer = 6 = [4,-1,2,1]
```

```cpp
int maxSubArray(const vector<int> &a) {
    long long cur = a[0], best = a[0];
    for (size_t i = 1; i < a.size(); i++) {
        cur = max((long long)a[i], cur + a[i]);
        best = max(best, cur);
    }
    return (int)best;
}
```

**Important observation**  
Works on **all-negative** arrays because `cur` may restart at any single element (answer = largest element). Initialize both with `a[0]`, never `0`. The variant that must return an *empty* subarray allowed initializes `best = 0`.

**Common mistake**  
Initializing `best = 0` on an all-negative array returns 0 (an empty subarray) when the problem demands non-empty — the classic off-by-contract bug. Also, `cur = max(a[i], cur + a[i])` must compare against `a[i]` *alone*, not `0`.

---

### 3.7 Special Scans — Hashing, Moore Voting, Dutch Flag

**Definition**  
Three O(1)-space-or-hash one-pass state machines: **two-sum** (complement lookup), **majority vote** (counter pairs), **three-way partition** (color bucketing).

**Intuition**  
Each encodes a different kind of memory: two-sum remembers *values seen*; Moore remembers *one candidate and its count* (a majority element occupies more than half the slots, so pairing it with others cancels them out); Dutch flag remembers *three region boundaries*.

**How it works**

```cpp
// 1) Two Sum — hash the complement
vector<int> twoSum(const vector<int> &a, int target) {
    unordered_map<int, int> seen;                 // value -> index
    for (int i = 0; i < (int)a.size(); i++) {
        if (seen.count(target - a[i]))
            return {seen[target - a[i]], i};
        seen[a[i]] = i;
    }
    return {};
}
// 2) Moore majority — candidate then verify (> n/2 required)
int majorityElement(const vector<int> &a) {
    int cand = 0, cnt = 0;
    for (int x : a) { if (!cnt) cand = x; cnt += (x == cand) ? 1 : -1; }
    cnt = 0;
    for (int x : a) if (x == cand) cnt++;         // verify pass
    return cnt > (int)a.size() / 2 ? cand : -1;
}
// 3) Dutch flag — sort 0/1/2 in one pass (§02 Pattern 3)
void sortColors(vector<int> &a) {
    int lo = 0, mid = 0, hi = (int)a.size() - 1;
    while (mid <= hi)
        if (a[mid] == 0) swap(a[lo++], a[mid++]);
        else if (a[mid] == 1) mid++;
        else swap(a[mid], a[hi--]);
}
```

**Important observation**  
Moore's two-phase structure is essential: the pass only guarantees a *candidate* occupying > n/2 slots; the verification pass handles the no-majority case. Longest consecutive sequence needs a `set` + "only start counting from values whose predecessor is absent" — each element enters a run at most once, keeping it `O(n)`.

**Common mistake**  
Skipping Moore's verification (returns a wrong element when no majority exists), or hashing *before* checking (returns `i == j` when `2·a[i] == target` — for exactly-one-pair semantics insert after lookup, as written).

---

### 3.8 Matrix Patterns — Zeroing, Rotation, Spiral

**Definition**  
2D arrays are rows of contiguous rows: `m[i][j]` → `base + (i * cols + j) * sizeof(T)`. The three canonical problems: mark zero rows/cols, rotate 90°, spiral traversal.

**Intuition**  
- **Set Matrix Zeroes without extra matrix**: encode "row/col is dirty" in the first row/column themselves (saving `O(m+n)` space), then apply markers in a second pass.
- **Rotate 90° CW**: transpose (swap across diagonal), then reverse each row.
- **Spiral**: maintain four shrinking boundaries `top, bottom, left, right` and peel layers clockwise.

**How it works**

```text
Rotate 90° CW:
[1 2 3]      transpose      [1 4 7]      reverse rows    [7 4 1]
[4 5 6]  ->  [2 5 8]    ->   [8 5 2]  ->  [6 3]
[7 8 9]      [3 6 9]         [9 6 3]        [3 2 1]

Spiral boundaries (3x3):
 top=0 ┌ 1 2 3 ┐        layer 1: right->down->left->up
 L=0 R=2│ 4 5 6 │        top=1,bottom=1,left=1,right=1
 bot=2  └ 7 8 9 ┘        layer 2: center 5 done
```

```cpp
void rotate90(vector<vector<int>> &m) {
    int n = m.size();
    for (int i = 0; i < n; i++)                    // transpose
        for (int j = i + 1; j < n; j++) swap(m[i][j], m[j][i]);
    for (int i = 0; i < n; i++)                    // reverse rows
        reverse(m[i].begin(), m[i].end());
}
```

**Important observation**  
`vector<vector<int>>` rows are *separately* allocated — column traversal `m[i][j]` for fixed `j` hops across heap blocks and misses cache; transpose first if you need column locality. Spiral edge case: after peeling, a single row/column leftover must be traversed *once*, not four times (guard each side with `while (l <= r)`-style checks).

**Common mistake**  
In spiral, forgetting the reverse direction on the bottom/left edges (double-counting corners), and in set-zeroes using `O(mn)` marker matrix when first-row/col encoding or hash sets of dirty rows suffice.

---

## 4. Terminology

| Term | Meaning |
|---|---|
| **Subarray** | Contiguous slice `a[l..r]`; `n(n+1)/2` of them exist. |
| **Subsequence** | Ordered selection allowing gaps; `2^n` of them. |
| **Prefix sum** | Running total array enabling `O(1)` range sums. |
| **In-place** | Output written back into the input using `O(1)` extra memory. |
| **Two pointers** | Paired indices whose movement is guided by comparison with a target. |
| **Slow/fast (write head)** | `fast` reads, `slow` marks the boundary of kept output. |
| **Running maximum** | Best value seen so far, updated in one pass. |
| **Kadane's invariant** | `cur` = best subarray *ending exactly at i*. |
| **Majority element** | Value occurring more than `n/2` times (unanimous vote analog). |
| **Dutch National Flag** | Three-region partition `< / = / >` in a single scan. |
| **Leader** | Element strictly greater than everything to its right. |
| **Boundary encoding** | Storing markers in the input matrix's own first row/col. |
| **Spiral traversal** | Layer-by-layer clockwise peeling via four shrinking bounds. |
| **Running XOR sum** | Prefix XOR enabling `subarrayXOR == K` via `pref ^ K` lookups. |

---

## 5. ASCII Visual Explanations

### Two-pointer sum on a sorted array

```text
target = 10,  a = [1, 3, 4, 6, 8, 9]

l=0 r=5: 1+9=10  <== found
if sum < target:  l++   (need bigger)
if sum > target:  r--   (need smaller)
each step discards a whole row of the n² pair matrix
```

### Prefix-sum range query

```text
a        = [ 2,  5,  3,  7,  1]
pref     = [0,  2,  7, 10, 17, 18]     pref[0]=0, pref[i+1]=pref[i]+a[i]

sum(a[1..3]) = pref[4] - pref[1] = 17 - 2 = 15  (= 5+3+7 ✓)
```

### Kadane decision at each index

```text
 [-2, 1, -3, 4, -1, 2, 1, -5, 4]
       └ extend or restart?
cur  = max( a[i] , cur + a[i] )
        start new   extend best ending at i-1
```

### Moore voting cancelation

```text
[2, 2, 1, 1, 2, 2, 1]
 2: cnt=1
 2: cnt=2
 1: cnt=1    (2 pairs with 1 -> both vanish)
 1: cnt=0
 2: cnt=1    (new candidate)
 2: cnt=2
 1: cnt=1
candidate=2 (then verify: occurs 4 > 7/2 ✓)
```

### Matrix rotate = transpose + row reverse

```text
step 1 transpose      step 2 reverse each row
1 2 3      1 4 7      7 4 1
4 5 6  ->  2 5 8  ->  8 5 2
7 8 9      3 6 9      9 6 3
```

<!--NEXT-->




