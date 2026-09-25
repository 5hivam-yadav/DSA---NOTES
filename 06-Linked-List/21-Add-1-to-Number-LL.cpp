/*
Problem: Add 1 to Number Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Linked List
Statement: Given a number as a linked list of digits (most significant first), add one and return the head.
Sample Input: head = [1, 2, 9]
Sample Output: [1, 3, 0]
Explanation: 129 + 1 = 130.
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
ListNode* rev(ListNode* h) {
    ListNode* p = nullptr;
    while (h) {
        auto n = h->next;
        h->next = p;
        p = h;
        h = n;
    }
    return p;
}
ListNode* add1(ListNode* h) {
    h = rev(h);
    auto t = h;
    int c = 1;
    ListNode* prev = nullptr;
    while (t && c) {
        int s = t->val + c;
        t->val = s % 10;
        c = s / 10;
        prev = t;
        t = t->next;
    }
    if (c) prev->next = new ListNode(c);
    return rev(h);
}

static ListNode* build(const vector<int>& v) {
    ListNode d(0); ListNode* t = &d;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return d.next;
}
int main() {
    ListNode* head = build({1, 2, 9});
    head = add1(head);
    for (ListNode* cur = head; cur; cur = cur->next) cout << cur->val << (cur->next ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Reverse, carry, reverse.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Add from LSD.
*/
