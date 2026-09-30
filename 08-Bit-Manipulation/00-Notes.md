# Bit Manipulation — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — Bit Test / Set / Clear / Toggle (flags & masks)

**What is the pattern?**

One mask + one operator modifies or queries a single bit in `O(1)`.

**When should I recognize it?**

- "Check if k-th bit is set", "turn feature on/off", state stored in an integer flag.
- Small sets (`n ≤ 20`) encoded as masks.

**Core intuition**

Bitwise operators act on all 32 bits in parallel; masking isolates the one you care about.

**Generic algorithm**

```text
test:   (x >> k) & 1
set:    x |  (1 << k)
clear:  x & ~(1 << k)
toggle: x ^  (1 << k)
```

**Time / Space**

`O(1)` / `O(1)` (hardware level).

**Edge cases**

`k ≥ 32` (UB); sign bit; `k = 31` on signed int.

**Common mistakes**

`1 << 31` overflows signed int → `1U << k` or `1LL << k`.

**Variations**

`x & (-x)` isolates the lowest set bit (used in Fenwick trees / subset loops).

### P2 — `x & (x-1)` Tricks (power of two, popcount)

**What is the pattern?**

Clear the lowest set bit repeatedly to count bits, or once to test power-of-two.

**When should I recognize it?**

- "Count set bits / number of 1s", "is power of 2", "bit flips needed".

**Core intuition**

`x-1` flips the lowest 1→0 and trailing 0→1; AND with `x` deletes exactly that lowest 1.

**Generic algorithm**

```text
isPow2:  x > 0 && (x & (x - 1)) == 0
popcnt:  c = 0; while (x) { x &= x - 1; c++; }
flips:   popcount(a ^ b)
```

**Time / Space**

`O(popcount)` ≤ `O(32)` / `O(1)`.

**Edge cases**

`x = 0`: `x & (x-1)` is 0 but `0` is **not** a power of 2 → check `x > 0`. Negative `x`.

**Common mistakes**

Forgetting `x > 0`; using it on negatives (two's complement surprises).

**Variations**

`__builtin_popcount` (GCC) is a single instruction; Brian Kernighan's loop avoids it.

### P3 — XOR Cancellation (single / pairs / groups)

**What is the pattern?**

XOR every element (or every bit count mod K) so duplicates annihilate.

**When should I recognize it?**

- "Every element appears twice except one", "two elements appear once", "appears three times except one", "find the odd one out".

**Core intuition**

`a ^ a = 0`, `a ^ 0 = a`, XOR is order-independent → all paired values vanish.

**Generic algorithm**

```text
single among pairs:    x = XOR(all)
two singles:           x = XOR(all); pick any set bit of x; XOR each group
single among triples:  per-bit counts mod 3 -> assemble
```

**Time / Space**

`O(n)` / `O(1)`.

**Edge cases**

Empty array (0); single element (itself; note `1^2 = 3` for two singles — must partition!).

**Common mistakes**

Stopping at "XOR all" for *two* singles; sign-bit handling when splitting groups.

**Variations**

Single II (mod 3), Single III (partition by differing bit), XOR of ranges (`0^1^…^n` cycle of 4).

### P4 — Bitmask Subset Enumeration

**What is the pattern?**

Iterate integers `0 .. 2^n-1`; bit `i` of the mask = "include element i" — instantly enumerates every subset.

**When should I recognize it?**

- "Generate power set", "all subsets" with `n ≤ 20`, "partition into two subsets minimizing difference", "TSP over subsets", "DP over subsets".

**Core intuition**

There are exactly `2^n` n-bit patterns ↔ `2^n` subsets — the integers *are* the subsets.

**Generic algorithm**

```text
for mask in 0 .. (1<<n)-1:
    for i in 0..n-1: if mask>>i & 1 -> element i in subset
    process
```

**Time / Space**

`O(2^n · n)` / `O(n)` (or `O(1)` if processing inline).

**Edge cases**

`n = 0` (empty subset only); `n = 31` (overflow — `1 << 31` UB; use `1LL`); all-zero mask.

**Common mistakes**

`1 << n` signed overflow; iterating members with wrong shift precedence (`mask >> i & 1` is fine — `>>` binds tighter than `&`).

**Variations**

Submask iteration `sub = (sub-1) & mask`; recursion equivalent = §07 pick/not-pick; DP over subsets = §16 advanced.

### P5 — Shifts as Arithmetic (multiply/divide/power without operators)

**What is the pattern?**

`<<` multiplies by powers of two, `>>` divides; repeated doubling/halving implements `*`, `/`, `pow`.

**When should I recognize it?**

- "Divide two integers without `*`, `/`, `%`", "power without `pow`", "multiply by 3/5 tricks", constraints demanding bit ops.

**Core intuition**

`x << k = x · 2^k`; division = greedily subtract the largest fitting shifted divisor and set quotient bits.

**Generic algorithm (divide)**

```text
sign = sign(a) ^ sign(b);  a=|a|, b=|b|
q = 0
for bit from 31..0:  if (a - (b<<bit) >= 0) { a -= b<<bit; q |= 1<<bit; }
return sign ? -q : q     (clamp to INT range)
```

**Time / Space**

`O(32)` / `O(1)`.

**Edge cases**

`INT_MIN / -1` (overflow clamp); `b = 0` (undefined/handle); `a < b` (q = 0); `b << 31` overflows long if b large — guard shifts.

**Common mistakes**

Forgetting sign handling; `b << i` overflow when `b` is large (compare in `long long`); missing INT_MIN special case.

**Variations**

Fast power by repeated squaring (§07); modulo via repeated subtraction (slow — prefer `%`).

### P6 — Sieve & Number-Theoretic Bit Tricks

**What is the pattern?**

Mark composites with bit/bool arrays for `O(n log log n)` primality, or use masks to enumerate divisors/multiples.

**When should I recognize it?**

- "Count primes / list primes ≤ n", "check prime quickly", "all divisors", "prime factorization".

**Core intuition**

Every composite `≤ n` has a prime factor `≤ √n` — mark multiples of each prime starting from `p²`.

**Generic algorithm (sieve)**

```text
isPrime[0..n] = true
for p = 2 .. sqrt(n): if isPrime[p]: for multiple = p*p; <= n; += p: isPrime[multiple] = false
```

**Time / Space**

Sieve `O(n log log n)` / `O(n)`; trial division `O(√n)` per query.

**Edge cases**

`n < 2` (no primes); `p*p` overflow (use `long long`); even numbers (skip).

**Common mistakes**

Starting multiples at `2p` instead of `p²` (waste, not wrong); `sqrt` in loop condition recomputed — precompute `p*p <= n`.

**Variations**

Linear sieve (Euler) `O(n)`; divisor enumeration by `i` up to `√n` pairing `(i, n/i)`.

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
