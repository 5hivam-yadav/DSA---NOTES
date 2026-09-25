/*
Problem: Burst Balloons
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: DP - Partition
Statement: Given balloons, burst them for coins = left*mid*right with virtual 1s at both ends (interval DP).
Sample Input: nums = [3,1,5,8]
Sample Output: 167
Explanation: Best burst order yields 167 coins.
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
    int maxCoins(vector<int>& a) {
        int n = a.size();
        vector<int> v(n + 2, 1);
        for (int i = 0; i < n; i++) v[i+1] = a[i];
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        for (int L = 1; L <= n; L++) for (int l = 1; l + L - 1 <= n; l++) {
            int r = l + L - 1;
            for (int k = l; k <= r; k++) dp[l][r] = max(dp[l][r], dp[l][k-1] + v[l-1] * v[k] * v[r+1] + dp[k+1][r]);
        }
        return dp[1][n];
    }
};
  // Last-burst split.

int main() {
    vector<int> nums = {3, 1, 5, 8};

    Solution sol;
    auto ans = sol.maxCoins(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Last burst k.
Time Complexity:
O(n^3)
Space Complexity:
O(n^2)
Key Idea:
Boundary product.
*/
