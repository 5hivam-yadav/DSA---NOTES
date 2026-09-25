/*
Problem: Distinct Subsequences
Platform: LeetCode
Problem Number: -
Difficulty: Hard
Pattern: DP - Strings
Statement: Given strings s and t, count distinct subsequences of s equal to t (DP over prefixes).
Sample Input: s = "rabbbit", t = "rabbit"
Sample Output: 3
Explanation: Three ways to delete to form rabbit.
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
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        vector<double> dp(m + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) for (int j = m; j >= 1; j--) if (s[i-1] == t[j-1]) dp[j] += dp[j-1];
        return (int)dp[m];
    }
};
  // double avoids overflow; mod variant uses 1e9+7.

int main() {
    string s = "rabbbit";
    string t = "rabbit";

    Solution sol;
    auto ans = sol.numDistinct(s, t);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Match-add or skip.
Time Complexity:
O(nm)
Space Complexity:
O(m)
Key Idea:
Reverse j 0/1 style.
*/
