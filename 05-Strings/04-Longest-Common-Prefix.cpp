/*
Problem: Longest Common Prefix
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - Strings
Statement: Given an array of strings, return their longest shared starting substring.
Sample Input: strs = ["flower","flow","flight"]
Sample Output: "fl"
Explanation: All three words start with fl.
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
    string longestCommonPrefix(vector<string>& s) {
        if (s.empty()) return "";
        for (int i = 0; i < (int)s[0].size(); i++) for (size_t j = 1; j < s.size(); j++) if (i >= (int)s[j].size() || s[j][i] != s[0][i]) return s[0].substr(0, i);
        return s[0];
    }
};

int main() {
    vector<string> strs = {"flower", "flow", "flight"};

    Solution sol;
    auto ans = sol.longestCommonPrefix(strs);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Column compare.
Time Complexity:
O(S)
Space Complexity:
O(1)
Key Idea:
First mismatch stops.
*/
