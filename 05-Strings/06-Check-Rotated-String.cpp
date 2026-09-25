/*
Problem: Check Rotated String
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Strings
Statement: Given strings s and goal, return true if goal is a rotation of s (check goal inside s+s with equal lengths).
Sample Input: s = "abcde", goal = "cdeab"
Sample Output: true
Explanation: "cdeab" appears inside "abcdeabcde".
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
    bool rotateString(string s, string g) {
        return s.size() == g.size() && (s + s).find(g) != string::npos;
    }
};

int main() {
    string s = "abcde";
    string goal = "cdeab";

    Solution sol;
    auto ans = sol.rotateString(s, goal);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
s+s contains goal.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Rotation substring.
*/
