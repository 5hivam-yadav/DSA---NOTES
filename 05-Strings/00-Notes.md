# Strings — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — Frequency / Count Signature Check

**What is the pattern?**

Reduce both strings to a canonical signature (26-slot count array, or sorted string) and compare.

**When should I recognize it?**

- "Are these two strings **anagrams** / rearrangements of each other?"
- "Group all anagrams", "find the difference", "every character appears same times".

**Core intuition**

Anagram-ness is a property of the *multiset* of characters, not their order — sorting or counting destroys order and exposes the multiset.

**General approach**

1. Quick rejects: different lengths → false.
2. Count 26 frequencies for both (or sort both).
3. Compare signatures.

**Time / Space**

Counting `O(n)` time, `O(1)` space; sorting `O(n log n)` time, `O(1)`/`O(n)` space.

**Edge cases**

Empty strings (true); length mismatch; Unicode / mixed case (normalize first).

**Common mistakes**

Counting both into separate arrays but comparing wrong indices; assuming equal counts of each char imply isomorphism (it doesn't — need a bijection).

**Variations**

"Group anagrams" → sort-key or count-key as map key; "custom sort by frequency" → count then bucket.

### P2 — Two-Pointer Palindrome / Window on String

**What is the pattern?**

`l` from the left, `r` from the right (or both from left for windows); move based on a comparison.

**When should I recognize it?**

- "Is/longest palindrome", "reverse words", "make palindrome with minimum changes", "longest substring with property".

**Core intuition**

Palindrome = mirrored pairs must match; scan inward and stop at the first mismatch. Forwards scans pair with a right pointer guided by a monotone condition.

**General approach (verify)**

1. `l = 0, r = n - 1`.
2. While `l < r`: mismatch → answer decision; else `l++, r--`.

**Time / Space**

`O(n)` / `O(1)`.

**Edge cases**

Empty / single char (trivially true); even vs odd lengths; non-alphanumeric filtering.

**Common mistakes**

Infinite loop when not advancing both pointers; comparing chars without normalizing case.

**Variations**

Expand-around-center `O(n^2)` for longest palindromic substring; min insertions = `n - LPS-length`.

### P3 — Depth / Stack Simulation for Parentheses

**What is the pattern?**

A running depth counter (or explicit stack) tracks `(`/`)` nesting.

**When should I recognize it?**

- "Remove outermost parentheses", "max nesting depth", "valid parentheses", "reverse substrings between brackets".

**Core intuition**

Depth tells you which characters belong to which nesting level; outermost = the span from depth 0 back to 0.

**General approach**

1. Scan left→right updating depth.
2. Record running max, or push/pop expected closers on a stack.
3. Answer derived from depth profile or stack emptiness.

**Time / Space**

`O(n)` time; `O(1)` with a counter, `O(n)` with a stack.

**Edge cases**

Empty string; unbalanced closers (depth −1); interleaved bracket types (need a stack of expected chars).

**Common mistakes**

Decrementing below zero (invalid input); using a counter where *matching type* matters.

**Variations**

Valid parentheses (stack of expected closers); min insertions to balance (greedy on depth).

### P4 — Word / Token Processing

**What is the pattern?**

Split into words, transform each (reverse/trim/convert), rejoin — two levels of two pointers.

**When should I recognize it?**

- "Reverse words in a string", "reverse each word", "simplify path", "decode string", "basic calculator".

**Core intuition**

A string is a sequence of *tokens* delimited by spaces (or brackets); process boundaries first, contents second.

**General approach**

1. Skip/normalize delimiters.
2. Mark word start, find word end.
3. Transform the slice (`reverse`, parse).
4. Append with correct separator.

**Time / Space**

`O(n)` time; `O(n)` for output.

**Edge cases**

Multiple/leading/trailing spaces; single word; empty string; all spaces.

**Common mistakes**

`s.substr` in a loop is fine, but `s = s + t` pattern is quadratic; forgetting separator between words; reversing the whole string without re-reversing words.

**Variations**

Reverse each word in place; parse roman/integer tokens (`10`/`11`/`12` — value + previous-symbol rule).

### P5 — Pattern Matching (KMP / Z / Rolling Hash)

**What is the pattern?**

Preprocess the pattern (LPS / Z-array) or fingerprint windows (hash) to find occurrences in `O(n + m)` instead of `O(n·m)`.

**When should I recognize it?**

- "Find all occurrences of `needle` in `haystack`", "count substrings matching pattern", "string rotation", "repeated string match", "longest prefix=suffix".

**Core intuition**

Naive matching re-compares characters KMP already proved equal. LPS/Z encode *how much of the pattern is already matched* so a mismatch jumps to the longest viable restart.

**General approach (KMP)**

1. Build `lps[i]` = longest proper prefix of `p[0..i]` that is also a suffix.
2. Walk text with pointer `j` on pattern; on mismatch `j = lps[j-1]`.
3. `j == m` → match found at `i - m + 1`; `j = lps[j-1]`.

**Time / Space**

KMP: `O(n + m)` time, `O(m)` space (each index entered/exited once). Z: `O(n + m)`. Rabin-Karp: `O(n + m)` average, `O(n·m)` worst (collisions).

**Edge cases**

Pattern longer than text; empty pattern; pattern with no borders (`lps` all 0); hash collisions (verify matches).

**Common mistakes**

Missing `j > 0` guard in LPS build (infinite loop); negative modulo in rolling hash; confusing `lps` of full string vs proper prefix (must be *proper*).

**Variations**

Rotation check: `s` in `t+t`; shortest palindrome (prefix-suffix via LPS on `s + '#' + rev(s)`); repeated string match (search in `s` repeated `n/m + 2` times).

### P6 — Manual Parsing (finite-state conversion)

**What is the pattern?**

A single scan carries *state* (accumulated value, sign, validity flags) to convert characters → number/structure.

**When should I recognize it?**

- "String to integer (atoi)", "roman to integer", "integer to roman", "version compare", "count and say", "decode string".

**Core intuition**

Parsing = a tiny automaton: read char → update state (value, multiplier, error flags) → move on. Overflow and clamping are part of the spec, not afterthoughts.

**General approach**

1. Skip whitespace; detect optional sign.
2. Accumulate `val = val * 10 + digit` with overflow clamp.
3. Stop at first non-digit; apply clamping to `[INT_MIN, INT_MAX]`.

**Time / Space**

`O(n)` / `O(1)`.

**Edge cases**

Empty/whitespace-only; lone sign; leading zeros; overflow mid-parse; input beyond `long long`.

**Common mistakes**

Overflow before clamping (use `long long` intermediate); parsing sign twice; not handling empty result (return 0).

**Variations**

Roman rules (`IV` before `IV` handled by *value + prev* trick); version compare (split on `.` with manual tokenizer); count-and-say (group-run encoding).

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
