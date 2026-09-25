/*
Problem: Delete Middle Node
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given a list head, delete the middle node (second middle if even) and return the head.
Sample Input: head = [1, 2, 3, 4, 5]
Sample Output: [1, 2, 4, 5]
Explanation: Node 3 is removed.
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
    ListNode* deleteMiddle(ListNode* h) {
        if (!h || !h->next) return nullptr;
        auto s = h, f = h, p = h;
        while (f && f->next) {
            p = s;
            s = s->next;
            f = f->next->next;
        }
        p->next = s->next;
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
    head = sol.deleteMiddle(head);
    for (ListNode* cur = head; cur; cur = cur->next) cout << cur->val << (cur->next ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Track prev of slow.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Slow + prev.
*/
