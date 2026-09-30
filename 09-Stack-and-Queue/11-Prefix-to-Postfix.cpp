/*
Problem: Prefix to Postfix
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Stack
Statement: Given a prefix expression, convert it to postfix scanning right to
left with a stack. Sample Input: s = "*+abc" Sample Output: "ab+c*" Explanation:
Operands are emitted in postfix order.
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

string pre2post(string s) {
    stack<string> st;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        char c = s[i];
        if (isalnum(c))
            st.push(string(1, c));
        else {
            string a = st.top();
            st.pop();
            string b = st.top();
            st.pop();
            st.push(a + b + c);
        }
    }
    return st.top();
}

int main() {
    string s = "*+abc";

    auto ans = pre2post(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Post = a b op.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Pop a then b.
*/
