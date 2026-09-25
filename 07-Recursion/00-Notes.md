# 07 — Recursion and Backtracking — Complete Pattern-Based Notes

---

## 1. Topic Overview

**Recursion** solves a problem by calling the same function on a smaller instance; **backtracking** is recursion that *makes a choice, explores it, then undoes it* to explore the next choice.

**What it is**
Every recursive function has a **base case** (stop) and a **recursive case** (shrink the problem). Backtracking explores a *decision tree* exhaustively while pruning branches that cannot succeed.

**Why it is important**
- Recursion is the foundation of trees (§13), graphs (§15), divide & conquer (§02 merge/quick sort), and DP (§16 — memoization *is* recursion + cache).
- Backtracking is the canonical way to generate **subsets, permutations, combinations**, and to solve constraint-satisfaction boards (N-Queens, Sudoku, mazes).
- Interviewers test whether you can *draw the recursion tree* and *state the state that a subcall needs*.

**Where it is used**
- Enumeration: subsets, permutations, combination sums, k-th permutation.
- Board search: N-Queens, Sudoku, rat in a maze, word search.
- Partitioning: palindrome partitioning.
- Structural: stack reversal, power functions, parenthesis generation.

**How it connects to other topics**
- Recursion → **memoization** → **tabulation** → **space optimization** = the DP pipeline (§16).
- Recursion is the natural traversal for trees/graphs (DFS).
- Pruning + greedy (§12) often replaces exhaustive backtracking when a proof exists.

**Interview memory hook:** *Base case first. One choice per call. Undo after returning. Sort + skip duplicates. Validate before recursing.*

---

## 2. Fundamentals

### 2.1 Anatomy of a recursive function

```cpp
void f(state) {
    if (baseCase) { record/return; }   // 1. STOP condition — check FIRST
    for (choice in choices) {
        make(choice);                  // 2. choose
        f(smallerState);               // 3. explore
        undo(choice);                  // 4. un-choose (backtrack)
    }
}
```

### 2.2 The call stack

```text
f(3)
└─ f(2)
   └─ f(1)   <- base case returns
   f(2) continues after return
f(3) continues after return
```

- Each call allocates a stack frame (parameters, locals, return address).
- Depth `D` → `O(D)` space; `D = O(n)` for index recursion → risk of stack overflow for `n ≳ 10^5`.

### 2.3 Recursion tree — count the work

```text
subsequences of [a, b, c]:

                /  \
           take a   skip a
          /    \      /   \
      take b  skip b ...  ...
       / \
     take c skip c

Leaves = 2^n -> time O(2^n * n) if each leaf costs O(n) to copy
```

**The number of leaves determines the complexity** — subsets are `O(2^n)` and permutations are `O(n!)`.

### 2.4 Parameter choices (what state does a call need?)

| Problem type | Typical state | Why |
|---|---|---|
| Subsequence / pick-not-pick | `(index)` | decisions proceed left→right |
| Combination sum | `(index, remaining target)` | target shrinks |
| Permutation (swap) | `(start)` | positions `0..start-1` fixed |
| Permutation (used array) | `(path, used[])` | order matters, no reuse |
| Board placement | `(row/cell)` + constraint sets | validity depends on history |
| Partition | `(start index)` + current part | cut points free |

---

## 3. Core Concepts

### 3.1 Pick / not-pick (subsequence pattern)

**Definition**  \nAt index `i`, branch into "include `a[i]`" and "exclude `a[i]`" — every level doubles the tree → `2^n` leaves = all subsequences.

**Intuition**  \nA subsequence is exactly a sequence of independent include/exclude decisions preserving order.

**Generic algorithm**
1. `f(i)`: if `i == n` → record `ds` / return base.
2. Take `a[i]`: push → `f(i+1)` → pop.
3. Not take: `f(i+1)`.

**Common mistakes**
- Forgetting `pop_back()` after returning → `ds` corrupted for the sibling branch.
- Pushing a reference into the answer — must store a **copy**.

---

### 3.2 Combination pattern (index never revisited)

**Definition**  \nChoose a multiset where **order doesn't matter**; recursion passes the *current index forward* so each combination is generated once.

**Why index-forward**  \nStarting the next branch at `i+1` (not `0`) prevents `[1,2]` and `[2,1]` duplicates structurally.

