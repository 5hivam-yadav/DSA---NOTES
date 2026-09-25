/*
Problem: Min Cost to Cut Stick
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: DP - Partition
Statement: Given stick length n and cut positions, return minimum total cutting cost (DP over sorted cuts with sentinels).
Sample Input: n = 7, cuts = [1,3,4,5]
Sample Output: 16
Explanation: Best order cuts 3, then 1, 5, 4 for cost 16.
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
    int minCost(int n, vector<int>& c) {
        c.push_back(0);
        c.push_back(n);
        sort(c.begin(), c.end());
        int m = c.size();
        vector<vector<int>> dp(m, vector<int>(m, 0));
        for (int L = 2; L < m; L++) for (int i = 0; i + L < m; i++) {
            int j = i + L;
            dp[i][j] = INT_MAX;
            for (int k = i + 1; k < j; k++) dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + c[j] - c[i]);
        }
        return dp[0][m-1];
    }
};

int main() {
    int n = 7;
    vector<int> cuts = {1, 3, 4, 5};

    Solution sol;
    auto ans = sol.minCost(n, cuts);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Cut interval cost.
Time Complexity:
O(m^3)
Space Complexity:
O(m^2)
Key Idea:
MCM on cuts.
*/
