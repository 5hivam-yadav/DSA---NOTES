/*
Problem: Delete Node
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given a linked list head and value x, delete the first node holding x and return the head.
Sample Input: head = [1, 2, 3], x = 2
Sample Output: [1, 3]
Explanation: Node 2 is unlinked.
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
    void deleteNode(ListNode* n) {
        n->val = n->next->val;
        ListNode* t = n->next;
        n->next = n->next->next;
        delete t;
    }
};

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    Solution sol;
    sol.deleteNode(head->next);
    for (ListNode* cur = head; cur; cur = cur->next) {
        cout << cur->val << (cur->next ? " " : "");
    }
    cout << endl;
    return 0;
}

/*
Approach:
Copy next + bypass.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
No head given trick.
*/