**Variations**
- **Combination Sum I**: elements reusable → recurse with same `i`, requires `a[i] <= target` pruning.
- **Combination Sum II**: duplicates in input → **sort first**, skip `a[i] == a[i-1]` at the same level.

---

### 3.3 Permutation pattern

**Definition**  \nAll orderings — each *position* gets a choice from the remaining elements.

**Two standard encodings**
1. **Swap-in-place**: `f(start)`: for `i ∈ [start, n)`: `swap(a[start], a[i])` → `f(start+1)` → `swap` back. `O(1)` per node.
2. **Used-array / path**: at each depth pick any unused element. Natural for **Permutations II** (sort + skip duplicates at the same depth).

**Complexity**  \n`O(n! · n)` — `n!` leaves, each path costs `O(n)`.

---

### 3.4 Pruning

**Definition**  \nStop exploring a branch the moment it *cannot* lead to a solution.

**Examples of signals**
- Current sum already exceeds target → cut.
- Placing a queen attacks an existing queen → cut.
- Remaining available elements can't fill the requirement → cut.

**Why it matters**  \nSame asymptotic worst case often, but far fewer nodes in practice — the difference between TLE and AC.

---

### 3.5 State restoration (undo)

**Definition**  \nAfter the recursive call returns, revert every modification so the *next sibling* sees the original state.

**Common mistake**  \nMissing `pop_back()` / missing `swap` back / not clearing a board cell → silently wrong answers (not crashes), the hardest bug type in backtracking.

---

### 3.6 Recursion → memoization bridge

```text
f(i) with no cache:   re-evaluates same (i) many times  -> exponential
f(i) with dp[i]:      each distinct state computed once -> O(states)
tabulation:           fill states bottom-up in dependency order
space optimization:   drop states not referenced by the next row
```

A recursive function qualifies for memoization when its **state is fully described by its parameters** (no hidden external state).

---

## 4. PATTERN LIBRARY

### P1 — Pick / Not-Pick (Subsequence Engine)

#### What is the pattern?
At each index branch into take/skip, undo after returning — enumerating all `2^n` subsequences.

#### When should I recognize it?
- "All subsequences", "count subsequences with property", "subset sum", "partition into subsequences", "target sum with ±".

#### Core intuition
Every element makes one independent binary decision → a perfect binary tree of height `n`.

#### General approach / Generic algorithm
1. Base: `i == n` → record/evaluate.
2. Take: push → recurse `i+1` → pop.
3. Skip: recurse `i+1`.
4. Undo restores state for the sibling branch.

#### C++ template
```cpp
void subseq(int i, vector<int>& a, vector<int>& ds) {
    if (i == (int)a.size()) { /* record ds */ return; }
    ds.push_back(a[i]); subseq(i + 1, a, ds);   // take
    ds.pop_back();                              // undo
    subseq(i + 1, a, ds);                       // skip
}
```

#### Time / Space
`O(2^n · n)` time (2^n leaves × O(n) path cost); `O(n)` recursion depth + output space.

#### Edge cases
Empty input (one empty subsequence); duplicates (may need sorting + level-skip); `n = 0`.

#### Common mistakes
Forgetting `pop_back`; storing the same vector reference; not copying when recording.

#### Variations
Target-constrained pick/not-pick → DP on (index, remaining) — §16.

#### Practice mapping
- `08-Print-All-Subsequences.cpp`, `09-Power-Set.cpp`, `10-Subsets-II.cpp`, `13-Subset-Sum-I.cpp`, `14-Subset-Sum-II-Exists.cpp`

---

### P2 — Combination Sum (index-forward + target)

#### What is the pattern?
Recurse on `(index, remaining target)`; index moves forward (no revisiting) or stays (reuse allowed).

#### When should I recognize it?
- "Combinations that sum to target", "combination sum I/II/III", "letter combinations of a phone number".

#### Core intuition
Index-forward kills order duplicates structurally; sorting + same-level skip kills value duplicates; `target - a[i]` shrinks the state.

#### General approach
1. Sort (needed for pruning + dedup).
2. At `i`: if `target == 0` → record; if `a[i] > target` → stop.
3. Skip duplicates at the same level: `if (i > start && a[i] == a[i-1]) continue;`.
4. Choose `a[i]`, recurse with `i+1` (or `i` if reuse).

