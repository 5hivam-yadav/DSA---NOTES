# Greedy — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — Sort by End Time (maximize count of non-overlapping intervals)

**What is the pattern?**

Sort intervals by finishing time; greedily take the next one that starts after the last taken one's end.

**When should I recognize it?**

- "Maximum meetings / activities / non-overlapping intervals / arrows to burst balloons (point version) / assign mice to holes (sorted pairs)".

**Core intuition**

The earliest finisher leaves maximum remaining room — exchange argument: swap it into any optimal solution without loss.

**Generic algorithm**

1. Sort by `end`.
2. `lastEnd = -inf`; for each interval: if `start >= lastEnd` → take, `lastEnd = end`.
3. Count taken.

**Time / Space**

`O(n log n)` / `O(1)` (output aside).

**Edge cases**

Touching intervals (`start == lastEnd` — usually allowed; check `>=` vs `>`); empty input; unsorted/negative times.

**Common mistakes**

Sorting by start for max-count; wrong overlap comparison (`>` vs `>=` per spec).

**Variations**

Min arrows to cover (sort by end, jump on overlap); min platforms (sweep, not selection — §3.3).

### P2 — Sort by Start Time (merge / insert / sweep)

**What is the pattern?**

Sort by start, sweep once merging overlaps (or collecting disjoint pieces).

**When should I recognize it?**

- "Merge intervals", "insert interval", "erase overlapping to make disjoint (min removals)", "insert into disjoint union".

**Core intuition**

Sorted by start, an interval can only overlap a *contiguous* run of the next ones → merge forward with `max(end)`.

**Generic algorithm**

1. Sort by start.
2. `cur = v[0]`; for next: if `next.start <= cur.end` → `cur.end = max(cur.end, next.end)`; else push `cur`, `cur = next`.
3. Push final.

**Time / Space**

`O(n log n)` / `O(n)` (or `O(1)` in-place variants).

**Edge cases**

Nested intervals (`[1,10]` then `[2,3]` → keep 10 — use `max`); touching (`==` merges? per spec); single interval.

**Common mistakes**

Forgetting `max` on merge end; merging with `>` when `>=` intended (touching).

**Variations**

Min removals to make non-overlapping = `n − maxNonOverlapping` (reuse P1).

### P3 — Smallest-First / Largest-First Pairing (assign resources)

**What is the pattern?**

Sort both requirement and resource arrays; pair greedily smallest-satisfying (or largest-first for capacity).

**When should I recognize it?**

- "Assign cookies to children", "assign tasks to workers", "maximum matching of small demands", "least-contention pairing".

**Core intuition**

Using the smallest sufficient resource preserves larger ones for harder demands — a matroid-style exchange argument.

**Generic algorithm (assign cookies)**

1. Sort children greediness ascending, cookie sizes ascending.
2. Two pointers: if `cookie >= greed` → assign, both++; else cookie++ (too small).

**Time / Space**

`O(n log n + m log m)` / `O(1)`.

**Edge cases**

More children than cookies (or vice versa); all cookies too small (0 assigned); equal values.

**Common mistakes**

Pairing largest-first when smallest-first is required (wastes resources); not sorting at all.

**Variations**

Lemonade change (give smallest feasible bill back — `5`s first); fractional knapsack (ratio sort — P4).

### P4 — Ratio / Value Greedy (fractional knapsack, job sequencing)

**What is the pattern?**

Sort by *value density* (or profit/deadline) and take as much as possible of the best remaining item.

**When should I recognize it?**

- "Fractional knapsack" (break items), "job sequencing with deadlines" (profit order + slot packing), "min cost merging" variants.

**Core intuition**

Highest value-per-unit first → each unit of capacity buys the most value; a unit taken from a lower-ratio item could be exchanged for a higher-ratio unit without loss.

**Generic algorithm (fractional)**

1. Sort by `value/weight` descending.
2. Take whole items while capacity allows; take a fraction of the next; stop.

**Time / Space**

`O(n log n)` / `O(1)`.

**Edge cases**

Capacity 0; item weight 0 (infinite ratio — handle); equal ratios (any order); one item heavier than all capacity.

**Common mistakes**

Computing `value/weight` as integer division (lose precision → sort by cross-multiplication); applying fractional greedy to **0/1 knapsack** (that needs DP — §16!).

**Variations**

Job sequencing: sort by profit desc, place each job in the latest free slot ≤ deadline (DSU slot optimization advanced).

### P5 — Coverage / Reachability Greedy (jump game, gas station)

**What is the pattern?**

Maintain a running "farthest reachable" (or total/prefix balance) and make a single forward pass committing when forced.

**When should I recognize it?**

- "Can reach end / minimum jumps" (jump I & II), "gas station circuit", "partition labels" (last-occurrence boundaries).

**Core intuition**

The state (`farthest`, `tank`, `last positions`) summarizes feasibility of *everything seen* — commitment points are where the summary would otherwise break.

**Generic algorithm (jump II)**

```text
jumps = 0, curEnd = 0, farthest = 0
for i in 0..n-2:
    farthest = max(farthest, i + a[i])
    if i == curEnd: jumps++; curEnd = farthest   // forced to jump
```

**Time / Space**

`O(n)` / `O(1)`.

**Edge cases**

Already at end (0 jumps); unreachable (`i > farthest` → fail in Jump I); single element; zeros.

**Common mistakes**

Counting a jump when `farthest` didn't improve (Jump I check: `if (i > farthest) return false`); jumping at `i == n-1` unnecessarily.

**Variations**

Partition labels: extend segment while any char's last occurrence is inside; gas station: reset start after deficit (§3.5).

### P6 — Two-Pointer / Two-Pass Greedy (candy, valid parentheses range)

**What is the pattern?**

Independent constraints handled in separate passes (left→right, right→left), or a balanced `lo/hi` range scanned with two counters.

**When should I recognize it?**

- "Candy distribution" (both neighbors), "valid parentheses with `*`" (min/max possible balance), "partition labels" pass.

**Core intuition**

When one pass cannot see both directions, run two passes and combine (max/and) — each pass is locally greedy and the combination satisfies both constraint sets.

**Generic algorithm (candy)**

1. `cand[i] = 1` all.
2. Left→right: if `r[i] > r[i-1]` → `cand[i] = cand[i-1] + 1`.
3. Right→left: mirror rule.
4. Answer = Σ `max`-combined values.

**Valid parentheses with `*`**: `lo` never below 0 (treat `*` as `)` when possible), `hi` never below 0 → valid iff `lo == 0` at end.

**Time / Space**

`O(n)` / `O(n)` (candy), `O(1)` (parentheses range).

**Edge cases**

Single element; all equal (all get minimum); unbalanced early (`hi < 0` → impossible).

**Common mistakes**

Using the second pass to *overwrite* instead of `max`; forgetting to cap `hi` (don't let `*` inflate unboundedly — cap at `n`).

**Variations**

Dutch-flag-style single-pass where constraints allow (§03/§02).

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
