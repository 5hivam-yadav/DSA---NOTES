/*
Problem: Add Two Numbers
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given two numbers as reverse-order linked lists, return their sum as
a reverse-order list. Sample Input: l1 = [2, 4, 3], l2 = [5, 6, 4] Sample
Output: [7, 0, 8] Explanation: 342 + 465 = 807, stored reversed.
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
    ListNode *addTwoNumbers(ListNode *a, ListNode *b) {
        ListNode d(0);
        auto t = &d;
        int c = 0;
        while (a || b || c) {
            int s = c;
            if (a) {
                s += a->val;
                a = a->next;
            }
            if (b) {
                s += b->val;
                b = b->next;
            }
            c = s / 10;
            t->next = new ListNode(s % 10);
            t = t->next;
        }
        return d.next;
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
    ListNode *l1 = build({2, 4, 3});
    ListNode *l2 = build({5, 6, 4});
    Solution sol;
    ListNode *ans = sol.addTwoNumbers(l1, l2);
    for (ListNode *cur = ans; cur; cur = cur->next)
        cout << cur->val << (cur->next ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Digit + carry.
Time Complexity:
O(max)
Space Complexity:
O(max)
Key Idea:
Carry forward.
*/
