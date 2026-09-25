# 06 — Linked List — Complete Pattern-Based Notes

---

## 1. Topic Overview

A **linked list** stores elements in nodes connected by pointers — no contiguous layout, no index access, but `O(1)` splices anywhere once you hold a reference.

**What it is**
A chain of nodes: each node holds data + a pointer to the next node (doubly linked lists also point backward). The list is accessed through `head` (and optionally `tail`).

**Why it is important**
- Teaches **pointer manipulation** — the single most error-prone interview skill.
- Core patterns (dummy node, fast/slow pointers, in-place reversal, merge) transfer to trees, graphs, and LRU caches.
- Many array problems become elegant with list surgery (reorder, merge, partition).

**Where it is used**
- LRU/LFU caches (doubly linked list + hash map).
- Undo/redo stacks, memory allocators, browser history.
- Interview staples: cycle detection, middle node, reverse, merge, intersection.

**How it connects to other topics**
- §13 Trees: trees are "linked lists with two pointers"; recursion patterns mirror list recursion.
- §09 Stack/Queue: stacks/queues can be implemented on linked lists; LRU uses both.
- §11 Heap / §12 Greedy: merge-K-sorted uses list merging.

**Interview memory hook:** *Dummy node for edge-case deletions/inserts. Fast/slow for middle & cycles. prev/curr for reversal. Draw the three pointers before coding.*

---

## 2. Fundamentals

### 2.1 Node structure

```cpp
struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};
// doubly linked:
// Node* prev;
```

### 2.2 Traversal — the only primitive

```cpp
for (Node* cur = head; cur; cur = cur->next) { /* visit cur */ }
```

Everything (count, search, print) is traversal with different work inside.

### 2.3 Terminology

