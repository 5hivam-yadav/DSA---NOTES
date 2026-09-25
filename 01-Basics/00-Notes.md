# 01 — Basics (C++, Patterns, Basic Maths, Basic Recursion & Basic Hashing)

---

## 1. Introduction

The foundation of Data Structures and Algorithms rests upon five foundational competencies:

1. **Programming Language Fundamentals**: Writing idiomatic, memory-safe, zero-overhead C++ using standard streams, control branches, functions, and references.
2. **Algorithmic Complexity**: Calculating deterministic upper bounds for Big-O execution time and auxiliary space consumption.
3. **Basic Mathematics**: Using arithmetic properties of positional number systems, integer factorizations, Euclidean division, and modular operations.
4. **Recursive Thinking**: Breaking a problem into a base case and self-similar smaller instances while managing the call stack.
5. **Direct Addressing & Hashing**: Mapping a universe of values into discrete buckets to achieve constant-time frequency indexing and lookups.

### Purpose

Without solid fundamentals, advanced structures like balanced search trees, graph flow networks, and multi-dimensional dynamic programming become impossible to implement correctly. Mastery of fundamentals ensures that basic operations — loop invariants, overflow handling, pass-by-value vs pass-by-reference, and recursion unwinding — become second nature.

### Why it matters in DSA

Modern technical interviews test edge-case discipline rigorously:

- What happens when `N = 0`, `N = -2^31`, or inputs exceed `10^9`?
- Why does `void foo(vector<int> v)` cost `O(N)` per call instead of `O(1)`?
- Why does `1LL * a * b` prevent integer overflow while `(long long)(a * b)` does not?

### Real-world intuition

Think of basic programming syntax and math as the physics engine of software engineering. If you do not understand CPU throughput limits (~10^8 operations/sec) or RAM limits (~256–512 MB), designing complex systems will lead to crashes, stack overflows, or Time Limit Exceeded (TLE) errors.

---

## 2. Prerequisites

Before studying these foundational concepts, ensure familiarity with:

- High-school arithmetic: powers, prime numbers, divisors, greatest common divisors, factorials.
- Basic algebraic equations and coordinate geometry.
- Computer memory (RAM): variables as named locations with fixed bit-widths (`int` = 32 bits, range about -2·10^9 to 2·10^9).
- Basic control flow: `if/else`, `for`, `while` loops.

---

## 3. Core Concepts

### 3.1 Time and Space Complexity (Asymptotic Analysis)

**Definition**  
Big-O notation (`O`) characterizes the upper bound of an algorithm's growth rate as input size `N` approaches infinity. Auxiliary space measures memory allocated beyond the problem inputs.

**Intuition**  
Big-O does not measure clock seconds; it measures the rate of growth in elementary machine operations. An `O(N)` algorithm doubles its operations when input doubles; an `O(N^2)` algorithm quadruples them.

**How it works**  
Modern judges allow roughly 10^8 basic CPU operations per second. Rule of thumb for choosing an acceptable complexity:

| Input size `N` | Acceptable complexity |
|---|---|
| `N <= 10` | `O(N!)`, `O(2^N · N)` |
| `N <= 20` | `O(2^N)` |
| `N <= 500` | `O(N^3)` |
| `N <= 5000` | `O(N^2)` |
| `N <= 10^5 … 10^6` | `O(N log N)`, `O(N)` |
| `N >= 10^9` | `O(log N)`, `O(1)` |

**Example**

```cpp
// O(N) time, O(1) auxiliary space
long long sum = 0;
for (int i = 1; i <= n; i++) {
    sum += i;
}
```

**Important observation**  
Auxiliary space does not equal total space. If an algorithm returns a newly allocated array of size `N`, its output space is `O(N)`, but its auxiliary workspace may remain `O(1)`.

**Common mistake**  
Ignoring implicit memory from the recursion call stack. A recursion of depth `N` consumes `O(N)` auxiliary space on the process call stack, risking stack overflow (SIGSEGV) when `N >= 10^5`.

