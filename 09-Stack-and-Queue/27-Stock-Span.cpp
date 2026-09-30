/*
Problem: Stock Span
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Monotonic Stack
Statement: Given daily prices, return the span of each day (consecutive days <=
today, including today) with a monotonic stack. Sample Input: prices = [100, 80,
60, 70, 60, 75, 85] Sample Output: [1, 1, 1, 2, 1, 4, 6] Explanation: Day 6 sees
back to day 1 (75 down to 80 blocks).
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class StockSpanner {
    vector<int> p, v;

  public:
    int next(int x) {
        int s = 1;
        while (!v.empty() && v.back() <= x) {
            s += p.back();
            v.pop_back();
            p.pop_back();
        }
        v.push_back(x);
        p.push_back(s);
        return s;
    }
};

/*
Approach:
Pop <= with spans.
Time Complexity:
O(1) amortized
Space Complexity:
O(n)
Key Idea:
Span jump.
*/
