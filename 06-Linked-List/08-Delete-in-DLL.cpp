/*
Problem: Delete in Doubly Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given a doubly linked list head and value x, delete the first node holding x and return the head.
Sample Input: head = [1, 2, 3], x = 2
Sample Output: [1, 3]
Explanation: Prev/next links bypass node 2.
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
DNode* delHead(DNode* h) {
    if (!h) return nullptr;
    auto n = h->next;
    if (n) n->prev = nullptr;
    delete h;
    return n;
}

int main() {
    DNode* n1 = new DNode(1);
    DNode* n2 = new DNode(2);
    DNode* n3 = new DNode(3);
    n1->next = n2; n2->prev = n1;
    n2->next = n3; n3->prev = n2;
    n1->next = n3; n3->prev = n1;
    delete n2;
    for (DNode* cur = n1; cur; cur = cur->next) {
        cout << cur->val << (cur->next ? " " : "");
    }
    cout << endl;
    return 0;
}

/*
Approach:
Bypass + fix prev.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
Two-link bypass.
*/
