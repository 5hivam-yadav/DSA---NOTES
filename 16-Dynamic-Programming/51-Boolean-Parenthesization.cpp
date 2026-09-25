/*
Problem: Boolean Parenthesization
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Dynamic Programming
Statement: Given a boolean expression of T/F with & | ^, count ways to parenthesize it to true (mod 1003).
Sample Input: s = "T|F&T^F"
Sample Output: 5
Explanation: Five parenthesizations evaluate true.
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

const int M = 1003;
int boolPar(string s) {
    int n = s.size();
    vector<vector<array<int, 2>>> dp(n, vector<array<int, 2>>(n, {0, 0}));
    for (int i = 0; i < n; i += 2) dp[i][i] = {s[i] == 'F', s[i] == 'T'};
    for (int L = 3; L <= n; L += 2) for (int i = 0; i + L - 1 < n; i += 2) {
        int j = i + L - 1, T = 0, F = 0;
        for (int k = i + 1; k < j; k += 2) {
            auto Lr = dp[i][k-1], Rr = dp[k+1][j];
            int lt = Lr[1], lf = Lr[0], rt = Rr[1], rf = Rr[0];
            if (s[k] == '&') {
                T += lt * rt;
                F += lt * rf + lf * rt + lf * rf;
            }
            else if (s[k] == '|') {
                T += lt * rt + lt * rf + lf * rt;
                F += lf * rf;
            }
            else {
                T += lt * rf + lf * rt;
                F += lt * rt + lf * rf;
            }
        }
        dp[i][j] = {F % M, T % M};
    }
    return dp[0][n-1][1];
}

int main() {
    string s = "T|F&T^F";

    auto ans = boolPar(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Operator truth tables.
Time Complexity:
O(n^3)
Space Complexity:
O(n^2)
Key Idea:
Count T/F pairs.
*/
