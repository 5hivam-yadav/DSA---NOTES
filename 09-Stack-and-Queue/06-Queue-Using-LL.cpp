/*
Problem: Queue Using Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Queue / Deque
Statement: Implement a queue with a singly linked list supporting enqueue at tail and dequeue at head.
Sample Input: enqueue 1, enqueue 2, dequeue, front
Sample Output: 1, 2
Explanation: FIFO order is preserved.
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

class LLQueue {
    N *f = nullptr, *r = nullptr;
public:
    void push(int x) {
        auto n = new N(x);
        if (!r) {
            f = r = n;
            return;
        }
        r->next = n;
        r = n;
    }
    int pop() {
        if (!f) return -1;
        int x = f->v;
        auto t = f;
        f = f->next;
        if (!f) r = nullptr;
        delete t;
        return x;
    }
};

/*
Approach:
Head/tail pointers.
Time Complexity:
O(1)
Space Complexity:
O(n)
Key Idea:
Tail push head pop.
*/
