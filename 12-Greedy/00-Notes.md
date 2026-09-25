# 12 — Greedy — Complete Pattern-Based Notes

---

## 1. Topic Overview

**Greedy algorithms** make the locally optimal choice at each step and hope (with proof) it leads to the global optimum — no backtracking, no table.

**What it is**
A problem is greedy-solvable when a **greedy choice property** holds: an optimal solution contains the locally best choice, so committing to it never precludes optimality. The proof is usually an **exchange argument**.

**Why it is important**
- Yields `O(n log n)` (sort + scan) solutions where DP would be exponential/polynomial-heavy.
- Interval scheduling, Huffman coding, Dijkstra, Kruskal/Prim, fractional knapsack — core algorithms are greedy.
- Interviews test *when* greedy is valid — choosing greedy where DP is needed is a classic wrong answer.

**Where it is used**
- Interval problems: meetings, platforms, non-overlapping, arrows.
- Scheduling: job sequencing, task scheduler, SJF.
- Jumps/coverage: jump game, gas station.
- Exchange/coin problems with canonical systems.
- Two-pass scoring: candy distribution.

**How it connects to other topics**
- §12 ↔ §16: greedy vs DP — greedy is DP without the table when the choice property holds.
- §11 Heap: priority-queue greedy (task scheduling, Dijkstra).
- §04 Binary Search: feasibility + greedy predicates.
- §15 Graph: Kruskal/Prim/Dijkstra are greedy.

**Interview memory hook:** *Sort by the right key (usually end time / ratio / slack), scan once, commit. If unsure whether greedy works → DP or prove with exchange.*

---

## 2. Fundamentals

### 2.1 Greedy vs DP vs brute force

```text
Brute:   try all choices           -> guaranteed correct, slow
DP:      optimal substructure + overlapping -> table, guaranteed
Greedy:  optimal substructure + greedy choice property (needs PROOF) -> fastest
```

**Key question**: "If I take the locally best option now, can any optimal solution be *rearranged* to also take it?" If yes → exchange argument works → greedy is safe.

### 2.2 The exchange argument (intuition)

```text
Suppose an optimal solution O uses item A first, but greedy picks B (B better than A).
Swap:   O' = (replace A with B) is at least as good as O
=> some optimal solution starts with B = greedy's choice
=> committing to B is safe
```

### 2.3 Terminology

| Term | Meaning |
|---|---|
| **Greedy choice property** | Local optimum extends to a global optimum. |
| **Optimal substructure** | Optimal solution contains optimal sub-solutions. |
| **Exchange argument** | Proof by swapping greedy's choice into any optimal solution. |
| **Sort key** | The ordering that makes the greedy choice visible. |
| **Canonical coin system** | Greedy coin change is provably optimal (e.g. standard currency). |
| **Feasibility window** | Interval [start, end] where an event fits. |

### 2.4 The canonical sort keys

```text
"finish as early as possible"      -> sort by END time        (maximize count)
"use least resource first"         -> sort ASCENDING (smallest first)
"biggest impact first"             -> sort DESCENDING
"least slack / earliest deadline"  -> sort by deadline
"ratio value/weight"               -> fractional knapsack (sort by ratio)
"merge overlaps"                   -> sort by START time
```

---

## 3. Core Concepts

### 3.1 Interval scheduling (maximize count)

**Definition**  \nSelect the maximum number of non-overlapping intervals.

**Intuition**  \nFinishing early leaves the most room for others — greedy by **end time** is provably optimal (exchange: any optimal solution can be modified to take the earliest-finishing interval first).

**How it works**
1. Sort by end time.
2. Take the first; skip all that overlap (`start < lastEnd`); repeat.

**Complexity**  \n`O(n log n)` sort + `O(n)` scan.

**Common mistake**  \nSorting by *start* for max-count — wrong (long early interval blocks many).

---

### 3.2 Merge / insert intervals

**Definition**  \nCombine overlapping intervals (or insert one into a sorted disjoint set).

**Intuition**  \nSort by start → a single sweep: if `cur.start <= last.end`, merge (`last.end = max(...)`); else push new.

**Complexity**  \n`O(n log n)`; insertion into an interval list is `O(log n)` binary search + `O(n)` shift (or `O(k)` merge of overlaps).

