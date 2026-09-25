/*
Problem: House Robber II
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - 1D
Statement: Given house values in a circle, return max loot without adjacent picks (solve linear twice: skip first / skip last).
Sample Input: nums = [2, 3, 2]
Sample Output: 3
Explanation: Best is house 2 alone (first and last conflict).
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include <functional>
#include <numeric>
#include <cmath>
#include <climits>
using namespace std;

class Solution {
public:
    int lin(vector<int>& a, int l, int r) {
        int p2 = 0, p1 = 0;
        for (int i = l; i <= r; i++) {
            int c = max(p1, p2 + a[i]);
            p2 = p1;
            p1 = c;
        }
        return p1;
    }
    int rob(vector<int>& a) {
        int n = a.size();
        if (n == 1) return a[0];
        return max(lin(a, 0, n-2), lin(a, 1, n-1));
    }
};

/*
Approach:
Exclude first or last.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Break circle.
*/
