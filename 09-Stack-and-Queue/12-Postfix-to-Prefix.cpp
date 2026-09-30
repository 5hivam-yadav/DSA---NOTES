/*
Problem: Postfix to Prefix
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Stack
Statement: Given a postfix expression, convert it to prefix with a stack
(operator + two operands). Sample Input: s = "ab+c*" Sample Output: "*+abc"
Explanation: Same tree printed pre-order.
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

string post2pre(string s) {
    stack<string> st;
    for (char c : s) {
        if (isalnum(c))
            st.push(string(1, c));
        else {
            string b = st.top();
            st.pop();
            string a = st.top();
            st.pop();
            st.push(c + a + b);
        }
    }
    return st.top();
}

int main() {
    string s = "ab+c*";

    auto ans = post2pre(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Pre = op a b.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Pop b then a.
*/
