/*
Problem: Print Longest Common Subsequence
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DP - Strings
Statement: Given two strings, return one longest common subsequence string (backtrack through the LCS DP table).
Sample Input: a = "abcde", b = "ace"
Sample Output: "ace"
Explanation: "ace" is a longest common subsequence.
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

string printLCS(string a, string b) {
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
        else if (dp[i-1][j] > dp[i][j-1]) i--;
        else j--;
    }
    reverse(r.begin(), r.end());
    return r;
}

int main() {
    string a = "abcde";
    string b = "ace";

    auto ans = printLCS(a, b);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Backtrack table.
Time Complexity:
O(nm)
Space Complexity:
O(nm)
Key Idea:
Walk matches.
*/