#### C++ template
```cpp
void combSum(int i, vector<int>& a, int t, vector<int>& ds, vector<vector<int>>& out) {
    if (t == 0) { out.push_back(ds); return; }
    if (i == (int)a.size() || t < 0) return;
    for (int j = i; j < (int)a.size() && t - a[j] >= 0; j++) {
        if (j > i && a[j] == a[j-1]) continue;      // dedup at this level
        ds.push_back(a[j]);
        combSum(j + 1, a, t - a[j], ds, out);       // j (not j+1) => reuse
        ds.pop_back();
    }
}
```

#### Time / Space
Exponential in target/`n`; `O(target/min)` depth worst case.

#### Edge cases
No combination sums to target; `a[i] == 0` (infinite loop if reuse allowed!); single element == target.

#### Common mistakes
Not sorting before dedup; reusing index for Combination II; missing `t - a[j] >= 0` pruning.

#### Variations
Letter combinations (fixed digit map); combination sum III (exactly `k` numbers).

#### Practice mapping
- `11-Combination-Sum-I.cpp`, `12-Combination-Sum-II.cpp`, `15-Combination-Sum-III.cpp`, `16-Letter-Combinations.cpp`

---

### P3 — Permutation Generation (swap or used-array)

#### What is the pattern?
Fill positions left→right choosing among unused elements — `n!` orderings.

#### When should I recognize it?
- "All permutations", "next permutation", "k-th permutation", "permutations of a string/array (with duplicates)".

#### Core intuition
Position `start` picks any remaining element; swapping in place avoids an extra `used[]` while keeping `O(1)` node cost.

#### General approach (swap)
1. `f(start)`: if `start == n` → record.
2. For `i` from `start` to `n-1`: `swap(a[start], a[i])` → `f(start+1)` → `swap` back.
3. For duplicates: sort + skip equal `a[i]` at the same depth.

#### C++ template
```cpp
void perm(int start, vector<int>& a, vector<vector<int>>& out) {
    if (start == (int)a.size()) { out.push_back(a); return; }
    unordered_set<int> seen;                          // handles dup without sort
    for (int i = start; i < (int)a.size(); i++) {
        if (seen.count(a[i])) continue; seen.insert(a[i]);
        swap(a[start], a[i]); perm(start + 1, a, out);
        swap(a[start], a[i]);                         // restore
    }
}
```

#### Time / Space
`O(n! · n)` time; `O(n)` depth (swap) or `O(n! )` for storing all.

#### Edge cases
`n = 1`; all elements identical (only 1 unique permutation); empty input.

#### Common mistakes
Forgetting to swap back; dedup with `seen` not reset per level; generating duplicates in Permutations II.

#### Variations
Used-array encoding (needed for path-based constraints); `k`-th permutation via factorial number system.

#### Practice mapping
- `23-Permutations.cpp`, `24-Permutations-II.cpp`, `25-Kth-Permutation.cpp`, `06-Generate-All-Binary-Strings.cpp`

---

### P4 — Board Placement with Validity Check

#### What is the pattern?
Place one item per row/positional slot; before recursing, verify the placement against constraints maintained in sets/maps.

#### When should I recognize it?
- N-Queens, Sudoku solver, rat in a maze, word search, m-coloring, knight tour.

#### Core intuition
Constraints are *local to what you already placed* → maintain incremental structures (used columns, diagonal ids, board grid) and check in `O(1)` before recursing.

#### General approach
1. At row/position `i`, try each candidate `j`.
2. Check validity against stored state (e.g. `col[j]`, `diag1[i-j]`, `diag2[i+j]`).
3. Mark state → recurse → **unmark** (backtrack).
4. On reaching the end row → record solution.

#### C++ template
```cpp
void queens(int r, vector<int>& place, vector<bool>& col,
            vector<bool>& d1, vector<bool>& d2, int n) {
    if (r == n) { /* record place */ return; }
    for (int c = 0; c < n; c++) {
        if (col[c] || d1[r - c + n] || d2[r + c]) continue;
        col[c] = d1[r - c + n] = d2[r + c] = true;
        place[r] = c;
        queens(r + 1, place, col, d1, d2, n);
        col[c] = d1[r - c + n] = d2[r + c] = false;   // undo
    }
}
```

#### Time / Space
N-Queens `O(n!)` naive (pruned heavily); Sudoku `O(9^empty)`; word search `O(mn · 4^L)`.