---

### 3.2 Pass-by-Value vs. Pass-by-Reference in C++

**Definition**

- **Pass-by-value**: the parameter receives a byte-for-byte copy of the actual argument.
- **Pass-by-reference (`&`)**: the parameter is an alias to the caller's actual memory location.
- **Const reference (`const &`)**: direct access to caller memory without copying, with a read-only guarantee.

**Intuition**  
Passing a 100,000-element `vector` by value copies 400 KB of RAM on every call. In a loop of 100,000 iterations this performs 10^10 byte copies, turning an `O(N)` procedure into a hidden `O(N^2)` bottleneck.

**How it works**

```cpp
void modifyVal(int x)  { x += 10; }          // caller unchanged
void modifyRef(int &x) { x += 10; }          // caller mutated
int  sumSize(const vector<int> &v) {         // zero-copy, read-only
    return (int)v.size();
}
```

**Important observation**  
Primitive types (`int`, `char`, `double`, pointers) fit in CPU registers — pass them by value. For heavy objects (`std::vector`, `std::string`, custom structs) prefer `const Type&` unless you must mutate or transfer ownership.

**Common mistake**  
Returning a reference to a local stack variable:

```cpp
int& badFunction() {
    int local = 42;
    return local;   // undefined behavior: frame destroyed on return!
}
```

---

### 3.3 Positional Digit Extraction and Safe Integer Reversal

**Definition**  
Deconstructing a base-10 integer into individual digits via modulo 10 (`n % 10`) and integer division (`n / 10`).

**Intuition**  
In decimal representation `n = d_k·10^k + … + d_0`. Modulo extracts the least significant digit `d_0`; integer division shifts all digits one place to the right.

**How it works**

```text
n = 1234
1234 % 10 = 4,  1234 / 10 = 123
 123 % 10 = 3,   123 / 10 = 12
  12 % 10 = 2,    12 / 10 = 1
   1 % 10 = 1,     1 / 10 = 0   -> stops (n == 0)
Extracted order: 4 -> 3 -> 2 -> 1
```

**Example (reversal with 32-bit overflow guard)**

```cpp
int reverse(int x) {
    int rev = 0;
    while (x != 0) {
        int pop = x % 10;
        x /= 10;
        if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && pop > 7)) return 0;
        if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && pop < -8)) return 0;
        rev = rev * 10 + pop;
    }
    return rev;
}
```

**Important observation**  
For negative numbers C++ truncates toward zero: `(-123) % 10 == -3` and `(-123) / 10 == -12`. Normalize with `((x % 10) + 10) % 10` when a non-negative digit is required.

**Common mistake**  
Using `while (n > 0)` when inputs can be negative, or computing `rev = rev * 10 + pop` without an overflow check — signed integer overflow is undefined behavior.

---

### 3.4 Euclidean GCD and LCM

**Definition**  
The greatest common divisor of non-negative integers `a` and `b`:

```text
gcd(a, b) = gcd(b, a mod b),   base case: gcd(a, 0) = a
```

**Intuition**  
If `g` divides both `a` and `b`, it also divides `a - b` and therefore the remainder `a mod b`. Taking the remainder jumps straight to the smallest residue instead of subtracting repeatedly.

**How it works**

```text
gcd(48, 18):
48 = 18 * 2 + 12  ->  gcd(18, 12)
18 = 12 * 1 + 6   ->  gcd(12, 6)
12 =  6 * 2 + 0   ->  gcd(6, 0)
base case reached ->  result = 6
```

Relation to LCM: `lcm(a, b) = a / gcd(a, b) * b`. Divide first to avoid overflow:

```cpp
long long lcm(long long a, long long b) {
    return (a / std::gcd(a, b)) * b;   // C++17 <numeric>
}
```

**Important observation**  
Every factor pair `(d, n/d)` has one member `<= sqrt(n)`, so divisor enumeration runs in `O(sqrt(n))`. The Euclidean algorithm takes `O(log min(a, b))` steps — at most ~45 iterations for 64-bit inputs.

