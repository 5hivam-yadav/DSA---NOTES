/*
Problem: Wildcard Matching
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: DP - Strings
Statement: Given string s and pattern p with ? (any char) and * (any sequence), return true if p matches all of s (DP).
Sample Input: s = "adceb", p = "*a*b"
Sample Output: true
Explanation: "*" covers gaps around a and b.
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
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<char> pr(m + 1, 0), cu(m + 1, 0);
        pr[0] = 1;
        for (int j = 1; j <= m; j++) pr[j] = pr[j-1] && p[j-1] == '*';
        for (int i = 1; i <= n; i++) {
            cu[0] = 0;
            for (int j = 1; j <= m; j++) {
                if (p[j-1] == '*') cu[j] = cu[j-1] || pr[j];
                else if (p[j-1] == '?' || p[j-1] == s[i-1]) cu[j] = pr[j-1];
                else cu[j] = 0;
            }
            swap(pr, cu);
        }
        return pr[m];
    }
};

int main() {
    string s = "adceb";
    string p = "*a*b";

    Solution sol;
    auto ans = sol.isMatch(s, p);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
* = empty or consume.
Time Complexity:
O(nm)
Space Complexity:
O(m)
Key Idea:
Star expansion.
*/
