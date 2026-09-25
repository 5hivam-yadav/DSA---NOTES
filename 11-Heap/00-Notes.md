# 11 — Heap

## Concept
- What: Complete binary tree with heap order; top = min or max. Why: O(log n) top-K, merge, scheduling.
- When: kth largest, top-K freq, merge K lists, task cool-down. Terms: heapify, sift up/down.

## Syntax
```cpp
priority_queue<int> mx; priority_queue<int,vector<int>,greater<int>> mn;
mx.push(x); mx.top(); mx.pop();
```

## Patterns
- Size-K heap (keep K best, top is answer). Two heaps median (max-left + min-right balance).
- K-way merge push heads. Freq map + heap. Greedy-expand (stones, ropes).

## Algorithms
- Heapify bottom-up O(n). Kth largest via min-K. Kth smallest via max-K.
- Merge K sorted push (val,list). Hands of straights map chain. Task scheduler idle math.
- Design Twitter: map user->posts + follow sets, heap merge feeds. Connect ropes min-sum. Max sum combo careful dup.

## Examples
[3,2,1,5,6,4] k=2 largest=5. Median [1,2,3] -> 2 via two heaps.

## Complexity
Push/pop O(log n); top O(1); heapify O(n); K-way O(N log K).

## Common Mistakes
- Default max vs min confusion; stale entries; comparator direction; balancing off-by-one.

## Templates
```cpp
int kthLargest(vector<int>a,int k){priority_queue<int,vector<int>,greater<int>>pq;for(int x:a){pq.push(x);if((int)pq.size()>k)pq.pop();}return pq.top();}
```

## Revision Summary
Top-K = size-K heap. Median = two heaps. Merge K = heap of heads.
