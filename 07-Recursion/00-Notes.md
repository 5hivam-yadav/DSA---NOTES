# Recursion and Backtracking — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — Pick / Not-Pick (Subsequence Engine)

**What is the pattern?**

At each index branch into take/skip, undo after returning — enumerating all `2^n` subsequences.

**When should I recognize it?**

- "All subsequences", "count subsequences with property", "subset sum", "partition into subsequences", "target sum with ±".

**Core intuition**

Every element makes one independent binary decision → a perfect binary tree of height `n`.

**General approach / Generic algorithm**

1. Base: `i == n` → record/evaluate.
2. Take: push → recurse `i+1` → pop.
3. Skip: recurse `i+1`.
4. Undo restores state for the sibling branch.

**Time / Space**

`O(2^n · n)` time (2^n leaves × O(n) path cost); `O(n)` recursion depth + output space.

**Edge cases**

Empty input (one empty subsequence); duplicates (may need sorting + level-skip); `n = 0`.

**Common mistakes**

Forgetting `pop_back`; storing the same vector reference; not copying when recording.

**Variations**

Target-constrained pick/not-pick → DP on (index, remaining) — §16.

### P2 — Combination Sum (index-forward + target)

**What is the pattern?**

Recurse on `(index, remaining target)`; index moves forward (no revisiting) or stays (reuse allowed).

**When should I recognize it?**

- "Combinations that sum to target", "combination sum I/II/III", "letter combinations of a phone number".

**Core intuition**

Index-forward kills order duplicates structurally; sorting + same-level skip kills value duplicates; `target - a[i]` shrinks the state.

**General approach**

1. Sort (needed for pruning + dedup).
2. At `i`: if `target == 0` → record; if `a[i] > target` → stop.
3. Skip duplicates at the same level: `if (i > start && a[i] == a[i-1]) continue;`.
4. Choose `a[i]`, recurse with `i+1` (or `i` if reuse).

**Time / Space**

Exponential in target/`n`; `O(target/min)` depth worst case.

**Edge cases**

No combination sums to target; `a[i] == 0` (infinite loop if reuse allowed!); single element == target.

**Common mistakes**

Not sorting before dedup; reusing index for Combination II; missing `t - a[j] >= 0` pruning.

**Variations**

Letter combinations (fixed digit map); combination sum III (exactly `k` numbers).

### P3 — Permutation Generation (swap or used-array)

**What is the pattern?**

Fill positions left→right choosing among unused elements — `n!` orderings.

**When should I recognize it?**

- "All permutations", "next permutation", "k-th permutation", "permutations of a string/array (with duplicates)".

**Core intuition**

Position `start` picks any remaining element; swapping in place avoids an extra `used[]` while keeping `O(1)` node cost.

**General approach (swap)**

1. `f(start)`: if `start == n` → record.
2. For `i` from `start` to `n-1`: `swap(a[start], a[i])` → `f(start+1)` → `swap` back.
3. For duplicates: sort + skip equal `a[i]` at the same depth.

**Time / Space**

`O(n! · n)` time; `O(n)` depth (swap) or `O(n! )` for storing all.

**Edge cases**

`n = 1`; all elements identical (only 1 unique permutation); empty input.

**Common mistakes**

Forgetting to swap back; dedup with `seen` not reset per level; generating duplicates in Permutations II.

**Variations**

Used-array encoding (needed for path-based constraints); `k`-th permutation via factorial number system.

### P4 — Board Placement with Validity Check

**What is the pattern?**

Place one item per row/positional slot; before recursing, verify the placement against constraints maintained in sets/maps.

**When should I recognize it?**

- N-Queens, Sudoku solver, rat in a maze, word search, m-coloring, knight tour.

**Core intuition**

Constraints are *local to what you already placed* → maintain incremental structures (used columns, diagonal ids, board grid) and check in `O(1)` before recursing.

**General approach**

1. At row/position `i`, try each candidate `j`.
2. Check validity against stored state (e.g. `col[j]`, `diag1[i-j]`, `diag2[i+j]`).
3. Mark state → recurse → **unmark** (backtrack).
4. On reaching the end row → record solution.

**Time / Space**

N-Queens `O(n!)` naive (pruned heavily); Sudoku `O(9^empty)`; word search `O(mn · 4^L)`.

**Edge cases**

No valid placement (return empty); single cell; already-filled constraints (Sudoku given cells); dead ends needing full undo.

**Common mistakes**

Diagonal index off-by-one (use offset `+ n`); not unmarking on return; processing board cells without a proper visitation marker (write/restore or separate `vis`).

**Variations**

Row-major vs cell-major iteration; constraint propagation (Sudoku naked singles); bitmask-parallel validity.

### P5 — Partition Cuts (enumerate split points)

**What is the pattern?**

Recurse on `(start)` and try every valid end cut; the remaining suffix recurses from `end + 1`.

**When should I recognize it?**

- "Partition string so every part is a palindrome", "word break", "partition array for max sum", "decode ways".

**Core intuition**

The first cut's position is a choice; after fixing it, the rest of the problem is the same on a smaller suffix → recursion with one changing parameter (`start`).

**General approach**

1. From `start`, extend `end`.
2. If `s[start..end]` is valid (palindrome / in dictionary) → recurse `end + 1`.
3. If reaching `n` → record partition.

**Time / Space**

Exponential in `n` worst case; palindrome check `O(len)` → precompute with expand or DP for `O(n^2)` total.

**Edge cases**

No valid partition; whole string is one part; single characters always palindromic (worst case `2^(n-1)` partitions).

**Common mistakes**

Forgetting `pop_back`; re-checking palindromes from scratch (precompute); off-by-one in `substr` length.

**Variations**

Minimize number of cuts (DP over cuts); word break (dictionary set lookup).

### P6 — Mathematical Recursion (fast power, divide & conquer)

**What is the pattern?**

Halve the exponent/problem, combine results — `O(log n)` instead of `O(n)` multiplications.

**When should I recognize it?**

- "Compute `x^n`", "power without `pow`", "count good numbers", "matrix chain-style repeated squaring".

**Core intuition**

`x^n = (x^(n/2))²` if n even, `x·x^(n-1)` if odd → each step halves the exponent.

**General approach**

1. Base: `n == 0 → 1`.
2. `half = f(x, n/2)`.
3. Return `half · half` or `x · half · half`.
4. Handle negatives (`1/x^|n|`) and `INT_MIN` overflow (`long long`).

**Time / Space**

`O(log n)` multiplications; recursion depth `O(log n)`.

**Edge cases**

`n = 0` (any `x → 1`), `x = 0/1`, negative `n`, `n = INT_MIN` (negation overflows int!).

**Common mistakes**

`(long long) n` before negating `INT_MIN`; missing modulo when the problem requires it; iterative vs recursive parity bugs.

**Variations**

Count good numbers (even/odd position parity with modulo); sort a stack recursively (insert-at-bottom).

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
