/*
Problem: Merge M Sorted Lists
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Heap
Statement: Given k sorted linked lists, merge them into one sorted list with a
min-heap in O(N log k). Sample Input: lists = [[1,4,5],[1,3,4],[2,6]] Sample
Output: [1,1,2,3,4,4,5,6] Explanation: Heap always yields the smallest head.
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

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
  public:
    struct C {
        bool operator()(ListNode *a, ListNode *b) { return a->val > b->val; }
    };
    ListNode *mergeKLists(vector<ListNode *> &L) {
        priority_queue<ListNode *, vector<ListNode *>, C> pq;
        for (auto h : L)
            if (h)
                pq.push(h);
        ListNode d(0);
        auto t = &d;
        while (!pq.empty()) {
            auto n = pq.top();
            pq.pop();
            t->next = n;
            t = n;
            if (n->next)
                pq.push(n->next);
        }
        return d.next;
    }
};

/*
Approach:
Heap of heads.
Time Complexity:
O(N log K)
Space Complexity:
O(K)
Key Idea:
Min head first.
*/
