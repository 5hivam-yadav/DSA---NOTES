/*
Problem: Stack Using Queue
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Queue / Deque
Statement: Implement a stack with queues: push then rotate so the newest stays
front (O(n) push, O(1) pop). Sample Input: push 1, push 2, pop, top Sample
Output: 2, 1 Explanation: Newest element is always dequeued first.
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

class MyStack {
    queue<int> q;

  public:
    void push(int x) {
        q.push(x);
        for (size_t i = 0; i + 1 < q.size(); i++) {
            q.push(q.front());
            q.pop();
        }
    }
    int pop() {
        int x = q.front();
        q.pop();
        return x;
    }
    int top() { return q.front(); }
    bool empty() { return q.empty(); }
};

/*
Approach:
Rotate after push.
Time Complexity:
O(n) push
Space Complexity:
O(n)
Key Idea:
Front = top.
*/
