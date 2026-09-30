/*
Problem: Preorder Traversal
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Tree
Statement: Given a binary tree root, return its preorder traversal (node, left,
right). Sample Input: root = [1,null,2,3] Sample Output: [1,2,3] Explanation:
Node first, then left, then right.
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
        o.push_back(r->val);
        f(r->left, o);
        f(r->right, o);
    }
    vector<int> preorderTraversal(TreeNode *r) {
        vector<int> o;
        f(r, o);
        return o;
    }
};

/*
Approach:
Node, left, right.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
Root first.
*/
