/*
Problem: Intersection Y
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given heads of two lists that may merge, return the intersection node or null (align lengths, then walk together).
Sample Input: listA = [4,1,8,4,5], listB = [5,6,1,8,4,5]
Sample Output: node with 8
Explanation: Tails merge starting at value 8.
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
    ListNode* getIntersectionNode(ListNode* a, ListNode* b) {
        auto p = a, q = b;
        while (p != q) {
            p = p ? p->next : b;
            q = q ? q->next : a;
        }
        return p;
    }
};

int main() {
    ListNode* common = new ListNode(8);
    common->next = new ListNode(4);
    common->next->next = new ListNode(5);

    ListNode* a = new ListNode(4);
    a->next = new ListNode(1);
    a->next->next = common;

    ListNode* b = new ListNode(5);
    b->next = new ListNode(6);
    b->next->next = new ListNode(1);
    b->next->next->next = common;

    Solution sol;
    ListNode* inter = sol.getIntersectionNode(a, b);
    if (inter) cout << "node with " << inter->val << endl;
    return 0;
}

/*
Approach:
a+b align.
Time Complexity:
O(n+m)
Space Complexity:
O(1)
Key Idea:
Equalize path.
*/
