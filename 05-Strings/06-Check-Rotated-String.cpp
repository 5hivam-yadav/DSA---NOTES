/*
Problem: Check Rotated String
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Strings
Statement: Given strings s and goal, return true if goal is a rotation of s
(check goal inside s+s with equal lengths). Sample Input: s = "abcde", goal =
"cdeab" Sample Output: true Explanation: "cdeab" appears inside "abcdeabcde".
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
