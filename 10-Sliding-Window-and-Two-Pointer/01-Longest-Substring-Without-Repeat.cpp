/*
Problem: Longest Substring without Repeat
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Sliding Window
Statement: Given a string, return the length of the longest substring without
repeating characters (sliding window + last index). Sample Input: s = "abcabcbb"
Sample Output: 3
Explanation: "abc" is the longest repeat-free window.
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
  public:
    int lengthOfLongestSubstring(string s) {
        int last[128];
        fill(begin(last), end(last), -1);
        int l = 0, b = 0;
        for (int r = 0; r < (int)s.size(); r++) {
            if (last[(unsigned char)s[r]] >= l)
                l = last[(unsigned char)s[r]] + 1;
            last[(unsigned char)s[r]] = r;
            b = max(b, r - l + 1);
        }
        return b;
    }
};

int main() {
    string s = "abcabcbb";

    Solution sol;
    auto ans = sol.lengthOfLongestSubstring(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Jump l past dup.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Last occurrence.
*/
