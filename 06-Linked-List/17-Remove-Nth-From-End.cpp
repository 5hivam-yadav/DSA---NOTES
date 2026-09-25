/*
Problem: Remove Nth from End
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given a list head and n, remove the n-th node from the end in one pass and return the head.
Sample Input: head = [1, 2, 3, 4, 5], n = 2
Sample Output: [1, 2, 3, 5]
Explanation: Node 4 is removed.
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
    ListNode* removeNthFromEnd(ListNode* h, int n) {
        ListNode d(0);
        d.next = h;
        auto a = &d, b = &d;
        for (int i = 0; i <= n; i++) b = b->next;
        while (b) {
            a = a->next;
            b = b->next;
        }
        a->next = a->next->next;
        return d.next;
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
    head = sol.removeNthFromEnd(head, 2);
    for (ListNode* cur = head; cur; cur = cur->next) cout << cur->val << (cur->next ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Gap n.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Dummy handles head.
*/
