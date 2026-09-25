/*
Problem: Recursive Implementation of Atoi
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Recursion
Statement: Convert a numeric string to an integer recursively: sign once, then acc*10 + digit per call.
Sample Input: s = "-123"
Sample Output: -123
Explanation: Digits accumulate as ((-1)*10-2)*10-3.
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

int atoiR(const string& s, int i, long long v, int sign) {
    if (i == (int)s.size() || !isdigit(s[i])) return (int)(sign * v);
    v = v * 10 + (s[i] - '0');
    if (sign * v > INT_MAX) return INT_MAX;
    if (sign * v < INT_MIN) return INT_MIN;
    return atoiR(s, i + 1, v, sign);
}

int main() {
    string s = "-123";
    int sign = 1, i = 0;
    if (s[0] == '-') { sign = -1; i = 1; }
    else if (s[0] == '+') { i = 1; }
    cout << atoiR(s, i, 0, sign) << endl;
    return 0;
}

/*
Approach:
Recurse per digit.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Digit recursion.
*/
