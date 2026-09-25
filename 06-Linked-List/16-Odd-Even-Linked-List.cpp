/*
Problem: Odd Even Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Linked List
Statement: Given a list head, group odd-indexed nodes first then even-indexed nodes, in place.
Sample Input: head = [1, 2, 3, 4, 5]
Sample Output: [1, 3, 5, 2, 4]
Explanation: Odd positions 1,3,5 come before 2,4.
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

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* oddEvenList(ListNode* h) {
        if (!h) return h;
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

static ListNode* build(const vector<int>& v) {
    ListNode d(0); ListNode* t = &d;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return d.next;
}
int main() {
    ListNode* head = build({1, 2, 3, 4, 5});
    Solution sol;
    head = sol.oddEvenList(head);
    for (ListNode* cur = head; cur; cur = cur->next) cout << cur->val << (cur->next ? " " : "");
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
