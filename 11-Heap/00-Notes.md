# 11 — Heap (Priority Queue) — Complete Pattern-Based Notes

---

## 1. Topic Overview

A **heap** is a complete binary tree satisfying the heap order: the parent is ≤ (min-heap) or ≥ (max-heap) its children — giving `O(1)` access to the extreme and `O(log n)` insert/delete.

**What it is**
Implemented as an array over a complete binary tree (`children of i = 2i+1, 2i+2`). `push` sifts up, `pop` sifts down, `heapify` builds in `O(n)`.

**Why it is important**
- The standard tool for **top-K**, **kth smallest/largest**, **merge K sorted**, and **greedy scheduling**.
- Turns `O(n log n)` full sorts into `O(n log k)` partial work when only the best k matter.
- Two-heap balancing solves streaming median problems.

**Where it is used**
- Kth largest/smallest; task scheduler; connect ropes; maximum sum combinations.
- Merge K sorted lists/arrays; design Twitter (merge feeds).
- Dijkstra's shortest path (§15); greedy with the "worst current candidate" (§12).

**How it connects to other topics**
- §15 Graph: Dijkstra = min-heap on `(dist, node)`.
- §12 Greedy: heap + greedy for scheduling/interval scoring.
- §16 DP: heap rarely used, but "k-way merge" appears in DP on sorted structures.

**Interview memory hook:** *Keep K best in a min-heap for kth-largest. Median = balanced max-left + min-right. Merge K = heap of heads.*

---

## 2. Fundamentals

### 2.1 Min-heap vs max-heap

```cpp
priority_queue<int>                               mx;  // max-heap (default)
priority_queue<int, vector<int>, greater<int>>    mn;  // min-heap

mx.push(x); mx.top(); mx.pop();   // top = largest / smallest
```

### 2.2 Array layout

```text
index:   0    1    2    3    4    5
value:   [10,  14,  3,   7,   8,   1]     (min-heap)

parent(i)      = (i - 1) / 2
left child(i)  = 2i + 1
right child(i) = 2i + 2

sift-up:   swap with parent while out of order
sift-down: swap with smaller child while out of order
```

### 2.3 Terminology

| Term | Meaning |
|---|---|
| **Heapify** | Build heap from arbitrary array in `O(n)` bottom-up. |
| **Sift up / down** | Restore order after insert / pop. |
| **Complete binary tree** | All levels full except possibly the last, filled left-to-right — dense array storage. |
| **Size-K heap** | Keep only the K best elements; heap top = K-th best. |
| **Stale entry** | Outdated heap item (lazy deletion) skipped at pop time. |

### 2.4 When heap beats sorting

| Situation | Sort | Heap |
|---|---|---|
| Need all sorted | `O(n log n)` ✅ | not applicable |
| Need kth / top-k, one-shot | `O(n log n)` or `nth_element O(n)` | `O(n log k)` |
| Data stream, kth so far | not possible | `O(n log k)` ✅ |
| Merge K sorted | `O(N log N)` | `O(N log K)` ✅ |

---

## 3. Core Concepts

### 3.1 Min-heap and max-heap

**Definition**  \nMin-heap: parent ≤ children → `top()` = minimum. Max-heap: parent ≥ children → `top()` = maximum.

**Why they matter**  \nYou always know the *best/worst* element in `O(1)` and can update in `O(log n)` — the alternative (re-sorting) costs `O(n log n)`.

**How it works**  \n`sift-up` on push (swap with parent while violated); `sift-down` on pop (swap with the *smaller* child while violated).

---

### 3.2 Size-K heap (kth largest / kth smallest / top-K)

**Definition**  \nMaintain a heap of at most `k` elements; when size exceeds `k`, evict the opposite extreme.

**Which heap?**
- **Kth largest** → min-heap of size `k` (the top *is* the kth largest; smaller elements got evicted).
- **Kth smallest** → max-heap of size `k`.

**Complexity**  \n`O(n log k)` time, `O(k)` space — beats `O(n log n)` full sort when `k ≪ n`, and works on **streams**.

**Common mistake**  \nUsing the wrong heap direction (max-heap of size k gives the kth *smallest*).

