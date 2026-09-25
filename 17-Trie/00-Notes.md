# 17 — Trie — Complete Pattern-Based Notes

---

## 1. Topic Overview

A **trie** (prefix tree) stores strings as paths in a tree — sharing common prefixes — so insert/search/prefix queries cost `O(L)` regardless of how many strings are stored.

**What it is**
Each node holds up to 26 (alphabet) child pointers + flags/counters. A string is stored *implicitly* as the path of its characters from the root.

**Why it is important**
- `O(L)` dictionary operations vs `O(L log N)` for balanced trees / hashing-with-sorted-output.
- Powers autocomplete, spell checkers, word games, IP routing, and **binary tries for XOR maximization**.
- Distinct-substring counting and prefix-aggregation problems are trie-native.

**Where it is used**
- Word Search II, design dictionary (with/without counts), replace words, longest word with all prefixes.
- Count distinct substrings / distinct rows.
- Max XOR of two numbers (binary trie) — a top "advanced" interview question.

**How it connects to other topics**
- §05 Strings: LPS/KMP handle *pattern matching*; tries handle *dictionary/prefix* workloads.
- §17 ↔ §08 Bit Manipulation: binary trie = trie over bits, greedy opposite-bit descent.
- §07 Recursion: DFS over the trie children (collect words, longest path with property).

**Interview memory hook:** *Walk-or-create per char. `end` flags words, `pref` counts prefixes. XOR max = always take the opposite bit if it exists.*

---

## 2. Fundamentals

### 2.1 Node structure

```cpp
struct Node {
    Node* ch[26] = {};
    int end = 0;      // number of words ending here
    int pref = 0;     // number of words passing through
};
```

### 2.2 Insert / search / prefix — walk-or-create

```text
insert "app":
root -a-> n1 -p-> n2 -p-> n3(end=1)
search "app":   follow a,p,p -> check n3.end > 0
startsWith "ap": follow a,p -> node exists => true
```

### 2.3 Why O(L)

Each character does `O(1)` work (array index) and moves one level down — depth = string length `L`, independent of the number of stored strings `N`.

### 2.4 Terminology

| Term | Meaning |
|---|---|
| **Prefix sharing** | Common prefixes stored once — memory-efficient for similar keys. |
| **`end` vs `pref`** | Word existence vs prefix frequency — different queries need different flags. |
| **Binary trie** | Trie over the 32 bits of an integer; children `[0]`, `[1]`. |
| **Greedy descent** | At each bit choose the child that maximizes (or matches) the goal. |
| **Compressed trie / radix tree** | Edge-labeled variants (Aho-Corasick, suffix trees build on this). |

---

## 3. Core Concepts

### 3.1 Insert / Search / StartsWith (walk-or-create)

**Definition** For each character: follow the child if it exists, else create it; flags updated at the end of the path.

**Why it matters** These three share one skeleton — `search` = walk-only, `insert` = walk-or-create + `end++`, `startsWith` = walk-only (ignore `end`).

**How it works**

```cpp
void insert(const string& s) {
    Node* t = root;
    for (char c : s) {
        int i = c - 'a';
        if (!t->ch[i]) t->ch[i] = new Node();
        t = t->ch[i];
        t->pref++;
    }
    t->end++;
}
```

**Complexity** `O(L)` per op; space `O(total characters × 26 pointers)` worst (less with sharing).

**Common mistakes** Updating `pref` on the wrong node (before moving vs after — be consistent); indexing `c - 'a'` without checking char range.

---

### 3.2 Counting words & prefixes (end vs pref)

**Definition** `end` = words terminating here; `pref` = words passing through here.

**Why both** - "How many words *are* `word`?" → `end`. - "How many words *start with* `word`?" → `pref` at the path's end. Trie II (insert/delete/count) needs both plus careful decrement on delete.

**Common mistake** Using `end` for prefix queries or `pref` for word-existence — different semantics.

---

### 3.3 Distinct substrings via suffix insertion

**Definition** Insert **every suffix** `s[i..]` into the trie; count newly created nodes → distinct substrings.

**Intuition** Each distinct substring corresponds to exactly one root-to-node path; new nodes = new substrings.

