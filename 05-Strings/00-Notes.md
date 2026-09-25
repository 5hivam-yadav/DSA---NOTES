# 05 — Strings — Complete Pattern-Based Notes

---

## 1. Topic Overview

A **string** is an array of characters — but character data brings its own universe: ASCII/Unicode encodings, substring structure, pattern matching, and palindromes.

**What it is**
A contiguous sequence of characters. In C++, `std::string` is a dynamic contiguous buffer with `O(1)` indexed access and `O(n)` concatenation.

**Why it is important**
- Text processing underlies parsing, searching, compression, and compilers.
- Strings are the classic vehicle for **frequency counting**, **two pointers**, **stack/depth**, and **pattern matching** (KMP/Z/Rabin-Karp) patterns.
- Interview favorites: anagrams, palindromes, longest substring without repeats, pattern search, prefixes.

**Where it is used**
- Anagram/isomorphic validation → frequency maps.
- Palindrome checks → two pointers.
- Bracket/depth problems → stack simulation.
- Pattern search → KMP, Z-algorithm, rolling hash.
- Prefix problems → Trie (§17), LPS arrays.

**How it connects to other topics**
- §03 Arrays: almost every array pattern transfers directly (two pointers, sliding window, prefix).
- §09 Stack: parentheses and nesting are string problems solved with a stack.
- §10 Sliding Window: longest substring problems are window problems over characters.
- §17 Trie: prefix structures for dictionaries.

**Interview memory hook:** *Anagram → count. Palindrome → two pointers. Nesting → depth/stack. "Find pattern in text" → KMP / Z / rolling hash.*

---

## 2. Fundamentals

### 2.1 Characters, ASCII, and indexing

- Every `char` is a small integer. Lowercase `a-z` → 97–122, uppercase `A-Z` → 65–90, digits `0-9` → 48–57.
- `c - 'a'` maps a lowercase letter to `0..25` — the basis of 26-slot frequency arrays.
- `s.size()` returns `size_t` (unsigned) — `for (int i = s.size() - 1; i >= 0; i--)` **never terminates** on empty strings; cast to `int` first.

### 2.2 Core vocabulary

| Term | Meaning | Example |
|---|---|---|
| **Substring** | Contiguous slice | `"bcd"` of `"abcde"` |
| **Subsequence** | Ordered, gaps allowed | `"ace"` of `"abcde"` |
| **Anagram** | Same multiset of characters | `"listen"` / `"silent"` |
| **Palindrome** | Reads same forwards & backwards | `"racecar"` |
| **Prefix / Suffix** | Start / end slice | `"ab"` / `"de"` of `"abcde"` |
| **LPS** | Longest proper prefix = suffix | of `"ababa"` → `"aba"` |
| **Rolling hash** | Fingerprint of a substring, updated incrementally | Rabin-Karp |

### 2.3 String as a two-pointer playground

```text
s = "a b c b a"
     l       r     l<r: compare, move inward
       l   r       mismatch -> not palindrome
```

Two pointers solve palindrome checks, in-place reversals, and word processing in `O(n)` time / `O(1)` extra space.

### 2.4 Frequency counting on strings

```text
"abracadabra"
 count['a']=5, 'b'=2, 'r'=2, 'c'=1, 'd'=1
```

Use `int cnt[26] = {}` when the alphabet is known (26 lowercase), `unordered_map<char,int>` otherwise. Sorting the string is the `O(n log n)` alternative that often simplifies comparisons (`s == t` after sort).

---

## 3. Core Concepts

### 3.1 Frequency / Map-based string checks (anagram, isomorphic)

**Definition**  \nTwo strings are anagrams iff their character multisets match. Two strings are isomorphic iff characters can be mapped one-to-one preserving positions.

**Intuition**  \nAnagram = "same bag of letters" → compare counts. Isomorphic = "consistent renaming" → record the mapping in **both** directions while scanning.

**How it works**
- Anagram: count 26 chars of both, compare arrays — or sort and compare strings.
- Isomorphic: `mapS[t[i]] = s[i]` style maps in both directions; if a stored mapping disagrees → false. Both maps are needed: `egg`/`add` fails with one map.

**Complexity**  \nCounting `O(n)`; sorting `O(n log n)`. Space `O(1)` (26) or `O(k)` distinct chars.

**Common mistake**  \nChecking only one direction of the isomorphic mapping (`foo`/`bar` would wrongly pass with a single map).

---

### 3.2 Palindrome two pointers

**Definition**  \nVerify or construct a palindrome by advancing two pointers inward (or outward from a center).

