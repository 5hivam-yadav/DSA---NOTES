# 02 — Sorting Algorithms (Selection, Bubble, Insertion, Merge, Quick)

---

## 1. Introduction

Sorting is the single most reusable algorithm family in computer science. Roughly a quarter of all interview questions assume sorted input or reward you for sorting first, because **sorted order exposes structure**: binary search becomes possible, two pointers become valid, greedy choices become provably optimal, and duplicates become adjacent.

This chapter builds every comparison sort from first principles — what invariant each pass maintains, why its complexity is what it is, and exactly where each implementation goes wrong. The seven solution files in this folder are working reference implementations of everything described here.

### Purpose

To make you able to *derive* a sorting algorithm under pressure, not merely recall one: choose between them by data size, memory budget, stability requirement, and adversarial-input risk.

### Why it matters in DSA

- **Enabler**: binary search (§04), two-pointer/sliding window (§10), greedy (§12) and many DP optimizations all presuppose sorted order.
- **Complexity yardstick**: `O(n log n)` is the comparison-sort lower bound — knowing it tells you when `O(n^2)` is unavoidable only because of constraints, and when you have written something accidentally quadratic.
- **Interview staple**: hand-written merge sort and quick sort partition logic are among the most frequently coded live.

### Real-world intuition

A card player sorting a hand is doing insertion sort (take one card, slide it into the sorted prefix). A librarian merging two already-sorted shelves is merge sort's merge step. Two sorted arrays enable merging wedding guest lists in linear time — the same reason databases sort before joining tables.

---

## 2. Prerequisites

- Arrays, indexing, and `for`/`while` loops (§01).
- Recursion: base case + recursive step, and call-stack space (§01 §3.6).
- Big-O notation and nested-loop cost analysis (§01 §3.1).
- C++ `vector`, `swap`, and pass-by-reference (`vector<int>&`).

---

## 3. Core Concepts

### 3.1 What Sorting Is — Invariants, Stability, Adaptivity

**Definition**  
A comparison sort rearranges `n` items into non-decreasing order using only pairwise comparisons. Correctness is guaranteed by an **invariant**: a statement true before each pass and still true after it.

**Intuition**  
Every sorting algorithm is a disciplined way of growing a region of the array that is known to be in final sorted position. Algorithms differ only in *where* that region starts and *how* elements move into it.

**How it works**  
Three properties classify any sort:

| Property | Definition | Why it matters |
|---|---|---|
| **Stable** | Equal elements keep original relative order | Sort by name then surname needs stability |
| **In-place** | `O(1)` extra memory (excluding input) | Memory-constrained / streaming data |
| **Adaptive** | Runs faster on nearly-sorted input | Live data with small perturbations |

**Example**

```text
Sort [(b,1), (a,2), (b,3)] by letter only:
stable:   (a,2), (b,1), (b,3)   <-- b,1 stays before b,3
unstable: (a,2), (b,3), (b,1)   <-- order of equal keys lost
```

**Important observation**  
All comparison sorts need `Ω(n log n)` worst-case comparisons (decision-tree argument: `n!` leaves require depth `≥ log2(n!) ≈ n log n`). Escape hatches: counting/radix sort `O(n + k)` for bounded integer keys, or exploiting presortedness.

**Common mistake**  
Confusing *stable* with *in-place*: insertion sort is both; merge sort is stable but not in-place; quick sort is in-place but not stable.

---

### 3.2 Selection Sort

**Definition**  
Repeatedly select the minimum element of the unsorted suffix and swap it into the end of the sorted prefix.

**Intuition**  
Scan the whole unsorted region to find the smallest item, then put it exactly where it belongs. One swap per pass; the sorted prefix grows by one.

**How it works**

```text
arr = [64, 25, 12, 22, 11]

pass 1: min=11 at idx4 -> swap with idx0 -> [11 | 25 12 22 64]
pass 2: min=12 at idx2 -> swap with idx1 -> [11 12 | 25 22 64]
pass 3: min=22 at idx3 -> swap with idx2 -> [11 12 22 | 25 64]
pass 4: min=25 at idx3 -> swap with idx3 -> [11 12 22 25 | 64]
done:   [11, 12, 22, 25, 64]
```

