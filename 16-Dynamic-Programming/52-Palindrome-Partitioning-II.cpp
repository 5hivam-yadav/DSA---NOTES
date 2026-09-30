/*
Problem: Palindrome Partitioning II
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Backtracking
Statement: Given s, return the minimum cuts to split it into palindromes (expand
palindromes + DP). Sample Input: s = "aab" Sample Output: 1 Explanation: Cut as
"aa" | "b".
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

class Solution {
  public:
    int minCut(string s) {
        int n = s.size();
        vector<vector<char>> pal(n, vector<char>(n, 0));
        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                pal[i][j] = (s[i] == s[j] && (j - i < 2 || pal[i + 1][j - 1]));
        vector<int> dp(n + 1, 0);
        for (int i = 0; i <= n; i++)
            dp[i] = i - 1;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < i; j++)
                if (pal[j][i - 1])
                    dp[i] = min(dp[i], dp[j] + 1);
        return dp[n];
    }
};

int main() {
    string s = "aab";

    Solution sol;
    auto ans = sol.minCut(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Pal table + cuts.
Time Complexity:
O(n^2)
Space Complexity:
O(n^2)
Key Idea:
Cut before pal suffix.
*/
