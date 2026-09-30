# C++ & Mathematical Foundations — Revision & Pattern Recognition

> Use this as a retrieval guide: match the cue, choose the pattern, state its invariant, then check boundaries and complexity.

## Solve workflow

1. Identify the input structure and constraints; reject a pattern whose preconditions are absent (for example, binary search needs monotonicity).
2. Match the statement to a cue below. Write the state/invariant in one sentence before coding.
3. Choose the simplest correct version, trace a smallest case and a boundary case, then state time and extra space.

## Pattern recognition

### P1 — Loop boundaries and index arithmetic

**What is the pattern?**

Translate a one-based, mathematical description into correct zero-based C++ loop bounds without off-by-one errors.

**When should I recognize it?**

Statements mention positions, ranges, row/column indices, digit positions, or a value printed several times.

**Core intuition**

A half-open interval `[l, r)` is represented by `for (int i = l; i < r; ++i)`. Choosing it consistently removes many boundary mistakes.

**General approach**

Draw the indices; write the first and last valid values; state whether the end is inclusive; use `<=` or `<` accordingly.

**Generic algorithm**

`for (int i = first; i <= last; ++i)` for inclusive ranges, or `i < endExclusive` for half-open ranges.

**Complexity**

`O(last - first + 1)` time and `O(1)` extra space.

**Edge cases and mistakes**

`n = 0`; inclusive versus exclusive endpoints; `r - l` versus `r - l + 1`; signed/unsigned subtraction.

**Variations and practice mapping**

Two-dimensional traversal and reverse loops: `01-User-Input-Output.cpp`, `05-For-Loops.cpp`, `06-While-Loops.cpp`, `26-Pattern-Square-Star.cpp`, `27-Pattern-Triangles-Pyramid.cpp`, `28-Pattern-Numbers-Alphabets-Diamond.cpp`.

### P2 — Safe integer and digit processing

**What is the pattern?**

Extract decimal digits, reverse a number, or calculate digit properties while keeping intermediate values in a safe type.

**When should I recognize it?**

The problem says digit sum, digit product, Armstrong number, palindrome number, or reverse integer.

**Core intuition**

`n % 10` removes the last digit; integer `n / 10` removes it permanently. Process until the value becomes zero.

**General approach**

Use `long long`; repeatedly take `n % 10`, process it, then set `n /= 10`. Preserve the original number when checking a property.

**Generic algorithm**

`while(n > 0) { d=n%10; use(d); n/=10; }`

**Complexity**

`O(log n)` time and `O(1)` space.

**Edge cases and mistakes**

`0` (a valid single-digit number); negative values; `INT_MIN` negation; changing `n` before checking a digit property.

**Variations and practice mapping**

Digit powers, palindromes, and reversal: `09-Count-Digits.cpp`, `10-Reverse-Integer.cpp`, `11-Palindrome-Number.cpp`, `13-Armstrong-Number.cpp`.

### P3 — GCD, factors, and primes

**What is the pattern?**

Use Euclidean division, divisor pairing, and elimination of multiples instead of checking every candidate unnecessarily.

**When should I recognize it?**

The statement asks for GCD/LCM, divisors, or whether a number is prime.

**Core intuition**

`gcd(a,b) = gcd(b, a%b)`. If `d` divides `n`, then `n/d` does too, so only test up to `sqrt(n)`. The sieve marks all multiples of each prime.

**Complexity, edge cases, and mistakes**

GCD is `O(log min(a,b))`; factors and trial-division primality are `O(sqrt n)`. Reject `n < 2`; widen multiplication in `d*d <= n`.

**Variations and practice mapping**

`12-GCD-HCF.cpp`, `14-Print-All-Divisors.cpp`, `15-Check-Prime.cpp`.

### P4 — Direct addressing and frequency tables

**What is the pattern?**

Index a table by a small bounded value for deterministic constant-time counting.

**When should I recognize it?**

Keys are non-negative and bounded, with questions about occurrence, duplicates, or frequency.

**Complexity, edge cases, and mistakes**

`O(n+k)` time and `O(k)` space. Use a map for negative or huge keys; avoid unchecked large allocations.

**Variations and practice mapping**

`24-Counting-Frequencies.cpp`, `25-Highest-Lowest-Frequency.cpp`.

### P5 — Base-case-first recursion

**What is the pattern?**

Call a strictly smaller version of the task until an explicit stopping condition is reached.

**When should I recognize it?**

The task is self-similar: printing a range, factorial, Fibonacci, digit processing, or accumulating a sum.

**Complexity, edge cases, and mistakes**

A linear chain is `O(n)` time and `O(n)` stack space. Validate negative input, put the base case first, and show the call stack in an explanation.

**Variations and practice mapping**

`16-Print-Name-N-Times.cpp`, `17-Print-1-to-N.cpp`, `18-Print-N-to-1.cpp`, `19-Sum-of-First-N-Numbers.cpp`, `20-Factorial-of-N.cpp`, `23-Fibonacci-Number.cpp`.

## Topic-specific final checks

- Verify the assumptions named in the selected pattern (sortedness, non-negative weights, DAG, alphabet bounds, or allowed transitions).
- Make empty, singleton, duplicate, and extreme-value behavior explicit where applicable.
- Prefer the compact invariant and transition over memorizing a full implementation.
