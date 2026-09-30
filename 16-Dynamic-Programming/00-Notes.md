# Dynamic Programming — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — Linear (1D) DP: take/skip with adjacency constraints

**What is the pattern?**

`dp[i]` = best answer for prefix `0..i`, transitioned from the previous one or two states.

**When should I recognize it?**

- "Climb stairs / frog jump / min cost climbing", "house robber I & II", "max sum of non-adjacent elements", "ninja training (days × 3 styles)", "delete and earn".

**Core intuition**

At position `i` you either **take** it (paying the "gap" cost — can't take `i-1`) or **skip** it (inherit `dp[i-1]`). Each state only needs a fixed window of history.

**Generic algorithm**

```text
dp[i] = best considering first i items
skip:  dp[i-1]
take:  value[i] + dp[i - gap]      (gap = 1 for non-adjacent, 0/1 elsewhere)
dp[i] = combine(skip, take)
```

**Time / Space**

`O(n)` time; `O(1)` space (two scalars) — rolling from `O(n)`.

**Edge cases**

`n = 0/1`; all zeros; negative values (careful: empty selection may be 0 vs "must pick"); circular variant (first & last conflict).

**Common mistakes**

Using `dp[i] = x` instead of `max(skip, take)`; circular case forgetting the two linear sub-runs; off-by-one in `i - gap`.

**Variations**

Frog jump (min of `|h[i]-h[i-1]|`, `|h[i]-h[i-2]|`); ninja training (state = *last style*, `dp[day][last]` → `O(1)` space with 3 vars); min cost climb (`dp[i] = cost[i] + min(dp[i-1], dp[i-2])`).

### P2 — Grid DP (paths, obstacles, minima, falling)

**What is the pattern?**

`dp[r][c]` = best/ways to reach cell `(r,c)`; each cell aggregates from allowed predecessors (right/down, or the row above).

**When should I recognize it?**

- "Unique paths", "unique paths with obstacles", "minimum path sum", "triangle min path", "minimum falling path sum", "cherry pickup II (two agents)", "maximal square (histogram heights)".

**Core intuition**

Only moves *toward the target* matter → DAG of cells → DP over top-left → bottom-right order; ways sum, minima take min.

**Generic algorithm**

```text
dp[0][0] = base
first row/col:  only reachable from one direction (or blocked)
dp[r][c] = combine(dp[predecessors]) + cost(r,c)
answer = dp[R-1][C-1]  (or max over last row)
```

**Time / Space**

`O(R·C)` time and space → `O(C)` with rolling rows.

**Edge cases**

1×1 grid; blocked cells (obstacles → 0 ways); unreachable (min = INF sentinel); negative values (min path needs careful init).

**Common mistakes**

Forgetting first-row/first-column initialization; obstacle cell should be `0` (ways) not `+1`; using `dp[r-1][c]` on `r=0` (guard or padded 1-row).

**Variations**

Triangle (index-based 1D from bottom up); cherry pickup (two walkers `dp[r1][r2]`, share row → `O(n²)` space); max path sum with *choices at each row* (ninja/unique paths III variants); maximal rectangle = histogram DP per row (§09 contribution + DP).

### P3 — Knapsack family (0/1, subset sum, partition, target)

**What is the pattern?**

Choose items subject to a **capacity/target constraint**; `dp[i][w]` = best (or possible) using the first `i` items with capacity/target `w`.

**When should I recognize it?**

- "Subset with sum K exists?", "partition array into two equal sums", "minimum subset sum difference", "count subsets with sum K", "target sum with +/−", "0/1 knapsack maximize value", "last stone weight / partition to min difference".

**Core intuition**

Every item: **skip** (inherit previous row) or **take** (jump to `w − weight[i]`). The capacity dimension is what makes choices interact — that's the DP.

**Generic algorithm**

```text
bool/ways dp[0..n][0..K]:
  dp[0][0] = true/1
  take:  dp[i-1][w - wt[i]]   (if w >= wt[i])
  skip:  dp[i-1][w]
  dp[i][w] = combine
answer: dp[n][K]   (or min over |total - 2S| for partition difference)
```

**0/1 vs unbounded (loop direction on 1D)** — the #1 DP trap:

```text
0/1 (each item once):     for w = W down to wt[i]   // reads OLD row
unbounded (reuse allowed): for w = wt[i] up to W     // reuses THIS item
```

**Time / Space**

`O(n·K)` time; `O(K)` space (1D) or `O(n·K)` (2D for reconstruction).

**Edge cases**

`K = 0` (empty subset — usually true); item > K (skip); zeros (careful counting); all items negative (max value = 0 unless must-pick); `K` huge (MLE — pseudo-polynomial!).

**Common mistakes**

Wrong loop direction (0/1 vs unbounded); forgetting `dp[0][0]`/`dp[0] = true` base; counting *combinations vs permutations* (outer loop order); using `int` for counts (mod).

**Variations**

**Partition equal**: `K = total/2` (odd total → false). **Min difference**: `K` = closest achievable to `total/2`. **Count subsets**: `dp[w] += dp[w - x]` (ascending, combinations order). **Target sum (±)**: count subsets with `s = (total + target)/2`. **Partition with difference d**: `s = (total + d)/2`.

### P4 — Unbounded knapsack & cutting (coins, rod, rod/cut variants)

**What is the pattern?**

Same as knapsack but items **can be reused** — recognized by "unlimited supply" (coins) or "cut a rod / buy any number".

**When should I recognize it?**

- "Coin change (min coins / count combinations)", "rod cutting maximize value", "perfect squares", "word break (dictionary reuse)".

**Core intuition**

Because item `i` may be reused, the transition may *stay on the same row* → iterate capacity **ascending** so `dp[w - c]` already includes using `i`.

**Generic algorithm**

```text
min coins:   dp[0]=0; dp[w] = min over coins (dp[w-c] + 1)   [INF if impossible]
count ways:  OUTER loop over coins, inner over w ascending   (combinations!)
rod:         dp[len] = max(price[i] + dp[len - len_i])
```

**Time / Space**

`O(amount · |coins|)` (or `O(n·W)` generally); `O(amount)` space.

**Edge cases**

Amount 0 (0 coins); impossible (`-1`); coin > amount; duplicate coins (dedup for counting); count-ways overflow (mod).

**Common mistakes**

Loop direction (permutations vs combinations for counting); leaving `INF + 1` overflowing into valid range (use a large sentinel and guard); rod cutting index base (`len` from 1).

**Variations**

Word break = boolean unbounded knapsack over dictionary *prefixes*; perfect squares (`dp[w] = 1 + min dp[w - i²]`); minimum insertions to reach word (forward DP).

### P5 — 2D linear DP (triangle, max-path, multi-way games)

**What is the pattern?**

The same 1D take/skip logic, but **two or more previous states** are needed, so the state is written as a table `dp[i][j]`.

**When should I recognize it?**

- "Maximum path from top to bottom **moving left/right/down**" (no down-up constraint).
- "Path from `(0,0)` to `(r-1,c-1)` picking up cells **except ends**" (cherry pickup).
- "Choose an element from **each row**, maximizing the sum" (triangle).
- "Delete and earn" style variants with two quantities tracking together.

**Core intuition**

> **Remember** — 1D with *one* previous state → scalars. 1D with *two or more* previous states → table. The moment you need `dp[i-1]` **and** `dp[i-2]` **and** `dp[j-1]`, stop compressing and just make the 2D grid; it is easier to write and to debug.

**Generic algorithm**

```text
for i = 0 .. n-1:
    for j = 0 .. m-1:
        if start:      dp[i][j] = base(i, j)
        else:          dp[i][j] = value(i,j) + combine( dp[i-1][j-1], dp[i-1][j], dp[i][j-1] )
answer = dp[n-1][m-1]
```

**Time / Space**

`O(r·c)` time; `O(r·c)` space. Cherry pickup is `O(n³)` (three nested loops) with `O(n²)` space via 3 layers.

**Edge cases**

Falling path: answer is the **max of the last row**, not a corner. Cherry pickup: `n = 1`; the two cherries on the final row can both be collected (hence three candidate answers); symmetric pruning `a ≤ b`. Triangle: `n = 1`.

**Common mistakes**

- Returning `dp[n-1][m-1]` when the walk may end anywhere.
- Forgetting that the two cherry walkers are **independent** (each chooses left/right separately → 4 moves) and that they *can* land on the same cell.
- Reusing the input grid as the DP table and then reading the original values back for comparisons.

**Variations**

"Delete and earn" (`dp[c] = max(dp[c], c + dp[c - gap])`); "grid with exactly k moves"; "maximum sum path with jumps" (jump-game variants → 1D greedy/DP).

### P6 — String DP I: the LCS family

**What is the pattern?**

Two strings (or a string and itself) form a **grid of prefix pairs**. `dp[i][j]` = the answer for the prefixes `s[0..i-1]` and `t[0..j-1]`. Almost every hard string-DP problem on the sheet is a thin disguise of LCS or of a *substring* variant of it.

**When should I recognize it?**

| Clue in the statement | Pattern |
|---|---|
| "longest sequence that appears in **both**" | LCS |
| "sequence in `s` that is also a **subsequence of `t`**, increasing" | LCIS |
| "longest string that is a sub-sequence of its **reverse**" | LPS = LCS(s, reverse(s)) |
| "shortest string **supersequence** of both" | derived from LCS length |
| "minimum insertions so `s` becomes a palindrome" | LCS(s, reverse(s)) derived |
| "min **insertions + deletions** to make `s` a subsequence of `t`" | LCS derived |
| "longest common **substring**" (contiguous!) | LCS with the *reset* rule |

**Core intuition**

Look at the **last characters** of both prefixes. Two cases:

1. `s[i-1] == t[j-1]` → they match, extend the common answer: `dp[i][j] = dp[i-1][j-1] + 1`.
2. They differ → at least one must be dropped: `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`.
3. One prefix empty → `0`.

> **Important** — Subsequence = ordered but **not necessarily contiguous**. Substring = contiguous. The *only* difference between the two algorithms is the mismatch case:
> * LCS (subsequence): `max(up, left)` — skip either character, the partial match survives.
> * LCSubstring (contiguous): `dp[i-1][j-1]` — a mismatch **breaks the chain**, restart from 0.

```text
         s:  a b c
             0 1 2 3    <- j
         t:  0 a b c
      (i) 0  0 0 0 0
         1  0 1 1 1
         2  0 1 1 2
         3  0 1 1 2
dp[i][j] = LCS of s[0..i-1], t[0..j-1]
```

**Generic algorithm**

```text
dp[i][0] = dp[0][j] = 0
for i = 1..n:
    for j = 1..m:
        if s[i-1] == t[j-1]:  dp[i][j] = dp[i-1][j-1] + 1
        else:                 dp[i][j] = max(dp[i-1][j], dp[i][j-1])
return dp[n][m]
```

**The LCS-derived family (no new algorithm needed)**

| Problem | Formula from `L = LCS(s, t)` |
|---|---|
| Longest Palindromic Subsequence of `s` | `LCS(s, reverse(s))` |
| Min insertions to make `s` a palindrome | `n - LCS(s, reverse(s))` |
| Min insertions + deletions to make `s` a subseq of `t` | `n + m - 2·L` |
| Length of shortest common supersequence | `n + m - L` |
| Number of distinct common subsequences | `2D counting DP` over the same grid |

> **Remember** — *"min insertions to make palindrome = n − LPS"* and *"SCS length = n + m − LCS"*. These two are asked constantly; recognizing the LCS grid underneath saves an hour.

> **Why** `n − LPS`? Each LPS character already pairs up for free; every other character must be mirrored with a newly inserted one.

**Time / Space**

`O(n·m)` time; `O(n·m)` space, reducible to `O(min(n,m))` since the transition reads only the previous row and the current row's diagonal.

**Edge cases**

Either string empty → `0`; identical strings → `n`; disjoint alphabets → `0`; LPS of a single char → `1`; very long strings (`n·m` up to `10⁸`) → compress to 1D; multi-byte strings → operate on the correct unit (chars vs code points).

**Common mistakes**

- **Mixing substring and subsequence** (forgetting the `: 0` reset).
- Off-by-one confusion: DP indices represent **prefix lengths**, so you must access `s[i-1]`. Be consistent across the whole file.
- Using `>` vs `>=` inconsistently while backtracking — both yield a valid LCS, but pick one.
- Trying to reconstruct from a **1D** DP — reconstruction needs the full table.
- For LPS, forgetting that `reverse(s)` shares characters with `s`; it is still correct, but people wrongly assume it "double counts".

**Variations**

LCIS (longest common **increasing** subsequence, `O(n·m)`); LCS of 3 strings (`O(n·m·k)`); LCS with wildcards (`?`); building the actual shortest common supersequence *string*; "distinct common subsequences" (add a `char`-indexed 3D table).

### P7 — String DP II: edit distance & character choices

**What is the pattern?**

Still a prefix-pair grid, but instead of "longest", the state is a **cost to transform** one string into the other, and the recurrence enumerates the *operations* you may perform on the last character.

**When should I recognize it?**

- "Minimum number of **insert / delete / replace** operations to convert `s` into `t`" → Levenshtein distance.
- "Convert `s` into `t` where `*` is a wildcard" → same grid, restricted transitions.
- "Count **distinct subsequences** of a string" → same grid shape, but the two strings are `s` and `s`, and the operation is "skip or take a character".
- "Number of ways to **delete** characters so both strings become equal" → LCS-derived.

**Core intuition**

At cell `(i, j)` the last characters `s[i-1]` and `t[j-1]` give three possible moves, and we take the cheapest (or sum, if counting):

```text
              s[i-1]  t[j-1]
   +---------+-------+-------+
   | match   | 0     |  dp[i-1][j-1]        no operation
   | insert  |       |  dp[i][j-1]   + 1    add t[j-1] to s
   | delete  |       |  dp[i-1][j]   + 1    remove s[i-1]
   | replace |       |  dp[i-1][j-1] + 1    substitute
   +---------+-------+-------+
```

> **Remember** — Levenshtein distance and LCS length are interchangeable: `distance = n + m - 2 · LCS(s, t)`. If you are comfortable with LCS, you can answer "edit distance" without writing the 4-case transition.

**Generic algorithm (edit distance)**

```text
dp[i][0] = i          // delete everything
dp[0][j] = j          // insert everything
for i = 1..n, j = 1..m:
    if s[i-1] == t[j-1]: dp[i][j] = dp[i-1][j-1]
    else:                 dp[i][j] = 1 + min(dp[i-1][j],    // delete
                                            dp[i][j-1],    // insert
                                            dp[i-1][j-1])   // replace
```

**Time / Space**

`O(n·m)` time, `O(n·m)` space (compressible to `O(min(n,m))` for edit distance / wildcard; distinct subsequences is `O(n)` time and space).

**Edge cases**

Empty string (`n = 0`) → distance to `t` is `m`; identical strings → `0`; pattern with leading/trailing `*`; consecutive `*` (harmless but can be collapsed); string of all identical characters (counting version → `n+1`); modulo overflow for counting variants.

**Common mistakes**

- Swapping insert and delete costs (matters when they differ, e.g. "insert only" or "delete only" variants).
- Forgetting that `*` needs **two** transitions (`dp[i-1][j]` and `dp[i][j-1]`) — one alone gives wrong answers on strings like `"adceb"` / `"*ab*"`.
- Not subtracting duplicates in the distinct-subsequence DP and over-counting (e.g. `"aaa"` → 8 instead of 4).
- Using `vector<vector<bool>>` and then taking references into it (proxy references) — use `char` or `int` if you need element access.

**Variations**

Edit distance with different operation costs; Levenshtein with swaps (Damerau); wildcard with regex classes (`[a-z]`); "min deletions to make both equal" (`n + m − 2·LCS`); count of distinct common subsequences (3D `dp[i][j][k]`); regex matching via backtracking/DP.

### P8 — Stock DP (buy/sell with varying constraints)

**What is the pattern?**

A 1D DP over **days** where the state carries *what you are currently holding*. The set of "states" (how many transactions, whether you hold a stock, whether you are in cooldown) determines which variant you are looking at.

**The five variants at a glance**

| Variant | What the state must remember | Canonical answer |
|---|---|---|
| **I** — one transaction | min price seen so far | `max(price - minSoFar)` |
| **II** — unlimited transactions | nothing (greedy works) | sum of all positive deltas |
| **III** — at most 2 transactions | up to 4 running values | max of 4 states |
| **IV** — at most `k` transactions | 2 arrays of size `k+1` | `O(n·k)` |
| **Cooldown** — 1-day cooldown after selling | 3 states (hold, sold, rest) | max of 3 states |
| **Fee** — transaction fee | 2 states (hold, not-hold) | not-hold at the end |

**Core intuition**

> **Pattern** — When the constraint is *"how many transactions may I make"*, the state must encode that count. When the constraint is *"can I sell today?"*, the state must encode a small number of **named statuses**, and each day you transition between them.

**Generic algorithm (hold / not-hold state machine)**

```text
hold[i]     = max(hold[i-1], -price[i])          // keep holding, or buy today
notHold[i]  = max(notHold[i-1], hold[i-1] + price[i])   // stay out, or sell today
answer = max(hold[n-1], notHold[n-1])            // holding at the end is allowed
```

**Time / Space**

`O(n)` time for I/II/III/cooldown/fee; `O(n·k)` for IV; space `O(1)` (scalars or 3-state arrays) everywhere except IV's `O(k)` arrays.

**Edge cases**

`n = 0` or `n = 1` → `0`; strictly decreasing prices → `0`; `k = 0`; `k` larger than `n/2` (collapse to Stock II); only one profitable stretch; cooldown with a single day.

**Common mistakes**

- Updating `buy[t]` and `sell[t]` **ascending** in Stock IV, which lets a single day host both a buy and a sell (the classic bug). Iterate **descending** or keep yesterday's copies.
- Using `INT_MIN` in arithmetic without guarding (`INT_MIN + x` overflows). Either guard with `if (state != INT_MIN)` or use `-1e9` and keep prices small, or use `long long` with `LLONG_MIN/2`.
- Returning a "hold" state at the end when the problem requires finishing *not holding* (unlimited variant must return `cash`).
- Forgetting the transaction fee can be paid on **either** side; the convention must be applied consistently (here: on the sell).

**Variations**

Short selling allowed; multiple stocks; buy/sell with a fixed holding period; maximum profit with `k` transactions **and** a cooldown; "best time to buy and sell with cooldown" using a heap.

### P9 — LIS family (longest increasing subsequence and friends)

**What is the pattern?**

A subsequence of `arr` where every next element is **strictly larger** (or strictly smaller for LDS). The answer is the *length* of the longest such chain, or the maximum **sum** of such a chain (MSIS / max bitonic).

**When should I recognize it?**

- "Longest **increasing** subsequence" (and its decreasing twin).
- "Maximum sum increasing subsequence" → same DP, `max` instead of `max length`.
- "Longest **bitonic** subsequence" → `LIS ending at i` + `LDS starting at i`, minus 1.
- "Count the number of LIS" → DP that **accumulates counts**, not just maxima.
- "Reconstruct the LIS" → DP + parent pointers.

**Core intuition**

Define:

```text
dp[i] = length of the longest increasing subsequence that ENDS exactly at index i
dp[i] = 1 + max( dp[j] for all j < i with arr[j] < arr[i] )      (or 1 if no such j)
answer = max(dp[i])
```

> **Common Mistake** — the classic error is writing `dp[j] < dp[i] + 1` (comparing **lengths**) instead of `arr[j] < arr[i]` (comparing **values**). Always compare array elements, never DP values.

**Time / Space**

`O(n²)` time / `O(n)` space for the DP; `O(n log n)` time / `O(n)` space with `lower_bound`.

**Edge cases**

`n = 0` → `0`; all equal elements → strict LIS length is `1`, non-decreasing is `n`; already sorted → `n`; reverse sorted → `1`; duplicates in "count the LIS" (duplicates are *not* allowed to extend a strictly increasing chain).

**Common mistakes**

- Comparing DP values instead of array values (see above).
- Using `upper_bound` for a strict LIS.
- Reusing the same `cnt[i]` after overwriting `len[i]` in the counting variant — the two branches must be mutually exclusive.
- Returning `tails` as the subsequence in the reconstruction variant.
- Forgetting `-1` in the bitonic combination.

**Variations**

LDS with reversed comparison; maximum-sum increasing subsequence; longest increasing subsequence in a **matrix**; number of distinct LIS; LIS of `k` sorted arrays (merge + LIS); "Russian doll envelopes" (sort + LIS on a second key); LCIS (2D version).

### P10 — Partition DP ("split the array/string into groups")

**What is the pattern?**

The input is divided into contiguous pieces, and each piece is evaluated independently; the goal is to optimize something *across* the pieces. The DP index is the **position/prefix length**, and the transition tries the **last piece size**.

**When should I recognize it?**

- "Minimum sum of squares of a partition", "maximum sum where each group ≤ k".
- "**Palindrome** partitioning — minimum cuts".
- "Divide an array into two sets with minimum difference" (subset-sum in disguise).
- "Count partitions of a string" / "ways to split a string such that every piece is a dictionary word" (word break, `O(n²)` view).

**Core intuition**

> **Pattern** — "Cut a sequence into valid pieces" ⇒ state = *how far along I am*, transition = *where the last piece ends*.

```text
dp[i] = best answer for the prefix [0 .. i-1]
dp[i] = min/max over all valid last pieces [j .. i-1]  of ( dp[j] + cost(j, i-1) )
```

**Time / Space**

`O(n·k)` when the piece size is bounded by `k`; `O(n²)` in general (palindrome cuts); `O(n)` space with a single row.

**Edge cases**

Empty input → `0`; already fully valid; a single element; negative values (breaks the `break` optimization); no valid partition exists (return `-1` / `INT_MAX`, decide which).

**Common mistakes**

- Cutting greedily instead of DP ("as large as possible" is usually wrong).
- Off-by-one between the number of cuts and the number of pieces.
- Assuming the `break` in the inner loop is always valid.
- Naive `isPal` inside a double loop giving `O(n³)` — with an `O(n²)` palindrome table (or `O(n)` Manacher, for the strict case) you stay at `O(n²)`.

**Variations**

Word break (boolean partition); restore-the-string (2D + parent pointers); partition with exactly `k` groups; "split array into consecutive subarrays with equal sum"; N-Queens counted by partitioning.

### P11 — Interval / "split point" DP (matrix chain, burst balloons, parenthesization)

**What is the pattern?**

> **Pattern** — Whenever the cost of an object depends on **how its pieces are combined / split**, the state is an **interval** `dp[i][j]`, and the transition tries every **split point** `k` between `i` and `j`.

The signature: the *operation order* or *grouping* is unknown and affects the result.

**When should I recognize it?**

- "Minimum cost to **multiply** matrices" / "**parenthesize** an expression".
- "**Burst** balloons so that the maximum number of coins is collected" (the "last balloon popped" is the split point).
- "Boolean **parenthesization** of an expression".
- "Remove boxes", "strange game", "min cost to merge stones".

**Core intuition**

```text
dp[i][j] = best cost of handling the interval [i .. j]

dp[i][j] = min/max over k in [i .. j-1] of
              dp[i][k] + dp[k+1][j] + cost(k)            // merge / burst / cut style
           or dp[i][k] + dp[k+1][j] + product(i..j)       // matrix-chain style
```

> **Important** — The single most important decision here: **where is the last operation?**
> * Matrix chain: the **last multiplication** joins the product of `[i..k]` and `[k+1..j]`.
> * Burst balloons: the **last balloon popped** must be the *only* balloon left in `[i..j]`, so it must be one of the *original* indices in the interval; its neighbours are then `k` and `k+1` **after** all inner balloons are gone.
>
> Getting this backwards (thinking of the *first* element) is the standard mistake and produces a wrong recurrence.

**Iteration order**

Fill **by length** (shortest intervals first), or by decreasing `i` / increasing `j`. Never fill in an order that reads an unfilled cell.

```cpp
for (int len = 2; len <= n; ++len)
    for (int i = 0; i + len - 1 < n; ++i) {
        int j = i + len - 1;
        for (int k = i; k < j; ++k) {
            ...
        }
    }
```

**Time / Space**

`O(n³)` time, `O(n²)` space. Always ask: "is `O(n³)` acceptable?" — if `n ≈ 1000`, you need a different technique.

**Edge cases**

`n = 1` (no operator, answer is the value itself); `n = 0`; all operators the same; maximum values (`O(n³)` with `long long` — products of matrices can overflow `int` fast); single-element intervals must be initialized **before** the loops.

**Common mistakes**

- Base cases (`T[i][i]`, `F[i][i]`) not set before the length loop.
- Wrong iteration order → reading `0` from cells that are not yet computed.
- In matrix chain, forgetting the `0`-index diagonal matrix convention.
- Confusing the *first* and *last* operation in the recurrence.
- Using `int` for matrix products (use `long long`).

**Variations**

Burst balloons (min version), "remove boxes" (3D interval DP with a count), min cost to merge stones (`O(n²k)`), polygon triangulation, optimal parenthesization of a general associative expression, matrix chain with `O(n² log n)` via divide & conquer on the optimal split (Hu–Shing), "strange printer".

### P12 — 2D grid DP: histograms, maximal rectangles, largest squares

**What is the pattern?**

A 2D DP where each cell summarizes something about the **rectangle anchored at that cell**, letting you compute an area in constant time. The trick is choosing a per-row state that reduces the 2D problem to a **1D histogram** problem.

**When should I recognize it?**

- "**Maximal rectangle** of 1s in a binary matrix".
- "Largest square of 1s ending at `(i,j)`".
- "Largest rectangle in a histogram" (the 1D ancestor of this pattern).
- "Largest square submatrix with all 1s" / "count square submatrices".

**Core intuition**

Convert the matrix row by row into a **height array**: `h[j]` = the number of consecutive 1s in column `j` ending at the current row. Then the largest rectangle in the current sub-matrix is exactly the **largest rectangle in the histogram** `h`.

```text
matrix                     heights after row 3
1 0 1 1 1                  1 0 1 1 1
1 0 1 1 1          -->     2 0 2 2 2
1 1 1 1 1                  3 1 3 3 3
                     max-area-rectangle(h) = 6
```

**Time / Space**

Maximal rectangle: `O(m·n)` time, `O(n)` space. Largest square: `O(m·n)` time, `O(m·n)` or `O(n)` space.

**Edge cases**

Empty matrix; all `1`s (answer `m·n` / `n²`); all `0`s → `0`; single row / single column; non-binary (rectangles must be all-`>= threshold`).

**Common mistakes**

- Forgetting to reset `h[j]` to `0` on a `0` (that is the whole point of the height transform).
- Using `>` instead of `>=` in the monotonic stack (equal heights then produce *equal* areas but you lose the earliest boundary; `>=` keeps the stack strictly increasing and correct).
- Not flushing the stack at `j == n`.
- Forgetting the `dp[i][0] = 0` border row/column in the square DP.

**Variations**

Largest rectangle in a histogram (1D); count rectangles of all sizes; maximal square with a different value; "largest 1-rectangle with `at most k` zeros" (extra height budget); transform any max-rectangle problem into a histogram problem.

### P13 — Relation chains (largest divisible subset, longest string chain)

**What is the pattern?**

> **Pattern** — "Find the longest **chain** such that each element relates to the next" is **LIS with a custom comparator**. The order is not given by `arr[j] < arr[i]`; it is given by *any* predicate you like.

**When should I recognize it?**

- "Largest subset such that every element **divides** the next one" → sort + LIS, or `O(n²)` DP.
- "Longest **string chain** where `b` can be formed by adding one character to `a`" → sort by length + DP.
- "Maximum length of a sequence where each pair is **compatible**" (Russian dolls, envelopes, "handshakes").

**Core intuition**

Two equivalent routes:

```text
Route 1 (sort first):   sort by the key that makes "can follow" monotonic
                        then run plain LIS
Route 2 (no sort):      dp[i] = 1 + max( dp[j] : j < i AND pred(a[j], a[i]) )
```

> **Interview Tip** — Always say out loud: *"This is LIS with a custom relation."* It instantly tells the interviewer you know what you are doing, and it tells you exactly which template to grab.

**Time / Space**

`O(n²)` time / `O(n)` space (DP); `O(n log n)` with a hash-based predecessor search for strings. Sorting is `O(n log n)` and is dwarfed by the `O(n²)` DP unless you switch routes.

**Edge cases**

`n = 0` → `0`; single element → `1`; all elements equal (divisible subset → `n`); values including `0` (`x % 0` is undefined — guard or note the constraint usually says `≥ 1`); duplicate strings.

**Common mistakes**

- Forgetting to sort (for the divisible subset) — the `j < i` DP then misses chains entirely.
- Using the **original** array values after mutating them by reference.
- Substring construction with an out-of-range index or building `prev` from `substr(0, i) + substr(i+1)` and accidentally producing the same string.
- In the string-chain version, reading `best[prev]` **after** assigning `best[w] = cur` for the current word (self-dependency).

**Variations**

Longest increasing subsequence with a tolerance (`|a[i] - a[j]| ≤ k`); maximum length of a chain of intervals; course schedule with a longest-path objective; "maximum number of pairs" (bipartite matching — greedy fails, use matching).

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
