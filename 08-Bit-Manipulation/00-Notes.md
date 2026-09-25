# 08 — Bit Manipulation — Complete Pattern-Based Notes

---

## 1. Topic Overview

**Bit manipulation** works directly on the binary representation of integers using AND, OR, XOR, NOT, and shifts.

**What it is**
Each `int` is 32 bits; operators act on all bits simultaneously. Bit tricks give `O(1)`/`O(32)` operations for tests and updates that would otherwise need loops or maps.

**Why it is important**
- Constant-time flags, parity, and power-of-two checks.
- XOR patterns solve "single/duplicate number" and parity problems elegantly.
- Bitmask enumeration connects to subsets, DP over subsets, and TSP-style state.
- Interviewers love `x & (x-1)` — it clears the lowest set bit in one shot.

**Where it is used**
- Single number / appearing-once problems (XOR cancellation).
- Counting set bits, checking odd/even, power of 2.
- Subset enumeration via masks (`0 .. 2^n - 1`).
- Division without `*`, `/`, `%` (shifts).
- Sieve, divisor/prime enumeration (masking multiples).

**How it connects to other topics**
- §07 Recursion: subset generation == iterating masks.
- §16 DP: DP over subsets uses masks as state.
- §15 Graph: visited masks, bipartite coloring with bits.

**Interview memory hook:** *`x & (x-1)` clears lowest set bit. XOR cancels pairs. Mask per bit for mod-3 counts. `1 << n` enumerates subsets.*

---

## 2. Fundamentals

### 2.1 Binary representation

```text
x = 13  ->  ...00001101
 bit index:   3 2 1 0       (LSB = bit 0)
 value:       8+4+0+1 = 13
```

- `x & (1 << k)` ≠ 0 → k-th bit is set.
- `x >> k` shifts right (divides by 2^k); `x << k` shifts left (multiplies by 2^k).
- Negative numbers use **two's complement**: `-x = ~x + 1`.

### 2.2 Core operations

| Operation | Expression | Result on `x = 12 (1100)` |
|---|---|---|
| Check k-th bit | `x & (1 << k)` | `12 & 8 = 8` (set) |
| Set k-th bit | `x \| (1 << k)` | `1100 \| 0100 = 1100` |
| Clear k-th bit | `x & ~(1 << k)` | `1100 & 1011 = 1000` |
| Toggle k-th bit | `x ^ (1 << k)` | flips bit k |
| Clear lowest set bit | `x & (x - 1)` | `1100 & 1011 = 1000` |
| Isolate lowest bit | `x & (-x)` | `1100 & 0100 = 0100` |
| Power of two? | `x > 0 && (x & (x-1)) == 0` | true for 1,2,4,8… |
| Count set bits | loop `x &= x-1` | popcount |

### 2.3 Terminology

| Term | Meaning |
|---|---|
| **LSB** | Least significant bit (bit 0, rightmost). |
| **MSB** | Most significant bit (bit 31 for int — sign). |
| **Mask** | A constant pattern used to select/modify bits. |
| **Two's complement** | `-x = ~x + 1`; addition wraps naturally. |
| **Bitmask subset** | Integer `0..2^n-1` where bit `i` = "item i chosen". |
| **XOR** | Bitwise exclusive-or: `a^a = 0`, `a^0 = a`, commutative/associative. |

---

## 3. Core Concepts

### 3.1 Bit tests, sets, clears, toggles

**Definition**  \nSingle-bit queries/updates using a **mask** `1 << k`.

**Intuition**  \nAND keeps only bit `k`; OR forces it on; AND-NOT forces it off; XOR flips it.

**How it works**

```cpp
bool  test (int x, int k) { return (x >> k) & 1; }   // or x & (1<<k)
int   set  (int x, int k) { return x |  (1 << k); }
int   clear(int x, int k) { return x & ~(1 << k); }
int   toggle(int x, int k){ return x ^  (1 << k); }
```

**Common mistakes**
- `1 << k` for `k ≥ 31` is UB on signed int — use `1U << k` or `1LL << k`.
- Sign bit (k = 31) on `int` — negative results confuse tests; mask with unsigned.

---

### 3.2 `x & (x-1)` — clear the lowest set bit

