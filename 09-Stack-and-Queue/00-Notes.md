# 09 — Stack and Queue — Complete Pattern-Based Notes

---

## 1. Topic Overview

**Stack** (LIFO) and **queue** (FIFO) are access-discipline structures. Their *monotonic* variants — stacks/deques that maintain increasing/decreasing order — are among the most powerful interview patterns.

**What it is**
- Stack: last-in first-out — matches nested/undo structure.
- Queue: first-in first-out — matches arrival/processing order.
- Monotonic stack/queue: elements kept in sorted order to answer next/previous greater/smaller queries in amortized `O(1)`.

**Why it is important**
- Parentheses, expression evaluation, and undo logic are stack-native.
- Next Greater Element, histogram area, trapping rain water, subarray min/max sums — all monotonic stack classics.
- BFS needs queues; sliding-window maximum needs a monotonic deque; LRU needs stack+hash ideas.

**Where it is used**
- Valid parentheses, min stack, infix/postfix conversion.
- NGE/NSE/PSE/PGE, asteroid collision, stock span.
- Largest rectangle in histogram, maximal rectangle.
- Sliding window maximum, BFS (§15), topological sort (§15).

**How it connects to other topics**
- §15: queue powers BFS; stack powers DFS and topo sort.
- §10 Sliding Window: monotonic deque is the window-max tool.
- §13 Trees: iterative traversals use explicit stacks.
- §06 Linked List: LRU = hash + doubly linked list + stack discipline.

**Interview memory hook:** *Nesting → stack. Next greater → monotonic. Window max → deque. Conversion → precedence + stack.*

---

## 2. Fundamentals

### 2.1 LIFO vs FIFO

```text
Stack (LIFO):  push A,B,C -> pop C,B,A     (like plates)
Queue (FIFO):  push A,B,C -> pop A,B,C     (like a line)
```

### 2.2 Building blocks

```cpp
stack<int> st;   st.push(x); st.top(); st.pop(); st.empty();
queue<int> q;    q.push(x); q.front(); q.pop();
deque<int> dq;   push_front/back, pop_front/back   (both ends O(1))
```

### 2.3 Monotonic stack — the key idea

```text
array:      [4, 2, 5, 1, 3]
next greater element (to the right):

scan L->R keeping a decreasing stack of indices:
  at 5: pop 2 (5 is 2's next greater) -> answer[2]=5
  at 3: pop 1  -> answer[1]=3
result:     [5, 5, -1, 3, -1]
```

**Invariant**: elements in the stack are in decreasing order (for NGE); each element is pushed once and popped once → amortized `O(1)` per element.

### 2.4 Terminology

| Term | Meaning |
|---|---|
| **Monotonic stack** | Stack kept strictly increasing or decreasing. |
| **Amortized O(1)** | Each element pushed/popped at most once overall. |
| **Deque** | Double-ended queue; both ends `O(1)`. |
| **Circular buffer** | Fixed-size array simulated as a queue. |
| **Sentinel** | Dummy value appended (e.g. `0` height) to flush the stack. |

---

## 3. Core Concepts

### 3.1 Stack: nesting and cancellation

**Definition**  \nPush open tokens; on a closing token, check/pop the match.

**Why it is needed**  \nNesting means "most recent must match first" — exactly LIFO order.

**How it works**
- Valid parentheses: push expected closer, or push opens and compare tops.
- Min stack: maintain `(value, minSoFar)` pairs — or two parallel stacks; the elegant `2x - top` encoding trick works without extra space but overflows for large values.
- Asteroid collision: positive asteroids move right (push), negative move left (pop while smaller; equal → both destroyed).

**Complexity**  \n`O(n)` time, `O(n)` space.

**Common mistake**  \nForgetting to validate `st.empty()` before `st.top()`.

---

### 3.2 Monotonic stack: next/previous greater/smaller

**Definition**  \nOne left-to-right (or right-to-left) pass maintaining a stack sorted in decreasing (or increasing) order; pops answer queries.

**Four variants (strictness matters!)**

| Query | Scan | Stack order | Pop while |
|---|---|---|---|
| Next greater | L→R | decreasing | `a[st.top()] <= a[i]` |
| Previous greater | R→L | decreasing | symmetric |
| Next smaller | L→R | increasing | `a[st.top()] >= a[i]` |
| Previous smaller | R→L | increasing | symmetric |

