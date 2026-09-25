/*
Problem: Reverse Doubly Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given a doubly linked list head, reverse it by swapping prev/next on every node and return the new head.
Sample Input: head = [1, 2, 3]
Sample Output: [3, 2, 1]
Explanation: All links flip direction.
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
DNode* rev(DNode* h) {
    DNode* p = nullptr;
    while (h) {
        DNode* n = h->next;
        h->next = p;
        h->prev = n;
        p = h;
        h = n;
    }
    return p;
}

int main() {
    DNode* n1 = new DNode(1);
    DNode* n2 = new DNode(2);
    DNode* n3 = new DNode(3);
    n1->next = n2; n2->prev = n1;
    n2->next = n3; n3->prev = n2;
    DNode* head = rev(n1);
    for (DNode* cur = head; cur; cur = cur->next) {
        cout << cur->val << (cur->next ? " " : "");
    }
    cout << endl;
    return 0;
}

/*
Approach:
Swap prev/next walking.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Swap links.
*/
