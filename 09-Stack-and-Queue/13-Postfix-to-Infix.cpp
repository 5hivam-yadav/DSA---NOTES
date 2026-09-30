/*
Problem: Postfix to Infix
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Stack
Statement: Given a postfix expression, convert it to a fully parenthesized infix
string with a stack. Sample Input: s = "ab+c*" Sample Output: "(a+b)*c"
Explanation: Operands pop, combine with operator, push back.
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

string post2in(string s) {
    stack<string> st;
    for (char c : s) {
        if (isalnum(c))
            st.push(string(1, c));
        else {
            string b = st.top();
            st.pop();
            string a = st.top();
            st.pop();
            st.push('(' + a + c + b + ')');
        }
    }
    return st.top();
}

int main() {
    string s = "ab+c*";

    auto ans = post2in(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Scan left combine.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Parenthesize.
*/
