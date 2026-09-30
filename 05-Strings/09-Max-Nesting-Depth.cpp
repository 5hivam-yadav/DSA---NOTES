/*
Problem: Max Nesting Depth
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Strings
Statement: Given a valid parentheses string, return its maximum nesting depth
with a counter. Sample Input: s = "(1+(2*3)+((8)/4))+1" Sample Output: 3
Explanation: Innermost ((8)/4) nests 3 deep.
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
    int maxDepth(string s) {
        int d = 0, b = 0;
        for (char c : s) {
            if (c == '(') {
                d++;
                b = max(b, d);
            } else if (c == ')')
                d--;
        }
        return b;
    }
};

int main() {
    string s = "(1+(2*3)+((8)/4))+1";

    Solution sol;
    auto ans = sol.maxDepth(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Counter max.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Depth track.
*/
