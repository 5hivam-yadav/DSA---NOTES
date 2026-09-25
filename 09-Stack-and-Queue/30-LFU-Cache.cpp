/*
Problem: LFU Cache
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Monotonic Stack
Statement: Design an LFU cache with get/put in O(1); evict the least frequently used (ties: least recently used).
Sample Input: capacity = 2, put(1,1), put(2,2), get(1), put(3,3), get(2)
Sample Output: 1, -1
Explanation: Key 1 has frequency 2, so key 2 is evicted.
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
#include <list>
using namespace std;

class LFUCache {
    int cap, mn = 0;
    unordered_map<int, pair<int, int>> kv;
    unordered_map<int, int> kf;
    unordered_map<int, list<int>> fl;
    unordered_map<int, unordered_map<int, list<int>::iterator>> pos;
public:
    LFUCache(int c): cap(c) {}
    void touch(int k) {
        int f = kf[k];
        fl[f].erase(pos[k][f]);
        if (fl[f].empty() && f == mn) mn++;
        kf[k]++;
        fl[kf[k]].push_back(k);
        pos[k][kf[k]] = prev(fl[kf[k]].end());
    }
    int get(int k) {
        if (!kv.count(k)) return -1;
        touch(k);
        return kv[k].first;
    }
    void put(int k, int v) {
        if (cap <= 0) return;
        if (kv.count(k)) {
            kv[k].first = v;
            touch(k);
            return;
        }
        if ((int)kv.size() == cap) {
            int e = fl[mn].front();
            fl[mn].pop_front();
            kv.erase(e);
            kf.erase(e);
            pos.erase(e);
        }
        kv[k] = {v, 0};
        kf[k] = 1;
        mn = 1;
        fl[1].push_back(k);
        pos[k][1] = prev(fl[1].end());
    }
};

/*
Approach:
Freq lists + min.
Time Complexity:
O(1)
Space Complexity:
O(cap)
Key Idea:
Evict min-freq LRU.
*/
