/*
Problem: Unique Binary Trees
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given n distinct keys, return the number of structurally unique BSTs storing them (Catalan number DP).
Sample Input: n = 3
Sample Output: 5
Explanation: C(3) = dp[0]*dp[2] + dp[1]*dp[1] + dp[2]*dp[0] = 2+1+2 = 5.
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
    int numTrees(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = dp[1] = 1;
        for (int i = 2; i <= n; i++) for (int r = 1; r <= i; r++) dp[i] += dp[r - 1] * dp[i - r];
        return dp[n];
    }
};
  // Catalan: C(2n,n)/(n+1).

int main() {
    int n = 3;

    Solution sol;
    auto ans = sol.numTrees(n);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Root split product.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Catalan DP.
*/
