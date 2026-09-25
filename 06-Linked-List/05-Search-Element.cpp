/*
Problem: Search Element
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given a linked list head and x, return true if some node holds x.
Sample Input: head = [1, 5, 3], x = 5
Sample Output: true
Explanation: Node with 5 is found.
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
bool find(ListNode* h, int x) {
    while (h) {
        if (h->val == x) return true;
        h = h->next;
    }
    return false;
}

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(5);
    head->next->next = new ListNode(3);
    cout << (find(head, 5) ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Walk compare.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Linear scan.
*/