**Common mistake**  
Writing `a * b / gcd(a, b)` directly: for `a = b = 10^9` the product `10^18` fits in `long long`, but with larger types or 32-bit intermediates it overflows. Always divide before multiplying.

---

### 3.5 Primes: Trial Division and the Sieve of Eratosthenes

**Definition**  
A prime has exactly two divisors. Trial division tests divisibility by every candidate up to `sqrt(n)`. The Sieve precomputes primality for all values up to `LIMIT` by repeatedly striking out multiples of each prime.

**Intuition**  
If both factors of `n` exceeded `sqrt(n)` their product would exceed `n` — impossible. For many queries, amortizing work across a shared table beats repeating `O(sqrt(n))` checks per number.

**How it works (sieve marking)**

```text
sieve(0..20), mark multiples of primes 2, 3, 5, 7...
idx:  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
      x x P P x P x P x x  x  P  x  P  x  x  x  P  x  P  x
P = prime kept, x = composite struck out
```

```cpp
vector<bool> sieve(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; 1LL * i * i <= n; i++)
        if (isPrime[i])
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = false;
    return isPrime;
}
```

**Important observation**  
Complexity `O(n log log n)` time, `O(n)` space. Inner loop starts at `i * i` because smaller multiples already carry a smaller prime factor. `vector<bool>` packs 8 flags per byte — memory-efficient but bit-proxy slow; use `vector<char>` for speed.

**Common mistake**  
`i * i <= n` overflows when `i > 46340`. Write `1LL * i * i <= n` or `i <= n / i`. Avoid `i <= sqrt(n)` with floating point — precision drift on large `n`.

---

### 3.6 Recursion: Call Stack Mechanics

**Definition**  
A function solving a problem by calling itself with smaller instances until an irreducible base case is reached.

**Intuition**  
Each call pushes a new stack frame (parameters, locals, return address). The base case triggers unwinding in Last-In-First-Out order, propagating partial results upward.

**How it works — every recursion needs three parts**

1. **Base case** — the smallest input, answered directly.
2. **Recursive step** — strictly smaller input than the current one.
3. **Combination** — work done with the returned value.

```text
fact(3)
 ├─ 3 * fact(2)
 │        ├─ 2 * fact(1)
 │        │        └─ return 1   (base case)
 │        └─ return 2 * 1 = 2
 └─ return 3 * 2 = 6
```

**Important observation**  
Depth equals the number of frames on the stack: ~10^5 frames overflow the default ~8 MB stack. Each frame costs tens of bytes minimum — recursion consumes `O(depth)` space even when the algorithm is logically iterative.

**Common mistake**  
Forgetting to advance toward the base case (`f(n)` calling `f(n)` instead of `f(n - 1)`) → infinite recursion → stack overflow. Also mutating shared state across branches without restoring it (backtracking forgot to undo).

---

### 3.7 Direct Addressing vs. Hash Tables

**Definition**  
- **Direct address table (frequency array)**: an array where the index *is* the value — `freq[x]++`.  
- **Hash table (`std::unordered_map`)**: a hash function maps an arbitrary key to a bucket index; collisions are chained.

**Intuition**  
If keys are small dense integers (or single characters), you can buy `O(1)` lookups with a flat array. When keys are sparse, large, or non-numeric, a hash table compresses the key space into a smaller bucket array.

**How it works**

```text
Frequency array for lowercase letters (dense keys 'a'..'z'):
index:    0    1    2   ...  25
char:    'a'  'b'  'c'      'z'
count:   | 3  | 0  | 7  ... | 1 |      O(1) guaranteed, contiguous

Hash map buckets (chaining on collision):
bucket 0: -> [key:104,val:1] -> [key:4,val:2] -> null   (collision)
bucket 1: -> [key:25, val:4] -> null
bucket 2: -> null
```

