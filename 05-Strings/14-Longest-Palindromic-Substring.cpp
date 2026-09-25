/*
Problem: Longest Palindromic Substring
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Strings
Statement: Given a string, return its longest palindromic substring (expand around each centre).
Sample Input: s = "babad"
Sample Output: "bab"
Explanation: bab (or aba) is the longest palindrome inside.
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
    string longestPalindrome(string s) {
        int n = s.size(), bl = 0, bn = 1;
        auto exp = [&](int l, int r) {
            while (l >= 0 && r < n && s[l] == s[r]) {
                l--;
                r++;
            }
            if (r - l - 1 > bn) {
                bn = r - l - 1;
                bl = l + 1;
            }
        };
        for (int i = 0; i < n; i++) {
            exp(i, i);
            exp(i, i + 1);
        }
        return s.substr(bl, bn);
    }
};
  // Manacher O(n) also.

int main() {
    string s = "babad";

    Solution sol;
    auto ans = sol.longestPalindrome(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Expand centers.
Time Complexity:
O(n^2)
Space Complexity:
O(1)
Key Idea:
Odd+even centers.
*/