#### Edge cases
No valid placement (return empty); single cell; already-filled constraints (Sudoku given cells); dead ends needing full undo.

#### Common mistakes
Diagonal index off-by-one (use offset `+ n`); not unmarking on return; processing board cells without a proper visitation marker (write/restore or separate `vis`).

#### Variations
Row-major vs cell-major iteration; constraint propagation (Sudoku naked singles); bitmask-parallel validity.

#### Practice mapping
- `19-N-Queens.cpp`, `20-Sudoku-Solver.cpp`, `22-Rat-in-a-Maze.cpp`, `18-Word-Search.cpp`, `21-M-Coloring.cpp`

---

### P5 — Partition Cuts (enumerate split points)

#### What is the pattern?
Recurse on `(start)` and try every valid end cut; the remaining suffix recurses from `end + 1`.

#### When should I recognize it?
- "Partition string so every part is a palindrome", "word break", "partition array for max sum", "decode ways".

#### Core intuition
The first cut's position is a choice; after fixing it, the rest of the problem is the same on a smaller suffix → recursion with one changing parameter (`start`).

#### General approach
1. From `start`, extend `end`.
2. If `s[start..end]` is valid (palindrome / in dictionary) → recurse `end + 1`.
3. If reaching `n` → record partition.

#### C++ template
```cpp
void parts(int start, string& s, vector<string>& cur, vector<vector<string>>& out) {
    if (start == (int)s.size()) { out.push_back(cur); return; }
    for (int end = start; end < (int)s.size(); end++) {
        if (!isPal(s, start, end)) continue;          // prune
        cur.push_back(s.substr(start, end - start + 1));
        parts(end + 1, s, cur, out);
        cur.pop_back();
    }
}
```

#### Time / Space
Exponential in `n` worst case; palindrome check `O(len)` → precompute with expand or DP for `O(n^2)` total.

#### Edge cases
No valid partition; whole string is one part; single characters always palindromic (worst case `2^(n-1)` partitions).

#### Common mistakes
Forgetting `pop_back`; re-checking palindromes from scratch (precompute); off-by-one in `substr` length.

#### Variations
Minimize number of cuts (DP over cuts); word break (dictionary set lookup).

#### Practice mapping
- `17-Palindrome-Partitioning.cpp`, `52-Palindrome-Partitioning-II.cpp` (DP context in §16), `14-Subset-Sum-II-Exists.cpp`

---

### P6 — Mathematical Recursion (fast power, divide & conquer)

#### What is the pattern?
Halve the exponent/problem, combine results — `O(log n)` instead of `O(n)` multiplications.

#### When should I recognize it?
- "Compute `x^n`", "power without `pow`", "count good numbers", "matrix chain-style repeated squaring".

#### Core intuition
`x^n = (x^(n/2))²` if n even, `x·x^(n-1)` if odd → each step halves the exponent.

#### General approach
1. Base: `n == 0 → 1`.
2. `half = f(x, n/2)`.
3. Return `half · half` or `x · half · half`.
4. Handle negatives (`1/x^|n|`) and `INT_MIN` overflow (`long long`).

#### C++ template
```cpp
double myPow(double x, long long n) {
    if (n < 0) { x = 1 / x; n = -n; }
    double r = 1;
    while (n) { if (n & 1) r *= x; x *= x; n >>= 1; }
    return r;
}
```

#### Time / Space
`O(log n)` multiplications; recursion depth `O(log n)`.

#### Edge cases
`n = 0` (any `x → 1`), `x = 0/1`, negative `n`, `n = INT_MIN` (negation overflows int!).

#### Common mistakes
`(long long) n` before negating `INT_MIN`; missing modulo when the problem requires it; iterative vs recursive parity bugs.

#### Variations
Count good numbers (even/odd position parity with modulo); sort a stack recursively (insert-at-bottom).

#### Practice mapping
- `02-Pow-x-n.cpp`, `03-Count-Good-Numbers.cpp`, `04-Sort-a-Stack.cpp`, `05-Reverse-a-Stack.cpp`, `01-Recursive-Implementation-of-Atoi.cpp`

---

## 5. PATTERN RECOGNITION

