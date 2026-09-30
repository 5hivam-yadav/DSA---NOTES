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
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
int len(ListNode *h) {
    int c = 0;
    while (h) {
        c++;
        h = h->next;
    }
    return c;
}

int main() {
    ListNode *head = new ListNode(4);
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
