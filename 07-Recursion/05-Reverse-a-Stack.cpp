/*
Problem: Reverse a Stack
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Stack
Statement: Given a stack, reverse it in place using recursion (pop all, insert each at the bottom).
Sample Input: stack top->bottom = [1, 2, 3]
Sample Output: [3, 2, 1]
Explanation: Bottom-insertion flips the order.
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

void insB(stack<int>& st, int x) {
    if (st.empty()) {
        st.push(x);
        return;
    }
    int t = st.top();
    st.pop();
    insB(st, x);
    st.push(t);
}
void revS(stack<int>& st) {
    if (st.empty()) return;
    int x = st.top();
    st.pop();
    revS(st);
    insB(st, x);
}

int main() {
    stack<int> st;
    vector<int> vals = {3, 2, 1}; // bottom to top so top is 1
    for (int x : vals) st.push(x);
    revS(st);
    vector<int> res;
    while (!st.empty()) { res.push_back(st.top()); st.pop(); }
    for (size_t i = 0; i < res.size(); i++) cout << res[i] << (i + 1 < res.size() ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Insert-at-bottom recurse.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Bottom insert.
*/