```cpp
void selectionSort(vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minIdx]) minIdx = j;
        swap(a[i], a[minIdx]);
    }
}
```

**Important observation**  
Always exactly `n - 1` swaps — the minimum number of writes of any sort. This makes it practical for write-heavy media (EEPROM, flash) where writes are expensive but comparisons are cheap.

**Common mistake**  
Stopping the inner loop at `n` instead of `n - 1`, or swapping *every* time a new minimum is seen (turns `O(n)` swaps into `O(n^2)`; only swap once per pass).

---

### 3.3 Bubble Sort (with early exit)

**Definition**  
Repeatedly walk adjacent pairs, swapping whenever they are out of order. After pass `i`, the largest remaining element has "bubbled" to position `n - i - 1`.

**Intuition**  
Like heavy bubbles rising: each full sweep guarantees at least one more element (the maximum of the unsorted region) reaches its final home.

**How it works**

```text
arr = [5, 1, 4, 2, 8]

pass 1: 5>1 swap -> [1,5,4,2,8]
        5>4 swap -> [1,4,5,2,8]
        5>2 swap -> [1,4,2,5,8]
        5<8 ok   -> 8 fixed at end
pass 2: ... 5 fixed, then 4, then 2, then sorted:
result: [1, 2, 4, 5, 8]
```

```cpp
void bubbleSort(vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++)   // last i already fixed
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        if (!swapped) break;                  // adaptive early exit
    }
}
```

**Important observation**  
The inner bound is `n - 1 - i`, not `n`: positions `> n - 1 - i` hold already-final elements. With `swapped`, best case becomes `O(n)` — the only `O(n^2)` sort that is naturally adaptive without modification.

**Common mistake**  
Using bound `j < n` (re-compares settled suffix — still correct but wastes work) or forgetting `swapped`, which forfeits the early exit and makes already-sorted input take `O(n^2)`.

---

### 3.4 Insertion Sort

**Definition**  
Grow a sorted prefix one element at a time: take the next element and slide it leftward into its correct position within the prefix.

**Intuition**  
Exactly how most people sort playing cards: pick up the next card and insert it into the already-sorted part of your hand.

**How it works**

```text
arr = [12, 11, 13, 5, 6]

key=11: 12>11 shift -> [11, 12 | 13, 5, 6]
key=13: 13>=12 stop  -> [11, 12, 13 | 5, 6]
key=5:  shift 13,12,11 -> [5, 11, 12, 13 | 6]
key=6:  shift 13,12,11 -> [5, 6, 11, 12, 13]
```

```cpp
void insertionSort(vector<int> &a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) {   // strict > keeps it stable
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}
```

**Important observation**  
Best case `O(n)` on sorted input, worst `O(n^2)` on reverse-sorted. It is stable (with `>`), in-place, and adaptive — the standard choice for *nearly-sorted* data and for the tiny-array base case inside hybrid sorts (`std::sort` switches to insertion sort below ~16 elements).

**Common mistake**  
Overwriting `a[i]` before saving `key`, or starting the inner loop at `j = 0` with a condition that reads `a[-1]` (always guard `j >= 0` first — `&&` short-circuits left to right).

---

### 3.5 Merge Sort

**Definition**  
Divide the array in half, sort each half recursively, then merge the two sorted halves in linear time.

**Intuition**  
The merge step is the engine: given two sorted lines of people, repeatedly take the front person of whichever line has the smaller head — total work is linear. Sorting two halves only needs `log n` levels of merging.

**How it works**