```cpp
// Direct addressing — only when range is small/dense
vector<int> freq(101, 0);
for (int x : nums) freq[x]++;          // O(1) per element

// Hashing — arbitrary keys
unordered_map<string, int> mp;
mp["alice"]++;                          // O(1) average
```

**Important observation**  
A frequency array needs `range` slots: counting values up to 10^9 wastes 4 GB. Use direct addressing only when `max_value <= ~10^6`. Hash maps trade memory (buckets + node pointers) for sparse-key support.

**Common mistake**  
Assuming `unordered_map` is always `O(1)`: adversarial inputs force every key into one bucket, degrading to `O(n)` per lookup. For guaranteed `O(log n)`, use `std::map` (red-black tree).

---

## 4. Terminology

| Term | Meaning |
|---|---|
| **Asymptotic bound** | Mathematical limit describing performance as problem size grows to infinity. |
| **Big-O (`O`)** | Asymptotic worst-case upper bound on time or space. |
| **Omega (`Ω`)** | Asymptotic best-case lower bound. |
| **Theta (`Θ`)** | Tight bound — the algorithm is both `O(f(n))` and `Ω(f(n))`. |
| **Stack overflow** | Fatal error (SIGSEGV) when the call stack exceeds its limit (~8 MB). |
| **In-place** | Modifying the input using only `O(1)` extra memory. |
| **Pass-by-reference** | Passing a memory alias (`&`) instead of a copy. |
| **Integer overflow** | Exceeding the datatype's max value (> 2^31 − 1 for signed 32-bit). |
| **Euclidean division** | Writing `a = q·b + r` with `0 <= r < |b|`. |
| **Hash collision** | Two distinct keys producing the same bucket index. |
| **Amortized time** | Average cost per operation over a worst-case sequence of operations. |
| **Tail recursion** | Recursive call in final position; eligible for compiler optimization. |

---

## 5. ASCII Visual Explanations

### Call stack lifecycle in recursion

```text
PUSH (descent to base case)         POP (unwind, values flow up)

main()                              main()      <- receives 6
 └─ fact(3)                          fact(3)  returns 3*2 = 6
     └─ fact(2)                      fact(2)  returns 2*1 = 2
         └─ fact(1)  [BASE]          fact(1)  returns 1
   ^ grows downward                  ^ shrinks upward
   LIFO: last frame pushed           first frame popped
```

### Loop index coordinates for 2D patterns

```text
Square stars, N = 4            Inverted triangle (stars = N - i)

    j→ 0 1 2 3                    i=0  * * * *   (4)
i=0    * * * *                    i=1    * * *   (3)
i=1    * * * *                    i=2      * *   (2)
i=2    * * * *                    i=3        *   (1)
i=3    * * * *

outer loop = rows (i)            inner condition depends on i
inner loop = columns (j)         printing shrinks each row
```

### Pyramid with centered spaces (N = 4)

```text
row i (0-based): spaces = N-1-i, stars = 2*i+1

         *            spaces=3 stars=1
        ***           spaces=2 stars=3
       *****          spaces=1 stars=5
      *******         spaces=0 stars=7
```

### Digit extraction walk-through

```text
n = 459
459 % 10 = 9   |  digit 9   |  n = 45
 45 % 10 = 5   |  digit 5   |  n =  4
  4 % 10 = 4   |  digit 4   |  n =  0  -> done
reverse order collected: 9, 5, 4  =>  reversed number = 459
```

---

## 6. Real-World Applications

- **Fast I/O**: competitive judges and log-processing pipelines disable stream sync (`ios::sync_with_stdio(false); cin.tie(nullptr);`) for 2–5× throughput on large inputs.
- **GCD/LCM**: RSA key generation verifies coprime exponents; audio/video frame alignment uses LCM of sample rates.
- **Sieve of Eratosthenes**: key generation in TLS/Diffie-Hellman precomputes large primes; hashing libraries pick table sizes.
- **Modulo arithmetic**: ring buffers in OS schedulers, hash-table index mapping, pseudorandom number generators (LCG), and rolling-hash string matching.
- **Frequency tables**: routers and firewalls classify packets with direct-address arrays; spell-checkers count character frequencies; compilers build symbol tables.
- **Recursion**: parser/interpreter AST traversal, filesystem directory walks, and DOM tree operations mirror recursive problem structure.

