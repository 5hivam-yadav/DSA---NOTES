/*
Problem: Implement Atoi
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Strings
Statement: Convert a string to a 32-bit signed integer: skip spaces, optional sign, read digits, clamp on overflow.
Sample Input: s = "   -42"
Sample Output: -42
Explanation: Spaces skipped, sign applied, digits read until end.
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
    int myAtoi(string s) {
        int i = 0, n = s.size();
        while (i < n && s[i] == ' ') i++;
        int sign = 1;
        if (i < n && (s[i] == '+' || s[i] == '-')) {
            if (s[i] == '-') sign = -1;
            i++;
        }
        long long v = 0;
        while (i < n && isdigit(s[i])) {
            v = v * 10 + (s[i] - '0');
            if (sign * v > INT_MAX) return INT_MAX;
            if (sign * v < INT_MIN) return INT_MIN;
            i++;
        }
        return (int)(sign * v);
    }
};

int main() {
    string s = "   -42";

    Solution sol;
    auto ans = sol.myAtoi(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Trim, sign, digits, clamp.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Overflow clamp.
*/