```text
merge([3, 27], [8, 19]):
  i-> 3     j-> 8    3 < 8  take 3     -> [3]
       i-> 27     j-> 8    8 < 27 take 8   -> [3, 8]
            i-> 27    j-> 19   19 < 27 take 19 -> [3, 8, 19]
                 i-> 27    take 27       -> [3, 8, 19, 27]

[5,2,9,1] 
   /      \
[5,2]    [9,1]        split (log n levels)
 / \      / \
[5] [2] [9] [1]       base cases
 \ /      \ /
[2,5]    [1,9]        merge
   \      /
  [1,2,5,9]           final merge
```

```cpp
void mergeRange(vector<int> &a, int l, int m, int r) {
    vector<int> t;
    int i = l, j = m + 1;
    while (i <= m && j <= r)
        t.push_back(a[i] <= a[j] ? a[i++] : a[j++]);  // <= keeps stable
    while (i <= m) t.push_back(a[i++]);
    while (j <= r) t.push_back(a[j++]);
    copy(t.begin(), t.end(), a.begin() + l);
}
void mergeSort(vector<int> &a, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    mergeRange(a, l, m, r);
}
```

**Important observation**  
Time is `O(n log n)` in *all* cases: `log n` levels × linear work per level. Space is `O(n)` auxiliary (the temp buffer) + `O(log n)` stack. It is stable and guaranteed — never degrades — which is why libraries use it when stability is required (`stable_sort`).

**Common mistake**  
Forgetting to copy *both* leftover tails after the main merge loop (`while (i <= m)` and `while (j <= r)` — people write only one), or computing `m = (l + r) / 2` which overflows for huge `l + r`.

---

### 3.6 Quick Sort

**Definition**  
Pick a **pivot**, partition the array so all elements `<= pivot` sit left and all `> pivot` sit right, place the pivot at its final position, then recurse on both sides.

**Intuition**  
The pivot's final index is known after one linear scan; everything left of it can only ever compare against smaller items, so the two halves never interact again. Fast because the pivot usually lands near the middle — but a bad pivot choice can degenerate to `O(n^2)`.

**How it works — Lomuto partition (pivot = last element)**

```text
arr = [10, 80, 30, 90, 40, 50, 70], pivot = 70
boundary i marks "end of <= pivot region"

 j scans: 10<=70  -> swap i,j -> [10, 80, 30, 90, 40, 50, 70]
          80>70   skip
          30<=70  -> swap     -> [10, 30, 80, 90, 40, 50, 70]
          90>70   skip
          40<=70  -> swap     -> [10, 30, 40, 90, 80, 50, 70]
          50<=70  -> swap     -> [10, 30, 40, 50, 80, 90, 70]
 final: swap pivot into boundary
        -> [10, 30, 40, 50, 70, 90, 80]   pivot index = 4
recurse on [10,30,40,50] and [90,80]
```

```cpp
int partitionLomuto(vector<int> &a, int lo, int hi) {
    int pivot = a[hi], i = lo;
    for (int j = lo; j < hi; j++)
        if (a[j] <= pivot) swap(a[i++], a[j]);
    swap(a[i], a[hi]);
    return i;
}
void quickSort(vector<int> &a, int lo, int hi) {
    if (lo >= hi) return;
    int p = partitionLomuto(a, lo, hi);
    quickSort(a, lo, p - 1);
    quickSort(a, p + 1, hi);
}
```

**Hoare partition (two pointers from both ends, fewer swaps)**

```cpp
int partitionHoare(vector<int> &a, int lo, int hi) {
    int pivot = a[lo], i = lo - 1, j = hi + 1;
    do { do i++; while (a[i] < pivot);
         do j--; while (a[j] > pivot);
         if (i < j) swap(a[i], a[j]);
    } while (i < j);
    return j;   // NOTE: split point; recursion is [lo, j] and [j+1, hi]
}
```

**Important observation**  
Average `O(n log n)` because pivots fall in the middle half on average; worst `O(n^2)` on already-sorted input with last-element pivot (every partition splits `n-1 : 0`). Space `O(log n)` stack average, `O(n)` worst. Not stable — swaps cross equal elements.