---

### 3.3 Two-heap median

**Definition**  \n`lo` = max-heap of lower half, `hi` = min-heap of upper half; rebalance so `|size(lo) − size(hi)| ≤ 1`.

**Why**  \nMedian = `lo.top()` (odd) or average of tops (even). Each insert: push to one, rebalance by moving the top → `O(log n)`.

**Invariant**: `max(lo) ≤ min(hi)` — maintained by moving the offending top across after insertion.

**Common mistakes**
- Forgetting to rebalance when sizes differ by more than 1.
- Integer overflow when averaging medians → `double` or `long long`.

---

### 3.4 K-way merge (merge K sorted)

**Definition**  \nPush the head of each list into a min-heap keyed by value; repeatedly pop the smallest and push its successor.

**Complexity**  \n`O(N log K)` — `N` total elements, heap size `K`. Pairwise divide-and-conquer merge achieves the same bound with `O(log K)` recursion depth.

**Heap element**: `pair<value, listIndex>` (or `{value, nodePtr}`) — the comparator orders by value; `priority_queue` of `pair` sorts by `first` then `second` automatically (min-heap with `greater<>`).

---

### 3.5 Heap + frequency (top-K frequent, scheduling)

**Definition**  \nCount with a hash map, then push `(freq, key)` into a heap (size-k or full).

**Task scheduler idleness math**: with `n` tasks and max frequency `f`, minimum length = `max(totalTasks, (f−1)·(n+1) + countOfMaxFreq)` — heap can simulate it, but the formula is `O(n)`.

**Common mistake**  \nPushing raw values instead of `(priority, tiebreak)` pairs — heap can't see the frequency.

---

### 3.6 Greedy expand with a heap (ropes / stones)

**Definition**  \nRepeatedly take the **two smallest** (or two largest) items, combine, push back — the greedy choice is provably optimal for "connect ropes min cost" and similar.

**Why it works**  \nExchange argument: combining smallest first never wastes large numbers in early multiplications — same structure as Huffman coding.

**Complexity**  \n`O(n log n)` (2n−1 heap ops).

---

### 3.7 Heapify (build in O(n))

**Definition**  \nStarting from the last non-leaf `(n/2 − 1)`, sift-down each node → valid heap.

**Why O(n)**  \nMost nodes are near the bottom where sift-down costs `O(1)`; summing `n/2^h · h` gives `O(n)` — counterintuitively cheaper than `n` pushes (`O(n log n)`).

---

## 4. PATTERN LIBRARY

### P1 — Size-K Heap (Kth / Top-K)

#### What is the pattern?
Keep at most `k` elements in a heap of the *opposite* direction; top = answer.

#### When should I recognize it?
- "Kth largest / kth smallest", "top k frequent", "k closest points", "k largest sum combinations" (with sorted trick), "kth largest in a stream".

#### Core intuition
For kth largest: maintain the `k` biggest seen — evict the smallest of them when a bigger arrives; the heap root is then exactly the kth biggest.

#### Generic algorithm
1. Min-heap (for kth largest).
2. Push each element; if `size > k` → `pop()`.
3. Answer = `top()`.

#### C++ template
```cpp
int kthLargest(vector<int> a, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;   // min-heap
    for (int x : a) { pq.push(x); if ((int)pq.size() > k) pq.pop(); }
    return pq.top();
}
```

#### Time / Space
`O(n log k)` / `O(k)`. Stream of `m` elements: `O(m log k)`.

#### Edge cases
`k == n` (heap holds everything); duplicates at the kth boundary; `k < 1` (invalid input).

#### Common mistakes
Wrong heap direction; pushing then popping when `size > k` *before* push (off-by-one); forgetting `k` may exceed `n`.

#### Variations
Kth smallest → max-heap; "stream" variant (`15-Kth-Largest-in-Stream.cpp`) never needs the old elements removed — same code.

#### Practice mapping
- `06-Kth-Largest-Element.cpp`, `07-Kth-Smallest-Element.cpp`, `15-Kth-Largest-in-Stream.cpp`, `17-Find-Median-from-Data-Stream.cpp`

