# Arrays and Matrices (Traversal, Two Pointers, Prefix, Kadane, Matrix) — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — One-pass traversal with running state

**What is the pattern?**

Answer from a single left-to-right scan while retaining only the facts needed by the next element.

**When should I recognize it?**

The question mentions count, check sortedness, maximum, minimum, second extreme, leaders, or consecutive runs. If only a few aggregate facts matter, do not store the whole answer.

**Core intuition**

At position `i`, keep the best information seen in `0..i`; update it, then decide whether the current element matters.

**General approach**

1. Initialise the state from the first element.
2. Read each element once.
3. Update the relevant aggregate.
4. Return the state requested by the problem.

**Generic algorithm**

`state = initialise(a[0]); for i = 1..n-1: state = combine(state, a[i]);`

**Edge cases**

Empty input; one element; all duplicates; every value negative; `INT_MIN`; requiring distinct or non-distinct extremes.

**Common mistakes**

Initialising the maximum to `0`, updating the second maximum before moving the first, and allowing duplicates into the second maximum.

**Variations**

Running parity/XOR; prefix maxima; suffix minima; count runs; finding leaders; rotating by one.

### P2 — Frequency counting and hashing

**What is the pattern?**

Count occurrences first, then answer questions about duplicates, membership, or complementary values.

**When should I recognize it?**

The statement asks for duplicates, frequencies, a value seen before, pairs with a given sum, or a set of missing values.

**Core intuition**

A frequency table turns "have I seen this before?" from a scan into a lookup.

**General approach**

Choose a frequency array when values are small and bounded; otherwise use a hash map. Insert only after answering the current lookup when the current element must not match itself.

**Generic algorithm**

`frequency.clear(); for x in a: query(frequency); frequency[x]++;`

**Edge cases**

Empty input; duplicate values; values outside the frequency-array range; `x + y == 2*x`; overflow in `x + y`.

**Common mistakes**

Querying after insertion (counts a value with itself) and assuming unordered containers are worst-case `O(1)`.

**Variations**

First missing positive; repeated and missing numbers; majority; longest consecutive sequence; subarray sum maps; anagrams.

### P3 — Two pointers on sorted input

**What is the pattern?**

Two indices move from opposite ends, eliminating an entire range of candidates at each step.

**When should I recognize it?**

The array is sorted, and the task concerns pair sums, palindromes, comparison-based counting, or partitioning.

**Core intuition**

If the sum is too small, the left value cannot help with any still-larger right value; if too large, the right value cannot help with any still-larger left value.

**General approach**

1. Sort if the array is not already sorted.
2. Set `left = 0`, `right = n - 1`.
3. Compare the current pair with the target.
4. Move one or both pointers.
5. Stop when `left >= right`.

**Generic algorithm**

`sort(a); l=0; r=n-1; while(l<r) { evaluate(a[l],a[r]); adjust(l,r); }`

**Edge cases**

Single element; target smaller/larger than all sums; duplicate values; needing index pairs; count with long sums.

**Common mistakes**

Forgetting to sort, using `a[l] + a[r]` in `int`, and counting the current element instead of the whole `r-l` range.

**Variations**

Pair sum; three/four sum by fixing one/two values; palindrome; partition; closest pair; merge two sorted arrays; inverse pairs.

### P4 — Prefix sums and prefix-value maps

**What is the pattern?**

Precompute cumulative information so a range sum becomes subtraction, or a needed sum becomes a lookup.

**When should I recognize it?**

The task asks about a subarray sum, XOR, product, or a range without changing the input.

**Core intuition**

A prefix stores the relationship between the current accumulated value and earlier positions.

**General approach**

For range sums, build `prefix[i+1] = prefix[i] + a[i]`. For subarrays equal to `k`, use `seen[prefixBefore]`, starting with `seen[0] = 1`.

**Complexity, edge cases, and mistakes**

`O(n)` time and space. Query `[l, r]` as `p[r+1] - p[l]`. Watch `n = 0`, overflow, and insertion order: increment a prefix only after querying it.

**Variations and practice mapping**

Range sums, subarray sum, prefix XOR: `13-Longest-Subarray-Sum-K.cpp`, `26-Count-Subarrays-Sum-K.cpp`, `33-Largest-Subarray-Sum-0.cpp`, `34-Count-Subarrays-Given-XOR-K.cpp`.

### P5 — Kadane and maximum-subarray variants

**What is the pattern?**

Keep the best subarray ending at the current index and reset when keeping the previous run is harmful.

**When should I recognize it?**

The question seeks a contiguous maximum/minimum sum, sometimes with a length constraint.

**Core intuition**

At each element, either start a new subarray or extend the best one ending immediately before it.

**Complexity, edge cases, and mistakes**

