/*
Problem: Odd Even Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Linked List
Statement: Given a list head, group odd-indexed nodes first then even-indexed
nodes, in place. Sample Input: head = [1, 2, 3, 4, 5] Sample Output: [1, 3, 5,
2, 4] Explanation: Odd positions 1,3,5 come before 2,4.
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
    ListNode *oddEvenList(ListNode *h) {
        if (!h)
            return h;
        auto o = h, e = h->next, eh = e;
        while (e && e->next) {
            o->next = e->next;
            o = o->next;
            e->next = o->next;
            e = e->next;
        }
        o->next = eh;
        return h;
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
    head = sol.oddEvenList(head);
    for (ListNode *cur = head; cur; cur = cur->next)
        cout << cur->val << (cur->next ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Two chains + join.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Regroup in place.
*/
