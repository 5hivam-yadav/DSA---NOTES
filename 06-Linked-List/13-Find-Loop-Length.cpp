/*
Problem: Find Loop Length
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Given a linked list with a cycle, return the cycle length (meet with Floyd, then walk one lap).
Sample Input: head = [1, 2, 3, 4] with tail to node 1
Sample Output: 4
Explanation: The loop contains all four nodes.
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
int loopLen(ListNode* h) {
    auto s = h, f = h;
    while (f && f->next) {
        s = s->next;
        f = f->next->next;
        if (s == f) {
            int c = 1;
            f = f->next;
            while (f != s) {
                c++;
                f = f->next;
            }
            return c;
        }
    }
    return 0;
}

int main() {
    ListNode* n1 = new ListNode(1);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(3);
    ListNode* n4 = new ListNode(4);
    n1->next = n2; n2->next = n3; n3->next = n4; n4->next = n1;
    cout << loopLen(n1) << endl;
    return 0;
}

/*
Approach:
Meet then walk circle.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Count from meet.
*/
