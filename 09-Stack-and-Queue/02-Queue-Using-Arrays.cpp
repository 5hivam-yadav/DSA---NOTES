/*
Problem: Queue Using Arrays
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Queue / Deque
Statement: Implement a queue with a fixed array (or circular buffer) supporting push, pop, peek and size.
Sample Input: push 1, push 2, pop, peek
Sample Output: 1, 2
Explanation: FIFO: 1 leaves first, 2 is front next.
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

class ArrQueue {
    int a[1000], f = 0, r = -1;
public:
    void push(int x) {
        a[++r] = x;
    }
    int pop() {
        return f > r ? -1 : a[f++];
    }
    int front() {
        return f > r ? -1 : a[f];
    }
};

/*
Approach:
front/rear indices.
Time Complexity:
O(1)
Space Complexity:
O(N)
Key Idea:
Circular variant reuses.
*/