**Intuition**  \nPopped elements' answer is the current element (it's the first one that beats them). Elements left in the stack have no answer (−1).

**Complexity**  \nAmortized `O(n)`: each index pushed once, popped once.

**Common mistakes**
- `<=` vs `<` decides whether equal elements count as "greater" — wrong strictness breaks duplicate handling (e.g. "sum of subarray minimums" needs *strict* on one side, *non-strict* on the other for correct boundaries).
- Storing values instead of indices (loses positions).

---

### 3.3 Contribution counting (histogram / subarray min-max sums)

**Definition**  \nFor each element, find the range where it is the min (or max), then add `a[i] · leftChoices · rightChoices` to the answer.

**How it works**
1. Compute previous-smaller (strict) and next-smaller (non-strict) — boundaries where `a[i]` stops being the minimum.
2. Width = `(i - p) · (n - i)` style product.
3. Sum contributions → `O(n)` total (vs `O(n²)` subarray enumeration).

**Why it is needed**  \nLargest rectangle in histogram, sum of subarray minimums/maximums, sum of subarray ranges — all are range-contribution problems.

---

### 3.4 Queue patterns (BFS, two-stack/queue interop)

- **BFS**: frontier queue — processes in distance order (§15).
- **Queue using two stacks**: push all to `in`; pop from `out` (flip when empty) — amortized `O(1)`.
- **Stack using one queue**: rotate `n-1` elements to the back after each push.
- **Deque for window max**: see §10 — maintain decreasing values in the deque.

---

### 3.5 Expression conversion & evaluation

**Definition**  \nInfix (`a+b`) ↔ postfix (`ab+`) ↔ prefix (`+ab`) via precedence + associativity rules using a stack.

**Rules**
- **Postfix evaluation**: operands on stack; on operator, pop `b`, pop `a`, push `a op b` (order matters for `-`, `/`).
- **Infix → postfix**: push operators with `>=` precedence (left-assoc); `(` pushed; `)` pops until `(`.
- **Prefix**: right-to-left scan, or reverse-complement trick.

**Precedence**: `^` (right-assoc) > `*`,`/` > `+`,`-`.

**Common mistake**  \nSwapping operand order for postfix (`b op a` instead of `a op b`) — wrong for subtraction/division.

---

## 4. PATTERN LIBRARY

### P1 — Valid Parentheses / Nesting Stack

#### What is the pattern?
Push openers; on a closer, verify/pop the matching top; answer = stack empty at end.

#### When should I recognize it?
- "Valid parentheses / brackets", "remove outermost parentheses", "max nesting depth", "reverse substrings in brackets".

#### Core intuition
Nesting is LIFO: the *most recent* opener must be closed first.

#### Generic algorithm
1. `for c in s`: open → push (or `depth++`); close → check top matches (or `depth--` with validation).
2. Valid iff stack empty (and never popped empty / never negative depth).

#### C++ template
```cpp
bool isValid(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(') st.push(')');
        else if (c == '[') st.push(']');
        else if (c == '{') st.push('}');
        else { if (st.empty() || st.top() != c) return false; st.pop(); }
    }
    return st.empty();
}
```

#### Time / Space
`O(n)` / `O(n)`.

#### Edge cases
Empty string (valid); closers first; interleaved types `([)]`; unbalanced leftovers.

#### Common mistakes
Checking `st.top()` before `st.empty()`; using a plain counter when bracket *types* matter.

#### Variations
Depth counter for single-type nesting; min insertions = simulate and count unclosed.

#### Practice mapping
- `07-Check-Balanced-Parentheses.cpp`, `01-Remove-Outermost-Parentheses.cpp`, `09-Max-Nesting-Depth.cpp`, `05-Valid-Parenthesis-String.cpp` (§12), `27-Stock-Span.cpp`

---

### P2 — Monotonic Stack (NGE / NSE / PGE / PSE)

#### What is the pattern?
One pass with a stack sorted in monotone order; pops are answered by the current element.

#### When should I recognize it?
- "Next greater element", "next smaller", "previous greater/smaller", "span", "temperature warmer day", "sum of subarray minimums/maximums", "trapping rain water", "largest rectangle in histogram".

