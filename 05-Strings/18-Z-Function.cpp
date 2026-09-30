/*
Problem: Z Function
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: String Matching
Statement: Given a string s, return the Z-array where z[i] is the longest prefix
match starting at i (linear time). Sample Input: s = "aabcaabxaaaz" Sample
Output: [0..] with z[4]=3 Explanation: "aab" matches at index 4 with length 3.
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

vector<int> zFunction(const string &s) {
    int n = (int)s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int strStrZ(const string &haystack, const string &needle) {
    if (needle.empty())
        return 0;
    string s = needle + "#" + haystack;
    vector<int> z = zFunction(s);
    int m = (int)needle.size();
    for (int i = m + 1; i < (int)s.size(); i++)
        if (z[i] >= m)
            return i - m - 1;
    return -1;
}

/*
Approach:
Z-box reuses matches;
search pat#text.
Time Complexity:
O(n+m)
Space Complexity:
O(n+m)
Key Idea:
[l, r] window is the Z-box.
*/
