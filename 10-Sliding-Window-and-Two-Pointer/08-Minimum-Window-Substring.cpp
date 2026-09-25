/*
Problem: Minimum Window Substring
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Sliding Window
Statement: Given s and t, return the smallest window of s containing all characters of t (with counts).
Sample Input: s = "ADOBECODEBANC", t = "ABC"
Sample Output: "BANC"
Explanation: "BANC" is the shortest covering window.
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
        int need[128] = {0}, have[128] = {0};
        for (char c : t) need[(unsigned char)c]++;
        int req = 0;
        for (int i = 0; i < 128; i++) if (need[i] > 0) req++;
        int formed = 0, l = 0, bl = 0, bn = INT_MAX;
        for (int r = 0; r < (int)s.size(); r++) {
            int c = s[r];
            have[c]++;
            if (need[c] > 0 && have[c] == need[c]) formed++;
            while (formed == req) {
                if (r - l + 1 < bn) {
                    bn = r - l + 1;
                    bl = l;
                }
                have[(unsigned char)s[l]]--;
                if (need[(unsigned char)s[l]] > 0 && have[(unsigned char)s[l]] < need[(unsigned char)s[l]]) formed--;
                l++;
            }
        }
        return bn == INT_MAX ? "" : s.substr(bl, bn);
    }
};

int main() {
    string s = "ADOBECODEBANC";
    string t = "ABC";

    Solution sol;
    auto ans = sol.minWindow(s, t);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Expand, shrink valid.
Time Complexity:
O(n+m)
Space Complexity:
O(1)
Key Idea:
have/need counts.
*/
