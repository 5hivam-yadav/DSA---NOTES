# Sorting — Revision & Pattern Recognition

## Recognition map

| Signal | Pattern / decision |
|---|---|
| Need ordered data, rank, intervals, or a two-pointer scan | Sort first; sorting often simplifies the invariant to a single sweep. |
| Need a specific order across multiple keys | Custom comparator; compare primary key, then tie-breakers. |
| Values are only `0`, `1`, `2` | Dutch National Flag, three regions, one pass. |
| Need inversion/reverse-pair counts while ordering | Merge sort; count cross pairs during merge. |
| Need only kth or top `k`, not a full order | `nth_element`, partial sort, or heap. |
| Need a stable order | `stable_sort`, or use a stable algorithm such as merge sort. |

## Core decisions

- `std::sort` is the default for full ordering: `O(n log n)` time. It is not stable.
- Selection sort: `O(n²)` comparisons, at most `n-1` swaps; useful for learning or minimizing writes.
- Bubble sort: stable when swapping only on `>`, adaptive with early exit; worst `O(n²)`.
- Insertion sort: stable and adaptive; good for tiny or nearly sorted inputs; worst `O(n²)`.
- Merge sort: stable `O(n log n)`, requires `O(n)` auxiliary memory for arrays.
- Quick sort: average `O(n log n)`, worst `O(n²)`; pivot/partition choice matters. `std::sort` avoids this worst case with introsort.

## Patterns to retrieve

### Sort then scan

Sort, then use adjacent comparisons or two pointers. Sorting costs `O(n log n)`; subsequent scan is usually `O(n)`. Use when original order is irrelevant or can be restored with indexed pairs.

### Comparator

Comparator must define a strict weak ordering: use `a.key < b.key`; for ties compare the next key. Avoid `<=` and inconsistent tie rules.

### Dutch National Flag

Maintain `[0, lo)` = low, `[lo, mid)` = middle, `(hi, n)` = high. While `mid <= hi`: low swaps with `lo` and advances both; middle advances `mid`; high swaps with `hi` and only decrements `hi` (reinspect the incoming value). `O(n)` time, `O(1)` space.

### Merge-based counting

During merge, when `right[j] < left[i]`, all remaining left values form cross inversions: add `mid - i + 1`. Use strict comparison for inversions and a 64-bit counter. `O(n log n)` time, `O(n)` space.

### Partial ordering

For kth element use `nth_element` (average `O(n)`); for sorted smallest `k`, use `partial_sort` (`O(n log k)`) or a size-`k` heap (`O(n log k)`). Define whether `k` is zero- or one-based.

## Common traps

- Sorting changes positions: retain original indices if the answer refers to them.
- Equal keys need deliberate stable/tie behavior.
- In binary search after sorting, prove duplicate and boundary handling.
- Stability means equal-key input order is preserved; in-place and stable are separate properties.
- Test empty, singleton, sorted, reverse-sorted, all-equal, and duplicate-heavy input.

## Solve workflow

Choose the minimum ordering information needed, state the sorted/partition invariant, and account for both the sort and the follow-up scan.