**Definition**  \nSubtracting 1 flips the lowest 1 to 0 and all lower 0s to 1; AND removes that lowest 1.

**Example**

```text
x   = 1100 (12)
x-1 = 1011
x&(x-1) = 1000 (8)     -> lowest set bit cleared
```

**Why it is needed**  \nCounts set bits in `O(popcount)` instead of 32; detects power of two (`x & (x-1)) == 0 && x > 0`).

**Complexity**  \n`O(number of set bits)` — at most 32.

---

### 3.3 XOR cancellation patterns

**Definition**  \nXOR is commutative, associative, and `a ^ a = 0`, `a ^ 0 = a` — pairs cancel.

**When it applies**
- Every element appears **twice except one** → XOR all → the single.
- **Two singles** among doubles → XOR all = `a ^ b`; split by any set bit of the result; XOR each group → each single.
- **One single, rest triples** → count each bit position mod 3 → assemble the number.
- Minimum flips between numbers = `popcount(a ^ b)`.

**Why it works**  \nCancelling pairs leaves the unpaired values; mod-3 per bit survives triple cancellation.

**Common mistakes**
- Using XOR when elements appear 4 times (need mod 4) or when counts are arbitrary.
- Forgetting that XOR gives the *combined* leftover — for two singles you must partition.

---

### 3.4 Bitmask subset enumeration

**Definition**  \nAn integer `mask ∈ [0, 2^n)` represents a subset: bit `i` set ⇔ element `i` included.

**How it works**

```text
n=3: mask 0..7
000 -> {}
001 -> {a0}   010 -> {a1}   100 -> {a2}
011 -> {a0,a1} ...  111 -> {a0,a1,a2}
```

- Enumerate all: `for (int m = 0; m < (1 << n); m++)`.
- Iterate members: `for (int i = 0; i < n; i++) if (m >> i & 1)`.
- Subsets of `m`: `sub = m; sub = (sub - 1) & m` iterates all submasks.

**Complexity**  \n`O(2^n · n)` naive enumeration; `O(3^n)` over all submasks of all masks.

**Common mistake**  \n`1 << n` overflows for `n = 31`; use `1LL << n` for `n` up to 62.

---

### 3.5 Shifts as arithmetic (divide/multiply without operators)

**Definition**  \n`x << k = x · 2^k`, `x >> k = x / 2^k` (floor, and implementation-defined for negatives).

**Division algorithm**  \nSubtract the largest shifted divisor, accumulate quotient bits — `O(32)` iterations with overflow clamping.

**Common mistakes**
- Negative `x >> k` sign-extends (arithmetic shift) — not a plain floor for all compilers.
- `INT_MIN / -1` overflows — special-case it.
- Shift by ≥ width is UB (`k < 32` for int).

---

## 4. PATTERN LIBRARY

### P1 — Bit Test / Set / Clear / Toggle (flags & masks)

#### What is the pattern?
One mask + one operator modifies or queries a single bit in `O(1)`.

#### When should I recognize it?
- "Check if k-th bit is set", "turn feature on/off", state stored in an integer flag.
- Small sets (`n ≤ 20`) encoded as masks.

#### Core intuition
Bitwise operators act on all 32 bits in parallel; masking isolates the one you care about.

#### Generic algorithm
```text
test:   (x >> k) & 1
set:    x |  (1 << k)
clear:  x & ~(1 << k)
toggle: x ^  (1 << k)
```

#### C++ template
```cpp
bool testBit(int x, int k)   { return (x >> k) & 1; }
int  setBit (int x, int k)   { return x |  (1 << k); }
int  clearBit(int x, int k)  { return x & ~(1 << k); }
int  toggleBit(int x, int k) { return x ^  (1 << k); }
```

#### Time / Space
`O(1)` / `O(1)` (hardware level).

#### Edge cases
`k ≥ 32` (UB); sign bit; `k = 31` on signed int.

#### Common mistakes
`1 << 31` overflows signed int → `1U << k` or `1LL << k`.

#### Variations
`x & (-x)` isolates the lowest set bit (used in Fenwick trees / subset loops).

#### Practice mapping
- `01-Introduction-to-Bit-Manipulation.cpp`, `02-Check-Kth-Bit.cpp`, `03-Check-Odd-Even.cpp`, `06-Set-Unset-Rightmost.cpp`