**Intuition**  \n`s[l] == s[r]` must hold for *every* mirrored pair; the first mismatch decides.

**Patterns**
- **Verify**: `l = 0, r = n-1`, move inward — `O(n)`.
- **Longest palindromic substring**: expand around each center (`2n-1` centers) — `O(n^2)`.
- **Minimum insertions to palindrome** = `n - length of longest palindromic subsequence`.

**Common mistakes**  \nOdd/even center handling; forgetting `l < r` bounds; assuming a palindrome is always even-length.

---

### 3.3 Depth-based parenthesis processing

**Definition**  \nBracket/nesting problems are solved by a running **depth** counter or an explicit stack.

**Intuition**  \n`(` increments depth, `)` decrements. Depth tells you what is "outermost": characters spanning depth `0 → max` are outermost and can be removed.

**How it works**

```text
"(()())()"
 depth: 1 2 1 2 1 0 1 0
 keep chars strictly between the depth-0 boundaries
```

**Variations**
- Valid parentheses → stack of expected closers.
- Max nesting depth → track running max of depth.
- Remove outermost → keep only chars with depth in `(0, maxDepth)`.

**Complexity**  \n`O(n)` time, `O(n)` stack (or `O(1)` with a pure depth counter).

---

### 3.4 Word / token processing (reverse words, reverse each word)

**Definition**  \nSplit on spaces, process each token (reverse, trim), rejoin.

**Intuition**  \nTwo levels of two pointers: word boundaries first, then characters inside each word.

**Common mistakes**  \nLeading/trailing/multiple spaces — normalize by trimming; C++ `stringstream >> word` naturally collapses repeated spaces.

---

### 3.5 Pattern matching: KMP, Z-algorithm, Rabin-Karp

**Definition**  \nFind occurrences of pattern `p` in text `t` without naive `O(n·m)` rescanning.

| Algorithm | Key idea | Preprocess | Match |
|---|---|---|---|
| **KMP** | LPS array: on mismatch, jump to longest proper prefix = suffix | `O(m)` | `O(n)` |
| **Z-algorithm** | `z[i]` = longest substring starting at `i` matching prefix | `O(n+m)` | `O(n)` |
| **Rabin-Karp** | Rolling hash of windows; verify on hash match | `O(m)` | `O(n)` avg |

**Intuition (LPS)**  \nWhen `p[j]` mismatches `t[i]`, we already know `t[i-j..i-1] == p[0..j-1]`. The LPS gives the longest border of that known prefix, so matching resumes there — never re-scanning characters.

**Common mistakes**
- LPS build needs `while (j > 0 && p[i] != p[j]) j = l[j-1];` — dropping `j > 0` loops forever on no-border patterns.
- Rolling hash: negative modulo → add `MOD` before `%`.
- String concatenation in a loop (`s = s + t`) is `O(n^2)` — use `+=` or `stringstream`.

---

## 4. PATTERN LIBRARY

### P1 — Frequency / Count Signature Check

#### What is the pattern?
Reduce both strings to a canonical signature (26-slot count array, or sorted string) and compare.

#### When should I recognize it?
- "Are these two strings **anagrams** / rearrangements of each other?"
- "Group all anagrams", "find the difference", "every character appears same times".

#### Core intuition
Anagram-ness is a property of the *multiset* of characters, not their order — sorting or counting destroys order and exposes the multiset.

#### General approach
1. Quick rejects: different lengths → false.
2. Count 26 frequencies for both (or sort both).
3. Compare signatures.

#### C++ template
```cpp
bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false;
    int cnt[26] = {};
    for (int i = 0; i < (int)s.size(); i++) { cnt[s[i]-'a']++; cnt[t[i]-'a']--; }
    for (int i = 0; i < 26; i++) if (cnt[i]) return false;
    return true;
}
```

#### Time / Space
Counting `O(n)` time, `O(1)` space; sorting `O(n log n)` time, `O(1)`/`O(n)` space.

#### Edge cases
Empty strings (true); length mismatch; Unicode / mixed case (normalize first).

