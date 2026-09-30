/*
Problem: Remove Outermost Parentheses
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Strings
Statement: Given a valid parentheses string of primitives, remove the outermost
brackets of each primitive. Sample Input: s = "(()())(())" Sample Output:
"()()()" Explanation: (()()) becomes ()() and (()) becomes ().
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
    string removeOuterParentheses(string s) {
        string r;
        int d = 0;
        for (char c : s) {
            if (c == '(') {
                if (d > 0)
                    r += c;
                d++;
            } else {
                d--;
                if (d > 0)
                    r += c;
            }
        }
        return r;
    }
};

int main() {
    string s = "(()())(())";

    Solution sol;
    auto ans = sol.removeOuterParentheses(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Depth counter.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Skip depth edges.
*/
