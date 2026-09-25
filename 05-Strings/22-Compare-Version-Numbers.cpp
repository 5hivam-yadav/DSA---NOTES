/*
Problem: Compare Version Numbers
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Strings
Statement: Given two version strings, compare them chunk by chunk numerically (missing chunks are 0).
Sample Input: v1 = "1.01", v2 = "1.001"
Sample Output: 0
Explanation: Both mean 1.1, so they are equal.
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
    int compareVersion(string a, string b) {
        size_t i = 0, j = 0;
        while (i < a.size() || j < b.size()) {
            long x = 0, y = 0;
            while (i < a.size() && a[i] != '.') x = x * 10 + (a[i++] - '0');
            while (j < b.size() && b[j] != '.') y = y * 10 + (b[j++] - '0');
            if (x < y) return -1;
            if (x > y) return 1;
            i++;
            j++;
        }
        return 0;
    }
};

int main() {
    string v1 = "1.01";
    string v2 = "1.001";

    Solution sol;
    auto ans = sol.compareVersion(v1, v2);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Parse revision by revision, missing = 0.
Time Complexity:
O(n+m)
Space Complexity:
O(1)
Key Idea:
Leading zeros vanish via integer parse.
*/
