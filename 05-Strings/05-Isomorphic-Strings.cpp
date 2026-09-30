/*
Problem: Isomorphic Strings
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Strings
Statement: Given strings s and t, return true if characters map one-to-one
preserving order (two maps for both directions). Sample Input: s = "egg", t =
"add" Sample Output: true Explanation: e->a and g->d is consistent.
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
    bool isIsomorphic(string s, string t) {
        int m1[256] = {0}, m2[256] = {0};
        for (size_t i = 0; i < s.size(); i++) {
            if (m1[(unsigned char)s[i]] != m2[(unsigned char)t[i]])
                return false;
            m1[(unsigned char)s[i]] = m2[(unsigned char)t[i]] = (int)i + 1;
        }
        return true;
    }
};

int main() {
    string s = "egg";
    string t = "add";

    Solution sol;
    auto ans = sol.isIsomorphic(s, t);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Map both ways.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Bijection check.
*/
