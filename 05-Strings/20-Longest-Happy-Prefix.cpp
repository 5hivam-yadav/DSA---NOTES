/*
Problem: Longest Happy Prefix
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Strings
Statement: Given s, return its longest prefix that is also a suffix but not the
whole string (KMP last pi value). Sample Input: s = "level" Sample Output: "l"
Explanation: "l" is both prefix and suffix; longer candidates fail.
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
    string longestPrefix(string s) {
        int n = (int)s.size();
        vector<int> lps(n, 0);
        for (int i = 1; i < n; i++) {
            int j = lps[i - 1];
            while (j > 0 && s[i] != s[j])
                j = lps[j - 1];
            if (s[i] == s[j])
                j++;
            lps[i] = j;
        }
        return s.substr(0, lps.back());
    }
};

int main() {
    string s = "level";

    Solution sol;
    auto ans = sol.longestPrefix(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
LPS last value = longest proper prefix-suffix.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Same LPS table as KMP.
*/