`O(n)` time, `O(1)` space. Initialise from `a[0]`, not zero, so all-negative input is handled. The maximum-product variant must track the smallest product as well as the largest.

**Variations and practice mapping**

Circular subarrays and maximum product: `17-Maximum-Subarray-Kadane.cpp`, `18-Buy-Sell-Stock-I.cpp`, `40-Maximum-Product-Subarray.cpp`.

### P6 — Dutch National Flag and in-place partitioning

**What is the pattern?**

Divide an unsorted range into regions using three boundaries, without extra memory.

**When should I recognize it?**

Values belong to a small known set, such as `0`, `1`, `2` or negative/zero/positive.

**Core intuition**

`[0, low)` is correct, `[low, i)` is zero, `[i, high)` is unknown, and `(high, n)` is correct.

**Complexity, edge cases, and mistakes**

`O(n)` time, `O(1)` space. Do not advance `i` after swapping with `high`; the element from the unknown region has not been classified.

**Variations and practice mapping**

Sign partition, first/last occurrence of each value: `08-Move-Zeros-to-End.cpp`, `15-Sort-Colors-012.cpp`, `19-Rearrange-by-Sign.cpp`.

### P7 — Majority element and voting

**What is the pattern?**

Cancel pairs of unequal values; a value appearing more than half the time survives.

**When should I recognize it?**

The frequency threshold is strictly greater than `n/2`, so only one candidate can exist.

**Complexity, edge cases, and mistakes**

Two `O(n)` scans, `O(1)` space. A general problem asking for a value occurring more than `n/3` needs at most three candidates. Verify a general majority candidate with a second pass.

**Variations and practice mapping**

General majority and `n/3` variants: `16-Majority-Element-n2.cpp`, `30-Majority-Element-n3.cpp`.

### P8 — In-place rearrangement

**What is the pattern?**

Use reversal or a write index to rearrange an array with `O(1)` extra space.

**When should I recognize it?**

Rotate, reverse, separate positive/negative values, or move zeros; no relative order must be preserved unless requested.

**Complexity, edge cases, and mistakes**

`O(n)` time, `O(1)` space. Decide whether stability is required before using an in-place method. For rotations, validate `k %= n` before indexing.

**Variations and practice mapping**

Rotate by one/by `d`, move zeros, reverse pairs: `06-Left-Rotate-by-One.cpp`, `07-Left-Rotate-by-D.cpp`, `08-Move-Zeros-to-End.cpp`, `19-Rearrange-by-Sign.cpp`, `39-Reverse-Pairs.cpp`.

### P9 — Merge-based counting

**What is the pattern?**

Count cross-half ordered pairs while merging two sorted halves, instead of enumerating every pair.

**When should I recognize it?**

The statement counts inversions or reverse pairs.

**Core intuition**

If `a[i] <= a[j]`, the right half contributes no new inversions with `a[i]`; otherwise it contributes `mid - i + 1`.

**Complexity, edge cases, and mistakes**

`O(n log n)` time, `O(n)` buffer. Use `<=` to exclude equal values from strict inversions and a 64-bit counter.

**Variations and practice mapping**

`36-Merge-Sorted-Arrays.cpp`, `38-Count-Inversions.cpp`, `39-Reverse-Pairs.cpp`.

### P10 — Intervals and ranges

**What is the pattern?**

Sort intervals by start, then sweep while tracking the furthest endpoint reached.

**When should I recognize it?**

The task asks to merge, insert, or count overlapping or non-overlapping intervals.

**Core intuition**

After sorting by start, all currently connected intervals form a chain.

**Complexity, edge cases, and mistakes**

`O(n log n)` time; sorting dominates. Decide whether touching intervals (`next.start == right`) overlap.

**Variations and practice mapping**

`35-Merge-Overlapping-Intervals.cpp`.

### P11 — Matrix traversal and transformation

**What is the pattern?**

Use coordinate loops, shrinking boundaries, or transpose-plus-reverse to traverse or transform a matrix.

**When should I recognize it?**

The input is a matrix and the task mentions rows, columns, rotation, spiral order, or setting zeroes.

**Complexity, edge cases, and mistakes**

Every cell is visited once: `O(r*c)` time, `O(1)` auxiliary space excluding output. Guard every boundary so a last row or column is not visited twice. Assume rectangular input unless stated otherwise.

**Variations and practice mapping**

`23-Set-Matrix-Zeroes.cpp`, `24-Rotate-Matrix-90.cpp`, `25-Spiral-Matrix.cpp`, `27-Pascals-Triangle-Variant1.cpp`, `28-Pascals-Triangle-Variant2.cpp`, `29-Pascals-Triangle-Variant3.cpp`.

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
