/*
Problem: Stack Using Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Stack
Statement: Implement a stack with a singly linked list (push/pop at head in O(1)).
Sample Input: push 1, push 2, pop, top
Sample Output: 2, 1
Explanation: Head is always the top.
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

struct N {
    int v;
    N* next;
    N(int x): v(x), next(nullptr) {}
};

class LLStack {
    N* h = nullptr;
public:
    void push(int x) {
        auto n = new N(x);
        n->next = h;
        h = n;
    }
    int pop() {
        if (!h) return -1;
        int x = h->v;
        auto t = h;
        h = h->next;
        delete t;
        return x;
    }
};

/*
Approach:
Push at head.
Time Complexity:
O(1)
Space Complexity:
O(n)
Key Idea:
Head = top.
*/
