# 07 — Recursion and Backtracking

## Concept
- What: Function calls itself on smaller input; backtracking undoes a choice.
- Why: Trees, combos, permutations, search. When: exhaustive choices with constraints.
- Terms: base case, choice, recursive call, state, pruning.

## Syntax
```cpp
void f(int i, vector<int>&ds){if(i==n){ans.push_back(ds);return;}ds.push_back(a[i]);f(i+1,ds);ds.pop_back();f(i+1,ds);}
```

## Patterns
- Take/not-take (subsequences, subset sum). Index+target (combination sum).
- Swap-in-place (permutations). Used-array (perm II with sort+skip).
- Board placement with validity (N-queens, sudoku). Partition cuts (palindrome).

## Algorithms
- Pow(x,n) fast: half + square, handle negative. Subsets, subset-II skip dup.
- Combination I (reuse) / II (once + skip). Permutations swap / used.
- N-queens col+diag sets. Sudoku 3x3 check. Palindrome partition. Kth perm factorial.

## Examples
Subsets [1,2] -> [],[1],[2],[1,2]. Perms [1,2] -> [1,2],[2,1].

## Complexity
Subsets O(2^n * n); perms O(n! * n); N-queens O(n!); sudoku 9^(empty).

## Common Mistakes
- Missing pop_back; dup handling without sort; copying vector each call; no pruning.

## Templates
```cpp
void subsets(int i,vector<int>&a,vector<int>&ds){if(i==(int)a.size()){ans.push_back(ds);return;}ds.push_back(a[i]);subsets(i+1,a,ds);ds.pop_back();subsets(i+1,a,ds);}
```

## Revision Summary
Base + choice + recurse + undo. Sort+skip for dups. Validity check before recurse.