---

## 7. Edge Cases and Pitfalls

1. **Negative modulo** — C++ gives `(-7) % 3 == -1`. Normalize to `[0, M-1]`:

   ```cpp
   int safeMod = ((x % M) + M) % M;
   ```

2. **Intermediate overflow** — `n * (n + 1) / 2` with `n = 10^5` reaches 10^10 > 2·10^9 (32-bit max). Promote first:

   ```cpp
   long long s = 1LL * n * (n + 1) / 2;
   ```

3. **Floating-point inexactness** — `sqrt(49) * sqrt(49) == 49` may be false (IEEE 754 rounding). Test with integers:

   ```cpp
   long long r = round(sqrt((double)n));
   if (r * r == n) { /* perfect square */ }
   ```

4. **Infinite recursion** — a missing or unreachable base case exhausts the stack (~10^5 frames). Always assert the recursive argument strictly moves toward the base case.

5. **Mixed I/O after `sync_with_stdio(false)`** — combining `printf/scanf` with `cin/cout` breaks interleaving order because the two buffers are unsynchronized. Pick one family.

6. **Empty input containers** — `v[0]` on an empty vector, `*s.rbegin()` on an empty string, or `size() - 1` on `size_t 0` wraps to 2^64 − 1. Guard with a size check before indexing.

7. **Off-by-one in loop bounds** — `<=` vs `<` on 0-based indices: `for (int i = 0; i <= n; i++)` reads `a[n]`, one past the end.

---

## 8. Comparison Table

| Approach | Time | Space | Best for | Limitation |
|---|---|---|---|---|
| Direct frequency array | `O(N)` build, `O(1)` query | `O(range)` | Dense keys ≤ 10^6, characters | Impossible for range 10^9 |
| `std::unordered_map` | `O(1)` avg query | `O(N)` | Sparse/arbitrary keys | `O(N)` worst case on collisions |
| `std::map` | `O(log N)` query | `O(N)` | Ordered iteration, range queries | Higher constant factor |
| Iterative loop | `O(f(N))` explicit | `O(1)`–`O(N)` | Flat problems, hot paths | Awkward for nested structures |
| Recursive function | Same as iteration | `O(depth)` stack | Trees, backtracking, divide & conquer | Stack overflow at depth ~10^5 |
| Trial division prime test | `O(sqrt(n))` per query | `O(1)` | Single checks, n ≤ 10^14 | Slow across many queries |
| Sieve of Eratosthenes | `O(n log log n)` build | `O(n)` | All primes ≤ 10^7 quickly | Memory caps n ≤ ~10^8 |

---

## 9. Best Practices

- **Enable fast I/O once at the top of `main()`**:

  ```cpp
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ```

- Prefer `'\n'` over `std::endl` — `endl` flushes the buffer, costing 10×+ on large output.
- Multiply through a 64-bit literal (`1LL * a * b`) *before* overflow can occur; casting after the fact is too late.
- Pass anything heavier than a machine word as `const Type&`; mutate only through a non-const `&` when required.
- Avoid VLAs (`int arr[n]`); use `vector<int> arr(n)` — stack allocation fails silently on large `n`.
- Handle negatives in math problems first; `while (n > 0)` on a possibly negative `n` silently skips the body.
- Keep pattern loops explicit: outer = rows, inner = columns, conditions derived from `i` alone — no hidden state.
- Validate `empty()`, `n == 0`, and single-element inputs before writing loops.

---

## 10. Important Patterns & Problem-Solving Strategies

### Pattern 1 — Two-pointer reversal

