/*
Problem: Check Balanced Parentheses
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Stack
Statement: Given a string of brackets, return true if every opener closes in the
correct order (stack). Sample Input: s = "()[]{}" Sample Output: true
Explanation: Each pair nests and closes properly.
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
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{')
                st.push(c);
            else {
                if (st.empty())
                    return false;
                char t = st.top();
                st.pop();
                if ((c == ')' && t != '(') || (c == ']' && t != '[') ||
                    (c == '}' && t != '{'))
                    return false;
            }
        }
        return st.empty();
    }
};

int main() {
    string s = "()[]{}";

    Solution sol;
    auto ans = sol.isValid(s);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Push open, match close.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
LIFO nesting.
*/
