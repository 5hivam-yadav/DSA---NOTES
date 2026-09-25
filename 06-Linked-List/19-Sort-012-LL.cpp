/*
Problem: Sort 0-1-2 Linked List
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Medium
Pattern: Linked List
Statement: Given a linked list of 0s, 1s and 2s, sort it by counting values then overwriting node data.
Sample Input: head = [1,0,2,1,0]
Sample Output: [0,0,1,1,2]
Explanation: Counts 0x2, 1x2, 2x1 are written back.
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
ListNode* sort012(ListNode* h) {
    ListNode z(0), o(0), t(0);
    auto a = &z, b = &o, c = &t;
    while (h) {
        if (h->val == 0) {
            a->next = h;
            a = a->next;
        }
        else if (h->val == 1) {
            b->next = h;
            b = b->next;
        }
        else {
            c->next = h;
            c = c->next;
        }
        h = h->next;
    }
    c->next = nullptr;
    b->next = t.next;
    a->next = (o.next ? o.next : t.next);
    return z.next;
}

static ListNode* build(const vector<int>& v) {
    ListNode d(0); ListNode* t = &d;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return d.next;
}
int main() {
    ListNode* head = build({1, 0, 2, 1, 0});
    head = sort012(head);
    for (ListNode* cur = head; cur; cur = cur->next) cout << cur->val << (cur->next ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Three chains join.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Stable buckets.
*/
