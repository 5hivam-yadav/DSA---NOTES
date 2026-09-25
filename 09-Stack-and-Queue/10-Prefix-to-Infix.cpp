/*
Problem: Prefix to Infix
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Stack
Statement: Given a prefix expression, convert it to a fully parenthesized infix string scanning right to left.
Sample Input: s = "*+abc"
Sample Output: "(a+b)*c"
Explanation: Operator combines the next two operands.
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

string pre2in(string s) {
    stack<string> st;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        char c = s[i];
        if (isalnum(c)) st.push(string(1, c));
        else {
            string a = st.top();
            st.pop();
            string b = st.top();
            st.pop();
            st.push('(' + a + c + b + ')');
        }
    }
    return st.top();
}

int main() {
    string s = "*+abc";

    auto ans = pre2in(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Scan right, combine.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Operand order a op b.
*/
