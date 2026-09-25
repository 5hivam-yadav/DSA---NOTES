# 10 — Sliding Window and Two Pointer

## Concept
- What: Maintain a window [l,r] or pair (i,j) with a valid invariant.
- Why: O(n) subarray/substring optima vs O(n^2). When: fixed-K window, longest with <=K distinct, pair sums.
- Terms: expand/shrink, freq map, at-most-K trick.

## Syntax
```cpp
for(int r=0,l=0;r<n;r++){freq[a[r]]++;while(invalid){freq[a[l]]--;l++;}ans=max(ans,r-l+1);}
```

## Patterns
- Fixed-K sum/max (prefix window). Longest without repeat (last-index jump).
- At-most-K minus (exact K = f(K)-f(K-1)). Freq + distinct count.
- Two pointers sorted (2-sum, 3-sum skip dup, container water).

## Algorithms
- Max-sum K: slide add/remove. Longest substr K distinct / char replacement (maxFreq).
- Binary ones w/ flips; nice subarrays (odd count); substr containing ABC (add n-j); min window (have/need); longest without repeat; 3-sum sort+skip; container area.

## Examples
s="abcabcbb" longest=3. K=3 [1,3,-1,-3,5] maxes [3,3,5].

## Complexity
O(n)/O(sigma) each index moves once; sorted variants O(n log n) or O(n^2) for 3-sum.

## Common Mistakes
- Shrinking with if not while; last-index < l check; exact-K without subtraction trick; int sum overflow.

## Templates
```cpp
int atMost(vector<int>&a,int k){if(k<0)return 0;unordered_map<int,int>f;int l=0,res=0;for(int r=0;r<(int)a.size();r++){f[a[r]]++;while((int)f.size()>k){if(--f[a[l]]==0)f.erase(a[l]);l++;}res+=r-l+1;}return res;}
```

## Revision Summary
Fixed slide; variable expand+shrink; exact=f(K)-f(K-1); sorted=2/3 pointers.
