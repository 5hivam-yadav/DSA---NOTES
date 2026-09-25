/*
Problem: Longest Palindromic Subseq
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - Strings
Statement: Given s, return the length of its longest palindromic subsequence (LCS of s and reverse(s)).
Sample Input: s = "bbbab"
Sample Output: 4
Explanation: "bbbb" is the longest palindromic subsequence.
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
    int longestPalindromeSubseq(string s) {
        string r = s;
        reverse(r.begin(), r.end());
        int n = s.size();
        vector<int> pr(n + 1, 0), cu(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) cu[j] = (s[i-1] == r[j-1]) ? pr[j-1] + 1 : max(pr[j], cu[j-1]);
            swap(pr, cu);
        }
        return pr[n];
    }
};

int main() {
    string s = "bbbab";

    Solution sol;
    auto ans = sol.longestPalindromeSubseq(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
LCS with reverse.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Palindrome = mirror LCS.
*/
