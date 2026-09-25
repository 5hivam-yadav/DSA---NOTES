/*
Problem: Minimum Window Subsequence
Platform: LeetCode
Problem Number: -
Difficulty: Hard
Pattern: Sliding Window
Statement: Given strings s and t, return the minimum-length contiguous window of s that contains t as a subsequence, or "" if none exists.
Sample Input: s = "abcdebdde", t = "bde"
Sample Output: "bcde"
Explanation: "bcde" contains b, d, e in order and is the shortest such window.
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
    string minWindow(string s, string t) {
        int n = s.size(), m = t.size(), bn = INT_MAX, bl = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == t[0]) {
                int a = i, b = 0;
                while (a < n && b < m) {
                    if (s[a] == t[b]) b++;
                    a++;
                }
                if (b == m) {
                    int e = a - 1, bb = m - 1;
                    while (bb >= 0) {
                        if (s[e] == t[bb]) bb--;
                        e--;
                    }
                    e++;
                    if (a - e < bn) {
                        bn = a - e;
                        bl = e;
                    }
                }
            }
        }
        return bn == INT_MAX ? "" : s.substr(bl, bn);
    }
};
  // DP O(nm) also.

int main() {
    string s = "abcdebdde";
    string t = "bde";

    Solution sol;
    auto ans = sol.minWindow(s, t);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Forward match + backtrack.
Time Complexity:
O(n^2 m)
Space Complexity:
O(1)
Key Idea:
Two-pointer per start.
*/
