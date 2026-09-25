/*
Problem: Matrix Chain Multiplication
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: DP - Partition
Statement: Given matrix dimensions d[0..n], return the minimum scalar multiplications to chain them (DP over intervals).
Sample Input: d = [40,20,30,10,30]
Sample Output: 26000
Explanation: Optimal parenthesization costs 26000.
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

int mcm(vector<int>& d) {
    int n = d.size() - 1;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int L = 2; L <= n; L++) for (int i = 0; i + L - 1 < n; i++) {
        int j = i + L - 1;
        dp[i][j] = INT_MAX;
        for (int k = i; k < j; k++) dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + d[i] * d[k+1] * d[j+1]);
    }
    return dp[0][n-1];
}
  // State interval; split k; increasing length.

int main() {
    vector<int> d = {40, 20, 30, 10, 30};

    auto ans = mcm(d);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Interval split.
Time Complexity:
O(n^3)
Space Complexity:
O(n^2)
Key Idea:
Length increasing.
*/