**Common mistake**  
- Forgetting the final `swap(a[i], a[hi])` — pivot never reaches its slot.  
- Mixing up Hoare's recursion bounds (`[lo, j], [j+1, hi]` — using `[lo, p-1]` with Hoare loops forever on 2-element input).  
- Not randomizing the pivot (`swap(a[lo + rand() % (hi - lo + 1)], a[hi])`) on known-adversarial inputs.

---

### 3.7 Library Sorting: `std::sort` and Hybrid Introsort

**Definition**  
`std::sort` is an **introsort**: quick sort + heap sort fallback + insertion sort for small ranges.

**Intuition**  
Each ingredient fixes another's weakness: quick sort's speed, heap sort's `O(n log n)` worst-case guarantee, insertion sort's low overhead on tiny slices.

**How it works**

```cpp
sort(a.begin(), a.end());                       // ascending
sort(a.begin(), a.end(), greater<int>());       // descending
sort(v.begin(), v.end(), [](auto &x, auto &y) { // custom key
    return x.grade > y.grade;
});
stable_sort(a.begin(), a.end());                // stability, needs O(n) buffer
```

**Important observation**  
`std::sort` runs `O(n log n)` worst case (heap sort kicks in when recursion depth exceeds `2·log2 n`) and is *not* stable; `stable_sort` is stable but allocates. Never hand-roll a sort in production — hand-written sorts exist here for interviews and learning only.

**Common mistake**  
Using `==` as the comparator (must be a strict weak ordering: `comp(a,a) == false`, and `comp(a,b) != comp(b,a)`), or using `<=` inside the comparator — both cause undefined behavior in library sorts.

---

## 4. Terminology

| Term | Meaning |
|---|---|
| **Comparison sort** | Sorts using only pairwise `<`/`>` queries; `Ω(n log n)` worst-case bound. |
| **Stability** | Equal keys retain their original relative order after sorting. |
| **In-place** | Uses `O(1)` extra memory beyond the input array. |
| **Adaptive** | Runs in less than `O(n log n)` on nearly-sorted input. |
| **Invariant** | Property that holds before and after each algorithmic step, proving correctness. |
| **Partition** | Quick sort step placing pivot at final index with smaller items left, larger right. |
| **Pivot** | Element chosen to partition around; its selection drives quick sort's performance. |
| **Run** | A maximal already-sorted subsequence inside the input. |
| **External sort** | Sorting data too large for RAM, streaming runs from disk (used by `sort` on files). |
| **Non-comparison sort** | Radix/counting sort exploiting integer key structure to beat `Ω(n log n)`. |
| **Hybrid sort** | Introsort/Timsort: combines algorithms to get the best of each regime. |
| **Cache-oblivious** | Algorithm whose good locality arises without modeling cache sizes (merge sort locality). |

---

## 5. ASCII Visual Explanations

### Divide-and-conquer skeleton (merge & quick)

```text
                 [5, 2, 9, 1]              <- level 0: n elements
                /             \
         [5, 2]               [9, 1]       <- level 1: 2 sorts of n/2
         /     \             /     \
       [5]     [2]         [9]     [1]     <- level 2: base cases
         \     /             \     /
        [2, 5]               [1, 9]        <- merge / partition back up
                \             /
              [1, 2, 5, 9]                 <- level 0 again: done

levels = log2(n);  work per level = O(n)  =>  total O(n log n)
```

### Bubble sort pass, sorted suffix grows right

```text
initial:  [5, 1, 4, 2, 8]   sorted: {}
after p1: [1, 4, 2, 5 | 8]  sorted: {8}
after p2: [1, 2, 4 | 5, 8]  sorted: {5, 8}
after p3: [1, 2 | 4, 5, 8]  sorted: {4, 5, 8}
after p4: [1 | 2, 4, 5, 8]  sorted: {2, 4, 5, 8}
bound each pass: n - 1 - i
```

### Quick sort pivot placement

