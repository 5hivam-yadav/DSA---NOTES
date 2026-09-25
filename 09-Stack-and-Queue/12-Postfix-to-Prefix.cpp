/*
Problem: Postfix to Prefix
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Stack
Statement: Given a postfix expression, convert it to prefix with a stack (operator + two operands).
Sample Input: s = "ab+c*"
Sample Output: "*+abc"
Explanation: Same tree printed pre-order.
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

string post2pre(string s) {
    stack<string> st;
    for (char c : s) {
        if (isalnum(c)) st.push(string(1, c));
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
