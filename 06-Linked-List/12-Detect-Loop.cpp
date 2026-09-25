/*
Problem: Detect Loop
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given a linked list head, return true if a cycle exists (Floyd slow/fast pointers), else false.
Sample Input: head = [3, 2, 0, -4] with tail to node 1
Sample Output: true
Explanation: The tail links back, forming a cycle.
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
    bool hasCycle(ListNode* h) {
        auto s = h, f = h;
        while (f && f->next) {
            s = s->next;
            f = f->next->next;
            if (s == f) return true;
        }
        return false;
    }
};

int main() {
    ListNode* n1 = new ListNode(3);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(0);
    ListNode* n4 = new ListNode(-4);
    n1->next = n2; n2->next = n3; n3->next = n4; n4->next = n2;
    Solution sol;
    cout << (sol.hasCycle(n1) ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Meet = cycle.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Floyd.
*/