#### Common mistakes
Counting both into separate arrays but comparing wrong indices; assuming equal counts of each char imply isomorphism (it doesn't — need a bijection).

#### Variations
"Group anagrams" → sort-key or count-key as map key; "custom sort by frequency" → count then bucket.

#### Practice mapping
- `07-Valid-Anagram.cpp`, `08-Sort-Characters-by-Frequency.cpp`, `05-Isomorphic-Strings.cpp`

---

### P2 — Two-Pointer Palindrome / Window on String

#### What is the pattern?
`l` from the left, `r` from the right (or both from left for windows); move based on a comparison.

#### When should I recognize it?
- "Is/longest palindrome", "reverse words", "make palindrome with minimum changes", "longest substring with property".

#### Core intuition
Palindrome = mirrored pairs must match; scan inward and stop at the first mismatch. Forwards scans pair with a right pointer guided by a monotone condition.

#### General approach (verify)
1. `l = 0, r = n - 1`.
2. While `l < r`: mismatch → answer decision; else `l++, r--`.

#### C++ template
```cpp
bool isPalindrome(const string& s) {
    int l = 0, r = (int)s.size() - 1;
    while (l < r) { if (s[l++] != s[r--]) return false; }
    return true;
}
```

#### Time / Space
`O(n)` / `O(1)`.

#### Edge cases
Empty / single char (trivially true); even vs odd lengths; non-alphanumeric filtering.

#### Common mistakes
Infinite loop when not advancing both pointers; comparing chars without normalizing case.

#### Variations
Expand-around-center `O(n^2)` for longest palindromic substring; min insertions = `n - LPS-length`.

#### Practice mapping
- `24-Min-Insertions-Palindrome.cpp`, `14-Longest-Palindromic-Substring.cpp`, `19-Shortest-Palindrome.cpp`, `25-Min-Chars-Front-Palindrome.cpp`

---

### P3 — Depth / Stack Simulation for Parentheses

#### What is the pattern?
A running depth counter (or explicit stack) tracks `(`/`)` nesting.

#### When should I recognize it?
- "Remove outermost parentheses", "max nesting depth", "valid parentheses", "reverse substrings between brackets".

#### Core intuition
Depth tells you which characters belong to which nesting level; outermost = the span from depth 0 back to 0.

#### General approach
1. Scan left→right updating depth.
2. Record running max, or push/pop expected closers on a stack.
3. Answer derived from depth profile or stack emptiness.

#### C++ template
```cpp
int maxDepth(const string& s) {
    int d = 0, best = 0;
    for (char c : s) { if (c == '(') best = max(best, ++d); else if (c == ')') d--; }
    return best;
}
```

#### Time / Space
`O(n)` time; `O(1)` with a counter, `O(n)` with a stack.

#### Edge cases
Empty string; unbalanced closers (depth −1); interleaved bracket types (need a stack of expected chars).

#### Common mistakes
Decrementing below zero (invalid input); using a counter where *matching type* matters.

#### Variations
Valid parentheses (stack of expected closers); min insertions to balance (greedy on depth).

#### Practice mapping
- `01-Remove-Outermost-Parentheses.cpp`, `09-Max-Nesting-Depth.cpp`

---

### P4 — Word / Token Processing

#### What is the pattern?
Split into words, transform each (reverse/trim/convert), rejoin — two levels of two pointers.

#### When should I recognize it?
- "Reverse words in a string", "reverse each word", "simplify path", "decode string", "basic calculator".

#### Core intuition
A string is a sequence of *tokens* delimited by spaces (or brackets); process boundaries first, contents second.

#### General approach
1. Skip/normalize delimiters.
2. Mark word start, find word end.
3. Transform the slice (`reverse`, parse).
4. Append with correct separator.

#### C++ template
```cpp
string reverseWords(string s) {
    string out; int n = s.size();
    for (int r = 0; r < n; ) {
        if (s[r] == ' ') { r++; continue; }
        int l = r; while (r < n && s[r] != ' ') r++;
        if (!out.empty()) out += ' ';
        out += s.substr(l, r - l);
    }
    reverse(out.begin(), out.end());   // whole string then per-word — or collect words and reverse order
    return out;
}
```

#### Time / Space
`O(n)` time; `O(n)` for output.

#### Edge cases
Multiple/leading/trailing spaces; single word; empty string; all spaces.

#### Common mistakes
`s.substr` in a loop is fine, but `s = s + t` pattern is quadratic; forgetting separator between words; reversing the whole string without re-reversing words.

#### Variations
Reverse each word in place; parse roman/integer tokens (`10`/`11`/`12` — value + previous-symbol rule).

#### Practice mapping
- `02-Reverse-Words.cpp`, `15-Reverse-Every-Word.cpp`, `10-Roman-to-Integer.cpp`, `11-Integer-to-Roman.cpp`, `12-Implement-Atoi.cpp`, `03-Largest-Odd-Number.cpp`

---

### P5 — Pattern Matching (KMP / Z / Rolling Hash)

#### What is the pattern?
Preprocess the pattern (LPS / Z-array) or fingerprint windows (hash) to find occurrences in `O(n + m)` instead of `O(n·m)`.

#### When should I recognize it?
- "Find all occurrences of `needle` in `haystack`", "count substrings matching pattern", "string rotation", "repeated string match", "longest prefix=suffix".

#### Core intuition
Naive matching re-compares characters KMP already proved equal. LPS/Z encode *how much of the pattern is already matched* so a mismatch jumps to the longest viable restart.

#### General approach (KMP)
1. Build `lps[i]` = longest proper prefix of `p[0..i]` that is also a suffix.
2. Walk text with pointer `j` on pattern; on mismatch `j = lps[j-1]`.
3. `j == m` → match found at `i - m + 1`; `j = lps[j-1]`.

#### C++ template
```cpp
vector<int> lpsBuild(const string& p) {
    vector<int> l(p.size(), 0);
    for (size_t i = 1; i < p.size(); i++) {
        int j = l[i - 1];
        while (j > 0 && p[i] != p[j]) j = l[j - 1];
        if (p[i] == p[j]) j++;
        l[i] = j;
    }
    return l;
}
```

#### Time / Space
KMP: `O(n + m)` time, `O(m)` space (each index entered/exited once). Z: `O(n + m)`. Rabin-Karp: `O(n + m)` average, `O(n·m)` worst (collisions).

#### Edge cases
Pattern longer than text; empty pattern; pattern with no borders (`lps` all 0); hash collisions (verify matches).

#### Common mistakes
Missing `j > 0` guard in LPS build (infinite loop); negative modulo in rolling hash; confusing `lps` of full string vs proper prefix (must be *proper*).

#### Variations
Rotation check: `s` in `t+t`; shortest palindrome (prefix-suffix via LPS on `s + '#' + rev(s)`); repeated string match (search in `s` repeated `n/m + 2` times).

#### Practice mapping
- `16-Find-Index-First-Occurrence-KMP.cpp`, `17-Rabin-Karp.cpp`, `18-Z-Function.cpp`, `19-Shortest-Palindrome.cpp`, `20-Longest-Happy-Prefix.cpp`, `06-Check-Rotated-String.cpp`, `23-Repeated-String-Match.cpp`

---

### P6 — Manual Parsing (finite-state conversion)

#### What is the pattern?
A single scan carries *state* (accumulated value, sign, validity flags) to convert characters → number/structure.

#### When should I recognize it?
- "String to integer (atoi)", "roman to integer", "integer to roman", "version compare", "count and say", "decode string".

#### Core intuition
Parsing = a tiny automaton: read char → update state (value, multiplier, error flags) → move on. Overflow and clamping are part of the spec, not afterthoughts.

#### General approach
1. Skip whitespace; detect optional sign.
2. Accumulate `val = val * 10 + digit` with overflow clamp.
3. Stop at first non-digit; apply clamping to `[INT_MIN, INT_MAX]`.

#### C++ template
```cpp
int myAtoi(const string& s) {
    long v = 0; int i = 0, sign = 1, n = s.size();
    while (i < n && s[i] == ' ') i++;
    if (i < n && (s[i] == '+' || s[i] == '-')) sign = (s[i++] == '-' ? -1 : 1);
    while (i < n && isdigit(s[i])) {
        v = v * 10 + (s[i++] - '0');
        if (sign * v > INT_MAX) return INT_MAX;
        if (sign * v < INT_MIN) return INT_MIN;
    }
    return (int)(sign * v);
}
```

#### Time / Space
`O(n)` / `O(1)`.

#### Edge cases
Empty/whitespace-only; lone sign; leading zeros; overflow mid-parse; input beyond `long long`.

#### Common mistakes
Overflow before clamping (use `long long` intermediate); parsing sign twice; not handling empty result (return 0).

#### Variations
Roman rules (`IV` before `IV` handled by *value + prev* trick); version compare (split on `.` with manual tokenizer); count-and-say (group-run encoding).

#### Practice mapping
- `12-Implement-Atoi.cpp`, `10-Roman-to-Integer.cpp`, `11-Integer-to-Roman.cpp`, `21-Count-and-Say.cpp`, `22-Compare-Version-Numbers.cpp`, `13-Count-Substrings-Beauty.cpp`

---

## 5. PATTERN RECOGNITION

| If the problem says... | Think about... |
|---|---|
| "are they anagrams" / "group anagrams" | Frequency signature (26-count or sort) |
| "two strings map to each other" (isomorphic) | Two-direction mapping check |
| "is palindrome" / "longest palindrome" | Two pointers / expand around center |
| "remove outermost / max nesting / brackets" | Depth counter or stack |
| "reverse words / each word" | Tokenize + two-level two pointers |
| "find pattern in text" / "all occurrences" | KMP / Z / rolling hash |
| "prefix that is also suffix" (LPS) | KMP LPS array |
| "is `s` a rotation of `t`" | `t` is substring of `s+s` |
| "convert string ↔ number / roman" | Manual parsing with state + clamping |
| "count substrings with exactly K beauty" | Sliding window + at-most trick (§10) |
| "longest happy prefix" | Z-array / LPS of the whole string |
| "minimum insertions to make palindrome" | `n - longest palindromic subsequence` (§16) |

**Decision rules**
1. **Equality of character multisets?** → count/sort (never KMP).
2. **Structure with nesting?** → depth/stack.
3. **Locating a pattern occurrence?** → preprocess with LPS/Z (`O(n+m)`).
4. **Transformation of words?** → tokenize, then two pointers.
5. **Order-insensitive comparison?** → signature; **order-sensitive matching?** → KMP/Z.

---

## 6. BRUTE → BETTER → OPTIMAL THINKING

### Anagram check
- **Brute** — generate all permutations of `s`, compare with `t`: `O(n!·n)`. Absurd but "correct".
- **Better** — sort both, compare: `O(n log n)`. Insight: order is irrelevant to anagram-ness.
- **Optimal** — one count array with `++`/`--`: `O(n)` time, `O(1)` space. Alphabet is fixed → counting beats sorting.

### Longest palindromic substring
- **Brute** — check all `O(n²)` substrings: `O(n³)`.
- **Better** — expand around each of `2n-1` centers: `O(n²)` time, `O(1)` space.
- **Optimal** (interview) — Manacher's algorithm `O(n)`; for most interviews `O(n²)` expand is accepted — know Manacher exists and why: reuse mirror information like Z/LPS.

### String matching (find pattern)
- **Brute** — nested loops, re-scan on mismatch: `O(n·m)` worst.
- **Better** — rolling hash windows: `O(n+m)` average, hash collisions remain.
- **Optimal** — KMP (or Z): `O(n+m)` worst case, `O(m)` space — no re-scanning ever, proven by the LPS invariant.

### Longest substring without repeating characters
- **Brute** — all substrings × set check: `O(n²)` (or `O(n³)` naive).
- **Better** — sliding window with frequency map, shrink while invalid: `O(n)`.
- **Optimal** — jump `left = max(left, lastIndex[c]+1)` using a last-seen array: `O(n)`, no while-shrink — same complexity, cleaner constant.

### Key transferable idea
> Strings convert **structure** into **signatures**: multiset → counts, palindrome → mirrored pairs, nesting → depth, matching → LPS. Identify which structure the problem is really about.

---

## 7. C++ / STL TOOLKIT

| Tool | Syntax | Use |
|---|---|---|
| Index access | `s[i]`, `s.at(i)` | `O(1)` (`.at` throws) |
| Size | `s.size()`, `s.length()` | cast to `int` for reverse loops |
| Substring | `s.substr(pos, len)` | copy of slice — `O(len)` |
| Find | `s.find(t)` / `s.rfind(t)` | first/last index or `npos` |
| Append | `s += c; s.push_back(c)` | amortized `O(1)` |
| Compare | `s == t`, `s < t` | lexicographic `O(min(len))` |
| Sort / reverse | `sort(s.begin(), s.end())` | `O(n log n)` / `O(n)` |
| Char classes | `isalpha(c)`, `isdigit(c)`, `tolower(c)` | parsing, normalization |
| Convert | `stoi(s)`, `stoll(s)`, `to_string(x)` | throw / clamp aware |
| Stream split | `stringstream ss(s); ss >> word` | whitespace tokenization |
| Count | `count(s.begin(), s.end(), c)` | `O(n)` |

```cpp
// frequency of lowercase letters
int cnt[26] = {};
for (char c : s) if (islower(c)) cnt[c - 'a']++;

// avoid quadratic building
string out; out.reserve(n);      // preallocate
for (char c : src) out += c;     // amortized O(1)

// split by spaces
stringstream ss(s); string w;
while (ss >> w) { /* process w */ }
```

**Common mistakes**
- `s = s + t` inside a loop → `O(n²)`; use `+=` with `reserve`.
- `for (int i = s.size() - 1; ...)` on unsigned — cast: `(int)s.size()`.
- `s.find` returns `string::npos`, not `-1` (compare with `npos`).
- `stoi` throws on non-numeric / overflow — validate first or use `strtol`.

---

## 8. COMPLEXITY GUIDE

| Operation | Time | Space |
|---|---:|---:|
| `s[i]`, push_back, `+=` (amortized) | `O(1)` | `O(1)` |
| `substr(pos,len)` | `O(len)` | `O(len)` copy |
| `find` (worst) | `O(n·m)` | `O(1)` |
| count / scan | `O(n)` | `O(1)` |
| sort | `O(n log n)` | `O(log n)` stack |
| anagram via counting | `O(n)` | `O(1)` (26) |
| palindrome verify | `O(n)` | `O(1)` |
| KMP build + search | `O(m + n)` | `O(m)` |
| Z-algorithm | `O(n + m)` | `O(n + m)` |
| Rabin-Karp | `O(n + m)` avg | `O(1)` |
| expand-around-center | `O(n²)` | `O(1)` |
| tokenize all words | `O(n)` | `O(n)` |

**How to estimate**
- One pass over the string with `O(1)` work → `O(n)`.
- Nested expansion (center × radius) → `O(n²)`.
- Preprocessing pattern + linear scan → `O(n + m)`.
- Building `m` copies of a string → `O(n·m)` — usually the hidden TLE.

---

## 9. EDGE CASES

- **Empty string** — most formulas still hold (anagram of two empties = true; palindrome = true) but `s[0]` crashes.
- **Single character** — palindrome trivially; longest substring = 1.
- **All identical characters** — windows never shrink; count pairs explode (`n(n-1)/2`).
- **All distinct characters** — windows never invalid; longest = n.
- **Spaces / leading-trailing** — normalize before word logic.
- **Case sensitivity** — `tolower` normalize if the statement implies it.
- **Digits only / non-letters** — `c - 'a'` on `'0'` gives garbage; guard with `isalpha`.
- **Length mismatch** — cheapest anagram reject.
- **Overflow in parsing** — `val*10 + d` can exceed `long long` on adversarial input; clamp inside the loop.
- **`npos` misuse** — `find` failure check forgotten.
- **Pattern longer than text** — matching loops must handle `m > n` without reading past end.

---

## 10. COMMON MISTAKES

| # | Mistake | What goes wrong | Why | How to avoid |
|---|---|---|---|---|
| 1 | `s = s + t` in a loop | `O(n²)` TLE | Immutable-style copy each time | `+=` / `reserve` |
| 2 | `i = s.size() - 1` unsigned | Loop never runs (huge value) | `size_t` wraps below 0 | `int n = (int)s.size()` |
| 3 | One-directional isomorphic map | `foo/bar` passes wrongly | Need bijection | Two maps |
| 4 | `find` == `-1` check | Missed failure | `npos` ≠ `-1` on all platforms | `== string::npos` |
| 5 | LPS without `j > 0` guard | Infinite loop | `l[-1]` / no-progress while | Keep the guard |
| 6 | Not normalizing case/space | False mismatch | Spec ambiguity | `tolower`, trim first |
| 7 | Forgetting final separator | `"ab c"` vs `"abc"` join bugs | Off-by-one in join | Check `out.empty()` |
| 8 | Overflow in `stoi`-like loop | Wrong/clamped value | `val*10+d` exceeds range | `long long` + clamp in-loop |
| 9 | Negative modulo in hash | Negative index into table | C++ `%` keeps sign | `((h % M) + M) % M` |
| 10 | Assuming `substr` is O(1) | Hidden quadratic | It copies | Use indices instead when hot |

**Conceptual mistakes**
- Using KMP when anagram counting suffices (wrong tool; order-insensitive ≠ matching).
- Assuming palindrome must be odd-length — always test both even/odd centers.
- Treating "substring" as "subsequence" — the enumeration differs completely.

---

## 11. IMPORTANT FORMULAS / RULES

```text
Anagram check:          counts equal  ⇔  sorted equal  ⇔  Σ count diffs = 0
Palindrome min insertions (one end)  = n - LPS-length(s)          [prefix match]
Palindrome min insertions (both ends)= n - longest palindromic subsequence  (§16)
Rotation test:          t is substring of s + s
Z[i]:                   longest match of s[i..] with s[0..]
KMP:  j = lps[j-1] on mismatch;  lps[i] = len of longest border of p[0..i]
Rolling hash window:    h -= old * base^(m-1);  h = h * base + new
Count distinct substrings of s = total nodes inserted into trie - 1  (§17)
```

**Rules**
1. First check **length** — cheapest rejection everywhere.
2. Fixed alphabet (26) → prefer `int[26]` over `unordered_map`.
3. "Order doesn't matter" → sort/count; "order matters, locate it" → KMP/Z.
4. Depth/nesting → counter only if bracket *type* doesn't matter; stack if it does.

---

## 12. REUSABLE TEMPLATES

```cpp
// 1. LPS build (KMP core)
vector<int> lpsBuild(const string& p) {
    vector<int> l(p.size(), 0);
    for (size_t i = 1; i < p.size(); i++) {
        int j = l[i - 1];
        while (j > 0 && p[i] != p[j]) j = l[j - 1];
        if (p[i] == p[j]) j++;
        l[i] = j;
    }
    return l;
}

// 2. KMP search — returns starting indices
vector<int> kmpSearch(const string& t, const string& p) {
    vector<int> l = lpsBuild(p), res;
    size_t j = 0;
    for (size_t i = 0; i < t.size(); i++) {
        while (j > 0 && t[i] != p[j]) j = l[j - 1];
        if (t[i] == p[j]) j++;
        if (j == p.size()) { res.push_back((int)(i - j + 1)); j = l[j - 1]; }
    }
    return res;
}

// 3. Anagram check
bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false;
    int cnt[26] = {};
    for (size_t i = 0; i < s.size(); i++) { cnt[s[i]-'a']++; cnt[t[i]-'a']--; }
    for (int i = 0; i < 26; i++) if (cnt[i]) return false;
    return true;
}

// 4. Two-pointer palindrome
bool isPalindrome(const string& s) {
    int l = 0, r = (int)s.size() - 1;
    while (l < r) if (s[l++] != s[r--]) return false;
    return true;
}
```

## 13. ADVANCED CONCEPTS

### 13.1 Aho-Corasick (multiple patterns at once)
Build a trie of all patterns + failure links (KMP's LPS generalized to a tree) → find `k` patterns in one text pass in `O(n + total matches)`. Prerequisite: trie (§17) + KMP LPS idea.

### 13.2 Rabin-Karp with double hashing
Two moduli (e.g. `10^9+7`, `10^9+9`) make collision probability negligible — used for substring equality checks, palindrome lookups, and "count distinct substrings" sanity checks.

### 13.3 Manacher's algorithm
Computes longest palindromic radius for all `2n-1` centers in `O(n)` by exploiting already-computed mirror radii — the same "reuse prefix knowledge" trick as Z/LPS, applied to palindromes.

### 13.4 Suffix array / LCP (beyond this chapter)
For heavy pattern workloads: suffix array + LCP + binary search gives `O((n+m) log n)` multiple-pattern search and solves "distinct substrings" (`n(n+1)/2 - Σ LCP`) in `O(n log n)`. Mentioned for awareness — interviews expect KMP/Z, not suffix arrays.

### 13.5 Trie connection (§17)
Prefix questions ("longest happy prefix", "count words with prefix") are `O(L)` with a trie instead of repeated string scans; distinct substrings = number of trie nodes over all suffixes.

### 13.6 Automaton view of parsing
Atoi/roman/decode-string are finite-state machines; recognizing "input is a stream, output is a running value" lets you write the same shape every time: `state` + `transition` + `accept`.

---

## 14. CONNECTIONS BETWEEN PATTERNS

```text
Array of chars (§03)
    |
    +--> Two pointers  ------> Palindromes, word reversal
    |
    +--> Frequency map --------> Anagram, isomorphic, grouping
    |
    +--> Depth / stack --------> Parentheses, nesting (§09)
    |
    +--> Sliding window (§10) -> Longest substring, at-most-K counts
    |
    +--> Preprocess pattern ----> LPS (KMP) <--> Z-array <--> rolling hash
    |                                  |
    |                                  v
    |                          shortest palindrome / happy prefix
    |
    +--> Trie (§17) ------------> Prefix dictionary, distinct substrings

Signature idea:  multiset -> counts
                nesting   -> depth
                match     -> LPS/Z
                prefix    -> trie
```

**Mental map** — decide in this order:
1. Order-insensitive? → **count/sort**.
2. Structure nesting? → **depth/stack**.
3. Need occurrences of a pattern? → **KMP/Z/hash**.
4. Need prefix-driven answers at scale? → **trie**.
5. Contiguity + constraint on window? → **sliding window (§10)**.

---

## 15. PROBLEM → PATTERN MAPPING

*(Reference only — solutions and approaches live in the `.cpp` files.)*

### Frequency / anagram / isomorphic
- `07-Valid-Anagram.cpp`
- `05-Isomorphic-Strings.cpp`
- `08-Sort-Characters-by-Frequency.cpp`

### Palindromes
- `14-Longest-Palindromic-Substring.cpp`
- `19-Shortest-Palindrome.cpp`
- `24-Min-Insertions-Palindrome.cpp`
- `25-Min-Chars-Front-Palindrome.cpp`

### Parentheses / depth
- `01-Remove-Outermost-Parentheses.cpp`
- `09-Max-Nesting-Depth.cpp`

### Word / token processing
- `02-Reverse-Words.cpp`
- `15-Reverse-Every-Word.cpp`
- `03-Largest-Odd-Number.cpp`
- `04-Longest-Common-Prefix.cpp`

### Prefix / LCP / rotation
- `06-Check-Rotated-String.cpp`
- `20-Longest-Happy-Prefix.cpp`
- `23-Repeated-String-Match.cpp`

### Pattern matching (KMP / Z / hash)
- `16-Find-Index-First-Occurrence-KMP.cpp`
- `17-Rabin-Karp.cpp`
- `18-Z-Function.cpp`

### Parsing / conversion
- `10-Roman-to-Integer.cpp`
- `11-Integer-to-Roman.cpp`
- `12-Implement-Atoi.cpp`
- `21-Count-and-Say.cpp`
- `22-Compare-Version-Numbers.cpp`

### Counting substrings / window-on-string
- `13-Count-Substrings-Beauty.cpp`

---

## 16. QUICK REVISION SHEET

**Concepts**
- String = char array; `c-'a'` indexing; `size()` is unsigned — cast for reverse loops.
- Substring (contiguous) vs subsequence (gaps) — different algorithms entirely.
- Anagram → multiset equality; isomorphic → bijection in **both** directions.

**Recognition clues**
| Signal | Tool |
|---|---|
| anagram / group / signature | count or sort |
| palindrome | two pointers / center expand |
| brackets / nesting | depth counter or stack |
| find pattern in text | KMP / Z / rolling hash |
| prefix = suffix | LPS |
| rotation | `s` in `t+t` |
| convert / parse | state machine + clamp |

**Algorithms**
```text
LPS build:      j=l[i-1]; while(j>0 && p[i]!=p[j]) j=l[j-1]; if(p[i]==p[j]) j++;
KMP:            on mismatch j=lps[j-1]; j==m => match
Z-box:          maintain [l,r] matching prefix
Rolling hash:   h = h*B + c;  subtract old*B^(m-1)
min insert (one end) = n - LPS-length
rotation check = is t substring of s+s
```

**Complexity**
| Task | Time |
|---|---|
| count/scan/palindrome | `O(n)` |
| anagram (count) | `O(n)` |
| sort-based | `O(n log n)` |
| KMP / Z | `O(n+m)` |
| expand center | `O(n²)` |

**Common mistakes**
Quadratic concat · unsigned reverse loop · one-way isomorphic map · LPS guard missing · negative modulo · not normalizing case · `npos` vs `-1`.

**Templates to remember** — `lpsBuild`, `kmpSearch`, `isAnagram` (26-count), `isPalindrome` (two pointers), depth counter for parens.

**Decision rules**
1. Order-insensitive → count/sort. 2. Nesting → depth/stack. 3. Occurrences → KMP/Z. 4. Prefix-heavy → trie (§17). 5. Window constraint → §10.

---

## 17. INTERVIEW CHECKLIST

- [ ] Can I explain substring vs subsequence vs anagram with examples?
- [ ] Can I write the 26-slot anagram check and the two-map isomorphic check?
- [ ] Can I verify a palindrome and expand around centers (odd + even)?
- [ ] Can I compute nesting depth with a counter and validate brackets with a stack?
- [ ] Can I tokenize words and handle multi/leading/trailing spaces?
- [ ] Can I build the LPS array and run KMP without looking it up?
- [ ] Can I explain why KMP is `O(n+m)` (no re-scanning)?
- [ ] Can I handle atoi edge cases (sign, whitespace, overflow clamp)?
- [ ] Can I apply `s+s` rotation trick and `n - LPS` palindrome insertion formula?
- [ ] Can I state complexity and edge cases (empty, single char, all-dup) before coding?

<!-- done -->
