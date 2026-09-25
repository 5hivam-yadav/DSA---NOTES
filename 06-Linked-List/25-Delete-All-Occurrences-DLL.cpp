/*
Problem: Delete All Occurrences Doubly Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Linked List
Statement: Given a doubly linked list head and key x, delete every node holding x and return the head.
Sample Input: head = [1, 2, 1, 3, 1], x = 1
Sample Output: [2, 3]
Explanation: All three 1s are unlinked.
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

struct DNode {
    int val;
    DNode* prev;
    DNode* next;
    DNode(int x): val(x), prev(nullptr), next(nullptr) {}
};
DNode* delAll(DNode* h, int x) {
    auto t = h;
    while (t) {
        auto n = t->next;
        if (t->val == x) {
            if (t->prev) t->prev->next = t->next;
            else h = t->next;
            if (t->next) t->next->prev = t->prev;
            delete t;
        }
        t = n;
    }
    return h;
}

int main() {
    vector<int> v = {1, 2, 1, 3, 1};
    DNode* head = new DNode(v[0]);
    DNode* cur = head;
    for (size_t i = 1; i < v.size(); i++) {
        DNode* n = new DNode(v[i]);
        cur->next = n; n->prev = cur; cur = n;
    }
    head = delAll(head, 1);
    for (cur = head; cur; cur = cur->next) cout << cur->val << (cur->next ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Splice all matches.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Fix both links.
*/
