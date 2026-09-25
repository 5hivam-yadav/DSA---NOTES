/*
Problem: Min Stack
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Stack
Statement: Design a stack supporting push, pop, top and getMin, each in O(1) time.
Sample Input: push(-2), push(0), push(-3), getMin(), pop(), top(), getMin()
Sample Output: -3, 0, -2
Explanation: getMin is -3; after pop, top is 0 and getMin is -2.
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

class MinStack {
    stack<pair<int, int>> st;
public:
    void push(int x) {
        int m = st.empty() ? x : min(x, st.top().second);
        st.push({x, m});
    }
    void pop() {
        st.pop();
    }
    int top() {
        return st.top().first;
    }
    int getMin() {
        return st.top().second;
    }
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
