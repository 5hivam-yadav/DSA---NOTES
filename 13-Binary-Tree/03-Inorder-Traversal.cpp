/*
Problem: Inorder Traversal
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Tree
Statement: Given a binary tree root, return its inorder traversal (left, node,
right) iteratively or recursively. Sample Input: root = [1,null,2,3] Sample
Output: [1,3,2] Explanation: Left of 2 is 3, so order is 1,3,2.
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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  public:
    void f(TreeNode *r, vector<int> &o) {
        if (!r)
            return;
        f(r->left, o);
        o.push_back(r->val);
        f(r->right, o);
    }
    vector<int> inorderTraversal(TreeNode *r) {
        vector<int> o;
        f(r, o);
        return o;
    }
};
// Iterative: stack, push-left spine.

/*
Approach:
Left, node, right.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
BST = sorted.
*/
