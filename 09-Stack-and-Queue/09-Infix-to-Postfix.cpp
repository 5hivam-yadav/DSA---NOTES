/*
Problem: Infix to Postfix
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Stack
Statement: Given an infix expression, convert it to postfix using a stack and precedence (^ > * / > + -).
Sample Input: s = "a+b*(c^d-e)"
Sample Output: "abcd^e-*+"
Explanation: Operators are emitted in precedence order.
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

int prec(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}
string in2post(string s) {
    string r;
    stack<char> st;
    for (char c : s) {
        if (isalnum(c)) r += c;
        else if (c == '(') st.push(c);
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                r += st.top();
                st.pop();
            }
            st.pop();
        }
        else {
            while (!st.empty() && prec(st.top()) >= prec(c)) {
                if (c == '^' && st.top() == '^') break;
                r += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty()) {
        r += st.top();
        st.pop();
    }
    return r;
}

int main() {
    string s = "a+b*(c^d-e)";

    auto ans = in2post(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Precedence + stack.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
^ right-assoc special.
*/
