/*
Problem: Min Stack
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Stack
Statement: Design a stack supporting push, pop, top and getMin, each in O(1)
time. Sample Input: push(-2), push(0), push(-3), getMin(), pop(), top(),
getMin() Sample Output: -3, 0, -2 Explanation: getMin is -3; after pop, top is 0
and getMin is -2.
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

class MinStack {
    stack<pair<int, int>> st;

  public:
    void push(int x) {
        int m = st.empty() ? x : min(x, st.top().second);
        st.push({x, m});
    }
    void pop() { st.pop(); }
    int top() { return st.top().first; }
    int getMin() { return st.top().second; }
};

/*
Approach:
Store (val, min).
Time Complexity:
O(1)
Space Complexity:
O(n)
Key Idea:
Carry min down.
*/
