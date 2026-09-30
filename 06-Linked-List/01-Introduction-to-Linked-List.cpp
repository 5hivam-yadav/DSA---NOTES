/*
Problem: Introduction to Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Introduce singly linked list basics: build nodes 1->2->3 and traverse
printing each value. Sample Input: values = [1,2,3] Sample Output: [1,2,3]
Explanation: Head links 1 -> 2 -> 3 -> null.
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
ListNode *build(vector<int> &v) {
    ListNode d(0);
    auto t = &d;
    for (int x : v) {
        t->next = new ListNode(x);
        t = t->next;
    }
    return d.next;
}
int length(ListNode *h) {
    int c = 0;
    while (h) {
        c++;
        h = h->next;
    }
    return c;
}

int main() {
    vector<int> values = {1, 2, 3};
    ListNode *head = build(values);
    for (ListNode *cur = head; cur; cur = cur->next) {
        cout << cur->val << (cur->next ? " " : "");
    }
    cout << endl;
    return 0;
}

/*
Approach:
Build + traverse.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Nodes + pointers.
*/