**Complexity** `O(n²)` insertions of total `O(n²)` characters (fine for `n ≤ 1000`); with suffix links / Ukkonen → `O(n)` (advanced, awareness only).

**Alternative** `n(n+1)/2 − Σ LCP` with suffix array (§05 advanced).

---

### 3.4 Replace words / shortest root

**Definition** For each word, find the *shortest* dictionary prefix that is a word (its "root") and replace.

**How it works** Insert roots into trie; for each word, walk until `end > 0` → that's the root; if none, keep the word.

**Complexity** `O(total characters)`.

---

### 3.5 Longest word with all prefixes present

**Definition** Find the longest word where **every prefix** is also a word in the set (ties → lexicographically smallest).

**How it works** Insert all words; DFS the trie tracking the current path — a node is only visitable if `end > 0` (its word-prefix exists). Track the best complete path.

**Complexity** `O(total characters)`.

---

### 3.6 Binary trie & XOR maximization

**Definition** A trie over the 32 bits of integers; inserting `x` and querying `maxXor(x)` = walk bit by bit choosing the **opposite** bit when available (that yields `1` at the most significant differing position).

**Why greedy works** Bits are processed MSB→LSB; a set bit at position `b` in the XOR contributes `2^b` which dominates *all* lower bits combined (`2^b > 2^(b-1) + … + 1`) → always prefer setting a higher bit.

**How it works**

```cpp
int maxXor(int x) {
    Node* t = root; int ans = 0;
    for (int b = 31; b >= 0; b--) {
        int bit = (x >> b) & 1;
        if (t->ch[bit ^ 1]) { ans |= (1 << b); t = t->ch[bit ^ 1]; }
        else t = t->ch[bit];
    }
    return ans;
}
```

**Complexity** Insert/query `O(32)`; max pair over n numbers `O(32n)`.

**Common mistakes** Forgetting `ans |= 1<<b` when taking the opposite child; starting from LSB (must go MSB-first).

---

## 4. PATTERN LIBRARY

### P1 — Dictionary Trie (insert / search / startsWith / count)

#### What is the pattern?
Standard character trie with `walk-or-create` insertion and flag-based queries.

#### When should I recognize it?
- "Implement a trie / dictionary", "search word", "starts with prefix", "count words with prefix", "word dictionary with wildcards (`.`)"

#### Core intuition
Paths = strings; sharing = prefixes; queries are walks; existence = terminal flag.

#### Generic algorithm
1. `insert`: for each char, create child if missing, move down; `end++` at last node.
2. `search`: walk; fail if child missing; return `end > 0`.
3. `startsWith`: walk only; return node exists.

#### C++ template
```cpp
struct Trie {
    struct N { N* ch[26] = {}; int end = 0, pref = 0; };
    N* root = new N();
    void insert(const string& s) {
        N* t = root;
        for (char c : s) {
            int i = c - 'a';
            if (!t->ch[i]) t->ch[i] = new N();
            t = t->ch[i]; t->pref++;
        }
        t->end++;
    }
    bool search(const string& s) {
        N* t = root;
        for (char c : s) { int i = c - 'a'; if (!t->ch[i]) return false; t = t->ch[i]; }
        return t->end > 0;
    }
    bool startsWith(const string& s) {
        N* t = root;
        for (char c : s) { int i = c - 'a'; if (!t->ch[i]) return false; t = t->ch[i]; }
        return true;
    }
};
```

#### Time / Space
`O(L)` per operation; space `O(Σ total chars × 26 pointers)` worst-case.

