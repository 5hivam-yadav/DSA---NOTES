/*
Problem: Insert in Doubly Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given a doubly linked list head, position and value, insert the value
there and return the head. Sample Input: head = [1, 2, 4], pos = 2, x = 3 Sample
Output: [1, 2, 3, 4] Explanation: 3 is spliced between 2 and 4.
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

struct DNode {
    int val;
    DNode *prev;
    DNode *next;
    DNode(int x) : val(x), prev(nullptr), next(nullptr) {}
};
DNode *insHead(DNode *h, int x) {
    auto n = new DNode(x);
    n->next = h;
    if (h)
        h->prev = n;
    return n;
}

int main() {
    DNode *head = new DNode(1);
    DNode *n2 = new DNode(2);
    DNode *n4 = new DNode(4);
    head->next = n2;
    n2->prev = head;
    n2->next = n4;
    n4->prev = n2;
    DNode *n3 = new DNode(3);
    n3->next = n4;
    n3->prev = n2;
    n2->next = n3;
    n4->prev = n3;
    for (DNode *cur = head; cur; cur = cur->next) {
        cout << cur->val << (cur->next ? " " : "");
    }
    cout << endl;
    return 0;
}

/*
Approach:
Fix both links.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
Update prev/next.
*/
