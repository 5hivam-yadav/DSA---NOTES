/*
Problem: Generate Parentheses
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Recursion
Statement: Given n, return all well-formed parentheses strings of n pairs via backtracking.
Sample Input: n = 3
Sample Output: ["((()))","(()())","(())()","()(())","()()()"]
Explanation: Catalan(3) = 5 valid strings.
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
    vector<string> ans;
    void f(int o, int c, string cur) {
        if (o == 0 && c == 0) {
            ans.push_back(cur);
            return;
        }
        if (o > 0) f(o - 1, c, cur + '(');
        if (c > o) f(o, c - 1, cur + ')');
    }
    vector<string> generateParenthesis(int n) {
        f(n, n, "");
        return ans;
    }
};

int main() {
    int n = 3;

    Solution sol;
    auto ans = sol.generateParenthesis(n);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
open/close counts.
Time Complexity:
O(4^n/sqrt n)
Space Complexity:
O(n)
Key Idea:
Close only if ahead.
*/
