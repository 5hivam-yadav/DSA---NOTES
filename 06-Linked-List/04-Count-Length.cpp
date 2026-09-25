/*
Problem: Count Length
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given a linked list head, return the number of nodes by traversal.
Sample Input: head = [4, 2, 7]
Sample Output: 3
Explanation: Three nodes are visited.
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
int len(ListNode* h) {
    int c = 0;
    while (h) {
        c++;
        h = h->next;
    }
    return c;
}

int main() {
    ListNode* head = new ListNode(4);
    head->next = new ListNode(2);
    head->next->next = new ListNode(7);
    cout << len(head) << endl;
    return 0;
}

/*
Approach:
Walk and count.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Traversal.
*/
