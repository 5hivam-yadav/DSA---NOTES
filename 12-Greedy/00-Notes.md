# 12 — Greedy

## Concept
- What: Locally optimal choice that stays globally optimal (needs proof: exchange argument).
- Why: O(n log n) simple optima. When: intervals, scheduling, coins(canonical), jumps reachable.
- Terms: sort by end/start, exchange proof, feasibility.

## Syntax
```cpp
sort(v.begin(),v.end(),[](auto&a,auto&b){return a[1]<b[1];});
```

## Patterns
- Intervals sort-by-end (non-overlap, arrows, platforms sweep separately).
- Scheduling profit/deadline (slot array or DSU). Jump min-coverage.
- Partition labels last-pos. Gas station total+min-prefix.

## Algorithms
- Assign cookies; lemonade change 5/10/20; valid parenthesis range lo/hi;
- N meetings end-sort; jump-I reachable max; jump-II windows; gas total>=0 + min point;
- candy two-pass; insert/merge intervals; non-overlapping erase overlap end; min arrows; LIS-greedy not; platform two arrays.

## Examples
Meetings (1,2),(3,4),(0,6),(5,7) -> 3. Lemonade [5,5,5,10,20] -> true.

## Complexity
Sort O(n log n) + scan O(n); space O(1) or O(n).

## Common Mistakes
- Sort by start for meeting-max (need end); greedy where DP needed (0/1 knapsack); coins non-canonical; overflow day counts.

## Templates
```cpp
int meetings(vector<pair<int,int>>v){sort(v.begin(),v.end(),[](auto&a,auto&b){return a.second<b.second;});int c=0,last=-1e9;for(auto&p:v)if(p.first>last){c++;last=p.second;}return c;}
```

## Revision Summary
Intervals by end; scheduling by profit; jumps by coverage; prove exchange.