---

### P2 — Two-Heap Median (streaming median)

#### What is the pattern?
Max-heap for the lower half + min-heap for the upper half, sizes balanced within 1.

#### When should I recognize it?
- "Find median from a data stream", "sliding window median" (with lazy deletion — advanced), "split array into balanced halves".

#### Core intuition
Medians live at the boundary of two halves — each heap stores one side sorted; rebalancing keeps the boundary at the center.

#### Generic algorithm
1. Insert into `lo` (max-heap); move `lo.top()` to `hi` if out of order.
2. Rebalance: if `lo.size() > hi.size() + 1` → move top to `hi`; if `hi.size() > lo.size()` → move back.
3. Median: odd → `lo.top()`; even → average of tops.

#### C++ template
```cpp
priority_queue<int> lo;                                   // max-heap
priority_queue<int, vector<int>, greater<int>> hi;         // min-heap
void add(int x) {
    lo.push(x); hi.push(lo.top()); lo.pop();              // keep order
    if (lo.size() < hi.size()) { lo.push(hi.top()); hi.pop(); }  // balance
}
double median() { return lo.size() > hi.size() ? lo.top() : (lo.top() + hi.top()) / 2.0; }
```

#### Time / Space
`O(log n)` per insert, `O(1)` median / `O(n)`.

#### Edge cases
First element; even vs odd counts; overflow when averaging (use `double` or `long long`).

#### Common mistakes
Skipping the order-fix step (median split invalid); off-by-one balancing (`lo` should hold the extra).

#### Variations
Sliding window median needs a multiset/two heaps with lazy deletion — mention as advanced.

#### Practice mapping
- `17-Find-Median-from-Data-Stream.cpp`

---

### P3 — K-Way Merge (merge K sorted structures)

#### What is the pattern?
Min-heap of the current heads of K sorted streams; pop-min, push its successor.

#### When should I recognize it?
- "Merge K sorted lists / arrays", "k smallest pairs", "merge feeds/timelines", "sort k-sorted array".

#### Core intuition
The global minimum of the union is always among the K heads — the heap maintains exactly those candidates.

#### Generic algorithm
1. Push head of each list as `(value, listId, index)`.
2. Repeatedly pop the smallest, append to output, push the next element from the same list.
3. Stop when the heap empties.

#### C++ template
```cpp
using T = tuple<int,int,int>;   // value, listIdx, elemIdx
priority_queue<T, vector<T>, greater<T>> pq;
for (int i = 0; i < K; i++) if (!lists[i].empty()) pq.push({lists[i][0], i, 0});
vector<int> out;
while (!pq.empty()) {
    auto [v, li, ei] = pq.top(); pq.pop();
    out.push_back(v);
    if (ei + 1 < (int)lists[li].size()) pq.push({lists[li][ei+1], li, ei+1});
}
```

#### Time / Space
`O(N log K)` time (N total elements), `O(K)` heap space.

#### Edge cases
Empty lists among the K; K = 0 / 1; all elements in one list; duplicates across lists.