| Term | Meaning |
|---|---|
| **Head** | First node; `nullptr` = empty list. |
| **Tail** | Last node (`next == nullptr`). |
| **Dummy node** | Temporary sentinel before `head`; avoids null-head special cases. |
| **Fast / slow** | Two walkers at different speeds (Floyd's tortoise & hare). |
| **K-group** | Chunk of `k` consecutive nodes processed together. |
| **Intersection (Y-shape)** | Two lists merging into one common tail. |
| **Cycle** | Some node's `next` leads back to an earlier node. |

### 2.4 Why linked lists exist (vs arrays)

| Operation | Array | Linked list |
|---|---|---|
| Access by index | `O(1)` | `O(n)` |
| Insert/delete at known node | `O(n)` shift | `O(1)` relink |
| Memory | contiguous, pre-sized | scattered, dynamic |

**Visual: the three-pointer reversal invariant**

```text
Before step:   prev | curr -> next -> rest
Relink:        curr -> prev
Advance:       prev = curr,  curr = next

Start: prev=nullptr, curr=head
 null <- 1    2 -> 3 -> null
 null <- 1 <- 2    3 -> null
 null <- 1 <- 2 <- 3
```

---

## 3. Core Concepts

### 3.1 Dummy node pattern

**Definition**  \nCreate a temporary node `dummy` whose `next` is the list head; all operations happen relative to `dummy`, and `dummy.next` is the final answer.

**Why it is needed**  \nDeleting/inserting at the head changes the answer pointer — without a dummy, you handle `head == nullptr` / head-deletion with extra branches, a classic bug source.

**How it works (delete node)**

```cpp
Node dummy(0); dummy.next = head;
Node* prev = &dummy;
while (prev->next && prev->next->val != target) prev = prev->next;
if (prev->next) prev->next = prev->next->next;   // skip over
return dummy.next;
```

**Common mistake**  \nReturning `dummy` instead of `dummy.next`, or losing the real head when no dummy is used.

---

### 3.2 Fast / slow pointers

**Definition**  \nTwo pointers start at `head`; slow moves 1 step, fast moves 2.

**Intuition**  \nIn a cycle, fast laps slow → they meet (cycle detection). Without a cycle, fast reaches the end while slow sits exactly at the **middle**.

**Results from one idea**
- **Middle**: slow = middle when fast hits end (even length: second middle).
- **Cycle detection**: `s == f` somewhere → cycle exists.
- **Cycle start**: after meeting, reset one pointer to head; both move 1 step → first common node = entry.
- **Cycle length**: walk from meeting point until back — count nodes.

**Complexity**  \n`O(n)` time, `O(1)` space.

**Common mistake**  \nMissing the `while (f && f->next)` guard → null dereference on acyclic lists.

---

### 3.3 In-place reversal

**Definition**  \nReverse the `next` direction of every node iteratively using `prev`, `curr`, `next`.

**Algorithm**
1. `next = curr->next` (save the rest).
2. `curr->next = prev` (flip link).
3. Advance `prev = curr`, `curr = next`.

**Recursive variant**: reverse the sublist after `head`, then fix `head->next->next = head`, `head->next = nullptr`.

**Variations**: reverse in groups of `k` (reverse each chunk, reconnect chunk tails); reverse a portion `[l..r]`; reverse a doubly linked list (swap `prev`/`next` only).

**Common mistake**  \nLosing the rest of the list before flipping `curr->next` — always save `next` first.

---

### 3.4 Merge two sorted lists

**Definition**  \nSplice nodes of two sorted lists into one by repeatedly attaching the smaller head.

**Intuition**  \nExactly the merge step of merge sort — but relinking nodes instead of copying.

**How it works**  \nDummy head + `while (a && b): attach smaller, advance it`; then attach whichever list remains.

**Complexity**  \n`O(n + m)` time, `O(1)` extra space (no new nodes).

**Extensions**: merge K sorted lists (§11 heap or divide-and-conquer pairwise merge); sort a linked list via merge sort → `O(n log n)`.

---

### 3.5 Add numbers digit-wise

**Definition**  \nNumbers stored as digit chains are added like column arithmetic.

**Intuition**  \nWalk both lists in parallel carrying `carry = sum / 10`; append `sum % 10`.

**Common mistakes**  \nForgetting a final `carry`; some variants store most-significant digit first (need stack or recursion); leading zeros.

---

### 3.6 Intersection, palindrome, clone

- **Y-intersection**: get lengths `lenA, lenB`; advance the longer by the difference; walk together — first shared node (pointer equality) is the intersection.
- **Palindrome list**: reverse second half, compare both halves, (optionally restore).
- **Clone with random pointer**: map `old → new` in one pass; or interleave copies and split.

---

## 4. PATTERN LIBRARY

### P1 — Dummy Node Splice (Insert / Delete / Merge)

#### What is the pattern?
Place a temporary `dummy` node before the head so every node — including the first — has a `prev`.

#### When should I recognize it?
- "Delete a node / remove nth from end / remove all occurrences", "merge two lists", "insert into sorted list", any operation that may change `head`.

#### Core intuition
Most linked-list bugs are "who is `prev` when we delete the head?" A dummy makes the answer uniform: `prev` always exists.

#### General approach
1. `dummy.next = head; prev = &dummy`.
2. Advance `prev` to the position *before* the action point.
3. Relink (`prev->next = ...`).
4. Return `dummy.next`.

#### C++ template
```cpp
Node* removeNthFromEnd(Node* head, int n) {
    Node dummy(0); dummy.next = head;
    Node *fast = &dummy, *slow = &dummy;
    for (int i = 0; i <= n; i++) fast = fast->next;   // n+1 ahead
    while (fast) { fast = fast->next; slow = slow->next; }
    slow->next = slow->next->next;
    return dummy.next;
}
```

#### Time / Space
`O(n)` time (one/two passes), `O(1)` space.

#### Edge cases
Empty list; delete the head; delete the tail; `n == length`.

#### Common mistakes
Returning `dummy` instead of `dummy.next`; off-by-one in the fast-lead distance.

#### Variations
Merge two sorted (attach smaller); remove all occurrences (keep deleting while match).

#### Practice mapping
- `03-Delete-Node.cpp`, `17-Remove-Nth-From-End.cpp`, `20-Intersection-Y.cpp`, `31-Merge-Two-Sorted-Lists.cpp`, `25-Delete-All-Occurrences-DLL.cpp`

---

### P2 — Fast / Slow Pointers (Middle, Cycle, Entry)

#### What is the pattern?
Two walkers, speed 1 vs 2, from the same start.

#### When should I recognize it?
- "Middle of the list", "does the list have a cycle", "start of the cycle", "palindrome list", "reorder list".

#### Core intuition
Speed ratio 2:1 means fast advances exactly one extra node per slow step → in a cycle the gap shrinks by 1 each step → meet. In a chain, fast at end ⇒ slow at middle.

#### General approach
1. `while (f && f->next)`: `s = s->next; f = f->next->next`.
2. Meeting ⇒ cycle; no meeting ⇒ no cycle; when `f` ends ⇒ `s` is middle.
3. Cycle entry: reset `s = head`, step both by 1 until equal.

#### C++ template
```cpp
bool hasCycle(Node* h) {
    Node *s = h, *f = h;
    while (f && f->next) { s = s->next; f = f->next->next; if (s == f) return true; }
    return false;
}
```

#### Time / Space
`O(n)` / `O(1)`.

#### Edge cases
Empty / single-node list; cycle at head; even vs odd length (middle convention).

#### Common mistakes
Missing `f->next` null check; resetting the wrong pointer for entry detection.

#### Variations
Cycle length (count from meeting); palindrome check (find middle, reverse second half, compare).

#### Practice mapping
- `11-Middle-of-Linked-List.cpp`, `12-Detect-Loop.cpp`, `13-Find-Loop-Length.cpp`, `14-Starting-Point-of-Loop.cpp`, `15-Check-Palindrome-LL.cpp`

---

### P3 — In-Place Reverse (prev / curr / next)

#### What is the pattern?
Three pointers walk the list flipping `next` links one at a time.

#### When should I recognize it?
- "Reverse the linked list", "reverse in groups of k", "reverse part of a list", "reorder list".

#### Core intuition
Before flipping `curr->next`, the rest of the list must be saved in a third pointer — `prev` alone loses it.

#### General approach
1. `prev = nullptr, curr = head`.
2. `next = curr->next; curr->next = prev; prev = curr; curr = next`.
3. Final answer is `prev`.

#### C++ template
```cpp
Node* reverse(Node* h) {
    Node* prev = nullptr;
    while (h) { Node* nxt = h->next; h->next = prev; prev = h; h = nxt; }
    return prev;
}
```

#### Time / Space
`O(n)` / `O(1)` iterative; recursion is `O(n)` stack.

#### Edge cases
Empty list; single node; already-reversed input.

#### Common mistakes
Losing `nxt` before relinking; returning `h` (now the tail) instead of `prev`.

#### Variations
K-group (reverse each chunk, stitch tails); recursive reversal; doubly linked (swap both pointers).

#### Practice mapping
- `10-Reverse-Linked-List.cpp`, `09-Reverse-DLL.cpp`, `27-Reverse-Nodes-in-K-Group.cpp`, `28-Rotate-Linked-List.cpp`

---

### P4 — Merge-Based Patterns (two-way, K-way, sort-by-merge)

#### What is the pattern?
Repeatedly attach the smallest head of sorted streams — linear merge of two, heap/divide of K.

#### When should I recognize it?
- "Merge two sorted lists", "merge K sorted lists", "sort a linked list", "sort 0/1/2 in one pass", "add two numbers as digit chains".

#### Core intuition
Sorted streams can be interleaved in total-linear time because the next smallest element is always at one of the heads.

#### General approach
1. Dummy head.
2. `while (a && b): attach smaller, advance it`.
3. Attach remainder.
4. For K lists: min-heap of heads (`O(N log K)`) or pairwise divide-and-conquer.

#### C++ template
```cpp
Node* mergeTwo(Node* a, Node* b) {
    Node dummy(0); Node* t = &dummy;
    while (a && b) {
        if (a->data <= b->data) { t->next = a; a = a->next; }
        else                    { t->next = b; b = b->next; }
        t = t->next;
    }
    t->next = a ? a : b;
    return dummy.next;
}
```

#### Time / Space
Two-way `O(n + m)` / `O(1)`; K-way heap `O(N log K)` / `O(K)`; pairwise merge `O(N log K)` / `O(log K)` recursion.

#### Edge cases
One list empty; equal elements (stability: prefer `<=`); K = 0.

#### Common mistakes
Losing the remainder list; unstable comparisons breaking equal-value order; pushing all nodes of a list into the heap instead of heads.

#### Variations
Three-way partition of 0/1/2 (Dutch flag on list); merge into sorted via repeated merge.

#### Practice mapping
- `31-Merge-Two-Sorted-Lists.cpp`, `23-Sort-Linked-List.cpp`, `19-Sort-012-LL.cpp`, `11-Heap/09-Merge-M-Sorted-Lists.cpp`

---

### P5 — Arithmetic on Digit Chains

#### What is the pattern?
Walk two lists in lockstep while carrying `carry`, appending `sum % 10` nodes.

#### When should I recognize it?
- "Add two numbers", "add 1 to a number represented as list", "multiply as list", "reverse digits".

#### Core intuition
The list *is* positional notation; align least-significant digits (or most-significant, depending on statement), simulate column addition.

#### General approach
1. Determine digit order (LeetCode "Add Two Numbers" = least-significant first).
2. Loop while either list has nodes or `carry != 0`.
3. Create node per digit; never drop the final carry.

#### C++ template
```cpp
Node* addTwo(Node* a, Node* b) {
    Node dummy(0); Node* t = &dummy; int carry = 0;
    while (a || b || carry) {
        int s = carry + (a ? a->data : 0) + (b ? b->data : 0);
        t->next = new Node(s % 10); t = t->next;
        carry = s / 10;
        if (a) a = a->next;
        if (b) b = b->next;
    }
    return dummy.next;
}
```

#### Time / Space
`O(max(n, m))` / `O(1)` extra (excluding output).

#### Edge cases
Different lengths; leading zeros in result; final carry creating a new head; both lists empty.

#### Common mistakes
Dropping final carry; assuming equal lengths; forgetting digit order (MSD-first needs stack/reverse).

#### Variations
Add 1 (carry propagation to head — use stack or reverse first); sum of two numbers as list vs integer.

#### Practice mapping
- `22-Add-Two-Numbers.cpp`, `21-Add-1-to-Number-LL.cpp`

---

### P6 — Partition / Reorder Patterns

#### What is the pattern?
Rebuild the list by *collecting nodes into buckets* (by value or position) and relinking — one pass out, one pass stitch.

#### When should I recognize it?
- "Odd-even positions", "segregate odd/even (DLL)", "reorder list", "flatten a multi-level list", "rotate by k", "pairs with given sum in DLL".

#### Core intuition
Values/positions are known in one traversal → build several chains simultaneously → concatenate. Rotation = cut the list at `n - k%n` and reattach the tail to the head.

#### General approach
1. Traverse, appending current node to its bucket chain (advance bucket tail).
2. Stitch buckets head-to-tail.
3. Fix tails (`tail->next = nullptr`).

#### C++ template
```cpp
Node* oddEven(Node* head) {
    Node oddH(0), evenH(0); Node *o = &oddH, *e = &evenH; int i = 1;
    while (head) {
        if (i++ & 1) { o->next = head; o = o->next; }
        else         { e->next = head; e = e->next; }
        head = head->next;
    }
    e->next = nullptr; o->next = evenH.next;   // tail of even must end
    return oddH.next;
}
```

#### Time / Space
`O(n)` / `O(1)`.

#### Edge cases
Single node; empty list; forgetting to terminate the last chain (creates a cycle!); DLL `prev` pointers not repaired.

#### Common mistakes
Leaving `tail->next` pointing into the old structure; not fixing `prev` in doubly linked lists; rotation with `k > n` or `k = 0`.

#### Variations
Flatten sorted multilevel list (merge down + right); clone with random pointer (hash map or interleaving); pairs with given sum in sorted DLL (two pointers).

#### Practice mapping
- `16-Odd-Even-Linked-List.cpp`, `24-Segregate-Odd-Even-DLL.cpp`, `28-Rotate-Linked-List.cpp`, `29-Flatten-LL.cpp`, `30-Clone-with-Random-Pointer.cpp`, `26-Pairs-with-Given-Sum-DLL.cpp`

---

## 5. PATTERN RECOGNITION

| If the problem says... | Think about... |
|---|---|
| "delete/remove a node, possibly the head" | Dummy node splice |
| "Nth from the end" | Two pointers with N-gap lead |
| "middle of list" | Fast/slow pointers |
| "cycle / loop / starting point of loop" | Floyd: meet → reset → entry |
| "reverse the list / in groups / part" | prev-curr-next (or recursion) |
| "merge two / K sorted lists" | Dummy + attach-smaller (+ heap for K) |
| "sort a linked list" | Merge sort `O(n log n)` |
| "add two numbers as lists" | Lockstep walk + carry |
| "odd-even / segregate / reorder / rotate" | Bucket collection + stitch |
| "palindrome list" | Find middle → reverse second half → compare |
| "intersection of two lists" | Length-align then lockstep |
| "flatten / clone" | Merge-down pattern / hash map or interleaving |
| "DLL operations" | Same patterns + repair `prev` |

**Decision rules**
1. Can the head change? → **dummy**.
2. Does it ask middle/cycle/nth-from-end? → **fast/slow**.
3. Is order reversed or chunked? → **three-pointer reverse**.
4. Are streams sorted? → **merge**.
5. Two lists in lockstep? → align first (length or gap), then walk.

---

## 6. BRUTE → BETTER → OPTIMAL THINKING

### Delete Nth node from end
- **Brute** — reverse the list, delete Nth from front, reverse back: `O(n)` but 3 passes and destructive.
- **Better** — count length, delete at `len-n`: `O(n)` two passes.
- **Optimal** — one pass: fast pointer leads by `n+1`, dummy handles head deletion: `O(n)` time, `O(1)` space, single traversal.

### Detect a cycle
- **Brute** — hash set of visited nodes: `O(n)` time but `O(n)` space — flags "seen", doesn't use list structure.
- **Better** — store visited flag inside nodes: `O(1)` extra space but mutates input (often disallowed).
- **Optimal** — fast/slow: `O(n)` time, `O(1)` space, no mutation. Proof: the gap between them shrinks by 1 each step inside a cycle, so they must meet.

### Reverse a list
- **Brute** — copy into array, rewrite values: `O(n)` space.
- **Better** — recursion: `O(n)` time, `O(n)` stack (elegant, risky for huge lists).
- **Optimal** — iterative three pointers: `O(n)` time, `O(1)` space. Always state this one in interviews.

### Merge two sorted lists
- **Brute** — collect all nodes into a vector, sort, relink: `O(n log n)`.
- **Better** — two-pointer merge on copied values: `O(n+m)` but allocates new nodes.
- **Optimal** — two-pointer merge **reusing existing nodes** with a dummy: `O(n+m)` time, `O(1)` space — no allocation at all.

### Key transferable idea
> Linked-list optimization is almost always **removing passes** (length count → gap lead) or **removing space** (hash set → fast/slow) while keeping one invariant: *every relink saves the node you are about to orphan.*

---

## 7. C++ / STL TOOLKIT

| Tool | Syntax | Use |
|---|---|---|
| Node struct | `struct Node{int data; Node* next;};` | singly |
| Dummy node | `Node dummy(0); dummy.next = head;` | safe head ops |
| Traversal | `for (Node* c = h; c; c = c->next)` | `O(n)` |
| Sentinel compare | `while (p && p->next)` | cycle/middle guards |
| Pair of pointers | `Node *s = h, *f = h;` | fast/slow |

```cpp
// traverse & collect values
for (Node* c = head; c; c = c->next) v.push_back(c->data);

// find tail
Node* t = head; while (t->next) t = t->next;

// two-pointer gap (n-th from end helper)
Node *fast = head, *slow = head;
for (int i = 0; i < n; i++) fast = fast->next;
```

**Key facts**
- Never copy a `Node*` you still need after a relink — name your pointers before editing links.
- Always check `p && p->next` — `p->next` on null is the #1 crash.
- Draw the three nodes (`prev`, `curr`, `next`) on paper before writing reversal code.

**Common mistakes**
- Returning a local pointer after relinking the old head.
- Forgetting `head` update after head insertion/deletion (avoid via dummy).
- Passing `Node* head` **by value is fine** (pointer copy), but `head` reassignment inside a function does not affect the caller's pointer — return the new head.

---

## 8. COMPLEXITY GUIDE

| Operation | Time | Space |
|---|---:|---:|
| Traverse / count / search | `O(n)` | `O(1)` |
| Insert / delete at known node | `O(1)` | `O(1)` |
| Insert / delete by value (search first) | `O(n)` | `O(1)` |
| Reverse (iterative) | `O(n)` | `O(1)` |
| Reverse (recursive) | `O(n)` | `O(n)` stack |
| Middle / cycle (fast-slow) | `O(n)` | `O(1)` |
| Merge two sorted | `O(n+m)` | `O(1)` |
| Merge K sorted (heap) | `O(N log K)` | `O(K)` |
| Sort list (merge sort) | `O(n log n)` | `O(log n)` |
| Nth-from-end (gap) | `O(n)` single pass | `O(1)` |
| Cycle length | `O(n)` | `O(1)` |

**How to estimate** — count node visits: every pointer that advances monotonically contributes `O(n)` total; a *pair* of walkers still visits each node at most twice → `O(n)`. Heap adds `log K` per extraction.

---

## 9. EDGE CASES

- **Empty list (`head == nullptr`)** — traversal, reverse, merge must all handle immediately.
- **Single node** — reverse is identity; middle is itself; cycle requires `next → self`.
- **Two nodes** — delete/merge branches often wrong here.
- **Head is the answer to delete** — this is why dummies exist.
- **Even vs odd length** — middle convention (LeetCode: second middle for even).
- **`n == length`** (nth from end = head); `n > length` (undefined — assume valid).
- **Cycle at the very head** (`tail.next = head`) — entry detection must still work.
- **`k = 0` or `k` multiple of length** in rotation — no change; `k % length` first.
- **DLL** — forgetting to maintain `prev` breaks backward iteration silently.
- **Unterminated tail** after stitching buckets → accidental cycle (infinite loop in tests!).

---

## 10. COMMON MISTAKES

| # | Mistake | What goes wrong | Why | How to avoid |
|---|---|---|---|---|
| 1 | Not saving `next` before relink | Rest of list lost → crash/truncation | Relink destroys the path | `Node* nxt = cur->next;` first |
| 2 | Missing null guard `f && f->next` | Segfault on short lists | Fast outruns null | Always both checks |
| 3 | Returning `dummy` instead of `dummy.next` | Fake node in result | Sentinel is not data | `return dummy.next;` |
| 4 | Forgetting head update | Old head leaked/orphaned | Head is a local copy | Return new head; use dummy |
| 5 | Off-by-one fast-lead (n+1) | Wrong node deleted | Gap counting | `for (i=0; i<=n; i++) fast=fast->next` with dummy |
| 6 | Losing `next` in K-group | Group stitched wrong | Partial reversal | Save chunk tail before reversing |
| 7 | Not terminating stitched chain | Accidental cycle | `tail->next` left stale | `tail->next = nullptr` |
| 8 | DLL: fixing `next` only | Backward traversal broken | Both pointers must flip | Swap `prev` and `next` together |
| 9 | Cycle entry: not resetting to head | Never finds entry | Proof requires both step-1 | `s = head; while (s != f)` |
| 10 | Assuming even-length middle | Off-by-one in palindrome check | Convention differences | State the convention; test 2-node list |

**Conceptual mistakes**
- Using recursion for very large lists (`10^5`) → stack overflow; prefer iterative.
- Sorting values into a new list when the statement requires **in-place** rearrangement.
- Forgetting `k % len` in rotations with huge `k`.

---

## 11. IMPORTANT FORMULAS / RULES

```text
Floyd meet:      in a cycle of length c, distance from head to entry = a;
                 after meeting, moving both at speed 1 from (head, meet) meet at entry.
                 Proof:  a + k·? ≡ meet distance  ->  first collision after a steps

Gap rule:        fast leads slow by d  ⇒  next lead = d - 1  (closing speed 1 per step)
                 fast=2, slow=1 ⇒ gap shrinks 1 each step ⇒ meet within ≤ c steps

Nth from end:    fast leads head by n (with dummy: n+1) ⇒ slow stops before nth

Rotate by k:     new head = node (k % n) from start; cut at n - k%n

Length parity:   even n → middle = n/2 + 1 (1-based second middle); odd → (n+1)/2

Merge K:         total work N nodes × log K heap ops = O(N log K)
```

**Invariants**
- Every relink step must keep: **all not-yet-processed nodes reachable** from some live pointer.
- After any reversal routine: `prev` points to the new head; old `head` is the tail (`next == nullptr`).

---

## 12. REUSABLE TEMPLATES

```cpp
// 1. Iterative reverse
Node* reverse(Node* h) {
    Node* prev = nullptr;
    while (h) { Node* nxt = h->next; h->next = prev; prev = h; h = nxt; }
    return prev;
}

// 2. Cycle detection
bool hasCycle(Node* h) {
    Node *s = h, *f = h;
    while (f && f->next) { s = s->next; f = f->next->next; if (s == f) return true; }
    return false;
}

// 3. Cycle entry (Floyd)
Node* detectCycleStart(Node* h) {
    Node *s = h, *f = h;
    while (f && f->next) {
        s = s->next; f = f->next->next;
        if (s == f) {
            s = h;
            while (s != f) { s = s->next; f = f->next; }
            return s;
        }
    }
    return nullptr;
}

// 4. Merge two sorted lists (dummy)
Node* mergeTwo(Node* a, Node* b) {
    Node dummy(0); Node* t = &dummy;
    while (a && b) {
        if (a->data <= b->data) { t->next = a; a = a->next; }
        else                    { t->next = b; b = b->next; }
        t = t->next;
    }
    t->next = a ? a : b;
    return dummy.next;
}

// 5. Middle (second middle for even)
Node* middle(Node* h) {
    Node *s = h, *f = h;
    while (f && f->next) { s = s->next; f = f->next->next; }
    return s;
}
```

## 13. ADVANCED CONCEPTS

### 13.1 Tortoise & hare beyond cycles
- **Find duplicate number (Floyd on value-as-index)**: `next = nums[i]` forms a functional graph with a cycle — same proof, no pointers stored.
- **Happy number / state machines**: detect cycles in *value sequences* with the same meet logic.

### 13.2 Merge sort on linked lists — the right way to sort
Split with slow/fast (`n/2`), recurse both halves, merge (P4). Time `O(n log n)`, space `O(log n)` recursion — beats `sort(values)` when the statement requires node reuse / in-place.

### 13.3 Persistence / copying
Not covered here, but know the idea: a *persistent* list versions each update by copying only the changed node — the immutable counterpart to in-place surgery.

### 13.4 Multi-level and randomized structures
- **Flatten**: repeatedly `merge(next, down)` bottom-up — "merge" generalizes beyond two lists.
- **Clone random pointer**: the interleave trick (A→A'→A→…, then split) uses `O(1)` extra space — an advanced dummy+stitch application.

### 13.5 XOR trick for singly linked lists
Unpaired elements (swap nodes, missing value) can sometimes be found with XOR of pointers/values — rarely needed, but explains some "list + XOR" problems.

### 13.6 Cache-conscious reality
Linked lists pay a pointer-chase per node; arrays beat them in practice despite worse asymptotics for insertion. Mention this in interviews to show systems awareness (§03 compares them).

---

## 14. CONNECTIONS BETWEEN PATTERNS

```text
Traversal (foundation)
    |
    +--> Dummy splice ------> delete / merge / insert problems
    |
    +--> Fast / slow -------> middle -> cycle -> entry -> palindrome list
    |                                |
    |                                v
    |                          reorder / rotate (needs reverse)
    |
    +--> Reverse (3 pointers) --> K-groups / reorder / bracket reversal
    |
    +--> Merge --------------> sort list (merge sort) --> merge K (heap, §11)
    |
    +--> Lockstep + carry ----> add two numbers
    |
    +--> Buckets + stitch ----> odd-even / segregate / flatten

Trees (§13) = node with TWO child pointers — same null-guards, same recursion shape.
LRU (§09)   = hash map + doubly linked list — dummy/relink patterns in production.
```

**Mental map** — when you see a list problem: **head mutable? → dummy. Positions asked? → fast/slow. Order reversed? → three pointers. Sorted streams? → merge.**

---

## 15. PROBLEM → PATTERN MAPPING

*(Reference only — solutions and approaches live in the `.cpp` files.)*

### Basics: traversal, insert, delete, count, search
- `01-Introduction-to-Linked-List.cpp`
- `02-Insert-Node.cpp`
- `03-Delete-Node.cpp`
- `04-Count-Length.cpp`
- `05-Search-Element.cpp`

### Doubly linked list
- `06-Introduction-to-DLL.cpp`
- `07-Insert-in-DLL.cpp`
- `08-Delete-in-DLL.cpp`
- `09-Reverse-DLL.cpp`
- `24-Segregate-Odd-Even-DLL.cpp`
- `25-Delete-All-Occurrences-DLL.cpp`
- `26-Pairs-with-Given-Sum-DLL.cpp`

### Fast / slow (middle, cycle, palindrome)
- `11-Middle-of-Linked-List.cpp`
- `12-Detect-Loop.cpp`
- `13-Find-Loop-Length.cpp`
- `14-Starting-Point-of-Loop.cpp`
- `15-Check-Palindrome-LL.cpp`

### Reverse (iterative / k-group / rotate)
- `10-Reverse-Linked-List.cpp`
- `27-Reverse-Nodes-in-K-Group.cpp`
- `28-Rotate-Linked-List.cpp`

### Merge / sort / partition
- `31-Merge-Two-Sorted-Lists.cpp`
- `23-Sort-Linked-List.cpp`
- `19-Sort-012-LL.cpp`
- `16-Odd-Even-Linked-List.cpp`
- `18-Delete-Middle-Node.cpp`
- `17-Remove-Nth-From-End.cpp`

### Arithmetic / add numbers
- `21-Add-1-to-Number-LL.cpp`
- `22-Add-Two-Numbers.cpp`

### Intersection / advanced
- `20-Intersection-Y.cpp`
- `29-Flatten-LL.cpp`
- `30-Clone-with-Random-Pointer.cpp`

---

## 16. QUICK REVISION SHEET

**Concepts**
- Node = data + next (+ prev for DLL). Head `nullptr` = empty. Dummy node = universal `prev`.
- Fast/slow: middle + cycle + entry from one idea. Three pointers = reverse.

**Recognition clues**
| Signal | Tool |
|---|---|
| head may change | dummy |
| middle / cycle / nth-from-end | fast-slow (gap `n` / reset for entry) |
| reverse / reorder / k-groups | prev-curr-next |
| two sorted streams | dummy + attach-smaller |
| add digits | lockstep + carry |
| odd-even / rotate / segregate | buckets + stitch (rotate: `k % n`) |
| palindrome list | middle → reverse half → compare |
| Y-intersection | length-align → lockstep |

**Algorithms (memorize)**
```cpp
reverse:   while(h){nxt=h->next; h->next=prev; prev=h; h=nxt;} return prev;
cycle:     while(f&&f->next){s=s->next; f=f->next->next; if(s==f) return true;}
entry:     after meet: s=head; while(s!=f) both +1;
merge:     dummy; attach smaller; t->next = a?a:b;
```

**Complexity**
traverse/reverse/fast-slow `O(n)/O(1)` · merge `O(n+m)/O(1)` · merge K `O(N log K)` · sort list `O(n log n)/O(log n)`.

**Common mistakes**
Not saving `next` · missing `f && f->next` · returning `dummy` not `dummy.next` · fast-lead off-by-one · unterminated tail (cycle) · DLL `prev` not repaired · `k % n` forgotten.

**Decision rules**
1. Head mutable → dummy. 2. Position questions → fast/slow. 3. Reversal → three pointers. 4. Sorted → merge. 5. Lockstep two lists → align first.

---

## 17. INTERVIEW CHECKLIST

- [ ] Can I draw and write the three-pointer reversal without losing nodes?
- [ ] Can I explain *why* fast/slow meet in a cycle (gap shrinks by 1)?
- [ ] Can I derive cycle entry (reset to head, both speed 1) and prove it?
- [ ] Can I delete Nth-from-end in one pass with a dummy?
- [ ] Can I merge two lists with `O(1)` space by reusing nodes?
- [ ] Can I handle empty / single / two-node lists in every template?
- [ ] Can I rotate by `k % n` and stitch without creating a cycle?
- [ ] Can I state time/space for reverse, merge, and sort-list?
- [ ] Can I convert a list problem to its array analogue and back?
- [ ] Can I spot when recursion (stack `O(n)`) is unacceptable vs fine?

<!-- done -->
