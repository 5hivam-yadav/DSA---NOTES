/*
Problem: Clone with Random Pointer
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Linked List
Statement: Given a list where each node has next and random pointers, return a deep copy (interleave copies, fix randoms, split).
Sample Input: head = [[7,null],[13,0],[11,4]]
Sample Output: deep copy of the same structure
Explanation: Each copy keeps the same val/next/random shape.
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
    Node* next;
    Node* random;
    Node(int x): val(x), next(nullptr), random(nullptr) {}
};

class Solution {
public:
    Node* copyRandomList(Node* h) {
        if (!h) return nullptr;
        auto t = h;
        while (t) {
            auto n = new Node(t->val);
            n->next = t->next;
            t->next = n;
            t = n->next;
        }
        t = h;
        while (t) {
            if (t->random) t->next->random = t->random->next;
            t = t->next->next;
        }
        t = h;
        Node* nh = h->next;
        while (t) {
            auto c = t->next;
            t->next = c->next;
            if (c->next) c->next = c->next->next;
            t = t->next;
        }
        return nh;
    }
};
  // Hashmap O(n)/O(n) simpler.

int main() {
    Node* n7 = new Node(7);
    Node* n13 = new Node(13);
    Node* n11 = new Node(11);
    n7->next = n13; n13->next = n11;
    n13->random = n7;
    Solution sol;
    Node* copy = sol.copyRandomList(n7);
    cout << "deep copy of the same structure" << endl;
    return 0;
}

/*
Approach:
Interleave clones.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
next->random trick.
*/
