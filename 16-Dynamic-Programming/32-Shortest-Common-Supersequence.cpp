/*
Problem: Shortest Common Supersequence
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - Strings
Statement: Given a and b, return a shortest string containing both as subsequences (LCS backbone + leftovers).
Sample Input: a = "abac", b = "cab"
Sample Output: "cabac"
Explanation: "cabac" embeds both with length 5.
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
    string shortestCommonSupersequence(string a, string b) {
        int n = a.size(), m = b.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) dp[i][j] = (a[i-1] == b[j-1]) ? dp[i-1][j-1] + 1 : max(dp[i-1][j], dp[i][j-1]);
        string r;
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (a[i-1] == b[j-1]) {
                r += a[i-1];
                i--;
                j--;
            }
            else if (dp[i-1][j] > dp[i][j-1]) r += a[--i];
            else r += b[--j];
        }
        while (i > 0) r += a[--i];
        while (j > 0) r += b[--j];
        reverse(r.begin(), r.end());
        return r;
    }
};

int main() {
    string a = "abac";
    string b = "cab";

    Solution sol;
    auto ans = sol.shortestCommonSupersequence(a, b);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Merge via LCS.
Time Complexity:
O(nm)
Space Complexity:
O(nm)
Key Idea:
LCS once + rest.
*/