#### Core intuition
An element waits in the stack until something *strictly better* (per query direction) arrives — that arrival is its answer; otherwise the array end is its answer (−1).

#### Generic algorithm (next greater, right side)
1. Scan L→R with a stack of **indices** in decreasing value order.
2. While `!st.empty() && a[st.top()] <= a[i]`: `ans[st.top()] = a[i]`; pop.
3. Push `i`. Leftover indices → `-1`.

#### C++ template
```cpp
vector<int> nge(const vector<int>& a) {
    int n = a.size(); vector<int> r(n, -1); vector<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.back()] <= a[i]) st.pop_back();
        if (!st.empty()) r[i] = a[st.back()];
        st.push_back(i);
    }
    return r;
}
```

#### Time / Space
Amortized `O(n)` (each index pushed/popped once) / `O(n)`.

#### Edge cases
All equal (strictness decides); increasing/decreasing arrays (one side never pops); single element.

#### Common mistakes
`<=` vs `<` (duplicate semantics); storing values instead of indices; wrong scan direction for "previous".

#### Variations
Circular array (`i % n` with `2n` loop); contribution counting for subarray min/max sums; two-pass (left + right) for boundary-sensitive problems.

#### Practice mapping
- `15-Next-Greater-Element.cpp`, `16-Next-Greater-Element-II.cpp`, `17-Next-Smaller-Element.cpp`, `18-Number-of-NGEs.cpp`, `19-Trapping-Rain-Water.cpp`, `20-Sum-of-Subarray-Minimums.cpp`, `22-Sum-of-Subarray-Ranges.cpp`, `27-Stock-Span.cpp`

---

### P3 — Contribution Counting (histogram / maximal rectangle)

#### What is the pattern?
For each element, compute the maximal range where it is the min/max/histogram-bar, then add `value × width` contributions.

#### When should I recognize it?
- "Largest rectangle in histogram", "maximal rectangle of 1s", "sum of subarray minimums".

#### Core intuition
Instead of enumerating subareas (`O(n²)`), ask for each bar: *how far does it extend as the limiting height?* → previous-smaller + next-smaller brackets it.

#### Generic algorithm
1. Histogram: `left[i]` = previous smaller index (strict), `right[i]` = next smaller (non-strict) — pick one strictness consistently to avoid double counting.
2. `area = a[i] * (right[i] - left[i] - 1)`.
3. Maximal rectangle: treat each row as histogram base, heights = consecutive 1s above.

#### C++ template
```cpp
// heights h[], sentinel-appended stack approach
long long largestRectangle(vector<int>& h) {
    h.push_back(0);                 // sentinel flushes stack
    vector<int> st; long long best = 0;
    for (int i = 0; i < (int)h.size(); i++) {
        while (!st.empty() && h[st.back()] > h[i]) {
            int ht = h[st.back()]; st.pop_back();
            int left = st.empty() ? -1 : st.back();
            best = max(best, 1LL * ht * (i - left - 1));
        }
        st.push_back(i);
    }
    h.pop_back();
    return best;
}
```

#### Time / Space
`O(n)` / `O(n)` per histogram row → `O(m·n)` for maximal rectangle.

#### Edge cases
Empty histogram; all equal heights; strictly increasing (right never pops — sentinel handles it); zero heights.

#### Common mistakes
Forgetting the sentinel (last bars never evaluated); inconsistent strictness (double/zero counting); not resetting heights between rows.

#### Variations
Sum of subarray minimums uses *counts* `(i - left) * (right - i)` instead of max.

#### Practice mapping
- `24-Largest-Rectangle-Histogram.cpp`, `25-Maximal-Rectangle.cpp`, `20-Sum-of-Subarray-Minimums.cpp`, `56-Largest-Rectangle-Done.cpp` (§16 DP variant)

---

### P4 — Min-Stack / Queue-with-Stacks (auxiliary structure pairs)

#### What is the pattern?
Pair the primary structure with an auxiliary one that tracks the "extra" answer (min, reversed order).

#### When should I recognize it?
- "Min stack with O(1) min", "max stack", "queue using two stacks", "stack using queue", "implement queue with limited API".

#### Core intuition
Every push also records the *running best* (min/max) or routes through a second container so the overall discipline (LIFO/FIFO) is preserved.

