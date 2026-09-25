# 16 — Dynamic Programming — Complete Pattern-Based Notes

---

## 1. Topic Overview

**Dynamic Programming** solves problems with **overlapping subproblems** and **optimal substructure** by computing each distinct subproblem **once** and reusing the answer — turning exponential recursion into polynomial tables.

**What it is**
DP = recursion + memo of repeated states. You design a **state** (what a subproblem is), a **transition** (how states build on each other), and **base cases**, then evaluate them in an order where dependencies are ready.

**Why it is important**
- The bridge from "I can write recursion" to "I can solve counting/optimization problems efficiently" — Fibonacci `O(2^n)` → `O(n)`.
- One of the two highest-frequency interview categories (with graphs); carries entire problem families: knapsack, strings, stocks, LIS, intervals, grids.
- Teaches **state design** — the single most transferable modeling skill in DSA.

**Where it is used**
- Counting ways, minimizing cost, maximizing profit under constraints.
- Sequence problems: LCS, edit distance, LIS, palindromes.
- Partition/knapsack: subset sum, target sum, partition difference.
- Grid paths, matrix-chain / burst balloons / interval DP.
- Graphs: DAG shortest paths, DP on trees, bitmask TSP.
- Automata/stocks: finite-state transitions over positions.

**How it connects to other topics**
- §07 Recursion → memoization → tabulation → space optimization (the ladder).
- §04 Binary Search: LIS `O(n log n)`; §08 Bit: bitmask DP; §15 Graph: DAG DP, Floyd-Warshall *is* DP.
- §12 Greedy: greedy is DP when the choice property holds — know the boundary.

**Interview memory hook:** *State → base → transition → order → space-opt. Ask "what does dp[i] mean?" before writing any code.*

---

## 2. Fundamentals

### 2.1 The two properties

```text
1. Overlapping subproblems:   the same subproblem is reached many times
      fib(5) calls fib(3) twice; knapsack states repeat per item/target

2. Optimal substructure:      an optimal solution is built from
                              optimal solutions of smaller instances
      shortest path subpaths are shortest; best subset contains best sub-subset
```

Recursion alone handles (2); **memoization** exploits (1). DP = both.

### 2.2 The five-part design (memorize this order)

```text
1. STATE      what does one subproblem / dp entry mean?      dp[i] = ...?
2. BASE CASE  smallest states, defined without recursion     dp[0] = ...
3. TRANSITION how a state derives from smaller states        dp[i] = f(dp[..])
4. ORDER      iterate so dependencies are computed first     bottom-up direction
5. SPACE      which rows/columns are actually needed?        roll arrays
```

**The #1 interview question**: *"What does `dp[i]` (or `dp[i][j]`) represent?"* — if you can't answer crisply, don't code.

### 2.3 Memoization vs tabulation

| | Memoization (top-down) | Tabulation (bottom-up) |
|---|---|---|
| Start from | the actual question | smallest bases |
| Order | automatic (call order) | you choose (dependency-safe) |
| Unreachable states | skipped (often faster) | all computed |
| Code shape | recursion + cache | loops + array |
| Stack depth | `O(depth)` — can overflow | none |
| Space opt | harder | easier (rolling rows) |

### 2.4 Terminology

| Term | Meaning |
|---|---|
| **State** | A unique subproblem identified by parameters (index, remaining, flags…). |
| **Transition** | Formula relating a state to smaller states. |
| **Base case** | Terminal states with direct answers. |
| **Memo / tabulation** | Cache of computed states / filled table. |
| **State space** | Number of distinct states × transition cost = complexity. |
| **Space optimization** | Dropping dimensions not referenced by the next row. |
| **Pick / not-pick** | The universal 1D/2D choice pattern (subsequence family). |
| **Knapsack family** | Capacity-constrained selection: 0/1, unbounded, subset, partition. |

### 2.5 Complexity discipline

```text
DP complexity  =  (#states)  ×  (cost of one transition)

1D n:            O(n)        O(n) space    -> O(1) possible
2D n*m:          O(n·m)      O(n·m)        -> O(m) rolling
capacity W:      O(n·W)      O(W)          (pseudo-polynomial!)
subset masks:    O(2^n · n)
```

**Remember**: `O(n·W)` is pseudo-polynomial (exponential in the *bits* of W) — fine when `W ≤ 10^5`, deadly at `10^9`.

---

## 3. Core Concepts

### 3.1 The ladder: recursion → memoization → tabulation → space optimization

```text
Recursion (§07)
    |   add a cache keyed by parameters
    v
Memoization (top-down)         each state computed once
    |   replace recursion with loops, fill bases first
    v
Tabulation (bottom-up)         no stack, explicit order
    |   drop dimensions not read by the next row
    v
Space optimization             O(n·m) -> O(m) or O(1)
```

**Example — Fibonacci**

```cpp
// memo
vector<long long> dp(n + 1, -1);
function<long long(int)> f = [&](int i) -> long long {
    if (i <= 1) return i;
    if (dp[i] != -1) return dp[i];
    return dp[i] = f(i - 1) + f(i - 2);
};
// tabulation
vector<long long> dp(n + 1);
for (int i = 2; i <= n; i++) dp[i] = dp[i-1] + dp[i-2];
// space
long long a = 0, b = 1;               // dp[i-2], dp[i-1]
for (int i = 2; i <= n; i++) { long long c = a + b; a = b; b = c; }
```

**When to stop at memoization**: first instinct is recursive; state space is sparse; recursion depth is safe (`≤ 10^4`).

**When to tabulate**: need space optimization; depth too large; iterative clarity required.

---

### 3.2 How to identify a DP problem (recognition)

**Strong signals**
- "**Count** the number of ways…" / "number of distinct…" → DP (or combinatorics, but try DP).
- "**Minimize / maximize** cost-profit under constraints" → DP (unless greedy proof exists).
- Overlapping choices over a sequence with **memory of the past** (last taken index, remaining budget, matching progress).
- Constraints `n ≤ 1000…10^5` with polynomial expectation (not `2^n`, not `n!`).
- "Minimum/maximum number of **operations to transform A into B**" → edit-distance style.

**Not DP (recognize the negatives)**
| Smell | Instead |
|---|---|
| "Make locally best choice now" with a clean proof | Greedy (§12) |
| Everything depends only on current index with no memory | plain iteration |
| Subproblems **don't** repeat (all distinct) | divide & conquer (§02) |
| Need all orderings | backtracking (§07) |

**Test**: *"Can I define the answer for an input in terms of answers to strictly smaller inputs?"* If yes → optimal substructure → DP candidate.

---

### 3.3 How to derive the STATE

**Recipe**
1. Identify the **decision points** — at each step, what do I choose? (take/skip, direction, partition cut, hold/sell…)
2. Identify what **context** changes the value of future decisions — that context is the state.
3. Ask: *"If two recursive calls differ only in X, can they return different answers?"* If yes, X **must** be in the state.
4. Minimize the state — drop anything that doesn't change outcomes.

**Examples of state derivation**

| Problem | Decisions | Context needed | State |
|---|---|---|---|
| 0/1 knapsack | take item i or not | capacity left | `dp[i][w]` |
| Subset sum = K | take/skip | remaining target | `dp[i][k]` (bool) |
| Min path sum (grid) | right / down | current cell | `dp[r][c]` |
| LCS | match / skip i / skip j | progress in both strings | `dp[i][j]` |
| House robber | take / skip | previous taken? | `dp[i]` (reads `i-2`) |
| Buy/sell stocks | hold / not hold / cooldown | holding flag | `dp[i][hold]` (+ cooldown) |
| LIS ending here | extend from smaller | last index | `dp[i]` or patience array |
| Burst balloons | last balloon in range | open bounds | `dp[l][r]` |

**State-size warnings**
- Boolean flag matters (holding a stock?) → add a dimension (`dp[n][2]`).
- Count used so far matters (k partitions) → add count dimension (`dp[n][k]`).
- `dp[i][j]` must be sayable **in one sentence**: e.g. *"`dp[i][j]` = LCS length of `s[0..i)` and `t[0..j)`"*.

---

### 3.4 How to derive the TRANSITION

**Recipe**
1. Look at the **last decision** that formed the state ("what happened last?").
2. Enumerate the choices for that last decision; each gives a candidate smaller state.
3. Combine candidates with `max` (optimization), `+` (counting), or `||` (boolean feasibility).
4. Guard invalid choices (index out of range, capacity exceeded) — they contribute nothing (`-inf` / `0` / `false`).

**Examples**

```text
LCS:     last chars match?   dp[i-1][j-1] + 1
         else                max(dp[i-1][j], dp[i][j-1])

Edit:    match               dp[i-1][j-1]
         insert/delete/replace  1 + min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1])

0/1 knap: max(dp[i-1][w], dp[i-1][w-wt[i]] + val[i])   if w >= wt[i]
          dp[i-1][w]                                     else

Coin change (min coins):  dp[w] = 1 + min over coins dp[w-c]
Coin change (count ways): iterate coins in OUTER loop -> each combination counted once

Min path: dp[r][c] + min(dp[r-1][c], dp[r][c-1])

Stocks:  hold = max(hold_prev, cash_prev - price)   // buy from cash
         cash = max(cash_prev, hold_prev + price)   // sell from hold
```

**Counting vs maximizing**: counting **sums** over choices with iteration order enforcing uniqueness; maximizing takes `max`; boolean uses `||`.

---

### 3.5 Base cases & iteration order

**Base cases** are states that depend on nothing — initialize them **explicitly** before the loops:
- `dp[0] = 0` / `1` / `true` per semantics.
- Empty-input sentinels: `dp[0][j] = j` (edit distance: empty → j inserts), `dp[i][0] = 0` (LCS with empty = 0), grid first cell = its value.

**Order rule**: iterate so every state you **read** was already written.
- 1D reading `dp[i - wt]` (smaller index) → unbounded: `w` **ascending**; 0/1 (reads previous row) → `w` **descending**.
- 2D reading `i-1`, `j-1` → `i`, `j` ascending safe.
- MCM `dp[l][r]` reads **shorter intervals** → iterate by **length**.
- Counting combinations: **items outer, capacity inner** (or the reverse for permutations) — order decides what's counted.

---

### 3.6 Space optimization

**When possible**: transitions read only a constant number of recent rows/columns.
- `dp[i][j]` from `dp[i-1][*]`, `dp[i][*]` → **two rows** (or one, with careful overwrite direction).
- `dp[i]` from `dp[i-1]`, `dp[i-2]` → two scalars (Fibonacci style).
- 0/1 knapsack 1D `O(W)` already optimized; unbounded uses ascending order on the same 1D.

**Why it matters**: `n·m = 10^8` ints = 400 MB → MLE; two rows ≈ 8 MB.

**Pitfall**: overwriting a cell still needed later — the 0/1-vs-unbounded loop direction is exactly this trap (§4 P3).

---

## 4. PATTERN LIBRARY

### P1 — Linear (1D) DP: take/skip with adjacency constraints

#### What is the pattern?
`dp[i]` = best answer for prefix `0..i`, transitioned from the previous one or two states.

#### When should I recognize it?
- "Climb stairs / frog jump / min cost climbing", "house robber I & II", "max sum of non-adjacent elements", "ninja training (days × 3 styles)", "delete and earn".

