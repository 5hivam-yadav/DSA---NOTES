/*
Problem: Reverse Nodes in K Group
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given a list head and k, reverse nodes k at a time, leaving a short
tail as-is. Sample Input: head = [1, 2, 3, 4, 5], k = 2 Sample Output: [2, 1, 4,
3, 5] Explanation: Pairs swap; the final 5 stays.
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
    ListNode *reverseKGroup(ListNode *h, int k) {
        auto c = h;
        for (int i = 0; i < k; i++) {
            if (!c)
                return h;
            c = c->next;
        }
        ListNode *p = nullptr;
        auto t = h;
        for (int i = 0; i < k; i++) {
            auto n = t->next;
            t->next = p;
            p = t;
            t = n;
        }
        h->next = reverseKGroup(t, k);
        return p;
    }
};

static ListNode *build(const vector<int> &v) {
    ListNode d(0);
    ListNode *t = &d;
    for (int x : v) {
        t->next = new ListNode(x);
        t = t->next;
    }
    return d.next;
}
int main() {
    ListNode *head = build({1, 2, 3, 4, 5});
    Solution sol;
    head = sol.reverseKGroup(head, 2);
    for (ListNode *cur = head; cur; cur = cur->next)
        cout << cur->val << (cur->next ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Reverse k, link recurse.
Time Complexity:
O(n)
Space Complexity:
O(n/k) stack
Key Idea:
Block reverse.
*/
