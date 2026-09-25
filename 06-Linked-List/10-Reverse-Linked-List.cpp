/*
Problem: Reverse Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given the head of a singly linked list, reverse the list and return the new head.
Sample Input: head = [1, 2, 3, 4, 5]
Sample Output: [5, 4, 3, 2, 1]
Explanation: All next pointers flip to run 5 -> 4 -> 3 -> 2 -> 1.
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
    ListNode* reverseList(ListNode* h) {
        ListNode* p = nullptr;
        while (h) {
            ListNode* n = h->next;
            h->next = p;
            p = h;
            h = n;
        }
        return p;
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
    head = sol.reverseList(head);
    for (ListNode* cur = head; cur; cur = cur->next) cout << cur->val << (cur->next ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
prev/curr swap.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Reroute 3 pointers.
*/