#### Edge cases
Empty string (insert `""` → root's `end`); duplicate inserts (count vs boolean); non-lowercase chars (map/index accordingly).

#### Common mistakes
Forgetting `end` flag (search always true); `c - 'a'` on non-letters; forgetting to increment `pref` on insert for count-variants.

#### Variations
Wildcard `.`, delete with counter decrements (Trie II), map-based children for large alphabets.

#### Practice mapping
- `01-Implement-Trie-I.cpp`, `02-Implement-Trie-II.cpp`

---

### P2 — Prefix Aggregation (count words with prefix / replace / longest-word chain)

#### What is the pattern?
Insert all words; per query walk to the prefix node and read `pref`/`end`; or DFS paths with prefix-validity constraints.

#### When should I recognize it?
- "Count words starting with prefix", "replace words by shortest root", "longest word where all prefixes exist", "autocomplete suggestions".

#### Core intuition
The node reached by a prefix *summarizes* everything under it — `pref` = count under it, `end` = completions.

#### Generic algorithm
1. Build trie.
2. Query: walk; if you fall off → 0/false; else read flag.
3. Replace: walk each word until `end > 0` (shortest root) else keep word.
4. Longest-with-prefixes: DFS, only descend into nodes with `end > 0`.

#### C++ template
```cpp
int countPrefix(N* root, const string& p) {
    N* t = root;
    for (char c : p) { int i = c - 'a'; if (!t->ch[i]) return 0; t = t->ch[i]; }
    return t->pref;
}
```

#### Time / Space
`O(L)` per query after `O(total)` build.

#### Edge cases
Prefix longer than any word; empty prefix (returns total); duplicates.

#### Common mistakes
Reading `end` instead of `pref` (word count vs prefix count); not handling "fall off the trie" (must return 0, not dereference null).

#### Variations
Trie + backtracking DFS to collect all matching words (Word Search II style).

#### Practice mapping
- `03-Longest-Word-With-All-Prefixes.cpp`, `02-Implement-Trie-II.cpp`

---

### P3 — Counting Structures (distinct substrings / distinct rows)

#### What is the pattern?
Insert suffixes (or rows) into a trie and **count newly created nodes** = count of distinct paths = distinct entities.

#### When should I recognize it?
- "Count distinct substrings", "distinct rows in binary matrix", "distinct strings after operations".

#### Core intuition
Distinct substrings ↔ distinct root-to-node paths; every new node = a never-before-seen substring.

#### Generic algorithm
1. For each suffix `i`: walk/create from root, counting creations.
2. Answer = number of created nodes (excluding root) — optionally subtract 1 for empty string per spec.

#### C++ template
```cpp
long long distinctSubstrings(const string& s) {
    Trie t; long long cnt = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        Trie::N* node = t.root;
        for (int j = i; j < (int)s.size(); j++) {
            int c = s[j] - 'a';
            if (!node->ch[c]) { node->ch[c] = new Trie::N(); cnt++; }
            node = node->ch[c];
        }
    }
    return cnt;
}
```

#### Time / Space
`O(n²)` time, `O(n²)` nodes worst (n ≤ 1000 typical).

#### Edge cases
Empty string (0 substrings or 1, check spec); all-same characters (trie depth n, few nodes... actually n nodes per suffix? shared → linear); duplicates across suffixes (counted once — the point!).

#### Common mistakes
Counting every insert step instead of only *creations*; double-counting when the same path exists.

#### Variations
Hash-set of substrings `O(n²)` memory-heavy alternative; suffix array formula (§05 advanced).

#### Practice mapping
- `04-Number-of-Distinct-Substrings.cpp`

---

### P4 — Binary Trie (XOR maximization / minimization)

#### What is the pattern?
Insert integers bit-by-bit (MSB→LSB) into a 2-children trie; query greedily for the bit path that maximizes (or minimizes) XOR.

#### When should I recognize it?
- "Maximum XOR of two numbers in an array", "maximum XOR query with updates", "min XOR pair", "XOR with largest/smaller".

#### Core intuition
XOR's most significant differing bit dominates all lower bits → at each bit, choose the opposite bit child if it exists (else same bit).

#### Generic algorithm
1. Insert each number: 32 levels, `ch[bit]`.
2. `maxXor(x)`: walk preferring `bit ^ 1`; accumulate `1<<b` when taken.
3. Answer over array = insert all, query each, take max (or query against previous inserts only).

#### C++ template
```cpp
struct BinTrie {
    struct N { N* ch[2] = {}; };
    N* root = new N();
    void ins(int x) {
        N* t = root;
        for (int b = 31; b >= 0; b--) {
            int bit = (x >> b) & 1;
            if (!t->ch[bit]) t->ch[bit] = new N();
            t = t->ch[bit];
        }
    }
    int maxXor(int x) {
        N* t = root; int ans = 0;
        for (int b = 31; b >= 0; b--) {
            int bit = (x >> b) & 1;
            if (t->ch[bit ^ 1]) { ans |= 1 << b; t = t->ch[bit ^ 1]; }
            else t = t->ch[bit];
        }
        return ans;
    }
};
```

#### Time / Space
Insert/query `O(32)` = `O(1)`; build+max over n: `O(32n)`; space `O(32n)` nodes.

#### Edge cases
Single element (no pair → 0/self-query); all zeros; negative numbers (treat as 32-bit patterns — signed shift caveat); duplicates.

#### Common mistakes
Querying before inserting anything (empty trie); LSB-first (must be MSB-first); forgetting `ans |= 1<<b`.

#### Variations
Min-XOR → prefer *same* bit; with deletions → reference counts per node; offline XOR queries → sort + insert (§08-style).

#### Practice mapping
- `05-Bit-Prefix-Max-XOR.cpp`, `06-Maximum-XOR-Two-Numbers.cpp`, `07-Offline-XOR-Queries.cpp`

---

### P5 — Trie + Backtracking on Grid (word search over a dictionary)

#### What is the pattern?
Put the *dictionary* (not the board) in a trie; DFS the board following trie paths, pruning when the path leaves the trie.

#### When should I recognize it?
- "Word search II" (find all dictionary words on a board), "boggle", "count distinct paths forming dictionary words".

#### Core intuition
The trie replaces the per-word search: one DFS simultaneously tests all words; when no child matches, the whole branch is impossible → massive pruning.

#### Generic algorithm
1. Insert all words into trie (optionally with an output index at terminals).
2. DFS each cell: move to child; if missing → backtrack; if terminal → record word; mark cell visited → explore 4 neighbors → unmark.
3. Optional optimization: remove found words / decrement counts to avoid duplicates.

#### C++ template
```cpp
// dfs(r, c, node):
//   node = node->ch[board[r][c] - 'a'];  if (!node) return;
//   if (node->end) { out.push_back(node->word); node->end = 0; }
//   mark visited; for 4 dirs: if in bounds && unvisited: dfs(...); unmark
```

#### Time / Space
Hard to bound exactly — `O(mn · 4^L)` worst, pruned by trie; space `O(total words)` trie + `O(L)` path.

#### Edge cases
Word used once (remove after found); overlapping words; single-cell words; board cell reuse (must unmark).

#### Common mistakes
Not unmarking cells (allows reuse within one word); leaving found words (duplicates); inserting reversed words when words may wrap (spec-dependent).

#### Variations
Prefix-count pruning (`pref > 0` required to descend).

#### Practice mapping
- `03-Longest-Word-With-All-Prefixes.cpp`, `07-Recursion/18-Word-Search.cpp` (single-word version)

---

### P6 — Offline / Batch XOR Queries (sort + incremental insert)

#### What is the pattern?
Sort queries by a key (value bound), sweep the array inserting elements into a binary trie as they become eligible, answer each query against the current trie.

#### When should I recognize it?
- "Maximum XOR with element from a prefix/suffix of the array" (queries offline).

#### Core intuition
The trie supports *insertions only* — re-sorted queries turn a dynamic problem into a monotone sweep where the trie only grows.

#### Generic algorithm
1. Sort array values and queries by the same key ascending.
2. Advance a pointer inserting `arr[i]` while `arr[i] <= query.key`.
3. `answer[qi] = trie.maxXor(query.x)` (−1 if trie empty).

#### C++ template
```cpp
// sort queries by m;  int p = 0;
// for each query q (ascending m): while (p < n && arr[p] <= q.m) trie.ins(arr[p++]);
// answers[q.i] = trie.empty() ? -1 : trie.maxXor(q.x);
```

#### Time / Space
`O((n + q) · 32 + (n + q) log(n + q))` / `O(32n)`.

#### Edge cases
No eligible elements (return −1); duplicate bounds (stable handling); all queries before any element.

#### Common mistakes
Wrong sweep direction (descending for suffix queries); forgetting sort of *queries* (order of insertion matters for correctness of eligibility).

#### Variations
Segment-tree-of-tries (fully dynamic) — advanced; meet-in-the-middle for two-array XOR max (§08).

#### Practice mapping
- `07-Offline-XOR-Queries.cpp`

---

## 5. PATTERN RECOGNITION

| If the problem says... | Think about... |
|---|---|
| "implement a dictionary / trie" | P1 walk-or-create |
| "words with prefix / count by prefix" | `pref` counter at path end (P2) |
| "replace word by shortest root" | trie walk until `end` (P2) |
| "longest word where all prefixes exist" | DFS with `end>0` gate (P2) |
| "distinct substrings" | insert all suffixes, count new nodes (P3) |
| "max XOR of two numbers" | binary trie greedy (P4) |
| "XOR queries with element ≤ m" | offline sort + insert sweep (P6) |
| "find all dictionary words on a board" | trie + board DFS (P5) |
| "autocomplete / suggestions" | trie DFS collecting subtrees |
| "many strings, repeated prefix checks" | trie beats hashing |
| exact-match only, no prefixes | `unordered_set` might suffice |

**Decision rules**
1. **Prefix semantics** (starts with, count with prefix) → trie (hashing can't answer prefixes efficiently).
2. **XOR extremum** → binary trie.
3. **Dictionary matching of many words** → trie (or Aho-Corasick for streams).
4. Only exact lookups, no prefix structure → consider `unordered_set` first (simpler).
5. Huge alphabet (Unicode) → map/`unordered_map` children instead of `ch[26]`.

---

## 6. BRUTE → BETTER → OPTIMAL THINKING

### Prefix counting (how many words start with P)
- **Brute** — scan every word, `strncmp` each: `O(N · L)`.
- **Better** — sort words, binary search the prefix range: `O(N log N + L log N)`.
- **Optimal** — trie: `O(N·L)` build once, then `O(L)` per query — wins with many queries.

### Max XOR pair
- **Brute** — check all pairs: `O(n²)`.
- **Better** — for each bit, partition sets (divide by MSB first): `O(32·n)` conceptually — this *is* the trie idea unfolded.
- **Optimal** — binary trie insert + query: `O(32n)` — same bound, clean structure, supports online inserts.

### Distinct substrings
- **Brute** — generate all `n(n+1)/2` substrings into a set: `O(n³)` (hashing each) or `O(n²)` memory.
- **Better** — suffix array + LCP: `O(n log n)`.
- **Optimal for interviews** — suffix-insertion trie counting nodes: `O(n²)` time/space, trivially short code; mention suffix array for `O(n log n)`.

### Word search II (all dictionary words on board)
- **Brute** — run single-word DFS per word: `O(words · mn · 4^L)`.
- **Better** — prefix-set pruning (reject words whose prefixes fail): big constant win, still per-word.
- **Optimal** — one shared trie DFS: explores each board path *once* against all words simultaneously → `O(mn · 4^L)` with far fewer live branches; found words are removed to cut repeats.

### Dictionary existence vs hashing
- **Brute** — sorted array + binary search per query: `O(L log N)`.
- **Better** — `unordered_set`: `O(L)` expected per query — **beats trie for exact matches**.
- **Optimal depends on needs**: exact-only → hash; prefixes/counts/wildcards/XOR → trie. Recognize this split; don't default blindly.

### Key transferable idea
> Tries trade memory for **prefix-aware `O(L)` operations**. Use them when queries mention *prefixes*, *shared structure*, or *bit-greedy XOR*; otherwise hashing is simpler and often faster.

---

## 7. C++ / STL TOOLKIT

| Tool | Syntax | Use |
|---|---|---|
| Node + children array | `Node* ch[26] = {}` | character trie |
| Node + 2 children | `Node* ch[2] = {}` | binary trie |
| Counter flags | `int end, pref` | word/prefix counts |
| `c - 'a'` indexing | `int i = c - 'a'` | lowercase maps to 0..25 |
| DFS over trie | recursion on children | collect words, longest path |
| `unordered_map<char, Node*>` | dynamic alphabet | Unicode/large alphabets |

```cpp
// walk-or-create
Node* t = root;
for (char c : s) {
    int i = c - 'a';
    if (!t->ch[i]) t->ch[i] = new Node();
    t = t->ch[i];
}

// walk-only (search / prefix)
Node* t = root;
for (char c : s) {
    int i = c - 'a';
    if (!t->ch[i]) return /* false / 0 */;
    t = t->ch[i];
}
// result: t->end > 0  (word)   |   t != nullptr (prefix path existed)

// binary trie descent
for (int b = 31; b >= 0; b--) {
    int bit = (x >> b) & 1;
    if (t->ch[bit ^ 1]) { /* take opposite */ t = t->ch[bit ^ 1]; }
    else t = t->ch[bit];
}
```

**Common mistakes**
- Forgetting `new Node()` before `t = t->ch[i]` (null deref).
- `c - 'a'` on uppercase/digits → out-of-bounds index (guard with `isalpha`/`tolower`).
- Not initializing `ch[26] = {}` (garbage pointers).

---

## 8. COMPLEXITY GUIDE

| Operation | Time | Space |
|---|---:|---:|
| insert / search / startsWith | `O(L)` | `O(L)` nodes worst |
| count prefix / word | `O(L)` | `O(1)` |
| All words under prefix (DFS) | `O(subtree size)` | `O(depth)` |
| Distinct substrings (suffix inserts) | `O(n²)` | `O(n²)` nodes |
| Binary trie insert / maxXor | `O(32)` | `O(32)` nodes |
| Max XOR over array | `O(32n)` | `O(32n)` |
| Offline XOR queries | `O((n+q)(32 + log))` | `O(32n)` |
| Word search II (board m×n, L) | `O(mn·4^L)` pruned | trie + path |

**How to estimate** — per-character work with fixed branching → `O(L)` per op; total build = `O(total characters)`. Space = number of distinct prefixes × children size.

---

## 9. EDGE CASES

- **Empty string inserted** — lives at root (`root->end`); search `""` checks `root->end > 0`.
- **Query falls off the trie mid-way** — return false/0; never dereference null.
- **Duplicate inserts** — `end` becomes 2 (count semantics) vs boolean (set semantics) — know which the problem wants.
- **Single-character words**; word that is a prefix of another (`app` + `apple` → `end` at both nodes).
- **All words share one prefix** — deep single chain; no issue but memory per char.
- **Non-lowercase input** — normalize (`tolower`) or widen children.
- **XOR with negative numbers** — treat bits as 32-bit two's complement; avoid signed `1<<31` (use `1U`/`1LL`).
- **Trie empty when querying XOR** — return −1/0 per spec (guard `root` children).
- **Very large alphabets** — `ch[26]` wastes space; switch to `map`.

---

## 10. COMMON MISTAKES

| # | Mistake | What goes wrong | Why | How to avoid |
|---|---|---|---|---|
| 1 | Forgetting the `end` flag | search returns true wrongly | path existence ≠ word existence | check `t->end > 0` |
| 2 | `pref` vs `end` mixup | wrong counts | prefix passes through; word ends | name fields clearly; comment queries |
| 3 | Not creating child before moving | null deref | `t = t->ch[i]` on null | `if (!t->ch[i]) new N();` first |
| 4 | `c - 'a'` on non-lowercase | out-of-bounds index | negative/large i | `tolower` + validate |
| 5 | Uninitialized children array | garbage pointers | `Node* ch[26];` no init | `= {}` in-struct |
| 6 | Empty-string semantics | search("") wrong | lives at root | check `root->end` |
| 7 | LSB-first in binary trie | wrong XOR greedy | MSB dominates | loop `b = 31..0` |
| 8 | Signed `1 << 31` | UB / wrong bit | sign bit | `1U << 31` or `1LL` |
| 9 | Forgetting `ans |= 1 << b` | XOR value wrong | took the child but didn't record | set bit when opposite taken |
| 10 | Counting insert steps for distinct substrings | inflated count | re-traversed shared paths | count only **newly created** nodes |
| 11 | Not removing found words (word search) | duplicate outputs | same path found again | clear `end` after recording |
| 12 | Excessive memory (26 pointers × nodes) | MLE on large sets | naive children array | pointer compression / map children |

**Conceptual mistakes**
- Using a trie when an `unordered_set` suffices (exact match only) — extra memory for nothing.
- Expecting `O(1)` lookup like hashing — trie is `O(L)` *predictable*, not constant.

---

## 11. IMPORTANT FORMULAS / RULES

```text
Trie op cost:        O(L)  (L = query length), independent of N
Nodes needed:        <= total characters inserted (<= sum of lengths)
Distinct substrings: # nodes created by inserting ALL suffixes
                     (== n(n+1)/2 - sum of LCPs via suffix array)
Binary trie depth:   32 (int) / 64 (long long)
maxXor greedy:       at bit b take child bit^1 if exists; gain 2^b
                     (2^b > 2^(b-1) + ... + 1 => MSB-first is optimal)
Offline XOR:         sort both array & queries by key; sweep-insert; answer current
Word/prefix counts:  end = terminating words; pref = words through node
```

**Decision rules**
1. Prefix semantics → trie. 2. XOR extremum → binary trie. 3. Exact-only → hash set. 4. Big alphabet → map children. 5. Many words on grid → trie + DFS.

---

## 12. REUSABLE TEMPLATES

```cpp
// 1. Character trie (insert / search / startsWith)
struct Trie {
    struct N { N* ch[26] = {}; int end = 0, pref = 0; };
    N* root = new N();
    void insert(const string& s) {
        N* t = root;
        for (char c : s) {
            int i = c - 'a';
            if (!t->ch[i]) t->ch[i] = new N();
            t = t->ch[i]; t->pref++;
        }
        t->end++;
    }
    bool search(const string& s) {
        N* t = root;
        for (char c : s) { int i = c - 'a'; if (!t->ch[i]) return false; t = t->ch[i]; }
        return t->end > 0;
    }
    bool startsWith(const string& s) {
        N* t = root;
        for (char c : s) { int i = c - 'a'; if (!t->ch[i]) return false; t = t->ch[i]; }
        return true;
    }
};

// 2. Binary trie (XOR)
struct BinTrie {
    struct N { N* ch[2] = {}; };
    N* root = new N();
    void ins(int x) {
        N* t = root;
        for (int b = 31; b >= 0; b--) {
            int bit = (x >> b) & 1;
            if (!t->ch[bit]) t->ch[bit] = new N();
            t = t->ch[bit];
        }
    }
    int maxXor(int x) {
        N* t = root; int ans = 0;
        for (int b = 31; b >= 0; b--) {
            int bit = (x >> b) & 1;
            if (t->ch[bit ^ 1]) { ans |= 1 << b; t = t->ch[bit ^ 1]; }
            else t = t->ch[bit];
        }
        return ans;
    }
};

// 3. Distinct substrings (count new nodes over all suffixes)
long long distinctSubstrings(const string& s) {
    Trie t; long long cnt = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        Trie::N* node = t.root;
        for (int j = i; j < (int)s.size(); j++) {
            int c = s[j] - 'a';
            if (!node->ch[c]) { node->ch[c] = new Trie::N(); cnt++; }
            node = node->ch[c];
        }
    }
    return cnt;
}
```

## 13. ADVANCED CONCEPTS

### 13.1 Trie memory considerations
Each node = 26 pointers (208 bytes on 64-bit) — huge for big dictionaries. Optimizations: **pointer compression** (only allocate children present, `map`/sorted small array), **array pools** (allocate nodes from one block for cache + bulk free), **radix/compact tries** (compress single-child chains into labeled edges).

### 13.2 Aho-Corasick (multi-pattern matching)
Trie + failure links (KMP-style) → match *many* patterns in one text pass `O(text + matches)`. The "trie version of KMP" — mention when asked about dictionary matching at scale.

### 13.3 Suffix trie / suffix tree
Insert all suffixes (compressed) → substring membership, LCP queries, longest common substring in `O(m)`. Ukkonen's algorithm builds suffix trees in `O(n)` — awareness-level for interviews.

### 13.4 Ternary search tries (TST)
Balances memory vs speed: each node has 3 children (`<`, `=`, `>`) — used in real-world string dictionaries (Java's TreeMap alternatives).

### 13.5 Bitwise tries beyond XOR
XOR/AND/OR "convolution-like" queries via bit tries; finding `max (a[i] & x)`, `max (a[i] | x)` variants — same greedy descent with different preference rules per bit.

### 13.6 Trie + DP
Concatenate words / word break with trie: walk dictionary trie while scanning the string — combines §16 word-break DP with `O(L)` dictionary steps instead of hash-set slicing.

---

## 14. CONNECTIONS BETWEEN PATTERNS

```text
Strings (§05)
   |
   +--> exact match, no prefix need ------> unordered_set (hash)
   |
   +--> PREFIX semantics ----------------> TRIE
   |        |
   |        +--> counts (end/pref) ------> autocomplete / replace words
   |        +--> DFS over children ------> longest word / collect suggestions
   |        +--> insert all suffixes ----> distinct substrings
   |        +--> + backtracking DFS -----> word search on boards (§07)
   |
   +--> pattern-in-text (matching) ------> KMP / Z (§05)   [not a trie job]
   |
Bits (§08)
   +--> trie over 32 bits --------------> binary trie ----> XOR maximization
                                              |
                                              +--> offline sweep (sort + insert)
                                              +--> segment-tree-of-tries (advanced)
```

**Mental map** — prefix → trie · XOR extremum → binary trie · many words on grid → trie + DFS · exact-only → hash · huge alphabet → map children.

---

## 15. PROBLEM → PATTERN MAPPING

*(Reference only — solutions and approaches live in the `.cpp` files.)*

### Dictionary trie (insert / search / prefix counts)
- `01-Implement-Trie-I.cpp`
- `02-Implement-Trie-II.cpp`

### Prefix aggregation / longest word chain
- `03-Longest-Word-With-All-Prefixes.cpp`

### Counting structures (distinct substrings)
- `04-Number-of-Distinct-Substrings.cpp`

### Binary trie (XOR)
- `05-Bit-Prefix-Max-XOR.cpp`
- `06-Maximum-XOR-Two-Numbers.cpp`
- `07-Offline-XOR-Queries.cpp`

---

## 16. QUICK REVISION SHEET

**Concepts**
- Trie = paths as strings; `O(L)` per op independent of N; prefixes shared.
- `end` = words terminating; `pref` = words passing through — different queries need different flags.
- Binary trie: MSB-first greedy — always take the opposite bit for max XOR (`2^b` dominates lower bits).
- Distinct substrings = nodes created by inserting all suffixes.

**Recognition clues**
| Signal | Tool |
|---|---|
| prefix counts / autocomplete | trie `pref` + DFS |
| dictionary with counts | `end`/`pref` counters |
| distinct substrings | suffix insertion, count new nodes |
| max XOR pair/query | binary trie opposite-bit |
| XOR queries with bound m | offline sort + sweep insert |
| all dictionary words on board | trie + backtracking DFS |
| exact match only | `unordered_set` (simpler) |

**Formulas**
```text
op cost:        O(L) per insert/search/prefix
maxXor:         per bit b: take bit^1 if exists, gain 2^b
nodes:          <= total characters inserted
distinct subs:  # nodes over all suffixes  = n(n+1)/2 - sum(LCP)
```

**Complexity** — ops `O(L)` · XOR ops `O(32)` · max over n `O(32n)` · distinct substrings `O(n²)`.

**Common mistakes** — missing `end` check · `pref`/`end` mixup · null child before create · LSB-first · `1<<31` signed · not counting only *new* nodes · memory blowup (26 pointers).

**Decision rules** — prefix → trie · XOR → binary trie · exact → hash · big alphabet → map children · grid words → trie+DFS.

---

## 17. INTERVIEW CHECKLIST

- [ ] Can I write insert/search/startsWith from memory?
- [ ] Can I explain when a trie beats a hash map (and when it doesn't)?
- [ ] Can I count words vs prefixes with `end`/`pref` correctly?
- [ ] Can I derive the binary-trie XOR greedy and justify MSB-first?
- [ ] Can I compute distinct substrings by counting new nodes?
- [ ] Can I handle empty strings, duplicates, and falling off the trie?
- [ ] Can I state memory implications and the pointer-compression fix?
- [ ] Can I apply the offline sweep pattern to bounded XOR queries?
- [ ] Can I combine trie + backtracking for multi-word board search?
- [ ] Can I quote `O(L)` / `O(32)` complexities precisely?

<!-- done -->
