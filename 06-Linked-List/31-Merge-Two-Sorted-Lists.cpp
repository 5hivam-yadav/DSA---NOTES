/*
Problem: Merge Two Sorted Lists
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Linked List
Statement: Given two sorted linked lists, merge them into one sorted list and return its head.
Sample Input: l1 = [1, 2, 4], l2 = [1, 3, 4]
Sample Output: [1, 1, 2, 3, 4, 4]
Explanation: Pick the smaller head at each step.
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
    ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
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
};

static ListNode* build(const vector<int>& v) {
    ListNode d(0); ListNode* t = &d;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return d.next;
}
int main() {
    ListNode* l1 = build({1, 2, 4});
    ListNode* l2 = build({1, 3, 4});
    Solution sol;
    ListNode* ans = sol.mergeTwoLists(l1, l2);
    for (ListNode* cur = ans; cur; cur = cur->next) cout << cur->val << (cur->next ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Dummy merge.
Time Complexity:
O(n+m)
Space Complexity:
O(1)
Key Idea:
Splice smaller.
*/