**Common mistakes**
- Forgetting `max` when merging (`[1,10]`, `[2,3]` → must keep 10).
- In-place insertion shifting indexes.

---

### 3.3 Minimum platforms / overlapping resources

**Definition**  \nMaximum number of intervals overlapping at any moment = resources needed.

**Intuition**  \nNot a selection problem — a **sweep**: sort arrivals and departures separately; walk both pointers, increment on arrival, decrement on departure → max running count.

**Complexity**  \n`O(n log n)` (two sorts) + `O(n)` sweep.

**Common mistake** Same-time arrival/departure: process departure *before* arrival (or per problem statement) to avoid +1 errors.

---

### 3.4 Jump / coverage greedy

**Definition**  \n**Jump I**: can we reach the end? Track `farthest` reachable; fail if stuck (`i > farthest`). **Jump II**: minimum jumps → BFS-like windows: within current reach, find the farthest next jump.

**Intuition** Coverage grows like BFS layers; each jump commits to the position that extends coverage most.

**Complexity** Jump I `O(n)`; Jump II `O(n)`.

**Common mistake** Updating `jumps` even when the current index doesn't extend reach (only increment when `i == currentEnd`).

---

### 3.5 Gas station (circular coverage)

**Definition** Start at a station so the tour completes with non-negative tank at all times.

**Intuition** If total `gas - cost ≥ 0` a start exists; the unique safe start is *after* the point of minimum prefix deficit — because any deficit before it would strand you.

**Algorithm** `total += diff; if (total < 0) { start = i + 1; total = 0; }` → if `total ≥ 0` overall, `start` works.

**Complexity** `O(n)` / `O(1)`.

---

### 3.6 Two-pass scoring (candy)

**Definition** Assign ratings with min candies: higher-rated neighbor strictly more than both neighbors.

**Intuition** Left-to-right pass enforces the left neighbor rule; right-to-left pass enforces the right rule; take `max` of both passes (independent constraints).

**Complexity** `O(n)` / `O(n)`.

**Common mistake** Trying to satisfy both directions in one pass — impossible; the two-pass is the standard correct greedy.

---

### 3.7 Greedy coins (canonical systems)

**Definition** Take the largest denomination ≤ remaining amount; repeat.

**When valid**: standard currency systems (1,2,5,10,20,50…) are canonical → greedy optimal. **When invalid**: arbitrary coin sets (e.g. `{1,3,4}` for 6: greedy 4+1+1=3 coins, optimal 3+3=2) → **DP needed** (§16).

**Interview point**: state explicitly *why* greedy works here (canonical) or fall back to DP.

---

## 4. PATTERN LIBRARY

### P1 — Sort by End Time (maximize count of non-overlapping intervals)

#### What is the pattern?
Sort intervals by finishing time; greedily take the next one that starts after the last taken one's end.

#### When should I recognize it?
- "Maximum meetings / activities / non-overlapping intervals / arrows to burst balloons (point version) / assign mice to holes (sorted pairs)".

#### Core intuition
The earliest finisher leaves maximum remaining room — exchange argument: swap it into any optimal solution without loss.

#### Generic algorithm
1. Sort by `end`.
2. `lastEnd = -inf`; for each interval: if `start >= lastEnd` → take, `lastEnd = end`.
3. Count taken.

#### C++ template
```cpp
int maxMeetings(vector<pair<int,int>> v) {
    sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.second < b.second; });
    int cnt = 0; long long last = LLONG_MIN;
    for (auto& p : v) if (p.first >= last) { cnt++; last = p.second; }
    return cnt;
}
```

#### Time / Space
`O(n log n)` / `O(1)` (output aside).

#### Edge cases
Touching intervals (`start == lastEnd` — usually allowed; check `>=` vs `>`); empty input; unsorted/negative times.

#### Common mistakes
Sorting by start for max-count; wrong overlap comparison (`>` vs `>=` per spec).

#### Variations
Min arrows to cover (sort by end, jump on overlap); min platforms (sweep, not selection — §3.3).

#### Practice mapping
- `06-N-Meetings-in-One-Room.cpp`, `14-Non-Overlapping-Intervals.cpp`, `15-Minimum-Arrows.cpp`, `09-Minimum-Platforms.cpp`

