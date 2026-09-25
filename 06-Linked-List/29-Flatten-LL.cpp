/*
Problem: Flatten Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Linked List
Statement: Given a multilevel list with next and child pointers, flatten it depth-first into one list.
Sample Input: head = [1, 2, 3] with child [4, 5] at 2
Sample Output: [1, 2, 4, 5, 3]
Explanation: Child list splices between 2 and 3.
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

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

class Solution {
public:
    Node* flatten(Node* h) {
        auto t = h;
        while (t) {
            if (t->child) {
                auto n = t->next;
                t->next = t->child;
                t->child->prev = t;
                t->child = nullptr;
                auto e = t->next;
                while (e->next) e = e->next;
                e->next = n;
                if (n) n->prev = e;
            }
            t = t->next;
        }
        return h;
    }
};

int main() {
    Node* n1 = new Node{1, nullptr, nullptr, nullptr};
    Node* n2 = new Node{2, nullptr, nullptr, nullptr};
    Node* n3 = new Node{3, nullptr, nullptr, nullptr};
    Node* c4 = new Node{4, nullptr, nullptr, nullptr};
    Node* c5 = new Node{5, nullptr, nullptr, nullptr};
    n1->next = n2; n2->prev = n1;
    n2->next = n3; n3->prev = n2;
    n2->child = c4;
    c4->next = c5; c5->prev = c4;
    Solution sol;
    Node* head = sol.flatten(n1);
    for (Node* cur = head; cur; cur = cur->next) cout << cur->val << (cur->next ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Splice child inline.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
DFS splice.
*/
