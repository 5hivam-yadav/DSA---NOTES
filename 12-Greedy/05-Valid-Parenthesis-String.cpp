/*
Problem: Valid Parenthesis String
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Greedy
Statement: Given a string of ( ) and *, return true if stars can act as brackets to balance it (greedy ranges).
Sample Input: s = "(*))"
Sample Output: true
Explanation: Star acts as ( to balance the extra ).
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
    bool checkValidString(string s) {
        int lo = 0, hi = 0;
        for (char c : s) {
            if (c == '(') {
                lo++;
                hi++;
            }
            else if (c == ')') {
                lo--;
                hi--;
            }
            else {
                lo--;
                hi++;
            }
            if (hi < 0) return false;
            lo = max(lo, 0);
        }
        return lo == 0;
    }
};

int main() {
    string s = "(*))";

    Solution sol;
    auto ans = sol.checkValidString(s);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Range of open count.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
lo/hi bounds.
*/