---

### P2 — Sort by Start Time (merge / insert / sweep)

#### What is the pattern?
Sort by start, sweep once merging overlaps (or collecting disjoint pieces).

#### When should I recognize it?
- "Merge intervals", "insert interval", "erase overlapping to make disjoint (min removals)", "insert into disjoint union".

#### Core intuition
Sorted by start, an interval can only overlap a *contiguous* run of the next ones → merge forward with `max(end)`.

#### Generic algorithm
1. Sort by start.
2. `cur = v[0]`; for next: if `next.start <= cur.end` → `cur.end = max(cur.end, next.end)`; else push `cur`, `cur = next`.
3. Push final.

#### C++ template
```cpp
vector<vector<int>> merge(vector<vector<int>>& v) {
    sort(v.begin(), v.end());
    vector<vector<int>> out;
    for (auto& it : v) {
        if (out.empty() || it[0] > out.back()[1]) out.push_back(it);
        else out.back()[1] = max(out.back()[1], it[1]);
    }
    return out;
}
```

#### Time / Space
`O(n log n)` / `O(n)` (or `O(1)` in-place variants).

#### Edge cases
Nested intervals (`[1,10]` then `[2,3]` → keep 10 — use `max`); touching (`==` merges? per spec); single interval.

#### Common mistakes
Forgetting `max` on merge end; merging with `>` when `>=` intended (touching).

#### Variations
Min removals to make non-overlapping = `n − maxNonOverlapping` (reuse P1).

#### Practice mapping
- `13-Merge-Intervals.cpp`, `12-Insert-Interval.cpp`, `14-Non-Overlapping-Intervals.cpp`, `35-Merge-Overlapping-Intervals.cpp` (§03)

---

### P3 — Smallest-First / Largest-First Pairing (assign resources)

#### What is the pattern?
Sort both requirement and resource arrays; pair greedily smallest-satisfying (or largest-first for capacity).

#### When should I recognize it?
- "Assign cookies to children", "assign tasks to workers", "maximum matching of small demands", "least-contention pairing".

#### Core intuition
Using the smallest sufficient resource preserves larger ones for harder demands — a matroid-style exchange argument.

#### Generic algorithm (assign cookies)
1. Sort children greediness ascending, cookie sizes ascending.
2. Two pointers: if `cookie >= greed` → assign, both++; else cookie++ (too small).

#### C++ template
```cpp
int findContentChildren(vector<int> g, vector<int> s) {
    sort(g.begin(), g.end()); sort(s.begin(), s.end());
    int i = 0, j = 0;
    while (i < (int)g.size() && j < (int)s.size()) {
        if (s[j] >= g[i]) i++;      // satisfied
        j++;                        // cookie used either way
    }
    return i;
}
```

#### Time / Space
`O(n log n + m log m)` / `O(1)`.

#### Edge cases
More children than cookies (or vice versa); all cookies too small (0 assigned); equal values.

#### Common mistakes
Pairing largest-first when smallest-first is required (wastes resources); not sorting at all.

#### Variations
Lemonade change (give smallest feasible bill back — `5`s first); fractional knapsack (ratio sort — P4).

#### Practice mapping
- `01-Assign-Cookies.cpp`, `04-Lemonade-Change.cpp`, `16-SJF-Scheduling.cpp`

---

### P4 — Ratio / Value Greedy (fractional knapsack, job sequencing)

#### What is the pattern?
Sort by *value density* (or profit/deadline) and take as much as possible of the best remaining item.

#### When should I recognize it?
- "Fractional knapsack" (break items), "job sequencing with deadlines" (profit order + slot packing), "min cost merging" variants.

#### Core intuition
Highest value-per-unit first → each unit of capacity buys the most value; a unit taken from a lower-ratio item could be exchanged for a higher-ratio unit without loss.

#### Generic algorithm (fractional)
1. Sort by `value/weight` descending.
2. Take whole items while capacity allows; take a fraction of the next; stop.

#### C++ template
```cpp
double fractionalKnapsack(vector<int> val, vector<int> wt, int W) {
    vector<int> idx(val.size());
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return (long long)val[a] * wt[b] > (long long)val[b] * wt[a];   // ratio, cross-mult
    });
    double ans = 0;
    for (int i : idx) {
        if (W >= wt[i]) { W -= wt[i]; ans += val[i]; }
        else            { ans += (double)val[i] * W / wt[i]; break; }
    }
    return ans;
}
```