#### Generic algorithm
- **Min stack**: push `(x, min(x, prevMin))`; top/min read from the pair.
- **Queue via 2 stacks**: `in` for pushes; when `out` empty, flip all of `in` into `out` — each element flipped once → amortized `O(1)`.

#### C++ template
```cpp
stack<pair<int,int>> st;   // (value, minSoFar)
void push(int x) {
    int m = st.empty() ? x : min(x, st.top().second);
    st.push({x, m});
}
int getMin() { return st.top().second; }
```

#### Time / Space
Push/pop `O(1)` amortized (queue) / `O(1)` strict (pair stack); `O(n)` space.

#### Edge cases
Single element; popping when auxiliary empties (queue flip trigger); overflow in `2x - top` trick (prefer pairs).

#### Common mistakes
Forgetting to flip only when `out` is empty (breaking amortization); `2x - top` overflow for large values.

#### Variations
Constant-space min stack (2x−top encoding — know its overflow caveat); deque-based sliding max (P5).

#### Practice mapping
- `08-Min-Stack.cpp`, `03-Stack-Using-Queue.cpp`, `04-Queue-Using-Stack.cpp`, `05-Stack-Using-LL.cpp`, `06-Queue-Using-LL.cpp`, `01-Stack-Using-Arrays.cpp`, `02-Queue-Using-Arrays.cpp`

---

### P5 — Monotonic Deque (sliding window maximum / minimum)

#### What is the pattern?
A deque stores *candidate indices* in decreasing (max) or increasing (min) value order; stale (out-of-window) indices are popped from the front.

#### When should I recognize it?
- "Sliding window maximum/minimum", "constraint problems needing window max in `O(1)`", "jump game with window-based reachability".

#### Core intuition
While adding `a[i]`, pop back while `a[back] <= a[i]` (they can never be the max while `i` is inside). Front always holds the max of the current window; expire `front <= i-k`.

#### Generic algorithm
```text
for i:
    while !dq.empty && a[dq.back] <= a[i]: pop_back
    push_back(i)
    while dq.front <= i - k: pop_front        (expired)
    if i >= k-1: answer[i] = a[dq.front]
```

#### C++ template
```cpp
vector<int> maxSlidingWindow(vector<int>& a, int k) {
    deque<int> dq; vector<int> out;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();
        if (i >= k - 1) out.push_back(a[dq.front()]);
    }
    return out;
}
```

#### Time / Space
`O(n)` (each index pushed/popped once) / `O(k)`.

#### Edge cases
`k = 1`; decreasing array (front never stale from back); duplicates (`<=` pops them).

