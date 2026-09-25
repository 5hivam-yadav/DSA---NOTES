/*
Problem: Insert Node
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given a singly linked list head and value x, append x at the tail and return the head.
Sample Input: head = [1, 2], x = 3
Sample Output: [1, 2, 3]
Explanation: 3 is linked after node 2.
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
ListNode* insertHead(ListNode* h, int x) {
    auto n = new ListNode(x);
    n->next = h;
    return n;
}
ListNode* insertTail(ListNode* h, int x) {
    auto n = new ListNode(x);
    if (!h) return n;
    auto t = h;
    while (t->next) t = t->next;
    t->next = n;
    return h;
}

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head = insertTail(head, 3);
    for (ListNode* cur = head; cur; cur = cur->next) {
        cout << cur->val << (cur->next ? " " : "");
    }
    cout << endl;
    return 0;
}

/*
Approach:
Head O(1), tail O(n).
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Relink pointers.
*/