#### Time / Space
`O(n log n)` / `O(1)`.

#### Edge cases
Capacity 0; item weight 0 (infinite ratio — handle); equal ratios (any order); one item heavier than all capacity.

#### Common mistakes
Computing `value/weight` as integer division (lose precision → sort by cross-multiplication); applying fractional greedy to **0/1 knapsack** (that needs DP — §16!).

#### Variations
Job sequencing: sort by profit desc, place each job in the latest free slot ≤ deadline (DSU slot optimization advanced).

#### Practice mapping
- `02-Fractional-Knapsack.cpp`, `03-Minimum-Coins.cpp`, `10-Job-Sequencing.cpp`, `11-Candy.cpp`

---

### P5 — Coverage / Reachability Greedy (jump game, gas station)

#### What is the pattern?
Maintain a running "farthest reachable" (or total/prefix balance) and make a single forward pass committing when forced.

#### When should I recognize it?
- "Can reach end / minimum jumps" (jump I & II), "gas station circuit", "partition labels" (last-occurrence boundaries).

#### Core intuition
The state (`farthest`, `tank`, `last positions`) summarizes feasibility of *everything seen* — commitment points are where the summary would otherwise break.

#### Generic algorithm (jump II)
```text
jumps = 0, curEnd = 0, farthest = 0
for i in 0..n-2:
    farthest = max(farthest, i + a[i])
    if i == curEnd: jumps++; curEnd = farthest   // forced to jump
```

#### C++ template
```cpp
int jump(vector<int>& a) {
    int jumps = 0, curEnd = 0, farthest = 0;
    for (int i = 0; i < (int)a.size() - 1; i++) {
        farthest = max(farthest, i + a[i]);
        if (i == curEnd) { jumps++; curEnd = farthest; }
    }
    return jumps;
}
```

#### Time / Space
`O(n)` / `O(1)`.

#### Edge cases
Already at end (0 jumps); unreachable (`i > farthest` → fail in Jump I); single element; zeros.

#### Common mistakes
Counting a jump when `farthest` didn't improve (Jump I check: `if (i > farthest) return false`); jumping at `i == n-1` unnecessarily.

#### Variations
Partition labels: extend segment while any char's last occurrence is inside; gas station: reset start after deficit (§3.5).

#### Practice mapping
- `07-Jump-Game-I.cpp`, `08-Jump-Game-II.cpp`

---

### P6 — Two-Pointer / Two-Pass Greedy (candy, valid parentheses range)

#### What is the pattern?
Independent constraints handled in separate passes (left→right, right→left), or a balanced `lo/hi` range scanned with two counters.

#### When should I recognize it?
- "Candy distribution" (both neighbors), "valid parentheses with `*`" (min/max possible balance), "partition labels" pass.

#### Core intuition
When one pass cannot see both directions, run two passes and combine (max/and) — each pass is locally greedy and the combination satisfies both constraint sets.

#### Generic algorithm (candy)
1. `cand[i] = 1` all.
2. Left→right: if `r[i] > r[i-1]` → `cand[i] = cand[i-1] + 1`.
3. Right→left: mirror rule.
4. Answer = Σ `max`-combined values.

**Valid parentheses with `*`**: `lo` never below 0 (treat `*` as `)` when possible), `hi` never below 0 → valid iff `lo == 0` at end.

#### Time / Space
`O(n)` / `O(n)` (candy), `O(1)` (parentheses range).

#### Edge cases
Single element; all equal (all get minimum); unbalanced early (`hi < 0` → impossible).

