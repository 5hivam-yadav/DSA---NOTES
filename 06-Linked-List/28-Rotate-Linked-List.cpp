/*
Problem: Rotate Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Linked List
Statement: Given a list head and k, rotate the list right by k places (k %= length, reconnect tail to head).
Sample Input: head = [1, 2, 3, 4, 5], k = 2
Sample Output: [4, 5, 1, 2, 3]
Explanation: Last two nodes move to the front.
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
    ListNode* rotateRight(ListNode* h, int k) {
        if (!h || !h->next || k == 0) return h;
        int n = 1;
        auto t = h;
        while (t->next) {
            t = t->next;
            n++;
        }
        t->next = h;
        k %= n;
        for (int i = 0; i < n - k; i++) t = t->next;
        h = t->next;
        t->next = nullptr;
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
    head = sol.rotateRight(head, 2);
    for (ListNode* cur = head; cur; cur = cur->next) cout << cur->val << (cur->next ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Ring + cut.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
k %= n circle.
*/
