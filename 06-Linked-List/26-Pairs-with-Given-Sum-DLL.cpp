/*
Problem: Pairs with Given Sum Doubly Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Linked List
Statement: Given a sorted doubly linked list and target, return all pairs of values summing to target (two pointers from both ends).
Sample Input: head = [1, 2, 4, 5, 6], target = 7
Sample Output: [[1, 6], [2, 5]]
Explanation: 1+6 and 2+5 both equal 7.
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

struct DNode {
    int val;
    DNode* prev;
    DNode* next;
    DNode(int x): val(x), prev(nullptr), next(nullptr) {}
};
  // l=head, r=tail; while(l!=r && l->prev!=r){ s=l->val+r->val; if(s==k) record, l=l->next, r=r->prev; else if(s<k) l=l->next; else r=r->prev; }

static vector<pair<int, int>> findPairs(DNode* head, int target) {
    vector<pair<int, int>> ans;
    if (!head) return ans;
    DNode* tail = head;
    while (tail->next) tail = tail->next;
    DNode *l = head, *r = tail;
    while (l && r && l != r && r->next != l) {
        int sum = l->val + r->val;
        if (sum == target) {
            ans.push_back({l->val, r->val});
            l = l->next;
            r = r->prev;
        } else if (sum < target) {
            l = l->next;
        } else {
            r = r->prev;
        }
    }
    return ans;
}
int main() {
    vector<int> v = {1, 2, 4, 5, 6};
    DNode* head = new DNode(v[0]);
    DNode* cur = head;
    for (size_t i = 1; i < v.size(); i++) {
        DNode* n = new DNode(v[i]);
        cur->next = n; n->prev = cur; cur = n;
    }
    auto ans = findPairs(head, 7);
    cout << "[";
    for (size_t i = 0; i < ans.size(); i++) {
        cout << "[" << ans[i].first << ", " << ans[i].second << "]" << (i + 1 < ans.size() ? ", " : "");
    }
    cout << "]" << endl;
    return 0;
}

/*
Approach:
Two ends inward.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Sorted 2ptr.
*/