```text
[10, 80, 30, 90, 40, 50, 70]  pivot=70 (last)
  i marks boundary of "<= 70" zone
  final: [10, 30, 40, 50 | 70 | 90, 80]
                   left        pivot    right
 recurse ->  [10,30,40,50]        [90,80]
```

### Insertion sort shift

```text
sorted prefix      key      action
[12]               11       12>11: shift 12 right, insert 11
[11, 12]           13       13>=12: append, no shift
[11, 12, 13]        5       shift 13,12,11; insert 5
[5, 11, 12, 13]     6       shift 13,12,11; insert 6
```

---

## 6. Real-World Applications

- **Databases**: ORDER BY clauses, B-tree maintenance, and sort-merge joins — sorting both tables first turns a quadratic join into a linear sweep.
- **Operating systems**: kernel schedulers keep run-queues ordered; `sort(1)` on multi-GB files uses external merge sort with disk-backed runs.
- **Search engines**: ranking pipelines sort document scores before top-k selection (or use a heap to skip full sorts).
- **Version control**: `git diff` sorts file changes before display so output is deterministic.
- **Graphics**: painter's algorithm sorts polygons by depth before rasterization; particle systems sort by z-order.
- **Deduplication**: sorting is the cheapest way to make duplicates adjacent, then removing them in one linear pass (`unique` after `sort`).
- **Electronics**: selection sort's minimal swap count is chosen for flash-memory programming where write endurance matters.

---

## 7. Edge Cases and Pitfalls

1. **Empty / single-element arrays** — every recursion must return at `lo >= hi`; `n = 0` must not execute `a[0]`.
2. **All elements equal** — Lomuto with `<=` puts every element left of pivot → `O(n^2)` recursion depth. Use `<=`/`>=` split or random pivot; Hoare handles this in `n/2 : n/2`.
3. **Reverse-sorted input** — last-element pivot quick sort degenerates to `O(n^2)`; the recursion depth `n` can blow the stack for `n ≈ 10^5`.
4. **Integer overflow in midpoint** — `int m = (lo + hi) / 2` overflows when `lo + hi > 2^31`; always `lo + (hi - lo) / 2`.
5. **Comparator contract** — a comparator returning `a <= b` for *both* directions violates strict weak ordering → infinite loops or UB in `std::sort`.
6. **Sorting pairs/tuples** — `sort(v.begin(), v.end())` on pairs sorts by first then second automatically; when you need a different primary key you must write a comparator, not mutate keys.
7. **Stability assumptions** — never assume `std::sort` preserves order of equals; if record order matters, decorate-sort-undecorate (attach original index as tiebreaker).
8. **Counting-sort range explosion** — `vector<int> count(maxValue)` with `maxValue = 10^9` allocates 4 GB; verify range before choosing counting sort.

---

## 8. Comparison Table

| Algorithm | Best | Average | Worst | Space | Stable | In-place | Notes |
|---|---|---|---|---|---|---|---|
| Selection | `O(n^2)` | `O(n^2)` | `O(n^2)` | `O(1)` | No | Yes | Min swaps (`n-1`) |
| Bubble | `O(n)` | `O(n^2)` | `O(n^2)` | `O(1)` | Yes | Yes | Adaptive w/ `swapped` |
| Insertion | `O(n)` | `O(n^2)` | `O(n^2)` | `O(1)` | Yes | Yes | Best on nearly-sorted |
| Merge | `O(n log n)` | `O(n log n)` | `O(n log n)` | `O(n)` | Yes | No | Guaranteed; stable |
| Quick (Lomuto) | `O(n log n)` | `O(n log n)` | `O(n^2)` | `O(log n)` | No | Yes | Fast in practice |
| Heap | `O(n log n)` | `O(n log n)` | `O(n log n)` | `O(1)` | No | Yes | Bad locality |
| `std::sort` | `O(n log n)` | `O(n log n)` | `O(n log n)` | `O(log n)` | No | Yes | Introsort hybrid |
| Counting | `O(n + k)` | `O(n + k)` | `O(n + k)` | `O(k)` | Yes | No | Integer keys, range k |

---

