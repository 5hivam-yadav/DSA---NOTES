/*
Problem: Check Palindrome Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Linked List
Statement: Given a linked list head, return true if the values form a palindrome
(O(n) time, O(1) space). Sample Input: head = [1, 2, 2, 1] Sample Output: true
Explanation: The sequence mirrors itself.
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

class Solution {
  public:
    bool isPalindrome(ListNode *h) {
        vector<int> v;
        while (h) {
            v.push_back(h->val);
            h = h->next;
        }
        int l = 0, r = (int)v.size() - 1;
        while (l < r)
            if (v[l++] != v[r--])
                return false;
        return true;
    }
};
// Optimal O(1): reverse second half.

static ListNode *build(const vector<int> &v) {
    ListNode d(0);
    ListNode *t = &d;
    for (int x : v) {
        t->next = new ListNode(x);
        t = t->next;
    }
    return d.next;
}
int main() {
    ListNode *head = build({1, 2, 2, 1});
    Solution sol;
    cout << (sol.isPalindrome(head) ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Copy + 2ptr.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Array mirror check.
*/