#### Core intuition
At position `i` you either **take** it (paying the "gap" cost — can't take `i-1`) or **skip** it (inherit `dp[i-1]`). Each state only needs a fixed window of history.

#### Generic algorithm
```text
dp[i] = best considering first i items
skip:  dp[i-1]
take:  value[i] + dp[i - gap]      (gap = 1 for non-adjacent, 0/1 elsewhere)
dp[i] = combine(skip, take)
```

#### C++ template (house robber)
```cpp
long long rob(const vector<int>& a) {
    long long prev2 = 0, prev1 = 0;             // dp[i-2], dp[i-1]
    for (int x : a) {
        long long cur = max(prev1, prev2 + x);  // skip or take
        prev2 = prev1; prev1 = cur;
    }
    return prev1;
}
// house robber II: run linear rob on [0..n-2] and [1..n-1], take max
```

#### Time / Space
`O(n)` time; `O(1)` space (two scalars) — rolling from `O(n)`.

#### Edge cases
`n = 0/1`; all zeros; negative values (careful: empty selection may be 0 vs "must pick"); circular variant (first & last conflict).

#### Common mistakes
Using `dp[i] = x` instead of `max(skip, take)`; circular case forgetting the two linear sub-runs; off-by-one in `i - gap`.

#### Variations
Frog jump (min of `|h[i]-h[i-1]|`, `|h[i]-h[i-2]|`); ninja training (state = *last style*, `dp[day][last]` → `O(1)` space with 3 vars); min cost climb (`dp[i] = cost[i] + min(dp[i-1], dp[i-2])`).

#### Practice mapping
- `02-Climbing-Stairs.cpp`, `03-Frog-Jump.cpp`, `04-Frog-Jump-K.cpp`, `05-Max-Sum-Non-Adjacent.cpp`, `06-House-Robber.cpp`, `07-House-Robber-II.cpp`, `08-Ninja-Training.cpp`

---

### P2 — Grid DP (paths, obstacles, minima, falling)

#### What is the pattern?
`dp[r][c]` = best/ways to reach cell `(r,c)`; each cell aggregates from allowed predecessors (right/down, or the row above).

#### When should I recognize it?
- "Unique paths", "unique paths with obstacles", "minimum path sum", "triangle min path", "minimum falling path sum", "cherry pickup II (two agents)", "maximal square (histogram heights)".

#### Core intuition
Only moves *toward the target* matter → DAG of cells → DP over top-left → bottom-right order; ways sum, minima take min.

#### Generic algorithm
```text
dp[0][0] = base
first row/col:  only reachable from one direction (or blocked)
dp[r][c] = combine(dp[predecessors]) + cost(r,c)
answer = dp[R-1][C-1]  (or max over last row)
```

#### C++ template (min path sum)
```cpp
int minPathSum(vector<vector<int>>& g) {
    int R = g.size(), C = g[0].size();
    vector<vector<int>> dp(R, vector<int>(C, 0));
    dp[0][0] = g[0][0];
    for (int c = 1; c < C; c++) dp[0][c] = dp[0][c-1] + g[0][c];
    for (int r = 1; r < R; r++) dp[r][0] = dp[r-1][0] + g[r][0];
    for (int r = 1; r < R; r++)
        for (int c = 1; c < C; c++)
            dp[r][c] = g[r][c] + min(dp[r-1][c], dp[r][c-1]);
    return dp[R-1][C-1];
}
```

#### Time / Space
`O(R·C)` time and space → `O(C)` with rolling rows.

#### Edge cases
1×1 grid; blocked cells (obstacles → 0 ways); unreachable (min = INF sentinel); negative values (min path needs careful init).

#### Common mistakes
Forgetting first-row/first-column initialization; obstacle cell should be `0` (ways) not `+1`; using `dp[r-1][c]` on `r=0` (guard or padded 1-row).

#### Variations
Triangle (index-based 1D from bottom up); cherry pickup (two walkers `dp[r1][r2]`, share row → `O(n²)` space); max path sum with *choices at each row* (ninja/unique paths III variants); maximal rectangle = histogram DP per row (§09 contribution + DP).

#### Practice mapping
- `09-Grid-Unique-Paths.cpp`, `10-Grid-Unique-Paths-II.cpp`, `11-Minimum-Path-Sum.cpp`, `12-Triangle.cpp`, `13-Min-Falling-Path-Sum.cpp`, `14-Cherry-Pickup-II.cpp`, `54-Maximal-Rectangle-DP.cpp`, `55-Count-Square-Submatrices.cpp`

---

### P3 — Knapsack family (0/1, subset sum, partition, target)

#### What is the pattern?
Choose items subject to a **capacity/target constraint**; `dp[i][w]` = best (or possible) using the first `i` items with capacity/target `w`.

#### When should I recognize it?
- "Subset with sum K exists?", "partition array into two equal sums", "minimum subset sum difference", "count subsets with sum K", "target sum with +/−", "0/1 knapsack maximize value", "last stone weight / partition to min difference".

#### Core intuition
Every item: **skip** (inherit previous row) or **take** (jump to `w − weight[i]`). The capacity dimension is what makes choices interact — that's the DP.

#### Generic algorithm
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

#### C++ template (0/1 knapsack, space-optimized)
```cpp
int knap01(vector<int>& wt, vector<int>& val, int W) {
    vector<int> dp(W + 1, 0);
    for (size_t i = 0; i < wt.size(); i++)
        for (int w = W; w >= wt[i]; w--)          // DESCENDING
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    return dp[W];
}
```

**Subset-sum as bool knapsack**

```cpp
vector<bool> dp(K + 1, false); dp[0] = true;
for (int x : a)
    for (int s = K; s >= x; s--)
        if (dp[s - x]) dp[s] = true;
```

#### Time / Space
`O(n·K)` time; `O(K)` space (1D) or `O(n·K)` (2D for reconstruction).

#### Edge cases
`K = 0` (empty subset — usually true); item > K (skip); zeros (careful counting); all items negative (max value = 0 unless must-pick); `K` huge (MLE — pseudo-polynomial!).

#### Common mistakes
Wrong loop direction (0/1 vs unbounded); forgetting `dp[0][0]`/`dp[0] = true` base; counting *combinations vs permutations* (outer loop order); using `int` for counts (mod).

#### Variations
**Partition equal**: `K = total/2` (odd total → false). **Min difference**: `K` = closest achievable to `total/2`. **Count subsets**: `dp[w] += dp[w - x]` (ascending, combinations order). **Target sum (±)**: count subsets with `s = (total + target)/2`. **Partition with difference d**: `s = (total + d)/2`.

#### Practice mapping
- `15-Subset-Sum-Equals-K.cpp`, `16-Partition-Equal-Subset-Sum.cpp`, `17-Partition-Set-Min-Difference.cpp`, `18-Count-Subsets-Sum-K.cpp`, `19-Count-Partitions-Given-Difference.cpp`, `20-Zero-One-Knapsack.cpp`, `23-Target-Sum.cpp`

---

### P4 — Unbounded knapsack & cutting (coins, rod, rod/cut variants)

#### What is the pattern?
Same as knapsack but items **can be reused** — recognized by "unlimited supply" (coins) or "cut a rod / buy any number".

#### When should I recognize it?
- "Coin change (min coins / count combinations)", "rod cutting maximize value", "perfect squares", "word break (dictionary reuse)".

#### Core intuition
Because item `i` may be reused, the transition may *stay on the same row* → iterate capacity **ascending** so `dp[w - c]` already includes using `i`.

#### Generic algorithm
```text
min coins:   dp[0]=0; dp[w] = min over coins (dp[w-c] + 1)   [INF if impossible]
count ways:  OUTER loop over coins, inner over w ascending   (combinations!)
rod:         dp[len] = max(price[i] + dp[len - len_i])
```

#### C++ template (coin change — minimum coins)
```cpp
int coinChange(vector<int>& coins, int amount) {
    const int INF = 1e9;
    vector<int> dp(amount + 1, INF); dp[0] = 0;
    for (int w = 1; w <= amount; w++)
        for (int c : coins)
            if (w >= c && dp[w - c] + 1 < dp[w]) dp[w] = dp[w - c] + 1;
    return dp[amount] >= INF ? -1 : dp[amount];
}
```

#### Time / Space
`O(amount · |coins|)` (or `O(n·W)` generally); `O(amount)` space.

#### Edge cases
Amount 0 (0 coins); impossible (`-1`); coin > amount; duplicate coins (dedup for counting); count-ways overflow (mod).

#### Common mistakes
Loop direction (permutations vs combinations for counting); leaving `INF + 1` overflowing into valid range (use a large sentinel and guard); rod cutting index base (`len` from 1).

#### Variations
Word break = boolean unbounded knapsack over dictionary *prefixes*; perfect squares (`dp[w] = 1 + min dp[w - i²]`); minimum insertions to reach word (forward DP).

#### Practice mapping
- `21-Minimum-Coins.cpp`, `22-Coin-Change-II.cpp`, `24-Rod-Cutting.cpp`, `25-Unbounded-Knapsack.cpp`

---

### P5 — 2D linear DP (triangle, max-path, multi-way games)

#### What is the pattern?
The same 1D take/skip logic, but **two or more previous states** are needed, so the state is written as a table `dp[i][j]`.

#### When should I recognize it?
- "Maximum path from top to bottom **moving left/right/down**" (no down-up constraint).
- "Path from `(0,0)` to `(r-1,c-1)` picking up cells **except ends**" (cherry pickup).
- "Choose an element from **each row**, maximizing the sum" (triangle).
- "Delete and earn" style variants with two quantities tracking together.

#### Core intuition
> **Remember** — 1D with *one* previous state → scalars. 1D with *two or more* previous states → table. The moment you need `dp[i-1]` **and** `dp[i-2]` **and** `dp[j-1]`, stop compressing and just make the 2D grid; it is easier to write and to debug.

#### Generic algorithm
```text
for i = 0 .. n-1:
    for j = 0 .. m-1:
        if start:      dp[i][j] = base(i, j)
        else:          dp[i][j] = value(i,j) + combine( dp[i-1][j-1], dp[i-1][j], dp[i][j-1] )
answer = dp[n-1][m-1]
```

#### C++ template (max falling path — moves ↓, ↘, ↙)
```cpp
int maxFallingPath(vector<vector<int>>& dp) {          // dp reused as the table
    int n = dp.size(), m = dp[0].size();
    for (int i = 1; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int best = dp[i - 1][j];
            if (j > 0)          best = max(best, dp[i - 1][j - 1]);
            if (j + 1 < m)      best = max(best, dp[i - 1][j + 1]);
            dp[i][j] += best;
        }
    return *max_element(dp.back().begin(), dp.back().end());  // may end anywhere
}
```

#### C++ template (cherry pickup — two independent walkers)
```cpp
int cherryPickup(vector<vector<int>>& g) {
    int n = g.size();
    vector<vector<vector<int>>> dp(3, vector<vector<int>>(n, vector<int>(n, -1)));
    dp[0][0][0] = g[0][0][0];
    for (int k = 0; k < 3; ++k)
        for (int a = 0; a < n; ++a)
            for (int b = a; b < n; ++b) {                 // symmetry: a <= b
                if (dp[k][a][b] < 0) continue;
                if (a + 1 < n && b + 1 < n)
                    dp[k+1][a+1][b+1] = max(dp[k+1][a+1][b+1], dp[k][a][b] + g[k+1][a+1][b+1]);
                if (a + 1 < n)
                    dp[k+1][a+1][b]   = max(dp[k+1][a+1][b],   dp[k][a][b] + g[k+1][a+1][b]);
                if (b + 1 < n)
                    dp[k+1][a][b+1]   = max(dp[k+1][a][b+1],   dp[k][a][b] + g[k+1][a][b+1]);
            }
    return max({dp[2][n-1][n-1], dp[2][n-1][n-2], dp[2][n-2][n-1]});
}
```

#### Time / Space
`O(r·c)` time; `O(r·c)` space. Cherry pickup is `O(n³)` (three nested loops) with `O(n²)` space via 3 layers.

#### Edge cases
Falling path: answer is the **max of the last row**, not a corner. Cherry pickup: `n = 1`; the two cherries on the final row can both be collected (hence three candidate answers); symmetric pruning `a ≤ b`. Triangle: `n = 1`.

#### Common mistakes
- Returning `dp[n-1][m-1]` when the walk may end anywhere.
- Forgetting that the two cherry walkers are **independent** (each chooses left/right separately → 4 moves) and that they *can* land on the same cell.
- Reusing the input grid as the DP table and then reading the original values back for comparisons.

#### Variations
"Delete and earn" (`dp[c] = max(dp[c], c + dp[c - gap])`); "grid with exactly k moves"; "maximum sum path with jumps" (jump-game variants → 1D greedy/DP).

#### Practice mapping
- `12-Triangle.cpp`, `13-Min-Falling-Path-Sum.cpp`, `14-Cherry-Pickup-II.cpp`

---

### P6 — String DP I: the LCS family

#### What is the pattern?
Two strings (or a string and itself) form a **grid of prefix pairs**. `dp[i][j]` = the answer for the prefixes `s[0..i-1]` and `t[0..j-1]`. Almost every hard string-DP problem on the sheet is a thin disguise of LCS or of a *substring* variant of it.

#### When should I recognize it?
| Clue in the statement | Pattern |
|---|---|
| "longest sequence that appears in **both**" | LCS |
| "sequence in `s` that is also a **subsequence of `t`**, increasing" | LCIS |
| "longest string that is a sub-sequence of its **reverse**" | LPS = LCS(s, reverse(s)) |
| "shortest string **supersequence** of both" | derived from LCS length |
| "minimum insertions so `s` becomes a palindrome" | LCS(s, reverse(s)) derived |
| "min **insertions + deletions** to make `s` a subsequence of `t`" | LCS derived |
| "longest common **substring**" (contiguous!) | LCS with the *reset* rule |

#### Core intuition
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

#### Generic algorithm
```text
dp[i][0] = dp[0][j] = 0
for i = 1..n:
    for j = 1..m:
        if s[i-1] == t[j-1]:  dp[i][j] = dp[i-1][j-1] + 1
        else:                 dp[i][j] = max(dp[i-1][j], dp[i][j-1])
return dp[n][m]
```

#### C++ template (LCS)
```cpp
int lcs(const string& s, const string& t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            dp[i][j] = (s[i-1] == t[j-1]) ? dp[i-1][j-1] + 1
                                           : max(dp[i-1][j], dp[i][j-1]);
    return dp[n][m];
}
```

#### C++ template (reconstruct the LCS string)
```cpp
string printLCS(string s, string t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            dp[i][j] = (s[i-1] == t[j-1]) ? dp[i-1][j-1] + 1
                                           : max(dp[i-1][j], dp[i][j-1]);
    string ans; int i = n, j = m;
    while (i > 0 && j > 0) {                       // walk backwards
        if (s[i-1] == t[j-1]) { ans += s[i-1]; --i; --j; }
        else if (dp[i-1][j] > dp[i][j-1]) --i;     // follow the larger branch
        else                              --j;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
```

#### C++ template (longest common **substring**)
```cpp
int lcSubstring(const string& s, const string& t) {
    int n = s.size(), m = t.size(), best = 0;
    vector<int> dp(m + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int prevDiag = 0;                            // dp[i-1][j-1] before overwrite
        for (int j = 1; j <= m; ++j) {
            int tmp = dp[j];
            dp[j] = (s[i-1] == t[j-1]) ? prevDiag + 1 : 0;   // <-- reset to 0
            best = max(best, dp[j]);
            prevDiag = tmp;
        }
    }
    return best;
}
```

#### The LCS-derived family (no new algorithm needed)

| Problem | Formula from `L = LCS(s, t)` |
|---|---|
| Longest Palindromic Subsequence of `s` | `LCS(s, reverse(s))` |
| Min insertions to make `s` a palindrome | `n - LCS(s, reverse(s))` |
| Min insertions + deletions to make `s` a subseq of `t` | `n + m - 2·L` |
| Length of shortest common supersequence | `n + m - L` |
| Number of distinct common subsequences | `2D counting DP` over the same grid |

> **Remember** — *"min insertions to make palindrome = n − LPS"* and *"SCS length = n + m − LCS"*. These two are asked constantly; recognizing the LCS grid underneath saves an hour.

> **Why** `n − LPS`? Each LPS character already pairs up for free; every other character must be mirrored with a newly inserted one.

#### Time / Space
`O(n·m)` time; `O(n·m)` space, reducible to `O(min(n,m))` since the transition reads only the previous row and the current row's diagonal.

#### Edge cases
Either string empty → `0`; identical strings → `n`; disjoint alphabets → `0`; LPS of a single char → `1`; very long strings (`n·m` up to `10⁸`) → compress to 1D; multi-byte strings → operate on the correct unit (chars vs code points).

#### Common mistakes
- **Mixing substring and subsequence** (forgetting the `: 0` reset).
- Off-by-one confusion: DP indices represent **prefix lengths**, so you must access `s[i-1]`. Be consistent across the whole file.
- Using `>` vs `>=` inconsistently while backtracking — both yield a valid LCS, but pick one.
- Trying to reconstruct from a **1D** DP — reconstruction needs the full table.
- For LPS, forgetting that `reverse(s)` shares characters with `s`; it is still correct, but people wrongly assume it "double counts".

#### Variations
LCIS (longest common **increasing** subsequence, `O(n·m)`); LCS of 3 strings (`O(n·m·k)`); LCS with wildcards (`?`); building the actual shortest common supersequence *string*; "distinct common subsequences" (add a `char`-indexed 3D table).

#### Practice mapping
- `26-LCS.cpp`, `27-Print-LCS.cpp`, `28-Longest-Common-Substring.cpp`, `29-Longest-Palindromic-Subseq.cpp`, `30-Min-Insertions-Palindrome.cpp`, `31-Min-Insert-Delete.cpp`, `32-Shortest-Common-Supersequence.cpp`

---

### P7 — String DP II: edit distance & character choices

#### What is the pattern?
Still a prefix-pair grid, but instead of "longest", the state is a **cost to transform** one string into the other, and the recurrence enumerates the *operations* you may perform on the last character.

#### When should I recognize it?
- "Minimum number of **insert / delete / replace** operations to convert `s` into `t`" → Levenshtein distance.
- "Convert `s` into `t` where `*` is a wildcard" → same grid, restricted transitions.
- "Count **distinct subsequences** of a string" → same grid shape, but the two strings are `s` and `s`, and the operation is "skip or take a character".
- "Number of ways to **delete** characters so both strings become equal" → LCS-derived.

#### Core intuition
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

#### Generic algorithm (edit distance)
```text
dp[i][0] = i          // delete everything
dp[0][j] = j          // insert everything
for i = 1..n, j = 1..m:
    if s[i-1] == t[j-1]: dp[i][j] = dp[i-1][j-1]
    else:                 dp[i][j] = 1 + min(dp[i-1][j],    // delete
                                            dp[i][j-1],    // insert
                                            dp[i-1][j-1])   // replace
```

#### C++ template (edit distance)
```cpp
int editDistance(const string& s, const string& t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; ++i) dp[i][0] = i;
    for (int j = 0; j <= m; ++j) dp[0][j] = j;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            dp[i][j] = (s[i-1] == t[j-1]) ? dp[i-1][j-1]
                     : 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
    return dp[n][m];
}
```

#### C++ template (wildcard matching)
```cpp
bool isMatch(const string& s, const string& p) {
    int n = s.size(), m = p.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;
    for (int j = 1; j <= m; ++j)                    // pattern "*" can match empty
        if (p[j-1] == '*') dp[0][j] = dp[0][j-1];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            if (p[j-1] == '*')
                dp[i][j] = dp[i-1][j] || dp[i][j-1];  // empty  |  consume one char
            else if (p[j-1] == '?' || p[j-1] == s[i-1])
                dp[i][j] = dp[i-1][j-1];
        }
    return dp[n][m];
}
```

#### C++ template (distinct subsequences)
```cpp
int distinctSubseq(const string& s) {
    int n = s.size();
    vector<int> dp(n + 1, 1);
    vector<int> last(26, -1);                      // last index where char appeared
    for (int i = 1; i <= n; ++i) {
        int c = s[i-1] - 'a';
        dp[i] = 2 * dp[i-1];                       // take + skip
        if (last[c] != -1) dp[i] -= dp[last[c]];   // remove duplicates from earlier take
        last[c] = i;
    }
    return dp[n];
}
```
The subtraction is the key idea: if `s[i-1]` already appeared at position `last[c]`, every subsequence that *started* with that char has already been counted, so subtract those copies.

#### Time / Space
`O(n·m)` time, `O(n·m)` space (compressible to `O(min(n,m))` for edit distance / wildcard; distinct subsequences is `O(n)` time and space).

#### Edge cases
Empty string (`n = 0`) → distance to `t` is `m`; identical strings → `0`; pattern with leading/trailing `*`; consecutive `*` (harmless but can be collapsed); string of all identical characters (counting version → `n+1`); modulo overflow for counting variants.

#### Common mistakes
- Swapping insert and delete costs (matters when they differ, e.g. "insert only" or "delete only" variants).
- Forgetting that `*` needs **two** transitions (`dp[i-1][j]` and `dp[i][j-1]`) — one alone gives wrong answers on strings like `"adceb"` / `"*ab*"`.
- Not subtracting duplicates in the distinct-subsequence DP and over-counting (e.g. `"aaa"` → 8 instead of 4).
- Using `vector<vector<bool>>` and then taking references into it (proxy references) — use `char` or `int` if you need element access.

#### Variations
Edit distance with different operation costs; Levenshtein with swaps (Damerau); wildcard with regex classes (`[a-z]`); "min deletions to make both equal" (`n + m − 2·LCS`); count of distinct common subsequences (3D `dp[i][j][k]`); regex matching via backtracking/DP.

#### Practice mapping
- `33-Distinct-Subsequences.cpp`, `34-Edit-Distance.cpp`, `35-Wildcard-Matching.cpp`

---

### P8 — Stock DP (buy/sell with varying constraints)

#### What is the pattern?
A 1D DP over **days** where the state carries *what you are currently holding*. The set of "states" (how many transactions, whether you hold a stock, whether you are in cooldown) determines which variant you are looking at.

#### The five variants at a glance
| Variant | What the state must remember | Canonical answer |
|---|---|---|
| **I** — one transaction | min price seen so far | `max(price - minSoFar)` |
| **II** — unlimited transactions | nothing (greedy works) | sum of all positive deltas |
| **III** — at most 2 transactions | up to 4 running values | max of 4 states |
| **IV** — at most `k` transactions | 2 arrays of size `k+1` | `O(n·k)` |
| **Cooldown** — 1-day cooldown after selling | 3 states (hold, sold, rest) | max of 3 states |
| **Fee** — transaction fee | 2 states (hold, not-hold) | not-hold at the end |

#### Core intuition
> **Pattern** — When the constraint is *"how many transactions may I make"*, the state must encode that count. When the constraint is *"can I sell today?"*, the state must encode a small number of **named statuses**, and each day you transition between them.

#### Generic algorithm (hold / not-hold state machine)
```text
hold[i]     = max(hold[i-1], -price[i])          // keep holding, or buy today
notHold[i]  = max(notHold[i-1], hold[i-1] + price[i])   // stay out, or sell today
answer = max(hold[n-1], notHold[n-1])            // holding at the end is allowed
```

#### C++ template (Stock I — single transaction)
```cpp
int maxProfit(vector<int>& p) {
    int mn = INT_MAX, best = 0;
    for (int x : p) { mn = min(mn, x); best = max(best, x - mn); }
    return best;
}
```

#### C++ template (Stock II — unlimited)
```cpp
int maxProfit2(vector<int>& p) {
    int ans = 0;
    for (int i = 1; i < (int)p.size(); ++i) ans += max(0, p[i] - p[i-1]);
    return ans;
}
```
**Why this works** — on any rising stretch, buying at the bottom and selling at the top is at least as good as any sequence of smaller trades; the greedy *is* optimal here.

#### C++ template (Stock III — at most 2 transactions, 4 states)
```cpp
int maxProfit3(vector<int>& p) {
    int b1 = INT_MIN, s1 = 0, b2 = INT_MIN, s2 = 0;
    for (int x : p) {
        b1 = max(b1, -x);            // after 1st buy
        s1 = max(s1, b1 + x);        // after 1st sell
        b2 = max(b2, s1 - x);        // after 2nd buy
        s2 = max(s2, b2 + x);        // after 2nd sell
    }
    return s2;
}
```
Note the `max(0, ...)` idea: initializing sells to `0` allows "doing fewer than 2 transactions", which is exactly what "**at most** 2" means.

#### C++ template (Stock IV — at most k transactions)
```cpp
int maxProfit4(vector<int>& p, int k) {
    int n = p.size();
    if (n == 0 || k == 0) return 0;
    if (k >= n / 2) {                       // unlimited
        int ans = 0;
        for (int i = 1; i < n; ++i) ans += max(0, p[i] - p[i-1]);
        return ans;
    }
    vector<int> buy(k + 1, INT_MIN), sell(k + 1, 0);
    for (int x : p) {
        for (int t = k; t >= 1; --t) {       // descending so states stay from yesterday
            buy[t]  = max(buy[t],  sell[t-1] - x);
            sell[t] = max(sell[t], buy[t] + x);
        }
    }
    return sell[k];
}
```

#### C++ template (cooldown — cannot buy the day after selling)
```cpp
int maxProfitCooldown(vector<int>& p) {
    if (p.empty()) return 0;
    vector<int> hold(p.size()), sold(p.size()), rest(p.size());
    hold[0] = -p[0];
    sold[0] = INT_MIN;                      // sold *and* resting are distinct states
    rest[0] = 0;
    for (int i = 1; i < (int)p.size(); ++i) {
        hold[i] = max(hold[i-1], rest[i-1] - p[i]);   // buy only after a rest day
        sold[i] = hold[i-1] + p[i];                   // sell today
        rest[i] = max(rest[i-1], sold[i-1]);          // do nothing
    }
    return max(sold.back(), rest.back());             // holding at the end gives nothing
}
```
> **Common Mistake** — Merging `sold` and `rest` into one state. Cooldown exists *precisely because* those two states differ; collapsing them is the single most common error in this problem.

#### C++ template (transaction fee)
```cpp
int maxProfitFee(vector<int>& p, int fee) {
    if (p.empty()) return 0;
    int hold = -p[0], cash = 0;
    for (int i = 1; i < (int)p.size(); ++i) {
        int prevHold = hold;
        hold = max(hold, cash - p[i]);       // buy, paying the fee immediately
        cash = max(cash, prevHold + p[i] - fee);  // sell
    }
    return cash;
}
```

#### Time / Space
`O(n)` time for I/II/III/cooldown/fee; `O(n·k)` for IV; space `O(1)` (scalars or 3-state arrays) everywhere except IV's `O(k)` arrays.

#### Edge cases
`n = 0` or `n = 1` → `0`; strictly decreasing prices → `0`; `k = 0`; `k` larger than `n/2` (collapse to Stock II); only one profitable stretch; cooldown with a single day.

#### Common mistakes
- Updating `buy[t]` and `sell[t]` **ascending** in Stock IV, which lets a single day host both a buy and a sell (the classic bug). Iterate **descending** or keep yesterday's copies.
- Using `INT_MIN` in arithmetic without guarding (`INT_MIN + x` overflows). Either guard with `if (state != INT_MIN)` or use `-1e9` and keep prices small, or use `long long` with `LLONG_MIN/2`.
- Returning a "hold" state at the end when the problem requires finishing *not holding* (unlimited variant must return `cash`).
- Forgetting the transaction fee can be paid on **either** side; the convention must be applied consistently (here: on the sell).

#### Variations
Short selling allowed; multiple stocks; buy/sell with a fixed holding period; maximum profit with `k` transactions **and** a cooldown; "best time to buy and sell with cooldown" using a heap.

#### Practice mapping
- `36-Buy-Sell-Stock-I.cpp`, `37-Buy-Sell-Stock-II.cpp`, `38-Buy-Sell-Stock-III.cpp`, `39-Buy-Sell-Stock-IV.cpp`, `40-Buy-Sell-Stock-Cooldown.cpp`, `41-Buy-Sell-Stock-Fee.cpp`

---

### P9 — LIS family (longest increasing subsequence and friends)

#### What is the pattern?
A subsequence of `arr` where every next element is **strictly larger** (or strictly smaller for LDS). The answer is the *length* of the longest such chain, or the maximum **sum** of such a chain (MSIS / max bitonic).

#### When should I recognize it?
- "Longest **increasing** subsequence" (and its decreasing twin).
- "Maximum sum increasing subsequence" → same DP, `max` instead of `max length`.
- "Longest **bitonic** subsequence" → `LIS ending at i` + `LDS starting at i`, minus 1.
- "Count the number of LIS" → DP that **accumulates counts**, not just maxima.
- "Reconstruct the LIS" → DP + parent pointers.

#### Core intuition
Define:

```text
dp[i] = length of the longest increasing subsequence that ENDS exactly at index i
dp[i] = 1 + max( dp[j] for all j < i with arr[j] < arr[i] )      (or 1 if no such j)
answer = max(dp[i])
```

> **Common Mistake** — the classic error is writing `dp[j] < dp[i] + 1` (comparing **lengths**) instead of `arr[j] < arr[i]` (comparing **values**). Always compare array elements, never DP values.

#### C++ template (O(n²) DP)
```cpp
int lis(const vector<int>& a) {
    int n = a.size();
    vector<int> dp(n, 1);
    int best = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j)
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
        best = max(best, dp[i]);
    }
    return best;
}
```

#### C++ template (O(n log n) with patience sorting)
Maintain `tails[k]` = the **smallest possible tail value** of an increasing subsequence of length `k+1` found so far. `tails` is always sorted, so we can binary-search it.

```cpp
int lisFast(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);  // first >= x
        if (it == tails.end()) tails.push_back(x);            // extend
        else *it = x;                                          // improve that length
    }
    return tails.size();
}
```

> **Important** — `tails` is **not** an actual subsequence, only a bookkeeping array. If you need the real sequence, you must keep parent pointers (or filter the original array).

> **Remember** — `lower_bound` gives **strictly** increasing; `upper_bound` gives **non-decreasing**. For strict LIS use `lower_bound`; for "non-decreasing subsequence" use `upper_bound`.

#### C++ template (count the number of LIS)
```cpp
int countLIS(const vector<int>& a) {
    int n = a.size();
    vector<int> len(n, 1), cnt(n, 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j)
            if (a[j] < a[i] && len[j] + 1 > len[i]) {
                len[i] = len[j] + 1;
                cnt[i] = cnt[j];                 // only on a strict improvement
            } else if (a[j] < a[i] && len[j] + 1 == len[i])
                cnt[i] += cnt[j];                // equally long: add the ways
    }
    int longest = *max_element(len.begin(), len.end());
    int ways = 0;
    for (int i = 0; i < n; ++i) if (len[i] == longest) ways += cnt[i];
    return ways;
}
```

#### C++ template (longest bitonic subsequence)
```cpp
int longestBitonic(const vector<int>& a) {
    int n = a.size();
    vector<int> inc(n, 1), dec(n, 1);
    for (int i = 0; i < n; ++i)                  // increasing, left to right
        for (int j = 0; j < i; ++j)
            if (a[j] < a[i]) inc[i] = max(inc[i], inc[j] + 1);
    for (int i = n - 1; i >= 0; --i)             // decreasing, right to left
        for (int j = i + 1; j < n; ++j)
            if (a[j] < a[i]) dec[i] = max(dec[i], dec[j] + 1);
    int best = 0;
    for (int i = 0; i < n; ++i) best = max(best, inc[i] + dec[i] - 1);
    return best;
}
```
The peak is counted twice, hence `-1`.

#### Time / Space
`O(n²)` time / `O(n)` space for the DP; `O(n log n)` time / `O(n)` space with `lower_bound`.

#### Edge cases
`n = 0` → `0`; all equal elements → strict LIS length is `1`, non-decreasing is `n`; already sorted → `n`; reverse sorted → `1`; duplicates in "count the LIS" (duplicates are *not* allowed to extend a strictly increasing chain).

#### Common mistakes
- Comparing DP values instead of array values (see above).
- Using `upper_bound` for a strict LIS.
- Reusing the same `cnt[i]` after overwriting `len[i]` in the counting variant — the two branches must be mutually exclusive.
- Returning `tails` as the subsequence in the reconstruction variant.
- Forgetting `-1` in the bitonic combination.

#### Variations
LDS with reversed comparison; maximum-sum increasing subsequence; longest increasing subsequence in a **matrix**; number of distinct LIS; LIS of `k` sorted arrays (merge + LIS); "Russian doll envelopes" (sort + LIS on a second key); LCIS (2D version).

#### Practice mapping
- `42-Longest-Increasing-Subsequence.cpp`, `43-Print-LIS.cpp`, `46-Longest-Bitonic-Subsequence.cpp`, `47-Number-of-LIS.cpp`

---

### P10 — Partition DP ("split the array/string into groups")

#### What is the pattern?
The input is divided into contiguous pieces, and each piece is evaluated independently; the goal is to optimize something *across* the pieces. The DP index is the **position/prefix length**, and the transition tries the **last piece size**.

#### When should I recognize it?
- "Minimum sum of squares of a partition", "maximum sum where each group ≤ k".
- "**Palindrome** partitioning — minimum cuts".
- "Divide an array into two sets with minimum difference" (subset-sum in disguise).
- "Count partitions of a string" / "ways to split a string such that every piece is a dictionary word" (word break, `O(n²)` view).

#### Core intuition
> **Pattern** — "Cut a sequence into valid pieces" ⇒ state = *how far along I am*, transition = *where the last piece ends*.

```text
dp[i] = best answer for the prefix [0 .. i-1]
dp[i] = min/max over all valid last pieces [j .. i-1]  of ( dp[j] + cost(j, i-1) )
```

#### C++ template (partition array — max sum with each group ≤ k)
```cpp
int partitionArray(int k, vector<int>& a) {
    int n = a.size();
    const int NEG = -1e9;
    vector<int> dp(n + 1, NEG);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        int sum = 0;
        for (int j = i; j >= 1; --j) {          // last group is [j-1 .. i-1]
            sum += a[j-1];
            if (sum > k) break;                 // groups only grow: safe to stop
            if (dp[j-1] != NEG)
                dp[i] = max(dp[i], dp[j-1] + sum);
        }
    }
    return dp[n];
}
```
The `break` is safe **only** because the group sum is non-decreasing as `j` decreases — with negative numbers it would be wrong. This is a great interview talking point.

#### C++ template (minimum palindrome cuts)
```cpp
bool isPal(const string& s, int i, int j) {
    while (i < j) if (s[i++] != s[j--]) return false;
    return true;
}
int minCuts(const string& s) {
    int n = s.size();
    if (n <= 1) return 0;
    vector<int> dp(n, 0);
    for (int i = 1; i <= n; ++i) {
        if (isPal(s, 0, i - 1)) { dp[i-1] = 0; continue; }     // whole prefix is a palindrome
        dp[i-1] = INT_MAX;
        for (int j = 1; j < i; ++j)
            if (isPal(s, j, i - 1)) dp[i-1] = min(dp[i-1], dp[j-1] + 1);
    }
    return dp[n-1];                     // dp = cuts, pieces = cuts + 1
}
```
> **Common Mistake** — Returning the number of **pieces** when the question asks for **cuts** (or vice versa). Write the conversion on paper before coding.

#### Time / Space
`O(n·k)` when the piece size is bounded by `k`; `O(n²)` in general (palindrome cuts); `O(n)` space with a single row.

#### Edge cases
Empty input → `0`; already fully valid; a single element; negative values (breaks the `break` optimization); no valid partition exists (return `-1` / `INT_MAX`, decide which).

#### Common mistakes
- Cutting greedily instead of DP ("as large as possible" is usually wrong).
- Off-by-one between the number of cuts and the number of pieces.
- Assuming the `break` in the inner loop is always valid.
- Naive `isPal` inside a double loop giving `O(n³)` — with an `O(n²)` palindrome table (or `O(n)` Manacher, for the strict case) you stay at `O(n²)`.

#### Variations
Word break (boolean partition); restore-the-string (2D + parent pointers); partition with exactly `k` groups; "split array into consecutive subarrays with equal sum"; N-Queens counted by partitioning.

#### Practice mapping
- `52-Palindrome-Partitioning-II.cpp`, `53-Partition-Array-Max-Sum.cpp`

---

### P11 — Interval / "split point" DP (matrix chain, burst balloons, parenthesization)

#### What is the pattern?
> **Pattern** — Whenever the cost of an object depends on **how its pieces are combined / split**, the state is an **interval** `dp[i][j]`, and the transition tries every **split point** `k` between `i` and `j`.

The signature: the *operation order* or *grouping* is unknown and affects the result.

#### When should I recognize it?
- "Minimum cost to **multiply** matrices" / "**parenthesize** an expression".
- "**Burst** balloons so that the maximum number of coins is collected" (the "last balloon popped" is the split point).
- "Boolean **parenthesization** of an expression".
- "Remove boxes", "strange game", "min cost to merge stones".

#### Core intuition
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

#### Iteration order
Fill **by length** (shortest intervals first), or by decreasing `i` / increasing `j`. Never fill in an order that reads an unfilled cell.

```cpp
for (int len = 2; len <= n; ++len)
    for (int i = 0; i + len - 1 < n; ++i) {
        int j = i + len - 1;
        for (int k = i; k < j; ++k) { ... }
    }
```

#### C++ template (burst balloons)
```cpp
int burst(vector<vector<int>>& val) {
    int n = val.size();
    vector<vector<int>> val2(n + 2, vector<int>(n + 2, 0));      // 1-indexed, boundaries
    for (int i = 1; i <= n; ++i) val2[i][i+1] = val[i-1][i-1];  // padding balloons
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    for (int len = 1; len <= n; ++len)
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                int coins = val2[i][k] + val2[k+1][j] + val2[i][j];
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k+1][j] + coins);
                val2[i][j] = max(val2[i][j], val2[i][k] + val2[k+1][j]);
            }
        }
    return dp[1][n];
}
```
The `val2` table is the clever part: it stores the best *boundary* value for the interval, so the inner coins are always maximal.

#### C++ template (boolean parenthesization)
```cpp
int solve(string ops, vector<int>& values) {
    int n = values.size();
    bool T[20][20] = {}, F[20][20] = {};
    for (int i = 0; i < n; ++i) T[i][i] = F[i][i] = values[i];
    for (int len = 2; len <= n; ++len)
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                bool lv = T[i][k] ? T[k+1][j] : F[k+1][j];
                bool rv = T[i][k] ? F[k+1][j] : T[k+1][j];
                if (ops[k] == '&') { T[i][j] |= lv && rv; F[i][j] |= !lv || !rv; }
                else                { T[i][j] |= lv || rv; F[i][j] |= !lv && !rv; }
            }
        }
    return T[0][n-1];
}
```
> **Remember** — With `&`: True needs `T&T`, False needs anything with an `F`. With `|`: True needs anything with a `T`, False needs `F&F`. Deriving these truth tables is the whole problem.

#### Time / Space
`O(n³)` time, `O(n²)` space. Always ask: "is `O(n³)` acceptable?" — if `n ≈ 1000`, you need a different technique.

#### Edge cases
`n = 1` (no operator, answer is the value itself); `n = 0`; all operators the same; maximum values (`O(n³)` with `long long` — products of matrices can overflow `int` fast); single-element intervals must be initialized **before** the loops.

#### Common mistakes
- Base cases (`T[i][i]`, `F[i][i]`) not set before the length loop.
- Wrong iteration order → reading `0` from cells that are not yet computed.
- In matrix chain, forgetting the `0`-index diagonal matrix convention.
- Confusing the *first* and *last* operation in the recurrence.
- Using `int` for matrix products (use `long long`).

#### Variations
Burst balloons (min version), "remove boxes" (3D interval DP with a count), min cost to merge stones (`O(n²k)`), polygon triangulation, optimal parenthesization of a general associative expression, matrix chain with `O(n² log n)` via divide & conquer on the optimal split (Hu–Shing), "strange printer".

#### Practice mapping
- `48-MCM.cpp`, `49-Min-Cost-to-Cut-Stick.cpp`, `50-Burst-Balloons.cpp`, `51-Boolean-Parenthesization.cpp`

---

### P12 — 2D grid DP: histograms, maximal rectangles, largest squares

#### What is the pattern?
A 2D DP where each cell summarizes something about the **rectangle anchored at that cell**, letting you compute an area in constant time. The trick is choosing a per-row state that reduces the 2D problem to a **1D histogram** problem.

#### When should I recognize it?
- "**Maximal rectangle** of 1s in a binary matrix".
- "Largest square of 1s ending at `(i,j)`".
- "Largest rectangle in a histogram" (the 1D ancestor of this pattern).
- "Largest square submatrix with all 1s" / "count square submatrices".

#### Core intuition
Convert the matrix row by row into a **height array**: `h[j]` = the number of consecutive 1s in column `j` ending at the current row. Then the largest rectangle in the current sub-matrix is exactly the **largest rectangle in the histogram** `h`.

```text
matrix                     heights after row 3
1 0 1 1 1                  1 0 1 1 1
1 0 1 1 1          -->     2 0 2 2 2
1 1 1 1 1                  3 1 3 3 3
                     max-area-rectangle(h) = 6
```

#### C++ template (maximal rectangle in a binary matrix)
```cpp
int maximalRectangle(vector<vector<int>>& mat) {
    int m = mat.size(); if (m == 0) return 0;
    int n = mat[0].size(), ans = 0;
    vector<int> h(n, 0), st;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) h[j] = mat[i][j] ? h[j] + 1 : 0;
        st.clear();                                        // monotonic increasing stack
        for (int j = 0; j <= n; ++j) {                     // j == n flushes the stack
            while (!st.empty() && h[st.back()] >= h[j]) {
                int ht = h[st.back()]; st.pop_back();
                int left = st.empty() ? -1 : st.back();
                ans = max(ans, ht * (j - left - 1));
            }
            st.push_back(j);
        }
    }
    return ans;
}
```

#### C++ template (largest square of 1s ending at each cell)
```cpp
int largestSquare(vector<vector<char>>& a) {
    int m = a.size(); if (m == 0) return 0;
    int n = a[0].size(), best = 0;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (a[i-1][j-1] == '1') {
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                best = max(best, dp[i][j]);
            }
    return best;
}
```
> **Remember** — The three neighbours (`up`, `left`, `diagonal`) are not optional: the diagonal is what stops the square from "drifting" into a non-square shape. Remove it and the recurrence is wrong.

#### C++ template (count all square submatrices)
```cpp
int countSquares(vector<vector<int>>& a) {
    int m = a.size(); if (m == 0) return 0;
    int n = a[0].size(); long long ans = 0;
    vector<int> dp(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int diag = 0;
        for (int j = 1; j <= n; ++j) {
            int top = dp[j];
            if (a[i][j-1]) { dp[j] = 1 + min({dp[j], dp[j-1], diag}); ans += dp[j]; }
            else dp[j] = 0;
            diag = top;
        }
    }
    return ans;
}
```
**Why** `ans += dp[i][j]`: if the largest square ending at `(i,j)` has side `s`, then squares of side `1, 2, …, s` also end there — exactly `s` squares.

#### Time / Space
Maximal rectangle: `O(m·n)` time, `O(n)` space. Largest square: `O(m·n)` time, `O(m·n)` or `O(n)` space.

#### Edge cases
Empty matrix; all `1`s (answer `m·n` / `n²`); all `0`s → `0`; single row / single column; non-binary (rectangles must be all-`>= threshold`).

#### Common mistakes
- Forgetting to reset `h[j]` to `0` on a `0` (that is the whole point of the height transform).
- Using `>` instead of `>=` in the monotonic stack (equal heights then produce *equal* areas but you lose the earliest boundary; `>=` keeps the stack strictly increasing and correct).
- Not flushing the stack at `j == n`.
- Forgetting the `dp[i][0] = 0` border row/column in the square DP.

#### Variations
Largest rectangle in a histogram (1D); count rectangles of all sizes; maximal square with a different value; "largest 1-rectangle with `at most k` zeros" (extra height budget); transform any max-rectangle problem into a histogram problem.

#### Practice mapping
- `54-Maximal-Rectangle-DP.cpp`, `55-Count-Square-Submatrices.cpp`, `56-Largest-Rectangle-Done.cpp`

---

### P13 — Relation chains (largest divisible subset, longest string chain)

#### What is the pattern?
> **Pattern** — "Find the longest **chain** such that each element relates to the next" is **LIS with a custom comparator**. The order is not given by `arr[j] < arr[i]`; it is given by *any* predicate you like.

#### When should I recognize it?
- "Largest subset such that every element **divides** the next one" → sort + LIS, or `O(n²)` DP.
- "Longest **string chain** where `b` can be formed by adding one character to `a`" → sort by length + DP.
- "Maximum length of a sequence where each pair is **compatible**" (Russian dolls, envelopes, "handshakes").

#### Core intuition
Two equivalent routes:

```text
Route 1 (sort first):   sort by the key that makes "can follow" monotonic
                        then run plain LIS
Route 2 (no sort):      dp[i] = 1 + max( dp[j] : j < i AND pred(a[j], a[i]) )
```

> **Interview Tip** — Always say out loud: *"This is LIS with a custom relation."* It instantly tells the interviewer you know what you are doing, and it tells you exactly which template to grab.

#### C++ template (largest divisible subset)
```cpp
int largestDivisibleSubset(vector<int>& a) {
    sort(a.begin(), a.end());
    int n = a.size();
    vector<int> dp(n, 1);
    int best = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j)
            if (a[i] % a[j] == 0) dp[i] = max(dp[i], dp[j] + 1);
        best = max(best, dp[i]);
    }
    return best;
}
```
> **Why the sort is safe** — the predicate `a[j] divides a[i]` implies `a[j] ≤ a[i]`, so any valid chain is already in sorted order. Sorting never destroys a valid chain.

#### C++ template (longest string chain)
```cpp
int longestStrChain(vector<string>& words) {
    sort(words.begin(), words.end(),
         [](const string& a, const string& b) { return a.size() < b.size(); });
    int n = words.size();
    unordered_map<string, int> best;                 // length of the best chain ending here
    int ans = 0;
    for (const string& w : words) {
        int cur = 1;
        for (int i = 0; i < (int)w.size(); ++i) {   // delete one char -> possible predecessor
            string prev = w.substr(0, i) + w.substr(i + 1);
            cur = max(cur, best[prev] + 1);          // note: [] inserts 0 for unseen keys
        }
        best[w] = cur;
        ans = max(ans, cur);
    }
    return ans;
}
```

#### Time / Space
`O(n²)` time / `O(n)` space (DP); `O(n log n)` with a hash-based predecessor search for strings. Sorting is `O(n log n)` and is dwarfed by the `O(n²)` DP unless you switch routes.

#### Edge cases
`n = 0` → `0`; single element → `1`; all elements equal (divisible subset → `n`); values including `0` (`x % 0` is undefined — guard or note the constraint usually says `≥ 1`); duplicate strings.

#### Common mistakes
- Forgetting to sort (for the divisible subset) — the `j < i` DP then misses chains entirely.
- Using the **original** array values after mutating them by reference.
- Substring construction with an out-of-range index or building `prev` from `substr(0, i) + substr(i+1)` and accidentally producing the same string.
- In the string-chain version, reading `best[prev]` **after** assigning `best[w] = cur` for the current word (self-dependency).

#### Variations
Longest increasing subsequence with a tolerance (`|a[i] - a[j]| ≤ k`); maximum length of a chain of intervals; course schedule with a longest-path objective; "maximum number of pairs" (bipartite matching — greedy fails, use matching).

#### Practice mapping
- `44-Largest-Divisible-Subset.cpp`, `45-Longest-String-Chain.cpp`

---

## 5. PATTERN RECOGNITION

> The goal of this section: given a fresh problem statement, decide *which template to open* **before** writing any code.

### 5.1 The master recognition table

| If the problem says... | Think about... | Template |
|---|---|---|
| "maximum/minimum such that you **cannot take adjacent** items" | 1D take/skip | P1 |
| "climb / jump `k` steps at a time" | 1D with a variable gap | P1 |
| "best of two choices **per day**", "choose exactly one activity" | 1D + one more dimension | P1 (Ninja) |
| "paths from top-left to bottom-right, **right/down only**" | Grid DP | P2 |
| "move **down, down-left, down-right**" | Grid DP (3 neighbours) | P2 |
| "obstacles / blocked cells" | Grid DP with `INF` | P2 |
| "sum of a **contiguous** subarray reaching exactly K" | 0/1 knapsack | P3 |
| "subset whose sum is K" / "can we make K?" | Subset-sum | P3 |
| "split into two groups with **equal/minimum-different** sum" | Subset-sum + complement | P3 |
| "assign `+`/`-` to reach a target" | Subset-sum reformulation | P3 |
| "min number of coins / rods / cuts" | Unbounded knapsack | P4 |
| "**exactly** K coins" (counting) | Unbounded knapsack | P4 |
| "choose an element from each row" | 2D linear DP | P5 |
| "longest sequence present in **both** strings" | LCS | P6 |
| "longest common **contiguous** piece" | LCSubstring | P6 |
| "make `s` a palindrome / supersequence" | LCS-derived | P6 |
| "min insert/delete/replace to convert" | Edit distance | P7 |
| "wildcard `*` / `?` matching" | Edit-distance-style grid | P7 |
| "count **distinct** subsequences" | 2D counting DP | P7 |
| "buy and sell, `k` times / with cooldown / with fee" | Stock DP | P8 |
| "longest **increasing** subsequence" | LIS (DP or `O(n log n)`) | P9 |
| "longest bitonic / increasing-with-sum" | LIS + LDS | P9 |
| "count the number of LIS" | LIS + counting | P9 |
| "split the string/array into valid **pieces**" | Partition DP | P10 |
| "minimum cuts / maximum sum of pieces" | Partition DP | P10 |
| "how should I **order/combine** these operations?" | Interval / split-point DP | P11 |
| "parenthesize the expression" | Interval DP | P11 |
| "largest rectangle/square in a matrix" | Histogram + monotonic stack | P12 |
| "longest chain where each relates to the next" | LIS with a custom predicate | P13 |

### 5.2 Five questions to ask yourself

1. **Is the answer a single value, a count, or a boolean?**
   Count → often needs modular arithmetic and careful de-duplication. Boolean → initialize the "impossible" state properly.
2. **Does the choice at index `i` depend on earlier choices in a *bounded* way?** (previous 1, previous 2, a whole row) → that bound is the DP's width.
3. **Is the input a sequence, a grid, two sequences, or an interval?**
   sequence → 1D; grid → 2D; two sequences → prefix-pair grid; interval → split point.
4. **Am I choosing to take or skip, to cut or not cut, to combine or split?**
   take/skip → P1; cut → P10; split → P11.
5. **Can I brute-force it, and what does the brute force look like?**
   If the brute force is exponential, count the *distinct sub-problems* — that count is your state space.

### 5.3 Quick state-design heuristic

```text
"The answer depends on WHICH items I am allowed to use from the prefix,
 and HOW MUCH of the previous item matters."

        how much history is needed?
                 |
     0  ------>  scalar  (rolling variables)
     1  ------>  1D dp[i]
     2+ ------->  2D dp[i][j]
     n  ------>  bitmask / 2^n  (then ask: is there structure?)
```

**Rule of thumb** — if the transition reads only `dp[i-1]`, use a scalar. If it reads `dp[i-1]` and `dp[i-2]`, still use scalars. The moment you add a *second independent axis* (a row, a second string, a count `k`), switch to a table without guilt.

### 5.4 DP vs Greedy vs Backtracking

| Signal | Choose |
|---|---|
| A locally best choice provably cannot hurt (exchange argument) | **Greedy** |
| Choices interact and the "best so far" must be remembered | **DP** |
| You must produce *all* solutions, or pruning is the only way to fit | **Backtracking** |
| "Count the number of ways" | **DP** (or backtracking + memoization) |
| Overlapping subproblems are obvious | **DP** |

> **Common Mistake** — Jumping to greedy because the problem *looks* like "take the best available". Before deciding, ask: "if I make this choice now, can a later choice ever make me want to undo it?" If yes → DP.

---

## 6. BRUTE → BETTER → OPTIMAL THINKING

The goal is not to memorize three solutions; it is to build the habit of **finding the repeated structure** that makes the better solution possible.

### 6.1 The general escalation

```text
Brute force          enumerate every possibility
   |                  "what is the simplest correct thing?"
   v
Better               remove obvious waste
   |                  - repeated computation  -> memoization
   |                  - scanning everything  -> hashing / prefix sums
   |                  - recomputing sub-answers -> bottom-up
   v
Optimal              exploit the structure
                      - rolling arrays        -> O(1) space
                      - monotonicity          -> O(n log n)
                      - greedy + exchange     -> O(n) or O(n log n)
                      - binary search on answer-> O(n log ans)
```

### 6.2 Case study A — Subset sum (target K)

| Stage | Idea | Complexity | Why it is not enough / enough |
|---|---|---|---|
| Brute | Enumerate all `2ⁿ` subsets, sum each | `O(2ⁿ · n)` | Blows up at `n = 20+` |
| Better (memo) | Recursive `(i, target)`, cache results | `O(n·K)` time/space | **Optimal under normal constraints**; `K` is the state space |
| Better (1D) | Bottom-up with one array | `O(n·K)` time, `O(K)` space | Same time, far less memory, no recursion depth issues |
| Optimal for huge `n` | If `n` is small and `K` huge → **meet in the middle** | `O(2ⁿᐟ²)` | Beats `O(n·K)` when `K` is astronomically large |

> **Key insight to say out loud** — the brute force is exponential in `n`; the DP is exponential in `K`. Pick whichever parameter is smaller. That sentence is the whole problem.

### 6.3 Case study B — Longest increasing subsequence

| Stage | Idea | Complexity |
|---|---|---|
| Brute | All `2ⁿ` subsequences, check increasing | `O(2ⁿ · n)` |
| Better | `O(n²)` DP: for each `i`, look back at all `j < i` | `O(n²)` |
| Optimal | Patience sorting with `lower_bound` over tails | `O(n log n)` |

**The observation that unlocks it** — for LIS we only ever need the *smallest tail* of a subsequence of each length. Everything else is dominated and can be discarded. Dominance is the key word: state `(length, tail)` — a larger tail is *never* better than a smaller one with the same length, so we keep only the minimum. That is what makes `tails` sorted and binary-searchable.

### 6.4 Case study C — Longest common subsequence

| Stage | Idea | Complexity |
|---|---|---|
| Brute | Enumerate subsequences of the shorter string, test membership | `O(2^min · n)` |
| Better | `O(n·m)` prefix-pair DP | `O(n·m)` |
| Optimized space | Keep only the previous row + a diagonal variable | `O(min(n,m))` space |

There is **no** known algorithm asymptotically better than `O(n·m)` in the general case (SETH-hardness), so `O(n·m)` *is* the optimal. Knowing when to stop optimizing is part of the skill.

### 6.5 Case study D — Coin change

| Stage | Idea | Complexity |
|---|---|---|
| Brute | Try every multiset of coins | exponential |
| Better (top-down) | `f(amount)` = `1 + min f(amount - c)` | `O(amount · |coins|)` |
| Better (bottom-up) | Fill the table once, ascending | same time, `O(amount)` space |
| Alternative | BFS over amounts (each coin = 1 edge) → shortest path | `O(amount · |coins|)` |

### 6.6 Case study E — Grid paths

| Stage | Idea | Complexity |
|---|---|---|
| Brute | Enumerate all `C(r+c, r)` paths and simulate | `O(C(r+c,r) · (r+c))` |
| Better | Count paths combinatorially (`C(r+c-2, r-1)`) | `O(min(r,c))` |
| With obstacles | Combinatorics **fails** → DP | `O(r·c)` |

> **Interview Tip** — Always mention the combinatorial shortcut *and* why it stops working. Obstacles, varying costs, and multiple entry points all destroy the closed form, and knowing the boundary of a formula is worth more than memorizing it.

### 6.7 What to say in an interview

```text
1. "Let me start with brute force to make sure I understand the problem."
2. "The brute force is O(...). It's too slow because ..."
3. "I notice that <sub-problem X> is computed many times with the same inputs."
4. "So I'll memoize on <state>, which brings it to O(...)."
5. "I only ever read the previous row, so I can compress this to O(...) space."
6. "This matches the constraints (<n, K>), so I'll stop here."
```

---

## 7. C++ / STL TOOLKIT

Only the tools that actually show up in DP solutions.

### 7.1 `vector` — the DP table

```cpp
vector<int> dp(n, 0);                 // 1D table, all zeros
vector<int> dp(n + 1, INT_MAX);       // 1D table, "unreachable" sentinel
vector<vector<int>> dp(n, vector<int>(m, 0));   // 2D table
vector<vector<long long>> dp(n, vector<long long>(m, LLONG_MAX));
```

| Point | Detail |
|---|---|
| What it does | Contiguous, resizable, random-access sequence |
| Time | `push_back` amortized `O(1)`; random access `O(1)`; **pre-sizing with `n` and using `dp[i] =` is faster than `push_back`** |
| Space | Exactly the size you ask for (plus capacity slack) |
| Use when | The state space is dense and bounded (classic DP) |

**Common mistake** — using `push_back` in a hot DP loop; for a `1e7 × 2` table it measurably matters. Use `resize` + index assignment.

### 7.2 Sentinels for "unreachable"

```cpp
const int INF = 1e9;
// max problems
vector<int> dp(n, -INF);
// min problems
vector<int> dp(n, INF);
// boolean problems
vector<char> dp(n, false);            // char beats vector<bool> for access speed
```

> **Important** — `INF + 1` is still `INF`-ish for `int`, but `INF - 1` silently becomes a *valid-looking* answer. When you add to a sentinel, **guard it**:
> ```cpp
> if (dp[j] != INF) dp[i] = min(dp[i], dp[j] + cost);
> ```
> Alternatively use `long long` and `LLONG_MAX / 2` so a single `+` can never overflow.

### 7.3 `lower_bound` / `upper_bound` (for the `O(n log n)` variants)

```cpp
auto it = lower_bound(tails.begin(), tails.end(), x);   // first element >= x
if (it == tails.end()) tails.push_back(x); else *it = x;

int pos = lower_bound(a.begin(), a.end(), k) - a.begin();   // index form
```

| Function | Finds | DP use |
|---|---|---|
| `lower_bound` | first `>= x` | strict LIS, first index where `dp >= x` |
| `upper_bound` | first `> x` | non-decreasing LIS, first index where `dp > x` |

**Complexity** — `O(log n)` per call. `it == end()` is a normal, comparable iterator, so the `push_back` branch is always safe.

### 7.4 1D array space compression (the diagonal trick)

When a 2D recurrence only reads `dp[i-1][j]`, `dp[i][j-1]`, and `dp[i-1][j-1]`, you can do it in one row **if** you save the old diagonal first:

```cpp
for (int i = 1; i <= n; ++i) {
    int diag = 0;                       // dp[i-1][0] is always 0
    for (int j = 1; j <= m; ++j) {
        int top = dp[j];                // save dp[i-1][j] before overwriting
        dp[j] = compute(top, dp[j-1], diag);
        diag = top;                     // becomes the next iteration's diagonal
    }
}
```

> **Common Mistake** — Forgetting `diag = top`. The bug produces a wrong answer on strings with repeated characters, which makes it look "almost right".

### 7.5 Rolling scalars (for P1/P8)

```cpp
long long prev2 = 0, prev1 = 0;
for (int x : a) {
    long long cur = max(prev1, prev2 + x);
    prev2 = prev1;
    prev1 = cur;
}
```
O(1) space, no array allocation, and impossible to get an index wrong.

### 7.6 `unordered_map` (for state that is not an index)

```cpp
unordered_map<string, int> dp;      // state = the string itself
dp[prev] + 1;                      // inserts 0 if absent — handy, but be aware
if (dp.count(key)) { ... }         // or use find() when absence matters
```

| Point | Detail |
|---|---|
| Average lookup | `O(1)` (worst case `O(n)` under adversarial collisions) |
| Reserve | `dp.reserve(1 << 20)` avoids rehash spikes |
| Common mistake | Modifying the map while iterating it over it |

### 7.7 `sort` with a custom comparator

```cpp
sort(words.begin(), words.end(),
     [](const string& a, const string& b) { return a.size() < b.size(); });

sort(v.begin(), v.end(), greater<int>());           // descending
sort(v.begin(), v.end(), [](int a, int b) { return a < b; });   // ascending
```

Used to **establish an order that makes a relation monotonic** before running LIS (see P13). The comparator must define a strict weak ordering — never use `<=` (that is UB).

### 7.8 Recursion helpers for memoization

```cpp
int solve(int i, int rem, vector<vector<int>>& memo) {
    if (i < 0 || rem == 0) return 0;                       // base cases first
    int& ans = memo[i][rem];
    if (ans != -1) return ans;                             // cache hit
    return ans = max(solve(i - 1, rem),
                     take(solve(i - 1, rem - cost[i])));
}
```
```cpp
vector<int> memo;                      // 1D version
int solve(int i, int rem) {
    if (i < 0 || rem == 0) return 0;
    int& ans = memo[i * (K + 1) + rem];   // flatten the 2D state into 1D
    if (ans != -1) return ans;
    return ans = ...;
}
```

| Point | Detail |
|---|---|
| What it does | Caches results of pure recursive functions |
| Time | Same as the state space `O(#states × transition cost)` |
| Space | `O(#states)` + `O(n)` call stack |
| Use when | You want the *recursive structure* to mirror the *definition* — best for tricky transitions |

### 7.9 Miscellaneous helpers

```cpp
const int MOD = 1e9 + 7;
dp[i] = (dp[i] + dp[j]) % MOD;                 // counting DP
int64_t total = 1LL * n * K;                   // avoid int overflow in cost estimates
max({a, b, c})                                 // initializer_list max
numeric_limits<int>::min() / 2                 // safe negative sentinel
accumulate(a.begin(), a.end(), 0);             // prefix totals
```

---

## 8. COMPLEXITY GUIDE

### 8.1 What makes a DP expensive

| Dimension | Cost driver | Example |
|---|---|---|
| Number of states | `∏ (state ranges)` | `(n+1) × (K+1)` for subset-sum |
| Branching per state | how many previous states are tried | `O(n)` inner loop in LIS DP |
| Space | size of the state space | `O(n·K)` memo table |

> **Rule** — `Time = O(#states × cost of one transition)`. Counting states correctly is 80% of complexity analysis for DP.

### 8.2 Reference table

| Pattern | States | Transition | Time | Space |
|---|---|---|---:|---:|
| 1D take/skip (P1) | `n` | `O(1)` | `O(n)` | `O(1)` |
| Grid paths (P2) | `r·c` | `O(1)` | `O(r·c)` | `O(r·c)` / `O(c)` |
| 0/1 knapsack (P3) | `n·W` | `O(1)` | `O(n·W)` | `O(W)` |
| Subset sum (P3) | `K` | `O(1)` | `O(n·K)` | `O(K)` |
| Unbounded knapsack (P4) | `W` | `O(C)` | `O(W·C)` | `O(W)` |
| 2D linear (P5) | `n·m` | `O(1)` | `O(n·m)` | `O(n·m)` |
| Cherry pickup (P5) | `n³` states | `O(1)` | `O(n³)` | `O(n²)` |
| LCS / LCSubstring (P6) | `n·m` | `O(1)` | `O(n·m)` | `O(min(n,m))` |
| Edit distance (P7) | `n·m` | `O(1)` | `O(n·m)` | `O(min(n,m))` |
| Distinct subsequences (P7) | `n` | `O(1)` | `O(n)` | `O(n)` / `O(1)` |
| Stock I / II (P8) | `n` | `O(1)` | `O(n)` | `O(1)` |
| Stock IV (P8) | `n·k` | `O(1)` | `O(n·k)` | `O(k)` |
| Cooldown / fee (P8) | `n·3` | `O(1)` | `O(n)` | `O(1)` |
| LIS DP (P9) | `n²` pairs | `O(1)` | `O(n²)` | `O(n)` |
| LIS fast (P9) | `n` | `log n` | `O(n log n)` | `O(n)` |
| Partition (P10) | `n·k` | `O(1)` | `O(n·k)` / `O(n²)` | `O(n)` |
| Interval / split (P11) | `n²` intervals | `O(n)` splits | `O(n³)` | `O(n²)` |
| Maximal rectangle (P12) | `m·n` | amortized `O(1)` | `O(m·n)` | `O(n)` |
| Largest square (P12) | `m·n` | `O(1)` | `O(m·n)` | `O(n)` |
| Relation chain (P13) | `n²` | `O(1)` | `O(n²)` | `O(n)` |

### 8.3 Choosing the approach under real constraints

| Constraints | Approach |
|---|---|
| `n ≤ 10⁵`, single sequence | `O(n)` or `O(n log n)` only |
| `n ≤ 10³`, two sequences | `O(n·m)` is fine |
| `n ≤ 500`, `K ≤ 10⁶` | `O(n·K)` = `5·10⁸` — too slow; look for bitset or combinatorial tricks |
| `n ≤ 20` | Bitmask DP is often better than `O(2ⁿ)` enumeration |
| `K` huge, `n ≤ 40` | Meet in the middle, `O(2ⁿᐟ²)` |
| `n ≤ 10⁵`, answer is small | Binary search on the answer (`O(n log ans)`) |

### 8.4 Practical performance notes

| Issue | Impact | Fix |
|---|---|---|
| `vector<vector<int>>` for a huge table | Cache misses, allocator overhead | Flatten to one `vector` and index `i * W + j` |
| `vector<bool>` | Proxy objects, very slow access | Use `vector<char>` |
| `push_back` in a hot loop | ~2× slower than indexed write | `resize` once, then assign |
| Recursion depth `n = 10⁵` | Stack overflow | Iterative bottom-up, or raise the stack |
| Counting without `% MOD` | Overflow after ~30 doublings | Apply `% MOD` inside the loop |

---

## 9. EDGE CASES

### 9.1 Universal DP edge cases

| Case | What happens | Handling |
|---|---|---|
| Empty input (`n = 0`) | `dp[0]` may not exist; answer is often `0` or "impossible" | Early `return` before any indexing |
| Single element | Base case *is* the answer | Test by hand |
| No valid solution | Sentinel leaks into the answer | Guard every addition; return `-1` explicitly |
| All values equal | Degenerate cases dominate | Verify the answer is `n` or `1` as expected |
| Negative values | "Is an empty selection allowed?" becomes ambiguous | Decide whether the answer may be `0` or must use ≥ 1 item |
| `n = 1` in interval DP | No `k` exists, so the split loop never runs | Initialize single-element intervals before the loop |
| Overflow | `n·K` or matrix products exceed `int` | Use `long long`; compute sizes as `1LL * n * K` |
| Maximum constraints | `O(n·K)` memory can exceed RAM | Flatten the table; compress rows; check `n*K*4` bytes |

### 9.2 Pattern-specific edge cases

| Pattern | Edge cases to test |
|---|---|
| P1 linear | `n = 0`; all-negative (can the answer be negative?); circular variant where first and last conflict |
| P2 grid | `1×1` grid; fully blocked (return `0`); all-open with `r = 1` or `c = 1`; start or end blocked |
| P3 subset sum | `target = 0`; target greater than the total sum; all elements `0`; one element equals the target |
| P4 unbounded | `amount = 0`; no coin ≤ amount; duplicate coins (dedupe); coin greater than amount |
| P5 2D linear | triangular vs rectangular input; walk may end anywhere (falling path) |
| P6 LCS | empty string; identical strings; disjoint alphabets; single character; odd/even palindrome length |
| P7 edit distance | empty `s`; empty `t`; identical; `*` only; leading `*`; counting overflow → `% MOD` |
| P8 stock | `n = 0`, `n = 1`; strictly decreasing; `k = 0`; `k ≥ n/2`; fee larger than any profit |
| P9 LIS | all equal (strict → `1`); fully sorted; reverse sorted; duplicates in "count the LIS" |
| P10 partition | already fully valid; no valid partition exists; `n = 1`; negative values (breaks the `break` shortcut) |
| P11 interval | `n = 1`; `n = 2`; the operator between two operands; matrix products needing `long long` |
| P12 rectangles | all `1`s; all `0`s; single row; single column; non-binary input |
| P13 chains | duplicates; `0` in the array (`x % 0` is UB); equal-length strings; empty word list |

> **Remember** — An empty input is the edge case that fails most often in contests. Write `if (n == 0) return 0;` before anything else, every single time.

---

## 10. COMMON MISTAKES

### 10.1 Conceptual mistakes

| Mistake | Why it is wrong | How to avoid it |
|---|---|---|
| Greedy where DP is required | The locally best choice can block a better global one | Ask: "can a later choice make me want to undo this one?" |
| Missing base case, or one that misses the empty sub-problem | Every recursive call eventually hits it | Write base cases **first**, before the recurrence |
| Wrong iteration order | The transition reads an unfilled cell | Derive the order from the *dependencies*, then write the loops |
| Confusing "cuts" with "pieces" | Off-by-one in the output | Write the conversion explicitly: `pieces = cuts + 1` |
| Treating a subsequence as a substring | The mismatch rule differs | Look for the words *contiguous* / *substring* in the statement |
| Comparing DP values instead of data values in LIS | Wrong predicate | The condition is `arr[j] < arr[i]`, never `dp[j] < dp[i]` |
| Thinking of the *first* rather than the *last* operation in interval DP | Wrong recurrence for MCM / burst balloons | Ask: "what is the last thing that happens to this interval?" |
| Not guarding the "impossible" sentinel | `INF − 1` looks like a valid answer | Guard before every addition, or use `LLONG_MAX / 2` |

### 10.2 Coding mistakes

| Mistake | Symptom | Fix |
|---|---|---|
| Off-by-one between "prefix length" and "last index" | Correct only on the sample | Pick one convention; prefer prefix lengths with `s[i-1]` |
| In-place update reading the value just written | Wrong answers with repeated elements | Save `top` / `prevDiag` before overwriting |
| Ascending update where descending is required (Stock IV) | Same day counted as buy *and* sell | Iterate `k` from high to low |
| `vector<bool>` for a hot DP row | Surprisingly slow and surprising semantics | Use `vector<char>` |
| `push_back` in the inner loop | TLE on large inputs | `resize` once, then index |
| Not handling `n = 0` | Crash or garbage output | Early return |
| `int` overflow in `n * K` or cost sums | WA at max constraints | `long long`; size math as `1LL * n * K` |
| Reusing the input array as the DP table | Reading already-mutated values in comparisons | Copy if needed: `vector<int> dp = grid;` |
| Forgetting `% MOD` in counting DPs | Silent overflow (UB) | Modulo at every accumulation |
| Mutating a container while iterating it | Iterator invalidation | Collect the keys first, then mutate |

### 10.3 Debugging checklist

```text
1. Print the table by hand for n = 1, 2, 3 and compare with your code.
2. Check the base row and base column explicitly.
3. Verify the iteration order against the transition's dependencies.
4. Feed the smallest failing input to a brute force and diff the tables.
5. Re-read the statement: is it "at most" or "exactly"?
```

---

## 11. IMPORTANT FORMULAS / RULES

### 11.1 Derived from LCS

| Formula | Statement |
|---|---|
| LPS | `LPS(s) = LCS(s, reverse(s))` |
| Min insertions to palindrome | `n − LCS(s, reverse(s))` |
| Edit distance | `n + m − 2 · LCS(s, t)` |
| Min ins + del to reach a subsequence | `n + m − 2 · LCS(s, t)` |
| Shortest common supersequence (length) | `n + m − LCS(s, t)` |

### 11.2 Derived from subset sum

| Formula | Statement |
|---|---|
| Min difference of two groups | Let `S = sum`; find the largest achievable `x ≤ S/2`; answer is `S − 2x` |
| Target sum with `+`/`−` signs | The `+` subset must sum to `(S + T) / 2`; requires `S + T` to be even |
| Partition into equal halves | Exists iff `S` is even **and** `S/2` is achievable |

### 11.3 Combinatorics

| Formula | Statement |
|---|---|
| Unique grid paths (no obstacles) | `C(r + c − 2, r − 1)` |
| Safe binomial computation | `C(n, k) = C(n, k−1) · (n − k + 1) / k`, with `long long` and a mod |
| Distinct increasing subsequences | Catalan numbers (for the strictly-increasing-pattern class) |

### 11.4 Recurrences worth memorizing

```text
Fibonacci         F(n) = F(n-1) + F(n-2),                 F(0)=0, F(1)=1
Climbing stairs   ways[i] = ways[i-1] + ways[i-2]
House robber      rob[i] = max( rob[i-1], a[i] + rob[i-2] )
Grid paths        dp[i][j] = dp[i-1][j] + dp[i][j-1]
LCS               dp[i][j] = dp[i-1][j-1] + 1                if s[i-1] == t[j-1]
                         = max(dp[i-1][j], dp[i][j-1])       otherwise
LCSubstring       dp[i][j] = dp[i-1][j-1] + 1  if match, else 0
Edit distance     dp[i][j] = dp[i-1][j-1]                    if match
                         = 1 + min(up, left, diag)           otherwise
Largest square    dp[i][j] = 1 + min(up, left, diag)         if cell == 1
LIS               dp[i]    = 1 + max{ dp[j] : j < i and a[j] < a[i] }
Interval / split  dp[i][j] = min_k ( dp[i][k] + dp[k+1][j] + cost )
```

### 11.5 Invariants to state in an interview

- **0/1 knapsack, descending loop**: after processing item `i`, `dp[w]` uses item `i` **at most once** — guaranteed because `w` decreases.
- **Unbounded knapsack, ascending loop**: ascending `w` lets the *same* item be reused within a single pass.
- **Prefix-sum property**: `dp[i]` summarizes `0 .. i−1`, so element `i−1` is the last one available.
- **Acyclicity**: every transition moves to a *strictly smaller* sub-problem, so memoization can never recurse infinitely.

> **Important** — The descending/ascending distinction between 0/1 and unbounded knapsack is the most testable detail in the whole knapsack family. Say it out loud.

---

## 12. REUSABLE TEMPLATES

Short, copy-paste-ready skeletons. Adapt names and types; keep the structure.

### 12.1 Skeleton — memoized (top-down) 2D DP
```cpp
#include <bits/stdc++.h>
using namespace std;

const int NEG = -1e9;

int solve(int i, int j, const vector<int>& a, vector<vector<int>>& memo) {
    if (i < 0 || j < 0) return 0;                    // base cases first
    int& ans = memo[i][j];
    if (ans != NEG) return ans;
    return ans = max(solve(i - 1, j, a, memo),
                     a[i] + solve(i - 1, j - 2, a, memo));
}
```

### 12.2 Skeleton — tabulated (bottom-up) 1D DP
```cpp
int solve(const vector<int>& a) {
    int n = a.size();
    if (n == 0) return 0;
    vector<int> dp(n, 0);
    for (int i = 1; i <= n; ++i)
        dp[i] = max(dp[i - 1], a[i - 1] + (i >= 2 ? dp[i - 2] : 0));
    return dp[n - 1];
}
```

### 12.3 Skeleton — 2D prefix-pair DP (strings)
```cpp
int solve(const string& s, const string& t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            dp[i][j] = transition(s, t, i, j, dp);
    return dp[n][m];
}
```

### 12.4 Skeleton — 0/1 knapsack
```cpp
int zeroOneKnapsack(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<int> dp(W + 1, 0);
    for (int i = 0; i < n; ++i)
        for (int w = W; w >= wt[i]; --w)          // DESCENDING = each item once
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    return dp[W];
}
```

### 12.5 Skeleton — unbounded knapsack
```cpp
int unboundedKnapsack(vector<int>& wt, vector<int>& val, int W) {
    int C = wt.size();
    vector<int> dp(W + 1, 0);
    for (int c = 0; c < C; ++c)
        for (int w = wt[c]; w <= W; ++w)         // ASCENDING = unlimited reuse
            dp[w] = max(dp[w], dp[w - wt[c]] + val[c]);
    return dp[W];
}
```

### 12.6 Skeleton — interval / split-point DP
```cpp
int solve(const vector<int>& a) {
    int n = a.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) dp[i][i] = base(i);        // base cases first
    for (int len = 2; len <= n; ++len)
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; ++k)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + cost(i, j, k));
        }
    return dp[0][n - 1];
}
```

### 12.7 Skeleton — grid DP
```cpp
int solve(vector<vector<int>>& g) {
    int r = g.size(), c = g[0].size();
    vector<vector<int>> dp(r, vector<int>(c, INT_MAX));
    dp[0][0] = g[0][0];
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j) {
            if (i > 0) dp[i][j] = min(dp[i][j], dp[i-1][j] + g[i][j]);
            if (j > 0) dp[i][j] = min(dp[i][j], dp[i][j-1] + g[i][j]);
        }
    return dp[r-1][c-1];
}
```

### 12.8 Skeleton — LIS (`O(n log n)`) with reconstruction
```cpp
vector<int> printLIS(const vector<int>& a) {
    vector<int> tails, tailIdx, prevIdx(a.size(), -1);
    for (int i = 0; i < (int)a.size(); ++i) {
        int pos = lower_bound(tails.begin(), tails.end(), a[i]) - tails.begin();
        if (pos > 0) prevIdx[i] = tailIdx[pos - 1];
        if (pos == (int)tails.size()) { tails.push_back(a[i]); tailIdx.push_back(i); }
        else { tails[pos] = a[i]; tailIdx[pos] = i; }
    }
    vector<int> ans;
    for (int i = tailIdx.back(); i != -1; i = prevIdx[i]) ans.push_back(a[i]);
    reverse(ans.begin(), ans.end());
    return ans;
}
```

### 12.9 Skeleton — counting DP with modulo
```cpp
int countWays(const vector<int>& a, int K) {
    const int MOD = 1000000007;
    int n = a.size();
    vector<int> dp(K + 1, 0);
    dp[0] = 1;
    for (int x : a)
        for (int w = K; w >= x; --w)
            dp[w] = (dp[w] + dp[w - x]) % MOD;
    return dp[K];
}
```

---

## 13. ADVANCED CONCEPTS

### 13.1 Divide and conquer optimization (for `O(n³)` → `O(n²)`)

**Prerequisite** — comfort with interval DP and the Monge / quadrangle inequality.

If the cost satisfies the **Monge property** (informally: "splitting earlier is never worse when the interval is further left"), the optimal split point `k(i, j)` is **monotone**:

```text
opt(i, j - 1) <= opt(i, j) <= opt(i + 1, j)
```

So instead of trying every `k`, you start the search where the previous interval's optimum was. This is used in matrix-chain multiplication (Hu–Shing) and in "min cost to cut sticks"-style problems.

### 13.2 Knapsack optimization

| Optimization | Idea | Applies when |
|---|---|---|
| Binary splitting | Split `c` identical items into `1, 2, 4, …` bundles | Unbounded knapsack, few distinct item types |
| Monotone deque | Sliding-window `max` over `dp[w - c·x] + x·val` | Concave (or convex) value functions |
| Lagrangian relaxation | Drop a constraint, add a penalty | Very large capacities |
| Meet in the middle | Enumerate halves and sort | Small `n`, huge `K` |

### 13.3 Bitmask DP

**Prerequisite** — brute force over `2ⁿ` subsets, then notice the answer for a subset depends only on the subset.

```text
Recursion      O(2^n)     recomputes shared prefixes
Bitmask DP     O(n·2^n)   one int per subset, O(1) per transition
```

```cpp
int total = 1 << n;
vector<int> dp(total, NEG);
dp[0] = 0;
for (int mask = 1; mask < total; ++mask) {
    int i = __builtin_ctz((unsigned)mask);          // lowest set bit
    dp[mask] = solve(dp[mask ^ (1 << i)], i);       // remove that element
}
```

> **Remember** — `mask ^ (1 << i)` clears bit `i`; `mask | (1 << i)` sets it; `__builtin_ctz(mask)` returns the index of the lowest set bit (undefined for `mask == 0`). The ascending order is valid because `mask ^ (1<<i) < mask` always.

### 13.4 Digit DP

**Prerequisite** — a plain DP over a string of digits, plus a bound.

State = `(position, tight, started)`, where `tight` means "the prefix still equals the bound's prefix" and `started` means "we are no longer skipping leading zeros". This turns "count numbers in `[1, N]` with property P" into `O(digits · 10)` states.

### 13.5 DP with monotonic structures

Some DPs are `O(n·k)` but a monotonic structure shaves a factor:

- **LIS in `O(n log n)`** — the simplest instance; `tails` is monotone by construction.
- **Sliding-window max DP** — a `deque` maintains the max over the last `k` DP values, turning `O(n·k)` into `O(n)`.
- **Merge sort** — reduces "count increasing pairs" from `O(n²)` to `O(n log n)` by counting cross-pairs during the merge.

### 13.6 Sparse / map-based DP

When the state space is huge but few states are ever **reachable**, a `map` beats an array:

```cpp
unordered_map<int, int> dp;                  // only reachable sums
dp[0] = 0;
for (int i = 0; i < n; ++i) {
    vector<int> keys;
    keys.reserve(dp.size());
    for (const auto& kv : dp) keys.push_back(kv.first);   // snapshot
    for (int key : keys)
        if (key + a[i] <= K)
            dp[key + a[i]] = max(dp[key + a[i]], dp[key] + 1);
}
```

> **Common Mistake** — Mutating the map while iterating over it. Snapshot the keys into a vector first.

### 13.7 Reconstructing the answer

To return the actual choices, add a **parent pointer** to the DP:

```cpp
// 2D case: walk backwards from the answer cell
while (i > 0) {
    if (dp[i][j] == dp[i-1][j]) --i;            // the transition was "skip"
    else { record_take(i); j -= gap; }          // the transition was "take"
}
```
For interval DP, record the best `k` in a separate `split[i][j]` table. For string DP, backtrack through the equality branch (see `printLCS`).

### 13.8 When *not* to use DP

| Situation | Use instead |
|---|---|
| The optimum decomposes into independent local choices | Greedy |
| The state is an arbitrary *set* | Bitmask / meet in the middle / hashing |
| Only membership of the answer matters, not its value | Two pointers, sliding window, hashing |
| A provably simpler pattern exists | Prefix sums, two pointers, monotonic stack |

> **Interview Tip** — Being able to say *"this looks like DP, but here is why a simpler `O(n)` technique suffices"* is a stronger signal than writing any DP at all.

---

## 14. CONNECTIONS BETWEEN PATTERNS

### 14.1 The master map

```text
                       Recursion
                           |
                   repeated work spotted
                           v
                       Memoization   <---- state = what you must remember
                           |
                 recursion depth is a problem
                           v
                       Tabulation
                           |
                 only the previous row is read
                           v
                    Space Optimization
```

### 14.2 DP ↔ other topics

| DP pattern | Connects to | Because |
|---|---|---|
| P1 linear | Greedy | Same structure; greedy is the DP with a provable collapse |
| P2 grid | Graph | A grid is a graph; shortest path with costs = grid DP |
| P3/P4 knapsack | Graph (BFS on states) | Each amount is a node; the DP is a topological relaxation |
| P6/P7 string | Trie, hashing | Tries accelerate "does this substring exist"; hashing accelerates equality |
| P8 stock | Greedy, sliding window | The unlimited variant collapses to a greedy sum; fee/cooldown do not |
| P9 LIS | Binary search, monotonic stack | `tails` + `lower_bound`; the stack form is the same dominance idea |
| P11 interval | Divide & conquer, recursion | Interval DP is a 2D recursion in disguise |
| P12 rectangles | Monotonic stack | Literally the histogram algorithm applied per row |
| P13 chains | Topological sort, LIS | Longest path in a DAG = LIS once you fix an order |

### 14.3 Two routes to the same answer

```text
Subset sum K     :  0/1 knapsack DP        O(n*K)
                    bitset DP             O(n*K / 64)      <- ~64x faster
                    meet in the middle    O(2^(n/2))

Shortest path    :  BFS                   O(V + E)
                    0-1 BFS                O(V + E)
                    Dijkstra               O((V + E) log V)
                    Bellman-Ford          O(V*E)

LIS              :  O(n^2) DP
                    O(n log n) tails + lower_bound
                    O(n log n) Fenwick tree over values
```

> **Remember** — Recognizing that a DP has an alternative formulation is a strength, not a detour. Mentioning the second route *after* presenting a working solution is exactly the right move.

### 14.4 How this topic connects to the rest of the sheet

```text
Recursion      -> gives DP its first expression
Arrays/Strings -> give DP its data
Sorting        -> the order that makes a relation monotonic (P13)
Binary Search  -> the O(n log n) upgrades (LIS) and search-on-answer
Greedy         -> the alternative you must rule out first
Graphs         -> DP on a DAG; the reason topological order works
Monotonic Stack-> the O(n) upgrade for many "previous greater/smaller" DPs
```

---

## 15. PROBLEM → PATTERN MAPPING

Every existing `.cpp` in this folder, grouped by the pattern it practices. No explanations here — see the pattern section above.

### P1 — Linear 1D (take/skip, jumps)
- `02-Climbing-Stairs.cpp`
- `03-Frog-Jump.cpp`
- `04-Frog-Jump-K.cpp`
- `05-Max-Sum-Non-Adjacent.cpp`
- `06-House-Robber.cpp`
- `07-House-Robber-II.cpp`
- `08-Ninja-Training.cpp`

### P2 — Grid DP
- `09-Grid-Unique-Paths.cpp`
- `10-Grid-Unique-Paths-II.cpp`
- `11-Minimum-Path-Sum.cpp`

### P5 — 2D linear DP
- `12-Triangle.cpp`
- `13-Min-Falling-Path-Sum.cpp`
- `14-Cherry-Pickup-II.cpp`

### P3 — Subset sum / 0-1 knapsack
- `15-Subset-Sum-Equals-K.cpp`
- `16-Partition-Equal-Subset-Sum.cpp`
- `17-Partition-Set-Min-Difference.cpp`
- `18-Count-Subsets-Sum-K.cpp`
- `19-Count-Partitions-Given-Difference.cpp`
- `20-Zero-One-Knapsack.cpp`
- `23-Target-Sum.cpp`

### P4 — Unbounded knapsack & cutting
- `21-Minimum-Coins.cpp`
- `22-Coin-Change-II.cpp`
- `24-Rod-Cutting.cpp`
- `25-Unbounded-Knapsack.cpp`

### P6 — LCS family
- `26-LCS.cpp`
- `27-Print-LCS.cpp`
- `28-Longest-Common-Substring.cpp`
- `29-Longest-Palindromic-Subseq.cpp`
- `30-Min-Insertions-Palindrome.cpp`
- `31-Min-Insert-Delete.cpp`
- `32-Shortest-Common-Supersequence.cpp`

### P7 — Edit distance & counting strings
- `33-Distinct-Subsequences.cpp`
- `34-Edit-Distance.cpp`
- `35-Wildcard-Matching.cpp`

### P8 — Stock DP
- `36-Buy-Sell-Stock-I.cpp`
- `37-Buy-Sell-Stock-II.cpp`
- `38-Buy-Sell-Stock-III.cpp`
- `39-Buy-Sell-Stock-IV.cpp`
- `40-Buy-Sell-Stock-Cooldown.cpp`
- `41-Buy-Sell-Stock-Fee.cpp`

### P9 — LIS family
- `42-Longest-Increasing-Subsequence.cpp`
- `43-Print-LIS.cpp`
- `46-Longest-Bitonic-Subsequence.cpp`
- `47-Number-of-LIS.cpp`

### P13 — Relation chains
- `44-Largest-Divisible-Subset.cpp`
- `45-Longest-String-Chain.cpp`

### P11 — Interval / split-point DP
- `48-MCM.cpp`
- `49-Min-Cost-to-Cut-Stick.cpp`
- `50-Burst-Balloons.cpp`
- `51-Boolean-Parenthesization.cpp`

### P10 — Partition DP
- `52-Palindrome-Partitioning-II.cpp`
- `53-Partition-Array-Max-Sum.cpp`

### P12 — Rectangles & squares
- `54-Maximal-Rectangle-DP.cpp`
- `55-Count-Square-Submatrices.cpp`
- `56-Largest-Rectangle-Done.cpp`

### Foundations
- `01-DP-Introduction.cpp`

---

## 16. QUICK REVISION SHEET

### 16.1 The five-part design (memorize in this order)

```text
1. STATE      what does dp[i][j] mean?     (one sentence, no "etc.")
2. TRANSITION how do I reach it?           (the recurrence)
3. BASE CASE  smallest sub-problem         (usually empty prefix / single element)
4. ORDER      which order fills the table  (derived from the dependencies)
5. ANSWER     which cell do I return?      (often dp[n], sometimes dp[n-1])
```

### 16.2 The four-step ladder

| Step | Use when | Recursion risk | Space |
|---|---|---|---|
| Recursion | the transition is hard to write iteratively | high | `O(stack)` |
| Memoization | you want the code to mirror the definition | high | `O(#states)` |
| Tabulation | recursion depth is a risk, or you want speed | none | `O(#states)` |
| Space-optimized | only the previous row is read | none | `O(width)` or `O(1)` |

### 16.3 Pattern recognition — the 13 signals

| Signal | Pattern |
|---|---|
| take or skip, cannot take adjacent | P1 |
| `k` steps at a time | P1 |
| right / down / down-right in a grid | P2 |
| sum equals `K`, or split into equal halves | P3 |
| unlimited use of items | P4 |
| choose one per row | P5 |
| common to both strings | P6 |
| insert / delete / replace cost | P7 |
| buy, sell, `k` times, cooldown, fee | P8 |
| increasing / bitonic subsequence | P9 |
| cut into valid pieces | P10 |
| how should I combine / order these | P11 |
| largest rectangle / square | P12 |
| chain with a custom relation | P13 |

### 16.4 Formula cheat sheet

```text
LPS(s)                       = LCS(s, reverse(s))
Min insertions to palindrome = n - LCS(s, reverse(s))
Edit distance                = n + m - 2 * LCS(s, t)
SCS length                   = n + m - LCS(s, t)
Grid paths (no obstacles)    = C(r + c - 2, r - 1)
Target-sum partition         = (+) subset sums to (S + T) / 2
Min group difference         = S - 2 * (best achievable <= S/2)
Bitonic length               = inc[i] + dec[i] - 1
Count of sub-sequences       = number of squares = dp[i][j]
```

### 16.5 Complexity cheat sheet

| Pattern | Time | Space |
|---|---:|---:|
| 1D take/skip | `O(n)` | `O(1)` |
| Grid | `O(r·c)` | `O(c)` |
| 0/1 knapsack | `O(n·W)` | `O(W)` |
| Unbounded knapsack | `O(W·C)` | `O(W)` |
| LCS / edit distance | `O(n·m)` | `O(min(n,m))` |
| Stock I–III, cooldown, fee | `O(n)` | `O(1)` |
| Stock IV | `O(n·k)` | `O(k)` |
| LIS | `O(n log n)` | `O(n)` |
| Partition | `O(n·k)` / `O(n²)` | `O(n)` |
| Interval / split | `O(n³)` | `O(n²)` |
| Maximal rectangle | `O(m·n)` | `O(n)` |

### 16.6 The mistakes that cost the most points

1. Wrong iteration order (reads an unfilled cell).
2. Missing `n == 0`.
3. Unguarded `INF` arithmetic.
4. Ascending instead of descending in 0/1 knapsack.
5. Stock IV updated ascending (same-day buy *and* sell).
6. Cooldown: merging the "sold" and "rest" states.
7. Substring vs subsequence confusion (the `: 0` reset).
8. `vector<bool>` / inner-loop `push_back` performance traps.
9. `int` overflow in `n * K`.
10. Cuts vs pieces off-by-one.

### 16.7 Decision rules

```text
Ask:  "Does the answer depend on what I chose earlier?"
        no  -> greedy / prefix sums
        yes -> continue

Ask:  "How much of the earlier choices matters?"
        a fixed small window  -> 1D DP
        a second dimension    -> 2D DP
        an arbitrary set      -> bitmask / hashing

Ask:  "Do the transitions always shrink the problem?"
        yes -> DP is safe (no infinite recursion)
        no  -> there may be a cycle; re-read the problem

Ask:  "Can I write the recursion and then memoize it?"
        yes -> start there; tabulate only if needed
```

### 16.8 Templates to remember verbatim

```cpp
// house robber (P1)
long long rob(const vector<int>& a) {
    long long p2 = 0, p1 = 0;
    for (int x : a) { long long c = max(p1, p2 + x); p2 = p1; p1 = c; }
    return p1;
}

// LCS (P6)
dp[i][j] = (s[i-1] == t[j-1]) ? dp[i-1][j-1] + 1 : max(dp[i-1][j], dp[i][j-1]);

// LIS O(n log n) (P9)
auto it = lower_bound(tails.begin(), tails.end(), x);
if (it == tails.end()) tails.push_back(x); else *it = x;

// 0/1 knapsack — DESCENDING (P3)
for (int w = W; w >= wt[i]; --w) dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);

// unbounded knapsack — ASCENDING (P4)
for (int w = wt[c]; w <= W; ++w) dp[w] = max(dp[w], dp[w - wt[c]] + val[c]);

// interval DP (P11)
for (int len = 2; len <= n; ++len)
    for (int i = 0; i + len - 1 < n; ++i) {
        int j = i + len - 1;
        for (int k = i; k < j; ++k)
            dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + cost);
    }
```

---

## 17. INTERVIEW CHECKLIST

### Concept
- [ ] I can explain DP in one sentence: *store the answer to a sub-problem so it is computed once*.
- [ ] I can name the two properties: **overlapping subproblems** and **optimal substructure**.
- [ ] I can explain why a greedy choice can be wrong when a DP is needed.

### State design
- [ ] I can state my state in a single precise sentence, with no "and other things".
- [ ] I can justify the dimensions of my state (why `i`, why `j`, why `k`).
- [ ] I know which single cell or scalar is the final answer.

### Transition
- [ ] I can derive the transition on paper before writing code.
- [ ] I checked that the transition only reads **strictly smaller** sub-problems.
- [ ] I chose the iteration order *from* the dependencies, not by habit.

### Implementation
- [ ] I can write the memoized version from memory.
- [ ] I can convert it to tabulation without changing its meaning.
- [ ] I can compress the space and explain which cells are still needed.
- [ ] I use `long long` where the values can be large.

### Correctness
- [ ] I can explain why the base cases are correct.
- [ ] I can argue that every valid solution is considered by the transition.
- [ ] I can argue that combining optimal sub-solutions gives the global optimum.

### Performance
- [ ] I computed the complexity from `#states × transition cost`.
- [ ] I checked that it fits the constraints.
- [ ] I avoided `vector<bool>` and inner-loop `push_back`.

### Edge cases
- [ ] Empty input, single element, and "no solution" are handled.
- [ ] I checked duplicates, negatives, and equal values.
- [ ] I checked overflow risk at maximum constraints.

### Communication
- [ ] I stated the brute force first, and said why it is too slow.
- [ ] I named the pattern I recognized (e.g. "this is LCS with a custom comparator").
- [ ] I explained the complexity trade-off, not just the final number.