#### Common mistakes
Expiring *before* pushing vs after (both work — but be consistent with index bounds); storing values instead of indices (can't check expiry).

#### Variations
Monotonic **min** deque for window minimums; two deques for min+max simultaneously.

#### Practice mapping
- `26-Sliding-Window-Maximum.cpp`, `10-Sliding-Window-and-Two-Pointer/` (window problems)

---

### P6 — LRU / LFU Cache (hash + linked list / counts)

#### What is the pattern?
Hash map for `O(1)` lookup + doubly linked list (or count buckets) for `O(1)` recency/frequency ordering.

#### When should I recognize it?
- "Design an LRU cache", "LFU cache", "evict least recently used".

#### Core intuition
List order = recency order; a hit moves a node to the head (`O(1)` with a DLL); eviction removes the tail. Hash maps node key → pointer.

#### Generic algorithm
- `get(key)`: lookup → move node to head → value.
- `put(key,val)`: insert at head; if over capacity → remove tail (and its hash entry).

#### C++ template
```cpp
// structure (sketch): list<pair<int,int>> lru; unordered_map<int, list<...>::iterator> pos;
// get: splice node to front; put: push_front, if size>cap: erase pos[lru.back().first], pop_back
```

#### Time / Space
`O(1)` get/put average / `O(capacity)`.

#### Edge cases
Capacity 0/1; updating an existing key (must move, not duplicate); evicting while inserting.

#### Common mistakes
Hash entry not erased on eviction (dangling iterator); not moving nodes on `get` (violates recency).

#### Variations
LFU: frequency map + bucket per count (min-heap alternative `O(log n)`).

#### Practice mapping
- `29-LRU-Cache.cpp`, `30-LFU-Cache.cpp`

---

## 5. PATTERN RECOGNITION

| If the problem says... | Think about... |
|---|---|
| "matching brackets / valid parentheses" | stack of expected closers |
| "remove outermost / nesting depth" | depth counter or stack |
| "next/previous greater/smaller" | monotonic stack (§ P2) |
| "sum of subarray minimums / ranges" | contribution counting (P3) |
| "largest rectangle / maximal rectangle" | histogram + sentinel stack (P3) |
| "sliding window maximum" | monotonic deque (P5) |
| "min stack" / "queue via stacks" | auxiliary pair structures (P4) |
| "infix / postfix / prefix" | precedence + stack |
| "LRU / LFU cache" | hash + DLL (P6) |
| "BFS / shortest path unweighted" | queue (§15) |
| "undo the last action" | stack discipline |
| "first-in-first-out processing" | queue |

**Decision rules**
1. **Nesting / matching / undo** → stack.
2. **"Nearest greater/smaller"** → monotonic stack; **"window max/min"** → monotonic deque.
3. **"Sum over all subarrays of min/max"** → contribution counting, not enumeration.
4. **Order = arrival** → queue; **order = recency** → stack.
5. **Need O(1) min/max alongside a stack** → pair encoding.

---

## 6. BRUTE → BETTER → OPTIMAL THINKING

### Next Greater Element
- **Brute** — for each `i`, scan right until greater: `O(n²)`.
- **Better** — scan from the right, but maintain results smartly: still needs ordered candidates.
- **Optimal** — monotonic stack: `O(n)` amortized. Proof of optimality: each element is pushed/popped at most once → total ≤ `2n` operations.

### Largest rectangle in histogram
- **Brute** — for each bar, expand left/right while height allows: `O(n²)`.
- **Better** — precompute previous/next smaller with two monotonic passes: `O(n)` + `O(n)`.
- **Optimal** — single sentinel stack pass computing widths on pops: `O(n)` time, `O(n)` space — same asymptotics, one pass, less code.

### Sum of subarray minimums
- **Brute** — enumerate all `n(n+1)/2` subarrays, min each: `O(n²)` (or `O(n³)` naive).
- **Better** — DP of min-ending-here: `O(n²)` → still slow.
- **Optimal** — for each element, count subarrays where it is the minimum `(i - left) * (right - i)` using PSE/NSE: `O(n)`. This "count contributions" leap is the chapter's key idea.

### Sliding window maximum
- **Brute** — recompute max per window: `O(nk)`.
- **Better** — heap of window indices with lazy expiry: `O(n log n)`.
- **Optimal** — monotonic deque: `O(n)` total — each index enqueued/dequeued once.

### Valid parentheses
- **Brute** — repeatedly delete matching pairs until stable: `O(n²)`.
- **Better** — counter for counts (works only for one bracket type): `O(n)`.
- **Optimal** — stack: `O(n)` time, `O(n)` space — necessary for type-matching (information-theoretically, you must remember unmatched openers).

### Key transferable idea
> Stack problems reduce to: *"what does the most recent unfinished thing need?"* — the stack stores exactly the unfinished things in order of recency.

---

## 7. C++ / STL TOOLKIT

| Tool | Syntax | Notes |
|---|---|---|
| `stack` | `st.push/top/pop/empty` | LIFO, default `deque` container |
| `queue` | `q.push/front/pop` | FIFO |
| `deque` | `dq.push_back/pop_front/...` | double-ended `O(1)` |
| `priority_queue` | max by default; `greater<>` for min | heap (§11) |
| `list` (DLL) | `splice`, `insert`, `erase` | O(1) relink — LRU building block |
| Array as stack | `vector<int> st; st.push_back(); st.pop_back();` | faster than `std::stack` in practice |

```cpp
// vector-based stack (preferred in CP)
vector<int> st;
st.push_back(x);
int t = st.back(); st.pop_back();

// deque window
deque<int> dq;
dq.push_back(i);
if (dq.front() <= i - k) dq.pop_front();

// postfix evaluation
for (char c : s) {
    if (isdigit(c)) st.push(c - '0');
    else { int b = st.back(); st.pop_back(); int a = st.back(); st.pop_back();
           st.push(apply(c, a, b)); }
}
```

**Common mistakes**
- `st.top()` / `q.front()` on empty → UB; check first.
- Mixing `push`/`pop` return types: `pop()` returns `void` — capture `top()` before popping.
- Using `stack<int, vector<int>>` and then `st.back()` — `std::stack` has no `.back()`; use `.top()`.

---

## 8. COMPLEXITY GUIDE

| Operation | Time | Space |
|---|---:|---:|
| stack/queue push·pop·top | `O(1)` | `O(n)` total |
| deque both ends | `O(1)` amortized | `O(n)` |
| Monotonic stack (whole scan) | `O(n)` amortized | `O(n)` |
| Monotonic deque (window max) | `O(n)` | `O(k)` |
| Valid parentheses | `O(n)` | `O(n)` |
| Infix→postfix | `O(n)` | `O(n)` |
| Largest rectangle (stack) | `O(n)` | `O(n)` |
| Sum subarray mins (contribution) | `O(n)` | `O(n)` |
| Maximal rectangle (m rows) | `O(m·n)` | `O(n)` |
| LRU get/put | `O(1)` avg | `O(capacity)` |
| Queue via 2 stacks (amortized) | `O(1)` per op | `O(n)` |

**How to estimate** — the amortization argument is everything: "each element pushed once, popped once ⇒ ≤ 2n operations total" proves `O(n)` for any monotonic structure.

---

## 9. EDGE CASES

- **Empty string / expression** — valid parentheses = true; evaluation = 0/undefined — check spec.
- **Single bracket / single element** — stack never deep; still validate.
- **All-equal heights** — histogram area = `n · h`; strictness in pop condition decides widths.
- **Strictly increasing/decreasing arrays** — monotonic stack never pops on one side → sentinel needed for histogram flush.
- **`k > n`** for window deque — no full window; guard `i >= k-1`.
- **Duplicate values** — decide `<=` vs `<` deliberately (equal elements' answer semantics).
- **Circular arrays** — loop `2n` with `i % n`, but limit answers to first `n`.
- **Overflow** — area computations (`height × width`) can exceed `2·10^9` → `long long`.
- **Expression edge** — missing operand, double operators, division by zero in evaluation.
- **LRU capacity 0** — evict everything immediately; map must stay empty.

---

## 10. COMMON MISTAKES

| # | Mistake | What goes wrong | Why | How to avoid |
|---|---|---|---|---|
| 1 | `top()`/`front()` on empty | UB / crash | unchecked pops | guard `!st.empty()` first |
| 2 | Wrong pop strictness (`<` vs `<=`) | duplicate answers wrong | equal-element semantics | decide per problem; write it down |
| 3 | Forgetting histogram sentinel | last bars never measured | stack never flushed | append `0` (or handle tail after loop) |
| 4 | Storing values not indices in monotonic stack | can't check window expiry | lost positions | store indices |
| 5 | Contribution double-counting | answers too large | strictness identical on both sides | strict on left, non-strict on right |
| 6 | Wrong scan direction for "previous" | mirrored answers | NGE right ≠ NGE left | reverse loop for previous queries |
| 7 | `pop()` then use old `top` logic | wrong value | `pop` returns void | capture before popping |
| 8 | Postfix operand order | `a-b` computed as `b-a` | stack LIFO | pop `b` first, then `a` → `a op b` |
| 9 | Circular NGE missing modulo | reads out of bounds | array is circular | `i % n`, loop `2n` |
| 10 | Deque storing values (window max) | can't detect expiry | need indices | store indices; compare `i - k` |

**Conceptual mistakes**
- Using a plain counter for multi-type parentheses (needs type-matching stack).
- Assuming `O(1)` "top" means `O(1)` "remove from middle" — heaps/stacks don't support arbitrary removal (use lazy deletion / DLL).
- Re-solving with `O(n²)` expansion when the amortized push-pop argument gives `O(n)`.

---

## 11. IMPORTANT FORMULAS / RULES

```text
Monotonic NGE:  scan R->L (for right answers) or L->R; pop while condition; leftover = -1
Amortization:   each index pushed 1x, popped 1x  =>  total <= 2n ops => O(n)

Contribution (min of subarray):   count(i) = (i - psee[i]) * (nsee[i] - i)
Histogram area for bar i:         h[i] * (right_boundary - left_boundary - 1)
Maximal rectangle:                for each row: heights[r][c] = heights[r-1][c] + 1 (if '1')

Trapping water:                    sum over i of  min(maxLeft, maxRight) - h[i]
                                   (or two-pointer O(1) space)

Postfix eval:                      pop b, pop a, push a op b
Infix->postfix:                    higher/equal precedence pops (left-assoc); '^' right-assoc

Task scheduler length:             max(total, (maxFreq - 1) * (n + 1) + countMax)   [§12]
```

**Rules / invariants**
1. Stack of indices, monotone values — always.
2. Left answers: scan left→right; right answers: scan right→left (or vice versa depending on setup).
3. One strict side + one non-strict side when counting disjoint ranges.

---

## 12. REUSABLE TEMPLATES

```cpp
// 1. Next greater element (right side)
vector<int> nge(const vector<int>& a) {
    int n = a.size(); vector<int> r(n, -1); vector<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.back()] <= a[i]) st.pop_back();
        if (!st.empty()) r[i] = st.back();
        st.push_back(i);
    }
    return r;
}

// 2. Valid parentheses
bool isValid(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(') st.push(')');
        else if (c == '[') st.push(']');
        else if (c == '{') st.push('}');
        else { if (st.empty() || st.top() != c) return false; st.pop(); }
    }
    return st.empty();
}

// 3. Sliding window maximum (monotonic deque)
vector<int> maxSlidingWindow(vector<int>& a, int k) {
    deque<int> dq; vector<int> out;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();
        if (i >= k - 1) out.push_back(a[dq.front()]);
    }
    return out;
}

// 4. Largest rectangle in histogram (sentinel)
long long largestRectangle(vector<int> h) {
    h.push_back(0);
    vector<int> st; long long best = 0;
    for (int i = 0; i < (int)h.size(); i++) {
        while (!st.empty() && h[st.back()] > h[i]) {
            int ht = h[st.back()]; st.pop_back();
            int left = st.empty() ? -1 : st.back();
            best = max(best, 1LL * ht * (i - left - 1));
        }
        st.push_back(i);
    }
    return best;
}
```

## 13. ADVANCED CONCEPTS

### 13.1 Cartesian tree / max-stack variations
The monotonic stack builds a *Cartesian tree* implicitly (parent = next greater) — used in range-min queries and tree DP on arrays. Recognize "implicit tree from array with min/max parent" phrasing.

### 13.2 Sum of subarray minimums with modulo / large n
Contribution counting with `long long` and sometimes `(i - p) * (n - s)` computed in 64-bit before modulo — the pattern scales to counting *all* subarrays satisfying min/max conditions.

### 13.3 Online bracket matching with hash of strings
Reverse Polish with strings, or checking "valid math expressions" with variable precedence — extend the same stack rules; precedence table becomes a map.

### 13.4 Sparse table + RMQ alternative
When you only need range min/max queries (not nearest-greater semantics), a sparse table answers `O(1)` after `O(n log n)` preprocessing — sometimes replaces the monotonic stack. Mention as the "other" range-extremum tool.

### 13.5 Persistent / functional stacks
Immutable stacks sharing structure (used in functional programming and some DP optimizations) — each push copies only the path: `O(log n)` per version. Advanced topic; recognize the idea.

### 13.6 Monotonic queue in DP optimization (Divide & Conquer / Knuth)
Deque-based sliding maxima feed into DP optimizations (monotone queue optimization for `dp[i] = min(dp[j] + C(j,i))` when quadrangle inequality holds) — bridge into advanced DP (§16).

---

## 14. CONNECTIONS BETWEEN PATTERNS

```text
LIFO need (nesting/undo)
    |
    v
Stack  ---------> monotonic stack ---------> contribution counting
    |                    |                         |
    |                    v                         v
    |             NGE/NSE/PGE/PSE          histogram / subarray min-max
    |
FIFO need (arrival/BFS)
    |
    v
Queue  ---------> monotonic deque ---------> sliding window max (bridge to §10)
    |
    v
BFS in graphs (§15)

Auxiliary pair (min-stack, 2-stack queue) = same idea with extra state
LRU = stack discipline + hash map + DLL (§06)
```

**Mental map** — *nesting→stack; nearest-greater→monotonic stack; window-extremum→monotonic deque; arrival→queue; recency cache→LRU.*

---

## 15. PROBLEM → PATTERN MAPPING

*(Reference only — solutions and approaches live in the `.cpp` files.)*

### Implementations (stack / queue from scratch)
- `01-Stack-Using-Arrays.cpp`
- `02-Queue-Using-Arrays.cpp`
- `03-Stack-Using-Queue.cpp`
- `04-Queue-Using-Stack.cpp`
- `05-Stack-Using-LL.cpp`
- `06-Queue-Using-LL.cpp`

### Nesting / parentheses / min-stack
- `07-Check-Balanced-Parentheses.cpp`
- `08-Min-Stack.cpp`
- `21-Asteroid-Collision.cpp`
- `23-Remove-K-Digits.cpp`

### Expression conversion
- `09-Infix-to-Postfix.cpp`
- `10-Prefix-to-Infix.cpp`
- `11-Prefix-to-Postfix.cpp`
- `12-Postfix-to-Prefix.cpp`
- `13-Postfix-to-Infix.cpp`
- `14-Infix-to-Prefix.cpp`

### Monotonic stack (NGE family / subarray sums)
- `15-Next-Greater-Element.cpp`
- `16-Next-Greater-Element-II.cpp`
- `17-Next-Smaller-Element.cpp`
- `18-Number-of-NGEs.cpp`
- `19-Trapping-Rain-Water.cpp`
- `20-Sum-of-Subarray-Minimums.cpp`
- `22-Sum-of-Subarray-Ranges.cpp`
- `27-Stock-Span.cpp`

### Histogram / rectangle contribution
- `24-Largest-Rectangle-Histogram.cpp`
- `25-Maximal-Rectangle.cpp`

### Monotonic deque (window max)
- `26-Sliding-Window-Maximum.cpp`

### Design / misc
- `28-Celebrity-Problem.cpp`
- `29-LRU-Cache.cpp`
- `30-LFU-Cache.cpp`

---

## 16. QUICK REVISION SHEET

**Concepts**
- Stack = LIFO (nesting, undo); Queue = FIFO (arrival, BFS).
- Monotonic stack: pop while condition; each index pushed/popped once → `O(n)`.
- Contribution counting: `value × (left choices × right choices)` beats enumeration.

**Recognition clues**
| Signal | Tool |
|---|---|
| brackets / nesting | stack or depth |
| next/previous greater/smaller | monotonic stack |
| subarray min/max sums | contribution counting |
| histogram / maximal rectangle | sentinel stack |
| window max/min | monotonic deque |
| min alongside stack | (value, minSoFar) pairs |
| LRU/LFU | hash + DLL |

**Algorithms (memorize)**
```text
NGE:       while (!st.empty() && a[st.back()] <= a[i]) -> answer pop; push i
Histogram: append sentinel 0; area = h * (i - left - 1) on pop
Window max: pop_back while a[back] <= a[i]; expire front <= i-k
Postfix:   pop b, pop a, push a op b
```

**Complexity** — all monotonic scans `O(n)` amortized / `O(n)` space · LRU `O(1)` · maximal rectangle `O(m·n)`.

**Common mistakes** — empty-top · strictness `<=` vs `<` · missing sentinel · values vs indices · wrong scan direction · postfix operand order.

**Decision rules** — nesting→stack · nearest-greater→monotonic · window→deque · arrival→queue · "sum over subarrays"→contribution.

---

## 17. INTERVIEW CHECKLIST

- [ ] Can I write the monotonic stack NGE template in both scan directions?
- [ ] Can I explain the amortized `O(n)` argument (push once, pop once)?
- [ ] Can I derive largest-rectangle widths from previous/next smaller?
- [ ] Can I handle strictness (duplicates) deliberately in pop conditions?
- [ ] Can I write the sliding window max with a deque (indices, expiry)?
- [ ] Can I evaluate postfix and convert infix↔postfix with precedence?
- [ ] Can I implement min-stack with pairs and justify its `O(1)`?
- [ ] Can I design an LRU cache with hash + list operations?
- [ ] Can I state edge cases (empty, single, all-equal) before coding?
- [ ] Can I move from `O(n²)` brute force to the monotonic `O(n)` and explain why?

<!-- done -->