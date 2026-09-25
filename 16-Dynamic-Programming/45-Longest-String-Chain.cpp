/*
Problem: Longest String Chain
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: DP - LIS
Statement: Given words, find the longest chain where each word adds one letter to the previous (sort by length + DP).
Sample Input: words = ["a","b","ba","bca","bda","bdca"]
Sample Output: 4
Explanation: a -> ba -> bca -> bdca has length 4.
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
    bool pre(const string& a, const string& b) {
        if (a.size() + 1 != b.size()) return false;
        size_t i = 0, j = 0;
        while (i < a.size() && j < b.size()) {
            if (a[i] == b[j]) i++;
            j++;
        }
        return i == a.size();
    }
    int longestStrChain(vector<string>& w) {
        sort(w.begin(), w.end(), [](auto& a, auto& b) { return a.size() < b.size(); });
        int n = w.size(), b = 1;
        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) for (int j = 0; j < i; j++) if (pre(w[j], w[i])) dp[i] = max(dp[i], dp[j] + 1);
        return *max_element(dp.begin(), dp.end());
    }
};

/*
Approach:
Length-sort + pred.
Time Complexity:
O(n^2 L)
Space Complexity:
O(n)
Key Idea:
One-insert predecessor.
*/
