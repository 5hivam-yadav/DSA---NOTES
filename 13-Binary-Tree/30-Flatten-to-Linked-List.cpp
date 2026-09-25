/*
Problem: Flatten to Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, flatten it in place to a right-skewed list in preorder (reverse-postorder with prev pointer, or Morris).
Sample Input: root = [1,2,5,3,4,null,6]
Sample Output: [1,null,2,null,3,null,4,null,5,null,6]
Explanation: Preorder chain 1->2->3->4->5->6.
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

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    void flatten(TreeNode* r) {
        auto c = r;
        while (c) {
            if (c->left) {
                auto p = c->left;
                while (p->right) p = p->right;
                p->right = c->right;
                c->right = c->left;
                c->left = nullptr;
            }
            c = c->right;
        }
    }
};
  // Reverse-postorder with prev pointer also O(n)/O(h).

/*
Approach:
Graft right onto predecessor.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Morris-style splice.
*/