#### Common mistakes
Pushing all elements up front (`O(N log N)` — loses the point); missing list index in tuple (can't find successor).

#### Variations
Pairwise divide-and-conquer merge (same bound, `O(log K)` depth); k-sorted array = merge adjacent windows.

#### Practice mapping
- `09-Merge-M-Sorted-Lists.cpp`, `08-Sort-K-Sorted-Array.cpp`, `16-Maximum-Sum-Combination.cpp`, `06-Linked-List/31-Merge-Two-Sorted-Lists.cpp`

---

### P4 — Heap + Greedy (scheduling, ropes, handshakes)

#### What is the pattern?
Repeatedly pick the globally best/worst current candidates from a heap, combine or schedule them, push results back.

#### When should I recognize it?
- "Connect ropes with minimum cost", "task scheduler minimum intervals", "hands of straights", "reorganize string", "minimum time to finish tasks".

#### Core intuition
Local choice among the *extreme* available options is globally safe when an exchange argument applies — the heap provides the extremes in `O(log n)`.

#### Generic algorithm (ropes)
```text
push all ropes into min-heap
while size > 1:
    a = pop; b = pop; cost += a + b; push(a + b)
answer = cost
```

#### C++ template
```cpp
long long connectRopes(vector<int>& r) {
    priority_queue<long long, vector<long long>, greater<long long>> pq(r.begin(), r.end());
    long long cost = 0;
    while (pq.size() > 1) {
        long long a = pq.top(); pq.pop();
        long long b = pq.top(); pq.pop();
        cost += a + b; pq.push(a + b);
    }
    return cost;
}
```

#### Time / Space
`O(n log n)` / `O(n)`.

#### Edge cases
0 or 1 rope (cost 0); single huge rope; overflow when sums approach `10^14` → `long long`.

#### Common mistakes
Forgetting to push the combined value; using min-heap when max needed (task scheduling often needs max-frequency first).

#### Variations
Task scheduler (formula `max(n, (f−1)(n+1)+cnt)` — or heap simulation); maximum sum combinations (two sorted arrays + max-heap of candidate pairs with visited set).

#### Practice mapping
- `14-Connect-Ropes-Min-Cost.cpp`, `11-Task-Scheduler.cpp`, `12-Hands-of-Straights.cpp`, `16-Maximum-Sum-Combination.cpp`

---

### P5 — Count-then-Heap (top-K frequent / rank by frequency)

#### What is the pattern?
Hash map counts frequencies → heap of `(freq, key)` (size k or full) → pop in frequency order.

#### When should I recognize it?
- "Top K frequent elements", "sort by frequency", "k closest / reorderBy frequency", "design Twitter (rank by time)".

#### Core intuition
Counting is `O(n)`; ordering *only the interesting K* with a heap is `O(n + n log k)` — better than full sort when `k ≪ n`.

#### Generic algorithm
1. `unordered_map` count pass.
2. Push `(freq, key)` into heap; keep size `k`.
3. Pop/collect.

#### C++ template
```cpp
vector<int> topKFrequent(vector<int>& a, int k) {
    unordered_map<int,int> f; for (int x : a) f[x]++;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;  // min-heap of (freq, val)
    for (auto& [v, c] : f) {
        pq.push({c, v});
        if ((int)pq.size() > k) pq.pop();
    }
    vector<int> out;
    while (!pq.empty()) { out.push_back(pq.top().second); pq.pop(); }
    reverse(out.begin(), out.end());
    return out;
}
```

#### Time / Space
`O(n + n log k)` / `O(n)`.

#### Edge cases
Ties at the kth frequency (any order usually accepted); `k ==` number of distinct keys.

#### Common mistakes
Pair ordering: `priority_queue<pair>` sorts by `first` **descending** by default — put freq first and use `greater<>` for min-heap; forgetting tiebreakers.

#### Variations
Bucket sort `O(n)` alternative (buckets by frequency); design Twitter = merge user timelines via heap of iterators.

#### Practice mapping
- `13-Design-Twitter.cpp`, `10-Replace-Elements-by-Rank.cpp`, `08-Sort-Characters-by-Frequency.cpp` (§05)

---

### P6 — Adaptive Heaps & Stale Entries (lazy deletion)

#### What is the pattern?
Push "candidate versions" into the heap; when popped, check if still current (vs hash/map state) — if stale, discard and pop again.

#### When should I recognize it?
- Problems needing "best current value" where values **decrease over time** (Dijkstra relaxations, scheduling deadlines, sliding-window median).

#### Core intuition
Updating a heap element in place costs `O(n)` with `priority_queue` — instead, push the new state and validate on pop; outdated entries are cheap garbage.

#### Generic algorithm
```text
push (newState)
while top is stale (doesn't match authoritative store): pop
use top
```

#### C++ template (sketch — Dijkstra in §15 uses this exactly)
```cpp
pq.push({newDist, v});
while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d != dist[u]) continue;      // stale entry
    // process u
}
```

#### Time / Space
Each real update adds one push → still `O((n + updates) log n)` / `O(n + updates)`.

#### Edge cases
All entries stale (empty check before use); equal distances (any tie order fine).

#### Common mistakes
Forgetting the staleness check (processing outdated best); comparing wrong fields.

#### Variations
Dijkstra (§15), sliding-window median (multiset erase + heap), "maximum sum of at most k non-overlapping intervals" (heap by end time).

#### Practice mapping
- `17-Find-Median-from-Data-Stream.cpp`, `15-Graph/28-Dijkstra-PQ.cpp`, `15-Graph/29-Dijkstra-Set.cpp`

---

## 5. PATTERN RECOGNITION

| If the problem says... | Think about... |
|---|---|
| "kth largest / smallest" | size-K heap (opposite direction) |
| "top K frequent / sort by frequency" | count + heap (or buckets) |
| "merge K sorted lists/arrays" | K-way merge with min-heap |
| "median from a stream" | two-heap balancing |
| "minimum cost to connect/merge" | greedy: pop two smallest, push sum |
| "schedule tasks / cooldown" | heap or frequency formula |
| "k largest sum combinations" | sorted arrays + max-heap of pairs |
| "nearest smaller/greater with removal order" | heap (or monotonic stack §09) |
| "process in priority order" | priority_queue |
| "streaming + need best so far" | heap (sort impossible online) |
| Dijkstra / shortest path | min-heap (§15) |

**Decision rules**
1. Need the extreme element with insertions → heap, not sort.
2. Only K matter → size-K heap (`O(n log k)`).
3. K streams merging → heap of heads (`O(N log K)`).
4. Values mutate after insertion → lazy deletion (P6).
5. One-shot static data & full order needed → plain `sort` is simpler.

---

## 6. BRUTE → BETTER → OPTIMAL THINKING

### Kth largest element
- **Brute** — sort all, index `n-k`: `O(n log n)` — works, but wasteful.
- **Better** — quickselect: `O(n)` average, `O(n)` space-ish, unstable worst case.
- **Optimal** (streaming / partial) — size-K min-heap: `O(n log k)`, handles online data. For static arrays quickselect is faster in practice; **know both and when each wins**.

### Merge K sorted lists
- **Brute** — concatenate then sort: `O(N log N)`.
- **Better** — pairwise merge (divide & conquer): `O(N log K)`, `O(log K)` stack.
- **Optimal** — heap of heads: `O(N log K)` time, `O(K)` space — best when lists are lazy/streams; pairwise wins on cache locality. Same bound; state the tradeoff.

### Median from stream
- **Brute** — store all, sort on query: `O(n log n)` per query.
- **Better** — two sorted halves (insert into vector at position): `O(n)` per insert.
- **Optimal** — two heaps: `O(log n)` insert, `O(1)` query — the standard answer.

### Minimum cost to connect ropes
- **Brute** — try all merge orders: exponential.
- **Better** — always merge the two smallest via repeated full scan for min: `O(n²)`.
- **Optimal** — min-heap of two: `O(n log n)` — Huffman-optimal (provably minimal via exchange argument).

### Task scheduler
- **Brute** — simulate slots one by one with a heap: `O(total)`.
- **Better** — heap simulation counting only gaps: `O(n log n)`.
- **Optimal** — frequency formula `max(total, (maxFreq−1)·(n+1) + countOfMax)`: `O(n)`. Recognize when a *formula* beats simulation.

### Key transferable idea
> Heaps buy **online access to extremes**: "sort once" when static; "heap" when streaming; "two heaps" when you need a *balance point*; "pop-two-push-one" when combining greedily.

---

## 7. C++ / STL TOOLKIT

| Tool | Syntax | Notes |
|---|---|---|
| Max-heap | `priority_queue<int> pq` | default |
| Min-heap | `priority_queue<int, vector<int>, greater<int>> pq` | ascending |
| Custom comparator | `priority_queue<T, vector<T>, Comp>` | functor/lambda with `operator()` |
| Pair heap | `priority_queue<pair<int,int>, ..., greater<>>` | orders by `first` then `second` |
| Operations | `push`, `top`, `pop`, `size`, `empty` | `top` O(1), rest O(log n) |
| `make_heap/push_heap/pop_heap` | on a `vector` | in-place heap ops |
| `multiset` | ordered multiset | alternative with `erase(one)` |

```cpp
// min-heap of (value, index)
using P = pair<int,int>;
priority_queue<P, vector<P>, greater<P>> pq;

// custom comparator: max-heap by priority (lower number = higher priority)
auto cmp = [](const Task& a, const Task& b) { return a.priority > b.priority; };
priority_queue<Task, vector<Task>, decltype(cmp)> pq(cmp);

// build heap from array in O(n)
vector<int> v = /* ... */;
make_heap(v.begin(), v.end());                 // max-heap
push_heap(v.begin(), v.end());                 // after v.push_back()
pop_heap(v.begin(), v.end()); v.pop_back();    // remove max
```

**Common mistakes**
- Forgetting the comparator *type* must match the third template arg (and constructor for stateful lambdas).
- `pq.push(x); pq.pop();` order for size-k (push first, then pop if `size > k`).
- Assuming `priority_queue` supports removal/updates → use lazy deletion (P6) or `multiset`.

---

## 8. COMPLEXITY GUIDE

| Operation | Time | Space |
|---|---:|---:|
| `push` / `pop` | `O(log n)` | `O(1)` extra |
| `top` | `O(1)` | — |
| `make_heap` (heapify n items) | `O(n)` | `O(1)` |
| Build via n pushes | `O(n log n)` | — |
| Size-k top-K over n items | `O(n log k)` | `O(k)` |
| K-way merge (N items, K lists) | `O(N log K)` | `O(K)` |
| Two-heap median insert | `O(log n)` | `O(n)` |
| Ropes / Huffman | `O(n log n)` | `O(n)` |
| Sorted top-K (comparison) | `O(n log n)` | `O(1)`–`O(n)` |

**How to estimate** — heap ops are one sift per level ≈ `log n ≈ 17` for `n = 10^5`. `n log n` at `10^5` ≈ `1.7·10^6` — fine; `10^7` items sort is ~`2.3·10^8` — consider `O(n)` alternatives (nth_element, buckets).

---

## 9. EDGE CASES

- **Empty heap** — `top()`/`pop()` on empty = UB; check `!pq.empty()`.
- **`k > n`** — size-k heap holds all n; kth largest undefined per spec (verify).
- **All elements equal** — median/tie handling; comparator must be a strict weak ordering (`<`, not `<=`).
- **Negative numbers** — min/max heap direction unchanged, but `greater<int>` vs default must still be deliberate.
- **Overflow** — median average `(a+b)/2` → use `1LL` or `double`; rope sums → `long long`.
- **Single element streams** — median = it; rebalance logic must tolerate one heap empty.
- **Duplicate keys in pair heaps** — second field (index) disambiguates; ties are fine.
- **Comparator equality** — invalid comparators (`comp(a,b) && comp(b,a)` both true) → heap corruption.

---

## 10. COMMON MISTAKES

| # | Mistake | What goes wrong | Why | How to avoid |
|---|---|---|---|---|
| 1 | Max-heap for kth *largest* | gives kth smallest | wrong direction | min-heap of size k |
| 2 | Push/pop order (`size > k`) | off-by-one at boundary | pop before push? | push first, pop if `size > k` |
| 3 | `top()` on empty heap | UB | no guard | check `!pq.empty()` |
| 4 | Forgetting to push combined rope | cost wrong / heap empties early | lost the merged item | `pq.push(a + b)` |
| 5 | Pair comparator confusion | wrong element priority | `pair` orders by `first` | put priority in `first`; use `greater<>` for min |
| 6 | Median average overflow | `int` wraps | `(a+b)` may exceed `10^9` | `1LL * (a + b) / 2.0` |
| 7 | No staleness check with mutating values | processes outdated top | heap can't update | `if (d != dist[u]) continue;` |
| 8 | Stateful lambda without constructor arg | compile error | `decltype(cmp)` needs init | pass `cmp` to constructor |
| 9 | Assumption heap is sorted | iterate heap → wrong | heap is only partially ordered | copy out and `sort` |
| 10 | Building heap with n pushes when heapify exists | `O(n log n)` vs `O(n)` | forgot `make_heap` | use `make_heap` / range ctor where possible |

**Conceptual mistakes**
- Choosing heap vs sort without thought: static + full order → sort; streaming/extreme → heap.
- Expecting `O(1)` median with a single sorted structure — the two-heap split is the point.
- Forgetting that heap `pop` removes the *top only* — no arbitrary removal (lazy deletion or multiset).

---

## 11. IMPORTANT FORMULAS / RULES

```text
Kth largest:     min-heap size k          top = answer          O(n log k)
Kth smallest:    max-heap size k
Median:          lo (max) + hi (min), |sizes| <= 1
                 odd: lo.top();  even: (lo.top() + hi.top()) / 2
K-way merge:     O(N log K), heap size K
Ropes cost:      sum of all internal nodes = O(n log n) greedy pop-2 push-1
Task scheduler:  max(total, (maxFreq-1)*(n+1) + countOfMaxFreq)
Heapify:         O(n) bottom-up from n/2 - 1
Log budget:      log2(10^5) ~ 17, log2(10^6) ~ 20
```

**Decision rules**
1. `k ≪ n` or stream → size-K heap.
2. Merge K → heap of heads.
3. Need both halves' boundary (median) → two heaps.
4. Combine smallest twice → min-heap greedy.
5. Static, need full order → `sort` (simpler, cache-friendly).

---

## 12. REUSABLE TEMPLATES

```cpp
// 1. Kth largest via min-heap of size k
int kthLargest(vector<int>& a, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int x : a) { pq.push(x); if ((int)pq.size() > k) pq.pop(); }
    return pq.top();
}

// 2. Two-heap median
struct Median {
    priority_queue<int> lo;                               // max-heap (lower half)
    priority_queue<int, vector<int>, greater<int>> hi;     // min-heap (upper half)
    void add(int x) {
        lo.push(x); hi.push(lo.top()); lo.pop();          // order: max(lo) <= min(hi)
        if (lo.size() < hi.size()) { lo.push(hi.top()); hi.pop(); }
    }
    double median() const {
        return lo.size() > hi.size() ? lo.top()
             : (lo.top() + hi.top()) / 2.0;
    }
};

// 3. K-way merge skeleton
using T = tuple<int,int,int>;   // value, listIdx, elemIdx
priority_queue<T, vector<T>, greater<T>> pq;

// 4. Connect ropes (Huffman)
long long connectRopes(vector<int>& r) {
    priority_queue<long long, vector<long long>, greater<long long>> pq(r.begin(), r.end());
    long long cost = 0;
    while (pq.size() > 1) {
        long long a = pq.top(); pq.pop();
        long long b = pq.top(); pq.pop();
        cost += a + b; pq.push(a + b);
    }
    return cost;
}
```

## 13. ADVANCED CONCEPTS

### 13.1 k-way merge with iterators / lazy streams
Merge K *lazy* sequences (files, generators) — heap holds iterators instead of values; memory `O(K)` regardless of stream length. Same algorithm as P3, different data source.

### 13.2 Interval scheduling with a heap (maximize accepted set)
Sort by end time (§12 greedy) — but when meetings have weights or dynamic insertion, a heap keyed by end time tracks the latest finish for O(log n) conflict checks.

### 13.3 Monotone stack vs heap for "nearest removed" problems
Some problems (e.g. "max of minimums after k removals") need the monotonic stack result *plus* processing order — heaps and stacks combine.

### 13.4 Pairing heap / Fibonacci heap (theory)
Fibonacci heap gives `O(1)` amortized `decrease-key` — the theoretical basis of faster Dijkstra (`O(E + V log V)`). Mention for theory questions; competitive code uses binary heaps or sets.

### 13.5 Bucket queue (Dial's algorithm)
When edge weights are small integers, bucket queues implement priority queues in `O(1)` per op — a practical optimization over heaps in weighted graphs (§15).

### 13.6 Deterministic medians (median of medians)
`O(n)` worst-case selection without randomness — theoretical importance; interviews accept quickselect `O(n)` average or size-k heaps.

---

## 14. CONNECTIONS BETWEEN PATTERNS

```text
Sorting (§02)  <static, full order>
      |
      |  "only k matter" / "streaming"
      v
   HEAP  ---- size-k ---->  kth / top-k
      |
      +---- K heads ------->  merge K sorted  ---->  merge sort on lists (§06)
      |
      +---- two heaps ----->  median stream
      |
      +---- pop-2 push-1 -->  Huffman / ropes  --->  greedy (§12)
      |
      +---- count + heap -->  top-k frequent / design Twitter
      |
      +---- lazy deletion --> Dijkstra (§15), adaptive scheduling

Monotonic stack (§09) solves STATIC nearest-greater queries; heaps solve DYNAMIC priority needs.
```

**Mental map** — extremes online → heap. K only → size-k. K streams → heads heap. Balance point → two heaps. Combining smallest → Huffman greedy. Mutating priorities → lazy deletion.

---

## 15. PROBLEM → PATTERN MAPPING

*(Reference only — solutions and approaches live in the `.cpp` files.)*

### Fundamentals / implementations
- `01-Introduction-to-Priority-Queue.cpp`
- `02-Min-Heap-Implementation.cpp`
- `03-Max-Heap-Implementation.cpp`
- `04-Check-Array-Represents-Min-Heap.cpp`
- `05-Convert-Min-to-Max-Heap.cpp`

### Size-K heap (kth / top-K / streams)
- `06-Kth-Largest-Element.cpp`
- `07-Kth-Smallest-Element.cpp`
- `15-Kth-Largest-in-Stream.cpp`

### K-way / k-sorted merge
- `08-Sort-K-Sorted-Array.cpp`
- `09-Merge-M-Sorted-Lists.cpp`

### Count + heap / ranking
- `10-Replace-Elements-by-Rank.cpp`
- `13-Design-Twitter.cpp`

### Heap + greedy
- `11-Task-Scheduler.cpp`
- `12-Hands-of-Straights.cpp`
- `14-Connect-Ropes-Min-Cost.cpp`
- `16-Maximum-Sum-Combination.cpp`

### Two-heap median
- `17-Find-Median-from-Data-Stream.cpp`

---

## 16. QUICK REVISION SHEET

**Concepts**
- Heap = complete binary tree; `push/pop O(log n)`, `top O(1)`, heapify `O(n)`.
- Kth largest → **min**-heap of size k; kth smallest → **max**-heap of size k.
- Median → max-heap (lower) + min-heap (upper) balanced within 1.
- Merge K → min-heap of the K heads.

**Recognition clues**
| Signal | Tool |
|---|---|
| kth / top-k | size-k heap |
| merge K sorted | heads heap |
| median from stream | two heaps |
| min cost combining | pop-2 push-1 greedy |
| top-k frequent | count + heap |
| priority processing / Dijkstra | priority_queue |

**Complexity** — push/pop `O(log n)` · top-K `O(n log k)` · merge K `O(N log K)` · heapify `O(n)` · ropes `O(n log n)`.

**Common mistakes** — wrong heap direction · push/pop off-by-one · empty `top()` · median overflow · pair ordering (`first` wins) · no staleness check.

**Decision rules** — static+full order→sort · streaming/extreme→heap · only K→size-k · K streams→heads · combining→Huffman · mutating→lazy deletion.

---

## 17. INTERVIEW CHECKLIST

- [ ] Can I choose min vs max heap for kth smallest/largest instantly?
- [ ] Can I write the size-k template with correct push/pop ordering?
- [ ] Can I implement two-heap median with rebalancing and justify it?
- [ ] Can I write K-way merge with `(value, list, idx)` tuples?
- [ ] Can I state heapify `O(n)` vs n-pushes `O(n log n)`?
- [ ] Can I apply pop-2 push-1 greedy to ropes/scheduling with a proof sketch?
- [ ] Can I handle empty heaps, ties, and overflow in averages?
- [ ] Can I compare heap vs sort vs quickselect and pick the right one?
- [ ] Can I explain lazy deletion for Dijkstra-style problems?
- [ ] Can I compute complexity as `O(n log k)` / `O(N log K)` and verify constraints?

<!-- done -->
