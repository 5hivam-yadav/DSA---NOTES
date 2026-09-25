/*
Problem: Sort Linked List
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Medium
Pattern: Linked List
Statement: Given a linked list head, sort it in O(n log n) time and O(log n)/O(1) space with merge sort.
Sample Input: head = [4, 2, 1, 3]
Sample Output: [1, 2, 3, 4]
Explanation: Halves are sorted and merged recursively.
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
    ListNode* mergeL(ListNode* a, ListNode* b) {
        ListNode d(0);
        auto t = &d;
        while (a && b) {
            if (a->val < b->val) {
                t->next = a;
                a = a->next;
            }
            else {
                t->next = b;
                b = b->next;
            }
            t = t->next;
        }
        t->next = a ? a : b;
        return d.next;
    }
    ListNode* sortList(ListNode* h) {
        if (!h || !h->next) return h;
        auto s = h, f = h->next;
        while (f && f->next) {
            s = s->next;
            f = f->next->next;
        }
        auto m = s->next;
        s->next = nullptr;
        return mergeL(sortList(h), sortList(m));
    }
};

static ListNode* build(const vector<int>& v) {
    ListNode d(0); ListNode* t = &d;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return d.next;
}
int main() {
    ListNode* head = build({4, 2, 1, 3});
    Solution sol;
    head = sol.sortList(head);
    for (ListNode* cur = head; cur; cur = cur->next) cout << cur->val << (cur->next ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Split + merge.
Time Complexity:
O(n log n)
Space Complexity:
O(log n)
Key Idea:
Merge sort on links.
*/
