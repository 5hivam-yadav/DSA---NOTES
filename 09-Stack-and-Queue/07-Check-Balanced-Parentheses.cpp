/*
Problem: Check Balanced Parentheses
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Stack
Statement: Given a string of brackets, return true if every opener closes in the correct order (stack).
Sample Input: s = "()[]{}"
Sample Output: true
Explanation: Each pair nests and closes properly.
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
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') st.push(c);
            else {
                if (st.empty()) return false;
                char t = st.top();
                st.pop();
                if ((c == ')' && t != '(') || (c == ']' && t != '[') || (c == '}' && t != '{')) return false;
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
