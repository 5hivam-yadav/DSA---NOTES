/*
Problem: Min Insertions Palindrome
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Strings
Statement: Given s, return the minimum insertions to make it a palindrome (n - longest palindromic subsequence).
Sample Input: s = "mbadm"
Sample Output: 2
Explanation: LPS length 3; 5 - 3 = 2.
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
    int minInsertions(string s) {
        string r = s;
        reverse(r.begin(), r.end());
        int n = (int)s.size();
        vector<int> prev(n + 1, 0), cur(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cur[j] = (s[i - 1] == r[j - 1]) ? prev[j - 1] + 1 : max(prev[j], cur[j - 1]);
            }
            prev.swap(cur);
        }
        return n - prev[n];
    }
};

int main() {
    string s = "mbadm";

    Solution sol;
    auto ans = sol.minInsertions(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Answer = n - LPS;
LPS = LCS(s, reverse(s)).
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Insertions mirror unmatched chars.
*/