#### Common mistakes
Using the second pass to *overwrite* instead of `max`; forgetting to cap `hi` (don't let `*` inflate unboundedly — cap at `n`).

#### Variations
Dutch-flag-style single-pass where constraints allow (§03/§02).

#### Practice mapping
- `11-Candy.cpp`, `05-Valid-Parenthesis-String.cpp`

---

## 5. PATTERN RECOGNITION

| If the problem says... | Think about... |
|---|---|
| "maximum number of meetings / non-overlapping" | sort by END (P1) |
| "merge / insert intervals" | sort by START (P2) |
| "minimum arrows to cover" | sort by end + jump (P1 variant) |
| "minimum platforms / simultaneous" | arrival–departure sweep (§3.3) |
| "assign smallest sufficient resource" | smallest-first pairing (P3) |
| "fractional knapsack" | ratio sort (P4) |
| "0/1 knapsack" | **DP, not greedy!** (§16) |
| "minimum jumps / can reach" | coverage farthest (P5) |
| "circuit / start point with balance" | gas station prefix (§3.5) |
| "candy / both neighbors" | two passes (P6) |
| "greedy coins work?" | canonical system? else DP |
| "job sequencing with profit" | profit desc + latest free slot |
| "partition labels / smallest windows covering" | last-occurrence boundaries |
| "lexicographically smallest/largest arrangement" | always pick smallest feasible next (with proof) |

**Decision rules**
1. **Maximize count of compatible things** → sort by end time.
2. **Merge overlapping** → sort by start.
3. **Resource pairing** → sort both, smallest sufficient.
4. **Fractional** → ratio; **integral (0/1)** → DP.
5. **Coverage/rounds** → farthest-reach single pass.
6. Unsure if greedy holds → **exchange argument** or use DP.

---

## 6. BRUTE → BETTER → OPTIMAL THINKING

### Maximum non-overlapping meetings
- **Brute** — try every subset, check compatibility: `O(2^n)`.
- **Better** — DP over sorted-by-end intervals: `O(n²)`.
- **Optimal** — sort by end + greedy scan: `O(n log n)`. Exchange argument proves it matches the DP.

### Fractional knapsack
- **Brute** — try all subsets of whole items + fractions: exponential.
- **Better** — sort by value descending (ignores weight): wrong.
- **Optimal** — sort by value/weight ratio: `O(n log n)`, provable via exchange of one unit.

### Jump game II
- **Brute** — BFS/DFS over positions: `O(n²)` (each state re-explores).
- **Better** — level-by-level BFS (layers = jumps): `O(n)`, `O(n)` space.
- **Optimal** — single pass tracking `farthest`/`curEnd`: `O(n)` time, `O(1)` space — BFS insight inlined.

### Gas station
- **Brute** — simulate from every start: `O(n²)`.
- **Better** — skip starts where prefix sums dip: still quadratic worst case.
- **Optimal** — one pass with total + reset-after-deficit: `O(n)`, `O(1)`.

### Coin change (canonical vs arbitrary)
- **Brute** — try all coin sequences: exponential.
- **Better** — greedy largest-first: `O(n log n)` — **correct only for canonical systems**.
- **Optimal** — for canonical: greedy `O(n)`; for arbitrary: DP `O(amount·coins)` (§16). Knowing *which* you're in is the skill.

### Job sequencing with deadlines
- **Brute** — all assignments: exponential.
- **Better** — DP by time slot: `O(n·maxDeadline)`.
- **Optimal** — profit-descending + latest-free-slot (array or DSU): `O(n log n)`.

### Key transferable idea
> Greedy optimality always reduces to: **sort by the key that makes the choice safe, then never look back.** If you can't name the key or the exchange argument, it's probably not greedy.

---

## 7. C++ / STL TOOLKIT

| Tool | Syntax | Use |
|---|---|---|
| Sort with comparator | `sort(v.begin(), v.end(), [](auto& a, auto& b){ return a.second < b.second; })` | interval key |
| `pair` / `vector<int>` intervals | `pair<int,int>` or `vector<int>{s,e}` | start/end storage |
| Two-pointer loop | `int i = 0, j = 0; while (...)` | pairing after sort |
| `iota` | `iota(idx.begin(), idx.end(), 0)` | index sort without copying |
| `accumulate` | `accumulate(v.begin(), v.end(), 0LL)` | totals (`long long` init) |
| `multiset` | erase one occurrence | alternative for dynamic intervals |

```cpp
// sort by custom key (cross-multiply ratios to avoid float)
sort(v.begin(), v.end(), [&](auto& a, auto& b) {
    return (long long)a.val * b.wt > (long long)b.val * a.wt;
});

// stable tie-breaking: secondary key
sort(v.begin(), v.end(), [](auto& a, auto& b) {
    if (a.end != b.end) return a.end < b.end;
    return a.start < b.start;         // tie-break
});
```

**Common mistakes**
- Comparator not strict weak ordering (use `<` consistently; `a <= b` breaks sort).
- Integer division when comparing ratios — use cross-multiplication with `long long`.
- Unstable assumptions: `sort` is unstable; add explicit tie-breakers when required.

---

## 8. COMPLEXITY GUIDE

| Pattern | Time | Space |
|---|---:|---:|
| Sort + scan (most greedy) | `O(n log n)` | `O(1)`–`O(n)` |
| Interval merge | `O(n log n)` | `O(n)` |
| Platforms sweep | `O(n log n)` | `O(1)` |
| Pairing (two sorted arrays) | `O(n log n)` | `O(1)` |
| Jump / gas (single pass) | `O(n)` | `O(1)` |
| Candy (two passes) | `O(n)` | `O(n)` |
| Fractional knapsack | `O(n log n)` | `O(1)` |
| Job sequencing (slots) | `O(n log n + n·D)` or DSU `O(n log n)` | `O(D)` |
| Lemonade change | `O(n)` | `O(1)` |
| Coins greedy | `O(n log n)` (sort) / `O(n)` | `O(1)` |

**How to estimate** — greedy cost = **sort cost + linear scan**. If no sorting needed (single pass), it's `O(n)`. Watch for `O(n·maxValue)` slot arrays → bound or DSU.

---

## 9. EDGE CASES

- **Empty input** — 0 meetings, 0 platforms, trivially feasible.
- **One interval / one station** — take it; jumps = 0.
- **Touching intervals** (`end == start`) — allowed? check `>=` vs `>`.
- **Fully nested intervals** — merge must take `max(end)`.
- **All cookies too small / no feasible** — answer 0 / false.
- **Ties in sort keys** — need deterministic tie-break or any order (state which).
- **Jump I unreachable** — detect `i > farthest`.
- **Negative gas / candy ratings** — formulas still hold; initialize correctly.
- **Zero-weight item (fractional)** — infinite ratio handling per spec.
- **Overflow** — sums of candies `n(n+1)/2` for `n=5·10^4` → `long long`.
- **Circular arrays** (gas) — one pass assumption: start index wraps via modulo.

---

## 10. COMMON MISTAKES

| # | Mistake | What goes wrong | Why | How to avoid |
|---|---|---|---|---|
| 1 | Sorting by start for max-count | wrong selection | start doesn't free resources early | sort by **end** |
| 2 | Greedy on 0/1 knapsack | suboptimal | fractional ≠ integral | DP (§16) for 0/1 |
| 3 | `>` vs `>=` on touching intervals | off-by-one counts | spec-dependent boundary | check statement; default `>=` for meetings |
| 4 | Forgetting `max(end)` in merge | shrinks merged range | nested intervals | `cur.end = max(cur.end, next.end)` |
| 5 | Integer ratio division | wrong sort order | `v1/w1 < v2/w2` not `v1/w1` int | cross-multiply `long long` |
| 6 | Jump II counting early | overcounts jumps | jumps only when forced | increment only at `i == curEnd` |
| 7 | Gas: ignoring total check | wrong "possible" answer | deficit reset alone isn't enough | require `total >= 0` |
| 8 | Candy single pass | violates one direction | can't see both neighbors | two passes + `max` |
| 9 | Non-strict-weak comparator | sort crash/UB | `a <= b` both ways true | strict `<` only |
| 10 | Assuming greedy without proof | WA on edge cases | greedy needs exchange argument | state proof or use DP |
| 11 | Not initializing `lastEnd` | first interval rejected | garbage start value | `-inf` / `LLONG_MIN` |
| 12 | Overflow in day/count totals | wrapped output | large n | `long long` |

**Conceptual mistakes**
- Confusing **selection** (choose subset — sort by end) with **resource counting** (overlap sweep).
- Using greedy for lexicographic *arrangements with constraints* without checking feasibility of each choice (sometimes needs backtracking/DP).

---

## 11. IMPORTANT FORMULAS / RULES

```text
Max non-overlap:         sort by end; take if start >= lastEnd
Min removals to disjoint: n - maxNonOverlap(end-sorted)
Merge:                   sorted by start; merge if start <= cur.end (take max end)
Platforms needed:        max over time of (arrivals <= t) - (departed < t)  [sweep]
Fractional knapsack:     sort by v/w desc; take fraction of first overflow item
Jump I:                  reachable iff never i > farthest (farthest = max(i + a[i]))
Jump II:                 jump when i == curEnd; curEnd = farthest
Gas:                     possible iff sum(gas - cost) >= 0; start after min-prefix point
Candy:                   sum(max(leftPass, rightPass))
Coins (canonical):       greedy largest-first (proof = canonical system)
Job sequencing:          profit desc -> latest free slot <= deadline
Partition labels:        segment extends while i <= min(last occurrence of chars in segment)
```

**Decision rules / invariants**
1. After sorting by end, `lastEnd` never decreases — greedy state is a single number.
2. If the greedy choice's key is ambiguous (start vs end vs ratio) → re-derive from the *goal* (free room = end; merge = start; value density = ratio).
3. Greedy is optimal only with a proof — otherwise use DP.

---

## 12. REUSABLE TEMPLATES

```cpp
// 1. Max non-overlapping intervals (sort by end)
int maxNonOverlap(vector<pair<int,int>> v) {
    sort(v.begin(), v.end(), [](auto& a, auto& b){ return a.second < b.second; });
    int cnt = 0; long long last = LLONG_MIN;
    for (auto& p : v) if (p.first >= last) { cnt++; last = p.second; }
    return cnt;
}

// 2. Merge intervals
vector<vector<int>> merge(vector<vector<int>>& v) {
    sort(v.begin(), v.end());
    vector<vector<int>> out;
    for (auto& it : v) {
        if (out.empty() || it[0] > out.back()[1]) out.push_back(it);
        else out.back()[1] = max(out.back()[1], it[1]);
    }
    return out;
}

// 3. Jump II
int jump(vector<int>& a) {
    int jumps = 0, curEnd = 0, farthest = 0;
    for (int i = 0; i < (int)a.size() - 1; i++) {
        farthest = max(farthest, i + a[i]);
        if (i == curEnd) { jumps++; curEnd = farthest; }
    }
    return jumps;
}

// 4. Assign cookies (smallest sufficient)
int assign(vector<int> g, vector<int> s) {
    sort(g.begin(), g.end()); sort(s.begin(), s.end());
    int i = 0, j = 0;
    while (i < (int)g.size() && j < (int)s.size()) { if (s[j] >= g[i]) i++; j++; }
    return i;
}
```

## 13. ADVANCED CONCEPTS

### 13.1 Exchange argument (proof technique)
Formal shape: take any optimal solution `O` differing from greedy `G` at the first choice; show swapping `G`'s choice in doesn't worsen `O`; repeat to transform `O` into `G`. Practice on: interval scheduling, Huffman, MST (Kruskal).

### 13.2 Matroids (why greedy provably works)
Greedy is optimal on **matroids** (structures closed under exchange with rank = size). Interval scheduling and spanning trees form matroids — naming this impresses interviewers; no need to prove theory live.

### 13.3 Huffman coding (optimal prefix codes)
Repeatedly merge the two smallest frequencies (P4-style heap greedy) → optimal prefix code. Same shape as connect-ropes. `O(n log n)`.

### 13.4 Scheduling theory (Earliest Deadline First)
EDF is optimal for meeting *all* deadlines on one machine when preemptable — sort by deadline. Knowing "sort by end ⇒ max count, sort by deadline ⇒ feasibility" clarifies which key to use.

### 13.5 Greedy with a heap (online greedy)
When the best choice isn't known after sorting (items arrive online / depend on state), a heap supplies the next best: task scheduling, Dijkstra (§15), interval scheduling with weights (weighted variant is DP-hard!).

### 13.6 Where greedy fails (know the counterexamples)
- 0/1 knapsack: greedy by ratio fails (`{60/10, 100/20, 120/30}` W=50 → ratio picks 10,20,20 of item3... classic counterexample).
- Arbitrary coin systems (`1,3,4` → 6).
- Longest path / traveling salesman (needs DP).
- Activity selection with *profits* (weighted intervals → DP).

---

## 14. CONNECTIONS BETWEEN PATTERNS

```text
Sort (§02)
  |
  +-- sort by END -------> max non-overlap / arrows / mice
  +-- sort by START ------> merge / insert intervals
  +-- sort by ratio ------> fractional knapsack
  +-- sort both ----------> pairing (cookies)
  +-- sort by profit -----> job sequencing / scheduling
  |
Single-pass scan
  +-- farthest reach ------> jump game
  +-- prefix balance ------> gas station
  +-- two passes ---------> candy (bidirectional constraints)
  |
Heap-based greedy (§11)
  +-- pop-2 push-1 -------> Huffman / ropes
  +-- priority queue -----> Dijkstra (§15), task scheduling
  |
When greedy fails --> DP (§16)  [0/1 knapsack, weighted intervals, coins general]
When greedy works --> proof (exchange / matroid)
```

**Mental map** — sort keys: **end** (free resources), **start** (merge), **ratio** (density), **profit** (value), **deadline** (feasibility). No key? Probably DP.

---

## 15. PROBLEM → PATTERN MAPPING

*(Reference only — solutions and approaches live in the `.cpp` files.)*

### Pairing / smallest-first
- `01-Assign-Cookies.cpp`
- `04-Lemonade-Change.cpp`
- `16-SJF-Scheduling.cpp`

### Interval selection (sort by end)
- `06-N-Meetings-in-One-Room.cpp`
- `14-Non-Overlapping-Intervals.cpp`
- `15-Minimum-Arrows.cpp`
- `09-Minimum-Platforms.cpp`

### Interval merge / insert (sort by start)
- `13-Merge-Intervals.cpp`
- `12-Insert-Interval.cpp`

### Ratio / value greedy
- `02-Fractional-Knapsack.cpp`
- `10-Job-Sequencing.cpp`
- `03-Minimum-Coins.cpp`

### Coverage / reachability
- `07-Jump-Game-I.cpp`
- `08-Jump-Game-II.cpp`

### Two-pass / range greedy
- `11-Candy.cpp`
- `05-Valid-Parenthesis-String.cpp`

---

## 16. QUICK REVISION SHEET

**Concepts**
- Greedy = locally optimal choice + **proof** (exchange argument). Sort by the key that makes the choice safe, then scan.
- Sort keys: **end** → max count · **start** → merge · **ratio** → fractional · **profit** → scheduling · both-sorted → pairing.
- Selection ≠ sweep ≠ pairing — identify the problem family first.

**Recognition clues**
| Signal | Key |
|---|---|
| maximize non-overlapping count | sort by end |
| merge overlaps | sort by start |
| fractional knapsack | value/weight desc |
| smallest sufficient resource | sort both asc |
| min jumps / reachability | farthest-reach pass |
| both neighbors constrained | two passes |
| arbitrary coins / 0/1 knapsack | **DP, not greedy** |

**Formulas**
```text
min removals = n - maxNonOverlap
jump: jump only when i == curEnd; curEnd = farthest
gas:  total >= 0; start after min prefix deficit
candy: sum(max(leftPass, rightPass))
```

**Complexity** — sort+scan `O(n log n)` · single-pass `O(n)` · two-pass `O(n)`.

**Common mistakes** — start-vs-end sort · greedy without proof on 0/1 problems · `>`/`>=` touching · missing `max(end)` in merge · integer ratio division · jump overcount.

**Decision rules** — name the sort key → write the scan → (optionally) state the exchange argument. Can't name the key? → DP.

---

## 17. INTERVIEW CHECKLIST

- [ ] Can I state the greedy choice property and sketch an exchange argument?
- [ ] Can I choose the correct sort key (end/start/ratio/profit) instantly?
- [ ] Can I write merge-intervals and max-non-overlap without bugs?
- [ ] Can I distinguish selection problems from sweep (platforms) problems?
- [ ] Can I write jump II with the `curEnd/farthest` logic?
- [ ] Can I explain why greedy fails on 0/1 knapsack with a counterexample?
- [ ] Can I handle touching/nested/tied intervals per the exact spec?
- [ ] Can I justify gas station with total ≥ 0 + min-prefix reasoning?
- [ ] Can I write candy as two passes and explain why one isn't enough?
- [ ] Can I state complexity as sort + scan and verify against constraints?

<!-- done -->
