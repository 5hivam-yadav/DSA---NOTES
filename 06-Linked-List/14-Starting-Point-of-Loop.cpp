/*
Problem: Starting Point of Loop
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given a linked list with a cycle, return the node where the cycle begins (meet, then restart one pointer at head).
Sample Input: head = [3, 2, 0, -4] with tail to node 1
Sample Output: node with 2
Explanation: Entry of the cycle holds 2.
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
    ListNode* detectCycle(ListNode* h) {
        auto s = h, f = h;
        while (f && f->next) {
            s = s->next;
            f = f->next->next;
            if (s == f) {
                s = h;
                while (s != f) {
                    s = s->next;
                    f = f->next;
                }
                return s;
            }
        }
        return nullptr;
    }
};

int main() {
    ListNode* n1 = new ListNode(3);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(0);
    ListNode* n4 = new ListNode(-4);
    n1->next = n2; n2->next = n3; n3->next = n4; n4->next = n2;
    Solution sol;
    ListNode* start = sol.detectCycle(n1);
    if (start) cout << "node with " << start->val << endl;
    return 0;
}

/*
Approach:
Meet then reset.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
mu from head.
*/
