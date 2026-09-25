/*
Problem: Middle of Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given the head of a singly linked list, return the middle node (second middle for even length; slow/fast pointers).
Sample Input: head = [1, 2, 3, 4, 5]
Sample Output: [3, 4, 5]
Explanation: Node 3 starts the second half.
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
    ListNode* middleNode(ListNode* h) {
        auto s = h, f = h;
        while (f && f->next) {
            s = s->next;
            f = f->next->next;
        }
        return s;
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
    ListNode* mid = sol.middleNode(head);
    for (ListNode* cur = mid; cur; cur = cur->next) cout << cur->val << (cur->next ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
fast 2x.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Second middle.
*/
