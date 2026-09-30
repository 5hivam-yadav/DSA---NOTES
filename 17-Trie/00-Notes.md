# Trie — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — Dictionary Trie (insert / search / startsWith / count)

**What is the pattern?**

Standard character trie with `walk-or-create` insertion and flag-based queries.

**When should I recognize it?**

- "Implement a trie / dictionary", "search word", "starts with prefix", "count words with prefix", "word dictionary with wildcards (`.`)"

**Core intuition**

Paths = strings; sharing = prefixes; queries are walks; existence = terminal flag.

**Generic algorithm**

1. `insert`: for each char, create child if missing, move down; `end++` at last node.
2. `search`: walk; fail if child missing; return `end > 0`.
3. `startsWith`: walk only; return node exists.

**Time / Space**

`O(L)` per operation; space `O(Σ total chars × 26 pointers)` worst-case.

**Edge cases**

Empty string (insert `""` → root's `end`); duplicate inserts (count vs boolean); non-lowercase chars (map/index accordingly).

**Common mistakes**

Forgetting `end` flag (search always true); `c - 'a'` on non-letters; forgetting to increment `pref` on insert for count-variants.

**Variations**

Wildcard `.`, delete with counter decrements (Trie II), map-based children for large alphabets.

### P2 — Prefix Aggregation (count words with prefix / replace / longest-word chain)

**What is the pattern?**

Insert all words; per query walk to the prefix node and read `pref`/`end`; or DFS paths with prefix-validity constraints.

**When should I recognize it?**

- "Count words starting with prefix", "replace words by shortest root", "longest word where all prefixes exist", "autocomplete suggestions".

**Core intuition**

The node reached by a prefix *summarizes* everything under it — `pref` = count under it, `end` = completions.

**Generic algorithm**

1. Build trie.
2. Query: walk; if you fall off → 0/false; else read flag.
3. Replace: walk each word until `end > 0` (shortest root) else keep word.
4. Longest-with-prefixes: DFS, only descend into nodes with `end > 0`.

**Time / Space**

`O(L)` per query after `O(total)` build.

**Edge cases**

Prefix longer than any word; empty prefix (returns total); duplicates.

**Common mistakes**

Reading `end` instead of `pref` (word count vs prefix count); not handling "fall off the trie" (must return 0, not dereference null).

**Variations**

Trie + backtracking DFS to collect all matching words (Word Search II style).

### P3 — Counting Structures (distinct substrings / distinct rows)

**What is the pattern?**

Insert suffixes (or rows) into a trie and **count newly created nodes** = count of distinct paths = distinct entities.

**When should I recognize it?**

- "Count distinct substrings", "distinct rows in binary matrix", "distinct strings after operations".

**Core intuition**

Distinct substrings ↔ distinct root-to-node paths; every new node = a never-before-seen substring.

**Generic algorithm**

1. For each suffix `i`: walk/create from root, counting creations.
2. Answer = number of created nodes (excluding root) — optionally subtract 1 for empty string per spec.

**Time / Space**

`O(n²)` time, `O(n²)` nodes worst (n ≤ 1000 typical).

**Edge cases**

Empty string (0 substrings or 1, check spec); all-same characters (trie depth n, few nodes... actually n nodes per suffix? shared → linear); duplicates across suffixes (counted once — the point!).

**Common mistakes**

Counting every insert step instead of only *creations*; double-counting when the same path exists.

**Variations**

Hash-set of substrings `O(n²)` memory-heavy alternative; suffix array formula (§05 advanced).

### P4 — Binary Trie (XOR maximization / minimization)

**What is the pattern?**

Insert integers bit-by-bit (MSB→LSB) into a 2-children trie; query greedily for the bit path that maximizes (or minimizes) XOR.

**When should I recognize it?**

- "Maximum XOR of two numbers in an array", "maximum XOR query with updates", "min XOR pair", "XOR with largest/smaller".

**Core intuition**

XOR's most significant differing bit dominates all lower bits → at each bit, choose the opposite bit child if it exists (else same bit).

**Generic algorithm**

1. Insert each number: 32 levels, `ch[bit]`.
2. `maxXor(x)`: walk preferring `bit ^ 1`; accumulate `1<<b` when taken.
3. Answer over array = insert all, query each, take max (or query against previous inserts only).

**Time / Space**

Insert/query `O(32)` = `O(1)`; build+max over n: `O(32n)`; space `O(32n)` nodes.

**Edge cases**

Single element (no pair → 0/self-query); all zeros; negative numbers (treat as 32-bit patterns — signed shift caveat); duplicates.

**Common mistakes**

Querying before inserting anything (empty trie); LSB-first (must be MSB-first); forgetting `ans |= 1<<b`.

**Variations**

Min-XOR → prefer *same* bit; with deletions → reference counts per node; offline XOR queries → sort + insert (§08-style).

### P5 — Trie + Backtracking on Grid (word search over a dictionary)

**What is the pattern?**

Put the *dictionary* (not the board) in a trie; DFS the board following trie paths, pruning when the path leaves the trie.

**When should I recognize it?**

- "Word search II" (find all dictionary words on a board), "boggle", "count distinct paths forming dictionary words".

**Core intuition**

The trie replaces the per-word search: one DFS simultaneously tests all words; when no child matches, the whole branch is impossible → massive pruning.

**Generic algorithm**

1. Insert all words into trie (optionally with an output index at terminals).
2. DFS each cell: move to child; if missing → backtrack; if terminal → record word; mark cell visited → explore 4 neighbors → unmark.
3. Optional optimization: remove found words / decrement counts to avoid duplicates.

**Time / Space**

Hard to bound exactly — `O(mn · 4^L)` worst, pruned by trie; space `O(total words)` trie + `O(L)` path.

**Edge cases**

Word used once (remove after found); overlapping words; single-cell words; board cell reuse (must unmark).

**Common mistakes**

Not unmarking cells (allows reuse within one word); leaving found words (duplicates); inserting reversed words when words may wrap (spec-dependent).

**Variations**

Prefix-count pruning (`pref > 0` required to descend).

### P6 — Offline / Batch XOR Queries (sort + incremental insert)

**What is the pattern?**

Sort queries by a key (value bound), sweep the array inserting elements into a binary trie as they become eligible, answer each query against the current trie.

**When should I recognize it?**

- "Maximum XOR with element from a prefix/suffix of the array" (queries offline).

**Core intuition**

The trie supports *insertions only* — re-sorted queries turn a dynamic problem into a monotone sweep where the trie only grows.

**Generic algorithm**

1. Sort array values and queries by the same key ascending.
2. Advance a pointer inserting `arr[i]` while `arr[i] <= query.key`.
3. `answer[qi] = trie.maxXor(query.x)` (−1 if trie empty).

**Time / Space**

`O((n + q) · 32 + (n + q) log(n + q))` / `O(32n)`.

**Edge cases**

No eligible elements (return −1); duplicate bounds (stable handling); all queries before any element.

**Common mistakes**

Wrong sweep direction (descending for suffix queries); forgetting sort of *queries* (order of insertion matters for correctness of eligibility).

**Variations**

Segment-tree-of-tries (fully dynamic) — advanced; meet-in-the-middle for two-array XOR max (§08).

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