| If the problem says... | Think about... |
|---|---|
| "all subsequences / subsets / pick or skip" | Pick/not-pick recursion (2^n tree) |
| "combinations summing to target" | Index-forward + target recursion |
| "all orderings / permutations" | Swap or used-array permutation |
| "each choice must be valid against placed ones" | Board placement + validity sets |
| "split into parts with a property" | Partition cuts recursion |
| "compute power / log-time numeric" | Fast exponentiation recursion |
| "generate parentheses / binary strings" | Choice-per-position recursion with validity |
| "count ways" or "min choices" with overlapping states | Backtracking first → memoize (§16) |
| "N-Queens / Sudoku / maze" | Constraint backtracking with undo |
| `n ≤ 15–20` and exponential allowed | Subsets/permutations enumeration |
| Exponential but states repeat | Recursion → memoization → DP |

**Decision rules**
1. Choices at each step + constraint? → backtracking skeleton.
2. Order irrelevant (combinations) vs relevant (permutations)? → index-forward vs swap/used.
3. Duplicates present? → **sort + skip at same level**.
4. Same state computed twice? → you have left recursion and entered DP territory.

---

## 6. BRUTE → BETTER → OPTIMAL THINKING

### Subsets / combinations
- **Brute** — generate all index masks, build each subset from scratch: `O(2^n · n)` with heavy copying.
- **Better** — recursive pick/not-pick sharing prefixes: same asymptotics but **one path buffer** with push/pop — orders of magnitude faster in practice.
- **Optimal** (for enumeration) — you cannot beat `2^n` output size; the optimal is *output-sensitive*: `O(2^n)` nodes, `O(n)` per leaf only when recorded. For counting-only problems, DP (`O(n·target)`) beats enumeration.

### Permutations
- **Brute** — for each element, insert into all positions of every smaller permutation: wasteful rebuilding.
- **Better** — swap-in-place recursion: `O(n!)` leaves, `O(n)` depth, `O(1)` per node.
- **Optimal** — next-permutation iteration (lexicographic, `O(n)` amortized) when only *one* permutation is needed; factorial number system for the k-th permutation: `O(n²)` → `O(n)` with precomputed factorials.

### Combination sum with pruning
- **Brute** — explore every tree node including hopeless branches: exponential with big constant.
- **Better** — sort + stop when `a[i] > remaining`: prunes whole subtrees.
- **Optimal** — sort + prune + `remaining - a[j] >= 0` loop bound + same-level dedup: still exponential worst case (unavoidable — output is exponential) but minimal nodes in practice.

### Count ways problems (subsequence sum = K)
- **Brute** — enumerate all `2^n` subsequences and count: `O(2^n)`.
- **Better** — memoize `(index, target)`: `O(n·target)` states — crosses into DP.
- **Optimal** — bottom-up 1D/2D DP, possibly space-optimized: `O(n·target)` time, `O(target)` space (§16).

### Key transferable idea
> **Enumeration is the default; memoization is the upgrade; greedy is the prize.** Always ask: "do subproblems repeat?" If yes → DP. "Is there a locally optimal choice with a proof?" If yes → greedy (§12). If neither → backtracking is the honest answer.

---

## 7. C++ / STL TOOLKIT

| Tool | Syntax | Use |
|---|---|---|
| Path buffer | `vector<int> ds;` + push/pop | shared current choice |
| Record result | `ans.push_back(ds)` | **copy** the buffer |
| Sort for dedup | `sort(a.begin(), a.end())` | prerequisite for skip-dup |
| Level dedup | `if (j > i && a[j]==a[j-1]) continue;` | combinations II |
| Used marker | `vector<bool> used(n)` | permutation II |
| Board state | `vector<string> board;` | N-Queens / Sudoku |
| Validity sets | `unordered_set<int> col, d1, d2;` | O(1) placement checks |
| Memo table | `vector<vector<int>> dp(n, vector<int>(t+1,-1));` | recursion → memo |

```cpp
// classic backtracking shell
vector<vector<int>> ans;
vector<int> ds;
function<void(int)> backtrack = [&](int i) {
    if (i == n) { ans.push_back(ds); return; }
    // choose
    ds.push_back(a[i]);
    backtrack(i + 1);
    ds.pop_back();          // undo
    backtrack(i + 1);
};
```

