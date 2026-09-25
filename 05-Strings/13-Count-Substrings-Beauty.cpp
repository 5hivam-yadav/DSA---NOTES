/*
Problem: Count Substrings Beauty
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Strings
Statement: Given s, count substrings where the max frequency minus min frequency (over present chars) is the beauty; sum it.
Sample Input: s = "aabcb"
Sample Output: 5
Explanation: Five substrings contribute beauty 1 each.
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
    int beautySum(string s) {
        int n = s.size(), ans = 0;
        for (int i = 0; i < n; i++) {
            int f[26] = {0};
            for (int j = i; j < n; j++) {
                f[s[j] - 'a']++;
                int mx = 0, mn = INT_MAX;
                for (int k = 0; k < 26; k++) if (f[k]) {
                    mx = max(mx, f[k]);
                    mn = min(mn, f[k]);
                }
                ans += mx - mn;
            }
        }
        return ans;
    }
};

int main() {
    string s = "aabcb";

    Solution sol;
    auto ans = sol.beautySum(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Expand + freq scan.
Time Complexity:
O(n^2 * 26)
Space Complexity:
O(1)
Key Idea:
Per-start expand.
*/
