/*
Problem: Sort a Stack
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Medium
Pattern: Stack
Statement: Given a stack, sort it ascending (top smallest) using recursion: pop, sort rest, insert in order.
Sample Input: stack top->bottom = [3, 1, 4, 2]
Sample Output: [1, 2, 3, 4]
Explanation: Elements are inserted back in sorted position.
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

void insS(stack<int>& st, int x) {
    if (st.empty() || st.top() <= x) {
        st.push(x);
        return;
    }
    int t = st.top();
    st.pop();
    insS(st, x);
    st.push(t);
}
void sortS(stack<int>& st) {
    if (st.empty()) return;
    int x = st.top();
    st.pop();
    sortS(st);
    insS(st, x);
}

int main() {
    stack<int> st;
    vector<int> vals = {2, 4, 1, 3}; // bottom to top, so top is 3
    for (int x : vals) st.push(x);
    sortS(st);
    vector<int> res;
    while (!st.empty()) { res.push_back(st.top()); st.pop(); }
    reverse(res.begin(), res.end()); // bottom to top
    for (size_t i = 0; i < res.size(); i++) cout << res[i] << (i + 1 < res.size() ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Sorted insert recurse.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Recursion replaces loop.
*/
