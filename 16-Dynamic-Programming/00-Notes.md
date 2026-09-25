# 16 — Dynamic Programming

## Concept
- What: Solve overlapping subproblems once; optimal substructure. Why: exponential to polynomial.
- When: count/optimize/partition/strings/stocks/grids. Terms: state, base, transition, memo/tab/space-opt.

## Syntax
```cpp
vector<int> dp(n,-1);
function<int(int)> f=[&](int i)->int{if(i<=1)return i;if(dp[i]!=-1)return dp[i];return dp[i]=f(i-1)+f(i-2);};
```

## Patterns
- 1D climb/rob (prev two). Grids (right/down, obstacle, min-path, triangle).
- Subsequence subset/partition/diff; unbounded coin/rod/cut; strings LCS/edit/distinct/wildcard;
- stocks 5 states (hold/sold/cooldown/fee); LIS O(n^2)/patience; MCM burst/pal-partition.

## Algorithms
Pipeline per problem: state meaning -> base -> transition -> order -> space-opt.
- Fib/climb/rob/house-II; grid unique/obstacle/min-path/triangle/cherry;
- subset/partition/diff/coin-change/count/rod/knapsack unbounded;
- LCS/print/SCS/edit/distinct/wildcard; stocks I..V; LIS/print/divisible/chain; MCM/burst/evaluate/pal-partition.

## Examples
climb(5)=8. LCS("abcde","ace")=3. rob [2,7,9,3,1]=12.

## Complexity
States*transition; usually O(n*m)/O(n*m) -> O(n)/O(1) opt.

## Common Mistakes
- Wrong base/index shift; iteration order; unbounded vs 0/1 loop direction; modulo; recursion depth.

## Templates
```cpp
int lisPatience(vector<int>&a){vector<int>d;for(int x:a){auto it=lower_bound(d.begin(),d.end(),x);if(it==d.end())d.push_back(x);else *it=x;}return d.size();}
int knap01(vector<int>&wt,vector<int>&v,int W){vector<int>dp(W+1,0);for(size_t i=0;i<wt.size();i++)for(int w=W;w>=wt[i];w--)dp[w]=max(dp[w],dp[w-wt[i]]+v[i]);return dp[W];}
```

## Revision Summary
State->base->transition->order->opt. 0/1 reverse loop; unbounded forward.