**Key facts**
- `ans.push_back(ds)` stores a **copy**; `ans.push_back(ds)` after more pushes would still be the snapshot at that moment.
- `vector<bool>` is bit-packed — fine for flags; use `vector<char>` if you need `&b[i]`.
- `unordered_set` ops are `O(1)` average — used for membership validity checks.

**Common mistakes**
- Lambda recursion needs `std::function` or a named function (capturing a lambda by reference in itself requires `function`).
- Deep recursion (`n > 10^4`) → stack overflow; convert to iteration or raise nothing (you can't) — use iterative DP instead.
- Reusing a `ds`-like buffer without undoing.

---

## 8. COMPLEXITY GUIDE

| Problem class | Time | Space (depth) |
|---|---:|---:|
| Subsequences / subsets | `O(2^n · n)` | `O(n)` |
| Subsets with dedup | `O(2^n · n)` | `O(n)` |
| Combinations C(n,k) | `O(C(n,k) · k)` | `O(k)` |
| Permutations | `O(n! · n)` | `O(n)` |
| N-Queens | `O(n!)` pruned | `O(n)` |
| Sudoku | `O(9^empty)` | `O(empty)` |
| Word search (m×n, word L) | `O(mn · 4^L)` | `O(L)` |
| Fast power | `O(log n)` | `O(log n)` rec |
| Memoized version | `O(states · choices)` | `O(states)` |

**How to estimate** — draw the recursion tree: `depth × branching factor = nodes`; multiply by per-node cost (`O(n)` if copying the path).

---

## 9. EDGE CASES

- **Empty input** — one empty subsequence/one empty permutation; record it.
- **`n = 1`** — degenerate trees; ensure base case fires before loops.
- **All elements identical** — unique permutations = 1; must dedup.
- **Target = 0** — combination sum records immediately (watch infinite loops).
- **Zero-valued elements with reuse** — infinite recursion; forbid or bound.
- **No valid placement** — return empty result, not crash.
- **Prune with `t < 0`** — must still handle exact-boundary `t == 0` first.
- **INT_MIN exponent** — `n = -n` overflows int; cast to `long long`.
- **Deep recursion limit** — `2·10^5` index recursion crashes; use DP iteration.
- **Board borders** — never index outside `[0, n)`; check before recursing.

---

## 10. COMMON MISTAKES

| # | Mistake | What goes wrong | Why | How to avoid |
|---|---|---|---|---|
| 1 | Forgetting `pop_back()` | Wrong answers (duplicates/garbage) | State not restored | Push → recurse → **pop** symmetric |
| 2 | No dedup (sort missing) | Duplicate combos/perms | Same values from different indices | Sort + same-level skip |
| 3 | Base case after recursive calls | Stack overflow | Infinite descent | Base case **first** |
| 4 | Copying `ds` by reference | All results point to final state | Shallow storage | `ans.push_back(ds)` copies; if pointers, `new` |
| 5 | Not pruning | TLE on large boards | Explores hopeless branches | Check constraints before recursing |
| 6 | Reuse index when not allowed (or vice versa) | Wrong enumeration size | Combination vs permutation semantics | `i+1` = no reuse; `i` = reuse |
| 7 | `seen` dedup not per-level | Wrong dedup | Global vs sibling dedup | `unordered_set` local to each call level |
| 8 | Non-monotone state in memo | Memo never hits | State not canonical | Params must fully identify the subproblem |
| 9 | INT_MIN negation | UB | `-INT_MIN` overflows int | Cast to `long long` |
| 10 | Deep recursion (n ≫ 10^4) | Segfault (stack) | Default stack ~8MB | Iterative DP or smaller depth |

**Conceptual mistakes**
- Confusing subsequence (order kept) vs permutation (reordered) vs combination (unordered) — each needs a different recursion signature.
- Memoizing a function with mutable global side effects — results depend on call order.
- Expecting backtracking to be polynomial — enumeration is exponential by nature.

---

## 11. IMPORTANT FORMULAS / RULES

```text
Subsequence count:        2^n            (each element in/out)
Subsets of n:             2^n  (incl. empty)
Permutations of n:        n!
Permutations of n multiset: n! / (c1!·c2!·…)
Combinations C(n,k):      n! / (k!(n-k)!)
Power:  x^n = (x^(n/2))·(x^(n/2))  [even] ;  x·(x^(n/2))^2 [odd]
N-Queens solution count (n=8): 92
Max recursion depth:      O(n) for index recursion — stack ~10^4–10^5 safe bound
```

**Rules / invariants**
1. **Undo rule**: every modification before a recursive call must be reversed after it.
2. **Dedup rule**: sort input; skip duplicates only at the *same recursion level*, never across levels.
3. **Prune rule**: check feasibility *before* recursing, not after entering.
4. **State rule**: if two calls with the same parameters can give different answers, your state is incomplete.

---

## 12. REUSABLE TEMPLATES

```cpp
// 1. Pick / not-pick (subsequences)
void subseq(int i, vector<int>& a, vector<int>& ds, vector<vector<int>>& out) {
    if (i == (int)a.size()) { out.push_back(ds); return; }
    ds.push_back(a[i]); subseq(i + 1, a, ds, out);
    ds.pop_back();
    subseq(i + 1, a, ds, out);
}

// 2. Combination sum (sorted + prune + dedup)
void combSum(int i, vector<int>& a, int t, vector<int>& ds, vector<vector<int>>& out) {
    if (t == 0) { out.push_back(ds); return; }
    for (int j = i; j < (int)a.size() && t - a[j] >= 0; j++) {
        if (j > i && a[j] == a[j-1]) continue;
        ds.push_back(a[j]);
        combSum(j + 1, a, t - a[j], ds, out);
        ds.pop_back();
    }
}

// 3. Permutations with dedup (swap + per-level seen)
void perm(int start, vector<int>& a, vector<vector<int>>& out) {
    if (start == (int)a.size()) { out.push_back(a); return; }
    unordered_set<int> seen;
    for (int i = start; i < (int)a.size(); i++) {
        if (seen.count(a[i])) continue;
        seen.insert(a[i]);
        swap(a[start], a[i]); perm(start + 1, a, out);
        swap(a[start], a[i]);
    }
}

// 4. Fast power (mod-ready)
long long modPow(long long x, long long n, long long M) {
    long long r = 1 % M; x %= M;
    while (n > 0) { if (n & 1) r = r * x % M; x = x * x % M; n >>= 1; }
    return r;
}
```

## 13. ADVANCED CONCEPTS

### 13.1 Iterative deepening & state-space search
IDS = DFS with depth limit — gets BFS's shortest-depth guarantee with DFS's `O(n)` memory. Related: IDA* for puzzles (15-puzzle) with heuristic cutoffs. Recognize when depth-first search alone is memory-bound.

### 13.2 Bitmask recursion (subsets in O(2ⁿ · n) with bit state)
Represent "which items used" as an `int mask` — enables DP over subsets (`O(2^n · n)`), fast union/difference, and travel-salesman-style DP (`dp[mask][i]`). Prerequisite: §08 bit manipulation.

```cpp
for (int mask = 0; mask < (1 << n); mask++)
    for (int i = 0; i < n; i++) if (mask >> i & 1) { /* item i in subset */ }
```

### 13.3 Constraint propagation (Sudoku-level reasoning)
Forward checking / arc consistency prune candidates *before* recursion — turns naive `9^empty` into milliseconds. Idea: maintain per-cell candidate sets, propagate after each placement.

### 13.4 Dancing Links / Algorithm X (exact cover)
For exact-cover problems (Sudoku, pentominoes), Algorithm X with DLX is optimal — advanced competition material; recognize the *category* even if you won't implement it live.

### 13.5 Recursion → memoization → tabulation → space optimization
This four-stage ladder (visualized in §14) is the DP pipeline of §16. The advanced skill is **reading a recursive solution and mechanically deriving the table**: states = memo dimensions, order = dependency order, transitions = recursive calls.

### 13.6 K-th lexicographic via factorial number system
Direct `O(n)` construction of the k-th permutation without recursion — used in "next permutation" generalizations and countdown-style problems.

---

## 14. CONNECTIONS BETWEEN PATTERNS

```text
Recursion
    |
    v
Backtracking (choice -> explore -> undo)
    |
    +--> Subsets / permutations / combinations (§07 core)
    +--> Board placement (N-Queens, Sudoku)
    +--> Partition cuts (palindrome partitioning)
    |
    v
Same recursion + memoization on repeated states
    |
    v
DYNAMIC PROGRAMMING (§16)
    |
    +--> Memoization (top-down)
    +--> Tabulation (bottom-up)
    +--> Space optimization (rolling rows)
    |
    v
Greedy (§12) — when a proof shows local = global (no table needed)

Trees (§13):  DFS = recursion on structure
Graphs (§15): DFS = same engine on adjacency lists
```

**Mental map**
1. Enumerate everything? → backtracking.
2. Subproblems repeat? → memoize (DP).
3. Optimal choice has a proof? → greedy.
4. `n ≤ 20`? → bitmask DP / subsets.

---

## 15. PROBLEM → PATTERN MAPPING

*(Reference only — solutions and approaches live in the `.cpp` files.)*

### Pick / not-pick (subsequences & subsets)
- `08-Print-All-Subsequences.cpp`
- `09-Power-Set.cpp`
- `10-Subsets-II.cpp`
- `13-Subset-Sum-I.cpp`
- `14-Subset-Sum-II-Exists.cpp`
- `06-Generate-All-Binary-Strings.cpp`

### Combination sum (index + target)
- `11-Combination-Sum-I.cpp`
- `12-Combination-Sum-II.cpp`
- `15-Combination-Sum-III.cpp`
- `16-Letter-Combinations.cpp`

### Permutations
- `23-Permutations.cpp`
- `24-Permutations-II.cpp`
- `25-Kth-Permutation.cpp`

### Board placement / constraint backtracking
- `19-N-Queens.cpp`
- `20-Sudoku-Solver.cpp`
- `21-M-Coloring.cpp`
- `22-Rat-in-a-Maze.cpp`
- `18-Word-Search.cpp`

### Partition cuts
- `17-Palindrome-Partitioning.cpp`

### Parenthesis / string generation
- `07-Generate-Parentheses.cpp`

### Mathematical recursion (fast power / stack recursion)
- `01-Recursive-Implementation-of-Atoi.cpp`
- `02-Pow-x-n.cpp`
- `03-Count-Good-Numbers.cpp`
- `04-Sort-a-Stack.cpp`
- `05-Reverse-a-Stack.cpp`

---

## 16. QUICK REVISION SHEET

**Concepts**
- Recursion = base case + smaller call; backtracking = choose → explore → **undo**.
- Tree shape decides complexity: subsets `2^n`, permutations `n!`.
- State = full parameters of a call; repeated state → memoize → DP (§16).

**Recognition clues**
| Signal | Pattern |
|---|---|
| take/skip every element | pick/not-pick |
| combinations, order irrelevant | index-forward |
| permutations, order relevant | swap / used-array |
| duplicates | sort + same-level skip |
| board + validity | placement + mark/unmark |
| cut into valid parts | partition from `start` |
| `x^n` / log-time numeric | fast power |
| `n ≤ 20`, enumerate all | subsets bitmask |

**Skeleton**
```cpp
base case first -> choose -> recurse -> undo
// combos: for (j = i; ...; j++) with t - a[j] >= 0 prune
// perms:  swap(a[start],a[i]) ... swap back  (+ per-level seen)
```

**Complexity**
subsets `O(2^n·n)` · perms `O(n!·n)` · N-Queens `O(n!)` pruned · word search `O(mn·4^L)` · fast power `O(log n)`.

**Common mistakes**
Missing `pop_back` · no sort before dedup · base case late · storing reference not copy · no pruning · index reuse confusion · `INT_MIN` negation · deep recursion stack overflow.

**Rules**
1. Undo everything you change. 2. Dedup at the *same level* only. 3. Prune before recursing. 4. Same params ⇒ same answer (or state is incomplete).

---

## 17. INTERVIEW CHECKLIST

- [ ] Can I write the backtracking skeleton (choose/undo) from memory?
- [ ] Can I explain why combinations pass `i+1` but combination-sum-I reuses `i`?
- [ ] Can I dedup permutations/combinations correctly (sort + level skip)?
- [ ] Can I draw the recursion tree and derive `2^n` / `n!` complexities?
- [ ] Can I implement N-Queens validity with column/diagonal sets?
- [ ] Can I justify each prune step (why can this branch be cut)?
- [ ] Can I trace push/pop state restoration on paper?
- [ ] Can I recognize when to memoize instead of brute backtracking?
- [ ] Can I handle empty input, all-duplicates, and target-0 edge cases?
- [ ] Can I write fast power with negative-exponent and overflow handling?

<!-- done -->
