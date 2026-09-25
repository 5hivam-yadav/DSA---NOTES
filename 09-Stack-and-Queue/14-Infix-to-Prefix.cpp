/*
Problem: Infix to Prefix
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Stack
Statement: Given an infix expression, convert it to prefix (reverse, postfix, reverse with bracket swap).
Sample Input: s = "a+b*c"
Sample Output: "+a*bc"
Explanation: Higher precedence * binds first.
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

string in2pre(string s) {
    reverse(s.begin(), s.end());
    for (char& c : s) {
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }
    int prec(char c);
    string t;
    stack<char> st;
    auto pr = [](char c) {
        if (c == '^') return 3;
        if (c == '*' || c == '/') return 2;
        if (c == '+' || c == '-') return 1;
        return 0;
    };
    for (char c : s) {
        if (isalnum(c)) t += c;
        else if (c == '(') st.push(c);
        else if (c == ')') {
            while (st.top() != '(') {
                t += st.top();
                st.pop();
            }
            st.pop();
        }
        else {
            while (!st.empty() && pr(st.top()) > pr(c)) {
                t += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty()) {
        t += st.top();
        st.pop();
    }
    reverse(t.begin(), t.end());
    return t;
}

int main() {
    string s = "a+b*c";

    auto ans = in2pre(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Reverse + postfix + reverse.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Swap assoc in reverse.
*/
