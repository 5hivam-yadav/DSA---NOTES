/*
Problem: Longest Repeating Char Replacement
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Sliding Window
Statement: Given s and k, find the longest substring achievable by replacing at most k chars to one letter.
Sample Input: s = "ABAB", k = 2
Sample Output: 4
Explanation: "ABAB" becomes "AAAA" with 2 replacements.
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
    int characterReplacement(string s, int k) {
        int f[26] = {0}, l = 0, mx = 0, b = 0;
        for (int r = 0; r < (int)s.size(); r++) {
            mx = max(mx, ++f[s[r] - 'A']);
            while (r - l + 1 - mx > k) {
                f[s[l++] - 'A']--;
            }
            b = max(b, r - l + 1);
        }
        return b;
    }
};

int main() {
    string s = "ABAB";
    int k = 2;

    Solution sol;
    auto ans = sol.characterReplacement(s, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
len - maxFreq <= k.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Majority window.
*/