---

### P2 — `x & (x-1)` Tricks (power of two, popcount)

#### What is the pattern?
Clear the lowest set bit repeatedly to count bits, or once to test power-of-two.

#### When should I recognize it?
- "Count set bits / number of 1s", "is power of 2", "bit flips needed".

#### Core intuition
`x-1` flips the lowest 1→0 and trailing 0→1; AND with `x` deletes exactly that lowest 1.

#### Generic algorithm
```text
isPow2:  x > 0 && (x & (x - 1)) == 0
popcnt:  c = 0; while (x) { x &= x - 1; c++; }
flips:   popcount(a ^ b)
```

#### C++ template
```cpp
int popcount(int x) { int c = 0; while (x) { x &= x - 1; c++; } return c; }
bool isPow2(int x)  { return x > 0 && (x & (x - 1)) == 0; }
int  bitFlips(int a, int b) { return __builtin_popcount(a ^ b); }
```

#### Time / Space
`O(popcount)` ≤ `O(32)` / `O(1)`.

#### Edge cases
`x = 0`: `x & (x-1)` is 0 but `0` is **not** a power of 2 → check `x > 0`. Negative `x`.

#### Common mistakes
Forgetting `x > 0`; using it on negatives (two's complement surprises).

#### Variations
`__builtin_popcount` (GCC) is a single instruction; Brian Kernighan's loop avoids it.

#### Practice mapping
- `04-Check-Power-of-2.cpp`, `05-Count-Set-Bits.cpp`, `14-Min-Bit-Flips.cpp`, `15-Power-n.cpp`

---

### P3 — XOR Cancellation (single / pairs / groups)

#### What is the pattern?
XOR every element (or every bit count mod K) so duplicates annihilate.

#### When should I recognize it?
- "Every element appears twice except one", "two elements appear once", "appears three times except one", "find the odd one out".

#### Core intuition
`a ^ a = 0`, `a ^ 0 = a`, XOR is order-independent → all paired values vanish.

#### Generic algorithm
```text
single among pairs:    x = XOR(all)
two singles:           x = XOR(all); pick any set bit of x; XOR each group
single among triples:  per-bit counts mod 3 -> assemble
```

#### C++ template
```cpp
int singleNumber(vector<int>& a) {
    int x = 0; for (int v : a) x ^= v; return x;
}
```

#### Time / Space
`O(n)` / `O(1)`.

#### Edge cases
Empty array (0); single element (itself; note `1^2 = 3` for two singles — must partition!).

#### Common mistakes
Stopping at "XOR all" for *two* singles; sign-bit handling when splitting groups.

#### Variations
Single II (mod 3), Single III (partition by differing bit), XOR of ranges (`0^1^…^n` cycle of 4).

#### Practice mapping
- `10-XOR-1-to-N.cpp`, `11-Single-Number-I.cpp`, `12-Single-Number-II.cpp`, `13-Single-Number-III.cpp`

---

### P4 — Bitmask Subset Enumeration

#### What is the pattern?
Iterate integers `0 .. 2^n-1`; bit `i` of the mask = "include element i" — instantly enumerates every subset.

#### When should I recognize it?
- "Generate power set", "all subsets" with `n ≤ 20`, "partition into two subsets minimizing difference", "TSP over subsets", "DP over subsets".

#### Core intuition
There are exactly `2^n` n-bit patterns ↔ `2^n` subsets — the integers *are* the subsets.

#### Generic algorithm
```text
for mask in 0 .. (1<<n)-1:
    for i in 0..n-1: if mask>>i & 1 -> element i in subset
    process
```

#### C++ template
```cpp
int n = a.size();
for (int mask = 0; mask < (1 << n); mask++) {
    long long sum = 0;
    for (int i = 0; i < n; i++) if (mask >> i & 1) sum += a[i];
    // process sum / subset
}
```

#### Time / Space
`O(2^n · n)` / `O(n)` (or `O(1)` if processing inline).

#### Edge cases
`n = 0` (empty subset only); `n = 31` (overflow — `1 << 31` UB; use `1LL`); all-zero mask.

#### Common mistakes
`1 << n` signed overflow; iterating members with wrong shift precedence (`mask >> i & 1` is fine — `>>` binds tighter than `&`).

#### Variations
Submask iteration `sub = (sub-1) & mask`; recursion equivalent = §07 pick/not-pick; DP over subsets = §16 advanced.

#### Practice mapping
- `09-Power-Set-Bitmask.cpp`, `07-Recursion/09-Power-Set.cpp`

---

### P5 — Shifts as Arithmetic (multiply/divide/power without operators)

#### What is the pattern?
`<<` multiplies by powers of two, `>>` divides; repeated doubling/halving implements `*`, `/`, `pow`.

#### When should I recognize it?
- "Divide two integers without `*`, `/`, `%`", "power without `pow`", "multiply by 3/5 tricks", constraints demanding bit ops.

#### Core intuition
`x << k = x · 2^k`; division = greedily subtract the largest fitting shifted divisor and set quotient bits.

#### Generic algorithm (divide)
```text
sign = sign(a) ^ sign(b);  a=|a|, b=|b|
q = 0
for bit from 31..0:  if (a - (b<<bit) >= 0) { a -= b<<bit; q |= 1<<bit; }
return sign ? -q : q     (clamp to INT range)
```

#### C++ template
```cpp
int divide(int dividend, int divisor) {
    if (dividend == INT_MIN && divisor == -1) return INT_MAX;   // overflow
    long a = llabs((long)dividend), b = llabs((long)divisor), q = 0;
    for (int i = 31; i >= 0; i--)
        if ((b << i) <= a) { a -= b << i; q |= 1L << i; }
    int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
    return (int)(sign * q);
}
```

#### Time / Space
`O(32)` / `O(1)`.

#### Edge cases
`INT_MIN / -1` (overflow clamp); `b = 0` (undefined/handle); `a < b` (q = 0); `b << 31` overflows long if b large — guard shifts.

#### Common mistakes
Forgetting sign handling; `b << i` overflow when `b` is large (compare in `long long`); missing INT_MIN special case.

#### Variations
Fast power by repeated squaring (§07); modulo via repeated subtraction (slow — prefer `%`).

#### Practice mapping
- `08-Divide-Without-Division.cpp`, `07-Swap-Two-Numbers.cpp` (XOR swap), `15-Power-n.cpp`

---

### P6 — Sieve & Number-Theoretic Bit Tricks

#### What is the pattern?
Mark composites with bit/bool arrays for `O(n log log n)` primality, or use masks to enumerate divisors/multiples.

#### When should I recognize it?
- "Count primes / list primes ≤ n", "check prime quickly", "all divisors", "prime factorization".

#### Core intuition
Every composite `≤ n` has a prime factor `≤ √n` — mark multiples of each prime starting from `p²`.

#### Generic algorithm (sieve)
```text
isPrime[0..n] = true
for p = 2 .. sqrt(n): if isPrime[p]: for multiple = p*p; <= n; += p: isPrime[multiple] = false
```

#### C++ template
```cpp
vector<bool> sieve(int n) {
    vector<bool> ip(n + 1, true);
    ip[0] = ip[1] = false;
    for (int p = 2; 1LL * p * p <= n; p++)
        if (ip[p]) for (int m = p * p; m <= n; m += p) ip[m] = false;
    return ip;
}
```

#### Time / Space
Sieve `O(n log log n)` / `O(n)`; trial division `O(√n)` per query.

#### Edge cases
`n < 2` (no primes); `p*p` overflow (use `long long`); even numbers (skip).

#### Common mistakes
Starting multiples at `2p` instead of `p²` (waste, not wrong); `sqrt` in loop condition recomputed — precompute `p*p <= n`.

#### Variations
Linear sieve (Euler) `O(n)`; divisor enumeration by `i` up to `√n` pairing `(i, n/i)`.

#### Practice mapping
- `16-Sieve-of-Eratosthenes.cpp`, `17-All-Divisors.cpp`, `18-Prime-Factorization.cpp`, `15-Check-Prime.cpp` (§01 trial division), `14-Print-All-Divisors.cpp` (§01)

---

## 5. PATTERN RECOGNITION

| If the problem says... | Think about... |
|---|---|
| "check/set/clear k-th bit" | mask `(1<<k)` ops |
| "is power of 2" / "count set bits" | `x & (x-1)` loop |
| "appears twice except one" | XOR all |
| "two singles among doubles" | XOR → split by set bit |
| "appears three times except one" | bit counts mod 3 |
| "all subsets / bitmask" | iterate `0..2^n-1` |
| "divide without / or *" | shift-subtract division |
| "min flips a → b" | `popcount(a ^ b)` |
| "primes up to n" | sieve |
| "n ≤ 20 with state per element" | bitmask (or §07 recursion) |
| "pairs with XOR = 0 / K" | XOR prefix map (§03) |
| parity / odd-even check | `x & 1` |

**Decision rules**
1. Fixed small bit positions → mask ops (`O(1)`).
2. Cancellation structure (pairs/triples) → XOR / per-bit counts.
3. Subset of up-to-20 items → bitmask enumeration or DP over subsets.
4. Primes/divisors → sieve / `√n` trial division.
5. No bit structure at all? → don't force bits; use hashing/DP.

---

## 6. BRUTE → BETTER → OPTIMAL THINKING

### Check k-th bit
- **Brute** — divide/modulo: `x / 2^k % 2`: `O(k)`.
- **Better** — right shift then `& 1`: `O(1)` conceptually, one op.
- **Optimal** — `(x >> k) & 1` — hardware instruction; nothing beats it.

### Count set bits
- **Brute** — loop all 32 bits checking each: `O(32)`.
- **Better** — Kernighan loop `x &= x-1`: `O(popcount)` — faster on sparse values.
- **Optimal** — `__builtin_popcount` / `popcnt` instruction: single cycle. Know all three; interview answer: Kernighan (portable, elegant).

### Single number among pairs
- **Brute** — hash map counts, find count==1: `O(n)` time, `O(n)` space.
- **Better** — sort, scan pairs: `O(n log n)` time, `O(1)` space.
- **Optimal** — XOR all: `O(n)` time, `O(1)` space. The information-theoretic floor — **optimal**.

### Divide two integers
- **Brute** — repeated subtraction: `O(dividend)` — TLE for `10^9`.
- **Better** — subtract shifted multiples greedily (binary long division): `O(32 · cost)` with care.
- **Optimal** — same asymptotics `O(log dividend)`; the real win is `long long` clamping so it's *correct*.

### Subsets
- **Brute** — build each subset by index arrays: `O(2^n · n²)` copying.
- **Better** — recursion with shared path buffer: `O(2^n · n)`.
- **Optimal** — for counting/summing: iterate masks accumulating incrementally (`sum += a[i]` when bit set, `O(2^n)` with Gray-code style refinement possible); for enumeration you cannot beat output size `2^n`.

### Key transferable idea
> Bits are just **packed booleans**. Every "bit problem" is an array problem with `O(32)` parallelism — when you see counts/cancellation/subsets, ask "what does each bit independently encode?"

---

## 7. C++ / STL TOOLKIT

| Tool | Syntax | Notes |
|---|---|---|
| Bit test | `x & (1 << k)` or `(x >> k) & 1` | mask must fit type |
| Set/clear/toggle | `x \| (1<<k)`, `x & ~(1<<k)`, `x ^ (1<<k)` | `O(1)` |
| Lowest set bit | `x & -x` / `x & (x-1)` | isolate / clear |
| Builtins | `__builtin_popcount(x)`, `__builtin_clz(x)`, `__builtin_ctz(x)` | GCC/Clang; `popcount/clz/ctz` in `<bit>` (C++20) |
| Clang/MSVC alt | `std::popcount(x)`, `std::bit_width(x)` | `<bit>` header |
| Shifts | `x << k`, `x >> k` | `1LL << k` for wide ranges |
| 64-bit literal | `1LL << k`, `long long` | avoids 32-bit overflow |
| Unsigned ops | `unsigned x` | right shift = logical (zero-fill) |

```cpp
// iterate set bits only
for (int m = x; m; m &= m - 1) { int b = __builtin_ctz(m); /* process b */ }

// all subsets of mask
for (int sub = mask; sub; sub = (sub - 1) & mask) { /* ... */ }

// parity (odd/even) fast
if (x & 1) { /* odd */ }
```

**Common mistakes**
- `1 << 31` → negative/UB; use `1u << 31` or `1LL`.
- `__builtin_popcount` takes `unsigned` — cast negatives explicitly.
- Mixing signed/unsigned in shifts → usual arithmetic conversions surprise.

---

## 8. COMPLEXITY GUIDE

| Operation | Time | Space |
|---|---:|---:|
| Bit test/set/clear/toggle | `O(1)` | `O(1)` |
| `x & (x-1)` popcount | `O(popcount)` ≤ 32 | `O(1)` |
| XOR-fold over array | `O(n)` | `O(1)` |
| Bit counts mod 3 | `O(32n)` or `O(n)` with arrays | `O(1)` |
| Mask enumeration | `O(2^n · n)` | `O(n)` |
| Submasks of all masks | `O(3^n)` | `O(1)` |
| Shift-based divide | `O(32)` | `O(1)` |
| Sieve of Eratosthenes | `O(n log log n)` | `O(n)` |
| Trial division primality | `O(√n)` | `O(1)` |
| Fast power | `O(log n)` | `O(log n)` rec |

**How to estimate**
- 32-bit loops are `O(1)` for constraint purposes (`~32 ≤ 100` operations).
- `2^n` subsets: `n=20 → 10^6`, `n=24 → 1.7·10^7` — check the constraint budget.
- Sieve: `n = 10^7` fits comfortably in time/memory; `vector<bool>` packs 8×.

---

## 9. EDGE CASES

- **`x = 0`** — `x & (x-1) == 0` is true, but 0 is not a power of 2 → always check `x > 0`.
- **Shift ≥ width** — `1 << 32` is UB; mask `k` into `[0, 31]`.
- **Sign bit / negatives** — two's complement makes `-x = ~x + 1`; `>>` on negatives is arithmetic (sign-filling).
- **`INT_MIN`** — `-INT_MIN` overflows; `INT_MIN / -1` overflows; `abs(INT_MIN)` UB.
- **`1 << 31`** — wraps to `INT_MIN` in signed arithmetic.
- **Empty array in XOR-fold** — returns 0 (identity) — confirm the problem expects that.
- **`n = 0` subsets** — exactly one (empty) subset; `1 << 0 == 1` ✓.
- **`n = 31/32` masks** — need `1LL << n` or impossible in 32-bit.
- **All-zero masks** — submask loop `for (sub = m; sub; sub = (sub-1) & m)` skips `0` — handle the empty subset separately if needed.
- **Duplicate single numbers** — verify problem guarantees (XOR tricks depend on the count structure).

---

## 10. COMMON MISTAKES

| # | Mistake | What goes wrong | Why | How to avoid |
|---|---|---|---|---|
| 1 | `1 << 31` on `int` | UB / negative mask | signed overflow | `1LL << k` / `1u` |
| 2 | Shift by ≥ 32 | UB | hardware shift masks only 5 bits | clamp `k` |
| 3 | Missing `x > 0` in pow2 check | 0 passes | `0 & -1 == 0` | always `x > 0 &&` |
| 4 | XOR-all for *two* singles | wrong result | `a^b` ≠ singles | partition by set bit |
| 5 | `>>` on negative ints | sign-fill, not logical | implementation-defined-ish | use `unsigned` for logical shift |
| 6 | `-INT_MIN` | overflow | no positive counterpart | `long long` |
| 7 | `1 << n` with `n ≥ 31` | overflow | 32-bit limit | `1LL << n` |
| 8 | Wrong precedence `mask & 1 == i` | parses as `mask & (1==i)` | `==` binds tighter than `&`? — actually `&` is lower than `==`! use parens: `(mask >> i) & 1` | |
| 9 | Sieve from `2p` not `p²` | correct but wasteful | — | start at `p*p` |
| 10 | Assuming `>>` on negatives is floor | may be implementation-defined | C++20 makes it arithmetic shift | avoid relying on it |

**Conceptual mistakes**
- Forcing bit tricks where hashing/DP is the right tool (bits need *structure* in the problem).
- Using `int` masks for `n > 30` subsets without `long long`.
- Counting bits of a signed negative without converting (implementation-defined before C++20).

---

## 11. IMPORTANT FORMULAS / RULES

```text
Identity:     x ^ x = 0,  x ^ 0 = x,  a ^ b = b ^ a  (XOR fold)
Power of 2:   x > 0 && (x & (x-1)) == 0
Isolate LSB:  x & (-x)   ==   x & (x-1-xor trick variant)
Clear LSB:    x & (x-1)
Set bits:     popcount(x);  popcount(a ^ b) = min bit flips a -> b
Two's compl:  -x = ~x + 1
Shift:        x << k = x * 2^k ;  x >> k = x / 2^k (floor for unsigned)
Subsets:      2^n total;  mask bit i <-> element i
Submasks:     for (sub = m; sub; sub = (sub-1) & m)
Range XOR:    0^1^...^n  cycles with period 4: n, n+1, 1, 0 for n%4 = 0,1,2,3
Sieve:        mark multiples of p from p*p up to n  ->  O(n log log n)
Single II:    per-bit count % 3, assemble
Single III:   XOR all -> group by any set bit -> XOR each group
```

**Decision rules**
1. Fixed bit position → mask op.
2. Count per position independent → per-bit counts (mod K).
3. Order-independent pairing → XOR.
4. Subset as state → bitmask (≤ 20) / DP over subsets.
5. Primes → sieve; primality query → `√n` trial.

---

## 12. REUSABLE TEMPLATES

```cpp
// 1. Kernighan popcount / power-of-two
int popcnt(int x) { int c = 0; while (x) { x &= x - 1; c++; } return c; }
bool isPow2(int x) { return x > 0 && (x & (x - 1)) == 0; }

// 2. Bit tests/updates
bool testBit(int x, int k)   { return (x >> k) & 1; }
int  setBit (int x, int k)   { return x |  (1 << k); }
int  clearBit(int x, int k)  { return x & ~(1 << k); }
int  toggleBit(int x, int k) { return x ^  (1 << k); }

// 3. XOR fold (single number)
int singleNumber(vector<int>& a) { int x = 0; for (int v : a) x ^= v; return x; }

// 4. Iterate subsets of mask (incl. empty handled outside)
for (int sub = mask; sub; sub = (sub - 1) & mask) { /* ... */ }

// 5. Sieve
vector<bool> sieve(int n) {
    vector<bool> ip(n + 1, true);
    if (n >= 0) ip[0] = false;
    if (n >= 1) ip[1] = false;
    for (int p = 2; 1LL * p * p <= n; p++)
        if (ip[p]) for (int m = p * p; m <= n; m += p) ip[m] = false;
    return ip;
}
```

## 13. ADVANCED CONCEPTS

### 13.1 Bitwise DP / DP over subsets
State `dp[mask][i]` with transitions over submasks — TSP `O(2^n · n²)`, assignment problem, Hamiltonian paths. Prerequisite: mask enumeration above. Transitions iterate set bits of `mask` (`while (m) { int b = __builtin_ctz(m); m &= m-1; }`).

### 13.2 Gray codes & incremental subset updates
A Gray code changes exactly one bit per step — useful when each successive subset must be derived from the previous in `O(1)` update time.

### 13.3 Fast Walsh–Hadamard Transform (FWHT)
Convolution under XOR/OR/AND in `O(n log n)` instead of `O(n²)` — competition-level; recognize "XOR convolution" phrasing.

### 13.4 Bitset optimization for knapsack / DP
`std::bitset<N>` shifts replace boolean loops: subset-sum feasibility becomes `bits |= bits << w` — `O(n²/64)` word-parallel. Mention in interviews for "DP too slow" follow-ups.

### 13.5 Randomized bit sampling (Hamming distance)
`x ^ y` + popcount = Hamming distance; used in locality-sensitive hashing (SimHash). Good "real world" talking point.

### 13.6 Rope / persistent structures
Not bit-specific, but "XOR linked list" (store `prev ^ next`) and "XOR trick in tree problems" appear occasionally — know they exist and why they save space (one field instead of two).

---

## 14. CONNECTIONS BETWEEN PATTERNS

```text
Integer (2's complement)
    |
    +--> masks (flags, state) --------> O(1) feature toggles
    |
    +--> x & (x-1) ------------------> popcount, power-of-2, lowbit
    |
    +--> XOR cancellation ------------> single/pairs numbers (03 arrays too)
    |
    +--> shift arithmetic ------------> fast pow (07), divide (08)
    |
    +--> bitmask = subset ------------> recursion subsets (07)  <-->  DP over subsets (16)
    |
    +--> sieve / divisibility --------> number theory problems

Bitmask DP:   O(2^n * n)  <- same 2^n tree as recursion, but iterative & cache-friendly
XOR prefix:   subarray XOR = pref[r] ^ pref[l]  (like prefix sums, 03)
```

**Mental map**
1. Fixed bit → mask op. 2. Pairs/triples → XOR. 3. Subset state → mask. 4. Multiplication/division by 2^k → shift. 5. Primes → sieve.

---

## 15. PROBLEM → PATTERN MAPPING

*(Reference only — solutions and approaches live in the `.cpp` files.)*

### Bit tests / set / clear / basics
- `01-Introduction-to-Bit-Manipulation.cpp`
- `02-Check-Kth-Bit.cpp`
- `03-Check-Odd-Even.cpp`
- `06-Set-Unset-Rightmost.cpp`

### `x & (x-1)` / popcount / power-of-2
- `04-Check-Power-of-2.cpp`
- `05-Count-Set-Bits.cpp`
- `14-Min-Bit-Flips.cpp`

### Shift arithmetic / swap / power
- `07-Swap-Two-Numbers.cpp`
- `08-Divide-Without-Division.cpp`
- `15-Power-n.cpp`

### XOR cancellation
- `10-XOR-1-to-N.cpp`
- `11-Single-Number-I.cpp`
- `12-Single-Number-II.cpp`
- `13-Single-Number-III.cpp`

### Bitmask subsets
- `09-Power-Set-Bitmask.cpp`

### Number theory (sieve / divisors / primes)
- `16-Sieve-of-Eratosthenes.cpp`
- `17-All-Divisors.cpp`
- `18-Prime-Factorization.cpp`

---

## 16. QUICK REVISION SHEET

**Concepts**
- Bits = packed flags; `x & (x-1)` clears lowest set bit; XOR cancels pairs.
- Mask `i` ↔ subset element `i`; `2^n` masks enumerate all subsets.
- Two's complement: `-x = ~x + 1`; shifts: `<<` ×, `>>` ÷ (unsigned).

**Recognition clues**
| Signal | Tool |
|---|---|
| count/flip bits | popcount (`x&=x-1`) |
| power of 2 | `x>0 && (x&(x-1))==0` |
| pairs/triples cancellation | XOR / mod-3 counts |
| subsets / n≤20 | mask loop |
| divide w/o `/` | shift-subtract |
| primes ≤ n | sieve |

**Formulas**
```text
pow2:     x > 0 && (x & (x-1)) == 0
flips:    popcount(a ^ b)
clearLSB: x & (x-1)      isolateLSB: x & -x
subsets:  2^n;   submasks: sub = (sub-1) & mask
range XOR 0..n:  period 4 -> n, n+1, 1, 0
sieve from p*p, O(n log log n)
```

**Complexity** — bit ops `O(1)`/≤32 · XOR fold `O(n)/O(1)` · masks `O(2^n·n)` · sieve `O(n log log n)` · trial `O(√n)`.

**Common mistakes** — `1<<31` · shift ≥ 32 · missing `x>0` in pow2 · XOR-all for two singles · `-INT_MIN` · `1<<n` overflow.

**Templates to remember** — `popcnt`, `isPow2`, bit set/clear/test, XOR fold, sieve, mask loop.

**Decision rules** — fixed bit→mask · cancellation→XOR · subset→mask · 2^k arithmetic→shift · primes→sieve.

---

## 17. INTERVIEW CHECKLIST

- [ ] Can I write test/set/clear/toggle for bit k without thinking?
- [ ] Can I explain *why* `x & (x-1)` clears the lowest set bit (with a binary example)?
- [ ] Can I solve single-number, double-numbers, and triple-numbers variants?
- [ ] Can I convert between recursion subsets and mask subsets?
- [ ] Can I handle overflow (`1LL << n`, `INT_MIN`) in every template?
- [ ] Can I write shift-based division with correct sign handling?
- [ ] Can I write a sieve and state `O(n log log n)`?
- [ ] Can I identify when bitmask DP (`O(2^n·n)`) is feasible from constraints?
- [ ] Can I list the UB traps (shift width, signed overflow, negative `>>`)?
- [ ] Can I justify bit tricks over hash maps when space/time matters?

<!-- done -->