## 9. Best Practices

- **Default to `std::sort`** — it is strictly better than anything you will hand-write outside an interview. Only hand-roll when the interviewer asks.
- **Pass large objects by `const&`**; for `vector<pair<string,int>>` sort an index array instead of moving strings repeatedly.
- **Randomize pivots** in quick sort (`random_shuffle`-style or `rand() %`) to convert adversarial `O(n^2)` into expected `O(n log n)`.
- **Use `stable_sort` or index-decorators** whenever equal-key order carries meaning (multi-key sorts: sort by surname, then stable by name).
- **Insertion sort for n ≤ ~16** inside your own D&C code — constant-factor win over recursing down to single elements.
- **Test with sorted, reverse-sorted, all-equal, and single-element inputs** — the four inputs that expose every partition and bound bug.
- **Midpoints and bounds** — always `lo + (hi - lo) / 2` and keep the invariant *range [lo, hi] inclusive* consistently in every function you pass it through.

---

## 10. Important Patterns & Problem-Solving Strategies

### Pattern 1 — Sort then two-pointer / binary search

```cpp
sort(a.begin(), a.end());
// pair-sum, dedup, range checks now O(n) or O(log n)
```
*Use when*: the problem asks for pairs/triplets with a target — first move removes the search cost.

### Pattern 2 — Comparator as a strategy

```cpp
sort(students.begin(), students.end(),
     [](const Student &x, const Student &y) {
         if (x.grade != y.grade) return x.grade > y.grade; // desc
         return x.name < y.name;                           // tiebreak
     });
```
*Use when*: ordering by compound keys without modifying the data.

### Pattern 3 — Dutch National Flag (3-way partition, Dijkstra)

```cpp
// partition into < pivot | == pivot | > pivot in one pass
int lo = 0, mid = 0, hi = n - 1;
while (mid <= hi)
    if (a[mid] < pivot) swap(a[lo++], a[mid++]);
    else if (a[mid] > pivot) swap(a[mid], a[hi--]);
    else mid++;
```
*Use when*: quick sort with many duplicates, or problems like "sort 0s 1s 2s" in `O(n)`.

### Pattern 4 — Merge as an independent tool

```cpp
// count inversions / merge k sorted lists / merge two sorted halves
while (i <= m && j <= r) t.push_back(a[i] <= a[j] ? a[i++] : a[j++]);
```
*Use when*: counting inversions (add `m - i + 1` per take from right), merging sorted streams.

### Pattern 5 — Partial selection instead of full sort

```cpp
nth_element(a.begin(), a.begin() + k, a.end()); // O(n) avg, kth smallest
partial_sort(a.begin(), a.begin() + k, a.end()); // top-k in O(n log k)
```
*Use when*: only the k smallest/largest matter (median, top-k scores) — full sort is wasted work.

---

## 11. Practice Problems

All problems live in this folder (`02-Sorting/`). Work them in order — each adds one idea on top of the previous.

| # | File | Core skill |
|---|---|---|
| 01 | `01-Selection-Sort.cpp` | min-scan invariant, `n-1` swaps |
| 02 | `02-Bubble-Sort.cpp` | adjacent swaps, `n-1-i` bound |
| 03 | `03-Insertion-Sort.cpp` | sorted-prefix growth, shifting |
| 04 | `04-Merge-Sort.cpp` | divide, conquer, linear merge |
| 05 | `05-Recursive-Bubble-Sort.cpp` | recursion replacing outer loop |
| 06 | `06-Recursive-Insertion-Sort.cpp` | recursive prefix insertion |
| 07 | `07-Quick-Sort.cpp` | partition + recursion (Hoare-style) |

**How to use this chapter**

1. Read the concept section, then code the sort from memory — the ASCII traces in §5 are your checklist.
2. Manually trace one full partition/merge on paper before running it.
3. For each file, state its time/space/stability triple out loud; compare against §8.
4. After implementing, test on the four hostile inputs from §7 (empty, singleton, sorted, all-equal).







