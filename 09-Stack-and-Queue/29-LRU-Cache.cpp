/*
Problem: LRU Cache
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Monotonic Stack
Statement: Design an LRU cache with get/put in O(1) using a hashmap plus doubly linked list; evict least recently used at capacity.
Sample Input: capacity = 2, put(1,1), put(2,2), get(1), put(3,3), get(2)
Sample Output: 1, -1
Explanation: get(1) hits; key 2 was evicted by put(3,3).
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

class LRUCache {
    struct N {
        int k, v;
        N *p, *n;
        N(int kk, int vv): k(kk), v(vv), p(nullptr), n(nullptr) {}
    };
    int cap;
    unordered_map<int, N*> m;
    N *h, *t;
    void add(N* x) {
        x->n = h->n;
        x->p = h;
        h->n->p = x;
        h->n = x;
    }
    void del(N* x) {
        x->p->n = x->n;
        x->n->p = x->p;
    }
public:
    LRUCache(int c): cap(c) {
        h = new N(0, 0);
        t = new N(0, 0);
        h->n = t;
        t->p = h;
    }
    int get(int k) {
        if (!m.count(k)) return -1;
        N* x = m[k];
        del(x);
        add(x);
        return x->v;
    }
    void put(int k, int v) {
        if (m.count(k)) {
            N* x = m[k];
            x->v = v;
            del(x);
            add(x);
            return;
        }
        if ((int)m.size() == cap) {
            N* x = t->p;
            del(x);
            m.erase(x->k);
            delete x;
        }
        N* x = new N(k, v);
        add(x);
        m[k] = x;
    }
};

/*
Approach:
Hash + DLL.
Time Complexity:
O(1)
Space Complexity:
O(cap)
Key Idea:
Move-to-front.
*/
