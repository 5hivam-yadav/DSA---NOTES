/*
Problem: Queue Using Stack
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Queue / Deque
Statement: Implement a queue with two stacks: push to input stack, pop/peek from
output stack (amortized O(1)). Sample Input: push 1, push 2, pop, peek Sample
Output: 1, 2 Explanation: Output stack reverses input into FIFO order.
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

class MyQueue {
    stack<int> in, out;
    void move() {
        if (out.empty())
            while (!in.empty()) {
                out.push(in.top());
                in.pop();
            }
    }

  public:
    void push(int x) { in.push(x); }
    int pop() {
        move();
        int x = out.top();
        out.pop();
        return x;
    }
    int peek() {
        move();
        return out.top();
    }
    bool empty() { return in.empty() && out.empty(); }
};

/*
Approach:
Amortized transfer.
Time Complexity:
O(1) amortized
Space Complexity:
O(n)
Key Idea:
Two-stack reversal.
*/