```cpp
void reverseInPlace(vector<int> &a) {
    int l = 0, r = (int)a.size() - 1;
    while (l < r) swap(a[l++], a[r--]);
}
```

*Use when*: palindromes, in-place array reversal, partitioning around a center.

### Pattern 2 — Modulo accumulation

```cpp
const int MOD = 1e9 + 7;
long long ans = 0;
for (int x : nums) ans = (ans + x) % MOD;
```

*Use when*: large sums/products, combinatorics counts, rolling hashes.

### Pattern 3 — Digit unrolling

```cpp
while (n > 0) {
    int d = n % 10;
    // process d
    n /= 10;
}
```

*Use when*: digit sums, Armstrong/palindrome numbers, base conversion, reversal.

### Pattern 4 — Precompute once, answer many

```cpp
vector<int> pre = buildPrefix(nums);   // O(n)
for (auto [l, r] : queries)
    ans = pre[r] - pre[l - 1];          // O(1)
```

*Use when*: repeated range queries over static data (sieves, prefix sums).

### Pattern 5 — Guard the invariant with a base case

```cpp
int f(int n) {
    if (n <= 1) return n;   // base case FIRST
    return f(n - 1) + f(n - 2);
}
```

*Use when*: every recursive solution — check the base case before any work.

---

## 11. Practice Problems

All problems live in this folder (`01-Basics/`). Suggested order follows the section order above.

| # | File | Core skill |
|---|---|---|
| 01 | `01-User-Input-Output.cpp` | `cin`/`cout`, streams |
| 02 | `02-If-Else-Statements.cpp` | branching |
| 03 | `03-Switch-Statement.cpp` | multi-way dispatch |
| 04 | `04-Arrays-and-Strings.cpp` | basic containers |
| 05 | `05-For-Loops.cpp` | counted iteration |
| 06 | `06-While-Loops.cpp` | condition-driven iteration |
| 07 | `07-Functions-Pass-by-Value-Reference.cpp` | §3.2 semantics |
| 08 | `08-Time-and-Space-Complexity.cpp` | §3.1 analysis |
| 09 | `09-Count-Digits.cpp` | §3.3 extraction |
| 10 | `10-Reverse-Integer.cpp` | §3.3 + overflow guard |
| 11 | `11-Palindrome-Number.cpp` | digit unrolling |
| 12 | `12-GCD-HCF.cpp` | §3.4 Euclidean algorithm |
| 13 | `13-Armstrong-Number.cpp` | digit powers |
| 14 | `14-Print-All-Divisors.cpp` | `O(sqrt(n))` pairing |
| 15 | `15-Check-Prime.cpp` | §3.5 trial division |
| 16 | `16-Print-Name-N-Times.cpp` | recursion base/step |
| 17 | `17-Print-1-to-N.cpp` | forward recursion |
| 18 | `18-Print-N-to-1.cpp` | backward recursion |
| 19 | `19-Sum-of-First-N-Numbers.cpp` | recursive accumulation |
| 20 | `20-Factorial-of-N.cpp` | call-stack trace |
| 21 | `21-Reverse-an-Array.cpp` | two-pointer pattern |
| 22 | `22-Check-Palindrome-String.cpp` | two-pointer on strings |
| 23 | `23-Fibonacci-Number.cpp` | overlapping subcalls |
| 24 | `24-Counting-Frequencies.cpp` | §3.7 frequency array |
| 25 | `25-Highest-Lowest-Frequency.cpp` | hash map scanning |
| 26 | `26-Pattern-Square-Star.cpp` | nested loops |
| 27 | `27-Pattern-Triangles-Pyramid.cpp` | spaces + stars formulas |
| 28 | `28-Pattern-Numbers-Alphabets-Diamond.cpp` | index arithmetic |

**How to use this chapter**

1. Read the concept sections, then attempt the matching file without looking.
2. Trace every recursion on paper (frames, arguments, return values) before running.
3. Re-derive the loop bounds of each pattern from the ASCII diagrams in §5.









