# 04 — Binary Search

## Concept
- What: Halve sorted/monotonic space each step. Why: O(log n) search, O(log N) answer search.
- When: Sorted, rotated, peak, sqrt, min-max allocation. Terms: search space, predicate, lower/upper bound.

## Syntax
```cpp
binary_search(a.begin(),a.end(),x);
lower_bound(a.begin(),a.end(),x)-a.begin();
```

## Patterns
- Classic index BS. First/last via bounds. Rotated via sorted-half test.
- Answer-space: predicate + lo/hi + best feasible. 2D flatten or stair-step.

## Algorithms
- Loop lo=0 hi=n-1 mid=lo+(hi-lo)/2. Rotated: if a[lo]<=a[mid] left sorted.
- Sqrt/nth-root: predicate mid^k<=x. Koko/bouquets/ship/cows/pages: feasibility + binary lift.

## Examples
[1,2,4,4,4,5] x=4 -> first 2 last 4. Rotated [4,5,6,7,0,1,2] x=0 -> 4.

## Complexity
1D O(log n); answer O(log N * check); 2D O(m log n) or O(m+n).

## Common Mistakes
- (lo+hi)/2 overflow; lo=mid infinite loop; duplicates in rotated; wrong sorted-half.

## Templates
```cpp
int bs(vector<int>&a,int x){int lo=0,hi=(int)a.size()-1;while(lo<=hi){int mid=lo+(hi-lo)/2;if(a[mid]==x)return mid;else if(a[mid]<x)lo=mid+1;else hi=mid-1;}return -1;}
```

## Revision Summary
Sorted? BS. Rotated? sorted-half. Min-max? BS on answer with predicate.
