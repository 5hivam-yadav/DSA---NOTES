/*
Problem: Longest Common Subsequence
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DP - Strings
Statement: Given strings text1 and text2, return the length of their longest common subsequence (order kept, gaps allowed).
Sample Input: text1 = "abcde", text2 = "ace"
Sample Output: 3
Explanation: "ace" is a subsequence of both with nothing longer possible.
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
    int longestCommonSubsequence(string a, string b) {
        int n = a.size(), m = b.size();
        vector<int> pr(m + 1, 0), cu(m + 1, 0);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) cu[j] = (a[i-1] == b[j-1]) ? pr[j-1] + 1 : max(pr[j], cu[j-1]);
            swap(pr, cu);
        }
        return pr[m];
    }
};

int main() {
    string text1 = "abcde";
    string text2 = "ace";

    Solution sol;
    auto ans = sol.longestCommonSubsequence(text1, text2);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Match or skip.
Time Complexity:
O(nm)
Space Complexity:
O(m)
Key Idea:
Prefix alignment.
*/
