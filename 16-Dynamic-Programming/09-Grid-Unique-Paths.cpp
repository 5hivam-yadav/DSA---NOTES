/*
Problem: Grid Unique Paths
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP on Grids
Statement: Given m x n grid, count paths from top-left to bottom-right moving only down/right (combinatorial DP).
Sample Input: m = 3, n = 7
Sample Output: 28
Explanation: C(8,2) = 28 monotone paths.
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
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[j] += dp[j - 1];
            }
        }
        return dp[n - 1];
    }
};

int main() {
    int m = 3;
    int n = 7;

    Solution sol;
    auto ans = sol.uniquePaths(m, n);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Only right/down moves, dp[j] = paths from top + left.
Time Complexity:
O(m*n)
Space Complexity:
O(n)
Key Idea:
Combinatorial C(m+n-2, m-1);
DP avoids overflow steps.
*/
